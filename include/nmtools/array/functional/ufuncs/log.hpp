#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_LOG_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_LOG_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/log.hpp"

namespace nmtools::functional
{
    constexpr inline auto log = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::log(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_LOG_HPP