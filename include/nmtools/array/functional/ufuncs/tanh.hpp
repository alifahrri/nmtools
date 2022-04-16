#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_TANH_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_TANH_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/tanh.hpp"

namespace nmtools::functional
{
    constexpr inline auto tanh = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::tanh(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_TANH_HPP