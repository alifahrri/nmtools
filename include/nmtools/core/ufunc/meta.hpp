#ifndef NMTOOLS_ARRAY_CORE_UFUNC_META_HPP
#define NMTOOLS_ARRAY_CORE_UFUNC_META_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/ref.hpp"
#include "nmtools/utility/at.hpp"
#include "nmtools/core/decorator.hpp"
#include "nmtools/index/outer.hpp"
#include "nmtools/index/remove_dims.hpp"
#include "nmtools/index/where.hpp"
#include "nmtools/index/sum.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/dtypes.hpp"
#include "nmtools/constants.hpp"

// seems like constexpr math is in the library level,
// TODO: deduce std library implementation instead of compiler to decide constexpr
// clang doesn't support constexpr math while gcc does
#if defined(__GNUC__) && !defined(__clang__) && !defined(NMTOOLS_UFUNC_CONSTEXPR)
#define NMTOOLS_UFUNC_CONSTEXPR constexpr
#else
#define NMTOOLS_UFUNC_CONSTEXPR
#endif

namespace nmtools
{
    namespace casting
    {
        enum class Casting {
            AUTO=0,
            EQUIV,
            SAME_KIND
        };
        using auto_t      = meta::as_type<Casting::AUTO>;
        using equiv_t     = meta::as_type<Casting::EQUIV>;
        using same_kind_t = meta::as_type<Casting::SAME_KIND>;

        constexpr inline auto AUTO      = auto_t {};
        constexpr inline auto EQUIV     = equiv_t {};
        constexpr inline auto SAME_KIND = same_kind_t {};

        namespace error
        {
            template <typename...>
            struct CASTING_UNSUPPORTED : meta::detail::fail_t {};
        }
    } // namespace casting

    template <typename T>
    struct get_casting
    {
        static constexpr auto value = casting::error::CASTING_UNSUPPORTED<T>{};
    };

    template <casting::Casting kind>
    struct get_casting<
        meta::as_type<kind>
    > {
        static constexpr auto value = kind;
    };

    template <typename T>
    constexpr inline auto get_casting_v = get_casting<T>::value;
} // nmaespace nmtools

namespace nmtools::meta
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

    namespace error
    {
        template <typename...>
        struct GET_REDUCER_RESULT_TYPE_UNSUPPORTED : detail::fail_t {};
    }

    /**
     * @brief Helper metafunction to deduce the type of reduce operations.
     * 
     * @tparam reducer_t 
     * @tparam element_t 
     * @tparam typename 
     */
    template <typename always_void, typename reducer_t, typename element_t, typename dtype_t, typename initial_t>
    struct get_reducer_result_type
    {
        static constexpr auto vtype = [](){
            if constexpr (
                !(is_num_v<element_t> || is_boolean_v<element_t>)
                || !(is_none_v<dtype_t> || is_dtype_v<dtype_t>)
                || !(is_none_v<initial_t> || is_num_v<initial_t> || is_boolean_v<initial_t>)
            ) {
                using type = error::GET_REDUCER_RESULT_TYPE_UNSUPPORTED<reducer_t,element_t,dtype_t,initial_t>;
                return as_value_v<type>;
            } else if constexpr (
                is_dtype_v<dtype_t>
            ) {
                using type = get_dtype_t<dtype_t>;
                return as_value_v<type>;
            } else if constexpr (
                is_none_v<dtype_t>
                && !is_none_v<initial_t>
            ) {
                using type = common_type_t<element_t,initial_t>;
                return as_value_v<type>;
            } else if constexpr (
                has_result_type_v<reducer_t>
            ) {
                using type = typename reducer_t::result_type;
                return as_value_v<type>;
            } else {
                using type = element_t;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // get_reducer_result_type

    template <typename reducer_t, typename element_t, typename dtype_t, typename initial_t>
    using get_reducer_result_type_t = type_t<get_reducer_result_type<void,reducer_t,element_t,dtype_t,initial_t>>;

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
            if constexpr (meta::has_result_type_v<op_type>) {
                using result_t = typename op_type::result_type;
                return meta::as_value<result_t>{};
            }
            else return meta::as_value<element_t>{};
        }();
        using type = meta::type_t<meta::remove_cvref_t<decltype(vtype)>>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_CORE_UFUNC_META_HPP