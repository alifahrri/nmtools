#ifndef NMTOOLS_META_BITS_TRAITS_IS_SPECIALIZATION
#define NMTOOLS_META_BITS_TRAITS_IS_SPECIALIZATION

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    /**
     * @brief check if given type T is specialization of template-template param primary_template
     * 
     * @tparam T type to check
     * @tparam primary_template primary template
     */
    template <typename T, template <typename...> typename primary_template>
    struct is_specialization : false_type {};

    template <template <typename...> typename primary_template, typename... Args>
    struct is_specialization<primary_template<Args...>, primary_template> : true_type {};

    /**
     * @brief helper alias template for is_specialization
     * 
     * @tparam T type to check
     * @tparam primary_template primary template 
     */
    template <typename T, template <typename...> typename primary_template>
    inline constexpr auto is_specialization_v = is_specialization<T,primary_template>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_IS_SPECIALIZATION