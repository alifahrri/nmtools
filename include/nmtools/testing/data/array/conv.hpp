#ifndef NMTOOLS_TESTING_DATA_ARRAY_CONV_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_CONV_HPP

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

NMTOOLS_TESTING_DECLARE_CASE(array, conv2d)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int input[1][4][4] = {
            {
                { 0, 1, 2, 3},
                { 4, 5, 6, 7},
                { 8, 9,10,11},
                {12,13,14,15},
            }
        };
        inline int weight[1][1][3][3] = {
            {
                {
                    {1,0,1},
                    {1,0,1},
                    {1,0,1},
                }
            }
        };
        inline int stride[2] = {1,1};
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[1][2][2] = {
            {
                {30,36},
                {54,60},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int input[1][1][4][4] = {
            {
                {
                    { 0, 1, 2, 3},
                    { 4, 5, 6, 7},
                    { 8, 9,10,11},
                    {12,13,14,15},
                }
            }
        };
        inline int weight[1][1][3][3] = {
            {
                {
                    {1,0,1},
                    {1,0,1},
                    {1,0,1},
                }
            }
        };
        inline int stride[2] = {1,1};
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[1][1][2][2] = {
            {
                {
                    {30,36},
                    {54,60},   
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        using case1::args::input;
        inline int weight[1][1][3][3] = {
            {
                {
                    {0,1,2},
                    {3,4,5},
                    {6,7,8},
                }
            }
        };
        inline int stride[2] = {1,1};
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[1][2][2] = {
            {
                {258,294},
                {402,438},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        using case1::args::input;
        inline int weight[1][1][3][3] = {
            {
                {
                    {1,1,1},
                    {0,0,0},
                    {1,1,1},
                }
            }
        };
        inline int stride[2] = {1,1};
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[1][2][2] = {
            {
                {30,36},
                {54,60},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int input[1][1][7][7] = {{{{ 0,  1,  2,  3,  4,  5,  6},
          { 7,  8,  9, 10, 11, 12, 13},
          {14, 15, 16, 17, 18, 19, 20},
          {21, 22, 23, 24, 25, 26, 27},
          {28, 29, 30, 31, 32, 33, 34},
          {35, 36, 37, 38, 39, 40, 41},
          {42, 43, 44, 45, 46, 47, 48}}}};
        inline int weight[1][1][3][3] = {
            {
                {
                    {1,1,1},
                    {1,1,1},
                    {1,1,1},
                }
            }
        };
        inline int stride[2] = {1,1};
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int result[1][1][5][5] = {{{{ 72,  81,  90,  99, 108},
          {135, 144, 153, 162, 171},
          {198, 207, 216, 225, 234},
          {261, 270, 279, 288, 297},
          {324, 333, 342, 351, 360}}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int input[1][1][5][5] = {{{{ 0,  1,  2,  3,  4},
          { 5,  6,  7,  8,  9},
          {10, 11, 12, 13, 14},
          {15, 16, 17, 18, 19},
          {20, 21, 22, 23, 24}}}};
        inline int weight[1][1][3][3] = {
            {
                {
                    {1,1,1},
                    {1,1,1},
                    {1,1,1},
                }
            }
        };
        inline int stride[2] = {1,1};
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int result[1][1][3][3] = {{{{ 54,  63,  72},
          { 99, 108, 117},
          {144, 153, 162}}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        using case6::args::input;
        inline int weight[1][1][3][3] = {
            {
                {
                    {1,1,1},
                    {1,1,1},
                    {1,1,1},
                }
            }
        };
        inline int stride[2] = {2,2};
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int result[1][1][2][2] = {{{{ 54,  72},
          {144, 162}}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline int input[1][3][5][5] = {
            {
                {
                    { 0,  1,  2,  3,  4},
                    { 5,  6,  7,  8,  9},
                    {10, 11, 12, 13, 14},
                    {15, 16, 17, 18, 19},
                    {20, 21, 22, 23, 24}
                },
                {
                    {25, 26, 27, 28, 29},
                    {30, 31, 32, 33, 34},
                    {35, 36, 37, 38, 39},
                    {40, 41, 42, 43, 44},
                    {45, 46, 47, 48, 49}
                },
                {
                    {50, 51, 52, 53, 54},
                    {55, 56, 57, 58, 59},
                    {60, 61, 62, 63, 64},
                    {65, 66, 67, 68, 69},
                    {70, 71, 72, 73, 74}
                }
            }
        };
        inline int weight[1][3][3][3] = {{{{ 0,  1,  2},
          { 3,  4,  5},
          { 6,  7,  8}},

         {{ 9, 10, 11},
          {12, 13, 14},
          {15, 16, 17}},

         {{18, 19, 20},
          {21, 22, 23},
          {24, 25, 26}}}};
        inline int stride[2] = {1,1};
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline int result[1][1][3][3] = {{{{15219, 15570, 15921},
          {16974, 17325, 17676},
          {18729, 19080, 19431}}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        using case8::args::input;
        inline int weight[3][3][3][3] = {{{{ 0,  1,  2},
          { 3,  4,  5},
          { 6,  7,  8}},

         {{ 9, 10, 11},
          {12, 13, 14},
          {15, 16, 17}},

         {{18, 19, 20},
          {21, 22, 23},
          {24, 25, 26}}},


        {{{27, 28, 29},
          {30, 31, 32},
          {33, 34, 35}},

         {{36, 37, 38},
          {39, 40, 41},
          {42, 43, 44}},

         {{45, 46, 47},
          {48, 49, 50},
          {51, 52, 53}}},


        {{{54, 55, 56},
          {57, 58, 59},
          {60, 61, 62}},

         {{63, 64, 65},
          {66, 67, 68},
          {69, 70, 71}},

         {{72, 73, 74},
          {75, 76, 77},
          {78, 79, 80}}}};
        inline int stride[2] = {1,1};
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline int result[1][3][3][3] = {{{{15219, 15570, 15921},
          {16974, 17325, 17676},
          {18729, 19080, 19431}},

         {{37818, 38898, 39978},
          {43218, 44298, 45378},
          {48618, 49698, 50778}},

         {{60417, 62226, 64035},
          {69462, 71271, 73080},
          {78507, 80316, 82125}}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        using case9::args::input;
        using case9::args::weight;
        inline int stride[2] = {2,2};
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline int result[1][3][2][2] = {{{{15219, 15921},
          {18729, 19431}},

         {{37818, 39978},
          {48618, 50778}},

         {{60417, 64035},
          {78507, 82125}}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        using case10::args::input;
        using case10::args::weight;
        inline int stride[2]  = {2,2};
        inline int padding[2] = {1,1};
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
        NMTOOLS_CAST_INDEX_ARRAYS(padding)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        inline int result[1][3][3][3] = {{{{ 6888, 10479,  7056},
          {11511, 17325, 11547},
          { 8040, 11991,  7920}},

         {{15960, 24816, 17100},
          {28764, 44298, 30258},
          {21972, 33618, 22824}},

         {{25032, 39153, 27144},
          {46017, 71271, 48969},
          {35904, 55245, 37728}}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        using case10::args::input;
        using case10::args::weight;
        inline int stride[2]  = {2,2};
        inline int padding[2] = {2,3};
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
        NMTOOLS_CAST_INDEX_ARRAYS(padding)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        inline int result[1][3][4][5] = {{{{    0,  3426,  5244,  3552,     0},
          {    0, 10296, 15570, 10422,     0},
          {    0, 12726, 19080, 12672,     0},
          {    0,  3768,  5586,  3666,     0}},

         {{    0,  7557, 11805,  8169,     0},
          {    0, 25119, 38898, 26703,     0},
          {    0, 32409, 49698, 33813,     0},
          {    0, 11139, 17007, 11523,     0}},

         {{    0, 11688, 18366, 12786,     0},
          {    0, 39942, 62226, 42984,     0},
          {    0, 52092, 80316, 54954,     0},
          {    0, 18510, 28428, 19380,     0}}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case13)
    {
        using case8::args::input;
        inline float weight[3][1][3][3] = 
        {
            {
                {
                    {1., 1., 1.},
                    {1., 1., 1.},
                    {1., 1., 1.}
                }
            },
            {
                {
                    {1., 1., 1.},
                    {1., 1., 1.},
                    {1., 1., 1.}
                }
            },
            {
                {
                    {1., 1., 1.},
                    {1., 1., 1.},
                    {1., 1., 1.}
                }
            }
        };
        inline auto stride   = 1;
        inline auto padding  = 0;
        inline auto dilation = 1;
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case13)
    {
        inline float result[1][3][3][3] = {
            {
                {
                    { 54.,  63.,  72.},
                    { 99., 108., 117.},
                    {144., 153., 162.}
                },
                {
                    {279., 288., 297.},
                    {324., 333., 342.},
                    {369., 378., 387.}
                },
                {
                    {504., 513., 522.},
                    {549., 558., 567.},
                    {594., 603., 612.}
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case14)
    {
        using case13::args::input;
        inline float weight[3][1][3][3] = 
        {
            {
                {
                    {1., 1., 1.},
                    {1., 1., 1.},
                    {1., 1., 1.}
                }
            },
            {
                {
                    {1., 1., 1.},
                    {1., 1., 1.},
                    {1., 1., 1.}
                }
            },
            {
                {
                    {1., 1., 1.},
                    {1., 1., 1.},
                    {1., 1., 1.}
                }
            }
        };
        inline auto stride   = 1;
        inline auto padding  = 1;
        inline auto dilation = 1;
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case14)
    {
        inline float result[1][3][5][5] = {
            {
                {
                    { 12.,  21.,  27.,  33.,  24.},
                    { 33.,  54.,  63.,  72.,  51.},
                    { 63.,  99., 108., 117.,  81.},
                    { 93., 144., 153., 162., 111.},
                    { 72., 111., 117., 123.,  84.}
                },
                {
                    {112., 171., 177., 183., 124.},
                    {183., 279., 288., 297., 201.},
                    {213., 324., 333., 342., 231.},
                    {243., 369., 378., 387., 261.},
                    {172., 261., 267., 273., 184.}
                },
                {
                    {212., 321., 327., 333., 224.},
                    {333., 504., 513., 522., 351.},
                    {363., 549., 558., 567., 381.},
                    {393., 594., 603., 612., 411.},
                    {272., 411., 417., 423., 284.}
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case15)
    {
        using case13::args::input;
        inline float weight[2][3][3][3] = {{{{1., 1., 1.},
          {1., 1., 1.},
          {1., 1., 1.}},

         {{1., 1., 1.},
          {1., 1., 1.},
          {1., 1., 1.}},

         {{1., 1., 1.},
          {1., 1., 1.},
          {1., 1., 1.}}},


        {{{.5, .5, .5},
          {.5, .5, .5},
          {.5, .5, .5}},

         {{.5, .5, .5},
          {.5, .5, .5},
          {.5, .5, .5}},

         {{.5, .5, .5},
          {.5, .5, .5},
          {.5, .5, .5}}}};
        inline auto stride   = 1;
        inline auto padding  = 0;
        inline auto dilation = 1;
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case15)
    {
        inline float result[1][2][3][3] = {{{{ 837.0000,  864.0000,  891.0000},
          { 972.0000,  999.0000, 1026.0000},
          {1107.0000, 1134.0000, 1161.0000}},

         {{ 418.5000,  432.0000,  445.5000},
          { 486.0000,  499.5000,  513.0000},
          { 553.5000,  567.0000,  580.5000}}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case16)
    {
        using case15::args::input;
        using case15::args::weight;
        inline float bias[2] = {0.25,0.25};
        inline auto stride   = 1;
        inline auto padding  = 0;
        inline auto dilation = 1;
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_ARRAYS(bias)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case16)
    {
        inline float result[1][2][3][3] = {{{{ 837.2500,  864.2500,  891.2500},
          { 972.2500,  999.2500, 1026.2500},
          {1107.2500, 1134.2500, 1161.2500}},

         {{ 418.7500,  432.2500,  445.7500},
          { 486.2500,  499.7500,  513.2500},
          { 553.7500,  567.2500,  580.7500}}}};
    }
}

#if NMTOOLS_TESTING_CONSTEXPR

NMTOOLS_TESTING_DECLARE_CASE(array, constexpr_conv2d)
{
    using namespace literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr inline int input[1][4][4] = {
            {
                { 0, 1, 2, 3},
                { 4, 5, 6, 7},
                { 8, 9,10,11},
                {12,13,14,15},
            }
        };
        constexpr inline int weight[1][1][3][3] = {
            {
                {
                    {1,0,1},
                    {1,0,1},
                    {1,0,1},
                }
            }
        };
        constexpr inline int stride[2] = {1,1};
        constexpr inline auto stride_ct = nmtools_tuple{1_ct,1_ct};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(input)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(weight)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline int result[1][2][2] = {
            {
                {30,36},
                {54,60},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        constexpr inline int input[1][1][4][4] = {
            {
                {
                    { 0, 1, 2, 3},
                    { 4, 5, 6, 7},
                    { 8, 9,10,11},
                    {12,13,14,15},
                }
            }
        };
        constexpr inline int weight[1][1][3][3] = {
            {
                {
                    {1,0,1},
                    {1,0,1},
                    {1,0,1},
                }
            }
        };
        constexpr inline int stride[2] = {1,1};
        constexpr inline auto stride_ct = nmtools_tuple{1_ct,1_ct};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(input)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(weight)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        constexpr inline int result[1][1][2][2] = {
            {
                {
                    {30,36},
                    {54,60},   
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        using case1::args::input;
        constexpr inline int weight[1][1][3][3] = {
            {
                {
                    {0,1,2},
                    {3,4,5},
                    {6,7,8},
                }
            }
        };
        constexpr inline int stride[2] = {1,1};
        constexpr inline auto stride_ct = nmtools_tuple{1_ct,1_ct};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(input)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(weight)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        constexpr inline int result[1][2][2] = {
            {
                {258,294},
                {402,438},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        using case1::args::input;
        constexpr inline int weight[1][1][3][3] = {
            {
                {
                    {1,1,1},
                    {0,0,0},
                    {1,1,1},
                }
            }
        };
        constexpr inline int stride[2] = {1,1};
        constexpr inline auto stride_ct = nmtools_tuple{1_ct,1_ct};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(input)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(weight)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        constexpr inline int result[1][2][2] = {
            {
                {30,36},
                {54,60},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        constexpr inline int input[1][1][7][7] = {{{{ 0,  1,  2,  3,  4,  5,  6},
          { 7,  8,  9, 10, 11, 12, 13},
          {14, 15, 16, 17, 18, 19, 20},
          {21, 22, 23, 24, 25, 26, 27},
          {28, 29, 30, 31, 32, 33, 34},
          {35, 36, 37, 38, 39, 40, 41},
          {42, 43, 44, 45, 46, 47, 48}}}};
        constexpr inline int weight[1][1][3][3] = {
            {
                {
                    {1,1,1},
                    {1,1,1},
                    {1,1,1},
                }
            }
        };
        constexpr inline int stride[2] = {1,1};
        constexpr inline auto stride_ct = nmtools_tuple{1_ct,1_ct};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(input)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(weight)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        constexpr inline int result[1][1][5][5] = {{{{ 72,  81,  90,  99, 108},
          {135, 144, 153, 162, 171},
          {198, 207, 216, 225, 234},
          {261, 270, 279, 288, 297},
          {324, 333, 342, 351, 360}}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        constexpr inline int input[1][1][5][5] = {{{{ 0,  1,  2,  3,  4},
          { 5,  6,  7,  8,  9},
          {10, 11, 12, 13, 14},
          {15, 16, 17, 18, 19},
          {20, 21, 22, 23, 24}}}};
        constexpr inline int weight[1][1][3][3] = {
            {
                {
                    {1,1,1},
                    {1,1,1},
                    {1,1,1},
                }
            }
        };
        constexpr inline int stride[2] = {1,1};
        constexpr inline auto stride_ct = nmtools_tuple{1_ct,1_ct};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(input)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(weight)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        constexpr inline int result[1][1][3][3] = {{{{ 54,  63,  72},
          { 99, 108, 117},
          {144, 153, 162}}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        using case6::args::input;
        constexpr inline int weight[1][1][3][3] = {
            {
                {
                    {1,1,1},
                    {1,1,1},
                    {1,1,1},
                }
            }
        };
        constexpr inline int stride[2] = {2,2};
        constexpr inline auto stride_ct = nmtools_tuple{2_ct,2_ct};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(input)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(weight)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        constexpr inline int result[1][1][2][2] = {{{{ 54,  72},
          {144, 162}}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        constexpr inline int input[1][3][5][5] = {
            {
                {
                    { 0,  1,  2,  3,  4},
                    { 5,  6,  7,  8,  9},
                    {10, 11, 12, 13, 14},
                    {15, 16, 17, 18, 19},
                    {20, 21, 22, 23, 24}
                },
                {
                    {25, 26, 27, 28, 29},
                    {30, 31, 32, 33, 34},
                    {35, 36, 37, 38, 39},
                    {40, 41, 42, 43, 44},
                    {45, 46, 47, 48, 49}
                },
                {
                    {50, 51, 52, 53, 54},
                    {55, 56, 57, 58, 59},
                    {60, 61, 62, 63, 64},
                    {65, 66, 67, 68, 69},
                    {70, 71, 72, 73, 74}
                }
            }
        };
        constexpr inline int weight[1][3][3][3] = {{{{ 0,  1,  2},
          { 3,  4,  5},
          { 6,  7,  8}},

         {{ 9, 10, 11},
          {12, 13, 14},
          {15, 16, 17}},

         {{18, 19, 20},
          {21, 22, 23},
          {24, 25, 26}}}};
        constexpr inline int stride[2] = {1,1};
        constexpr inline auto stride_ct = nmtools_tuple{1_ct,1_ct};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(input)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(weight)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        constexpr inline int result[1][1][3][3] = {{{{15219, 15570, 15921},
          {16974, 17325, 17676},
          {18729, 19080, 19431}}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        using case8::args::input;
        constexpr inline int weight[3][3][3][3] = {{{{ 0,  1,  2},
          { 3,  4,  5},
          { 6,  7,  8}},

         {{ 9, 10, 11},
          {12, 13, 14},
          {15, 16, 17}},

         {{18, 19, 20},
          {21, 22, 23},
          {24, 25, 26}}},


        {{{27, 28, 29},
          {30, 31, 32},
          {33, 34, 35}},

         {{36, 37, 38},
          {39, 40, 41},
          {42, 43, 44}},

         {{45, 46, 47},
          {48, 49, 50},
          {51, 52, 53}}},


        {{{54, 55, 56},
          {57, 58, 59},
          {60, 61, 62}},

         {{63, 64, 65},
          {66, 67, 68},
          {69, 70, 71}},

         {{72, 73, 74},
          {75, 76, 77},
          {78, 79, 80}}}};
        constexpr inline int stride[2] = {1,1};
        constexpr inline auto stride_ct = nmtools_tuple{1_ct,1_ct};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(input)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(weight)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        constexpr inline int result[1][3][3][3] = {{{{15219, 15570, 15921},
          {16974, 17325, 17676},
          {18729, 19080, 19431}},

         {{37818, 38898, 39978},
          {43218, 44298, 45378},
          {48618, 49698, 50778}},

         {{60417, 62226, 64035},
          {69462, 71271, 73080},
          {78507, 80316, 82125}}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        using case9::args::input;
        using case9::args::weight;
        constexpr inline int stride[2] = {2,2};
        constexpr inline auto stride_ct = nmtools_tuple{2_ct,2_ct};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(input)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(weight)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        constexpr inline int result[1][3][2][2] = {{{{15219, 15921},
          {18729, 19431}},

         {{37818, 39978},
          {48618, 50778}},

         {{60417, 64035},
          {78507, 82125}}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        using case10::args::input;
        using case10::args::weight;
        constexpr inline int stride[2]   = {2,2};
        constexpr inline int padding[2]  = {1,1};
        constexpr inline auto stride_ct  = nmtools_tuple{2_ct,2_ct};
        constexpr inline auto padding_ct = nmtools_tuple{1_ct,1_ct};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(input)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(weight)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        constexpr inline int result[1][3][3][3] = {{{{ 6888, 10479,  7056},
          {11511, 17325, 11547},
          { 8040, 11991,  7920}},

         {{15960, 24816, 17100},
          {28764, 44298, 30258},
          {21972, 33618, 22824}},

         {{25032, 39153, 27144},
          {46017, 71271, 48969},
          {35904, 55245, 37728}}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        using case10::args::input;
        using case10::args::weight;
        constexpr inline int stride[2]   = {2,2};
        constexpr inline int padding[2]  = {2,3};
        constexpr inline auto stride_ct  = nmtools_tuple{2_ct,2_ct};
        constexpr inline auto padding_ct = nmtools_tuple{2_ct,3_ct};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(input)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(weight)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        constexpr inline int result[1][3][4][5] = {{{{    0,  3426,  5244,  3552,     0},
          {    0, 10296, 15570, 10422,     0},
          {    0, 12726, 19080, 12672,     0},
          {    0,  3768,  5586,  3666,     0}},

         {{    0,  7557, 11805,  8169,     0},
          {    0, 25119, 38898, 26703,     0},
          {    0, 32409, 49698, 33813,     0},
          {    0, 11139, 17007, 11523,     0}},

         {{    0, 11688, 18366, 12786,     0},
          {    0, 39942, 62226, 42984,     0},
          {    0, 52092, 80316, 54954,     0},
          {    0, 18510, 28428, 19380,     0}}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case13)
    {
        using case8::args::input;
        constexpr inline float weight[3][1][3][3] = 
        {
            {
                {
                    {1., 1., 1.},
                    {1., 1., 1.},
                    {1., 1., 1.}
                }
            },
            {
                {
                    {1., 1., 1.},
                    {1., 1., 1.},
                    {1., 1., 1.}
                }
            },
            {
                {
                    {1., 1., 1.},
                    {1., 1., 1.},
                    {1., 1., 1.}
                }
            }
        };
        constexpr inline auto stride   = 1;
        constexpr inline auto padding  = 0;
        constexpr inline auto dilation = 1;
        constexpr inline auto stride_ct   = 1_ct;
        constexpr inline auto padding_ct  = 0_ct;
        constexpr inline auto dilation_ct = 1_ct;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(input)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(weight)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case13)
    {
        constexpr inline float result[1][3][3][3] = {
            {
                {
                    { 54.,  63.,  72.},
                    { 99., 108., 117.},
                    {144., 153., 162.}
                },
                {
                    {279., 288., 297.},
                    {324., 333., 342.},
                    {369., 378., 387.}
                },
                {
                    {504., 513., 522.},
                    {549., 558., 567.},
                    {594., 603., 612.}
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case14)
    {
        using case13::args::input;
        constexpr inline float weight[3][1][3][3] = 
        {
            {
                {
                    {1., 1., 1.},
                    {1., 1., 1.},
                    {1., 1., 1.}
                }
            },
            {
                {
                    {1., 1., 1.},
                    {1., 1., 1.},
                    {1., 1., 1.}
                }
            },
            {
                {
                    {1., 1., 1.},
                    {1., 1., 1.},
                    {1., 1., 1.}
                }
            }
        };
        constexpr inline auto stride   = 1;
        constexpr inline auto padding  = 1;
        constexpr inline auto dilation = 1;
        constexpr inline auto stride_ct   = 1_ct;
        constexpr inline auto padding_ct  = 1_ct;
        constexpr inline auto dilation_ct = 1_ct;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(input)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(weight)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case14)
    {
        constexpr inline float result[1][3][5][5] = {
            {
                {
                    { 12.,  21.,  27.,  33.,  24.},
                    { 33.,  54.,  63.,  72.,  51.},
                    { 63.,  99., 108., 117.,  81.},
                    { 93., 144., 153., 162., 111.},
                    { 72., 111., 117., 123.,  84.}
                },
                {
                    {112., 171., 177., 183., 124.},
                    {183., 279., 288., 297., 201.},
                    {213., 324., 333., 342., 231.},
                    {243., 369., 378., 387., 261.},
                    {172., 261., 267., 273., 184.}
                },
                {
                    {212., 321., 327., 333., 224.},
                    {333., 504., 513., 522., 351.},
                    {363., 549., 558., 567., 381.},
                    {393., 594., 603., 612., 411.},
                    {272., 411., 417., 423., 284.}
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case15)
    {
        using case13::args::input;
        constexpr inline float weight[2][3][3][3] = {{{{1., 1., 1.},
          {1., 1., 1.},
          {1., 1., 1.}},

         {{1., 1., 1.},
          {1., 1., 1.},
          {1., 1., 1.}},

         {{1., 1., 1.},
          {1., 1., 1.},
          {1., 1., 1.}}},


        {{{.5, .5, .5},
          {.5, .5, .5},
          {.5, .5, .5}},

         {{.5, .5, .5},
          {.5, .5, .5},
          {.5, .5, .5}},

         {{.5, .5, .5},
          {.5, .5, .5},
          {.5, .5, .5}}}};
        constexpr inline auto stride   = 1;
        constexpr inline auto padding  = 0;
        constexpr inline auto dilation = 1;
        constexpr inline auto stride_ct   = 1_ct;
        constexpr inline auto padding_ct  = 0_ct;
        constexpr inline auto dilation_ct = 1_ct;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(input)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(weight)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case15)
    {
        constexpr inline float result[1][2][3][3] = {{{{ 837.0000,  864.0000,  891.0000},
          { 972.0000,  999.0000, 1026.0000},
          {1107.0000, 1134.0000, 1161.0000}},

         {{ 418.5000,  432.0000,  445.5000},
          { 486.0000,  499.5000,  513.0000},
          { 553.5000,  567.0000,  580.5000}}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case16)
    {
        using case15::args::input;
        using case15::args::weight;
        constexpr inline float bias[2] = {0.25,0.25};
        constexpr inline auto stride   = 1;
        constexpr inline auto padding  = 0;
        constexpr inline auto dilation = 1;
        constexpr inline auto stride_ct   = 1_ct;
        constexpr inline auto padding_ct  = 0_ct;
        constexpr inline auto dilation_ct = 1_ct;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(input)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(weight)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(bias)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case16)
    {
        constexpr inline float result[1][2][3][3] = {{{{ 837.2500,  864.2500,  891.2500},
          { 972.2500,  999.2500, 1026.2500},
          {1107.2500, 1134.2500, 1161.2500}},

         {{ 418.7500,  432.2500,  445.7500},
          { 486.2500,  499.7500,  513.2500},
          { 553.7500,  567.2500,  580.7500}}}};
    }
}

#endif

#endif // NMTOOLS_TESTING_DATA_ARRAY_CONV_HPP