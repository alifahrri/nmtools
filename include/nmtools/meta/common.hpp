#ifndef NMTOOLS_META_COMMON_HPP
#define NMTOOLS_META_COMMON_HPP

#include "nmtools/platform.hpp"
#include "nmtools/def.hpp"

namespace nmtools::meta
{
    template <typename...>
    using void_t = void;

    /**
     * @brief helper alias template to get public member type `type` from type T
     * 
     * @tparam T type to transform
     */
    template <typename T>
    using type_t = typename T::type;

    /**
     * @brief 
     * 
     * @tparam T 
     */
    template <typename T>
    static inline constexpr auto value_v = T::value;

    template <typename T, T v>
    struct integral_constant
    {
        using value_type = T;
        nmtools_meta_variable_attribute
        static constexpr value_type value = v;
        constexpr operator value_type() const noexcept
        {
            return value;
        }
        constexpr value_type operator()() const noexcept { return value; }
    };

    struct true_type : integral_constant<bool,true> {};
    struct false_type : integral_constant<bool,false> {};

    /**
     * @brief To provide enable_if without depends to stl
     * 
     * @tparam condition 
     * @tparam T 
     */
    template <bool condition, typename T=void>
    struct enable_if {};

    template <typename T>
    struct enable_if<true, T>
    {
        using type = T;
    };

    template <bool condition, typename T=void>
    using enable_if_t = type_t<enable_if<condition,T>>;

    template <typename T, typename U>
    struct is_same : false_type {};

    template <typename T>
    struct is_same<T,T> : true_type {};

    template <typename T, typename U>
    constexpr inline auto is_same_v = is_same<T,U>::value;

    /**
     * @brief Type as value
     * 
     * @tparam T type to wrap
     */
    template <typename T>
    struct as_value
    {
        using type = T;
    };

    /**
     * @brief helper inline variable for as_value
     * 
     * @tparam T type to wrap
     */
    template <typename T>
    constexpr inline auto as_value_v = as_value<T>{};

    template <typename T>
    struct is_vtype : false_type {};

    template <typename T>
    struct is_vtype<as_value<T>> : true_type {};

    template <typename T>
    struct is_vtype<T&> : is_vtype<T> {};

    template <typename T>
    struct is_vtype<const T> : is_vtype<T> {};

    template <typename T>
    constexpr inline auto is_vtype_v = is_vtype<T>::value;

    /**
     * @brief Generic value holder to wrap value as type.
     * 
     * @tparam Ts 
     */
    template <auto...Ts>
    struct as_type {};

    template <auto...Ts>
    constexpr inline auto as_type_v = as_type<Ts...>{};

    template <typename T, T...Ints>
    struct integer_sequence
    {
        using value_type = T;
        static constexpr auto size() noexcept
        {
            return sizeof...(Ints);
        } 
    };

    template <size_t...Ints>
    struct index_sequence : integer_sequence<size_t,Ints...> {};

    namespace detail
    {
        template <typename lhs_t, typename rhs_t>
        struct merge_ix {};

        template<size_t...M, size_t...N>
        struct merge_ix< index_sequence<M...>, index_sequence<N...> >
        {
            using type = index_sequence<M...,N...>;
        };

        template <size_t, typename=void>
        struct make_index_sequence {};

        template <size_t N>
        struct make_index_sequence<N,enable_if_t<(N>0)>>
        {
            static constexpr auto vtype = [](){
                if constexpr (N==1) {
                    using type = index_sequence<0>;
                    return as_value_v<type>;
                } else if constexpr (N==2) {
                    using type = index_sequence<0,1>;
                    return as_value_v<type>;
                } else if constexpr (N>2) {
                    using lhs_t = typename make_index_sequence<N-1>::type;
                    using rhs_t = index_sequence<N-1>;
                    using type  = typename merge_ix< lhs_t, rhs_t >::type;
                    return as_value_v<type>;
                }
            }();
            using type = type_t<decltype(vtype)>;
        };

        template <>
        struct make_index_sequence<0,void>
        {
            using type = index_sequence<>;
        };
    }

    template <size_t N>
    using make_index_sequence = type_t<detail::make_index_sequence<N>>;

    template <size_t N>
    constexpr inline auto make_index_sequence_v = make_index_sequence<N>{};

    // TODO: rename, ct_t maybe
    template <auto I, auto...Is>
    struct make_ct
    {
        static constexpr auto vtype = [](){
            if constexpr (static_cast<bool>(sizeof...(Is))) {
                using type = integer_sequence<decltype(I),I,Is...>;
                return as_value_v<type>;
            } else {
                return as_value_v<integral_constant<decltype(I),I>>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };

    template <auto I, auto...Is>
    using ct = type_t<make_ct<I,Is...>>;

    template <auto I, auto...Is>
    constexpr inline auto ct_v = ct<I,Is...>{};

    // used mostly by functional module
    struct empty_operands_t {};
    struct empty_attributes_t {};
} // nmtools::meta

namespace nmtools::meta
{
    // TODO: remove
    /**
     * @brief Create default fixed-size ndarray.
     * Forward declaration, to be defined later.
     * 
     * @tparam element_t desired element type
     * @tparam shape_t   desired shape
     */
    template <typename element_t, typename shape_t>
    struct make_fixed_ndarray;

