#ifndef NMTOOLS_ARRAY_NDARRAY_NDARRAY_HPP
#define NMTOOLS_ARRAY_NDARRAY_NDARRAY_HPP

#include "nmtools/array/index/product.hpp"
#include "nmtools/array/index/pack.hpp"
#include "nmtools/array/index/compute_strides.hpp"
#include "nmtools/array/index/compute_indices.hpp"
#include "nmtools/array/index/compute_offset.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/utility.hpp"

// experimental version that combine all three to single class

namespace nmtools::array
{

    template <typename T>
    struct base_ndarray_t
    {
        template <typename shape_type, typename buffer_type>
        static constexpr auto initialize_shape(const buffer_type& buffer)
        {
            if constexpr (meta::is_constant_index_array_v<shape_type>) {
                return shape_type {};
            } else /* if constexpr (meta::is_fixed_index_array_v<shape_type>) */ {
                auto shape = shape_type {};
                if constexpr (meta::is_resizeable_v<shape_type>) {
                    shape.resize(1);
                }
                using index_type = meta::get_element_type_t<shape_type>;
                for (size_t i=0; i<len(shape)-1; i++) {
                    at(shape,i) = (index_type)1;
                }
                at(shape,len(shape)-1) = len(buffer);
                return shape;
            }
        }

        template <typename buffer_type>
        static constexpr auto initialize_data()
        {
            auto buffer = buffer_type {};
            if constexpr (meta::is_resizeable_v<buffer_type>) {
                buffer.resize(1);
            }
            at(buffer,len(buffer)-1) = 1;
            return buffer;
        }

        template <typename strides_type, typename shape_type>
        static constexpr auto compute_strides(const shape_type& shape)
        {
            auto strides = strides_type{};
            auto result  = index::compute_strides(shape);
            [[maybe_unused]] auto dim = len(result);
            if constexpr (meta::is_resizeable_v<strides_type>) {
                strides.resize(dim);
            }
            if constexpr (!meta::is_constant_index_array_v<strides_type>) {
                for (size_t i=0; i<dim; i++) {
                    at(strides,i) = at(result,i);
                }
            }
            return strides;
        }

        constexpr T* self()
        {
            return static_cast<T*>(this);
        }

        constexpr const T* self() const
        {
            return static_cast<const T*>(this);
        }

        constexpr auto& shape() const
        {
            return self()->shape_;
        } // shape

        constexpr auto dim() const
        {
            return len(shape());
        } // dim

        constexpr auto& strides() const
        {
            return self()->strides_;
        }

        constexpr decltype(auto) data() const
        {
            return &self()->data_[0];
        } // data()

        constexpr auto size() const
        {
            return len(self()->data_);
        }

        template <typename...size_types>
        constexpr decltype(auto) operator()(const size_types&...indices)
        {
            auto indices_ = index::pack_indices(indices...);
            auto offset   = self()->offset(indices_,shape(),strides());
            return nmtools::at(self()->data_,offset);
        } // operator()

        template <typename...size_types>
        constexpr decltype(auto) operator()(const size_types&...indices) const
        {
            auto indices_ = index::pack_indices(indices...);
            auto offset   = self()->offset(indices_,shape(),strides());
            return nmtools::at(self()->data_,offset);
        } // operator()
    }; // base_ndarray_t

    template <typename shape_t, typename strides_t>
    struct row_major_offset_t
    {
        template <typename indices_t>
        constexpr auto operator()(const indices_t& indices, const shape_t&, const strides_t& strides) const
        {
            return index::compute_offset(indices,strides);
        } // operator()
    }; // row_major_offset_t

    template <typename shape_type>
    using resolve_stride_type_t = meta::resolve_optype_t<index::compute_strides_t,shape_type>;

