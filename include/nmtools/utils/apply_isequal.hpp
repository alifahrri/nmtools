#ifndef NMTOOLS_UTILS_APPLY_ISEQUAL_HPP
#define NMTOOLS_UTILS_APPLY_ISEQUAL_HPP

#include "nmtools/utils/isequal.hpp"

namespace nmtools::utils
{
    /**
     * @brief applicative isequal
     * 
     * @tparam left_t 
     * @tparam right_t 
     * @param left 
     * @param right 
     * @return true 
     * @return false 
     */
    template <typename left_t, typename right_t>
    constexpr inline auto apply_isequal(const left_t& left, const right_t& right) -> bool
    {
        if constexpr (
                // currently some nested array are allowed
                // TODO: remove nested array as ndarray
               (!meta::is_list_v<left_t> && !meta::is_list_v<right_t>)
            && (meta::is_ndarray_v<left_t> || meta::is_num_v<left_t>)
            && (meta::is_ndarray_v<right_t> || meta::is_num_v<right_t>)
        ) {
            return utils::isequal(left,right);
        } else if constexpr (meta::is_list_v<left_t> && meta::is_list_v<right_t>) {
            auto equal = len(left) == len(right);
            for (size_t i=0; (i<len(left)) && (i<len(right)); i++) {
                equal = equal && apply_isequal(at(left,i),at(right,i));
            }
            return equal;
        } else if constexpr (meta::is_tuple_v<left_t> && meta::is_list_v<right_t>) {
            auto equal = len(left) == len(right);
            meta::template_for<meta::len_v<left_t>>([&](auto i){
                if (equal) {
                    equal = equal && apply_isequal(at(left,i),at(right,i));
                }
            });
            return equal;
        } else if constexpr (meta::is_list_v<left_t> && meta::is_tuple_v<right_t>) {
            auto equal = len(left) == len(right);
            meta::template_for<meta::len_v<right_t>>([&](auto i){
                if (equal) {
                    equal = equal && apply_isequal(at(left,i),at(right,i));
                }
            });
            return equal;
        } else /* if constexpr (meta::is_tuple_v<left_t> && meta::is_tuple_v<right_t>) */ {
            auto equal = len(left) == len(right);
            constexpr auto n_res = meta::len_v<left_t>;
            constexpr auto n_exp = meta::len_v<right_t>;
            constexpr auto N = (n_res > n_exp ? n_res : n_exp);
            meta::template_for<N>([&](auto i){
                if (equal) {
                    equal = equal && apply_isequal(at(left,i),at(right,i));
                }
            });
            return equal;
        }
    } // apply_isequal
} // namespace nmtools::utils

#endif // NMTOOLS_UTILS_APPLY_ISEQUAL_HPP