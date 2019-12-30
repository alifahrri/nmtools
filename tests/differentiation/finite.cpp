#include "nmtools/differentiation.hpp"
#include <gtest/gtest.h>
#include <cmath>

namespace diff = nmtools::differentiation;

TEST(finite, first_order_centered_0)
{
    auto f = [](double x){
        return -0.1*std::pow(x,4) - 0.15*std::pow(x,3) - 0.5*std::pow(x,2) - 0.25*x + 1.2;
    };
    double d{0};
    diff::finite_difference<1>(f,0.5,0.25,d);
    EXPECT_NEAR(d,-0.9125,1e-6);
}

TEST(finite, first_order_forward_0)
{
    auto f = [](double x){
        return -0.1*std::pow(x,4) - 0.15*std::pow(x,3) - 0.5*std::pow(x,2) - 0.25*x + 1.2;
    };
    double d{0};
    diff::finite_difference<1,diff::Formulas::Forward>(f,0.5,0.25,d);
    EXPECT_NEAR(d,-0.859375,1e-6);
}

TEST(finite, first_order_backward_0)
{
    auto f = [](double x){
        return -0.1*std::pow(x,4) - 0.15*std::pow(x,3) - 0.5*std::pow(x,2) - 0.25*x + 1.2;
    };
    double d{0};
    diff::finite_difference<1,diff::Formulas::Backward>(f,0.5,0.25,d);
    EXPECT_NEAR(d,-0.878125,1e-6);
}