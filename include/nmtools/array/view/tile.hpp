#ifndef NMTOOLS_ARRAY_VIEW_TILE_HPP
#define NMTOOLS_ARRAY_VIEW_TILE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/index/tile.hpp"
#include "nmtools/array/shape.hpp"

namespace nmtools::view
{
    /**
     * @brief Type constructor for tile view.
     * 
     * @tparam array_t array type to be referenced.
     * @tparam reps_t  reps type
     */
    template <typename array_t, typename reps_t>
    struct tile_t
    {
        using value_type = meta::get_element_type_t<array_t>;
        using const_reference = const value_type&;
        using array_type = resolve_array_type_t<array_t>;
        using src_shape_type = decltype(nmtools::shape</*force_constant_index*/true>(meta::declval<array_t>()));
        using dst_shape_type = meta::resolve_optype_t<index::shape_tile_t,src_shape_type,reps_t>;
        using reps_type  = resolve_attribute_type_t<reps_t>;
        
        array_type     array;
        reps_type      reps;
        dst_shape_type shape_;

        constexpr tile_t(const array_t& array_, const reps_t& reps)
            : array(initialize(array_, meta::as_value_v<array_type>))
            , reps(init_attribute(reps, meta::as_value_v<reps_type>))
            , shape_(index::shape_tile(nmtools::shape</*force_constant_index*/true>(array_),reps))
        {}
        
        constexpr decltype(auto) shape() const
        {
            return shape_;
        } // shape

        constexpr decltype(auto) dim() const
        {
            return len(shape());
        } // dim

        template <typename...size_types>
        constexpr auto index(size_types...indices) const
        {
            // tile view is just indexing view, no value transform
            auto indices_ = pack_indices(indices...);
            auto shape_   = detail::shape(array);
            return index::tile(shape_,reps,indices_);
        } // index
    }; // tile_t

    /**
     * @brief Construct a view by repeating array the number of times given by reps.
     * 
     * This follow numpy's tile, that is, if reps has length d, the result will have dimension of max(d, dim(array)).
     * 
     * @tparam array_t 
     * @tparam reps_t 
     * @param array The input array
     * @param reps The number of repetitions of array along each axis.
     * @return constexpr auto 
     */
    template <typename array_t, typename reps_t>
    constexpr auto tile(const array_t& array, const reps_t& reps)
    {
        return decorator_t<tile_t,array_t,reps_t>{{array,reps}};
    } // tile
} // namespace nmtools::view

namespace nmtools::meta
{
    // TODO: remove
    template <typename array_t, typename reps_t>
    struct fixed_size<
        view::decorator_t<view::tile_t, array_t, reps_t>
    >
    {
        using view_type  = view::decorator_t<view::tile_t, array_t, reps_t>;
        using shape_type = decltype(declval<view_type>().shape());

        static constexpr auto value = [](){
            // reps may change shape, so change size
            if constexpr (is_constant_index_array_v<shape_type>) {
                return index::product(shape_type{});
            } else {
                return error::FIXED_SIZE_UNSUPPORTED<view_type>{};
            }
        }();
    }; // fixed_size

    template <typename array_t, typename reps_t>
    struct bounded_size<
        view::decorator_t<view::tile_t, array_t, reps_t>
    > : fixed_size<
        view::decorator_t<view::tile_t, array_t, reps_t>
    > {}; // bounded_size

    template <typename array_t, typename reps_t>
    struct is_ndarray< view::decorator_t< view::tile_t, array_t, reps_t >>
        : is_ndarray<array_t> {};
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_TILE_HPP