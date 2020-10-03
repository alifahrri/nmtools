#ifndef NMTOOLS_TESTING_DATA_BLAS_MATRIX_NORM_HPP
#define NMTOOLS_TESTING_DATA_BLAS_MATRIX_NORM_HPP

/* TODO: use __has_include */
#include "nmtools/array/fixed.hpp"
#include "nmtools/blas/blas.hpp"
#include "testing/testing.hpp"
#include <array>
/* TODO: use __has_include */
#include <vector>
#include <valarray>

/* @todo: make simple script to autogenereate test data */

NMTOOLS_TESTING_DECLARE_CASE(blas,matrix_norm)
{
    template <typename T>
    constexpr T x[2][5] = {
        {1, 2, 3, 4,  5},
        {6, 7, 8, 9, 10}
    };

    NMTOOLS_TESTING_DECLARE_ARGS(case1) {
        // allow testing raw array
        using matrix_norm::x;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,x);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,2,5);
        inline constexpr auto p = 1;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1) {
        inline constexpr auto norm = 15;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2) {
        // allow testing raw array
        using matrix_norm::x;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,x);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,2,5);
        inline constexpr auto p = ::nmtools::blas::norm_t::infinity_norm;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2) {
        inline constexpr auto norm = 40;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3) {
        // allow testing raw array
        using matrix_norm::x;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,x);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,2,5);
        inline constexpr auto p = ::nmtools::blas::norm_t::frobenius_norm;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3) {
        inline constexpr auto norm = 1.96214168703485860589808e+01;
    }

    namespace magic = common_matrix::magic;

    NMTOOLS_TESTING_DECLARE_ARGS(case4) {
        // allow testing raw array
        using magic::m5x5;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,m5x5);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,5,5);
        inline constexpr auto p = 1;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4) {
        inline constexpr auto norm = 65;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5) {
        // allow testing raw array
        using magic::m10x10;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,m10x10);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,10,10);
        inline constexpr auto p = 1;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5) {
        inline constexpr auto norm = 505;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6) {
        // allow testing raw array
        using magic::m15x15;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,m15x15);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,15,15);
        inline constexpr auto p = 1;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6) {
        inline constexpr auto norm = 1695;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7) {
        // allow testing raw array
        using magic::m20x20;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,m20x20);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,20,20);
        inline constexpr auto p = 1;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7) {
        inline constexpr auto norm = 4010;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8) {
        // allow testing raw array
        using magic::m25x25;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,m25x25);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,25,25);
        inline constexpr auto p = 1;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8) {
        inline constexpr auto norm = 7825;
    }
}

#endif // NMTOOLS_TESTING_DATA_BLAS_MATRIX_NORM_HPP