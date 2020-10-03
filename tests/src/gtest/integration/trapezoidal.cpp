#include "nmtools/integration.hpp"
#include <cmath>
#include <gtest/gtest.h>

namespace integration = nmtools::integration;

/* for true value, see chapra numerical method, chapter newton-cotes integration */

TEST(trapezoidal, test0)
{
    auto f = [](double x){
        return 0.2 + 25*x - 200*std::pow(x,2) + 675*std::pow(x,3) - 900*std::pow(x,4) + 400*std::pow(x,5);
    };
    double I;
    double a{0}, b{0.8};
    integration::trapezoid(f,a,b,10,I);
    EXPECT_NEAR(I,1.6150,1e-4);
}

TEST(trapezoidal, test1)
{
    auto f = [](double x){
        return 0.2 + 25*x - 200*std::pow(x,2) + 675*std::pow(x,3) - 900*std::pow(x,4) + 400*std::pow(x,5);
    };
    double I;
    double a{0}, b{0.8};
    integration::trapezoid(f,a,b,9,I);
    EXPECT_NEAR(I,1.6091,1e-4);
}

TEST(trapezoidal, test2)
{
    auto f = [](double x){
        return 0.2 + 25*x - 200*std::pow(x,2) + 675*std::pow(x,3) - 900*std::pow(x,4) + 400*std::pow(x,5);
    };
    double I;
    double a{0}, b{0.8};
    integration::trapezoid(f,a,b,8,I);
    EXPECT_NEAR(I,1.6008,1e-4);
}

TEST(trapezoidal, test3)
{
    auto f = [](double x){
        return 0.2 + 25*x - 200*std::pow(x,2) + 675*std::pow(x,3) - 900*std::pow(x,4) + 400*std::pow(x,5);
    };
    double I;
    double a{0}, b{0.8};
    integration::trapezoid(f,a,b,7,I);
    EXPECT_NEAR(I,1.5887,1e-4);
}

TEST(trapezoidal, test4)
{
    auto f = [](double x){
        return 0.2 + 25*x - 200*std::pow(x,2) + 675*std::pow(x,3) - 900*std::pow(x,4) + 400*std::pow(x,5);
    };
    double I;
    double a{0}, b{0.8};
    integration::trapezoid(f,a,b,6,I);
    EXPECT_NEAR(I,1.5703,1e-4);
}

TEST(trapezoidal, test5)
{
    auto f = [](double x){
        return 0.2 + 25*x - 200*std::pow(x,2) + 675*std::pow(x,3) - 900*std::pow(x,4) + 400*std::pow(x,5);
    };
    double I;
    double a{0}, b{0.8};
    integration::trapezoid(f,a,b,5,I);
    EXPECT_NEAR(I,1.5399,1e-4);
}

TEST(trapezoidal, test6)
{
    auto f = [](double x){
        return 0.2 + 25*x - 200*std::pow(x,2) + 675*std::pow(x,3) - 900*std::pow(x,4) + 400*std::pow(x,5);
    };
    double I;
    double a{0}, b{0.8};
    integration::trapezoid(f,a,b,4,I);
    EXPECT_NEAR(I,1.4848,1e-4);
}

TEST(trapezoidal, test7)
{
    auto f = [](double x){
        return 0.2 + 25*x - 200*std::pow(x,2) + 675*std::pow(x,3) - 900*std::pow(x,4) + 400*std::pow(x,5);
    };
    double I;
    double a{0}, b{0.8};
    integration::trapezoid(f,a,b,3,I);
    EXPECT_NEAR(I,1.3695,1e-4);
}

TEST(trapezoidal, test8)
{
    auto f = [](double x){
        return 0.2 + 25*x - 200*std::pow(x,2) + 675*std::pow(x,3) - 900*std::pow(x,4) + 400*std::pow(x,5);
    };
    double I;
    double a{0}, b{0.8};
    integration::trapezoid(f,a,b,2,I);
    EXPECT_NEAR(I,1.0688,1e-4);
}

