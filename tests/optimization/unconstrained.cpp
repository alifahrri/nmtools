#include <gtest/gtest.h>
#include <cmath>
#include "optimization.hpp"

namespace opt = numeric::optimization;

TEST(optimization, gold_section_maximum)
{
    auto f = [](double x){
        return 2*sin(x)-(std::pow(x,2)/10);
    };
    double xl{0}, xu{4}, xopt;
    double es{1e-6}, ea, fxopt;
    size_t imax{1000}, iter;
    opt::gold_section(f,xl,xu,xopt,imax,iter,es,ea,fxopt);
    /* see chapra numerical method */
    double x_true{1.4276}, fx_true{1.7757};
    EXPECT_NEAR(xopt,x_true,1e-4);
    EXPECT_NEAR(fxopt,fx_true,1e-4);
}

TEST(optimization, gold_section_generic_max)
{
    auto f = [](double x){
        return 2*sin(x)-(std::pow(x,2)/10);
    };
    double xl{0}, xu{4}, xopt;
    double es{1e-6}, ea, fxopt;
    size_t imax{1000}, iter;
    opt::detail::gold_section(f,xl,xu,xopt,imax,iter,es,ea,fxopt);
    /* see chapra numerical method */
    double x_true{1.4276}, fx_true{1.7757};
    EXPECT_NEAR(xopt,x_true,1e-4);
    EXPECT_NEAR(fxopt,fx_true,1e-4);
}

TEST(optimization, parabolic_interpolation_max_0)
{
    auto f = [](double x){
        return 2*sin(x)-(std::pow(x,2)/10);
    };
    std::stringstream ss;
    auto logger = [&](std::map<std::string,double> map) {
        ss << "LOG : " << map["iter"] << "\n";
        ss << "(x0,f0) " << "(" << map["x0"] << "," << map["f0"] << "); ";
        ss << "(x1,f1) " << "(" << map["x1"] << "," << map["f1"] << "); ";
        ss << "(x2,f2) " << "(" << map["x2"] << "," << map["f2"] << "); ";
        ss << "(x3,f3) " << "(" << map["x3"] << "," << map["f3"] << "); ";
        ss << "(xo,fx) " << "(" << map["xopt"] << "," << map["fx"] << "); ";
        ss << "ea : " << "(" << map["ea"] << ")";
        ss << std::endl;
    };
    double x0{0}, x1{1}, x2{4}, xopt;
    double es{1e-4}, ea, fxopt;
    size_t imax{1000}, iter;
    opt::parabolic_interpolation(f,x0,x1,x2,xopt,imax,iter,es,ea,fxopt,std::greater<double>{},&logger);
    /* see chapra numerical method */
    double x_true{1.4276}, fx_true{1.7757};
    EXPECT_NEAR(xopt,x_true,1e-4) << ss.str();
    EXPECT_NEAR(fxopt,fx_true,1e-4) << ss.str();
}

TEST(optimization, parabolic_interpolation_max_1)
{
    auto f = [](double x){
        return sin(x);
    };
    std::stringstream ss;
    auto logger = [&](std::map<std::string,double> map) {
        ss << "LOG : " << map["iter"] << "\n";
        ss << "(x0,f0) " << "(" << map["x0"] << "," << map["f0"] << "); ";
        ss << "(x1,f1) " << "(" << map["x1"] << "," << map["f1"] << "); ";
        ss << "(x2,f2) " << "(" << map["x2"] << "," << map["f2"] << "); ";
        ss << "(x3,f3) " << "(" << map["x3"] << "," << map["f3"] << "); ";
        ss << "(xo,fx) " << "(" << map["xopt"] << "," << map["fx"] << "); ";
        ss << "ea : " << "(" << map["ea"] << ")";
        ss << std::endl;
    };
    double x0{0}, x1{1}, x2{2}, xopt;
    double es{1e-4}, ea, fxopt;
    size_t imax{1000}, iter;
    opt::parabolic_interpolation(f,x0,x1,x2,xopt,imax,iter,es,ea,fxopt,std::greater<double>{},&logger);
    double x_true{M_PI_2}, fx_true{1.};
    EXPECT_NEAR(xopt,x_true,1e-4) << ss.str();
    EXPECT_NEAR(fxopt,fx_true,1e-4) << ss.str();
}

TEST(optimization, parabolic_interpolation_max_2)
{
    auto f = [](double x){
        return cos(x);
    };
    std::stringstream ss;
    auto logger = [&](std::map<std::string,double> map) {
        ss << "LOG : " << map["iter"] << "\n";
        ss << "(x0,f0) " << "(" << map["x0"] << "," << map["f0"] << "); ";
        ss << "(x1,f1) " << "(" << map["x1"] << "," << map["f1"] << "); ";
        ss << "(x2,f2) " << "(" << map["x2"] << "," << map["f2"] << "); ";
        ss << "(x3,f3) " << "(" << map["x3"] << "," << map["f3"] << "); ";
        ss << "(xo,fx) " << "(" << map["xopt"] << "," << map["fx"] << "); ";
        ss << "ea : " << "(" << map["ea"] << ")";
        ss << std::endl;
    };
    double x0{0}, x1{1}, x2{2}, xopt;
    double es{1e-4}, ea, fxopt;
    size_t imax{1000}, iter;
    opt::parabolic_interpolation(f,x0,x1,x2,xopt,imax,iter,es,ea,fxopt,std::greater<double>{},&logger);
    double x_true{0.}, fx_true{1.};
    EXPECT_NEAR(xopt,x_true,1e-4) << ss.str();
    EXPECT_NEAR(fxopt,fx_true,1e-4) << ss.str();
}

TEST(optimization, parabolic_interpolation_min_1)
{
    auto f = [](double x){
        return cos(x);
    };
    std::stringstream ss;
    auto logger = [&](std::map<std::string,double> map) {
        ss << "LOG : " << map["iter"] << "\n";
        ss << "(x0,f0) " << "(" << map["x0"] << "," << map["f0"] << "); ";
        ss << "(x1,f1) " << "(" << map["x1"] << "," << map["f1"] << "); ";
        ss << "(x2,f2) " << "(" << map["x2"] << "," << map["f2"] << "); ";
        ss << "(x3,f3) " << "(" << map["x3"] << "," << map["f3"] << "); ";
        ss << "(xo,fx) " << "(" << map["xopt"] << "," << map["fx"] << "); ";
        ss << "ea : " << "(" << map["ea"] << ")";
        ss << std::endl;
    };
    double x0{4}, x1{0}, x2{-2}, xopt;
    double es{1e-4}, ea, fxopt;
    size_t imax{1000}, iter;
    opt::parabolic_interpolation(f,x0,x1,x2,xopt,imax,iter,es,ea,fxopt,std::less<double>{},&logger);
    double x_true{M_PI}, fx_true{-1.};
    EXPECT_NEAR(f(xopt),fx_true,1e-4) << ss.str();
    EXPECT_NEAR(fxopt,fx_true,1e-4) << ss.str();
}
/*
TEST(optimization, gold_section_minimum)
{

}
*/