#ifndef NMTOOLS_TESTING_DATA_BLAS_VVADD_HPP
#define NMTOOLS_TESTING_DATA_BLAS_VVADD_HPP

/* TODO: use __has_include */
#include "nmtools/array/fixed.hpp"
#include "nmtools/blas/blas.hpp"
#include "testing/testing.hpp"
#include <array>
/* TODO: use __has_include */
#include <vector>
#include <valarray>

/* @todo: make simple script to autogenereate test data */

NMTOOLS_TESTING_DECLARE_CASE(blas,vvadd)
{
    template <typename T>
    constexpr T v10[10] = {1,   2,   3,   4,   5,   6,   7,   8,   9,   0};

    template <typename T>
    constexpr T v20[20] = {1,    2,    3,    4,    5,    6,    7,    8,    9,   10,   11,   12,   13,   14,   15,   16,   17,   18,   19,   20};

    NMTOOLS_TESTING_DECLARE_ARGS(case1) {
        using ::nmtools::testing::data::blas::vvadd::v10;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,v10);
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(y,v10);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(x,10);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(y,10);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1) {
        constexpr auto x = std::array<double,10>{2,    4,    6,    8,   10,   12,   14,   16,   18,    0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2) {
        using ::nmtools::testing::data::blas::vvadd::v20;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,v20);
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(y,v20);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(x,20);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(y,20);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2) {
        constexpr auto x = std::array<double,20>{2,    4,    6,    8,   10,   12,   14,   16,   18,   20,   22,   24,   26,   28,   30,   32,   34,   36,   38,   40};
    }
} // namespace nmtools::testing::data::blas::vvadd

#endif // NMTOOLS_TESTING_DATA_BLAS_VVADD_HPP