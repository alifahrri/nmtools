#include <gtest/gtest.h>
#include "nmtools/ode.hpp"
#include "nmtools/utility.hpp"
#include <cmath>

TEST(euler, test_0) {
    constexpr auto dydx = [](double x, double y){
        return -2*std::pow(x,3) + 12*std::pow(x,2) - 20*x + 8.5;
    };
    constexpr double xi{0};
    constexpr double yi{1};
    constexpr double xf{4};
    constexpr double dx{0.5};
    {
        auto yf = nmtools::ode::euler(dydx,yi,xi,xf,dx);
        EXPECT_NEAR(yf,7,1e-6);
    }
    {
        constexpr auto yf = nmtools::ode::euler(dydx,yi,xi,xf,dx);
        static_assert(nmtools::near(yf,7,1e-6));
    }
}

TEST(midpoint, test_0) {
    constexpr auto dydx = [](double x, double y){
        return -2*std::pow(x,3) + 12*std::pow(x,2) - 20*x + 8.5;
    };
    constexpr double xi{0};
    constexpr double yi{1};
    constexpr double xf{4};
    constexpr double dx{0.5};
    {
        auto yf = nmtools::ode::midpoint(dydx,yi,xi,xf,dx);
        EXPECT_NEAR(yf,3,1e-6);
    }
    {
        constexpr auto yf = nmtools::ode::midpoint(dydx,yi,xi,xf,dx);
        static_assert(nmtools::near(yf,3,1e-6));
    }
}

TEST(heun, test_0) {
    constexpr auto dydx = [](double x, double y){
        return -2*std::pow(x,3) + 12*std::pow(x,2) - 20*x + 8.5;
    };
    constexpr double xi{0};
    constexpr double yi{1};
    constexpr double xf{4};
    constexpr double dx{0.5};
    {
        auto yf = nmtools::ode::heun(dydx,yi,xi,xf,dx);
        EXPECT_NEAR(yf,3,1e-6);
    }
    {
        constexpr auto yf = nmtools::ode::heun(dydx,yi,xi,xf,dx);
        static_assert(nmtools::near(yf,3,1e-6));
    }
}