#ifndef NMTOOLS_ARRAY_INDEX_MAKE_ARRAY_HPP
#define NMTOOLS_ARRAY_INDEX_MAKE_ARRAY_HPP

// TODO: remove this file

#include <type_traits>
#include <cstddef> // size_t
#include <utility> // integer_sequence
#include <array>
#include <tuple>

#include "nmtools/meta.hpp"

namespace nmtools::index
{
    /**
     * @addtogroup index
     * @{
     */

    // TODO: remove
    /**
     * @brief given array-like a, make array of type array_t,
     * where the element is initialized using elements of array-like a
     * at indices I... with offset, e.g. {a[I+offset]...}.
     * 
     * @tparam array_t desired array_t, asuming aggregate initialization is well-formed
     * @tparam T array-like
     * @tparam I integer sequence to take elements of a
     * @param a array to initialize the resulting array
     * @param offset index offset
     * @return constexpr auto 
     * @see nmtools::row
     * @see nmtools::array::detail::make_array_ref
     */
    template <typename array_t, typename T, size_t ...I>
    constexpr auto make_array(const T &a, std::integer_sequence<size_t, I...>, size_t offset=0)
    {
        return array_t{a[I+offset]...};
    } // make_array

    // TODO: remove
    /**
     * @brief create array from packed type T.
     * <a href="https://godbolt.org/z/v39Goh">godbolt demo</a>.
     * 
     * @tparam array_t desired array template-template param
     * @tparam T 
     * @tparam I 
     * @param a 
     * @return constexpr auto 
     * @note underscore prefix added to avoid ambiguous calls with make_array
     * @todo remove prefix
     */
    template <template <typename,size_t> typename array_t, typename T, size_t ...I>
    constexpr auto _make_array(const T &a, std::integer_sequence<size_t, I...>)
    {
        using common_t = std::common_type_t<decltype(std::get<I>(a))...>;
        return array_t{static_cast<common_t>(std::get<I>(a))...};
    } // make_array

    /**
     * @brief create array from single type or packed type T.
     * 
     * @tparam array_t desired array template-template param
     * @tparam T either simply type or pakced type like tuple/pair.
     * @param t 
     * @return constexpr auto 
     */
    template <template <typename,size_t> typename array_t, typename T>
    constexpr auto make_array(T&& t)
    {
        // @note meta::remove_cvref_t is required to properly check the traits!
        if constexpr (meta::has_tuple_size_v<meta::remove_cvref_t<T>>) {
            using indices_t = std::make_index_sequence<std::tuple_size_v<meta::remove_cvref_t<T>>>;
            return _make_array<array_t>(std::forward<T>(t), indices_t{});
        }
        else {
            return array_t{std::forward<T>(t)};
        }
    } // make_array

    /**
     * @brief create array.
     * 
     * @tparam array_t desired array template-template param
     * @tparam T first type
     * @tparam U second type
     * @tparam Ts rest of the type(s)
     * @param t 
     * @param u 
     * @param ts 
     * @return constexpr auto 
     */
    template <template <typename,size_t> typename array_t, typename T, typename U, typename...Ts>
    constexpr auto make_array(T&& t, U&& u, Ts&&...ts)
    {
        using common_type = std::common_type_t<T,U,Ts...>;
        return array_t{
            static_cast<common_type>(std::forward<T>(t)),
            static_cast<common_type>(std::forward<U>(u)),
            static_cast<common_type>(std::forward<Ts>(ts))...
        };
    } // make_array

    /**
     * @brief helper alias template to make array of reference
     * 
     * @tparam T 
     * @tparam N 
     */
    template <typename T, size_t N>
    using array_ref = std::array<std::reference_wrapper<T>,N>;

    /**
     * @brief helper alias template for make_array_ref
     * 
     * @tparam N 
     */
    template <size_t N>
    using size_constant = std::integral_constant<size_t,N>;

    // TODO: remove
    /**
     * @brief create array of reference from a.
     * With new_size starting from offset.
     * 
     * @tparam T value_type of a
     * @tparam N size of a
     * @tparam new_size new size of returning array ref
     * @param a array to take reference of
     * @param offset starting index, e.g. a[I+offset]...
     * @return auto array of reference
     */
    template <typename T, size_t N, size_t new_size>
    constexpr auto make_array_ref(std::array<T,N> &a, size_constant<new_size>, size_t offset=0)
    {
        using array_t = array_ref<T,N>;
        return make_array<array_t>(a, std::make_index_sequence<new_size>{}, offset);
    }

    // TODO: remove
    /**
     * @brief create array of reference from a.
     * With new_size starting from offset.
     * 
     * @tparam T value_type of a
     * @tparam N size of a
     * @tparam new_size new size of returning array ref
     * @param a array to take reference of
     * @param offset starting index, e.g. a[I+offset]...
     * @return auto array of reference
     */
    template <typename T, size_t N, size_t new_size>
    constexpr auto make_array_ref(const std::array<T,N> &a, size_constant<new_size>, size_t offset=0)
    {
        return make_array(a, std::make_index_sequence<new_size>{}, offset);
    }

    /** @} */ // end group index
} // namespace nmtools::index

#endif // NMTOOLS_ARRAY_INDEX_MAKE_ARRAY_HPP