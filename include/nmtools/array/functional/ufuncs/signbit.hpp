#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SIGNBIT_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SIGNBIT_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/signbit.hpp"

namespace nmtools::functional
{
    constexpr inline auto signbit = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::signbit(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SIGNBIT_HPP