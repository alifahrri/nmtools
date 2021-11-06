#ifndef NMTOOLS_META_BITS_TRAITS_IS_INDEX_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_INDEX_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/is_constant_index.hpp"
#include "nmtools/meta/bits/traits/is_integer.hpp"
#include "nmtools/meta/bits/traits/is_integral_constant.hpp"

namespace nmtools::meta
{
    /**
     * @brief Check if type `T` is an index
     * 
     * @tparam T 
     * @tparam typename 
     */
    template <typename T, typename=void>
    struct is_index
    {
        static constexpr auto value = [](){
            return is_constant_index_v<T> || is_integer_v<T>;
        }();
    };

    template <typename T>
    inline constexpr auto is_index_v = is_index<T>::value;

    // this allow bool to be considered as "index"
    // TODO: remove
    /**
     * @brief 
     * 
     * @tparam T 
     */
    template <typename T>
    struct is_index<T, enable_if_t<
        std::is_integral_v<T> || is_integral_constant_v<T>
    > > : true_type {};
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_IS_INDEX_HPP