#include <gtest/gtest.h>
#include "nmtools/curvefit.hpp"
#include <tuple>

#define NEAR(x,y,eps) (std::fabs(x-y) < eps)

TEST(curvefit,sinusoid_double_precision) {
    namespace fit = nmtools::curvefit;
    constexpr double t[] = { 0.,      0.15,   0.30,   0.45,   0.60,   0.75,   0.90,   1.05,   1.20,   1.35  };
    constexpr double y[] = { 2.200,   1.595,  1.031,  0.722,  0.786,  1.200,  1.805,  2.369,  2.678,  2.614 };
    constexpr double w{4.189};
    constexpr double zero = 1e-3;
    {
        auto [a0, a1, b1] = fit::sinusoid(t,y,w);
        EXPECT_NEAR(a0,1.7,1e-1);
        EXPECT_NEAR(a1,0.500,zero);
        EXPECT_NEAR(b1,-0.866,zero);
    }
    {
        constexpr auto coefficients = fit::sinusoid(t,y,w);
        constexpr auto a0 = std::get<0>(coefficients);
        constexpr auto a1 = std::get<1>(coefficients);
        constexpr auto b1 = std::get<2>(coefficients);
        static_assert(NEAR(a0,1.7,1e-1));
        static_assert(NEAR(a1,0.500,zero));
        static_assert(NEAR(b1,-0.866,zero));
    }
}

TEST(curvefit,sinusoid_single_precision) {
    namespace fit = nmtools::curvefit;
    constexpr float t[] = { 0.,      0.15,   0.30,   0.45,   0.60,   0.75,   0.90,   1.05,   1.20,   1.35  };
    constexpr float y[] = { 2.200,   1.595,  1.031,  0.722,  0.786,  1.200,  1.805,  2.369,  2.678,  2.614 };
    constexpr float w{4.189};
    constexpr float zero = 1e-3;
    {
        auto [a0, a1, b1] = fit::sinusoid(t,y,w);
        EXPECT_NEAR(a0,1.7,1e-1);
        EXPECT_NEAR(a1,0.500,zero);
        EXPECT_NEAR(b1,-0.866,zero);
    }
    {
        constexpr auto coefficients = fit::sinusoid(t,y,w);
        constexpr auto a0 = std::get<0>(coefficients);
        constexpr auto a1 = std::get<1>(coefficients);
        constexpr auto b1 = std::get<2>(coefficients);
        static_assert(NEAR(a0,1.7,1e-1));
        static_assert(NEAR(a1,0.500,zero));
        static_assert(NEAR(b1,-0.866,zero));
    }
}

TEST(curvefit,sinusoid_container) {
    namespace fit = nmtools::curvefit;
    constexpr std::array<double,10> t{ 0.,      0.15,   0.30,   0.45,   0.60,   0.75,   0.90,   1.05,   1.20,   1.35  };
    constexpr std::array<double,10> y{ 2.200,   1.595,  1.031,  0.722,  0.786,  1.200,  1.805,  2.369,  2.678,  2.614 };
    constexpr double w{4.189};
    constexpr double zero = 1e-3;
    {
        auto [a0, a1, b1] = fit::sinusoid(t,y,w);
        EXPECT_NEAR(a0,1.7,1e-1);
        EXPECT_NEAR(a1,0.500,zero);
        EXPECT_NEAR(b1,-0.866,zero);
    }
    {
        constexpr auto coefficients = fit::sinusoid(t,y,w);
        constexpr auto a0 = std::get<0>(coefficients);
        constexpr auto a1 = std::get<1>(coefficients);
        constexpr auto b1 = std::get<2>(coefficients);
        static_assert(NEAR(a0,1.7,1e-1));
        static_assert(NEAR(a1,0.500,zero));
        static_assert(NEAR(b1,-0.866,zero));
    }
    {
        std::vector<double> t{ 0.,      0.15,   0.30,   0.45,   0.60,   0.75,   0.90,   1.05,   1.20,   1.35  };
        std::vector<double> y{ 2.200,   1.595,  1.031,  0.722,  0.786,  1.200,  1.805,  2.369,  2.678,  2.614 };
        auto [a0, a1, b1] = fit::sinusoid(t,y,w);
        EXPECT_NEAR(a0,1.7,1e-1);
        EXPECT_NEAR(a1,0.500,zero);
        EXPECT_NEAR(b1,-0.866,zero);
    }
}