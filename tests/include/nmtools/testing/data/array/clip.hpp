#ifndef NMTOOLS_TESTING_DATA_ARRAY_CLIP_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_CLIP_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(array, clip)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int8_t a[3][2] = {
            {0,1},
            {2,3},
            {4,5},
        };
        inline int8_t amin[2] = {1,0};
        inline int8_t amax[1] = {3};
        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(amin)
        NMTOOLS_CAST_ARRAYS(amax)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int8_t shape[2] = {3,2};
        inline int8_t result[3][2] = {
            {1,1},
            {2,3},
            {3,3},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int8_t a[3][2] = {
            {0,1},
            {2,3},
            {4,5},
        };
        inline int8_t amin[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        inline int8_t amax[1] = {3};
        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(amin)
        NMTOOLS_CAST_ARRAYS(amax)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int8_t shape[3] = {2,3,2};
        inline int8_t result[2][3][2] = {
            {
                {0,1},
                {2,3},
                {3,3},
            },
            {
                {3,3},
                {3,3},
                {3,3},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int8_t a[3][2] = {
            {0,1},
            {2,3},
            {4,5},
        };
        inline int8_t amin[2] = {1,0};
        inline int8_t amax = 3;
        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(amin)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int8_t shape[2] = {3,2};
        inline int8_t result[3][2] = {
            {1,1},
            {2,3},
            {3,3},
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_CLIP_HPP