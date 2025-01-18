#ifndef NMTOOLS_ARRAY_FUNCTIONAL_SOFTMIN_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_SOFTMIN_HPP

#include "nmtools/array/core/functor.hpp"
#include "nmtools/array/functional/ufuncs/negative.hpp"
#include "nmtools/array/functional/softmax.hpp"
#include "nmtools/array/view/softmin.hpp"

namespace nmtools::functional
{
    constexpr inline auto softmin_fun = [](const auto&...args){
        return view::softmin(args...);
    };

    constexpr inline auto softmin = functor_t{unary_fmap_t<decltype(softmin_fun)>{softmin_fun}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_SOFTMIN_HPP