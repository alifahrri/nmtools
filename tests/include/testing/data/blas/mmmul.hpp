#ifndef NMTOOLS_TESTING_DATA_BLAS_MMMUL_HPP
#define NMTOOLS_TESTING_DATA_BLAS_MMMUL_HPP

/* TODO: use __has_include */
#include "nmtools/array/fixed.hpp"
#include "nmtools/blas/blas.hpp"
#include "testing/testing.hpp"
#include <array>
/* TODO: use __has_include */
#include <vector>
#include <valarray>

/* @todo: make simple script to autogenereate test data */

NMTOOLS_TESTING_DECLARE_CASE(blas,mmmul)
{
    using namespace common_matrix;
    NMTOOLS_TESTING_DECLARE_ARGS(case1) {
        using magic::m5x5;
        using common_matrix::z5x5;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,m5x5);
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(y,z5x5);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,5,5);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(y,5,5);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1) {
        /**
         * @brief any matrix multiplied with zeros matrix results in zeros matrix
         * 
         */
        constexpr inline auto x = cast(z5x5<double>);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2) {
        using magic::m10x10;
        using common_matrix::z10x10;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,m10x10);
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(y,z10x10);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,10,10);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(y,10,10);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2) {
        /**
         * @brief any matrix multiplied with zeros matrix results in zeros matrix
         * 
         */
        constexpr inline auto x = cast(z10x10<double>);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3) {
        using magic::m15x15;
        using common_matrix::z15x15;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,m15x15);
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(y,z15x15);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,15,15);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(y,15,15);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3) {
        /**
         * @brief any matrix multiplied with zeros matrix results in zeros matrix
         * 
         */
        constexpr inline auto x = cast(z15x15<double>);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4) {
        using magic::m20x20;
        using common_matrix::z20x20;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,m20x20);
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(y,z20x20);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,20,20);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(y,20,20);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4) {
        /**
         * @brief any matrix multiplied with zeros matrix results in zeros matrix
         * 
         */
        constexpr inline auto x = cast(z20x20<double>);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5) {
        using magic::m25x25;
        using common_matrix::z25x25;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,m25x25);
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(y,z25x25);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,25,25);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(y,25,25);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5) {
        /**
         * @brief any matrix multiplied with zeros matrix results in zeros matrix
         * 
         */
        constexpr inline auto x = cast(z25x25<double>);
    }
} // namespace nmtools::testing::data::blas::mmmul

#endif // NMTOOLS_TESTING_DATA_BLAS_MMMUL_HPP