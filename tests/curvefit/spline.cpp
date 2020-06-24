#include <gtest/gtest.h>
#include "nmtools/curvefit.hpp"

#define NEAR(x,y,eps) (std::fabs(x-y) < eps)

TEST(curvefit, cubic_spline)
{
    {
        std::vector<double> t_data{
            0.0, 0.1, 0.2, 0.35, 0.5, 0.65, 0.8, 0.9, 1.0
        };
        std::vector<double> z_data{
            0.0, 0.2, 0.4, 0.7, 1.0, 0.4, 0.2, 0.2, 0.0
        };
        auto results = nmtools::curvefit::cubic_spline(t_data, z_data, t_data);
        ASSERT_EQ(std::size(results),std::size(t_data));
        for (size_t i=0; i<std::size(results); i++)
            EXPECT_NEAR(z_data[i], results[i], 1e-6);
    }
}

TEST(curvefit, cubic_spline_from_array)
{
    constexpr std::array<double,9> t_data{
        0.0, 0.1, 0.2, 0.35, 0.5, 0.65, 0.8, 0.9, 1.0
    };
    constexpr std::array<double,9> z_data{
        0.0, 0.2, 0.4, 0.7, 1.0, 0.4, 0.2, 0.2, 0.0
    };
    {
        auto results = nmtools::curvefit::cubic_spline(t_data, z_data, t_data);
        ASSERT_EQ(std::size(results),std::size(t_data));
        for (size_t i=0; i<std::size(results); i++)
            EXPECT_NEAR(z_data[i], results[i], 1e-6);
    }
    {
        constexpr auto results = nmtools::curvefit::cubic_spline(t_data, z_data, t_data);
        static_assert(std::size(results)==std::size(t_data));
        // for (size_t i=0; i<std::size(results); i++)
        //     static_assert(NEAR(z_data[i], results[i], 1e-6));
        static_assert(NEAR(z_data[0], results[0], 1e-6));
        static_assert(NEAR(z_data[1], results[1], 1e-6));
        static_assert(NEAR(z_data[2], results[2], 1e-6));
        static_assert(NEAR(z_data[3], results[3], 1e-6));
        static_assert(NEAR(z_data[4], results[4], 1e-6));
        static_assert(NEAR(z_data[5], results[5], 1e-6));
        static_assert(NEAR(z_data[6], results[6], 1e-6));
        static_assert(NEAR(z_data[7], results[7], 1e-6));
        static_assert(NEAR(z_data[8], results[8], 1e-6));
    }
}