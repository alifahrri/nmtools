#ifndef NMTOOLS_TESTING_DATA_INDEX_COMPUTE_STRIDES_HPP
#define NMTOOLS_TESTING_DATA_INDEX_COMPUTE_STRIDES_HPP

#include "nmtools/testing/doctest.hpp"

NMTOOLS_TESTING_DECLARE_CASE(compute_strides)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int32_t shape[1] = {3};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int32_t result[1] = {1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int32_t shape[2] = {3,2};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int32_t result[2] = {2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int32_t shape[3] = {3,2,1};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int32_t result[3] = {2,1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int32_t shape[3] = {3,2,3};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int32_t result[3] = {6,3,1};
    }
}

#endif // NMTOOLS_TESTING_DATA_INDEX_COMPUTE_STRIDES_HPP