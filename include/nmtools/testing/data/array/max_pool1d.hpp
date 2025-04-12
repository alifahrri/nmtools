#ifndef NMTOOLS_TESTING_DATA_ARRAY_MAX_POOL1D_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_MAX_POOL1D_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"
#include "nmtools/meta.hpp"

using namespace nmtools::literals;
using nmtools::None;

NMTOOLS_TESTING_DECLARE_CASE(array, max_pool1d)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline float array[1][1][10] = {
            {
                {0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f}
            }
        };
        inline int kernel_size = 3;
        inline int stride      = 3;
        inline auto padding    = None;
        inline int dilation    = 1;
        inline auto ceil_mode  = False;
        NMTOOLS_CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline float result[1][1][3] = {
            {
                {2.f, 5.f, 8.f}
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1b)
    {
        inline float array[1][1][10] = {
            {
                {0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f}
            }
        };
        inline int kernel_size[1] = {3};
        inline int stride[1]      = {3};
        inline int padding[1]     = {0};
        inline int dilation[1]    = {1};
        inline auto ceil_mode     = False;
        NMTOOLS_CAST_ARRAYS(array);
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size);
        NMTOOLS_CAST_INDEX_ARRAYS(stride);
        NMTOOLS_CAST_INDEX_ARRAYS(padding);
        NMTOOLS_CAST_INDEX_ARRAYS(dilation);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1b)
    {
        inline float result[1][1][3] = {
            {
                {2.f, 5.f, 8.f}
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline float array[1][1][10] = {
            {
                {0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f}
            }
        };
        inline int kernel_size = 3;
        inline int stride      = 2;
        inline auto padding    = None;
        inline int dilation    = 1;
        inline auto ceil_mode  = False;
        NMTOOLS_CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline float result[1][1][4] = {
            {
                {2.f, 4.f, 6.f, 8.f}
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2b)
    {
        inline float array[1][1][10] = {
            {
                {0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f}
            }
        };
        inline int kernel_size[1] = {3};
        inline int stride[1]      = {2};
        inline int padding[1]     = {0};
        inline int dilation[1]    = {1};
        inline auto ceil_mode     = False;
        NMTOOLS_CAST_ARRAYS(array);
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size);
        NMTOOLS_CAST_INDEX_ARRAYS(stride);
        NMTOOLS_CAST_INDEX_ARRAYS(padding);
        NMTOOLS_CAST_INDEX_ARRAYS(dilation);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2b)
    {
        inline float result[1][1][4] = {
            {
                {2.f, 4.f, 6.f, 8.f}
            }
        };
    }


    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline float array[1][1][10] = {
            {
                {0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f}
            }
        };
        inline int kernel_size = 4;
        inline int stride      = 2;
        inline int padding     = 1;
        inline int dilation    = 1;
        inline auto ceil_mode  = False;
        NMTOOLS_CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline float result[1][1][5] = {
            {
                {2.f, 4.f, 6.f, 8.f, 9.f}
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3b)
    {
        inline float array[1][1][10] = {
            {
                {0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f}
            }
        };
        inline int kernel_size[1] = {4};
        inline int stride[1]      = {2};
        inline int padding[1]     = {1};
        inline int dilation[1]    = {1};
        inline auto ceil_mode     = False;
        NMTOOLS_CAST_ARRAYS(array);
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size);
        NMTOOLS_CAST_INDEX_ARRAYS(stride);
        NMTOOLS_CAST_INDEX_ARRAYS(padding);
        NMTOOLS_CAST_INDEX_ARRAYS(dilation);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3b)
    {
        inline float result[1][1][5] = {
            {
                {2.f, 4.f, 6.f, 8.f, 9.f}
            }
        };
    }


    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline float array[1][1][10] = {
            {
                {0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f}
            }
        };
        inline int kernel_size = 3;
        inline int stride      = 1;
        inline auto padding    = None;
        inline int dilation    = 2;
        inline auto ceil_mode  = False;
        NMTOOLS_CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline float result[1][1][6] = {
            {
                {4.f, 5.f, 6.f, 7.f, 8.f, 9.f}
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4b)
    {
        inline float array[1][1][10] = {
            {
                {0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f}
            }
        };
        inline int kernel_size[1] = {3};
        inline int stride[1]      = {1};
        inline int padding[1]     = {0};
        inline int dilation[1]    = {2};
        inline auto ceil_mode     = False;
        NMTOOLS_CAST_ARRAYS(array);
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size);
        NMTOOLS_CAST_INDEX_ARRAYS(stride);
        NMTOOLS_CAST_INDEX_ARRAYS(padding);
        NMTOOLS_CAST_INDEX_ARRAYS(dilation);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4b)
    {
        inline float result[1][1][6] = {
            {
                {4.f, 5.f, 6.f, 7.f, 8.f, 9.f}
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline float array[1][1][10] = {
            {
                {0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f}
            }
        };
        inline int kernel_size = 3;
        inline int stride      = 3;
        inline auto padding    = None;
        inline int dilation    = 1;
        inline auto ceil_mode  = True;
        NMTOOLS_CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline float result[1][1][4] = {
            {
                {2.f, 5.f, 8.f, 9.f}
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5b)
    {
        inline float array[1][1][10] = {
            {
                {0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f}
            }
        };
        inline int kernel_size[1] = {3};
        inline int stride[1]      = {3};
        inline int padding[1]     = {0};
        inline int dilation[1]    = {1};
        inline auto ceil_mode     = True;
        NMTOOLS_CAST_ARRAYS(array);
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size);
        NMTOOLS_CAST_INDEX_ARRAYS(stride);
        NMTOOLS_CAST_INDEX_ARRAYS(padding);
        NMTOOLS_CAST_INDEX_ARRAYS(dilation);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5b)
    {
        inline float result[1][1][4] = {
            {
                {2.f, 5.f, 8.f, 9.f}
            }
        };
    }


    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline float array[1][2][8] = {
            {
                {0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f},
                {8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f}
            }
        };
        inline int kernel_size = 4;
        inline int stride      = 2;
        inline int padding     = 1;
        inline int dilation    = 1;
        inline auto ceil_mode  = False;
        NMTOOLS_CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline float result[1][2][4] = {
            {
                { 2.f,  4.f,  6.f,  7.f},
                {10.f, 12.f, 14.f, 15.f}
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6b)
    {
        inline float array[1][2][8] = {
            {
                {0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f},
                {8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f}
            }
        };
        inline int kernel_size[1] = {4};
        inline int stride[1]      = {2};
        inline int padding[1]     = {1};
        inline int dilation[1]    = {1};
        inline auto ceil_mode     = False;
        NMTOOLS_CAST_ARRAYS(array);
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size);
        NMTOOLS_CAST_INDEX_ARRAYS(stride);
        NMTOOLS_CAST_INDEX_ARRAYS(padding);
        NMTOOLS_CAST_INDEX_ARRAYS(dilation);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6b)
    {
        inline float result[1][2][4] = {
            {
                { 2.f,  4.f,  6.f,  7.f},
                {10.f, 12.f, 14.f, 15.f}
            }
        };
    }

}

#endif // NMTOOLS_TESTING_DATA_ARRAY_MAX_POOL1D_HPP