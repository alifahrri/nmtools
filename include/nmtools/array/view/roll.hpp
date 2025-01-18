#ifndef NMTOOLS_ARRAY_VIEW_ROLL_HPP
#define NMTOOLS_ARRAY_VIEW_ROLL_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/index/roll.hpp"
#include "nmtools/array/core/indexing.hpp"
#include "nmtools/array/view/flatten.hpp"
#include "nmtools/array/view/reshape.hpp"
#include "nmtools/utility/shape.hpp"

namespace nmtools::view
{
    template <typename src_shape_t, typename shift_t, typename axis_t, typename src_size_t>
    struct roll_t
        : base_indexer_t<roll_t<src_shape_t,shift_t,axis_t,src_size_t>>
    {
        using src_shape_type = meta::fwd_attribute_t<src_shape_t>;
        using src_size_type  = meta::fwd_attribute_t<src_size_t>;

        using dst_shape_type = src_shape_type;
        using dst_size_type  = src_size_type;

        using shift_type = meta::fwd_attribute_t<shift_t>;
        using axis_type  = meta::fwd_attribute_t<axis_t>;

        static constexpr auto n_inputs  = 1;
        static constexpr auto n_outputs = 1;

        const src_shape_type src_shape;
        const dst_shape_type dst_shape;
        const shift_type shift;
        const axis_type  axis;
        const src_size_type  src_size;
        const dst_size_type  dst_size;

        constexpr roll_t(const src_shape_t& src_shape_
            , const shift_t& shift_
            , const axis_t& axis_
            , const src_size_t& src_size_
        )
            : src_shape(fwd_attribute(src_shape_))
            , dst_shape(fwd_attribute(src_shape_))
            , shift(fwd_attribute(shift_))
            , axis(fwd_attribute(axis_))
            , src_size(fwd_attribute(src_size_))
            , dst_size(fwd_attribute(src_size_))
        {}

        template <typename indices_t>
        constexpr auto indices(const indices_t& indices) const
        {
            auto src_indices = index::roll(src_shape,indices,shift,axis);
            return src_indices;
        }

        template <typename...args_t>
        constexpr auto operator==(const roll_t<args_t...>& other) const
        {
            return utils::isequal(src_shape,other.src_shape)
                && utils::isequal(axis,other.axis)
                && utils::isequal(shift,other.shift)
            ;
        }
    };

    template <typename src_shape_t, typename shift_t, typename axis_t, typename src_size_t>
    constexpr auto roller(const src_shape_t& src_shape, const shift_t& shift, const axis_t& axis, src_size_t src_size)
    {
        auto m_dst_shape = index::shape_roll(src_shape,shift,axis);
        if constexpr (meta::is_fail_v<decltype(m_dst_shape)>) {
            return m_dst_shape;
        } else if constexpr (meta::is_maybe_v<decltype(m_dst_shape)>) {
            using result_t = decltype(roll_t{*m_dst_shape,shift,axis,unwrap(src_size)});
            using return_t = nmtools_maybe<result_t>;
            return (m_dst_shape
                ? return_t{result_t{*m_dst_shape,shift,axis,unwrap(src_size)}}
                : return_t{meta::Nothing}
            );
        } else {
            return roll_t{m_dst_shape,shift,axis,unwrap(src_size)};
        }
    } // roller

    template <typename array_t, typename shift_t, typename axis_t=none_t>
    constexpr auto roll(const array_t& array, const shift_t& shift, const axis_t& axis=axis_t{})
    {
        if constexpr (is_none_v<axis_t>) {
            auto src_shape = shape<true>(array);
            auto flattened = view::flatten(array);
            auto rolled    = view::roll(flattened,shift,meta::ct_v<0>);
            auto reshaped  = view::reshape(rolled,src_shape);
            return reshaped;
        } else {
            auto f = [](const auto& array, const auto& shift, const auto& axis){
                auto src_shape = shape<true>(array);
                auto src_size  = size<true>(array);
                auto indexer   = roller(src_shape,shift,axis,src_size);
                return indexing(array,indexer);
            };
            return lift_indexing(f,array,shift,axis);
        }
    }
} // namespace nmtools::view

namespace nmtools::array
{
    template <typename...args_t, auto max_dim>
    struct  as_static_t<
        view::roll_t<args_t...>, max_dim
    > {
        using attribute_type = view::roll_t<args_t...>;

        attribute_type attribute;

        auto operator()() const
        {
            auto src_shape = as_static<max_dim>(attribute.src_shape);
            auto shift     = as_static<max_dim>(attribute.shift);
            auto axis      = as_static<max_dim>(attribute.axis);
            auto src_size  = as_static<max_dim>(attribute.src_size);
            return view::roller(src_shape,shift,axis,src_size);
        }
    };
}

#endif // NMTOOLS_ARRAY_VIEW_ROLL_HPP