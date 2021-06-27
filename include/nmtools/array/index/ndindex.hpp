#ifndef NMTOOLS_ARRAY_INDEX_NDINDEX_HPP
#define NMTOOLS_ARRAY_INDEX_NDINDEX_HPP

#include "nmtools/array/detail.hpp"
#include "nmtools/array/index/product.hpp"
#include "nmtools/array/index/compute_strides.hpp"
#include "nmtools/array/meta.hpp"
#include "nmtools/meta.hpp"

#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/shape.hpp"

#include <array>
#include <tuple>
#include <type_traits>

namespace nmtools::index
{
    /**
     * @brief ndindex to support dynamic dimension
     * 
     * @tparam shape_t 
     * @tparam typename 
     */
    template <typename shape_t, typename=void>
    struct ndindex_t
    {
        using shape_type = const shape_t&;
        using stride_type = meta::remove_cvref_t<decltype(compute_strides(std::declval<shape_t>()))>;
        using size_type = meta::get_element_or_common_type_t<shape_t>;

        shape_type shape;
        stride_type stride;

        /**
         * @brief Construct a new indices pack t object
         * 
         * @param shape original array shape
         */
        constexpr ndindex_t(shape_type shape)
            : shape(shape), stride(compute_strides(shape))
        {
            // @note: this prevents ndindex_t to be used in constexpr
            // gcc error: must be initialized by mem-initializer
            // stride = array::detail::compute_strides(shape);
        }

        /**
         * @brief return the number of element
         * 
         * @return auto 
         */
        constexpr decltype(auto) size() const noexcept
        {
            return product(shape);
        } // size

        /**
         * @brief get the packed indices from flat indices
         * 
         * @param i flat index
         * @return auto 
         */
        constexpr inline decltype(auto) operator[](size_t i) const
        {
            using array::detail::compute_indices;
            if constexpr (meta::is_fixed_index_array_v<shape_t>) {
                using detail::as_tuple;
                // map offset (flat index) back to indices
                return as_tuple(compute_indices(i,shape,stride));
            }
            else {
                // map offset (flat index) back to indices
                return compute_indices(i,shape,stride);
            }
        } // operator[]
    }; // ndindex_t

    /**
     * @brief make ndindex from array representing shape
     * 
     * @tparam T element type of shape
     * @tparam N number of dimension
     * @param shape original array shape
     * @return constexpr auto indices transformer
     * @see ndindex_t
     */
    template <typename shape_t>
    constexpr auto ndindex(const shape_t& shape)
    {
        static_assert( meta::is_index_array_v<shape_t>
            , "unsupported ndindex" );
        return ndindex_t(shape);
    } // ndindex
}

#endif // NMTOOLS_ARRAY_INDEX_NDINDEX_HPP