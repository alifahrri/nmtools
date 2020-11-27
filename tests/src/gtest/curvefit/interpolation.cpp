#include "nmtools/curvefit.hpp"
#include "nmtools/utils/isclose.hpp"
#include <gtest/gtest.h>

namespace nmt = nmtools;
namespace cvt = nmtools::curvefit;
using std::array;
using std::vector;
using nmt::utils::isclose;

TEST(curvefit, compute_slopes)
{
    {
        auto x = array<double,4>{3.0, 4.5, 7.0, 9.0};
        auto y = array<double,4>{2.5, 1.0, 2.5, 0.5};

        auto m = cvt::compute_slopes(x,y);
        using return_t = array<double,3>;
        auto expected = return_t{-1.0, 0.6, -1.0};
        static_assert(std::is_same_v<decltype(m),return_t>);
        EXPECT_TRUE(isclose(m,expected));
    }
    {
        double x[4] = {3.0, 4.5, 7.0, 9.0};
        double y[4] = {2.5, 1.0, 2.5, 0.5};

        auto m = cvt::compute_slopes(x,y);
        using return_t = array<double,3>;
        auto expected = return_t{-1.0, 0.6, -1.0};
        static_assert(std::is_same_v<decltype(m),return_t>);
        EXPECT_TRUE(isclose(m,expected));
    }
    {
        auto x = vector<double>{3.0, 4.5, 7.0, 9.0};
        auto y = vector<double>{2.5, 1.0, 2.5, 0.5};

        auto m = cvt::compute_slopes(x,y);
        using return_t = vector<double>;
        auto expected = return_t{-1.0, 0.6, -1.0};
        static_assert(std::is_same_v<decltype(m),return_t>);
        EXPECT_TRUE(isclose(m,expected));
    }
    {
        auto x = array<double,4>{3.0, 4.5, 7.0, 9.0};
        auto y = vector<double>{2.5, 1.0, 2.5, 0.5};

        auto m = cvt::compute_slopes(x,y);
        using return_t = vector<double>;
        auto expected = return_t{-1.0, 0.6, -1.0};
        static_assert(std::is_same_v<decltype(m),return_t>);
        EXPECT_TRUE(isclose(m,expected));
    }
    {
        double x[4] = {3.0, 4.5, 7.0, 9.0};
        auto y = vector<double>{2.5, 1.0, 2.5, 0.5};

        auto m = cvt::compute_slopes(x,y);
        using return_t = vector<double>;
        auto expected = return_t{-1.0, 0.6, -1.0};
        static_assert(std::is_same_v<decltype(m),return_t>);
        EXPECT_TRUE(isclose(m,expected));
    }
}

TEST(curvefit, linear_spline)
{
    {
        auto x = array<double,4>{3.0, 4.5, 7.0, 9.0};
        auto y = array<double,4>{2.5, 1.0, 2.5, 0.5};

        auto f = cvt::linear_spline(x,y);
        auto [fx, in_range] = f(5.0);
        EXPECT_TRUE(in_range);
        EXPECT_TRUE(isclose(fx,1.3));
        static_assert(std::is_invocable_v<decltype(f),double>);
    }
    {
        auto x = vector<double>{3.0, 4.5, 7.0, 9.0};
        auto y = vector<double>{2.5, 1.0, 2.5, 0.5};

        auto f = cvt::linear_spline(x,y);
        auto [fx, in_range] = f(5.0);
        EXPECT_TRUE(in_range);
        EXPECT_TRUE(isclose(fx,1.3));
        static_assert(std::is_invocable_v<decltype(f),double>);
    }
    {
        double x[4] = {3.0, 4.5, 7.0, 9.0};
        double y[4] = {2.5, 1.0, 2.5, 0.5};

        auto f = cvt::linear_spline(x,y);
        auto [fx, in_range] = f(5.0);
        EXPECT_TRUE(in_range);
        EXPECT_TRUE(isclose(fx,1.3));
        static_assert(std::is_invocable_v<decltype(f),double>);
    }
    {
        constexpr auto x = array<double,4>{3.0, 4.5, 7.0, 9.0};
        constexpr auto y = array<double,4>{2.5, 1.0, 2.5, 0.5};

        constexpr auto f = cvt::linear_spline(x,y);
        constexpr auto result = f(5.0);
        constexpr auto fx = std::get<0>(result);
        constexpr auto in_range = std::get<1>(result);
        static_assert(in_range);
        static_assert(isclose(fx,1.3));
        static_assert(std::is_invocable_v<decltype(f),double>);
    }
}

TEST(curvefit, make_tridiagonal)
{
    using cvt::detail::make_tridiagonal;
    {
        auto x = array<double,4>{3.0, 4.5, 7.0, 9.0};
        auto y = array<double,4>{2.5, 1.0, 2.5, 0.5};

        using return_t = array<double,3>;

        auto [e,f,g,r] = make_tridiagonal(x,y);
        static_assert(std::is_same_v<decltype(e),return_t>);
    }
    using cvt::detail::make_tridiagonal;
    {
        constexpr auto x = array<double,4>{3.0, 4.5, 7.0, 9.0};
        constexpr auto y = array<double,4>{2.5, 1.0, 2.5, 0.5};

        using return_t = const array<double,3>;

        constexpr auto t = make_tridiagonal(x,y);
        constexpr auto e = std::get<0>(t);
        constexpr auto f = std::get<1>(t);
        constexpr auto g = std::get<2>(t);
        constexpr auto r = std::get<3>(t);
        static_assert(std::is_same_v<decltype(e),return_t>);
    }
}

