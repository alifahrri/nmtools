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
    template <typename array_t, typename axis_t>
    struct expand_dims_t
    {
        using value_type = meta::get_element_type_t<array_t>;
        using const_reference = const value_type&;
        // array type as required by decorator
        using array_type = resolve_array_type_t<array_t>;
        using axis_type  = resolve_attribute_type_t<axis_t>;

        array_type array;
        axis_type  axis;

        constexpr expand_dims_t(const array_t& array, const axis_t& axis)
            : array(initialize(array, meta::as_value_v<array_type>))
            , axis(init_attribute(axis, meta::as_value_v<axis_type>)) {}
        
        constexpr auto shape() const noexcept
        {
            auto shape_ = detail::shape(array);
            // TODO: maybe rename index::expand_dims to index::shape_expand_dims
            auto newshape = index::expand_dims(shape_,axis);
            return newshape;
        } // shape

        constexpr auto dim() const noexcept
        {
            auto shape_ = shape();
            auto dim_   = ::nmtools::shape(shape_);
            return at(dim_, 0);
        } // dim

        template <typename...size_types>
        constexpr auto index(size_types...Is) const
        {
            auto indices = pack_indices(Is...);

            // TODO: maybe move index computation to index::expand_dims
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

    /**
     * @brief Infer the shape of expand_dims view at compile-time.
     * 
     * @tparam array_t 
     * @tparam axis_t 
     */
    template <typename array_t, typename axis_t>
    struct fixed_ndarray_shape< expand_dims_t<array_t,axis_t>
    >
    {
        static inline constexpr auto value = [](){
            if constexpr (is_fixed_size_ndarray_v<array_t> &&
                (is_constant_index_array_v<axis_t> || is_constant_index_v<axis_t>))
            {
                constexpr auto shape = fixed_ndarray_shape_v<array_t>;
                constexpr auto axis  = [](){
                    if constexpr (is_constant_index_v<axis_t>) {
                        // use std::tuple for now
                        return std::tuple{axis_t{}};
                    } else {
                        return axis_t{};
                    }
                }();
                // TODO: maybe rename index::expand_dims to index::shape_expand_dims
                return index::expand_dims(shape,axis);
            } else {
                return detail::Fail;
            }
        }();
        using value_type = detail::fail_to_void_t<remove_cvref_t<decltype(value)>>;
    }; // fixed_ndarray_shape

    template <typename array_t, typename axis_t>
    struct is_ndarray< decorator_t<expand_dims_t,array_t,axis_t> >
    {
        static inline constexpr auto value = true;
    }; // is_ndarray

} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_EXPAND_DIMS_HPP