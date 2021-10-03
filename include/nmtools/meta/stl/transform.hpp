#ifndef NMTOOLS_META_STL_TRANSFORM_HPP
#define NMTOOLS_META_STL_TRANSFORM_HPP

#include "nmtools/meta/transform.hpp"

#include <optional>

namespace nmtools::meta
{

#ifndef NMTOOLS_META_MAKE_MAYBE_TYPE
#define NMTOOLS_META_MAKE_MAYBE_TYPE
    template <typename T, typename>
    struct make_maybe_type
    {
        using type = std::optional<T>;
    }; // make_maybe_type

    template <typename T>
    using make_maybe_type_t = type_t<make_maybe_type<T>>;

    // std::nullopt_t has no default constructor
    inline constexpr auto nothing = ::std::nullopt;

    // useful for detect nothing
    using nothing_t = meta::remove_cvref_t<decltype(nothing)>;
#endif // NMTOOLS_META_MAKE_MAYBE_TYPE


#ifndef NMTOOLS_META_MAKE_UNSIGNED
#define NMTOOLS_META_MAKE_UNSIGNED

    /**
     * @brief define make_unsigned to use std::make_unsigned
     * 
     * @tparam T 
     */
    template <typename T>
    struct make_unsigned : ::std::make_unsigned<T> {};

    template <typename T>
    using make_unsigned_t = type_t<make_unsigned<T>>;
#endif // NMTOOLS_META_MAKE_UNSIGNED

#ifndef NMTOOLS_META_MAKE_SIGNED
#define NMTOOLS_META_MAKE_SIGNED

    /**
     * @brief define make_signed to use std::make_signed
     * 
     * @tparam T type to be transformed
     */
    template<typename T>
    struct make_signed : ::std::make_signed<T> {};

    template <typename T>
    using make_signed_t = type_t<make_signed<T>>;
#endif // NMTOOLS_META_MAKE_SIGNED


#ifndef NMTOOLS_META_MAKE_TUPLE
#define NMTOOLS_META_MAKE_TUPLE

    /**
     * @brief define meta::make_tuple to return std::tuple
     * 
     * @tparam Ts 
     */
    template <typename...Ts>
    struct make_tuple
    {
        using type = ::std::tuple<Ts...>;
    }; // make_tuple

    template <typename...Ts>
    using make_tuple_t = type_t<make_tuple<Ts...>>;
#endif // NMTOOLS_META_MAKE_TUPLE

    // TODO: add make_tuple, make_either...

// the following code breaks gcc: "internal compiler error: in finish_member_declaration, at cp/semantics.c:3237"
// (even in newest version: 11.2), works fine on clang, check the else block for workaround
// https://github.com/alifahrri/nmtools/runs/3708887742?check_suite_focus=true
// https://github.com/alifahrri/nmtools/pull/156/checks?check_run_id=3708887743
// https://github.com/alifahrri/nmtools/pull/156/checks?check_run_id=3711520594
#if 0
    /**
     * @brief Specialization fo to_value for std types (tuple of int constant)
     * 
     * @tparam Is 
     */
    template <auto...Is>
    struct to_value<
        std::tuple<std::integral_constant<decltype(Is),Is>...>
    >
    {
        using tuple_type = std::tuple<std::integral_constant<decltype(Is),Is>...>;
        using value_type = std::common_type_t<decltype(Is)...>;
        // The following line breaks gcc (even in newest version: 11.2)
        static inline constexpr auto value = std::array<value_type,sizeof...(Is)>{static_cast<value_type>(Is)...};

        // trying to find workaround but didn't work
        // static constexpr auto value = [](){
        //     using type = std::array<value_type,sizeof...(Is)>;
        //     auto dst = type{};
        //     meta::template_for<sizeof...(Is)>([&](auto index){
        //         constexpr auto i = decltype(index)::value;
        //         constexpr auto v = std::tuple_element_t<i,tuple_type>::value;
        //         dst[i] = v;
        //     });
        //     return dst;
        // }();
    }; // to_value

#else
    template <typename...Ts>
    struct to_value<
        std::tuple<Ts...>
    >
    {
        using tuple_type = type_list<Ts...>;
        static constexpr auto value = [](){
            constexpr auto N = sizeof...(Ts);
            // for simplicity, use int as value type for now
            using array_type = std::array<int,N>;
            return meta::template_reduce<N>([&](auto init, auto index){
                constexpr auto i = decltype(index)::value;
                using init_t = remove_cvref_t<decltype(init)>;
                using type_i = type_list_at_t<i,tuple_type>;
                if constexpr (is_integral_constant_v<type_i>) {
                    if constexpr (i==0) {
                        // starting point, create the array
                        auto array = array_type{};
                        array[i] = type_i::value;
                        return array;
                    } else if constexpr (std::is_same_v<init_t,error::TO_VALUE_UNSUPPORTED>) {
                        return error::TO_VALUE_UNSUPPORTED{};
                    } else {
                        init[i] = type_i::value;
                        return init;
                    }
                } else {
                    return error::TO_VALUE_UNSUPPORTED{};
                }
            }, error::TO_VALUE_UNSUPPORTED{});
        }();
    }; // to_value
#endif

    template <auto I>
    struct to_value<std::integral_constant<decltype(I),I>>
    {
        static inline constexpr auto value = I;
    }; // to_value

    // some edge case: array of constant, simply transform to value
    // such array exist maybe because element type deduction is imperfect
    // or couldnt handle such case
    template <auto I, size_t N>
    struct to_value<std::array<std::integral_constant<decltype(I),I>,N>>
    {
        static inline constexpr auto value = [](){
            using type = std::array<decltype(I),N>;
            auto value = type{};
            for (size_t i=0; i<N; i++) {
                value[i] = I;
            }
            return value;
        }();
    }; // to_value

#ifndef NMTOOLS_META_MAKE_ARRAY_TYPE
#define NMTOOLS_META_MAKE_ARRAY_TYPE

    template <typename T, size_t N, typename>
    struct make_array_type
    {
        using type = std::array<T,N>;
    }; // make_array_type

    template <typename T, size_t N>
    using make_array_type_t = type_t<make_array_type<T,N>>;
#endif // NMTOOLS_META_MAKE_ARRAY_TYPE

    template <typename left_t, typename right_t>
    struct get_either_left<std::variant<left_t,right_t>>
    {
        using type = left_t;
    };

    template <typename left_t, typename right_t>
    struct get_either_right<std::variant<left_t,right_t>>
    {
        using type = right_t;
    };

    template <typename left_t, typename right_t>
    struct get_either_left<const std::variant<left_t,right_t>>
    {
        using type = left_t;
    };

    template <typename left_t, typename right_t>
    struct get_either_right<const std::variant<left_t,right_t>>
    {
        using type = right_t;
    };

} // namespace nmtools::meta

#endif // NMTOOLS_META_STL_TRANSFORM_HPP