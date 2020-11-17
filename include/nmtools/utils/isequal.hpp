/**
 * @file isequal.hpp
 * @author Fahri Ali Rahman (ali.rahman.fahri@gmail.com)
 * @brief Contains definition of isequal
 * @version 0.1
 * @date 2020-11-17
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef NMTOOLS_UTILS_ISEQUAL_HPP
#define NMTOOLS_UTILS_ISEQUAL_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/index.hpp"
#include "nmtools/array/utility/apply_at.hpp"

#include <type_traits>
#include <cassert>
#include <iterator>
#include <cmath>
#include <tuple>
#include <array>

namespace nmtools::utils
{
    namespace detail {
        /**
         * @brief check if all elements of t is is equals to corresponding elements of u, element-wise.
         * 
         * Only supports integral element type.
         *
         * @tparam T lhs type
         * @tparam U rhs type
         * @param t lhs
         * @param u rhs
         * @return constexpr auto 
         */
        template <typename T, typename U>
        constexpr auto isequal(const T& t, const U& u)
        {
            static_assert(
                (std::is_integral_v<T> && std::is_integral_v<U>) ||
                (meta::is_ndarray_v<T> && meta::is_ndarray_v<U>)
                , "unsupported isequal; only support integral element type"
            );
            if constexpr (std::is_integral_v<T>)
                return t == u;
            else {
                constexpr auto t_is_int = std::is_integral_v<meta::get_element_type_t<T>>;
                constexpr auto u_is_int = std::is_integral_v<meta::get_element_type_t<U>>;
                static_assert (t_is_int && u_is_int
                    , "unsupported isequal; only support integral element type"
                );
                bool equal = true;
                // @todo: static assert whenever possible
                assert (dim(t)==dim(u)
                    // , "dimension mismatch for isequal"
                );
                auto t_shape = shape(t);
                auto u_shape = shape(u);
                auto t_indices = indices_pack(t_shape);
                auto u_indices = indices_pack(u_shape);
                // @todo: static assert whenever possible
                assert (t_indices.size()==u_indices.size()
                    // , "size mismatch for isequal"
                );
                for (size_t i=0; i<t_indices.size(); i++)
                    equal = equal && (apply_at(t, t_indices[i]) == apply_at(u, u_indices[i]));
                return equal;
            }
        } // isequal
    } // namespace detail

    /**
     * @brief check if all elements of t is is equals to corresponding elements of u, element-wise.
     * 
     * Only supports integral element type.
     *
     * @tparam T lhs type
     * @tparam U rhs type
     * @param t lhs
     * @param u rhs
     * @return constexpr auto 
     */
    template <typename T, typename U>
    constexpr auto isequal(const T& t, const U& u)
    {
        // check if tuple_size for T & U is available
        constexpr auto is_packed_T = meta::has_tuple_size_v<T>;
        constexpr auto is_packed_U = meta::has_tuple_size_v<U>;
        // check if T & U is simply array
        constexpr auto is_array_T = meta::is_ndarray_v<T>;
        constexpr auto is_array_U = meta::is_ndarray_v<U>;

        if constexpr (is_packed_T && is_packed_U) {
            constexpr auto nt = std::tuple_size_v<T>;
            constexpr auto nu = std::tuple_size_v<U>;
            static_assert (nt==nu
                , "unsupported isequal, mismatched size for packed type"
            );
            auto equal = true; // conjuction identity
            meta::template_for<nt>([&](auto index){
                constexpr auto i = decltype(index)::value;
                const auto& t_ = std::get<i>(t);
                const auto& u_ = std::get<i>(u);
                equal = equal && isequal(t_,u_);
            });
            return equal;
        }
        else return detail::isequal(t,u);
    }
} // namespace nmtools::utils

#endif // NMTOOLS_UTILS_ISEQUAL_HPP