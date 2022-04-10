#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ADD_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ADD_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/add.hpp"

namespace nmtools::functional
{
    struct add_fmap_t
    {
        static constexpr auto arity = 2;

        template <typename attr_tuple,
            template<typename...>typename operand_tuple, typename left_t, typename right_t>
        constexpr auto operator()([[maybe_unused]] const attr_tuple& attributes, const operand_tuple<left_t,right_t>& operands) const
        {
            const auto& [left,right] = operands;
            if constexpr (meta::is_pointer_v<left_t> && meta::is_pointer_v<right_t>) {
                return view::add(*left,*right);
            } else if constexpr (meta::is_pointer_v<left_t>) {
                return view::add(*left,right);
            } else if constexpr (meta::is_pointer_v<right_t>) {
                return view::add(left,*right);
            } else {
                return view::add(left,right);
            }
        } // operator()
    };

    using add_t = functor_t<add_fmap_t,meta::empty_operands_t,meta::empty_attributes_t>;

    constexpr inline auto add = add_t{};

    struct reduce_add_t
    {
        static constexpr auto arity = 1;

        template <
            template<auto...>typename sequence, auto...Is,
            template<typename...>typename attr_tuple, typename...attributes_t,
            template<typename...>typename operand_tuple, typename array_t
        >
        constexpr auto operator()(sequence<Is...>, const attr_tuple<attributes_t...>& attributes, const operand_tuple<array_t>& operands) const
        {
            if constexpr (meta::is_pointer_v<array_t>) {
                return view::reduce_add(*nmtools::get<0>(operands), nmtools::get<Is>(attributes)...);
            } else {
                return view::reduce_add(nmtools::get<0>(operands), nmtools::get<Is>(attributes)...);
            }
        } // operator()

        template <
            template<typename...>typename attr_tuple, typename...attributes_t,
            template<typename...>typename operand_tuple, typename array_t
        >
        constexpr auto operator()(const attr_tuple<attributes_t...>& attributes, const operand_tuple<array_t>& operands) const
        {
            return (*this)(meta::make_index_sequence_v<sizeof...(attributes_t)>, attributes, operands);
        } // operator()
    }; // reduce_add_t

    constexpr inline auto reduce_add = functor_t(reduce_add_t{});
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ADD_HPP