#ifndef NMTOOLS_UTILITY_FWD_HPP
#define NMTOOLS_UTILITY_FWD_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/tuple_cat.hpp"
#include "nmtools/dtypes.hpp"

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct FWD_OPERAND_UNSUPPORTED : detail::fail_t {};

        template <typename...>
        struct FWD_ATTRIBUTE_UNSUPPORTED : detail::fail_t {};
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

    template <typename T>
    struct fwd_attribute
    {
        static constexpr auto vtype = [](){
            [[maybe_unused]]
            constexpr auto is_valid_attribute = [](auto vtype){
                using type = type_t<decltype(vtype)>;
                return is_none_v<type>
                    || is_num_v<type>
                    || is_dtype_v<type>
                    || is_slice_index_v<type>
                    || is_slice_index_array_v<type>
                    || is_index_array_v<type>
                    || is_integral_constant_v<type>
                    || is_attribute_v<type>
                ;
            };
            if constexpr (is_bounded_array_v<T>) {
                constexpr auto N = meta::len_v<T>;
                using element_t = get_element_type_t<T>;
                using type = nmtools_array<element_t,N>;
                return as_value_v<type>;
            } else if constexpr (
                is_valid_attribute(as_value_v<T>)
            ) {
                using type = T;
                return as_value_v<type>;
            } else if constexpr (is_maybe_v<T>) {
                using type = get_maybe_type_t<T>;
                if constexpr (is_valid_attribute(as_value_v<type>)) {
                    return as_value_v<T>;
                } else {
                    using type = error::FWD_ATTRIBUTE_UNSUPPORTED<T>;
                    return as_value_v<type>;
                }
            } else {
                using type = error::FWD_ATTRIBUTE_UNSUPPORTED<T>;
                return as_value_v<type>;
            }
        }();

        using type = type_t<decltype(vtype)>;
    }; // fwd_attribute

    template <typename T>
    using fwd_attribute_t = type_t<fwd_attribute<T>>;
} // namespace nmtools::meta

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

    template <typename T, typename=void>
    struct fwd_attribute_t
    {
        using type = meta::fwd_attribute_t<T>;

        constexpr type operator()(const T& attribute) const
        {
            return attribute;
        }
    }; // fwd_attribute_t

    template <typename T, auto N>
    struct fwd_attribute_t<T[N], meta::enable_if_t<meta::is_num_v<T>>>
    {
        using input_t = T[N];
        using type = meta::fwd_attribute_t<T[N]>;

        constexpr type operator()(const input_t& attribute) const
        {
            auto result = type{};
            for (size_t i=0; i<N; i++) {
                result[i] = attribute[i];
            }
            return result;
        }
    }; // fwd_attribute_t

    template <typename T>
    constexpr auto fwd_attribute(const T& attribute)
        -> meta::type_t<fwd_attribute_t<T>>
    {
        auto op = fwd_attribute_t<T>{};
        return op(attribute);
    } // fwd_attribute

    template <typename...Ts>
    constexpr auto pack_operands(const Ts&...ts)
    {
        using result_t = nmtools_tuple<meta::fwd_operand_t<meta::remove_cvref_t<Ts>>...>;
        return result_t{fwd_operand(ts)...};
    }

    template <typename...Ts>
    constexpr auto pack_attributes(const Ts&...ts)
    {
        using result_t = nmtools_tuple<meta::type_t<fwd_attribute_t<Ts>>...>;
        return result_t{fwd_attribute(ts)...};
    }

    template <typename T, template<typename...>typename tuple, typename...Ts, auto...Is>
    constexpr auto push_operands(const T& t, const tuple<Ts...>& ts
        , meta::index_sequence<Is...>)
    {
        using result_t = tuple<
              meta::fwd_operand_t<T>
            , meta::fwd_operand_t<meta::remove_cvref_t<Ts>>...>;
        return result_t{fwd_operand(t),fwd_operand(nmtools::get<Is>(ts))...};
    }

    template <typename T, template<typename...>typename tuple, typename...Ts>
    constexpr auto push_operands(const T& t, const tuple<Ts...>& ts)
    {
        auto t_sequence = meta::make_index_sequence_v<sizeof...(Ts)>;
        return push_operands(t,ts,t_sequence);
    }

    template <typename T, template<typename...>typename tuple, typename...Ts, auto...Is>
    constexpr auto append_operands(const tuple<Ts...>& ts, const T& t)
    {
        using result_t = tuple<
              meta::fwd_operand_t<meta::remove_cvref_t<Ts>>...
            , meta::fwd_operand_t<T>>;
        return result_t{fwd_operand(nmtools::get<Is>(ts))...,fwd_operand(t)};
    }

    template <typename T, template<typename...>typename tuple, typename...Ts>
    constexpr auto append_operands(const tuple<Ts...>& ts, const T& t)
    {
        auto t_sequence = meta::make_index_sequence_v<sizeof...(Ts)>;
        return append_operands(ts,t,t_sequence);
    }

    template <template<typename...>typename tuple, typename...Ts, typename...Us, auto...TIs, auto...UIs>
    constexpr auto cat_operands(const tuple<Ts...>& ts, const tuple<Us...>& us
        , meta::index_sequence<TIs...>, meta::index_sequence<UIs...>)
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
        auto t_sequence = meta::make_index_sequence_v<sizeof...(Ts)>;
        auto u_sequence = meta::make_index_sequence_v<sizeof...(Us)>;
        return cat_operands(ts,us,t_sequence,u_sequence);
    }
} // namespace nmtools

#endif // NMTOOLS_UTILITY_FWD_HPP