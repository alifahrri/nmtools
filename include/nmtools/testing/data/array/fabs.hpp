#ifndef NMTOOLS_TESTING_DATA_ARRAY_FABS_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_FABS_HPP

#include "nmtools/ndarray/dynamic.hpp"
#include "nmtools/ndarray/hybrid.hpp"
#include "nmtools/ndarray/fixed.hpp"
#include "nmtools/testing/testing.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nmtools;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(view, fabs)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline float a[3][3] = {
            {0,-1,2},
            {3,-4,5},
            {6,-7,8},
        };
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int shape[2] = {3,3};
        inline float result[3][3] = {
            {static_cast<float>(std::fabs(0)),static_cast<float>(std::fabs(-1)),static_cast<float>(std::fabs(2))},
            {static_cast<float>(std::fabs(3)),static_cast<float>(std::fabs(-4)),static_cast<float>(std::fabs(5))},
            {static_cast<float>(std::fabs(6)),static_cast<float>(std::fabs(-7)),static_cast<float>(std::fabs(8))},
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_FABS_HPP