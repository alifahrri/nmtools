#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_HARDTANH_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_HARDTANH_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/activations/hardtanh.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using hardtanh = fun::unary_ufunc<view::hardtanh_t<>>;
    }

    constexpr inline auto hardtanh = functor_t{unary_fmap_t<fun::hardtanh>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_HARDTANH_HPP