#ifndef NMTOOLS_NETWORK_OUT_DEGREE_HPP
#define NMTOOLS_NETWORK_OUT_DEGREE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"

namespace nmtools::tag
{
    struct out_degree_t {};
}

namespace nmtools::network
{
    template <typename adjacency_list_t>
    constexpr auto out_degree(const adjacency_list_t& list)
    {
        if constexpr (meta::is_maybe_v<adjacency_list_t>) {
            using result_t = decltype(out_degree(unwrap(list)));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(list)
                ? return_t{out_degree(unwrap(list))}
                : return_t{meta::Nothing}
            );
        } else {
            using result_t = meta::resolve_optype_t<tag::out_degree_t,adjacency_list_t>;

            auto result = result_t {};

            if constexpr (!meta::is_constant_index_array_v<result_t>
                && !meta::is_fail_v<result_t>
            ) {
                [[maybe_unused]]
                auto num_nodes = len(list);
                if constexpr (meta::is_resizable_v<result_t>) {
                    result.resize(num_nodes);
                }

                if constexpr (meta::is_tuple_v<adjacency_list_t>) {
                    constexpr auto NUM_NODES = meta::len_v<adjacency_list_t>;
                    meta::template_for<NUM_NODES>([&](auto I){
                        at(result,I) = nmtools::size(at(list,I));
                    });
                } else {
                    for (nm_size_t i=0; i<(nm_size_t)num_nodes; i++) {
                        at(result,i) = nmtools::size(at(list,i));
                    }
                }
            }

            return result;
        }
    }
} // namespace nmtools::network

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct OUT_DEGREE_UNSUPPORTED : detail::fail_t {};
    }

    template <typename adjacency_list_t>
    struct resolve_optype<
        void, tag::out_degree_t, adjacency_list_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_adjacency_list_v<adjacency_list_t>) {
                using type = error::OUT_DEGREE_UNSUPPORTED<adjacency_list_t>;
                return as_value_v<type>;
            } else {
                constexpr auto NUM_NODES = len_v<adjacency_list_t>;
                if constexpr (NUM_NODES > 0) {
                    using type = nmtools_array<nm_size_t,NUM_NODES>;
                    return as_value_v<type>;
                } else {
                    // TODO: use small vector
                    using type = nmtools_list<nm_size_t>;
                    return as_value_v<type>;
                }
            }
        }();

        using type = type_t<decltype(vtype)>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_NETWORK_OUT_DEGREE_HPP