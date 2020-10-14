#ifndef NMTOOLS_ARRAY_UTILITY_ZEROS_LIKE_HPP
#define NMTOOLS_ARRAY_UTILITY_ZEROS_LIKE_HPP

/* common tag for preconditions, e.g. size assertion */
#include "nmtools/utility/tag.hpp"

#include "nmtools/array/utility/at.hpp"     // at
#include "nmtools/array/utility/shape.hpp"  // matrix_size, vector_size

#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"
#include <type_traits>
#include <cmath>
#include <cassert>

namespace nmtools
{
    /**
     * @brief create zero matrix/vector 
     * 
     * @tparam T matrix/vector/arithmetic
     * @param a example of existing matrix/vector
     * @return constexpr auto 
     */
    template <typename T>
    constexpr auto zeros_like(const T& a)
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
        /* TODO: check if return_t can be instantiated this way */
        auto ret = return_t{};
        /* ret is aritmethic type (scalr), return casted zero */
        if constexpr (std::is_arithmetic_v<T>)
            return static_cast<T>(0);
        /* ret is conteiner, for each elements call zeros_like */
        else {
            /* when T can be resized with 2 arguments, meaning that it is matrix, 
                then we should resize it that way */
            if constexpr (traits::is_array2d_v<T> && traits::is_resizeable2d_v<T>)
            {
                auto [rows, cols] = matrix_size(a);
                ret.resize(rows, cols);
            }
            /* otherwise, also resize each elements of ret */
            else if constexpr (traits::is_resizeable_v<T>) {
                /* TODO: should we use vector_size instead of size? */
                ret.resize(size(a));
                for (size_t i=0; i<size(a); i++)
                    at(ret,i) = zeros_like(at(a,i));
            }
            return ret;
        }
    } // constexpr auto zeros_like(const T& a)
} // namespace nmtools
#endif // NMTOOLS_ARRAY_UTILITY_ZEROS_LIKE_HPP