#ifndef NMTOOLS_ARRAY_UTILITY_ONES_LIKE_HPP
#define NMTOOLS_ARRAY_UTILITY_ONES_LIKE_HPP

/* common tag for preconditions, e.g. size assertion */
#include "nmtools/utility/tag.hpp"
/* common array (as in matrix/vector) utility */
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/utility/shape.hpp"

#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"
#include <type_traits>
#include <cmath>
#include <cassert>

namespace nmtools
{
    /* make symbols accessible for unqualified-lookup */
    using std::get;
    using std::size;
    using std::fabs;
    using std::sqrt;
    using std::tuple_size;
    using std::tuple_size_v;

    /**
     * @brief create matrix/vector filled with 1s
     * 
     * @tparam T matrix/vector/arithmetic
     * @param a example of existing matrix/vector
     * @return constexpr auto 
     */
    template <typename T>
    constexpr auto ones_like(const T& a)
    {
        /** TODO: proper constraints **/
        static_assert(
            traits::is_array1d_v<T> ||
            traits::is_array2d_v<T> ||
            std::is_arithmetic_v<T>,
            "unsupported type for zeros_like"
        );
        using traits::remove_cvref_t;
        using meta::transform_bounded_array_t;
        using return_t = transform_bounded_array_t<remove_cvref_t<T>>;
        auto ret = return_t{};
        /* ret is aritmethic type (scalr), return as it is */
        if constexpr (std::is_arithmetic_v<T>)
            return static_cast<T>(1);
        /* ret is conteiner, for each elements call zeros_like */
        else {
            auto ret = zeros_like(a);
            using return_t = traits::remove_cvref_t<decltype(ret)>;
            /* array2d implementation */
            if constexpr (traits::is_array2d_v<return_t>)
            {
                /* common implementation loop for both fixed and dynamic */
                auto ones_like2d_impl = [](auto &ret, auto rows, auto cols){
                    for (size_t i=0; i<rows; i++)
                        for (size_t j=0; j<cols; j++)
                            at(ret,i,j) = 1;
                };
                constexpr auto is_fixed_size = traits::is_fixed_size_matrix_v<return_t>;
                if constexpr (is_fixed_size) {
                    /* TODO: find-out if reading matrix_size as constexpr is beneficial */
                    constexpr auto shape = matrix_size(ret);
                    constexpr auto rows = std::get<0>(shape);
                    constexpr auto cols = std::get<1>(shape);
                    ones_like2d_impl(ret,rows,cols);
                }
                else {
                    auto [rows, cols] = matrix_size(ret);
                    ones_like2d_impl(ret,rows,cols);
                }
            }
            /* array1d implementation */
            else {
                /* common implementation loop for 1d fixed and dynamic */
                auto ones_like1d_impl = [](auto &ret, auto n){
                    for (size_t i=0; i<n; i++)
                        at(ret,i) = 1;
                };
                constexpr auto is_fixed_size = traits::is_fixed_size_vector_v<return_t>;
                if constexpr (is_fixed_size) {
                    constexpr auto n = vector_size(ret);
                    ones_like1d_impl(ret,n);
                }
                else {
                    auto n = vector_size(ret);
                    ones_like1d_impl(ret,n);
                }
            }
            return ret;
        }
    } // constexpr auto ones_like(const T& a)
}
#endif // NMTOOLS_ARRAY_UTILITY_ONES_LIKE_HPP