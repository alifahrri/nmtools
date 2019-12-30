#include <gtest/gtest.h>
#include "nmtools/ode.hpp"
#include <cmath>

TEST(euler, test_0) {
    auto dydx = [](double x, double y){
        return -2*std::pow(x,3) + 12*std::pow(x,2) - 20*x + 8.5;
    };
    double xi{0};
    double yi{1};
    double xf{4};
    double dx{0.5};
    double yf;
    nmtools::ode::euler(dydx,yi,xi,xf,dx,yf);
    EXPECT_NEAR(yf,7,1e-6);
}

TEST(midpoint, test_0) {
    auto dydx = [](double x, double y){
        return -2*std::pow(x,3) + 12*std::pow(x,2) - 20*x + 8.5;
    };
    double xi{0};
    double yi{1};
    double xf{4};
    double dx{0.5};
    double yf;
    nmtools::ode::midpoint(dydx,yi,xi,xf,dx,yf);
    EXPECT_NEAR(yf,3,1e-6);
}

TEST(heun, test_0) {
    auto dydx = [](double x, double y){
        return -2*std::pow(x,3) + 12*std::pow(x,2) - 20*x + 8.5;
    };
    double xi{0};
    double yi{1};
    double xf{4};
    double dx{0.5};
    double yf;
    nmtools::ode::heun(dydx,yi,xi,xf,dx,yf);
    EXPECT_NEAR(yf,3,1e-6);
}