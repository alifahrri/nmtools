#ifndef NMTOOLS_TESTING_DATA_ARRAY_TAKE_ALONG_AXIS_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_TAKE_ALONG_AXIS_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

/*
NOTE: in numpy, the difference between take and take_along_axis is that
take_along_axis forces the "indices" and "arr" to have the same number of dimensions
while in take it doesn't have such restriction and the result's dim will follow indices

examples:
>>> a
array([[[ 0,  1],
        [ 2,  3],
        [ 4,  5]],

       [[ 6,  7],
        [ 8,  9],
        [10, 11]]])
>>> indices = np.array([[[0,1]]])
>>> np.take_along_axis(a,indices,1)
array([[[0, 3]],

       [[6, 9]]])
>>> np.take(a,indices,1)
array([[[[[0, 1],
          [2, 3]]]],



       [[[[6, 7],
          [8, 9]]]]])



In addition, the shape must be broadcastable:

>>> indices = np.array([[[1],[0]]])
>>> indices.shape
(1, 2, 1)
>>> np.take_along_axis(a,indices,0)
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
  File "<__array_function__ internals>", line 5, in take_along_axis
  File "/home/fahri/.local/lib/python3.8/site-packages/numpy/lib/shape_base.py", line 170, in take_along_axis
    return arr[_make_along_axis_idx(arr_shape, indices, axis)]
IndexError: shape mismatch: indexing arrays could not be broadcast together with shapes (1,2,1) (1,3,1) (1,1,2) 

And, the value must not be out of bounds

>>> indices = np.array([[[1],[0],[2]]])
>>> np.take_along_axis(a,indices,0)
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
  File "<__array_function__ internals>", line 5, in take_along_axis
  File "/home/fahri/.local/lib/python3.8/site-packages/numpy/lib/shape_base.py", line 170, in take_along_axis
    return arr[_make_along_axis_idx(arr_shape, indices, axis)]
IndexError: index 2 is out of bounds for axis 0 with size 2
*/

