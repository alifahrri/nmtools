#ifndef NMTOOLS_TESTING_DATA_BLAS_COL_SUM_HPP
#define NMTOOLS_TESTING_DATA_BLAS_COL_SUM_HPP

/* TODO: use __has_include */
#include "nmtools/array/fixed.hpp"
#include "nmtools/blas/blas.hpp"
#include "testing/testing.hpp"
#include <array>
/* TODO: use __has_include */
#include <vector>
#include <valarray>

/* @todo: make simple script to autogenereate test data */

NMTOOLS_TESTING_DECLARE_CASE(blas, col_sum)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1) {
        template <typename T>
        constexpr T x[2][5] = {
            {1, 2, 3, 4,  5},
            {6, 7, 8, 9, 10}
        };
        inline auto xad = cast<double>(x<double>);
        inline auto xaf = cast<double>(x<float>);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,2,5);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1) {
        inline constexpr auto sum = std::array<double,2>{15, 40};
    }

    namespace magic = common_matrix::magic;

    NMTOOLS_TESTING_DECLARE_ARGS(case2) {
        using magic::m5x5;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,m5x5);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,5,5);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2) {
        inline constexpr auto sum = std::array<double,5>{65, 65, 65, 65, 65};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3) {
        using magic::m10x10;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,m10x10);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,10,10);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3) {
        inline constexpr auto sum = std::array<double,10>{505, 505, 505, 505, 505, 505, 505, 505, 505, 505};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4) {
        using magic::m15x15;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,m15x15);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,15,15);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4) {
        inline constexpr auto sum = std::array<double,15>{1695, 1695, 1695, 1695, 1695, 1695, 1695, 1695, 1695, 1695, 1695, 1695, 1695, 1695, 1695};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5) {
        using magic::m20x20;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,m20x20);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,20,20);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5) {
        inline constexpr auto sum = std::array<double,20>{4010,   4010,   4010,   4010,   4010,   4010,   4010,   4010,   4010,   4010,   4010,   4010,   4010,   4010,   4010,   4010,   4010,   4010,   4010,   4010,};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6) {
        using magic::m25x25;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,m25x25);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,25,25);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6) {
        inline constexpr auto sum = std::array<double,25>{7825,   7825,   7825,   7825,   7825,   7825,   7825,   7825,   7825,   7825,   7825,   7825,   7825,   7825,   7825,   7825,   7825,   7825,   7825,   7825,   7825,   7825,   7825,   7825,   7825,};
    }
}

#endif // NMTOOLS_TESTING_DATA_BLAS_COL_SUM_HPP