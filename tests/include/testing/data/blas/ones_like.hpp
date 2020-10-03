#ifndef NMTOOLS_TESTING_DATA_BLAS_ONES_LIKE_HPP
#define NMTOOLS_TESTING_DATA_BLAS_ONES_LIKE_HPP

/* TODO: use __has_include */
#include "nmtools/array/fixed.hpp"
#include "nmtools/blas/blas.hpp"
#include "testing/testing.hpp"
#include <array>
/* TODO: use __has_include */
#include <vector>
#include <valarray>

/* @todo: make simple script to autogenereate test data */

NMTOOLS_TESTING_DECLARE_CASE(blas, ones_like)
{
    using namespace common_matrix;
    NMTOOLS_TESTING_DECLARE_ARGS(case1) {
        using common_matrix::z5x5;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,z5x5);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,5,5);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1) {
        constexpr inline auto x = cast(o5x5<double>);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2) {
        using common_matrix::z10x10;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,z10x10);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,10,10);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2) {
        constexpr inline auto x = cast(o10x10<double>);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3) {
        using common_matrix::z15x15;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,z15x15);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,15,15);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3) {
        constexpr inline auto x = cast(o15x15<double>);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4) {
        using common_matrix::z20x20;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,z20x20);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,20,20);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4) {
        constexpr inline auto x = cast(o20x20<double>);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5) {
        using common_matrix::z25x25;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,z25x25);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,25,25);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5) {
        constexpr inline auto x = cast(o25x25<double>);
    }
}

#endif // NMTOOLS_TESTING_DATA_BLAS_ONES_LIKE_HPP