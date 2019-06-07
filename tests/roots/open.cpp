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

TEST(roots,fzero)
{
    auto f = [](double x) {
        return (x+3)*std::pow(x-1,2);
    };
    std::stringstream ss;
    size_t i=0;
    double fxr;
    auto logger = [&](std::map<std::string,double> map) {
        fxr = map["fb"];
        ss << "LOG : " << i++ << "\n";
        ss << "(a,fa) " << "(" << map["a"] << "," << map["fa"] << "); ";
        ss << "(b,fb) " << "(" << map["b"] << "," << map["fb"] << "); ";
        ss << "(c,fc) " << "(" << map["c"] << "," << map["fc"] << "); ";
        ss << "(s,fs) " << "(" << map["s"] << "," << map["fs"] << ")";
        // for(auto e : map) 
        //     ss << e.first << " : " << e.second << "; ";
        ss << std::endl;
    };
    double xl{-4.0}, xu{4.0/3.0}, xr;

    numeric::roots::fzero(f,xl,xu,xr,1e-6,std::numeric_limits<double>::epsilon(),&logger);
    EXPECT_NEAR(fxr,0.0,1e-6)
        << "xr = " << xr << "\n"
        << ss.str();
}

TEST(roots,fzero_no_logger)
{
    auto f = [](double x) {
        return (x+3)*std::pow(x-1,2);
    };
    double xl{-4.0}, xu{4.0/3.0}, xr;

    numeric::roots::fzero(f,xl,xu,xr,1e-6);
    EXPECT_NEAR(f(xr),0.0,1e-6)
        << "xr = " << xr;
}