#ifndef NMTOOLS_TESTING_DATA_LINALG_HPP
#define NMTOOLS_TESTING_DATA_LINALG_HPP

#include <array>

namespace nmtools::testing::data::linalg
{
    namespace householder_vector
    {
        /**
         * @brief arguments to householder_vector
         * 
         */
        namespace args {
            auto x = std::array<double,3>{1,2,3};
        } // namespace args
        /**
         * @brief expected values
         * 
         */
        namespace expected {
            constexpr auto housv = std::array<double,3>{1.580552462257980e+00,   6.666666666666666e-01,   1.000000000000000e+00};
            constexpr auto beta = 5.072806786760140e-01;
        } // namespace expected
    } // namespace householder_vector
} // namespace nmtools::testing::data::linalg

#endif // NMTOOLS_TESTING_DATA_LINALG_HPP