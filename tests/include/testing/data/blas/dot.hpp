#ifndef NMTOOLS_TESTING_DATA_BLAS_DOT_HPP
#define NMTOOLS_TESTING_DATA_BLAS_DOT_HPP

/* TODO: use __has_include */
#include "nmtools/array/fixed.hpp"
#include "nmtools/blas/blas.hpp"
#include "testing/testing.hpp"
#include <array>
/* TODO: use __has_include */
#include <vector>
#include <valarray>

/* @todo: make simple script to autogenereate test data */

NMTOOLS_TESTING_DECLARE_CASE(blas, dot)
{
    template <typename T>
    constexpr T tenth5[5] = {0.10, 0.10, 0.10, 0.10, 0.10};

    template <typename T>
    constexpr T tenth10[10] = {0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10};

    template <typename T>
    constexpr T tenth15[15] = {0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10};

    template <typename T>
    constexpr T tenth20[20] = {0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10};

    template <typename T>
    constexpr T tenth25[25] = {0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10};

    NMTOOLS_TESTING_DECLARE_ARGS(case1) {
        using ::nmtools::testing::data::common::v5;
        using ::nmtools::testing::data::blas::dot::tenth5;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,v5);
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(y,tenth5);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(x,5);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(y,5);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1) {
        constexpr auto d = 6.5;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2) {
        using ::nmtools::testing::data::common::v10;
        using ::nmtools::testing::data::blas::dot::tenth10;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,v10);
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(y,tenth10);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(x,10);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(y,10);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2) {
        constexpr auto d = 50.5;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3) {
        using ::nmtools::testing::data::common::v15;
        using ::nmtools::testing::data::blas::dot::tenth15;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,v15);
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(y,tenth15);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(x,15);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(y,15);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3) {
        constexpr auto d = 169.5;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4) {
        using ::nmtools::testing::data::common::v20;
        using ::nmtools::testing::data::blas::dot::tenth20;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,v20);
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(y,tenth20);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(x,20);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(y,20);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4) {
        constexpr auto d = 401.;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5) {
        using ::nmtools::testing::data::common::v25;
        using ::nmtools::testing::data::blas::dot::tenth25;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,v25);
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(y,tenth25);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(x,25);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(y,25);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5) {
        constexpr auto d = 782.5;
    }
} // namespace nmtools::testing::data::blas::dot

#endif