#ifndef NMTOOLS_TESTING_DATA_INDEX_REMOVE_DIMS_HPP
#define NMTOOLS_TESTING_DATA_INDEX_REMOVE_DIMS_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(index, remove_dims)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int shape[3] = {1,2,3};
        inline int axis = 1;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[2] = {1,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int shape[3] = {1,2,3};
        inline int axis = 1;
        inline auto keepdims = True;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[3] = {1,1,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int shape[3] = {1,2,3};
        inline int axis = -2;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[2] = {1,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int shape[3] = {1,2,3};
        inline int axis = -2;
        inline auto keepdims = True;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[3] = {1,1,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int shape[1] = {2};
        inline int axis = 0;
        inline auto keepdims = False;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline auto result = None;
    }
}

#endif // NMTOOLS_TESTING_DATA_INDEX_REMOVE_DIMS_HPP