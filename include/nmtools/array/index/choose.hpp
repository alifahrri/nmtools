#ifndef NMTOOLS_ARRAY_INDEX_EXTRACT_HPP
#define NMTOOLS_ARRAY_INDEX_EXTRACT_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
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
            auto ii = tuple_at(indices,i);
            auto s  = tuple_at(array,ii);
            at(res,i) = s;
        }; // choose_impl

        if constexpr (meta::has_tuple_size_v<indices_t>)
            meta::template_for<std::tuple_size_v<indices_t>>([&](auto i){
                choose_impl(i);
            });
        else
            for (size_t i=0; i<tuple_size(indices); i++)
                choose_impl(i);

        return res;
    } // choose
} // namespace nmtools::index

namespace nmtools::meta
{
    /**
     * @brief resolve choose return type for resizeable indices and resizeable array
     * 
     * @tparam indices_t 
     * @tparam array_t 
     */
    template <typename indices_t, typename array_t>
    struct resolve_optype<
        std::enable_if_t<
            is_resizeable_v<array_t>
            && is_resizeable_v<indices_t>
            && std::is_integral_v<meta::get_element_type_t<indices_t>>
            && std::is_arithmetic_v<get_element_or_common_type_t<array_t>>
        >,
        index::choose_t, indices_t, array_t
    >
    {
        using element_t = get_element_or_common_type_t<array_t>;
        using type = replace_element_type_t<indices_t,element_t>;
    }; // resolve_optype choose_t

    /**
     * @brief resolve choose return type for resizeable indices and fixed-size array
     * 
     * @tparam indices_t 
     * @tparam array_t 
     */
    template <typename indices_t, typename array_t>
    struct resolve_optype<
        std::enable_if_t<
            !is_resizeable_v<array_t>
            && has_tuple_size_v<array_t>
            && is_resizeable_v<indices_t>
            && std::is_integral_v<meta::get_element_type_t<indices_t>>
            && std::is_arithmetic_v<get_element_or_common_type_t<array_t>>
        >,
        index::choose_t, indices_t, array_t
    >
    {
        using value_t = get_element_or_common_type_t<array_t>;
        using type    = replace_element_type_t<indices_t,value_t>;
    }; // resolve_optype choose_t

    /**
     * @brief resolve choose return type for resizeable fixed size indices and resizeable array
     * 
     * @tparam indices_t 
     * @tparam array_t 
     */
    template <typename indices_t, typename array_t>
    struct resolve_optype<
        std::enable_if_t<
            !is_resizeable_v<indices_t>
            && has_tuple_size_v<indices_t>
            && is_resizeable_v<array_t>
            && std::is_integral_v<get_element_or_common_type_t<indices_t>>
            && std::is_arithmetic_v<get_element_or_common_type_t<array_t>>
        >,
        index::choose_t, indices_t, array_t
    >
    {
        static constexpr auto N = std::tuple_size_v<indices_t>;
        using value_t = get_element_or_common_type_t<array_t>;
        using type    = std::array<value_t,N>;
    }; // resolve_optype choose_t

    template <typename indices_t, typename array_t>
    struct resolve_optype<
        std::enable_if_t<
            !is_resizeable_v<indices_t>
            && !is_resizeable_v<array_t>
            && has_tuple_size_v<indices_t>
            && has_tuple_size_v<array_t>
            && std::is_integral_v<get_element_or_common_type_t<indices_t>>
            && std::is_arithmetic_v<get_element_or_common_type_t<array_t>>
        >,
        index::choose_t, indices_t, array_t
    >
    {
        static constexpr auto M = std::tuple_size_v<indices_t>;
        static constexpr auto N = std::tuple_size_v<array_t>;
        using value_t = get_element_or_common_type_t<array_t>;
        using type = std::array<value_t,M>;
    }; // resolve_optype choose_t
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_EXTRACT_HPP