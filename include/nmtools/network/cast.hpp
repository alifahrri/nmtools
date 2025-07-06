#ifndef NMTOOLS_NETWORK_CAST_HPP
#define NMTOOLS_NETWORK_CAST_HPP

#include "nmtools/meta.hpp"

namespace nmtools::network::kind
{
    // tag for outer/inner container of adjacency_list
    struct static_vec_t {};
    struct vector_t {};
    struct array_t {};

    inline constexpr auto static_vec = static_vec_t {};
    inline constexpr auto vector     = vector_t {};
    inline constexpr auto array      = array_t {};
}

namespace nmtools::tag
{
    struct network_cast_t {};
}

namespace nmtools::network
{
    template <typename result_t, typename adjacency_list_t>
    constexpr auto cast(const adjacency_list_t& adj_list)
    {
        auto result = result_t {};

        if constexpr (!meta::is_fail_v<result_t>) {
            [[maybe_unused]]
            auto num_nodes = len(adj_list);

            if constexpr (meta::is_resizable_v<result_t>) {
                result.resize(num_nodes);
            }

            auto inner_loop = [&](auto I){
                const auto& successors = at(adj_list,I);
                auto& dst_successors = at(result,I);

                using successors_t = meta::remove_cvref_t<decltype(successors)>;
                using dst_successors_t = meta::remove_cvref_t<decltype(dst_successors)>;
                static_assert( meta::is_index_array_v<successors_t> );
                static_assert( meta::is_index_array_v<dst_successors_t> );
                static_assert( meta::is_resizable_v<dst_successors_t> );

                [[maybe_unused]]
                auto n_successors = len(successors);
                if constexpr (meta::is_resizable_v<decltype(dst_successors)>) {
                    dst_successors.resize(n_successors);
                }

                if constexpr (meta::is_tuple_v<successors_t>) {
                    constexpr auto N_SUCCESSORS = meta::len_v<successors_t>;
                    meta::template_for<N_SUCCESSORS>([&](auto J){
                        at(dst_successors,J) = at(successors,J);
                    });
                } else {
                    for (nm_size_t i=0; i<(nm_size_t)n_successors; i++) {
                        at(dst_successors,i) = at(successors,i);
                    }
                }
            };

            if constexpr (meta::is_tuple_v<adjacency_list_t>) {
                constexpr auto NUM_NODES = meta::len_v<adjacency_list_t>;
                meta::template_for<NUM_NODES>([&](auto I){
                    inner_loop(I);
                });
            } else {
                for (nm_size_t i=0; i<(nm_size_t)num_nodes; i++) {
                    inner_loop(i);
                }
            }
        }

        return result;
    }

