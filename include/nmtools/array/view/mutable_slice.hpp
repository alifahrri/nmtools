#ifndef NMTOOLS_ARRAY_VIEW_MUTABLE_SLICE_HPP
#define NMTOOLS_ARRAY_VIEW_MUTABLE_SLICE_HPP

#include "nmtools/array/view/slice.hpp"
#include "nmtools/array/meta.hpp"

#include <tuple>

namespace nmtools::view
{
    using meta::is_array1d_v;
    using meta::is_array2d_v;
    using meta::is_ndarray_v;
    using meta::is_fixed_size_vector_v;
    using meta::is_fixed_size_matrix_v;
    using meta::is_fixed_size_ndarray_v;
    using meta::has_shape_v;
    using meta::has_size_v;
    using meta::has_dim_v;

    /**
     * @addtogroup view
     * Collections of functions/class for view objects
     * @{
     */

    /**
     * @brief represent sliced reference to 1D/2D/ND array.
     * 
     * @tparam Array non-cvref type of array to be referenced, should be deducable via CTAD
     */
    template <typename Array, typename start_t, typename stop_t>
    struct mutable_slice_t
    {
        static_assert(
            is_array1d_v<Array> || is_array2d_v<Array>,
            "mutable_slice_t only support 1D & 2D array for now"
        );
        // get_element_type metafunction should be able to handle
        // ndarray, array2d, array1d etc
        using value_type = meta::get_element_type_t<Array>;
        using const_reference = const value_type&;
        // array type as required by decorator
        using array_type = Array&;
        using offset_type = detail::get_offset_type_t<array_type,start_t,stop_t>;

        // const reference to actual array type
        array_type array;
        start_t start;
        stop_t stop;
        offset_type offset;

        /**
         * @brief construct mutable slice view
         * 
         */
        constexpr mutable_slice_t(array_type array, start_t start, stop_t stop)
            : array(array), start(start), stop(stop)
        {
            offset = detail::offset(array,start,stop);
        } // mutable_slice_t

        /**
         * @brief return the shape of dst (sliced) array
         * 
         * @return constexpr auto 
         */
        constexpr auto shape() const noexcept
        {
            const auto& start = std::get<0>(offset);
            const auto& stop  = std::get<1>(offset);
            return detail::sub(stop,start);
        } // shape

        /**
         * @brief index mapping from dst (sliced) indices to src (referenced) indices
         * 
         * @tparam size_types 
         * @param indices 
         * @return constexpr auto 
         * @todo provide a way to make assertion optional
         */
        template <typename...size_types>
        constexpr auto index(size_types...indices)
        {
            const auto& start = std::get<0>(offset);
            const auto& stop  = std::get<1>(offset);
            auto mapped_indices = detail::slice(start,stop,indices...);
            assert( detail::all(detail::lt(mapped_indices,stop))
                //, "out of bounds indices"
            );
            return mapped_indices;
        } // index

        template <typename...size_types>
        constexpr auto index(size_types...indices) const
        {
            const auto& start = std::get<0>(offset);
            const auto& stop  = std::get<1>(offset);
            auto mapped_indices = detail::slice(start,stop,indices...);
            assert( detail::all(detail::lt(mapped_indices,stop))
                //, "out of bounds indices"
            );
            return mapped_indices;
        } // index
    }; // mutable_slice_t

    /**
     * @brief create mutable_slice_t object
     * 
     * @tparam array_t type of array
     * @param array array to be referenced
     * @return constexpr auto 
     * @see nmtools::view::mutable_slice_t
     */
    template <typename array_t, typename start_t, typename stop_t>
    constexpr auto mutable_slice(array_t& array, const start_t& start, const stop_t& stop)
    {
        // @note using aggregate initialization 
        // since decorator_t doesn't provide constructor
        return decorator_t<mutable_slice_t,array_t,start_t,stop_t>{mutable_slice_t(array, start, stop)};
    } // mutable_slice

    /** @} */ // end group view
} // namespace nmtools::view

namespace nmtools
{
    /**
     * @brief specializtion of meta::fixed_vector_size for slice view.
     * 
     * @tparam array_t 
     * @tparam start_t 
     * @tparam stop_t 
     */
    template <typename array_t, typename start_t, typename stop_t>
    struct meta::fixed_vector_size< view::mutable_slice_t<array_t,start_t,stop_t>
        , std::enable_if_t<
            // @note use std::conjuction to short circuit
            // since type_list_conjunction requires tparam to have tuple_size
            std::conjunction_v<
                meta::is_fixed_size_vector<meta::remove_cvref_t<array_t>>,
                meta::has_tuple_size<start_t>,
                meta::type_list_conjunction<start_t,meta::is_integral_constant>,
                meta::has_tuple_size<stop_t>,
                meta::type_list_conjunction<stop_t,meta::is_integral_constant>
            >
        >
    > : meta::fixed_vector_size< meta::remove_cvref_t<array_t> > {};

    /**
     * @brief specialization of meta::fixed_matrix_size for slice view.
     * 
     * @tparam array_t 
     * @tparam start_t 
     * @tparam stop_t 
     */
    template <typename array_t, typename start_t, typename stop_t>
    struct meta::fixed_matrix_size< view::mutable_slice_t<array_t,start_t,stop_t>
        , std::enable_if_t<
            std::conjunction_v<
                meta::is_fixed_size_matrix<meta::remove_cvref_t<array_t>>,
                meta::has_tuple_size<start_t>,
                meta::type_list_conjunction<start_t,meta::is_integral_constant>,
                meta::has_tuple_size<stop_t>,
                meta::type_list_conjunction<stop_t,meta::is_integral_constant>
            >
        >
    > : meta::fixed_matrix_size< meta::remove_cvref_t<array_t> > {};
} // namespace nmtools

#endif // NMTOOLS_ARRAY_VIEW_MUTABLE_SLICE_HPP