#include <gtest/gtest.h>
#include "curvefit.hpp"

TEST(curvefit, cubic_spline)
{
    {
        std::vector<double> t_data{
            0.0, 0.1, 0.2, 0.35, 0.5, 0.65, 0.8, 0.9, 1.0
        };
        std::vector<double> z_data{
            0.0, 0.2, 0.4, 0.7, 1.0, 0.4, 0.2, 0.2, 0.0
        };
        auto results = numeric::curvefit::cubic_spline(t_data, z_data, t_data);
        ASSERT_EQ(std::size(results),std::size(t_data));
        for (size_t i=0; i<std::size(results); i++)
            EXPECT_NEAR(z_data[i], results[i], 1e-6);
    }
}