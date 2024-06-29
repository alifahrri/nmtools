#ifndef NMTOOLS_ARRAY_VIEW_UFUNC_DETAIL_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNC_DETAIL_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/view/ref.hpp"
#include "nmtools/array/utility/apply_at.hpp"
#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/view/slice.hpp"
#include "nmtools/array/view/flatten.hpp"
#include "nmtools/array/view/broadcast_arrays.hpp"
#include "nmtools/array/index/outer.hpp"
#include "nmtools/array/index/remove_dims.hpp"
#include "nmtools/array/index/where.hpp"
#include "nmtools/array/index/sum.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/dtypes.hpp"
#include "nmtools/array/ndarray.hpp"
#include "nmtools/array/eval.hpp"
#include "nmtools/constants.hpp"

// seems like constexpr math is in the library level,
// TODO: deduce std library implementation instead of compiler to decide constexpr
// clang doesn't support constexpr math while gcc does
#if defined(__GNUC__) && !defined(__clang__) && !defined(NMTOOLS_UFUNC_CONSTEXPR)
#define NMTOOLS_UFUNC_CONSTEXPR constexpr
#else
#define NMTOOLS_UFUNC_CONSTEXPR
#endif

namespace nmtools::view::detail
{
    /**
     * @brief helper metafunction to deduce the operand types for ufunc,
     * dont take reference for 'view' objects/simple number.
     * 
     * @tparam always_void 
     * @tparam arrays_t 
     */
    template <typename always_void, typename...arrays_t>
    struct get_operands_type
    {
        static_assert( sizeof...(arrays_t) > 0, "nmtools internal error" );
        static constexpr auto vtype = [](){
            // TODO: no need to create full tuple here, use meta::type_list
            using arrays_type = nmtools_tuple<arrays_t...>;
            // for view / num type: simply copy (take value),
            // otherwise take reference
            return meta::template_reduce<sizeof...(arrays_t)>([](auto init, auto index){
                constexpr auto i = decltype(index)::value;
                using array_t    = meta::at_t<arrays_type,i>;
                using operand_t  = view::resolve_array_type_t<array_t>;
                using init_t = meta::type_t<decltype(init)>; 
                if constexpr (meta::is_void_v<init_t>) {
                    return meta::as_value_v<nmtools_tuple<operand_t>>;
                } else {
                    return meta::as_value_v<meta::append_type_t<init_t,operand_t>>;
                }
            }, meta::as_value_v<void>);
        }();
        using type = meta::type_t<decltype(vtype)>;
    }; // get_operands_type

    template <typename...arrays_t>
    using get_operands_type_t = meta::type_t<get_operands_type<void,arrays_t...>>;

    /**
     * @brief Helper trait to check if type T has member type `result_type`
     * 
     * @tparam T type to check
     * @tparam typename 
     */
    template <typename T, typename=void>
    struct has_result_type : meta::false_type {};

    template <typename T>
    struct has_result_type<T,meta::void_t<typename T::result_type>> : meta::true_type {};

    template <typename T>
    constexpr inline auto has_result_type_v = has_result_type<T>::value;

    /**
     * @brief Helper metafunction to deduce the return type from op an args for ufuncs.
     * 
     * @tparam always_void 
     * @tparam op_t 
     * @tparam args_t 
     */
    template <typename always_void, typename op_t, typename...args_t>
    struct get_ufunc_result_type
    {
        using type = decltype(meta::declval<op_t>()(meta::declval<args_t>()...));
    }; // get_ufunc_result_type

    template <typename op_t, typename...args_t>
    struct get_ufunc_result_type<
        meta::void_t<typename op_t::result_type>,
        op_t, args_t...
    >
    {
        using type = typename op_t::result_type;
    }; // get_ufunc_result_type

    template <typename op_t, typename...args_t>
    using get_ufunc_result_type_t = typename get_ufunc_result_type<void,op_t,args_t...>::type;

    /**
     * @brief Helper metafunction to deduce the type of reduce operations.
     * 
     * @tparam reducer_t 
     * @tparam element_t 
     * @tparam typename 
     */
    template <typename reducer_t, typename element_t, typename=void>
    struct get_reducer_result_type
    {
        using type = element_t;
    }; // get_reducer_result_type

    template <typename reducer_t, typename element_t>
    struct get_reducer_result_type< reducer_t, element_t,
        meta::void_t<typename reducer_t::result_type>
    >
    {
        using type = typename reducer_t::result_type;
    }; // get_reducer_result_type

    template <typename reducer_t, typename element_t>
    using get_reducer_result_type_t = typename get_reducer_result_type<reducer_t,element_t>::type;

    /**
     * @brief helper type that wraps type `T`, avoid constructing the actual type.
     * 
     * @tparam T 
     */
    template <typename T>
    struct type_wrapper
    {
        using type = T;
    }; // type_wrapper
        
    /**
     * @brief Get the result type of given op_type
     *
     * Prefer op_type::result_type when available, use element_t otherwise.
     * 
     * @tparam element_t 
     * @tparam op_type 
     */
    template <typename element_t, typename op_type>
    struct get_result_type
    {
        // for op type with explicit result_type member type, prefer that type
        // other wise use referenced array's element type
        static constexpr auto vtype = [](){
            if constexpr (detail::has_result_type_v<op_type>) {
                using result_t = typename op_type::result_type;
                return meta::as_value<result_t>{};
            }
            else return meta::as_value<element_t>{};
        }();
        using type = meta::type_t<meta::remove_cvref_t<decltype(vtype)>>;
    };
} // namespace::view::detail

#endif // NMTOOLS_ARRAY_VIEW_UFUNC_DETAIL_HPP