#ifndef NMTOOLS_ARRAY_NDARRAY_FIXED_HPP
#define NMTOOLS_ARRAY_NDARRAY_FIXED_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/detail.hpp"
#include "nmtools/array/meta.hpp" // meta::fixed_matrix_size etc.
#include "nmtools/array/utility/at.hpp"

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
         * @todo remove
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
         * @todo remove
         */
        static constexpr auto strides()
        {
            auto stride = std::array<size_t,dim()>{};
            for (size_t i=0; i<dim(); i++)
                stride[i] = detail::stride(shape_,i);
            return stride;
        }
        static inline constexpr auto strides_ = strides();

        using this_type  = fixed_ndarray<T,Shape1,ShapeN...>;
        // underlying flat storage
        using data_type = meta::make_nested_raw_array_t<T,Shape1,ShapeN...>;
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
            return at(data, n, ns...);
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
            return at(data, n, ns...);
        } // operator()

        // constexpr decltype(auto) operator=(this_type&& other)
        // {
        //     this->data = other.data;
        //     return *this;
        // }

        template <typename ndarray_t, typename=std::enable_if_t<meta::is_ndarray_v<ndarray_t>>>
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

    // provide user-defined ctad
    // @note 1D
    template <typename T, size_t N>
    fixed_ndarray(T (&&a)[N]) -> fixed_ndarray<T,N>;
    // @note 2D
    template <typename T, size_t Rows, size_t Cols>
    fixed_ndarray(T (&&a)[Rows][Cols]) -> fixed_ndarray<T,Rows,Cols>;
    // @note 3D
    template <typename T, size_t Shape1, size_t Shape2, size_t Shape3>
    fixed_ndarray(T (&&a)[Shape1][Shape2][Shape3]) -> fixed_ndarray<T,Shape1,Shape2,Shape3>;
    // @note 4D
    template <typename T, size_t Shape1, size_t Shape2, size_t Shape3, size_t Shape4>
    fixed_ndarray(T (&&a)[Shape1][Shape2][Shape3][Shape4]) -> fixed_ndarray<T,Shape1,Shape2,Shape3,Shape4>;
    // @note 5D
    template <typename T, size_t Shape1, size_t Shape2, size_t Shape3, size_t Shape4, size_t Shape5>
    fixed_ndarray(T (&&a)[Shape1][Shape2][Shape3][Shape4][Shape5]) -> fixed_ndarray<T,Shape1,Shape2,Shape3,Shape4,Shape5>;
    // @note 6D
    template <typename T, size_t Shape1, size_t Shape2, size_t Shape3, size_t Shape4, size_t Shape5, size_t Shape6>
    fixed_ndarray(T (&&a)[Shape1][Shape2][Shape3][Shape4][Shape5][Shape6]) -> fixed_ndarray<T,Shape1,Shape2,Shape3,Shape4,Shape5,Shape6>;
    // @note 7D
    template <typename T, size_t Shape1, size_t Shape2, size_t Shape3, size_t Shape4, size_t Shape5, size_t Shape6, size_t Shape7>
    fixed_ndarray(T (&&a)[Shape1][Shape2][Shape3][Shape4][Shape5][Shape6][Shape7]) -> fixed_ndarray<T,Shape1,Shape2,Shape3,Shape4,Shape5,Shape6,Shape7>;
    // @note 8D
    template <typename T, size_t Shape1, size_t Shape2, size_t Shape3, size_t Shape4, size_t Shape5, size_t Shape6, size_t Shape7, size_t Shape8>
    fixed_ndarray(T (&&a)[Shape1][Shape2][Shape3][Shape4][Shape5][Shape6][Shape7][Shape8]) -> fixed_ndarray<T,Shape1,Shape2,Shape3,Shape4,Shape5,Shape6,Shape7,Shape8>;
    // @note 9D
    template <typename T, size_t Shape1, size_t Shape2, size_t Shape3, size_t Shape4, size_t Shape5, size_t Shape6, size_t Shape7, size_t Shape8, size_t Shape9>
    fixed_ndarray(T (&&a)[Shape1][Shape2][Shape3][Shape4][Shape5][Shape6][Shape7][Shape8][Shape9]) -> fixed_ndarray<T,Shape1,Shape2,Shape3,Shape4,Shape5,Shape6,Shape7,Shape8,Shape9>;
    // @note 10D
    template <typename T, size_t Shape1, size_t Shape2, size_t Shape3, size_t Shape4, size_t Shape5, size_t Shape6, size_t Shape7, size_t Shape8, size_t Shape9, size_t Shape10>
    fixed_ndarray(T (&&a)[Shape1][Shape2][Shape3][Shape4][Shape5][Shape6][Shape7][Shape8][Shape9][Shape10]) -> fixed_ndarray<T,Shape1,Shape2,Shape3,Shape4,Shape5,Shape6,Shape7,Shape8,Shape9,Shape10>;
    // @note 11D
    template <typename T, size_t Shape1, size_t Shape2, size_t Shape3, size_t Shape4, size_t Shape5, size_t Shape6, size_t Shape7, size_t Shape8, size_t Shape9, size_t Shape10, size_t Shape11>
    fixed_ndarray(T (&&a)[Shape1][Shape2][Shape3][Shape4][Shape5][Shape6][Shape7][Shape8][Shape9][Shape10][Shape11]) -> fixed_ndarray<T,Shape1,Shape2,Shape3,Shape4,Shape5,Shape6,Shape7,Shape8,Shape9,Shape10,Shape11>;

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
    constexpr auto shape(const array::fixed_ndarray<T,Shape1,ShapeN...>& a)
    {
        return a.shape();
    } // shape

    /**
     * @brief return the dimensionality of fixed_ndarray, which is known at compile-time
     * 
     * @tparam T 
     * @tparam Shape 
     * @param a 
     * @return constexpr auto 
     */
    template <typename T, size_t...Shape>
    constexpr auto dim(const array::fixed_ndarray<T,Shape...>& a)
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
        using value_type = decltype(value);
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
        static inline constexpr auto value = std::array{Shape1,ShapeN...};
        using value_type = decltype(value);
    };

    template <typename T, size_t N>
    struct meta::is_index_array< array::fixed_ndarray<T,N>
        , std::enable_if_t<meta::is_index_v<T>>
    > : std::true_type {};

    template <typename T, size_t N>
    struct meta::is_fixed_index_array< array::fixed_ndarray<T,N>
        , std::enable_if_t<meta::is_index_v<T>>
    > : std::true_type {};

    template <typename T, size_t N>
    struct meta::fixed_index_array_size< array::fixed_ndarray<T,N>
        , std::enable_if_t<meta::is_index_v<T>>
    >
    {
        static constexpr auto value = N;
    };

    template <typename T, size_t N, auto NEW_SIZE>
    struct meta::resize_fixed_vector< array::fixed_ndarray<T,N>, NEW_SIZE >
    {
        using type = array::fixed_ndarray<T,NEW_SIZE>;
    };


    /**
     * @brief specialize replace_element_type for array::fixed_ndarray
     * 
     * @tparam T 
     * @tparam U 
     * @tparam Shape1 
     * @tparam ShapeN 
     */
    template <typename T, typename U, size_t Shape1, size_t...ShapeN>
    struct meta::replace_element_type<array::fixed_ndarray<T,Shape1,ShapeN...>,U,std::enable_if_t<std::is_arithmetic_v<U>>>
    {
        using type = array::fixed_ndarray<U,Shape1,ShapeN...>;
    }; // replace_element_type
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

    /**
     * @brief helper type to pack values as type
     * 
     * @tparam compile-time values
     */
    template <auto...>
    struct value_type {};

    template <typename T, auto...Shapes, template<auto...> typename typelist, auto...NewShapes>
    struct resize_fixed_ndarray<array::fixed_ndarray<T,Shapes...>,typelist<NewShapes...>>
    {
        using type = array::fixed_ndarray<T,NewShapes...>;
    }; // resize_fixed_ndarray

    /**
     * @brief resize array::fixed_ndarray from raw array
     * 
     * @tparam T 
     * @tparam Shapes 
     * @tparam NewShape1 
     */
    template <typename T, auto...Shapes, auto NewShape1>
    struct resize_fixed_ndarray<
        array::fixed_ndarray<T,Shapes...>,
        T[NewShape1],
        std::enable_if_t<std::is_arithmetic_v<T>>
    >
    {
        using new_shape_t = value_type<NewShape1>;
        using this_t = array::fixed_ndarray<T,Shapes...>;
        using type = type_t<resize_fixed_ndarray<this_t,new_shape_t>>;
    }; // resize_fixed_ndarray

    template <typename T, auto...Shapes, auto NewShape1, auto NewShape2>
    struct resize_fixed_ndarray<
        array::fixed_ndarray<T,Shapes...>,
        T[NewShape1][NewShape2],
        std::enable_if_t<std::is_arithmetic_v<T>>
    >
    {
        using new_shape_t = value_type<NewShape1,NewShape2>;
        using this_t = array::fixed_ndarray<T,Shapes...>;
        using type = type_t<resize_fixed_ndarray<this_t,new_shape_t>>;
    }; // resize_fixed_ndarray

    template <typename T, auto...Shapes, auto NewShape1, auto NewShape2, auto NewShape3>
    struct resize_fixed_ndarray<
        array::fixed_ndarray<T,Shapes...>,
        T[NewShape1][NewShape2][NewShape3],
        std::enable_if_t<std::is_arithmetic_v<T>>
    >
    {
        using new_shape_t = value_type<NewShape1,NewShape2,NewShape3>;
        using this_t = array::fixed_ndarray<T,Shapes...>;
        using type = type_t<resize_fixed_ndarray<this_t,new_shape_t>>;
    }; // resize_fixed_ndarray

    template <typename T, auto...Shapes, auto NewShape1, auto NewShape2, auto NewShape3, auto NewShape4>
    struct resize_fixed_ndarray<
        array::fixed_ndarray<T,Shapes...>,
        T[NewShape1][NewShape2][NewShape3][NewShape4],
        std::enable_if_t<std::is_arithmetic_v<T>>
    >
    {
        using new_shape_t = value_type<NewShape1,NewShape2,NewShape3,NewShape4>;
        using this_t = array::fixed_ndarray<T,Shapes...>;
        using type = type_t<resize_fixed_ndarray<this_t,new_shape_t>>;
    }; // resize_fixed_ndarray

    template <typename T, auto...Shapes, auto NewShape1, auto NewShape2, auto NewShape3, auto NewShape4, auto NewShape5>
    struct resize_fixed_ndarray<
        array::fixed_ndarray<T,Shapes...>,
        T[NewShape1][NewShape2][NewShape3][NewShape4][NewShape5],
        std::enable_if_t<std::is_arithmetic_v<T>>
    >
    {
        using new_shape_t = value_type<NewShape1,NewShape2,NewShape3,NewShape4,NewShape5>;
        using this_t = array::fixed_ndarray<T,Shapes...>;
        using type = type_t<resize_fixed_ndarray<this_t,new_shape_t>>;
    }; // resize_fixed_ndarray

    template <typename T, auto...Shapes, auto NewShape1, auto NewShape2, auto NewShape3, auto NewShape4, auto NewShape5, auto NewShape6>
    struct resize_fixed_ndarray<
        array::fixed_ndarray<T,Shapes...>,
        T[NewShape1][NewShape2][NewShape3][NewShape4][NewShape5][NewShape6],
        std::enable_if_t<std::is_arithmetic_v<T>>
    >
    {
        using new_shape_t = value_type<NewShape1,NewShape2,NewShape3,NewShape4,NewShape5,NewShape6>;
        using this_t = array::fixed_ndarray<T,Shapes...>;
        using type = type_t<resize_fixed_ndarray<this_t,new_shape_t>>;
    }; // resize_fixed_ndarray

    /** @} */ // end group meta
} // namespace nmtools::meta

