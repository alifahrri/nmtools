#ifndef NMTOOLS_ARRAY_FUNCTIONAL_SOFTMAX_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_SOFTMAX_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/softmax.hpp"

namespace nmtools::functional
{
    constexpr inline auto softmax = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::softmax(args...);
    }});

} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_SOFTMAX_HPP