#ifndef NMTOOLS_ARRAY_FUNCTIONAL_TRANSPOSE_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_TRANSPOSE_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/transpose.hpp"

namespace nmtools::functional
{
    constexpr inline auto transpose = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::transpose(args...);
    }});
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_TRANSPOSE_HPP