#include <gtest/gtest.h>
#include "ode.hpp"
#include <cmath>

namespace ode = numeric::ode;

TEST(rk_helper,constants) {
    namespace detail = numeric::helper::detail;

    constexpr detail::Constants<double,100,50,25,25> constants;
    static_assert(constants.values[0]==0.5);
    static_assert(constants.values[1]==0.25);
    static_assert(constants.values[2]==0.25);
}

TEST(rk_helper,triangular_number) {
    namespace detail = numeric::helper::detail;
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

namespace nm = numeric;
namespace ode = nm::ode;
namespace hlp = nm::helper;

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

TEST(rk_helper,k) {
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