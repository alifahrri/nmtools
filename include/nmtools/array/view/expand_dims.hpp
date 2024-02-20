#ifndef NMTOOLS_ARRAY_VIEW_EXPAND_DIMS_HPP
#define NMTOOLS_ARRAY_VIEW_EXPAND_DIMS_HPP

#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/index/expand_dims.hpp"
#include "nmtools/array/index/compute_indices.hpp"
#include "nmtools/array/index/compute_strides.hpp"
#include "nmtools/array/index/compute_offset.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/shape.hpp"

namespace nmtools::view
{
    /**
     * @brief Type constructor for expand_dims view
     * 
     * @tparam array_t 
     * @tparam axis_t 
     */
    template <typename array_t, typename axis_t>
    struct expand_dims_t
    {
        using value_type = meta::get_element_type_t<array_t>;
        // array type as required by decorator
        using array_type = resolve_array_type_t<array_t>;
        using axis_type  = resolve_attribute_type_t<axis_t>;
        using src_shape_type = meta::remove_cvref_t<decltype(nmtools::shape(meta::declval<array_t>()))>;
        using shape_type = meta::resolve_optype_t<index::shape_expand_dims_t,src_shape_type,axis_t>;

        array_type array;
        axis_type  axis;
        shape_type shape_;

        constexpr expand_dims_t(const array_t& array_, const axis_t& axis)
            : array(initialize(array_, meta::as_value_v<array_type>))
            , axis(init_attribute(axis, meta::as_value_v<axis_type>))
            , shape_(index::shape_expand_dims(nmtools::shape(array_),axis))
        {}

        constexpr auto operands() const noexcept
        {
            return nmtools_tuple<array_type>{array};
        }

        constexpr auto attributes() const noexcept
        {
            return nmtools_tuple{axis};
        }
        
        constexpr auto shape() const noexcept
        {
            return shape_;
        } // shape

        constexpr auto dim() const noexcept
        {
            return len(shape());
        } // dim

        template <typename...size_types>
        constexpr auto index(size_types...Is) const
        {
            auto indices = pack_indices(Is...);

            // TODO: maybe move index computation to index::shape_expand_dims
            auto expanded_shape   = shape();
            auto squeezed_strides = index::compute_strides(expanded_shape);

            auto shape_     = detail::shape(array);
            auto offset     = index::compute_offset(indices,squeezed_strides);
            auto tf_indices = index::compute_indices(offset,shape_);

            return tf_indices;
        } // index
    }; // expand_dims_t

    /**
     * @brief expand the shape of an array
     * 
     * @tparam array_t array_like
     * @tparam axis_t integer or array of integer
     * @param array input array
     * @param axis Position in the expanded axes where the new axis (or axes) is placed.
     * @return constexpr auto expand_dims view
     */
    template <typename array_t, typename axis_t>
    constexpr auto expand_dims(const array_t& array, const axis_t& axis)
    {
        return decorator_t<expand_dims_t,array_t,axis_t>{{array,axis}};
    } // expand_dims

} // namespace nmtools::view

namespace nmtools::meta
{
    using view::decorator_t;
    using view::expand_dims_t;

    template <typename array_t, typename axis_t>
    struct is_ndarray< decorator_t<expand_dims_t,array_t,axis_t> >
    {
        static inline constexpr auto value = true;
    }; // is_ndarray

} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_EXPAND_DIMS_HPP