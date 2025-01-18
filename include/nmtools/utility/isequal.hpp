#ifndef NMTOOLS_UTILS_ISEQUAL_HPP
#define NMTOOLS_UTILS_ISEQUAL_HPP

#include "nmtools/meta.hpp"
#include "nmtools/assert.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/array/index/ndindex.hpp"
#include "nmtools/utility/at.hpp"
#include "nmtools/utility/isequal/isequal.hpp"
#include "nmtools/utility/unwrap.hpp"

namespace nmtools::utils
{
    namespace error
    {
        template <typename...>
        struct ISEQUAL_UNSUPPORTED : meta::detail::fail_t {};
    }

    namespace detail {
        // TODO: cleanup equality check for boolean type
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
#endif // NMTOOLS_HAS_VECTOR

        // given T1 and T2 from either type, select T1 or T2
        // which has same concept as U
        template <typename t1, typename t2, typename u_t>
        constexpr auto select_same([[maybe_unused]] meta::as_value<t1> T1, [[maybe_unused]] meta::as_value<t2> T2, meta::as_value<u_t>)
        {
            if constexpr (is_none_v<u_t> && is_none_v<t1>) {
                return T1;
            } else if constexpr (is_none_v<u_t> && is_none_v<t2>) {
                return T2;
            } else if constexpr (meta::is_num_v<u_t> && meta::is_num_v<t1>) {
                return T1;
            } else if constexpr (meta::is_num_v<u_t> && meta::is_num_v<t2>) {
                return T2;
            } else if constexpr (meta::is_ndarray_v<u_t> && meta::is_ndarray_v<t1>) {
                return T1;
            } else if constexpr (meta::is_ndarray_v<u_t> && meta::is_ndarray_v<t2>) {
                return T2;
            }
            // the following index array may be found when either type contains tuple
            // which is not considered ndarray, but is index array
            else if constexpr (meta::is_index_array_v<u_t> && meta::is_index_array_v<t1>) {
                return T1;
            } else if constexpr (meta::is_index_array_v<u_t> && meta::is_index_array_v<t2>) {
                return T2;
            } else {
                return meta::as_value_v<void>;
            }
        } // select_same

        // check if T1 & T2 has the same concept
        // but be strict on fixed-shape & dim without triggering compile-time error
        template <typename t1, typename t2>
        constexpr auto same_concept(meta::as_value<t1>, meta::as_value<t2>){
            constexpr auto same_ndarray = [](){
                // fixed index array must be handled specifically since some index array (tuple of int constant) is not ndarray
                if constexpr (meta::is_fixed_index_array_v<t1> && meta::is_fixed_index_array_v<t2>) {
                    return meta::len_v<t1> == meta::len_v<t2>;
                }
                // use constexpr to avoid instantiating isequal on fail type because t1/t2 is not fixed ndarray
                else if constexpr (meta::is_fixed_size_ndarray_v<t1> && meta::is_fixed_size_ndarray_v<t2>) {
                    // avoid call to isequal since we want to be permissive
                    // return isequal(meta::fixed_ndarray_shape_v<t1>, meta::fixed_ndarray_shape_v<t2>);
                    constexpr auto shape1 = meta::fixed_ndarray_shape_v<t1>;
                    constexpr auto shape2 = meta::fixed_ndarray_shape_v<t2>;
                    if constexpr (len(shape1)==len(shape2)) {
                        constexpr auto n = len(shape1);
                        return meta::template_reduce<n>([&](auto init, auto index){
                            return init && (at(shape1,index)==at(shape2,index));
                        }, true);
                    } else {
                        return false;
                    }
                } else if constexpr (meta::is_fixed_dim_ndarray_v<t1> && meta::is_fixed_dim_ndarray_v<t2>) {
                    return (meta::fixed_dim_v<t1> == meta::fixed_dim_v<t2>);
                } else {
                    return meta::is_ndarray_v<t1> && meta::is_ndarray_v<t2>;
                }
            }();
            return (meta::is_num_v<t1> && meta::is_num_v<t2>)
                || (is_none_v<t1> && is_none_v<t2>) || same_ndarray;
        };

