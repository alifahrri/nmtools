#ifndef NMTOOLS_TESTING_DATA_ARRAY_WHERE_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_WHERE_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(view, where)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline bool condition[10] = {true, true, true, true, true, false, false, false, false, false};
        inline int8_t x[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        inline int8_t y[10] = {0,10,20,30,40,50,60,70,80,90};
        NMTOOLS_CAST_ARRAYS(condition)
        NMTOOLS_CAST_ARRAYS(x)
        NMTOOLS_CAST_ARRAYS(y)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int8_t dim = 1;
        inline int8_t shape[1] = {10};
        inline int8_t result[10] = {0, 1, 2, 3, 4, 50, 60, 70, 80, 90};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline bool condition[3][4] = {
            {false,  true,  true, true},
            {false, false,  true, true},
            {false, false, false, true},
        };
        inline int8_t x[3][1] = {
            {0},
            {1},
            {2},
        };
        inline int8_t y[1][4] = {{10,11,12,13}};
        NMTOOLS_CAST_ARRAYS(condition)
        NMTOOLS_CAST_ARRAYS(x)
        NMTOOLS_CAST_ARRAYS(y)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int8_t dim = 2;
        inline int8_t shape[2] = {3,4};
        inline int8_t result[3][4] = {
            {10,  0,  0, 0},
            {10, 11,  1, 1},
            {10, 11, 12, 2},
        };
    }

#ifndef NMTOOLS_TESTING_MINIMIZE_FOOTPRINT
    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline bool condition[3][4] = {
            {false,  true,  true, true},
            {false, false,  true, true},
            {false, false, false, true},
        };
        inline int8_t x[1][3][1] = {
            {
                {0},
                {1},
                {2},
            }
        };
        inline int8_t y[1][4] = {{10,11,12,13}};
        NMTOOLS_CAST_ARRAYS(condition)
        NMTOOLS_CAST_ARRAYS(x)
        NMTOOLS_CAST_ARRAYS(y)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int8_t dim = 3;
        inline int8_t shape[3] = {1,3,4};
        inline int8_t result[1][3][4] = {
            {
                {10,  0,  0, 0},
                {10, 11,  1, 1},
                {10, 11, 12, 2},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1b)
    {
        inline int8_t condition[10] = {1, 1, 1, 1, 1, 0, 0, 0, 0, 0};
        inline int8_t x[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        inline int8_t y[10] = {0,10,20,30,40,50,60,70,80,90};
        NMTOOLS_CAST_ARRAYS(condition)
        NMTOOLS_CAST_ARRAYS(x)
        NMTOOLS_CAST_ARRAYS(y)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1b)
    {
        inline int8_t dim = 1;
        inline int8_t shape[1] = {10};
        inline int8_t result[10] = {0, 1, 2, 3, 4, 50, 60, 70, 80, 90};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2b)
    {
        inline int8_t condition[3][4] = {
            {0, 1, 1, 1},
            {0, 0, 1, 1},
            {0, 0, 0, 1},
        };
        inline int8_t x[3][1] = {
            {0},
            {1},
            {2},
        };
        inline int8_t y[1][4] = {{10,11,12,13}};
        NMTOOLS_CAST_ARRAYS(condition)
        NMTOOLS_CAST_ARRAYS(x)
        NMTOOLS_CAST_ARRAYS(y)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2b)
    {
        inline int8_t dim = 2;
        inline int8_t shape[2] = {3,4};
        inline int8_t result[3][4] = {
            {10,  0,  0, 0},
            {10, 11,  1, 1},
            {10, 11, 12, 2},
        };
    }

    
    NMTOOLS_TESTING_DECLARE_ARGS(case3b)
    {
        inline int8_t condition[3][4] = {
            {0, 1, 1, 1},
            {0, 0, 1, 1},
            {0, 0, 0, 1},
        };
        inline int8_t x[1][3][1] = {
            {
                {0},
                {1},
                {2},
            }
        };
        inline int8_t y[1][4] = {{10,11,12,13}};
        NMTOOLS_CAST_ARRAYS(condition)
        NMTOOLS_CAST_ARRAYS(x)
        NMTOOLS_CAST_ARRAYS(y)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3b)
    {
        inline int8_t dim = 3;
        inline int8_t shape[3] = {1,3,4};
        inline int8_t result[1][3][4] = {
            {
                {10,  0,  0, 0},
                {10, 11,  1, 1},
                {10, 11, 12, 2},
            }
        };
    }
#endif
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_WHERE_HPP