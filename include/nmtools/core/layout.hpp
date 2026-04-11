#ifndef NMTOOLS_CORE_LAYOUT_HPP
#define NMTOOLS_CORE_LAYOUT_HPP

#include "nmtools/index/product.hpp"
#include "nmtools/index/pack.hpp"
#include "nmtools/index/compute_strides.hpp"
#include "nmtools/index/compute_indices.hpp"
#include "nmtools/index/compute_offset.hpp"
#include "nmtools/index/reverse.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/utility/at.hpp"
#include "nmtools/utility/get.hpp"

// experimental version that combine all three to single class

namespace nmtools
{
    template <typename shape_t, typename strides_t>
    struct row_major_offset_t
    {
        using shape_type = shape_t;
        using strides_type = strides_t;

        shape_type shape_;
        strides_type strides_;

        constexpr row_major_offset_t(const shape_t& shape, const strides_t& strides)
            : shape_(shape)
            , strides_(strides)
        {}

        constexpr row_major_offset_t()
            : shape_{}
            , strides_{}
        {}

        constexpr row_major_offset_t(const row_major_offset_t& other)
            : shape_(other.shape_)
            , strides_(other.strides_)
        {}

        constexpr row_major_offset_t& operator=(const row_major_offset_t& other)
        {
            if constexpr (!meta::is_constant_index_array_v<shape_type>) {
                [[maybe_unused]] auto dim = len(other.shape_);
                if constexpr (meta::is_resizable_v<shape_type>) {
                    shape_.resize(dim);
                }
                constexpr auto N = meta::len_v<shape_type>;
                if constexpr (N>0) {
                    meta::template_for<N>([&](auto i){
                        at(shape_,i) = at(other.shape_,i);
                    });
                } else {
                    for (size_t i=0; i<dim; i++) {
                        at(shape_,i) = at(other.shape_,i);
                    }
                }
            }
            if constexpr (!meta::is_constant_index_array_v<strides_type>) {
                [[maybe_unused]] auto dim = len(other.strides_);
                if constexpr (meta::is_resizable_v<strides_type>) {
                    strides_.resize(dim);
                }
                constexpr auto N = meta::len_v<strides_type>;
                if constexpr (N>0) {
                    meta::template_for<N>([&](auto i){
                        at(strides_,i) = at(other.strides_,i);
                    });
                } else {
                    for (size_t i=0; i<dim; i++) {
                        at(strides_,i) = at(other.strides_,i);
                    }
                }
            }
            return *this;
        }

        template <typename indices_t>
        constexpr auto operator()(const indices_t& indices) const
        {
            return index::compute_offset(indices,strides_);
        } // operator()
    }; // row_major_offset_t

    template <typename shape_t, typename strides_t>
    struct column_major_offset_t
    {
        using shape_type = meta::remove_cvref_t<decltype(index::reverse(meta::declval<shape_t>()))>;
        using strides_type = meta::remove_cvref_t<decltype(index::reverse(index::compute_strides(meta::declval<shape_type>())))>;

        shape_type shape_;
        strides_type strides_;


        constexpr column_major_offset_t(const shape_t& shape, const strides_t&)
            : shape_(index::reverse(shape))
            , strides_(index::reverse(index::compute_strides(shape_)))
        {}

        constexpr column_major_offset_t(const column_major_offset_t& other)
            : shape_(other.shape_)
            , strides_(other.strides_)
        {}

        constexpr column_major_offset_t()
            : shape_{}
            , strides_{}
        {}

        constexpr column_major_offset_t& operator=(const column_major_offset_t& other)
        {
            if constexpr (!meta::is_constant_index_array_v<shape_type>) {
                [[maybe_unused]] auto dim = len(other.shape_);
                if constexpr (meta::is_resizable_v<shape_type>) {
                    shape_.resize(dim);
                }
                constexpr auto N = meta::len_v<shape_type>;
                if constexpr (N>0) {
                    meta::template_for<N>([&](auto i){
                        at(shape_,i) = at(other.shape_,i);
                    });
                } else {
                    for (size_t i=0; i<dim; i++) {
                        at(shape_,i) = at(other.shape_,i);
                    }
                }
            }
            if constexpr (!meta::is_constant_index_array_v<strides_type>) {
                [[maybe_unused]] auto dim = len(other.strides_);
                if constexpr (meta::is_resizable_v<strides_type>) {
                    strides_.resize(dim);
                }
                constexpr auto N = meta::len_v<strides_type>;
                if constexpr (N>0) {
                    meta::template_for<N>([&](auto i){
                        at(strides_,i) = at(other.strides_,i);
                    });
                } else {
                    for (size_t i=0; i<dim; i++) {
                        at(strides_,i) = at(other.strides_,i);
                    }
                }
            }
            return *this;
        }

        template <typename indices_t>
        constexpr auto operator()(const indices_t& indices) const
        {
            auto offset = index::compute_offset(indices,strides_);
            return offset;
        } // operator()
    };
} // namespace nmtools

#endif // NMTOOLS_CORE_LAYOUT_HPP