    template <typename T, typename index_t
        , template <typename...>typename buffer_t
        , template <typename...>typename shape_buffer_t
        , template <typename...>typename stride_buffer_t=resolve_stride_type_t
        , template <typename...>typename compute_offset_t=row_major_offset_t
        , typename=void>
    struct ndarray_t : base_ndarray_t<ndarray_t<T, index_t, buffer_t, shape_buffer_t, stride_buffer_t, compute_offset_t>>
    {
        using buffer_type = buffer_t<T>;
        using value_type  = T;
        using index_type  = index_t;
        using shape_type  = shape_buffer_t<index_type>;
        using stride_type = stride_buffer_t<shape_type>;
        using base_type   = base_ndarray_t<ndarray_t>;
        using offset_type = compute_offset_t<shape_type,stride_type>;

        static_assert( meta::is_index_array_v<shape_type>, "unsupported shape_type for ndarray" );
        static_assert( meta::is_index_array_v<stride_type>, "unsupported stride_type for ndarray");

        buffer_type data_;
        shape_type  shape_;
        stride_type strides_;
        offset_type offset = {};

        constexpr ndarray_t()
            : data_     (base_type::template initialize_data<buffer_type>())
            , shape_    (base_type::template initialize_shape<shape_type>(data_))
            , strides_  (base_type::template compute_strides<stride_type>(shape_))
        {
            if constexpr (meta::is_resizeable_v<buffer_type>) {
                auto numel = index::product(shape_);
                // shape may be fixed while data is resizeable
                if (len(data_) != numel) {
                    data_.resize(numel);
                }
            }
        }

        template <typename size_type, typename...size_types>
        auto resize([[maybe_unused]] const size_type& size, const size_types&...sizes)
            -> meta::enable_if_t<
                   (meta::is_index_v<size_type> || meta::is_index_array_v<size_type>)
                && (meta::is_index_v<size_types> && ...)
                && (!meta::is_constant_index_array_v<shape_type>)
            , bool>
        {
            auto sizes_ = index::pack_indices(size,sizes...);
            auto newdim = len(sizes_);
            auto numel  = index::product(sizes_);
            if constexpr (meta::is_resizeable_v<shape_type>) {
                shape_.resize(newdim);
            }
            if constexpr (meta::is_resizeable_v<buffer_type>) {
                data_.resize(numel);
            }
            auto same_dim   = (index_type)len(shape_) == (index_type)newdim;
            auto same_numel = (index_type)len(data_)  == (index_type)numel;
            if (!same_dim || !same_numel) {
                return false;
            }
            for (size_t i=0; i<newdim; i++) {
                at(shape_,i) = at(sizes_,i);
            }
            strides_ = base_type::template compute_strides<stride_type>(shape_);
            return true;
        } // resize
    }; // ndarray_t

    enum class BufferKind : size_t {
        FIXED,
        DYNAMIC,
        HYBRID,         // hybrid with fixed upper bound
        HYBRID_DYNAMIC, // hybrid with resizeable upper bound
    };

    namespace error
    {
        template<typename...>
        struct MAKE_NDARRAY_UNSUPPORTED : meta::detail::fail_t {};
    } // namespace error

    template <typename shape_t, typename buffer_t>
    struct make_ndarray_t
    {
        static constexpr auto vtype = [](){
            return meta::as_value_v<error::MAKE_NDARRAY_UNSUPPORTED<shape_t,buffer_t>>;
        }();
        using type = meta::type_t<decltype(vtype)>;
    }; // make_ndarray_t
} // namespace nmtools::array

