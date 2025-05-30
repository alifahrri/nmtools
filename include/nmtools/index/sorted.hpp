#ifndef NMTOOLS_INDEX_SORTED_HPP
#define NMTOOLS_INDEX_SORTED_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/index/argsort.hpp"

namespace nmtools::index
{
    // TODO: move to "tag" namespace
    struct sorted_t {};

    template <typename indices_t>
    constexpr auto sorted(const indices_t& indices)
    {
        if constexpr (meta::is_maybe_v<indices_t>) {
            using result_t = decltype(sorted(unwrap(indices)));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(indices)
                ? return_t{sorted(unwrap(indices))}
                : return_t{meta::Nothing}
            );
        } else {
            using result_t = meta::resolve_optype_t<sorted_t,indices_t>;

            auto result = result_t {};

            if constexpr (!meta::is_constant_index_array_v<result_t>
                && !meta::is_fail_v<result_t>
            ) {
                // TODO: propagate errors
                auto sort_idx = index::argsort(indices);

                auto size = len(indices);

                if constexpr (meta::is_resizable_v<result_t>) {
                    result.resize(size);
                }

                for (nm_size_t i=0; i<(nm_size_t)size; i++) {
                    at(result,i) = at(indices,at(sort_idx,i));
                }
            }

            return result;
        }
    } // sorted
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct SORTED_UNSUPPORTED : detail::fail_t {};
    }

    template <typename indices_t>
    struct resolve_optype<
        void, index::sorted_t, indices_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<indices_t>) {
                using type = error::SORTED_UNSUPPORTED<indices_t>;
                return as_value_v<type>;
            } else {
                // TODO: handle constant index array to compute at compile-time
                constexpr auto SIZE = len_v<indices_t>;
                [[maybe_unused]]
                constexpr auto B_SIZE = bounded_size_v<indices_t>;

                using index_t = get_element_type_t<indices_t>;
                if constexpr (SIZE > 0) {
                    using type = nmtools_array<index_t,SIZE>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(B_SIZE)>) {
                    using type = nmtools_static_vector<index_t,B_SIZE>;
                    return as_value_v<type>;
                } else {
                    // TODO: use small vector
                    using type = nmtools_list<index_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // index::sorted_t
} // namespace nmtools::meta

#endif // NMTOOLS_INDEX_SORTED_HPP