#ifndef NMTOOLS_TESTING_DATA_ARRAY_TAN_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_TAN_HPP

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

NMTOOLS_TESTING_DECLARE_CASE(view, tan)
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
            {std::tan(0.f),std::tan(1.f),std::tan(2.f)},
            {std::tan(3.f),std::tan(4.f),std::tan(5.f)},
            {std::tan(6.f),std::tan(7.f),std::tan(8.f)},
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_TAN_HPP