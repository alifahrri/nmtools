#ifndef NMTOOLS_ARRAY_VIEW_HPP
#define NMTOOLS_ARRAY_VIEW_HPP

#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/utility/shape.hpp"

#include <cassert>

namespace nmtools::view
{
    using traits::is_array1d_v;
    using traits::is_array2d_v;
    using traits::is_ndarray_v;
    using traits::is_fixed_size_vector_v;
    using traits::is_fixed_size_matrix_v;
    using traits::is_fixed_ndarray_v;
    using traits::has_shape_v;
    using traits::has_size_v;
    using traits::has_dim_v;

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
            auto indices_pack = indices_t{static_cast<common_size_t>(indices)...};
            return indices_pack;
        } // identity
    } // detail

    /**
     * @brief represent constant reference to 1D/2D/ND array.
     * Inspired from <a href="https://llvm.org/doxygen/classllvm_1_1ArrayRef.html">llvm ArrayRef</a>
     * and <a href="https://github.com/tcbrindle/NanoRange/blob/master/include/nanorange/views/ref.hpp">nanorange view ref</a>
     * but specialized for 1D/2D/ND fixed/resizeable array with random access and numpy-like
     * array shape information (dim(), shape())
     * 
     * @tparam Array non-cvref type of array to be referenced, should be deducable via CTAD
     */
    template <typename Array>
    struct ref_t
    {
        static_assert(
            is_array1d_v<Array> || is_array2d_v<Array> || is_ndarray_v<Array>,
            "ref_t only support 1D, 2D, or ndarray for now"
        );
        // get_element_type metafunction should be able to handle
        // ndarray, array2d, array1d etc
        using value_type = meta::get_element_type_t<Array>;
        using const_reference = const value_type&;
        static inline constexpr bool is_fixed_size = is_fixed_size_vector_v<Array> || is_fixed_size_matrix_v<Array> || is_fixed_ndarray_v<Array>;

        // const reference to actual array type
        const Array& array;

        /**
         * @brief construct ref view
         * 
         */
        constexpr ref_t(const Array& array) : array(array) {}

        /**
         * @brief return compile-time boolean indicating the referenced array has compile-time shape
         * 
         * @return constexpr auto 
         * @see nmtools::traits::is_fixed_size_vector
         * @see nmtools::traits::is_fixed_size_matrix
         * @see nmtools::traits::is_fixed_ndarray
         */
        static constexpr auto is_fixed_shape()
        {
            return is_fixed_size_vector_v<Array> 
                || is_fixed_size_matrix_v<Array>
                || is_fixed_ndarray_v<Array>;
        } // is_fixed_shape

        /**
         * @brief return the dimensionality of the referred array
         * 
         * @tparam array_t the type of array
         * @param array 
         * @return constexpr auto 
         * @note marked as static fn here to properly handle fixed_size array
         * @see nmtools::traits::has_dim
         * @see nmtools::traits::is_array2d
         * @see nmtools::traits::is_array1d
         * @see nmtools::array_dim
         */
        template <typename array_t>
        static constexpr auto dim(const array_t& array)
        {
            if constexpr (has_dim_v<array_t>)
                return array.dim();
            // @note since is_array2d_v and is_array1d_v may not be mutually exclusive prefer array2d first
            else if constexpr (is_array2d_v<array_t>)
                return 2;
            else if constexpr (is_array1d_v<array_t>)
                return 1;
            else
                return array_dim(array);
        } // dim()

        /**
         * @brief return the dimensionality of the referred array
         * 
         * @return constexpr auto 
         */
        constexpr auto dim() const noexcept
        {
            return dim(array);
        } // dim()

        /**
         * @brief return the shape of this array
         * 
         * @return constexpr auto 
         * @see nmtools::vector_size
         * @see nmtools::matrix_size
         * @see nmtools::array_shape
         */
        constexpr auto shape() const
        {
            if constexpr (has_shape_v<Array>)
                return array.shape();
            // @note since is_array2d_v and is_array1d_v may not be mutually exclusive, check for array2d first
            else if constexpr (is_array2d_v<Array>)
                return matrix_size(array);
            // @note for 1d array, wrap return value in array for generalization
            else if constexpr (is_array1d_v<Array> && has_size_v<Array>)
                return std::array{array.size()};
            else if constexpr (is_array1d_v<Array>)
                return std::array{vector_size(array)};
            else
                return array_shape(array);
        } // shape

        /**
         * @brief immutable element acces to the referenced array
         * 
         * @tparam size_types size type(s) to array
         * @param indices 
         * @return constexpr const_reference 
         * @todo make error handling configurable, e.g. throw/assert/optional
         * @see nmtools::at
         */
        template <typename...size_types>
        constexpr const_reference operator()(size_types...indices)
        {
            constexpr auto n = sizeof...(size_types);
            // @note for fixed size, it is necessary to pass Array{} (value initialization) to dim since `this` may not be constant exprression
            // @see https://en.cppreference.com/w/cpp/language/value_initialization
            if constexpr (is_fixed_shape())
                static_assert (dim(Array{})==n);
            else
                assert (dim(array)==n);
            // call at to referred object, not to this
            return at(array, indices...);
        } // operator()

    }; // ref_t

    /**
     * @brief create ref_t object
     * 
     * @tparam Array type of array
     * @param array array to be referenced
     * @return constexpr auto 
     * @see nmtools::view::ref_t
     */
    template <typename Array>
    constexpr auto ref(const Array& array)
    {
        return ref_t(array);
    } // ref

    /** @} */ // end group view
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_HPP