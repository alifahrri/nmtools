#ifndef NMTOOLS_TESTING_DATA_INDEX_BROADCAST_TO_STRIDES_HPP
#define NMTOOLS_TESTING_DATA_INDEX_BROADCAST_TO_STRIDES_HPP

#include "nmtools/testing/testing.hpp"

NMTOOLS_TESTING_DECLARE_CASE(index,broadcast_to_strides)
{
    using namespace literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int src_shape[2] = {4,1};
        inline int dst_shape[2] = {4,4};

        inline auto src_shape_ct = nmtools_tuple{4_ct,1_ct};
        inline auto dst_shape_ct = nmtools_tuple{4_ct,4_ct};

        inline auto src_shape_nl1 = nmtools_array{null_size_t(),null_size_t(1)};
        inline auto dst_shape_nl1 = nmtools_array{null_size_t(),null_size_t(4)};

        inline auto src_shape_mx1 = nmtools_tuple{4,1_ct};
        inline auto dst_shape_mx1 = nmtools_tuple{4,4_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[2] = {1,0};
        inline auto result_nl1 = nmtools_array{null_size_t(1),null_size_t(0)};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int src_shape[1] = {1};
        inline int dst_shape[2] = {6,1};

        inline auto src_shape_ct = nmtools_tuple{1_ct};
        inline auto dst_shape_ct = nmtools_tuple{6_ct,1_ct};

        inline auto src_shape_nl1 = nmtools_array{null_size_t(1)};
        inline auto dst_shape_nl1 = nmtools_array{null_size_t(6),null_size_t(1)};

        inline auto src_shape_mx1 = nmtools_tuple{1_ct};
        inline auto dst_shape_mx1 = nmtools_tuple{6_ct,1_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[2] = {0,0};
        inline auto result_nl1 = nmtools_array{null_size_t(0),null_size_t(0)};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int src_shape[1] = {3};
        inline int dst_shape[2] = {6,3};

        inline auto src_shape_ct = nmtools_tuple{3_ct};
        inline auto dst_shape_ct = nmtools_tuple{6_ct,3_ct};

        inline auto src_shape_nl1 = nmtools_array{null_size_t(3)};
        inline auto dst_shape_nl1 = nmtools_array{null_size_t(6),null_size_t(3)};

        inline auto src_shape_mx1 = nmtools_tuple{3_ct};
        inline auto dst_shape_mx1 = nmtools_tuple{6_ct,3_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[2] = {0,1};
        inline auto result_nl1 = nmtools_array{null_size_t(0),null_size_t(1)};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int src_shape[3] = {2,1,3};
        inline int dst_shape[3] = {2,4,3};

        inline auto src_shape_ct = nmtools_tuple{2_ct,1_ct,3_ct};
        inline auto dst_shape_ct = nmtools_tuple{2_ct,4_ct,3_ct};

        inline auto src_shape_nl1 = nmtools_array{null_size_t(2),null_size_t(1),null_size_t(3)};
        inline auto dst_shape_nl1 = nmtools_array{null_size_t(2),null_size_t(4),null_size_t(3)};

        inline auto src_shape_mx1 = nmtools_tuple{2_ct,1_ct,3_ct};
        inline auto dst_shape_mx1 = nmtools_tuple{2_ct,4_ct,3_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[3] = {3,0,1};
        inline auto result_nl1 = nmtools_array{null_size_t(3),null_size_t(0),null_size_t(1)};
    }
}

NMTOOLS_TESTING_DECLARE_CASE(index,broadcast_to_v2)
{
    using namespace literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1a)
    {
        // inline int dst_shape[2] = {4,4};
        inline int src_shape[2] = {4,1};
        inline int indices[2]   = {0,0};
        inline int dst_strides[2] = {1,0};
        // not-broadcasted stride of src shape (4,1) is (1,1)
        inline int src_strides[2] = {1,1};

        inline auto src_shape_ct = nmtools_tuple{4_ct,1_ct};
        inline auto indices_ct   = nmtools_tuple{0_ct,0_ct};
        inline auto dst_strides_ct = nmtools_tuple{1_ct,0_ct};
        inline auto src_strides_ct = nmtools_tuple{1_ct,1_ct};

        inline auto src_shape_nl1 = nmtools_array{null_size_t(),null_size_t(1)};
        inline auto indices_nl1 = nmtools_array{null_size_t(),null_size_t(0)};
        inline auto dst_strides_nl1 = nmtools_array{null_size_t(),null_size_t(0)};
        inline auto src_strides_nl1 = nmtools_array{null_size_t(),null_size_t(1)};

        inline auto src_shape_mx1 = nmtools_tuple{4,1_ct};
        inline auto indices_mx1   = nmtools_tuple{0,0_ct};
        inline auto dst_strides_mx1 = nmtools_tuple{1,0_ct};
        inline auto src_strides_mx1 = nmtools_tuple{1,1_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_strides)
        NMTOOLS_CAST_INDEX_ARRAYS(src_strides)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1a)
    {
        inline int result[2] = {0,0};
        // with current implementation it can't partially compute the result
        inline auto result_nl1 = nmtools_array{null_size_t(),null_size_t()};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1b)
    {
        inline int src_shape[2] = {4,1};
        inline int indices[2] = {0,1};
        inline int dst_strides[2] = {1,0};
        inline int src_strides[2] = {1,1};

        inline auto src_shape_ct = nmtools_tuple{4_ct,1_ct};
        inline auto indices_ct   = nmtools_tuple{0_ct,1_ct};
        inline auto dst_strides_ct = nmtools_tuple{1_ct,0_ct};
        inline auto src_strides_ct = nmtools_tuple{1_ct,1_ct};

        inline auto src_shape_nl1 = nmtools_array{null_size_t(),null_size_t(1)};
        inline auto indices_nl1 = nmtools_array{null_size_t(),null_size_t(1)};
        inline auto dst_strides_nl1 = nmtools_array{null_size_t(),null_size_t(0)};
        inline auto src_strides_nl1 = nmtools_array{null_size_t(),null_size_t(1)};

        inline auto src_shape_mx1 = nmtools_tuple{4,1_ct};
        inline auto indices_mx1   = nmtools_tuple{0,1_ct};
        inline auto dst_strides_mx1 = nmtools_tuple{1,0_ct};
        inline auto src_strides_mx1 = nmtools_tuple{1,1_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_strides)
        NMTOOLS_CAST_INDEX_ARRAYS(src_strides)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1b)
    {
        inline int result[2] = {0,0};
        inline auto result_nl1 = nmtools_array{null_size_t(),null_size_t()};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1c)
    {
        inline int src_shape[2] = {4,1};
        inline int indices[2] = {0,2};
        inline int dst_strides[2] = {1,0};
        inline int src_strides[2] = {1,1};

        inline auto src_shape_ct = nmtools_tuple{4_ct,1_ct};
        inline auto indices_ct   = nmtools_tuple{0_ct,2_ct};
        inline auto dst_strides_ct = nmtools_tuple{1_ct,0_ct};
        inline auto src_strides_ct = nmtools_tuple{1_ct,1_ct};

        inline auto src_shape_nl1 = nmtools_array{null_size_t(),null_size_t(1)};
        inline auto indices_nl1 = nmtools_array{null_size_t(),null_size_t(2)};
        inline auto dst_strides_nl1 = nmtools_array{null_size_t(),null_size_t(0)};
        inline auto src_strides_nl1 = nmtools_array{null_size_t(),null_size_t(1)};

        inline auto src_shape_mx1 = nmtools_tuple{4,1_ct};
        inline auto indices_mx1   = nmtools_tuple{0,2_ct};
        inline auto dst_strides_mx1 = nmtools_tuple{1,0_ct};
        inline auto src_strides_mx1 = nmtools_tuple{1,1_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_strides)
        NMTOOLS_CAST_INDEX_ARRAYS(src_strides)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1c)
    {
        inline int result[2] = {0,0};
        inline auto result_nl1 = nmtools_array{null_size_t(),null_size_t()};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1d)
    {
        inline int src_shape[2] = {4,1};
        inline int indices[2] = {0,3};
        inline int dst_strides[2] = {1,0};
        inline int src_strides[2] = {1,1};

        inline auto src_shape_ct = nmtools_tuple{4_ct,1_ct};
        inline auto indices_ct   = nmtools_tuple{0_ct,3_ct};
        inline auto dst_strides_ct = nmtools_tuple{1_ct,0_ct};
        inline auto src_strides_ct = nmtools_tuple{1_ct,1_ct};

        inline auto src_shape_nl1 = nmtools_array{null_size_t(),null_size_t(1)};
        inline auto indices_nl1 = nmtools_array{null_size_t(),null_size_t(3)};
        inline auto dst_strides_nl1 = nmtools_array{null_size_t(),null_size_t(0)};
        inline auto src_strides_nl1 = nmtools_array{null_size_t(),null_size_t(1)};

        inline auto src_shape_mx1 = nmtools_tuple{4,1_ct};
        inline auto indices_mx1   = nmtools_tuple{0,3_ct};
        inline auto dst_strides_mx1 = nmtools_tuple{1,0_ct};
        inline auto src_strides_mx1 = nmtools_tuple{1,1_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_strides)
        NMTOOLS_CAST_INDEX_ARRAYS(src_strides)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1d)
    {
        inline int result[2] = {0,0};
        inline auto result_nl1 = nmtools_array{null_size_t(),null_size_t()};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1e)
    {
        inline int src_shape[2] = {4,1};
        inline int indices[2] = {1,0};
        inline int dst_strides[2] = {1,0};
        inline int src_strides[2] = {1,1};

        inline auto src_shape_ct = nmtools_tuple{4_ct,1_ct};
        inline auto indices_ct   = nmtools_tuple{1_ct,0_ct};
        inline auto dst_strides_ct = nmtools_tuple{1_ct,0_ct};
        inline auto src_strides_ct = nmtools_tuple{1_ct,1_ct};

        inline auto src_shape_nl1 = nmtools_array{null_size_t(),null_size_t(1)};
        inline auto indices_nl1 = nmtools_array{null_size_t(),null_size_t(0)};
        inline auto dst_strides_nl1 = nmtools_array{null_size_t(),null_size_t(0)};
        inline auto src_strides_nl1 = nmtools_array{null_size_t(),null_size_t(1)};

        inline auto src_shape_mx1 = nmtools_tuple{4,1_ct};
        inline auto indices_mx1   = nmtools_tuple{1,0_ct};
        inline auto dst_strides_mx1 = nmtools_tuple{1,0_ct};
        inline auto src_strides_mx1 = nmtools_tuple{1,1_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_strides)
        NMTOOLS_CAST_INDEX_ARRAYS(src_strides)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1e)
    {
        inline int result[2] = {1,0};
        inline auto result_nl1 = nmtools_array{null_size_t(),null_size_t()};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1f)
    {
        inline int src_shape[2] = {4,1};
        inline int indices[2] = {2,0};
        inline int dst_strides[2] = {1,0};
        inline int src_strides[2] = {1,1};

        inline auto src_shape_ct = nmtools_tuple{4_ct,1_ct};
        inline auto indices_ct   = nmtools_tuple{2_ct,0_ct};
        inline auto dst_strides_ct = nmtools_tuple{1_ct,0_ct};
        inline auto src_strides_ct = nmtools_tuple{1_ct,1_ct};

        inline auto src_shape_nl1 = nmtools_array{null_size_t(),null_size_t(1)};
        inline auto indices_nl1 = nmtools_array{null_size_t(),null_size_t(0)};
        inline auto dst_strides_nl1 = nmtools_array{null_size_t(),null_size_t(0)};
        inline auto src_strides_nl1 = nmtools_array{null_size_t(),null_size_t(1)};

        inline auto src_shape_mx1 = nmtools_tuple{4,1_ct};
        inline auto indices_mx1   = nmtools_tuple{2,0_ct};
        inline auto dst_strides_mx1 = nmtools_tuple{1,0_ct};
        inline auto src_strides_mx1 = nmtools_tuple{1,1_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_strides)
        NMTOOLS_CAST_INDEX_ARRAYS(src_strides)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1f)
    {
        inline int result[2] = {2,0};
        inline auto result_nl1 = nmtools_array{null_size_t(),null_size_t()};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1g)
    {
        inline int src_shape[2] = {4,1};
        inline int indices[2] = {3,0};
        inline int dst_strides[2] = {1,0};
        inline int src_strides[2] = {1,1};

        inline auto src_shape_ct = nmtools_tuple{4_ct,1_ct};
        inline auto indices_ct   = nmtools_tuple{3_ct,0_ct};
        inline auto dst_strides_ct = nmtools_tuple{1_ct,0_ct};
        inline auto src_strides_ct = nmtools_tuple{1_ct,1_ct};

        inline auto src_shape_nl1 = nmtools_array{null_size_t(),null_size_t(1)};
        inline auto indices_nl1 = nmtools_array{null_size_t(),null_size_t(0)};
        inline auto dst_strides_nl1 = nmtools_array{null_size_t(),null_size_t(0)};
        inline auto src_strides_nl1 = nmtools_array{null_size_t(),null_size_t(1)};

        inline auto src_shape_mx1 = nmtools_tuple{4,1_ct};
        inline auto indices_mx1   = nmtools_tuple{3,0_ct};
        inline auto dst_strides_mx1 = nmtools_tuple{1,0_ct};
        inline auto src_strides_mx1 = nmtools_tuple{1,1_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_strides)
        NMTOOLS_CAST_INDEX_ARRAYS(src_strides)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1g)
    {
        inline int result[2] = {3,0};
        inline auto result_nl1 = nmtools_array{null_size_t(),null_size_t()};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2a)
    {
        inline int src_shape[1] = {1};
        inline int indices[2] = {0,0};
        inline int dst_strides[2] = {0,0};
        inline int src_strides[1] = {1};

        inline auto src_shape_ct = nmtools_tuple{1_ct};
        inline auto indices_ct   = nmtools_tuple{0_ct,0_ct};
        inline auto dst_strides_ct = nmtools_tuple{0_ct,0_ct};
        inline auto src_strides_ct = nmtools_tuple{1_ct};

        inline auto src_shape_nl1 = nmtools_array{null_size_t(1)};
        inline auto indices_nl1 = nmtools_array{null_size_t(),null_size_t(0)};
        inline auto dst_strides_nl1 = nmtools_array{null_size_t(),null_size_t(0)};
        inline auto src_strides_nl1 = nmtools_array{null_size_t(1)};

        inline auto src_shape_mx1 = nmtools_tuple{1_ct};
        inline auto indices_mx1   = nmtools_tuple{0,0_ct};
        inline auto dst_strides_mx1 = nmtools_tuple{0,0_ct};
        inline auto src_strides_mx1 = nmtools_tuple{1_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_strides)
        NMTOOLS_CAST_INDEX_ARRAYS(src_strides)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2a)
    {
        inline int result[1] = {0};
        inline auto result_nl1 = nmtools_array{null_size_t()};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2b)
    {
        inline int src_shape[1] = {1};
        inline int indices[2] = {1,0};
        inline int dst_strides[2] = {0,0};
        inline int src_strides[1] = {1};

        inline auto src_shape_ct = nmtools_tuple{1_ct};
        inline auto indices_ct   = nmtools_tuple{1_ct,0_ct};
        inline auto dst_strides_ct = nmtools_tuple{0_ct,0_ct};
        inline auto src_strides_ct = nmtools_tuple{1_ct};

        inline auto src_shape_nl1 = nmtools_array{null_size_t(1)};
        inline auto indices_nl1 = nmtools_array{null_size_t(),null_size_t(0)};
        inline auto dst_strides_nl1 = nmtools_array{null_size_t(),null_size_t(0)};
        inline auto src_strides_nl1 = nmtools_array{null_size_t(1)};

        inline auto src_shape_mx1 = nmtools_tuple{1_ct};
        inline auto indices_mx1   = nmtools_tuple{1,0_ct};
        inline auto dst_strides_mx1 = nmtools_tuple{0,0_ct};
        inline auto src_strides_mx1 = nmtools_tuple{1_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_strides)
        NMTOOLS_CAST_INDEX_ARRAYS(src_strides)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2b)
    {
        inline int result[1] = {0};
        inline auto result_nl1 = nmtools_array{null_size_t()};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2c)
    {
        inline int src_shape[1] = {1};
        inline int indices[2] = {2,0};
        inline int dst_strides[2] = {0,0};
        inline int src_strides[1] = {1};

        inline auto src_shape_ct = nmtools_tuple{1_ct};
        inline auto indices_ct   = nmtools_tuple{2_ct,0_ct};
        inline auto dst_strides_ct = nmtools_tuple{0_ct,0_ct};
        inline auto src_strides_ct = nmtools_tuple{1_ct};

        inline auto src_shape_nl1 = nmtools_array{null_size_t(1)};
        inline auto indices_nl1 = nmtools_array{null_size_t(),null_size_t(0)};
        inline auto dst_strides_nl1 = nmtools_array{null_size_t(),null_size_t(0)};
        inline auto src_strides_nl1 = nmtools_array{null_size_t(1)};

        inline auto src_shape_mx1 = nmtools_tuple{1_ct};
        inline auto indices_mx1   = nmtools_tuple{2,0_ct};
        inline auto dst_strides_mx1 = nmtools_tuple{0,0_ct};
        inline auto src_strides_mx1 = nmtools_tuple{1_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_strides)
        NMTOOLS_CAST_INDEX_ARRAYS(src_strides)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2c)
    {
        inline int result[1] = {0};
        inline auto result_nl1 = nmtools_array{null_size_t()};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2d)
    {
        inline int src_shape[1] = {1};
        inline int indices[2] = {3,0};
        inline int dst_strides[2] = {0,0};
        inline int src_strides[1] = {1};

        inline auto src_shape_ct = nmtools_tuple{1_ct};
        inline auto indices_ct   = nmtools_tuple{3_ct,0_ct};
        inline auto dst_strides_ct = nmtools_tuple{0_ct,0_ct};
        inline auto src_strides_ct = nmtools_tuple{1_ct};

        inline auto src_shape_nl1 = nmtools_array{null_size_t(1)};
        inline auto indices_nl1 = nmtools_array{null_size_t(),null_size_t(0)};
        inline auto dst_strides_nl1 = nmtools_array{null_size_t(),null_size_t(0)};
        inline auto src_strides_nl1 = nmtools_array{null_size_t(1)};

        inline auto src_shape_mx1 = nmtools_tuple{1_ct};
        inline auto indices_mx1   = nmtools_tuple{3,0_ct};
        inline auto dst_strides_mx1 = nmtools_tuple{0,0_ct};
        inline auto src_strides_mx1 = nmtools_tuple{1_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_strides)
        NMTOOLS_CAST_INDEX_ARRAYS(src_strides)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2d)
    {
        inline int result[1] = {0};
        inline auto result_nl1 = nmtools_array{null_size_t()};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2e)
    {
        inline int src_shape[1] = {1};
        inline int indices[2] = {4,0};
        inline int dst_strides[2] = {0,0};
        inline int src_strides[1] = {1};

        inline auto src_shape_ct = nmtools_tuple{1_ct};
        inline auto indices_ct   = nmtools_tuple{4_ct,0_ct};
        inline auto dst_strides_ct = nmtools_tuple{0_ct,0_ct};
        inline auto src_strides_ct = nmtools_tuple{1_ct};

        inline auto src_shape_nl1 = nmtools_array{null_size_t(1)};
        inline auto indices_nl1 = nmtools_array{null_size_t(),null_size_t(0)};
        inline auto dst_strides_nl1 = nmtools_array{null_size_t(),null_size_t(0)};
        inline auto src_strides_nl1 = nmtools_array{null_size_t(1)};

        inline auto src_shape_mx1 = nmtools_tuple{1_ct};
        inline auto indices_mx1   = nmtools_tuple{4,0_ct};
        inline auto dst_strides_mx1 = nmtools_tuple{0,0_ct};
        inline auto src_strides_mx1 = nmtools_tuple{1_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_strides)
        NMTOOLS_CAST_INDEX_ARRAYS(src_strides)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2e)
    {
        inline int result[1] = {0};
        inline auto result_nl1 = nmtools_array{null_size_t()};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2f)
    {
        inline int src_shape[1] = {1};
        inline int indices[2] = {5,0};
        inline int dst_strides[2] = {0,0};
        inline int src_strides[1] = {1};

        inline auto src_shape_ct = nmtools_tuple{1_ct};
        inline auto indices_ct   = nmtools_tuple{5_ct,0_ct};
        inline auto dst_strides_ct = nmtools_tuple{0_ct,0_ct};
        inline auto src_strides_ct = nmtools_tuple{1_ct};

        inline auto src_shape_nl1 = nmtools_array{null_size_t(1)};
        inline auto indices_nl1 = nmtools_array{null_size_t(),null_size_t(0)};
        inline auto dst_strides_nl1 = nmtools_array{null_size_t(),null_size_t(0)};
        inline auto src_strides_nl1 = nmtools_array{null_size_t(1)};

        inline auto src_shape_mx1 = nmtools_tuple{1_ct};
        inline auto indices_mx1   = nmtools_tuple{5,0_ct};
        inline auto dst_strides_mx1 = nmtools_tuple{0,0_ct};
        inline auto src_strides_mx1 = nmtools_tuple{1_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_strides)
        NMTOOLS_CAST_INDEX_ARRAYS(src_strides)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2f)
    {
        inline int result[1] = {0};
        inline auto result_nl1 = nmtools_array{null_size_t()};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3a)
    {
        inline int src_shape[1] = {3};
        inline int indices[2] = {0,0};
        inline int dst_strides[2] = {0,1};
        inline int src_strides[1] = {1};

        inline auto src_shape_ct = nmtools_tuple{3_ct};
        inline auto indices_ct   = nmtools_tuple{0_ct,0_ct};
        inline auto dst_strides_ct = nmtools_tuple{0_ct,1_ct};
        inline auto src_strides_ct = nmtools_tuple{1_ct};

        inline auto src_shape_nl1 = nmtools_array{null_size_t(3)};
        inline auto indices_nl1 = nmtools_array{null_size_t(),null_size_t(0)};
        inline auto dst_strides_nl1 = nmtools_array{null_size_t(),null_size_t(1)};
        inline auto src_strides_nl1 = nmtools_array{null_size_t(1)};

        inline auto src_shape_mx1 = nmtools_tuple{3_ct};
        inline auto indices_mx1   = nmtools_tuple{0,0_ct};
        inline auto dst_strides_mx1 = nmtools_tuple{0,1_ct};
        inline auto src_strides_mx1 = nmtools_tuple{1_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_strides)
        NMTOOLS_CAST_INDEX_ARRAYS(src_strides)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3a)
    {
        inline int result[1] = {0};
        inline auto result_nl1 = nmtools_array{null_size_t()};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3b)
    {
        inline int src_shape[1] = {3};
        inline int indices[2] = {0,1};
        inline int dst_strides[2] = {0,1};
        inline int src_strides[1] = {1};

        inline auto src_shape_ct = nmtools_tuple{3_ct};
        inline auto indices_ct   = nmtools_tuple{0_ct,1_ct};
        inline auto dst_strides_ct = nmtools_tuple{0_ct,1_ct};
        inline auto src_strides_ct = nmtools_tuple{1_ct};

        inline auto src_shape_nl1 = nmtools_array{null_size_t(3)};
        inline auto indices_nl1 = nmtools_array{null_size_t(),null_size_t(1)};
        inline auto dst_strides_nl1 = nmtools_array{null_size_t(),null_size_t(1)};
        inline auto src_strides_nl1 = nmtools_array{null_size_t(1)};

        inline auto src_shape_mx1 = nmtools_tuple{3_ct};
        inline auto indices_mx1   = nmtools_tuple{0,1_ct};
        inline auto dst_strides_mx1 = nmtools_tuple{0,1_ct};
        inline auto src_strides_mx1 = nmtools_tuple{1_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_strides)
        NMTOOLS_CAST_INDEX_ARRAYS(src_strides)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3b)
    {
        inline int result[1] = {1};
        inline auto result_nl1 = nmtools_array{null_size_t()};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3c)
    {
        inline int src_shape[1] = {3};
        inline int indices[2] = {0,2};
        inline int dst_strides[2] = {0,1};
        inline int src_strides[1] = {1};

        inline auto src_shape_ct = nmtools_tuple{3_ct};
        inline auto indices_ct   = nmtools_tuple{0_ct,2_ct};
        inline auto dst_strides_ct = nmtools_tuple{0_ct,1_ct};
        inline auto src_strides_ct = nmtools_tuple{1_ct};

        inline auto src_shape_nl1 = nmtools_array{null_size_t(3)};
        inline auto indices_nl1 = nmtools_array{null_size_t(),null_size_t(2)};
        inline auto dst_strides_nl1 = nmtools_array{null_size_t(),null_size_t(1)};
        inline auto src_strides_nl1 = nmtools_array{null_size_t(1)};

        inline auto src_shape_mx1 = nmtools_tuple{3_ct};
        inline auto indices_mx1   = nmtools_tuple{0,2_ct};
        inline auto dst_strides_mx1 = nmtools_tuple{0,1_ct};
        inline auto src_strides_mx1 = nmtools_tuple{1_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_strides)
        NMTOOLS_CAST_INDEX_ARRAYS(src_strides)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3c)
    {
        inline int result[1] = {2};
        inline auto result_nl1 = nmtools_array{null_size_t()};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3d)
    {
        inline int src_shape[1] = {3};
        inline int indices[2] = {1,0};
        inline int dst_strides[2] = {0,1};
        inline int src_strides[1] = {1};

        inline auto src_shape_ct = nmtools_tuple{3_ct};
        inline auto indices_ct   = nmtools_tuple{1_ct,0_ct};
        inline auto dst_strides_ct = nmtools_tuple{0_ct,1_ct};
        inline auto src_strides_ct = nmtools_tuple{1_ct};

        inline auto src_shape_nl1 = nmtools_array{null_size_t(3)};
        inline auto indices_nl1 = nmtools_array{null_size_t(),null_size_t(0)};
        inline auto dst_strides_nl1 = nmtools_array{null_size_t(),null_size_t(1)};
        inline auto src_strides_nl1 = nmtools_array{null_size_t(1)};

        inline auto src_shape_mx1 = nmtools_tuple{3_ct};
        inline auto indices_mx1   = nmtools_tuple{1,0_ct};
        inline auto dst_strides_mx1 = nmtools_tuple{0,1_ct};
        inline auto src_strides_mx1 = nmtools_tuple{1_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_strides)
        NMTOOLS_CAST_INDEX_ARRAYS(src_strides)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3d)
    {
        inline int result[1] = {0};
        inline auto result_nl1 = nmtools_array{null_size_t()};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3e)
    {
        inline int src_shape[1] = {3};
        inline int indices[2] = {1,1};
        inline int dst_strides[2] = {0,1};
        inline int src_strides[1] = {1};

        inline auto src_shape_ct = nmtools_tuple{3_ct};
        inline auto indices_ct   = nmtools_tuple{1_ct,1_ct};
        inline auto dst_strides_ct = nmtools_tuple{0_ct,1_ct};
        inline auto src_strides_ct = nmtools_tuple{1_ct};

        inline auto src_shape_nl1 = nmtools_array{null_size_t(3)};
        inline auto indices_nl1 = nmtools_array{null_size_t(),null_size_t(1)};
        inline auto dst_strides_nl1 = nmtools_array{null_size_t(),null_size_t(1)};
        inline auto src_strides_nl1 = nmtools_array{null_size_t(1)};

        inline auto src_shape_mx1 = nmtools_tuple{3_ct};
        inline auto indices_mx1   = nmtools_tuple{1,1_ct};
        inline auto dst_strides_mx1 = nmtools_tuple{0,1_ct};
        inline auto src_strides_mx1 = nmtools_tuple{1_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_strides)
        NMTOOLS_CAST_INDEX_ARRAYS(src_strides)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3e)
    {
        inline int result[1] = {1};
        inline auto result_nl1 = nmtools_array{null_size_t()};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3f)
    {
        inline int src_shape[1] = {3};
        inline int indices[2] = {1,2};
        inline int dst_strides[2] = {0,1};
        inline int src_strides[1] = {1};

        inline auto src_shape_ct = nmtools_tuple{3_ct};
        inline auto indices_ct   = nmtools_tuple{1_ct,2_ct};
        inline auto dst_strides_ct = nmtools_tuple{0_ct,1_ct};
        inline auto src_strides_ct = nmtools_tuple{1_ct};

        inline auto src_shape_nl1 = nmtools_array{null_size_t(3)};
        inline auto indices_nl1 = nmtools_array{null_size_t(),null_size_t(2)};
        inline auto dst_strides_nl1 = nmtools_array{null_size_t(),null_size_t(1)};
        inline auto src_strides_nl1 = nmtools_array{null_size_t(1)};

        inline auto src_shape_mx1 = nmtools_tuple{3_ct};
        inline auto indices_mx1   = nmtools_tuple{1,2_ct};
        inline auto dst_strides_mx1 = nmtools_tuple{0,1_ct};
        inline auto src_strides_mx1 = nmtools_tuple{1_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_strides)
        NMTOOLS_CAST_INDEX_ARRAYS(src_strides)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3f)
    {
        inline int result[1] = {2};
        inline auto result_nl1 = nmtools_array{null_size_t()};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3g)
    {
        inline int src_shape[1] = {3};
        inline int indices[2] = {5,2};
        inline int dst_strides[2] = {0,1};
        inline int src_strides[1] = {1};

        inline auto src_shape_ct = nmtools_tuple{3_ct};
        inline auto indices_ct   = nmtools_tuple{5_ct,2_ct};
        inline auto dst_strides_ct = nmtools_tuple{0_ct,1_ct};
        inline auto src_strides_ct = nmtools_tuple{1_ct};

        inline auto src_shape_nl1 = nmtools_array{null_size_t(3)};
        inline auto indices_nl1 = nmtools_array{null_size_t(),null_size_t(2)};
        inline auto dst_strides_nl1 = nmtools_array{null_size_t(),null_size_t(1)};
        inline auto src_strides_nl1 = nmtools_array{null_size_t(1)};

        inline auto src_shape_mx1 = nmtools_tuple{3_ct};
        inline auto indices_mx1   = nmtools_tuple{5,2_ct};
        inline auto dst_strides_mx1 = nmtools_tuple{0,1_ct};
        inline auto src_strides_mx1 = nmtools_tuple{1_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_strides)
        NMTOOLS_CAST_INDEX_ARRAYS(src_strides)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3g)
    {
        inline int result[1] = {2};
        inline auto result_nl1 = nmtools_array{null_size_t()};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4a)
    {
        inline int src_shape[3] = {2,1,3};
        inline int indices[3] = {0,0,0};
        inline int dst_strides[3] = {3,0,1};
        inline int src_strides[3] = {3,3,1};

        inline auto src_shape_ct = nmtools_tuple{2_ct,1_ct,3_ct};
        inline auto indices_ct   = nmtools_tuple{0_ct,0_ct,0_ct};
        inline auto dst_strides_ct = nmtools_tuple{3_ct,0_ct,1_ct};
        inline auto src_strides_ct = nmtools_tuple{3_ct,3_ct,1_ct};

        inline auto src_shape_nl1 = nmtools_array{null_size_t(),null_size_t(1),null_size_t(3)};
        inline auto indices_nl1 = nmtools_array{null_size_t(),null_size_t(0),null_size_t(0)};
        inline auto dst_strides_nl1 = nmtools_array{null_size_t(),null_size_t(0),null_size_t(1)};
        inline auto src_strides_nl1 = nmtools_array{null_size_t(),null_size_t(3),null_size_t(1)};

        inline auto src_shape_mx1 = nmtools_tuple{2,1_ct,3_ct};
        inline auto indices_mx1   = nmtools_tuple{0,0_ct,0_ct};
        inline auto dst_strides_mx1 = nmtools_tuple{3,0_ct,1_ct};
        inline auto src_strides_mx1 = nmtools_tuple{3,3_ct,1_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_strides)
        NMTOOLS_CAST_INDEX_ARRAYS(src_strides)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4a)
    {
        inline int result[3] = {0,0,0};
        inline auto result_nl1 = nmtools_array{null_size_t(),null_size_t(),null_size_t()};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4b)
    {
        inline int src_shape[3] = {2,1,3};
        inline int indices[3] = {0,1,0};
        inline int dst_strides[3] = {3,0,1};
        inline int src_strides[3] = {3,3,1};

        inline auto src_shape_ct = nmtools_tuple{2_ct,1_ct,3_ct};
        inline auto indices_ct   = nmtools_tuple{0_ct,1_ct,0_ct};
        inline auto dst_strides_ct = nmtools_tuple{3_ct,0_ct,1_ct};
        inline auto src_strides_ct = nmtools_tuple{3_ct,3_ct,1_ct};

        inline auto src_shape_nl1 = nmtools_array{null_size_t(),null_size_t(1),null_size_t(3)};
        inline auto indices_nl1 = nmtools_array{null_size_t(),null_size_t(1),null_size_t(0)};
        inline auto dst_strides_nl1 = nmtools_array{null_size_t(),null_size_t(0),null_size_t(1)};
        inline auto src_strides_nl1 = nmtools_array{null_size_t(),null_size_t(3),null_size_t(1)};

        inline auto src_shape_mx1 = nmtools_tuple{2,1_ct,3_ct};
        inline auto indices_mx1   = nmtools_tuple{0,1_ct,0_ct};
        inline auto dst_strides_mx1 = nmtools_tuple{3,0_ct,1_ct};
        inline auto src_strides_mx1 = nmtools_tuple{3,3_ct,1_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_strides)
        NMTOOLS_CAST_INDEX_ARRAYS(src_strides)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4b)
    {
        inline int result[3] = {0,0,0};
        inline auto result_nl1 = nmtools_array{null_size_t(),null_size_t(),null_size_t()};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4c)
    {
        inline int src_shape[3] = {2,1,3};
        inline int indices[3] = {0,0,1};
        inline int dst_strides[3] = {3,0,1};
        inline int src_strides[3] = {3,3,1};

        inline auto src_shape_ct = nmtools_tuple{2_ct,1_ct,3_ct};
        inline auto indices_ct   = nmtools_tuple{0_ct,0_ct,1_ct};
        inline auto dst_strides_ct = nmtools_tuple{3_ct,0_ct,1_ct};
        inline auto src_strides_ct = nmtools_tuple{3_ct,3_ct,1_ct};

        inline auto src_shape_nl1 = nmtools_array{null_size_t(),null_size_t(1),null_size_t(3)};
        inline auto indices_nl1 = nmtools_array{null_size_t(),null_size_t(0),null_size_t(1)};
        inline auto dst_strides_nl1 = nmtools_array{null_size_t(),null_size_t(0),null_size_t(1)};
        inline auto src_strides_nl1 = nmtools_array{null_size_t(),null_size_t(3),null_size_t(1)};

        inline auto src_shape_mx1 = nmtools_tuple{2,1_ct,3_ct};
        inline auto indices_mx1   = nmtools_tuple{0,0_ct,1_ct};
        inline auto dst_strides_mx1 = nmtools_tuple{3,0_ct,1_ct};
        inline auto src_strides_mx1 = nmtools_tuple{3,3_ct,1_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_strides)
        NMTOOLS_CAST_INDEX_ARRAYS(src_strides)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4c)
    {
        inline int result[3] = {0,0,1};
        inline auto result_nl1 = nmtools_array{null_size_t(),null_size_t(),null_size_t()};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4d)
    {
        inline int src_shape[3] = {2,1,3};
        inline int indices[3] = {0,3,2};
        inline int dst_strides[3] = {3,0,1};
        inline int src_strides[3] = {3,3,1};

        inline auto src_shape_ct = nmtools_tuple{2_ct,1_ct,3_ct};
        inline auto indices_ct   = nmtools_tuple{0_ct,3_ct,2_ct};
        inline auto dst_strides_ct = nmtools_tuple{3_ct,0_ct,1_ct};
        inline auto src_strides_ct = nmtools_tuple{3_ct,3_ct,1_ct};

        inline auto src_shape_nl1 = nmtools_array{null_size_t(),null_size_t(1),null_size_t(3)};
        inline auto indices_nl1 = nmtools_array{null_size_t(),null_size_t(3),null_size_t(2)};
        inline auto dst_strides_nl1 = nmtools_array{null_size_t(),null_size_t(0),null_size_t(1)};
        inline auto src_strides_nl1 = nmtools_array{null_size_t(),null_size_t(3),null_size_t(1)};

        inline auto src_shape_mx1 = nmtools_tuple{2,1_ct,3_ct};
        inline auto indices_mx1   = nmtools_tuple{0,3_ct,2_ct};
        inline auto dst_strides_mx1 = nmtools_tuple{3,0_ct,1_ct};
        inline auto src_strides_mx1 = nmtools_tuple{3,3_ct,1_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_strides)
        NMTOOLS_CAST_INDEX_ARRAYS(src_strides)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4d)
    {
        inline int result[3] = {0,0,2};
        inline auto result_nl1 = nmtools_array{null_size_t(),null_size_t(),null_size_t()};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4e)
    {
        inline int src_shape[3] = {2,1,3};
        inline int indices[3] = {1,0,0};
        inline int dst_strides[3] = {3,0,1};
        inline int src_strides[3] = {3,3,1};

        inline auto src_shape_ct = nmtools_tuple{2_ct,1_ct,3_ct};
        inline auto indices_ct   = nmtools_tuple{1_ct,0_ct,0_ct};
        inline auto dst_strides_ct = nmtools_tuple{3_ct,0_ct,1_ct};
        inline auto src_strides_ct = nmtools_tuple{3_ct,3_ct,1_ct};

        inline auto src_shape_nl1 = nmtools_array{null_size_t(),null_size_t(1),null_size_t(3)};
        inline auto indices_nl1 = nmtools_array{null_size_t(),null_size_t(0),null_size_t(0)};
        inline auto dst_strides_nl1 = nmtools_array{null_size_t(),null_size_t(0),null_size_t(1)};
        inline auto src_strides_nl1 = nmtools_array{null_size_t(),null_size_t(3),null_size_t(1)};

        inline auto src_shape_mx1 = nmtools_tuple{2,1_ct,3_ct};
        inline auto indices_mx1   = nmtools_tuple{1,0_ct,0_ct};
        inline auto dst_strides_mx1 = nmtools_tuple{3,0_ct,1_ct};
        inline auto src_strides_mx1 = nmtools_tuple{3,3_ct,1_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_strides)
        NMTOOLS_CAST_INDEX_ARRAYS(src_strides)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4e)
    {
        inline int result[3] = {1,0,0};
        inline auto result_nl1 = nmtools_array{null_size_t(),null_size_t(),null_size_t()};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4f)
    {
        inline int src_shape[3] = {2,1,3};
        inline int indices[3] = {1,2,0};
        inline int dst_strides[3] = {3,0,1};
        inline int src_strides[3] = {3,3,1};

        inline auto src_shape_ct = nmtools_tuple{2_ct,1_ct,3_ct};
        inline auto indices_ct   = nmtools_tuple{1_ct,2_ct,0_ct};
        inline auto dst_strides_ct = nmtools_tuple{3_ct,0_ct,1_ct};
        inline auto src_strides_ct = nmtools_tuple{3_ct,3_ct,1_ct};

        inline auto src_shape_nl1 = nmtools_array{null_size_t(),null_size_t(1),null_size_t(3)};
        inline auto indices_nl1 = nmtools_array{null_size_t(),null_size_t(2),null_size_t(0)};
        inline auto dst_strides_nl1 = nmtools_array{null_size_t(),null_size_t(0),null_size_t(1)};
        inline auto src_strides_nl1 = nmtools_array{null_size_t(),null_size_t(3),null_size_t(1)};

        inline auto src_shape_mx1 = nmtools_tuple{2,1_ct,3_ct};
        inline auto indices_mx1   = nmtools_tuple{1,2_ct,0_ct};
        inline auto dst_strides_mx1 = nmtools_tuple{3,0_ct,1_ct};
        inline auto src_strides_mx1 = nmtools_tuple{3,3_ct,1_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_strides)
        NMTOOLS_CAST_INDEX_ARRAYS(src_strides)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4f)
    {
        inline int result[3] = {1,0,0};
        inline auto result_nl1 = nmtools_array{null_size_t(),null_size_t(),null_size_t()};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4g)
    {
        inline int src_shape[3] = {2,1,3};
        inline int indices[3] = {1,3,2};
        inline int dst_strides[3] = {3,0,1};
        inline int src_strides[3] = {3,3,1};

        inline auto src_shape_ct = nmtools_tuple{2_ct,1_ct,3_ct};
        inline auto indices_ct   = nmtools_tuple{1_ct,3_ct,2_ct};
        inline auto dst_strides_ct = nmtools_tuple{3_ct,0_ct,1_ct};
        inline auto src_strides_ct = nmtools_tuple{3_ct,3_ct,1_ct};

        inline auto src_shape_nl1 = nmtools_array{null_size_t(),null_size_t(1),null_size_t(3)};
        inline auto indices_nl1 = nmtools_array{null_size_t(),null_size_t(3),null_size_t(2)};
        inline auto dst_strides_nl1 = nmtools_array{null_size_t(),null_size_t(0),null_size_t(1)};
        inline auto src_strides_nl1 = nmtools_array{null_size_t(),null_size_t(3),null_size_t(1)};

        inline auto src_shape_mx1 = nmtools_tuple{2,1_ct,3_ct};
        inline auto indices_mx1   = nmtools_tuple{1,3_ct,2_ct};
        inline auto dst_strides_mx1 = nmtools_tuple{3,0_ct,1_ct};
        inline auto src_strides_mx1 = nmtools_tuple{3,3_ct,1_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_strides)
        NMTOOLS_CAST_INDEX_ARRAYS(src_strides)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4g)
    {
        inline int result[3] = {1,0,2};
        inline auto result_nl1 = nmtools_array{null_size_t(),null_size_t(),null_size_t()};
    }
}

#endif // NMTOOLS_TESTING_DATA_INDEX_BROADCAST_TO_STRIDES_HPP