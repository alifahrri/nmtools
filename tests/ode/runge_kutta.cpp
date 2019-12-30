#include <gtest/gtest.h>
#include "nmtools/ode.hpp"
#include <cmath>
#include <sstream>

namespace nm = nmtools;
namespace ode = nm::ode;
namespace hlp = nm::helper;

TEST(utility, is_2d_array) {
    std::array<double,1> array1d;
    std::array<std::array<double,1>,1> array2d;
    static_assert( nm::traits::is_2d_array<decltype(array2d)>::value );
    static_assert( !nm::traits::is_2d_array<decltype(array1d)>::value );
}

TEST(rk_helper,constants) {
    namespace detail = nmtools::helper::detail;

    constexpr detail::Constants<double,100,50,25,25> constants;
    static_assert(constants.values[0]==0.5);
    static_assert(constants.values[1]==0.25);
    static_assert(constants.values[2]==0.25);
}

TEST(rk_helper,triangular_number) {
    namespace detail = nmtools::helper::detail;
    static_assert(detail::triangular_number(1)==1);
    static_assert(detail::triangular_number(2)==3);
    static_assert(detail::triangular_number(3)==6);
    static_assert(detail::triangular_number(4)==10);
    static_assert(detail::triangular_number(5)==15);
    static_assert(detail::triangular_number(6)==21);
}

struct F {
    double operator()(double,double){ return 0; }
};

TEST(rk_helper,k_constants) {
    constexpr size_t N = 4;
    constexpr hlp::detail::Constants<double,100,50,25,25> p;
    constexpr hlp::detail::Constants<double,100,50,25,25,10,10,10> q;
    constexpr F f;
    constexpr ode::detail::K<N,F,double,decltype(p),decltype(q)> k(f,0,0,1,p,q);
}

TEST(rk_helper,butcher_tableau) {
    constexpr std::array<double,3> c = {
        1/3, 2/3, 1
    };
    std::vector<std::vector<double>> a = {
        {1/2},
        {0, 1/2},
        {0, 0, 1}
    };
    constexpr std::array<double,4> b = {
        1/6, 1/3, 1/3, 1/6
    };
    EXPECT_TRUE( ode::detail::butcher_tableau(a, b, c) );
}

TEST(rk_helper,k_0) {
    auto dy = [](double x, double y) {
        return tan(y) + 1;
    };
    std::array<double,1> c = { 2./3. };
    std::vector<std::vector<double>> a = { {2./3.} };
    std::vector<double> ks;
    double h{0.025};
    ks.emplace_back( ode::detail::k(0,dy,double{1.025},double{1},h,a,c,ks) );
    ks.emplace_back( ode::detail::k(1,dy,double{1.025},double{1},h,a,c,ks) );
    double zero{1e-6};
    EXPECT_TRUE( ks.size() == 2 );
    EXPECT_NEAR( ks[0], 2.557407725, zero );
    EXPECT_NEAR( ks[1], 2.7138981184, zero );
}

TEST(rk_helper,k_1) {
    auto dy = [](double x, double y) {
        return tan(y) + 1;
    };
    std::array<double,1> c = { 2./3. };
    std::array<double,1> a = { 2./3. };
    std::vector<double> ks;
    double h{0.025};
    ks.emplace_back( ode::detail::k(0,dy,double{1.025},double{1},h,a,c,ks) );
    ks.emplace_back( ode::detail::k(1,dy,double{1.025},double{1},h,a,c,ks) );
    double zero{1e-6};
    EXPECT_TRUE( ks.size() == 2 );
    EXPECT_NEAR( ks[0], 2.557407725, zero );
    EXPECT_NEAR( ks[1], 2.7138981184, zero );
}

