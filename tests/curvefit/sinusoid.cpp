#include <gtest/gtest.h>
#include "curvefit.hpp"

TEST(curvefit,sinusoid_double_precision) {
    namespace fit = numeric::curvefit;
    double t[] = { 0.,      0.15,   0.30,   0.45,   0.60,   0.75,   0.90,   1.05,   1.20,   1.35  };
    double y[] = { 2.200,   1.595,  1.031,  0.722,  0.786,  1.200,  1.805,  2.369,  2.678,  2.614 };
    double a0, a1, b1;
    double w{4.189};
    fit::sinusoid(t,y,w,a0,a1,b1);
    double zero = 1e-3;
    EXPECT_NEAR(a0,1.7,1e-1);
    EXPECT_NEAR(a1,0.500,zero);
    EXPECT_NEAR(b1,-0.866,zero);
}

TEST(curvefit,sinusoid_single_precision) {
    namespace fit = numeric::curvefit;
    float t[] = { 0.,      0.15,   0.30,   0.45,   0.60,   0.75,   0.90,   1.05,   1.20,   1.35  };
    float y[] = { 2.200,   1.595,  1.031,  0.722,  0.786,  1.200,  1.805,  2.369,  2.678,  2.614 };
    float a0, a1, b1;
    float w{4.189};
    fit::sinusoid(t,y,w,a0,a1,b1);
    float zero = 1e-3;
    EXPECT_NEAR(a0,1.7,1e-1);
    EXPECT_NEAR(a1,0.500,zero);
    EXPECT_NEAR(b1,-0.866,zero);
}