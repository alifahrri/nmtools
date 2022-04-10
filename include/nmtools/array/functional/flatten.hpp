#ifndef NMTOOLS_ARRAY_FUNCTIONAL_FLATTEN_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_FLATTEN_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/flatten.hpp"

namespace nmtools::functional
{
    struct flatten_t
    {
        static constexpr auto arity = 1;

        template <
            typename attribute_t,
            template<typename...>typename operand_tuple, typename array_t
        >
        constexpr auto operator()(const attribute_t&, const operand_tuple<array_t>& operands) const
        {
            if constexpr (meta::is_pointer_v<array_t>) {
                return view::flatten(*nmtools::get<0>(operands));
            } else {
                return view::flatten(nmtools::get<0>(operands));
            }
        } // operator()
    }; // flatten_t

    constexpr inline auto flatten = functor_t(flatten_t());
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_FLATTEN_HPP