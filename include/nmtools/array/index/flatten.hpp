#ifndef NMTOOLS_ARRAY_INDEX_FLATTEN_HPP
#define NMTOOLS_ARRAY_INDEX_FLATTEN_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/shape.hpp"

namespace nmtools::index
{
    using namespace literals;

    struct shape_flatten_t {};

    template <typename shape_t, typename fixed_size_t>
    constexpr auto shape_flatten(const shape_t& shape, const fixed_size_t)
    {
        using result_t = meta::resolve_optype_t<shape_flatten_t,shape_t,fixed_size_t>;

        using namespace literals;

        auto result = result_t {};
        if constexpr (!meta::is_constant_index_array_v<result_t>) {
            auto n = len(shape);
            // assume result is single size
            at(result,0_ct) = 1;
            for (size_t i=0; i<(size_t)n; i++) {
                at(result,0_ct) = at(result,0_ct) * at(shape,i);
            }
        }
        return result;
    } // shape_flatten
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct SHAPE_FLATTEN_UNSUPPORTED : detail::fail_t {};
    }

    template <typename shape_t, typename fixed_size_t>
    struct resolve_optype<
        void, index::shape_flatten_t, shape_t, fixed_size_t
    >
    {
        static constexpr auto vtype = [](){
            if constexpr (is_constant_index_v<fixed_size_t>) {
                using type = nmtools_tuple<ct<fixed_size_t::value>>;
                return as_value_v<type>;
            } else if constexpr (
                is_constant_index_array_v<shape_t>
                || is_clipped_index_array_v<shape_t>
            ) {
                constexpr auto shape = to_value_v<shape_t>;
                constexpr auto result = index::shape_flatten(shape,fixed_size_t{});
                using nmtools::len, nmtools::at;
                return template_reduce<len(result)>([&](auto init, auto index){
                    using init_t = type_t<decltype(init)>;
                    constexpr auto I = at(result,index);
                    if constexpr (is_constant_index_array_v<shape_t>) {
                        using type = append_type_t<init_t,ct<I>>;
                        return as_value_v<type>;
                    } else {
                        using type = append_type_t<init_t,clipped_size_t<I>>;
                        return as_value_v<type>;
                    }
                }, as_value_v<nmtools_tuple<>>);
            } else if constexpr (is_none_v<shape_t>) {
                using type = nmtools_tuple<ct<1ul>>;
                return as_value_v<type>;
            } else if constexpr (is_index_array_v<shape_t>) {
                // flatten is strictly 1D
                using type = nmtools_array<size_t,1>;
                return as_value_v<type>;
            } else {
                return as_value_v<error::SHAPE_FLATTEN_UNSUPPORTED<shape_t>>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_FLATTEN_HPP