#ifndef NMTOOLS_TESTING_DATA_ARRAY_POOLING_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_POOLING_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"
#include "nmtools/testing/data/index/pooling.hpp"

using namespace nmtools::literals;

NMTOOLS_TESTING_DECLARE_CASE(array, max_pool2d)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int array[1][1][4][4] = {
            {
                {
                    {0, 1,  2, 3},
                    {4, 5,  6, 7},
                    {8, 9, 10,11},
                    {12,13,14,15},
                }
            }
        };
        inline int kernel_size[2] = {3,3};
        inline int stride[2]  = {2,2};
        inline auto padding   = None;
        inline auto dilation  = None;
        inline auto ceil_mode = True;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[1][1][2][2] = {
            {
                {
                    {10,11},
                    {14,15},
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1b)
    {
        inline int array[1][1][4][4] = {
            {
                {
                    {0, 1,  2, 3},
                    {4, 5,  6, 7},
                    {8, 9, 10,11},
                    {12,13,14,15},
                }
            }
        };
        inline int kernel_size[2] = {3,3};
        inline int stride[2]  = {3,3};
        inline auto padding   = None;
        inline auto dilation  = None;
        inline auto ceil_mode = True;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1b)
    {
        inline int result[1][1][2][2] = {
            {
                {
                    {10,11},
                    {14,15},
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1c)
    {
        inline int array[1][1][4][4] = {
            {
                {
                    {0, 1,  2, 3},
                    {4, 5,  6, 7},
                    {8, 9, 10,11},
                    {12,13,14,15},
                }
            }
        };
        inline int kernel_size[2] = {3,3};
        inline int stride[2]  = {4,4};
        inline auto padding   = None;
        inline auto dilation  = None;
        inline auto ceil_mode = True;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1c)
    {
        inline int result[1][1][1][1] = {
            {
                {
                    {10},
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int array[1][1][4][4] = {
            {
                {
                    {0, 1,  2, 3},
                    {4, 5,  6, 7},
                    {8, 9, 10,11},
                    {12,13,14,15},
                }
            }
        };
        inline int kernel_size[2] = {3,3};
        inline int stride[2]  = {1,1};
        inline auto padding   = None;
        inline auto dilation  = None;
        inline auto ceil_mode = True;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[1][1][2][2] = {
            {
                {
                    {10,11},
                    {14,15},
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int array[1][1][4][4] = {
            {
                {
                    {0, 1,  2, 3},
                    {4, 5,  6, 7},
                    {8, 9, 10,11},
                    {12,13,14,15},
                }
            }
        };
        inline int kernel_size[2] = {3,3};
        inline int stride[2]  = {1,2};
        inline auto padding   = None;
        inline auto dilation  = None;
        inline auto ceil_mode = True;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[1][1][2][2] = {
            {
                {
                    {10,11},
                    {14,15},
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int array[1][1][4][4] = {
            {
                {
                    {0, 1,  2, 3},
                    {4, 5,  6, 7},
                    {8, 9, 10,11},
                    {12,13,14,15},
                }
            }
        };
        inline int kernel_size[2] = {3,3};
        inline int stride[2]  = {2,1};
        inline auto padding   = None;
        inline auto dilation  = None;
        inline auto ceil_mode = True;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[1][1][2][2] = {
            {
                {
                    {10,11},
                    {14,15},
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int array[1][1][4][4] = {
            {
                {
                    {0, 1,  2, 3},
                    {4, 5,  6, 7},
                    {8, 9, 10,11},
                    {12,13,14,15},
                }
            }
        };
        inline int kernel_size[2] = {3,3};
        inline int stride[2]  = {2,1};
        inline auto padding   = None;
        inline auto dilation  = None;
        inline auto ceil_mode = False;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int result[1][1][1][2] = {
            {
                {
                    {10,11},
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int array[1][1][4][4] = {
            {
                {
                    {0, 1,  2, 3},
                    {4, 5,  6, 7},
                    {8, 9, 10,11},
                    {12,13,14,15},
                }
            }
        };
        inline int kernel_size[2] = {3,3};
        inline int stride[2]  = {1,2};
        inline auto padding   = None;
        inline auto dilation  = None;
        inline auto ceil_mode = False;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int result[1][1][2][1] = {
            {
                {
                    {10},
                    {14},
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int array[1][1][4][4] = {
            {
                {
                    {0, 1,  2, 3},
                    {4, 5,  6, 7},
                    {8, 9, 10,11},
                    {12,13,14,15},
                }
            }
        };
        inline int kernel_size[2] = {2,2};
        inline int stride[2]  = {1,1};
        inline auto padding   = None;
        inline auto dilation  = None;
        inline auto ceil_mode = False;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int result[1][1][3][3] = {
            {
                {
                    { 5, 6, 7},
                    { 9,10,11},
                    {13,14,15},
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline int array[1][1][4][4] = {
            {
                {
                    {0, 1,  2, 3},
                    {4, 5,  6, 7},
                    {8, 9, 10,11},
                    {12,13,14,15},
                }
            }
        };
        inline int kernel_size[2] = {2,2};
        inline int stride[2]  = {2,2};
        inline auto padding   = None;
        inline auto dilation  = None;
        inline auto ceil_mode = False;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline int result[1][1][2][2] = {
            {
                {
                    { 5, 7},
                    {13,15},
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        inline int array[1][1][4][4] = {
            {
                {
                    {0, 1,  2, 3},
                    {4, 5,  6, 7},
                    {8, 9, 10,11},
                    {12,13,14,15},
                }
            }
        };
        inline int kernel_size[2] = {2,2};
        inline int stride[2]  = {3,3};
        inline auto padding   = None;
        inline auto dilation  = None;
        inline auto ceil_mode = False;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline int result[1][1][1][1] = {
            {
                {
                    { 5},
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        inline int array[1][1][4][4] = {
            {
                {
                    {0, 1,  2, 3},
                    {4, 5,  6, 7},
                    {8, 9, 10,11},
                    {12,13,14,15},
                }
            }
        };
        inline int kernel_size[2] = {2,2};
        inline int stride[2]  = {3,3};
        inline auto padding   = None;
        inline auto dilation  = None;
        inline auto ceil_mode = True;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline int result[1][1][2][2] = {
            {
                {
                    { 5, 7},
                    {13,15},
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10b)
    {
        inline int array[1][1][4][4] = {
            {
                {
                    {0, 1,  2, 3},
                    {4, 5,  6, 7},
                    {8, 9, 10,11},
                    {12,13,14,15},
                }
            }
        };
        inline int kernel_size[2] = {2,2};
        inline int stride[2]  = {2,2};
        inline auto padding   = None;
        inline auto dilation  = None;
        inline auto ceil_mode = True;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10b)
    {
        inline int result[1][1][2][2] = {
            {
                {
                    { 5, 7},
                    {13,15},
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10c)
    {
        inline int array[1][1][4][4] = {
            {
                {
                    {0, 1,  2, 3},
                    {4, 5,  6, 7},
                    {8, 9, 10,11},
                    {12,13,14,15},
                }
            }
        };
        inline int kernel_size[2] = {2,2};
        inline int stride[2]  = {1,1};
        inline auto padding   = None;
        inline auto dilation  = None;
        inline auto ceil_mode = True;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10c)
    {
        inline int result[1][1][3][3] = {
            {
                {
                    { 5, 6, 7},
                    { 9,10,11},
                    {13,14,15},
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        inline int array[1][1][6][6] = {
            {
                {
                    { 0,  1,  2,  3,  4,  5},
                    { 6,  7,  8,  9, 10, 11},
                    {12, 13, 14, 15, 16, 17},
                    {18, 19, 20, 21, 22, 23},
                    {24, 25, 26, 27, 28, 29},
                    {30, 31, 32, 33, 34, 35}
                }
            }
        };
        inline int kernel_size[2] = {3, 3};
        inline int stride[2]  = {2, 2};
        inline auto padding   = None;
        inline auto dilation  = None;
        inline auto ceil_mode = True;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        inline int result[1][1][3][3] = {
            {
                {
                    {14, 16, 17},
                    {26, 28, 29},
                    {32, 34, 35}
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11b)
    {
        inline int array[1][1][6][6] = {
            {
                {
                    { 0,  1,  2,  3,  4,  5},
                    { 6,  7,  8,  9, 10, 11},
                    {12, 13, 14, 15, 16, 17},
                    {18, 19, 20, 21, 22, 23},
                    {24, 25, 26, 27, 28, 29},
                    {30, 31, 32, 33, 34, 35}
                }
            }
        };
        inline int kernel_size[2] = {3, 3};
        inline int stride[2]  = {2, 2};
        inline auto padding   = None;
        inline auto dilation  = None;
        inline auto ceil_mode = False;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11b)
    {
        inline int result[1][1][2][2] = {
            {
                {
                    {14, 16},
                    {26, 28}
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11c)
    {
        inline int array[1][1][6][6] = {
            {
                {
                    { 0,  1,  2,  3,  4,  5},
                    { 6,  7,  8,  9, 10, 11},
                    {12, 13, 14, 15, 16, 17},
                    {18, 19, 20, 21, 22, 23},
                    {24, 25, 26, 27, 28, 29},
                    {30, 31, 32, 33, 34, 35}
                }
            }
        };
        inline int kernel_size[2] = {3, 3};
        inline int stride[2]  = {3, 3};
        inline auto padding   = None;
        inline auto dilation  = None;
        inline auto ceil_mode = False;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11c)
    {
        inline int result[1][1][2][2] = {
            {
                {
                    {14, 17},
                    {32, 35}
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        inline int array[1][1][7][7] = {
            {
                {
                    { 0,  1,  2,  3,  4,  5,  6},
                    { 7,  8,  9, 10, 11, 12, 13},
                    {14, 15, 16, 17, 18, 19, 20},
                    {21, 22, 23, 24, 25, 26, 27},
                    {28, 29, 30, 31, 32, 33, 34},
                    {35, 36, 37, 38, 39, 40, 41},
                    {42, 43, 44, 45, 46, 47, 48}
                }
            }
        };
        inline int kernel_size[2] = {3, 3};
        inline int stride[2]  = {2, 2};
        inline auto padding   = None;
        inline auto dilation  = None;
        inline auto ceil_mode = True;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        inline int result[1][1][3][3] = {
            {
                {
                    {16, 18, 20},
                    {30, 32, 34},
                    {44, 46, 48}
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12b)
    {
        inline int array[1][1][7][7] = {
            {
                {
                    { 0,  1,  2,  3,  4,  5,  6},
                    { 7,  8,  9, 10, 11, 12, 13},
                    {14, 15, 16, 17, 18, 19, 20},
                    {21, 22, 23, 24, 25, 26, 27},
                    {28, 29, 30, 31, 32, 33, 34},
                    {35, 36, 37, 38, 39, 40, 41},
                    {42, 43, 44, 45, 46, 47, 48}
                }
            }
        };
        inline int kernel_size[2] = {3, 3};
        inline int stride[2]  = {2, 2};
        inline auto padding   = None;
        inline auto dilation  = None;
        inline auto ceil_mode = False;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }

    NMTOOLS_TESTING_DECLARE_EXPECT(case12b)
    {
        inline int result[1][1][3][3] = {
            {
                {
                    {16, 18, 20},
                    {30, 32, 34},
                    {44, 46, 48}
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12c)
    {
        inline int array[1][1][7][7] = {
            {
                {
                    { 0,  1,  2,  3,  4,  5,  6},
                    { 7,  8,  9, 10, 11, 12, 13},
                    {14, 15, 16, 17, 18, 19, 20},
                    {21, 22, 23, 24, 25, 26, 27},
                    {28, 29, 30, 31, 32, 33, 34},
                    {35, 36, 37, 38, 39, 40, 41},
                    {42, 43, 44, 45, 46, 47, 48}
                }
            }
        };
        inline int kernel_size[2] = {3, 3};
        inline int stride[2]  = {3, 3};
        inline auto padding   = None;
        inline auto dilation  = None;
        inline auto ceil_mode = False;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }

    NMTOOLS_TESTING_DECLARE_EXPECT(case12c)
    {
        inline int result[1][1][2][2] = {
            {
                {
                    {16, 19},
                    {37, 40}
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12d)
    {
        inline int array[1][1][7][7] = {
            {
                {
                    { 0,  1,  2,  3,  4,  5,  6},
                    { 7,  8,  9, 10, 11, 12, 13},
                    {14, 15, 16, 17, 18, 19, 20},
                    {21, 22, 23, 24, 25, 26, 27},
                    {28, 29, 30, 31, 32, 33, 34},
                    {35, 36, 37, 38, 39, 40, 41},
                    {42, 43, 44, 45, 46, 47, 48}
                }
            }
        };
        inline int kernel_size[2] = {3, 3};
        inline int stride[2]  = {3, 3};
        inline auto padding   = None;
        inline auto dilation  = None;
        inline auto ceil_mode = True;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12d)
    {
        inline int result[1][1][3][3] = {
            {
                {
                    {16, 19, 20},
                    {37, 40, 41},
                    {44, 47, 48}
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12e)
    {
        inline int array[1][1][7][7] = {
            {
                {
                    { 0,  1,  2,  3,  4,  5,  6},
                    { 7,  8,  9, 10, 11, 12, 13},
                    {14, 15, 16, 17, 18, 19, 20},
                    {21, 22, 23, 24, 25, 26, 27},
                    {28, 29, 30, 31, 32, 33, 34},
                    {35, 36, 37, 38, 39, 40, 41},
                    {42, 43, 44, 45, 46, 47, 48}
                }
            }
        };
        inline int kernel_size[2] = {3, 3};
        inline int stride[2]  = {3, 3};
        inline auto padding   = None;
        inline auto dilation  = None;
        inline auto ceil_mode = false;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }

    NMTOOLS_TESTING_DECLARE_EXPECT(case12e)
    {
        inline int result[1][1][2][2] = {
            {
                {
                    {16, 19},
                    {37, 40}
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12f)
    {
        inline int array[1][1][7][7] = {
            {
                {
                    { 0,  1,  2,  3,  4,  5,  6},
                    { 7,  8,  9, 10, 11, 12, 13},
                    {14, 15, 16, 17, 18, 19, 20},
                    {21, 22, 23, 24, 25, 26, 27},
                    {28, 29, 30, 31, 32, 33, 34},
                    {35, 36, 37, 38, 39, 40, 41},
                    {42, 43, 44, 45, 46, 47, 48}
                }
            }
        };
        inline int kernel_size[2] = {3, 3};
        inline int stride[2]  = {3, 3};
        inline auto padding   = None;
        inline auto dilation  = None;
        inline auto ceil_mode = true;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12f)
    {
        inline int result[1][1][3][3] = {
            {
                {
                    {16, 19, 20},
                    {37, 40, 41},
                    {44, 47, 48}
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case13)
    {
        inline int array[1][1][7][7] = {
            {
                {
                    { 0,  1,  2,  3,  4,  5,  6},
                    { 7,  8,  9, 10, 11, 12, 13},
                    {14, 15, 16, 17, 18, 19, 20},
                    {21, 22, 23, 24, 25, 26, 27},
                    {28, 29, 30, 31, 32, 33, 34},
                    {35, 36, 37, 38, 39, 40, 41},
                    {42, 43, 44, 45, 46, 47, 48}
                }
            }
        };
        inline int kernel_size[2] = {3, 3};
        inline int stride[2]      = {2, 2};
        inline auto padding = None;
        inline int dilation[2]    = {2, 2};
        inline auto ceil_mode     = True;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
        NMTOOLS_CAST_INDEX_ARRAYS(dilation)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case13)
    {
        inline int result[1][1][2][2] = {{{{32, 34}, {46, 48}}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case14)
    {
        inline int array[1][1][7][7] = {
            {
                {
                    { 0,  1,  2,  3,  4,  5,  6},
                    { 7,  8,  9, 10, 11, 12, 13},
                    {14, 15, 16, 17, 18, 19, 20},
                    {21, 22, 23, 24, 25, 26, 27},
                    {28, 29, 30, 31, 32, 33, 34},
                    {35, 36, 37, 38, 39, 40, 41},
                    {42, 43, 44, 45, 46, 47, 48}
                }
            }
        };
        inline int kernel_size[2] = {3, 3};
        inline int stride[2]      = {2, 2};
        inline auto padding = None;
        inline int dilation[2]    = {3, 3};
        inline auto ceil_mode     = True;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
        NMTOOLS_CAST_INDEX_ARRAYS(dilation)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case14)
    {
        inline int result[1][1][1][1] = {{{{48}}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case14b)
    {
        inline int array[1][1][7][7] = {
            {
                {
                    { 0,  1,  2,  3,  4,  5,  6},
                    { 7,  8,  9, 10, 11, 12, 13},
                    {14, 15, 16, 17, 18, 19, 20},
                    {21, 22, 23, 24, 25, 26, 27},
                    {28, 29, 30, 31, 32, 33, 34},
                    {35, 36, 37, 38, 39, 40, 41},
                    {42, 43, 44, 45, 46, 47, 48}
                }
            }
        };
        inline int kernel_size[2] = {3, 3};
        inline int stride[2]      = {2, 2};
        inline auto padding = None;
        inline int dilation[2]    = {3, 3};
        inline auto ceil_mode     = False;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
        NMTOOLS_CAST_INDEX_ARRAYS(dilation)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case14b)
    {
        inline int result[1][1][1][1] = {{{{48}}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case14c)
    {
        inline int array[1][1][7][7] = {
            {
                {
                    { 0,  1,  2,  3,  4,  5,  6},
                    { 7,  8,  9, 10, 11, 12, 13},
                    {14, 15, 16, 17, 18, 19, 20},
                    {21, 22, 23, 24, 25, 26, 27},
                    {28, 29, 30, 31, 32, 33, 34},
                    {35, 36, 37, 38, 39, 40, 41},
                    {42, 43, 44, 45, 46, 47, 48}
                }
            }
        };
        inline int kernel_size[2] = {3, 3};
        inline int stride[2]      = {2, 2};
        inline auto padding = None;
        inline int dilation       = 3;
        inline auto ceil_mode     = True;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case14c)
    {
        inline int result[1][1][1][1] = {{{{48}}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case14d)
    {
        inline int array[1][1][7][7] = {
            {
                {
                    { 0,  1,  2,  3,  4,  5,  6},
                    { 7,  8,  9, 10, 11, 12, 13},
                    {14, 15, 16, 17, 18, 19, 20},
                    {21, 22, 23, 24, 25, 26, 27},
                    {28, 29, 30, 31, 32, 33, 34},
                    {35, 36, 37, 38, 39, 40, 41},
                    {42, 43, 44, 45, 46, 47, 48}
                }
            }
        };
        inline int kernel_size[2] = {3, 3};
        inline int stride         = 2;
        inline auto padding = None;
        inline int dilation       = 3;
        inline auto ceil_mode     = True;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case14d)
    {
        inline int result[1][1][1][1] = {{{{48}}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case14e)
    {
        inline int array[1][1][7][7] = {
            {
                {
                    { 0,  1,  2,  3,  4,  5,  6},
                    { 7,  8,  9, 10, 11, 12, 13},
                    {14, 15, 16, 17, 18, 19, 20},
                    {21, 22, 23, 24, 25, 26, 27},
                    {28, 29, 30, 31, 32, 33, 34},
                    {35, 36, 37, 38, 39, 40, 41},
                    {42, 43, 44, 45, 46, 47, 48}
                }
            }
        };
        inline int kernel_size = 3;
        inline int stride      = 2;
        inline auto padding = None;
        inline int dilation    = 3;
        inline auto ceil_mode  = True;
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case14e)
    {
        inline int result[1][1][1][1] = {{{{48}}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case15)
    {
        inline int array[1][1][7][7] = {
            {
                {
                    { 0,  1,  2,  3,  4,  5,  6},
                    { 7,  8,  9, 10, 11, 12, 13},
                    {14, 15, 16, 17, 18, 19, 20},
                    {21, 22, 23, 24, 25, 26, 27},
                    {28, 29, 30, 31, 32, 33, 34},
                    {35, 36, 37, 38, 39, 40, 41},
                    {42, 43, 44, 45, 46, 47, 48}
                }
            }
        };
        inline int kernel_size[2] = {3, 3};
        inline int stride[2]      = {2, 2};
        inline auto padding = None;
        inline int dilation[2]    = {2, 1};
        inline auto ceil_mode     = True;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
        NMTOOLS_CAST_INDEX_ARRAYS(dilation)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case15)
    {
        inline int result[1][1][2][3] = {
            {
                {
                    {30, 32, 34},
                    {44, 46, 48}
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case16)
    {
        inline int array[1][1][7][7] = {
            {
                {
                    { 0,  1,  2,  3,  4,  5,  6},
                    { 7,  8,  9, 10, 11, 12, 13},
                    {14, 15, 16, 17, 18, 19, 20},
                    {21, 22, 23, 24, 25, 26, 27},
                    {28, 29, 30, 31, 32, 33, 34},
                    {35, 36, 37, 38, 39, 40, 41},
                    {42, 43, 44, 45, 46, 47, 48}
                }
            }
        };
        inline int kernel_size[2] = {3, 3};
        inline int stride[2]      = {2, 2};
        inline auto padding = None;
        inline int dilation[2]    = {1, 2};
        inline auto ceil_mode     = True;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
        NMTOOLS_CAST_INDEX_ARRAYS(dilation)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case16)
    {
        inline int result[1][1][3][2] = {
            {
                {
                    {18, 20},
                    {32, 34},
                    {46, 48}
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case17)
    {
        inline int array[1][1][7][7] = {
            {
                {
                    { 0,  1,  2,  3,  4,  5,  6},
                    { 7,  8,  9, 10, 11, 12, 13},
                    {14, 15, 16, 17, 18, 19, 20},
                    {21, 22, 23, 24, 25, 26, 27},
                    {28, 29, 30, 31, 32, 33, 34},
                    {35, 36, 37, 38, 39, 40, 41},
                    {42, 43, 44, 45, 46, 47, 48}
                }
            }
        };
        inline int kernel_size[2] = {3, 3};
        inline int stride[2]      = {1, 1};
        inline auto padding = None;
        inline int dilation[2]    = {3, 3};
        inline auto ceil_mode     = True;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
        NMTOOLS_CAST_INDEX_ARRAYS(dilation)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case17)
    {
        inline int result[1][1][1][1] = {{{{48}}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case18)
    {
        inline int array[1][1][7][7] = {
            {
                {
                    { 0,  1,  2,  3,  4,  5,  6},
                    { 7,  8,  9, 10, 11, 12, 13},
                    {14, 15, 16, 17, 18, 19, 20},
                    {21, 22, 23, 24, 25, 26, 27},
                    {28, 29, 30, 31, 32, 33, 34},
                    {35, 36, 37, 38, 39, 40, 41},
                    {42, 43, 44, 45, 46, 47, 48}
                }
            }
        };
        inline int kernel_size[2] = {3, 3};
        inline int stride[2]      = {1, 1};
        inline auto padding = None;
        inline int dilation[2]    = {2, 2};
        inline auto ceil_mode     = True;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
        NMTOOLS_CAST_INDEX_ARRAYS(dilation)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case18)
    {
        inline int result[1][1][3][3] = {
            {
                {
                    {32,33,34},
                    {39,40,41},
                    {46,47,48},
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case19)
    {
        inline int array[1][1][7][7] = {
            {
                {
                    { 0,  1,  2,  3,  4,  5,  6}, 
                    { 7,  8,  9, 10, 11, 12, 13}, 
                    {14, 15, 16, 17, 18, 19, 20}, 
                    {21, 22, 23, 24, 25, 26, 27}, 
                    {28, 29, 30, 31, 32, 33, 34}, 
                    {35, 36, 37, 38, 39, 40, 41}, 
                    {42, 43, 44, 45, 46, 47, 48}
                }
            }
        };
        inline int kernel_size[2] = {3, 3};
        inline int stride[2]      = {2, 2};
        inline int padding[2]     = {1, 1};
        inline int dilation[2]    = {2, 2};
        inline auto ceil_mode     = True;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
        NMTOOLS_CAST_INDEX_ARRAYS(padding)
        NMTOOLS_CAST_INDEX_ARRAYS(dilation)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case19)
    {
        inline int result[1][1][3][3] = {
            {
                {
                    {24, 26, 26},
                    {38, 40, 40},
                    {38, 40, 40},
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case20)
    {
        inline int array[1][1][7][7] = {
            {
                {
                    { 0,  1,  2,  3,  4,  5,  6}, 
                    { 7,  8,  9, 10, 11, 12, 13}, 
                    {14, 15, 16, 17, 18, 19, 20}, 
                    {21, 22, 23, 24, 25, 26, 27}, 
                    {28, 29, 30, 31, 32, 33, 34}, 
                    {35, 36, 37, 38, 39, 40, 41}, 
                    {42, 43, 44, 45, 46, 47, 48}
                }
            }
        };
        inline int kernel_size[2] = {3, 3};
        inline int stride[2]      = {2, 2};
        inline int padding[2]     = {1, 2};
        inline int dilation[2]    = {2, 2};
        inline auto ceil_mode     = True;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
        NMTOOLS_CAST_INDEX_ARRAYS(padding)
        NMTOOLS_CAST_INDEX_ARRAYS(dilation)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case20)
    {
        inline int result[1][1][3][4] = {
            {
                {
                    {23, 25, 27, 27},
                    {37, 39, 41, 41},
                    {37, 39, 41, 41},
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case21)
    {
        inline int array[1][1][5][5] = {
            {
                {
                    { 0,  1,  2,  3,  4}, 
                    { 5,  6,  7,  8,  9}, 
                    {10, 11, 12, 13, 14}, 
                    {15, 16, 17, 18, 19}, 
                    {20, 21, 22, 23, 24}
                }
            }
        };
        inline int kernel_size[2] = {2, 2};
        inline int stride[2]      = {1, 1};
        inline int padding[2]     = {1, 1};
        inline int dilation[2]    = {1, 1};
        inline auto ceil_mode     = False;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
        NMTOOLS_CAST_INDEX_ARRAYS(padding)
        NMTOOLS_CAST_INDEX_ARRAYS(dilation)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case21)
    {
        inline int result[1][1][6][6] = {
            {
                {
                    { 0,  1,  2,  3,  4,  4},
                    { 5,  6,  7,  8,  9,  9},
                    {10, 11, 12, 13, 14, 14},
                    {15, 16, 17, 18, 19, 19},
                    {20, 21, 22, 23, 24, 24},
                    {20, 21, 22, 23, 24, 24}
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case22)
    {
        inline int array[1][1][7][7] = {
            {
                {
                    { 0,  1,  2,  3,  4,  5,  6},
                    { 7,  8,  9, 10, 11, 12, 13},
                    {14, 15, 16, 17, 18, 19, 20},
                    {21, 22, 23, 24, 25, 26, 27},
                    {28, 29, 30, 31, 32, 33, 34},
                    {35, 36, 37, 38, 39, 40, 41},
                    {42, 43, 44, 45, 46, 47, 48}
                }
            }
        };
        inline int kernel_size[2] = {4, 4};
        inline int stride[2]      = {1, 1};
        inline int padding[2]     = {1, 2};
        inline int dilation[2]    = {1, 1};
        inline auto ceil_mode     = False;

        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
        NMTOOLS_CAST_INDEX_ARRAYS(padding)
        NMTOOLS_CAST_INDEX_ARRAYS(dilation)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case22)
    {
        inline int result[1][1][6][8] = {
            {
                {
                    {15, 16, 17, 18, 19, 20, 20, 20},
                    {22, 23, 24, 25, 26, 27, 27, 27},
                    {29, 30, 31, 32, 33, 34, 34, 34},
                    {36, 37, 38, 39, 40, 41, 41, 41},
                    {43, 44, 45, 46, 47, 48, 48, 48},
                    {43, 44, 45, 46, 47, 48, 48, 48}
                }
            }
        };
    }
}

NMTOOLS_TESTING_DECLARE_CASE(array, avg_pool2d)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int array[1][1][4][4] = {
            {
                {
                    {0, 1,  2, 3},
                    {4, 5,  6, 7},
                    {8, 9, 10,11},
                    {12,13,14,15},
                }
            }
        };
        inline int kernel_size[2] = {3,3};
        inline int stride[2]  = {2,2};
        inline auto padding   = None;
        inline auto dilation  = None;
        inline auto ceil_mode = True;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline float result[1][1][2][2] = {
            {
                {
                    { 5.f, 6.5f},
                    {11.f,12.5f},
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int array[1][1][4][4] = {
            {
                {
                    {0, 1,  2, 3},
                    {4, 5,  6, 7},
                    {8, 9, 10,11},
                    {12,13,14,15},
                }
            }
        };
        inline int kernel_size[2] = {3,3};
        inline int stride[2]  = {1,1};
        inline auto padding   = None;
        inline auto dilation  = None;
        inline auto ceil_mode = True;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline float result[1][1][2][2] = {
            {
                {
                    {5.f, 6.f},
                    {9.f,10.f},
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int array[1][1][4][4] = {
            {
                {
                    {0, 1,  2, 3},
                    {4, 5,  6, 7},
                    {8, 9, 10,11},
                    {12,13,14,15},
                }
            }
        };
        inline int kernel_size[2] = {3,3};
        inline int stride[2]  = {2,1};
        inline auto padding   = None;
        inline auto dilation  = None;
        inline auto ceil_mode = True;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline float result[1][1][2][2] = {
            {
                {
                    { 5.f, 6.f},
                    {11.f,12.f},
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int array[1][1][4][4] = {
            {
                {
                    {0, 1,  2, 3},
                    {4, 5,  6, 7},
                    {8, 9, 10,11},
                    {12,13,14,15},
                }
            }
        };
        inline int kernel_size[2] = {3,3};
        inline int stride[2]  = {1,2};
        inline auto padding   = None;
        inline auto dilation  = None;
        inline auto ceil_mode = True;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline float result[1][1][2][2] = {
            {
                {
                    {5.f, 6.5f},
                    {9.f,10.5f},
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int array[1][1][4][4] = {
            {
                {
                    {0, 1,  2, 3},
                    {4, 5,  6, 7},
                    {8, 9, 10,11},
                    {12,13,14,15},
                }
            }
        };
        inline int kernel_size[2] = {3,3};
        inline int stride[2]  = {2,1};
        inline auto padding   = None;
        inline auto dilation  = None;
        inline auto ceil_mode = False;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline float result[1][1][1][2] = {
            {
                {
                    {5.f, 6.f},
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int array[1][1][4][4] = {
            {
                {
                    {0, 1,  2, 3},
                    {4, 5,  6, 7},
                    {8, 9, 10,11},
                    {12,13,14,15},
                }
            }
        };
        inline int kernel_size[2] = {3,3};
        inline int stride[2]  = {1,2};
        inline auto padding   = None;
        inline auto dilation  = None;
        inline auto ceil_mode = False;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline float result[1][1][2][1] = {
            {
                {
                    {5.f},
                    {9.f},
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int array[1][1][4][4] = {
            {
                {
                    {0, 1,  2, 3},
                    {4, 5,  6, 7},
                    {8, 9, 10,11},
                    {12,13,14,15},
                }
            }
        };
        inline int kernel_size[2] = {2,2};
        inline int stride[2]  = {1,1};
        inline auto padding   = None;
        inline auto dilation  = None;
        inline auto ceil_mode = False;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline float result[1][1][3][3] = {
            {
                {
                    { 2.5f,  3.5f,  4.5f},
                    { 6.5f,  7.5f,  8.5f},
                    {10.5f, 11.5f, 12.5f}
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline int array[1][1][4][4] = {
            {
                {
                    {0, 1,  2, 3},
                    {4, 5,  6, 7},
                    {8, 9, 10,11},
                    {12,13,14,15},
                }
            }
        };
        inline int kernel_size[2] = {2,2};
        inline int stride[2]  = {2,2};
        inline auto padding   = None;
        inline auto dilation  = None;
        inline auto ceil_mode = False;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline float result[1][1][2][2] = {
            {
                {
                    { 2.5f,  4.5f},
                    {10.5f, 12.5f},
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        inline int array[1][1][4][4] = {
            {
                {
                    {0, 1,  2, 3},
                    {4, 5,  6, 7},
                    {8, 9, 10,11},
                    {12,13,14,15},
                }
            }
        };
        inline int kernel_size[2] = {2,2};
        inline int stride[2]  = {3,3};
        inline auto padding   = None;
        inline auto dilation  = None;
        inline auto ceil_mode = False;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline float result[1][1][1][1] = {
            {
                {
                    { 2.5f},
                }
            }
        };
    }


    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        inline int array[1][1][4][4] = {
            {
                {
                    {0, 1,  2, 3},
                    {4, 5,  6, 7},
                    {8, 9, 10,11},
                    {12,13,14,15},
                }
            }
        };
        inline int kernel_size[2] = {2,2};
        inline int stride[2]  = {3,3};
        inline auto padding   = None;
        inline auto dilation  = None;
        inline auto ceil_mode = True;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline float result[1][1][2][2] = {
            {
                {
                    { 2.5f,  5.f},
                    {12.5f, 15.f},
                }
            }
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_POOLING_HPP