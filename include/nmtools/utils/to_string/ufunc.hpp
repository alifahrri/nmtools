#ifndef NMTOOLS_UTILS_TO_STRING_UFUNC_HPP
#define NMTOOLS_UTILS_TO_STRING_UFUNC_HPP

#include "nmtools/array/view/ufunc/ufunc.hpp"
#include "nmtools/array/view/ufunc/outer.hpp"
#include "nmtools/array/view/ufunc/reduce.hpp"
#include "nmtools/array/view/ufunc/accumulate.hpp"

// TODO: move to respective ufunc files

namespace nmtools::utils::impl
{
    template <typename op_t
        , typename formatter_t
    >
    struct to_string_t<
        args::ufunc<op_t>
        , formatter_t
    >
    {
        using attribute_type = args::ufunc<op_t>;
        using formatter_type = formatter_t;

        auto operator()([[maybe_unused]] const attribute_type& attribute) const noexcept
        {
            nmtools_string str;

            auto op_str = to_string(attribute.op,formatter_type{});
            if (op_str.empty()) {
                op_str = NMTOOLS_TYPENAME_TO_STRING(op_t);
            }

            str += "{";

            str += ".op=";
            str += op_str;

            str += "}";
            
            return str;
        }
    };

    template <typename op_t
        , typename axis_t
        , typename dtype_t
        , typename initial_t
        , typename keepdims_t
        , typename formatter_t
    >
    struct to_string_t<
        args::reduce<op_t,axis_t,dtype_t,initial_t,keepdims_t>
        , formatter_t
    >
    {
        using attribute_type = args::reduce<op_t,axis_t,dtype_t,initial_t,keepdims_t>;
        using formatter_type = formatter_t;

        auto operator()(const attribute_type& attribute) const noexcept
        {
            nmtools_string str;

            auto op_str = nmtools_string("");
            op_str = NMTOOLS_TYPENAME_TO_STRING(op_t);

            using mapper_type = to_string_t<decltype(attribute.op),formatter_type>;
            if constexpr (meta::has_result_type_v<mapper_type>) {
                if constexpr (!meta::is_fail_v<typename mapper_type::result_type>) {
                    op_str = to_string(attribute.op,formatter_type{});
                }
            }

            str += "{";

            str += ".op=";
            str += op_str; 
            str += ",.axis=";
            str += to_string(attribute.axis,formatter_type{}); 
            str += ",.dtype=";
            str += to_string(attribute.dtype,formatter_type{}); 
            str += ",.initial=";
            str += to_string(attribute.initial,formatter_type{});
            str += ",.keepdims=";
            str += to_string(attribute.keepdims,formatter_type{});

            str += "}";
            
            return str;
        }
    };

    template <typename op_t
        , typename dtype_t
        , typename formatter_t
    >
    struct to_string_t<
        args::outer<op_t,dtype_t>
        , formatter_t
    >
    {
        using attribute_type = args::outer<op_t,dtype_t>;
        using formatter_type = formatter_t;

        auto operator()(const attribute_type& attribute) const noexcept
        {
            nmtools_string str;

            auto op_str = to_string(attribute.op,formatter_type{});
            if (op_str.empty()) {
                op_str = NMTOOLS_TYPENAME_TO_STRING(op_t);
            }

            str += "{";

            str += ".op=";
            str += op_str;
            str += ",.dtype=";
            str += to_string(attribute.dtype,formatter_type{});

            str += "}";
            
            return str;
        }
    };

    template <typename op_t
        , typename axis_t
        , typename dtype_t
        , typename formatter_t
    >
    struct to_string_t<
        args::accumulate<op_t,axis_t,dtype_t>
        , formatter_t
    > {
        using attribute_type = args::accumulate<op_t,axis_t,dtype_t>;
        using formatter_type = formatter_t;

        auto operator()(const attribute_type& attribute) const noexcept
        {
            nmtools_string str;

            auto op_str = to_string(attribute.op);
            if (op_str.empty()) {
                op_str = NMTOOLS_TYPENAME_TO_STRING(op_t);
            }

            str += "{";

            str += ".op=";
            str += op_str;
            str += ",.axis=";
            str += to_string(attribute.axis,formatter_type{});
            str += ",.dtype=";
            str += to_string(attribute.dtype,formatter_type{});

            str += "}";
            
            return str;
        }
    };
}

#endif // NMTOOLS_UTILS_TO_STRING_UFUNC_HPP