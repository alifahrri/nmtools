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
#include "nmtools/array/index/ndindex.hpp"
#include "nmtools/array/utility/apply_at.hpp"
#include "nmtools/utils/isequal.hpp"
#include "nmtools/math.hpp"
#include "nmtools/platform/math/constexpr.hpp"

#ifndef NMTOOLS_ISCLOSE_NAN_HANDLING
#define NMTOOLS_ISCLOSE_NAN_HANDLING 0
#endif // NMTOOLS_ISCLOSE_NAN_HANDLING

#ifndef NMTOOLS_ISCLOSE_INF_HANDLING
#define NMTOOLS_ISCLOSE_INF_HANDLING 0
#endif // NMTOOLS_ISCLOSE_INF_HANDLING

namespace nmtools::utils
{
    using nmtools::math::fabs;
    using nmtools::math::constexpr_fabs;

    namespace detail {
        // TODO: cleanup isclose for boolean
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
        constexpr auto isclose(const T& t, const U& u, [[maybe_unused]] E eps=static_cast<E>(1e-6))
        {
            using ::nmtools::index::ndindex;
            // treat T & U as value
            constexpr auto t1 = meta::as_value_v<T>;
            constexpr auto t2 = meta::as_value_v<U>;

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
                [[maybe_unused]] auto t1_lhs = meta::as_value_v<meta::get_either_left_t<t1>>;
                [[maybe_unused]] auto t2_lhs = meta::as_value_v<meta::get_either_left_t<t2>>;
                [[maybe_unused]] auto t1_rhs = meta::as_value_v<meta::get_either_right_t<t1>>;
                [[maybe_unused]] auto t2_rhs = meta::as_value_v<meta::get_either_right_t<t2>>;
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
                [[maybe_unused]] auto v1  = meta::as_value_v<meta::get_maybe_type_t<t1>>;
                [[maybe_unused]] auto v2  = meta::as_value_v<meta::get_maybe_type_t<t2>>;
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

            if constexpr (is_none_v<T> && is_none_v<U>)
                return true;
            // both type is maybe type, when both is empty, this also return true
            else if constexpr (meta::is_maybe_v<T> && meta::is_maybe_v<U>) {
                // for maybe type,
                // assume casting to bool checks if the objects contains a value
                // which is supported by std optional
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
                
                using nmtools::get_if;
                using tlhs_ptr_t  = decltype(get_if<tlhs_t>(&t));
                using ulhs_ptr_t  = decltype(get_if<ulhs_t>(&u));
                using trhs_ptr_t  = decltype(get_if<trhs_t>(&t));
                using urhs_ptr_t  = decltype(get_if<urhs_t>(&u));
                using tuple_lhs_t = meta::make_tuple_type_t<tlhs_ptr_t,ulhs_ptr_t>;
                using tuple_rhs_t = meta::make_tuple_type_t<trhs_ptr_t,urhs_ptr_t>;
                auto close = false;
                // under the hood, recursively call isclose to properly handle view type
                if (const auto [tptr, uptr] = tuple_lhs_t{get_if<tlhs_t>(&t), get_if<ulhs_t>(&u)}; tptr && uptr)
                    close = isclose(*tptr,*uptr,eps);
                else if (const auto [tptr, uptr] = tuple_rhs_t{get_if<trhs_t>(&t),get_if<urhs_t>(&u)}; tptr && uptr)
                    close = isclose(*tptr,*uptr,eps);
                return close;
            }
            // only T is is either type
            // select left or right that has same concept with U
            else if constexpr (meta::is_either_v<T>) {
                using lhs_t = meta::get_either_left_t<T>;
                using rhs_t = meta::get_either_right_t<T>;
                constexpr auto ref = meta::as_value_v<U>;

                auto close = false;
                if (auto l_ptr = get_if<lhs_t>(&t); l_ptr) {
                    constexpr auto lhs = meta::as_value_v<lhs_t>;
                    if constexpr (meta::is_either_v<lhs_t>) {
                        // maybe nested either
                        // should be okay to instantiate since *ptr is either
                        close = isclose(*l_ptr,u);
                    } else if constexpr (same_concept(lhs,ref)) {
                        // avoid instantiate if not the same concept
                        close = isclose(*l_ptr,u);
                    } else {
                        // maybe encountered in nested either
                        // ignore, maybe this path doesn't have matched concept
                    }
                } else {
                    constexpr auto rhs = meta::as_value_v<rhs_t>;
                    [[maybe_unused]] auto r_ptr = get_if<rhs_t>(&t);
                    if constexpr (meta::is_either_v<rhs_t>) {
                        // maybe nested either
                        // should be okay to instantiate since *ptr is either
                        close = isclose(*r_ptr,u);
                    } else if constexpr (same_concept(rhs,ref)) {
                        // avoid instantiate if not the same concept
                        close = isclose(*r_ptr,u);
                    } else {
                        // maybe encountered in nested either
                        // ignore, maybe this path doesn't have matched concept
                    }
                }
                return close;
            }
            // only U is either type
            // select left or right that has same concept with T
            else if constexpr (meta::is_either_v<U>) {
                using lhs_t = meta::get_either_left_t<U>;
                using rhs_t = meta::get_either_right_t<U>;
                constexpr auto ref = meta::as_value_v<T>;

                auto close = false;
                if (auto l_ptr = get_if<lhs_t>(&u); l_ptr) {
                    constexpr auto lhs = meta::as_value_v<lhs_t>;
                    if constexpr (same_concept(lhs,ref)) {
                        close = isclose(t,*l_ptr);
                    }
                } else /* if (auto r_ptr = get_if<rhs_t>(&u); r_ptr) */ {
                    [[maybe_unused]] auto r_ptr = get_if<rhs_t>(&u);
                    constexpr auto rhs = meta::as_value_v<rhs_t>;
                    if constexpr (same_concept(rhs,ref)) {
                        close = isclose(t,*r_ptr);
                    }
                }
                return close;
            }
            else if constexpr (meta::is_num_v<T>) {
                // use get_element_type to allow view
                using t_type = meta::get_element_type_t<T>;
                using u_type = meta::get_element_type_t<U>;
                using common_t = meta::common_type_t<t_type,u_type,E>;
                auto abs_diff = constexpr_fabs(static_cast<t_type>(t)-static_cast<u_type>(u));
                auto result = abs_diff < static_cast<common_t>(eps);
                #if NMTOOLS_ISCLOSE_NAN_HANDLING
                result = result || (math::isnan(t) && math::isnan(u));
                #endif
                #if NMTOOLS_ISCLOSE_INF_HANDLING
                result = result || (math::isinf(t) && math::isinf(u));
                #endif
                return result;
            }
            else {
                [[maybe_unused]]
                auto isclose_impl = [](auto lhs, auto rhs, auto eps) {
                    return constexpr_fabs(lhs-rhs) < eps;
                };
                bool close = true;
                // TODO: static assert whenever possible
                // NOTE: use assert instead of exception, to support compile with -fno-exceptions
                // TODO: use maybe type
                auto t_shape = ::nmtools::shape(t);
                auto u_shape = ::nmtools::shape(u);
                nmtools_cassert( ::nmtools::utils::isequal(t_shape,u_shape)
                    , "shape mismatch for isclose"
                );
                auto t_indices = ndindex(t_shape);
                auto u_indices = ndindex(u_shape);
                auto numel = t_indices.size();
                for (size_t i = 0; i<numel; i++) {
                    close = close && isclose(apply_at(t, t_indices[i]), apply_at(u, u_indices[i]), eps);
                }
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
        // TODO: remove tuple_size metafunctions
        // check if tuple_size for T & U is available
        constexpr auto is_packed_T = meta::has_tuple_size_v<T>;
        constexpr auto is_packed_U = meta::has_tuple_size_v<U>;

        if constexpr (is_packed_T && is_packed_U) {
            // TODO: use better/consistent/appropriate metafunctions
            constexpr auto nt = meta::len_v<T>;
            constexpr auto nu = meta::len_v<U>;
            static_assert (nt==nu
                , "unsupported isclose, mismatched size for packed type"
            );
            auto equal = true; // conjuction identity
            meta::template_for<nt>([&](auto index){
                constexpr auto i = decltype(index)::value;
                const auto& t_ = nmtools::get<i>(t);
                const auto& u_ = nmtools::get<i>(u);
                equal = equal && isclose(t_,u_,eps);
            });
            return equal;
        }
        else return detail::isclose(t,u,eps);
    } // isclose

    template <
        typename F, typename lhs_operands_t, typename lhs_attributes_t
        , typename G, typename rhs_operands_t, typename rhs_attributes_t>
    constexpr auto isequal(
        const functional::functor_t<F,lhs_operands_t,lhs_attributes_t>& lhs
        , const functional::functor_t<G,rhs_operands_t,rhs_attributes_t>& rhs
    ) {
        if constexpr ( !meta::is_same_v<F,G> || 
            !meta::is_same_v<lhs_operands_t,rhs_operands_t>
        ) {
            // TODO: also check the values of operands
            return false;
        } else if constexpr (
            !meta::is_same_v<lhs_attributes_t,meta::empty_attributes_t>
            && !meta::is_same_v<rhs_attributes_t,meta::empty_attributes_t>
        ) {
            constexpr auto M = meta::len_v<lhs_attributes_t>;
            constexpr auto N = meta::len_v<rhs_attributes_t>;
            if constexpr (M != N) {
                return false;
            } else {
                auto equal = true;
                meta::template_for<M>([&](auto index){
                    auto equal_attribute = [&](){
                        auto lhs_attribute = at(lhs.attributes,index);
                        auto rhs_attribute = at(rhs.attributes,index);
                        if constexpr (meta::is_floating_point_v<decltype(lhs_attribute)>
                            && meta::is_floating_point_v<decltype(rhs_attribute)>)
                        {
                            return isclose(lhs_attribute,rhs_attribute);
                        } else {
                            return isequal(lhs_attribute,rhs_attribute);
                        }
                    }();
                    equal = equal && equal_attribute;
                });
                return equal;
            }
        } else if constexpr ( meta::is_same_v<F,G>
            && meta::is_same_v<lhs_attributes_t,meta::empty_attributes_t>
            && meta::is_same_v<rhs_attributes_t,meta::empty_attributes_t>
        ) {
            return true;
        } else {
            return false;
        }
    }

    template <
        template<typename...>typename lhs_tuple, typename...lhs_functors_t, typename lhs_operands_t,
        template<typename...>typename rhs_tuple, typename...rhs_functors_t, typename rhs_operands_t
    >
    constexpr auto isequal(
        const functional::functor_composition_t<lhs_tuple<lhs_functors_t...>,lhs_operands_t>& lhs
        , const functional::functor_composition_t<rhs_tuple<rhs_functors_t...>,rhs_operands_t>& rhs
    ) {
        constexpr auto N_LHS = meta::len_v<decltype(lhs.functors)>;
        constexpr auto N_RHS = meta::len_v<decltype(rhs.functors)>;

        auto equal = N_LHS == N_RHS;
        constexpr auto N = (N_LHS < N_RHS) ? N_LHS : N_RHS;
        meta::template_for<N>([&](auto index){
            equal = equal && isequal(at(lhs.functors,index),at(rhs.functors,index));
        });
        return equal;
    }
} // namespace nmtools::utils

#endif // NMTOOLS_UTILS_ISCLOSE_HPP