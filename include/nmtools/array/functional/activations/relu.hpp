#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_RELU_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_RELU_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/activations/relu.hpp"

namespace nmtools::functional
{
    struct relu_fmap_t
    {
        static constexpr auto arity = 1;

        template <typename attr_tuple,
            template<typename...>typename operand_tuple, typename array_t>
        constexpr auto operator()(const attr_tuple&, const operand_tuple<array_t>& operand) const
        {
            if constexpr (meta::is_pointer_v<array_t>) {
                return view::relu(*nmtools::get<0>(operand));
            } else {
                return view::relu(nmtools::get<0>(operand));
            }
        } // operator()
    }; // relu_fmap_t

    constexpr inline auto relu = functor_t(relu_fmap_t{});
    
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_RELU_HPP