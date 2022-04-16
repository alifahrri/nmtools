#ifndef NMTOOLS_ARRAY_FUNCTIONAL_SOFTMIN_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_SOFTMIN_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/softmin.hpp"

namespace nmtools::functional
{
    constexpr inline auto softmin = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::softmin(args...);
    }});
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_SOFTMIN_HPP