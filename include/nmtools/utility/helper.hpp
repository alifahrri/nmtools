#ifndef NMTOOLS_UTILITY_HELPER_HPP
#define NMTOOLS_UTILITY_HELPER_HPP

#include <type_traits>
#include <cassert>
#include <iterator>
#include <cmath>
#include <tuple>
#include <array>
#include "nmtools/traits.hpp"

namespace nmtools::helper {

    using std::size;

    /**
     * @brief helper function for compile-time conditional logging
     * 
     * @tparam Logger 
     * @param logger logger pointer to callable
     * @param mapping arguments mapping, to be logged
     * @return auto 
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
        using traits::is_array1d_v;
        using traits::is_array2d_v;
        using traits::has_tuple_size_v;
        using std::is_arithmetic_v;
        static_assert(
            (is_arithmetic_v<T> && is_arithmetic_v<U>) ||
            (is_array1d_v<T> && is_array1d_v<U>) ||
            (is_array2d_v<T> && is_array2d_v<U>),
            "unsupported isclose"
        );
        if constexpr (is_arithmetic_v<T>)
            return fabs(M-N) < eps;
        else {
            auto nm = size(M);
            auto nn = size(N);
            /* size is known at compile-time, assert at compile-time */
            if constexpr (has_tuple_size_v<T> && has_tuple_size_v<U>) {
                constexpr auto nm = std::tuple_size_v<T>;
                constexpr auto nn = std::tuple_size_v<U>;
                static_assert(nm==nn);
            }
            /* defer assertion to runtime */
            else assert(nm==nn);
            
            for (size_t i=0; i<nm; i++) {
                auto m = M[i];
                auto n = N[i];
                if constexpr (std::is_arithmetic_v<decltype(m)>) {
                    if (fabs(m-n) > eps)
                        return false;
                } else {
                    auto nmm = size(m);
                    auto nnn = size(n);
                    assert (nmm=nnn);
                    for (size_t j=0; j<nmm; j++) {
                        auto mm = m[j];
                        auto nn = n[j];
                        if (fabs(mm-nn) > eps)
                            return false;
                    }
                }
            }
            return true;
        }
    }

} // namespace nmtools::helper

#endif // NMTOOLS_UTILITY_HELPER_HPP