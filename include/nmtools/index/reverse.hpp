#ifndef NMTOOLS_ARRAY_INDEX_REVERSE_HPP
#define NMTOOLS_ARRAY_INDEX_REVERSE_HPP

#include "nmtools/utility/at.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/utility/has_value.hpp"
#include "nmtools/utility/unwrap.hpp"
#include "nmtools/meta.hpp"

namespace nmtools::index
{
    // tag to resolve index reverse type
    struct reverse_t {};

    /**
     * @brief entrypoint for reversing array (of indices)
     * 
     * @tparam indices_t array of same type
     * @param indices 
     * @return constexpr auto 
     */
    template <typename indices_t>
    constexpr auto reverse(const indices_t& indices)
    {
        using result_t = resolve_optype_t<reverse_t,indices_t>;
        auto ret = result_t{};
        // assume already reversed at meta::resolve if result_t is constant
        if constexpr (!is_constant_index_array_v<result_t>) {
            [[maybe_unused]] auto n = (nm_size_t)len(indices);
            if constexpr (is_resizable_v<result_t>) {
                ret.resize(n);
            }
            constexpr auto DIM = len_v<result_t>;
            if constexpr (DIM > 0) {
                template_for<DIM>([&](auto index){
                    if constexpr (!is_constant_index_v<decltype(at(ret,index))>) {
                        constexpr auto I = decltype(index)::value;
                        auto idx = at(indices,ct_v<DIM-1-I>);
                        if (has_value(idx)) {
                            at(ret,index) = idx;
                        }
                    }
                });
            } else {
                for (nm_size_t i=0; i<n; i++) {
                    auto idx = at(indices,n-1-i);
                    if (has_value(idx)) {
                        at(ret,i) = idx;
                    }
                }
            }
        }
        return ret;
    } // reverse
} // namespace nmtools

namespace nmtools::meta
{

    namespace error
    {
        template <typename...>
        struct INDEX_REVERSE_UNSUPPORTED : detail::fail_t {};
    }

    template <typename indices_t>
    struct resolve_optype<
        void, index::reverse_t, indices_t
    >
    {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<indices_t>) {
                using type = error::INDEX_REVERSE_UNSUPPORTED<indices_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_index_array_v<indices_t>
                || is_mixed_index_array_v<indices_t>
            ) {
                constexpr auto indices = to_value_v<indices_t>;
                // using element_t [[maybe_unused]] = get_index_element_type_t<decltype(indices)>;
                using element_t = nm_index_t;
                constexpr auto reversed = index::reverse(indices);
                // convert back to type
                using nmtools::len, nmtools::has_value, nmtools::at, nmtools::unwrap;
                return template_reduce<len(reversed)>([&](auto init, auto index){
                    using init_t = type_t<decltype(init)>;
                    constexpr auto I = decltype(index)::value;
                    constexpr auto idx = at(reversed,I);
                    if constexpr (has_value(idx)) {
                        using index_t = ct<unwrap(idx)>;
                        using result_t = append_type_t<init_t,index_t>;
                        return as_value_v<result_t>;
                    } else {
                        using index_t = element_t;
                        using result_t = append_type_t<init_t,index_t>;
                        return as_value_v<result_t>;
                    }
                }, as_value_v<nmtools_tuple<>>);
            } else {
                constexpr auto DIM = len_v<indices_t>;
                [[maybe_unused]]
                constexpr auto MAX_DIM = max_len_v<indices_t>;
                using element_t = conditional_t<is_nullable_index_array_v<indices_t>,null_int,nm_index_t>;
                if constexpr (DIM > 0) {
                    using type = nmtools_array<element_t,DIM>;
                    return as_value_v<type>;
                } else if constexpr (MAX_DIM > 0) {
                    using type = nmtools_static_vector<element_t,MAX_DIM>;
                    return as_value_v<type>;
                } else {
                    // TODO: use small vector
                    using type = nmtools_list<element_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_REVERSE_HPP