#ifndef NMTOOLS_ARRAY_VIEW_FLIP_HPP
#define NMTOOLS_ARRAY_VIEW_FLIP_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/index/slice.hpp"
#include "nmtools/array/index/flip.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/utility/apply_at.hpp"
#include "nmtools/array/view/decorator.hpp"

namespace nmtools::view
{
    /**
     * @brief view object for flip
     * 
     * @tparam array_t 
     * @tparam axis_t 
     */
    template <typename array_t, typename axis_t>
    struct flip_t
    {
        using array_type = resolve_array_type_t<array_t>;
        // axis_type is simply given axis (as parameter)
        // assume axis_t can be integer, none, or index array
        using axis_type = resolve_attribute_type_t<axis_t>;
        // deduce shape_type from fn call
        using shape_type  = const decltype(nmtools::shape<true>(meta::declval<array_t>()));
        using dim_type    = const decltype(nmtools::dim<true>(meta::declval<array_t>()));
        using slices_type = const meta::resolve_optype_t<index::flip_slices_t,dim_type,axis_type>;

        // the underlying array
        array_type array;
        // the underlying array's shape
        shape_type shape_;
        dim_type dim_;
        // axes represents underlying array's axes to be flipped
        axis_type axes;
        // under the hood, this view uses index' slice to compute indices
        // for example flip(a) is the same as a[::-1] where a is 1D array
        slices_type slices;

        constexpr flip_t(const array_t& array_, const axis_t& axis)
            : array(initialize<array_type>(array_))
            , shape_(nmtools::shape<true>(array_))
            , dim_(nmtools::dim<true>(array_))
            , axes(init_attribute<axis_type>(axis))
            , slices(index::flip_slices(dim_,axes))
        {}
        
        constexpr auto shape() const
        {
            // note that flipping doesn't change the shape at all
            return shape_;
        } // shape

        constexpr auto dim() const
        {
            return dim_;
        } // dim

        template <typename...size_types>
        constexpr auto index(size_types...indices) const
        {
            // here we directly provide operator() to actually performing operations,
            // instead of returning (transformed) index only
            auto flip_indices = pack_indices(indices...);

            auto indices_ = index::apply_slice(flip_indices,shape_,slices);
            return indices_;
        } // operator()
    }; // flip_t

    /**
     * @brief Reverse the order of elements of given array according to specified axis.
     *
     * Axis can be None, a single integer, or index_array.
     * For None axis, reverse all original axis.
     * 
     * @tparam array_t 
     * @tparam axis_t 
     * @param array array in which its elements are to be reversed
     * @param axis axis to operate
     * @return constexpr auto 
     */
    template <typename array_t, typename axis_t>
    constexpr inline auto flip(const array_t& array, const axis_t& axis)
    {
        using view_t = decorator_t<flip_t,array_t,axis_t>;
        return view_t{{array,axis}};
    } // flip
} // namespace nmtools::view

namespace nmtools::meta
{
    template <typename array_t, typename axis_t>
    struct is_ndarray< view::decorator_t< view::flip_t, array_t, axis_t >>
    {
        static constexpr auto value = is_ndarray_v<array_t>;
    };
} // namespace nmtools

#endif // NMTOOLS_ARRAY_VIEW_FLIP_HPP