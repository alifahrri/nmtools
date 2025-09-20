#ifndef NMTOOLS_UTL_tuple_HPP
#define NMTOOLS_UTL_tuple_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/expr.hpp"
#include "nmtools/meta/bits/transform/type_list_at.hpp"

namespace nmtools::utl
{
    template <size_t I, typename...Ts>
    struct tuple_base;

    template <typename...Ts>
    struct tuple;

    template <auto I, typename T>
    struct get_t;

    // avoid ambiguous instantiation for structured bindings
    template <auto I, typename...Ts>
    constexpr decltype(auto) get(const tuple<Ts...>& tp)
    {
        // carry const-ness to avoid picking wrong overload
        auto getter = get_t<I,const tuple<Ts...>&>{};
        return (getter(tp));
    }

    template <auto I, typename...Ts>
    constexpr decltype(auto) get(tuple<Ts...>& tp)
    {
        auto getter = get_t<I,tuple<Ts...>&>{};
        return getter(tp);
    }

    template <>
    struct tuple_base<0> {};

    template <typename T>
    struct tuple_base<1,T>
    {
        T data;

        constexpr tuple_base()
            : data{}
        {}

        constexpr tuple_base(T t)
            : data(t)
        {}
    };

    template <size_t I, typename T, typename...Ts>
    struct tuple_base<I,T,Ts...>
        : tuple_base<sizeof...(Ts),Ts...>
    {
        using base_type = tuple_base<sizeof...(Ts),Ts...>;
        T data;

        constexpr tuple_base()
            : base_type()
            , data{}
        {}

        constexpr tuple_base(T t, Ts...ts)
            : base_type(ts...)
            , data(t)
        {}
    };

    template <typename...Ts>
    struct tuple
        : tuple_base<sizeof...(Ts),Ts...>
    {
        using base_type = tuple_base<sizeof...(Ts),Ts...>;

        constexpr tuple()
            : base_type()
        {}

        constexpr tuple(Ts...ts)
            : base_type(ts...)
        {}

        template <auto...Is, typename...Us>
        constexpr tuple(meta::index_sequence<Is...>
            , const tuple<Us...>& other
        )
            : base_type(utl::get<Is>(other)...)
        {}

        template <typename...Us>
        constexpr tuple(const tuple<Us...>& other)
            : tuple(meta::make_index_sequence_v<sizeof...(Us)>,other)
        {}
        
        // TODO: add overload constructor for non-const tuple<Us...>&
    };

    // avoid multiple overloads of constructor
    template <>
    struct tuple<>
    {
        constexpr tuple() {};
    };

    template <typename T>
    struct tuple_size;

    template <typename T>
    inline constexpr auto tuple_size_v = tuple_size<T>::value;

    template <nm_size_t I, typename T>
    struct tuple_element;

    template <nm_size_t I, typename T>
    using tuple_element_t = meta::type_t<tuple_element<I,T>>;

    template <typename...Ts>
    struct tuple_size<tuple<Ts...>>
    {
        static constexpr auto value = sizeof...(Ts);
    };

    template <typename...Ts>
    struct tuple_size<const tuple<Ts...>>
        : tuple_size<tuple<Ts...>>
    {};

    template <typename...Ts>
    struct tuple_size<tuple<Ts...>&>
        : tuple_size<tuple<Ts...>>
    {};

    template <nm_size_t I, typename...Ts>
    struct tuple_element<I,tuple<Ts...>>
    {
        using type_list = meta::type_list<Ts...>;
        using type = meta::at_t<type_list,I>;
    };

    template <auto I, typename T, typename...Ts>
    struct get_t<I,const tuple<T,Ts...>&>
    {
        using tuple_type = tuple<T,Ts...>;
        using base_type  = typename tuple_type::base_type;

        constexpr decltype(auto) operator()(const tuple_type& tp) const
        {
            auto getter = get_t<I,const base_type&>{};
            return getter(static_cast<const base_type&>(tp));
        }
    };

    template <auto I, typename T, typename...Ts>
    struct get_t<I,tuple<T,Ts...>&>
    {
        using tuple_type = tuple<T,Ts...>;
        using base_type  = typename tuple_type::base_type;

        constexpr decltype(auto) operator()(tuple_type& tp) const
        {
            auto getter = get_t<I,base_type&>{};
            return getter(static_cast<base_type&>(tp));
        }
    };

    template <auto I, typename T, typename...Ts>
    struct get_t<I,const tuple_base<sizeof...(Ts)+1,T,Ts...>&>
    {
        using tuple_type = tuple_base<sizeof...(Ts)+1,T,Ts...>;

        constexpr decltype(auto) operator()(const tuple_type& tp) const
        {
            if constexpr (I == 0) {
                return (tp.data);
            } else {
                using base_type = tuple_base<sizeof...(Ts),Ts...>;
                auto getter = get_t<I-1,const base_type&>{};
                return getter(static_cast<const base_type&>(tp));
            }
        }
    };

    template <auto I, typename T, typename...Ts>
    struct get_t<I,tuple_base<sizeof...(Ts)+1,T,Ts...>&>
    {
        using tuple_type = tuple_base<sizeof...(Ts)+1,T,Ts...>;

        constexpr decltype(auto) operator()(tuple_type& tp)
        {
            if constexpr (I == 0) {
                return (tp.data);
            } else {
                using base_type = tuple_base<sizeof...(Ts),Ts...>;
                auto getter = get_t<I-1,base_type&>{};
                return getter(static_cast<base_type&>(tp));
            }
        }
    };
} // namespace nmtools::utl

// make sure to follow stl tuple, if has stl
#if __has_include(<tuple>)
#include <tuple>
#else
namespace std
{
    template <typename T>
    struct tuple_size;

    template <nm_size_t I, typename T>
    struct tuple_element;
} // namespace std
#endif // <tuple>

template <typename...Ts>
struct std::tuple_size<nmtools::utl::tuple<Ts...>>
{
    using tuple_type = nmtools::utl::tuple<Ts...>;
    static constexpr auto value = nmtools::utl::tuple_size_v<tuple_type>;
};

template <typename...Ts>
struct std::tuple_size<const nmtools::utl::tuple<Ts...>>
    : std::tuple_size<nmtools::utl::tuple<Ts...>> {};

template <nm_size_t I, typename...Ts>
struct std::tuple_element<I,nmtools::utl::tuple<Ts...>>
{
    using tuple_type = nmtools::utl::tuple<Ts...>;
    using type = nmtools::utl::tuple_element_t<I,tuple_type>;
};

template <nm_size_t I, typename...Ts>
struct std::tuple_element<I,const nmtools::utl::tuple<Ts...>>
{
    using tuple_type = nmtools::utl::tuple<Ts...>;
    using type = const nmtools::utl::tuple_element_t<I,tuple_type>;
};

#endif // NMTOOLS_UTL_tuple_HPP