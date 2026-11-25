#ifndef NMTOOLS_NETWORK_IS_UNDIRECTED_HPP
#define NMTOOLS_NETWORK_IS_UNDIRECTED_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/index/contains.hpp"

namespace nmtools::tag
{
    struct is_undirected_t {};
}

namespace nmtools::network
{
    template <typename adjacency_list_t>
    constexpr auto is_undirected(const adjacency_list_t& adj_list)
    {
        if constexpr (is_maybe_v<adjacency_list_t>) {
            using result_t = decltype(is_undirected(unwrap(adj_list)));
            using return_t = conditional_t<is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(adj_list)
                ? return_t{is_undirected(unwrap(adj_list))}
                : return_t{meta::Nothing}
            );
        } else {
            using result_t = resolve_optype_t<tag::is_undirected_t,adjacency_list_t>;

            auto result = result_t {};

            if constexpr (!is_fail_v<result_t>
                && !is_constant_index_v<result_t>
            ) {
                // demote constant structures so they can be indexed at runtime
                [[maybe_unused]]
                decltype(auto) adj = [&]() -> decltype(auto) {
                    if constexpr (is_constant_adjacency_list_v<adjacency_list_t>) {
                        return to_value_v<adjacency_list_t>;
                    } else {
                        return (adj_list);
                    }
                }();

                result = false;
                auto n = len(adj_list);

                result = true;
                for (nm_size_t i=0; (i<(nm_size_t)n) && result; i++) {
                    auto neighbors = at(adj,i);
                    for (nm_size_t j=0; (j<(nm_size_t)len(neighbors)) && result; j++) {
                        auto v = at(neighbors,j);
                        if ((nm_size_t)v >= (nm_size_t)n) {
                            result = false;
                        } else if (!index::contains(at(adj,v),i)) {
                            result = false;
                        }
                    }
                }
            }

            return result;
        }
    } // is_undirected
} // namespace nmtools::network

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct IS_UNDIRECTED_UNSUPPORTED : detail::fail_t {};
    }

    template <typename adjacency_list_t>
    struct resolve_optype<
        void, tag::is_undirected_t, adjacency_list_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_adjacency_list_v<adjacency_list_t>) {
                using type = error::IS_UNDIRECTED_UNSUPPORTED<adjacency_list_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_adjacency_list_v<adjacency_list_t>) {
                constexpr auto adj_list = to_value_v<adjacency_list_t>;
                constexpr auto result = network::is_undirected(adj_list);
                using type = ct<unwrap(result)>;
                return as_value_v<type>;
            } else {
                using type = nm_bool_t;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // tag::is_undirected_t
} // namespace nmtools::meta

#endif // NMTOOLS_NETWORK_IS_UNDIRECTED_HPP
