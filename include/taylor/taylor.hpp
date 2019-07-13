#ifndef TAYLOR_SERIES_HPP
#define TAYLOR_SERIES_HPP

#include <cmath>

namespace numeric {
    namespace taylor {
        namespace detail {
            constexpr size_t factorial(size_t n) {
                return n > 0 ? n * factorial(n-1) : 1;
            }
            template <size_t N, typename Scalar>
            constexpr Scalar taylor_series(Scalar a, Scalar h) {
                return 0;
            }

            template <size_t N, typename Scalar, typename F>
            constexpr Scalar taylor_series(Scalar a, Scalar h, const F &f) {
                return (f(a) * std::pow(h,N) / factorial(N));
            }

            template <size_t N, typename Scalar, typename F, typename ...DFs>
            constexpr Scalar taylor_series(Scalar a, Scalar h, const F &f, const DFs& ... dfs) {
                return (f(a) * std::pow(h,N) / factorial(N)) + taylor_series<N+1,Scalar>(a,h,dfs...);
            } // namespace detail
        }

        template <typename Scalar, typename F, typename ...DFs>
        constexpr Scalar taylor_series(Scalar x, Scalar a, const F &f, const DFs& ...dfs) {
            return f(a) + detail::taylor_series<1,Scalar>(a,x-a,dfs...);
        }
    } // namespace taylor
} // namespace numeric
#endif // TAYLOR_SERIES_HPP