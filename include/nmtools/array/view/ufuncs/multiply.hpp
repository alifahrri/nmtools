#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_MULTIPLY_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_MULTIPLY_HPP

#include "nmtools/utils/to_string/to_string.hpp"
#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::view::fun
{
    template <
        typename lhs_t=none_t,
        typename rhs_t=none_t,
        typename res_t=none_t,
        typename=void
    >
    struct multiply
    {

        static constexpr auto identity()
        {
            if constexpr (meta::is_num_v<res_t>) {
                return static_cast<res_t>(1);
            } else {
                return 1;
            }
        }

        // NOTE: tried to disable but not successful
        // TODO: remove by unifying with primary template
        #if 0
        // NOTE: required for 'result_type' for reduction
        static constexpr auto result_vtype = [](){
            if constexpr (meta::is_num_v<res_t>) {
                return meta::as_value_v<res_t>;
            } else {
                return meta::as_value_v<none_t>;
            }
        }();
        using result_type = meta::type_t<decltype(result_vtype)>;
        #endif

        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const
        {
            using result_type = res_t;
            if constexpr (is_none_v<result_type>) {
                return t * u;
            } else {
                return static_cast<result_type>(t * u);
            }
        } // operator()
    }; // multiply

    // NOTE: tried to disable but not successful
    // TODO: remove by unifying with primary template
    #if 1
    template <typename res_t>
    struct multiply<none_t,none_t,res_t
        , meta::enable_if_t<meta::is_num_v<res_t>>
    >
    {
        using result_type = res_t;

        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const -> res_t
        {
            return t * u;
        } // operator()
    }; // multiply
    #endif
}

namespace nmtools::view
{
    template <
        typename lhs_t=none_t,
        typename rhs_t=none_t,
        typename res_t=none_t
    >
    using multiply_t = fun::multiply<lhs_t,rhs_t,res_t>;

    template <typename left_t, typename right_t, typename casting_t=casting::auto_t>
    constexpr auto multiply(const left_t& a, const right_t& b, casting_t=casting_t{})
    {
        constexpr auto cast_kind = get_casting_v<casting_t>;
        static_assert( !meta::is_fail_v<decltype(cast_kind)>, "unsupported casting kind" );
        using lhs_t [[maybe_unused]] = meta::get_element_type_t<left_t>;
        using rhs_t [[maybe_unused]] = meta::get_element_type_t<right_t>;
        using casting::Casting;
        if constexpr (cast_kind == Casting::AUTO) {
            return ufunc(multiply_t<>{},a,b);
        } else /* if constexpr (cast_kind == Casting::SAME_KIND) */ {
            static_assert( meta::is_same_v<lhs_t,rhs_t>, "unsupported same-kind cast");
            return ufunc(multiply_t<lhs_t,rhs_t,rhs_t>{},a,b);
        }
        // TODO: support Casting::EQUIV
    } // multiply

    template <typename left_t, typename axis_t, typename dtype_t, typename initial_t, typename keepdims_t>
    constexpr auto reduce_multiply(const left_t& a, const axis_t& axis, dtype_t dtype, initial_t initial, keepdims_t keepdims)
    {
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = multiply_t<none_t,none_t,res_t>;
        return reduce(op_t{},a,axis,dtype,initial,keepdims);
    } // reduce_multiply

    template <typename left_t, typename axis_t, typename dtype_t, typename initial_t, typename keepdims_t, typename op_t=none_t>
    constexpr auto reduce_multiply(const left_t& a, const args::reduce<axis_t,dtype_t,initial_t,keepdims_t,op_t>& attributes)
    {
        return reduce_multiply(a
            , attributes.axis
            , attributes.dtype
            , attributes.initial
            , attributes.keepdims
        );
    }

    template <typename left_t, typename axis_t, typename dtype_t, typename initial_t>
    constexpr auto reduce_multiply(const left_t& a, const axis_t& axis, dtype_t dtype, initial_t initial)
    {
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = multiply_t<none_t,none_t,res_t>;
        return reduce(op_t{},a,axis,dtype,initial);
    } // reduce_multiply

    template <typename left_t, typename axis_t, typename dtype_t>
    constexpr auto reduce_multiply(const left_t& a, const axis_t& axis, dtype_t dtype)
    {
        return reduce_multiply(a,axis,dtype,None);
    } // reduce_multiply

    // TODO: use default args instead of overload
    template <typename left_t, typename axis_t>
    constexpr auto reduce_multiply(const left_t& a, const axis_t& axis)
    {
        return reduce_multiply(a,axis,None,None);
    } // reduce_multiply

    template <typename left_t, typename axis_t, typename dtype_t>
    constexpr auto accumulate_multiply(const left_t& a, const axis_t& axis, dtype_t dtype)
    {
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = multiply_t<none_t,none_t,res_t>;
        return accumulate(op_t{},a,axis,dtype);
    } // accumulate_multiply

    template <typename left_t, typename axis_t>
    constexpr auto accumulate_multiply(const left_t& a, const axis_t& axis)
    {
        return accumulate_multiply(a,axis,None);
    } // accumulate_multiply

    template <typename left_t, typename right_t, typename dtype_t=none_t>
    constexpr auto outer_multiply(const left_t& a, const right_t& b, dtype_t dtype=dtype_t{})
    {
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = multiply_t<none_t,none_t,res_t>;
        return outer(op_t{},a,b,dtype);
    } // outer_multiply
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <
        typename lhs_t,
        typename rhs_t,
        typename res_t
    >
    struct to_string_t<view::fun::multiply<lhs_t,rhs_t,res_t>,none_t>
    {
        auto operator()(view::fun::multiply<lhs_t,rhs_t,res_t>) const
        {
            auto str = nmtools_string();

            str += "multiply";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_MULTIPLY_HPP