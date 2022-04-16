#ifndef NMTOOLS_ARRAY_FUNCTIONAL_BATCH_NORM_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_BATCH_NORM_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/batch_norm.hpp"

namespace nmtools::functional
{
    constexpr inline auto batch_norm = functor_t(quinary_fmap_t{
        [](const auto&...args){
            return view::batch_norm(args...);
    }});
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_BATCH_NORM_HPP