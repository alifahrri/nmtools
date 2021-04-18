#ifndef NMTOOLS_TESTING_DATA_ARRAY_UTILITY_SQUEEZE_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_UTILITY_SQUEEZE_HPP

/* TODO: use __has_include */
#include "nmtools/array/fixed.hpp"
#include "testing/testing.hpp"
#include <array>
#include <tuple>

/* @todo: make simple script to autogenereate test data */

NMTOOLS_TESTING_DECLARE_CASE(squeeze)
{
    template <typename T>
    constexpr T a[1][2] = {{1,2}};
    template <typename T>
    constexpr T b[2][1] = {{1},{2}};
    template <typename T>
    constexpr T c[2][2] = {{1,2},{3,4}};

    NMTOOLS_TESTING_DECLARE_ARGS(case1) {
        using squeeze::a;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,a);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,1,2);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1) {
        constexpr inline auto res = std::array<double,2>{1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2) {
        using squeeze::b;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,b);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,2,1);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2) {
        constexpr inline auto res = std::array<double,2>{1,2};
    }
    NMTOOLS_TESTING_DECLARE_ARGS(case3) {
        using squeeze::c;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,c);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,2,2);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3) {
        constexpr inline auto res = std::array<std::array<double,2>,2>{{{1,2},{3,4}}};
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_UTILITY_SQUEEZE_HPP