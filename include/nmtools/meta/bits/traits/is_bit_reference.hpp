#ifndef NMTOOLS_META_BITS_TRAITS_IS_BIT_REFERENCE_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_BIT_REFERENCE_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    /**
     * @brief check if type T is std::_Bit_reference
     * 
     * This trait is added since std::vector<bool> access return std::_Bit_reference
     * and specializing is_integral is undefined behaviour
     * 
     * @tparam T 
     * @tparam typename 
     */
    template <typename T>
    struct is_bit_reference : false_type {};

    template <typename T>
    inline constexpr auto is_bit_reference_v = is_bit_reference<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_IS_BIT_REFERENCE_HPP