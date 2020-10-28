#ifndef NMTOOLS_UTILITY_HELPER_HPP
#define NMTOOLS_UTILITY_HELPER_HPP

#include "nmtools/traits.hpp"
#include "nmtools/array/utility.hpp"

#include <type_traits>
#include <cassert>
#include <iterator>
#include <cmath>
#include <tuple>
#include <array>

namespace nmtools::helper {

    using std::size;

    /**
     * @brief helper function for compile-time conditional logging
     * 
     * @tparam Logger 
     * @param logger logger pointer to callable
     * @param mapping arguments mapping, to be logged
     * @return auto 
     * @todo remove
     */
    template <typename Logger>
    auto log(Logger logger, auto mapping) {
        /* only compile if logger is not nullptr_t */
        if constexpr (!std::is_null_pointer_v<Logger>) {
            static_assert(
                std::is_pointer_v<Logger>, 
                "expects logger to be pointer"
            );
            (*logger)(mapping);
        }
    }

    /**
     * @addtogroup utils
     * @{
     */

    /**
     * @brief implemenatation detail for isclose
     * 
     */
    namespace detail {

        using traits::is_array1d_v;
        using traits::is_array2d_v;
        using traits::has_tuple_size_v;
        using traits::is_fixed_size_matrix_v;
        using std::get;
        using std::is_arithmetic_v;

        /**
        * @brief check if M is close with N given tolerance
        * 
        * @param M matrix-like or vector-like
        * @param N matrix-like or vector-like
        * @param eps tolerance
        * @return constexpr auto 
        */
        template <typename T, typename U, typename E=double>
        constexpr auto isclose(const T& M, const U& N, E eps=1e-6)
        {
            static_assert(
                (is_arithmetic_v<T> && is_arithmetic_v<U>) ||
                (is_array1d_v<T> && is_array1d_v<U>) ||
                (is_array2d_v<T> && is_array2d_v<U>),
                "unsupported isclose"
            );
            if constexpr (is_array2d_v<T> && is_array2d_v<U>)
            {
                if constexpr (is_fixed_size_matrix_v<T> && is_fixed_size_matrix_v<U>) {
                    constexpr auto msize = fixed_matrix_size_v<T>;
                    constexpr auto nsize = fixed_matrix_size_v<U>;
                    constexpr auto nrow = get<0>(nsize);
                    constexpr auto ncol = get<1>(nsize);
                    constexpr auto mrow = get<0>(msize);
                    constexpr auto mcol = get<1>(msize);
                    /* TODO: size assertion */
                    /* TODO: unify this loop with runtime version */
                    for (size_t i=0; i<nrow; i++)
                        for (size_t j=0; j<ncol; j++)
                            if (fabs(at(M,i,j)-at(N,i,j)) > eps)
                                return false;
                    return true;
                }
                else {
                    auto [nrow, ncols] = matrix_size(N);
                    auto [mrow, mcols] = matrix_size(M);
                    /* TODO: size assertion */
                    /* TODO: unify this loop with compile-time version */
                    for (size_t i=0; i<nrow; i++)
                        for (size_t j=0; j<ncols; j++)
                            if (fabs(at(M,i,j)-at(N,i,j)) > eps)
                                return false;
                    return true;
                }
            }
            else if constexpr (is_array1d_v<T> && is_array1d_v<U>)
            {
                auto nm = vector_size(M);
                auto nn = vector_size(N);
                /* TODO: size assertion */
                for (size_t i=0; i<nm; i++)
                    if (fabs(at(M,i)-at(N,i)) > eps)
                        return false;
                return true;
            }
            else if constexpr (is_arithmetic_v<T> && is_arithmetic_v<U>)
            {
                return fabs(M-N) < eps;
            }
        } // constexpr auto isclose

        /**
         * @brief handles isclose for packed matrix/vector using fold expression.
         * 
         * @tparam T tuple
         * @tparam U tuple
         * @tparam E=double 
         * @tparam I index sequence
         * @param t lhs
         * @param u rhs
         * @param eps 
         * @return constexpr auto 
         */
        template <typename T, typename U, typename E=double, size_t...I>
        constexpr auto isclose(const T& t, const U& u, std::integer_sequence<size_t,I...>, E eps=1e-6)
        {
            constexpr auto is_tuple_T = traits::is_tuple_v<T>;
            constexpr auto is_tuple_U = traits::is_tuple_v<U>;

            /* unpack */    
            return (... && isclose(std::get<I>(t),std::get<I>(u),eps));
        } // constexpr auto isclose
    } // namespace detail

    /**
     * @brief check if M is close with N given tolerance. When M and N is packed,
     * like in tuple, then they must have same tuple size.
     * 
     * @tparam T possibly-packed (e.g. tuple) matrix-like or vector-like
     * @tparam U possibly-packed (e.g. tuple) matrix-like or vector-like
     * @tparam E=double 
     * @param t (tuple of) matrix or vector or scalar
     * @param u (tuple of) matrix or vector or scalar
     * @param eps 
     * @return constexpr auto 
     */
    template <typename T, typename U, typename E=double>
    constexpr auto isclose(const T& t, const U& u, E eps=1e-6)
    {
        // check if T & U is std::tuple
        constexpr auto is_tuple_T = traits::is_tuple_v<T>;
        constexpr auto is_tuple_U = traits::is_tuple_v<U>;
        // check if tuple_size for T & U is available
        constexpr auto is_packed_T = traits::has_tuple_size_v<T>;
        constexpr auto is_packed_U = traits::has_tuple_size_v<U>;
        // check if T & U is simply array
        constexpr auto is_array_T = traits::is_array1d_v<T> || traits::is_array2d_v<T>;
        constexpr auto is_array_U = traits::is_array1d_v<U> || traits::is_array2d_v<U>;
        // @note that std::array will be array & packed, std::tuple will be tuple & packed, std::pair will be only packed

        if constexpr (is_packed_T && is_packed_U) {
            // @note check for packed instead of strictly tuple to allow comparison between std::pair / std::tuple with std::array
            constexpr auto nt = std::tuple_size_v<T>;
            constexpr auto nu = std::tuple_size_v<U>;
            static_assert(nt == nu, "size mismatch for packed type");
            using index_t = std::make_index_sequence<nt>;
            // call overloaded isclose which takes compile-time indices
            return detail::isclose(t,u,index_t{},eps);
        }
        else {
            // call overloaded isclose which simply takes array/arithmetic
            return detail::isclose(t,u,eps);
        }
    } // constexpr auto isclose
    
    /**
     * @brief stringify given array to given stream type.
     * 
     * @tparam stream_t stream type, e.g. std::stringstream,
     * @tparam T array-like, 2d, 1d, or scalar
     * @param array array to stringify
     * @return auto stream with type of stream_t
     */
    template <typename stream_t, typename T>
    auto stringify(const T& array)
    {
        auto stream = stream_t{};
        if constexpr (traits::is_array2d_v<T>) {
            auto [rows, cols] = matrix_size(array);
            for (size_t i=0; i<rows; i++) {
                // NOTE: std basic_stringstream cant have operator <<
                // with another basic_stringsteam lol, call str() for temporary workaround
                stream << stringify<stream_t>(row(array,i)).str() << "\n";
            }
        }
        else if constexpr (traits::is_array1d_v<T>) {
            auto n = vector_size(array);
            for (size_t i=0; i<n; i++)
                stream << at(array,i) << "\t";
        }
        else {
            stream << array;
        }
        return stream;
    } // auto stringify

    /** @} */ // end group utils
} // namespace nmtools::helper

#endif // NMTOOLS_UTILITY_HELPER_HPP