#ifndef NMTOOLS_TESTING_DATA_INDEX_POOLING_HPP
#define NMTOOLS_TESTING_DATA_INDEX_POOLING_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

using namespace nmtools::literals;

NMTOOLS_TESTING_DECLARE_CASE(index, pool_pad)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int src_shape[4] = {1,1,4,4};
        inline int kernel_size[2] = {3,3};
        inline int stride[2] = {2,2};
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int expected[4][2] = {
            {0,0},
            {0,0},
            {0,1},
            {0,1},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1b)
    {
        inline int src_shape[4] = {1,1,4,4};
        inline int kernel_size[2] = {3,3};
        inline int stride[2] = {3,3};
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1b)
    {
        inline int expected[4][2] = {
            {0,0},
            {0,0},
            {0,2},
            {0,2},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1c)
    {
        inline int src_shape[4] = {1,1,4,4};
        inline int kernel_size[2] = {3,3};
        inline int stride[2] = {4,4};
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1c)
    {
        inline int expected[4][2] = {
            {0,0},
            {0,0},
            {0,0},
            {0,0},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int src_shape[4] = {1,1,4,4};
        inline int kernel_size[2] = {3,3};
        inline int stride[2] = {1,1};
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int expected[4][2] = {
            {0,0},
            {0,0},
            {0,0},
            {0,0},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int src_shape[4] = {1,1,4,4};
        inline int kernel_size[2] = {3,3};
        inline int stride[2] = {1,2};
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int expected[4][2] = {
            {0,0},
            {0,0},
            {0,0},
            {0,1},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int src_shape[4] = {1,1,4,4};
        inline int kernel_size[2] = {3,3};
        inline int stride[2] = {2,1};
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int expected[4][2] = {
            {0,0},
            {0,0},
            {0,1},
            {0,0},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        inline int src_shape[4] = {1,1,4,4};
        inline int kernel_size[2] = {2,2};
        inline int stride[2] = {3,3};
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline int expected[4][2] = {
            {0,0},
            {0,0},
            {0,1},
            {0,1},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10b)
    {
        inline int src_shape[4] = {1,1,4,4};
        inline int kernel_size[2] = {2,2};
        inline int stride[2] = {2,2};
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10b)
    {
        inline int expected[4][2] = {
            {0,0},
            {0,0},
            {0,0},
            {0,0},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10c)
    {
        inline int src_shape[4] = {1,1,4,4};
        inline int kernel_size[2] = {2,2};
        inline int stride[2] = {1,1};
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10c)
    {
        inline int expected[4][2] = {
            {0,0},
            {0,0},
            {0,0},
            {0,0},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        inline int src_shape[4] = {1,1,6,6};
        inline int kernel_size[2] = {3,3};
        inline int stride[2] = {2,2};
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        inline int expected[4][2] = {
            {0,0},
            {0,0},
            {0,1},
            {0,1},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        inline int src_shape[4] = {1,1,7,7};
        inline int kernel_size[2] = {3,3};
        inline int stride[2] = {2,2};
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        inline int expected[4][2] = {
            {0,0},
            {0,0},
            {0,0},
            {0,0},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12d)
    {
        inline int src_shape[4] = {1,1,7,7};
        inline int kernel_size[2] = {3,3};
        inline int stride[2] = {3,3};
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12d)
    {
        inline int expected[4][2] = {
            {0,0},
            {0,0},
            {0,1},
            {0,1},
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_INDEX_POOLING_HPP