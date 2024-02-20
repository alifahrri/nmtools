#ifndef NMTOOLS_ARRAY_VIEW_TRANSPOSE_HPP
#define NMTOOLS_ARRAY_VIEW_TRANSPOSE_HPP

#include "nmtools/constants.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/array/at.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/view/decorator.hpp"

#include "nmtools/array/index/transpose.hpp"
#include "nmtools/array/index/scatter.hpp"
#include "nmtools/array/index/gather.hpp"
#include "nmtools/array/index/reverse.hpp"

namespace nmtools::view
{

    /**
     * @addtogroup view
     * Collections of functions/class for view objects
     * @{
     */
    
    /**
     * @brief Returns a view of the array with axes transposed.
     * 
     * For a 1-D array this has no effect, as a transposed vector is simply the same vector.
     * If axes is given, the indices are permuted by given axis, simply reverese otherwise.
     * Inspired by <a href="https://numpy.org/doc/stable/reference/generated/numpy.ndarray.transpose.html#numpy.ndarray.transpose">numpy</a>.
     * 
     * @tparam array_t array type to be transpose-viewed. only support array1d/array2d for now
     * @tparam axes_t type of axes, deducible via ctad
     * @todo support for compile-time axes (e.g. tuple<integral_constant<...>...>)
     */
    template <typename array_t, typename axes_t=none_t>
    struct transpose_t
    {
        using value_type = meta::get_element_type_t<array_t>;
        using const_reference = const value_type&;
        // array type as required by decorator
        using array_type = resolve_array_type_t<array_t>;
        using src_shape_type = decltype(nmtools::shape</*force_constant_index*/true>(meta::declval<array_t>()));
        using dst_shape_type = meta::resolve_optype_t<index::shape_transpose_t,src_shape_type,axes_t>;
        using axes_type  = resolve_attribute_type_t<axes_t>;

        array_type      array;
        axes_type       axes;
        dst_shape_type  shape_;

        constexpr transpose_t(const array_t& array_, const axes_t& axes=axes_t{})
            : array(initialize(array_, meta::as_value_v<array_type>))
            , axes(init_attribute(axes, meta::as_value_v<axes_type>))
            , shape_(index::shape_transpose(nmtools::shape</*force_constant_index*/true>(array_),axes))
        {}
        
        constexpr auto operands() const noexcept
        {
            return nmtools_tuple<array_type>{array};
        }

        constexpr auto attributes() const noexcept
        {
            return nmtools_tuple{axes};
        }

        /**
         * @brief return the shape of dst (sliced) array
         * 
         * @return constexpr auto 
         */
        constexpr decltype(auto) shape() const noexcept
        {
            return shape_;
        } // shape
        
        /**
         * @brief transpose index mapping
         * 
         * @tparam size_types variadic template parameter for indices
         * @param indices 
         * @return constexpr auto 
         */
        template <typename...size_types>
        constexpr auto index(size_types...indices) const
        {
            auto indices_ = pack_indices(indices...);

            // TODO: move to index/transpose.hpp
            if constexpr (is_none_v<axes_type>) {
                return ::nmtools::index::reverse(indices_);
            } else {
                return ::nmtools::index::scatter(indices_, axes);
            }
        } // index
    }; // transpose_t

    /**
     * @brief make transpose view
     * 
     * @tparam array_t 
     * @tparam axes_t 
     * @param array 
     * @param axes 
     * @return constexpr auto 
     */
    template <typename array_t, typename axes_t=none_t>
    constexpr auto transpose(const array_t& array, const axes_t& axes=axes_t{})
    {
        #if !defined(NMTOOLS_NO_BASE_ACCESS)
        return decorator_t<transpose_t,array_t,axes_t>{{array,axes}};
        #else // NMTOOLS_NO_BASE_ACCESS
        using return_t = decorator_t<transpose_t,array_t,axes_t>;
        using view_t = transpose_t<array_t,axes_t>;
        return return_t{view_t{array,axes}};
        #endif // NMTOOLS_NO_BASE_ACCESS
    } // transpose

    /** @} */ // end group view

} // namespace nmtools::view

namespace nmtools
{

    /**
     * @brief specialization of meta::is_ndarray for transpose view and arbitray axes
     *
     * Only enabled when array_t is fixed size, this specialization is necessary since
     * axes_t may holds runtime value hence fixed_ndarray_shape becomes unavailable.
     * 
     * @tparam array_t 
     * @tparam axes_t 
     */
    template <typename array_t, typename axes_t>
    struct meta::is_ndarray< view::decorator_t<view::transpose_t,array_t,axes_t> >
     : meta::is_ndarray<array_t> {};
} // namespace nmtools

#endif // NMTOOLS_ARRAY_VIEW_TRANSPOSE_HPP