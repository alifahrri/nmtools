#ifndef NMTOOLS_ARRAY_FUNCTIONAL_SOFTMAX_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_SOFTMAX_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/softmax.hpp"

namespace nmtools::functional
{
    struct softmax_fmap_t
    {
        static constexpr auto arity = 1;

        template <template<typename...>typename attr_tuple, typename dim_t,
            template<typename...>typename operand_tuple, typename array_t>
        constexpr auto operator()(const attr_tuple<dim_t>& attributes, const operand_tuple<array_t>& operands) const
        {
            if constexpr (meta::is_pointer_v<array_t>) {
                return view::softmax(*nmtools::get<0>(operands),nmtools::get<0>(attributes));
            } else {
                return view::softmax(nmtools::get<0>(operands),nmtools::get<0>(attributes));
            }
        } // operator()
    }; // softmax_fmap_t

    constexpr inline auto softmax = functor_t(softmax_fmap_t{});

} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_SOFTMAX_HPP