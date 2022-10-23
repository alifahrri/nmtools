#ifndef NMTOOLS_TESTING_DATA_ARRAY_COS_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_COS_HPP

#include "nmtools/array/ndarray.hpp"
#include "nmtools/testing/array_cast.hpp"
#include "nmtools/testing/testing.hpp"
#include "nmtools/math.hpp"

NMTOOLS_TESTING_DECLARE_CASE(view, cos)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline float a[3][3] = {
            {0,1,2},
            {3,4,5},
            {6,7,8},
        };
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline float result[3][3] = {
            {math::cos(0.f),math::cos(1.f),math::cos(2.f)},
            {math::cos(3.f),math::cos(4.f),math::cos(5.f)},
            {math::cos(6.f),math::cos(7.f),math::cos(8.f)},
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_COS_HPP