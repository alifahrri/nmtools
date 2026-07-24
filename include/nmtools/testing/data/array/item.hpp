#ifndef NMTOOLS_TESTING_DATA_ARRAY_ITEM_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_ITEM_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(array,item)
{
    using namespace literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int a[1] = {42};
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result = 42;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1b)
    {
        inline int a[1][1] = {{42}};
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1b)
    {
        inline int result = 42;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1c)
    {
        inline int a = 42;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1c)
    {
        inline int result = 42;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1d)
    {
        inline int a[1] = {42};
        NMTOOLS_CAST_ARRAYS(a)

        inline int a_num = 42;

        inline auto a_e1 = to_either(a_a,a_num,0);
        inline auto a_e2 = to_either(a_a,a_num,1);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1d)
    {
        inline int result = 42;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int a[3][3] = {
            {0,1,2},
            {3,4,5},
            {6,7,8},
        };
        inline int idx = 3;
        inline auto idx_ct = 3_ct;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result = 3;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2b)
    {
        inline int a[3][3] = {
            {0,1,2},
            {3,4,5},
            {6,7,8},
        };
        inline int idx = 9;
        inline auto idx_ct = 9_ct;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2b)
    {
        inline auto result = Nothing;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int a[3][3] = {
            {0,1,2},
            {3,4,5},
            {6,7,8},
        };
        inline int idx = 7;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result = 7;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int a[2][3] = {
            {0,1,2},
            {3,4,5},
        };
        inline int idx[2] = {0,1};
        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_INDEX_ARRAYS(idx)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result = 1;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4b)
    {
        inline int a[2][3] = {
            {0,1,2},
            {3,4,5},
        };
        inline int idx[3] = {0,1,0};
        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_INDEX_ARRAYS(idx)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4b)
    {
        inline auto result = Nothing;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int a[2][3] = {
            {0,1,2},
            {3,4,5},
        };
        inline int idx[2] = {1,2};
        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_INDEX_ARRAYS(idx)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int result = 5;
    }

#ifndef NMTOOLS_TESTING_MINIMIZE_FOOTPRINT
    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        inline int idx[3] = {1,2,1};
        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_INDEX_ARRAYS(idx)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int result = 11;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        inline int idx[3] = {0,2,0};
        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_INDEX_ARRAYS(idx)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int result = 4;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline float a[2][3] = {
            {0.5,1.5,2.5},
            {3.5,4.5,5.5},
        };
        inline int idx = 4;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline float result = 4.5;
    }
#endif // NMTOOLS_TESTING_MINIMIZE_FOOTPRINT
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_ITEM_HPP
