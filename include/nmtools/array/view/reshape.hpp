#ifndef NMTOOLS_ARRAY_VIEW_RESHAPE_HPP
#define NMTOOLS_ARRAY_VIEW_RESHAPE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/view/flatten.hpp"

#include "nmtools/array/index/product.hpp"
#include "nmtools/array/index/compute_indices.hpp"
#include "nmtools/array/index/compute_offset.hpp"
#include "nmtools/array/index/compute_strides.hpp"
#include "nmtools/assert.hpp"

#include "nmtools/utils/isequal.hpp"

namespace nmtools::view
{
    /**
     * @addtogroup view
     * Collections of functions/class for view objects
     * @{
     */
    
    /**
     * @brief reshape view type
     * 
     * @tparam array_t type of array to be reshaped
     * @tparam shape_t type of new shape
     */
    template <typename array_t, typename shape_t>
    struct reshape_t
    {
        using value_type = meta::get_element_type_t<array_t>;
        using const_reference = const value_type&;
        // array type as required by decorator
        using array_type = resolve_array_type_t<array_t>;
        using shape_type = resolve_attribute_type_t<shape_t>;
        
        array_type array;
        shape_type new_shape;

        /**
         * @brief construct reshape view
         * 
         */
        constexpr reshape_t(const array_t& array, const shape_t& shape)
            : array(initialize(array, meta::as_value_v<array_type>))
            , new_shape(init_attribute(shape, meta::as_value_v<shape_type>)) {}
        
        /**
         * @brief simply return size of new_shape
         * 
         * @return constexpr auto 
         */
        constexpr auto dim() const noexcept
        {
            return len(new_shape);
        } // dim
        
        /**
         * @brief simply return new_shape
         * 
         * @return constexpr decltype(auto) 
         */
        constexpr decltype(auto) shape() const noexcept
        {
            // TODO: support negative shape dimension
            // NOTE: must normalize raw bounded array
            return new_shape;
        } // shape

        /**
         * @brief index transformer for reshape view
         * 
         * @tparam size_types
         * @param indices variadic of integral type or single packed indices
         * @return constexpr auto transformed indices, mapped to original array shape
         */
        template <typename...size_types>
        constexpr auto index(size_types...indices) const
        {
            auto indices_ = pack_indices(indices...);
            auto shape_   = detail::shape(array); // src shape
            auto strides  = index::compute_strides(new_shape);
            auto offset   = index::compute_offset(indices_,strides);
            auto tf_idx   = index::compute_indices(offset,shape_);
            return tf_idx;
        } // index
    }; // reshape_t

    /**
     * @brief return reshape view
     * 
     * @tparam array_t 
     * @tparam shape_t 
     * @param array array to be reshaped
     * @param new_shape 
     * @return constexpr auto reshape view
     */
    template <typename array_t, typename shape_t>
    constexpr auto reshape(const array_t& array, const shape_t& new_shape)
    {
        auto shape = ::nmtools::shape(array);
        auto old_numel = index::product(shape);
        auto new_numel = index::product(new_shape);
        // TODO: better error handling
        nmtools_assert( utils::isequal(old_numel,new_numel)
            , "unsupported reshape, mismatched number of elements"
        );
        return decorator_t<reshape_t,array_t,shape_t>{{array,new_shape}};
    } // reshape

    /** @} */ // end group view

} // namespace nmtools::view

namespace nmtools
{
    /**
     * @brief specialization fo is_ndarray for reshape view
     *
     * Note that this specialization bypass the specialization from decorator_t
     * by being more specific on view_t (reshape_t in this case)
     * 
     * @tparam array_t referenced array of reshape view
     * @tparam shape_t type of new shape of reshape view
     */
    template <typename array_t, typename shape_t>
    struct meta::is_ndarray< view::decorator_t<view::reshape_t, array_t, shape_t> >
    {
        static constexpr auto get()
        {
            using view_type  = view::decorator_t<view::reshape_t, array_t, shape_t>;
            using array_type = typename view_type::array_type;
            if constexpr (meta::is_array2d_v<view_type>)
                return true;
            else if constexpr (meta::is_array1d_v<view_type>)
                return true;
            else return meta::is_ndarray_v<meta::remove_cvref_t<array_type>>;
        } // get()

        static inline constexpr auto value = get();
        using value_type = decltype(value);
    }; // is_ndarray

    /**
     * @brief specialization of meta::fixed_ndarray_shape for reshape view
     *
     * Enabled for fixed size ndarray.
     * Results in fail_t when shape_t is not integral_constant.
     * 
     * @tparam array_t 
     * @tparam shape_t 
     */
    template <typename array_t, typename shape_t>
    struct meta::fixed_ndarray_shape<
        view::reshape_t< array_t, shape_t>
    >
    {
        static constexpr auto value = []()
        {
            // for now, simply return the new shape
            // when both src shape and dst shape is known at compile time.
            // it should be possible to allow array with runtime shape
            // to be reshaped with fixed shape.
            if constexpr (is_fixed_size_ndarray_v<array_t> && (is_constant_index_v<shape_t> || is_constant_index_array_v<shape_t>)) {
                return shape_t{};
            } else {
                return detail::Fail;
            }
        }();
        using value_type = detail::fail_to_void_t<remove_cvref_t<decltype(value)>>;
    }; // fixed_ndarray_shape

} // namespace nmtools

#endif // NMTOOLS_ARRAY_VIEW_RESHAPE_HPP