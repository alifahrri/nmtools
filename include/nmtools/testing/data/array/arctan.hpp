#ifndef NMTOOLS_TESTING_DATA_ARRAY_ARCTAN_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_ARCTAN_HPP

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

NMTOOLS_TESTING_DECLARE_CASE(view, arctan)
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
            {std::atan(0.0f),std::atan(0.1f),std::atan(0.2f)},
            {std::atan(0.3f),std::atan(0.4f),std::atan(0.5f)},
            {std::atan(0.6f),std::atan(0.7f),std::atan(0.8f)},
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_ARCTAN_HPP