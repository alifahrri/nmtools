#ifndef NMTOOLS_TESTING_DATA_ARRAY_POWER_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_POWER_HPP

#include "nmtools/ndarray/dynamic.hpp"
#include "nmtools/ndarray/hybrid.hpp"
#include "nmtools/ndarray/fixed.hpp"
#include "nmtools/testing/testing.hpp"

#include <vector>
#include <array>
#include <tuple>

namespace nm = nmtools;
namespace na = nmtools;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(view, power)
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
            {1, 1,  4},
            {1, 4, 25},
            {1, 7, 64},
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
            {0*0,1*1,2*2},
            {3*3,4*4,5*5},
            {6*6,7*7,8*8},
        };
    }
}

NMTOOLS_TESTING_DECLARE_CASE(view, reduce_power)
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
            {      0,       1},
            {    256,   19683},
            {1048576,48828125},
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
        inline auto dtype = float64;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int shape[2] = {2,2};
        inline long double result[2][2] = {
            {0,1},
            {std::pow(std::pow(6,8),10),std::pow(std::pow(7,9),11)},
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
        // must provide dtype for correct result
        inline auto dtype = uint64;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int shape[2] = {2,3};
        inline uint64_t result[2][3] = {
            {     0,        8,        1024},
            {279936,134217728,100000000000},
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
        inline int axis = 2;
        inline auto dtype = None;
        inline auto initial = 1;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int shape[2] = {2,3};
        inline int result[2][3] = {
            {1,1,1},
            {1,1,1},
        };
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
        inline int axis = 0;
        inline auto dtype = None;
        inline auto initial = 0;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int shape[2] = {3,2};
        inline int result[3][2] = {
            {1,0},
            {0,0},
            {0,0},
        };
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
        inline int axis = 0;
        inline auto dtype = None;
        inline auto initial = None;
        inline auto keepdims = True;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int shape[3] = {1,3,2};
        inline int result[1][3][2] = {
            {
                {      0,       1},
                {    256,   19683},
                {1048576,48828125},
            }
        };
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
            },
        };
        inline int axis = 1;
        inline auto dtype = float64;
        inline auto initial = None;
        inline auto keepdims = False;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int shape[2] = {2,2};
        inline long double result[2][2] = {
            {0,1},
            {std::pow(std::pow(6,8),10),std::pow(std::pow(7,9),11)},
        };
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
        inline int axis = 2;
        // must provide dtype for correct result
        inline auto dtype = uint64;
        inline auto initial = None;
        inline auto keepdims = true;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline int shape[3] = {2,3,1};
        inline uint64_t result[2][3][1] = {
            {{     0},{        8},{        1024}},
            {{279936},{134217728},{100000000000}},
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
        inline int axis = 2;
        inline auto dtype = None;
        inline auto initial = 1;
        inline auto keepdims = false;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline int shape[2] = {2,3};
        inline int result[2][3] = {
            {1,1,1},
            {1,1,1},
        };
    }
}

NMTOOLS_TESTING_DECLARE_CASE(view, accumulate_power)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline long long int a[2][3][2] = {
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
        inline long long int result[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {      0,       1},
                {    256,   19683},
                {1048576,48828125}
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline long long int a[2][3][2] = {
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
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int shape[3] = {2,3,2};
        inline uint64_t result[2][3][2] = {
            {
                {0,   0},
                {2,   8},
                {4,1024},
            },
            {
                { 6,      279936},
                { 8,   134217728},
                {10,100000000000}
            }
        };
    }
}

NMTOOLS_TESTING_DECLARE_CASE(view, outer_power)
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
       {{{     0,      0,      0},
        {     1,      1,      1},
        {    64,    128,    256}},

       {{   729,   2187,   6561},
        {  4096,  16384,  65536},
        { 15625,  78125, 390625}}};
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_POWER_HPP