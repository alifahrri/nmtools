#ifndef NMTOOLS_TESTING_INDEX_CONVND_HPP
#define NMTOOLS_TESTING_INDEX_CONVND_HPP

#include "nmtools/meta.hpp"
#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

using namespace nmtools::literals;

NMTOOLS_TESTING_DECLARE_CASE(index, conv_reshape_input)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int src_shape[3] = {1,5,4};
        inline int groups = 1;
        inline auto n_planes = 1_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        // batch, 1 (to bcast w/ n_output), groups, channel, plane
        inline int result[5] = {1,1,1,5,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int src_shape[4] = {1,1,4,4};
        inline int groups = 1;
        inline auto n_planes = 2_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[6] = {1,1,1,1,4,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int src_shape[4] = {1,1,5,5};
        inline int groups = 1;
        inline auto n_planes = 2_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[6] = {1,1,1,1,5,5};
    }
}

NMTOOLS_TESTING_DECLARE_CASE(index, conv_reshape_weight)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int src_shape[3] = {1,5,3};
        inline int groups = 1;
        inline auto n_planes = 1_ct;
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[4] = {1,1,5,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int src_shape[4] = {1,1,3,3};
        inline int groups = 1;
        inline auto n_planes = 2_ct;
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[5] = {1,1,1,3,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int src_shape[4] = {2,1,3,3};
        inline int groups = 1;
        inline auto n_planes = 2_ct;
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[5] = {2,1,1,3,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int src_shape[4] = {4,3,3,3};
        inline int groups = 1;
        inline auto n_planes = 2_ct;
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[5] = {4,1,3,3,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int src_shape[4] = {4,3,3,3};
        inline int groups = 2;
        inline auto n_planes = 2_ct;
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int result[5] = {2,2,3,3,3};
    }
}

NMTOOLS_TESTING_DECLARE_CASE(index, conv_reduce_axis)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int n_planes = 1_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[2] = {-1,-3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int n_planes = 2_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[3] = {-1,-2,-5};
    }
}

NMTOOLS_TESTING_DECLARE_CASE(index, conv_reshape_reduce)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int src_shape[4] = {1,2,2,2};
        inline int groups = 2;
        inline auto n_planes = 1_ct;
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[3] = {1,4,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int src_shape[5] = {1,2,2,2,2};
        inline int groups = 2;
        inline auto n_planes = 2_ct;
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[4] = {1,4,2,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int src_shape[4] = {1,3,1,2};
        inline int groups = 1;
        inline auto n_planes = 1_ct;
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[3] = {1,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int src_shape[5] = {1,5,1,2,2};
        inline int groups = 1;
        inline auto n_planes = 2_ct;
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[4] = {1,5,2,2};
    }
}

NMTOOLS_TESTING_DECLARE_CASE(index,conv_sum_axes)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        
    }
}

NMTOOLS_TESTING_DECLARE_CASE(index, conv_kernel_size)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int weight_shape[3] = {1,5,3};
        inline auto n_planes = 1_ct;
        NMTOOLS_CAST_INDEX_ARRAYS(weight_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[1] = {3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int weight_shape[4] = {2,1,3,3};
        inline auto n_planes = 2_ct;
        NMTOOLS_CAST_INDEX_ARRAYS(weight_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[2] = {3,3};
    }
}

#endif // NMTOOLS_TESTING_INDEX_CONVND_HPP