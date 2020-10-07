#ifndef NMTOOLS_TESTING_DATA_ARRAY_UTILITY_AT_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_UTILITY_AT_HPP

/* TODO: use __has_include */
#include "testing/testing.hpp"
#include <array>

/* @todo: make simple script to autogenereate test data */

NMTOOLS_TESTING_DECLARE_CASE(at)
{
    namespace magic = common_matrix::magic;

    NMTOOLS_TESTING_DECLARE_ARGS(case1) {
        using magic::m5x5;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,m5x5);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,5,5);
        constexpr inline auto i = 2;
        constexpr inline auto j = 2;
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(i);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(j);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1) {
        constexpr inline auto res = 13;
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_UTILITY_AT_HPP