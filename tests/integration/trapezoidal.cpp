#include "integration.hpp"
#include <cmath>
#include <gtest/gtest.h>

namespace integration = numeric::integration;

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