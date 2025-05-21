#ifndef NMTOOLS_META_BITS_ARRAY_BOUNDED_NUM_NODES_HPP
#define NMTOOLS_META_BITS_ARRAY_BOUNDED_NUM_NODES_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/is_adjacency_list.hpp"
#include "nmtools/meta/bits/array/fixed_num_nodes.hpp"

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct BOUNDED_NUM_NODES_UNSUPPORTED : detail::fail_t {};
    }

    template <typename T, typename=void>
    struct bounded_num_nodes
    {
        static constexpr auto value = [](){
            using error_type [[maybe_unused]] = error::BOUNDED_NUM_NODES_UNSUPPORTED<T>;
            if constexpr (!is_adjacency_list_v<T>) {
                using type = error_type;
                return type{};
            } else {
                constexpr auto NUM_NODES = fixed_num_nodes_v<T>;
                [[maybe_unused]]
                constexpr auto B_NUM_NODES = bounded_size_v<T>;
                if constexpr (!is_fail_v<decltype(NUM_NODES)>) {
                    return NUM_NODES;
                } else if constexpr (!is_fail_v<decltype(B_NUM_NODES)>) {
                    return B_NUM_NODES;
                } else {
                    using type = error_type;
                    return type{};
                }
            }
        }();
    };

    template <typename T>
    struct bounded_num_nodes<const T> : bounded_num_nodes<T> {};

    template <typename T>
    struct bounded_num_nodes<T&> : bounded_num_nodes<T> {};

    template <typename T>
    constexpr inline auto bounded_num_nodes_v = bounded_num_nodes<T>::value;
}

#endif // NMTOOLS_META_BITS_ARRAY_BOUNDED_NUM_NODES_HPP