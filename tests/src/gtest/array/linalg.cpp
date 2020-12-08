#include "nmtools/array/fixed.hpp"
#include "nmtools/blas/blas.hpp"
#include "nmtools/utils/isclose.hpp"
#include "nmtools/linalg.hpp"
#include <gtest/gtest.h>
#include <array>

namespace nmt = nmtools;
using nmt::utils::isclose;
using nmt::array::fixed_vector;
using nmt::array::fixed_matrix;

using vec2_t   = std::array<double,2>;
using vec3_t   = std::array<double,3>;
using mat3x3_t = std::array<vec3_t,3>;
using mat2x2_t = std::array<vec2_t,2>;

TEST(fixed_array_linalg, forward_elimination)
{
    auto A = fixed_matrix<double,3,3>({
        {3., -0.1, -0.2},
        {0.1, 7, -0.3},
        {0.3, -0.2, 10}
    });
    auto b = fixed_vector<double,3>({7.85, -19.3, 71.4});
    auto expected_A = mat3x3_t{
        vec3_t{3., -0.1, -0.2},
        vec3_t{0.0, 7.00333, -0.29333},
        vec3_t{0.0, 0.0, 10.0120}
    };
    auto expected_b = vec3_t{ 7.85, -19.5617, 70.0843 };

    {
        auto [Ae,be] = nmt::linalg::forward_elimination(A,b);
        EXPECT_TRUE(isclose(Ae,expected_A,5e-5));
        EXPECT_TRUE(isclose(be,expected_b,5e-5));
    }
}

TEST(fixed_array_linalg, backward_substitution)
{
    auto A = fixed_matrix<double,3,3>({
        {3., -0.1, -0.2},
        {0.0, 7.00333, -0.29333},
        {0.0, 0.0, 10.0120}
    });
    auto b = fixed_vector<double,3>({ 7.85, -19.5617, 70.0843 });
    auto expected_x = vec3_t{ 3., -2.5, 7.};
    {
        auto x = nmt::linalg::backward_substitution(A,b);
        EXPECT_TRUE(isclose(x,expected_x,1e-3));
    }
}

TEST(fixed_array_linalg, naive_gauss_elimination)
{
    auto A = fixed_matrix<double,3,3>({
        {3., -0.1, -0.2},
        {0.1, 7, -0.3},
        {0.3, -0.2, 10}
    });
    auto b = fixed_vector<double,3>({7.85, -19.3, 71.4});
    auto expected_x = vec3_t{ 3., -2.5, 7.};
    {
        auto x = nmt::linalg::naive_gauss_elimination(A,b);
        EXPECT_TRUE(isclose(x,expected_x,1e-3));
    }
}

TEST(fixed_array_linalg, partial_pivot)
{
    auto A = fixed_matrix<double,2,2>({
        {3e-3, 3e+0},
        {1e+0, 1e+0},
    });
    auto b = fixed_vector<double,2>({ 2.0001, 1.0000 });
    auto row = int{0};
    auto expected_A = mat2x2_t{{
        {1e+0, 1e+0},
        {3e-3, 3e+0},
    }};
    auto expected_b = vec2_t{ 1.0000, 2.0001, };
    {
        auto p = nmt::linalg::partial_pivot(A,b,row);
        EXPECT_TRUE(p==1);
    }
    {
        using pivot_t = nmt::linalg::elimination_tag::pivot_inplace_t;
        auto [Ap,bp] = nmt::linalg::partial_pivot<pivot_t>(A,b,row);
        EXPECT_TRUE(isclose(Ap,expected_A));
        EXPECT_TRUE(isclose(bp,expected_b));
    }
}

TEST(fixed_array_linalg, gauss_elimination)
{
    auto A = fixed_matrix<double,2,2>({
        {2e+0, 1e+5},
        {1e+0, 1e+0},
    });
    auto b = fixed_vector<double,2>({ 1e+5 + 2, 2e+0 });
    auto expected_x = vec2_t{ 1.0, 1.0 };
    {
        auto x = nmt::linalg::gauss_elimination(A,b);
        EXPECT_TRUE(isclose(x,expected_x));
    }
}

TEST(fixed_array_linalg, tridiagonal_decomposition)
{
    auto e = fixed_vector<double,4>({0, -1, -1, -1});
    auto f = fixed_vector<double,4>({2.04, 2.04, 2.04, 2.04});
    auto g = fixed_vector<double,4>({-1, -1, -1, 0});
    auto expected_l = std::array<double,4>{0, -0.4901, -0.6452, -0.7169};
    auto expected_u = std::array<double,4>{2.04, 1.5498, 1.3947, 1.3230};
    {
        auto [l,u] = nmt::linalg::tridiagonal_decomposition(e,f,g);
        using return_t = fixed_vector<double,4>;
        static_assert(std::is_same_v<decltype(l),return_t>);
        static_assert(std::is_same_v<decltype(u),return_t>);
        EXPECT_TRUE(isclose(l,expected_l,1e-3));
        EXPECT_TRUE(isclose(u,expected_u,1e-3));
    }
}

