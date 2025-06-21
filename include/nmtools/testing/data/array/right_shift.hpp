#ifndef NMTOOLS_TESTING_DATA_ARRAY_RIGHT_SHIFT_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_RIGHT_SHIFT_HPP

#include "nmtools/ndarray/dynamic.hpp"
#include "nmtools/ndarray/hybrid.hpp"
#include "nmtools/ndarray/fixed.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nmtools;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(view, right_shift)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int a[3][3] = {
            {0,1,2},
            {3,4,5},
            {6,7,8},
        };
        inline int b[3] = {0,1,2};
        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int shape[2] = {3,3};
        inline int result[3][3] = {
            {0 >> 0, 1 >> 1, 2 >> 2},
            {3 >> 0, 4 >> 1, 5 >> 2},
            {6 >> 0, 7 >> 1, 8 >> 2},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int a[3][3] = {
            {0,1,2},
            {3,4,5},
            {6,7,8},
        };
        inline int b = 2;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int shape[2] = {3,3};
        inline int result[3][3] = {
            {0 >> 2, 1 >> 2, 2 >> 2},
            {3 >> 2, 4 >> 2, 5 >> 2},
            {6 >> 2, 7 >> 2, 8 >> 2},
        };
    }
}

NMTOOLS_TESTING_DECLARE_CASE(view, reduce_right_shift)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int a[2][3][2] = {
            {
                {11,10},
                { 9, 8},
                { 7, 6},
            },
            {
                {5,4},
                {3,2},
                {1,0},
            },
        };
        inline int axis = 0;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int shape[2] = {3,2};
        inline int result[3][2] = {
            {0,0},
            {1,2},
            {3,6},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int a[2][3][2] = {
            {
                {11,10},
                { 9, 8},
                { 7, 6},
            },
            {
                {5,4},
                {3,2},
                {1,0},
            },
        };
        inline int axis = 1;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int shape[2] = {2,2};
        inline int result[2][2] = {
            {0,0},
            {0,1},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int a[2][3][2] = {
            {
                {11,10},
                { 9, 8},
                { 7, 6},
            },
            {
                {5,4},
                {3,2},
                {1,0},
            },
        };
        inline int axis = 2;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int shape[2] = {2,3};
        inline int result[2][3] = {
            {0,0,0},
            {0,0,1},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int a[2][3][2] = {
            {
                {11,10},
                { 9, 8},
                { 7, 6},
            },
            {
                {5,4},
                {3,2},
                {1,0},
            },
        };
        inline int axis = 2;
        inline auto dtype = int32;
        inline auto initial = 256;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int shape[2] = {2,3};
        inline int result[2][3] = {
            { 0,0,  0},
            { 0,8,128},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int a[2][3][2] = {
            {
                {11,10},
                { 9, 8},
                { 7, 6},
            },
            {
                {5,4},
                {3,2},
                {1,0},
            },
        };
        inline int axis = 0;
        inline auto dtype = None;
        inline auto initial = None;
        inline auto keepdims = True;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int shape[3] = {1,3,2};
        inline int result[1][3][2] = {
            {
                {0,0},
                {1,2},
                {3,6},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int a[2][3][2] = {
            {
                {11,10},
                { 9, 8},
                { 7, 6},
            },
            {
                {5,4},
                {3,2},
                {1,0},
            },
        };
        inline int axis = 1;
        inline auto dtype = None;
        inline auto initial = None;
        inline auto keepdims = False;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int shape[2] = {2,2};
        inline int result[2][2] = {
            {0,0},
            {0,1},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int a[2][3][2] = {
            {
                {11,10},
                { 9, 8},
                { 7, 6},
            },
            {
                {5,4},
                {3,2},
                {1,0},
            },
        };
        inline int axis = 2;
        inline auto dtype = None;
        inline auto initial = None;
        inline auto keepdims = true;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int shape[3] = {2,3,1};
        inline int result[2][3][1] = {
            {{0},{0},{0}},
            {{0},{0},{1}},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline int a[2][3][2] = {
            {
                {11,10},
                { 9, 8},
                { 7, 6},
            },
            {
                {5,4},
                {3,2},
                {1,0},
            },
        };
        inline int axis = 2;
        inline auto dtype = int32;
        inline auto initial = 256;
        inline auto keepdims = false;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline int shape[2] = {2,3};
        inline int result[2][3] = {
            { 0,0,  0},
            { 0,8,128},
        };
    }
}

NMTOOLS_TESTING_DECLARE_CASE(view, accumulate_right_shift)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int a[2][3][2] = {
            {
                {11,10},
                { 9, 8},
                { 7, 6},
            },
            {
                {5,4},
                {3,2},
                {1,0},
            },
        };
        inline int axis = 0;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int shape[3] = {2,3,2};
        inline int result[2][3][2] = {
            {
                {11,10},
                { 9, 8},
                { 7, 6},
            },
            {
                {0,0},
                {1,2},
                {3,6},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int a[2][3][2] = {
            {
                {11,10},
                { 9, 8},
                { 7, 6},
            },
            {
                {5,4},
                {3,2},
                {1,0},
            },
        };
        inline int axis = 1;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int shape[3] = {2,3,2};
        inline int result[2][3][2] = {
            {
                {11,10},
                {0,0},
                {0,0},
            },
            {
                {5,4},
                {0,1},
                {0,1},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int a[2][3][2] = {
            {
                {11,10},
                { 9, 8},
                { 7, 6},
            },
            {
                {5,4},
                {3,2},
                {1,0},
            },
        };
        inline int axis = 2;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int shape[3] = {2,3,2};
        inline int result[2][3][2] = {
            {
                {11,0},
                { 9,0},
                { 7,0},
            },
            {
                {5,0},
                {3,0},
                {1,1},
            }
        };
    }
}

NMTOOLS_TESTING_DECLARE_CASE(view, outer_right_shift)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int a[2][3] = {
            {0,1,2},
            {3,4,5},
        };
        inline int b[3] = { 6,  7, 8};
        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int shape[3] = {2,3,3};
        inline int result[2][3][3] = \
       {{{0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}},

       {{0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}}};
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_RIGHT_SHIFT_HPP