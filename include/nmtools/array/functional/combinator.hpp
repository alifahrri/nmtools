#ifndef NMTOOLS_ARRAY_FUNCTIONAL_COMBINATOR_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_COMBINATOR_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/functional/functor.hpp"

namespace nmtools::combinator
{
    using functional::functor_t, functional::fmap_t;

    struct swap_t
    {
        template <typename lhs_t, typename rhs_t>
        constexpr auto operator()(const lhs_t& lhs, const rhs_t& rhs) const
        {
            return pack_operands(rhs,lhs);
        }
    }; // swap_t

    template <auto N>
    struct dup_t
    {
        template <typename array_t>
        constexpr auto operator()(const array_t& array) const
        {
            return meta::template_reduce<N>([&](auto init, auto){
                return push_operands(array,init);
            }, nmtools_tuple{});
        }
    }; // dup_t

    template <auto N>
    struct dig_t
    {
        template <typename...operands_t>
        constexpr auto operator()(const operands_t&...operands) const
        {
            auto operands_pack = pack_operands(operands...);
            const auto& operand_i = at(operands_pack,meta::ct_v<N>);
            auto left  = utility::tuple_slice(operands_pack,None,meta::ct_v<N>);
            auto right = utility::tuple_slice(operands_pack,meta::ct_v<N+1>);
            return cat_operands(push_operands(operand_i,left),right);
        }
    }; // dig_t

    template <auto N>
    struct bury_t
    {
        template <typename...operands_t>
        constexpr auto operator()(const operands_t&...operands) const
        {
            auto operands_pack = pack_operands(operands...);
            const auto& operand_i = at(operands_pack,meta::ct_v<0>);
            auto left  = utility::tuple_slice(operands_pack,meta::ct_v<1>,meta::ct_v<N+1>);
            auto right = utility::tuple_slice(operands_pack,meta::ct_v<N+1>);
            return cat_operands(left,push_operands(operand_i,right));
        }
    }; // bury_t

    template <> struct dig_t<1> : swap_t {};
    template <> struct bury_t<1> : swap_t {};

    template <auto N> using dig_fmap_t  = fmap_t<dig_t<N>,N+1,N+1>;
    template <auto N> using dup_fmap_t  = fmap_t<dup_t<N>,1,N>;
    template <auto N> using bury_fmap_t = fmap_t<bury_t<N>,N+1,N+1>;

    static_assert( meta::is_default_constructible_v<bury_fmap_t<2>> );
    static_assert( meta::is_default_constructible_v<bury_t<2>> );

    template <auto N>
    constexpr inline auto bury_n = functor_t<bury_fmap_t<N>>{};
    template <auto N>
    constexpr inline auto dig_n = functor_t<dig_fmap_t<N>>{};
    template <auto N>
    constexpr inline auto dup_n = functor_t<dup_fmap_t<N>>{};

    constexpr inline auto dup   = dup_n<2>;
    constexpr inline auto swap  = functor_t{fmap_t<swap_t,2,2>{}};
    constexpr inline auto dig1  = dig_n<1>;
    constexpr inline auto dig2  = dig_n<2>;
    constexpr inline auto bury1 = bury_n<1>;
    constexpr inline auto bury2 = bury_n<2>;
}

#endif // NMTOOLS_ARRAY_FUNCTIONAL_COMBINATOR_HPP