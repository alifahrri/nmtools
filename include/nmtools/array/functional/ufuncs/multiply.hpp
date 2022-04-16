#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_MULTIPLY_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_MULTIPLY_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/multiply.hpp"

namespace nmtools::functional
{
    constexpr inline auto multiply = functor_t(binary_fmap_t{
        [](const auto&...args){
            return view::multiply(args...);
    }});

    constexpr inline auto reduce_multiply = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::reduce_multiply(args...);
    }});

    constexpr inline auto outer_multiply = functor_t(binary_fmap_t{
        [](const auto&...args){
            return view::outer_multiply(args...);
    }});

    constexpr inline auto accumulate_multiply = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::accumulate_multiply(args...);
    }});
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_MULTIPLY_HPP