#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCTANH_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCTANH_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/arctanh.hpp"

namespace nmtools::functional
{
    constexpr inline auto arctanh = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::arctanh(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCTANH_HPP