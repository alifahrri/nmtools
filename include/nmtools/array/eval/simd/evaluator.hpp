#ifndef NMTOOLS_ARRAY_EVAL_SIMD_BASE_HPP
#define NMTOOLS_ARRAY_EVAL_SIMD_BASE_HPP

#include "nmtools/array/eval.hpp"
#include "nmtools/array/data.hpp"
#include "nmtools/array/eval/simd/ufunc.hpp"

namespace nmtools::array
{
    template <typename simd_tag_t>
    struct simd_base_t
    {
        template <typename dtype_t,typename op_type>
        static inline auto create_simd_op(op_type op)
        {
            // TODO: tell the caller some combo is not supported
            using simd_t = simd::ufunc_simd_t<op_type,simd_tag_t,dtype_t>;
            return simd_t{op};
        }
    };

    template <typename view_t, typename simd_tag_t, typename resolver_t>
    struct evaluator_t<view_t,simd_base_t<simd_tag_t>,resolver_t>
    {
        using view_type    = const view_t&;
        using output_type  = meta::resolve_optype_t<resolver_t,view_t,none_t>;
        using context_type = const simd_base_t<simd_tag_t>&;
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

            const auto op = context.template create_simd_op<element_type>(view.op);
            const auto N = op.bit_width / (sizeof(element_type) * 8); // 8 means 8-bit

            const auto size = inp_index.size();
            // ex: 5 float; N=4; i=0..(5-4)
            // ex: 3 float; N=4; i=0..(3-4)
            for (size_t i=0; (i+N)<=size; i+=N) {
                // TODO: support aligned load/store
                const auto a = op.loadu(&inp_ptr[i]);
                const auto b = op.eval(a);
                op.storeu(&out_ptr[i],b);
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
}

#endif // NMTOOLS_ARRAY_EVAL_SIMD_BASE_HPP