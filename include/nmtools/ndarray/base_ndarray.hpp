#ifndef NMTOOLS_ARRAY_NDARRAY_BASE_NDARRAY_HPP
#define NMTOOLS_ARRAY_NDARRAY_BASE_NDARRAY_HPP

#include "nmtools/index/product.hpp"
#include "nmtools/index/pack.hpp"
#include "nmtools/index/compute_strides.hpp"
#include "nmtools/index/compute_indices.hpp"
#include "nmtools/index/compute_offset.hpp"
#include "nmtools/index/reverse.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/utility/at.hpp"
#include "nmtools/utility/cast.hpp"
#include "nmtools/utility/get.hpp"

// experimental version that combine all three to single class

namespace nmtools::array
{
    template <typename shape_t, typename strides_t>
    struct row_major_offset_t
    {
        using shape_type = shape_t;
        using strides_type = strides_t;

        shape_type shape_;
        strides_type strides_;

        constexpr row_major_offset_t(const shape_t& shape, const strides_t& strides)
            : shape_(shape)
            , strides_(strides)
        {}

        constexpr row_major_offset_t()
            : shape_{}
            , strides_{}
        {}

        constexpr row_major_offset_t(const row_major_offset_t& other)
            : shape_(other.shape_)
            , strides_(other.strides_)
        {}

        constexpr row_major_offset_t& operator=(const row_major_offset_t& other)
        {
            if constexpr (!meta::is_constant_index_array_v<shape_type>) {
                [[maybe_unused]] auto dim = len(other.shape_);
                if constexpr (meta::is_resizable_v<shape_type>) {
                    shape_.resize(dim);
                }
                constexpr auto N = meta::len_v<shape_type>;
                if constexpr (N>0) {
                    meta::template_for<N>([&](auto i){
                        at(shape_,i) = at(other.shape_,i);
                    });
                } else {
                    for (size_t i=0; i<dim; i++) {
                        at(shape_,i) = at(other.shape_,i);
                    }
                }
            }
            if constexpr (!meta::is_constant_index_array_v<strides_type>) {
                [[maybe_unused]] auto dim = len(other.strides_);
                if constexpr (meta::is_resizable_v<strides_type>) {
                    strides_.resize(dim);
                }
                constexpr auto N = meta::len_v<strides_type>;
                if constexpr (N>0) {
                    meta::template_for<N>([&](auto i){
                        at(strides_,i) = at(other.strides_,i);
                    });
                } else {
                    for (size_t i=0; i<dim; i++) {
                        at(strides_,i) = at(other.strides_,i);
                    }
                }
            }
            return *this;
        }

        template <typename indices_t>
        constexpr auto operator()(const indices_t& indices) const
        {
            return index::compute_offset(indices,strides_);
        } // operator()
    }; // row_major_offset_t

    template <typename shape_t, typename strides_t>
    struct column_major_offset_t
    {
        using shape_type = meta::remove_cvref_t<decltype(index::reverse(meta::declval<shape_t>()))>;
        using strides_type = meta::remove_cvref_t<decltype(index::reverse(index::compute_strides(meta::declval<shape_type>())))>;

        shape_type shape_;
        strides_type strides_;


        constexpr column_major_offset_t(const shape_t& shape, const strides_t&)
            : shape_(index::reverse(shape))
            , strides_(index::reverse(index::compute_strides(shape_)))
        {}

        constexpr column_major_offset_t(const column_major_offset_t& other)
            : shape_(other.shape_)
            , strides_(other.strides_)
        {}

        constexpr column_major_offset_t()
            : shape_{}
            , strides_{}
        {}

        constexpr column_major_offset_t& operator=(const column_major_offset_t& other)
        {
            if constexpr (!meta::is_constant_index_array_v<shape_type>) {
                [[maybe_unused]] auto dim = len(other.shape_);
                if constexpr (meta::is_resizable_v<shape_type>) {
                    shape_.resize(dim);
                }
                constexpr auto N = meta::len_v<shape_type>;
                if constexpr (N>0) {
                    meta::template_for<N>([&](auto i){
                        at(shape_,i) = at(other.shape_,i);
                    });
                } else {
                    for (size_t i=0; i<dim; i++) {
                        at(shape_,i) = at(other.shape_,i);
                    }
                }
            }
            if constexpr (!meta::is_constant_index_array_v<strides_type>) {
                [[maybe_unused]] auto dim = len(other.strides_);
                if constexpr (meta::is_resizable_v<strides_type>) {
                    strides_.resize(dim);
                }
                constexpr auto N = meta::len_v<strides_type>;
                if constexpr (N>0) {
                    meta::template_for<N>([&](auto i){
                        at(strides_,i) = at(other.strides_,i);
                    });
                } else {
                    for (size_t i=0; i<dim; i++) {
                        at(strides_,i) = at(other.strides_,i);
                    }
                }
            }
            return *this;
        }

