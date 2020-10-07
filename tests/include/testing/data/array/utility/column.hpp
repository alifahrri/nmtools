#ifndef NMTOOLS_TESTING_DATA_ARRAY_UTILITY_ROW_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_UTILITY_ROW_HPP

/* TODO: use __has_include */
#include "testing/testing.hpp"
#include <array>

/* @todo: make simple script to autogenereate test data */

NMTOOLS_TESTING_DECLARE_CASE(column)
{
    namespace magic = common_matrix::magic;

    NMTOOLS_TESTING_DECLARE_ARGS(case1) {
        using magic::m5x5;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,m5x5);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,5,5);
        constexpr inline size_t r = 2;
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(r);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1) {
        auto res = std::array<double,5>{ 1, 7, 13, 19, 25};
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_UTILITY_ROW_HPP