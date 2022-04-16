#ifndef NMTOOLS_ARRAY_FUNCTIONAL_MATMUL_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_MATMUL_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/matmul.hpp"

namespace nmtools::functional
{
    constexpr inline auto matmul = functor_t(binary_fmap_t{
        [](const auto&...args){
            return view::matmul(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_MATMUL_HPP