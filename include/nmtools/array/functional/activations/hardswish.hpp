#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_HARDSWISH_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_HARDSWISH_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/activations/hardswish.hpp"

namespace nmtools::functional
{
    constexpr inline auto hardswish = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::hardswish(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_HARDSWISH_HPP