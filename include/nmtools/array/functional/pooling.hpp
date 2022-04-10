#ifndef NMTOOLS_ARRAY_FUNCTIONAL_POOLING_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_POOLING_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/pooling.hpp"

namespace nmtools::functional
{
    struct avg_pool2d_t
    {
        static constexpr auto arity = 1;

        template <template<auto...>typename sequence, auto...Is
            , template<typename...>typename attr_tuple
            , typename...attributes_t
            , template<typename...>typename operand_tuple, typename array_t
        >
        constexpr auto operator()(sequence<Is...>, const attr_tuple<attributes_t...>& attributes, const operand_tuple<array_t>& operands) const
        {
            const auto& array = nmtools::get<0>(operands);
            if constexpr (meta::is_pointer_v<array_t>) {
                // NOTE: use fold expr to preserve default attributes
                return view::avg_pool2d(*array,nmtools::get<Is>(attributes)...);
            } else {
                return view::avg_pool2d(array,nmtools::get<Is>(attributes)...);
            }
        } // operator()

        template <template<typename...>typename attr_tuple
            , typename...attributes_t
            , template<typename...>typename operand_tuple, typename array_t
        >
        constexpr auto operator()(const attr_tuple<attributes_t...>& attributes, const operand_tuple<array_t>& operands) const
        {
            return (*this)(meta::make_index_sequence_v<sizeof...(attributes_t)>,attributes,operands);
        } // operator()
    }; // avg_pool2d_t

    struct max_pool2d_t
    {
        static constexpr auto arity = 1;

        template <template<auto...>typename sequence, auto...Is
            , template<typename...>typename attr_tuple
            , typename...attributes_t
            , template<typename...>typename operand_tuple, typename array_t
        >
        constexpr auto operator()(sequence<Is...>, const attr_tuple<attributes_t...>& attributes, const operand_tuple<array_t>& operands) const
        {
            const auto& array = nmtools::get<0>(operands);
            if constexpr (meta::is_pointer_v<array_t>) {
                // NOTE: use fold expr to preserve default attributes
                return view::max_pool2d(*array,nmtools::get<Is>(attributes)...);
            } else {
                return view::max_pool2d(array,nmtools::get<Is>(attributes)...);
            }
        } // operator()

        template <template<typename...>typename attr_tuple
            , typename...attributes_t
            , template<typename...>typename operand_tuple, typename array_t
        >
        constexpr auto operator()(const attr_tuple<attributes_t...>& attributes, const operand_tuple<array_t>& operands) const
        {
            return (*this)(meta::make_index_sequence_v<sizeof...(attributes_t)>,attributes,operands);
        } // operator()
    }; // avg_pool2d_t

    constexpr inline auto avg_pool2d = functor_t(avg_pool2d_t{});

    constexpr inline auto max_pool2d = functor_t(max_pool2d_t{});

} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_POOLING_HPP