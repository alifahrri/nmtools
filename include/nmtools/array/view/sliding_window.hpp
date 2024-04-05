#ifndef NMTOOLS_ARRAY_VIEW_SLIDING_WINDOW_HPP
#define NMTOOLS_ARRAY_VIEW_SLIDING_WINDOW_HPP

#include "nmtools/array/index/sliding_window.hpp"
#include "nmtools/array/index/product.hpp"
#include "nmtools/array/view/decorator.hpp"
#include "nmtools/utility/unwrap.hpp"
#include "nmtools/utility/fwd.hpp"

namespace nmtools::args
{
    template <typename indexer_t>
    struct indexing
    {
        using indexer_type = indexer_t;

        indexer_type indexer = {};

        template <typename...args_t>
        constexpr auto operator==(const indexing<args_t...>& other) const
        {
            return indexer == other.indexer;
        }
    }; // indexing

    template <typename...args_t>
    indexing(args_t...) -> indexing<args_t...>;
} // namespace nmtools::args

namespace nmtools::meta
{
    template <typename indexer_t>
    struct is_attribute<args::indexing<indexer_t>> : true_type {};
} // namespace nmtools::meta

namespace nmtools::view
{
    template <typename indexer_t>
    struct base_indexer_t
    {
        constexpr indexer_t* self()
        {
            return static_cast<indexer_t*>(this);
        }

        constexpr const indexer_t* self() const
        {
            return static_cast<const indexer_t*>(this);
        }

        constexpr auto shape() const
        {
            return self()->dst_shape;
        }

        constexpr auto dim() const
        {
            return len(shape());
        }

        constexpr auto size() const
        {
            return index::product(shape());
        }
    }; // base_indexer_t

    template <typename src_shape_t
        , typename window_shape_t
        , typename axis_t>
    struct sliding_window_t
        : base_indexer_t<sliding_window_t<src_shape_t,window_shape_t,axis_t>>
    {
        using src_shape_type    = meta::fwd_attribute_t<src_shape_t>;
        using window_shape_type = meta::fwd_attribute_t<window_shape_t>;
        using axis_type         = meta::fwd_attribute_t<axis_t>;
        using dst_shape_type = meta::resolve_optype_t<index::shape_sliding_window_t
            , src_shape_type, window_shape_type, axis_type>;

        const src_shape_type src_shape;
        const window_shape_type window_shape;
        const axis_type axis;
        const dst_shape_type dst_shape;

        constexpr sliding_window_t(const src_shape_t& src_shape
            , const window_shape_t& window_shape
            , const axis_t& axis
        )
            : src_shape(fwd_attribute(src_shape))
            , window_shape(fwd_attribute(window_shape))
            , axis(fwd_attribute(axis))
            , dst_shape(index::shape_sliding_window(
                src_shape,window_shape,axis))
        {}

        template <typename indices_t>
        constexpr auto indices(const indices_t& indices) const
        {
            auto src_indices = index::sliding_window(indices
                , unwrap(dst_shape), src_shape, window_shape, axis);
            return src_indices;
        }

        template <typename...args_t>
        constexpr auto operator==(sliding_window_t<args_t...> other) const
        {
            return utils::isequal(src_shape,other.src_shape)
                && utils::isequal(dst_shape,other.dst_shape)
                && utils::isequal(window_shape,other.window_shape)
                && utils::isequal(axis,other.axis)
            ;
        }
    }; // sliding_window_t

    template <typename array_t, typename indexer_t>
    struct indexing_t
    {
        using operand_type = meta::fwd_operand_t<array_t>;
        using array_type   = operand_type;
        using indexer_type = indexer_t;

        using attributes_type = args::indexing<indexer_type>;

        operand_type array;
        indexer_type indexer;

        constexpr indexing_t(const array_t& array, const indexer_t& indexer)
            : array(fwd_operand(array))
            , indexer(indexer)
        {}

        constexpr auto operands() const noexcept
        {
            return nmtools_tuple<array_type>{array};
        } // operands

        constexpr auto attributes() const noexcept
        {
            return attributes_type{indexer};
        }

        constexpr auto shape() const
        {
            return indexer.shape();
        }

        constexpr auto dim() const
        {
            return indexer.dim();
        }

        constexpr auto size() const
        {
            return indexer.size();
        }

        template <typename...size_types>
        constexpr auto operator()(size_types...indices) const
        {
            auto dst_indices = pack_indices(indices...);
            auto src_indices = indexer.indices(dst_indices);
            if constexpr (meta::is_pointer_v<array_type>) {
                return apply_at(*array,src_indices);
            } else {
                return apply_at(array,src_indices);
            }
        }
    }; // indexing_t

    template <typename array_t, typename indexer_t>
    constexpr auto indexing(const array_t& array, const indexer_t& indexer)
    {
        using view_type = decorator_t<indexing_t,array_t,indexer_t>;
        return view_type{{array,indexer}};
    } // indexing

    template <typename array_t, typename window_shape_t, typename axis_t=none_t>
    constexpr auto sliding_window(const array_t& array
        , const window_shape_t& window_shape, const axis_t& axis=axis_t{})
    {
        auto src_shape = shape<true>(array);
        auto indexer   = sliding_window_t{src_shape,window_shape,axis};
        return indexing(array,indexer);
    } // sliding_window
} // namespace nmtools::view

namespace nmtools::meta
{
    template <typename array_t, typename indexer_t>
    struct is_ndarray<
        view::decorator_t<view::indexing_t,array_t,indexer_t>
    > {
        static constexpr auto value = is_ndarray_v<array_t>;
    };

    template <typename array_t, typename indexer_t>
    struct get_element_type<
        view::decorator_t<view::indexing_t,array_t,indexer_t>
    > {
        using type = get_element_type_t<array_t>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_SLIDING_WINDOW_HPP