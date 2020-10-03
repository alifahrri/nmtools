#include "nmtools/curvefit.hpp"
#include "nmtools/utility/helper.hpp"
#include <gtest/gtest.h>
#include <tuple>
#include <array>
#include <vector>

namespace nmt = nmtools;
namespace cvt = nmt::curvefit;
using nmt::helper::isclose;

TEST(curvefit, linear_regression)
{
    constexpr auto axd = std::array<double,7>{1,2,3,4,5,6,7};
    constexpr auto ayd = std::array<double,7>{0.5,2.5,2.0,4.0,3.5,6.0,5.5};
    constexpr double rxd[7] = {1,2,3,4,5,6,7};
    constexpr double ryd[7] = {0.5,2.5,2.0,4.0,3.5,6.0,5.5};
    auto vxd = std::vector<double>{1,2,3,4,5,6,7};
    auto vyd = std::vector<double>{0.5,2.5,2.0,4.0,3.5,6.0,5.5};
    /* test linear regression to return coefficients with array container as input at runtime*/
    {
        auto [a0,a1] = cvt::linear_regression(axd,ayd);
        using return_t = double;
        static_assert(std::is_same_v<decltype(a0),return_t>);
        static_assert(std::is_same_v<decltype(a1),return_t>);
        EXPECT_TRUE(isclose(a0,0.07142857));
        EXPECT_TRUE(isclose(a1,0.8392857));
    }
    /* test linear regression to return coefficients with array container as input at compile-time */
    {
        constexpr auto coeff = cvt::linear_regression(axd,ayd);
        constexpr auto a0 = std::get<0>(coeff);
        constexpr auto a1 = std::get<1>(coeff);
        using return_t = const double;
        static_assert(std::is_same_v<decltype(a0),return_t>);
        static_assert(std::is_same_v<decltype(a1),return_t>);
        static_assert(isclose(a0,0.0714286,1e-7));
        static_assert(isclose(a1,0.839286,1e-6));
    }
    /* test linear regression to return callable, with array container as input, at runtime */
    {
        using tag = cvt::rtag::fn_regression_t;
        auto f = cvt::linear_regression<tag>(axd,ayd);
        /* return type is callable */
        static_assert(std::is_invocable_v<decltype(f),double>);
        EXPECT_TRUE(isclose(f(0),0.07142857));
        EXPECT_TRUE(isclose(f(1),0.8392857+0.07142857));
    }
    /* test linear regression to return callable, with array container as input, at compile time */
    {
        using tag = cvt::rtag::fn_regression_t;
        constexpr auto f = cvt::linear_regression<tag>(axd,ayd);
        /* return type is callable */
        static_assert(std::is_invocable_v<decltype(f),double>);
        static_assert(isclose(f(0),0.07142857));
        static_assert(isclose(f(1),0.8392857+0.07142857));
    }
    /* test linear regression to return coefficients, with raw array as input at runtime*/
    {
        auto [a0,a1] = cvt::linear_regression(rxd,ryd);
        using return_t = double;
        static_assert(std::is_same_v<decltype(a0),return_t>);
        static_assert(std::is_same_v<decltype(a1),return_t>);
        EXPECT_TRUE(isclose(a0,0.07142857));
        EXPECT_TRUE(isclose(a1,0.8392857));
    }
    /* test linear regression to return coefficients with raw array as input at compile-time */
    {
        constexpr auto coeff = cvt::linear_regression(rxd,ryd);
        constexpr auto a0 = std::get<0>(coeff);
        constexpr auto a1 = std::get<1>(coeff);
        using return_t = const double;
        static_assert(std::is_same_v<decltype(a0),return_t>);
        static_assert(std::is_same_v<decltype(a1),return_t>);
        static_assert(isclose(a0,0.0714286,1e-7));
        static_assert(isclose(a1,0.839286,1e-6));
    }
    /* test linear regression to return callable, with raw array as input, at runtime */
    {
        using tag = cvt::rtag::fn_regression_t;
        auto f = cvt::linear_regression<tag>(rxd,ryd);
        /* return type is callable */
        static_assert(std::is_invocable_v<decltype(f),double>);
        EXPECT_TRUE(isclose(f(0),0.07142857));
        EXPECT_TRUE(isclose(f(1),0.8392857+0.07142857));
    }
    /* test linear regression to return callable, with raw array as input, at compile time */
    {
        using tag = cvt::rtag::fn_regression_t;
        constexpr auto f = cvt::linear_regression<tag>(rxd,ryd);
        /* return type is callable */
        static_assert(std::is_invocable_v<decltype(f),double>);
        static_assert(isclose(f(0),0.07142857));
        static_assert(isclose(f(1),0.8392857+0.07142857));
    }
    /* test linear regression to return coefficients with vector container as input at runtime*/
    {
        auto [a0,a1] = cvt::linear_regression(vxd,vyd);
        using return_t = double;
        static_assert(std::is_same_v<decltype(a0),return_t>);
        static_assert(std::is_same_v<decltype(a1),return_t>);
        EXPECT_TRUE(isclose(a0,0.07142857));
        EXPECT_TRUE(isclose(a1,0.8392857));
    }
    /* test linear regression to return callable, with vector container as input, at runtime */
    {
        using tag = cvt::rtag::fn_regression_t;
        auto f = cvt::linear_regression<tag>(vxd,vyd);
        /* return type is callable */
        static_assert(std::is_invocable_v<decltype(f),double>);
        EXPECT_TRUE(isclose(f(0),0.07142857));
        EXPECT_TRUE(isclose(f(1),0.8392857+0.07142857));
    }
}

