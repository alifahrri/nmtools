#ifndef NMTOOLS_UTL_STRING_CAST_HPP
#define NMTOOLS_UTL_STRING_CAST_HPP

#include "nmtools/def.hpp"
#include "nmtools/assert.hpp"
#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/is_constant_index.hpp"
#include "nmtools/meta/bits/transform/remove_cvref.hpp"
#include "nmtools/utility/utl/get_if.hpp"
#include "nmtools/utl/string.hpp"
#include "nmtools/utl/static_string.hpp"

#if !defined(NMTOOLS_DISABLE_STL) && __has_include(<string>)
    #include <string>
    #define NMTOOLS_UTL_HAS_STD_STRING 1
#else
    #define NMTOOLS_UTL_HAS_STD_STRING 0
#endif // <string>

namespace nmtools::utl
{
    namespace detail
    {
        template <typename T>
        struct is_static_string_base : false_type {};
        template <nm_size_t Capacity, typename T>
        struct is_static_string_base<static_string_base<Capacity,T>> : true_type {};

        template <typename T>
        struct is_string_base : false_type {};
        template <nm_size_t Capacity, typename T>
        struct is_string_base<string_base<Capacity,T>> : true_type {};

        template <typename T>
        struct static_string_capacity {};
        template <nm_size_t Capacity, typename T>
        struct static_string_capacity<static_string_base<Capacity,T>>
        {
            constexpr static nm_size_t value = Capacity;
        };

        #if NMTOOLS_UTL_HAS_STD_STRING
        template <typename T>
        struct is_std_string : false_type {};
        template <>
        struct is_std_string<std::string> : true_type {};
        #endif // NMTOOLS_UTL_HAS_STD_STRING

        template <typename... args_t>
        struct always_false : false_type {};

        // build a utl string (either flavor) out of content characters:
        // both flavors have content-based resize that appends/maintains the
        // trailing terminating '\0' automatically.
        template <typename dst_t, typename src_t>
        constexpr auto make_utl_string(nm_size_t n, const src_t& src)
        {
            auto result = dst_t{};
            result.resize(n);
            for (nm_size_t i=0; i<n; i++) {
                result[i] = src[i];
            }
            return result;
        }
    } // namespace detail

    /************************************************************************* */
    // string_cast<dst_str_t>(src_str)
    //
    // converts between utl::string_base (aka utl::string),
    // utl::static_string_base (aka utl::static_string) and std::string
    // (when available).
    //
    // convention: utl strings keep a trailing '\0' in their buffer, while
    // std::string does not. all flavors report size() excluding the
    // trailing '\0'. conversions preserve this invariant in both
    // directions.
    //
    // casting into a static_string_base panics when the source does not fit
    // into its capacity, unless a constant index truncate flag (such as
    // meta::true_type) is given, in which case the content is clamped to
    // fit. casting into a string_base grows to its heap backend when needed.
    //
    // the truncate flag is honored for any source flavor when casting into
    // a static_string_base; without it, any source that does not fit panics.
    /************************************************************************* */

    // from utl::static_string_base
    //
    // truncate_t: constant index flag (e.g. meta::true_type), only
    // meaningful when both src and dst are static_string_base; when true,
    // content is clamped to fit into the destination capacity instead of
    // panicking.
    template <typename dst_t, typename truncate_t=false_type, nm_size_t Capacity, typename T>
    constexpr auto string_cast(const static_string_base<Capacity,T>& src, [[maybe_unused]] truncate_t truncate = truncate_t{}) -> dst_t
    {
        using dst_type = remove_cvref_t<dst_t>;
        constexpr bool is_static_dst = detail::is_static_string_base<dst_type>::value;
        if constexpr (is_same_v<dst_type, static_string_base<Capacity,T>>) {
            return src;
        } else if constexpr (is_static_dst || detail::is_string_base<dst_type>::value) {
            auto n = src.size();
            if constexpr (is_static_dst) {
                constexpr auto dst_capacity = detail::static_string_capacity<dst_type>::value;
                constexpr bool do_truncate = is_constant_index_v<truncate_t> ? (truncate_t::value != 0) : false;
                if constexpr (do_truncate) {
                    constexpr auto max_content = dst_capacity - 1;
                    if (n > (nm_size_t)max_content) {
                        n = (nm_size_t)max_content;
                    }
                } else {
                    nmtools_panic( (n + 1) <= (nm_size_t)dst_capacity
                        , "string_cast: source does not fit into destination capacity"
                    );
                }
            }
            return detail::make_utl_string<dst_type>(n, src);
        }
        #if NMTOOLS_UTL_HAS_STD_STRING
        else if constexpr (detail::is_std_string<dst_type>::value) {
            static_assert( is_same_v<T,char>
                , "string_cast: only char based strings can be cast to std::string"
            );
            auto n = src.size();
            return std::string(src.data(), n);
        }
        #endif // NMTOOLS_UTL_HAS_STD_STRING
        else {
            static_assert( detail::always_false<dst_type>::value
                , "string_cast: unsupported destination string type"
            );
            return dst_type{};
        }
    }

