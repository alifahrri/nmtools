#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_HARDTANH_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_HARDTANH_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/activations/hardtanh.hpp"

namespace nmtools::functional
{
    constexpr inline auto hardtanh = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::hardtanh(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_HARDTANH_HPP