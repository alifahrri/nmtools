#ifndef NMTOOLS_TESTING_DATA_INDEX_COMPUTE_STEP_HPP
#define NMTOOLS_TESTING_DATA_INDEX_COMPUTE_STEP_HPP

#include "nmtools/testing/testing.hpp"

NMTOOLS_TESTING_DECLARE_CASE(index, compute_step)
{
    using namespace nmtools::literals;

    // case1: none → 1
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline auto step = nmtools::None;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result = 1;
    }

    // case2: positive int → abs(step)
    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int step = 2;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result = 2;
    }

    // case3: negative int → abs(step)
    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int step = -3;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result = 3;
    }

    // case4: zero → 0
    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int step = 0;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result = 0;
    }
}

#endif // NMTOOLS_TESTING_DATA_INDEX_COMPUTE_STEP_HPP
