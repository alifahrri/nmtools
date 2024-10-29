#ifndef NMTOOLS_ARRAY_EVAL_OPENCL_EVALUATOR_HPP
#define NMTOOLS_ARRAY_EVAL_OPENCL_EVALUATOR_HPP

#include "nmtools/array/eval.hpp"
#include "nmtools/utility/data.hpp"
#include "nmtools/array/eval/opencl/context.hpp"

#include <memory>

namespace nmtools::array
{
    template <typename view_t, typename resolver_t>
    struct evaluator_t<view_t,std::shared_ptr<opencl::context_t>,resolver_t>
    {
        using view_type    = const view_t&;
        static constexpr auto output_vtype = [](){
            using output_type  = meta::resolve_optype_t<resolver_t,view_t,none_t>;
            using element_type = meta::get_element_type_t<output_type>;
            if constexpr (meta::is_same_v<element_type,bool>) {
                using result_type = meta::replace_element_type_t<output_type,uint8_t>;
                return meta::as_value_v<result_type>;
            } else {
                return meta::as_value_v<output_type>;
            }
        }();
        using output_type  = meta::type_t<decltype(output_vtype)>;
        using context_type = std::shared_ptr<opencl::context_t>;

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
            [[maybe_unused]] auto out_index = ndindex(out_shape);
            [[maybe_unused]] auto inp_index = ndindex(inp_shape);

            using element_type [[maybe_unused]] = meta::get_element_type_t<output_t>;

            auto kernel = opencl::kernel_t<view_t>{view,context};

            kernel.eval(output);
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

#endif // NMTOOLS_ARRAY_EVAL_OPENCL_EVALUATOR_HPP