#include <gtest/gtest.h>
#include "roots.hpp"

TEST(roots,newton_raphson)
{
    auto f = [](double x) {
        return std::exp(-x)-x;
    };
    auto df = [](double x) {
        return -std::exp(-x)-1;
    };
    double x0{0.0}, es{5e-3}, xr, ea;
    size_t imax{1000}, iter{0};

    numeric::roots::newton_raphson(f,df,x0,xr,es,imax,iter,ea);
    EXPECT_NEAR(f(xr),0.0,es)
        << "xr = " << xr << "\n"
        << "iter = " << iter << "\n"
        << "ea = " << ea;
}

TEST(roots,secant)
{
    auto f = [](double x) {
        return std::exp(-x)-x;
    };
    double x0{1.0}, x_1{0.0}, es{5e-3}, xr, ea;
    size_t imax{1000}, iter{0};

    numeric::roots::secant(f,x0,x_1,xr,es,imax,iter,ea);
    EXPECT_NEAR(f(xr),0.0,es)
        << "xr = " << xr << "\n"
        << "iter = " << iter << "\n"
        << "ea = " << ea;
}

TEST(roots,modified_secant)
{
    auto f = [](double x) {
        return std::exp(-x)-x;
    };
    double x0{1.0}, delta{1e-2}, es{5e-3}, xr, ea;
    size_t imax{1000}, iter{0};

    numeric::roots::modified_secant(f,x0,delta,xr,es,imax,iter,ea);
    EXPECT_NEAR(f(xr),0.0,es)
        << "xr = " << xr << "\n"
        << "iter = " << iter << "\n"
        << "ea = " << ea;
}