        template <typename indices_t>
        constexpr auto operator()(const indices_t& indices) const
        {
            auto offset = index::compute_offset(indices,strides_);
            return offset;
        } // operator()
    };
} // namespace nmtools::array

namespace nmtools::meta
{
    template <typename T, typename=void>
    struct is_row_major_offset : false_type {};

    template <typename T, typename=void>
    struct is_column_major_offset : false_type {};

    template <typename T>
    struct is_row_major_offset<const T> : is_row_major_offset<T> {};

    template <typename T>
    struct is_row_major_offset<T&> : is_row_major_offset<T> {};

    template <typename T>
    struct is_column_major_offset<const T> : is_column_major_offset<T> {};

    template <typename T>
    struct is_column_major_offset<T&> : is_column_major_offset<T> {};

    template <typename shape_t, typename strides_t>
    struct is_row_major_offset<
        array::row_major_offset_t<shape_t,strides_t>
    > {
        static constexpr auto value = is_index_array_v<shape_t> && is_index_array_v<strides_t>;
    };

    template <typename shape_t, typename strides_t>
    struct is_column_major_offset<
        array::column_major_offset_t<shape_t,strides_t>
    > {
        static constexpr auto value = is_index_array_v<shape_t> && is_index_array_v<strides_t>;
    };

    template <typename T>
    constexpr inline auto is_row_major_offset_v = is_row_major_offset<T>::value;

    template <typename T>
    constexpr inline auto is_column_major_offset_v = is_column_major_offset<T>::value;
} // namespace nmtools::meta

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
                if constexpr (meta::is_resizable_v<shape_type>) {
                    shape.resize(1);
                }
                constexpr auto dim = meta::len_v<shape_type>;
                if constexpr (dim > 0) {
                    // to accommodate clipped shape
                    meta::template_for<dim>([&](auto index){
                        at(shape,index) = 1;
                    });
                } else {
                    for (size_t i=0; i<len(shape)-1; i++) {
                        at(shape,i) = 1;
                    }
                }
                at(shape,meta::ct_v<-1>) = len(buffer);
                return shape;
            }
        }

        template <typename buffer_type>
        static constexpr auto initialize_data()
        {
            auto buffer = buffer_type {};
            if constexpr (meta::is_resizable_v<buffer_type>) {
                buffer.resize(1);
            }
            at(buffer,len(buffer)-1) = 0;
            return buffer;
        }

        template <typename strides_type, typename shape_type>
        static constexpr auto compute_strides(const shape_type& shape)
        {
            auto result  = index::compute_strides(shape);
            if constexpr (meta::is_same_v<strides_type,decltype(result)>) {
                return result;
            } else {
                auto strides = strides_type{};
                [[maybe_unused]] auto dim = len(result);
                if constexpr (meta::is_resizable_v<strides_type>) {
                    strides.resize(dim);
                }
                if constexpr (!meta::is_constant_index_array_v<strides_type>) {
                    for (size_t i=0; i<dim; i++) {
                        at(strides,i) = at(result,i);
                    }
                }
                return strides;
            }
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

        constexpr decltype(auto) data()
        {
            return &self()->data_[0];
        } // data()

        constexpr auto size() const
        {
            using buffer_type = meta::remove_cvref_t<decltype(self()->data_)>;
            if constexpr (meta::is_fixed_size_v<buffer_type>) {
                constexpr auto size_ = meta::fixed_size_v<buffer_type>;
                return meta::ct_v<size_>;
            } else {
                // assume flat
                // return len(self()->data_);
                return index::product(shape());
            }
        }

        template <typename...size_types>
        constexpr decltype(auto) offset(const size_types&...indices) const
        {
            auto indices_ = index::pack_indices(indices...);
            auto offset   = self()->offset_(indices_);
            return offset;
        }

        template <typename...size_types>
        constexpr decltype(auto) operator()(const size_types&...indices)
        {
            return nmtools::at(self()->data_,offset(indices...));
        } // operator()

        template <typename...size_types>
        constexpr decltype(auto) operator()(const size_types&...indices) const
        {
            return nmtools::at(self()->data_,offset(indices...));
        } // operator()
    }; // base_ndarray_t

    template <typename shape_type>
    using resolve_stride_type_t = meta::resolve_optype_t<index::compute_strides_t,shape_type>;
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_NDARRAY_BASE_NDARRAY_HPP