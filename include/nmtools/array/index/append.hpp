#ifndef NMTOOLS_ARRAY_INDEX_APPEND_HPP
#define NMTOOLS_ARRAY_INDEX_APPEND_HPP

#include "nmtools/meta.hpp"

namespace nmtools::index
{
    struct append_t {};

    template <typename indices_t, typename index_t>
    constexpr auto append(const indices_t& indices, index_t index)
    {
        using result_t = meta::resolve_optype_t<append_t,indices_t,index_t>;

        auto result = result_t {};

        if constexpr (!meta::is_constant_index_array_v<result_t>
            && !meta::is_fail_v<result_t>
        ) {
            auto n = len(indices);
            if constexpr (meta::is_resizable_v<result_t>) {
                result.resize(n+1);
            }
            [[maybe_unused]]
            auto f = [&](const auto& indices){
                auto n = len(indices);
                for (nm_size_t i=0; i<(nm_size_t)n; i++) {
                    at(result,i) = at(indices,i);
                }
            };
            constexpr auto B_SIZE = meta::bounded_size_v<indices_t>;
            // avoid calling at(indices,i) when indices is tuple<>
            if constexpr (meta::is_fail_v<decltype(B_SIZE)>) {
                f(indices);
            } else if constexpr (B_SIZE > 0) {
                f(indices);
            }
            at(result,n) = index;
        }

        return result;
    }
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct APPEND_UNSUPPORTED : detail::fail_t {};
    }

    template <typename indices_t, typename index_t>
    struct resolve_optype<
        void, index::append_t, indices_t, index_t
    > {
        static constexpr auto vtype = [](){
            [[maybe_unused]]
            constexpr auto DIM = len_v<indices_t>;
            [[maybe_unused]]
            constexpr auto B_DIM = bounded_size_v<indices_t>;
            if constexpr (!is_index_array_v<indices_t>
                || !is_index_v<index_t>
            ) {
                using type = error::APPEND_UNSUPPORTED<indices_t,index_t>;
                return as_value_v<type>;
            } else if constexpr (
                is_constant_index_array_v<indices_t>
                && is_constant_index_v<index_t>
            ) {
                constexpr auto indices = to_value_v<indices_t>;
                constexpr auto idx     = to_value_v<index_t>;
                constexpr auto result  = index::append(indices,idx);
                using nmtools::at, nmtools::len;
                return template_reduce<len(result)>([&](auto init, auto index){
                    using init_type   = type_t<decltype(init)>;
                    using result_type = append_type_t<init_type,ct<at(result,index)>>;
                    return as_value_v<result_type>;
                }, as_value_v<nmtools_tuple<>>);
            } else if constexpr (DIM > 0) {
                using element_t = get_index_element_type_t<indices_t>;
                using type = nmtools_array<element_t,DIM+1>;
                return as_value_v<type>;
            } else if constexpr (!is_fail_v<decltype(B_DIM)>) {
                if constexpr (B_DIM == 0) {
                    using type = nmtools_array<nm_index_t,1>;
                    return as_value_v<type>;
                } else {
                    using element_t = get_index_element_type_t<indices_t>;
                    using type = nmtools_static_vector<element_t,B_DIM>;
                    return as_value_v<type>;
                }
            } else {
                using element_t = get_index_element_type_t<indices_t>;
                // TODO: support small_vector
                using type = nmtools_list<element_t>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_APPEND_HPP