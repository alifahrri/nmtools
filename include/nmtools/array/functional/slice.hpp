#ifndef NMTOOLS_ARRAY_FUNCTIONAL_SLICE_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_SLICE_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/slice.hpp"

namespace nmtools::functional
{
    constexpr inline auto slice = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::slice(args...);
    }});

    constexpr inline auto apply_slice = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::apply_slice(args...);
    }});
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_SLICE_HPP