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
#if NMTOOLS_HAS_VECTOR
        // vector of bool madness

        /**
         * @brief specialize vector of bool reference to deal with its odds
         * 
         * @param t 
         * @param u 
         * @return auto 
         */
        template <typename T>
        auto isequal(T t, std::vector<bool>::const_reference u)
        {
            // @todo fix check for integral type for T 
            return t == u;
        } // isequal

        template <typename U>
        auto isequal(std::vector<bool>::const_reference t, U u)
        {
            // @todo fix check for integral type for U
            return t == u;
        } // isequal

        // turns out it is also needed to provide both explicit bool, no matching call error otherwise
        constexpr inline auto isequal(bool t, bool u)
        {
            // @todo fix check for integral type for U
            return t == u;
        } // isequal

        // inline auto isequal(std::vector<bool>::const_reference t, std::vector<bool>::const_reference u)
        // {
        //     return t == u;
        // } // isequal

        // @note declaring these is okay for libc++ but causes redefinition error in libstdc++
        // inline auto isequal(std::vector<bool>::const_reference t, bool u)
        // {
        //     return t == u;
        // } // isequal

        // inline auto isequal(bool t, std::vector<bool>::const_reference u)
        // {
        //     return t == u;
        // } // isequal
#endif // NMTOOLS_HAS_VECTOR
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
            using tval_t = meta::get_element_type_t<T>;
            using uval_t = meta::get_element_type_t<U>;
            // @note add is_bit_reference here since std::vector<bool> access return std::_Bit_reference
            // and specializing is_integral is undefined behaviour
            static_assert(
                (
                    meta::compose_logical_or_v<T,meta::is_integer,meta::is_integral_constant>
                    || meta::compose_logical_or_v<U,meta::is_integer,meta::is_integral_constant>
                )
                ||
                (
                    meta::is_ndarray_v<T> && meta::is_ndarray_v<U>
                    && meta::compose_logical_or_v<tval_t,meta::is_integer>
                    && meta::compose_logical_or_v<uval_t,meta::is_integer>
                )
                ||
                ( is_none_v<T> && is_none_v<U> )
                , "unsupported isequal; only support integral element type"
            );
            if constexpr (is_none_v<T>)
                return true;
            else if constexpr (meta::is_integer_v<T>) {
                using value_type = T;
                return static_cast<value_type>(t) == static_cast<value_type>(u);
            }
            else if constexpr (meta::is_integral_constant_v<T>) {
                using value_type = typename T::value_type;
                return static_cast<value_type>(t) == static_cast<value_type>(u);
            }
            else {
                bool equal = true;
                // @todo: static assert whenever possible
                assert (dim(t)==dim(u)
                    // , "dimension mismatch for isequal"
                );
                auto t_shape = shape(t);
                auto u_shape = shape(u);
                auto t_indices = ndindex(t_shape);
                auto u_indices = ndindex(u_shape);
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