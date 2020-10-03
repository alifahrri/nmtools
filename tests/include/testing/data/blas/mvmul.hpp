#ifndef NMTOOLS_TESTING_DATA_BLAS_MVMUL_HPP
#define NMTOOLS_TESTING_DATA_BLAS_MVMUL_HPP

/* TODO: use __has_include */
#include "nmtools/array/fixed.hpp"
#include "nmtools/blas/blas.hpp"
#include "testing/testing.hpp"
#include <array>
/* TODO: use __has_include */
#include <vector>
#include <valarray>

/* @todo: make simple script to autogenereate test data */

NMTOOLS_TESTING_DECLARE_CASE(blas, mvmul)
{
    template <typename T>
    constexpr T v3[3] = {1, 2, 3};

    template <typename T>
    constexpr T v5[5] = {1, 2, 3, 4, 5};

    template <typename T>
    constexpr T v10[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    template <typename T>
    constexpr T v15[15] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

    template <typename T>
    constexpr T v20[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};

    template <typename T>
    constexpr T v25[25] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};

    NMTOOLS_TESTING_DECLARE_ARGS(case1) {
        // allow testing using raw array
        using ::nmtools::testing::data::common_matrix::e3x3;
        using ::nmtools::testing::data::blas::mvmul::v3;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,e3x3);
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(y,v3);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,3,3);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(y,3);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1) {
        /**
         * @brief identity matrix multiplied with any vector returns the vector itself;
         * 
         */
        constexpr auto x = cast(v3<double>);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2) {
        // note: for testing using raw array
        using ::nmtools::testing::data::common_matrix::e5x5;
        using ::nmtools::testing::data::blas::mvmul::v5;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,e5x5);
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(y,v5);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,5,5);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(y,5);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2) {
        /**
         * @brief identity matrix multiplied with any vector returns the vector itself;
         * 
         */
        constexpr auto x = cast(v5<double>);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3) {
        // note: for testing using raw array
        using ::nmtools::testing::data::common_matrix::e10x10;
        using ::nmtools::testing::data::blas::mvmul::v10;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,e10x10);
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(y,v10);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,10,10);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(y,10);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3) {
        /**
         * @brief identity matrix multiplied with any vector returns the vector itself;
         * 
         */
        constexpr auto x = cast(v10<double>);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4) {
        // note: for testing using raw array
        using ::nmtools::testing::data::common_matrix::e15x15;
        using ::nmtools::testing::data::blas::mvmul::v15;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,e15x15);
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(y,v15);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,15,15);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(y,15);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4) {
        /**
         * @brief identity matrix multiplied with any vector returns the vector itself;
         * 
         */
        constexpr auto x = cast(v15<double>);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5) {
        // note: for testing using raw array
        using ::nmtools::testing::data::common_matrix::e20x20;
        using ::nmtools::testing::data::blas::mvmul::v20;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,e20x20);
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(y,v20);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,20,20);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(y,20);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5) {
        /**
         * @brief identity matrix multiplied with any vector returns the vector itself;
         * 
         */
        constexpr auto x = cast(v20<double>);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6) {
        // note: for testing using raw array
        using ::nmtools::testing::data::common_matrix::e25x25;
        using ::nmtools::testing::data::blas::mvmul::v25;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,e25x25);
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(y,v25);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,25,25);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(y,25);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6) {
        /**
         * @brief identity matrix multiplied with any vector returns the vector itself;
         * 
         */
        constexpr auto x = cast(v25<double>);
    }
}

#endif // NMTOOLS_TESTING_DATA_BLAS_MVMUL_HPP