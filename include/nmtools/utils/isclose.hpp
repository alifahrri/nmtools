/**
 * @file isclose.hpp
 * @author Fahri Ali Rahman (ali.rahman.fahri@gmail.com)
 * @brief Contains definition of isclose
 * @version 0.1
 * @date 2020-11-17
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef NMTOOLS_UTILS_ISCLOSE_HPP
#define NMTOOLS_UTILS_ISCLOSE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/index.hpp"
#include "nmtools/array/utility/apply_at.hpp"
#include "nmtools/utils/isequal.hpp"

#include <type_traits>
#include <cassert>
#include <iterator>
#include <cmath>
#include <tuple>
#include <array>

namespace nmtools::utils
{
    using std::fabs;

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
        template <typename T, typename Eps>
        auto isclose(T t, std::vector<bool>::const_reference u, Eps)
        {
            // @todo fix either check for integral type for T 
            // or casting to some common type then compare with eps
            return t == u;
        } // isequal

        template <typename U, typename Eps>
        auto isclose(std::vector<bool>::const_reference t, U u, Eps)
        {
            // @todo fix either check for integral type for T 
            // or casting to some common type then compare with eps
            return t == u;
        } // isequal

        // template <typename Eps>
        // auto isclose(std::vector<bool>::const_reference t, std::vector<bool>::const_reference u, Eps)
        // {
        //     return t == u;
        // } // isequal

        // @note declaring these is okay for libc++ but causes redefinition error in libstdc++
        // template <typename Eps>
        // auto isclose(std::vector<bool>::const_reference t, bool u, Eps)
        // {
        //     return t == u;
        // } // isequal

        // template <typename Eps>
        // auto isclose(bool t, std::vector<bool>::const_reference u, Eps)
        // {
        //     return t == u;
        // } // isequal
#endif // NMTOOLS_HAS_VECTOR
        /**
         * @brief check if all value of t is near with the value of u, element-wise.
         * 
         * @tparam T lhs type
         * @tparam U rhs type
         * @tparam E epsilon type
         * @param t lhs
         * @param u rhs
         * @param eps epsilon
         * @return constexpr auto 
         */
        template <typename T, typename U, typename E=double>
        constexpr auto isclose(const T& t, const U& u, E eps=static_cast<E>(1e-6))
        {
            using ::nmtools::ndindex;
            static_assert(
                (meta::is_scalar_v<T>  && meta::is_scalar_v<U>) ||
                (meta::is_ndarray_v<T> && meta::is_ndarray_v<U>)
                , "unsupported isclose; only support arithmetic element type or ndarray"
            );
            auto isclose_impl = [](auto lhs, auto rhs, auto eps) {
                return fabs(lhs-rhs) < eps;
            };
            if constexpr (meta::is_scalar_v<T>) {
                using common_t = std::common_type_t<T,U,E>;
                return fabs(static_cast<common_t>(t)-static_cast<common_t>(u))
                    < static_cast<common_t>(eps);
            }
            else {
                bool close = true;
                // @todo: static assert whenever possible
                assert (dim(t)==dim(u)
                    // , "dimension mismatch for isclose"
                );
                auto t_shape = shape(t);
                auto u_shape = shape(u);
                assert (::nmtools::utils::isequal(t_shape,u_shape)
                    // , "shape mismatch for isclose"
                );
                auto t_indices = ndindex(t_shape);
                auto u_indices = ndindex(u_shape);
                // @todo: static assert whenever possible
                assert (t_indices.size()==u_indices.size()
                    // , "size mismatch for isclose"
                );
                for (size_t i = 0; i<t_indices.size(); i++)
                    // dont recurse, we already checked that t and u satify static assert here
                    close = close && isclose_impl(apply_at(t, t_indices[i]), apply_at(u, u_indices[i]), eps);
                return close;
            }
        } // isclose
    } // namespace detail

    /**
     * @brief check if all value of t is near with the value of u, element-wise.
     * 
     * @tparam T lhs type
     * @tparam U rhs type
     * @tparam E epsilon type
     * @param t lhs
     * @param u rhs
     * @param eps epsilon
     * @return constexpr auto 
     */
    template <typename T, typename U, typename E=double>
    constexpr auto isclose(const T& t, const U& u, E eps=static_cast<E>(1e-6))
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
                , "unsupported isclose, mismatched size for packed type"
            );
            auto equal = true; // conjuction identity
            meta::template_for<nt>([&](auto index){
                constexpr auto i = decltype(index)::value;
                const auto& t_ = std::get<i>(t);
                const auto& u_ = std::get<i>(u);
                equal = equal && isclose(t_,u_,eps);
            });
            return equal;
        }
        else return detail::isclose(t,u,eps);
    } // islcose
} // namespace nmtools::utils

#endif // NMTOOLS_UTILS_ISCLOSE_HPP