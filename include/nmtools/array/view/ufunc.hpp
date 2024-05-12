#ifndef NMTOOLS_ARRAY_VIEW_UFUNC_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNC_HPP

#include "nmtools/array/view/ufunc/ufunc.hpp"
#include "nmtools/array/view/ufunc/reduce.hpp"
#include "nmtools/array/view/ufunc/accumulate.hpp"
#include "nmtools/array/view/ufunc/outer.hpp"

namespace nmtools::view
{
    // provide user defined CTAD with tuple of arrays as args
    // here, expect the second arg (tuple{arrays...}) to be view (from broadcasting)
    // NOTE: somehow doesn't work, deduce using _ufunc for now
    template <template<typename...>typename tuple, typename op_t, typename...arrays_t>
    ufunc_t(op_t, tuple<arrays_t...>) -> ufunc_t<op_t,arrays_t...>;

    // TODO: remove
    #if 1
    template <typename op_t, template<typename...> typename tuple, typename...arrays_t, size_t...Is>
    constexpr auto _ufunc(op_t op, const tuple<arrays_t...>& func, meta::index_sequence<Is...>)
    {
        // help deduction
        return decorator_t<ufunc_t,op_t,arrays_t...>({{op, nmtools::get<Is>(func)...}});
    }; // _ufunc

    template <typename op_t, template<typename...> typename tuple, typename...arrays_t>
    constexpr auto _ufunc(op_t op, const tuple<arrays_t...>& func)
    {
        return _ufunc(op,func,meta::make_index_sequence<sizeof...(arrays_t)>{});
    }; // _ufunc

    /**
     * @brief Creates ufunc_t object, given op and arrays.
     * 
     * @tparam op_t 
     * @tparam array_t 
     * @tparam arrays_t 
     * @param op 
     * @param array 
     * @param arrays 
     * @return constexpr auto 
     */
    template <typename op_t, typename array_t, typename...arrays_t>
    constexpr auto ufunc(op_t op, const array_t& array, const arrays_t&...arrays)
    {
        // TODO: check either for arrays...
        if constexpr (meta::is_maybe_v<array_t>) {
            // TODO: also check for arrays_t...
            using result_type = decltype(ufunc(op,*array,arrays...));
            using return_type = nmtools_maybe<result_type>;
            if (static_cast<bool>(array)) {
                auto result = ufunc(op,*array,arrays...);
                return return_type{result};
            } else {
                return return_type{meta::Nothing};
            }
        } else if constexpr (meta::is_either_v<array_t>) {
            // handle if array is either type,
            // such case can happen for reduce ufunc with runtime keepdims.
            // TODO: also handle any either type in arrays...
            // TODO: generalize get_if, declval
            using lhs_t = meta::get_either_left_t<array_t>;
            using rhs_t = meta::get_either_right_t<array_t>;
            using lhs_ufunc_t = decltype(ufunc(op,meta::declval<lhs_t>(),arrays...));
            using rhs_ufunc_t = decltype(ufunc(op,meta::declval<rhs_t>(),arrays...));
            using result_t = meta::replace_either_t<array_t,lhs_ufunc_t,rhs_ufunc_t>;
            if (auto lptr = nmtools::get_if<lhs_t>(&array)) {
                static_assert( meta::is_pointer_v<decltype(lptr)>
                    , "nmtools internal error" );
                static_assert( meta::is_same_v<meta::remove_cvref_t<decltype(*lptr)>,lhs_t>
                    , "nmtools internal error" );
                return result_t{ufunc(op,*lptr,arrays...)};
            } else /* if (auto rptr = get_if<rhs_t>(&array)) */ {
                // must be true,
                // use else to avoid warnings
                auto rptr = nmtools::get_if<rhs_t>(&array);
                static_assert( meta::is_pointer_v<decltype(rptr)>
                    , "nmtools internal error" );
                static_assert( meta::is_same_v<meta::remove_cvref_t<decltype(*rptr)>,rhs_t>
                    , "nmtools internal error" );
                return result_t{ufunc(op,*rptr,arrays...)};
            }
        } else if constexpr (meta::is_num_v<array_t> && (meta::is_num_v<arrays_t> && ...)) {
            // NOTE: quick workaround to compile
            // TODO: revisit this cases
            #ifndef NMTOOLS_NO_BASE_ACCESS
            // all arrays are numeric, use scalar_ufunc instead
            using view_t = decorator_t<scalar_ufunc_t,op_t,array_t,arrays_t...>;
            return view_t{{op,array,arrays...}};
            #else
            using result_t = decorator_t<scalar_ufunc_t,op_t,array_t,arrays_t...>;
            using view_t = scalar_ufunc_t<op_t,array_t,arrays_t...>;
            return result_t{view_t{op,array,arrays...}};
            #endif // NMTOOLS_NO_BASE_ACCESS
        } else if constexpr (sizeof...(arrays) > 0) {
            // enable broadcasting if operands >= 2
            // here, broadcasted array should be view
            auto b_arrays = broadcast_arrays(array, arrays...);
            using b_arrays_t = decltype(b_arrays);
            constexpr auto n_args = meta::len_v<b_arrays_t>;
            static_assert ( n_args == (sizeof...(arrays)+1)
                , "nmtools internal error" );
            return _ufunc(op, b_arrays);
        } else {
            // NOTE: quick workaround to compile
            // TODO: revisit this cases
            #ifndef NMTOOLS_NO_BASE_ACCESS
            // single argument ufunc, skip broadcasting
            using view_t = decorator_t<ufunc_t,op_t,meta::remove_address_space_t<array_t>>;
            return view_t{{op,{array}}};
            #else
            using result_t = decorator_t<ufunc_t,op_t,meta::remove_address_space_t<array_t>>;
            using view_t = ufunc_t<op_t,meta::remove_address_space_t<array_t>>;
            return result_t{view_t{op,{array}}};
            #endif // NMTOOLS_NO_BASE_ACCESS
        }
    } // ufunc
    #endif

