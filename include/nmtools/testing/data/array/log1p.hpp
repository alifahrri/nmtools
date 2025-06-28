#ifndef NMTOOLS_TESTING_DATA_ARRAY_LOG1P_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_LOG1P_HPP

#include "nmtools/ndarray/dynamic.hpp"
#include "nmtools/ndarray/hybrid.hpp"
#include "nmtools/ndarray/fixed.hpp"
#include "nmtools/testing/testing.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nmtools;
namespace view = nm::view;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(view, log1p)
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
            {std::log1p(0.f),std::log1p(1.f),std::log1p(2.f)},
            {std::log1p(3.f),std::log1p(4.f),std::log1p(5.f)},
            {std::log1p(6.f),std::log1p(7.f),std::log1p(8.f)},
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_LOG1P_HPP