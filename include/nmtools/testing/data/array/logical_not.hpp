#ifndef NMTOOLS_TESTING_DATA_ARRAY_LOGICAL_NOT_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_LOGICAL_NOT_HPP

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

NMTOOLS_TESTING_DECLARE_CASE(view, logical_not)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline nm_bool_t a[3][3] = {
            { true, false,  true},
            {false,  true, false},
            { true, false,  true},
        };
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int shape[2] = {3,3};
        inline nm_bool_t result[3][3] = {
            { !true, !false,  !true},
            {!false,  !true, !false},
            { !true, !false,  !true},
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_LOGICAL_NOT_HPP