#ifndef NMTOOLS_TESTING_DATA_ARRAY_BITWISE_OR_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_BITWISE_OR_HPP

#include "nmtools/ndarray/dynamic.hpp"
#include "nmtools/ndarray/hybrid.hpp"
#include "nmtools/ndarray/fixed.hpp"
#include "nmtools/testing/testing.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nmtools;
namespace view = nm::view;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(view, bitwise_or)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int a[3][3] = {
            {0,1,2},
            {3,4,5},
            {6,7,8},
        };
        inline int b[3] = {0,1,2};
        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int shape[2] = {3,3};
        inline int result[3][3] = {
            {0 | 0, 1 | 1, 2 | 2},
            {3 | 0, 4 | 1, 5 | 2},
            {6 | 0, 7 | 1, 8 | 2},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int a[3][3] = {
            {0,1,2},
            {3,4,5},
            {6,7,8},
        };
        inline int b = 1;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int shape[2] = {3,3};
        inline int result[3][3] = {
            {0 | 1, 1 | 1, 2 | 1},
            {3 | 1, 4 | 1, 5 | 1},
            {6 | 1, 7 | 1, 8 | 1},
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_BITWISE_OR_HPP