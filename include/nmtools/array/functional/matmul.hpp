#ifndef NMTOOLS_ARRAY_FUNCTIONAL_MATMUL_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_MATMUL_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/matmul.hpp"

namespace nmtools::functional
{
    struct matmul_fmap_t
    {
        static constexpr auto arity = 2;

        template <typename attr_tuple,
            template<typename...>typename operand_tuple, typename left_t, typename right_t>
        constexpr auto operator()([[maybe_unused]] const attr_tuple& attributes, const operand_tuple<left_t,right_t>& operands) const
        {
            const auto& [left,right] = operands;
            if constexpr (meta::is_pointer_v<left_t> && meta::is_pointer_v<right_t>) {
                return view::matmul(*left,*right);
            } else if constexpr (meta::is_pointer_v<left_t>) {
                return view::matmul(*left,right);
            } else if constexpr (meta::is_pointer_v<right_t>) {
                return view::matmul(left,*right);
            } else {
                return view::matmul(left,right);
            }
        } // operator()
    };
    
    using matmul_t = functor_t<matmul_fmap_t,meta::empty_operands_t,meta::empty_attributes_t>;

    constexpr inline auto matmul = matmul_t {};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_MATMUL_HPP