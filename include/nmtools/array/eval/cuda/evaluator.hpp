#ifndef NMTOOLS_ARRAY_EVAL_CUDA_EVALUATOR_HPP
#define NMTOOLS_ARRAY_EVAL_CUDA_EVALUATOR_HPP

#include "nmtools/array/eval.hpp"
#include "nmtools/array/data.hpp"
#include "nmtools/array/eval/cuda/context.hpp"
#include "nmtools/array/functional.hpp"

namespace nmtools::array
{
    template <typename view_t, typename resolver_t>
    struct evaluator_t<view_t,std::shared_ptr<cuda::context_t>,resolver_t>
    {
        using view_type = const view_t&;
        using output_type  = meta::resolve_optype_t<resolver_t,view_t,none_t>;
        using context_type = std::shared_ptr<cuda::context_t>;

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

            auto f = functional::get_function_composition(view);
            const auto& operands = functional::get_function_operands(view);

            context->run(f,output,operands);
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
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_EVAL_CUDA_EVALUATOR_HPP