#ifndef NMTOOLS_ARRAY_FUNCTIONAL_SOFTMAX_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_SOFTMAX_HPP

#include "nmtools/array/core/functor.hpp"
#include "nmtools/array/functional/ufuncs/maximum.hpp"
#include "nmtools/array/functional/ufuncs/subtract.hpp"
#include "nmtools/array/functional/ufuncs/exp.hpp"
#include "nmtools/array/functional/ufuncs/add.hpp"
#include "nmtools/array/functional/ufuncs/divide.hpp"
#include "nmtools/array/view/softmax.hpp"

namespace nmtools::functional
{
    constexpr inline auto softmax_fun = [](const auto&...args){
        return view::softmax(args...);
    };

    constexpr inline auto softmax = functor_t{unary_fmap_t<decltype(softmax_fun)>{softmax_fun}};

} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_SOFTMAX_HPP