#ifndef NMTOOLS_ARRAY_EVAL_OPENCL_KERNEL_HELPER_HPP
#define NMTOOLS_ARRAY_EVAL_OPENCL_KERNEL_HELPER_HPP

#include "nmtools/meta.hpp"
#include "nmtools/ndarray.hpp"
#include "nmtools/array/index/product.hpp"
#include "nmtools/array/view/ref.hpp"
#include "nmtools/array/view/mutable_ref.hpp"
#include "nmtools/array/view/flatten.hpp"
#include "nmtools/array/view/mutable_flatten.hpp"
#include "nmtools/array/view/reshape.hpp"
#include "nmtools/evaluator/kernel_helper.hpp"

#ifndef nm_cl_index_t
#ifdef nm_index_t
#define nm_cl_index_t nm_index_t
#else // nm_index_t
using nmtools::uint32_t, nmtools::int32_t;
#define nm_cl_index_t int32_t
#endif // nm_index_t
#endif // nm_cl_index_t

#ifndef nm_cl_size_t
#ifdef nm_size_t
#define nm_cl_size_t nm_size_t
#else // nm_size_t
using nmtools::uint32_t, nmtools::int32_t;
#define nm_cl_size_t uint32_t
#endif // nm_size_t
#endif // nm_cl_size_t

namespace nmtools::array::opencl
{
    using ::nmtools::array::create_vector;
    using ::nmtools::array::create_array;
    using ::nmtools::array::create_mutable_array;

    template <typename mutable_vector_t, typename vector_t>
    auto assign_vector(mutable_vector_t& lhs, const vector_t& rhs)
    {
        auto size = nmtools::size(lhs);
        for (nm_cl_size_t i=0; i<(nm_cl_size_t)size; i++) {
            at(lhs,i) = at(rhs,i);
        }
    }

    #ifdef __OPENCL_VERSION__
    template <typename mutable_array_t, typename array_t>
    auto assign_array(mutable_array_t& output, const array_t& input)
    {
        auto valid = [&](){
            if constexpr (meta::is_maybe_v<array_t>) {
                return static_cast<bool>(input);
            } else {
                return true;
            }
        }();
        auto size = nmtools::size(output);
        auto idx = get_global_id(0);
        if (((nm_cl_size_t)idx < (nm_cl_size_t)size) && valid) {
            auto flat_lhs = view::mutable_flatten(output);
            auto flat_rhs = [&](){
                if constexpr (meta::is_maybe_v<array_t>) {
                    return view::flatten(*input);
                } else {
                    return view::flatten(input);
                }
            }();
            flat_lhs((nm_cl_index_t)idx) = flat_rhs((nm_cl_index_t)idx);
        }
    }
    #endif // __OPENCL_VERSION__
} // namespace nmtools::array::opencl

#endif // NMTOOLS_ARRAY_EVAL_OPENCL_KERNEL_HELPER_HPP