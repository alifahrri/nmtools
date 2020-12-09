#ifndef NMTOOLS_TESTING_DATA_BLAS_ZEROS_LIKE_HPP
#define NMTOOLS_TESTING_DATA_BLAS_ZEROS_LIKE_HPP

/* TODO: use __has_include */
#include "nmtools/array/fixed.hpp"
#include "nmtools/blas/blas.hpp"
#include "testing/testing.hpp"
#include <array>
/* TODO: use __has_include */
#include <vector>
#include <valarray>

/* @todo: make simple script to autogenereate test data */

NMTOOLS_TESTING_DECLARE_CASE(blas,zeros_like)
{
    using namespace common_matrix;

    template <typename T>
    constexpr T x3[3] = {1, 2, 3};

    template <typename T>
    constexpr T z3[3] = {0, 0, 0};

    NMTOOLS_TESTING_DECLARE_ARGS(case1) {
        using ::nmtools::testing::data::blas::zeros_like::x3;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,x3);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(x,3);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1) {
        constexpr inline auto x = cast<double>(z3<double>);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2) {
        using common_matrix::o3x3;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,o3x3);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,3,3);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2) {
        constexpr inline auto x = cast<double>(z3x3<double>);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3) {
        using common_matrix::o5x5;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,o5x5);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,5,5);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3) {
        constexpr inline auto x = cast<double>(z5x5<double>);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4) {
        using common_matrix::o10x10;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,o10x10);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,10,10);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4) {
        constexpr inline auto x = cast<double>(z10x10<double>);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5) {
        using common_matrix::o15x15;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,o15x15);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,15,15);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5) {
        constexpr inline auto x = cast<double>(z15x15<double>);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6) {
        using common_matrix::o20x20;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,o20x20);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,20,20);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6) {
        constexpr inline auto x = cast<double>(z20x20<double>);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7) {
        using common_matrix::o25x25;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,o25x25);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,25,25);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7) {
        constexpr inline auto x = cast<double>(z25x25<double>);
    }
} // namespace nmtools::testing::data::blas::zeros_like

#endif // NMTOOLS_TESTING_DATA_BLAS_ZEROS_LIKE_HPP