#ifndef NMTOOLS_ARRAY_VIEW_LINEAR_HPP
#define NMTOOLS_ARRAY_VIEW_LINEAR_HPP

#include "nmtools/array/core/alias.hpp"
#include "nmtools/array/view/tensordot.hpp"
#include "nmtools/array/view/ufuncs/add.hpp"

namespace nmtools::view
{
    template <typename input_t, typename weight_t, typename bias_t=none_t>
    constexpr auto linear(const input_t& input, const weight_t& weight, const bias_t& bias=bias_t{})
    {
        auto axes = nmtools_tuple{
            nmtools_tuple{meta::ct_v<-1>}
            , nmtools_tuple{meta::ct_v<-1>}
        };
        if constexpr (is_none_v<bias_t>) {
            return view::tensordot(input,weight,axes);
        } else {
            auto aliased  = view::aliased(input,weight,bias);
            auto a_input  = nmtools::get<0>(aliased);
            auto a_weight = nmtools::get<1>(aliased);
            auto a_bias   = nmtools::get<2>(aliased);
            return view::add(view::tensordot(a_input,a_weight,axes), a_bias);
        }
    } // linear
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_LINEAR_HPP