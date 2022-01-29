#ifndef NMTOOLS_UTILS_APPLY_TO_STRING_HPP
#define NMTOOLS_UTILS_APPLY_TO_STRING_HPP

#include "nmtools/utils/to_string.hpp"
#include "nmtools/meta.hpp"

namespace nmtools::utils
{
    /**
     * @brief applicative to_string
     * 
     * @tparam T 
     * @param array 
     * @return nmtools_string 
     */
    template <typename T>
    inline auto apply_to_string(const T& array) -> nmtools_string
    {
        if constexpr (meta::is_list_v<T>) {
            auto str = nmtools_string();
            for (size_t i=0; i<len(array); i++) {
                str += nmtools::utils::to_string(at(array,i));
                str += ";\n";
            }
            return str;
        } else if constexpr (meta::is_tuple_v<T>) {
            auto str = nmtools_string();
            meta::template_for<meta::len_v<T>>([&](auto i){
                str += nmtools::utils::to_string(at(array,i));
                str += ";\n";
            });
            return str;
        } else {
            return nmtools::utils::to_string(array);
        }
    }
} // namespace nmtools::utils

#endif // NMTOOLS_UTILS_APPLY_TO_STRING_HPP