        template <typename t1>
        constexpr auto constrained(meta::as_value<t1>)
        {
            using t1_t = meta::get_element_type_t<t1>;

            // allow none, integer, or ndarray
            // for ndarray, the element type must be integral
            auto is_none = is_none_v<t1>;
            auto is_integer         = (meta::is_integer_v<t1> || meta::is_integral_constant_v<t1>);
            auto is_num_or_array    = (meta::is_num_v<t1>) || (meta::is_ndarray_v<t1>);
            auto is_index_constant  =  meta::is_index_array_v<t1>;
            auto element_is_integer =  meta::is_integer_v<t1_t>;
            return (is_num_or_array && element_is_integer) || is_integer || is_index_constant || is_none || is_ellipsis_v<t1>;
        } // constrained(T1,T2)

        // check if T1 and T2 is both scalar or both ndarray
        template <typename t1, typename t2>
        constexpr auto constrained(meta::as_value<t1>, meta::as_value<t2>)
        {
            using t1_t = meta::get_element_type_t<t1>;
            using t2_t = meta::get_element_type_t<t2>;

            // allow none, integer, or ndarray
            // for ndarray, the element type must be integral
            auto is_none =
                is_none_v<t1>
                && is_none_v<t2>;
            auto is_ellipsis =
                is_ellipsis_v<t1>
                && is_ellipsis_v<t2>;
            auto is_integer =
                (meta::is_integer_v<t1> || meta::is_integral_constant_v<t1>)
                && (meta::is_integer_v<t2> || meta::is_integral_constant_v<t2>);
            auto is_num_or_array =
                (meta::is_num_v<t1> && meta::is_num_v<t2>)
                || (meta::is_ndarray_v<t1> && meta::is_ndarray_v<t2>);
            auto is_index_constant =
                meta::is_index_array_v<t1>
                && meta::is_index_array_v<t2>;
            auto element_is_integer =
                meta::is_integer_v<t1_t>
                && meta::is_integer_v<t2_t>;
            auto is_slice = 
                meta::is_slice_index_v<t1>
                && meta::is_slice_index_v<t2>;
            auto is_slice_array =
                meta::is_slice_index_array_v<t1>
                && meta::is_slice_index_array_v<t2>;
            auto is_attribute =
                meta::is_attribute_v<t1>
                && meta::is_attribute_v<t2>;
            return (is_num_or_array && element_is_integer)
                || is_integer 
                || is_index_constant 
                || is_none 
                || is_ellipsis 
                || is_slice 
                || is_slice_array
                || is_attribute
            ;
        } // constrained(T1,T2)

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
            using ::nmtools::index::ndindex;
            // treat T & U as value
            [[maybe_unused]] constexpr auto t1 = meta::as_value_v<T>;
            [[maybe_unused]] constexpr auto t2 = meta::as_value_v<U>;

