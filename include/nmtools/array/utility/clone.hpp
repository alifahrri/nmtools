#ifndef NMTOOLS_ARRAY_UTILITY_CLONE_HPP
#define NMTOOLS_ARRAY_UTILITY_CLONE_HPP

/* common tag for preconditions, e.g. size assertion */
#include "nmtools/utility/tag.hpp"

#include "nmtools/array/utility/at.hpp"         // at
#include "nmtools/array/utility/shape.hpp"      // vector_size, matrix_size
#include "nmtools/array/utility/zeros_like.hpp" // zeros_like

#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"
#include <type_traits>
#include <cmath>
#include <cassert>

namespace nmtools
{
    namespace detail
    {
        constexpr auto clone_impl(auto &ret, const auto& a, auto rows, auto cols){
            for (size_t i=0; i<rows; i++)
                for (size_t j=0; j<cols; j++)
                    at(ret,i,j) = at(a,i,j);
        } // clone_impl

        constexpr auto clone_impl(auto &ret, const auto& a, auto n){
            for (size_t i=0; i<n; i++)
                at(ret,i) = at(a,i);
        } // clone_impl
    } // namespace detail

    /**
     * @brief clone matrix/vector 
     * 
     * @tparam Array 
     * @param a matrix/vector/arithmetic
     * @return constexpr auto 
     */
    template <typename Array>
    constexpr auto clone(const Array& a)
    {
        /** TODO: proper constraints **/
        static_assert(
            traits::is_array1d_v<Array>
            || traits::is_array2d_v<Array>
            || std::is_arithmetic_v<Array>,
            "unsupported type for clone"
        );
        using detail::clone_impl;
        /* ret is aritmethic type (scalr), return as it is */
        if constexpr (std::is_arithmetic_v<Array>)
            return a;
        /* ret is conteiner, for each elements call zeros_like */
        else {
            auto ret = zeros_like(a);
            using return_t = traits::remove_cvref_t<decltype(ret)>;
            /* array2d implementation */
            if constexpr (traits::is_array2d_v<return_t>)
            {
                constexpr auto is_fixed_size = traits::is_fixed_size_matrix_v<return_t>;
                if constexpr (is_fixed_size) {
                    /* TODO: find-out if reading matrix_size as constexpr is beneficial */
                    constexpr auto shape = matrix_size(ret);
                    constexpr auto rows = std::get<0>(shape);
                    constexpr auto cols = std::get<1>(shape);
                    clone_impl(ret,a,rows,cols);
                }
                else {
                    auto [rows, cols] = matrix_size(ret);
                    clone_impl(ret,a,rows,cols);
                }
            }
            /* array1d implementation */
            else {
                constexpr auto is_fixed_size = traits::is_fixed_size_vector_v<return_t>;
                if constexpr (is_fixed_size) {
                    constexpr auto n = vector_size(ret);
                    clone_impl(ret,a,n);
                }
                else {
                    auto n = vector_size(ret);
                    clone_impl(ret,a,n);
                }
            }
            return ret;
        }
    } // constexpr auto clone(const Array& a)
} // namespace clone

#endif // NMTOOLS_ARRAY_UTILITY_CLONE_HPP