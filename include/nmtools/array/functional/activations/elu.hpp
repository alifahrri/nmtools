#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_ELU_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_ELU_HPP

#include "nmtools/array/core/functor.hpp"
#include "nmtools/array/view/activations/elu.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using elu = fun::unary_ufunc<view::elu_t<>>;
    }

    constexpr inline auto elu = functor_t{unary_fmap_t<fun::elu>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_ELU_HPP