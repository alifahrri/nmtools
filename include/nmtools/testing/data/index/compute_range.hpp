#ifndef NMTOOLS_TESTING_DATA_INDEX_COMPUTE_RANGE_HPP
#define NMTOOLS_TESTING_DATA_INDEX_COMPUTE_RANGE_HPP

#include "nmtools/testing/testing.hpp"

NMTOOLS_TESTING_DECLARE_CASE(index, compute_range)
{
    using namespace nmtools::literals;

    // case1: all none → si
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int si = 5;
        inline auto start = nmtools::None;
        inline auto stop  = nmtools::None;
        inline auto step  = nmtools::None;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result = 5;
    }

    // case2: start=int, stop=none, step=none → si - start
    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int si = 5;
        inline int start = 2;
        inline auto stop  = nmtools::None;
        inline auto step  = nmtools::None;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result = 3;
    }

    // case3: start=none, stop=int, step=none → stop
    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int si = 5;
        inline auto start = nmtools::None;
        inline int stop  = 3;
        inline auto step  = nmtools::None;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result = 3;
    }

    // case4: start=none, stop=negative, step=none → si + stop
    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int si = 5;
        inline auto start = nmtools::None;
        inline int stop  = -2;
        inline auto step  = nmtools::None;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result = 3;
    }

    // case5: both positive, stop > start → abs(stop - start)
    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int si = 5;
        inline int start = 1;
        inline int stop  = 4;
        inline auto step  = nmtools::None;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int result = 3;
    }

    // case6: start positive, stop negative → (si - abs(stop)) - start
    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int si = 5;
        inline int start = 1;
        inline int stop  = -1;
        inline auto step  = nmtools::None;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int result = 3;
    }

    // case7: both negative → (si - abs(stop)) - (si - abs(start))
    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int si = 5;
        inline int start = -3;
        inline int stop  = -1;
        inline auto step  = nmtools::None;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int result = 2;
    }

    // case8: start negative, stop positive → stop - (si - abs(start))
    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline int si = 5;
        inline int start = -3;
        inline int stop  = 3;
        inline auto step  = nmtools::None;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline int result = 1;
    }

    // case9: start=int, stop=none, step=int(negative) → start+1
    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        inline int si = 5;
        inline int start = 2;
        inline auto stop  = nmtools::None;
        inline int step  = -1;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline int result = 3;
    }

    // case10: start=int, stop=none, step=int(positive) → si-start
    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        inline int si = 5;
        inline int start = 2;
        inline auto stop  = nmtools::None;
        inline int step  = 1;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline int result = 3;
    }

    // case11: larger si
    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        inline int si = 8;
        inline int start = 3;
        inline int stop  = 6;
        inline auto step  = nmtools::None;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        inline int result = 3;
    }

    // case12: start=none, stop=si (clamped)
    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        inline int si = 5;
        inline auto start = nmtools::None;
        inline int stop  = 10;
        inline auto step  = nmtools::None;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        inline int result = 5;
    }
}

#endif // NMTOOLS_TESTING_DATA_INDEX_COMPUTE_RANGE_HPP
