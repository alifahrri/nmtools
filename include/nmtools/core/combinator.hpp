#ifndef NMTOOLS_ARRAY_FUNCTIONAL_COMBINATOR_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_COMBINATOR_HPP

#include "nmtools/meta.hpp"
#include "nmtools/core/functor.hpp"
#include "nmtools/utility/to_string/to_string.hpp"

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

    template <typename functor_t, typename operands_t, typename output_shape_t, typename output_element_t, auto N>
    constexpr auto operator*(const functional::node_t<functor_t,operands_t,output_shape_t,output_element_t>& node, dup_t<N> cb)
    {
        auto composition = node.functor * cb;
        // TODO: better handling arity
        using result_t = functional::node_t<decltype(composition),operands_t,output_shape_t,output_element_t>;
        // TODO: do not discard intermediate shape/type
        return result_t{composition,node.operands,node.output_shape,node.output_element};
    }

    template <auto N>
    struct dig_t
    {
        template <typename...operands_t>
        constexpr auto operator()(const operands_t&...operands) const
        {
            auto operands_pack = pack_operands(operands...);
            if constexpr (meta::is_maybe_v<decltype(operands_pack)>) {
                using result_t = decltype((*this)(unwrap(operands_pack)));
                using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
                return (operands_pack
                    ? return_t{(*this)(unwrap(operands_pack))}
                    : return_t{meta::Nothing}
                );
            } else {
                const auto& operand_i = at(operands_pack,meta::ct_v<N>);
                auto left  = utility::tuple_slice(operands_pack,None,meta::ct_v<N>);
                auto right = utility::tuple_slice(operands_pack,meta::ct_v<N+1>);
                return cat_operands(push_operands(operand_i,left),right);
            }
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
} // namespace nmtools::combinator

namespace nmtools::meta
{
    template <>
    struct is_combinator<functional::fmap_t<combinator::swap_t,2,2>> : true_type {};

    template <auto M, auto I, auto N>
    struct is_combinator<functional::fmap_t<combinator::dup_t<M>,I,N>> : true_type {};

    template <auto N>
    struct is_combinator<functional::fmap_t<combinator::dig_t<N>,N+1,N+1>> : true_type {};

    template <auto N>
    struct is_combinator<functional::fmap_t<combinator::bury_t<N>,N+1,N+1>> : true_type {};
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto N, auto...fmt_args>
    struct to_string_t<
        // functional::functor_t< combinator::dup_fmap_t<N> >, fmt_string_t<fmt_args...>
        // combinator::dup_fmap_t<N>, fmt_string_t<fmt_args...>
        // functional::fmap_t< combinator::dup_t<N>, IN, OUT >, fmt_string_t<fmt_args...>
        combinator::dup_t<N>, fmt_string_t<fmt_args...>
    > {
        using result_type = nmtools_string;

        // auto operator()(const functional::functor_t< combinator::dup_fmap_t<N> >&) const noexcept
        // auto operator()(const combinator::dup_fmap_t<N>&) const noexcept
        // auto operator()(const functional::fmap_t<combinator::dup_t<N>,IN,OUT>&) const noexcept
        auto operator()(const combinator::dup_t<N>&) const noexcept
        {
            nmtools_string str;

            str += "dup";
            str += to_string(N,Compact);

            return str;
        }
    };

    template <auto N, auto...fmt_args>
    struct to_string_t<
        combinator::bury_t<N>, fmt_string_t<fmt_args...>
    > {
        using result_type = nmtools_string;

        auto operator()(const combinator::bury_t<N>&) const noexcept
        {
            nmtools_string str;

            str += "bury";
            str += to_string(N,Compact);

            return str;
        }
    };

    template <auto N, auto...fmt_args>
    struct to_string_t<
        combinator::dig_t<N>, fmt_string_t<fmt_args...>
    > {
        using result_type = nmtools_string;

        auto operator()(const combinator::dig_t<N>&) const noexcept
        {
            nmtools_string str;

            str += "dig";
            str += to_string(N,Compact);

            return str;
        }
    };

    template <auto...fmt_args>
    struct to_string_t<
        combinator::swap_t, fmt_string_t<fmt_args...>
    > {
        using result_type = nmtools_string;

        auto operator()(const combinator::swap_t&) const noexcept
        {
            nmtools_string str;

            str += "swap";

            return str;
        }
    };
}
#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_FUNCTIONAL_COMBINATOR_HPP