TEST(templated_trapezoidal, test0)
{
    auto f = [](double x){
        return 0.2 + 25*x - 200*std::pow(x,2) + 675*std::pow(x,3) - 900*std::pow(x,4) + 400*std::pow(x,5);
    };
    double I;
    double a{0}, b{0.8};
    integration::trapezoid<10>(f,a,b,I);
    EXPECT_NEAR(I,1.6150,1e-4);
}

TEST(templated_trapezoidal, test1)
{
    auto f = [](double x){
        return 0.2 + 25*x - 200*std::pow(x,2) + 675*std::pow(x,3) - 900*std::pow(x,4) + 400*std::pow(x,5);
    };
    double I;
    double a{0}, b{0.8};
    integration::trapezoid<9>(f,a,b,I);
    EXPECT_NEAR(I,1.6091,1e-4);
}

TEST(templated_trapezoidal, test2)
{
    auto f = [](double x){
        return 0.2 + 25*x - 200*std::pow(x,2) + 675*std::pow(x,3) - 900*std::pow(x,4) + 400*std::pow(x,5);
    };
    double I;
    double a{0}, b{0.8};
    integration::trapezoid<8>(f,a,b,I);
    EXPECT_NEAR(I,1.6008,1e-4);
}

TEST(templated_trapezoidal, test3)
{
    auto f = [](double x){
        return 0.2 + 25*x - 200*std::pow(x,2) + 675*std::pow(x,3) - 900*std::pow(x,4) + 400*std::pow(x,5);
    };
    double I;
    double a{0}, b{0.8};
    integration::trapezoid<7>(f,a,b,I);
    EXPECT_NEAR(I,1.5887,1e-4);
}

TEST(templated_trapezoidal, test4)
{
    auto f = [](double x){
        return 0.2 + 25*x - 200*std::pow(x,2) + 675*std::pow(x,3) - 900*std::pow(x,4) + 400*std::pow(x,5);
    };
    double I;
    double a{0}, b{0.8};
    integration::trapezoid<6>(f,a,b,I);
    EXPECT_NEAR(I,1.5703,1e-4);
}

TEST(templated_trapezoidal, test5)
{
    auto f = [](double x){
        return 0.2 + 25*x - 200*std::pow(x,2) + 675*std::pow(x,3) - 900*std::pow(x,4) + 400*std::pow(x,5);
    };
    double I;
    double a{0}, b{0.8};
    integration::trapezoid<5>(f,a,b,I);
    EXPECT_NEAR(I,1.5399,1e-4);
}

TEST(templated_trapezoidal, test6)
{
    auto f = [](double x){
        return 0.2 + 25*x - 200*std::pow(x,2) + 675*std::pow(x,3) - 900*std::pow(x,4) + 400*std::pow(x,5);
    };
    double I;
    double a{0}, b{0.8};
    integration::trapezoid<4>(f,a,b,I);
    EXPECT_NEAR(I,1.4848,1e-4);
}

TEST(templated_trapezoidal, test7)
{
    auto f = [](double x){
        return 0.2 + 25*x - 200*std::pow(x,2) + 675*std::pow(x,3) - 900*std::pow(x,4) + 400*std::pow(x,5);
    };
    double I;
    double a{0}, b{0.8};
    integration::trapezoid<3>(f,a,b,I);
    EXPECT_NEAR(I,1.3695,1e-4);
}

TEST(templated_trapezoidal, test8)
{
    auto f = [](double x){
        return 0.2 + 25*x - 200*std::pow(x,2) + 675*std::pow(x,3) - 900*std::pow(x,4) + 400*std::pow(x,5);
    };
    double I;
    double a{0}, b{0.8};
    integration::trapezoid<2>(f,a,b,I);
    EXPECT_NEAR(I,1.0688,1e-4);
}

TEST(trapezoidal, zero_test) {
    double w{M_PI/2};
    double T{2*M_PI/w};
    auto f = [=](double x) {
        double t = x - T/2;
        if ( (t>(-3*T/4)) && (t<-T/4) ) return -1.;
        else if ( (t>(-T/4)) && (t<(T/4)) ) return 1.;
        else if ( (t>(T/4)) && (t<(3*T/4)) ) return -1.;
        else return 1.;
    };
    double a{10};
    double zero = 1e-4;
    integration::trapezoid<100000>(f,double{0},T,a);
    EXPECT_NEAR(a,0,zero);
}