TEST(rk_helper,k_2_a1d) {
    constexpr auto dy = [](double x, double y) {
        return 4*std::exp(0.8*x) - 0.5*y;
    };
    constexpr std::array<double,3> c = { 1./2., 1./2., 1. };
    constexpr std::array<double,6> a = { 1./2., 0., 1./2., 0., 0., 1. };
    constexpr double h{0.5};
    constexpr double x{0.0}, y{2.0};
    constexpr double zero{5e-5};
    std::vector<double> ks;
    ks.emplace_back( ode::detail::k(0,dy,x,y,h,a,c,ks) );
    ks.emplace_back( ode::detail::k(1,dy,x,y,h,a,c,ks) );
    ks.emplace_back( ode::detail::k(2,dy,x,y,h,a,c,ks) );
    ks.emplace_back( ode::detail::k(3,dy,x,y,h,a,c,ks) );
    std::stringstream ss; ss << ks[0] << "; " << ks[1] << "; " << ks[2] << "; " << ks[3];
    EXPECT_TRUE( ks.size() == 4 );
    EXPECT_NEAR( ks[0], 3.0, zero ) << ss.str(); 
    EXPECT_NEAR( ks[1], 3.510611, zero ) << ss.str();
    EXPECT_NEAR( ks[2], 3.446785, zero ) << ss.str();
    EXPECT_NEAR( ks[3], 4.105603, zero ) << ss.str(); 
}

TEST(rk_helper,k_2_a2dvector) {
    constexpr auto dy = [](double x, double y) {
        return 4*std::exp(0.8*x) - 0.5*y;
    };
    constexpr std::array<double,3> c = { 1./2., 1./2., 1. };
    std::vector<std::vector<double>> a = {
        { 1./2. },
        { 0., 1./2. },
        { 0., 0., 1. }
    };
    constexpr double h{0.5};
    constexpr double x{0.0}, y{2.0};
    constexpr double zero{5e-5};
    std::vector<double> ks;
    ks.emplace_back( ode::detail::k(0,dy,x,y,h,a,c,ks) );
    ks.emplace_back( ode::detail::k(1,dy,x,y,h,a,c,ks) );
    ks.emplace_back( ode::detail::k(2,dy,x,y,h,a,c,ks) );
    ks.emplace_back( ode::detail::k(3,dy,x,y,h,a,c,ks) );
    std::stringstream ss; ss << ks[0] << "; " << ks[1] << "; " << ks[2] << "; " << ks[3];
    EXPECT_TRUE( ks.size() == 4 );
    EXPECT_NEAR( ks[0], 3.0, zero ) << ss.str(); 
    EXPECT_NEAR( ks[1], 3.510611, zero ) << ss.str();
    EXPECT_NEAR( ks[2], 3.446785, zero ) << ss.str();
    EXPECT_NEAR( ks[3], 4.105603, zero ) << ss.str(); 
}

TEST(rk_helper,k_2_a2darray) {
    constexpr auto dy = [](double x, double y) {
        return 4*std::exp(0.8*x) - 0.5*y;
    };
    constexpr std::array<double,3> c = { 1./2., 1./2., 1. };
    constexpr std::array<std::array<double,3>,3> a = {
        std::array<double,3>{ 1./2., 0.,    0. },
        std::array<double,3>{ 0.,    1./2., 0. },
        std::array<double,3>{ 0.,    0.,    1. }
    };
    constexpr double h{0.5};
    constexpr double x{0.0}, y{2.0};
    constexpr double zero{5e-5};
    std::vector<double> ks;
    ks.emplace_back( ode::detail::k(0,dy,x,y,h,a,c,ks) );
    ks.emplace_back( ode::detail::k(1,dy,x,y,h,a,c,ks) );
    ks.emplace_back( ode::detail::k(2,dy,x,y,h,a,c,ks) );
    ks.emplace_back( ode::detail::k(3,dy,x,y,h,a,c,ks) );
    std::stringstream ss; ss << ks[0] << "; " << ks[1] << "; " << ks[2] << "; " << ks[3];
    EXPECT_TRUE( ks.size() == 4 );
    EXPECT_NEAR( ks[0], 3.0, zero ) << ss.str(); 
    EXPECT_NEAR( ks[1], 3.510611, zero ) << ss.str();
    EXPECT_NEAR( ks[2], 3.446785, zero ) << ss.str();
    EXPECT_NEAR( ks[3], 4.105603, zero ) << ss.str(); 
}

TEST(rk_helper,rk_driver_core_0) {
    auto dy = [](double x, double y) {
        return tan(y) + 1;
    };
    std::array<double,1> c = { 2./3. };
    std::vector<std::vector<double>> a = { {2./3.} };
    constexpr std::array<double,2> b = {
        1./4., 3./4.
    };
    double h{0.025};
    double x{1.025};
    double y{1};
    double zero{1e-6};
    auto yn = ode::detail::rk_driver(dy,x,y,h,a,b,c);
    EXPECT_NEAR(yn,1.066869388,zero);
}

