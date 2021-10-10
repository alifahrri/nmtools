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

    template <typename...Ts, size_t I>
    struct type_at<std::tuple<Ts...>,I>
    {
        using tuple_t = std::tuple<Ts...>;
        using type = std::tuple_element_t<I,tuple_t>;
    }; // type_at


    /**
     * @brief specialization of resize_fixed_vector for std::array type
     * 
     * @tparam T value_type of std::array, automatically deduced
     * @tparam N size of std::array, automatically deduced
     * @tparam new_size new desired size
     */
    template <typename T, auto N, auto new_size>
    struct resize_fixed_vector<std::array<T,N>,new_size>
    {
        using type = std::array<T,new_size>;
    };

    /**
     * @brief specialization of resize_fixed_vector for raw array type,
     * resulting type is std::array instead of raw array.
     * 
     * @tparam T element type of raw array, automatically deduced
     * @tparam N size of raw array, automatically deduced
     * @tparam new_size new desired size
     */
    template <typename T, auto N, auto new_size>
    struct resize_fixed_vector<T[N],new_size>
    {
        using type = std::array<T,new_size>;
    };

    template <typename...Ts>
    struct tuple_to_array<std::tuple<Ts...>>
    {
        using common_t = std::common_type_t<Ts...>;
        using type = std::array<common_t,sizeof...(Ts)>;
    }; // tuple_to_array

    template <typename first, typename second>
    struct tuple_to_array<std::pair<first,second>>
    {
        using common_t = std::common_type_t<first,second>;
        using type = std::array<common_t,2>;
    }; // tuple_to_array

    /**
     * @brief overloaded version of transform_bounded_array for T[N]
     * 
     * @tparam T element type
     * @tparam N number of elements
     */
    template <typename T, std::size_t N>
    struct transform_bounded_array<T[N]>
    {
        using value_type = typename transform_bounded_array<remove_cvref_t<T>>::type;
        using type = std::array<remove_cvref_t<value_type>,N>;
    };

#ifndef NMTOOLS_META_MAKE_CT
#define NMTOOLS_META_MAKE_CT
    template <auto I, auto...Is>
    struct make_ct
    {
        static constexpr auto vtype = [](){
            if constexpr (static_cast<bool>(sizeof...(Is))) {
                using type = std::integer_sequence<decltype(I),I,Is...>;
                return as_value_v<type>;
            } else {
                return as_value_v<std::integral_constant<decltype(I),I>>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };

    template <auto I, auto...Is>
    using ct = type_t<make_ct<I,Is...>>;

    template <auto I, auto...Is>
    constexpr inline auto ct_v = ct<I,Is...>{};
#endif // NMTOOLS_META_MAKE_CT

    /**
     * @brief Replace element type of std::array
     * 
     * @tparam T src element type, maybe nested array
     * @tparam N 
     * @tparam U dst element type
     */
    template <typename T, size_t N, typename U>
    struct replace_element_type<std::array<T,N>,U,std::enable_if_t<std::is_arithmetic_v<U>>>
    {
        static constexpr auto vtype = [](){
            if constexpr (std::is_arithmetic_v<T>) {
                using type = std::array<U,N>;
                return as_value_v<type>;
            }
            else {
                using element_t = type_t<replace_element_type<T,U>>;
                using type = std::array<element_t,N>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // replace_element_type

    template <typename...Ts, typename new_type>
    struct append_type<std::tuple<Ts...>,new_type>
    {
        using type = std::tuple<Ts...,new_type>;
    }; // append_type

    template <typename...Ts, typename...Us>
    struct concat_type< std::tuple<Ts...>, std::tuple<Us...> >
    {
        using type = std::tuple<Ts...,Us...>;
    }; // concat_type

    /**
     * @brief Specialization of resize_fixed_ndarray for std::array.
     * 
     * @tparam T 
     * @tparam U 
     * @tparam N 
     * @todo move to separate file, e.g. meta/stl/transform.hpp
     */
    template <typename T, typename U, size_t N>
    struct resize_fixed_ndarray<std::array<T,N>,U,
        std::enable_if_t<is_fixed_size_ndarray_v<U>>
    >
    {
        template <typename array_t, typename new_t>
        struct replace_value_type
        {
            using type = void;
        };

        template <typename value_t, size_t M, typename new_t>
        struct replace_value_type<std::array<value_t,M>,new_t>
        {
            static constexpr auto vtype = [](){
                if constexpr (is_num_v<value_t>) {
                    using type = std::array<new_t,M>;
                    return as_value_v<type>;
                } else {
                    using inner_t = type_t<replace_value_type<value_t,new_t>>;
                    using type = std::array<inner_t,M>;
                    return as_value_v<type>;
                }
            }();
            using type = type_t<decltype(vtype)>;
        };
        
        static constexpr auto vtype = [](){
            constexpr auto shape = fixed_ndarray_shape_v<U>;
            constexpr auto DIM   = fixed_ndarray_dim_v<U>;
            using element_t = get_element_type_t<std::array<T,N>>;
            return template_reduce<DIM>([&](auto init, auto index){
                constexpr auto i = decltype(index)::value;
                using init_t = type_t<remove_cvref_t<decltype(init)>>;
                constexpr auto size = std::get<i>(shape);
                if constexpr (i==0) {
                    using type = std::array<element_t,size>;
                    return as_value_v<type>;
                } else {
                    using array_t = init_t;
                    using inner_t = std::array<element_t,size>;
                    using type = type_t<replace_value_type<array_t,inner_t>>;
                    return as_value_v<type>;
                }
            }, /*init=*/as_value_v<void>);
        }();
        using type = type_t<decltype(vtype)>;
    }; // resize_fixed_ndarray

    template <typename T, typename U, size_t N>
    struct resize_fixed_ndarray<T[N],U,
        std::enable_if_t<is_fixed_size_ndarray_v<U>>
    >
    {
        using shape_t = std::tuple<std::integral_constant<size_t,N>>;
        using default_ndarray_t = type_t<make_fixed_ndarray<T,shape_t>>;
        using type = resize_fixed_ndarray_t<default_ndarray_t,U>;
    }; // resize_fixed_ndarray

    template <typename left_t, typename right_t, typename Left, typename Right>
    struct replace_either<std::variant<left_t,right_t>,Left,Right>
    {
        using type = std::variant<Left,Right>;
    };

} // namespace nmtools::meta

#endif // NMTOOLS_META_STL_TRANSFORM_HPP