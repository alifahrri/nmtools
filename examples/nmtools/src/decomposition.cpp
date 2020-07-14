#include <array>
#include <tuple>
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

    DESC("perform LU Decomposition at runtime")
    {
        auto [L,U] = nla::lu_decomposition(A);
        print_matrix(L);
        print_matrix(U);
    }

    DESC("perform LU Decomposition at compile-time")
    {
        constexpr auto LU = nla::lu_decomposition(A);
        constexpr auto L = std::get<0>(LU);
        constexpr auto U = std::get<1>(LU);
        print_matrix(L);
        print_matrix(U);
    }

    DESC("perform matrix inversion at runtime")
    {
        auto inv = nla::inverse(A);
        print_matrix(inv);
    }

    DESC("perform matrix inversion at compile-time")
    {
        constexpr auto inv = nla::inverse(A);
        print_matrix(inv);
    }
}