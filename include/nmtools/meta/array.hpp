#ifndef NMTOOLS_META_ARRAY_HPP
#define NMTOOLS_META_ARRAY_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/traits.hpp"
#include "nmtools/meta/loop.hpp"

#include <type_traits>
#include <tuple>

namespace nmtools::meta
{
    /**
     * @addtogroup meta
     * @{
     */

    /**
     * @brief returns the number of elements of fixed shape at its 1st axis.
     *
     * @tparam T type to check
     * @tparam typename customization point
     */
    template <typename T, typename=void>
    struct nested_array_size
    {
        static constexpr auto value = 0;
    }; // nested_array_size

    /**
     * @brief specialization of nested_array_size for type that has tuple_size and value_type.
     * 
     * @tparam T type tot check
     */
    template <typename T>
    struct nested_array_size<T
        , std::enable_if_t<has_tuple_size_v<T> && has_value_type_v<T>>
    > {
        static constexpr auto value = std::tuple_size_v<T>;
    }; // nested_array_size

    /**
     * @brief helper variable template to get the number of elements of fixed shape at its 1st axis.
     * 
     * @tparam T type to check
     * @see nested_array_size
     */
    template <typename T>
    inline constexpr auto nested_array_size_v = nested_array_size<T>::value;

    /**
     * @brief get the number of dimension of (possibly) nested array.
     *
     * By default, check using expr::square_bracket.
     * 
     * @tparam T type to check
     * @tparam typename
     */
    template <typename T, typename=void>
    struct nested_array_dim
    {
        static constexpr auto value = 0;
    }; // nested_array_dim

    /**
     * @brief specialization of nested_array_dim
     *
     * Sepcialized when T square bracket expression with size_t is well-formed,
     * checked using has_square_bracket. Recursively instantiate nested_array_dim
     * with decreasing dimension.
     * 
     * @tparam T type to check
     * @see expr::square_bracket
     * @see has_square_bracket
     */
    template <typename T>
    struct nested_array_dim<T,std::enable_if_t<has_square_bracket_v<T,size_t>>>
    {
        using value_type = std::remove_reference_t<expr::square_bracket<T,size_t>>;
        static constexpr auto value = 1 + nested_array_dim<value_type>::value;
    }; // nested_array_dim

    /**
     * @brief helper variable template for nested_array_dim.
     * 
     * @tparam T type to check
     */
    template <typename T>
    inline constexpr auto nested_array_dim_v = nested_array_dim<T>::value;

    namespace detail
    {
        /**
         * @brief remove N number of dimension of a nested array.
         * 
         * @tparam T type to transfrom
         * @tparam N number of dimension to remove
         */
        template <typename T, size_t N, typename=void>
        struct remove_nested_array_dim
        {
            /**
             * @brief helper function declaration to deduce the nested type of given type U
             *
             * Actual case when U is subscriptable.
             * 
             * @tparam U array to check
             * @return enable_if_t<has_square_bracket_v<U,size_t>,expr::square_bracket<U,size_t>> 
             * @note the deduction is performed as static fn instead of specailization to prevent
             * ambiguous instantiation with terminal case when N==0
             */
            template <typename U>
            static auto try_nested_type()
                -> enable_if_t<has_square_bracket_v<U,size_t>,expr::square_bracket<U,size_t>>;
            /**
             * @brief helper function declaration to deduce the nested type of given type U
             * 
             * Return identity if U is not subscriptable.
             * 
             * @tparam U type to check
             * @return enable_if_t<!has_square_bracket_v<U,size_t>,T> 
             * @note the deduction is performed as static fn instead of specailization to prevent
             * ambiguous instantiation with terminal case when N==0
             */
            template <typename U>
            static auto try_nested_type()
                -> enable_if_t<!has_square_bracket_v<U,size_t>,U>;
            using nested_type = remove_cvref_t<decltype(try_nested_type<T>())>;
            using type = typename detail::remove_nested_array_dim<nested_type,N-1>::type;
        }; // remove_nested_array_dim

        // @note providing this specialization while also providing specializaiton for N==0
        // will cause error: ambiguous template instantiation
        // template <typename T, size_t N>
        // struct remove_nested_array_dim<T,N,std::enable_if_t<has_square_bracket_v<T,size_t>>>
        // {
        //     using nested_type = remove_cvref_t<expr::square_bracket<T,size_t>>;
        //     using type = typename detail::remove_nested_array_dim<nested_type,N-1>::type;
        // };

