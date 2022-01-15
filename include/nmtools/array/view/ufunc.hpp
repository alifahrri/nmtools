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

    template <typename op_t, template<typename...> typename tuple, typename...arrays_t, size_t...Is>
    constexpr auto _ufunc(op_t op, const tuple<arrays_t...>& func, meta::index_sequence<Is...>)
    {
        // help deduction
        return decorator_t<ufunc_t,op_t,arrays_t...>{{op, nmtools::get<Is>(func)...}};
    }; // _ufunc

    template <typename op_t, template<typename...> typename tuple, typename...arrays_t>
    constexpr auto _ufunc(op_t op, const tuple<arrays_t...>& func)
    {
        return _ufunc(op,func,meta::make_index_sequence<sizeof...(arrays_t)>{});
    }; // _ufunc

    /**
     * @brief Creates unfunc_t object, given op and arrays.
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
        if constexpr (meta::is_either_v<array_t>) {
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
            // all arrays are numeric, use scalar_ufunc instead
            using view_t = decorator_t<scalar_ufunc_t,op_t,array_t,arrays_t...>;
            return view_t{{op,array,arrays...}};
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
            // single argument ufunc, skip broadcasting
            using view_t = decorator_t<ufunc_t,op_t,array_t>;
            return view_t{{op,{array}}};
        }
    } // ufunc

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
    template <typename op_t, typename array_t, typename axis_t, typename initial_t, typename keepdims_t=meta::false_type>
    constexpr auto reduce(op_t op, const array_t& array, const axis_t& axis, initial_t initial, keepdims_t keepdims=keepdims_t{})
    {
        // note: here, axis as reference to prevent array decays
        // the view type may decide wether to take ref or copy
        // TODO: error handling for duplicate axis

        if constexpr (meta::is_either_v<array_t>) {
            using left_t  = meta::get_either_left_t<array_t>;
            using right_t = meta::get_either_right_t<array_t>;
            using ret_left_t  = decltype(reduce(op,meta::declval<left_t>(),axis,initial,keepdims));
            using ret_right_t = decltype(reduce(op,meta::declval<right_t>(),axis,initial,keepdims));
            using either_t = meta::replace_either_t<array_t,ret_left_t,ret_right_t>;
            if (auto l_ptr = nmtools::get_if<left_t>(&array)) {
                return either_t{reduce(op,*l_ptr,axis,initial,keepdims)};
            } else /* if (auto r_ptr = nmtools::get_if<right_t>(&array)) */ {
                auto r_ptr = nmtools::get_if<right_t>(&array);
                return either_t{reduce(op,*r_ptr,axis,initial,keepdims)};
            }
        }
        // keepdims is runtime value, 
        // current reduce view implementation must know if it is scalar or ndarray at compile time,
        // only when axis is None, this can be performed, because 
        // when axis is None, reduce can return scalar or ndarray depends on keepdims type
        // use variant to tell that the return value may be scalar or ndarray,
        // depending on the value of keepdims at runtime
        else if constexpr (is_none_v<axis_t> && meta::is_boolean_v<keepdims_t>) {
            using scalar_t = decorator_t<reduce_t,op_t,array_t,axis_t,initial_t,meta::false_type>;
            using ndarray_t = decorator_t<reduce_t,op_t,array_t,axis_t,initial_t,meta::true_type>;
            // TODO: make default either type configurable
            using either_t = meta::make_either_type_t<scalar_t,ndarray_t>;
            return (keepdims ?
                    either_t{ndarray_t{{op,array,axis,initial,True}}}
                : either_t{scalar_t{{op,array,axis,initial,False}}});
        }
        else if constexpr (meta::is_boolean_v<keepdims_t>) {
            using left_t   = decltype(reduce(op,array,axis,initial,True));
            using right_t  = decltype(reduce(op,array,axis,initial,False));
            using either_t = meta::make_either_type_t<left_t,right_t>;
            return (
                keepdims ?
                  either_t{reduce(op,array,axis,initial,True)}
                : either_t{reduce(op,array,axis,initial,False)}
            );
        }
        // otherwise simply use as it is
        else {
            using view_t = decorator_t<reduce_t,op_t,array_t,axis_t,initial_t,keepdims_t>;
            return view_t{{op,array,axis,initial,keepdims}};
        }
    } // reduce

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
    template <typename op_t, typename array_t, typename axis_t>
    constexpr auto accumulate(op_t op, const array_t& array, axis_t axis)
    {
        // note: axis as reference to prevent array decays
        using view_t = decorator_t<accumulate_t,op_t,array_t,axis_t>;
        return view_t{{op,array,axis}};
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
    template <typename op_t, typename lhs_t, typename rhs_t>
    constexpr auto outer(op_t op, const lhs_t& lhs, const rhs_t& rhs)
    {
        using view_t = decorator_t<outer_t,op_t,lhs_t,rhs_t>;
        return view_t{{op,lhs,rhs}};
    }
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_UFUNC_HPP
