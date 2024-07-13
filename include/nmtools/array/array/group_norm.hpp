#ifndef NMTOOLS_ARRAY_ARRAY_GROUP_NORM_HPP
#define NMTOOLS_ARRAY_ARRAY_GROUP_NORM_HPP

#include "nmtools/array/view/group_norm.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>
        , typename input_t, typename num_groups_t, typename weight_t, typename bias_t, typename epsilon_t=float>
    constexpr auto group_norm(const input_t& input, num_groups_t num_groups, const weight_t& weight, const bias_t& bias, epsilon_t epsilon=epsilon_t{1e-5}
        , context_t&& context=context_t{}, output_t&& output=output_t{}, meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto group_norm = view::group_norm(input,num_groups,weight,bias,epsilon);
        return eval(group_norm
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    } // group_norm
}

#endif // NMTOOLS_ARRAY_ARRAY_GROUP_NORM_HPP