#ifndef NMTOOLS_ARRAY_EVAL_KERNEL_HELPER_HPP
#define NMTOOLS_ARRAY_EVAL_KERNEL_HELPER_HPP

#include "nmtools/def.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/array/ndarray.hpp"
#include "nmtools/array/index/product.hpp"
#include "nmtools/array/view/ref.hpp"
#include "nmtools/array/view/mutable_ref.hpp"
#include "nmtools/array/view/flatten.hpp"
#include "nmtools/array/view/mutable_flatten.hpp"
#include "nmtools/array/view/reshape.hpp"
#include "nmtools/utility/unwrap.hpp"

#ifdef NMTOOLS_KERNEL_MAX_DIM
#define NMTOOLS_KERNEL_MAX_DIM_ NMTOOLS_KERNEL_MAX_DIM 
#else
#define NMTOOLS_KERNEL_MAX_DIM_ 8
#endif

#ifndef nm_stringify
#define nm_stringify(a) #a
#endif

namespace nmtools::array
{
    struct create_vector_t {};

    template <typename data_t, typename shape_t, typename dim_t>
    struct device_array
    {
        data_t* buffer;
        shape_t shape;
        dim_t dim;
    };

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
        // assume array.shape is passed by value
        return create_array(array.buffer,array.shape);
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

    template <typename type, typename shape_type>
    nmtools_func_attribute
    auto create_mutable_array(type* data_ptr, const shape_type& shape)
    {
        const auto numel = index::product(shape);

        auto ref = view::mutable_ref(data_ptr,numel);
        return view::reshape(ref,shape);
    }

    template <auto DIM=0, typename dim_type=nm_index_t, typename size_type=nm_index_t, typename type>
    nmtools_func_attribute
    auto create_mutable_array(type* data_ptr, const size_type* shape_ptr, dim_type dim)
    {
        const auto shape = create_vector<DIM>(shape_ptr,dim);
        return create_mutable_array(data_ptr,shape);
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
        if constexpr (meta::is_maybe_v<array_t>) {
            if (!static_cast<bool>(result)) {
                return;
            }
            assign_result(output,*result,thread_id,block_id,block_size);
        } else {
            auto size = nmtools::size(output);
            auto idx = block_id.x() * block_size.x() + thread_id.x();
            if (idx < size) {
                auto flat_lhs = view::mutable_flatten(output);
                auto flat_rhs = view::flatten(result);
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

#undef NMTOOLS_KERNEL_MAX_DIM_

#endif // NMTOOLS_ARRAY_EVAL_KERNEL_HELPER_HPP