TEST(rk_helper,rk_driver_core_1) {
    auto dy = [](double x, double y) {
        return tan(y) + 1;
    };
    std::array<double,1> c = { 2./3. };
    std::array<double,1> a = { {2./3.} };
    constexpr std::array<double,2> b = {
        1./4., 3./4.
    };
    double h{0.025};
    double x{1.025};
    double y{1};
    double zero{1e-6};
    auto yn = ode::detail::rk_driver(dy,x,y,h,a,b,c);
    EXPECT_NEAR(yn,1.066869388,zero);
}

TEST(rk_helper,rk_driver_0) {
    auto dy = [](double x, double y) {
        return tan(y) + 1;
    };
    std::array<double,1> c = { 2./3. };
    std::vector<std::vector<double>> a = { {2./3.} };
    constexpr std::array<double,2> b = {
        1./4., 3./4.
    };
    double h{0.025};
    double xi{1.0}, xf{1.1}, y{1};
    double zero{1e-6};
    auto yn = ode::detail::rk_driver(dy,xi,xf,y,h,a,b,c);
    EXPECT_NEAR(yn,1.335079087,zero);
}

TEST(rk_helper,rk_driver_1) {
    constexpr auto dy = [](double x, double y) {
        return tan(y) + 1;
    };
    constexpr std::array<double,1> c = { 2./3. };
    constexpr std::array<double,1> a = { 2./3. };
    constexpr std::array<double,2> b = {
        1./4., 3./4.
    };
    constexpr double h{0.025};
    constexpr double xi{1.0}, xf{1.1}, y{1};
    constexpr double zero{1e-6};
    /* TODO : support compile-time computation */
    auto yn = ode::detail::rk_driver(dy,xi,xf,y,h,a,b,c);
    EXPECT_NEAR(yn,1.335079087,zero);
}

TEST(runge_kutta,ralston) {
    constexpr auto dy = [](double x, double y) {
        return tan(y) + 1;
    };
    constexpr double h{0.025};
    constexpr double xi{1.0}, xf{1.1}, y{1};
    constexpr double zero{1e-6};
    /* TODO : support compile-time computation */
    auto yn = ode::ralston(dy,xi,xf,y,h);
    EXPECT_NEAR(yn,1.335079087,zero);
}

TEST(runge_kutta,midpoint) {
    constexpr auto dy = [](double x, double y) {
        return tan(y) + 1;
    };
    constexpr double h{0.025};
    constexpr double xi{1.0}, xf{1.1}, y{1};
    constexpr double zero{1e-6};
    /* TODO : support compile-time computation */
    auto yn = ode::midpoint(dy,xi,xf,y,h);
    EXPECT_NEAR(yn,1.333900694,zero);
}

TEST(runge_kutta,rk4_0) {
    constexpr auto dy = [](double x, double y) {
        return 4*std::exp(0.8*x) - 0.5*y;
    };
    std::stringstream ss;
    auto logger = [&](std::map<std::string,double> map) {
        ss << "LOG : ";
        for (const auto &m : map)
            ss << m.first << " : " << m.second << "; ";
        ss << std::endl;
    };
    constexpr double h{0.5};
    constexpr double xi{0.0}, xf{0.5}, y{2.0};
    constexpr double zero{5e-6};
    /* TODO : support compile-time computation */
    auto yn = ode::rk4(dy,xi,xf,y,h,&logger);
    EXPECT_NEAR(yn,3.751699,zero) << ss.str();
}

TEST(runge_kutta,rk4_1) {
    constexpr auto dy = [](double x, double y) {
        return -2*std::pow(x,3) + 12*std::pow(x,2) - 20*x + 8.5;
    };
    constexpr double h{0.5};
    constexpr double xi{0.0}, xf{0.5}, y{1.0};
    constexpr double zero{5e-5};
    /* TODO : support compile-time computation */
    auto yn = ode::rk4(dy,xi,xf,y,h);
    EXPECT_NEAR(yn,3.21875,zero);
}