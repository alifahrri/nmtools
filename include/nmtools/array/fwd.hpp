#ifndef NMTOOLS_ARRAY_FWD_HPP
#define NMTOOLS_ARRAY_FWD_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/tuple_cat.hpp"

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct FWD_OPERAND_UNSUPPORTED : detail::fail_t {};
    }

    // the following assumes T is cvref_pointer-removed
    template <typename T>
    struct fwd_operand
    {
        static constexpr auto vtype = [](){
            if constexpr (is_view_v<T>
                || is_num_v<T>
                || is_none_v<T>
                || is_constant_index_array_v<T>
                || is_constant_index_v<T>
            ) {
                return as_value_v<const T>;
            } else if constexpr (is_bounded_array_v<T>) {
                return as_value_v<const T&>;
            } else if constexpr (is_ndarray_v<T>) {
                return as_value_v<const T*>;
            } else if constexpr (is_pointer_v<T> && is_ndarray_v<remove_pointer_t<T>>) {
                return as_value_v<const T>;
            } else if constexpr (is_either_v<T> || is_maybe_v<T>) {
                return as_value_v<const T>;
            } else {
                using type = error::FWD_OPERAND_UNSUPPORTED<T>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // fwd_operand

    template <typename T>
    using fwd_operand_t = type_t<fwd_operand<T>>;
}

namespace nmtools
{
    template <typename T>
    constexpr auto fwd_operand(const T& operand)
        -> meta::fwd_operand_t<T>
    {
        using result_t = meta::fwd_operand_t<T>;
        if constexpr (meta::is_pointer_v<result_t> && !meta::is_pointer_v<T>) {
            return &operand;
        } else {
            return operand;
        }
    } // fwd_operand

    template <typename...Ts>
    constexpr auto pack_operands(const Ts&...ts)
    {
        return nmtools_tuple<meta::fwd_operand_t<Ts>...>{fwd_operand(ts)...};
    }

    template <typename T, template<typename...>typename tuple, typename...Ts, auto...Is>
    constexpr auto push_operands(const T& t, const tuple<Ts...>& ts, meta::index_sequence<Is...>)
    {
        return tuple<meta::fwd_operand_t<T>,meta::fwd_operand_t<Ts>...>{fwd_operand(t),fwd_operand(nmtools::get<Is>(ts))...};
    }

    template <typename T, template<typename...>typename tuple, typename...Ts>
    constexpr auto push_operands(const T& t, const tuple<Ts...>& ts)
    {
        return push_operands(t,ts,meta::make_index_sequence_v<sizeof...(Ts)>);
    }

    template <typename T, template<typename...>typename tuple, typename...Ts, auto...Is>
    constexpr auto append_operands(const tuple<Ts...>& ts, const T& t)
    {
        return tuple<meta::fwd_operand_t<Ts>...,meta::fwd_operand_t<T>>{fwd_operand(nmtools::get<Is>(ts))...,fwd_operand(t)};
    }

    template <typename T, template<typename...>typename tuple, typename...Ts>
    constexpr auto append_operands(const tuple<Ts...>& ts, const T& t)
    {
        return append_operands(ts,t,meta::make_index_sequence_v<sizeof...(Ts)>);
    }

    template <template<typename...>typename tuple, typename...Ts, typename...Us, auto...TIs, auto...UIs>
    constexpr auto cat_operands(const tuple<Ts...>& ts, const tuple<Us...>& us, meta::index_sequence<TIs...>, meta::index_sequence<UIs...>)
    {
        using result_t = tuple<
              meta::fwd_operand_t<meta::remove_cvref_pointer_t<Ts>>...
            , meta::fwd_operand_t<meta::remove_cvref_pointer_t<Us>>...>;
        return result_t{
              fwd_operand(nmtools::get<TIs>(ts))...
            , fwd_operand(nmtools::get<UIs>(us))...
        };
    } // cat_operands

    template <template<typename...>typename tuple, typename...Ts, typename...Us>
    constexpr auto cat_operands(const tuple<Ts...>& ts, const tuple<Us...>& us)
    {
        return cat_operands(ts,us,meta::make_index_sequence_v<sizeof...(Ts)>,meta::make_index_sequence_v<sizeof...(Us)>);
    }
} // namespace nmtools

#endif // NMTOOLS_ARRAY_FWD_HPP