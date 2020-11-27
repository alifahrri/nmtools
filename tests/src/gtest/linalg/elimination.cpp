#include "nmtools/linalg.hpp"
#include "nmtools/utils/isclose.hpp"
#include <gtest/gtest.h>
#include <cmath>
#include <array>

namespace nmt = nmtools;
namespace nla = nmt::linalg;

using nmt::utils::isclose;

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
        EXPECT_TRUE(nmt::utils::isclose(Ae,expected_A,5e-5));
        EXPECT_TRUE(nmt::utils::isclose(be,expected_b,5e-5));
    }
    {
        constexpr auto tuple = nla::forward_elimination(A,b);
        constexpr auto Ae = std::get<0>(tuple);
        constexpr auto be = std::get<1>(tuple);
        static_assert(nmt::utils::isclose(Ae,expected_A,5e-5));
        static_assert(nmt::utils::isclose(be,expected_b,5e-5));
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
        EXPECT_TRUE(nmt::utils::isclose(x,expected_x,1e-3));
    }
    {
        constexpr auto x = nla::backward_substitution(A,b);
        static_assert(nmt::utils::isclose(x,expected_x,1e-3));
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
        EXPECT_TRUE(nmt::utils::isclose(x,expected_x,1e-3));
    }
    {
        constexpr auto x = nla::naive_gauss_elimination(A,b);
        static_assert(nmt::utils::isclose(x,expected_x,1e-3));
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
        using pivot_t = nla::elimination_tag::pivot_inplace_t;
        auto [Ap,bp] = nla::partial_pivot<pivot_t>(A,b,row);
        EXPECT_TRUE(nmt::utils::isclose(Ap,expected_A));
        EXPECT_TRUE(nmt::utils::isclose(bp,expected_b));
    }
    {
        using pivot_t = nla::elimination_tag::pivot_inplace_t;
        constexpr auto tuple = nla::partial_pivot<pivot_t>(A,b,row);
        constexpr auto Ap = std::get<0>(tuple);
        constexpr auto bp = std::get<1>(tuple);
        static_assert(nmt::utils::isclose(Ap,expected_A));
        static_assert(nmt::utils::isclose(bp,expected_b));
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
        EXPECT_TRUE(nmt::utils::isclose(x,expected_x));
    }
    {
        constexpr auto x = nla::gauss_elimination(A,b);
        static_assert(nmt::utils::isclose(x,expected_x));
    }
}

TEST(linalg, tridiagonal_decomposition)
{
    constexpr auto e = std::array<double,4>{0, -1, -1, -1};
    constexpr auto f = std::array<double,4>{2.04, 2.04, 2.04, 2.04};
    constexpr auto g = std::array<double,4>{-1, -1, -1, 0};
    auto ve = std::vector<double>{0, -1, -1, -1};
    auto vf = std::vector<double>{2.04, 2.04, 2.04, 2.04};
    auto vg = std::vector<double>{-1, -1, -1, 0};
    double re[4] = {0, -1, -1, -1};
    double rf[4] = {2.04, 2.04, 2.04, 2.04};
    double rg[4] = {-1, -1, -1, 0};
    constexpr auto expected_l = std::array<double,4>{0, -0.4901, -0.6452, -0.7169};
    constexpr auto expected_u = std::array<double,4>{2.04, 1.5498, 1.3947, 1.3230};

    /* test with array container at runtime */
    {
        auto [l,u] = nla::tridiagonal_decomposition(e,f,g);
        using return_t = std::array<double,4>;
        static_assert(std::is_same_v<decltype(l),return_t>);
        static_assert(std::is_same_v<decltype(u),return_t>);
        EXPECT_TRUE(isclose(l,expected_l,1e-3));
        EXPECT_TRUE(isclose(u,expected_u,1e-3));
    }
    /* test with vector container at runtime */
    {
        auto [l,u] = nla::tridiagonal_decomposition(ve,vf,vg);
        using return_t = std::vector<double>;
        static_assert(std::is_same_v<decltype(l),return_t>);
        static_assert(std::is_same_v<decltype(u),return_t>);
        EXPECT_TRUE(isclose(l,expected_l,1e-3));
        EXPECT_TRUE(isclose(u,expected_u,1e-3));
    }
    /* test with raw at runtime */
    {
        auto [l,u] = nla::tridiagonal_decomposition(re,rf,rg);
        using return_t = std::array<double,4>;
        static_assert(std::is_same_v<decltype(l),return_t>);
        static_assert(std::is_same_v<decltype(u),return_t>);
        EXPECT_TRUE(isclose(l,expected_l,1e-3));
        EXPECT_TRUE(isclose(u,expected_u,1e-3));
    }
    /* test with array container at compile-time */
    {
        constexpr auto lu = nla::tridiagonal_decomposition(e,f,g);
        constexpr auto l = std::get<0>(lu);
        constexpr auto u = std::get<1>(lu);
        using return_t = const std::array<double,4>;
        static_assert(std::is_same_v<decltype(l),return_t>);
        static_assert(std::is_same_v<decltype(u),return_t>);
        static_assert(isclose(l,expected_l,1e-3));
        static_assert(isclose(u,expected_u,1e-3));
    }
}