#include "nmtools/array/view/flatten.hpp" // view::flatten
#include "nmtools/array/view/mutable_flatten.hpp" // view::mutable_flatten
#include "nmtools/utils/isequal.hpp"
#include "nmtools/array/shape.hpp"

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
     */
    template <typename T, size_t Shape1, size_t...ShapeN>
    template <typename ndarray_t, typename>
    constexpr decltype(auto) fixed_ndarray<T,Shape1,ShapeN...>::operator=(ndarray_t&& rhs)
    {
        using utils::isequal;
        using meta::fixed_ndarray_dim_v;
        using meta::fixed_ndarray_shape_v;

        if constexpr (meta::is_fixed_dim_ndarray_v<ndarray_t>)
            static_assert (fixed_ndarray_dim_v<ndarray_t> == fixed_ndarray_dim_v<this_type>
                , "unsupported dim for fixed_ndarray assignment"
            );
        
        constexpr auto this_shape = fixed_ndarray_shape_v<this_type>;
        if constexpr (meta::is_fixed_size_ndarray_v<ndarray_t>)
            static_assert( isequal(fixed_ndarray_shape_v<ndarray_t>, this_shape)
                , "unsupported shape for for fixed_ndarray assignment"
            );
        else
            assert( isequal(shape(rhs),this_shape)
                // , "unsupported shape for for fixed_ndarray assignment"
            );

        auto flat_rhs  = view::flatten(std::forward<ndarray_t>(rhs));
        auto flat_data = view::mutable_flatten(this->data);
        constexpr auto n_rhs = meta::fixed_vector_size_v<decltype(flat_rhs)>;
        static_assert (numel_==n_rhs
            , "mismatched shape for fixed_ndarray assignment"
        );
        for (size_t i=0; i<numel_; i++)
            at(flat_data,i) = at(flat_rhs,i);

        return *this;
    } // operator=
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_NDARRAY_FIXED_HPP