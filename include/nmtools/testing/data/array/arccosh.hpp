#ifndef NMTOOLS_TESTING_DATA_ARRAY_ARCCOSH_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_ARCCOSH_HPP

#include "nmtools/ndarray/dynamic.hpp"
#include "nmtools/ndarray/hybrid.hpp"
#include "nmtools/ndarray/fixed.hpp"
#include "nmtools/testing/testing.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(view, arccosh)
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
            {std::acosh(1.f),std::acosh(1.f),std::acosh(2.f)},
            {std::acosh(3.f),std::acosh(4.f),std::acosh(5.f)},
            {std::acosh(6.f),std::acosh(7.f),std::acosh(8.f)},
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_ARCCOSH_HPP