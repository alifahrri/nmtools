#ifndef NMTOOLS_TESTING_DATA_BLAS_CLONE_HPP
#define NMTOOLS_TESTING_DATA_BLAS_CLONE_HPP

/* TODO: use __has_include */
#include "nmtools/array/fixed.hpp"
#include "nmtools/blas/blas.hpp"
#include "testing/testing.hpp"
#include <array>
/* TODO: use __has_include */
#include <vector>
#include <valarray>

/* @todo: make simple script to autogenereate test data */

NMTOOLS_TESTING_DECLARE_CASE(blas,clone)
{
    namespace magic = common_matrix::magic;

    NMTOOLS_TESTING_DECLARE_ARGS(case1) {
        // allow testing raw array
        using magic::m5x5;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,m5x5);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,5,5);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1) {
        constexpr inline auto res = cast(magic::m5x5<double>);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2) {
        // allow testing raw array
        using magic::m10x10;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,m10x10);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,10,10);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2) {
        constexpr inline auto res = cast(magic::m10x10<double>);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3) {
        // allow testing raw array
        using magic::m15x15;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,m15x15);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,15,15);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3) {
        constexpr inline auto res = cast(magic::m15x15<double>);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4) {
        // allow testing raw array
        using magic::m20x20;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,m20x20);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,20,20);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4) {
        constexpr inline auto res = cast(magic::m20x20<double>);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5) {
        // allow testing raw array
        using magic::m25x25;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,m25x25);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,25,25);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5) {
        constexpr inline auto res = cast(magic::m25x25<double>);
    }
}

#endif // NMTOOLS_TESTING_DATA_BLAS_CLONE_HPP