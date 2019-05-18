#include <gtest/gtest.h>
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

/*
TEST(optimization, gold_section_minimum)
{

}
*/