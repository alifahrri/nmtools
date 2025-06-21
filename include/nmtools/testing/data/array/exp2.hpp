#ifndef NMTOOLS_TESTING_DATA_ARRAY_EXP2_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_EXP2_HPP

#include "nmtools/ndarray/dynamic.hpp"
#include "nmtools/ndarray/hybrid.hpp"
#include "nmtools/ndarray/fixed.hpp"
#include "nmtools/testing/testing.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nmtools;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(view, exp2)
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
        inline int shape[2] = {3,3};
        inline float result[3][3] = {
            {std::exp2(0.f),std::exp2(1.f),std::exp2(2.f)},
            {std::exp2(3.f),std::exp2(4.f),std::exp2(5.f)},
            {std::exp2(6.f),std::exp2(7.f),std::exp2(8.f)},
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_EXP2_HPP