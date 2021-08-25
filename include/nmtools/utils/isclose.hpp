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
#include "nmtools/assert.hpp"
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
            // treat T & U as value
            constexpr auto t1 = meta::as_value<T>{};
            constexpr auto t2 = meta::as_value<U>{};

            // check if T1 and T2 is both scalar or both ndarray
            constexpr auto constrained = [](auto T1, auto T2){
                // expect T1 and T2 is as_value
                using t1 = meta::type_t<decltype(T1)>;
                using t2 = meta::type_t<decltype(T2)>;
                // allow scalar, ndarray, or None
                return (meta::is_num_v<t1>  && meta::is_num_v<t2>)
                    || (meta::is_ndarray_v<t1> && meta::is_ndarray_v<t2>)
                    || (is_none_v<t1> && is_none_v<t2>);
            };

            // given either type, check if the type is constrained
            constexpr auto constrained_either = [constrained](auto T1, auto T2){
                using t1 = meta::type_t<decltype(T1)>;
                using t2 = meta::type_t<decltype(T2)>;
                auto t1_lhs = meta::as_value<meta::get_either_left_t<t1>>{};
                auto t2_lhs = meta::as_value<meta::get_either_left_t<t2>>{};
                auto t1_rhs = meta::as_value<meta::get_either_right_t<t1>>{};
                auto t2_rhs = meta::as_value<meta::get_either_right_t<t2>>{};
                if constexpr (meta::is_either_v<t1> && meta::is_either_v<t2>)
                    return (constrained(t1_lhs,t2_lhs) || constrained(t1_rhs,t2_rhs));
                else if constexpr (meta::is_either_v<t1>)
                    return constrained(t1_lhs,T2) || constrained(t1_rhs,T2);
                else if constexpr (meta::is_either_v<t2>)
                    return constrained(T1,t2_lhs) || constrained(T1,t2_rhs);
                else return false;
            };

            // given maybe type, check if the type is constrained
            constexpr auto constrained_maybe = [constrained](auto T1, auto T2){
                using t1 = meta::type_t<meta::remove_cvref_t<decltype(T1)>>;
                using t2 = meta::type_t<meta::remove_cvref_t<decltype(T2)>>;
                auto v1  = meta::as_value<meta::get_maybe_type_t<t1>>{};
                auto v2  = meta::as_value<meta::get_maybe_type_t<t2>>{};
                if constexpr (meta::is_maybe_v<t1> && meta::is_maybe_v<t2>)
                    return constrained(v1,v2);
                else if constexpr (meta::is_maybe_v<t1>)
                    return constrained(v1,T2);
                else if constexpr (meta::is_maybe_v<t2>)
                    return constrained(T1,v2);
                else return false;
            };

            // actually constraint
            static_assert(
                constrained(t1,t2) || constrained_either(t1,t2) || constrained_maybe(t1,t2)
                , "unsupported isclose; only support scalar type or ndarray"
            );
            auto isclose_impl = [](auto lhs, auto rhs, auto eps) {
                return fabs(lhs-rhs) < eps;
            };

            using std::get_if;

            if constexpr (is_none_v<T> && is_none_v<U>)
                return true;
            // both type is maybe type, when both is empty, this also return true
            else if constexpr (meta::is_maybe_v<T> && meta::is_maybe_v<U>) {
                // for maybe type,
                // assume casting to bool checks if the objects contains a value
                // which is supported by std::optional
                auto hast = static_cast<bool>(t);
                auto hasu = static_cast<bool>(u);
                auto same = hast == hasu;
                if (hast && hasu && same)
                    same = same && isclose(*t,*u,eps);
                return same;
            }
            // only lhs is maybe
            // return true if t is not empty and the value is equal to u
            else if constexpr (meta::is_maybe_v<T>) {
                auto has_value = static_cast<bool>(t);
                return (has_value ? isclose(*t,u,eps) : false);
            }
            // only rhs is maybe
            // return true if u is not empty and the value is equal to t
            else if constexpr (meta::is_maybe_v<U>) {
                auto has_value = static_cast<bool>(u);
                return (has_value ? isclose(t,*u,eps) : false);
            }
            // for either type only match for both lhs or rhs for corresponding type,
            // doesn't support matching lhs with rhs
            else if constexpr (meta::is_either_v<T> && meta::is_either_v<U>) {
                // get the left and right types for corresponding either type
                using tlhs_t = meta::get_either_left_t<T>;
                using trhs_t = meta::get_either_right_t<T>;
                using ulhs_t = meta::get_either_left_t<U>;
                using urhs_t = meta::get_either_right_t<U>;
                using std::tuple;
                auto close = false;
                // under the hood, recursively call isclose to properly handle view type
                if (auto [tptr, uptr] = tuple{get_if<tlhs_t>(&t), get_if<ulhs_t>(&u)}; tptr && uptr)
                    close = isclose(*tptr,*uptr,eps);
                else if (auto [tptr, uptr] = tuple{get_if<trhs_t>(&t),get_if<urhs_t>(&u)}; tptr && uptr)
                    close = isclose(*tptr,*uptr,eps);
                return close;
            }
            // only T is is either type
            // select left or right that has same concept with U
            else if constexpr (meta::is_either_v<T>) {
                using lhs_t = meta::get_either_left_t<T>;
                using rhs_t = meta::get_either_right_t<T>;
                auto lhs = meta::as_value<lhs_t>{};
                auto rhs = meta::as_value<rhs_t>{};
                auto tsame = detail::select_same(lhs, rhs, t2);
                using same_t = meta::type_t<decltype(tsame)>;

                auto close = false;
                if (auto ptr = get_if<same_t>(&t); ptr)
                    close = isclose(*ptr,u);
                return close;
            }
            // only U is either type
            // select left or right that has same concept with T
            else if constexpr (meta::is_either_v<U>) {
                using lhs_t = meta::get_either_left_t<U>;
                using rhs_t = meta::get_either_right_t<U>;
                auto lhs = meta::as_value<lhs_t>{};
                auto rhs = meta::as_value<rhs_t>{};
                auto tsame = detail::select_same(lhs, rhs, t1);
                using same_t = meta::type_t<decltype(tsame)>;

                auto close = false;
                if (auto ptr = get_if<same_t>(&u); ptr)
                    close = isequal(t,*ptr);
                return close;
            }
            else if constexpr (meta::is_num_v<T>) {
                // use get_element_type to allow view
                using t_type = meta::get_element_type_t<T>;
                using u_type = meta::get_element_type_t<U>;
                using common_t = std::common_type_t<t_type,u_type,E>;
                return fabs(static_cast<t_type>(t)-static_cast<u_type>(u))
                    < static_cast<common_t>(eps);
            }
            else {
                bool close = true;
                // @todo: static assert whenever possible
                auto t_dim = ::nmtools::dim(t);
                auto u_dim = ::nmtools::dim(u);
                nmtools_assert_throw( (t_dim==u_dim)
                    , "dimension mismatch for isclose"
                );
                auto t_shape = ::nmtools::shape(t);
                auto u_shape = ::nmtools::shape(u);
                nmtools_assert_throw( ::nmtools::utils::isequal(t_shape,u_shape)
                    , "shape mismatch for isclose"
                );
                auto t_indices = ndindex(t_shape);
                auto u_indices = ndindex(u_shape);
                auto t_size = t_indices.size();
                auto u_size = u_indices.size();
                // @todo: static assert whenever possible
                nmtools_assert_throw( (t_size==u_size)
                    , "size mismatch for isclose"
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