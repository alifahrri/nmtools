#ifndef NMTOOLS_ARRAY_VIEW_SQUEEZE_HPP
#define NMTOOLS_ARRAY_VIEW_SQUEEZE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/index/squeeze.hpp"
#include "nmtools/array/index/remove_single_dims.hpp"
#include "nmtools/array/index/compute_indices.hpp"
#include "nmtools/array/index/compute_strides.hpp"
#include "nmtools/array/index/compute_offset.hpp"
#include "nmtools/array/shape.hpp"

namespace nmtools::view
{
    /**
     * @addtogroup view
     * Collections of functions/class for view objects
     * @{
     */

    template <typename array_t>
    struct squeeze_t
    {
        using value_type = meta::get_element_type_t<array_t>;
        using const_reference = const value_type&;
        // array type as required by decorator
        using array_type = resolve_array_type_t<array_t>;
        using src_shape_type = meta::remove_cvref_t<decltype(nmtools::shape(meta::declval<array_t>()))>;
        using shape_type = meta::resolve_optype_t<index::shape_squeeze_t,src_shape_type>;

        // "array" member variable is required by decorator, for index view
        array_type array;
        shape_type shape_;

        constexpr squeeze_t(const array_t& array_)
            : array(initialize(array_, meta::as_value_v<array_type>))
            , shape_(index::shape_squeeze(nmtools::shape(array_)))
        {}

        constexpr auto operands() const noexcept
        {
            return nmtools_tuple<array_type>{array};
        }

        constexpr auto attributes() const noexcept
        {
            return nmtools_tuple{};
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
        nmtools_index_attribute
        constexpr auto index(size_types...Is) const
        {
            auto indices = pack_indices(Is...);

            auto squeezed_shape   = shape();
            auto squeezed_strides = index::compute_strides(squeezed_shape);

            auto shape_     = detail::shape(array);
            auto offset     = index::compute_offset(indices,squeezed_strides);
            auto tf_indices = index::compute_indices(offset,shape_);

            return tf_indices;
        } // index
    }; // squeeze_t

    /**
     * @brief remove single dimensional entry from array
     * 
     * @tparam array_t 
     * @param array 
     * @return constexpr auto 
     */
    template <typename array_t>
    constexpr auto squeeze(const array_t& array)
    {
        return decorator_t<squeeze_t,array_t>{{array}};
    } // squeeze
    /* @} */
} // namespace nmtools::view

namespace nmtools::meta
{
    template <typename array_t>
    struct is_ndarray< view::decorator_t<view::squeeze_t,array_t> >
    {
        static inline constexpr auto value = true;
    }; // is_ndarray
}

#endif // NMTOOLS_ARRAY_VIEW_SQUEEZE_HPP