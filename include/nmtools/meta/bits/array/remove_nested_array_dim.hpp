#ifndef NMTOOLS_META_BITS_ARRAY_REMOVE_NESTED_ARRAY_DIM_HPP
#define NMTOOLS_META_BITS_ARRAY_REMOVE_NESTED_ARRAY_DIM_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/transform/remove_cvref.hpp"

namespace nmtools::meta
{
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
} // namespace nmtools::meta


#endif // NMTOOLS_META_BITS_ARRAY_REMOVE_NESTED_ARRAY_DIM_HPP