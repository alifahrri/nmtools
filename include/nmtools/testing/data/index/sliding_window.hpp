#ifndef NMTOOLS_TESTING_DATA_INDEX_SLIDING_WINDOW_HPP
#define NMTOOLS_TESTING_DATA_INDEX_SLIDING_WINDOW_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

using namespace nmtools::literals;

NMTOOLS_TESTING_DECLARE_CASE(index, shape_sliding_window)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int src_shape[1] = {6};
        inline int window_shape = 3;
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)

        inline auto src_shape_ct = nmtools_tuple{6_ct};
        inline auto window_shape_ct = 3_ct;
        
        inline auto src_shape_cl = to_clipped(src_shape_ct);
        inline auto window_shape_cl = to_clipped(window_shape_ct);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int dst_shape[2] = {4,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int src_shape[2] = {3,4};
        inline int window_shape[2] = {2,2};
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)

        inline auto src_shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto window_shape_ct = nmtools_tuple{2_ct,2_ct};

        inline auto src_shape_cl = to_clipped(src_shape_ct);
        inline auto window_shape_cl = to_clipped(window_shape_ct);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int dst_shape[4] = {2,3,2,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int src_shape[2] = {3,4};
        inline int window_shape = 3;
        inline int axis = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)

        inline auto src_shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto window_shape_ct = 3_ct;
        inline auto axis_ct = 0_ct;

        inline auto src_shape_cl = to_clipped(src_shape_ct);
        inline auto window_shape_cl = to_clipped(window_shape_ct);
        inline auto axis_cl = to_clipped(axis_ct);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int dst_shape[3] = {1,4,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int src_shape[2] = {3,4};
        inline int window_shape[2] = {2,3};
        inline int axis[2] = {1,1};
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)

        inline auto src_shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto window_shape_ct = nmtools_tuple{2_ct,3_ct};
        inline auto axis_ct = nmtools_tuple{1_ct,1_ct};

        inline auto src_shape_cl = to_clipped(src_shape_ct);
        inline auto window_shape_cl = to_clipped(window_shape_ct);
        inline auto axis_cl = to_clipped(axis_ct);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int dst_shape[4] = {3,1,2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int src_shape[2] = {4,3};
        inline int window_shape[2] = {2,3};
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)

        inline auto src_shape_ct = nmtools_tuple{4_ct,3_ct};
        inline auto window_shape_ct = nmtools_tuple{2_ct,3_ct};

        inline auto src_shape_cl = to_clipped(src_shape_ct);
        inline auto window_shape_cl = to_clipped(window_shape_ct);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int dst_shape[4] = {3,1,2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int src_shape[2] = {4,3};
        inline int window_shape[2] = {2,3};
        inline int axis[2] = {0,0};
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)

        inline auto src_shape_ct = nmtools_tuple{4_ct,3_ct};
        inline auto window_shape_ct = nmtools_tuple{2_ct,3_ct};
        inline auto axis_ct = nmtools_tuple{0_ct,0_ct};

        inline auto src_shape_cl = to_clipped(src_shape_ct);
        inline auto window_shape_cl = to_clipped(window_shape_ct);
        inline auto axis_cl = to_clipped(axis_ct);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int dst_shape[4] = {1,3,2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int src_shape[2] = {4,3};
        inline int window_shape[3] = {2,2,2};
        inline int axis[3] = {0,0,0};
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)

        inline auto src_shape_ct = nmtools_tuple{4_ct,3_ct};
        inline auto window_shape_ct = nmtools_tuple{2_ct,2_ct,2_ct};
        inline auto axis_ct = nmtools_tuple{0_ct,0_ct,0_ct};

        inline auto src_shape_cl = to_clipped(src_shape_ct);
        inline auto window_shape_cl = to_clipped(window_shape_ct);
        inline auto axis_cl = to_clipped(axis_ct);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int dst_shape[5] = {1,3,2,2,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline int src_shape[2] = {4,3};
        inline int window_shape[3] = {2,2,2};
        inline int axis[3] = {0,1,0};
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)

        inline auto src_shape_ct = nmtools_tuple{4_ct,3_ct};
        inline auto window_shape_ct = nmtools_tuple{2_ct,2_ct,2_ct};
        inline auto axis_ct = nmtools_tuple{0_ct,1_ct,0_ct};

        inline auto src_shape_cl = to_clipped(src_shape_ct);
        inline auto window_shape_cl = to_clipped(window_shape_ct);
        inline auto axis_cl = to_clipped(axis_ct);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline int dst_shape[5] = {2,2,2,2,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        inline int src_shape[3] = {2,4,3};
        inline int window_shape[3] = {2,2,2};
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)

        inline auto src_shape_ct = nmtools_tuple{2_ct,4_ct,3_ct};
        inline auto window_shape_ct = nmtools_tuple{2_ct,2_ct,2_ct};

        inline auto src_shape_cl = to_clipped(src_shape_ct);
        inline auto window_shape_cl = to_clipped(window_shape_ct);
    }

    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline int dst_shape[6] = {1,3,2,2,2,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        inline int src_shape[3] = {2,4,3};
        inline int window_shape[3] = {2,3,2};
        inline int axis[3] = {2,1,0};
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)

        inline auto src_shape_ct = nmtools_tuple{2_ct,4_ct,3_ct};
        inline auto window_shape_ct = nmtools_tuple{2_ct,3_ct,2_ct};
        inline auto axis_ct = nmtools_tuple{2_ct,1_ct,0_ct};

        inline auto src_shape_cl = to_clipped(src_shape_ct);
        inline auto window_shape_cl = to_clipped(window_shape_ct);
        inline auto axis_cl = to_clipped(axis_ct);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline int dst_shape[6] = {1,2,2,2,3,2};
    }
}

