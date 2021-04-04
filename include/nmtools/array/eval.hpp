#ifndef NMTOOLS_ARRAY_EVAL_HPP
#define NMTOOLS_ARRAY_EVAL_HPP

#include "nmtools/array/ndarray/dynamic.hpp"

#include "nmtools/utils/isequal.hpp"
#include "nmtools/array/utility/apply_at.hpp"
#include "nmtools/array/utility/apply_resize.hpp"

#include "nmtools/meta.hpp"
#include "nmtools/constants.hpp"
#include "nmtools/assert.hpp"

namespace nmtools::array
{
    struct eval_t {};

    template <typename view_t, typename context_t, typename=void>
    struct evaluator_t;

    template <typename view_t>
    struct evaluator_t<view_t,none_t>
    {
        using view_type    = const view_t&;
        using context_type = const none_t&;
        using output_type  = meta::resolve_optype_t<eval_t,view_t,none_t>;

        view_type view;
        context_type context;

        template <typename output_t>
        constexpr auto operator()(output_t& output) const
        {
            auto out_shape = ::nmtools::shape(output);
            auto inp_shape = ::nmtools::shape(view);

            // must be same shape
            nmtools_assert( ::nmtools::utils::isequal(out_shape,inp_shape),
                "mismatched shape for evaluator call"
            );

            auto out_index = ndindex(out_shape);
            auto inp_index = ndindex(inp_shape);

            auto n = inp_index.size();
            for (size_t i=0; i<n; i++) {
                // while the shape is the same,
                // the underlying type of indexing may be not
                auto inp_idx = inp_index[i];
                auto out_idx = out_index[i];
                apply_at(output,out_idx) = apply_at(view,inp_idx);
            }
        } // operator()

        template <typename output_t>
        constexpr auto operator()() const
        {
            using result_t = meta::transform_bounded_array_t<output_t>;
            auto output = result_t{};
            if constexpr (meta::is_resizeable_v<result_t>) {
                auto inp_shape = ::nmtools::shape(view);
                ::nmtools::detail::apply_resize(output,inp_shape);
            }

            (*this)(output);

            return output;
        } // operator()

        constexpr auto operator()() const
            -> std::enable_if_t<!std::is_void_v<output_type>,output_type>
        {
            return (*this).template operator()<output_type>();
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

    template <typename view_t, typename context_t>
    constexpr auto evaluator(const view_t& view, context_t&& context)
    {
        using ctx_t = meta::remove_cvref_t<context_t>;
        using evaluator_type = evaluator_t<view_t,ctx_t>;
        return evaluator_type{view,context};
    } // evaluator

    template <typename output_t=none_t, typename context_t=none_t, typename view_t>
    constexpr auto eval(const view_t& view, context_t&& context=context_t{}, output_t&& output=output_t{})
    {
        auto evaluator_ = evaluator(view,context);
        return evaluator_(output);
    } // eval

} // namespace nmtools::array

namespace nmtools::meta
{
    template <typename view_t>
    struct resolve_optype<
        void, array::eval_t, view_t, none_t
    >
    {
        using element_t = get_element_type_t<view_t>;
        // use dynamic_ndarray for now
        // TODO: complete shape-inference for all view types and
        // deduce the output type from the underlying arrays
        using type = array::dynamic_ndarray<element_t>;
    }; // eval_t
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_EVAL_HPP