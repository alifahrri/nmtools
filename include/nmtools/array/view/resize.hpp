#ifndef NMTOOLS_ARRAY_VIEW_RESIZE_HPP
#define NMTOOLS_ARRAY_VIEW_RESIZE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/view/decorator.hpp"

#include "nmtools/array/index/resize.hpp"
#include "nmtools/utility/unwrap.hpp"

namespace nmtools::view
{
    template <typename array_t, typename dst_shape_t>
    struct resize_t
    {
        using array_type = resolve_array_type_t<array_t>;
        using dst_shape_type = resolve_attribute_type_t<dst_shape_t>;
        using src_shape_type = const decltype(nmtools::shape<true>(meta::declval<array_t>()));

        array_type     array;
        dst_shape_type dst_shape;
        src_shape_type src_shape;

        constexpr resize_t(const array_t& array_, const dst_shape_t& dst_shape)
            : array(initialize<array_type>(array_))
            , dst_shape(init_attribute<dst_shape_type>(dst_shape))
            , src_shape(nmtools::shape<true>(array_))
        {}

        constexpr auto operands() const noexcept
        {
            return nmtools_tuple<array_type>{array};
        }

        constexpr auto attributes() const noexcept
        {
            return nmtools_tuple{dst_shape};
        }

        constexpr auto dim() const
        {
            return len(dst_shape);
        }

        constexpr auto shape() const
        {
            return dst_shape;
        }

        constexpr auto size() const
        {
            return index::product(dst_shape);
        }

        template <typename...size_types>
        constexpr auto index(size_types...indices) const
        {
            auto indices_ = pack_indices(indices...);
            auto tf_indices = index::resize(indices_,src_shape,dst_shape);
            return tf_indices;
        }
    }; // struct resize_t

    /*
       NOTE: must use always_inline attribute when compiling c++ for opencl kernel, otherwise:
       on -O3
       with hybrid shape: invalid cast
       with fixed shape: can't translate llvm instruction
       on -O1
       with hybrid shape: invalid cast
       with fixed shape: invalid cast
    */

    template <typename array_t, typename dst_shape_t>
    nmtools_view_attribute
    constexpr auto resize(const array_t& array, const dst_shape_t& dst_shape)
    {
        const auto src_shape = nmtools::shape<true>(array);
        const auto maybe_dst_shape = index::shape_resize(src_shape,dst_shape);
        using maybe_dst_shape_type = meta::remove_cvref_t<decltype(maybe_dst_shape)>;
        if constexpr (meta::is_maybe_v<maybe_dst_shape_type>) {
            using dst_shape_type = meta::get_maybe_type_t<maybe_dst_shape_type>;
            using resized_type = decorator_t<resize_t,array_t,dst_shape_type>;
            using return_type  = nmtools_maybe<resized_type>;
            if (static_cast<bool>(maybe_dst_shape)) {
                return return_type{resized_type{{array,*maybe_dst_shape}}};
            } else {
                return return_type{meta::Nothing};
            }
        } else {
            using resized_type = decorator_t<resize_t,array_t,maybe_dst_shape_type>;
            return resized_type{{array,maybe_dst_shape}};
        }
    } // resize
} // namespace nmtools::view

namespace nmtools::meta
{
    template <typename array_t, typename dst_shape_t>
    struct is_ndarray<
        view::decorator_t< view::resize_t, array_t, dst_shape_t>
    >
    {
        static constexpr auto value = is_ndarray_v<array_t>;
    };

    template <typename array_t, typename dst_shape_t>
    struct fixed_size<
        view::decorator_t<view::resize_t,array_t,dst_shape_t>
    > {
        using view_type = view::resize_t<array_t,dst_shape_t>;
        using dst_shape_type = typename view_type::dst_shape_type;

        static constexpr auto value = [](){
            if constexpr (is_constant_index_array_v<dst_shape_type>) {
                return index::product(dst_shape_type{});
            } else {
                return error::FIXED_SIZE_UNSUPPORTED<view_type>{};
            }
        }();
    };

    template <typename array_t, typename dst_shape_t>
    struct bounded_size<
        view::decorator_t<view::resize_t,array_t,dst_shape_t>
    > {
        using view_type = view::resize_t<array_t,dst_shape_t>;
        using dst_shape_type = typename view_type::dst_shape_type;

        static constexpr auto value = [](){
            if constexpr (is_constant_index_array_v<dst_shape_type>) {
                return index::product(dst_shape_type{});
            } else if constexpr (is_clipped_index_array_v<dst_shape_type>) {
                auto max_shape = to_value_v<dst_shape_type>;
                return index::product(max_shape);
            } else {
                return error::BOUNDED_SIZE_UNSUPPORTED<view_type>{};
            }
        }();
    };
}

#endif // NMTOOLS_ARRAY_VIEW_RESIZE_HPP