    template <typename op_t, typename array_t, typename...op_args_t>
    constexpr auto unary_ufunc(op_t op, const array_t& array, op_args_t...op_args)
    {
        if constexpr (meta::is_maybe_v<array_t>) {
            using result_type = decltype(unary_ufunc(op,*array,op_args...));
            using return_type = nmtools_maybe<result_type>;
            return (static_cast<bool>(array)
                ? return_type{unary_ufunc(op,*array,op_args...)}
                : return_type{meta::Nothing}
            );
        } else if constexpr (meta::is_either_v<array_t>) {
            using lhs_t = meta::get_either_left_t<array_t>;
            using rhs_t = meta::get_either_right_t<array_t>;
            using lhs_ufunc_t = decltype(unary_ufunc(op,meta::declval<lhs_t>(),op_args...));
            using rhs_ufunc_t = decltype(unary_ufunc(op,meta::declval<rhs_t>(),op_args...));
            using return_t = meta::replace_either_t<array_t,lhs_ufunc_t,rhs_ufunc_t>;
            if (auto lptr = nmtools::get_if<lhs_t>(&array)) {
                return return_t{unary_ufunc(op,*lptr,op_args...)};
            } else /* if (auto rptr = get_if<rhs_t>(&array)) */ {
                auto rptr = nmtools::get_if<rhs_t>(&array);
                return return_t{unary_ufunc(op,*rptr,op_args...)};
            }
        } else if constexpr (sizeof...(op_args)) {
            return unary_ufunc(op[nmtools_tuple{op_args...}],array);
        } else if constexpr (meta::is_num_v<array_t>) {
            using view_t = decorator_t<scalar_ufunc_t,op_t,array_t>;
            return view_t{{op,array}};
        } else {
            using result_t = decorator_t<ufunc_t,op_t,array_t>;
            return result_t{{op,array}};
        }
    } // unary_ufunc

