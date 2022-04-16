#ifndef NMTOOLS_ARRAY_FUNCTIONAL_SQUEEZE_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_SQUEEZE_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/squeeze.hpp"

namespace nmtools::functional
{
    constexpr inline auto squeeze = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::squeeze(args...);
    }});
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_SQUEEZE_HPP