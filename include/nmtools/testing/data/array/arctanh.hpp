#ifndef NMTOOLS_TESTING_DATA_ARRAY_ARCTANH_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_ARCTANH_HPP

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

NMTOOLS_TESTING_DECLARE_CASE(view, arctanh)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline float a[3][3] = {
            {.1f,.1f,.2f},
            {.3f,.4f,.5f},
            {.6f,.7f,.8f},
        };
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int shape[2] = {3,3};
        inline float result[3][3] = {
            {std::atanh(.1f),std::atanh(.1f),std::atanh(.2f)},
            {std::atanh(.3f),std::atanh(.4f),std::atanh(.5f)},
            {std::atanh(.6f),std::atanh(.7f),std::atanh(.8f)},
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_ARCTANH_HPP