    template <typename op_t, typename lhs_t, typename rhs_t>
    constexpr auto binary_ufunc(op_t op, const lhs_t& lhs, const rhs_t& rhs)
    {
        if constexpr (meta::is_maybe_v<lhs_t>) {
            using result_type = decltype(binary_ufunc(op,*lhs,rhs));
            using return_type = meta::conditional_t<meta::is_maybe_v<result_type>
                , result_type, nmtools_maybe<result_type>
            >;
            auto get_result = [&](){
                auto result = binary_ufunc(op,*lhs,rhs);
                if constexpr (meta::is_maybe_v<result_type>) {
                    return (result
                        ? return_type{*result}
                        : return_type{meta::Nothing}
                    );
                } else {
                    return return_type{result};
                }
            };
            return (static_cast<bool>(lhs)
                ? get_result()
                : return_type{meta::Nothing}
            );
        } else if constexpr (meta::is_maybe_v<rhs_t>) {
            using result_type = decltype(binary_ufunc(op,lhs,*rhs));
            using return_type = nmtools_maybe<result_type>;
            return (static_cast<bool>(rhs)
                ? return_type{binary_ufunc(op,lhs,*rhs)}
                : return_type{meta::Nothing}
            );
        } else if constexpr (meta::is_either_v<lhs_t>) {
            using l_lhs_t = meta::get_either_left_t<lhs_t>;
            using l_rhs_t = meta::get_either_right_t<lhs_t>;
            using lhs_ufunc_t = decltype(binary_ufunc(op,meta::declval<lhs_t>(),rhs));
            using rhs_ufunc_t = decltype(binary_ufunc(op,meta::declval<rhs_t>(),rhs));
            using result_t = meta::replace_either_t<lhs_t,lhs_ufunc_t,rhs_ufunc_t>;
            if (auto lptr = nmtools::get_if<l_lhs_t>(&lhs)) {
                return result_t{binary_ufunc(op,*lptr,rhs)};
            } else {
                auto rptr = nmtools::get_if<l_rhs_t>(&lhs);
                return result_t{binary_ufunc(op,*rptr,rhs)};
            }
        } else if constexpr (meta::is_either_v<rhs_t>) {
            using r_lhs_t = meta::get_either_left_t<rhs_t>;
            using r_rhs_t = meta::get_either_right_t<rhs_t>;
            using lhs_ufunc_t = decltype(binary_ufunc(op,lhs,meta::declval<r_lhs_t>()));
            using rhs_ufunc_t = decltype(binary_ufunc(op,lhs,meta::declval<r_rhs_t>()));
            using result_t = meta::replace_either_t<rhs_t,lhs_ufunc_t,rhs_ufunc_t>;
            if (auto lptr = nmtools::get_if<r_lhs_t>(&rhs)) {
                return result_t{binary_ufunc(op,lhs,*lptr)};
            } else {
                auto rptr = nmtools::get_if<r_rhs_t>(&rhs);
                return result_t{binary_ufunc(op,lhs,*rptr)};
            }
        } else if constexpr (meta::is_num_v<lhs_t> && meta::is_num_v<rhs_t>) {
            // all rhs are numeric, use scalar_ufunc instead
            using view_t = decorator_t<scalar_ufunc_t,op_t,lhs_t,rhs_t>;
            return view_t{{op,lhs,rhs}};
        } else {
            using result_t = decorator_t<ufunc_t,op_t,lhs_t,rhs_t>;
            return result_t{{op,lhs,rhs}};
        }
    } // binary_ufunc

    template <typename op_t, template<typename...>typename tuple, typename lhs_t, typename rhs_t>
    constexpr auto binary_ufunc(op_t op, const tuple<lhs_t,rhs_t>& arrays)
    {
        return binary_ufunc(op,nmtools::get<0>(arrays),nmtools::get<1>(arrays));
    } // binary_ufunc

