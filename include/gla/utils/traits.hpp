#ifndef GLA_UTILS_TRAITS_HPP
#define GLA_UTILS_TRAITS_HPP

#include <type_traits>

namespace gla
{
    namespace utils
    {
        namespace traits
        {
            template <typename T, typename = void>
            struct has_n_cols : std::false_type {};

            template <typename T>
            struct has_n_cols<T, std::void_t<
                decltype(std::declval<T>().n_cols())
            > /* void_t */ > : std::true_type {};

            template <typename T>
            static constexpr bool has_n_cols_v = has_n_cols<T>::value;

            template <typename T, typename = void>
            struct has_n_rows : std::false_type {};

            template <typename T>
            struct has_n_rows<T, std::void_t<
                decltype(std::declval<T>().n_cols())
            > /* void_t */ > : std::true_type {};

            template <typename T>
            static constexpr bool has_n_rows_v = has_n_rows<T>::value;

            template <typename T, typename = void>
            struct has_resize : std::false_type {};

            template <typename T>
            struct has_resize<T, std::void_t<
                decltype(std::declval<T>().resize(int{},int{}))
            > /* void_t */ > : std::true_type {};

            template <typename T>
            static constexpr bool has_resize_v = has_resize<T>::value;


            template <typename T, typename elements_type, typename = void>
            struct has_set_elements : std::false_type {};

            template <typename T, typename elements_type>
            struct has_set_elements<T, elements_type, std::void_t<
                decltype(std::declval<T>().set_elements(std::declval<elements_type>()))
            > /* void_t */ > : std::true_type {};

            template <typename T, typename elements_type>
            static constexpr bool has_set_elements_v = has_set_elements<T,elements_type>::value;

            template <typename T, typename matrix_type, typename = void>
            struct has_lu_decompostion : std::false_type {};

            template <typename T, typename matrix_type>
            struct has_lu_decompostion<T, matrix_type, std::void_t<
                decltype(T::lu_decomposition(std::declval<matrix_type>()))
            > /* void_t */ > : std::true_type {};

            template <typename T, typename matrix_type>
            static constexpr bool has_lu_decomposition_v = has_lu_decompostion<T,matrix_type>::value;

            template <typename T, typename matrix_type, typename = void>
            struct has_inverse : std::false_type {};

            template <typename T, typename matrix_type>
            struct has_inverse<T, matrix_type, std::void_t<
                decltype(T::inverse(std::declval<matrix_type>()))
            > /* void_t */ > : std::true_type {};

            template <typename T, typename matrix_type>
            static constexpr bool has_inverse_v = has_inverse<T,matrix_type>::value;
        } // namespace traits
        
    } // namespace utils
    
} // namespace gla

#endif // GLA_UTILS_TRAITS_HPP