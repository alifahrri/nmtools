#ifndef NMTOOLS_TESTING_DATA_ARRAY_LOGICAL_AND_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_LOGICAL_AND_HPP

#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/testing/testing.hpp"

#include <vector>
#include <array>
#include <algorithm> // std::max

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(view, logical_and)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline bool a[3][3] = {
            { true, false,  true},
            {false,  true, false},
            { true, false,  true},
        };
        inline bool b[3] = {false,true,true};
        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int shape[2] = {3,3};
        inline bool result[3][3] = {
            { true && false, false && true,  true && true},
            {false && false,  true && true, false && true},
            { true && false, false && true,  true && true},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline bool a[3][3] = {
            { true, false,  true},
            {false,  true, false},
            { true, false,  true},
        };
        inline bool b = true;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int shape[2] = {3,3};
        inline bool result[3][3] = {
            { true && true, false && true,  true && true},
            {false && true,  true && true, false && true},
            { true && true, false && true,  true && true},
        };
    }
}

NMTOOLS_TESTING_DECLARE_CASE(view, reduce_logical_and)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
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
            },
        };
        inline int axis = 0;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int shape[2] = {3,2};
        inline bool result[3][2] = {
            {false, true},
            { true, true},
            { true, true},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
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
            },
        };
        inline int axis = 1;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int shape[2] = {2,2};
        inline bool result[2][2] = {
            {false, true},
            { true, true},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
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
            },
        };
        inline int axis = 2;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int shape[2] = {2,3};
        inline bool result[2][3] = {
            {false, true, true},
            { true, true, true},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
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
            },
        };
        inline int axis[2] = {0,1};
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int shape[1] = {2};
        inline bool result[2] = {false, true};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
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
            },
        };
        inline int axis[2] = {0,2};
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int shape[1] = {3};
        inline bool result[3] = {false, true, true};
    }

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
            },
        };
        inline int axis[2] = {1,2};
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int shape[1] = {2};
        inline bool result[2] = {false,true};
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_LOGICAL_AND_HPP