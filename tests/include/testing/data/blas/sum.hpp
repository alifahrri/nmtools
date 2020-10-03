#ifndef NMTOOLS_TESTING_DATA_BLAS_SUM_HPP
#define NMTOOLS_TESTING_DATA_BLAS_SUM_HPP

/* TODO: use __has_include */
#include "nmtools/array/fixed.hpp"
#include "nmtools/blas/blas.hpp"
#include "testing/testing.hpp"
#include <array>
/* TODO: use __has_include */
#include <vector>
#include <valarray>

/* @todo: make simple script to autogenereate test data */

NMTOOLS_TESTING_DECLARE_CASE(blas,sum)
{
    template <typename T>
    constexpr T x[2][5] = {
        {1, 2, 3, 4,  5},
        {6, 7, 8, 9, 10}
    };
    NMTOOLS_TESTING_DECLARE_ARGS(case1) {
        using ::nmtools::testing::data::blas::sum::x;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,x);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,2,5);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1) {
        inline constexpr auto sum = 55.;
    }
}

#endif // NMTOOLS_TESTING_DATA_BLAS_SUM_HPP