TEST(fixed_array_linalg, tridiagonal_substitution)
{
    auto e = fixed_vector<double,4>({0, -0.49, -0.645, -0.717});
    auto r = fixed_vector<double,4>({40.8, 0.8, 0.8, 200.8});
    auto expected_d = std::array<double,4>{40.8, 20.792, 14.210, 210.989};
    /* test with array container at runtime */
    {
        auto d = nmt::linalg::tridiagonal_substitution(e,r);
        using return_t = fixed_vector<double,4>;
        static_assert(std::is_same_v<decltype(d),return_t>);
        EXPECT_TRUE(isclose(d,expected_d,1e-3));
    }
}

TEST(fixed_array_linalg, tridiagonal_backward)
{
    auto u = fixed_vector<double,4>({2.04, 1.550, 1.395, 1.323});
    auto d = fixed_vector<double,4>({40.8, 20.792, 14.210, 210.989});
    auto g = fixed_vector<double,4>({-1, -1, -1, 0});
    auto expected_x = std::array<double,4>{65.9517, 93.7415, 124.507, 159.478};
    /* test with array container at runtime */
    {
        auto x = nmt::linalg::tridiagonal_backward(u,g,d);
        using return_t = fixed_vector<double,4>;
        static_assert(std::is_same_v<decltype(x),return_t>);
        EXPECT_TRUE(isclose(x,expected_x,1e-3));
    }
}

TEST(fixed_array_linalg, tridiagonal_elimination)
{
    auto e = fixed_vector<double,4>({0, -1, -1, -1});
    auto f = fixed_vector<double,4>({2.04, 2.04, 2.04, 2.04});
    auto g = fixed_vector<double,4>({-1, -1, -1, 0});
    auto b = fixed_vector<double,4>({40.8, 0.8, 0.8, 200.8});
    auto expected_x = std::array<double,4>{65.9698, 93.7778, 124.538, 159.480};
    /* test with array container at runtime */
    {
        auto x = nmt::linalg::tridiagonal_elimination(e,f,g,b);
        using return_t = fixed_vector<double,4>;
        static_assert(std::is_same_v<decltype(x),return_t>);
        EXPECT_TRUE(isclose(x,expected_x,1e-3));
    }
}

TEST(fixed_array_linalg, lu_decomposition)
{
    auto A = fixed_matrix<double,3,3>({
        {3., -0.1, -0.2},
        {0.1, 7, -0.3},
        {0.3, -0.2, 10},
    });
    auto expected_U = mat3x3_t{{
        {3., -0.1, -0.2},
        {0.0, 7.00333, -0.29333},
        {0.0, 0.0, 10.0120}
    }};
    auto expected_L = mat3x3_t{{
        {1., 0., 0.},
        {0.033333, 1.0, 0.},
        {0.1, -0.02713, 1.0},
    }};
    /* test for matrix with array container at runtime */
    {
        auto [L,U] = nmt::linalg::lu_decomposition(A);
        EXPECT_TRUE(isclose(L,expected_L,1e-5));
        EXPECT_TRUE(isclose(U,expected_U,5e-5));
    }
}

TEST(fixed_array_linalg, substitution)
{
    auto L = fixed_matrix<double,3,3>({
        {1., 0., 0.},
        {0.033333, 1.0, 0.},
        {0.1, -0.02713, 1.0,}
    });
    auto b = vec3_t{7.85, -19.3, 71.4};
    auto expected_d = vec3_t{ 7.85, -19.5617, 70.0843 };
    /* test with array container at runtime */
    {
        auto d = nmt::linalg::substitution(L,b);
        EXPECT_TRUE(isclose(d,expected_d,1e-2));
    }
}

TEST(fixed_array_linalg, inverse)
{
    auto A = fixed_matrix<double,3,3>({
        {3., -0.1, -0.2},
        {0.1, 7, -0.3},
        {0.3, -0.2, 10},
    });
    auto inverse_A = mat3x3_t{{
        { 0.33249, 0.004944, 0.006798},
        {-0.00518, 0.142903, 0.004183},
        {-0.01008, 0.00271,  0.09988},
    }};
    {
        auto inv = nmt::linalg::inverse(A);
        EXPECT_TRUE(isclose(inv,inverse_A,1e-4));
    }
}

TEST(fixed_array_linalg, cholesky_decomposition)
{
    auto A = fixed_matrix<double,3,3>({
         {6,  15,  55},
        {15,  55, 225},
        {55, 225, 979},
    });
    auto expected_L = mat3x3_t{{
        {2.44949, 0      , 0},
        {6.12372, 4.1833 , 0},
        {22.4537, 20.9165, 6.1101},
    }};
    /* test with array container at runtime */
    {
        auto L = nmt::linalg::cholesky_decomposition(A);
        /* type of L should be same as A which is mat3_t */
        using return_t = fixed_matrix<double,3,3>;
        static_assert(std::is_same_v<decltype(L),return_t>);
        EXPECT_TRUE(isclose(L,expected_L,1e-4));
    }
}