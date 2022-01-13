#ifndef NMTOOLS_ARRAY_VIEW_TRANSPOSE_HPP
#define NMTOOLS_ARRAY_VIEW_TRANSPOSE_HPP

#include "nmtools/constants.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/array/at.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/view/decorator.hpp"

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
        using axes_type  = resolve_attribute_type_t<axes_t>;

        array_type array;
        axes_type axes;

        constexpr transpose_t(const array_t& array, const axes_t& axes=axes_t{})
            : array(initialize(array, meta::as_value_v<array_type>))
            , axes(init_attribute(axes, meta::as_value_v<axes_type>)) {}
        
        /**
         * @brief return the shape of dst (sliced) array
         * 
         * @return constexpr auto 
         */
        constexpr decltype(auto) shape() const noexcept
        {
            auto shape_ = detail::shape(array);
            if constexpr (is_none_v<axes_type>) {
                return nmtools::index::reverse(shape_);
            } else {
                return nmtools::index::gather(shape_, axes);
            }
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

            if constexpr (is_none_v<axes_type>) {
                indices_ = ::nmtools::index::reverse(indices_);
            } else {
                indices_ = ::nmtools::index::scatter(indices_, axes);
            }
            return indices_;
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
        return decorator_t<transpose_t,array_t,axes_t>{{array,axes}};
    } // transpose

    /** @} */ // end group view

} // namespace nmtools::view

namespace nmtools
{

    /**
     * @brief Specialization of fixed_ndarray_shape for transpose view.
     * 
     * @tparam array_t      referenced array type
     * @tparam indices_t    indices type
     */
    template <typename array_t, typename indices_t>
    struct meta::fixed_ndarray_shape<
        view::transpose_t<array_t,indices_t>
    >
    {
        static constexpr auto value = [](){
            if constexpr (!is_fixed_size_ndarray_v<array_t>) {
                return detail::Fail;
            } else if constexpr (is_none_v<indices_t>) {
                constexpr auto src_value = meta::fixed_ndarray_shape_v<array_t>;
                return ::nmtools::index::reverse(src_value);
            } else if constexpr (meta::is_constant_index_array_v<indices_t>) {
                constexpr auto src = meta::fixed_ndarray_shape_v<array_t>;
                constexpr auto dst = indices_t{};
                return ::nmtools::index::gather(src,dst);
            } else {
                // the array is fixed size but the desired indices are not
                return detail::Fail;
            }
        }();
        using value_type = decltype(value);
    }; // fixed_ndarray_shape

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