        /**
         * @brief terminal case for remove_nested_array_dim
         * 
         * @tparam T 
         */
        template <typename T>
        struct remove_nested_array_dim<T,0,void>
        {
            using type = remove_cvref_t<T>;
        }; // remove_nested_array_dim
    } // namespace detail

    /**
     * @brief remove N number of dimension of a nested array.
     * 
     * @tparam T type to transform
     * @tparam N number of dimension to be removed
     * @tparam typename 
     */
    template <typename T, size_t N, typename=void>
    struct remove_nested_array_dim
    {
        using type = T;
    }; // remove_nested_array_dim

    template <typename T, size_t N>
    struct remove_nested_array_dim<T,N,enable_if_t<has_square_bracket_v<T,size_t>>>
    {
        using type = typename detail::remove_nested_array_dim<T,N>::type;
    }; // remove_nested_array_dim

    /**
     * @brief helper alias template to remove N number of dimension of a nested array.
     * 
     * @tparam T type to transform
     * @tparam N number of dimension to be removed
     */
    template <typename T, size_t N>
    using remove_nested_array_dim_t = typename remove_nested_array_dim<T,N>::type;

    /**
     * @brief Get element type of nested array.
     * 
     * If T is some type that has expression t[i][j]...,
     * provide member typedef with type of that element type with maximum indexing,
     * otherwise provide typedef with T.
     * 
     * 
     * @tparam T type to check
     * @tparam typename 
     */
    template <typename T, typename=void>
    struct remove_all_nested_array_dim
    {
        using type = T;
    }; // remove_all_nested_array_dim

    /**
     * @brief Specialization of remove_all_nested_array_dim.
     *
     * Enabled when given type T can be 'sliced' with size_t.
     * 
     * @tparam T type to check
     * @see meta::has_square_bracket
     */
    template <typename T>
    struct remove_all_nested_array_dim<T,std::enable_if_t<has_square_bracket_v<T,size_t>>>
    {
        // recursively call itself until it reach default case
        using value_type = remove_cvref_t<expr::square_bracket<T,size_t>>;
        using type = typename remove_all_nested_array_dim<value_type>::type;
    }; // remove_all_nested_array_dim

    /**
     * @brief helper alias template for remove_all_nested_array_dim.
     * 
     * @tparam T type to check
     */
    template <typename T>
    using remove_all_nested_array_dim_t = typename remove_all_nested_array_dim<T>::type;

    /** @} */ // end group meta

} // namespace nmtools::meta

namespace nmtools::meta
{
    /**
     * @brief check if T t{} are:
     * - t[0][0][0] is valid
     * 
     * @tparam T 
     * @tparam void 
     */
    template <typename T, typename=void>
    struct is_array3d
    {
        static constexpr inline auto _check()
        {
            if constexpr (has_atnd_v<T,size_t,size_t,size_t>)
                return true;
            else if constexpr (has_funcnd_v<T,size_t,size_t,size_t>)
                return true;
            else if constexpr (has_bracketnd_v<T,size_t,size_t,size_t>)
                return true;
            else if constexpr (std::is_array_v<T> && std::rank_v<T> == 3)
                return true;
            else if constexpr (nested_array_dim_v<T> == 3)
                return true;
            else return false;
        } // _check
        static constexpr inline auto value = _check();
    }; // is_array3d

    template <typename T>
    inline constexpr bool is_array3d_v = is_array3d<T>::value;

    /**
     * @brief check if T t{} are:
     * - t[0][0] is valid
     * 
     * @tparam T 
     * @tparam void 
     */
    template <typename T, typename=void>
    struct is_array2d
    {
        static constexpr inline auto _check()
        {
            if constexpr (has_atnd_v<T,size_t,size_t>)
                return true;
            else if constexpr (has_funcnd_v<T,size_t,size_t>)
                return true;
            else if constexpr (has_bracketnd_v<T,size_t,size_t>)
                return true;
            else if constexpr (std::is_array_v<T> && std::rank_v<T> == 2)
                return true;
            else if constexpr (nested_array_dim_v<T> == 2)
                return true;
            else return false;
        } // _check
        static constexpr inline auto value = _check();
    }; // is_array2d

    template <typename T>
    inline constexpr bool is_array2d_v = is_array2d<T>::value;

