#ifndef NMTOOLS_ARRAY_INDEX_EXTRACT_HPP
#define NMTOOLS_ARRAY_INDEX_EXTRACT_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/array/index/tuple_at.hpp"

#include <type_traits>
#include <cstddef>
#include <utility>

namespace nmtools::index
{
    /**
     * @brief specific tag to resolve return type
     * 
     */
    struct choose_t {};

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
        using return_t = meta::resolve_optype_t<choose_t,indices_t,array_t>;
        auto res = return_t{};

        if constexpr (meta::is_resizeable_v<return_t>)
            res.resize(tuple_size(indices));

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

        return res;
    } // choose
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        // specific type tor respresent index::choose type infer error
        struct INDEX_CHOOSE_UNHANDLED_CASE : detail::fail_t {};
    } // namespace error
    
    template <typename indices_t, typename array_t>
    struct resolve_optype<
        void, index::choose_t, indices_t, array_t
    >
    {
        static constexpr auto vtype = [](){
            using element_t = remove_cvref_t<get_element_or_common_type_t<array_t>>;
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
                using type = make_fixed_ndarray_t<element_t,std::tuple<ct<N>>>;
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
                return as_value_v<error::INDEX_CHOOSE_UNHANDLED_CASE>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };

} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_EXTRACT_HPP