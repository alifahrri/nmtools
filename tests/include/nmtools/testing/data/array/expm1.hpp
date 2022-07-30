#ifndef NMTOOLS_TESTING_DATA_ARRAY_EXPM1_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_EXPM1_HPP

#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/testing/testing.hpp"

#include <vector>
#include <array>

// lower testing precision for expm1
#undef NMTOOLS_TESTING_OUTPUT_PRECISION
#define NMTOOLS_TESTING_OUTPUT_PRECISION 1e-5

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(view, expm1)
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
            {std::expm1(0.f),std::expm1(1.f),std::expm1(2.f)},
            {std::expm1(3.f),std::expm1(4.f),std::expm1(5.f)},
            {std::expm1(6.f),std::expm1(7.f),std::expm1(8.f)},
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_EXPM1_HPP