#ifndef NMTOOLS_ARRAY_FUNCTIONAL_REPEAT_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_REPEAT_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/repeat.hpp"

namespace nmtools::functional
{
    constexpr inline auto repeat = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::repeat(args...);
    }});
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_REPEAT_HPP