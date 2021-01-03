#ifndef NMTOOLS_ARRAY_UTILITY_SHAPE_HPP
#define NMTOOLS_ARRAY_UTILITY_SHAPE_HPP

#include "nmtools/array/index/make_array.hpp"
#include "nmtools/array/meta.hpp"
#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"

#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/utility/apply_at.hpp"

/* TODO: should we include array and std::array specialization here? */
#include <array>
#include <tuple>
#include <type_traits>

namespace nmtools
{
    /** @addtogroup utility
    * @ingroup array
    * Collections of utility functions for array-like objects
    * @{
    */

    using std::get;

    /**
     * @brief generic function to get size of dynamic-matrix, assuming nested vector.
     * May be specialized for custom dynamic-matrix type.
     * 
     * @tparam Matrix matrix-like
     * @param M matrix to check
     * @return std::enable_if_t<meta::is_nested_array2d_v<Matrix> || meta::is_fixed_size_matrix_v<Matrix>,std::pair<size_t,size_t>> 
     * @todo remove, prefer shape
     */
    template <typename Matrix>
    constexpr auto matrix_size(const Matrix& M) 
        -> std::enable_if_t<
            meta::is_nested_array2d_v<Matrix>
            || meta::is_fixed_size_matrix_v<Matrix>
            || meta::has_shape_v<Matrix>
            , std::pair<size_t,size_t> >
    {
        static_assert(
            meta::is_array2d_v<Matrix>
            /* TODO: meaningful error message */
        );
        /* TODO: check all size for each rows. 
        Nested vector container may have different size at axis 0 */
        if constexpr (meta::is_fixed_size_matrix_v<Matrix>)
        {
            auto [rows, cols] = meta::fixed_matrix_size_v<Matrix>;
            return {rows, cols};
        }
        else if constexpr (meta::has_shape_v<Matrix>)
        {
            auto [rows, cols] = M.shape();
            return {rows, cols};
        }
        else return std::pair{size(M), size(at(M,0))};
    } // std::pair<size_t,size_t> matrix_size(const Matrix& M)

    /**
     * @brief generic function to get size of dynamic-vector (as in math vector, not container).
     * May be specialized for custom dynamic-matrix type.
     * 
     * @tparam Vector vector-like
     * @param v vector to check
     * @return size_t 
     * @todo remove, prefer shape
     */
    template <typename Vector>
    constexpr auto vector_size(const Vector& v)
        -> std::enable_if_t<
            std::is_same_v<std::void_t<decltype(size(v))>,void>
            && !meta::is_fixed_size_vector_v<Vector>, size_t >
    {
        static_assert(
            meta::is_array1d_v<Vector>
            /* TODO: meaningful error message */
        );

        return size(v);
    } // size_t vector_size(const Vector& v)

    template <typename Vector>
    constexpr auto vector_size(const Vector& v)
        -> std::enable_if_t< meta::is_fixed_size_vector_v<Vector>, size_t>
    {
        return meta::fixed_vector_size_v<Vector>;
    }

    namespace detail
    {
        /**
         * @brief return the shape of fixed-size ndarray as compile-time constant
         * 
         * @tparam array_t fixed-size ndarray
         * @tparam typename sfinae to enable this fn for fixed-size ndarray only
         * @tparam Is compile-time index sequence to get the shape element
         * @param array 
         * @return constexpr auto 
         * @see meta::index_constant
         */
        template <typename array_t, typename=std::enable_if_t<meta::is_fixed_size_ndarray_v<array_t>>, size_t...Is>
        constexpr auto make_constant_shape(const array_t& array, std::index_sequence<Is...>)
        {
            constexpr auto shape_ =  meta::fixed_ndarray_shape_v<array_t>;
            return std::tuple{meta::index_constant<std::get<Is>(shape_)>{}...};
        } // make_constant_shape

        /**
         * @brief return the shape of fixed-size ndarray as compile-time constant
         * 
         * @tparam array_t fixed-size ndarray
         * @tparam typename sfinae to enable this fn for fixed-size ndarray only
         * @param array 
         * @return constexpr auto 
         */
        template <typename array_t, typename=std::enable_if_t<meta::is_fixed_size_ndarray_v<array_t>>>
        constexpr auto make_constant_shape(const array_t& array)
        {
            constexpr auto N = meta::fixed_ndarray_dim_v<array_t>;
            using indices_t = std::make_index_sequence<N>;
            return make_constant_shape(array, indices_t{});
        } // make_constant_shape

        /**
         * @brief repeat t N times as array
         * 
         * @tparam N desired number for t to be repeated
         * @tparam T 
         * @param t value to be repeated
         * @return constexpr auto 
         */
        template <size_t N, typename T>
        constexpr auto repeat(const T& t)
        {
            auto res = std::array<T,N>{};
            meta::template_for<N>([&](auto index){
                constexpr auto i = decltype(index)::value;
                std::get<i>(res) = t;
            });
            return res;
        } // repeat

    } // namespace detail

