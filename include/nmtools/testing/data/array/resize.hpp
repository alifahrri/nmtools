#ifndef NMTOOLS_TESTING_DATA_ARRAY_RESIZE_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_RESIZE_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(resize)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int32_t array[4][4] = {
            { 0, 1, 2, 3},
            { 4, 5, 6, 7},
            { 8, 9,10,11},
            {12,13,14,15},
        };
        inline auto dst_shape = nmtools_array{2ul,2ul};
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int32_t expected[2][2] = {
            {0, 2},
            {8,10},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int32_t array[4][4] = {
            { 0, 1, 2, 3},
            { 4, 5, 6, 7},
            { 8, 9,10,11},
            {12,13,14,15},
        };
        inline auto dst_shape = nmtools_array{2ul,3ul};
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int32_t expected[2][3] = {
            {0,1, 2},
            {8,9,10},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int32_t array[4][4] = {
            { 0, 1, 2, 3},
            { 4, 5, 6, 7},
            { 8, 9,10,11},
            {12,13,14,15},
        };
        inline auto dst_shape = nmtools_array{3ul,2ul};
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int32_t expected[3][2] = {
            {0, 2},
            {4, 6},
            {8,10},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int32_t array[4][4] = {
            { 0, 1, 2, 3},
            { 4, 5, 6, 7},
            { 8, 9,10,11},
            {12,13,14,15},
        };
        inline auto dst_shape = nmtools_array{3ul,3ul};
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int32_t expected[3][3] = {
            {0,1, 2},
            {4,5, 6},
            {8,9,10},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int32_t array[4][4] = {
            { 0, 1, 2, 3},
            { 4, 5, 6, 7},
            { 8, 9,10,11},
            {12,13,14,15},
        };
        inline auto dst_shape = nmtools_array{4ul,2ul};
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int32_t expected[4][2] = {
            { 0, 2},
            { 4, 6},
            { 8,10},
            {12,14}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int32_t array[4][4] = {
            { 0, 1, 2, 3},
            { 4, 5, 6, 7},
            { 8, 9,10,11},
            {12,13,14,15},
        };
        inline auto dst_shape = nmtools_array{8ul,4ul};
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int32_t expected[8][4] = {
            { 0, 1, 2, 3},
            { 0, 1, 2, 3},
            { 4, 5, 6, 7},
            { 4, 5, 6, 7},
            { 8, 9,10,11},
            { 8, 9,10,11},
            {12,13,14,15},
            {12,13,14,15},
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_RESIZE_HPP