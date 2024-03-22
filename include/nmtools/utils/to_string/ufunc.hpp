#ifndef NMTOOLS_UTILS_TO_STRING_UFUNC_HPP
#define NMTOOLS_UTILS_TO_STRING_UFUNC_HPP

#include "nmtools/array/view/ufunc/ufunc.hpp"
#include "nmtools/array/view/ufunc/outer.hpp"
#include "nmtools/array/view/ufunc/reduce.hpp"
#include "nmtools/array/view/ufunc/accumulate.hpp"

namespace nmtools::utils::impl
{
    template <typename op_t>
    struct to_string_t<
        args::ufunc<op_t>, none_t, void
    >
    {
        using attribute_type = args::ufunc<op_t>;

        auto operator()([[maybe_unused]] const attribute_type& attribute) const noexcept
        {
            nmtools_string str;

            auto op_str = to_string(attribute.op);
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
        , typename keepdims_t>
    struct to_string_t<
        args::reduce<op_t,axis_t,dtype_t,initial_t,keepdims_t>, none_t, void
    >
    {
        using attribute_type = args::reduce<op_t,axis_t,dtype_t,initial_t,keepdims_t>;

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
            str += to_string(attribute.axis); 
            str += ",.dtype=";
            str += to_string(attribute.dtype); 
            str += ",.initial=";
            str += to_string(attribute.initial); 
            str += ",.keepdims=";
            str += to_string(attribute.keepdims);

            str += "}";
            
            return str;
        }
    };

    template <typename op_t
        , typename dtype_t>
    struct to_string_t<
        args::outer<op_t,dtype_t>, none_t, void
    >
    {
        using attribute_type = args::outer<op_t,dtype_t>;

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
            str += ",.dtype=";
            str += to_string(attribute.dtype);

            str += "}";
            
            return str;
        }
    };

    template <typename op_t
        , typename axis_t
        , typename dtype_t>
    struct to_string_t<
        args::accumulate<op_t,axis_t,dtype_t>, none_t, void
    >
    {
        using attribute_type = args::accumulate<op_t,axis_t,dtype_t>;

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
            str += to_string(attribute.axis); 
            str += ",.dtype=";
            str += to_string(attribute.dtype); 

            str += "}";
            
            return str;
        }
    };
}

#endif // NMTOOLS_UTILS_TO_STRING_UFUNC_HPP