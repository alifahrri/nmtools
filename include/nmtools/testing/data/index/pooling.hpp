#ifndef NMTOOLS_TESTING_DATA_INDEX_POOLING_HPP
#define NMTOOLS_TESTING_DATA_INDEX_POOLING_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

using namespace nmtools::literals;

NMTOOLS_TESTING_DECLARE_CASE(index, shape_pool2d)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int shape[4] = {1,1,4,4};
        inline int kernel_size[2] = {3,3};
        inline int stride[2] = {2,2};
        inline int ceil_mode = true;
        inline auto shape_ct       = nmtools_tuple{1_ct,1_ct,4_ct,4_ct};
        inline auto kernel_size_ct = nmtools_tuple{3_ct,3_ct};
        inline auto stride_ct      = nmtools_tuple{2_ct,2_ct};
        inline auto ceil_mode_ct   = nmtools::True;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[4] = {1,1,2,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int shape[4] = {1,1,4,4};
        inline int kernel_size[2] = {3,3};
        inline int stride[2] = {2,2};
        inline int ceil_mode = false;
        inline auto shape_ct = nmtools_tuple{1_ct,1_ct,4_ct,4_ct};
        inline auto kernel_size_ct = nmtools_tuple{3_ct,3_ct};
        inline auto stride_ct      = nmtools_tuple{2_ct,2_ct};
        inline auto ceil_mode_ct   = False;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[4] = {1,1,1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int shape[4] = {1,3,32,32};
        inline int kernel_size[2] = {2,2};
        inline int stride[2] = {1,1};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[4] = {1,3,31,31};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int shape[4] = {1,3,32,32};
        inline int kernel_size[2] = {2,2};
        inline int stride[2] = {2,2};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[4] = {1,3,16,16};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int shape[4] = {1,8,28,28};
        inline int kernel_size[2] = {2,2};
        inline int stride[2] = {2,2};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int result[4] = {1,8,14,14};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int shape[4] = {1,16,14,14};
        inline int kernel_size[2] = {3,3};
        inline int stride[2] = {3,3};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int result[4] = {1,16,4,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int shape[3] = {16,14,14};
        inline int kernel_size[2] = {3,3};
        inline int stride[2] = {3,3};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int result[3] = {16,4,4};
    }
}

NMTOOLS_TESTING_DECLARE_CASE(index, constexpr_shape_pool2d)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr inline int shape[4] = {1,1,4,4};
        constexpr inline int kernel_size[2] = {3,3};
        constexpr inline int stride[2] = {2,2};
        constexpr inline int ceil_mode = true;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(kernel_size)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline int result[4] = {1,1,2,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        constexpr inline int shape[4] = {1,1,4,4};
        constexpr inline int kernel_size[2] = {3,3};
        constexpr inline int stride[2] = {2,2};
        constexpr inline int ceil_mode = false;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(kernel_size)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        constexpr inline int result[4] = {1,1,1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        constexpr inline int shape[4] = {1,3,32,32};
        constexpr inline int kernel_size[2] = {2,2};
        constexpr inline int stride[2] = {1,1};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(kernel_size)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        constexpr inline int result[4] = {1,3,31,31};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        constexpr inline int shape[4] = {1,3,32,32};
        constexpr inline int kernel_size[2] = {2,2};
        constexpr inline int stride[2] = {2,2};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(kernel_size)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        constexpr inline int result[4] = {1,3,16,16};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        constexpr inline int shape[4] = {1,8,28,28};
        constexpr inline int kernel_size[2] = {2,2};
        constexpr inline int stride[2] = {2,2};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(kernel_size)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        constexpr inline int result[4] = {1,8,14,14};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        constexpr inline int shape[4] = {1,16,14,14};
        constexpr inline int kernel_size[2] = {3,3};
        constexpr inline int stride[2] = {3,3};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(kernel_size)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        constexpr inline int result[4] = {1,16,4,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        constexpr inline int shape[3] = {16,14,14};
        constexpr inline int kernel_size[2] = {3,3};
        constexpr inline int stride[2] = {3,3};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(kernel_size)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        constexpr inline int result[3] = {16,4,4};
    }
}

NMTOOLS_TESTING_DECLARE_CASE(index, slice_pool2d)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int indices[4] = {0,0,0,0};
        inline int shape[4] = {1,1,4,4};
        inline int kernel_size[2] = {3,3};
        inline int stride[2] = {2,2};
        inline int ceil_mode = true;
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        // start,stop,step
        using slice_t  = nmtools_array<int,3>;
        using slices_t = nmtools_array<slice_t,4>;

        inline auto stride = 2;
        inline auto kernel_size = 3;
        // {stride*0,stride*0+kernel_size,1}
        inline auto result = slices_t{{{0,1,1},{0,1,1},{0,kernel_size,1},{0,kernel_size,1}}};
        inline int shape[4] = {1,1,2,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int indices[4] = {0,0,1,0};
        inline int shape[4] = {1,1,4,4};
        inline int kernel_size[2] = {3,3};
        inline int stride[2] = {2,2};
        inline int ceil_mode = true;
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        // start,stop,step
        using slice_t  = nmtools_array<int,3>;
        using slices_t = nmtools_array<slice_t,4>;

        inline auto stride = 2;
        inline auto kernel_size = 3;
        // {stride*0,stride*0+kernel_size,1}
        inline auto result = slices_t{{{0,1,1},{0,1,1},{2,2+kernel_size,1},{0,kernel_size,1}}};
        inline int shape[4] = {1,1,2,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int indices[4] = {0,0,0,1};
        inline int shape[4] = {1,1,4,4};
        inline int kernel_size[2] = {3,3};
        inline int stride[2] = {2,2};
        inline int ceil_mode = true;
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        // start,stop,step
        using slice_t  = nmtools_array<int,3>;
        using slices_t = nmtools_array<slice_t,4>;

        inline auto stride = 2;
        inline auto kernel_size = 3;
        // {stride*0,stride*0+kernel_size,1}
        inline auto result = slices_t{{{0,1,1},{0,1,1},{0,kernel_size,1},{2,2+kernel_size,1}}};
        inline int shape[4] = {1,1,2,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int indices[4] = {0,0,1,1};
        inline int shape[4] = {1,1,4,4};
        inline int kernel_size[2] = {3,3};
        inline int stride[2] = {2,2};
        inline int ceil_mode = true;
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        // start,stop,step
        using slice_t  = nmtools_array<int,3>;
        using slices_t = nmtools_array<slice_t,4>;

        inline auto stride = 2;
        inline auto kernel_size = 3;
        // {stride*0,stride*0+kernel_size,1}
        inline auto result = slices_t{{{0,1,1},{0,1,1},{2,2+kernel_size,1},{2,2+kernel_size,1}}};
        inline int shape[4] = {1,1,2,2};
    }
}

#endif // NMTOOLS_TESTING_DATA_INDEX_POOLING_HPP