namespace nmtools::meta
{
    template <typename T, typename index_t
        , template <typename...>typename buffer_t
        , template <typename...>typename shape_buffer_t
        , template <typename...>typename stride_buffer_t
        , template <typename...>typename offset_compute_t>
    struct get_element_type<array::ndarray_t<T,index_t,buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>>
    {
        using array_type = array::ndarray_t<T,index_t,buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>;
        static constexpr auto vtype = [](){
            if constexpr (is_num_v<T>) {
                return as_value_v<T>;
            } else {
                return as_value_v<error::GET_ELEMENT_TYPE_UNSUPPORTED<array_type>>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // get_element_type

    template <typename T, typename index_t
        , template <typename...>typename buffer_t
        , template <typename...>typename shape_buffer_t
        , template <typename...>typename stride_buffer_t
        , template <typename...>typename offset_compute_t>
    struct is_ndarray<
        array::ndarray_t<T,index_t,buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>
    >
    {
        static constexpr auto value = is_num_v<T>;
    }; // is_ndarray

    template <typename T, typename index_t
        , template <typename...>typename buffer_t
        , template <typename...>typename shape_buffer_t
        , template <typename...>typename stride_buffer_t
        , template <typename...>typename offset_compute_t>
    struct fixed_dim<
        array::ndarray_t<T,index_t,buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>
    >
    {
        using array_type = array::ndarray_t<T,index_t,buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>;
        using shape_type = typename array_type::shape_type;

        static constexpr auto value = [](){
            if constexpr (is_fixed_index_array_v<shape_type>) {
                return len_v<shape_type>;
            } else {
                return error::FIXED_DIM_UNSUPPORTED<array_type>{};
            }
        }();
        using value_type = decltype(value);
    }; // fixed_dim

    // TODO: remove
    template <typename T, typename index_t
        , template <typename...>typename buffer_t
        , template <typename...>typename shape_buffer_t
        , template <typename...>typename stride_buffer_t
        , template <typename...>typename offset_compute_t>
    struct fixed_ndarray_shape<
        array::ndarray_t<T,index_t,buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>
    >
    {
        using array_type = array::ndarray_t<T,index_t,buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>;
        using shape_type = typename array_type::shape_type;

        static constexpr auto value = [](){
            if constexpr (is_constant_index_array_v<shape_type>) {
                return shape_type {};
            } else {
                return error::FIXED_SHAPE_UNSUPPORTED<array_type>{};
            }
        }();
        using value_type = decltype(value);
    }; // fixed_ndarray_shape

    template <typename T, typename index_t
        , template <typename...>typename buffer_t
        , template <typename...>typename shape_buffer_t
        , template <typename...>typename stride_buffer_t
        , template <typename...>typename offset_compute_t>
    struct fixed_shape<
        array::ndarray_t<T,index_t,buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>
    >
    {
        using array_type = array::ndarray_t<T,index_t,buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>;
        using shape_type = typename array_type::shape_type;

        static constexpr auto value = [](){
            if constexpr (is_constant_index_array_v<shape_type>) {
                return shape_type {};
            } else {
                return error::FIXED_SHAPE_UNSUPPORTED<array_type>{};
            }
        }();
        using value_type = decltype(value);
    }; // fixed_shape

    template <typename T, typename index_t
        , template <typename...>typename buffer_t
        , template <typename...>typename shape_buffer_t
        , template <typename...>typename stride_buffer_t
        , template <typename...>typename offset_compute_t>
    struct fixed_size<
        array::ndarray_t<T,index_t,buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>
    >
    {
        using array_type  = array::ndarray_t<T,index_t,buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>;
        using shape_type  = typename array_type::shape_type;
        using buffer_type = typename array_type::buffer_type;

        static constexpr auto value = [](){
            if constexpr (is_fixed_size_v<buffer_type>) {
                return fixed_size_v<buffer_type>;
            } else if constexpr (is_constant_index_array_v<shape_type>) {
                return index::product(shape_type{});
            } else {
                return error::FIXED_SIZE_UNSUPPORTED<array_type>{};
            }
        }();
        using value_type = decltype(value);
    }; // fixed_size

    template <typename T, typename index_t
        , template <typename...>typename buffer_t
        , template <typename...>typename shape_buffer_t
        , template <typename...>typename stride_buffer_t
        , template <typename...>typename offset_compute_t>
    struct bounded_dim<
        array::ndarray_t<T,index_t,buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>
    >
    {
        using array_type  = array::ndarray_t<T,index_t,buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>;
        using shape_type  = typename array_type::shape_type;
        using buffer_type = typename array_type::buffer_type;

        static constexpr auto value = [](){
            if constexpr (is_bounded_size_v<shape_type>) {
                return bounded_size_v<shape_type>;
            } else if constexpr (is_fixed_size_v<shape_type>) {
                // TODO: consider to add error mapping fn so this else-if/else block not needed
                return fixed_size_v<shape_type>;
            } else {
                return error::BOUNDED_DIM_UNSUPPORTED<array_type>{};
            }
        }();
        using value_type = decltype(value);
    }; // bounded_dim

    template <typename T, typename index_t
        , template <typename...>typename buffer_t
        , template <typename...>typename shape_buffer_t
        , template <typename...>typename stride_buffer_t
        , template <typename...>typename offset_compute_t>
    struct bounded_size<
        array::ndarray_t<T,index_t,buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>
    >
    {
        using array_type  = array::ndarray_t<T,index_t,buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>;
        using shape_type  = typename array_type::shape_type;
        using buffer_type = typename array_type::buffer_type;

        static constexpr auto value = [](){
            if constexpr (is_bounded_size_v<buffer_type>) {
                return bounded_size_v<buffer_type>;
            } else if constexpr (is_fixed_size_v<array_type>) {
                return fixed_size_v<array_type>;
            } else {
                return error::BOUNDED_SIZE_UNSUPPORTED<array_type>{};
            }
        }();
        using value_type = decltype(value);
    };

    template <typename T, typename index_t
        , template <typename...>typename buffer_t
        , template <typename...>typename shape_buffer_t
        , template <typename...>typename stride_buffer_t
        , template <typename...>typename offset_compute_t
        , auto...new_shape>
    struct resize_shape<
        array::ndarray_t<T,index_t,buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>
        , as_type<new_shape...>
    >
    {
        using array_type  = array::ndarray_t<T,index_t,buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>;
        using shape_type  = typename array_type::shape_type;
        using buffer_type = typename array_type::buffer_type;

        // NOTE: must be alias template since ndarray_t expect class template for shape_type
        template <typename...>
        using new_shape_type = nmtools_tuple<ct<new_shape>...>;

        // TODO: check if buffer type is sufficient
        using type = array::ndarray_t<T,index_t,buffer_t,new_shape_type,array::resolve_stride_type_t,offset_compute_t>;
    };

    template <typename T, typename index_t
        , template <typename...>typename buffer_t
        , template <typename...>typename shape_buffer_t
        , template <typename...>typename stride_buffer_t
        , template <typename...>typename offset_compute_t
        , auto new_size>
    struct resize_dim<
        array::ndarray_t<T,index_t,buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>
        , new_size
    >
    {
        using array_type  = array::ndarray_t<T,index_t,buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>;
        using shape_type  = typename array_type::shape_type;
        using buffer_type = typename array_type::buffer_type;

        // NOTE: must be alias template since ndarray_t expect class template for shape_type
        template <typename index_type>
        using new_shape_type = nmtools_array<index_type,new_size>;

        using type = array::ndarray_t<T,index_t,buffer_t,new_shape_type,array::resolve_stride_type_t,offset_compute_t>;
    };

    template <typename T, typename index_t
        , template <typename...>typename buffer_t
        , template <typename...>typename shape_buffer_t
        , template <typename...>typename stride_buffer_t
        , template <typename...>typename offset_compute_t
        , auto new_size>
    struct resize_size<
        array::ndarray_t<T,index_t,buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>
        , new_size
    >
    {
        using array_type  = array::ndarray_t<T,index_t,buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>;
        using shape_type  = typename array_type::shape_type;
        using buffer_type = typename array_type::buffer_type;

        // NOTE: must be alias template since ndarray_t expect class template for shape_type
        template <typename data_type>
        using new_buffer_type = nmtools_array<data_type,new_size>;

        // TODO: check if shape type is sufficient
        using type = array::ndarray_t<T,index_t,new_buffer_type,shape_buffer_t,stride_buffer_t,offset_compute_t>;
    };

    template <typename T, typename U, typename index_t
        , template <typename...>typename buffer_t
        , template <typename...>typename shape_buffer_t
        , template <typename...>typename stride_buffer_t
        , template <typename...>typename offset_compute_t>
    struct replace_element_type<
        array::ndarray_t<T,index_t,buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>, U
    >
    {
        using type = array::ndarray_t<U,index_t,buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>;
    }; // replace_element_type
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_NDARRAY_NDARRAY_HPP