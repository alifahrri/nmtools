#ifndef NMTOOLS_TESTING_DATA_ARRAY_REPEAT_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_REPEAT_HPP

#include "nmtools/testing/array_cast.hpp"
#include "nmtools/testing/testing.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace view = nm::view;
namespace kind = na::kind;

using namespace nm::literals;

NMTOOLS_TESTING_DECLARE_CASE(array, repeat)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int array[2][2] = {{1,2},{3,4}};
        inline int repeats = 3;
        inline auto axis = None;
        inline auto repeats_ct = 3_ct;
        NMTOOLS_CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int shape[1] = {12};
        inline int dim = 1;
        inline int result[12] = {1,1,1,2,2,2,3,3,3,4,4,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int array[2][2] = {{1,2},{3,4}};
        inline int repeats = 2;
        inline auto axis = 0;
        inline auto repeats_ct = 2_ct;
        inline auto axis_ct    = 0_ct;
        NMTOOLS_CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int shape[2] = {4,2};
        inline int dim = 2;
        inline int result[4][2] = {
            {1,2},
            {1,2},
            {3,4},
            {3,4}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int array[2][2] = {{1,2},{3,4}};
        inline int repeats = 2;
        inline auto axis = 1;
        inline auto repeats_ct = 2_ct;
        inline auto axis_ct    = 1_ct;
        NMTOOLS_CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int shape[2] = {2,4};
        inline int dim = 2;
        inline int result[2][4] = {
            {1,1,2,2},
            {3,3,4,4}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int array[2][2] = {{1,2},{3,4}};
        inline auto repeats = nmtools_array{1,2};
        inline auto repeats_ct = nmtools_tuple{1_ct,2_ct};
        inline auto repeats_cl = to_clipped(repeats_ct);
        inline auto axis = 0;
        inline auto axis_ct = 0_ct;
        inline auto axis_cl = to_clipped(axis_ct);
        NMTOOLS_CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int shape[2] = {3,2};
        inline int dim = 2;
        inline int result[3][2] = {
            {1,2},
            {3,4},
            {3,4},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int array[2][2] = {{1,2},{3,4}};
        inline auto repeats = nmtools_array{1,2};
        inline auto repeats_ct = nmtools_tuple{1_ct,2_ct};
        inline auto repeats_cl = to_clipped(repeats_ct);
        inline auto axis = 1;
        inline auto axis_ct = 1_ct;
        NMTOOLS_CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int shape[2] = {2,3};
        inline int dim = 2;
        inline int result[2][3] = {
            {1,2,2},
            {3,4,4}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int array[1][2][2] = {{{1,2},{3,4}}};
        inline auto repeats = 2;
        inline auto repeats_ct = 2_ct;
        inline auto axis = 0;
        inline auto axis_ct = 0_ct;
        NMTOOLS_CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int shape[3] = {2,2,2};
        inline int dim = 3;
        inline int result[2][2][2] = {
            {
                {1,2},
                {3,4}
            },
            {
                {1,2},
                {3,4}
            },
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_REPEAT_HPP