TEST(curvefit, least_square_regression)
{
    using std::array;
    using std::vector;

    /* test using array container */
    {
        auto axd = array<double,15>{   10.,   16.3,    23.,   27.5,     31.,  35.6,    39.,   41.5,   42.9,    45.,    46.,   45.5,    46.,    49.,    50. };
        auto ayd = array<double,15>{ 8.953, 16.405, 22.607, 27.769, 32.065, 35.641, 38.617, 41.095, 43.156, 44.872, 46.301, 47.490, 48.479, 49.303, 49.988 };
        auto [a0, a1] = cvt::least_square_regression(ayd, axd);
        EXPECT_TRUE(isclose(a0,-0.859,1e-3)) << a0;
        EXPECT_TRUE(isclose(a1,1.032,1e-3)) << a1;
    }
    /* test using array container */
    {
        auto x1 = array<double,6>{ 0., 2., 2.5, 1., 4., 7. };
        auto x2 = array<double,6>{ 0., 1., 2.,  3., 6., 2. };
        auto y  = array<double,6>{ 5, 10, 9, 0, 3, 27 };
        auto [a0, a1, a2] = cvt::least_square_regression(y, x1, x2);
        EXPECT_TRUE(isclose(a0,5))  << a0;
        EXPECT_TRUE(isclose(a1,4))  << a1;
        EXPECT_TRUE(isclose(a2,-3)) << a2;
    }
    /* test using array container, return callable */
    {
        using tag = cvt::rtag::fn_regression_t;
        auto axd = array<double,15>{   10.,   16.3,    23.,   27.5,     31.,  35.6,    39.,   41.5,   42.9,    45.,    46.,   45.5,    46.,    49.,    50. };
        auto ayd = array<double,15>{ 8.953, 16.405, 22.607, 27.769, 32.065, 35.641, 38.617, 41.095, 43.156, 44.872, 46.301, 47.490, 48.479, 49.303, 49.988 };
        auto f = cvt::least_square_regression<tag>(ayd, axd);
        static_assert(std::is_invocable_v<decltype(f),double>);
        EXPECT_TRUE(isclose(f(0),-0.859,1e-3));
        EXPECT_TRUE(isclose(f(1),1.032-0.859,1e-3));
    }
    /* test using array container, return callable */
    {
        using tag = cvt::rtag::fn_regression_t;
        auto x1 = array<double,6>{ 0., 2., 2.5, 1., 4., 7. };
        auto x2 = array<double,6>{ 0., 1., 2.,  3., 6., 2. };
        auto y  = array<double,6>{ 5, 10, 9, 0, 3, 27 };
        auto f = cvt::least_square_regression<tag>(y, x1, x2);
        static_assert(std::is_invocable_v<decltype(f),double,double>);
        EXPECT_TRUE(isclose(f(0,0),5));
        EXPECT_TRUE(isclose(f(1,0),4+5));
        EXPECT_TRUE(isclose(f(0,1),-3+5));
    }
    // /* when using vector, unfortunately we can't use structured bindings */
    // {
    //     auto axd = vector<double>{   10.,   16.3,    23.,   27.5,     31.,  35.6,    39.,   41.5,   42.9,    45.,    46.,   45.5,    46.,    49.,    50. };
    //     auto ayd = vector<double>{ 8.953, 16.405, 22.607, 27.769, 32.065, 35.641, 38.617, 41.095, 43.156, 44.872, 46.301, 47.490, 48.479, 49.303, 49.988 };
    //     auto a = cvt::least_square_regression(axd, ayd);
    //     EXPECT_TRUE(isclose(a[0],-0.859,1e-3));
    //     EXPECT_TRUE(isclose(a[1],1.032,1e-3));
    // }
}