    // TODO: handle optional lhs, rhs
    /**
     * @brief Creates ufunc_t object, given op and arrays.
     * 
     * @tparam op_t 
     * @tparam lhs_t 
     * @tparam rhs_t 
     * @param op 
     * @param lhs 
     * @param rhs 
     * @return constexpr auto 
     */
    template <typename op_t, typename lhs_t, typename rhs_t>
    constexpr auto broadcast_binary_ufunc(op_t op, const lhs_t& lhs, const rhs_t& rhs)
    {
        if constexpr (meta::is_maybe_v<lhs_t>) {
            using result_type = decltype(broadcast_binary_ufunc(op,*lhs,rhs));
            using return_type = meta::conditional_t<meta::is_maybe_v<result_type>
                , result_type, nmtools_maybe<result_type>
            >;
            auto get_result = [&](){
                auto result = broadcast_binary_ufunc(op,*lhs,rhs);
                if constexpr (meta::is_maybe_v<result_type>) {
                    return (result
                        ? return_type{*result}
                        : return_type{meta::Nothing}
                    );
                } else {
                    return return_type{result};
                }
            };
            return (static_cast<bool>(lhs)
                ? get_result()
                : return_type{meta::Nothing}
            );
        } else if constexpr (meta::is_maybe_v<rhs_t>) {
            using result_type = decltype(broadcast_binary_ufunc(op,lhs,*rhs));
            using return_type = nmtools_maybe<result_type>;
            return (static_cast<bool>(rhs)
                ? return_type{broadcast_binary_ufunc(op,lhs,*rhs)}
                : return_type{meta::Nothing}
            );
        } else if constexpr (meta::is_either_v<lhs_t>) {
            using l_lhs_t = meta::get_either_left_t<lhs_t>;
            using l_rhs_t = meta::get_either_right_t<lhs_t>;
            using lhs_ufunc_t = decltype(broadcast_binary_ufunc(op,meta::declval<l_lhs_t>(),rhs));
            using rhs_ufunc_t = decltype(broadcast_binary_ufunc(op,meta::declval<l_rhs_t>(),rhs));
            using result_t = meta::replace_either_t<lhs_t,lhs_ufunc_t,rhs_ufunc_t>;
            if (auto lptr = nmtools::get_if<l_lhs_t>(&lhs)) {
                static_assert( meta::is_pointer_v<decltype(lptr)>
                    , "nmtools internal error" );
                static_assert( meta::is_same_v<meta::remove_cvref_t<decltype(*lptr)>,l_lhs_t>
                    , "nmtools internal error" );
                return result_t{broadcast_binary_ufunc(op,*lptr,rhs)};
            } else {
                auto rptr = nmtools::get_if<l_rhs_t>(&lhs);
                static_assert( meta::is_pointer_v<decltype(rptr)>
                    , "nmtools internal error" );
                static_assert( meta::is_same_v<meta::remove_cvref_t<decltype(*rptr)>,l_rhs_t>
                    , "nmtools internal error" );
                return result_t{broadcast_binary_ufunc(op,*rptr,rhs)};
            }
        } else if constexpr (meta::is_either_v<rhs_t>) {
            using r_lhs_t = meta::get_either_left_t<rhs_t>;
            using r_rhs_t = meta::get_either_right_t<rhs_t>;
            using lhs_ufunc_t = decltype(broadcast_binary_ufunc(op,lhs,meta::declval<r_lhs_t>()));
            using rhs_ufunc_t = decltype(broadcast_binary_ufunc(op,lhs,meta::declval<r_rhs_t>()));
            using result_t = meta::replace_either_t<rhs_t,lhs_ufunc_t,rhs_ufunc_t>;
            if (auto lptr = nmtools::get_if<r_lhs_t>(&rhs)) {
                static_assert( meta::is_pointer_v<decltype(lptr)>
                    , "nmtools internal error" );
                static_assert( meta::is_same_v<meta::remove_cvref_t<decltype(*lptr)>,r_lhs_t>
                    , "nmtools internal error" );
                return result_t{broadcast_binary_ufunc(op,lhs,*lptr)};
            } else {
                auto rptr = nmtools::get_if<r_rhs_t>(&rhs);
                static_assert( meta::is_pointer_v<decltype(rptr)>
                    , "nmtools internal error" );
                static_assert( meta::is_same_v<meta::remove_cvref_t<decltype(*rptr)>,r_rhs_t>
                    , "nmtools internal error" );
                return result_t{broadcast_binary_ufunc(op,lhs,*rptr)};
            }
        } else if constexpr (meta::is_num_v<lhs_t> && meta::is_num_v<rhs_t>) {
            // all rhs are numeric, use scalar_ufunc instead
            using view_t = decorator_t<scalar_ufunc_t,op_t,lhs_t,rhs_t>;
            return view_t{{op,lhs,rhs}};
        } else {
            auto broadcasted_arrays = broadcast_arrays(lhs, rhs);
            return binary_ufunc(op, broadcasted_arrays);
        }
    } // broadcast_binary_ufunc

    template <typename op_t, typename array_t, typename...args_t>
    constexpr auto unary_ufunc(const array_t& array, args::ufunc<op_t> attributes, args_t...args)
    {
        return unary_ufunc(attributes.op,array,args...);
    } // unary_ufunc

    template <typename op_t, typename lhs_t, typename rhs_t>
    constexpr auto binary_ufunc(const lhs_t& lhs, const rhs_t& rhs, args::ufunc<op_t> attributes)
    {
        return binary_ufunc(attributes.op,lhs,rhs);
    } // binary_ufunc

    template <typename op_t, template<typename...>typename tuple, typename lhs_t, typename rhs_t>
    constexpr auto binary_ufunc(const tuple<lhs_t,rhs_t>& arrays, args::ufunc<op_t> attributes)
    {
        return binary_ufunc(attributes.op,arrays);
    } // binary_ufunc

