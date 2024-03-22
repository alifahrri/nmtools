#ifndef NMTOOLS_TESTING_STRING_HPP
#define NMTOOLS_TESTING_STRING_HPP

#include "nmtools/testing/platform.hpp"
#include "nmtools/meta.hpp"

#include "nmtools/utils/to_string.hpp"

#define NMTOOLS_TESTING_GET_TYPENAME NMTOOLS_TYPENAME_TO_STRING

#ifndef NMTOOLS_DISABLE_STL
#include <sstream>
#include <string>
#define NMTOOLS_STRING std::string
#elif defined(ARDUINO)
#include <Arduino.h>
#define NMTOOLS_STRING String
#elif __has_include(<string>)
// Quick workaround to disable stl but enable std::string
#include <sstream>
#include <string>
#define NMTOOLS_STRING std::string
#endif // NMTOOLS_DISABLE_STL

// allow to test on platform without RTTI support,
#if defined(__clang__)
#if __has_feature(cxx_rtti)
#define NMTOOLS_RTTI_ENABLED
#endif
#elif defined(__GNUC__)
#if defined(__GXX_RTTI)
#define NMTOOLS_RTTI_ENABLED
#endif
#elif defined(_MSC_VER)
#if defined(_CPPRTTI)
#define NMTOOLS_RTTI_ENABLED
#endif
#endif

namespace nmtools::testing
{
    template <size_t...I>
    using index_sequence = meta::integer_sequence<size_t,I...>;

    using utils::remove_string;

    /**
     * @ingroup testing
     * @{
     */

    /**
     * @brief overloaded version of make_func_args
     * 
     * @tparam Args non-type template parameters passed that should be passed to func
     * @param func function name
     * @param args arguments that should be passed to func
     * @return auto string formated with `func<tparams(s)...>(typename(s)...)`
     */
    template <typename...Args>
    auto make_func_args(NMTOOLS_STRING func, const Args&...args)
    {
        NMTOOLS_STRING ss;
        constexpr auto n = (sizeof...(args));
        #ifdef _NMTOOLS_TESTING_HAS_TYPE_INDEX
        auto typenames = meta::make_array_type_t<NMTOOLS_STRING,n>{
            {boost::typeindex::type_id<decltype(args)>().pretty_name()...}
        };
        #elif defined(NMTOOLS_RTTI_ENABLED)
        auto typenames = meta::make_array_type_t<NMTOOLS_STRING,n>{
            {typeid(decltype(args)).name()...}
        };
        #else
        // empty
        auto typenames = meta::make_array_type_t<NMTOOLS_STRING,n>{};
        #endif
        ss += func;
        ss += '(';
        for (size_t i=0; i<n; i++) {
            ss += typenames[i];
            if (i!=(n-1))
                ss += ",";
        }
        ss += ')';
        return ss;
    } // auto make_func_args

    template <typename...Args>
    auto make_func_args(NMTOOLS_STRING func, NMTOOLS_STRING result_type, const Args&...args)
    {
        NMTOOLS_STRING ss;
        constexpr auto n = (sizeof...(args));
        #ifdef _NMTOOLS_TESTING_HAS_TYPE_INDEX
        auto typenames = meta::make_array_type_t<NMTOOLS_STRING,n>{
            {boost::typeindex::type_id<decltype(args)>().pretty_name()...}
        };
        #elif defined(NMTOOLS_RTTI_ENABLED)
        auto typenames = meta::make_array_type_t<NMTOOLS_STRING,n>{
            {typeid(decltype(args)).name()...}
        };
        #else
        // empty
        auto typenames = meta::make_array_type_t<NMTOOLS_STRING,n>{};
        #endif
        ss += func;
        ss += '(';
        for (size_t i=0; i<n; i++) {
            ss += typenames[i];
            if (i!=(n-1))
                ss += ",";
        }
        ss += ") -> ";
        ss += result_type;
        return ss;
    } // auto make_func_args

    /** @} */ // end groupt testing
} // nmtools::testing

#endif // NMTOOLS_TESTING_STRING_HPP
