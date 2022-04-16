#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ADD_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ADD_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/add.hpp"

namespace nmtools::functional
{
    constexpr inline auto add = functor_t(binary_fmap_t{
        [](const auto&...args){
            return view::add(args...);
    }});

    constexpr inline auto reduce_add = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::reduce_add(args...);
    }});

    constexpr inline auto outer_add = functor_t(binary_fmap_t{
        [](const auto&...args){
            return view::outer_add(args...);
    }});

    constexpr inline auto accumulate_add = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::accumulate_add(args...);
    }});
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ADD_HPP