    template <typename op_t, typename lhs_t, typename rhs_t>
    constexpr auto broadcast_binary_ufunc(const lhs_t& lhs, const rhs_t& rhs, args::ufunc<op_t> attributes)
    {
        return broadcast_binary_ufunc(attributes.op,lhs,rhs);
    } // broadcast_binary_ufunc

    /**
     * @brief Create reduce_t object given op, array, axis and initial value.
     * 
     * @tparam op_t 
     * @tparam array_t 
     * @tparam axis_t 
     * @tparam initial_t 
     * @param op operation to perform, must be binary op
     * @param array array in which reduction to be performed
     * @param axis axis to reduce
     * @param initial inital value, can be None
     * @param keepdims keep reduced axes in the result as dimensions with size one.
     * @return constexpr auto 
     */
    template <typename op_t, typename array_t, typename axis_t, typename dtype_t=none_t, typename initial_t=none_t, typename keepdims_t=meta::false_type>
    constexpr auto reduce(op_t op, const array_t& array, const axis_t& axis, dtype_t dtype=dtype_t{}, initial_t initial=initial_t{}, keepdims_t keepdims=keepdims_t{})
    {
        // note: here, axis as reference to prevent array decays
        // the view type may decide wether to take ref or copy
        // TODO: error handling for duplicate axis

        if constexpr (meta::is_maybe_v<array_t>) {
            using array_type  = meta::get_maybe_type_t<array_t>;
            using result_type = decltype(reduce(op,meta::declval<array_type>(),axis,dtype,initial,keepdims));
            using return_type = nmtools_maybe<result_type>;
            if (static_cast<bool>(array)) {
                return return_type{reduce(op,*array,axis,dtype,initial,keepdims)};
            } else {
                return return_type{meta::Nothing};
            }
        } else if constexpr (meta::is_either_v<array_t>) {
            using left_t  = meta::get_either_left_t<array_t>;
            using right_t = meta::get_either_right_t<array_t>;
            using ret_left_t  = decltype(reduce(op,meta::declval<left_t>(),axis,dtype,initial,keepdims));
            using ret_right_t = decltype(reduce(op,meta::declval<right_t>(),axis,dtype,initial,keepdims));
            using either_t = meta::replace_either_t<array_t,ret_left_t,ret_right_t>;
            if (auto l_ptr = nmtools::get_if<left_t>(&array)) {
                return either_t{reduce(op,*l_ptr,axis,dtype,initial,keepdims)};
            } else /* if (auto r_ptr = nmtools::get_if<right_t>(&array)) */ {
                auto r_ptr = nmtools::get_if<right_t>(&array);
                return either_t{reduce(op,*r_ptr,axis,dtype,initial,keepdims)};
            }
        }
        // keepdims is runtime value, 
        // current reduce view implementation must know if it is scalar or ndarray at compile time,
        // only when axis is None, this can be performed, because 
        // when axis is None, reduce can return scalar or ndarray depends on keepdims type
        // use variant to tell that the return value may be scalar or ndarray,
        // depending on the value of keepdims at runtime
        else if constexpr (meta::is_boolean_v<keepdims_t>) {
            using left_t   = decltype(reduce(op,array,axis,dtype,initial,True));
            using right_t  = decltype(reduce(op,array,axis,dtype,initial,False));
            using either_t = meta::make_either_type_t<left_t,right_t>;
            return (
                keepdims ?
                  either_t{reduce(op,array,axis,dtype,initial,True)}
                : either_t{reduce(op,array,axis,dtype,initial,False)}
            );
        }
        // otherwise simply use as it is
        else {
            using view_t = decorator_t<reduce_t,op_t,array_t,axis_t,initial_t,keepdims_t,dtype_t>;
            return view_t{{op,array,axis,initial,keepdims,dtype}};
        }
    } // reduce

    template <typename array_t, typename axis_t, typename dtype_t, typename initial_t, typename keepdims_t, typename op_t>
    constexpr auto reduce(const array_t& array, const args::reduce<axis_t,dtype_t,initial_t,keepdims_t,op_t>& attributes)
    {
        return reduce(
            attributes.op
            , array
            , attributes.axis
            , attributes.dtype
            , attributes.initial
            , attributes.keepdims
        );
    }

    template <typename array_t, typename op_t, typename axis_t, typename dtype_t, typename initial_t, typename keepdims_t>
    constexpr auto reduce(const array_t& array, op_t op, const args::reduce<axis_t,dtype_t,initial_t,keepdims_t>& attributes)
    {
        return reduce(
            op
            , array
            , attributes.axis
            , attributes.dtype
            , attributes.initial
            , attributes.keepdims
        );
    }