    template <typename adjacency_list_t, typename outer_kind_t, typename inner_kind_t>
    constexpr auto cast(const adjacency_list_t& adj_list, outer_kind_t, inner_kind_t)
    {
        if constexpr (meta::is_maybe_v<adjacency_list_t>) {
            using result_t = decltype(cast(unwrap(adj_list),outer_kind_t{},inner_kind_t{}));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(adj_list)
                ? return_t{cast(unwrap(adj_list),outer_kind_t{},inner_kind_t{})}
                : return_t{meta::Nothing}
            );
        } else {
            using result_t = meta::resolve_optype_t<tag::network_cast_t,adjacency_list_t,outer_kind_t,inner_kind_t>;

            return cast<result_t>(adj_list);
        }
    }

    template <typename dst_node_ids_t, typename src_node_ids_t>
    constexpr auto cast_node_ids(const src_node_ids_t& src_node_ids, meta::as_value<dst_node_ids_t> = meta::as_value<dst_node_ids_t>{})
    {
        auto dst_node_ids = dst_node_ids_t{};
        auto num_nodes = len(src_node_ids);
        if constexpr (meta::is_resizable_v<dst_node_ids_t>) {
            dst_node_ids.resize(num_nodes);
        }
        // TODO: handle tuple
        for (nm_size_t i=0; i<(nm_size_t)num_nodes; i++) {
            at(dst_node_ids,i) = at(src_node_ids,i);
        }
        return dst_node_ids;
    }

    template <typename dst_node_attributes_t, typename src_node_attributes_t>
    constexpr auto cast_node_attributes(const src_node_attributes_t& src_node_attributes)
    {
        auto dst_node_attributes = dst_node_attributes_t {};

        auto num_nodes = len(src_node_attributes);
        if constexpr (meta::is_resizable_v<dst_node_attributes_t>) {
            dst_node_attributes.resize(num_nodes);
        }
        // TODO: handle tuple
        for (nm_size_t i=0; i<(nm_size_t)num_nodes; i++) {
            at(dst_node_attributes,i) = at(src_node_attributes,i);
        }
        return dst_node_attributes;
    }
}

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct NETWORK_CAST_UNSUPPORTED : detail::fail_t {};
    }

    template <typename adjacency_list_t, typename outer_kind_t, typename inner_kind_t>
    struct resolve_optype<
        void, tag::network_cast_t, adjacency_list_t, outer_kind_t, inner_kind_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!(is_adjacency_list_v<adjacency_list_t> || is_tuple_v<adjacency_list_t>)
            ) {
                using type = error::NETWORK_CAST_UNSUPPORTED<adjacency_list_t,outer_kind_t,inner_kind_t>;
                return as_value_v<type>;
            } else {
                constexpr auto NUM_NODES = len_v<adjacency_list_t>;
                constexpr auto MAX_NEIGHBOURS = [&](){
                    if constexpr (NUM_NODES >= 0) {
                        return template_reduce<NUM_NODES>([](auto init, auto index){
                            constexpr auto I = decltype(index)::value;
                            using type_i = at_t<adjacency_list_t,I>;
                            // TODO: fix bounded_size_v for array<T,0>
                            // constexpr auto B_SIZE = bounded_size_v<remove_cvref_t<type_i>>;
                            constexpr auto B_SIZE = len_v<remove_cvref_t<type_i>>;
                            if constexpr (!is_fail_v<decltype(B_SIZE)>) {
                                auto b_size = nm_index_t(B_SIZE);
                                return init < 0
                                    ? init
                                    : nm_index_t(b_size > init ? b_size : init)
                                ;
                            } else {
                                // if has no bounded_size then it is runtime size, use -1 to indicate
                                return -1;
                            }
                        },nm_index_t(0));
                    } else {
                        return -1;
                    }
                }();

                // TODO: deduce index type of inner container
                // e.g. return uint8_t if all of them are uint8_t and so on
                using index_t = nm_index_t;

                auto inner_vtype = [&](){
                    // TODO; support array, and also make sure all nodes have the same number of neighbours
                    if constexpr (is_same_v<inner_kind_t,network::kind::static_vec_t>
                        || is_same_v<inner_kind_t,network::kind::array_t>
                    ) {
                        using type = nmtools_static_vector<index_t,MAX_NEIGHBOURS>;
                        return as_value_v<type>;
                    } else /* if constexpr (is_same_v<inner_kind_t,network::kind::vector_t>) */ {
                        using type = nmtools_list<index_t>;
                        return as_value_v<type>;
                    }
                    // TODO: support small vector
                }();
                using inner_t = type_t<decltype(inner_vtype)>;

                auto outer_vtype = [&](){
                    if constexpr (is_same_v<outer_kind_t,network::kind::array_t>) {
                        using type = nmtools_array<inner_t,NUM_NODES>;
                        return as_value_v<type>;
                    } else if constexpr (is_same_v<outer_kind_t,network::kind::static_vec_t>) {
                        using type = nmtools_static_vector<inner_t,NUM_NODES>;
                        return as_value_v<type>;
                    } else {
                        using type = nmtools_list<inner_t>;
                        return as_value_v<type>;
                    }
                    // TODO: support small vector
                }();

                using type = type_t<decltype(outer_vtype)>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_NETWORK_CAST_HPP