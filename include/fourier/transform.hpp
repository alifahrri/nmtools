#ifndef FOURIER_TRANSFORM_HPP
#define FOURIER_TRANSFORM_HPP

#include "utility.hpp"

#include <type_traits>
#include <iterator>
#include <complex>
#include <algorithm>
#include <cmath>

namespace numeric {

    namespace fourier {
        namespace detail {
            using namespace std::complex_literals;

            template <typename D>
            using fft_accumulate_return_t = decltype(
                *std::begin(D{}) * 1i,
                *std::begin(D{}) * std::exp(1i*M_PI),
                std::decay_t<decltype(*std::begin(D{}))>()
            );

            template <typename D>
            using fft_stdcomplex_alloc_t = decltype(
                /* container is not a raw array */
                std::declval< typename std::enable_if< !std::is_array<D>::value >::type >(),
                /* element is std::complex */
                std::declval< typename std::enable_if< traits::is_std_complex< decltype(*std::begin( std::declval<D>() ))>::value > >(),
                D()
            );

            template <typename D>
            using fft_stdcomplex_raw_t = decltype(
                /* container is a raw array */
                std::declval< typename std::enable_if< std::is_array<D>::value >::type >(),
                /* element is std::complex */
                std::declval< typename std::enable_if< traits::is_std_complex< decltype(*std::begin( D{} ))>::value > >(),
                std::decay_t<D>{}
            );

            /* implementation of accumulation routine when x is a (generic) container of std::complex */
            template <typename D>
            constexpr auto fft_accumulate(const D &x, size_t k, size_t N) 
                -> fft_accumulate_return_t<D>
            {
                size_t n{0};
                std::decay_t<decltype(*std::begin(x))> Xk{};
                auto w = 2*M_PI/N;
                for (auto xn = std::begin(x); xn != std::end(x); xn++) {
                    Xk += (*xn) * std::exp(-1i*(w*k*n)); n++;
                }
                return Xk;
            }

            /* implementation of dft where x is a (generic) container of std::complex */
            template <typename D>
            constexpr auto dft(const D &x) 
                ->  fft_stdcomplex_alloc_t<D>
            {
                size_t N {std::size(x)};
                D X = x;
                size_t k {0};
                for (auto &Xk : X) {
                    Xk = fft_accumulate(x,k++,N);
                }
                return X;
            }

            template <typename D>
            constexpr auto dft(const D &x) 
                -> fft_stdcomplex_raw_t<D>
            {
                using value_type = std::decay_t< decltype(*std::begin(x)) >;
                size_t N {std::size(x)};
                fft_stdcomplex_raw_t<D> X = new value_type[N];
                for (size_t k = 0; k<N; k++) {
                    X[k] = fft_accumulate(x,k,N);
                }
                return X;
            }

            template <typename D>
            constexpr auto fft2_copy(const D& x, D &odd, D& even, size_t n) 
            {
                size_t oc{0}, ec{0};
                for (size_t i=0; i<n; i++) {
                    if ( i%2 == 0 ) {
                        auto pos = std::begin(odd) + oc;
                        helper::insert(odd,pos,x[i]);
                        oc++;
                    }
                    else {
                        auto pos = std::begin(even) + ec;
                        helper::insert(even,pos,x[i]);
                        ec++;
                    }
                }
            }

            /* dynamic size container */
            template <typename D
            // , typename = std::enable_if_t< traits::is_insertable<D>::value && traits::has_ref_square_bracket_operator<D>::value >
            >
            constexpr auto fft2(const D &x, size_t N, size_t s)
                -> fft_stdcomplex_alloc_t<D>
            {
                if (N==1) {
                    fft_stdcomplex_alloc_t<D> X{};
                    const auto &x0 = *(std::begin(x));
                    // X.insert(std::end(X),x0);
                    helper::insert(X,x0);
                    return X;
                } else {
                    /* placeholder for iterative calls */
                    fft_stdcomplex_alloc_t<D> x0{}, x1{};
                    /* fill inputs for iterative calls arguments */
                    fft2_copy(x,x0,x1,N);
                    /* call fft2 for each odd & even data */
                    auto X0 = fft2(x0,N/2,2*s);
                    auto X1 = fft2(x1,N/2,2*s);
                    /* output placeholder */
                    fft_stdcomplex_alloc_t<D> X{};
                    /* insert value to output placeholder */
                    auto o_odd_it = std::begin(X);
                    auto [i_odd_it,i_even_it] = std::make_tuple( std::begin(X0), std::begin(X1) );
                    auto [i_odd_end,i_even_end] = std::make_tuple( i_odd_it+(N/2), i_even_it+(N/2) );
                    helper::insert(X,o_odd_it,  i_odd_it,  i_odd_end);
                    /* note : we shoud assign updated value from X.begin() */
                    auto o_even_it = std::begin(X) + N/2;
                    helper::insert(X,o_even_it, i_even_it, i_even_end);
                    for (size_t k=0; k<(N/2); k++) {
                        auto t = X[k];
                        X[k] = t + std::exp( -(M_PI*k/N)*2i ) * X[k+N/2];
                        X[k+N/2] = t - std::exp( -(M_PI*k/N)*2i ) * X[k+N/2];
                    }
                    return X;
                }
            }
#if 0
            /* fixed size container */
            template <typename D>
            constexpr auto fft2(const D &x, size_t N, size_t s) 
                -> fft_stdcomplex_alloc_t<D>
            {

            }
#endif
        } // namespace detail

        template <typename D>
        constexpr auto dft(const D &x) 
            -> decltype(detail::dft(x))
        {
            return detail::dft(x);
        }

        template <typename D>
        constexpr auto fft2(const D &x) 
            -> decltype(detail::fft2(x,std::size(x),1))
        {
            return detail::fft2(x,std::size(x),1);
        }
    } // namespace fourier
} // namespace numeric

#endif // FOURIER_TRANSFORM_HPP