    /**
     * @brief check if T t{} are:
     * - t[0] is valid
     * 
     * @tparam T 
     * @tparam void 
     */
    template <typename T, typename=void>
    struct is_array1d
    {
        static constexpr inline auto _check()
        {
            if constexpr (has_atnd_v<T,size_t>)
                return true;
            else if constexpr (has_funcnd_v<T,size_t>)
                return true;
            else if constexpr (has_square_bracket_v<T,size_t>)
                return true;
            else if constexpr (std::is_array_v<T> && std::rank_v<T> == 1)
                return true;
            else if constexpr (nested_array_dim_v<T> == 1)
                return true;
            else return false;
        } // _check
        static constexpr inline auto value = _check();
    }; // is_array1d

    /**
     * @brief helper variable template to check if T is 1d array-like
     * 
     * @tparam T 
     */
    template <typename T>
    inline constexpr bool is_array1d_v = is_array1d<T>::value;

    /**
     * @brief check if T is vector-like, (in math terms, not container terms)
     * 
     * @tparam T 
     * @todo remove
     */
    template <typename T>
    struct is_vector_like : is_array1d<T> {};

    template <typename T>
    inline constexpr bool is_vector_like_v = is_vector_like<T>::value;

    /**
     * @brief check if T is matrix-like
     * 
     * @tparam T 
     * @todo remove
     */
    template <typename T>
    struct is_matrix_like : is_array2d<T> {};

    template <typename T>
    inline constexpr bool is_matrix_like_v = is_matrix_like<T>::value;
} // namespace nmtools::meta

namespace nmtools::meta
{
    /**
     * @addtogroup traits
     * @{
     */

    /**
     * @brief get fixed-size vector (math) size at compile time
     * 
     * @tparam T 
     * @tparam typename=void 
     * @see fixed_vector_size_v
     * @see is_fixed_size_vector
     */
    template <typename T, typename=void>
    struct fixed_vector_size
    {
        using value_type = void;
    }; // fixed_vector_size

    /**
     * @brief helper variable template for fixed_vector_size
     * 
     * @tparam T 
     */
    template <typename T>
    inline constexpr auto fixed_vector_size_v = fixed_vector_size<T>::value;

    /**
     * @brief trait to check if type T is fixed-size vector (math).
     * 
     * @tparam T type to check
     * @tparam typename=void 
     * @see is_fixed_size_vector_v
     * @see fixed_vector_size
     */
    template <typename T, typename=void>
    struct is_fixed_size_vector
    {
        static constexpr auto _check()
        {
            using fixed_size_t = fixed_vector_size<T>;
            using value_type   = typename fixed_size_t::value_type;
            if constexpr (!std::is_same_v<value_type,void>)
                return true;
            else return false;
        } // _check()
        static constexpr auto value = _check();
    }; // is_fixed_size_vector

    /**
     * @brief helper variable template for is_fixed_size_vector.
     * 
     * @tparam T type to check
     */
    template <typename T>
    inline constexpr bool is_fixed_size_vector_v = is_fixed_size_vector<T>::value;

    /**
     * @brief get fixed-matrix's size at compile time.
     * well-formed specialization should have `value` and `value_type`.
     * 
     * @tparam T 
     * @tparam typename=void 
     * @see fixed_matrix_size_v
     * @see is_fixed_size_matrix
     */
    template <typename T, typename=void>
    struct fixed_matrix_size
    {
        using value_type = void;
    };

    /**
     * @brief helper variable template to get fixed-matrix's size
     * 
     * @tparam M fixed-matrix
     */
    template <typename M>
    inline constexpr auto fixed_matrix_size_v = fixed_matrix_size<M>::value;

    /**
     * @brief traits to check if type T is fixed-size matrix
     * 
     * @tparam T type to check
     * @tparam typename=void 
     * @see is_fixed_size_matrix_v
     * @see fixed_matrix_size
     */
    template <typename T, typename=void>
    struct is_fixed_size_matrix
    {
        static constexpr auto _check()
        {
            using fixed_size_t = fixed_matrix_size<T>;
            using value_type   = typename fixed_size_t::value_type;
            if constexpr (!std::is_same_v<value_type,void>)
                return true;
            else return false;
        } // _check()
        static constexpr auto value = _check();
    }; // is_fixed_size_matrix

    /**
     * @brief helper variable template for is_fixed_size_matrix
     * 
     * @tparam T type to check
     */
    template <typename T>
    inline constexpr bool is_fixed_size_matrix_v = is_fixed_size_matrix<T>::value;

