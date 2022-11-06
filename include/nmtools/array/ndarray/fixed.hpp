#ifndef NMTOOLS_ARRAY_NDARRAY_FIXED_HPP
#define NMTOOLS_ARRAY_NDARRAY_FIXED_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/index/compute_strides.hpp"
#include "nmtools/array/at.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/utility/forward.hpp"
#include "nmtools/array/index/product.hpp"

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
            #if 1
            return nmtools_array<size_t,dim_>{Shape1,ShapeN...};
            #else
            return nmtools_tuple{meta::ct_v<Shape1>,meta::ct_v<ShapeN>...};
            #endif
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
            return index::product(shape_);
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
            auto stride = meta::make_array_type_t<size_t,dim()>{};
            for (size_t i=0; i<dim(); i++)
                stride[i] = ::nmtools::index::stride(shape_,i);
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
            -> meta::enable_if_t<sizeof...(ns)==sizeof...(ShapeN),reference>
        {
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
            -> meta::enable_if_t<sizeof...(ns)==sizeof...(ShapeN),const_reference>
        {
            return at(data, n, ns...);
        } // operator()

        // constexpr decltype(auto) operator=(this_type&& other)
        // {
        //     this->data = other.data;
        //     return *this;
        // }

        template <typename ndarray_t, typename=meta::enable_if_t<meta::is_ndarray_v<ndarray_t>>>
        constexpr decltype(auto) operator=(ndarray_t&& rhs);

        /**
         * @brief provides assignment operator from nested array
         * 
         * @param rhs nested std array to be copied
         * @return constexpr decltype(auto) 
         */
        constexpr decltype(auto) operator=(meta::make_nested_raw_array_t<T,Shape1,ShapeN...>&& rhs)
        {
            using nested_t = meta::make_nested_raw_array_t<T,Shape1,ShapeN...>;
            return this->template operator=<nested_t>(nmtools::forward<nested_t>(rhs));
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

namespace nmtools::meta
{
    template <typename T, size_t Shape1, size_t...ShapeN>
    struct fixed_shape<
        array::fixed_ndarray<T,Shape1,ShapeN...>
    >
    {
        // calling fixed_shape should return constexpr value instead of constant runtime
        static constexpr auto value = nmtools_array{Shape1,ShapeN...};
        using value_type = decltype(value);
    }; // fixed_shape

    template <typename T, size_t Shape1, size_t...ShapeN, auto...new_shape>
    struct resize_shape<
        array::fixed_ndarray<T,Shape1,ShapeN...>
        , as_type<new_shape...>
    >
    {
        using type = array::fixed_ndarray<T,new_shape...>;
    }; // resize_shape
    
} // namespace nmtools::meta

namespace nmtools
{
    /**
     * @ingroup utility
     * 
     */

    // TODO: remove
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

    // TODO: remove
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

    // TODO: remove
    /**
     * @brief specialization of fixed_ndarray for meta::fixed_ndarray_shape array traits.
     * 
     * @tparam T element type of fixed_vector
     * @tparam Shape1 number of elements at first axis
     * @tparam ShapeN number of elements for the rest axes
     */
    template <typename T, size_t Shape1, size_t...ShapeN>
    struct meta::fixed_ndarray_shape<array::fixed_ndarray<T,Shape1,ShapeN...>>
        : fixed_shape<array::fixed_ndarray<T,Shape1,ShapeN...>> {};
    #if 0
    {
        static inline constexpr auto value = meta::make_array_type_t<size_t,sizeof...(ShapeN)+1>{Shape1,ShapeN...};
        using value_type = decltype(value);
    };
    #endif

    // TODO: remove
    template <typename T, size_t N>
    struct meta::is_index_array< array::fixed_ndarray<T,N>
        , meta::enable_if_t<meta::is_index_v<T>>
    > : meta::true_type {};

    // TODO: remove
    template <typename T, size_t N>
    struct meta::is_fixed_index_array< array::fixed_ndarray<T,N>
        , meta::enable_if_t<meta::is_index_v<T>>
    > : meta::true_type {};

    // TODO: remove
    template <typename T, size_t N>
    struct meta::fixed_index_array_size< array::fixed_ndarray<T,N>
        , meta::enable_if_t<meta::is_index_v<T>>
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
    struct meta::replace_element_type<array::fixed_ndarray<T,Shape1,ShapeN...>,U,meta::enable_if_t<meta::is_num_v<U>>>
    {
        using type = array::fixed_ndarray<U,Shape1,ShapeN...>;
    }; // replace_element_type
} // namespace nmtools

namespace nmtools::meta
{
    /**
     * @ingroup meta
     * @{
     */

    template <typename T, auto N, auto M>
    struct resize_size<array::fixed_ndarray<T,N>,M>
    {
        using type = array::fixed_ndarray<T,M>;
    };

    // TODO: remove
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

    // TODO: remove, use as_type
    /**
     * @brief helper type to pack values as type
     * 
     * Helpful for pack compile-time values for resize_fixed_ndarray
     * which requires type.
     * 
     * @tparam compile-time values
     */
    template <auto...>
    struct value_type {};

    template <auto...values, auto new_value>
    struct append_value< value_type<values...>, new_value >
    {
        using type = value_type<values..., new_value>;
    }; // append_value

    // TODO: remove
    template <typename T, auto...Shapes, template<auto...> typename typelist, auto...NewShapes>
    struct resize_fixed_ndarray<array::fixed_ndarray<T,Shapes...>,typelist<NewShapes...>>
    {
        using type = array::fixed_ndarray<T,NewShapes...>;
    }; // resize_fixed_ndarray

    /**
     * @brief Construct new fixed_ndarray type with resized shape.
     * 
     * @tparam T        element type of fixed_ndarray
     * @tparam Shapes   shapes of fixed_ndarray
     * @tparam U        another fixed-size ndarray that contain desired shape
     */
    template <typename T, auto...Shapes, typename U>
    struct resize_fixed_ndarray<
        array::fixed_ndarray<T,Shapes...>, U,
        meta::enable_if_t<is_fixed_size_ndarray_v<U> && is_num_v<T>>
    >
    {
        // convert shape value of U (a fixed ndarray type) to type
        static constexpr auto vshape = [](){
            constexpr auto shape = fixed_ndarray_shape_v<U>;
            constexpr auto dim = fixed_ndarray_dim_v<U>;

            constexpr auto vshape = template_reduce<dim>([&](auto lhs, auto index){
                using lhs_t = remove_cvref_t<decltype(lhs)>;
                constexpr auto i = decltype(index)::value;
                // somehow the order is reversed, don't know why
                // note: shape can hold constant value (int constant)
                // use compile time constant to index
                // and make sure to convert to value as needed by resize
                constexpr auto I = [&](){
                    auto I_ = at(shape,ct<i>{});
                    using I_t = decltype(I_);
                    if constexpr (is_constant_index_v<I_t>)
                        return I_t::value;
                    else return I_;
                }();

                // for initial, just create value_type
                // otherwise call append
                if constexpr (i==0) {
                    using type = value_type<I>;
                    return as_value_v<type>;
                } else {
                    using vtype = type_t<lhs_t>;
                    using type  = append_value_t<vtype,I>;
                    return as_value_v<type>;
                }
            }, /*init=*/None);
            return vshape;
        }();
        using type = resize_fixed_ndarray_t<
            array::fixed_ndarray<T,Shapes...>,
            type_t<decltype(vshape)>
        >;
    }; // resize_fixed_ndarray

// TODO: cleanup, use new generic ndarray
#ifndef NMTOOLS_MAKE_FIXED_NDARRAY
#define NMTOOLS_MAKE_FIXED_NDARRAY

    /**
     * @brief Default definition of make_fixed_ndarray.
     * returns nmtools::array::fixed_ndarray.
     * 
     * @tparam element_t desired element type
     * @tparam shape_t   a constant index array type, containing desired shape
     * @todo consider to make this default fixed_ndarray override-able via global macro
     */
    template <typename element_t, typename shape_t>
    struct make_fixed_ndarray
    {
        static constexpr auto vshape = [](){
            // template_reduce needs at least 2 elements
            constexpr auto DIM = len_v<shape_t>;
            if constexpr (DIM >= 2) {
                // TODO: refactor to use template_reduce with explicit number of iteration
                // perform reduce op to combine all values in shape_t to T[axis0][axis1]...
                // as needed to feed shape to resize_fixed_ndarray_t
                // assume shape_t has default constructor and constexpr-ready
                constexpr auto shape = template_reduce([](auto lhs, auto /*rhs*/, auto index){
                    using lhs_t = remove_cvref_t<decltype(lhs)>;
                    constexpr auto i = decltype(index)::value;
                    // assume shape is_constant_index_array
                    // somehow the order is reversed, don't know why
                    constexpr auto N = at_t<shape_t,DIM-i-1>::value;
                    if constexpr (is_none_v<lhs_t>) {
                        return as_value_v<element_t[N]>;
                    } else {
                        // at this poiht lhs_t should be as_value<T[axis0][axis1]...>
                        using T = type_t<lhs_t>;
                        return as_value_v<T[N]>;
                    }
                }, /*init=*/None, shape_t{});
                return shape;
            } else {
                // assume shape is_constant_index_array
                constexpr auto N = at_t<shape_t,0>::value;
                return as_value_v<element_t[N]>;
            }
        }();
        using type = resize_fixed_ndarray_t<
            array::fixed_ndarray<element_t,1>,
            type_t<decltype(vshape)>
        >;
    }; // make_fixed_ndarray

    template <typename element_t, typename shape_t>
    using make_fixed_ndarray_t = type_t<make_fixed_ndarray<element_t,shape_t>>;

    #define nmtools_fixed_ndarray ::nmtools::array::fixed_ndarray

#endif // NMTOOLS_MAKE_FIXED_NDARRAY

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
     * @todo support assignment from generic ndarray and also resizable ndarray
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
        else {
            nmtools_assert_throw( isequal(::nmtools::shape(rhs),this_shape)
                , "unsupported shape for for fixed_ndarray assignment"
            );
        }

        auto flat_rhs  = view::flatten(nmtools::forward<ndarray_t>(rhs));
        auto flat_data = view::mutable_flatten(this->data);
        constexpr auto n_rhs = meta::fixed_size_v<decltype(flat_rhs)>;
        static_assert (numel_==n_rhs
            , "mismatched shape for fixed_ndarray assignment"
        );
        for (size_t i=0; i<numel_; i++)
            at(flat_data,i) = at(flat_rhs,i);

        return *this;
    } // operator=
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_NDARRAY_FIXED_HPP