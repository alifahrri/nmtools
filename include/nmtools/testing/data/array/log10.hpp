#ifndef NMTOOLS_TESTING_DATA_ARRAY_LOG10_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_LOG10_HPP

#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/testing/testing.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(view, log10)
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
            {std::log10(1.f),std::log10(1.f),std::log10(2.f)},
            {std::log10(3.f),std::log10(4.f),std::log10(5.f)},
            {std::log10(6.f),std::log10(7.f),std::log10(8.f)},
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_LOG10_HPP