    /**
     * @brief get fixed-array size at compile-time.
     * well-formed specialization should have `value` and `value_type`.
     * 
     * @tparam T type to check
     * @tparam typename optional for sfinae
     */
    template <typename T, typename=void>
    struct fixed_ndarray_shape
    {
        /**
         * @brief get the shape of ndarray.
         *
         * Dispatched code based on the attributes, with the following order:
         * - T is nested array and has fixed-size
         * - T is bounded array
         * - T is fixed-size matrix
         * - T is fixed-size vector
         * - fail
         * 
         * @return constexpr auto 
         */
        static constexpr auto _get()
        {
            // check for fixed-size array (that has tuple_size_v)
            if constexpr (nested_array_size_v<T> > 0) {
                // nested_array_dim_v mimics std::rank_v
                // nested_array_size_v mimics std::extent_v
                constexpr auto dim = nested_array_dim_v<T>;
                auto shape = std::array<size_t,dim>{};
                template_for<dim>([&](auto index){
                    constexpr auto i = decltype(index)::value;
                    using nested_t = remove_nested_array_dim_t<T,i>;
                    std::get<i>(shape) = nested_array_size_v<nested_t>;
                });
                return shape;
            }
            // check for bounded-array (e.g. double[1][2][3]...)
            else if constexpr (is_bounded_array_v<T>) {
                constexpr auto rank = std::rank_v<T>;
                auto shape = std::array<size_t,rank>{};
                template_for<rank>([&](auto index) {
                    constexpr auto i = decltype(index)::value;
                    constexpr auto n = std::extent_v<T,i>;
                    shape[i] = n;
                });
                return shape;
            }
            // default for matrix
            else if constexpr (is_fixed_size_matrix_v<T>)
                return fixed_matrix_size_v<T>;
            // default for vector
            else if constexpr (is_fixed_size_vector_v<T>){
                constexpr auto value = fixed_vector_size_v<T>;
                // @need to make_tuple to provide consistency between dimensions!
                return std::make_tuple(value);
            }
            // fail otherwise
            else return detail::fail_t{};
        } // _get()
        static inline constexpr auto value = _get();
        using value_type = detail::fail_to_void_t<meta::remove_cvref_t<decltype(value)>>;
    };

    /**
     * @brief helper variable template to get fixed-array size at compile-time.
     * well-formed specialization should have `value` and `value_type`.
     * 
     * @tparam T type to check
     */
    template <typename T>
    inline constexpr auto fixed_ndarray_shape_v = fixed_ndarray_shape<T>::value;

    /**
     * @brief check if given type T is fixed-size array (vector/matrix/ndarray)
     *
     * Default implementation check if calls to fixed_ndarray_shape returns successful (value_type not void),
     * returns true for such case, false otherwise.
     * 
     * @tparam T type to check
     * @tparam typename customization point
     * @see fixed_ndarray_shape
     */
    template <typename T, typename=void>
    struct is_fixed_size_ndarray
    {
        static constexpr auto _check()
        {
            using fixed_size_t = fixed_ndarray_shape<T>;
            using value_type   = typename fixed_size_t::value_type;
            if constexpr (!std::is_same_v<value_type,void>)
                return true;
            else return false;
        } // _check()
        static constexpr auto value = _check();
    }; // is_fixed_size_ndarray

    /**
     * @brief helper variable template to check if given type T is n-dimensional array that shape is known at compile-time
     * 
     * @tparam T type to check
     */
    template <typename T>
    inline constexpr bool is_fixed_size_ndarray_v = is_fixed_size_ndarray<T>::value;

    /**
     * @brief Get the number of maximum size of hybrid index array
     * 
     * @tparam T 
     * @tparam typename 
     */
    template <typename T, typename=void>
    struct hybrid_index_array_max_size
    {
        static constexpr auto value = detail::fail_t{};
        using type = detail::fail_t;
    }; // hybrid_index_array_max_size

    template <typename T>
    inline constexpr auto hybrid_index_array_max_size_v = hybrid_index_array_max_size<T>::value;

    template <typename T, auto N, typename=void>
    struct resize_hybrid_index_array_max_size
    {
        using type = void;
    }; // resize_hybrid_ndarray_max_size

    template <typename T, auto N>
    using resize_hybrid_index_array_max_size_t = type_t<resize_hybrid_index_array_max_size<T,N>>;

