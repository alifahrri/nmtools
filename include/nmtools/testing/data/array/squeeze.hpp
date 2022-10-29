#ifndef NMTOOLS_TESTING_DATA_ARRAY_SQUEEZE_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_SQUEEZE_HPP

#include "nmtools/testing/testing.hpp"

NMTOOLS_TESTING_DECLARE_CASE(squeeze)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline double array[6] = {1,2,3,4,5,6};
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int shape_[1] = {6};
        inline auto shape = cast<int>(shape_);
        inline double expected[6] = {1,2,3,4,5,6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline double array[6][1] = {
            {1},
            {2},
            {3},
            {4},
            {5},
            {6},
        };
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int shape_[1] = {6};
        inline auto shape = cast<int>(shape_);
        inline double expected[6] = {1,2,3,4,5,6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline double array[6][2] = {
            {1,1},
            {2,2},
            {3,3},
            {4,4},
            {5,5},
            {6,6},
        };
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int shape_[2] = {6,2};
        inline auto shape = cast<int>(shape_);
        inline double expected[6][2] = {
            {1,1},
            {2,2},
            {3,3},
            {4,4},
            {5,5},
            {6,6},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline double array[1][6] = {
            {1,2,3,4,5,6}
        };
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int shape_[1] = {6};
        inline auto shape = cast<int>(shape_);
        inline double expected[6] = {1,2,3,4,5,6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline double array[6][1][1] = {
            {
                {1}
            },
            {
                {2}
            },
            {
                {3}
            },
            {
                {4}
            },
            {
                {5}
            },
            {
                {6}
            }
        };
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int shape_[1] = {6};
        inline auto shape = cast<int>(shape_);
        inline double expected[6] = {1,2,3,4,5,6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline double array[1][6][1] = {
            {
                {1},
                {2},
                {3},
                {4},
                {5},
                {6}
            }
        };
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int shape_[1] = {6};
        inline auto shape = cast<int>(shape_);
        inline double expected[6] = {1,2,3,4,5,6};
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_SQUEEZE_HPP