            if constexpr (is_ellipsis_v<T> && is_ellipsis_v<U>) {
                return true;
            }
            else if constexpr (is_none_v<T> && is_none_v<U>) {
                return true;
            } // both type is maybe type, when both is empty, this also return true
            else if constexpr (meta::is_maybe_v<T> && meta::is_maybe_v<U>) {
                // for maybe type,
                // assume casting to bool checks if the objects contains a value
                // which is supported by optional
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
            // match left with left, or right with right, then recursively call isequal
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
                using tuple_lhs_t = nmtools_tuple<tlhs_ptr_t,ulhs_ptr_t>;
                using tuple_rhs_t = nmtools_tuple<trhs_ptr_t,urhs_ptr_t>;
                auto same = false;
                // under the hood, recursively call isequal to properly handle view type
                if (const auto [tptr, uptr] = tuple_lhs_t{get_if<tlhs_t>(&t), get_if<ulhs_t>(&u)}; tptr && uptr)
                    same = isequal(*tptr,*uptr);
                else if (const auto [tptr, uptr] = tuple_rhs_t{get_if<trhs_t>(&t),get_if<urhs_t>(&u)}; tptr && uptr)
                    same = isequal(*tptr,*uptr);
                return same;
            }
            // only T is is either type
            // select left or right that has same concept with U
            else if constexpr (meta::is_either_v<T>) {
                using lhs_t = meta::get_either_left_t<T>;
                using rhs_t = meta::get_either_right_t<T>;
                constexpr auto ref = meta::as_value_v<U>;

                auto equal = false;
                if (auto l_ptr = get_if<lhs_t>(&t); l_ptr) {
                    constexpr auto lhs = meta::as_value_v<meta::resolve_optype_t<unwrap_t,lhs_t>>;
                    // TODO: implement nested either
                    // avoid instantiation if not the same concept
                    if constexpr (same_concept(lhs,ref)) {
                        equal = detail::isequal(*l_ptr,u);
                    }
                } else {
                    constexpr auto rhs = meta::as_value_v<meta::resolve_optype_t<unwrap_t,rhs_t>>;
                    [[maybe_unused]] auto r_ptr = get_if<rhs_t>(&t);
                    // TODO: implement nested either
                    // avoid instantiation if not the same concept
                    if constexpr (same_concept(rhs,ref)) {
                        equal = detail::isequal(*r_ptr,u);
                    }
                }
                return equal;
                /*
                auto lhs = meta::as_value_v<lhs_t>;
                auto rhs = meta::as_value_v<rhs_t>;
                auto t_same = detail::select_same(lhs, rhs, t2);
                using same_t = meta::type_t<decltype(t_same)>;
                static_assert( !meta::is_void_v<same_t>
                    , "couldn't find matching left / right concept in either type"
                );

                auto same = false;
                if (auto ptr = get_if<same_t>(&t); ptr)
                    same = isequal(*ptr,u);
                return same;
                */
            }
            // only U is either type
            // select left or right that has same concept with T
            else if constexpr (meta::is_either_v<U>) {
                using lhs_t = meta::get_either_left_t<U>;
                using rhs_t = meta::get_either_right_t<U>;
                constexpr auto ref = meta::as_value_v<T>;

                auto equal = false;
                if (auto l_ptr = get_if<lhs_t>(&u)) {
                    constexpr auto lhs = meta::as_value_v<meta::resolve_optype_t<unwrap_t,lhs_t>>;
                    // TODO: implement nested either
                    // avoid instantiation if not the same concept
                    if constexpr (same_concept(lhs,ref)) {
                        equal = detail::isequal(t,*l_ptr);
                    }
                } else {
                    [[maybe_unused]] auto r_ptr = get_if<rhs_t>(&u);
                    constexpr auto rhs = meta::as_value_v<meta::resolve_optype_t<unwrap_t,rhs_t>>;
                    if constexpr (same_concept(rhs,ref)) {
                        equal = detail::isequal(t,*r_ptr);
                    }
                }
                return equal;

                /*
                auto lhs = meta::as_value_v<lhs_t>;
                auto rhs = meta::as_value_v<rhs_t>;
                auto tsame = detail::select_same(lhs, rhs, t1);
                using same_t = meta::type_t<decltype(tsame)>;

                auto same = false;
                if (auto ptr = get_if<same_t>(&u); ptr)
                    same = isequal(t,*ptr);
                return same;
                */
            }
            // assume both T and U is integer
            else if constexpr (meta::is_num_v<T> && meta::is_num_v<U>) {
                using value_type = meta::common_type_t<T,U>;
                return static_cast<value_type>(t) == static_cast<value_type>(u);
            }
            else if constexpr (meta::is_integral_constant_v<T> && meta::is_integer_v<U>) {
                using value_type = meta::common_type_t<typename T::value_type,U>;
                return static_cast<value_type>(t) == static_cast<value_type>(u);
            }
            // "specialize" on index array, avoid using ndindex
            else if constexpr (meta::is_index_array_v<T> && meta::is_index_array_v<U>) {
                bool equal = true;
                // TODO: static assert whenever possible
                // NOTE: use assert instead of exception, to support compile with -fno-exceptions
                nmtools_cassert ( (nm_size_t)len(t)==(nm_size_t)len(u)
                    , "mismatched dimension"
                );
                // prefer fixed size for indexing to allow constant index
                if constexpr (meta::is_fixed_index_array_v<T>) {
                    constexpr auto N = meta::fixed_index_array_size_v<T>;
                    using t_t = meta::get_element_or_common_type_t<T>;
                    using u_t = meta::get_element_or_common_type_t<U>;
                    using common_t = meta::promote_index_t<t_t,u_t>;
                    meta::template_for<N>([&](auto i){
                        equal = equal && ((common_t)at(t,i) == (common_t)at(u,i));
                    });
                    return equal;
                }
                else if constexpr (meta::is_fixed_index_array_v<U>) {
                    constexpr auto N = meta::fixed_index_array_size_v<U>;
                    using t_t = meta::get_element_or_common_type_t<T>;
                    using u_t = meta::get_element_or_common_type_t<U>;
                    meta::template_for<N>([&](auto i){
                        auto t_i = at(t,i);
                        auto u_i = at(u,i);
                        using common_t = meta::promote_index_t<t_t,u_t>;
                        equal = equal && (static_cast<common_t>(t_i) == static_cast<common_t>(u_i));
                    });
                    return equal;
                }
                else {
                    using t_t = meta::get_element_or_common_type_t<T>;
                    using u_t = meta::get_element_or_common_type_t<U>;
                    for (size_t i=0; i<len(t); i++) {
                        auto t_i = at(t,i);
                        auto u_i = at(u,i);
                        using idx_t = meta::promote_index_t<t_t,u_t>;
                        equal = equal && ((idx_t)t_i == (idx_t)u_i);
                    }
                    return equal;
                }
            }
            else if constexpr (meta::is_slice_index_array_v<T> && meta::is_slice_index_array_v<U>) {
                auto n_left  = nmtools::len(t);
                auto n_right = nmtools::len(u);
                auto equal = n_left == n_right;
                for (size_t i=0; i<nmtools::len(t) && equal; i++) {
                    equal = equal && isequal(at(t,i),at(u,i));
                }
                return equal;
            }
            else if constexpr (meta::is_slice_index_v<T> && meta::is_slice_index_v<U>) {
                return meta::is_same_v<T,U>;
            }
            else if constexpr (meta::is_attribute_v<T> && meta::is_attribute_v<U>) {
                return t == u;
            }
            else if constexpr (meta::is_ndarray_v<T> && meta::is_ndarray_v<U>) {
                bool equal = true;
                auto t_dim = ::nmtools::dim(t);
                auto u_dim = ::nmtools::dim(u);
                {
                    using common_t [[maybe_unused]] = meta::promote_index_t<decltype(t_dim),decltype(u_dim)>;
                    // TODO: static assert whenever possible
                    // NOTE: use assert instead of exception, to support compile with -fno-exceptions
                    // TODO: use maybe type
                    nmtools_cassert( ((common_t)t_dim == (common_t)u_dim)
                        , "dimension mismatch for isequal"
                    );
                }
                auto t_shape = ::nmtools::shape(t);
                auto u_shape = ::nmtools::shape(u);
                auto t_indices = ndindex(t_shape);
                auto u_indices = ndindex(u_shape);
                // TODO: static assert whenever possible
                auto t_size = t_indices.size();
                auto u_size = u_indices.size();
                {
                    using common_t [[maybe_unused]] = meta::promote_index_t<decltype(t_size),decltype(u_size)>;
                    nmtools_cassert( ((common_t)t_size == (common_t)u_size)
                        , "size mismatch for isequal"
                    );
                }
                using t_t = meta::get_element_or_common_type_t<T>;
                using u_t = meta::get_element_or_common_type_t<U>;
                using common_t = meta::promote_index_t<t_t,u_t>;
                for (size_t i=0; i<t_indices.size(); i++)
                    equal = equal && ((common_t)apply_at(t, t_indices[i]) == (common_t)apply_at(u, u_indices[i]));
                return equal;
            } else {
                return error::ISEQUAL_UNSUPPORTED<T,U>{};
            }
        } // isequal
    } // namespace detail

    template <typename lhs_t, typename rhs_t, typename>
    struct isequal_t
    {
        constexpr auto operator()(const lhs_t& lhs, const rhs_t& rhs) const
        {
            return detail::isequal(lhs,rhs);
        }
    };

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
        // TODO: remove tuple_size metafunctions
        // check if tuple_size for T & U is available
        constexpr auto is_packed_T = meta::has_tuple_size_v<T>;
        constexpr auto is_packed_U = meta::has_tuple_size_v<U>;

        if constexpr (is_packed_T && is_packed_U) {
            // TODO: use better/consistent/appropriate metafunctions
            constexpr auto nt = meta::len_v<T>;
            constexpr auto nu = meta::len_v<U>;
            static_assert (nt==nu
                , "unsupported isequal, mismatched size for packed type"
            );
            auto equal = true; // conjuction identity
            meta::template_for<nt>([&](auto index){
                constexpr auto i = decltype(index)::value;
                const auto& t_ = nmtools::get<i>(t);
                const auto& u_ = nmtools::get<i>(u);
                equal = equal && isequal(t_,u_);
            });
            return equal;
        // comparison of maybe type with nothing type is allowed
        } else if constexpr (meta::is_maybe_v<T> && meta::is_nothing_v<U>) {
            return !static_cast<bool>(t);
        }
        else if constexpr (meta::is_nothing_v<T> && meta::is_maybe_v<U>) {
            return !static_cast<bool>(u);
        } else if constexpr (meta::is_maybe_v<T> && meta::is_maybe_v<U>) {
            using t_type = meta::get_maybe_type_t<T>;
            using u_type = meta::get_maybe_type_t<U>;
            using result_type = decltype(isequal(meta::declval<t_type>(),meta::declval<u_type>()));
            static_assert( !meta::is_fail_v<result_type>, "unsupported types for isequal");
            // Nothing and Nothing should be true here
            auto is_equal = static_cast<bool>(t) == static_cast<bool>(u);
            if (is_equal && static_cast<bool>(t)) {
                return isequal(*t,*u);
            } else {
                return is_equal;
            }
        } else if constexpr (meta::is_maybe_v<T>) {
            using t_type = meta::get_maybe_type_t<T>;
            using result_type = decltype(isequal(meta::declval<t_type>(),u));
            static_assert( !meta::is_fail_v<result_type>, "unsupported types for isequal");
            // can safely proceed
            if (static_cast<bool>(t)) {
                return isequal(*t,u);
            } else {
                return false;
            }
        } else if constexpr (meta::is_maybe_v<U>) {
            using u_type = meta::get_maybe_type_t<U>;
            using result_type = decltype(isequal(t,meta::declval<u_type>()));
            static_assert( !meta::is_fail_v<result_type>, "unsupported types for isequal");
            if (static_cast<bool>(u)) {
                return isequal(t,*u);
            } else {
                return false;
            }
        }
        else {
            auto isequal_impl = isequal_t<T,U>{};
            return isequal_impl(t,u);
        }
    } // isequal

    template <typename lhs_t, typename rhs_t>
    constexpr auto isequal(dtype_t<lhs_t>, dtype_t<rhs_t>)
    {
        return meta::is_same_v<lhs_t,rhs_t>;
    }

    template <typename lhs_t, typename rhs_t>
    struct isequal_t<dtype_t<lhs_t>,dtype_t<rhs_t>>
    {
        constexpr auto operator()(const dtype_t<lhs_t>&, const dtype_t<rhs_t>&) const
        {
            return meta::is_same_v<lhs_t,rhs_t>;
        }
    };
} // namespace nmtools::utils

#endif // NMTOOLS_UTILS_ISEQUAL_HPP