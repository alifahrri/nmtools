#include <gtest/gtest.h>
#include "fourier/series.hpp"
#include <array>

TEST(fourier,series_double_precision) {
    double a0;
    std::array<double,10> a, b;
    double w{M_PI/2};
    double T{2*M_PI/w};
    auto f = [=](double x) -> double {
        double t = x - T/2;
        if ( (t>(-3*T/4)) && (t<-T/4) ) return -1.;
        else if ( (t>(-T/4)) && (t<(T/4)) ) return 1.;
        else if ( (t>(T/4)) && (t<(3*T/4)) ) return -1.;
        else return 1.;
    };
    numeric::fourier::series<10000>(f,T,a0,a,b);
    double zero = 1e-3;
    EXPECT_NEAR(a0,0,zero);
    for (size_t i=0; i<10; i++) {
        auto k = i+1;
        if (k==1 || k==5 || k==9) 
            EXPECT_NEAR(a[i],-4/(k*M_PI),zero) << k;
        else if (k==3 || k==7 || k==11)
            EXPECT_NEAR(a[i],4/(k*M_PI),zero) << k;
        else 
            EXPECT_NEAR(a[i],0,zero) << k;
        EXPECT_NEAR(b[i],0,zero) << k;
    }
}

TEST(fourier,series_single_precision) {
    float a0;
    std::array<float,10> a, b;
    float w{M_PI/2};
    float T{2*M_PI/w};
    auto f = [=](float x) -> float {
        float t = x - T/2;
        if ( (t>(-3*T/4)) && (t<-T/4) ) return -1.;
        else if ( (t>(-T/4)) && (t<(T/4)) ) return 1.;
        else if ( (t>(T/4)) && (t<(3*T/4)) ) return -1.;
        else return 1.;
    };
    numeric::fourier::series<10000>(f,T,a0,a,b);
    float zero = 1e-3;
    EXPECT_NEAR(a0,0,zero);
    for (size_t i=0; i<10; i++) {
        auto k = i+1;
        if (k==1 || k==5 || k==9) 
            EXPECT_NEAR(a[i],-4/(k*M_PI),zero) << k;
        else if (k==3 || k==7 || k==11)
            EXPECT_NEAR(a[i],4/(k*M_PI),zero) << k;
        else 
            EXPECT_NEAR(a[i],0,zero) << k;
        EXPECT_NEAR(b[i],0,zero) << k;
    }
}