    template <typename T>
    struct hybrid_ndarray_max_size
    {
        static constexpr auto value = detail::fail_t{};
        using type = detail::fail_t;
    }; // hybrid_ndarray_max_size

    template <typename T>
    inline constexpr auto hybrid_ndarray_max_size_v = hybrid_ndarray_max_size<T>::value;

    template <typename T, typename=void>
    struct is_hybrid_ndarray
    {
        using value_type = std::conditional_t<
            std::is_same_v<
                detail::fail_t,
                type_t<hybrid_ndarray_max_size<T>>
            >,
            std::false_type, std::true_type
        >;
        static constexpr auto value = value_type::value;
    }; // is_hybrid_ndarray

    template <typename T>
    inline constexpr bool is_hybrid_ndarray_v = is_hybrid_ndarray<T>::value;

    template <typename T, auto N, typename=void>
    struct resize_hybrid_ndarray_max_size
    {
        using type = void;
    }; // resize_hybrid_ndarray_max_size

    template <typename T, auto N>
    using resize_hybrid_ndarray_max_size_t = type_t<resize_hybrid_ndarray_max_size<T,N>>;

    template <typename T, typename=void>
    struct is_dynamic_ndarray : std::negation<is_fixed_size_ndarray<T>> {};

    template <typename T>
    inline constexpr bool is_dynamic_ndarray_v = is_dynamic_ndarray<T>::value;

    /**
     * @brief get fixed-array dimension
     *
     * Default implementation will check if type T is fixed-size ndarray
     * and get the number of dimension from the shape then set value and value_type
     * accordingly, otherwise value_type is void and value is fail_t{}.
     * 
     * @tparam T type to check
     * @tparam typename customization poit
     * @see is_fixed_size_ndarray
     * @see fixed_ndarray_shape
     * @note not to be confused with fixed_dim, in which *may* return the number of dimension for runtime array
     */
    template <typename T, typename=void>
    struct fixed_ndarray_dim
    {
        static constexpr auto _get()
        {
            if constexpr (is_fixed_size_ndarray_v<T>) {
                auto shape = fixed_ndarray_shape_v<T>;
                auto dim = std::tuple_size_v<decltype(shape)>;
                return dim;
            }
            else return detail::fail_t{};
        } // _get()
        static constexpr auto value = _get();
        using value_type = detail::fail_to_void_t<meta::remove_cvref_t<decltype(value)>>;
    }; // fixed_ndarray_dim

    /**
     * @brief helper variable template for fixed_ndarray_dim
     * 
     * @tparam T 
     */
    template <typename T>
    inline static constexpr auto fixed_ndarray_dim_v = fixed_ndarray_dim<T>::value;

    /**
     * @brief check if type T has fixed-dimension
     * 
     * @tparam T type to check
     * @tparam typename 
     * @see fixed_ndarray_dim
     * @see nested_array_dim_v
     * @note not to be confused with fixed_ndarray_dim, in which *only* return the number of dimension for fixed-size array
     */
    template <typename T, typename=void>
    struct fixed_dim
    {
        static constexpr auto _get() {
            // for fixed-size ndarray, read dimension from fixed_ndarray_dim,
            // which simply count the number of shape
            using dim_t = fixed_ndarray_dim<T>;
            using value_type = typename dim_t::value_type;
            if constexpr (!std::is_same_v<value_type,void>)
                return dim_t::value;
            // for nested array, while the shape may only known at runtime,
            // the dimension can be known at compilet time
            else if constexpr (nested_array_dim_v<T> > 0)
                return nested_array_dim_v<T>;
            else return detail::fail_t{};
        } // _get()
        static constexpr auto value = _get();
        using value_type = detail::fail_to_void_t<meta::remove_cvref_t<decltype(value)>>;
    }; // fixed_dim

    /**
     * @brief helper variable template for fixed_dim
     * 
     * @tparam T type to check
     */
    template <typename T>
    inline static constexpr auto fixed_dim_v = fixed_dim<T>::value;

    /**
     * @brief check if type T is fixed-dimension ndarray
     *
     * Default implementation checks if fixed_ndarray_dim<T>
     * has value_type that is not void.
     * 
     * @tparam T type to check
     * @tparam typename customization point
     * @see fixed_dim
     */
    template <typename T, typename=void>
    struct is_fixed_dim_ndarray
    {
        static constexpr auto _check()
        {
            // for fixed-size ndarray, read dimension from fixed_dim,
            // which simply count the number of shape
            using dim_t = fixed_dim<T>;
            using value_type = typename dim_t::value_type;
            if constexpr (!std::is_same_v<value_type,void>)
                return true;
            else return false;
        } // _check()
        static constexpr auto value = _check();
    }; // is_fixed_dim_ndarray

