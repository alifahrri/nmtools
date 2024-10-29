#ifndef NMTOOLS_ARRAY_INDEX_RANGE_HPP
#define NMTOOLS_ARRAY_INDEX_RANGE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/shape.hpp"

namespace nmtools::index
{
    struct range_t {};

    template <typename start_t, typename stop_t, typename step_t=meta::ct<1>>
    constexpr auto range([[maybe_unused]] start_t start
        , [[maybe_unused]] stop_t stop
        , [[maybe_unused]] step_t step=step_t{}
    ) {
        using result_t = meta::resolve_optype_t<range_t,start_t,stop_t,step_t>;

        auto result = result_t {};

        if constexpr (!meta::is_fail_v<result_t>
            && !meta::is_constant_index_array_v<result_t>
        ) {
            auto n = (stop - start) / step;
            if constexpr (meta::is_resizable_v<result_t>) {
                result.resize(n);
            }

            for (nm_size_t i=0; i<(nm_size_t)n; i++) {
                at(result,i) = i * step;
            }
        }

        return result;
    } // range

    template <typename stop_t>
    constexpr auto range(stop_t stop)
    {
        return range(meta::ct_v<0>,stop,meta::ct_v<1>);
    }
} // nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct RANGE_UNSUPPORTED : detail::fail_t {};
    }

    template <typename start_t, typename stop_t, typename step_t>
    struct resolve_optype<
        void, index::range_t, start_t, stop_t, step_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (
                !is_index_v<start_t>
                || !is_index_v<stop_t>
                || !is_index_v<step_t>
            ) {
                using type = error::RANGE_UNSUPPORTED<start_t,stop_t,step_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_index_v<start_t>
                && is_constant_index_v<stop_t>
                && is_constant_index_v<step_t>
            ) {
                constexpr auto start = to_value_v<start_t>;
                constexpr auto stop  = to_value_v<stop_t>;
                constexpr auto step  = to_value_v<step_t>;
                constexpr auto start_cl = clipped_int64_t<int64_t(start > 0 ? start : 1)>(start);
                constexpr auto stop_cl  = clipped_int64_t<(int64_t)stop>(stop);
                constexpr auto step_cl  = clipped_int64_t<(int64_t)step>(step);
                constexpr auto result   = index::range(start_cl,stop_cl,step_cl);
                using nmtools::at, nmtools::len;
                return template_reduce<len(result)>([&](auto init, auto I){
                    using init_t = type_t<decltype(init)>;
                    using type = append_type_t<init_t,ct<at(result,I)>>;
                    return as_value_v<type>;
                }, as_value_v<nmtools_tuple<>>);
            } else {
                constexpr auto max_dim = max_value_v<stop_t>;
                if constexpr (!is_fail_v<decltype(max_dim)>) {
                    using type = nmtools_static_vector<nm_size_t,max_dim>;
                    return as_value_v<type>;
                } else {
                    // TODO: small vector optimization
                    using type = nmtools_list<nm_size_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // index::range_t
} // nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_RANGE_HPP