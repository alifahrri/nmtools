#ifndef NMTOOLS_ARRAY_VIEW_ARRAY_SLICE_HPP
#define NMTOOLS_ARRAY_VIEW_ARRAY_SLICE_HPP

#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/view/broadcast_arrays.hpp"
#include "nmtools/array/index/array_slice.hpp"
#include "nmtools/array/index/ndindex.hpp"
#include "nmtools/array/view/discrete.hpp"
#include "nmtools/array/view/ref.hpp"
#include "nmtools/array/utility/apply_resize.hpp"

namespace nmtools::view
{
    /**
     * @brief Type constructor for array_slice (discrete) view.
     * 
     * @tparam array_t 
     * @tparam indices_t 
     * @tparam dst_shape_t 
     */
    template <typename array_t, typename indices_t, typename dst_shape_t>
    struct array_slice_t
    {
        using array_type   = meta::fwd_operand_t<array_t>;  
        // assume tuple of view (see function)
        using indices_type = const indices_t;
        using shape_type   = const dst_shape_t;

        array_type   array;
        indices_type indices;
        shape_type   dst_shape;

        constexpr array_slice_t(const array_t& array, const indices_t& indices, const dst_shape_t& dst_shape)
            : array(fwd_operand(array))
            , indices(indices)
            , dst_shape(dst_shape)
        {}

        template <typename output_t>
        constexpr auto eval(output_t& output) const
        {
            if constexpr (meta::is_resizable_v<output_t>) {
                ::nmtools::detail::apply_resize(output, dst_shape);
            }

            auto success = true;
            auto dst_indices = index::ndindex(dst_shape);
            for (size_t i=0; i<dst_indices.size(); i++) {
                auto index = dst_indices[i];
                auto src_index = index::array_slice(index, indices);
                // NOTE: currently only support full indexing
                // TODO: check boundary
                // TODO: use mutable_slice for partial indexing
                apply_at(output, index) = detail::apply_at(array,src_index);
            }
            return success;
        } // eval
    }; // array_slice_t

    template <typename array_t, typename index0_t, typename...indices_t>
    constexpr auto array_slice(const array_t& array, const index0_t& index0, const indices_t&...indices)
    {
        auto broadcasted = [&](){
            if constexpr (sizeof...(indices_t)) {
                return broadcast_arrays(index0, indices...);
            } else {
                // avoid array decay
                return view::ref(index0);
            }
        }();
        auto maybe_shape = index::shape_array_slice(shape(array), shape(index0), shape(indices)...);
        using broadcasted_t = decltype(broadcasted);
        using dst_shape_t   = meta::get_maybe_type_t<decltype(maybe_shape)>;
        if constexpr (meta::is_maybe_v<broadcasted_t>) {
            using tuple_t  = meta::get_maybe_type_t<broadcasted_t>;
            using view_t   = discrete_t<array_slice_t,array_t,tuple_t,dst_shape_t>;
            using return_t = nmtools_maybe<view_t>;
            if (broadcasted) {
                return return_t{view_t{{array,*broadcasted,*maybe_shape}}};
            } else {
                return_t {};
            }
        } else {
            using view_t = discrete_t<array_slice_t,array_t,broadcasted_t,dst_shape_t>;
            // NOTE: assume dst_shape is maybe type
            return view_t{{array,broadcasted,*maybe_shape}};
        }
    } // array_slice
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_ARRAY_SLICE_HPP