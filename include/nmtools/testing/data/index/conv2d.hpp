#ifndef NMTOOLS_TESTING_DATA_INDEX_CONV_HPP
#define NMTOOLS_TESTING_DATA_INDEX_CONV_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(index, shape_conv2d)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int shape[4]       = {1,3,224,224};
        inline int out_channels   = 64;
        inline int kernel_size[2] = {3,3};
        inline int padding[2]     = {0,0};
        inline int stride[2]      = {2,2};
        inline int dilations[2]   = {1,1};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(padding)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
        NMTOOLS_CAST_INDEX_ARRAYS(dilations)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[4] = {1,64,111,111};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int shape[4]     = {1,64,55,55};
        inline int out_channels = 16;
        inline int kernel_size[2] = {1,1};
        inline int padding[2]   = {0,0};
        inline int stride[2]    = {1,1};
        inline int dilations[2] = {1,1};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(padding)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
        NMTOOLS_CAST_INDEX_ARRAYS(dilations)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[4] = {1,16,55,55};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int shape[4]     = {1,16,55,55};
        inline int out_channels = 64;
        inline int kernel_size[2] = {3,3};
        inline int padding[2]   = {1,1};
        inline int stride[2]    = {1,1};
        inline int dilations[2] = {1,1};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(padding)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
        NMTOOLS_CAST_INDEX_ARRAYS(dilations)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[4] = {1,64,55,55};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int shape[4] = {1,3,224,224};
        inline int out_channels   = 32;
        inline int kernel_size[2] = {3,3};
        inline int padding[2]     = {1,1};
        inline int stride[2]      = {2,2};
        inline int dilations[2]   = {1,1};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(padding)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
        NMTOOLS_CAST_INDEX_ARRAYS(dilations)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[4] = {1,32,112,112};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int shape[4] = {1,32,112,112};
        inline int out_channels   = 32;
        inline int kernel_size[2] = {3,3};
        inline int padding[2]     = {1,1};
        inline int stride[2]      = {1,1};
        inline int dilations[2]   = {1,1};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(padding)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
        NMTOOLS_CAST_INDEX_ARRAYS(dilations)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int result[4] = {1,32,112,112};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int shape[4]       = {1,3,112,112};
        inline int out_channels   = 64;
        inline int kernel_size[2] = {3,3};
        inline int padding[2]     = {1,1};
        inline int stride[2]      = {1,1};
        inline int dilations[2]   = {1,1};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(padding)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
        NMTOOLS_CAST_INDEX_ARRAYS(dilations)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int result[4] = {1,64,112,112};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int shape[3]       = {3,5,5};
        inline int out_channels   = 2;
        inline int kernel_size[2] = {3,3};
        inline int padding[2]     = {1,1};
        inline int stride[2]      = {2,2};
        inline int dilations[2]   = {1,1};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(padding)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
        NMTOOLS_CAST_INDEX_ARRAYS(dilations)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int result[3] = {2,3,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline int shape[4]        = {1,3,5,5};
        inline int out_channels    = 3;
        inline int kernel_size[2] = {3,3};
        inline int stride[2]      = {1,1};
        inline int padding[2]     = {0,0};
        inline int dilations[2]    = {1,1};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(padding)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
        NMTOOLS_CAST_INDEX_ARRAYS(dilations)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline int result[4] = {1,3,3,3};
    }

    // https://github.com/vdumoulin/conv_arithmetic/blob/master/README.md#convolution-animations
    // No padding, no strides
    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        inline int shape[3]       = {1,4,4};
        inline int out_channels   = 1;
        inline int kernel_size[2] = {3,3};
        inline int stride[2]      = {1,1};
        inline int padding[2]     = {0,0};
        inline int dilations[2]   = {1,1};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(padding)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
        NMTOOLS_CAST_INDEX_ARRAYS(dilations)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline int result[3] = {1,2,2};
    }

    // Arbitrary padding, no strides
    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        inline int shape[3]       = {1,5,5};
        inline int out_channels   = 1;
        inline int kernel_size[2] = {4,4};
        inline int stride[2]      = {1,1};
        inline int padding[2]     = {2,2};
        inline int dilations[2]   = {1,1};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(padding)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
        NMTOOLS_CAST_INDEX_ARRAYS(dilations)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline int result[3] = {1,6,6};
    }

    // Half padding, no strides
    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        inline int shape[3]       = {1,5,5};
        inline int out_channels   = 1;
        inline int kernel_size[2] = {3,3};
        inline int stride[2]      = {1,1};
        inline int padding[2]     = {1,1};
        inline int dilations[2]   = {1,1};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(padding)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
        NMTOOLS_CAST_INDEX_ARRAYS(dilations)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        inline int result[3] = {1,5,5};
    }

    // Full padding, no strides
    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        inline int shape[3]       = {1,5,5};
        inline int out_channels   = 1;
        inline int kernel_size[2] = {3,3};
        inline int stride[2]      = {1,1};
        inline int padding[2]     = {2,2};
        inline int dilations[2]   = {1,1};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(padding)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
        NMTOOLS_CAST_INDEX_ARRAYS(dilations)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        inline int result[3] = {1,7,7};
    }

    // No padding, strides
    NMTOOLS_TESTING_DECLARE_ARGS(case13)
    {
        inline int shape[3]       = {1,5,5};
        inline int out_channels   = 1;
        inline int kernel_size[2] = {3,3};
        inline int stride[2]      = {2,2};
        inline int padding[2]     = {0,0};
        inline int dilations[2]   = {1,1};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(padding)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
        NMTOOLS_CAST_INDEX_ARRAYS(dilations)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case13)
    {
        inline int result[3] = {1,2,2};
    }

    // Padding, strides
    NMTOOLS_TESTING_DECLARE_ARGS(case14)
    {
        inline int shape[3]       = {1,5,5};
        inline int out_channels   = 1;
        inline int kernel_size[2] = {3,3};
        inline int stride[2]      = {2,2};
        inline int padding[2]     = {1,1};
        inline int dilations[2]   = {1,1};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(padding)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
        NMTOOLS_CAST_INDEX_ARRAYS(dilations)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case14)
    {
        inline int result[3] = {1,3,3};
    }

    // Padding, strides (odd)
    NMTOOLS_TESTING_DECLARE_ARGS(case15)
    {
        inline int shape[3]       = {1,6,6};
        inline int out_channels   = 1;
        inline int kernel_size[2] = {3,3};
        inline int stride[2]      = {2,2};
        inline int padding[2]     = {1,1};
        inline int dilations[2]   = {1,1};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(padding)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
        NMTOOLS_CAST_INDEX_ARRAYS(dilations)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case15)
    {
        inline int result[3] = {1,3,3};
    }
}

