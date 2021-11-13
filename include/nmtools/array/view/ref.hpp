#ifndef NMTOOLS_ARRAY_VIEW_REF_HPP
#define NMTOOLS_ARRAY_VIEW_REF_HPP

#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/array/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/view/decorator.hpp"

#include <cassert>

namespace nmtools::view
{
    using meta::is_ndarray_v;
    using meta::is_fixed_size_ndarray_v;
    using meta::has_shape_v;
    using meta::has_size_v;
    using meta::has_dim_v;

    /**
     * @addtogroup view
     * Collections of functions/class for view objects
     * @{
     */

    namespace detail {
        /**
         * @brief identity mapping of indices
         * 
         * @tparam size_types 
         * @param indices 
         * @return constexpr auto 
         */
        template <typename...size_types>
        constexpr auto identity(size_types...indices)
        {
            using common_size_t = std::common_type_t<size_types...>;
            using indices_t = std::array<common_size_t,sizeof...(indices)>;
            auto ndindex = indices_t{static_cast<common_size_t>(indices)...};
            return ndindex;
        } // identity
    } // detail

    /**
     * @brief represent constant reference to 1D/2D/ND array.
     * Inspired from <a href="https://llvm.org/doxygen/classllvm_1_1ArrayRef.html">llvm ArrayRef</a>
     * and <a href="https://github.com/tcbrindle/NanoRange/blob/master/include/nanorange/views/ref.hpp">nanorange view ref</a>
     * but specialized for 1D/2D/ND fixed/resizeable array with random access and numpy-like
     * array shape information (dim(), shape())
     * 
     * @tparam array_t non-cvref type of array to be referenced, should be deducable via CTAD
     */
    template <typename array_t>
    struct ref_t
    {
        // get_element_type metafunction should be able to handle
        // ndarray, array2d, array1d etc
        using value_type = meta::get_element_type_t<array_t>;
        using const_reference = const value_type&;
        // array type as required by decorator
        using array_type = resolve_array_type_t<array_t>;

        // const reference to actual array type
        array_type array;

        /**
         * @brief construct ref view
         * 
         */
        constexpr ref_t(const array_t& array)
            : array(initialize<array_type>(array)) {}

        /**
         * @brief identity mapping of indices
         * 
         * @tparam size_types 
         * @param indices 
         * @return constexpr auto 
         */
        template <typename...size_types>
        constexpr auto index(size_types...indices) const
        {
            return detail::identity(indices...);
        } // index
    }; // ref_t

    /**
     * @brief create ref_t object
     * 
     * @tparam array_t type of array
     * @param array array to be referenced
     * @return constexpr auto 
     * @see nmtools::view::ref_t
     */
    template <typename array_t>
    constexpr auto ref(const array_t& array)
    {
        // @note using aggregate initialization 
        // since decorator_t doesn't provide constructor
        return decorator_t<ref_t,array_t>{array};
    } // ref

    /** @} */ // end group view
} // namespace nmtools::view

namespace nmtools
{
    /**
     * @brief specialization of meta::fixed_ndarray_shape for ref view.
     *
     * Only enabled when the referenced array is fixed-size.
     * 
     * @tparam array_t referenced array type
     * @note needs to remove-cvref since the referenced array type returned from make_view may be ref
     * @see nmtools::view::make_view
     */
    template <typename array_t>
    struct meta::fixed_ndarray_shape< view::ref_t<array_t>
        , std::enable_if_t< meta::is_fixed_size_ndarray_v<meta::remove_cvref_t<array_t>> >
    > : meta::fixed_ndarray_shape<meta::remove_cvref_t<array_t>> {};
} // namespace nmtools

namespace nmtools::meta
{
    template <typename array_t>
    struct is_ndarray< view::decorator_t<view::ref_t, array_t> >
    {
        static constexpr auto value = is_ndarray_v<array_t>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_REF_HPP