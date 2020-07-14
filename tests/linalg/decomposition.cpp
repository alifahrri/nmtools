#include "nmtools/linalg.hpp"
#include "nmtools/utility/helper.hpp"
#include <gtest/gtest.h>
#include <cmath>
#include <array>
#include <vector>

namespace nmt = nmtools;
namespace nla = nmt::linalg;

using std::array;
using std::vector;
using nmt::helper::isclose;

template <size_t n, size_t m, typename T>
using mat_t = array<array<T,n>,m>;
template <size_t n, typename T>
using vec_t = array<T,n>;
using mat3_t = mat_t<3,3,double>;
using vec3_t = vec_t<3,double>;
using mat2_t = mat_t<2,2,double>;
using vec2_t = vec_t<2,double>;

TEST(linalg, lu_decomposition)
{
    constexpr auto A = mat3_t{
        vec3_t{3., -0.1, -0.2},
        vec3_t{0.1, 7, -0.3},
        vec3_t{0.3, -0.2, 10}
    };
    auto vA = vector<vector<double>>{
        vector<double>{3., -0.1, -0.2},
        vector<double>{0.1, 7, -0.3},
        vector<double>{0.3, -0.2, 10}
    };
    constexpr double rA[3][3] = {
        {3., -0.1, -0.2},
        {0.1, 7, -0.3},
        {0.3, -0.2, 10}
    };
    constexpr auto expected_U = mat3_t{
        vec3_t{3., -0.1, -0.2},
        vec3_t{0.0, 7.00333, -0.29333},
        vec3_t{0.0, 0.0, 10.0120}
    };
    constexpr auto expected_L = mat3_t{
        vec3_t{1., 0., 0.},
        vec3_t{0.033333, 1.0, 0.},
        vec3_t{0.1, -0.02713, 1.0},
    };
    constexpr auto expected_b = vec3_t{ 7.85, -19.5617, 70.0843 };
    constexpr auto b = vec3_t{7.85, -19.3, 71.4};
    /* test for matrix with array container at runtime */
    {
        auto [L,U] = nla::lu_decomposition(A);
        EXPECT_TRUE(nmt::helper::isclose(L,expected_L,1e-5));
        EXPECT_TRUE(nmt::helper::isclose(U,expected_U,5e-5));
    }
    /* test for matrix with vector container at runtime */
    {
        auto [L,U] = nla::lu_decomposition(vA);
        EXPECT_TRUE(nmt::helper::isclose(L,expected_L,1e-5));
        EXPECT_TRUE(nmt::helper::isclose(U,expected_U,5e-5));
    }
    /* test for matrix with raw array at runtime */
    {
        auto [L,U] = nla::lu_decomposition(rA);
        EXPECT_TRUE(nmt::helper::isclose(L,expected_L,1e-5));
        EXPECT_TRUE(nmt::helper::isclose(U,expected_U,5e-5));
    }
    /* test for matrix with array container at compile-time */
    {
        constexpr auto LU = nla::lu_decomposition(A);
        constexpr auto L = std::get<0>(LU);
        constexpr auto U = std::get<1>(LU);
        static_assert(nmt::helper::isclose(L,expected_L,1e-5));
        static_assert(nmt::helper::isclose(U,expected_U,5e-5));
    }
    /* test for matrix with raw array at compile-time */
    {
        constexpr auto LU = nla::lu_decomposition(rA);
        constexpr auto L = std::get<0>(LU);
        constexpr auto U = std::get<1>(LU);
        static_assert(nmt::helper::isclose(L,expected_L,1e-5));
        static_assert(nmt::helper::isclose(U,expected_U,5e-5));
    }
}

TEST(linalg, substitution)
{
    constexpr auto L = mat3_t{
        vec3_t{1., 0., 0.},
        vec3_t{0.033333, 1.0, 0.},
        vec3_t{0.1, -0.02713, 1.0},
    };
    auto vL = vector<vector<double>>{
        vector<double>{1., 0., 0.},
        vector<double>{0.033333, 1.0, 0.},
        vector<double>{0.1, -0.02713, 1.0},
    };
    constexpr double rL[3][3] = {
        {1., 0., 0.},
        {0.033333, 1.0, 0.},
        {0.1, -0.02713, 1.0},
    };
    constexpr auto expected_d = vec3_t{ 7.85, -19.5617, 70.0843 };
    constexpr auto b = vec3_t{7.85, -19.3, 71.4};
    /* test with array container at runtime */
    {
        auto d = nla::substitution(L,b);
        EXPECT_TRUE(nmt::helper::isclose(d,expected_d,1e-2));
    }
    /* test with vector container at runtime */
    {
        auto d = nla::substitution(vL,b);
        EXPECT_TRUE(nmt::helper::isclose(d,expected_d,1e-2));
    }
    /* test with raw array at runtime */
    {
        auto d = nla::substitution(rL,b);
        EXPECT_TRUE(nmt::helper::isclose(d,expected_d,1e-2));
    }
    /* test with array container at compile time */
    {
        constexpr auto d = nla::substitution(L,b);
        static_assert(nmt::helper::isclose(d,expected_d,1e-2));
    }
    /* test with raw array at compile time */
    {
        constexpr auto d = nla::substitution(rL,b);
        static_assert(nmt::helper::isclose(d,expected_d,1e-2));
    }
}

TEST(linalg, inverse)
{
    constexpr auto A = mat3_t{
        vec3_t{3., -0.1, -0.2},
        vec3_t{0.1, 7, -0.3},
        vec3_t{0.3, -0.2, 10}
    };
    auto vA = vector<vector<double>>{
        vector<double>{3., -0.1, -0.2},
        vector<double>{0.1, 7, -0.3},
        vector<double>{0.3, -0.2, 10}
    };
    constexpr double rA[3][3] = {
        {3., -0.1, -0.2},
        {0.1, 7, -0.3},
        {0.3, -0.2, 10}
    };
    constexpr auto inverse_A = mat3_t{
        vec3_t{ 0.33249, 0.004944, 0.006798},
        vec3_t{-0.00518, 0.142903, 0.004183},
        vec3_t{-0.01008, 0.00271,  0.09988},
    };
    /* test with array container at runtime */
    {
        auto inv = nla::inverse(A);
        EXPECT_TRUE(isclose(inv,inverse_A,1e-4));
    }
    /* test with vector container at runtime */
    {
        auto inv = nla::inverse(vA);
        EXPECT_TRUE(isclose(inv,inverse_A,1e-4));
    }
    /* test with array container at runtime */
    {
        auto inv = nla::inverse(rA);
        EXPECT_TRUE(isclose(inv,inverse_A,1e-4));
    }
    /* test with array container at compile-time */
    {
        constexpr auto inv = nla::inverse(A);
        static_assert(isclose(inv,inverse_A,1e-4));
    }
    /* test with array container at compile-time */
    {
        constexpr auto inv = nla::inverse(rA);
        static_assert(isclose(inv,inverse_A,1e-4));
    }
}