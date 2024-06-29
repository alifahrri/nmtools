#ifndef NMTOOLS_UTL_TUPLEV2_HPP
#define NMTOOLS_UTL_TUPLEV2_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/expr.hpp"
#include "nmtools/meta/bits/transform/type_list_at.hpp"
#include "nmtools/utl/tuple.hpp"

namespace nmtools::utl
{
    template <auto I, typename...Ts>
    struct tuplev2_base;

    template <typename...Ts>
    struct tuplev2;

    template <auto I, typename T>
    struct get_t;

    // avoid ambiguous instantiation for structured bindings
    template <auto I, typename...Ts>
    constexpr decltype(auto) get(const tuplev2<Ts...>& tp)
    {
        // carry const-ness to avoid picking wrong overload
        auto getter = get_t<I,const tuplev2<Ts...>&>{};
        return (getter(tp));
    }

    template <auto I, typename...Ts>
    constexpr decltype(auto) get(tuplev2<Ts...>& tp)
    {
        auto getter = get_t<I,tuplev2<Ts...>&>{};
        return getter(tp);
    }

    template <>
    struct tuplev2_base<0UL> {};

    template <typename T>
    struct tuplev2_base<1,T>
    {
        T data;

        constexpr tuplev2_base()
            : data{}
        {}

        constexpr tuplev2_base(T t)
            : data(t)
        {}
    };

    template <auto I, typename T, typename...Ts>
    struct tuplev2_base<I,T,Ts...>
        : tuplev2_base<sizeof...(Ts),Ts...>
    {
        using base_type = tuplev2_base<sizeof...(Ts),Ts...>;
        T data;

        constexpr tuplev2_base()
            : base_type()
            , data{}
        {}

        constexpr tuplev2_base(T t, Ts...ts)
            : base_type(ts...)
            , data(t)
        {}
    };

    template <typename...Ts>
    struct tuplev2
        : tuplev2_base<sizeof...(Ts),Ts...>
    {
        using base_type = tuplev2_base<sizeof...(Ts),Ts...>;

        constexpr tuplev2()
            : base_type()
        {}

        constexpr tuplev2(Ts...ts)
            : base_type(ts...)
        {}

        template <auto...Is, typename...Us>
        constexpr tuplev2(meta::index_sequence<Is...>
            , const tuplev2<Us...>& other
        )
            : base_type(utl::get<Is>(other)...)
        {}

        template <typename...Us>
        constexpr tuplev2(const tuplev2<Us...>& other)
            : tuplev2(meta::make_index_sequence_v<sizeof...(Us)>,other)
        {}
        
        // TODO: add overload constructor for non-const tuplev2<Us...>&
    };

    // avoid multiple overloads of constructor
    template <>
    struct tuplev2<>
    {
        constexpr tuplev2() {};
    };

    template <typename...Ts>
    struct tuple_size<tuplev2<Ts...>>
    {
        static constexpr auto value = sizeof...(Ts);
    };

    template <typename...Ts>
    struct tuple_size<const tuplev2<Ts...>>
        : tuple_size<tuplev2<Ts...>>
    {};

    template <typename...Ts>
    struct tuple_size<tuplev2<Ts...>&>
        : tuple_size<tuplev2<Ts...>>
    {};

    template <nm_size_t I, typename...Ts>
    struct tuple_element<I,tuplev2<Ts...>>
    {
        using type_list = meta::type_list<Ts...>;
        using type = meta::at_t<type_list,I>;
    };

    template <auto I, typename T, typename...Ts>
    struct get_t<I,const tuplev2<T,Ts...>&>
    {
        using tuple_type = tuplev2<T,Ts...>;
        using base_type  = typename tuple_type::base_type;

        constexpr decltype(auto) operator()(const tuple_type& tp) const
        {
            auto getter = get_t<I,const base_type&>{};
            return getter(static_cast<const base_type&>(tp));
        }
    };

    template <auto I, typename T, typename...Ts>
    struct get_t<I,tuplev2<T,Ts...>&>
    {
        using tuple_type = tuplev2<T,Ts...>;
        using base_type  = typename tuple_type::base_type;

        constexpr decltype(auto) operator()(tuple_type& tp) const
        {
            auto getter = get_t<I,base_type&>{};
            return getter(static_cast<base_type&>(tp));
        }
    };

    template <auto I, typename T, typename...Ts>
    struct get_t<I,const tuplev2_base<sizeof...(Ts)+1,T,Ts...>&>
    {
        using tuple_type = tuplev2_base<sizeof...(Ts)+1,T,Ts...>;

        constexpr decltype(auto) operator()(const tuple_type& tp) const
        {
            if constexpr (I == 0) {
                return (tp.data);
            } else {
                using base_type = tuplev2_base<sizeof...(Ts),Ts...>;
                auto getter = get_t<I-1,const base_type&>{};
                return getter(static_cast<const base_type&>(tp));
            }
        }
    };

    template <auto I, typename T, typename...Ts>
    struct get_t<I,tuplev2_base<sizeof...(Ts)+1,T,Ts...>&>
    {
        using tuple_type = tuplev2_base<sizeof...(Ts)+1,T,Ts...>;

        constexpr decltype(auto) operator()(tuple_type& tp)
        {
            if constexpr (I == 0) {
                return (tp.data);
            } else {
                using base_type = tuplev2_base<sizeof...(Ts),Ts...>;
                auto getter = get_t<I-1,base_type&>{};
                return getter(static_cast<base_type&>(tp));
            }
        }
    };
} // namespace nmtools::utl

template <typename...Ts>
struct std::tuple_size<nmtools::utl::tuplev2<Ts...>>
{
    using tuple_type = nmtools::utl::tuplev2<Ts...>;
    static constexpr auto value = nmtools::utl::tuple_size_v<tuple_type>;
};

template <typename...Ts>
struct std::tuple_size<const nmtools::utl::tuplev2<Ts...>>
    : std::tuple_size<nmtools::utl::tuplev2<Ts...>> {};

template <nm_size_t I, typename...Ts>
struct std::tuple_element<I,nmtools::utl::tuplev2<Ts...>>
{
    using tuple_type = nmtools::utl::tuplev2<Ts...>;
    using type = nmtools::utl::tuple_element_t<I,tuple_type>;
};

template <nm_size_t I, typename...Ts>
struct std::tuple_element<I,const nmtools::utl::tuplev2<Ts...>>
{
    using tuple_type = nmtools::utl::tuplev2<Ts...>;
    using type = const nmtools::utl::tuple_element_t<I,tuple_type>;
};

#endif // NMTOOLS_UTL_TUPLEV2_HPP