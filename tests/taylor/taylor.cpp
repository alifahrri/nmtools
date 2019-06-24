#include <gtest/gtest.h>
#include "taylor.hpp"
#include <cmath>

namespace cos_fn {
    constexpr double f0(double a) {
        /* evaluate at pi/4 */
        return cos(M_PI/4);
    }
    constexpr double f1(double a) {
        /* evaluate at pi/4 */
        return -sin(M_PI/4);
    }
    constexpr double f2(double a) {
        /* evaluate at pi/4 */
        return -cos(M_PI/4);
    }
    constexpr double f3(double a) {
        /* evaluate at pi/4 */
        return sin(M_PI/4);
    }
    constexpr double f4(double a) {
        /* evaluate at pi/4 */
        return cos(M_PI/4);
    }
}

constexpr double c0 = cos(M_PI/4);
constexpr double c1 = c0-(sin(M_PI/4)*(M_PI/12));
constexpr double c2 = c1-(cos(M_PI/4)/2*std::pow(M_PI/12,2));
constexpr double c3 = c2+(sin(M_PI/4)/6*std::pow(M_PI/12,3));
constexpr double c4 = c3+(cos(M_PI/4)/24*std::pow(M_PI/12,4));
/* define min difference */
constexpr double zero = 1e-15;

using namespace numeric::taylor;

TEST(taylor, constexpr_taylor_series) 
{
    /* compute taylor series */
    namespace fn = cos_fn;
    constexpr double t0 = taylor_series(M_PI/3,M_PI/4,fn::f0);
    constexpr double t1 = taylor_series(M_PI/3,M_PI/4,fn::f0,fn::f1);
    constexpr double t2 = taylor_series(M_PI/3,M_PI/4,fn::f0,fn::f1,fn::f2);
    constexpr double t3 = taylor_series(M_PI/3,M_PI/4,fn::f0,fn::f1,fn::f2,fn::f3);
    constexpr double t4 = taylor_series(M_PI/3,M_PI/4,fn::f0,fn::f1,fn::f2,fn::f3,fn::f4);

    /* assert at compile time */
    static_assert(std::fabs(t0-c0)<zero);
    static_assert(std::fabs(t1-c1)<zero);
    static_assert(std::fabs(t2-c2)<zero);
    static_assert(std::fabs(t3-c3)<zero);
    static_assert(std::fabs(t4-c4)<zero);
}

TEST(taylor, taylor_series)
{
    auto f = [](double x) { return cos(x); };
    auto df = [](double x) { return -sin(x); };
    auto ddf = [](double x) { return -cos(x); };

    /* approximate f(x), assuming we know f(a), df(a), ddf(a) */
    auto x = M_PI/3;
    auto a = M_PI/4;
    EXPECT_TRUE(std::fabs(taylor_series(x,a,f)-c0)<zero);
    EXPECT_TRUE(std::fabs(taylor_series(x,a,f,df)-c1)<zero);
    EXPECT_TRUE(std::fabs(taylor_series(x,a,f,df,ddf)-c2)<zero);
}