#ifndef NMTOOLS_TESTING_DATA_ARRAY_MINIMUM_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_MINIMUM_HPP

#include "nmtools/ndarray/dynamic.hpp"
#include "nmtools/ndarray/hybrid.hpp"
#include "nmtools/ndarray/fixed.hpp"
#include "nmtools/testing/testing.hpp"

#include <vector>
#include <array>
#include <algorithm> // std::min

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(view, minimum)
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
            {std::min(0,0),std::min(1,1),std::min(2,2)},
            {std::min(3,0),std::min(4,1),std::min(5,2)},
            {std::min(6,0),std::min(7,1),std::min(8,2)},
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
            {std::min(0,2),std::min(1,2),std::min(2,2)},
            {std::min(3,2),std::min(4,2),std::min(5,2)},
            {std::min(6,2),std::min(7,2),std::min(8,2)},
        };
    }
}

NMTOOLS_TESTING_DECLARE_CASE(view, reduce_minimum)
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
        inline int result[3][2] = {
            {0,1},
            {2,3},
            {4,5},
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
        inline int result[2][2] = {
            {0,1},
            {6,7},
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
        inline int result[2][3] = {
            {0,2, 4},
            {6,8,10},
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
        inline int result[2] = {0,1};
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
        inline int result[3] = {0,2,4};
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
        inline int result[2] = {0,6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline uint8_t a[2][3][2] = {
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
        inline auto dtype = uint32;
        inline auto initial = 256;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int shape[1] = {2};
        inline int result[2] = {0,6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
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
        inline auto dtype = None;
        inline auto initial = None;
        inline auto keepdims = True;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline int shape[3] = {1,3,2};
        inline int result[1][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
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
        inline auto dtype = None;
        inline auto initial = None;
        inline auto keepdims = False;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline int shape[2] = {2,2};
        inline int result[2][2] = {
            {0,1},
            {6,7},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
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
        inline auto dtype = None;
        inline auto initial = None;
        inline auto keepdims = true;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline int shape[3] = {2,3,1};
        inline int result[2][3][1] = {
            {{0},{2},{ 4}},
            {{6},{8},{10}},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
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
        inline auto dtype = None;
        inline auto initial = None;
        inline auto keepdims = false;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        inline int shape[1] = {2};
        inline int result[2] = {0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12)
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
        inline auto dtype = None;
        inline auto initial = None;
        inline auto keepdims = true;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        inline int shape[3] = {1,3,1};
        inline int result[1][3][1] = {
            {{0},{2},{4}}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case13)
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
        inline auto axis = None;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case13)
    {
        inline auto shape = None;
        inline int result = 0;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case14)
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
        inline auto axis = None;
        inline auto initial = -1;
        inline auto keepdims = False; 
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case14)
    {
        inline auto shape = None;
        inline int result = -1;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case15)
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
        inline auto axis = None;
        inline auto initial = -1;
        inline auto keepdims = True; 
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case15)
    {
        inline int shape[3] = {1,1,1};
        inline int result[1][1][1] = {{{-1}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case16)
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
        inline auto axis = None;
        inline auto initial = -1;
        inline auto keepdims = false;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case16)
    {
        inline auto shape = None;
        inline int result = -1;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case17)
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
        inline auto axis = None;
        inline auto initial = -1;
        inline auto keepdims = true; 
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case17)
    {
        inline int shape[3] = {1,1,1};
        inline int result[1][1][1] = {{{-1}}};
    }
}

NMTOOLS_TESTING_DECLARE_CASE(view, accumulate_minimum)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline float a[2][3][2] = {
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
        inline int shape[3] = {2,3,2};
        inline float result[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {0,1},
                {2,3},
                {4,5},
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline float a[2][3][2] = {
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
        inline int shape[3] = {2,3,2};
        inline float result[2][3][2] = {
            {
                {0,1},
                {0,1},
                {0,1},
            },
            {
                {6,7},
                {6,7},
                {6,7},
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline float a[2][3][2] = {
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
        inline int shape[3] = {2,3,2};
        inline float result[2][3][2] = {
            {
                {0,0},
                {2,2},
                {4,4},
            },
            {
                { 6, 6},
                { 8, 8},
                {10,10},
            },
        };
    }
}

NMTOOLS_TESTING_DECLARE_CASE(view, outer_minimum)
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
        {1, 1, 1},
        {2, 2, 2}},

       {{3, 3, 3},
        {4, 4, 4},
        {5, 5, 5}}};
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_MINIMUM_HPP