TEST(linalg, tridiagonal_substitution)
{
    constexpr auto e = std::array<double,4>{0, -0.49, -0.645, -0.717};
    constexpr auto r = std::array<double,4>{40.8, 0.8, 0.8, 200.8};
    auto ve = std::vector<double>{0, -0.49, -0.645, -0.717};
    auto vr = std::vector<double>{40.8, 0.8, 0.8, 200.8};
    double re[4] = {0, -0.49, -0.645, -0.717};
    double rr[4] = {40.8, 0.8, 0.8, 200.8};
    constexpr auto expected_d = std::array<double,4>{40.8, 20.792, 14.210, 210.989};
    /* test with array container at runtime */
    {
        auto d = nla::tridiagonal_substitution(e,r);
        using return_t = std::array<double,4>;
        static_assert(std::is_same_v<decltype(d),return_t>);
        EXPECT_TRUE(isclose(d,expected_d,1e-3));
    }
    /* test with vector container at runtime */
    {
        auto d = nla::tridiagonal_substitution(ve,vr);
        using return_t = std::vector<double>;
        static_assert(std::is_same_v<decltype(d),return_t>);
        EXPECT_TRUE(isclose(d,expected_d,1e-3));
    }
    /* test with raw array at runtime */
    {
        auto d = nla::tridiagonal_substitution(re,rr);
        using return_t = std::array<double,4>;
        static_assert(std::is_same_v<decltype(d),return_t>);
        EXPECT_TRUE(isclose(d,expected_d,1e-3));
    }
    /* test with array container at compile-time */
    {
        constexpr auto d = nla::tridiagonal_substitution(e,r);
        using return_t = const std::array<double,4>;
        static_assert(std::is_same_v<decltype(d),return_t>);
        static_assert(isclose(d,expected_d,1e-3));
    }
}

TEST(linalg, tridiagonal_backward)
{
    constexpr auto u = std::array<double,4>{2.04, 1.550, 1.395, 1.323};
    constexpr auto d = std::array<double,4>{40.8, 20.792, 14.210, 210.989};
    constexpr auto g = std::array<double,4>{-1, -1, -1, 0};
    auto vu = std::vector<double>{2.04, 1.550, 1.395, 1.323};
    auto vd = std::vector<double>{40.8, 20.792, 14.210, 210.989};
    auto vg = std::vector<double>{-1, -1, -1, 0};
    double ru[4] = {2.04, 1.550, 1.395, 1.323};
    double rd[4] = {40.8, 20.792, 14.210, 210.989};
    double rg[4] = {-1, -1, -1, 0};
    constexpr auto expected_x = std::array<double,4>{65.9517, 93.7415, 124.507, 159.478};
    /* test with array container at runtime */
    {
        auto x = nla::tridiagonal_backward(u,g,d);
        using return_t = std::array<double,4>;
        static_assert(std::is_same_v<decltype(x),return_t>);
        EXPECT_TRUE(isclose(x,expected_x,1e-3));
    }
    /* test with vector container at runtime */
    {
        auto x = nla::tridiagonal_backward(vu,vg,vd);
        using return_t = std::vector<double>;
        static_assert(std::is_same_v<decltype(x),return_t>);
        EXPECT_TRUE(isclose(x,expected_x,1e-3));
    }
    /* test with raw array at runtime */
    {
        auto x = nla::tridiagonal_backward(ru,rg,rd);
        using return_t = std::array<double,4>;
        static_assert(std::is_same_v<decltype(x),return_t>);
        EXPECT_TRUE(isclose(x,expected_x,1e-3));
    }
    /* test with array container at compile-time */
    {
        constexpr auto x = nla::tridiagonal_backward(u,g,d);
        using return_t = const std::array<double,4>;
        static_assert(std::is_same_v<decltype(x),return_t>);
        static_assert(isclose(x,expected_x,1e-3));
    }
}

TEST(linalg, tridiagonal_elimination)
{
    constexpr auto e = std::array<double,4>{0, -1, -1, -1};
    constexpr auto f = std::array<double,4>{2.04, 2.04, 2.04, 2.04};
    constexpr auto g = std::array<double,4>{-1, -1, -1, 0};
    constexpr auto b = std::array<double,4>{40.8, 0.8, 0.8, 200.8};
    constexpr auto expected_x = std::array<double,4>{65.9698, 93.7778, 124.538, 159.480};
    /* test with array container at runtime */
    {
        auto x = nla::tridiagonal_elimination(e,f,g,b);
        using return_t = std::array<double,4>;
        static_assert(std::is_same_v<decltype(x),return_t>);
        EXPECT_TRUE(isclose(x,expected_x,1e-3));
    }
    /* test with array container at compile-time */
    {
        constexpr auto x = nla::tridiagonal_elimination(e,f,g,b);
        using return_t = const std::array<double,4>;
        static_assert(std::is_same_v<decltype(x),return_t>);
        static_assert(isclose(x,expected_x,1e-3));
    }
}

/* TODO: add more test case */