TEST(curvefit, cubic_spline)
{
    using std::size;
    {
        auto x = array<double,4>{3.0, 4.5, 7.0, 9.0};
        auto y = array<double,4>{2.5, 1.0, 2.5, 0.5};

        auto f = cvt::cubic_spline(x,y);
        for (size_t i=0; i<size(x); i++) {
            auto t = x[i];
            auto r = y[i];
            auto [fx, in_range] = f(t);
            EXPECT_TRUE(in_range);
            EXPECT_TRUE(isclose(fx,r));
        }
        /* temporary test case to check if f is continuous */
        /* TODO: actually calculate the value */
        {
            auto [fx1,in_range1] = f(4.5+1e-7);
            auto [fx2,in_range2] = f(4.5-1e-7);
            EXPECT_TRUE(isclose(fx1,fx2,1e-5));
        }
        {
            auto [fx1,in_range1] = f(7.0+1e-7);
            auto [fx2,in_range2] = f(7.0-1e-7);
            EXPECT_TRUE(isclose(fx1,fx2,1e-5));
        }
        static_assert(std::is_invocable_v<decltype(f),double>);
    }
    {
        auto x = vector<double>{3.0, 4.5, 7.0, 9.0};
        auto y = vector<double>{2.5, 1.0, 2.5, 0.5};

        auto f = cvt::cubic_spline(x,y);
        for (size_t i=0; i<size(x); i++) {
            auto t = x[i];
            auto r = y[i];
            auto [fx, in_range] = f(t);
            EXPECT_TRUE(in_range);
            EXPECT_TRUE(isclose(fx,r));
        }
        /* temporary test case to check if f is continuous */
        /* TODO: actually calculate the value */
        {
            auto [fx1,in_range1] = f(4.5+1e-7);
            auto [fx2,in_range2] = f(4.5-1e-7);
            EXPECT_TRUE(isclose(fx1,fx2,1e-3));
        }
        {
            auto [fx1,in_range1] = f(7.0+1e-7);
            auto [fx2,in_range2] = f(7.0-1e-7);
            EXPECT_TRUE(isclose(fx1,fx2,1e-3));
        }
        static_assert(std::is_invocable_v<decltype(f),double>);
    }
    {
        double x[4] = {3.0, 4.5, 7.0, 9.0};
        double y[4] = {2.5, 1.0, 2.5, 0.5};

        auto f = cvt::cubic_spline(x,y);
        for (size_t i=0; i<size(x); i++) {
            auto t = x[i];
            auto r = y[i];
            auto [fx, in_range] = f(t);
            EXPECT_TRUE(in_range);
            EXPECT_TRUE(isclose(fx,r));
        }
        /* temporary test case to check if f is continuous */
        /* TODO: actually calculate the value */
        {
            auto [fx1,in_range1] = f(4.5+1e-7);
            auto [fx2,in_range2] = f(4.5-1e-7);
            EXPECT_TRUE(isclose(fx1,fx2,1e-3));
        }
        {
            auto [fx1,in_range1] = f(7.0+1e-7);
            auto [fx2,in_range2] = f(7.0-1e-7);
            EXPECT_TRUE(isclose(fx1,fx2,1e-3));
        }
        static_assert(std::is_invocable_v<decltype(f),double>);
    }
    /* test compile time version */
    {
        constexpr auto x = array<double,4>{3.0, 4.5, 7.0, 9.0};
        constexpr auto y = array<double,4>{2.5, 1.0, 2.5, 0.5};

        constexpr auto f = cvt::cubic_spline(x,y);
        /* temporary test case to check if f is continuous */
        /* TODO: actually calculate the value */
        {
            constexpr auto f1 = f(3.0+1e-7);
            constexpr auto f2 = f(3.0);
            constexpr auto fx1 = std::get<0>(f1);
            constexpr auto fx2 = std::get<0>(f2);
            static_assert(isclose(fx1,fx2,1e-6));
        }
        {
            constexpr auto f1 = f(4.5+1e-7);
            constexpr auto f2 = f(4.5-1e-7);
            constexpr auto fx1 = std::get<0>(f1);
            constexpr auto fx2 = std::get<0>(f2);
            static_assert(isclose(fx1,fx2,1e-6));
        }
        {
            constexpr auto f1 = f(7.0+1e-7);
            constexpr auto f2 = f(7.0-1e-7);
            constexpr auto fx1 = std::get<0>(f1);
            constexpr auto fx2 = std::get<0>(f2);
            static_assert(isclose(fx1,fx2,1e-6));
        }
        {
            constexpr auto f1 = f(9.0);
            constexpr auto f2 = f(9.0-1e-7);
            constexpr auto fx1 = std::get<0>(f1);
            constexpr auto fx2 = std::get<0>(f2);
            static_assert(isclose(fx1,fx2,1e-6));
        }
        static_assert(std::is_invocable_v<decltype(f),double>);
    }
}