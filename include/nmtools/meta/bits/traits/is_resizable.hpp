#ifndef NMTOOLS_META_BITS_TRAITS_IS_resizable_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_resizable_HPP

#include "nmtools/meta/expr.hpp"
#include "nmtools/meta/bits/traits/has_size_type.hpp"

namespace nmtools::meta
{
    /**
     * @brief trait to check if given type T is resizable with size_types as arguments.
     * 
     * @tparam T type to check
     * @tparam size_types arguments to `resize`
     */
    template <typename T, typename...size_types>
    struct is_resizable_nd : detail::expression_check<void,expr::resizend,T,size_types...>{};

    /**
     * @brief helper variable template to check if given type T is resizable with size_types as arguments.
     * 
     * @tparam T type to check
     * @tparam size_types arguments to `resize`
     */
    template <typename T, typename...size_types>
    nmtools_meta_variable_attribute
    inline constexpr bool is_resizable_nd_v = is_resizable_nd<T,size_types...>::value;

    // TODO: cleanup metafunctions
    /**
     * @brief check if given type T is resizable (1D).
     *
     * Default implementation will check if T has size_type,
     * then calls is_resizable_nd with size_type as arguments,
     * otherwise assume size_type is size_t then call is_resizable_nd.
     * 
     * @tparam T 
     * @tparam typename 
     */
    template <typename T, typename=void>
    struct is_resizable
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
                return is_resizable_nd_v<T,size_type>;
            }
            else {
                using size_type = size_t;
                return is_resizable_nd_v<T,size_type>;
            }
        }();
    }; // is_resizable

    /**
     * @brief helper variable template to check if type T is resizable
     * 
     * @tparam T type to check
     */
    template <typename T>
    nmtools_meta_variable_attribute
    inline constexpr bool is_resizable_v = is_resizable<T>::value;

    // TODO: cleanup metafunctions
    /**
     * @brief check if given type T is resizable (2D).
     *
     * Default implementation will check if T has size_type,
     * then calls is_resizable_nd with size_type as arguments,
     * otherwise assume size_type is size_t then call is_resizable_nd.
     * 
     * @tparam T 
     * @tparam typename 
     */
    template <typename T, typename=void>
    struct is_resizable2d
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
                return is_resizable_nd_v<T,size_type,size_type>;
            }
            else {
                using size_type = size_t;
                return is_resizable_nd_v<T,size_type,size_type>;
            }
        }();
    };

    /**
     * @brief helper variable template to check if type T is resizable
     * 
     * @tparam T type to check
     */
    template <typename T>
    inline constexpr bool is_resizable2d_v = is_resizable2d<T>::value;
} // namespace nmtools::meta

namespace nmtools
{
    using meta::is_resizable_v;
}

#endif // NMTOOLS_META_BITS_TRAITS_IS_resizable_HPP