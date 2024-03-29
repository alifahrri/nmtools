#ifndef NMTOOLS_UTILITY_TUPLE_SLICE_HPP
#define NMTOOLS_UTILITY_TUPLE_SLICE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/tuple_cat.hpp"

namespace nmtools::utility
{
    template <typename start_t, typename stop_t=none_t, template<typename...>typename tuple, typename...args_t>
    constexpr auto tuple_slice(const tuple<args_t...>& tp, start_t=start_t{}, stop_t=stop_t{})
    {
        constexpr auto N = sizeof...(args_t);
        constexpr auto START = [](){
            if constexpr (is_none_v<start_t>) {
                return 0;
            } else {
                return start_t::value;
            }
        }();
        constexpr auto STOP = [](){
            if constexpr (is_none_v<stop_t>) {
                return sizeof...(args_t);
            } else {
                constexpr auto value = stop_t::value;
                if constexpr (value < 0) {
                    return sizeof...(args_t) + value;
                } else {
                    return value;
                }
            }
        }();
        return meta::template_reduce<N>([&](auto init, auto index){
            constexpr auto i = decltype(index)::value;
            if constexpr ((i >= START) && (i<STOP)) {
                auto& element = nmtools::get<i>(tp);
                using element_t = decltype(element);
                // TODO: proper fix
                if constexpr (meta::is_bounded_array_v<element_t>) {
                    return tuple_append<element_t&>(init,element);
                } else {
                    return tuple_append(init,element);
                }
            } else {
                return init;
            }
        }, nmtools_tuple{});
    } // tuple_slice
} // namespace nmtools::utility

#endif // NMTOOLS_UTILITY_TUPLE_SLICE_HPP