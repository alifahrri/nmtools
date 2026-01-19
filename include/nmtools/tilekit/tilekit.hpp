#ifndef NMTOOLS_TILEKIT_TILEKIT_HPP
#define NMTOOLS_TILEKIT_TILEKIT_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/core.hpp"
#include "nmtools/array/tiling_window.hpp"
#include "nmtools/index/product.hpp"
#include "nmtools/ndarray/array.hpp"

namespace nmtools::tilekit::view
{
    template <typename array_t, typename offset_t, typename shape_t, typename axis_t=none_t>
    constexpr auto load(const array_t& array, const offset_t& offset, const shape_t& shape, const axis_t& axis=axis_t{})
    {
        static_assert( meta::is_constant_index_array_v<shape_t> );
        static_assert( meta::is_constant_index_v<axis_t> || is_none_v<axis_t> );

        constexpr auto DIM = meta::len_v<offset_t>;
        static_assert( DIM > 0 );
        static_assert( meta::is_tuple_v<offset_t> );

        auto slices = utility::tuple_append(offset,Ellipsis);
        auto window = nmtools::view::tiling_window(array,shape,axis);
        auto sliced = unwrap(nmtools::view::apply_slice(window,slices));

        return sliced;
    }
}

namespace nmtools::tilekit
{
    template <typename ctx_t, typename array_t, typename offset_t, typename shape_t, typename axis_t=none_t>
    constexpr auto load(ctx_t&& ctx, const array_t& array, const offset_t& offset, const shape_t& shape, const axis_t& axis=axis_t{})
    {
        constexpr auto shapev = meta::to_value_v<shape_t>;
        constexpr auto numel  = index::product(shapev);

        using element_t = meta::get_element_type_t<array_t>;
        using buffer_t  = nmtools_array<element_t,numel>;        
        using result_t  = object_t<buffer_t,shape_t>;

        auto sliced = view::load(array,offset,shape,axis);
        auto result = result_t{};

        eval(
            sliced
            , nmtools::forward<ctx_t>(ctx)
            , result
        );

        return result;
    }

    template <typename ctx_t, typename output_t, typename offset_t, typename result_t, typename axis_t=none_t>
    constexpr auto store([[maybe_unused]] ctx_t&& ctx, output_t& output, const offset_t& offset, const result_t& result, [[maybe_unused]] const axis_t& axis=axis_t{})
    {
        #if 1
        static_assert( meta::is_fixed_shape_v<result_t> );
        static_assert( meta::is_constant_index_v<axis_t> || is_none_v<axis_t> );

        constexpr auto DIM = meta::len_v<offset_t>;
        static_assert( DIM > 0 );
        static_assert( meta::is_tuple_v<offset_t> );

        auto shape  = nmtools::shape<true>(result);
        auto [dim0] = shape;
        auto [off0] = offset;

        for (nm_size_t j=0; j<dim0; j++) {
            at(output,off0*dim0+j) = at(result,j);
        }
        #else
        static_assert( meta::is_fixed_shape_v<result_t> );
        static_assert( meta::is_constant_index_v<axis_t> || is_none_v<axis_t> );

        constexpr auto DIM = meta::len_v<offset_t>;
        static_assert( DIM > 0 );
        static_assert( meta::is_tuple_v<offset_t> );

        auto shape  = nmtools::shape<true>(result);
        auto slices = utility::tuple_append(offset,Ellipsis);
        auto window = view::mutable_tiling_window(output,shape,axis);
        auto out    = view::apply_mutable_slice(window,slices);
    
        eval(
            view::ref(result)
            , nmtools::forward<ctx_t>(ctx)
            , out
        );
        #endif
    }
}

// tilekit utility

namespace nmtools::tilekit
{
    template <typename block_shape_t>
    constexpr auto product(const block_shape_t& b_shape)
    {
        return nmtools::index::product(b_shape);
    }

    template <typename block_shape_t, typename tile_shape_t>
    struct ndoffset_t
    {
        using block_shape_type  = block_shape_t;
        using block_stride_type = meta::resolve_optype_t<index::compute_strides_t,block_shape_type>;
        using tile_shape_type   = tile_shape_t;
        using size_type = nm_size_t;

        block_shape_type  block_shape_;
        block_stride_type block_stride_;
        tile_shape_type   tile_shape_;

        size_type size_;

        constexpr ndoffset_t(const block_shape_t& block_shape
            , const tile_shape_t& tile_shape)
            : block_shape_(block_shape)
            , block_stride_(index::compute_strides(block_shape_))
            , tile_shape_(tile_shape)
            , size_(index::product(block_shape_))
        {}

        constexpr auto size() const noexcept
        {
            return size_;
        }

        constexpr auto operator[](nm_size_t i) const
        {
            auto indices = index::compute_indices(i,block_shape_,block_stride_);
            // assume fixed dim
            constexpr auto DIM = len_v<decltype(indices)>;
            meta::template_for<DIM>([&](auto i){
                constexpr auto I = decltype(i)::value;
                nmtools::get<I>(indices) *= nmtools::get<I>(tile_shape_);
            });
            return indices;
        }
    };

    template <typename array_shape_t, typename tile_shape_t>
    constexpr auto ndoffset([[maybe_unused]] const array_shape_t& a_shape
        , [[maybe_unused]] const tile_shape_t& t_shape)
    {
        constexpr auto DIM = len_v<array_shape_t>;
        auto b_shape = template_reduce<DIM>([&](auto init, auto i){
            constexpr auto I = decltype(i)::value;
            auto a_dim = nmtools::get<I>(a_shape);
            auto t_dim = nmtools::get<I>(t_shape);
            return utility::tuple_append(init,a_dim/t_dim);
        }, nmtools_tuple{});
        return ndoffset_t(b_shape,t_shape);
    }
}

#endif // NMTOOLS_TILEKIT_TILEKIT_HPP