#ifndef NMTOOLS_ARRAY_EVAL_X86_SIMD128_HPP
#define NMTOOLS_ARRAY_EVAL_X86_SIMD128_HPP

#include "nmtools/array/eval.hpp"
#include "nmtools/array/data.hpp"
#include "nmtools/array/view/ufuncs/sqrt.hpp"
#include "nmtools/array/view/ufuncs/ceil.hpp"
#include "nmtools/array/view/ufuncs/floor.hpp"
#include "nmtools/array/view/ufuncs/reciprocal.hpp"
#include "nmtools/array/view/activations/hardtanh.hpp"
#include "nmtools/array/view/activations/relu.hpp"
#include "nmtools/array/view/activations/relu6.hpp"

#include <x86intrin.h>

namespace nmtools::array
{
    struct simd_x86_128_t
    {
        // TODO: support aligned load/store
        template <typename T>
        inline auto loadu(const T* inp_ptr) const noexcept
        {
            if constexpr (std::is_same_v<T,float>) {
                return _mm_loadu_ps(inp_ptr);
            } else if constexpr (std::is_same_v<T,double>) {
                return _mm_loadu_pd(inp_ptr);
            }
        }

        template <typename T, typename simd_t>
        inline auto storeu(T* out_ptr, const simd_t simd) const noexcept
        {
            // assume simd_t & T is compatible (float & _m128; double & _m128d)
            if constexpr (std::is_same_v<T,float>) {
                _mm_storeu_ps(out_ptr,simd);
            } else if constexpr (std::is_same_v<T,double>) {
                _mm_storeu_pd(out_ptr,simd);
            }
        }

        template <typename op_t>
        inline auto eval([[maybe_unused]] op_t op, __m128 a) const noexcept
        {
            if constexpr (meta::is_same_v<op_t,view::sqrt_t>) {
                return _mm_sqrt_ps(a);
            } else if constexpr (meta::is_same_v<op_t,view::ceil_t>) {
                return _mm_ceil_ps(a);
            } else if constexpr (meta::is_same_v<op_t,view::floor_t>) {
                return _mm_floor_ps(a);
            } else if constexpr (meta::is_same_v<op_t,view::relu_t>) {
                return _mm_max_ps(a,_mm_set1_ps(0.0f));
            } else if constexpr (meta::is_same_v<op_t,view::relu6_t>) {
                const auto b = _mm_min_ps(a,_mm_set1_ps(6.0f));
                return _mm_max_ps(b,_mm_set1_ps(0.0f));
            } else if constexpr (meta::is_same_v<op_t,view::hardtanh_t<float>>) {
                const auto min_val = _mm_set1_ps(op.min_val);
                const auto max_val = _mm_set1_ps(op.max_val);
                auto b = _mm_max_ps(a,min_val);
                return _mm_min_ps(b,max_val);
            }
            
            else if constexpr (meta::is_same_v<op_t,view::reciprocal_t>) {
                return _mm_rcp_ps(a);
            }
        }

        template <typename op_t>
        inline auto eval([[maybe_unused]] op_t op, __m128d a) const noexcept
        {
            if constexpr (meta::is_same_v<op_t,view::sqrt_t>) {
                return _mm_sqrt_pd(a);
            } else if constexpr (meta::is_same_v<op_t,view::ceil_t>) {
                return _mm_ceil_pd(a);
            } else if constexpr (meta::is_same_v<op_t,view::floor_t>) {
                return _mm_floor_pd(a);
            } else if constexpr (meta::is_same_v<op_t,view::relu_t>) {
                return _mm_max_pd(a,_mm_set1_pd(0.0f));
            } else if constexpr (meta::is_same_v<op_t,view::relu6_t>) {
                auto b = _mm_min_pd(a,_mm_set1_pd(6.0f));
                return _mm_max_pd(b,_mm_set1_pd(0.0f));
            } else if constexpr (meta::is_same_v<op_t,view::hardtanh_t<double>>) {
                const auto min_val = _mm_set1_pd(op.min_val);
                const auto max_val = _mm_set1_pd(op.max_val);
                auto b = _mm_max_pd(a,min_val);
                return _mm_min_pd(b,max_val);
            }
        }
    };

