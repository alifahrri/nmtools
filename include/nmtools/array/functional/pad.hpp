#ifndef NMTOOLS_ARRAY_FUNCTIONAL_PAD_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_PAD_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/pad.hpp"

namespace nmtools::functional
{
    constexpr inline auto pad = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::pad(args...);
    }});
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_PAD_HPP