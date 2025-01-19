#ifndef NMTOOLS_ARRAY_INDEX_EXTRACT_HPP
#define NMTOOLS_ARRAY_INDEX_EXTRACT_HPP

#include "nmtools/utility/at.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/stl.hpp"
#include "nmtools/ndarray/fixed.hpp"
#include "nmtools/index/tuple_at.hpp"
#include "nmtools/meta.hpp"

namespace nmtools::index
{
    /**
     * @brief specific tag to resolve return type
     * 
     */
    struct choose_t {};

    // TODO: cleanup index functions
    /**
     * @brief construct array from indices array
     * 
     * @tparam indices_t 
     * @tparam array_t 
     * @param indices 
     * @param array 
     * @return constexpr auto 
     */
    template <typename indices_t, typename array_t>
    constexpr auto choose(const indices_t& indices, const array_t& array)
    {
        // TODO: support constant index array
        using return_t = meta::resolve_optype_t<choose_t,indices_t,array_t>;
        auto res = return_t{};

        if constexpr (!meta::is_constant_index_array_v<return_t>) {
            if constexpr (meta::is_resizable_v<return_t>) {
                res.resize(len(indices));
            }

            // actual implementation of choose
            auto choose_impl = [&](auto i){
                auto ii = at(indices,i);
                // TODO: tuple to array
                auto s  = at(array,ii);
                at(res,i) = s;
            }; // choose_impl

            if constexpr (meta::is_fixed_index_array_v<indices_t>) {
                meta::template_for<meta::len_v<indices_t>>([&](auto i){
                    choose_impl(i);
                });
            } else {
                for (size_t i=0; i<len(indices); i++)
                    choose_impl(i);
            }
        }

        return res;
    } // choose
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        // specific type tor respresent index::choose type infer error
        template <typename...>
        struct INDEX_CHOOSE_UNHANDLED_CASE : detail::fail_t {};

        template <typename...>
        struct INDEX_CHOOSE_UNSUPPORTED : detail::fail_t {};
    } // namespace error
    
    template <typename indices_t, typename array_t>
    struct resolve_optype<
        void, index::choose_t, indices_t, array_t
    >
    {
        static constexpr auto vtype = [](){
            using element_t = remove_cvref_t<get_element_or_common_type_t<array_t>>;
            #if 1
            [[maybe_unused]] constexpr auto N = len_v<indices_t>;
            [[maybe_unused]] constexpr auto B_SIZE = bounded_size_v<indices_t>;
            if constexpr (is_fail_v<element_t> || !(is_index_array_v<indices_t> && is_index_array_v<array_t>)) {
                using type = error::INDEX_CHOOSE_UNSUPPORTED<indices_t,array_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_index_array_v<indices_t> && is_constant_index_array_v<array_t>) {
                constexpr auto indices = to_value_v<indices_t>;
                constexpr auto array   = to_value_v<array_t>;
                constexpr auto result  = index::choose(indices,array);
                using nmtools::len, nmtools::at;
                return meta::template_reduce<len(result)>([&](auto init, auto index){
                    constexpr auto I  = at(result,index);
                    using init_type   = type_t<decltype(init)>;
                    using result_type = append_type_t<init_type,ct<(nm_size_t)I>>;
                    return as_value_v<result_type>;
                }, as_value_v<nmtools_tuple<>>);
            } else if constexpr (N > 0) {
                using type = nmtools_array<element_t,N>;
                return as_value_v<type>;
            } else if constexpr (!is_fail_v<decltype(B_SIZE)>) {
                using type = nmtools_static_vector<element_t,B_SIZE>;
                return as_value_v<type>;
            } else /* if constexpr (is_index_array_v<indices_t> && is_index_array_v<array_t>) */ {
                // TODO: use small_vector
                using type = nmtools_list<element_t>;
                return as_value_v<type>;
            }
            #else
            if constexpr (
                   is_hybrid_index_array_v<indices_t>
                && is_hybrid_index_array_v<array_t>
            ) {
                using type = replace_element_type_t<indices_t,element_t>;
                return as_value_v<type>;
            } else if constexpr (
                   is_dynamic_index_array_v<indices_t>
                && is_dynamic_index_array_v<array_t>
            ) {
                using type = replace_element_type_t<indices_t,element_t>;
                return as_value_v<type>;
            } else if constexpr (
                   is_fixed_index_array_v<indices_t>
                && is_fixed_index_array_v<array_t>
            ) {
                using tf_indices_t = tuple_to_array_t<transform_bounded_array_t<indices_t>>;
                using type = replace_element_type_t<tf_indices_t,element_t>;
                return as_value_v<type>;
            } else if constexpr (
                   is_constant_index_array_v<indices_t>
                && is_constant_index_array_v<array_t>
            ) {
                // TODO: compute at compile-time here, then maps back to type
                constexpr auto N = fixed_index_array_size_v<indices_t>;
                using type = make_fixed_ndarray_t<element_t,nmtools_tuple<ct<N>>>;
                return as_value_v<type>;
            } else if constexpr (
                   is_hybrid_index_array_v<indices_t>
                && is_dynamic_index_array_v<array_t>
            ) {
                // in this case, we can still choose indices_t since the shape will
                // mostly depends on indices_t
                using type = replace_element_type_t<indices_t,element_t>;
                return as_value_v<type>;
            } else if constexpr (
                   is_hybrid_index_array_v<indices_t>
                && is_fixed_index_array_v<array_t>
            ) {
                using type = replace_element_type_t<indices_t,element_t>;
                return as_value_v<type>;
            } else if constexpr (
                   is_hybrid_index_array_v<indices_t>
                && is_constant_index_array_v<array_t>
            ) {
                using type = replace_element_type_t<indices_t,element_t>;
                return as_value_v<type>;
            } else if constexpr (
                   is_dynamic_index_array_v<indices_t>
                && is_hybrid_index_array_v<array_t>
            ) {
                using type = replace_element_type_t<indices_t,element_t>;
                return as_value_v<type>;
            } else if constexpr (
                   is_dynamic_index_array_v<indices_t>
                && is_fixed_index_array_v<array_t>
            ) {
                using type = replace_element_type_t<indices_t,element_t>;
                return as_value_v<type>;
            } else if constexpr (
                   is_dynamic_index_array_v<indices_t>
                && is_constant_index_array_v<array_t>
            ) {
                using type = replace_element_type_t<indices_t,element_t>;
                return as_value_v<type>;
            } else if constexpr (
                   is_fixed_index_array_v<indices_t>
                && is_hybrid_index_array_v<array_t>
            ) {
                using tf_indices_t = tuple_to_array_t<transform_bounded_array_t<indices_t>>;
                using type = replace_element_type_t<tf_indices_t,element_t>;
                return as_value_v<type>;
            } else if constexpr (
                   is_fixed_index_array_v<indices_t>
                && is_dynamic_index_array_v<array_t>
            ) {
                using tf_indices_t = tuple_to_array_t<transform_bounded_array_t<indices_t>>;
                using type = replace_element_type_t<tf_indices_t,element_t>;
                return as_value_v<type>;
            } else if constexpr (
                   is_fixed_index_array_v<indices_t>
                && is_constant_index_array_v<array_t>
            ) {
                using tf_indices_t = tuple_to_array_t<transform_bounded_array_t<indices_t>>;
                using type = replace_element_type_t<tf_indices_t,element_t>;
                return as_value_v<type>;
            } else {
                return as_value_v<error::INDEX_CHOOSE_UNHANDLED_CASE<indices_t,array_t>>;
            }
            #endif
        }();
        using type = type_t<decltype(vtype)>;
    };

} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_EXTRACT_HPP