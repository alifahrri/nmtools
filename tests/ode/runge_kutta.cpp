#include <gtest/gtest.h>
#include "ode.hpp"

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

TEST(rk_helper,k_constants) {
    namespace nm = numeric;
    namespace ode = nm::ode;
    namespace helper = nm::helper;
    constexpr size_t N = 4;
    constexpr helper::detail::Constants<double,100,50,25,25> p;
    constexpr helper::detail::Constants<double,100,50,25,25,10,10,10> q;
    constexpr F f;
    constexpr ode::detail::K<N,F,double,decltype(p),decltype(q)> k(f,0,0,1,p,q);
}