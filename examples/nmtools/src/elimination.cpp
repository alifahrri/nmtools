#include <array>
#include <iostream>
#include "nmtools/linalg.hpp"

namespace nmt = nmtools;
namespace nla = nmt::linalg;

using std::array;
using std::nullptr_t;

#define DESC(x) std::cout << x << std::endl;

template <size_t n, size_t m, typename T>
using mat_t = array<array<T,n>,m>;
template <size_t n, typename T>
using vec_t = array<T,n>;

int main()
{
    constexpr auto A = mat_t<3,3,double>{
        vec_t<3,double>{3.0, -0.1, -0.2},
        vec_t<3,double>{0.1,  7.0, -0.3},
        vec_t<3,double>{0.3, -0.2, 10.0},
    };
    constexpr auto b = vec_t<3,double>{7.85, -19.3, 71.4};
    auto logger = [](auto mapping){
        for (auto [k,v] : mapping)
            std::cout << k << " = " << v << "\t";
        std::cout << std::endl;
    };
    auto print_matrix = [](auto M){
        for (const auto m : M) {
            if constexpr (std::is_arithmetic_v<decltype(m)>)
                std::cout << m << "\t";
            else {
                for (const auto a : m)
                    std::cout << a << "\t";
            }
            std::cout << std::endl;
        }
    };

    DESC("gauss elimintation at runtime with logging")
    {
        auto s = nullptr_t{}; // do not use scales
        auto [Ae, be] = nla::forward_elimination(A,b,s,&logger);
        DESC("upper tridiagonal matrix");
        print_matrix(Ae);
        DESC("rhs vector");
        print_matrix(be);
        auto x = nla::backward_substitution(Ae,be,&logger);
        DESC("solution vector");
        print_matrix(x);
    }

    DESC("gauss elimination at compile-time")
    {
        constexpr auto x = nla::naive_gauss_elimination(A,b);
        DESC("solution vector");
        print_matrix(x);
    }

    DESC("partial pivoting")
    {
        /* some ill-conditioned matrix */
        constexpr auto A = mat_t<2,2,double>{
            vec_t<2,double>{3e-3, 3e+0},
            vec_t<2,double>{1e+0, 1e+0},
        };
        constexpr auto b = vec_t<2,double>{ 2.0001, 1.0000 };

        DESC("original matrix A");
        print_matrix(A);
        DESC("original vector b");
        print_matrix(b);

        auto row = int{0}; // perform pivot at row 0

        DESC("default parital pivot only return pivot row")
        {
            /* using default pivot tag */
            auto p = nla::partial_pivot(A,b,row);
            std::cout << "pivot row: "  << p << std::endl;
        }

        DESC("in-place partial pivoting")
        {
            /* pivot tag selection, here we will perform in-place pivoting */
            using pivot_t = nla::tag::pivot_inplace_t;
            auto [Ar,br] = nla::partial_pivot<pivot_t>(A,b,row);

            DESC("matrix A after pivot");
            print_matrix(Ar);
            DESC("vector b after pivot");
            print_matrix(br);
        }

        DESC("in-place partial pivoting with scaling")
        {
            /* some ill-conditioned matrix */
            constexpr auto A = mat_t<2,2,double>{
                vec_t<2,double>{2e+0, 1e+5},
                vec_t<2,double>{1e+0, 1e+0},
            };
            constexpr auto b = vec_t<2,double>{ 1e+5, 2e+0 };
            constexpr auto scales = vec_t<2,double>{ 1e+5, 1e+0 };
            DESC("original matrix A");
            print_matrix(A);
            DESC("original vector b");
            print_matrix(b);

            /* pivot tag selection, here we will perform in-place pivoting */
            using pivot_t = nla::tag::pivot_inplace_t;
            /* partial pivot with scales */
            auto [Ar,br,s] = nla::partial_pivot<pivot_t>(A,b,row,scales);

            DESC("matrix A after pivot");
            print_matrix(Ar);
            DESC("vector b after pivot");
            print_matrix(br);
            DESC("scales after pivot");
            print_matrix(s);
        }

        DESC("forward elimination with partial pivoting")
        {
            /* some ill-conditioned matrix */
            constexpr auto A = mat_t<2,2,double>{
                vec_t<2,double>{2e+0, 1e+5},
                vec_t<2,double>{1e+0, 1e+0},
            };
            constexpr auto b = vec_t<2,double>{ 1e+5 + 2, 2e+0 };
            constexpr auto scales = vec_t<2,double>{ 1e+5, 1e+0 };
            DESC("original matrix A");
            print_matrix(A);
            DESC("original vector b");
            print_matrix(b);

            /* use forward elimination with pivot */
            using elim_t = nla::tag::elimination_with_pivot_t;
            auto [Ae, be] = nla::forward_elimination<elim_t>(A,b,scales);

            DESC("matrix A after elimination");
            print_matrix(Ae);
            DESC("vector b after elimination");
            print_matrix(be);
        }

        DESC("gauss elimintation with partial pivot and scaling")
        {
            /* some ill-conditioned matrix */
            constexpr auto A = mat_t<2,2,double>{
                vec_t<2,double>{2e+0, 1e+5},
                vec_t<2,double>{1e+0, 1e+0},
            };
            constexpr auto b = vec_t<2,double>{ 1e+5 + 2, 2e+0 };
            constexpr auto scales = vec_t<2,double>{ 1e+5, 1e+0 };
            DESC("original matrix A");
            print_matrix(A);
            DESC("original vector b");
            print_matrix(b);

            auto x = nla::gauss_elimination(A,b);
            DESC("solution vector");
            print_matrix(x);
        }
    }
}