#ifndef NMTOOLS_TESTING_DATA_ARRAY_MAX_POOL3D_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_MAX_POOL3D_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

using namespace nmtools::literals;
using nmtools::None;

NMTOOLS_TESTING_DECLARE_CASE(array, max_pool3d)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline float array[1][1][4][4][4] = {
            {
                {
                    {{ 0.f,  1.f,  2.f,  3.f}, { 4.f,  5.f,  6.f,  7.f}, { 8.f,  9.f, 10.f, 11.f}, {12.f, 13.f, 14.f, 15.f}},
                    {{16.f, 17.f, 18.f, 19.f}, {20.f, 21.f, 22.f, 23.f}, {24.f, 25.f, 26.f, 27.f}, {28.f, 29.f, 30.f, 31.f}},
                    {{32.f, 33.f, 34.f, 35.f}, {36.f, 37.f, 38.f, 39.f}, {40.f, 41.f, 42.f, 43.f}, {44.f, 45.f, 46.f, 47.f}},
                    {{48.f, 49.f, 50.f, 51.f}, {52.f, 53.f, 54.f, 55.f}, {56.f, 57.f, 58.f, 59.f}, {60.f, 61.f, 62.f, 63.f}}
                }
            }
        };
        inline int kernel_size = 2;
        inline int stride      = 2;
        inline auto padding    = None;
        inline int dilation    = 1;
        inline auto ceil_mode  = False;
        NMTOOLS_CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline float result[1][1][2][2][2] = {
            {
                {
                    {{21.f, 23.f}, {29.f, 31.f}},
                    {{53.f, 55.f}, {61.f, 63.f}}
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1b)
    {
        inline float array[1][1][4][4][4] = {
            {
                {
                    {{ 0.f,  1.f,  2.f,  3.f}, { 4.f,  5.f,  6.f,  7.f}, { 8.f,  9.f, 10.f, 11.f}, {12.f, 13.f, 14.f, 15.f}},
                    {{16.f, 17.f, 18.f, 19.f}, {20.f, 21.f, 22.f, 23.f}, {24.f, 25.f, 26.f, 27.f}, {28.f, 29.f, 30.f, 31.f}},
                    {{32.f, 33.f, 34.f, 35.f}, {36.f, 37.f, 38.f, 39.f}, {40.f, 41.f, 42.f, 43.f}, {44.f, 45.f, 46.f, 47.f}},
                    {{48.f, 49.f, 50.f, 51.f}, {52.f, 53.f, 54.f, 55.f}, {56.f, 57.f, 58.f, 59.f}, {60.f, 61.f, 62.f, 63.f}}
                }
            }
        };
        inline int kernel_size[3] = {2, 2, 2};
        inline int stride[3]      = {2, 2, 2};
        inline int padding[3]     = {0, 0, 0};
        inline int dilation[3]    = {1, 1, 1};
        inline auto ceil_mode     = False;
        NMTOOLS_CAST_ARRAYS(array);
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size);
        NMTOOLS_CAST_INDEX_ARRAYS(stride);
        NMTOOLS_CAST_INDEX_ARRAYS(padding);
        NMTOOLS_CAST_INDEX_ARRAYS(dilation);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1b)
    {
        inline float result[1][1][2][2][2] = {
            {
                {
                    {{21.f, 23.f}, {29.f, 31.f}},
                    {{53.f, 55.f}, {61.f, 63.f}}
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline float array[1][1][4][4][4] = {
            {
                {
                    {{ 0.f,  1.f,  2.f,  3.f}, { 4.f,  5.f,  6.f,  7.f}, { 8.f,  9.f, 10.f, 11.f}, {12.f, 13.f, 14.f, 15.f}},
                    {{16.f, 17.f, 18.f, 19.f}, {20.f, 21.f, 22.f, 23.f}, {24.f, 25.f, 26.f, 27.f}, {28.f, 29.f, 30.f, 31.f}},
                    {{32.f, 33.f, 34.f, 35.f}, {36.f, 37.f, 38.f, 39.f}, {40.f, 41.f, 42.f, 43.f}, {44.f, 45.f, 46.f, 47.f}},
                    {{48.f, 49.f, 50.f, 51.f}, {52.f, 53.f, 54.f, 55.f}, {56.f, 57.f, 58.f, 59.f}, {60.f, 61.f, 62.f, 63.f}}
                }
            }
        };
        inline int kernel_size = 3;
        inline int stride      = 3;
        inline auto padding    = None;
        inline int dilation    = 1;
        inline auto ceil_mode  = False;
        NMTOOLS_CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline float result[1][1][1][1][1] = {
            {
                {
                    {{42.f}}
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2b)
    {
        inline float array[1][1][4][4][4] = {
            {
                {
                    {{ 0.f,  1.f,  2.f,  3.f}, { 4.f,  5.f,  6.f,  7.f}, { 8.f,  9.f, 10.f, 11.f}, {12.f, 13.f, 14.f, 15.f}},
                    {{16.f, 17.f, 18.f, 19.f}, {20.f, 21.f, 22.f, 23.f}, {24.f, 25.f, 26.f, 27.f}, {28.f, 29.f, 30.f, 31.f}},
                    {{32.f, 33.f, 34.f, 35.f}, {36.f, 37.f, 38.f, 39.f}, {40.f, 41.f, 42.f, 43.f}, {44.f, 45.f, 46.f, 47.f}},
                    {{48.f, 49.f, 50.f, 51.f}, {52.f, 53.f, 54.f, 55.f}, {56.f, 57.f, 58.f, 59.f}, {60.f, 61.f, 62.f, 63.f}}
                }
            }
        };
        inline int kernel_size[3] = {3, 3, 3};
        inline int stride[3]      = {3, 3, 3};
        inline int padding[3]     = {0, 0, 0};
        inline int dilation[3]    = {1, 1, 1};
        inline auto ceil_mode     = False;
        NMTOOLS_CAST_ARRAYS(array);
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size);
        NMTOOLS_CAST_INDEX_ARRAYS(stride);
        NMTOOLS_CAST_INDEX_ARRAYS(padding);
        NMTOOLS_CAST_INDEX_ARRAYS(dilation);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2b)
    {
        inline float result[1][1][1][1][1] = {
            {
                {
                    {{42.f}}
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline float array[1][1][4][4][4] = {
            {
                {
                    {{ 0.f,  1.f,  2.f,  3.f}, { 4.f,  5.f,  6.f,  7.f}, { 8.f,  9.f, 10.f, 11.f}, {12.f, 13.f, 14.f, 15.f}},
                    {{16.f, 17.f, 18.f, 19.f}, {20.f, 21.f, 22.f, 23.f}, {24.f, 25.f, 26.f, 27.f}, {28.f, 29.f, 30.f, 31.f}},
                    {{32.f, 33.f, 34.f, 35.f}, {36.f, 37.f, 38.f, 39.f}, {40.f, 41.f, 42.f, 43.f}, {44.f, 45.f, 46.f, 47.f}},
                    {{48.f, 49.f, 50.f, 51.f}, {52.f, 53.f, 54.f, 55.f}, {56.f, 57.f, 58.f, 59.f}, {60.f, 61.f, 62.f, 63.f}}
                }
            }
        };
        inline int kernel_size = 2;
        inline int stride      = 2;
        inline auto padding    = None;
        inline int dilation    = 1;
        inline auto ceil_mode  = False;
        NMTOOLS_CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline float result[1][1][2][2][2] = {
            {
                {
                    {{21.f, 23.f}, {29.f, 31.f}},
                    {{53.f, 55.f}, {61.f, 63.f}}
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3b)
    {
        inline float array[1][1][4][4][4] = {
            {
                {
                    {{ 0.f,  1.f,  2.f,  3.f}, { 4.f,  5.f,  6.f,  7.f}, { 8.f,  9.f, 10.f, 11.f}, {12.f, 13.f, 14.f, 15.f}},
                    {{16.f, 17.f, 18.f, 19.f}, {20.f, 21.f, 22.f, 23.f}, {24.f, 25.f, 26.f, 27.f}, {28.f, 29.f, 30.f, 31.f}},
                    {{32.f, 33.f, 34.f, 35.f}, {36.f, 37.f, 38.f, 39.f}, {40.f, 41.f, 42.f, 43.f}, {44.f, 45.f, 46.f, 47.f}},
                    {{48.f, 49.f, 50.f, 51.f}, {52.f, 53.f, 54.f, 55.f}, {56.f, 57.f, 58.f, 59.f}, {60.f, 61.f, 62.f, 63.f}}
                }
            }
        };
        inline int kernel_size[3] = {2, 2, 2};
        inline int stride[3]      = {2, 2, 2};
        inline int padding[3]     = {0, 0, 0};
        inline int dilation[3]    = {1, 1, 1};
        inline auto ceil_mode     = False;
        NMTOOLS_CAST_ARRAYS(array);
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size);
        NMTOOLS_CAST_INDEX_ARRAYS(stride);
        NMTOOLS_CAST_INDEX_ARRAYS(padding);
        NMTOOLS_CAST_INDEX_ARRAYS(dilation);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3b)
    {
        inline float result[1][1][2][2][2] = {
            {
                {
                    {{21.f, 23.f}, {29.f, 31.f}},
                    {{53.f, 55.f}, {61.f, 63.f}}
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline float array[1][1][4][4][4] = {
            {
                {
                    {{ 0.f,  1.f,  2.f,  3.f}, { 4.f,  5.f,  6.f,  7.f}, { 8.f,  9.f, 10.f, 11.f}, {12.f, 13.f, 14.f, 15.f}},
                    {{16.f, 17.f, 18.f, 19.f}, {20.f, 21.f, 22.f, 23.f}, {24.f, 25.f, 26.f, 27.f}, {28.f, 29.f, 30.f, 31.f}},
                    {{32.f, 33.f, 34.f, 35.f}, {36.f, 37.f, 38.f, 39.f}, {40.f, 41.f, 42.f, 43.f}, {44.f, 45.f, 46.f, 47.f}},
                    {{48.f, 49.f, 50.f, 51.f}, {52.f, 53.f, 54.f, 55.f}, {56.f, 57.f, 58.f, 59.f}, {60.f, 61.f, 62.f, 63.f}}
                }
            }
        };
        inline int kernel_size = 2;
        inline int stride      = 3;
        inline auto padding    = None;
        inline int dilation    = 1;
        inline auto ceil_mode  = False;
        NMTOOLS_CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline float result[1][1][1][1][1] = {
            {
                {
                    {{21.f}}
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4b)
    {
        inline float array[1][1][4][4][4] = {
            {
                {
                    {{ 0.f,  1.f,  2.f,  3.f}, { 4.f,  5.f,  6.f,  7.f}, { 8.f,  9.f, 10.f, 11.f}, {12.f, 13.f, 14.f, 15.f}},
                    {{16.f, 17.f, 18.f, 19.f}, {20.f, 21.f, 22.f, 23.f}, {24.f, 25.f, 26.f, 27.f}, {28.f, 29.f, 30.f, 31.f}},
                    {{32.f, 33.f, 34.f, 35.f}, {36.f, 37.f, 38.f, 39.f}, {40.f, 41.f, 42.f, 43.f}, {44.f, 45.f, 46.f, 47.f}},
                    {{48.f, 49.f, 50.f, 51.f}, {52.f, 53.f, 54.f, 55.f}, {56.f, 57.f, 58.f, 59.f}, {60.f, 61.f, 62.f, 63.f}}
                }
            }
        };
        inline int kernel_size[3] = {2, 2, 2};
        inline int stride[3]      = {3, 3, 3};
        inline int padding[3]     = {0, 0, 0};
        inline int dilation[3]    = {1, 1, 1};
        inline auto ceil_mode     = False;
        NMTOOLS_CAST_ARRAYS(array);
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size);
        NMTOOLS_CAST_INDEX_ARRAYS(stride);
        NMTOOLS_CAST_INDEX_ARRAYS(padding);
        NMTOOLS_CAST_INDEX_ARRAYS(dilation);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4b)
    {
        inline float result[1][1][1][1][1] = {
            {
                {
                    {{21.f}}
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline float array[1][1][4][4][4] = {
            {
                {
                    {{ 0.f,  1.f,  2.f,  3.f}, { 4.f,  5.f,  6.f,  7.f}, { 8.f,  9.f, 10.f, 11.f}, {12.f, 13.f, 14.f, 15.f}},
                    {{16.f, 17.f, 18.f, 19.f}, {20.f, 21.f, 22.f, 23.f}, {24.f, 25.f, 26.f, 27.f}, {28.f, 29.f, 30.f, 31.f}},
                    {{32.f, 33.f, 34.f, 35.f}, {36.f, 37.f, 38.f, 39.f}, {40.f, 41.f, 42.f, 43.f}, {44.f, 45.f, 46.f, 47.f}},
                    {{48.f, 49.f, 50.f, 51.f}, {52.f, 53.f, 54.f, 55.f}, {56.f, 57.f, 58.f, 59.f}, {60.f, 61.f, 62.f, 63.f}}
                }
            }
        };
        inline int kernel_size = 2;
        inline int stride      = 2;
        inline int padding     = 1;
        inline int dilation    = 1;
        inline auto ceil_mode  = False;
        NMTOOLS_CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline float result[1][1][3][3][3] = {
            {
                {
                    {{ 0.f,  2.f,  3.f}, { 8.f, 10.f, 11.f}, {12.f, 14.f, 15.f}},
                    {{32.f, 34.f, 35.f}, {40.f, 42.f, 43.f}, {44.f, 46.f, 47.f}},
                    {{48.f, 50.f, 51.f}, {56.f, 58.f, 59.f}, {60.f, 62.f, 63.f}}
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5b)
    {
        inline float array[1][1][4][4][4] = {
            {
                {
                    {{ 0.f,  1.f,  2.f,  3.f}, { 4.f,  5.f,  6.f,  7.f}, { 8.f,  9.f, 10.f, 11.f}, {12.f, 13.f, 14.f, 15.f}},
                    {{16.f, 17.f, 18.f, 19.f}, {20.f, 21.f, 22.f, 23.f}, {24.f, 25.f, 26.f, 27.f}, {28.f, 29.f, 30.f, 31.f}},
                    {{32.f, 33.f, 34.f, 35.f}, {36.f, 37.f, 38.f, 39.f}, {40.f, 41.f, 42.f, 43.f}, {44.f, 45.f, 46.f, 47.f}},
                    {{48.f, 49.f, 50.f, 51.f}, {52.f, 53.f, 54.f, 55.f}, {56.f, 57.f, 58.f, 59.f}, {60.f, 61.f, 62.f, 63.f}}
                }
            }
        };
        inline int kernel_size[3] = {2, 2, 2};
        inline int stride[3]      = {2, 2, 2};
        inline int padding[3]     = {1, 1, 1};
        inline int dilation[3]    = {1, 1, 1};
        inline auto ceil_mode     = False;
        NMTOOLS_CAST_ARRAYS(array);
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size);
        NMTOOLS_CAST_INDEX_ARRAYS(stride);
        NMTOOLS_CAST_INDEX_ARRAYS(padding);
        NMTOOLS_CAST_INDEX_ARRAYS(dilation);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5b)
    {
        inline float result[1][1][3][3][3] = {
            {
                {
                    {{ 0.f,  2.f,  3.f}, { 8.f, 10.f, 11.f}, {12.f, 14.f, 15.f}},
                    {{32.f, 34.f, 35.f}, {40.f, 42.f, 43.f}, {44.f, 46.f, 47.f}},
                    {{48.f, 50.f, 51.f}, {56.f, 58.f, 59.f}, {60.f, 62.f, 63.f}}
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline float array[1][1][4][4][4] = {
            {
                {
                    {{ 0.f,  1.f,  2.f,  3.f}, { 4.f,  5.f,  6.f,  7.f}, { 8.f,  9.f, 10.f, 11.f}, {12.f, 13.f, 14.f, 15.f}},
                    {{16.f, 17.f, 18.f, 19.f}, {20.f, 21.f, 22.f, 23.f}, {24.f, 25.f, 26.f, 27.f}, {28.f, 29.f, 30.f, 31.f}},
                    {{32.f, 33.f, 34.f, 35.f}, {36.f, 37.f, 38.f, 39.f}, {40.f, 41.f, 42.f, 43.f}, {44.f, 45.f, 46.f, 47.f}},
                    {{48.f, 49.f, 50.f, 51.f}, {52.f, 53.f, 54.f, 55.f}, {56.f, 57.f, 58.f, 59.f}, {60.f, 61.f, 62.f, 63.f}}
                }
            }
        };
        inline int kernel_size = 2;
        inline int stride      = 2;
        inline auto padding    = None;
        inline int dilation    = 2;
        inline auto ceil_mode  = False;
        NMTOOLS_CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline float result[1][1][1][1][1] = {
            {
                {
                    {{42.f}}
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6b)
    {
        inline float array[1][1][4][4][4] = {
            {
                {
                    {{ 0.f,  1.f,  2.f,  3.f}, { 4.f,  5.f,  6.f,  7.f}, { 8.f,  9.f, 10.f, 11.f}, {12.f, 13.f, 14.f, 15.f}},
                    {{16.f, 17.f, 18.f, 19.f}, {20.f, 21.f, 22.f, 23.f}, {24.f, 25.f, 26.f, 27.f}, {28.f, 29.f, 30.f, 31.f}},
                    {{32.f, 33.f, 34.f, 35.f}, {36.f, 37.f, 38.f, 39.f}, {40.f, 41.f, 42.f, 43.f}, {44.f, 45.f, 46.f, 47.f}},
                    {{48.f, 49.f, 50.f, 51.f}, {52.f, 53.f, 54.f, 55.f}, {56.f, 57.f, 58.f, 59.f}, {60.f, 61.f, 62.f, 63.f}}
                }
            }
        };
        inline int kernel_size[3] = {2, 2, 2};
        inline int stride[3]      = {2, 2, 2};
        inline int padding[3]     = {0, 0, 0};
        inline int dilation[3]    = {2, 2, 2};
        inline auto ceil_mode     = False;
        NMTOOLS_CAST_ARRAYS(array);
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size);
        NMTOOLS_CAST_INDEX_ARRAYS(stride);
        NMTOOLS_CAST_INDEX_ARRAYS(padding);
        NMTOOLS_CAST_INDEX_ARRAYS(dilation);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6b)
    {
        inline float result[1][1][1][1][1] = {
            {
                {
                    {{42.f}}
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline float array[1][1][4][5][6] = {{{
            {
                { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f},
                { 6.f, 7.f, 8.f, 9.f,10.f,11.f},
                {12.f,13.f,14.f,15.f,16.f,17.f},
                {18.f,19.f,20.f,21.f,22.f,23.f},
                {24.f,25.f,26.f,27.f,28.f,29.f}
            },
            {
                {30.f,31.f,32.f,33.f,34.f,35.f},
                {36.f,37.f,38.f,39.f,40.f,41.f},
                {42.f,43.f,44.f,45.f,46.f,47.f},
                {48.f,49.f,50.f,51.f,52.f,53.f},
                {54.f,55.f,56.f,57.f,58.f,59.f}
            },
            {
                {60.f,61.f,62.f,63.f,64.f,65.f},
                {66.f,67.f,68.f,69.f,70.f,71.f},
                {72.f,73.f,74.f,75.f,76.f,77.f},
                {78.f,79.f,80.f,81.f,82.f,83.f},
                {84.f,85.f,86.f,87.f,88.f,89.f}
            },
            {
                {90.f,91.f,92.f,93.f,94.f,95.f},
                {96.f,97.f,98.f,99.f,100.f,101.f},
                {102.f,103.f,104.f,105.f,106.f,107.f},
                {108.f,109.f,110.f,111.f,112.f,113.f},
                {114.f,115.f,116.f,117.f,118.f,119.f}
            }
        }}};
        inline int kernel_size[3] = {2, 3, 4};
        inline int stride[3]      = {2, 3, 4};
        inline int padding[3]     = {0, 0, 0};
        inline int dilation[3]    = {1, 1, 1};
        inline auto ceil_mode     = False;
        NMTOOLS_CAST_ARRAYS(array);
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size);
        NMTOOLS_CAST_INDEX_ARRAYS(stride);
        NMTOOLS_CAST_INDEX_ARRAYS(padding);
        NMTOOLS_CAST_INDEX_ARRAYS(dilation);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline float result[1][1][2][1][1] = {
            {
                {
                    {{45.f}},
                    {{105.f}}
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7b)
    {
        inline float array[1][1][4][5][6] = {{{
            {
                { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f},
                { 6.f, 7.f, 8.f, 9.f,10.f,11.f},
                {12.f,13.f,14.f,15.f,16.f,17.f},
                {18.f,19.f,20.f,21.f,22.f,23.f},
                {24.f,25.f,26.f,27.f,28.f,29.f}
            },
            {
                {30.f,31.f,32.f,33.f,34.f,35.f},
                {36.f,37.f,38.f,39.f,40.f,41.f},
                {42.f,43.f,44.f,45.f,46.f,47.f},
                {48.f,49.f,50.f,51.f,52.f,53.f},
                {54.f,55.f,56.f,57.f,58.f,59.f}
            },
            {
                {60.f,61.f,62.f,63.f,64.f,65.f},
                {66.f,67.f,68.f,69.f,70.f,71.f},
                {72.f,73.f,74.f,75.f,76.f,77.f},
                {78.f,79.f,80.f,81.f,82.f,83.f},
                {84.f,85.f,86.f,87.f,88.f,89.f}
            },
            {
                {90.f,91.f,92.f,93.f,94.f,95.f},
                {96.f,97.f,98.f,99.f,100.f,101.f},
                {102.f,103.f,104.f,105.f,106.f,107.f},
                {108.f,109.f,110.f,111.f,112.f,113.f},
                {114.f,115.f,116.f,117.f,118.f,119.f}
            }
        }}};
        inline int kernel_size[3] = {2, 3, 4};
        inline int stride[3]      = {2, 3, 4};
        inline auto padding   = None;
        inline auto dilation  = None;
        inline auto ceil_mode = False;
        NMTOOLS_CAST_ARRAYS(array);
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size);
        NMTOOLS_CAST_INDEX_ARRAYS(stride);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7b)
    {
        inline float result[1][1][2][1][1] = {
            {
                {
                    {{45.f}},
                    {{105.f}}
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7c)
    {
        inline float array[1][1][4][5][6] = {{{
            {
                { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f},
                { 6.f, 7.f, 8.f, 9.f,10.f,11.f},
                {12.f,13.f,14.f,15.f,16.f,17.f},
                {18.f,19.f,20.f,21.f,22.f,23.f},
                {24.f,25.f,26.f,27.f,28.f,29.f}
            },
            {
                {30.f,31.f,32.f,33.f,34.f,35.f},
                {36.f,37.f,38.f,39.f,40.f,41.f},
                {42.f,43.f,44.f,45.f,46.f,47.f},
                {48.f,49.f,50.f,51.f,52.f,53.f},
                {54.f,55.f,56.f,57.f,58.f,59.f}
            },
            {
                {60.f,61.f,62.f,63.f,64.f,65.f},
                {66.f,67.f,68.f,69.f,70.f,71.f},
                {72.f,73.f,74.f,75.f,76.f,77.f},
                {78.f,79.f,80.f,81.f,82.f,83.f},
                {84.f,85.f,86.f,87.f,88.f,89.f}
            },
            {
                {90.f,91.f,92.f,93.f,94.f,95.f},
                {96.f,97.f,98.f,99.f,100.f,101.f},
                {102.f,103.f,104.f,105.f,106.f,107.f},
                {108.f,109.f,110.f,111.f,112.f,113.f},
                {114.f,115.f,116.f,117.f,118.f,119.f}
            }
        }}};
        inline int kernel_size[3] = {2, 3, 4};
        inline auto stride    = None;
        inline auto padding   = None;
        inline auto dilation  = None;
        inline auto ceil_mode = False;
        NMTOOLS_CAST_ARRAYS(array);
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7c)
    {
        inline float result[1][1][2][1][1] = {
            {
                {
                    {{45.f}},
                    {{105.f}}
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline float array[1][1][4][5][6] = {{{
            {{ 0.f, 1.f, 2.f, 3.f, 4.f, 5.f}, { 6.f, 7.f, 8.f, 9.f,10.f,11.f}, {12.f,13.f,14.f,15.f,16.f,17.f}, {18.f,19.f,20.f,21.f,22.f,23.f}, {24.f,25.f,26.f,27.f,28.f,29.f}},
            {{30.f,31.f,32.f,33.f,34.f,35.f}, {36.f,37.f,38.f,39.f,40.f,41.f}, {42.f,43.f,44.f,45.f,46.f,47.f}, {48.f,49.f,50.f,51.f,52.f,53.f}, {54.f,55.f,56.f,57.f,58.f,59.f}},
            {{60.f,61.f,62.f,63.f,64.f,65.f}, {66.f,67.f,68.f,69.f,70.f,71.f}, {72.f,73.f,74.f,75.f,76.f,77.f}, {78.f,79.f,80.f,81.f,82.f,83.f}, {84.f,85.f,86.f,87.f,88.f,89.f}},
            {{90.f,91.f,92.f,93.f,94.f,95.f}, {96.f,97.f,98.f,99.f,100.f,101.f}, {102.f,103.f,104.f,105.f,106.f,107.f}, {108.f,109.f,110.f,111.f,112.f,113.f}, {114.f,115.f,116.f,117.f,118.f,119.f}}
        }}};
        inline int kernel_size[3] = {4, 2, 3};
        inline int stride[3]      = {4, 2, 3};
        inline int padding[3]     = {0, 0, 0};
        inline int dilation[3]    = {1, 1, 1};
        inline auto ceil_mode     = False;
        NMTOOLS_CAST_ARRAYS(array);
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size);
        NMTOOLS_CAST_INDEX_ARRAYS(stride);
        NMTOOLS_CAST_INDEX_ARRAYS(padding);
        NMTOOLS_CAST_INDEX_ARRAYS(dilation);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline float result[1][1][1][2][2] = {
            {
                {
                    {
                        { 98.f, 101.f},
                        {110.f, 113.f}
                    }
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        inline float array[1][1][4][5][6] = {{{
            {{ 0.f, 1.f, 2.f, 3.f, 4.f, 5.f}, { 6.f, 7.f, 8.f, 9.f,10.f,11.f}, {12.f,13.f,14.f,15.f,16.f,17.f}, {18.f,19.f,20.f,21.f,22.f,23.f}, {24.f,25.f,26.f,27.f,28.f,29.f}},
            {{30.f,31.f,32.f,33.f,34.f,35.f}, {36.f,37.f,38.f,39.f,40.f,41.f}, {42.f,43.f,44.f,45.f,46.f,47.f}, {48.f,49.f,50.f,51.f,52.f,53.f}, {54.f,55.f,56.f,57.f,58.f,59.f}},
            {{60.f,61.f,62.f,63.f,64.f,65.f}, {66.f,67.f,68.f,69.f,70.f,71.f}, {72.f,73.f,74.f,75.f,76.f,77.f}, {78.f,79.f,80.f,81.f,82.f,83.f}, {84.f,85.f,86.f,87.f,88.f,89.f}},
            {{90.f,91.f,92.f,93.f,94.f,95.f}, {96.f,97.f,98.f,99.f,100.f,101.f}, {102.f,103.f,104.f,105.f,106.f,107.f}, {108.f,109.f,110.f,111.f,112.f,113.f}, {114.f,115.f,116.f,117.f,118.f,119.f}}
        }}};
        inline int kernel_size[3] = {4, 2, 3};
        inline int stride         = 2;
        inline auto padding       = None;
        inline auto dilation      = None;
        inline auto ceil_mode     = False;
        NMTOOLS_CAST_ARRAYS(array);
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline float result[1][1][1][2][2] = {
            {
                {
                    { { 98.f, 100.f}, {110.f, 112.f} }
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        inline float array[1][1][4][5][6] = {{{
            {{ 0.f, 1.f, 2.f, 3.f, 4.f, 5.f}, { 6.f, 7.f, 8.f, 9.f,10.f,11.f}, {12.f,13.f,14.f,15.f,16.f,17.f}, {18.f,19.f,20.f,21.f,22.f,23.f}, {24.f,25.f,26.f,27.f,28.f,29.f}},
            {{30.f,31.f,32.f,33.f,34.f,35.f}, {36.f,37.f,38.f,39.f,40.f,41.f}, {42.f,43.f,44.f,45.f,46.f,47.f}, {48.f,49.f,50.f,51.f,52.f,53.f}, {54.f,55.f,56.f,57.f,58.f,59.f}},
            {{60.f,61.f,62.f,63.f,64.f,65.f}, {66.f,67.f,68.f,69.f,70.f,71.f}, {72.f,73.f,74.f,75.f,76.f,77.f}, {78.f,79.f,80.f,81.f,82.f,83.f}, {84.f,85.f,86.f,87.f,88.f,89.f}},
            {{90.f,91.f,92.f,93.f,94.f,95.f}, {96.f,97.f,98.f,99.f,100.f,101.f}, {102.f,103.f,104.f,105.f,106.f,107.f}, {108.f,109.f,110.f,111.f,112.f,113.f}, {114.f,115.f,116.f,117.f,118.f,119.f}}
        }}};
        inline int kernel_size[3] = {4, 2, 3};
        inline int stride         = 2;
        inline auto padding       = None;
        inline auto dilation      = None;
        inline auto ceil_mode     = True;
        NMTOOLS_CAST_ARRAYS(array);
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline float result[1][1][1][3][3] = {
            {
                {
                    { { 98.f, 100.f, 101.f}, {110.f, 112.f, 113.f}, {116.f, 118.f, 119.f} }
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        inline float array[1][1][4][5][6] = {{{
            {{ 0.f, 1.f, 2.f, 3.f, 4.f, 5.f}, { 6.f, 7.f, 8.f, 9.f,10.f,11.f}, {12.f,13.f,14.f,15.f,16.f,17.f}, {18.f,19.f,20.f,21.f,22.f,23.f}, {24.f,25.f,26.f,27.f,28.f,29.f}},
            {{30.f,31.f,32.f,33.f,34.f,35.f}, {36.f,37.f,38.f,39.f,40.f,41.f}, {42.f,43.f,44.f,45.f,46.f,47.f}, {48.f,49.f,50.f,51.f,52.f,53.f}, {54.f,55.f,56.f,57.f,58.f,59.f}},
            {{60.f,61.f,62.f,63.f,64.f,65.f}, {66.f,67.f,68.f,69.f,70.f,71.f}, {72.f,73.f,74.f,75.f,76.f,77.f}, {78.f,79.f,80.f,81.f,82.f,83.f}, {84.f,85.f,86.f,87.f,88.f,89.f}},
            {{90.f,91.f,92.f,93.f,94.f,95.f}, {96.f,97.f,98.f,99.f,100.f,101.f}, {102.f,103.f,104.f,105.f,106.f,107.f}, {108.f,109.f,110.f,111.f,112.f,113.f}, {114.f,115.f,116.f,117.f,118.f,119.f}}
        }}};
        inline int kernel_size[3] = {4, 2, 3};
        inline int stride         = 2;
        inline int padding[3]     = {0, 1, 1};
        inline auto dilation      = None;
        inline auto ceil_mode     = True;
        NMTOOLS_CAST_ARRAYS(array);
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size);
        NMTOOLS_CAST_INDEX_ARRAYS(padding);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        inline float result[1][1][1][3][4] = {
            {
                {
                    { { 91.f,  93.f,  95.f,  95.f}, {103.f, 105.f, 107.f, 107.f}, {115.f, 117.f, 119.f, 119.f} }
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11b)
    {
        inline float array[1][1][4][5][6] = {{{
            {{ 0.f, 1.f, 2.f, 3.f, 4.f, 5.f}, { 6.f, 7.f, 8.f, 9.f,10.f,11.f}, {12.f,13.f,14.f,15.f,16.f,17.f}, {18.f,19.f,20.f,21.f,22.f,23.f}, {24.f,25.f,26.f,27.f,28.f,29.f}},
            {{30.f,31.f,32.f,33.f,34.f,35.f}, {36.f,37.f,38.f,39.f,40.f,41.f}, {42.f,43.f,44.f,45.f,46.f,47.f}, {48.f,49.f,50.f,51.f,52.f,53.f}, {54.f,55.f,56.f,57.f,58.f,59.f}},
            {{60.f,61.f,62.f,63.f,64.f,65.f}, {66.f,67.f,68.f,69.f,70.f,71.f}, {72.f,73.f,74.f,75.f,76.f,77.f}, {78.f,79.f,80.f,81.f,82.f,83.f}, {84.f,85.f,86.f,87.f,88.f,89.f}},
            {{90.f,91.f,92.f,93.f,94.f,95.f}, {96.f,97.f,98.f,99.f,100.f,101.f}, {102.f,103.f,104.f,105.f,106.f,107.f}, {108.f,109.f,110.f,111.f,112.f,113.f}, {114.f,115.f,116.f,117.f,118.f,119.f}}
        }}};
        inline int kernel_size[3] = {4, 2, 3};
        inline int stride[3]      = {2, 2, 2};
        inline int padding[3]     = {0, 1, 1};
        inline auto dilation      = None;
        inline auto ceil_mode     = True;
        NMTOOLS_CAST_ARRAYS(array);
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size);
        NMTOOLS_CAST_INDEX_ARRAYS(padding);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11b)
    {
        inline float result[1][1][1][3][4] = {
            {
                {
                    { { 91.f,  93.f,  95.f,  95.f}, {103.f, 105.f, 107.f, 107.f}, {115.f, 117.f, 119.f, 119.f} }
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        inline float array[1][1][4][5][6] = {{{
            {{ 0.f, 1.f, 2.f, 3.f, 4.f, 5.f}, { 6.f, 7.f, 8.f, 9.f,10.f,11.f}, {12.f,13.f,14.f,15.f,16.f,17.f}, {18.f,19.f,20.f,21.f,22.f,23.f}, {24.f,25.f,26.f,27.f,28.f,29.f}},
            {{30.f,31.f,32.f,33.f,34.f,35.f}, {36.f,37.f,38.f,39.f,40.f,41.f}, {42.f,43.f,44.f,45.f,46.f,47.f}, {48.f,49.f,50.f,51.f,52.f,53.f}, {54.f,55.f,56.f,57.f,58.f,59.f}},
            {{60.f,61.f,62.f,63.f,64.f,65.f}, {66.f,67.f,68.f,69.f,70.f,71.f}, {72.f,73.f,74.f,75.f,76.f,77.f}, {78.f,79.f,80.f,81.f,82.f,83.f}, {84.f,85.f,86.f,87.f,88.f,89.f}},
            {{90.f,91.f,92.f,93.f,94.f,95.f}, {96.f,97.f,98.f,99.f,100.f,101.f}, {102.f,103.f,104.f,105.f,106.f,107.f}, {108.f,109.f,110.f,111.f,112.f,113.f}, {114.f,115.f,116.f,117.f,118.f,119.f}}
        }}};
        inline int kernel_size[3] = {4, 2, 3};
        inline int stride         = 2;
        inline int padding[3]     = {0, 1, 1};
        inline auto dilation      = None;
        inline auto ceil_mode     = False;
        NMTOOLS_CAST_ARRAYS(array);
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size);
        NMTOOLS_CAST_INDEX_ARRAYS(padding);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        inline float result[1][1][1][3][3] = {
            {
                {
                    { { 91.f,  93.f,  95.f}, {103.f, 105.f, 107.f}, {115.f, 117.f, 119.f} }
                }
            }
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_MAX_POOL3D_HPP