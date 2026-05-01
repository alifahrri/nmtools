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

        // Copy constructor (constexpr-friendly, avoids std::tuple copy issues)
        constexpr row_major_offset_t(const row_major_offset_t& other) noexcept
            : shape_(other.shape_)
            , strides_(other.strides_)
        {}

        // Reset shape/strides without assignment (constexpr-friendly)
        template <typename other_shape_t, typename other_strides_t>
        constexpr void reset(const other_shape_t& shape, const other_strides_t& strides) noexcept
        {
            if constexpr (!is_constant_index_array_v<other_shape_t>) {
                [[maybe_unused]] auto dim = len(shape);
                if constexpr (is_resizable_v<other_shape_t>) {
                    shape_.resize(dim);
                }
                constexpr auto N = len_v<other_shape_t>;
                if constexpr (N>0) {
                    template_for<N>([&](auto i){
                        at(shape_,i) = at(shape,i);
                    });
                } else {
                    for (nm_size_t i=0; i<(nm_size_t)dim; i++) {
                        at(shape_,i) = at(shape,i);
                    }
                }
            }
            if constexpr (!is_constant_index_array_v<other_strides_t>) {
                [[maybe_unused]] auto dim = len(strides);
                if constexpr (is_resizable_v<other_strides_t>) {
                    strides_.resize(dim);
                }
                constexpr auto N = len_v<other_strides_t>;
                if constexpr (N>0) {
                    template_for<N>([&](auto i){
                        at(strides_,i) = at(strides,i);
                    });
                } else {
                    for (nm_size_t i=0; i<(nm_size_t)dim; i++) {
                        at(strides_,i) = at(strides,i);
                    }
                }
            }
        }

        template <typename other_shape_t, typename other_strides_t>
        constexpr row_major_offset_t(const row_major_offset_t<other_shape_t,other_strides_t>& other) noexcept
            : shape_{}
            , strides_{}
        {
            this->reset(other.shape_,other.strides_);
        }

        template <typename other_shape_t, typename other_strides_t>
        constexpr row_major_offset_t& operator=(const row_major_offset_t<other_shape_t,other_strides_t>& other) noexcept
        {
            this->reset(other.shape_,other.strides_);
            return *this;
        }

        // Copy assignment for same type (constexpr-friendly, avoids std::tuple assignment)
        constexpr row_major_offset_t& operator=(const row_major_offset_t& other) noexcept
        {
            this->reset(other.shape_,other.strides_);
            return *this;
        }

        // Move assignment (delegates to copy assignment to avoid non-constexpr std::tuple move)
        constexpr row_major_offset_t& operator=(row_major_offset_t&& other) noexcept
        {
            return *this = static_cast<const row_major_offset_t&>(other);
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
        using shape_type = remove_cvref_t<decltype(index::reverse(declval<shape_t>()))>;
        using strides_type = remove_cvref_t<decltype(index::reverse(index::compute_strides(declval<shape_type>())))>;

        shape_type shape_;
        strides_type strides_;


        constexpr column_major_offset_t(const shape_t& shape, const strides_t&)
            : shape_(index::reverse(shape))
            , strides_(index::reverse(index::compute_strides(shape_)))
        {}

        constexpr column_major_offset_t()
            : shape_{}
            , strides_{}
        {}

        constexpr column_major_offset_t(const column_major_offset_t& other)
            : shape_(other.shape_)
            , strides_(other.strides_)
        {}

        // Reset shape/strides without assignment (constexpr-friendly)
        template <typename other_shape_t, typename other_strides_t>
        constexpr void reset(const other_shape_t& shape, const other_strides_t& strides) noexcept
        {
            if constexpr (!is_constant_index_array_v<other_shape_t>) {
                [[maybe_unused]] auto dim = len(shape);
                if constexpr (is_resizable_v<other_shape_t>) {
                    shape_.resize(dim);
                }
                constexpr auto N = len_v<other_shape_t>;
                if constexpr (N>0) {
                    template_for<N>([&](auto i){
                        at(shape_,i) = at(shape,i);
                    });
                } else {
                    for (nm_size_t i=0; i<(nm_size_t)dim; i++) {
                        at(shape_,i) = at(shape,i);
                    }
                }
            }
            if constexpr (!is_constant_index_array_v<other_strides_t>) {
                [[maybe_unused]] auto dim = len(strides);
                if constexpr (is_resizable_v<other_strides_t>) {
                    strides_.resize(dim);
                }
                constexpr auto N = len_v<other_strides_t>;
                if constexpr (N>0) {
                    template_for<N>([&](auto i){
                        at(strides_,i) = at(strides,i);
                    });
                } else {
                    for (nm_size_t i=0; i<(nm_size_t)dim; i++) {
                        at(strides_,i) = at(strides,i);
                    }
                }
            }
        }

        template <typename other_shape_t, typename other_strides_t>
        constexpr column_major_offset_t(const column_major_offset_t<other_shape_t,other_strides_t>& other)
            : shape_{}
            , strides_{}
        {
            this->reset(other.shape_,other.strides_);
        }

        // Copy assignment for same type (constexpr-friendly)
        constexpr column_major_offset_t& operator=(const column_major_offset_t& other) noexcept
        {
            this->reset(other.shape_,other.strides_);
            return *this;
        }

        // Move assignment (delegates to copy assignment)
        constexpr column_major_offset_t& operator=(column_major_offset_t&& other) noexcept
        {
            return *this = static_cast<const column_major_offset_t&>(other);
        }

        template <typename other_shape_t, typename other_strides_t>
        constexpr column_major_offset_t& operator=(const column_major_offset_t<other_shape_t,other_strides_t>& other) noexcept
        {
            this->reset(other.shape_,other.strides_);
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