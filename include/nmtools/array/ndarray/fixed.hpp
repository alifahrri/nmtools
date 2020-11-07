#ifndef NMTOOLS_ARRAY_NDARRAY_FIXED_HPP
#define NMTOOLS_ARRAY_NDARRAY_FIXED_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/detail.hpp"
#include "nmtools/array/meta.hpp" // meta::fixed_matrix_size etc.

#include <array>
#include <tuple>

/**
 * @defgroup array 
 * collections of array functions and structs.
 * 
 */

namespace nmtools::array {

    /**
     * @addtogroup Fixed Fixed Array
     * @ingroup array
     * @{
     */

    /**
     * @brief sample implementation of n-dimensional array,
     * trying to mimic numpy ndarray layout @cite NumPy_ndarray_layout
     * 
     * @tparam T element type of fixed_ndarray
     * @tparam Shape1 the size of 1st axis of fixed_ndarray
     * @tparam ShapeN the sizes of the rest axes of fixed_ndarray
     */
    template <typename T, size_t Shape1, size_t...ShapeN>
    struct fixed_ndarray
    {
        // godbolt : https://godbolt.org/z/xP31vz
        /**
         * @brief return the number of dimension
         * 
         * @return constexpr auto 
         */
        static constexpr auto dim()
        {
            return sizeof...(ShapeN) + 1;
        }
        static inline constexpr auto dim_ = dim();

        /**
         * @brief return the shape information
         * 
         * @return constexpr auto 
         */
        static constexpr auto shape()
        {
            return std::array<size_t,dim_>{Shape1,ShapeN...};
        }
        static inline constexpr auto shape_ = shape();

        /**
         * @brief return the number of elements
         * 
         * @return constexpr auto 
         */
        static constexpr auto numel()
        {
            size_t numel_ = 1;
            for (auto s : shape_)
                numel_ *= s;
            return numel_;
        }
        static inline constexpr auto numel_ = numel();

        /**
         * @brief return the strides information
         * 
         * @return constexpr auto 
         */
        static constexpr auto strides()
        {
            auto stride = std::array<size_t,dim()>{};
            for (size_t i=0; i<dim(); i++)
                stride[i] = detail::stride(shape_,i);
            return stride;
        }
        static inline constexpr auto strides_ = strides();

        // constexpr fixed_ndarray() {}

        using this_type  = fixed_ndarray<T,Shape1,ShapeN...>;
        // underlying flat storage
        using data_type  = std::array<T,numel_>;
        // element/value type
        using value_type = T;
        // single axis type
        using size_type  = size_t;
        using reference  = value_type&;
        using const_reference = const value_type&;

        data_type data;

        /**
         * @brief mutable access to element
         * 
         * @tparam size 
         * @param n 1st index of element to be accessed
         * @param ns the rest of indices of element to be accessed
         * @return constexpr reference 
         * @note use sfinae instead of static assertion to make sure
         * expression checking (`meta::has_funcnd_v<...>`) works
         */
        template <typename...size>
        constexpr auto operator()(size_type n, size...ns)
            -> std::enable_if_t<sizeof...(ns)==sizeof...(ShapeN),reference>
        {
            using common_size_t = std::common_type_t<size_type,size...>;
            auto indices = std::array<common_size_t,sizeof...(ns)+1>{n,static_cast<common_size_t>(ns)...};
            auto offset = detail::compute_offset(strides_, indices);
            return data[offset];
        } // operator()

        /**
         * @brief immutable access to element
         * 
         * @tparam size 
         * @param n 1st index of element to be accessed
         * @param ns the rest of indices of element to be accessed
         * @return constexpr const_reference 
         * @note use sfinae instead of static assertion to make sure
         * expression checking (`meta::has_funcnd_v<...>`) works
         */
        template <typename...size>
        constexpr auto operator()(size_type n, size...ns) const
            -> std::enable_if_t<sizeof...(ns)==sizeof...(ShapeN),const_reference>
        {
            using common_size_t = std::common_type_t<size_type,size...>;
            auto indices = std::array<common_size_t,sizeof...(ns)+1>{n,static_cast<common_size_t>(ns)...};
            auto offset = detail::compute_offset(strides_, indices);
            return data[offset];
        } // operator()

        // constexpr decltype(auto) operator=(this_type&& other)
        // {
        //     this->data = other.data;
        //     return *this;
        // }

        template <typename ndarray_t>
        constexpr decltype(auto) operator=(ndarray_t&& rhs);

        /**
         * @brief provides assignment operator from nested std::array
         * 
         * @param rhs nested std array to be copied
         * @return constexpr decltype(auto) 
         */
        constexpr decltype(auto) operator=(meta::make_nested_raw_array_t<T,Shape1,ShapeN...>&& rhs)
        {
            using nested_t = meta::make_nested_raw_array_t<T,Shape1,ShapeN...>;
            return this->template operator=<nested_t>(std::forward<nested_t>(rhs));
        }
    }; // struct fixed_ndarray

