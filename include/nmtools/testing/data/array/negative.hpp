#ifndef NMTOOLS_TESTING_DATA_ARRAY_NEGATIVE_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_NEGATIVE_HPP

#include "nmtools/ndarray/dynamic.hpp"
#include "nmtools/ndarray/hybrid.hpp"
#include "nmtools/ndarray/fixed.hpp"
#include "nmtools/testing/testing.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(view, negative)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int a[3][3] = {
            {0,1,2},
            {3,4,5},
            {6,7,8},
        };
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int shape[2] = {3,3};
        inline int result[3][3] = {
            {-0,-1,-2},
            {-3,-4,-5},
            {-6,-7,-8},
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_NEGATIVE_HPP