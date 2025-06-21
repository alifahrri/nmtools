#ifndef NMTOOLS_ARRAY_EVAL_KERNEL_HELPER_HPP
#define NMTOOLS_ARRAY_EVAL_KERNEL_HELPER_HPP

#include "nmtools/def.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/ndarray.hpp"
#include "nmtools/index/product.hpp"
#include "nmtools/array/ref.hpp"
#include "nmtools/core/mutable_ref.hpp"
#include "nmtools/array/flatten.hpp"
#include "nmtools/core/mutable_flatten.hpp"
#include "nmtools/array/reshape.hpp"
#include "nmtools/ndarray/base_ndarray.hpp"
#include "nmtools/utility/unwrap.hpp"

#ifdef NMTOOLS_KERNEL_MAX_DIM
#define NMTOOLS_KERNEL_MAX_DIM_ NMTOOLS_KERNEL_MAX_DIM 
#else
#define NMTOOLS_KERNEL_MAX_DIM_ 8
#endif

#ifndef nm_stringify
#define nm_stringify(a) #a
#endif

namespace nmtools
{
    struct create_vector_t {};

    template <typename data_t, typename shape_t, typename dim_t>
    struct device_array : base_ndarray_t<device_array<data_t,shape_t,dim_t>>
    {
        using value_type  = data_t;
        using shape_type  = shape_t;
        using buffer_type = data_t*;
        using stride_type = resolve_stride_type_t<shape_type>;
        using offset_type = row_major_offset_t<shape_type,stride_type>;
        using base_type   = base_ndarray_t<device_array>;

        // TODO: make buffer not a pointer, wrap the pointer instead
        data_t* data_;
        shape_t shape_;
        dim_t dim_;
        stride_type strides_;
        offset_type offset_;

        nmtools_func_attribute
        device_array(data_t* data_, const shape_t& shape_, dim_t dim_)
            : data_   (data_)
            , shape_  (shape_)
            , dim_    (dim_)
            , strides_(base_type::template compute_strides<stride_type>(shape_))
            , offset_ (shape_,strides_)
        {}

        nmtools_func_attribute
        device_array(const device_array& other)
            : data_   (other.data_)
            , shape_  (other.shape_)
            , dim_    (other.dim_)
            , strides_(base_type::template compute_strides<stride_type>(shape_))
            , offset_ (shape_,strides_)
        {}
    };

    template <typename data_t, typename shape_t, typename dim_t>
    device_array(const data_t*, const shape_t&, dim_t) -> device_array<data_t,shape_t,dim_t>;

    template <typename T>
    nmtools_func_attribute
    auto create_array(T array)
        -> meta::enable_if_t<meta::is_num_v<T>,T>
    {
        return array;
    }

    template <typename data_t, typename shape_t, typename dim_t>
    nmtools_func_attribute
    auto create_array(const device_array<data_t,shape_t,dim_t>& array)
    {
        // assume array.shape_ is passed by value
        return create_array(array.data_,array.shape_);
    }

    template <auto DIM=0, typename size_type=nm_index_t, typename type>
    nmtools_func_attribute
    auto create_vector(const type* data_ptr, size_type dim)
    {
        using vector_t = meta::resolve_optype_t<create_vector_t,meta::as_type<DIM>,type>;
        auto vector = vector_t{};

        if constexpr (meta::is_resizable_v<vector_t>) {
            vector.resize(dim);
        }

        for (size_type i=0; i<dim; i++) {
            at(vector,i) = data_ptr[i];
        }

        return vector;
    }

    template <typename type, typename shape_type>
    nmtools_func_attribute
    auto create_array(const type* data_ptr, const shape_type& shape)
    {
        auto numel = index::product(shape);

        auto ref = view::ref(data_ptr,numel);
        auto reshaped = view::reshape(ref,shape);
        return reshaped;
    }

    template <auto DIM=0, typename dim_type=nm_index_t, typename size_type=nm_index_t, typename type>
    nmtools_func_attribute
    auto create_array(const type* data_ptr, const size_type* shape_ptr, dim_type dim)
    {
        auto shape = create_vector<DIM>(shape_ptr,dim);
        auto array = create_array(data_ptr,shape);
        return array;
    }

    template <auto DIM=0, typename dim_type=nm_index_t, typename size_type=nm_index_t, typename type>
    nmtools_func_attribute
    auto create_mutable_array(type* data_ptr, const size_type* shape_ptr, dim_type dim)
    {
        const auto shape = create_vector<DIM>(shape_ptr,dim);
        return device_array(data_ptr,shape,dim);
    }

    template <typename size_type=nm_size_t>
    struct kernel_size
    {
        size_type id[3];
        constexpr size_type x() const
        {
            return id[0];
        }
        constexpr size_type y() const
        {
            return id[1];
        }
        constexpr size_type z() const
        {
            return id[2];
        }
    };

    template <typename T>
    constexpr auto compute_offset(kernel_size<T> thread_id, kernel_size<T> block_id, kernel_size<T> block_size)
    {
        // TODO: check for grid shape
        auto idx = block_id.x() * block_size.x() + thread_id.x();
        return idx;
    }

