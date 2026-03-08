#ifndef NMTOOLS_CORE_UNROLL_HPP
#define NMTOOLS_CORE_UNROLL_HPP

#include "nmtools/meta.hpp"
#include "nmtools/constants.hpp"
#include "nmtools/assert.hpp"
#include "nmtools/utility/forward.hpp"
#include "nmtools/utility/get.hpp"

#include "nmtools/utility/isequal.hpp"
#include "nmtools/utility/at.hpp"
#include "nmtools/utility/apply_resize.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/utility/tuple_cat.hpp"

#include "nmtools/index/compute_offset.hpp"

#include "nmtools/core/eval.hpp"

namespace nmtools
{
    struct unroll_t {};
    constexpr inline auto Unroll = unroll_t{};

    template <typename view_t, typename resolver_t>
    struct evaluator_t<view_t,unroll_t,resolver_t>
    {
        using view_type    = const view_t&;
        using context_type = const unroll_t&;
        // TODO: move output type as template params
        using output_type  = meta::resolve_optype_t<resolver_t,view_t>;

        view_type view;
        context_type context;

        template <typename output_t>
        constexpr auto operator()(output_t& output) const
            -> meta::enable_if_t<meta::is_ndarray_v<output_t>>
        {
            const auto out_shape = ::nmtools::shape(output);
            const auto inp_shape = ::nmtools::shape(view);

            // must be same shape
            // nmtools_assert must return, atm returning from this mem fn is
            // not supported, for now skip if mismatch
            // nmtools_assert( ::nmtools::utils::isequal(out_shape,inp_shape),
            //     "mismatched shape for evaluator call"
            // );

            if (!::nmtools::utils::isequal(out_shape,inp_shape))
                return;

            using ::nmtools::index::ndindex;
            auto out_index = ndindex(out_shape);
            auto inp_index = ndindex(inp_shape);

            constexpr auto OUT_SIZE = len_v<decltype(out_index)>;
            constexpr auto INP_SIZE = len_v<decltype(inp_index)>;
            static_assert( (OUT_SIZE > 0) && (INP_SIZE > 0) );

            const auto out_stride = index::compute_strides(out_shape);
            // const auto inp_stride = index::compute_strides(inp_shape);
            template_for<OUT_SIZE>([&](auto i){
                auto inp_idx = inp_index[i];
                auto out_idx = out_index[i];
                // auto flat_inp_idx = index::compute_offset(inp_idx,inp_stride);
                auto flat_out_idx = index::compute_offset(out_idx,out_stride);
                output.data()[flat_out_idx] = apply_at(view,inp_idx);
            });
        } // operator()

        template <typename output_t>
        constexpr auto operator()(output_t& output) const
            -> meta::enable_if_t<meta::is_num_v<output_t>>
        {
            output = static_cast<output_t>(view);
        } // operator()

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

        template <typename output_t>
        constexpr auto operator()(meta::as_value<output_t>) const
        {
            return (*this).template operator()<output_t>();
        } // operator()

        constexpr auto operator()(none_t) const
        {
            return (*this)();
        } // operator()
    }; // evaluator_t
}

#endif // NMTOOLS_CORE_UNROLL_HPP