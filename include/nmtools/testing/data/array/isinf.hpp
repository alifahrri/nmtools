#ifndef NMTOOLS_TESTING_DATA_ARRAY_ISINF_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_ISINF_HPP

#include "nmtools/ndarray/dynamic.hpp"
#include "nmtools/ndarray/hybrid.hpp"
#include "nmtools/ndarray/fixed.hpp"
#include "nmtools/testing/testing.hpp"

#include <vector>
#include <array>
#include <algorithm> // std::max

namespace nm = nmtools;
namespace na = nmtools;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(view, isinf)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline double a[3][3] = {
            { 0.1, INFINITY, 0.3 },
            { NAN,    NAN,   NAN },
            { 0.1, INFINITY, 0.3 },
        };
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int shape[2] = {3,3};
        inline nm_bool_t result[3][3] = {
            { std::isinf(0.1), std::isinf(INFINITY), std::isinf(0.3) },
            { std::isinf(NAN), std::isinf(   NAN  ), std::isinf(NAN) },
            { std::isinf(0.1), std::isinf(INFINITY), std::isinf(0.3) },
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_ISINF_HPP