    template <
        typename size_type=nm_size_t
        , typename mutable_array_t
        , typename array_t
    >
    nmtools_func_attribute
    auto assign_result(
        mutable_array_t& output
        , const array_t& result
        , kernel_size<size_type> thread_id
        , kernel_size<size_type> block_id
        , kernel_size<size_type> block_size
    ) {
        if constexpr (meta::is_maybe_v<meta::remove_cvref_t<decltype(result)>>) {
            if (!static_cast<bool>(result)) {
                return;
            }
            assign_result(output,*result,thread_id,block_id,block_size);
        } else if constexpr (meta::is_maybe_v<mutable_array_t>) {
            if (!static_cast<bool>(output)) {
                return;
            }
            assign_result(*output,result,thread_id,block_id,block_size);
        } else {
            auto size = nmtools::size(output);
            auto idx = compute_offset(thread_id,block_id,block_size);
            if (idx < size) {
                auto flat_lhs = unwrap(view::mutable_flatten(output));
                auto flat_rhs = unwrap(view::flatten(result));
                const auto rhs = flat_rhs(idx);
                auto& lhs = flat_lhs(idx);
                lhs = rhs;
            }
        }
    }
}

namespace nmtools::meta
{
    template <auto DIM, typename data_t>
    struct resolve_optype<
        void, array::create_vector_t, as_type<DIM>, data_t
    >
    {
        using data_type = remove_address_space_t<remove_cvref_t<data_t>>;
        static constexpr auto vtype = [](){
            if constexpr (DIM <= 0) {
                using type = utl::static_vector<data_type,NMTOOLS_KERNEL_MAX_DIM_>;
                return as_value_v<type>;
            } else {
                using type = nmtools_array<data_type,DIM>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };

    template <typename T, typename=void>
    struct is_device_array : false_type {};

    template <typename T>
    struct is_device_array<const T> : is_device_array<T> {};

    template <typename T>
    struct is_device_array<T&> : is_device_array<T> {};

    template <typename data_t, typename shape_t, typename dim_t>
    struct is_device_array<array::device_array<data_t,shape_t,dim_t>> : true_type {};

    template <typename T>
    constexpr inline auto is_device_array_v = is_device_array<T>::value;
}

namespace nmtools::meta
{
    template <typename data_t, typename shape_t, typename dim_t>
    struct get_element_type<array::device_array<data_t,shape_t,dim_t>>
    {
        using array_type = array::device_array<data_t,shape_t,dim_t>;
        static constexpr auto vtype = [](){
            using T = typename array_type::value_type;
            if constexpr (is_num_v<T>) {
                return as_value_v<T>;
            } else {
                return as_value_v<error::GET_ELEMENT_TYPE_UNSUPPORTED<array_type>>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // get_element_type

    template <typename data_t, typename shape_t, typename dim_t>
    struct is_ndarray<
        array::device_array<data_t,shape_t,dim_t>
    >
    {
        using array_type = array::device_array<data_t,shape_t,dim_t>;
        using element_type = typename array_type::value_type;
        static constexpr auto value = is_num_v<element_type>;
    }; // is_ndarray

    template <typename data_t, typename shape_t, typename dim_t>
    struct fixed_dim<
        array::device_array<data_t,shape_t,dim_t>
    >
    {
        using array_type = array::device_array<data_t,shape_t,dim_t>;
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

    template <typename data_t, typename shape_t, typename dim_t>
    struct fixed_shape<
        array::device_array<data_t,shape_t,dim_t>
    >
    {
        using array_type = array::device_array<data_t,shape_t,dim_t>;
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

    template <typename data_t, typename shape_t, typename dim_t>
    struct fixed_size<
        array::device_array<data_t,shape_t,dim_t>
    >
    {
        using array_type  = array::device_array<data_t,shape_t,dim_t>;
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

    template <typename data_t, typename shape_t, typename dim_t>
    struct bounded_dim<
        array::device_array<data_t,shape_t,dim_t>
    >
    {
        using array_type  = array::device_array<data_t,shape_t,dim_t>;
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

    template <typename data_t, typename shape_t, typename dim_t>
    struct bounded_size<
        array::device_array<data_t,shape_t,dim_t>
    >
    {
        using array_type  = array::device_array<data_t,shape_t,dim_t>;
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

    template <typename data_t, typename shape_t, typename dim_t>
    struct is_index_array<
        array::device_array<data_t,shape_t,dim_t>
    >
    {
        using array_type = array::device_array<data_t,shape_t,dim_t>;
        using shape_type = typename array_type::shape_type;

        static constexpr auto value = [](){
            constexpr auto dim = len_v<shape_type>;
            return (dim == 1)
                && is_index_v<get_element_type_t<data_t>>
            ;
        }();
    }; // is_index_array

    template <typename data_t, typename shape_t, typename dim_t>
    struct contiguous_axis<
        array::device_array<data_t,shape_t,dim_t>
    > {
        using array_type  = array::device_array<data_t,shape_t,dim_t>;
        using offset_type = typename array_type::offset_type;
        static constexpr auto value = [](){
            if constexpr (is_row_major_offset_v<offset_type>) {
                return -1;
            } else if constexpr (is_column_major_offset_v<offset_type>) {
                return 0;
            } else {
                return error::CONTIGUOUS_AXIS_UNSUPPORTED<array_type>{};
            }
        }();
    };
} // namespace nmtools::meta

#undef NMTOOLS_KERNEL_MAX_DIM_

#endif // NMTOOLS_ARRAY_EVAL_KERNEL_HELPER_HPP