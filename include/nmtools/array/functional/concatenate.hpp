#ifndef NMTOOLS_ARRAY_FUNCTIONAL_CONCATENATE_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_CONCATENATE_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/concatenate.hpp"

namespace nmtools::functional
{
    constexpr inline auto concatenate = functor_t(binary_fmap_t{
        [](const auto&...args){
            return view::concatenate(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_CONCATENATE_HPP