    /** @} */ // end group fixed array
} // namespace nmtools::array

namespace nmtools
{
    /**
     * @ingroup utility
     * 
     */

    /**
     * @brief return the shape of fixed_ndarray, which is known at compile-time
     * 
     * @tparam T element type of fixed_ndarray
     * @tparam Shape1 the size of element at 1st axis
     * @tparam ShapeN the sizes of the element for the rest of axes
     * @param a ndarray
     * @return constexpr auto 
     */
    template <typename T, size_t Shape1, size_t...ShapeN>
    constexpr auto array_shape(const array::fixed_ndarray<T,Shape1,ShapeN...>& a)
    {
        return a.shape();
    } // array_shape

    /**
     * @brief return the dimensionality of fixed_ndarray, which is known at compile-time
     * 
     * @tparam T 
     * @tparam Shape 
     * @param a 
     * @return constexpr auto 
     */
    template <typename T, size_t...Shape>
    constexpr auto array_dim(const array::fixed_ndarray<T,Shape...>& a)
    {
        return a.dim();
    } // 

    /** @} */ // end group utility

    /**
     * @brief specialization of fixed_ndarray for meta::fixed_matrix_size array traits
     * 
     * @tparam T element type of fixed_ndarray
     * @tparam Rows number of elements of 1st axis of fixed_ndarray
     * @tparam Cols number of elements of 2nd axis of fixed_ndarray
     */
    template <typename T, size_t Rows, size_t Cols>
    struct meta::fixed_matrix_size<array::fixed_ndarray<T,Rows,Cols>>
    {
        static inline constexpr auto value = std::make_pair(Rows,Cols);
        using value_type = decltype(value);
    };

    /**
     * @brief specialization of fixed_ndarray fo rmeta::fixed_vector_size array traits.
     * 
     * @tparam T element type of fixed_ndarray
     * @tparam N number of elements of fixed_ndarray
     */
    template <typename T, size_t N>
    struct meta::fixed_vector_size<array::fixed_ndarray<T,N>>
    {
        static constexpr inline auto value = N;
    };

    /**
     * @brief specialization of fixed_ndarray for meta::fixed_ndarray_shape array traits.
     * 
     * @tparam T element type of fixed_vector
     * @tparam Shape1 number of elements at first axis
     * @tparam ShapeN number of elements for the rest axes
     */
    template <typename T, size_t Shape1, size_t...ShapeN>
    struct meta::fixed_ndarray_shape<array::fixed_ndarray<T,Shape1,ShapeN...>>
    {
        static inline constexpr auto value = std::make_tuple(Shape1,ShapeN...);
        using value_type = decltype(value);
    };
} // namespace nmtools

#include "nmtools/meta.hpp"

namespace nmtools::meta
{
    /**
     * @ingroup meta
     * @{
     */

    /**
     * @brief specialization of metafunction
     * nmtools::meta::get_ndarray_value_type for array::fixed_ndarray types
     * 
     * @tparam T element type of fixed_ndarray
     * @tparam Shape 
     */
    template <typename T, auto...Shape>
    struct get_ndarray_value_type<array::fixed_ndarray<T,Shape...>>
    {
        using type = T;
    };

    /** @} */ // end group meta
} // namespace nmtools::meta

#include "nmtools/array/utility/clone.hpp" // clone_impl
#include "nmtools/array/view/flatten.hpp"

namespace nmtools::array
{
    /**
     * @brief assignment operator from generic ndarray
     * 
     * @tparam T element/value type of fixed_ndarray
     * @tparam Shape1 
     * @tparam ShapeN 
     * @tparam ndarray_t 
     * @param rhs ndarray to be cloned
     * @return constexpr auto 
     * @todo support assignment from generic ndarray and also resizeable ndarray/matrix/vector
     * @see nmtools::matrix_size
     * @see nmtools::vector_size
     * @see nmtools::detail::clone_impl
     */
    template <typename T, size_t Shape1, size_t...ShapeN>
    template <typename ndarray_t>
    constexpr decltype(auto) fixed_ndarray<T,Shape1,ShapeN...>::operator=(ndarray_t&& rhs)
    {
        // static_assert (
        //     ( meta::is_fixed_size_matrix_v<ndarray_t> && (dim()==2) )
        //     || ( meta::is_fixed_size_vector_v<ndarray_t> && (dim()==1) ),
        //     "fixed_ndarray only support assignment from fixed ndarray/matrix/vector for now"
        // );

        using ::nmtools::detail::clone_impl;

        auto flat_rhs = view::flatten(std::forward<ndarray_t>(rhs));
        constexpr auto n_rhs = meta::fixed_vector_size_v<decltype(flat_rhs)>;
        static_assert (numel_==n_rhs
            , "mismatched shape for fixed_ndarray assignment"
        );
        clone_impl(this->data, flat_rhs, numel_);

        return *this;
    } // operator=
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_NDARRAY_FIXED_HPP