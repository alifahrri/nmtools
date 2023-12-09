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
        inline int stride[2] = {2,2};
        inline int ceil_mode = True;
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
        inline int stride[2] = {1,1};
        inline int ceil_mode = True;
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
        inline int stride[2] = {1,2};
        inline int ceil_mode = True;
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
        inline int stride[2] = {2,1};
        inline int ceil_mode = True;
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
        inline int stride[2] = {2,1};
        inline int ceil_mode = False;
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
        inline int stride[2] = {1,2};
        inline int ceil_mode = False;
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
        inline int stride[2] = {1,1};
        inline int ceil_mode = False;
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
        inline int stride[2] = {2,2};
        inline int ceil_mode = False;
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
        inline int stride[2] = {3,3};
        inline int ceil_mode = False;
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
        inline int stride[2] = {3,3};
        inline int ceil_mode = True;
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
        inline int stride[2] = {2,2};
        inline int ceil_mode = True;
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
        inline int stride[2] = {1,1};
        inline int ceil_mode = True;
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
        inline int stride[2] = {2,1};
        inline int ceil_mode = True;
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
        inline int stride[2] = {1,2};
        inline int ceil_mode = True;
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
        inline int stride[2] = {2,1};
        inline int ceil_mode = False;
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
        inline int stride[2] = {1,2};
        inline int ceil_mode = False;
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
        inline int stride[2] = {1,1};
        inline int ceil_mode = False;
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
        inline int stride[2] = {2,2};
        inline int ceil_mode = False;
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
        inline int stride[2] = {3,3};
        inline int ceil_mode = False;
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
        inline int stride[2] = {3,3};
        inline int ceil_mode = True;
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