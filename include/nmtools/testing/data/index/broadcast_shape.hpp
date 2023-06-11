#ifndef NMTOOLS_TESTING_DATA_INDEX_BROADCAST_SHAPE_HPP
#define NMTOOLS_TESTING_DATA_INDEX_BROADCAST_SHAPE_HPP

#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(broadcast_shape)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int a[2] = {5,4};
        inline int b[1] = {1};
        NMTOOLS_CAST_INDEX_ARRAYS(a)
        NMTOOLS_CAST_INDEX_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline bool success = true;
        inline int expected[2] = {5,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int a[1] = {1};
        inline int b[2] = {5,4};
        NMTOOLS_CAST_INDEX_ARRAYS(a)
        NMTOOLS_CAST_INDEX_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline bool success = true;
        inline int expected[2] = {5,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int a[1] = {4};
        inline int b[2] = {5,4};
        NMTOOLS_CAST_INDEX_ARRAYS(a)
        NMTOOLS_CAST_INDEX_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline bool success = true;
        inline int expected[2] = {5,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int a[4] = {8,1,6,1};
        inline int b[3] = {7,1,5};
        NMTOOLS_CAST_INDEX_ARRAYS(a)
        NMTOOLS_CAST_INDEX_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline bool success = true;
        inline int expected[4] = {8,7,6,5};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int a[3] = {256,256,3};
        inline int b[1] = {3};
        NMTOOLS_CAST_INDEX_ARRAYS(a)
        NMTOOLS_CAST_INDEX_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline bool success = true;
        inline int expected[3] = {256,256,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int a[1] = {5};
        inline int b[2] = {5,4};
        NMTOOLS_CAST_INDEX_ARRAYS(a)
        NMTOOLS_CAST_INDEX_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline bool success = false;
        inline int expected[2] = {0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int a[2] = {2,1};
        inline int b[3] = {8,4,3};
        NMTOOLS_CAST_INDEX_ARRAYS(a)
        NMTOOLS_CAST_INDEX_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline bool success = false;
        inline int expected[3] = {0,0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline int a[2] = {4,1};
        inline int b[3] = {8,1,3};
        inline int c[1] = {3};
        NMTOOLS_CAST_INDEX_ARRAYS(a)
        NMTOOLS_CAST_INDEX_ARRAYS(b)
        NMTOOLS_CAST_INDEX_ARRAYS(c)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline bool success = true;
        inline int expected[3] = {8,4,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        inline int a[2] = {4,1};
        inline int b[3] = {8,2,3};
        inline int c[1] = {3};
        NMTOOLS_CAST_INDEX_ARRAYS(a)
        NMTOOLS_CAST_INDEX_ARRAYS(b)
        NMTOOLS_CAST_INDEX_ARRAYS(c)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline bool success = false;
        inline int expected[3] = {8,4,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        inline int a[2] = {4,1};
        inline int b[3] = {8,1,3};
        inline int c[1] = {3};
        inline int d[6] = {2,2,3,1,4,1};
        NMTOOLS_CAST_INDEX_ARRAYS(a)
        NMTOOLS_CAST_INDEX_ARRAYS(b)
        NMTOOLS_CAST_INDEX_ARRAYS(c)
        NMTOOLS_CAST_INDEX_ARRAYS(d)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline bool success = true;
        inline int expected[6] = {2,2,3,8,4,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        inline int a[2] =         {4,1};
        inline int b[3] =       {8,1,3};
        inline int c[1] =           {3};
        inline int d[6] = {2,2,3,1,4,1};
        inline int e[1] =           {1};
        inline int f[4] =     {3,1,4,1};
        inline int g[6] = {2,1,1,1,1,1};
        NMTOOLS_CAST_INDEX_ARRAYS(a)
        NMTOOLS_CAST_INDEX_ARRAYS(b)
        NMTOOLS_CAST_INDEX_ARRAYS(c)
        NMTOOLS_CAST_INDEX_ARRAYS(d)
        NMTOOLS_CAST_INDEX_ARRAYS(e)
        NMTOOLS_CAST_INDEX_ARRAYS(f)
        NMTOOLS_CAST_INDEX_ARRAYS(g)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        inline bool success = true;
        inline int expected[6] = {2,2,3,8,4,3};
    }
}

#endif // NMTOOLS_TESTING_DATA_INDEX_BROADCAST_SHAPE_HPP