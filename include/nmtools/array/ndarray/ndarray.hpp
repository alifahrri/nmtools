#ifndef NMTOOLS_ARRAY_NDARRAY_NDARRAY_HPP
#define NMTOOLS_ARRAY_NDARRAY_NDARRAY_HPP

#include "nmtools/array/index/product.hpp"
#include "nmtools/array/index/pack.hpp"

// experimental version that combine all three to single class

namespace nmtools::array
{
    template <typename T
        , template <typename...>typename buffer_t
        , template <typename...>typename shape_buffer_t
        , template <typename...>typename stride_buffer_t=shape_buffer_t
        , typename=void>
    struct ndarray
    {
        using buffer_type = buffer_t<T>;
        using value_type  = T;
        using index_type  = size_t;
        using shape_type  = shape_buffer_t<index_type>;
        using stride_type = stride_buffer_t<index_type>;

        buffer_type data_;
        shape_type  shape_;
        stride_type strides_;
        index_type  numel_;

        ndarray() {}

        constexpr auto dim() const
        {
            return len(shape_);
        } // dim

        constexpr auto& shape() const
        {
            return shape_;
        } // shape

        template <typename...size_types>
        constexpr decltype(auto) operator()(size_types...indices)
        {
            auto indices_ = index::pack_indices(indices...);
            auto offset   = index::compute_offset(strides_, indices_);
            // implicitly assume buffer type has [] (no need to pass via at)
            return data_[offset];
        } // operator()

        template <typename...size_types>
        constexpr decltype(auto) operator()(size_types...indices) const
        {
            auto indices_ = index::pack_indices(indices...);
            auto offset   = index::compute_offset(strides_, indices_);
            // implicitly assume buffer type has [] (no need to pass via at)
            return data_[offset];
        } // operator()
    }; // ndarray
}

#endif // NMTOOLS_ARRAY_NDARRAY_NDARRAY_HPP