    // TODO: remove
    /**
     * @brief Create default dynamic-size ndarray.
     * Forward declaration, to be defined later.
     * 
     * @tparam element_t desired element type
     */
    template <typename element_t>
    struct make_dynamic_ndarray;

    // TODO: remove
    /**
     * @brief Create default hybrid ndarray.
     * 
     * @tparam element_t    Desired element type
     * @tparam max_elements Desired maximum number of elements
     * @tparam dim          Desired number of dimension
     */
    template <typename element_t, auto max_elements, auto dim>
    struct make_hybrid_ndarray;
} // namespace nmtools::meta

namespace nmtools::meta::detail
{
    
    /**
     * @brief helper tag to indicate checking fail at compile-time
     * 
     */
    struct fail_t {};

    // inline variable for convinience
    constexpr inline auto Fail = fail_t{};

    // TODO: remove 
    /**
     * @brief helper metafunction to transform fail_t to void
     *
     * This transform may be used to metafunction that returning a type 
     * from type deduction that may fail by returning fail_t instead of returning void.
     * 
     * @tparam T type to transform
     */
    template <typename T>
    struct fail_to_void
    {
        using type = T;
    }; // fail_to_void

    // TODO: remove
    /**
     * @brief actual case for fail_to_void when T is fail_T
     * 
     * @tparam  
     */
    template <>
    struct fail_to_void<fail_t>
    {
        using type = void;
    }; // fail_to_void

    // TODO: remove
    /**
     * @brief helper alias template to fail_to_void
     * 
     * @tparam T type to transform
     */
    template <typename T>
    using fail_to_void_t = typename fail_to_void<T>::type;

    // TODO: remove
    /**
     * @brief maps void type to fail_t type.
     *
     * This may be helpful if one want to returning value in which it type is
     * deduced from another metafunction that may fail (member type is void),
     * since we can returning void, transform to fail_t instead.
     * 
     * @tparam T type to transform
     */
    template <typename T>
    struct void_to_fail
    {
        using type = T;
    }; // void_to_fail

    // TODO: remove
    /**
     * @brief actual case for void_to_fail when T is void
     * 
     * @tparam 
     */
    template <>
    struct void_to_fail<void>
    {
        using type = fail_t;
    };

    // TODO: remove
    /**
     * @brief helper alias template for void_to_fail.
     * 
     * @tparam T type to transform
     */
    template <typename T>
    using void_to_fail_t = typename void_to_fail<T>::type;

    // TODO: remove
    /**
     * @brief helper function to map fail_t to bool as false
     * 
     * @param v 
     * @return constexpr auto 
     */
    constexpr auto fail_to_false(bool v)
    {
        return v;
    } // fail_to_false

    // TODO: remove
    /**
     * @brief helper function to map fail_t to bool as false
     * 
     * @return constexpr auto 
     */
    constexpr auto fail_to_false(fail_t)
    {
        return false;
    } // fail_to_false
} // namespace nmtools::meta

// TODO: move to constants.hpp
namespace nmtools
{
    /**
     * @brief specific tag to represents "None" type
     * 
     */
    struct none_t {};

    /**
     * @brief special inline variable to represent "None" value
     * 
     */
    inline constexpr auto None = none_t {};

    /**
     * @brief Special tag to represents "..." a.k.a. "Ellipsis" type
     * 
     */
    struct ellipsis_t {};

    inline constexpr auto Ellipsis = ellipsis_t {};

    /**
     * @brief special constant for true_type
     * 
     */
    inline constexpr auto True  = meta::true_type {};

    /**
     * @brief sepcial constant for false_type
     * 
     */
    inline constexpr auto False = meta::false_type {};

    /**
     * @brief Special constant to represents "-1"
     * 
     */
    inline constexpr auto Last = meta::integral_constant<int,-1>{};

    /**
     * @brief helper traits to check for "None" type
     * 
     * @tparam T 
     */
    template <typename T, typename=void>
    struct is_none : meta::false_type {};

    template <>
    struct is_none<none_t> : meta::true_type {};

    template <>
    struct is_none<const none_t> : meta::true_type {};
    template <>
    struct is_none<const none_t&> : meta::true_type {};

    #ifdef __OPENCL_VERSION__
    template <typename T>
    struct is_none<global T> : is_none<T> {};

    template <typename T>
    struct is_none<local T> : is_none<T> {};

    template <typename T>
    struct is_none<private T> : is_none<T> {};

    template <typename T>
    struct is_none<constant T> : is_none<T> {};

    template <typename T>
    struct is_none<generic T> : is_none<T> {};
    #endif // __OPENCL_VERSION__

    /**
     * @brief helper inline variable template to check for "None" type
     * 
     * @tparam T 
     */
    template <typename T>
    inline constexpr auto is_none_v = is_none<T>::value;

    template <typename T>
    struct is_ellipsis : meta::false_type {};

    template <typename T>
    struct is_ellipsis<const T> : is_ellipsis<T> {};

    template <typename T>
    struct is_ellipsis<const T&> : is_ellipsis<T> {};

    template <>
    struct is_ellipsis<ellipsis_t> : meta::true_type {};

    template <typename T>
    inline constexpr auto is_ellipsis_v = is_ellipsis<T>::value;
} // namespace nmtools

#endif // NMTOOLS_META_COMMON_HPP