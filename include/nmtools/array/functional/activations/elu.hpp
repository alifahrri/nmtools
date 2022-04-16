#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_ELU_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_ELU_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/activations/elu.hpp"

namespace nmtools::functional
{
    constexpr inline auto elu = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::elu(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_ELU_HPP