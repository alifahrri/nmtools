#ifndef NMTOOLS_ARRAY_FUNCTIONAL_RESHAPE_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_RESHAPE_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/reshape.hpp"

namespace nmtools::functional
{
    struct reshape_fmap_t
    {
        static constexpr auto arity = 1;

        template <
            template<typename...>typename  attr_tuple, typename newshape_t,
            template<typename...>typename operand_tuple, typename array_t
        >
        constexpr auto operator()(const attr_tuple<newshape_t>& attributes, const operand_tuple<array_t>& operands) const
        {
            if constexpr (meta::is_pointer_v<meta::remove_cvref_t<array_t>>) {
                static_assert( !meta::is_pointer_v<meta::remove_cvref_t<decltype(*nmtools::get<0>(operands))>> );
                return view::reshape(*nmtools::get<0>(operands),nmtools::get<0>(attributes));
            } else {
                return view::reshape(nmtools::get<0>(operands),nmtools::get<0>(attributes));
            }
        } // operator()
    }; // reshape_fmap_t
    
    using reshape_t = functor_t<reshape_fmap_t,meta::empty_operands_t,meta::empty_attributes_t>;

    constexpr inline auto reshape = reshape_t{};
} // namespace nmtools::functional

#endif //NMTOOLS_ARRAY_FUNCTIONAL_RESHAPE_HPP