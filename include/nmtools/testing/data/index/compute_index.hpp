#ifndef NMTOOLS_TESTING_DATA_INDEX_COMPUTE_INDEX_HPP
#define NMTOOLS_TESTING_DATA_INDEX_COMPUTE_INDEX_HPP

#include "nmtools/testing/testing.hpp"

NMTOOLS_TESTING_DECLARE_CASE(index, compute_index)
{
    using namespace nmtools::literals;

    // case1: all none → indices[i_i]
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int indices[3] = {0,1,2};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        inline int si = 5;
        inline auto start = nmtools::None;
        inline auto stop  = nmtools::None;
        inline auto step  = nmtools::None;
        inline int i_i = 0;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result = 0;
    }

    // case2: start=int, stop=none, step=none, positive start
    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int indices[3] = {0,1,2};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        inline int si = 5;
        inline int start = 2;
        inline auto stop  = nmtools::None;
        inline auto step  = nmtools::None;
        inline int i_i = 1;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result = 3;
    }

    // case3: start=int, stop=int, step=none, both positive
    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int indices[3] = {0,1,2};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        inline int si = 5;
        inline int start = 1;
        inline int stop  = 4;
        inline auto step  = nmtools::None;
        inline int i_i = 0;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result = 1;
    }

    // case4: all int, positive
    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int indices[3] = {0,1,2};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        inline int si = 5;
        inline int start = 1;
        inline int stop  = 4;
        inline int step  = 2;
        inline int i_i = 1;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result = 3;
    }

    // case5: start=none, stop=int, step=none
    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int indices[3] = {0,1,2};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        inline int si = 5;
        inline auto start = nmtools::None;
        inline int stop  = 4;
        inline auto step  = nmtools::None;
        inline int i_i = 0;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int result = 0;
    }

    // case6: start=none, stop=int, step=int, positive
    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int indices[3] = {0,1,2};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        inline int si = 5;
        inline auto start = nmtools::None;
        inline int stop  = 4;
        inline int step  = 2;
        inline int i_i = 1;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int result = 2;
    }

    // case7: start=none, stop=none, step=int negative
    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int indices[3] = {0,1,2};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        inline int si = 5;
        inline auto start = nmtools::None;
        inline auto stop  = nmtools::None;
        inline int step  = -1;
        inline int i_i = 0;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int result = 4;
    }

    // case8: start=none, stop=none, step=int negative, higher index
    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline int indices[3] = {0,1,2};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        inline int si = 5;
        inline auto start = nmtools::None;
        inline auto stop  = nmtools::None;
        inline int step  = -1;
        inline int i_i = 2;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline int result = 2;
    }

    // case9: start=int, stop=none, step=int positive
    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        inline int indices[3] = {0,1,2};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        inline int si = 8;
        inline int start = 3;
        inline auto stop  = nmtools::None;
        inline int step  = 2;
        inline int i_i = 1;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline int result = 5;
    }

    // case10: start=int, stop=none, step=int negative
    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        inline int indices[3] = {0,1,2};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        inline int si = 5;
        inline int start = 4;
        inline auto stop  = nmtools::None;
        inline int step  = -1;
        inline int i_i = 2;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline int result = 2;
    }

    // case11: all int, negative step, both positive start/stop
    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        inline int indices[3] = {0,1,2};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        inline int si = 5;
        inline int start = 1;
        inline int stop  = 4;
        inline int step  = -1;
        inline int i_i = 0;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        inline int result = 3;
    }

    // case12: all int, negative start, positive step
    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        inline int indices[3] = {0,1,2};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        inline int si = 5;
        inline int start = -2;
        inline int stop  = 4;
        inline int step  = 1;
        inline int i_i = 0;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        inline int result = 2;
    }
}

#endif // NMTOOLS_TESTING_DATA_INDEX_COMPUTE_INDEX_HPP
