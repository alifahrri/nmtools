#ifndef NMTOOLS_ARRAY_INDEX_SCATTER_HPP
#define NMTOOLS_ARRAY_INDEX_SCATTER_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/assert.hpp"

namespace nmtools::index
{
    // tag to resolve scatter return type
    struct scatter_t {};

    // TODO: cleanup index functions
    /**
     * @brief perform scatter op
     * 
     * perform `ret[idx[i]] = vec[i]` aka reverse of gather
     *
     * @tparam vector_t type of vec
     * @tparam indices_t type of indices
     * @param vec 
     * @param indices 
     * @return constexpr auto 
     * @see gather
     */
    template <typename vector_t, typename indices_t>
    constexpr auto scatter(const vector_t& vec, const indices_t& indices)
    {
        using result_t = resolve_optype_t<scatter_t,vector_t,indices_t>;

        auto ret = result_t{};

        // TODO: support optional
        // TODO: static assert whenever possible

        [[maybe_unused]] auto n = (nm_size_t)len(vec);
        [[maybe_unused]] auto m = (nm_size_t)len(indices);
        if (n != m) {
            nmtools_cassert ((nm_size_t)n == (nm_size_t)m
                , "unsupported scatter, mismatched dimension between vec and indices"
            );
        }

        if constexpr (!is_constant_index_array_v<result_t>) {

            if constexpr (is_resizable_v<result_t>)
                ret.resize(len(vec)); // assuming indices has size

            auto scatter_impl = [&](auto& ret, const auto& vec, const auto& indices, auto i){
                [[maybe_unused]]
                auto value  = at(vec,i);
                auto idx    = at(indices,i);
                if constexpr (!is_constant_index_v<decltype(at(ret,unwrap(idx)))>) {
                    if (has_value(value) && has_value(idx)) {
                        at(ret,unwrap(idx)) = unwrap(value);
                    }
                }
            }; // scatter_impl

            // handle tuple if it has common_type
            constexpr auto DIM = len_v<vector_t>;
            if constexpr (DIM > 0) {
                template_for<DIM>([&](auto i){
                    scatter_impl(ret, vec, indices, i);
                });
            }
            else {
                for (nm_size_t i=0; i<m; i++) {
                    scatter_impl(ret, vec, indices, i);
                }
            }
        }

        return ret;
    } // scatter
} // namespace nmtools

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct INDEX_SCATTER_UNSUPPORTED : detail::fail_t {};
    }

    template <typename vector_t, typename indices_t>
    struct resolve_optype<
        void, index::scatter_t, vector_t, indices_t
    >
    {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<indices_t> || !is_index_array_v<vector_t>) {
                using type = error::INDEX_SCATTER_UNSUPPORTED<indices_t>;
                return as_value_v<type>;
            } else if constexpr (
                (is_constant_index_array_v<vector_t> || is_mixed_index_array_v<vector_t>)
                && (is_constant_index_array_v<indices_t> || is_mixed_index_array_v<indices_t>)
            ) {
                constexpr auto vec = to_value_v<vector_t>;
                constexpr auto ind = to_value_v<indices_t>;
                // using element_t [[maybe_unused]] = get_element_type_t<decltype(vec)>;
                using element_t = nm_index_t;
                constexpr auto res = index::scatter(vec, ind);
                // convert back to type
                using nmtools::len, nmtools::at, nmtools::unwrap, nmtools::has_value;
                return template_reduce<len(res)>([&](auto init, auto index){
                    constexpr auto I = decltype(index)::value;
                    using init_t = type_t<decltype(init)>;
                    if constexpr (has_value(at(res,I))) {
                        using result_t = append_type_t<init_t,ct<unwrap(at(res,I))>>;
                        return as_value_v<result_t>;
                    } else {
                        using result_t = append_type_t<init_t,element_t>;
                        return as_value_v<result_t>;
                    }
                }, as_value_v<nmtools_tuple<>>);
            } else {
                constexpr auto DIM = len_v<vector_t>;
                [[maybe_unused]]
                constexpr auto MAX_DIM = max_len_v<vector_t>;
                using index_t = conditional_t<is_nullable_index_array_v<vector_t>,null_int,nm_index_t>;
                if constexpr (DIM > 0) {
                    using type = nmtools_array<index_t,DIM>;
                    return as_value_v<type>;
                } else if constexpr (MAX_DIM > 0) {
                    using type = nmtools_static_vector<index_t,MAX_DIM>;
                    return as_value_v<type>;
                } else {
                    // TODO: use small vector
                    using type = nmtools_list<index_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_SCATTER_HPP