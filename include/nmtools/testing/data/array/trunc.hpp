#ifndef NMTOOLS_TESTING_DATA_ARRAY_TRUNC_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_TRUNC_HPP

#include "nmtools/ndarray/dynamic.hpp"
#include "nmtools/ndarray/hybrid.hpp"
#include "nmtools/ndarray/fixed.hpp"
#include "nmtools/testing/testing.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(view, trunc)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline float a[3][3] = {
            {1.0,2.1,3.2},
            {1.3,2.4,3.5},
            {1.6,2.7,3.8},
        };
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int shape[2] = {3,3};
        inline float result[3][3] = {
            {std::trunc(1.0f),std::trunc(2.1f),std::trunc(3.2f)},
            {std::trunc(1.3f),std::trunc(2.4f),std::trunc(3.5f)},
            {std::trunc(1.6f),std::trunc(2.7f),std::trunc(3.8f)},
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_TRUNC_HPP