NMTOOLS_TESTING_DECLARE_CASE(index, sliding_window)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1a)
    {
        inline int indices[4] = {0,0,0,0};
        inline int dst_shape[4] = {3,2,2,2};
        inline int src_shape[2] = {3,4};
        inline int window_shape[2] = {2,2};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1a)
    {
        inline int expected[2] = {0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1b)
    {
        inline int indices[4] = {0,0,0,1};
        inline int dst_shape[4] = {3,2,2,2};
        inline int src_shape[2] = {3,4};
        inline int window_shape[2] = {2,2};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1b)
    {
        inline int expected[2] = {0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1c)
    {
        inline int indices[4] = {0,0,1,0};
        inline int dst_shape[4] = {3,2,2,2};
        inline int src_shape[2] = {3,4};
        inline int window_shape[2] = {2,2};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1c)
    {
        inline int expected[2] = {1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1d)
    {
        inline int indices[4] = {0,0,1,1};
        inline int dst_shape[4] = {3,2,2,2};
        inline int src_shape[2] = {3,4};
        inline int window_shape[2] = {2,2};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1d)
    {
        inline int expected[2] = {1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1e)
    {
        inline int indices[4] = {0,1,0,0};
        inline int dst_shape[4] = {3,2,2,2};
        inline int src_shape[2] = {3,4};
        inline int window_shape[2] = {2,2};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1e)
    {
        inline int expected[2] = {0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1f)
    {
        inline int indices[4] = {0,1,0,1};
        inline int dst_shape[4] = {3,2,2,2};
        inline int src_shape[2] = {3,4};
        inline int window_shape[2] = {2,2};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1f)
    {
        inline int expected[2] = {0,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1g)
    {
        inline int indices[4] = {0,1,1,1};
        inline int dst_shape[4] = {3,2,2,2};
        inline int src_shape[2] = {3,4};
        inline int window_shape[2] = {2,2};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1g)
    {
        inline int expected[2] = {1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1h)
    {
        inline int indices[4] = {1,0,0,0};
        inline int dst_shape[4] = {3,2,2,2};
        inline int src_shape[2] = {3,4};
        inline int window_shape[2] = {2,2};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1h)
    {
        inline int expected[2] = {1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1i)
    {
        inline int indices[4] = {1,0,0,1};
        inline int dst_shape[4] = {3,2,2,2};
        inline int src_shape[2] = {3,4};
        inline int window_shape[2] = {2,2};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1i)
    {
        inline int expected[2] = {1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1j)
    {
        inline int indices[4] = {1,0,1,0};
        inline int dst_shape[4] = {3,2,2,2};
        inline int src_shape[2] = {3,4};
        inline int window_shape[2] = {2,2};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1j)
    {
        inline int expected[2] = {2,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1k)
    {
        inline int indices[4] = {1,0,1,1};
        inline int dst_shape[4] = {3,2,2,2};
        inline int src_shape[2] = {3,4};
        inline int window_shape[2] = {2,2};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1k)
    {
        inline int expected[2] = {2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1l)
    {
        inline int indices[4] = {1,1,0,0};
        inline int dst_shape[4] = {3,2,2,2};
        inline int src_shape[2] = {3,4};
        inline int window_shape[2] = {2,2};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1l)
    {
        inline int expected[2] = {1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1m)
    {
        inline int indices[4] = {1,1,0,1};
        inline int dst_shape[4] = {3,2,2,2};
        inline int src_shape[2] = {3,4};
        inline int window_shape[2] = {2,2};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1m)
    {
        inline int expected[2] = {1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1n)
    {
        inline int indices[4] = {1,1,1,0};
        inline int dst_shape[4] = {3,2,2,2};
        inline int src_shape[2] = {3,4};
        inline int window_shape[2] = {2,2};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1n)
    {
        inline int expected[2] = {2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1o)
    {
        inline int indices[4] = {1,1,1,1};
        inline int dst_shape[4] = {3,2,2,2};
        inline int src_shape[2] = {3,4};
        inline int window_shape[2] = {2,2};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1o)
    {
        inline int expected[2] = {2,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1p)
    {
        inline int indices[4] = {2,0,0,0};
        inline int dst_shape[4] = {3,2,2,2};
        inline int src_shape[2] = {3,4};
        inline int window_shape[2] = {2,2};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1p)
    {
        inline int expected[2] = {2,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1q)
    {
        inline int indices[4] = {2,0,0,1};
        inline int dst_shape[4] = {3,2,2,2};
        inline int src_shape[2] = {3,4};
        inline int window_shape[2] = {2,2};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1q)
    {
        inline int expected[2] = {2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1r)
    {
        inline int indices[4] = {2,0,1,0};
        inline int dst_shape[4] = {3,2,2,2};
        inline int src_shape[2] = {3,4};
        inline int window_shape[2] = {2,2};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1r)
    {
        inline int expected[2] = {3,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1s)
    {
        inline int indices[4] = {2,0,1,1};
        inline int dst_shape[4] = {3,2,2,2};
        inline int src_shape[2] = {3,4};
        inline int window_shape[2] = {2,2};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1s)
    {
        inline int expected[2] = {3,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1t)
    {
        inline int indices[4] = {2,1,0,0};
        inline int dst_shape[4] = {3,2,2,2};
        inline int src_shape[2] = {3,4};
        inline int window_shape[2] = {2,2};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1t)
    {
        inline int expected[2] = {2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1u)
    {
        inline int indices[4] = {2,1,0,1};
        inline int dst_shape[4] = {3,2,2,2};
        inline int src_shape[2] = {3,4};
        inline int window_shape[2] = {2,2};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1u)
    {
        inline int expected[2] = {2,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1v)
    {
        inline int indices[4] = {2,1,1,0};
        inline int dst_shape[4] = {3,2,2,2};
        inline int src_shape[2] = {3,4};
        inline int window_shape[2] = {2,2};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1v)
    {
        inline int expected[2] = {3,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1w)
    {
        inline int indices[4] = {2,1,1,1};
        inline int dst_shape[4] = {3,2,2,2};
        inline int src_shape[2] = {3,4};
        inline int window_shape[2] = {2,2};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1w)
    {
        inline int expected[2] = {3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2a)
    {
        inline int indices[2] = {0,0};
        inline int dst_shape[2] = {4,3};
        inline int src_shape[1] = {6};
        inline int window_shape = 3;
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2a)
    {
        inline int expected[1] = {0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2b)
    {
        inline int indices[2] = {0,1};
        inline int dst_shape[2] = {4,3};
        inline int src_shape[1] = {6};
        inline int window_shape = 3;
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2b)
    {
        inline int expected[1] = {1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2c)
    {
        inline int indices[2] = {0,2};
        inline int dst_shape[2] = {4,3};
        inline int src_shape[1] = {6};
        inline int window_shape = 3;
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2c)
    {
        inline int expected[1] = {2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2d)
    {
        inline int indices[2] = {1,0};
        inline int dst_shape[2] = {4,3};
        inline int src_shape[1] = {6};
        inline int window_shape = 3;
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2d)
    {
        inline int expected[1] = {1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2e)
    {
        inline int indices[2] = {1,1};
        inline int dst_shape[2] = {4,3};
        inline int src_shape[1] = {6};
        inline int window_shape = 3;
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2e)
    {
        inline int expected[1] = {2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2f)
    {
        inline int indices[2] = {1,2};
        inline int dst_shape[2] = {4,3};
        inline int src_shape[1] = {6};
        inline int window_shape = 3;
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2f)
    {
        inline int expected[1] = {3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2g)
    {
        inline int indices[2] = {2,0};
        inline int dst_shape[2] = {4,3};
        inline int src_shape[1] = {6};
        inline int window_shape = 3;
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2g)
    {
        inline int expected[1] = {2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2h)
    {
        inline int indices[2] = {2,1};
        inline int dst_shape[2] = {4,3};
        inline int src_shape[1] = {6};
        inline int window_shape = 3;
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2h)
    {
        inline int expected[1] = {3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2i)
    {
        inline int indices[2] = {2,2};
        inline int dst_shape[2] = {4,3};
        inline int src_shape[1] = {6};
        inline int window_shape = 3;
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2i)
    {
        inline int expected[1] = {4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2j)
    {
        inline int indices[2] = {3,0};
        inline int dst_shape[2] = {4,3};
        inline int src_shape[1] = {6};
        inline int window_shape = 3;
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2j)
    {
        inline int expected[1] = {3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2k)
    {
        inline int indices[2] = {3,1};
        inline int dst_shape[2] = {4,3};
        inline int src_shape[1] = {6};
        inline int window_shape = 3;
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2k)
    {
        inline int expected[1] = {4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2l)
    {
        inline int indices[2] = {3,2};
        inline int dst_shape[2] = {4,3};
        inline int src_shape[1] = {6};
        inline int window_shape = 3;
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2l)
    {
        inline int expected[1] = {5};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3a)
    {
        inline int indices[4] = {0,0,0,0};
        inline int dst_shape[4] = {3,1,2,3};
        inline int src_shape[2] = {3,4};
        inline int window_shape[2] = {2,3};
        inline int axis[2] = {1,1};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3a)
    {
        inline int expected[2] = {0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3b)
    {
        inline int indices[4] = {0,0,0,1};
        inline int dst_shape[4] = {3,1,2,3};
        inline int src_shape[2] = {3,4};
        inline int window_shape[2] = {2,3};
        inline int axis[2] = {1,1};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3b)
    {
        inline int expected[2] = {0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3c)
    {
        inline int indices[4] = {0,0,0,2};
        inline int dst_shape[4] = {3,1,2,3};
        inline int src_shape[2] = {3,4};
        inline int window_shape[2] = {2,3};
        inline int axis[2] = {1,1};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3c)
    {
        inline int expected[2] = {0,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3d)
    {
        inline int indices[4] = {0,0,1,0};
        inline int dst_shape[4] = {3,1,2,3};
        inline int src_shape[2] = {3,4};
        inline int window_shape[2] = {2,3};
        inline int axis[2] = {1,1};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3d)
    {
        inline int expected[2] = {0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3e)
    {
        inline int indices[4] = {0,0,1,1};
        inline int dst_shape[4] = {3,1,2,3};
        inline int src_shape[2] = {3,4};
        inline int window_shape[2] = {2,3};
        inline int axis[2] = {1,1};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3e)
    {
        inline int expected[2] = {0,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3f)
    {
        inline int indices[4] = {0,0,1,2};
        inline int dst_shape[4] = {3,1,2,3};
        inline int src_shape[2] = {3,4};
        inline int window_shape[2] = {2,3};
        inline int axis[2] = {1,1};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3f)
    {
        inline int expected[2] = {0,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3g)
    {
        inline int indices[4] = {1,0,0,0};
        inline int dst_shape[4] = {3,1,2,3};
        inline int src_shape[2] = {3,4};
        inline int window_shape[2] = {2,3};
        inline int axis[2] = {1,1};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3g)
    {
        inline int expected[2] = {1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3h)
    {
        inline int indices[4] = {1,0,0,1};
        inline int dst_shape[4] = {3,1,2,3};
        inline int src_shape[2] = {3,4};
        inline int window_shape[2] = {2,3};
        inline int axis[2] = {1,1};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3h)
    {
        inline int expected[2] = {1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3i)
    {
        inline int indices[4] = {1,0,0,2};
        inline int dst_shape[4] = {3,1,2,3};
        inline int src_shape[2] = {3,4};
        inline int window_shape[2] = {2,3};
        inline int axis[2] = {1,1};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3i)
    {
        inline int expected[2] = {1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3j)
    {
        inline int indices[4] = {1,0,1,0};
        inline int dst_shape[4] = {3,1,2,3};
        inline int src_shape[2] = {3,4};
        inline int window_shape[2] = {2,3};
        inline int axis[2] = {1,1};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3j)
    {
        inline int expected[2] = {1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3k)
    {
        inline int indices[4] = {1,0,1,1};
        inline int dst_shape[4] = {3,1,2,3};
        inline int src_shape[2] = {3,4};
        inline int window_shape[2] = {2,3};
        inline int axis[2] = {1,1};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3k)
    {
        inline int expected[2] = {1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3l)
    {
        inline int indices[4] = {1,0,1,2};
        inline int dst_shape[4] = {3,1,2,3};
        inline int src_shape[2] = {3,4};
        inline int window_shape[2] = {2,3};
        inline int axis[2] = {1,1};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3l)
    {
        inline int expected[2] = {1,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3m)
    {
        inline int indices[4] = {2,0,0,0};
        inline int dst_shape[4] = {3,1,2,3};
        inline int src_shape[2] = {3,4};
        inline int window_shape[2] = {2,3};
        inline int axis[2] = {1,1};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3m)
    {
        inline int expected[2] = {2,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3n)
    {
        inline int indices[4] = {2,0,0,1};
        inline int dst_shape[4] = {3,1,2,3};
        inline int src_shape[2] = {3,4};
        inline int window_shape[2] = {2,3};
        inline int axis[2] = {1,1};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3n)
    {
        inline int expected[2] = {2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3o)
    {
        inline int indices[4] = {2,0,1,0};
        inline int dst_shape[4] = {3,1,2,3};
        inline int src_shape[2] = {3,4};
        inline int window_shape[2] = {2,3};
        inline int axis[2] = {1,1};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3o)
    {
        inline int expected[2] = {2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3p)
    {
        inline int indices[4] = {2,0,1,1};
        inline int dst_shape[4] = {3,1,2,3};
        inline int src_shape[2] = {3,4};
        inline int window_shape[2] = {2,3};
        inline int axis[2] = {1,1};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3p)
    {
        inline int expected[2] = {2,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3q)
    {
        inline int indices[4] = {2,0,1,2};
        inline int dst_shape[4] = {3,1,2,3};
        inline int src_shape[2] = {3,4};
        inline int window_shape[2] = {2,3};
        inline int axis[2] = {1,1};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3q)
    {
        inline int expected[2] = {2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4a)
    {
        inline int indices[3] = {0,0,0};
        inline int dst_shape[3] = {1,4,3};
        inline int src_shape[2] = {3,4};
        inline int window_shape = 3;
        inline int axis = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4a)
    {
        inline int expected[2] = {0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4b)
    {
        inline int indices[3] = {0,0,1};
        inline int dst_shape[3] = {1,4,3};
        inline int src_shape[2] = {3,4};
        inline int window_shape = 3;
        inline int axis = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4b)
    {
        inline int expected[2] = {1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4c)
    {
        inline int indices[3] = {0,0,2};
        inline int dst_shape[3] = {1,4,3};
        inline int src_shape[2] = {3,4};
        inline int window_shape = 3;
        inline int axis = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4c)
    {
        inline int expected[2] = {2,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4d)
    {
        inline int indices[3] = {0,1,0};
        inline int dst_shape[3] = {1,4,3};
        inline int src_shape[2] = {3,4};
        inline int window_shape = 3;
        inline int axis = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4d)
    {
        inline int expected[2] = {0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4e)
    {
        inline int indices[3] = {0,1,1};
        inline int dst_shape[3] = {1,4,3};
        inline int src_shape[2] = {3,4};
        inline int window_shape = 3;
        inline int axis = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4e)
    {
        inline int expected[2] = {1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4f)
    {
        inline int indices[3] = {0,1,2};
        inline int dst_shape[3] = {1,4,3};
        inline int src_shape[2] = {3,4};
        inline int window_shape = 3;
        inline int axis = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4f)
    {
        inline int expected[2] = {2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4g)
    {
        inline int indices[3] = {0,2,0};
        inline int dst_shape[3] = {1,4,3};
        inline int src_shape[2] = {3,4};
        inline int window_shape = 3;
        inline int axis = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4g)
    {
        inline int expected[2] = {0,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4h)
    {
        inline int indices[3] = {0,2,1};
        inline int dst_shape[3] = {1,4,3};
        inline int src_shape[2] = {3,4};
        inline int window_shape = 3;
        inline int axis = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4h)
    {
        inline int expected[2] = {1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4i)
    {
        inline int indices[3] = {0,2,2};
        inline int dst_shape[3] = {1,4,3};
        inline int src_shape[2] = {3,4};
        inline int window_shape = 3;
        inline int axis = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4i)
    {
        inline int expected[2] = {2,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4j)
    {
        inline int indices[3] = {0,3,0};
        inline int dst_shape[3] = {1,4,3};
        inline int src_shape[2] = {3,4};
        inline int window_shape = 3;
        inline int axis = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4j)
    {
        inline int expected[2] = {0,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4k)
    {
        inline int indices[3] = {0,3,1};
        inline int dst_shape[3] = {1,4,3};
        inline int src_shape[2] = {3,4};
        inline int window_shape = 3;
        inline int axis = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4k)
    {
        inline int expected[2] = {1,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4l)
    {
        inline int indices[3] = {0,3,2};
        inline int dst_shape[3] = {1,4,3};
        inline int src_shape[2] = {3,4};
        inline int window_shape = 3;
        inline int axis = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4l)
    {
        inline int expected[2] = {2,3};
    }
}

#endif // NMTOOLS_TESTING_DATA_INDEX_SLIDING_WINDOW_HPP