#ifndef NMTOOLS_TESTING_DATA_ARRAY_ARRAY_SLICE_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_ARRAY_SLICE_HPP

#include "nmtools/testing/array_cast.hpp"
#include "nmtools/testing/testing.hpp"

NMTOOLS_TESTING_DECLARE_CASE(index, shape_array_slice)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int shape[2]  = {4,3};
        inline int slice0[2] = {2,2};
        inline int slice1[2] = {2,2};
        NMTOOLS_CAST_ARRAYS(shape)
        NMTOOLS_CAST_ARRAYS(slice0)
        NMTOOLS_CAST_ARRAYS(slice1)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[2] = {2,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int shape[2]  = {4,3};
        inline int slice0[2] = {2,1};
        inline int slice1[1] = {2};
        NMTOOLS_CAST_ARRAYS(shape)
        NMTOOLS_CAST_ARRAYS(slice0)
        NMTOOLS_CAST_ARRAYS(slice1)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[2] = {2,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int shape[2]  = {5,7};
        inline int slice0[2] = {2,1};
        inline int slice1[1] = {1};
        NMTOOLS_CAST_ARRAYS(shape)
        NMTOOLS_CAST_ARRAYS(slice0)
        NMTOOLS_CAST_ARRAYS(slice1)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[2] = {2,1};
    }
    
    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int shape[2]  = {5,7};
        inline int slice0[1] = {3};
        inline int slice1[1] = {3};
        NMTOOLS_CAST_ARRAYS(shape)
        NMTOOLS_CAST_ARRAYS(slice0)
        NMTOOLS_CAST_ARRAYS(slice1) 
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[1] = {3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int shape[2]  = {5,7};
        inline int slice0[1] = {3};
        NMTOOLS_CAST_ARRAYS(shape)
        NMTOOLS_CAST_ARRAYS(slice0)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int result[2] = {3,7};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int shape[2]  = {4,3};
        inline int slice0[2] = {2,2};
        NMTOOLS_CAST_ARRAYS(shape)
        NMTOOLS_CAST_ARRAYS(slice0)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int result[3] = {2,2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int shape[3]  = {2,3,2};
        inline int slice0[2] = {2,1};
        NMTOOLS_CAST_ARRAYS(shape)
        NMTOOLS_CAST_ARRAYS(slice0)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int result[4] = {2,1,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline int shape[3]  = {2,3,2};
        inline int slice0[2] = {2,1};
        inline int slice1[1] = {1};
        NMTOOLS_CAST_ARRAYS(shape)
        NMTOOLS_CAST_ARRAYS(slice0)
        NMTOOLS_CAST_ARRAYS(slice1)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline int result[3] = {2,1,2};
    }
}

NMTOOLS_TESTING_DECLARE_CASE(array, array_slice)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int array[4][3] = {
            {0, 1, 2},
            {3, 4, 5},
            {6, 7, 8},
            {9,10,11},
        };
        inline int slice0[2][2] = {
            {0,0},
            {3,3},
        };
        inline int slice1[2][2] = {
            {0,2},
            {0,2},
        };
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_ARRAYS(slice0)
        NMTOOLS_CAST_ARRAYS(slice1)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[2][2] = {
            {0, 2},
            {9,11},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        using case1::args::array;
        inline int slice0[2] = {0,3};
        inline int slice1[2] = {0,2};
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_ARRAYS(slice0)
        NMTOOLS_CAST_ARRAYS(slice1)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[2] = {0,11};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        using case1::args::array;
        inline int slice0[2][1] = {{0},{3}};
        inline int slice1[2] = {0,2};
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_ARRAYS(slice0)
        NMTOOLS_CAST_ARRAYS(slice1)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[2][2] = {
            {0, 2},
            {9,11},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int array[5][7] = {
            { 0,  1,  2,  3,  4,  5,  6},
            { 7,  8,  9, 10, 11, 12, 13},
            {14, 15, 16, 17, 18, 19, 20},
            {21, 22, 23, 24, 25, 26, 27},
            {28, 29, 30, 31, 32, 33, 34}
        };
        inline int slice0[3] = {0,2,4};
        inline int slice1[3] = {0,1,2};
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_ARRAYS(slice0)
        NMTOOLS_CAST_ARRAYS(slice1)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[3] = {0,15,30};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        using case4::args::array;
        inline int slice0[3] = {0,2,4};
        inline int slice1[1] = {1};
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_ARRAYS(slice0)
        NMTOOLS_CAST_ARRAYS(slice1)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int result[3] = {1,15,29};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        using case5::args::array;
        inline int slice0[3] = {0,2,4};
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_ARRAYS(slice0)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int result[3][7] = {
            { 0,  1,  2,  3,  4,  5,  6},
            {14, 15, 16, 17, 18, 19, 20},
            {28, 29, 30, 31, 32, 33, 34}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int array[4][3] = {
            {0, 1, 2},
            {3, 4, 5},
            {6, 7, 8},
            {9,10,11},
        };
        inline int slice0[2][2] = {
            {0,0},
            {3,3},
        };
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_ARRAYS(slice0)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int result[2][2][3] = {
            {
                {0,1,2},
                {0,1,2},
            },
            {
                {9,10,11},
                {9,10,11},
            }
        };
    }

    // the following are invalid:
    // >>> slice0 = np.array([[0,0,0],[3,3,3]])
    // >>> slice1 = np.array([[0,2,3],[0,2,3]])
    // >>> a[slice0,slice1]
    // Traceback (most recent call last):
    //   File "<stdin>", line 1, in <module>
    // IndexError: index 3 is out of bounds for axis 1 with size 3

    // but the following are ok:
    // >>> slice0 = np.array([[0,0,0],[0,0,0]])
    // >>> slice1 = np.array([[0,2,0],[0,2,0]])
    // >>> a[slice0,slice1]
    // array([[0, 2, 0],
    //        [0, 2, 0]])

    // The resulting dimension follows the largest slice dim
    // >>> slice0
    // array([[0, 0],
    //        [2, 3]])
    // >>> slice1
    // array([0, 2])
    // >>> a[slice0[np.newaxis,...],slice1[np.newaxis,...]]
    // array([[[ 0,  2],
    //         [ 6, 11]]])

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline int array[2][3][2] = {
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
        inline int slice0[2][1] = {{0}, {1}};
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_ARRAYS(slice0)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline int result[2][1][3][2] = {
            {
                {
                    {0,1},
                    {2,3},
                    {4,5},
                }
            },
            {
                {
                    { 6, 7},
                    { 8, 9},
                    {10,11},
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        using case8::args::array;
        inline int slice0[2][1] = {{0},{1}};
        inline int slice1[1] = {2};
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_ARRAYS(slice0)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline int result[2][1][2] = {
            {
                {4,5},
            },
            {
                {10,11},
            }
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_ARRAY_SLICE_HPP