    /**
     * @brief return the shape of an array
     *
     * This function should work for fixed-size ndarray, fixed-dim ndarray, array1d, or array that has .shape().
     * 
     * @tparam array_t array type
     * @param array
     * @return constexpr auto 
     */
    template <typename array_t>
    constexpr auto shape(const array_t& array)
    {
        static_assert (meta::is_fixed_size_ndarray_v<array_t> || meta::has_shape_v<array_t>
            || (meta::nested_array_dim_v<array_t> > 0)
            || (meta::is_array1d_v<array_t> && meta::has_size_v<array_t>)
            , "unsupported shape; only support fixed-shape array or array has .shape()"
        );
        // check for fixed-shape array, should capture all kind of fixed-size array
        if constexpr (meta::is_fixed_size_ndarray_v<array_t>) {
            // @todo whenever the shape is constant return it as compile-time constant
            // @note not possible at this point, need to refactor indices & strides computation to support compile-time constant
            // return detail::make_constant_shape(array);
            return meta::fixed_ndarray_shape_v<array_t>;
        }
        // check for dynamic-shape array but fixed-dimension array
        else if constexpr (meta::nested_array_dim_v<array_t> > 0) {
            constexpr auto N = meta::nested_array_dim_v<array_t>;
            auto shape_ = std::array<size_t,N>{};
            meta::template_for<N>([&](auto index){
                constexpr auto i = decltype(index)::value;
                constexpr auto n = i+1;
                // example for 3dim nested dynamic array
                // vector<vector<vector<>>>; N==3
                // i==0:
                // s: size_t
                // i==1:
                // indices = array<size_t,1>{0};
                // a: vector<vector>>
                // s: size_t
                // i==2:
                // indices = array<size_t,2>{0,0};
                // s: size_t
                if constexpr (i==0) {
                    auto s = vector_size(array);
                    std::get<i>(shape_) = s;
                }
                else {
                    auto indices = detail::repeat<i>(0ul);
                    auto a = apply_at(array, indices);
                    // assuming nested array has size(a), which it should
                    auto s = vector_size(a);
                    std::get<i>(shape_) = s;
                }
            });
            return shape_;
        }
        else if constexpr (meta::is_array1d_v<array_t> && meta::has_size_v<array_t>)
            return std::tuple{vector_size(array)};
        else return array.shape();
    } // shape

    /**
     * @brief get the shape of an array, and convert it to given shape-type
     *
     * May be useful to convert tuple shape info to array.
     * 
     * @tparam shape_t desired shape type
     * @tparam array_t array type
     * @param array 
     * @return constexpr decltype(auto) 
     */
    template <template<typename,size_t> typename shape_t, typename array_t>
    constexpr decltype(auto) shape(const array_t& array)
    {
        auto shape_ = shape(array);
        return index::make_array<shape_t>(shape_);
    } // shape

    /**
     * @brief return the number of dimension of an array
     *
     * This fn should work with an array that is fixed-dim, matrix, vector, or the array has .dim().
     * 
     * @tparam array_t array type
     * @param array 
     * @return constexpr auto 
     * @see meta::fixed_dim_v
     */
    template <typename array_t>
    constexpr auto dim(const array_t& array)
    {
        static_assert (meta::is_fixed_dim_ndarray_v<array_t> || meta::has_dim_v<array_t>
            , "unsupported dim; only support fixed-dim array or array has .dim()"
        );
        // prefer for explicit call to dim() first
        if constexpr (meta::has_dim_v<array_t>)
            return array.dim();
        else if constexpr (meta::is_fixed_dim_ndarray_v<array_t>) {
            // @todo whenever the dim is constant return it as compile-time constant
            // @note not possible at this point, need to refactor indices & strides computation to support compile-time constant
            // return meta::index_constant<meta::fixed_ndarray_dim_v<array_t>>{};
            return meta::fixed_dim_v<array_t>;
        }
        else if constexpr (meta::is_array2d_v<array_t>) {
            // @todo whenever the dim is constant return it as compile-time constant
            // @note not possible at this point, need to refactor indices & strides computation to support compile-time constant
            // return meta::index_constant<2>{};
            return 2;
        }
        else if constexpr (meta::is_array1d_v<array_t>) {
            // @todo whenever the dim is constant return it as compile-time constant
            // @note not possible at this point, need to refactor indices & strides computation to support compile-time constant
            // return meta::index_constant<1>{};
            return 1;
        }
    } // dim

    /** @} */ // end group utility
} // namespace nmtools

#endif // NMTOOLS_ARRAY_UTILITY_SHAPE_HPP