    template <typename view_t, typename resolver_t>
    struct evaluator_t<view_t,simd_x86_128_t,resolver_t>
    {
        using view_type    = const view_t&;
        using output_type  = meta::resolve_optype_t<resolver_t,view_t,none_t>;
        using context_type = const simd_x86_128_t&;
        using op_type      = typename view_t::op_type;

        view_type view;
        context_type context;

        template <typename output_t>
        constexpr auto operator()(output_t& output) const
            -> meta::enable_if_t<meta::is_ndarray_v<output_t>>
        {
            auto out_shape = ::nmtools::shape(output);
            auto inp_shape = ::nmtools::shape(view);

            // TODO: provide common base/utility for error handling

            if (!::nmtools::utils::isequal(out_shape,inp_shape))
                return;

            using ::nmtools::index::ndindex;
            auto out_index = ndindex(out_shape);
            auto inp_index = ndindex(inp_shape);

            using element_type = meta::get_element_type_t<output_t>;
            // TODO: do not static assert, tell the caller some combo is not supported
            static_assert(meta::is_floating_point_v<element_type>
                , "currently only support float/double");

            // NOTE: assume unary ufunc
            // TODO: generalize
            auto inp_ptr = nmtools::data(*nmtools::get<0>(view.operands));
            auto out_ptr = nmtools::data(output);

            constexpr auto N = 128 / (sizeof(element_type) * 8); // 8 means 8-bit

            const auto size = inp_index.size();
            // ex: 5 float; N=4; i=0..(5-4)
            // ex: 3 float; N=4; i=0..(3-4)
            const auto op = view.op;
            for (size_t i=0; (i+N)<=size; i+=N) {
                // TODO: support aligned load/store
                const auto a = context.loadu(&inp_ptr[i]);
                const auto b = context.eval(op,a);
                context.storeu(&out_ptr[i],b);
            }

            // the rest of data
            // ex: 5 float, N=128/32=4; 5/4=1; i=1*4=4
            // ex: 3 float, N=4; M=3/4=0; i=M*N=0
            auto M = (size / N);
            for (size_t i=(M*N); i<size; i++) {
                // while the shape is the same,
                // the underlying type of indexing may be not
                auto inp_idx = inp_index[i];
                auto out_idx = out_index[i];
                apply_at(output,out_idx) = apply_at(view,inp_idx);
            }
        } // operator()

        // TODO: provide common base/utility
        template <typename output_t>
        constexpr auto operator()(output_t& output) const
            -> meta::enable_if_t<meta::is_num_v<output_t>>
        {
            output = static_cast<output_t>(view);
        } // operator()

        // TODO: provide common base/utility
        template <typename output_t=output_type, meta::enable_if_t<!meta::is_void_v<output_t>,int> = 0>
        constexpr auto operator()() const
        {
            using result_t = meta::transform_bounded_array_t<output_t>;
            auto output = result_t{};
            if constexpr (meta::is_resizable_v<result_t>) {
                auto inp_shape = ::nmtools::shape(view);
                ::nmtools::detail::apply_resize(output,inp_shape);
            }

            (*this)(output);

            return output;
        } // operator()

        // TODO: provide common base/utility
        template <typename output_t>
        constexpr auto operator()(meta::as_value<output_t>) const
        {
            return (*this).template operator()<output_t>();
        } // operator()

        // TODO: provide common base/utility
        constexpr auto operator()(none_t) const
        {
            return (*this)();
        } // operator()
    };

    constexpr auto Simd128x86 = simd_x86_128_t {};
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_EVAL_X86_SIMD128_HPP