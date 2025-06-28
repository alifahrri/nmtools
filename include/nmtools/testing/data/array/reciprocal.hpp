#ifndef NMTOOLS_TESTING_DATA_ARRAY_RECIPROCAL_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_RECIPROCAL_HPP

#include "nmtools/ndarray/dynamic.hpp"
#include "nmtools/ndarray/hybrid.hpp"
#include "nmtools/ndarray/fixed.hpp"
#include "nmtools/testing/testing.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nmtools;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(view, reciprocal)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline float a[3][3] = {
            {1,1,2},
            {3,4,5},
            {6,7,8},
        };
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int shape[2] = {3,3};
        inline float result[3][3] = {
            {1/1.f,1/1.f,1/2.f},
            {1/3.f,1/4.f,1/5.f},
            {1/6.f,1/7.f,1/8.f},
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_RECIPROCAL_HPP