NMTOOLS_TESTING_DECLARE_CASE(index, shape_take_along_axis)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int shape[3]   = {2,3,2};
        inline int indices[3] = {1,1,2};
        inline auto axis_u = 0ul;
        inline auto axis_i = -3l;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[3] = {1,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int shape[3] = {2,3,2};
        inline int indices[3] = {1,1,2};
        inline auto axis_u = 1ul;
        inline auto axis_i = -2l;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[3] = {2,1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int shape[3] = {2,3,2};
        inline int indices[3] = {1,1,2};
        inline auto axis_u = 2ul;
        inline auto axis_i = -1l;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[3] = {2,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int shape[3]   = {2,3,2};
        inline int indices[3] = {1,3,1};
        inline auto axis_u = 0ul;
        inline auto axis_i = -3l;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[3] = {1,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int shape[3]   = {2,3,2};
        inline int indices[3] = {1,3,1};
        inline auto axis_u = 1ul;
        inline auto axis_i = -2l;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int result[3] = {2,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int shape[3]   = {2,3,2};
        inline int indices[3] = {1,3,1};
        inline auto axis_u = 2ul;
        inline auto axis_i = -1l;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int result[3] = {2,3,1};
    }

    // Error handling

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int shape[3]   = {2,3,2};
        inline int indices[3] = {1,1,2};
        inline auto axis_u = 3ul;
        inline auto axis_i = -4l;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline auto result = meta::Nothing;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline int shape[3]   = {2,3,2};
        inline int indices[3] = {1,3,1};
        inline auto axis_u = 4ul;
        inline auto axis_i = -4l;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline auto result = meta::Nothing;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        inline int shape[3]   = {2,3,2};
        inline int indices[1] = {1};
        inline auto axis_u = 1ul;
        inline auto axis_i = -2l;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline auto result = meta::Nothing;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        inline int shape[3]   = {2,3,2};
        inline int indices[3] = {1,2,1};
        inline auto axis_u = 1ul;
        inline auto axis_i = -2l;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline auto result = meta::Nothing;
    }

    // Normal case

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        inline int shape[3]   = {2,1,6};
        inline int indices[3] = {1,3,1};
        inline auto axis_u = 0ul;
        inline auto axis_i = -3l;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        inline int result[3] = {1,3,6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        inline int shape[3]   = {2,1,6};
        inline int indices[3] = {1,3,1};
        inline auto axis_u = 2ul;
        inline auto axis_i = -1l;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        inline int result[3] = {2,3,1};
    }
}

NMTOOLS_TESTING_DECLARE_CASE(array, take_along_axis)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
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
        inline int indices[1][1][2] = {{{0,1}}};
        inline int axis = 0;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[1][3][2] = {
            {
                {0, 7},
                {2, 9},
                {4,11},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        using case1::args::array;
        using case1::args::indices;
        inline int axis = 1;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[2][1][2] = {
            {
                {0,3},
            },
            {
                {6,9},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        using case1::args::array;
        using case1::args::indices;
        inline int axis = 2;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[2][3][2] = {
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
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
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
        inline int indices[1][3][1] = {
            {
                {1},
                {0},
                {0},
            }
        };
        inline int axis = 0;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[1][3][2] = {
          {
              {6,7},
              {2,3},
              {4,5},
          }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        using case4::args::array;
        using case4::args::indices;
        inline int axis = 1;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int result[2][3][2] = {
            {
                {2,3},
                {0,1},
                {0,1},
            },
            {
                {8,9},
                {6,7},
                {6,7},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        using case4::args::array;
        using case4::args::indices;
        inline int axis = 2;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int result[2][3][1] = {
            {
                {1},
                {2},
                {4},
            },
            {
                { 7},
                { 8},
                {10},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int array[2][1][6] = {
            {
                {0,1,2,3,4,5},
            },
            {
                {6,7,8,9,10,11},
            }
        };
        inline int indices[1][3][1] = {
            {
                {1},
                {0},
                {0},
            },
        };
        inline int axis = 0;
        // TODO: error at axis = 1;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int result[1][3][6] = {
            {
                {6,7,8,9,10,11},
                {0,1,2,3, 4, 5},
                {0,1,2,3, 4, 5},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        using case7::args::array;
        using case7::args::indices;
        inline int axis = 2;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline int result[2][3][1] = {
            {
                {1},
                {0},
                {0},
            },
            {
                {7},
                {6},
                {6}
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
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
        inline int indices[2][3][2] = {
            {
                {0,0},
                {0,0},
                {0,0},
            },
            {
                {1,1},
                {1,1},
                {1,1},
            }
        };
        inline int axis = 0;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline int result[2][3][2] = {
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
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        using case9::args::array;
        inline int indices[2][3][2] = {
            {
                {0,0},
                {1,1},
                {2,2},
            },
            {
                {0,0},
                {1,1},
                {2,2},
            }
        };
        inline int axis = 1;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline int result[2][3][2] = {
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
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        using case9::args::array;
        inline int indices[2][3][2] = {
            {
                {0,1},
                {0,1},
                {0,1},
            },
            {
                {0,1},
                {0,1},
                {0,1},
            }
        };
        inline int axis = 2;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        inline int result[2][3][2] = {
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
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        inline float array[12] = {0., 1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11.};
        inline int indices[12] = {0,1,2,3,4,5,6,7,8,9,10,11};
        inline int axis = 0;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        inline float result[12] = {0., 1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11.};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case13)
    {
        inline float array[12] = {66., 55., 45., 36., 28., 21., 15., 10., 6., 3., 1., 0.};
        inline int indices[12] = {11,10,9,8,7,6,5,4,3,2,1};
        inline int axis = -1;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case13)
    {
        inline float result[12] = {0.,1.,3.,6.,10.,15.,21.,28.,36.,45.,55.,66.};
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_TAKE_ALONG_AXIS_HPP