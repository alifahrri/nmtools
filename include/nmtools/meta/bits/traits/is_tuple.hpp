#ifndef NMTOOLS_META_BITS_TRAITS_IS_TUPLE_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_TUPLE_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    /**
     * @brief check if given type is tuple kind.
     *
     * Note that this is not necessarily std::tuple,
     * this is intended to be more like tuple in concept.
     * The choice of the name, tuple, is from haskell Tuple.
     */
    template <typename>
    struct is_tuple : false_type {};

    /**
     * @brief helper variable template to check if given type is tuple
     * 
     * @tparam Args automatically deduced
     * @example 
     *  static_assert(is_tuple_v<std::tuple<int,double>> == true);
     *  static_assert(is_tuple_v<double> == false);
     */
    template <typename ...Args>
    inline constexpr bool is_tuple_v = is_tuple<Args...>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_IS_TUPLE_HPP