    // from utl::string_base
    template <typename dst_t, typename truncate_t=false_type, nm_size_t Capacity, typename T>
    constexpr auto string_cast(const string_base<Capacity,T>& src, [[maybe_unused]] truncate_t truncate = truncate_t{}) -> dst_t
    {
        using dst_type = remove_cvref_t<dst_t>;
        constexpr bool is_static_dst = detail::is_static_string_base<dst_type>::value;
        if constexpr (is_same_v<dst_type, string_base<Capacity,T>>) {
            return src;
        } else if constexpr (is_static_dst || detail::is_string_base<dst_type>::value) {
            auto n = src.size();
            if constexpr (is_static_dst) {
                constexpr auto dst_capacity = detail::static_string_capacity<dst_type>::value;
                constexpr bool do_truncate = is_constant_index_v<truncate_t> ? (truncate_t::value != 0) : false;
                if constexpr (do_truncate) {
                    constexpr auto max_content = dst_capacity - 1;
                    if (n > (nm_size_t)max_content) {
                        n = (nm_size_t)max_content;
                    }
                } else {
                    nmtools_panic( (n + 1) <= (nm_size_t)dst_capacity
                        , "string_cast: source does not fit into destination capacity"
                    );
                }
            }
            return detail::make_utl_string<dst_type>(n, src);
        }
        #if NMTOOLS_UTL_HAS_STD_STRING
        else if constexpr (detail::is_std_string<dst_type>::value) {
            static_assert( is_same_v<T,char>
                , "string_cast: only char based strings can be cast to std::string"
            );
            auto n = src.size();
            return std::string(src.data(), n);
        }
        #endif // NMTOOLS_UTL_HAS_STD_STRING
        else {
            static_assert( detail::always_false<dst_type>::value
                , "string_cast: unsupported destination string type"
            );
            return dst_type{};
        }
    }

    #if NMTOOLS_UTL_HAS_STD_STRING
    // from std::string
    template <typename dst_t, typename truncate_t=false_type>
    constexpr auto string_cast(const std::string& src, [[maybe_unused]] truncate_t truncate = truncate_t{}) -> dst_t
    {
        using dst_type = remove_cvref_t<dst_t>;
        if constexpr (is_same_v<dst_type, std::string>) {
            return src;
        } else {
            constexpr bool is_static_dst  = detail::is_static_string_base<dst_type>::value;
            constexpr bool is_dynamic_dst = detail::is_string_base<dst_type>::value;
            static_assert( is_static_dst || is_dynamic_dst
                , "string_cast: destination must be a utl string type or std::string"
            );
            auto n = (nm_size_t)src.size();
            if constexpr (is_static_dst) {
                constexpr auto dst_capacity = detail::static_string_capacity<dst_type>::value;
                constexpr bool do_truncate = is_constant_index_v<truncate_t> ? (truncate_t::value != 0) : false;
                if constexpr (do_truncate) {
                    constexpr auto max_content = dst_capacity - 1;
                    if (n > (nm_size_t)max_content) {
                        n = (nm_size_t)max_content;
                    }
                } else {
                    nmtools_panic( (n + 1) <= (nm_size_t)dst_capacity
                        , "string_cast: source does not fit into destination capacity"
                    );
                }
            }
            return detail::make_utl_string<dst_type>(n, src);
        }
    }
    #endif // NMTOOLS_UTL_HAS_STD_STRING
} // namespace nmtools::utl

#endif // NMTOOLS_UTL_STRING_CAST_HPP
