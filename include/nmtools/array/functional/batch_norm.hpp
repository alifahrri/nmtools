#ifndef NMTOOLS_ARRAY_FUNCTIONAL_BATCH_NORM_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_BATCH_NORM_HPP

#include "nmtools/array/core/functor.hpp"
#include "nmtools/array/functional/moveaxis.hpp"
#include "nmtools/array/functional/ufuncs/add.hpp"
#include "nmtools/array/functional/ufuncs/multiply.hpp"
#include "nmtools/array/functional/ufuncs/subtract.hpp"
#include "nmtools/array/functional/ufuncs/divide.hpp"
#include "nmtools/array/functional/ufuncs/sqrt.hpp"
#include "nmtools/array/view/batch_norm.hpp"

namespace nmtools::functional
{
    constexpr inline auto batch_norm_fun = [](const auto&...args){
        return view::batch_norm(args...);
    };

    constexpr inline auto batch_norm = functor_t{quinary_fmap_t<decltype(batch_norm_fun)>{batch_norm_fun}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_BATCH_NORM_HPP