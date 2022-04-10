#ifndef NMTOOLS_UTILITY_TUPLE_CAT_HPP
#define NMTOOLS_UTILITY_TUPLE_CAT_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/get.hpp"

namespace nmtools::utility
{
    template <template<typename...>typename tuple_t, typename...args_t, typename value_t, template<auto...>typename sequence, auto...Is>
    constexpr auto tuple_append(const tuple_t<args_t...>& tuple, const value_t& val, sequence<Is...>)
    {
        using result_t = tuple_t<args_t...,value_t>;
        return result_t{nmtools::get<Is>(tuple)...,val};
    }

    template <template<typename...>typename tuple_t, typename...args_t, typename value_t>
    constexpr auto tuple_append(const tuple_t<args_t...>& tuple, const value_t& val)
    {
        return tuple_append(tuple,val,meta::make_index_sequence_v<sizeof...(args_t)>);
    }

    /**
     * @brief Helper function to join two tuple,
     * Used by matmul and ufuncs.
     * 
     * @tparam left_t 
     * @tparam l_args_t 
     * @tparam right_t 
     * @tparam r_args_t 
     * @param left 
     * @param right 
     * @return constexpr auto 
     */
    template <template<typename...>typename left_t, typename...l_args_t
        , template<typename...>typename right_t, typename...r_args_t>
    constexpr auto tuple_cat(const left_t<l_args_t...>& left, const right_t<r_args_t...>& right)
    {
        constexpr auto N = sizeof...(r_args_t);
        return meta::template_reduce<N>([&](auto init, auto index){
            constexpr auto i = decltype(index)::value;
            constexpr auto M = meta::len_v<decltype(init)>;
            return tuple_append(init,nmtools::get<i>(right),meta::make_index_sequence_v<M>);
        }, left);
    } // tuple_cat
} // namespace nmtools::utility

#endif // NMTOOLS_UTILITY_TUPLE_CAT_HPP