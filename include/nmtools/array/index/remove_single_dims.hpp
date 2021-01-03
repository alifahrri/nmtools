#ifndef NMTOOLS_ARRAY_INDEX_REMOVE_SINGLE_DIMS_HPP
#define NMTOOLS_ARRAY_INDEX_REMOVE_SINGLE_DIMS_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/index/filter.hpp"

#include <type_traits>
#include <cstddef> // size_t
#include <utility> // integer_sequence

namespace nmtools::index
{
    template <typename T>
    using eq_one = meta::constant_eq<T,1>;

    /**
     * @brief specific tag to resolve return type
     * 
     */
    struct remove_single_dims_t {};

    /**
     * @brief remove single dimension entry from given shape
     * 
     * @tparam shape_t 
     * @param shape 
     * @return constexpr auto 
     */
    template <typename shape_t>
    constexpr auto remove_single_dims(const shape_t& shape)
    {
        if constexpr (meta::apply_logical_and_v<meta::is_integral_constant,shape_t>) {
            using squeezed_t = meta::filter_t<eq_one,shape_t>;
            return squeezed_t{};
        }
        else {
            constexpr auto f = [](auto a){
                return a > 1;
            };
            auto [arg, squeezed] = filter(f,shape);
            return squeezed;
        }
    } // remove_single_dims
} // namespace index

namespace nmtools
{
    /**
     * @brief resolve return type for remove_single_dims op when
     * 
     * @tparam shape_t resizeable array with integral element type
     */
    template <typename shape_t>
    struct meta::resolve_optype<
        std::enable_if_t<
            meta::is_resizeable_v<shape_t>
            && std::is_integral_v<meta::get_element_type_t<shape_t>>
        >,
        index::remove_single_dims_t, shape_t
    >
    {
        using type = shape_t;
    }; // resolve_optype remove_single_dims_t

    /**
     * @brief resolve return type for remove_single_dims op
     * 
     * @tparam shape_t fixed array or tuple with integral element type
     */
    template <typename shape_t>
    struct meta::resolve_optype<
        std::enable_if_t<
            !meta::is_resizeable_v<shape_t>
            && meta::has_tuple_size_v<shape_t>
            && std::is_integral_v<meta::get_element_or_common_type_t<shape_t>>
        >,
        index::remove_single_dims_t, shape_t
    >
    {
        static constexpr auto N = std::tuple_size_v<shape_t>;
        using common_t = meta::get_element_or_common_type_t<shape_t>;
        using type = array::hybrid_ndarray<common_t,N,1>;
    }; // resolve_optype remove_single_dims_t
}

#endif // NMTOOLS_ARRAY_INDEX_REMOVE_SINGLE_DIMS_HPP