TEST(compile_time_trapezoidal, test0)
{
    constexpr auto f = [](double x){
        return 0.2 + 25*x - 200*std::pow(x,2) + 675*std::pow(x,3) - 900*std::pow(x,4) + 400*std::pow(x,5);
    };
    constexpr double a{0}, b{0.8};
    constexpr double zero{1e-4};
    constexpr double I = integration::trapezoid(f,a,b,10);
    constexpr double e = std::fabs(I-1.6150);
    static_assert(e <= zero);
    ASSERT_TRUE(e<=zero);
}

TEST(compile_time_trapezoidal, test1)
{
    constexpr auto f = [](double x){
        return 0.2 + 25*x - 200*std::pow(x,2) + 675*std::pow(x,3) - 900*std::pow(x,4) + 400*std::pow(x,5);
    };
    constexpr double a{0}, b{0.8};
    constexpr double zero{1e-4};
    constexpr double I = integration::trapezoid(f,a,b,9);
    constexpr double e = std::fabs(I-1.6091);
    static_assert(e <= zero);
    ASSERT_TRUE(e<=zero);
}

TEST(compile_time_trapezoidal, test2)
{
    constexpr auto f = [](double x){
        return 0.2 + 25*x - 200*std::pow(x,2) + 675*std::pow(x,3) - 900*std::pow(x,4) + 400*std::pow(x,5);
    };
    constexpr double a{0}, b{0.8};
    constexpr double zero{1e-4};
    constexpr double I = integration::trapezoid(f,a,b,8);
    constexpr double e = std::fabs(I-1.6008);
    static_assert( e<=zero );
    ASSERT_TRUE( e<=zero );
}

TEST(compile_time_trapezoidal, test3)
{
    constexpr auto f = [](double x){
        return 0.2 + 25*x - 200*std::pow(x,2) + 675*std::pow(x,3) - 900*std::pow(x,4) + 400*std::pow(x,5);
    };
    constexpr double a{0}, b{0.8};
    constexpr double zero{1e-4};
    constexpr double I = integration::trapezoid(f,a,b,7);
    constexpr double e = std::fabs(I-1.5887);
    static_assert( e<=zero );
    ASSERT_TRUE( e<=zero );
}

TEST(compile_time_trapezoidal, test4)
{
    constexpr auto f = [](double x){
        return 0.2 + 25*x - 200*std::pow(x,2) + 675*std::pow(x,3) - 900*std::pow(x,4) + 400*std::pow(x,5);
    };
    constexpr double a{0}, b{0.8};
    constexpr double zero{1e-4};
    constexpr double I = integration::trapezoid(f,a,b,6);
    constexpr double e = std::fabs(I-1.5703);
    static_assert( e<=zero );
    ASSERT_TRUE( e<=zero );
}

TEST(compile_time_trapezoidal, test5)
{
    constexpr auto f = [](double x){
        return 0.2 + 25*x - 200*std::pow(x,2) + 675*std::pow(x,3) - 900*std::pow(x,4) + 400*std::pow(x,5);
    };
    constexpr double a{0}, b{0.8};
    constexpr double zero{1e-4};
    constexpr double I = integration::trapezoid(f,a,b,5);
    constexpr double e = std::fabs(I-1.5399);
    static_assert( e<=zero );
    ASSERT_TRUE( e<=zero );
}

TEST(compile_time_trapezoidal, test6)
{
    constexpr auto f = [](double x){
        return 0.2 + 25*x - 200*std::pow(x,2) + 675*std::pow(x,3) - 900*std::pow(x,4) + 400*std::pow(x,5);
    };
    constexpr double a{0}, b{0.8};
    constexpr double zero{1e-4};
    constexpr double I = integration::trapezoid(f,a,b,4);
    constexpr double e = std::fabs(I-1.4848);
    static_assert( e<=zero );
    ASSERT_TRUE( e<=zero );
}