    /**
     * @brief Create accumulate_t object given op, array and axis.
     * 
     * @tparam op_t 
     * @tparam array_t 
     * @tparam axis_t 
     * @param op 
     * @param array 
     * @param axis 
     * @return constexpr auto 
     */
    template <typename op_t, typename array_t, typename axis_t, typename dtype_t=none_t>
    constexpr auto accumulate(op_t op, const array_t& array, axis_t axis, dtype_t dtype=dtype_t{})
    {
        if constexpr (meta::is_maybe_v<array_t>) {
            using array_type  = meta::get_maybe_type_t<array_t>;
            using result_type = decltype(accumulate(op,meta::declval<array_type>(),axis,dtype));
            using return_type = nmtools_maybe<result_type>;
            if (static_cast<bool>(array)) {
                return return_type{accumulate(op,*array,axis,dtype)};
            } else {
                return return_type{meta::Nothing};
            }
        } else {
            using view_t = decorator_t<accumulate_t,op_t,array_t,axis_t,dtype_t>;
            return view_t{{op,array,axis,dtype}};
        }
    } // accumulate

    template <typename op_t, typename array_t, typename axis_t, typename dtype_t>
    constexpr auto accumulate(const array_t& array, const args::accumulate<axis_t,dtype_t,op_t>& attributes)
    {
        return accumulate(
            attributes.op
            , array
            , attributes.axis
            , attributes.dtype
        );
    } // accumulate

    template <typename array_t, typename op_t, typename axis_t, typename dtype_t>
    constexpr auto accumulate(const array_t& array, op_t op, const args::accumulate<axis_t,dtype_t,none_t>& attributes)
    {
        return accumulate(array, args::accumulate{attributes.axis,attributes.dtype,op});
    } // accumulate

    /**
     * @brief Create outer_t object given op, lhs array and rhs array.
     * 
     * @tparam op_t 
     * @tparam lhs_t 
     * @tparam rhs_t 
     * @param op operation to perform for each pair of lhs and rhs
     * @param lhs lhs array
     * @param rhs rhs array
     * @return constexpr auto 
     */
    template <typename op_t, typename lhs_t, typename rhs_t, typename dtype_t=none_t>
    constexpr auto outer(op_t op, const lhs_t& lhs, const rhs_t& rhs, dtype_t dtype=dtype_t{})
    {
        if constexpr (meta::is_maybe_v<lhs_t>) {
            using lhs_type = meta::get_maybe_type_t<lhs_t>;
            using result_type = decltype(outer(op,meta::declval<lhs_type>(),rhs,dtype));
            using return_type = meta::conditional_t<
                meta::is_maybe_v<result_type>
                , result_type
                , nmtools_maybe<result_type>>
            ;
            if (static_cast<bool>(lhs)) {
                auto result = outer(op,*lhs,rhs,dtype);
                if constexpr (meta::is_maybe_v<result_type>) {
                    return result;
                } else {
                    return return_type{result};
                }
            } else {
                return return_type{meta::Nothing};
            }
        } else if constexpr (meta::is_maybe_v<rhs_t>) {
            using rhs_type = meta::get_maybe_type_t<rhs_t>;
            using result_type = decltype(outer(op,lhs,meta::declval<rhs_type>(),dtype));
            using return_type = nmtools_maybe<result_type>;
            if (static_cast<bool>(rhs)) {
                return return_type{outer(op,lhs,*rhs,dtype)};
            } else {
                return return_type{meta::Nothing};
            }
        }
        // TODO: handle either type
        else {
            using view_t = decorator_t<outer_t,op_t,lhs_t,rhs_t,dtype_t>;
            return view_t{{op,lhs,rhs,dtype}};
        }
    } // outer

    template <typename op_t, typename lhs_t, typename rhs_t, typename dtype_t=none_t>
    constexpr auto outer(const lhs_t& lhs, const rhs_t& rhs, const args::outer<dtype_t,op_t>& attributes)
    {
        return outer(attributes.op,lhs,rhs,attributes.dtype);
    } // outer

    template <typename array_t, typename op_t, typename dtype_t>
    constexpr auto outer(const array_t& array, op_t op, const args::outer<dtype_t,none_t>& attributes)
    {
        return outer(array,args::outer{attributes.dtype,op});
    } // outer
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_UFUNC_HPP
