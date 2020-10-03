#include "nmtools/differentiation.hpp"
#include <gtest/gtest.h>
#include <cmath>

namespace diff = nmtools::differentiation;

#define NEAR(x,y,eps) (std::fabs(x-y) < eps)

TEST(finite, first_order_centered_0)
{
    constexpr auto f = [](double x){
        return -0.1*std::pow(x,4) - 0.15*std::pow(x,3) - 0.5*std::pow(x,2) - 0.25*x + 1.2;
    };
    {
        auto d = diff::finite_difference(f,0.5,0.25);
        EXPECT_NEAR(d,-0.9125,1e-6);
    }
    {
        constexpr auto d = diff::finite_difference(f,0.5,0.25);
        static_assert(NEAR(d,-0.9125,1e-6));
    }
}

TEST(finite, first_order_forward_0)
{
    constexpr auto f = [](double x){
        return -0.1*std::pow(x,4) - 0.15*std::pow(x,3) - 0.5*std::pow(x,2) - 0.25*x + 1.2;
    };
    {
        auto d = diff::finite_difference<1,diff::Formulas::Forward>(f,0.5,0.25);
        EXPECT_NEAR(d,-0.859375,1e-6);
    }
    {
        constexpr auto d = diff::finite_difference<1,diff::Formulas::Forward>(f,0.5,0.25);
        static_assert(NEAR(d,-0.859375,1e-6));
    }
}

TEST(finite, first_order_backward_0)
{
    constexpr auto f = [](double x){
        return -0.1*std::pow(x,4) - 0.15*std::pow(x,3) - 0.5*std::pow(x,2) - 0.25*x + 1.2;
    };
    {
        auto d = diff::finite_difference<1,diff::Formulas::Backward>(f,0.5,0.25);
        EXPECT_NEAR(d,-0.878125,1e-6);
    }
    {
        constexpr auto d = diff::finite_difference<1,diff::Formulas::Backward>(f,0.5,0.25);
        static_assert(NEAR(d,-0.878125,1e-6));
    }
}