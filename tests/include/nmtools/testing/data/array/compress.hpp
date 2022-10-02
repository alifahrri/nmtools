#ifndef NMTOOLS_TESTING_DATA_ARRAY_COMPRESS_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_COMPRESS_HPP

#include "nmtools/array/ndarray.hpp"
#include "nmtools/testing/array_cast.hpp"
#include "nmtools/testing/testing.hpp"
#include "nmtools/constants.hpp"

NMTOOLS_TESTING_DECLARE_CASE(array, compress)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int condition[2] = {0,1};
        inline int array[3][2] = {
            {1,2},
            {3,4},
            {5,6},
        };
        inline int axis = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(condition)
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int shape[2] = {1,2};
        inline int result[1][2] = {
            {3,4}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int condition[2] = {0,1};
        inline int array[3][2] = {
            {1,2},
            {3,4},
            {5,6},
        };
        inline int axis = 1;
        NMTOOLS_CAST_INDEX_ARRAYS(condition)
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int shape[2] = {3,1};
        inline int result[3][1] = {
            {2},
            {4},
            {6},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline bool condition[3] = {false,true,true};
        inline int array[3][2] = {
            {1,2},
            {3,4},
            {5,6},
        };
        inline int axis = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(condition)
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int shape[2] = {2,2};
        inline int result[2][2] = {
            {3,4},
            {5,6},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline bool condition[5] = {false,true,true,false,true};
        inline int array[3][2] = {
            {1,2},
            {3,4},
            {5,6},
        };
        inline auto axis = None;
        NMTOOLS_CAST_INDEX_ARRAYS(condition)
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int shape[1] = {3};
        inline int result[3] = {2,3,5};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline auto condition = nmtools_tuple{False,True,True,False,True};
        inline int array[3][2] = {
            {1,2},
            {3,4},
            {5,6},
        };
        inline auto axis = None;
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int shape[1] = {3};
        inline int result[3] = {2,3,5};
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_COMPRESS_HPP