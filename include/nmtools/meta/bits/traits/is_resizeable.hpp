#ifndef NMTOOLS_META_BITS_TRAITS_IS_RESIZEABLE_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_RESIZEABLE_HPP

#include "nmtools/meta/expr.hpp"
#include "nmtools/meta/bits/traits/has_size_type.hpp"

namespace nmtools::meta
{
    /**
     * @brief trait to check if given type T is resizeable with size_types as arguments.
     * 
     * @tparam T type to check
     * @tparam size_types arguments to `resize`
     */
    template <typename T, typename...size_types>
    struct is_resizeable_nd : detail::expression_check<void,expr::resizend,T,size_types...>{};

    /**
     * @brief helper variable template to check if given type T is resizeable with size_types as arguments.
     * 
     * @tparam T type to check
     * @tparam size_types arguments to `resize`
     */
    template <typename T, typename...size_types>
    inline constexpr bool is_resizeable_nd_v = is_resizeable_nd<T,size_types...>::value;

    // TODO: cleanup metafunctions
    /**
     * @brief check if given type T is resizeable (1D).
     *
     * Default implementation will check if T has size_type,
     * then calls is_resizeable_nd with size_type as arguments,
     * otherwise assume size_type is size_t then call is_resizeable_nd.
     * 
     * @tparam T 
     * @tparam typename 
     */
    template <typename T, typename=void>
    struct is_resizeable
    {
        /**
         * @brief default implementation for actual checking,
         * implemented as static member function to avoid clunky sfinae
         * and allows to easily specialize specific type.
         * 
         * @return constexpr auto 
         */
        static constexpr auto value = [](){
            if constexpr (has_size_type_v<T>) {
                using size_type = typename T::size_type;
                return is_resizeable_nd_v<T,size_type>;
            }
            else {
                using size_type = size_t;
                return is_resizeable_nd_v<T,size_type>;
            }
        }();
    }; // is_resizeable

    /**
     * @brief helper variable template to check if type T is resizeable
     * 
     * @tparam T type to check
     */
    template <typename T>
    inline constexpr bool is_resizeable_v = is_resizeable<T>::value;

    // TODO: cleanup metafunctions
    /**
     * @brief check if given type T is resizeable (2D).
     *
     * Default implementation will check if T has size_type,
     * then calls is_resizeable_nd with size_type as arguments,
     * otherwise assume size_type is size_t then call is_resizeable_nd.
     * 
     * @tparam T 
     * @tparam typename 
     */
    template <typename T, typename=void>
    struct is_resizeable2d
    {
        /**
         * @brief default implementation for actual checking,
         * implemented as static member function to avoid clunky sfinae
         * and allows to easily specialize specific type.
         * 
         * @return constexpr auto 
         */
        static constexpr auto value = [](){
            if constexpr (has_size_type_v<T>) {
                using size_type = typename T::size_type;
                return is_resizeable_nd_v<T,size_type,size_type>;
            }
            else {
                using size_type = size_t;
                return is_resizeable_nd_v<T,size_type,size_type>;
            }
        }();
    };

    /**
     * @brief helper variable template to check if type T is resizeable
     * 
     * @tparam T type to check
     */
    template <typename T>
    inline constexpr bool is_resizeable2d_v = is_resizeable2d<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_IS_RESIZEABLE_HPP