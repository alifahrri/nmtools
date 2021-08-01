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

        // given T1 and T2 from either type, select T1 or T2
        // which has same concept as U
        template <typename t1, typename t2, typename u_t>
        constexpr auto select_same(meta::as_value<t1> T1, meta::as_value<t2> T2, meta::as_value<u_t> u)
        {
            if constexpr (is_none_v<u_t> && is_none_v<t1>)
                return T1;
            else if constexpr (is_none_v<u_t> && is_none_v<t2>)
                return T2;
            else if constexpr (meta::is_num_v<u_t> && meta::is_num_v<t1>)
                return T1;
            else if constexpr (meta::is_num_v<u_t> && meta::is_num_v<t2>)
                return T2;
            else if constexpr (meta::is_ndarray_v<u_t> && meta::is_ndarray_v<t1>)
                return T1;
            else if constexpr (meta::is_ndarray_v<u_t> && meta::is_ndarray_v<t2>)
                return T2;
            else return meta::as_value<void>{};
        }

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
            // treat T & U as value
            constexpr auto t1 = meta::as_value<T>{};
            constexpr auto t2 = meta::as_value<U>{};

            // check if T1 and T2 is both scalar or both ndarray
            constexpr auto constrained = [](auto T1, auto T2){
                // expect T1 and T2 is as_value
                using t1 = meta::type_t<meta::remove_cvref_t<decltype(T1)>>;
                using t2 = meta::type_t<meta::remove_cvref_t<decltype(T2)>>;
                using t1_t = meta::get_element_type_t<t1>;
                using t2_t = meta::get_element_type_t<t2>;

                // allow none, integer, or ndarray
                // for ndarray, the element type must be integral
                auto is_none = is_none_v<t1> && is_none_v<t1>;
                auto is_integer = (meta::is_integer_v<t1> || meta::is_integral_constant_v<t1>)
                    && (meta::is_integer_v<t2> || meta::is_integral_constant_v<t2>);
                auto is_num_or_array =  (meta::is_num_v<t1> && meta::is_num_v<t2>)
                    || (meta::is_ndarray_v<t1> && meta::is_ndarray_v<t2>);
                auto is_index_constant = meta::is_index_array_v<t1> && meta::is_index_array_v<t2>;
                auto element_is_integer = meta::is_integer_v<t1_t> && meta::is_integer_v<t2_t>;
                return (is_num_or_array && element_is_integer) || is_integer || is_index_constant || is_none;
            };

            // given either type, check if the type is constrained
            constexpr auto constrained_either = [constrained](auto T1, auto T2){
                using t1 = meta::type_t<meta::remove_cvref_t<decltype(T1)>>;
                using t2 = meta::type_t<meta::remove_cvref_t<decltype(T2)>>;
                auto t1_lhs = meta::as_value<meta::get_either_left_t<t1>>{};
                auto t2_lhs = meta::as_value<meta::get_either_left_t<t2>>{};
                auto t1_rhs = meta::as_value<meta::get_either_right_t<t1>>{};
                auto t2_rhs = meta::as_value<meta::get_either_right_t<t2>>{};
                if constexpr (meta::is_either_v<t1> && meta::is_either_v<t2>)
                    return constrained(t1_lhs,t2_lhs) || constrained(t1_rhs,t2_rhs);
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

            // actually constraint the types
            static_assert(
                constrained(t1,t2) || constrained_either(t1,t2) || constrained_maybe(t1,t2)
                , "unsupported isclose; only support scalar type or ndarray"
            );

            // assume either type is variant
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
                    same = same && isequal(*t,*u);
                return same;
            }
            // only lhs is maybe
            // return true if t is not empty and the value is equal to u
            else if constexpr (meta::is_maybe_v<T>) {
                auto has_value = static_cast<bool>(t);
                return (has_value ? isequal(*t,u) : false);
            }
            // only rhs is maybe
            // return true if u is not empty and the value is equal to t
            else if constexpr (meta::is_maybe_v<U>) {
                auto has_value = static_cast<bool>(u);
                return (has_value ? isequal(t,*u) : false);
            }
            // both are either type
            // match left with left, or right with right, then recursively call isclose
            else if constexpr (meta::is_either_v<T> && meta::is_either_v<U>) {
                // get the left and right types for corresponding either type
                using tlhs_t = meta::get_either_left_t<T>;
                using trhs_t = meta::get_either_right_t<T>;
                using ulhs_t = meta::get_either_left_t<U>;
                using urhs_t = meta::get_either_right_t<U>;
                using std::tuple;
                auto same = false;
                // under the hood, recursively call isclose to properly handle view type
                if (auto [tptr, uptr] = tuple{get_if<tlhs_t>(&t), get_if<ulhs_t>(&u)}; tptr && uptr)
                    same = isequal(*tptr,*uptr);
                else if (auto [tptr, uptr] = tuple{get_if<trhs_t>(&t),get_if<urhs_t>(&u)}; tptr && uptr)
                    same = isequal(*tptr,*uptr);
                return same;
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

                auto same = false;
                if (auto ptr = get_if<same_t>(&t); ptr)
                    same = isequal(*ptr,u);
                return same;
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

                auto same = false;
                if (auto ptr = get_if<same_t>(&u); ptr)
                    same = isequal(t,*ptr);
                return same;
            }
            // assume both T and U is integer
            else if constexpr (meta::is_integer_v<T>) {
                using value_type = T;
                return static_cast<value_type>(t) == static_cast<value_type>(u);
            }
            // assume both T and U is integral constant
            else if constexpr (meta::is_integral_constant_v<T>) {
                using value_type = typename T::value_type;
                return static_cast<value_type>(t) == static_cast<value_type>(u);
            }
            // "specialize" on index array, avoid using ndindex
            else if constexpr (meta::is_index_array_v<T> && meta::is_index_array_v<U>) {
                bool equal = true;
                // @todo: static assert whenever possible
                assert ( len(t)==len(u) );
                // prefer fixed size for indexing to allow constant index
                if constexpr (meta::is_fixed_index_array_v<T>) {
                    constexpr auto N = meta::fixed_index_array_size_v<T>;
                    meta::template_for<N>([&](auto i){
                        equal = equal && (at(t,i) == at(u,i));
                    });
                    return equal;
                }
                else if constexpr (meta::is_fixed_index_array_v<U>) {
                    constexpr auto N = meta::fixed_index_array_size_v<U>;
                    meta::template_for<N>([&](auto i){
                        equal = equal && (at(t,i) == at(u,i));
                    });
                    return equal;
                }
                else {
                    for (size_t i=0; i<len(t); i++)
                        equal = equal && (at(t,i) == at(u,i));
                    return equal;
                }
            }
            // assume both T and U is ndarray
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