#ifndef NMTOOLS_INDEX_ADD_INDICES_HPP
#define NMTOOLS_INDEX_ADD_INDICES_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/at.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/utility/has_value.hpp"

namespace nmtools::index
{
    struct add_indices_t {};

    template <typename lhs_indices_t, typename rhs_indices_t>
    constexpr auto add_indices(const lhs_indices_t& lhs_indices, const rhs_indices_t& rhs_indices)
    {
        using result_t = resolve_optype_t<add_indices_t,lhs_indices_t,rhs_indices_t>;

        auto result = result_t {};

        if constexpr (!is_fail_v<result_t>
            && !is_constant_index_array_v<result_t>
        ) {
            constexpr auto DIM = len_v<result_t>;

            if constexpr (DIM > 0) {
                template_for<DIM>([&](auto i){
                    if constexpr (!is_constant_index_array_v<decltype(at(result,i))>) {
                        const auto& lhs_i = at(lhs_indices,i);
                        const auto& rhs_i = at(rhs_indices,i);
                        if (has_value(lhs_i) && has_value(rhs_i)) {
                            at(result,i) = lhs_i + rhs_i;
                        }
                    }
                });
            } else {
                // TODO: check if len(lhs_indices) == len(rhs_indices)
                auto dim = len(lhs_indices);
                if constexpr (is_resizable_v<result_t>) {
                    result.resize(dim);
                }
                for (nm_size_t i=0; i<(nm_size_t)dim; i++) {
                    const auto& lhs_i = at(lhs_indices,i);
                    const auto& rhs_i = at(rhs_indices,i);
                    if (has_value(lhs_i) && has_value(rhs_i)) {
                        at(result,i) = lhs_i + rhs_i;
                    }
                }
            }
        }

        return result;
    }
}

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct ADD_INDICES_UNSUPPORTED : detail::fail_t {};
    }

    template <typename lhs_indices_t, typename rhs_indices_t>
    struct resolve_optype<
        void, index::add_indices_t, lhs_indices_t, rhs_indices_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<lhs_indices_t>
                || !is_index_array_v<rhs_indices_t>
            ) {
                using type = error::ADD_INDICES_UNSUPPORTED<lhs_indices_t,rhs_indices_t>;
                return as_value_v<type>;
            } else if constexpr (
                (is_constant_index_array_v<lhs_indices_t> || is_mixed_index_array_v<lhs_indices_t>)
                && (is_constant_index_array_v<rhs_indices_t> || is_mixed_index_array_v<rhs_indices_t>)
            ) {
                constexpr auto lhs_indices = to_value_v<lhs_indices_t>;
                constexpr auto rhs_indices = to_value_v<rhs_indices_t>;
                constexpr auto result = index::add_indices(lhs_indices,rhs_indices);
                using nmtools::len, nmtools::at;
                constexpr auto N = len(result);
                // check if should return array
                constexpr auto return_array = [&](){
                    auto all_none = !has_value(at(result,0));
                    for (nm_size_t i=1; i<(nm_size_t)N; i++) {
                        all_none &= !has_value(at(result,i));
                    }
                    return all_none;
                }();
                if constexpr (return_array) {
                    using type = nmtools_array<nm_size_t,N>;
                    return as_value_v<type>;
                } else {
                    return template_reduce<N>([&](auto init, auto I){
                        constexpr auto i = decltype(I)::value;
                        using init_t = type_t<decltype(init)>;
                        constexpr auto res_i = at(result,i);
                        if constexpr (has_value(res_i)) {
                            using type = append_type_t<init_t,ct<(nm_size_t)res_i>>;
                            return as_value_v<type>;
                        } else {
                            using type = append_type_t<init_t,nm_size_t>;
                            return as_value_v<type>;
                        }
                    }, as_value_v<nmtools_tuple<>>);
                }
            } else if constexpr (
                is_nullable_index_array_v<lhs_indices_t>
                && is_nullable_index_array_v<rhs_indices_t>
            ) {
                // TODO: select which has the largest compile time DIM / B_DIM
                using type = conditional_t<
                    is_nullable_index_array_v<lhs_indices_t>
                    , lhs_indices_t
                    , rhs_indices_t
                >;
                return as_value_v<type>;
            } else {
                constexpr auto LHS_DIM = len_v<lhs_indices_t>;
                constexpr auto RHS_DIM = len_v<rhs_indices_t>;
                [[maybe_unused]] constexpr auto LHS_MAX_DIM = max_len_v<lhs_indices_t>;
                [[maybe_unused]] constexpr auto RHS_MAX_DIM = max_len_v<rhs_indices_t>;
                if constexpr ((LHS_DIM > 0) && (RHS_DIM > 0)) {
                    // TODO: assert if LHS_DIM == RHS_DIM
                    using type = nmtools_array<nm_size_t,LHS_DIM>;
                    return as_value_v<type>;
                } else if constexpr (LHS_MAX_DIM > 0) {
                    using type = nmtools_static_vector<nm_size_t,LHS_MAX_DIM>;
                    return as_value_v<type>;
                } else if constexpr (RHS_MAX_DIM > 0) {
                    using type = nmtools_static_vector<nm_size_t,RHS_MAX_DIM>;
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
}

#endif // NMTOOLS_INDEX_ADD_INDICES_HPP