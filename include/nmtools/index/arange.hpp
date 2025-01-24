#ifndef NMTOOLS_ARRAY_INDEX_ARANGE_HPP
#define NMTOOLS_ARRAY_INDEX_ARANGE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/at.hpp"
#include "nmtools/utility/shape.hpp"

namespace nmtools::index
{
    // workaround for clang
    // since gcc has constexpr ceil while clang doesn't :|
    constexpr size_t ceil_(float num)
    {
        return (static_cast<float>(static_cast<size_t>(num)) == num)
            ? static_cast<size_t>(num)
            : static_cast<size_t>(num) + ((num > 0) ? 1 : 0);
    }

    struct arange_shape_t {};

    template <typename start_t, typename stop_t, typename step_t>
    constexpr auto arange_shape([[maybe_unused]] start_t start, [[maybe_unused]] stop_t stop, [[maybe_unused]] step_t step)
    {
        using return_t = meta::resolve_optype_t<arange_shape_t,start_t,stop_t,step_t>;
        auto ret = return_t {};
        if constexpr (!meta::is_constant_index_array_v<return_t>) {
            // TODO: use index_type instead of size_t
            size_t d = ceil_(float(stop - start) / step);
            at(ret,0) = d;
        }
        return ret;
    } // arange_shape
}

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct ARANGE_SHAPE_UNSUPPORTED : detail::fail_t {};
    }

    template <typename start_t, typename stop_t, typename step_t>
    struct resolve_optype<
        void, index::arange_shape_t, start_t, stop_t, step_t
    >
    {
        static constexpr auto vtype = [](){
            if constexpr (
                is_integral_constant_v<start_t>
                && is_integral_constant_v<stop_t>
                && (is_integral_constant_v<step_t> || is_none_v<step_t>)
            ) {
                constexpr auto start = to_value_v<start_t>;
                constexpr auto stop  = to_value_v<stop_t>;
                constexpr auto step  = [](){
                    if constexpr (is_none_v<step_t>) {
                        return 1;
                    } else {
                        return to_value_v<step_t>;
                    }
                }();
                constexpr auto shape = index::arange_shape(start,stop,step);
                // arange is strictly 1D
                using type = nmtools_tuple<ct<nmtools::at(shape,0)>>;
                return as_value_v<type>;
            } else if constexpr (
                is_index_v<start_t>
                && is_index_v<stop_t>
                && (is_num_v<step_t> || is_none_v<step_t>)
            ) {
                using type = nmtools_array<nm_size_t,1>;
                return as_value_v<type>;
            } else {
                using type = error::ARANGE_SHAPE_UNSUPPORTED<start_t,stop_t,step_t>;
                return as_value_v<type>;
            }
        }();
        
        using type = type_t<decltype(vtype)>;
    };
}

#endif // NMTOOLS_ARRAY_INDEX_ARANGE_HPP