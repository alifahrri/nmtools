#ifndef NMTOOLS_TESTING_DATA_ARRAY_SQRT_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_SQRT_HPP

#include "nmtools/ndarray/dynamic.hpp"
#include "nmtools/ndarray/hybrid.hpp"
#include "nmtools/ndarray/fixed.hpp"
#include "nmtools/testing/testing.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nmtools;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(view, sqrt)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline float a[3][3] = {
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
        inline float result[3][3] = {
            {std::sqrt(0.f),std::sqrt(1.f),std::sqrt(2.f)},
            {std::sqrt(3.f),std::sqrt(4.f),std::sqrt(5.f)},
            {std::sqrt(6.f),std::sqrt(7.f),std::sqrt(8.f)},
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_SQRT_HPP