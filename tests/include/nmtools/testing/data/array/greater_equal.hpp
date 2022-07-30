#ifndef NMTOOLS_TESTING_DATA_ARRAY_GREATER_EQUAL_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_GREATER_EQUAL_HPP

#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/testing/testing.hpp"

#include <vector>
#include <array>
#include <algorithm> // std::max

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(view, greater_equal)
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
        inline bool result[3][3] = {
            {(0>=0),(1>=1),(2>=2)},
            {(3>=0),(4>=1),(5>=2)},
            {(6>=0),(7>=1),(8>=2)},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int a[3][3] = {
            {0,1,2},
            {3,4,5},
            {6,7,8},
        };
        inline int b = 2;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int shape[2] = {3,3};
        inline bool result[3][3] = {
            {(0>=2),(1>=2),(2>=2)},
            {(3>=2),(4>=2),(5>=2)},
            {(6>=2),(7>=2),(8>=2)},
        };
    }
}
#endif // NMTOOLS_TESTING_DATA_ARRAY_GREATER_EQUAL_HPP