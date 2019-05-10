#include <gtest/gtest.h>
#include "roots/bisection.hpp"

TEST(bisection,bisection)
{
    auto f = [](double x) {
        return x*2 + 3;
    };

    double xu{10.0}, xl{-10.0}, es{5e-3}, xr{xu}, ea;
    size_t imax{1000}, iter{0};

    numeric::roots::bisection(f, xu, xl, es, xr, imax, iter, ea);

    EXPECT_NEAR(f(xr),0.0,es)
        << "xr = " << xr << "\n"
        << "iter = " << iter << "\n"
        << "ea = " << ea;
}