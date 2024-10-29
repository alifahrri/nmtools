#ifndef NMTOOLS_TESTING_DATA_ARRAY_ONES_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_ONES_HPP

#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/dtypes.hpp"
#include "nmtools/constants.hpp"
#include "nmtools/testing/testing.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(array, ones)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int shape[3] = {2,3,2};
        inline auto dtype = float32;
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        using namespace nmtools::literals;
        inline auto shape_ct = nmtools_tuple{2_ct,3_ct,2_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline float result[2][3][2] = {
            {
                {1, 1},
                {1, 1},
                {1, 1},
            },
            {
                {1, 1},
                {1, 1},
                {1, 1},
            },
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_ONES_HPP