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

template <typename T>
using mat3 = mat_t<3,3,T>;
template <typename T>
using vec3 = vec_t<3,T>;

using mat3d = mat3<double>;
using vec3d = vec3<double>;
using mat3f = mat3<float>;
using vec3f = vec3<float>;

int main()
{
    constexpr auto A = mat3d{
        vec3d{3.0, -0.1, -0.2},
        vec3d{0.1,  7.0, -0.3},
        vec3d{0.3, -0.2, 10.0},
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

    DESC("cholesky decomposition at runtime")
    {
        constexpr auto A = mat3d{
            vec3d{ 6,  15,  55},
            vec3d{15,  55, 225},
            vec3d{55, 225, 979},
        };
        auto L = nla::cholesky_decomposition(A);
        print_matrix(L);
    }

    DESC("cholesky decomposition at compile-time")
    {
        constexpr auto A = mat3d{
            vec3d{ 6,  15,  55},
            vec3d{15,  55, 225},
            vec3d{55, 225, 979},
        };
        constexpr auto L = nla::cholesky_decomposition(A);
        print_matrix(L);
    }
}