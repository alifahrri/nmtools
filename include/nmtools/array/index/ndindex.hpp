#ifndef NMTOOLS_ARRAY_INDEX_NDINDEX_HPP
#define NMTOOLS_ARRAY_INDEX_NDINDEX_HPP

#include "nmtools/array/detail.hpp"
#include "nmtools/array/meta.hpp"
#include "nmtools/traits.hpp"
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
     * @todo remove, unify with fixed-dim version
     */
    template <typename shape_t, typename=void>
    struct ndindex_t
    {
        using shape_type = shape_t;
        using stride_type = shape_t;
        using size_type = typename shape_type::value_type;

        shape_type shape;
        stride_type stride;

        /**
         * @brief Construct a new indices pack t object
         * 
         * @param shape original array shape
         */
        constexpr ndindex_t(shape_type shape)
            : shape(shape), stride(array::detail::compute_strides(shape))
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
            // compute product
            auto identity = static_cast<size_type>(1);
            for (const auto s : shape)
                identity *= s;
            return identity;
        } // size

        /**
         * @brief get the packed indices from flat indices
         * 
         * @param i flat index
         * @return auto 
         */
        constexpr inline decltype(auto) operator[](size_t i)
        {
            using array::detail::compute_indices;
            // map offset (flat index) back to indices
            return compute_indices(i,shape,stride);
        } // operator[]
    }; // ndindex_t

    /**
     * @brief indices transformer
     * 
     * Adapter from N-dimensional indices to packed 1-D indices,
     * can be used to transform nested N loop to 1 flat loop.
     * Only support fixed-dimensional array for now.
     * 
     * @tparam array_t compile-time array type to represent shape_type and stride_type
     * @tparam T
     * @tparam N number of dimension
     * @see nmtools::apply_at
     */
    template <template<typename,size_t> typename array_t, typename T, size_t N>
    struct ndindex_t<array_t<T,N>>
    {
        using shape_type = array_t<T,N>;
        using stride_type = array_t<T,N>;
        using size_type = typename shape_type::value_type;

        shape_type shape;
        stride_type stride;

        /**
         * @brief Construct a new indices pack t object
         * 
         * @param shape original array shape
         */
        constexpr ndindex_t(shape_type shape)
            : shape(shape), stride(array::detail::compute_strides(shape))
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
            // compute product
            auto identity = static_cast<size_type>(1);
            meta::template_for<N>([&](auto index){
                constexpr auto i = decltype(index)::value;
                identity *= std::get<i>(shape);
            });
            return identity;
        } // size

        /**
         * @brief get the packed indices from flat indices
         * 
         * @param i flat index
         * @return auto 
         */
        constexpr inline decltype(auto) operator[](size_t i)
        {
            using array::detail::compute_indices;
            using detail::as_tuple;
            // map offset (flat index) back to indices
            return as_tuple(compute_indices(i,shape,stride));
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
    constexpr auto ndindex(shape_t shape)
    {
        if constexpr (meta::is_specialization_v<shape_t,std::tuple> || meta::is_specialization_v<shape_t,std::pair>) {
            auto shape_ = detail::make_array<std::array>(shape);
            return ndindex_t(shape_);
        }
        else return ndindex_t(shape);
    } // ndindex
}

#endif // NMTOOLS_ARRAY_INDEX_NDINDEX_HPP