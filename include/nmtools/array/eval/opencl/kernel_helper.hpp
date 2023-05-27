#ifndef NMTOOLS_ARRAY_EVAL_OPENCL_KERNEL_HELPER_HPP
#define NMTOOLS_ARRAY_EVAL_OPENCL_KERNEL_HELPER_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/ndarray.hpp"
#include "nmtools/array/index/product.hpp"
#include "nmtools/array/view/ref.hpp"
#include "nmtools/array/view/mutable_ref.hpp"
#include "nmtools/array/view/flatten.hpp"
#include "nmtools/array/view/mutable_flatten.hpp"
#include "nmtools/array/view/reshape.hpp"

#ifdef NMTOOLS_OPENCL_KERNEL_MAX_DIM
#define NMTOOLS_OPENCL_KERNEL_MAX_DIM_ NMTOOLS_OPENCL_KERNEL_MAX_DIM 
#else
#define NMTOOLS_OPENCL_KERNEL_MAX_DIM_ 8
#endif

namespace nmtools::array::opencl
{
    struct create_vector_t {};

    template <auto DIM=0, typename size_type, typename type>
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

    template <auto DIM=0, typename dim_type=unsigned long, typename size_type=unsigned long, typename type>
    auto create_array(const type* data_ptr, const size_type* shape_ptr, dim_type dim)
    {
        auto shape = create_vector<DIM>(shape_ptr,dim);
        auto numel = index::product(shape);

        auto ref = view::ref(data_ptr,numel);
        return view::reshape(ref,shape);
    }

    template <auto DIM=0, typename dim_type=unsigned long, typename size_type=unsigned long, typename type>
    auto create_mutable_array(type* data_ptr, const size_type* shape_ptr, dim_type dim)
    {
        const auto shape = create_vector<DIM>(shape_ptr,dim);
        const auto numel = index::product(shape);

        auto ref = view::mutable_ref(data_ptr,numel);
        return view::reshape(ref,shape);
    }

    template <typename mutable_vector_t, typename vector_t>
    auto assign_vector(mutable_vector_t& lhs, const vector_t& rhs)
    {
        auto size = nmtools::size(lhs);
        for (size_t i=0; i<size; i++) {
            at(lhs,i) = at(rhs,i);
        }
    }

    #ifdef __OPENCL_VERSION__
    template <typename mutable_array_t, typename array_t>
    auto assign_array(mutable_array_t& output, const array_t& input)
    {
        auto size = nmtools::size(output);
        auto idx = get_global_id(0);
        if (idx < size) {
            auto flat_lhs = view::mutable_flatten(output);
            auto flat_rhs = view::flatten(input);
            flat_lhs(idx) = flat_rhs(idx);
        }
    }
    #endif // __OPENCL_VERSION__
} // namespace nmtools::array::opencl

namespace nmtools::meta
{
    template <auto DIM, typename data_type>
    struct resolve_optype<
        void, array::opencl::create_vector_t, as_type<DIM>, data_type
    >
    {
        static constexpr auto vtype = [](){
            if constexpr (DIM <= 0) {
                using type = utl::static_vector<remove_address_space_t<data_type>,NMTOOLS_OPENCL_KERNEL_MAX_DIM_>;
                return as_value_v<type>;
            } else {
                using type = nmtools_array<remove_address_space_t<data_type>,DIM>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
}

#undef NMTOOLS_OPENCL_KERNEL_MAX_DIM_

#endif // NMTOOLS_ARRAY_EVAL_OPENCL_KERNEL_HELPER_HPP