NMTOOLS_TESTING_DECLARE_CASE(index, slice_conv2d)
{
    // https://github.com/vdumoulin/conv_arithmetic/blob/master/README.md#convolution-animations
    // No padding, no strides
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int indices[3]   = {0,0,0};
        inline int src_shape[3] = {1,4,4};
        inline int dst_shape[3] = {1,2,2};
        inline int kernel_size[2] = {3,3};
        inline int stride[2]      = {1,1};
        inline int padding[2]     = {0,0};
        inline int dilations[2]   = {1,1};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(padding)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
        NMTOOLS_CAST_INDEX_ARRAYS(dilations)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        // NOTE: on slicing stop index is not included [0,3)
        // a[...,0:3:1,0:3:1]
        using array_t  = nmtools_array<size_t,3>;
        using index_t  = size_t;
        using slice_t  = nmtools_either<index_t,array_t>;
        using slices_t = nmtools_array<slice_t,3>;
        // NOTE: utl either doesn't support this
        // TODO: fix utl either construction/conversion
        #if 0
        inline auto result = slices_t{array_t{0,1,1},array_t{0,3,1},array_t{0,3,1}};
        #else
        inline auto result = slices_t{slice_t{array_t{0,1,1}},slice_t{array_t{0,3,1}},slice_t{array_t{0,3,1}}};
        #endif
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int indices[3]   = {0,1,0};
        inline int src_shape[3] = {1,4,4};
        inline int dst_shape[3] = {1,2,2};
        inline int kernel_size[2] = {3,3};
        inline int stride[2]      = {1,1};
        inline int padding[2]     = {0,0};
        inline int dilations[2]   = {1,1};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(padding)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
        NMTOOLS_CAST_INDEX_ARRAYS(dilations)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        // a[...,1:4:1,0:3:1]
        using array_t  = nmtools_array<size_t,3>;
        using index_t  = size_t;
        using slice_t  = nmtools_either<index_t,array_t>;
        using slices_t = nmtools_array<slice_t,3>;
        #if 0
        inline auto result = slices_t{array_t{0,1,1},array_t{1,4,1},array_t{0,3,1}};
        #else
        inline auto result = slices_t{slice_t{array_t{0,1,1}},slice_t{array_t{1,4,1}},slice_t{array_t{0,3,1}}};
        #endif
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int indices[3]   = {0,0,1};
        inline int src_shape[3] = {1,4,4};
        inline int dst_shape[3] = {1,2,2};
        inline int kernel_size[2] = {3,3};
        inline int stride[2]      = {1,1};
        inline int padding[2]     = {0,0};
        inline int dilations[2]   = {1,1};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(padding)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
        NMTOOLS_CAST_INDEX_ARRAYS(dilations)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        // a[...,0:3:1,1:4:1]
        using array_t  = nmtools_array<size_t,3>;
        using index_t  = size_t;
        using slice_t  = nmtools_either<index_t,array_t>;
        using slices_t = nmtools_array<slice_t,3>;
        #if 0
        inline auto result = slices_t{array_t{0,1,1},array_t{0,3,1},array_t{1,4,1}};
        #else
        inline auto result = slices_t{(slice_t)array_t{0,1,1},(slice_t)array_t{0,3,1},(slice_t)array_t{1,4,1}};
        #endif
        // shape_out = (in_shape + 2*padding - dilation * (kernel - 1) - 1) / stride + 1
        // padding=0, dilation=1, stride=1 :
        // shape_out = (in_shape - (kernel - 1) - 1) + 1 = (in_shape - kernel - 1)
        // start_idx = (out_idx * stride) + (0 * kernel)
        // stop_idx  = (out_idx * stride) + (1 * kernel)
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int indices[3]   = {0,1,1};
        inline int src_shape[3] = {1,4,4};
        inline int dst_shape[3] = {1,2,2};
        inline int kernel_size[2] = {3,3};
        inline int stride[2]      = {1,1};
        inline int padding[2]     = {0,0};
        inline int dilations[2]   = {1,1};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(padding)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
        NMTOOLS_CAST_INDEX_ARRAYS(dilations)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        // a[...,1:4:1,1:4:1]
        using array_t  = nmtools_array<size_t,3>;
        using index_t  = size_t;
        using slice_t  = nmtools_either<index_t,array_t>;
        using slices_t = nmtools_array<slice_t,3>;
        #if 0
        inline auto result = slices_t{array_t{0,1,1},array_t{1,4,1},array_t{1,4,1}};
        #else
        inline auto result = slices_t{(slice_t)array_t{0,1,1},(slice_t)array_t{1,4,1},(slice_t)array_t{1,4,1}};
        #endif
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int indices[3]     = {0,1,1};
        inline int src_shape[3]   = {1,7,7};
        inline int dst_shape[3]   = {1,5,5};
        inline int kernel_size[2] = {3,3};
        inline int padding[2]     = {0,0};
        inline int stride[2]      = {1,1};
        inline int dilations[2]   = {1,1};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(padding)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
        NMTOOLS_CAST_INDEX_ARRAYS(dilations)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        // a[...,1:4:1,1:4:1]
        using array_t  = nmtools_array<size_t,3>;
        using index_t  = size_t;
        using slice_t  = nmtools_either<index_t,array_t>;
        using slices_t = nmtools_array<slice_t,3>;
        #if 0
        inline auto result = slices_t{array_t{0,1,1},array_t{1,4,1},array_t{1,4,1}};
        #else
        inline auto result = slices_t{(slice_t)array_t{0,1,1},(slice_t)array_t{1,4,1},(slice_t)array_t{1,4,1}};
        #endif
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int indices[3]     = {0,0,0};
        inline int src_shape[3]   = {1,5,5};
        inline int dst_shape[3]   = {1,2,2};
        inline int kernel_size[2] = {3,3};
        inline int padding[2]     = {0,0};
        inline int stride[2]      = {2,2};
        inline int dilations[2]   = {1,1};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(padding)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
        NMTOOLS_CAST_INDEX_ARRAYS(dilations)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        using array_t  = nmtools_array<size_t,3>;
        using index_t  = size_t;
        using slice_t  = nmtools_either<index_t,array_t>;
        using slices_t = nmtools_array<slice_t,3>;
        #if 0
        inline auto result = slices_t{array_t{0,1,1},array_t{0,3,1},array_t{0,3,1}};
        #else
        inline auto result = slices_t{(slice_t)array_t{0,1,1},(slice_t)array_t{0,3,1},(slice_t)array_t{0,3,1}};
        #endif
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int indices[3]     = {0,1,0};
        inline int src_shape[3]   = {1,5,5};
        inline int dst_shape[3]   = {1,2,2};
        inline int kernel_size[2] = {3,3};
        inline int padding[2]     = {0,0};
        inline int stride[2]      = {2,2};
        inline int dilations[2]   = {1,1};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(padding)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
        NMTOOLS_CAST_INDEX_ARRAYS(dilations)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        using array_t  = nmtools_array<size_t,3>;
        using index_t  = size_t;
        using slice_t  = nmtools_either<index_t,array_t>;
        using slices_t = nmtools_array<slice_t,3>;
        #if 0
        inline auto result = slices_t{array_t{0,1,1},array_t{2,5,1},array_t{0,3,1}};
        #else
        inline auto result = slices_t{(slice_t)array_t{0,1,1},(slice_t)array_t{2,5,1},(slice_t)array_t{0,3,1}};
        #endif
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline int indices[3]     = {0,2,0};
        inline int src_shape[3]   = {1,5,5};
        inline int dst_shape[3]   = {1,2,2};
        inline int kernel_size[2] = {3,3};
        inline int padding[2]     = {0,0};
        inline int stride[2]      = {2,2};
        inline int dilations[2]   = {1,1};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(padding)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
        NMTOOLS_CAST_INDEX_ARRAYS(dilations)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        using array_t  = nmtools_array<size_t,3>;
        using index_t  = size_t;
        using slice_t  = nmtools_either<index_t,array_t>;
        using slices_t = nmtools_array<slice_t,3>;
        #if 0
        inline auto result = slices_t{array_t{0,1,1},array_t{4,7,1},array_t{0,3,1}};
        #else
        inline auto result = slices_t{(slice_t)array_t{0,1,1},(slice_t)array_t{4,7,1},(slice_t)array_t{0,3,1}};
        #endif
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        inline int indices[4]   = {0,0,0,0};
        inline int src_shape[4] = {1,3,5,5};
        inline int dst_shape[4] = {1,3,3,3};
        inline int kernel_size[3] = {3,3};
        inline int padding[2]     = {0,0};
        inline int stride[2]      = {1,1};
        inline int dilations[2]   = {1,1};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(padding)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
        NMTOOLS_CAST_INDEX_ARRAYS(dilations)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        using array_t  = nmtools_array<size_t,3>;
        using index_t  = size_t;
        using slice_t  = nmtools_either<index_t,array_t>;
        using slices_t = nmtools_array<slice_t,4>;
        #if 0
        inline auto result = slices_t{size_t{0},array_t{0,3,1},array_t{0,3,1},array_t{0,3,1}};
        #else
        inline auto result = slices_t{(slice_t)size_t{0},(slice_t)array_t{0,3,1},(slice_t)array_t{0,3,1},(slice_t)array_t{0,3,1}};
        #endif
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        inline int indices[4]   = {0,2,2,2};
        inline int src_shape[4] = {1,3,5,5};
        inline int dst_shape[4] = {1,3,3,3};
        inline int kernel_size[3] = {3,3};
        inline int padding[2]     = {0,0};
        inline int stride[2]      = {1,1};
        inline int dilations[2]   = {1,1};
        inline int groups = 3;
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(padding)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
        NMTOOLS_CAST_INDEX_ARRAYS(dilations)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        using array_t  = nmtools_array<size_t,3>;
        using index_t  = size_t;
        using slice_t  = nmtools_either<index_t,array_t>;
        using slices_t = nmtools_array<slice_t,4>;
        #if 0
        inline auto result = slices_t{size_t{0},size_t{2},array_t{2,5,1},array_t{2,5,1}};
        #else
        inline auto result = slices_t{(slice_t)size_t{0},(slice_t)size_t{2},(slice_t)array_t{2,5,1},(slice_t)array_t{2,5,1}};
        #endif
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        inline int indices[4]   = {0,0,0,0};
        inline int src_shape[4] = {1,3,5,5};
        inline int dst_shape[4] = {1,3,3,3};
        inline int kernel_size[3] = {3,3};
        inline int padding[2]     = {0,0};
        inline int stride[2]      = {1,1};
        inline int dilations[2]   = {1,1};
        inline int groups = 1;
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(kernel_size)
        NMTOOLS_CAST_INDEX_ARRAYS(padding)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
        NMTOOLS_CAST_INDEX_ARRAYS(dilations)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        using array_t  = nmtools_array<size_t,3>;
        using index_t  = size_t;
        using slice_t  = nmtools_either<index_t,array_t>;
        using slices_t = nmtools_array<slice_t,4>;
        #if 0
        inline auto result = slices_t{size_t{0},array_t{0,3,1},array_t{0,3,1},array_t{0,3,1}};
        #else
        inline auto result = slices_t{(slice_t)size_t{0},(slice_t)array_t{0,3,1},(slice_t)array_t{0,3,1},(slice_t)array_t{0,3,1}};
        #endif
    }
}

#endif // NMTOOLS_TESTING_DATA_INDEX_CONV_HPP