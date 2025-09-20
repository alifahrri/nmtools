#ifndef NMTOOLS_TILEKIT_TILEKIT_HPP
#define NMTOOLS_TILEKIT_TILEKIT_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/core.hpp"
#include "nmtools/array/tiling_window.hpp"
#include "nmtools/index/product.hpp"
#include "nmtools/ndarray/array.hpp"

namespace nmtools::tilekit
{
    template <typename ctx_t, typename array_t, typename offset_t, typename shape_t, typename axis_t=none_t>
    constexpr auto load(ctx_t&& ctx, const array_t& array, const offset_t& offset, const shape_t& shape, const axis_t& axis=axis_t{})
    {
        static_assert( meta::is_constant_index_array_v<shape_t> );
        static_assert( meta::is_constant_index_v<axis_t> || is_none_v<axis_t> );

        constexpr auto DIM = meta::len_v<offset_t>;
        static_assert( DIM > 0 );
        static_assert( meta::is_tuple_v<offset_t> );

        constexpr auto shapev = meta::to_value_v<shape_t>;
        constexpr auto numel  = index::product(shapev);

        using element_t = meta::get_element_type_t<array_t>;
        using buffer_t  = nmtools_array<element_t,numel>;        
        using result_t  = object_t<buffer_t,shape_t>;

        auto slices = utility::tuple_append(offset,Ellipsis);
        auto window = view::tiling_window(array,shape,axis);
        auto sliced = unwrap(view::apply_slice(window,slices));
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

#endif // NMTOOLS_TILEKIT_TILEKIT_HPP