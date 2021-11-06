#ifndef NMTOOLS_META_COMMON_HPP
#define NMTOOLS_META_COMMON_HPP

namespace nmtools::meta
{
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

    struct false_type
    {
        using value_type = bool;
        static constexpr auto value = false;
        operator value_type()
        {
            return value;
        }
    };

    struct true_type
    {
        using value_type = bool;
        static constexpr auto value = true;
        operator value_type()
        {
            return value;
        }
    };


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
} // nmtools::meta

namespace nmtools::meta
{
    /**
     * @brief Create default fixed-size ndarray.
     * Forward declaration, to be defined later.
     * 
     * @tparam element_t desired element type
     * @tparam shape_t   desired shape
     */
    template <typename element_t, typename shape_t>
    struct make_fixed_ndarray;

    /**
     * @brief Create default dynamic-size ndarray.
     * Forward declaration, to be defined later.
     * 
     * @tparam element_t desired element type
     */
    template <typename element_t>
    struct make_dynamic_ndarray;

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

#endif // NMTOOLS_META_COMMON_HPP