    /**
     * @brief helper variable template for is_fixed_dim_ndarray
     * 
     * @tparam T type to check
     */
    template <typename T>
    inline constexpr auto is_fixed_dim_ndarray_v = is_fixed_dim_ndarray<T>::value;

    /**
     * @brief check if given type T is n-dimensional array
     * 
     * Default implemetnation check for distjunction of fixed-size ndarray, array1d and array2d.
     *
     * @tparam T type to check
     * @tparam typename customization point
     * @see is_fixed_size_ndarray
     * @see is_array1d
     * @see is_array2d
     */
    template <typename T, typename=void>
    struct is_ndarray
    {
        static constexpr auto _check()
        {
            // @note this will try to instantiate all the following traits
            // this is troublesome if any of the following traits is not well-formed for some T
            // return is_fixed_size_ndarray_v<T>
            //     || is_array1d_v<T>
            //     || is_array2d_v<T>;

            // use short circuit instead
            if constexpr (is_fixed_size_ndarray_v<T>)
                return true;
            else if constexpr (is_array2d_v<T>)
                return true;
            else if constexpr (is_array1d_v<T>)
                return true;
            else return false;
        } // _check()
        static constexpr auto value = _check();
    }; // is_ndarray

    /**
     * @brief helper variable template to check if T is n-dimensional array
     * 
     * @tparam T type to check
     */
    template <typename T>
    inline constexpr bool is_ndarray_v = is_ndarray<T>::value;


    /** @} */ // end group traits

    /**
     * @addtogroup traits
     * @{
     */
    
    /* various partial specializaton / sfinae */

    /**
     * @brief specializaton fo fixed_matrix_size for raw array type.
     *
     * Specialized when T is 2D bounded array.
     * 
     * @tparam T element type of raw array
     * @tparam Rows size of array at first axis (number of rows)
     * @tparam Cols size of array at second axis (number of columns)
     */
    template <typename T, size_t Rows, size_t Cols>
    struct fixed_matrix_size<T[Rows][Cols]>
    {
        static constexpr inline auto value = std::make_pair(Rows,Cols);
        using value_type = decltype(value);
    }; // fixed_matrix_size

    /**
     * @brief specializaton of fixed_matrix_size for nested std::array type
     * 
     * @tparam T 
     * @tparam n 
     * @tparam m 
     */
    template <typename T, size_t Rows, size_t Cols>
    struct fixed_matrix_size<std::array<std::array<T,Cols>,Rows>> 
    {
        static inline constexpr auto value = std::make_pair(Rows,Cols);
        using value_type = decltype(value); // std::pair
    }; // fixed_matrix_size

    /**
     * @brief specializaton of fixed_vector_size for std::array
     * 
     * @tparam T 
     * @tparam N 
     */
    template <typename T, size_t N>
    struct fixed_vector_size<std::array<T,N>> : std::tuple_size<std::array<T,N>> {};

    /**
     * @brief specialization of fixed_vector size for raw arary
     * 
     * @tparam T element type of raw array, automatically deduced
     * @tparam N size of raw array, automatically deduced
     * @todo move to array meta
     */
    template <typename T, size_t N>
    struct fixed_vector_size<T[N]>
    {
        static inline constexpr auto value = N;
    };

    /**
     * @brief specializaton fo is_fixed_size_vector for raw array type.
     * 
     * @tparam T element type of raw array, automatically deduced
     * @tparam N size of raw array, automatically deduced
     */
    template <typename T, size_t N>
    struct is_fixed_size_vector<T[N]> : true_type {};

    template <typename T>
    struct is_dynamic_size_matrix : std::negation<is_fixed_size_matrix<T>> {};

    template <typename T>
    inline constexpr bool is_dynamic_size_matrix_v = is_dynamic_size_matrix<T>::value;

    template <typename T>
    struct is_dynamic_size_vector : std::negation<is_fixed_size_vector<T>> {};

    template <typename T>
    inline constexpr bool is_dynamic_size_vector_v = is_dynamic_size_vector<T>::value;

    /** @} */ // end group traits

} // namespace nmtools::meta

#endif // NMTOOLS_META_ARRAY_HPP