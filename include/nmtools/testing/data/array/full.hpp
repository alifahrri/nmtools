#ifndef NMTOOLS_TESTING_DATA_ARRAY_FULL_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_FULL_HPP

#include "nmtools/ndarray/dynamic.hpp"
#include "nmtools/ndarray/hybrid.hpp"
#include "nmtools/ndarray/fixed.hpp"
#include "nmtools/constants.hpp"
#include "nmtools/testing/testing.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nmtools;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(array, full)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int shape[3] = {2,3,2};
        inline float fill_value = 3.14;
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        using namespace nmtools::literals;
        inline auto shape_ct = nmtools_tuple{2_ct,3_ct,2_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline float result[2][3][2] = {
            {
                {3.14, 3.14},
                {3.14, 3.14},
                {3.14, 3.14},
            },
            {
                {3.14, 3.14},
                {3.14, 3.14},
                {3.14, 3.14},
            },
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_FULL_HPP