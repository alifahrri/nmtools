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
        using shape_type  = const shape_t&;
        using stride_type = resolve_optype_t<compute_strides_t,shape_t>;
        using size_type   = remove_cvref_t<meta::get_index_element_type_t<shape_t>>;

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
        template <typename size_type>
        constexpr inline decltype(auto) operator[](size_type i) const
        {
            return index::compute_indices(i,shape,stride);
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

namespace nmtools::meta
{
    template <typename shape_t>
    struct len<
        index::ndindex_t<shape_t>, enable_if_t<is_constant_index_array_v<shape_t>>
    > {
        static constexpr auto value = index::product(shape_t{});
    };
}


#endif // NMTOOLS_ARRAY_INDEX_NDINDEX_HPP