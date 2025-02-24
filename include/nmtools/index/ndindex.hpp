#ifndef NMTOOLS_ARRAY_INDEX_NDINDEX_HPP
#define NMTOOLS_ARRAY_INDEX_NDINDEX_HPP

#include "nmtools/index/product.hpp"
#include "nmtools/index/compute_strides.hpp"
#include "nmtools/index/compute_indices.hpp"
#include "nmtools/meta.hpp"

#include "nmtools/utility/at.hpp"
#include "nmtools/utility/shape.hpp"

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
        using stride_type = meta::resolve_optype_t<compute_strides_t,shape_t>;
        using size_type = meta::remove_cvref_t<meta::get_index_element_type_t<shape_t>>;

        shape_type shape;
        stride_type stride;

        /**
         * @brief Construct a new indices pack t object
         * 
         * @param shape original array shape
         */
        constexpr ndindex_t(shape_type shape)
            : shape(shape), stride(compute_strides(shape)) {}

        /**
         * @brief return the number of element
         * 
         * @return auto 
         */
        constexpr decltype(auto) size() const noexcept
        {
            // TODO: consider to return as constant index when possible
            return static_cast<size_t>(product(shape));
        } // size

        /**
         * @brief get the packed indices from flat indices
         * 
         * @param i flat index
         * @return auto 
         */
        constexpr inline decltype(auto) operator[](size_t i) const
        {
            using index::compute_indices;
            if constexpr (meta::is_fixed_index_array_v<shape_t>) {
                // map offset (flat index) back to indices
                return compute_indices(i,shape,stride);
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

namespace nmtools
{
    /**
     * @brief Specialization of len for ndindex
     * 
     * @tparam shape_t 
     * @param ndindex 
     * @return constexpr auto 
     */
    template <typename shape_t>
    constexpr auto len(const index::ndindex_t<shape_t>& ndindex)
    {
        return ndindex.size();
    } // len
} // namespace nmtools


#endif // NMTOOLS_ARRAY_INDEX_NDINDEX_HPP