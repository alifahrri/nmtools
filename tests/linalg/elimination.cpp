#include "nmtools/linalg.hpp"
#include "nmtools/utility/helper.hpp"
#include <gtest/gtest.h>
#include <cmath>
#include <array>

namespace nmt = nmtools;
namespace nla = nmt::linalg;

using std::array;
template <size_t n, size_t m, typename T>
using mat_t = array<array<T,n>,m>;
template <size_t n, typename T>
using vec_t = array<T,n>;
using mat3_t = mat_t<3,3,double>;
using vec3_t = vec_t<3,double>;
using mat2_t = mat_t<2,2,double>;
using vec2_t = vec_t<2,double>;

TEST(linalg, forward_elimination)
{
    constexpr auto A = mat3_t{
        vec3_t{3., -0.1, -0.2},
        vec3_t{0.1, 7, -0.3},
        vec3_t{0.3, -0.2, 10}
    };
    constexpr auto expected_A = mat3_t{
        vec3_t{3., -0.1, -0.2},
        vec3_t{0.0, 7.00333, -0.29333},
        vec3_t{0.0, 0.0, 10.0120}
    };
    constexpr auto expected_b = vec3_t{ 7.85, -19.5617, 70.0843 };
    constexpr auto b = vec3_t{7.85, -19.3, 71.4};
    {
        auto [Ae, be] = nla::forward_elimination(A,b);
        EXPECT_TRUE(nmt::helper::isclose(Ae,expected_A,5e-5));
        EXPECT_TRUE(nmt::helper::isclose(be,expected_b,5e-5));
    }
    {
        constexpr auto tuple = nla::forward_elimination(A,b);
        constexpr auto Ae = std::get<0>(tuple);
        constexpr auto be = std::get<1>(tuple);
        static_assert(nmt::helper::isclose(Ae,expected_A,5e-5));
        static_assert(nmt::helper::isclose(be,expected_b,5e-5));
    }
}

TEST(linalg, backward_substitution)
{
    constexpr auto A = mat3_t{
        vec3_t{3., -0.1, -0.2},
        vec3_t{0.0, 7.00333, -0.29333},
        vec3_t{0.0, 0.0, 10.0120}
    };
    constexpr auto b = vec3_t{ 7.85, -19.5617, 70.0843 };
    constexpr auto expected_x = vec3_t{ 3., -2.5, 7.};
    {
        auto x = nla::backward_substitution(A,b);
        EXPECT_TRUE(nmt::helper::isclose(x,expected_x,1e-3));
    }
    {
        constexpr auto x = nla::backward_substitution(A,b);
        static_assert(nmt::helper::isclose(x,expected_x,1e-3));
    }
}

TEST(linalg, naive_gauss_elimination)
{
    constexpr auto A = mat3_t{
        vec3_t{3., -0.1, -0.2},
        vec3_t{0.1, 7, -0.3},
        vec3_t{0.3, -0.2, 10}
    };
    constexpr auto b = vec3_t{7.85, -19.3, 71.4};
    constexpr auto expected_x = vec3_t{ 3., -2.5, 7.};
    {
        auto x = nla::naive_gauss_elimination(A,b);
        EXPECT_TRUE(nmt::helper::isclose(x,expected_x,1e-3));
    }
    {
        constexpr auto x = nla::naive_gauss_elimination(A,b);
        static_assert(nmt::helper::isclose(x,expected_x,1e-3));
    }
}

TEST(linalg, partial_pivot)
{
    constexpr auto A = mat2_t{
        vec2_t{3e-3, 3e+0},
        vec2_t{1e+0, 1e+0},
    };
    constexpr auto b = vec2_t{ 2.0001, 1.0000 };
    constexpr auto row = int{0};
    constexpr auto expected_A = mat2_t{
        vec2_t{1e+0, 1e+0},
        vec2_t{3e-3, 3e+0},
    };
    constexpr auto expected_b = vec2_t{ 1.0000, 2.0001, };
    {
        auto p = nla::partial_pivot(A,b,row);
        EXPECT_TRUE(p==1);
    }
    {
        constexpr auto p = nla::partial_pivot(A,b,row);
        static_assert(p==1);
    }
    {
        using pivot_t = nla::tag::pivot_inplace_t;
        auto [Ap,bp] = nla::partial_pivot<pivot_t>(A,b,row);
        EXPECT_TRUE(nmt::helper::isclose(Ap,expected_A));
        EXPECT_TRUE(nmt::helper::isclose(bp,expected_b));
    }
    {
        using pivot_t = nla::tag::pivot_inplace_t;
        constexpr auto tuple = nla::partial_pivot<pivot_t>(A,b,row);
        constexpr auto Ap = std::get<0>(tuple);
        constexpr auto bp = std::get<1>(tuple);
        static_assert(nmt::helper::isclose(Ap,expected_A));
        static_assert(nmt::helper::isclose(bp,expected_b));
    }
}

TEST(linalg, gauss_elimination)
{
    constexpr auto A = mat2_t{
        vec2_t{2e+0, 1e+5},
        vec2_t{1e+0, 1e+0},
    };
    constexpr auto b = vec2_t{ 1e+5 + 2, 2e+0 };
    constexpr auto expected_x = vec2_t{ 1.0, 1.0 };
    {
        auto x = nla::gauss_elimination(A,b);
        EXPECT_TRUE(nmt::helper::isclose(x,expected_x));
    }
    {
        constexpr auto x = nla::gauss_elimination(A,b);
        static_assert(nmt::helper::isclose(x,expected_x));
    }
}

/* TODO: add more test case */