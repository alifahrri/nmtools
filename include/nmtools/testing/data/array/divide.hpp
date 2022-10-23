#ifndef NMTOOLS_TESTING_DATA_ARRAY_DIVIDE_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_DIVIDE_HPP

#include "nmtools/array/view/ufuncs/divide.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/testing/testing.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(view, divide)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline float a[3][3] = {
            {0,1,2},
            {3,4,5},
            {6,7,8},
        };
        inline int b[3] = {1,1,2};
        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int shape[2] = {3,3};
        inline float result[3][3] = {
            {0.f/1,1.f/1,2.f/2},
            {3.f/1,4.f/1,5.f/2},
            {6.f/1,7.f/1,8.f/2},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline float a[3][3] = {
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
        inline float result[3][3] = {
            {0.f/2,1.f/2,2.f/2},
            {3.f/2,4.f/2,5.f/2},
            {6.f/2,7.f/2,8.f/2},
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_DIVIDE_HPP