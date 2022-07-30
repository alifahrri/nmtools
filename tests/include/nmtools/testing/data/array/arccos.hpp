#ifndef NMTOOLS_TESTING_DATA_ARRAY_ARCCOS_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_ARCCOS_HPP

#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/testing/testing.hpp"

#include <vector>
#include <array>
#include <cmath>

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(view, arccos)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline float a[3][3] = {
            {0.0,0.1,0.2},
            {0.3,0.4,0.5},
            {0.6,0.7,0.8},
        };
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int shape[2] = {3,3};
        inline float result[3][3] = {
            {std::acos(0.0f),std::acos(0.1f),std::acos(0.2f)},
            {std::acos(0.3f),std::acos(0.4f),std::acos(0.5f)},
            {std::acos(0.6f),std::acos(0.7f),std::acos(0.8f)},
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_ARCCOS_HPP