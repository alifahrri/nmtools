#ifndef NMTOOLS_UTILITY_FLATTEN_EITHER_HPP
#define NMTOOLS_UTILITY_FLATTEN_EITHER_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/get_if.hpp"
#include "nmtools/utility/forward.hpp"
#include "nmtools/utility/get.hpp"

namespace nmtools
{
    struct flatten_either_t {};
} // namespace nmtools


namespace nmtools::detail
{
    // to allow marking unreachable get_flat_either
    template <auto I, typename T>
    struct GET_FLAT_EITHER_UNREACHABLE : meta::detail::fail_t {};

    template <size_t I, typename either_t>
    constexpr auto get_flat_either(either_t&& either)
    {
        using no_cvref_either_t = meta::remove_cvref_t<either_t>;
        using left_t  = meta::get_either_left_t<no_cvref_either_t>;
        using right_t = meta::get_either_right_t<no_cvref_either_t>;

        [[maybe_unused]] auto l_ptr = get_if<left_t>(&nmtools::forward<either_t>(either));
        [[maybe_unused]] auto r_ptr = get_if<right_t>(&nmtools::forward<either_t>(either));

        if constexpr (meta::is_either_v<left_t> && meta::is_either_v<right_t>) {
            using left_types_t  = meta::resolve_optype_t<flatten_either_t,left_t>;
            using right_types_t = meta::resolve_optype_t<flatten_either_t,right_t>;
            [[maybe_unused]] constexpr auto n_left  = meta::len_v<left_types_t>;
            [[maybe_unused]] constexpr auto n_right = meta::len_v<right_types_t>;
            if constexpr (I < n_left) {
                using l_result_t = decltype(get_flat_either<I>(*l_ptr));
                if (l_ptr) {
                    return get_flat_either<I>(*l_ptr);
                } else {
                    return static_cast<l_result_t>(nullptr);
                }
            } else if constexpr (I >= n_left && I < n_right) {
                constexpr auto J = I - n_left;
                using r_result_t = decltype(get_flat_either<J>(*r_ptr));
                if (r_ptr) {
                    return get_flat_either<J>(*r_ptr);
                } else {
                    return static_cast<r_result_t>(nullptr);
                }
            } else {
                return GET_FLAT_EITHER_UNREACHABLE<I,either_t>{};
            }
        } else if constexpr (meta::is_either_v<left_t>) {
            // we know right_t is not either,
            // so we know left is starting from 0,
            // but we do not know how deep is the left,

            using left_types_t  = meta::resolve_optype_t<flatten_either_t,left_t>;
            [[maybe_unused]] constexpr auto n_left  = meta::len_v<left_types_t>;
            if constexpr (I < n_left) {
                auto l_ptr = get_if<left_t>(&nmtools::forward<either_t>(either));
                using result_t = decltype(get_flat_either<I>(*l_ptr));
                if (l_ptr) {
                    return get_flat_either<I>(*l_ptr);
                } else {
                    return static_cast<result_t>(nullptr);
                }
            } else {
                return get_if<right_t>(&nmtools::forward<either_t>(either));
            }
        } else if constexpr (meta::is_either_v<right_t>) {
            // we know left_t is not either,
            // so index at right start from 1
            if constexpr (I==0) {
                return get_if<left_t>(&nmtools::forward<either_t>(either));
            } else {
                auto r_ptr = get_if<right_t>(&nmtools::forward<either_t>(either));

                using result_t = decltype(get_flat_either<I-1>(*r_ptr));
                // assume reachable
                if (r_ptr) {
                    return get_flat_either<I-1>(*r_ptr);
                } else {
                    return static_cast<result_t>(nullptr);
                }
            }
        } else {
            if constexpr (I==0) {
                return l_ptr;
            } else if constexpr (I==1) {
                return r_ptr;
            } else {
                return GET_FLAT_EITHER_UNREACHABLE<I,either_t>{};
            }
        }
    }
} // namespace nmtools::detail

namespace nmtools
{
    /**
     * @brief Flatten a possibly-nested either type to flat tuple of pointers.
     * 
     * @tparam either_t 
     * @param either 
     * @return constexpr auto 
     */
    template <typename either_t>
    constexpr auto flatten_either(either_t&& either)
    {
        using result_t = meta::resolve_optype_t<flatten_either_t,either_t>;

        auto res = result_t {};

        constexpr auto N = meta::len_v<result_t>;
        meta::template_for<N>([&](auto index){
            constexpr auto I = decltype(index)::value;
            // NOTE: using nmtools::forward to avoid ambiguous call
            // TODO: consider to look more on cpo to prevent ambiguous call
            auto ptr = detail::get_flat_either<I>(nmtools::forward<either_t>(either));
            // since this is like variant type,
            // should only have one valid pointer
            if (ptr) {
                using res_t = meta::at_t<result_t,I>;
                // NOTE: quick workaround for invalid conversion from const* to *, especially when using utl
                // TODO: fix, remove const_cast
                get<I>(res) = const_cast<res_t>(ptr);
            }
        });

        return res;
    } // flatten_either
} // namespace nmtools

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct FLATTEN_EITHER_UNSUPPORTED : detail::fail_t {};
    } // namespace error
    
    template <typename either_t>
    struct resolve_optype<void,flatten_either_t,either_t>
    {
        static constexpr auto vtype = [](){
            using no_cvref_either_t = remove_cvref_t<either_t>;
            if constexpr (is_either_v<no_cvref_either_t>) {
                using left_t  = get_either_left_t<no_cvref_either_t>;
                using right_t = get_either_right_t<no_cvref_either_t>;

                if constexpr (is_either_v<left_t> && is_either_v<right_t>) {
                    using flatten_left_t  = resolve_optype_t<flatten_either_t,left_t>;
                    using flatten_right_t = resolve_optype_t<flatten_either_t,right_t>;
                    constexpr auto N = len_v<flatten_right_t>;
                    return template_reduce<N>([](auto init, auto index){
                        constexpr auto i = decltype(index)::value;
                        using init_t = type_t<decltype(init)>;
                        using type_i = at_t<flatten_right_t,i>;
                        using type   = append_type_t<init_t,type_i>;
                        return as_value_v<type>;
                    }, as_value_v<flatten_left_t>);
                } else if constexpr (is_either_v<left_t>) {
                    using flatten_left_t = resolve_optype_t<flatten_either_t,left_t>;
                    using type = append_type_t<flatten_left_t,right_t*>;
                    return as_value_v<type>;
                } else if constexpr (is_either_v<right_t>) {
                    using flatten_left_t  = nmtools_tuple<left_t*>;
                    using flatten_right_t = resolve_optype_t<flatten_either_t,right_t>;
                    constexpr auto N = len_v<flatten_right_t>;
                    return template_reduce<N>([](auto init, auto index){
                        constexpr auto i = decltype(index)::value;
                        using init_t = type_t<decltype(init)>;
                        using type_i = at_t<flatten_right_t,i>;
                        using type   = append_type_t<init_t,type_i>;
                        return as_value_v<type>;
                    }, as_value_v<flatten_left_t>);
                } else {
                    using type = nmtools_tuple<left_t*,right_t*>;
                    return as_value_v<type>;
                }
            } else {
                using type = error::FLATTEN_EITHER_UNSUPPORTED<either_t>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
    
} // namespace nmtools::meta


#endif // NMTOOLS_UTILITY_FLATTEN_EITHER_HPP