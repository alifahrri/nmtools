#ifndef NMTOOLS_TESTING_DATA_ARRAY_ARANGE_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_ARANGE_HPP

#include "nmtools/ndarray/dynamic.hpp"
#include "nmtools/ndarray/hybrid.hpp"
#include "nmtools/ndarray/fixed.hpp"
#include "nmtools/dtypes.hpp"
#include "nmtools/testing/testing.hpp"

#include <vector>
#include <array>
#include <cmath>

namespace nm = nmtools;
namespace na = nmtools;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(array, arange)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int stop = 5;
        inline auto dtype = int32;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int shape[1] = {5};
        inline int result[5] = {0, 1, 2, 3, 4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int start = 1;
        inline int stop  = 5;
        inline auto dtype = int32;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int shape[1] = {4};
        inline int result[4] = {1, 2, 3, 4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int start = 1;
        inline int stop  = 5;
        inline int step  = 2;
        inline auto dtype = int32;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int shape[1] = {2};
        inline int result[2] = {1, 3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int start = 1;
        inline int stop  = 5;
        inline int step  = 3;
        inline auto dtype = int32;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int shape[1] = {2};
        inline int result[2] = {1, 4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int stop = 5;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int shape[1] = {5};
        inline int result[5] = {0, 1, 2, 3, 4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int start = 1;
        inline int stop  = 5;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int shape[1] = {4};
        inline int result[4] = {1, 2, 3, 4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int start = 1;
        inline int stop  = 5;
        inline int step  = 2;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int shape[1] = {2};
        inline int result[2] = {1, 3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline int start = 1;
        inline int stop  = 5;
        inline int step  = 3;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline int shape[1] = {2};
        inline int result[2] = {1, 4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        using namespace nmtools::literals;
        inline auto start = 1_ct;
        inline auto stop  = 5_ct;
        inline auto step  = 3_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline int shape[1] = {2};
        inline int result[2] = {1, 4};
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_ARANGE_HPP