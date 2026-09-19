#ifndef NMTOOLS_TESTING_DATA_INDEX_COMPUTE_OFFSET_HPP
#define NMTOOLS_TESTING_DATA_INDEX_COMPUTE_OFFSET_HPP

#include "nmtools/testing/testing.hpp"

NMTOOLS_TESTING_DECLARE_CASE(index, compute_offset)
{
    using namespace nmtools::literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1a)
    {
        // note that this is strides not shape
        inline int strides[2] = {2,1};
        inline auto strides_ct = nmtools_tuple{2_ct,1_ct};
        inline auto strides_cl = nmtools_tuple{"2:[2]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(strides);

        inline int indices[2] = {0,0};
        inline auto indices_ct = nmtools_tuple{0_ct,0_ct};
        inline auto indices_cl = nmtools_tuple{"0:[1]"_ct,"0:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);

        // shape for the overloaded version that can handle nested shape
        inline int shape[2]   = {3,2};
        inline auto shape_ct  = nmtools_tuple{2_ct,1_ct};
        inline auto shape_nl1 = to_nullable(shape,0);
        inline auto shape_nl2 = to_nullable(shape,1);
        inline auto shape_mx1 = to_mixed(shape_ct,0_ct);
        inline auto shape_mx2 = to_mixed(shape_ct,1_ct);
        NMTOOLS_CAST_INDEX_ARRAYS(shape);

        inline auto strides_nl1 = to_nullable(strides,0);
        inline auto strides_nl2 = to_nullable(strides,1);

        inline auto indices_nl1 = to_nullable(indices,0);
        inline auto indices_nl2 = to_nullable(indices,1);

        inline auto strides_mx1 = to_mixed(strides_ct,0_ct);
        inline auto strides_mx2 = to_mixed(strides_ct,1_ct);

        inline auto indices_mx1 = to_mixed(indices_ct,0_ct);
        inline auto indices_mx2 = to_mixed(indices_ct,1_ct);

        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(strides);
        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1a)
    {
        inline int result = 0;
        inline auto result_nl1 = null_size_t();
        inline auto result_nl2 = null_size_t();
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1b)
    {
        inline int strides[2] = {2,1};
        inline auto strides_ct = nmtools_tuple{2_ct,1_ct};
        inline auto strides_cl = nmtools_tuple{"2:[2]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(strides);

        inline int indices[2] = {0,1};
        inline auto indices_ct = nmtools_tuple{0_ct,1_ct};
        inline auto indices_cl = nmtools_tuple{"0:[1]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);

        // shape for the overloaded version that can handle nested shape
        inline int shape[2]   = {3,2};
        inline auto shape_ct  = nmtools_tuple{3_ct,2_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);

        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(strides);
        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1b)
    {
        inline int result = 1;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1c)
    {
        inline int strides[2] = {2,1};
        inline auto strides_ct = nmtools_tuple{2_ct,1_ct};
        inline auto strides_cl = nmtools_tuple{"2:[2]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(strides);

        inline int indices[2] = {1,0};
        inline auto indices_ct = nmtools_tuple{1_ct,0_ct};
        inline auto indices_cl = nmtools_tuple{"1:[1]"_ct,"0:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);

        // shape for the overloaded version that can handle nested shape
        inline int shape[2]   = {3,2};
        inline auto shape_ct  = nmtools_tuple{3_ct,2_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);

        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(strides);
        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1c)
    {
        inline int result = 2;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1d)
    {
        inline int strides[2] = {2,1};
        inline auto strides_ct = nmtools_tuple{2_ct,1_ct};
        inline auto strides_cl = nmtools_tuple{"2:[2]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(strides);

        inline int indices[2] = {1,1};
        inline auto indices_ct = nmtools_tuple{1_ct,1_ct};
        inline auto indices_cl = nmtools_tuple{"1:[1]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);

        // shape for the overloaded version that can handle nested shape
        inline int shape[2]   = {3,2};
        inline auto shape_ct  = nmtools_tuple{3_ct,2_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);

        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(strides);
        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1d)
    {
        inline int result = 3;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1e)
    {
        inline int strides[2] = {2,1};
        inline auto strides_ct = nmtools_tuple{2_ct,1_ct};
        inline auto strides_cl = nmtools_tuple{"2:[2]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(strides);

        inline int indices[2] = {2,0};
        inline auto indices_ct = nmtools_tuple{2_ct,0_ct};
        inline auto indices_cl = nmtools_tuple{"2:[2]"_ct,"0:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);

        // shape for the overloaded version that can handle nested shape
        inline int shape[2]   = {3,2};
        inline auto shape_ct  = nmtools_tuple{3_ct,2_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);

        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(strides);
        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1e)
    {
        inline int result = 4;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1f)
    {
        inline int strides[2] = {2,1};
        inline auto strides_ct = nmtools_tuple{2_ct,1_ct};
        inline auto strides_cl = nmtools_tuple{"2:[2]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(strides);

        inline int indices[2] = {2,1};
        inline auto indices_ct = nmtools_tuple{2_ct,1_ct};
        inline auto indices_cl = nmtools_tuple{"2:[2]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);

        // shape for the overloaded version that can handle nested shape
        inline int shape[2]   = {3,2};
        inline auto shape_ct  = nmtools_tuple{3_ct,2_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);

        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(strides);
        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1f)
    {
        inline int result = 5;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2a)
    {
        inline int strides[3] = {6,3,1};
        inline auto strides_ct = nmtools_tuple{6_ct,3_ct,1_ct};
        inline auto strides_cl = nmtools_tuple{"6:[6]"_ct,"3:[3]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(strides);

        inline int indices[3] = {0,0,0};
        inline auto indices_ct = nmtools_tuple{0_ct,0_ct,0_ct};
        inline auto indices_cl = nmtools_tuple{"0:[1]"_ct,"0:[1]"_ct,"0:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);

        // shape for the overloaded version that can handle nested shape
        inline int shape[3]   = {1,2,3};
        inline auto shape_ct  = nmtools_tuple{1_ct,2_ct,3_ct};
        inline auto shape_nl1 = to_nullable(shape,0);
        inline auto shape_mx1 = to_mixed(shape_ct,0_ct);
        NMTOOLS_CAST_INDEX_ARRAYS(shape);

        inline auto strides_nl1 = nmtools_array{null_size_t(),null_size_t(3),null_size_t(1)};
        inline auto indices_nl1 = nmtools_array{null_size_t(),null_size_t(),null_size_t()};

        inline auto strides_mx1 = nmtools_tuple{6,3_ct,1_ct};
        inline auto indices_mx1 = nmtools_tuple{0,0_ct,0_ct};

        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(strides);
        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2a)
    {
        inline int result = 0;
        inline auto result_nl1 = null_size_t();
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2b)
    {
        inline int strides[3] = {6,3,1};
        inline auto strides_ct = nmtools_tuple{6_ct,3_ct,1_ct};
        inline auto strides_cl = nmtools_tuple{"6:[6]"_ct,"3:[3]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(strides);

        inline int indices[3] = {0,0,1};
        inline auto indices_ct = nmtools_tuple{0_ct,0_ct,1_ct};
        inline auto indices_cl = nmtools_tuple{"0:[1]"_ct,"0:[1]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);

        // shape for the overloaded version that can handle nested shape
        inline int shape[3]   = {1,2,3};
        inline auto shape_ct  = nmtools_tuple{1_ct,2_ct,3_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);

        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(strides);
        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2b)
    {
        inline int result = 1;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2c)
    {
        inline int strides[3] = {6,3,1};
        inline auto strides_ct = nmtools_tuple{6_ct,3_ct,1_ct};
        inline auto strides_cl = nmtools_tuple{"6:[6]"_ct,"3:[3]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(strides);

        inline int indices[3] = {0,0,2};
        inline auto indices_ct = nmtools_tuple{0_ct,0_ct,2_ct};
        inline auto indices_cl = nmtools_tuple{"0:[1]"_ct,"0:[1]"_ct,"2:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);

        // shape for the overloaded version that can handle nested shape
        inline int shape[3]   = {1,2,3};
        inline auto shape_ct  = nmtools_tuple{1_ct,2_ct,3_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);

        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(strides);
        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2c)
    {
        inline int result = 2;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2d)
    {
        inline int strides[3] = {6,3,1};
        inline auto strides_ct = nmtools_tuple{6_ct,3_ct,1_ct};
        inline auto strides_cl = nmtools_tuple{"6:[6]"_ct,"3:[3]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(strides);

        inline int indices[3] = {0,1,0};
        inline auto indices_ct = nmtools_tuple{0_ct,1_ct,0_ct};
        inline auto indices_cl = nmtools_tuple{"0:[1]"_ct,"1:[1]"_ct,"0:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);

        // shape for the overloaded version that can handle nested shape
        inline int shape[3]   = {1,2,3};
        inline auto shape_ct  = nmtools_tuple{1_ct,2_ct,3_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);

        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(strides);
        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2d)
    {
        inline int result = 3;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2e)
    {
        inline int strides[3] = {6,3,1};
        inline auto strides_ct = nmtools_tuple{6_ct,3_ct,1_ct};
        inline auto strides_cl = nmtools_tuple{"6:[6]"_ct,"3:[3]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(strides);

        inline int indices[3] = {0,1,1};
        inline auto indices_ct = nmtools_tuple{0_ct,1_ct,1_ct};
        inline auto indices_cl = nmtools_tuple{"0:[1]"_ct,"1:[1]"_ct,"1:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);

        // shape for the overloaded version that can handle nested shape
        inline int shape[3]   = {1,2,3};
        inline auto shape_ct  = nmtools_tuple{1_ct,2_ct,3_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);

        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(strides);
        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2e)
    {
        inline int result = 4;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2f)
    {
        inline int strides[3] = {6,3,1};
        inline auto strides_ct = nmtools_tuple{6_ct,3_ct,1_ct};
        inline auto strides_cl = nmtools_tuple{"6:[6]"_ct,"3:[3]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(strides);

        inline int indices[3] = {0,1,2};
        inline auto indices_ct = nmtools_tuple{0_ct,1_ct,2_ct};
        inline auto indices_cl = nmtools_tuple{"0:[1]"_ct,"1:[1]"_ct,"2:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);

        // shape for the overloaded version that can handle nested shape
        inline int shape[3]   = {1,2,3};
        inline auto shape_ct  = nmtools_tuple{1_ct,2_ct,3_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);

        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(strides);
        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2f)
    {
        inline int result = 5;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2g)
    {
        inline int strides[3] = {6,3,1};
        inline auto strides_ct = nmtools_tuple{6_ct,3_ct,1_ct};
        inline auto strides_cl = nmtools_tuple{"6:[6]"_ct,"3:[3]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(strides);

        inline int indices[3] = {1,0,0};
        inline auto indices_ct = nmtools_tuple{1_ct,0_ct,0_ct};
        inline auto indices_cl = nmtools_tuple{"1:[1]"_ct,"0:[1]"_ct,"0:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);

        // shape for the overloaded version that can handle nested shape
        inline int shape[3]   = {1,2,3};
        inline auto shape_ct  = nmtools_tuple{1_ct,2_ct,3_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);

        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(strides);
        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2g)
    {
        inline int result = 6;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2h)
    {
        inline int strides[3] = {6,3,1};
        inline auto strides_ct = nmtools_tuple{6_ct,3_ct,1_ct};
        inline auto strides_cl = nmtools_tuple{"6:[6]"_ct,"3:[3]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(strides);

        inline int indices[3] = {1,0,1};
        inline auto indices_ct = nmtools_tuple{1_ct,0_ct,1_ct};
        inline auto indices_cl = nmtools_tuple{"1:[1]"_ct,"0:[1]"_ct,"1:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);

        // shape for the overloaded version that can handle nested shape
        inline int shape[3]   = {1,2,3};
        inline auto shape_ct  = nmtools_tuple{1_ct,2_ct,3_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);

        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(strides);
        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2h)
    {
        inline int result = 7;
    }

    // col-major interleave from cute layout example
    // (4,(4,2)):(4,(1,16))
    // notice that cute essentially col major, so the inner (4,2) becomes {2,4} here, also the strides
    // nmtools use compute_indices aka unravel_index in numpy speak
    // the inner indices computation of cute is computed differently, resulting in col-major indices
    // nmtools keep the unravel_index/compute_indices for consistency
    // result:
    // int result[4][8] = {
    //     { 0, 1, 2, 3,16,17,18,19},
    //     { 4, 5, 6, 7,20,21,22,23},
    //     { 8, 9,10,11,24,25,26,27},
    //     {12,13,14,15,28,29,30,31},
    // };
    using nmtools_tuple, nmtools_array;

    NMTOOLS_TESTING_DECLARE_ARGS(case3a)
    {
        inline int indices[2] = {0,0};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);

        inline int inner_shape[2] = {2,4};
        NMTOOLS_CAST_INDEX_ARRAYS(inner_shape);

        inline int inner_strides[2] = {16,1};
        NMTOOLS_CAST_INDEX_ARRAYS(inner_strides);

        inline auto inner_shape_0 = 4;

        inline auto nested_shape_a = tuple{inner_shape_0,inner_shape_a};
        inline auto nested_shape_v = tuple{inner_shape_0,inner_shape_v};
        inline auto nested_shape_h = tuple{inner_shape_0,inner_shape_h};
        inline auto nested_shape_f = tuple{inner_shape_0,inner_shape_f};

        inline auto nested_strides_a = tuple{inner_shape_0,inner_strides_a};
        inline auto nested_strides_v = tuple{inner_shape_0,inner_strides_v};
        inline auto nested_strides_h = tuple{inner_shape_0,inner_strides_h};
        inline auto nested_strides_f = tuple{inner_shape_0,inner_strides_f};

        inline auto indices_ct = tuple{0_ct,0_ct};

        inline auto nested_shape_ct   = tuple{4_ct,tuple{2_ct,4_ct}};
        inline auto nested_strides_ct = tuple{4_ct,tuple{16_ct,1_ct}};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3a)
    {
        inline int result = 0;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3b)
    {
        inline int indices[2] = {0,1};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);

        inline int inner_shape[2] = {2,4};
        NMTOOLS_CAST_INDEX_ARRAYS(inner_shape);

        inline int inner_strides[2] = {16,1};
        NMTOOLS_CAST_INDEX_ARRAYS(inner_strides);

        inline auto inner_shape_0 = 4;

        inline auto nested_shape_a = tuple{inner_shape_0,inner_shape_a};
        inline auto nested_shape_v = tuple{inner_shape_0,inner_shape_v};
        inline auto nested_shape_h = tuple{inner_shape_0,inner_shape_h};
        inline auto nested_shape_f = tuple{inner_shape_0,inner_shape_f};

        inline auto nested_strides_a = tuple{inner_shape_0,inner_strides_a};
        inline auto nested_strides_v = tuple{inner_shape_0,inner_strides_v};
        inline auto nested_strides_h = tuple{inner_shape_0,inner_strides_h};
        inline auto nested_strides_f = tuple{inner_shape_0,inner_strides_f};

        inline auto indices_ct = tuple{0_ct,1_ct};

        inline auto nested_shape_ct   = tuple{4_ct,tuple{2_ct,4_ct}};
        inline auto nested_strides_ct = tuple{4_ct,tuple{16_ct,1_ct}};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3b)
    {
        inline int result = 1;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3c)
    {
        inline int indices[2] = {0,2};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);

        inline int inner_shape[2] = {2,4};
        NMTOOLS_CAST_INDEX_ARRAYS(inner_shape);

        inline int inner_strides[2] = {16,1};
        NMTOOLS_CAST_INDEX_ARRAYS(inner_strides);

        inline auto inner_shape_0 = 4;

        inline auto nested_shape_a = tuple{inner_shape_0,inner_shape_a};
        inline auto nested_shape_v = tuple{inner_shape_0,inner_shape_v};
        inline auto nested_shape_h = tuple{inner_shape_0,inner_shape_h};
        inline auto nested_shape_f = tuple{inner_shape_0,inner_shape_f};

        inline auto nested_strides_a = tuple{inner_shape_0,inner_strides_a};
        inline auto nested_strides_v = tuple{inner_shape_0,inner_strides_v};
        inline auto nested_strides_h = tuple{inner_shape_0,inner_strides_h};
        inline auto nested_strides_f = tuple{inner_shape_0,inner_strides_f};

        inline auto indices_ct = tuple{0_ct,2_ct};

        inline auto nested_shape_ct   = tuple{4_ct,tuple{2_ct,4_ct}};
        inline auto nested_strides_ct = tuple{4_ct,tuple{16_ct,1_ct}};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3c)
    {
        inline int result = 2;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3d)
    {
        inline int indices[2] = {0,5};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);

        inline int inner_shape[2] = {2,4};
        NMTOOLS_CAST_INDEX_ARRAYS(inner_shape);

        inline int inner_strides[2] = {16,1};
        NMTOOLS_CAST_INDEX_ARRAYS(inner_strides);

        inline auto inner_shape_0 = 4;

        inline auto nested_shape_a = tuple{inner_shape_0,inner_shape_a};
        inline auto nested_shape_v = tuple{inner_shape_0,inner_shape_v};
        inline auto nested_shape_h = tuple{inner_shape_0,inner_shape_h};
        inline auto nested_shape_f = tuple{inner_shape_0,inner_shape_f};

        inline auto nested_strides_a = tuple{inner_shape_0,inner_strides_a};
        inline auto nested_strides_v = tuple{inner_shape_0,inner_strides_v};
        inline auto nested_strides_h = tuple{inner_shape_0,inner_strides_h};
        inline auto nested_strides_f = tuple{inner_shape_0,inner_strides_f};

        inline auto indices_ct = tuple{0_ct,5_ct};

        inline auto nested_shape_ct   = tuple{4_ct,tuple{2_ct,4_ct}};
        inline auto nested_strides_ct = tuple{4_ct,tuple{16_ct,1_ct}};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3d)
    {
        inline int result = 17;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3e)
    {
        inline int indices[2] = {0,7};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);

        inline int inner_shape[2] = {2,4};
        NMTOOLS_CAST_INDEX_ARRAYS(inner_shape);

        inline int inner_strides[2] = {16,1};
        NMTOOLS_CAST_INDEX_ARRAYS(inner_strides);

        inline auto inner_shape_0 = 4;

        inline auto nested_shape_a = tuple{inner_shape_0,inner_shape_a};
        inline auto nested_shape_v = tuple{inner_shape_0,inner_shape_v};
        inline auto nested_shape_h = tuple{inner_shape_0,inner_shape_h};
        inline auto nested_shape_f = tuple{inner_shape_0,inner_shape_f};

        inline auto nested_strides_a = tuple{inner_shape_0,inner_strides_a};
        inline auto nested_strides_v = tuple{inner_shape_0,inner_strides_v};
        inline auto nested_strides_h = tuple{inner_shape_0,inner_strides_h};
        inline auto nested_strides_f = tuple{inner_shape_0,inner_strides_f};

        inline auto indices_ct = tuple{0_ct,7_ct};

        inline auto nested_shape_ct   = tuple{4_ct,tuple{2_ct,4_ct}};
        inline auto nested_strides_ct = tuple{4_ct,tuple{16_ct,1_ct}};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3e)
    {
        inline int result = 19;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3f)
    {
        inline int indices[2] = {1,0};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);

        inline int inner_shape[2] = {2,4};
        NMTOOLS_CAST_INDEX_ARRAYS(inner_shape);

        inline int inner_strides[2] = {16,1};
        NMTOOLS_CAST_INDEX_ARRAYS(inner_strides);

        inline auto inner_shape_0 = 4;

        inline auto nested_shape_a = tuple{inner_shape_0,inner_shape_a};
        inline auto nested_shape_v = tuple{inner_shape_0,inner_shape_v};
        inline auto nested_shape_h = tuple{inner_shape_0,inner_shape_h};
        inline auto nested_shape_f = tuple{inner_shape_0,inner_shape_f};

        inline auto nested_strides_a = tuple{inner_shape_0,inner_strides_a};
        inline auto nested_strides_v = tuple{inner_shape_0,inner_strides_v};
        inline auto nested_strides_h = tuple{inner_shape_0,inner_strides_h};
        inline auto nested_strides_f = tuple{inner_shape_0,inner_strides_f};

        inline auto indices_ct = tuple{1_ct,0_ct};

        inline auto nested_shape_ct   = tuple{4_ct,tuple{2_ct,4_ct}};
        inline auto nested_strides_ct = tuple{4_ct,tuple{16_ct,1_ct}};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3f)
    {
        inline int result = 4;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3g)
    {
        inline int indices[2] = {0,4};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);

        inline int inner_shape[2] = {2,4};
        NMTOOLS_CAST_INDEX_ARRAYS(inner_shape);

        inline int inner_strides[2] = {16,1};
        NMTOOLS_CAST_INDEX_ARRAYS(inner_strides);

        inline auto inner_shape_0 = 4;

        inline auto nested_shape_a = tuple{inner_shape_0,inner_shape_a};
        inline auto nested_shape_v = tuple{inner_shape_0,inner_shape_v};
        inline auto nested_shape_h = tuple{inner_shape_0,inner_shape_h};
        inline auto nested_shape_f = tuple{inner_shape_0,inner_shape_f};

        inline auto nested_strides_a = tuple{inner_shape_0,inner_strides_a};
        inline auto nested_strides_v = tuple{inner_shape_0,inner_strides_v};
        inline auto nested_strides_h = tuple{inner_shape_0,inner_strides_h};
        inline auto nested_strides_f = tuple{inner_shape_0,inner_strides_f};

        inline auto indices_ct = tuple{0_ct,4_ct};

        inline auto nested_shape_ct   = tuple{4_ct,tuple{2_ct,4_ct}};
        inline auto nested_strides_ct = tuple{4_ct,tuple{16_ct,1_ct}};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3g)
    {
        inline int result = 16;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3h)
    {
        inline int indices[2] = {1,4};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);

        inline int inner_shape[2] = {2,4};
        NMTOOLS_CAST_INDEX_ARRAYS(inner_shape);

        inline int inner_strides[2] = {16,1};
        NMTOOLS_CAST_INDEX_ARRAYS(inner_strides);

        inline auto inner_shape_0 = 4;

        inline auto nested_shape_a = tuple{inner_shape_0,inner_shape_a};
        inline auto nested_shape_v = tuple{inner_shape_0,inner_shape_v};
        inline auto nested_shape_h = tuple{inner_shape_0,inner_shape_h};
        inline auto nested_shape_f = tuple{inner_shape_0,inner_shape_f};

        inline auto nested_strides_a = tuple{inner_shape_0,inner_strides_a};
        inline auto nested_strides_v = tuple{inner_shape_0,inner_strides_v};
        inline auto nested_strides_h = tuple{inner_shape_0,inner_strides_h};
        inline auto nested_strides_f = tuple{inner_shape_0,inner_strides_f};

        inline auto indices_ct = tuple{1_ct,4_ct};

        inline auto nested_shape_ct   = tuple{4_ct,tuple{2_ct,4_ct}};
        inline auto nested_strides_ct = tuple{4_ct,tuple{16_ct,1_ct}};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3h)
    {
        inline int result = 20;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3i)
    {
        inline int indices[2] = {2,0};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);

        inline int inner_shape[2] = {2,4};
        NMTOOLS_CAST_INDEX_ARRAYS(inner_shape);

        inline int inner_strides[2] = {16,1};
        NMTOOLS_CAST_INDEX_ARRAYS(inner_strides);

        inline auto inner_shape_0 = 4;

        inline auto nested_shape_a = tuple{inner_shape_0,inner_shape_a};
        inline auto nested_shape_v = tuple{inner_shape_0,inner_shape_v};
        inline auto nested_shape_h = tuple{inner_shape_0,inner_shape_h};
        inline auto nested_shape_f = tuple{inner_shape_0,inner_shape_f};

        inline auto nested_strides_a = tuple{inner_shape_0,inner_strides_a};
        inline auto nested_strides_v = tuple{inner_shape_0,inner_strides_v};
        inline auto nested_strides_h = tuple{inner_shape_0,inner_strides_h};
        inline auto nested_strides_f = tuple{inner_shape_0,inner_strides_f};

        inline auto indices_ct = tuple{2_ct,0_ct};

        inline auto nested_shape_ct   = tuple{4_ct,tuple{2_ct,4_ct}};
        inline auto nested_strides_ct = tuple{4_ct,tuple{16_ct,1_ct}};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3i)
    {
        inline int result = 8;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3j)
    {
        inline int indices[2] = {2,4};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);

        inline int inner_shape[2] = {2,4};
        NMTOOLS_CAST_INDEX_ARRAYS(inner_shape);

        inline int inner_strides[2] = {16,1};
        NMTOOLS_CAST_INDEX_ARRAYS(inner_strides);

        inline auto inner_shape_0 = 4;

        inline auto nested_shape_a = tuple{inner_shape_0,inner_shape_a};
        inline auto nested_shape_v = tuple{inner_shape_0,inner_shape_v};
        inline auto nested_shape_h = tuple{inner_shape_0,inner_shape_h};
        inline auto nested_shape_f = tuple{inner_shape_0,inner_shape_f};

        inline auto nested_strides_a = tuple{inner_shape_0,inner_strides_a};
        inline auto nested_strides_v = tuple{inner_shape_0,inner_strides_v};
        inline auto nested_strides_h = tuple{inner_shape_0,inner_strides_h};
        inline auto nested_strides_f = tuple{inner_shape_0,inner_strides_f};

        inline auto indices_ct = tuple{2_ct,4_ct};

        inline auto nested_shape_ct   = tuple{4_ct,tuple{2_ct,4_ct}};
        inline auto nested_strides_ct = tuple{4_ct,tuple{16_ct,1_ct}};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3j)
    {
        inline int result = 24;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3k)
    {
        inline int indices[2] = {3,0};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);

        inline int inner_shape[2] = {2,4};
        NMTOOLS_CAST_INDEX_ARRAYS(inner_shape);

        inline int inner_strides[2] = {16,1};
        NMTOOLS_CAST_INDEX_ARRAYS(inner_strides);

        inline auto inner_shape_0 = 4;

        inline auto nested_shape_a = tuple{inner_shape_0,inner_shape_a};
        inline auto nested_shape_v = tuple{inner_shape_0,inner_shape_v};
        inline auto nested_shape_h = tuple{inner_shape_0,inner_shape_h};
        inline auto nested_shape_f = tuple{inner_shape_0,inner_shape_f};

        inline auto nested_strides_a = tuple{inner_shape_0,inner_strides_a};
        inline auto nested_strides_v = tuple{inner_shape_0,inner_strides_v};
        inline auto nested_strides_h = tuple{inner_shape_0,inner_strides_h};
        inline auto nested_strides_f = tuple{inner_shape_0,inner_strides_f};

        inline auto indices_ct = tuple{3_ct,0_ct};

        inline auto nested_shape_ct   = tuple{4_ct,tuple{2_ct,4_ct}};
        inline auto nested_strides_ct = tuple{4_ct,tuple{16_ct,1_ct}};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3k)
    {
        inline int result = 12;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3l)
    {
        inline int indices[2] = {3,4};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);

        inline int inner_shape[2] = {2,4};
        NMTOOLS_CAST_INDEX_ARRAYS(inner_shape);

        inline int inner_strides[2] = {16,1};
        NMTOOLS_CAST_INDEX_ARRAYS(inner_strides);

        inline auto inner_shape_0 = 4;

        inline auto nested_shape_a = tuple{inner_shape_0,inner_shape_a};
        inline auto nested_shape_v = tuple{inner_shape_0,inner_shape_v};
        inline auto nested_shape_h = tuple{inner_shape_0,inner_shape_h};
        inline auto nested_shape_f = tuple{inner_shape_0,inner_shape_f};

        inline auto nested_strides_a = tuple{inner_shape_0,inner_strides_a};
        inline auto nested_strides_v = tuple{inner_shape_0,inner_strides_v};
        inline auto nested_strides_h = tuple{inner_shape_0,inner_strides_h};
        inline auto nested_strides_f = tuple{inner_shape_0,inner_strides_f};

        inline auto indices_ct = tuple{3_ct,4_ct};

        inline auto nested_shape_ct   = tuple{4_ct,tuple{2_ct,4_ct}};
        inline auto nested_strides_ct = tuple{4_ct,tuple{16_ct,1_ct}};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3l)
    {
        inline int result = 28;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3m)
    {
        inline int indices[2] = {3,7};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);

        inline int inner_shape[2] = {2,4};
        NMTOOLS_CAST_INDEX_ARRAYS(inner_shape);

        inline int inner_strides[2] = {16,1};
        NMTOOLS_CAST_INDEX_ARRAYS(inner_strides);

        inline auto inner_shape_0 = 4;

        inline auto nested_shape_a = tuple{inner_shape_0,inner_shape_a};
        inline auto nested_shape_v = tuple{inner_shape_0,inner_shape_v};
        inline auto nested_shape_h = tuple{inner_shape_0,inner_shape_h};
        inline auto nested_shape_f = tuple{inner_shape_0,inner_shape_f};

        inline auto nested_strides_a = tuple{inner_shape_0,inner_strides_a};
        inline auto nested_strides_v = tuple{inner_shape_0,inner_strides_v};
        inline auto nested_strides_h = tuple{inner_shape_0,inner_strides_h};
        inline auto nested_strides_f = tuple{inner_shape_0,inner_strides_f};

        inline auto indices_ct = tuple{3_ct,7_ct};

        inline auto nested_shape_ct   = tuple{4_ct,tuple{2_ct,4_ct}};
        inline auto nested_strides_ct = tuple{4_ct,tuple{16_ct,1_ct}};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3m)
    {
        inline int result = 31;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3n)
    {
        inline int indices[2] = {1,7};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);

        inline int inner_shape[2] = {2,4};
        NMTOOLS_CAST_INDEX_ARRAYS(inner_shape);

        inline int inner_strides[2] = {16,1};
        NMTOOLS_CAST_INDEX_ARRAYS(inner_strides);

        inline auto inner_shape_0 = 4;

        inline auto nested_shape_a = tuple{inner_shape_0,inner_shape_a};
        inline auto nested_shape_v = tuple{inner_shape_0,inner_shape_v};
        inline auto nested_shape_h = tuple{inner_shape_0,inner_shape_h};
        inline auto nested_shape_f = tuple{inner_shape_0,inner_shape_f};

        inline auto nested_strides_a = tuple{inner_shape_0,inner_strides_a};
        inline auto nested_strides_v = tuple{inner_shape_0,inner_strides_v};
        inline auto nested_strides_h = tuple{inner_shape_0,inner_strides_h};
        inline auto nested_strides_f = tuple{inner_shape_0,inner_strides_f};

        inline auto indices_ct = tuple{1_ct,7_ct};

        inline auto nested_shape_ct   = tuple{4_ct,tuple{2_ct,4_ct}};
        inline auto nested_strides_ct = tuple{4_ct,tuple{16_ct,1_ct}};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3n)
    {
        inline int result = 23;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3o)
    {
        inline int indices[2] = {2,2};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);

        inline int inner_shape[2] = {2,4};
        NMTOOLS_CAST_INDEX_ARRAYS(inner_shape);

        inline int inner_strides[2] = {16,1};
        NMTOOLS_CAST_INDEX_ARRAYS(inner_strides);

        inline auto inner_shape_0 = 4;

        inline auto nested_shape_a = tuple{inner_shape_0,inner_shape_a};
        inline auto nested_shape_v = tuple{inner_shape_0,inner_shape_v};
        inline auto nested_shape_h = tuple{inner_shape_0,inner_shape_h};
        inline auto nested_shape_f = tuple{inner_shape_0,inner_shape_f};

        inline auto nested_strides_a = tuple{inner_shape_0,inner_strides_a};
        inline auto nested_strides_v = tuple{inner_shape_0,inner_strides_v};
        inline auto nested_strides_h = tuple{inner_shape_0,inner_strides_h};
        inline auto nested_strides_f = tuple{inner_shape_0,inner_strides_f};

        inline auto indices_ct = tuple{2_ct,2_ct};

        inline auto nested_shape_ct   = tuple{4_ct,tuple{2_ct,4_ct}};
        inline auto nested_strides_ct = tuple{4_ct,tuple{16_ct,1_ct}};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3o)
    {
        inline int result = 10;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3p)
    {
        inline int indices[2] = {1,2};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);

        inline int inner_shape[2] = {2,4};
        NMTOOLS_CAST_INDEX_ARRAYS(inner_shape);

        inline int inner_strides[2] = {16,1};
        NMTOOLS_CAST_INDEX_ARRAYS(inner_strides);

        inline auto inner_shape_0 = 4;

        inline auto nested_shape_a = tuple{inner_shape_0,inner_shape_a};
        inline auto nested_shape_v = tuple{inner_shape_0,inner_shape_v};
        inline auto nested_shape_h = tuple{inner_shape_0,inner_shape_h};
        inline auto nested_shape_f = tuple{inner_shape_0,inner_shape_f};

        inline auto nested_strides_a = tuple{inner_shape_0,inner_strides_a};
        inline auto nested_strides_v = tuple{inner_shape_0,inner_strides_v};
        inline auto nested_strides_h = tuple{inner_shape_0,inner_strides_h};
        inline auto nested_strides_f = tuple{inner_shape_0,inner_strides_f};

        inline auto indices_ct = tuple{1_ct,2_ct};

        inline auto nested_shape_ct   = tuple{4_ct,tuple{2_ct,4_ct}};
        inline auto nested_strides_ct = tuple{4_ct,tuple{16_ct,1_ct}};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3p)
    {
        inline int result = 6;
    }

    // swizzled column major, using f2
    NMTOOLS_TESTING_DECLARE_ARGS(case4a)
    {
        inline int indices[2] = {0,0};
        inline auto indices_ct = tuple{0_ct,0_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);

        inline int shape[2] = {8,8};
        inline auto shape_ct = tuple{8_ct,8_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);

        inline f2<int> striding[2] = {f2(1),f2(9)};
        inline auto striding_ct = tuple{f2(1_ct),f2(9_ct)};
        NMTOOLS_CAST_INDEX_ARRAYS(striding);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4a)
    {
        inline int result = 0;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4b)
    {
        inline int indices[2] = {0,1};
        inline auto indices_ct = tuple{0_ct,1_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);

        inline int shape[2] = {8,8};
        inline auto shape_ct = tuple{8_ct,8_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);

        inline f2<int> striding[2] = {f2(1),f2(9)};
        inline auto striding_ct = tuple{f2(1_ct),f2(9_ct)};
        NMTOOLS_CAST_INDEX_ARRAYS(striding);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4b)
    {
        inline int result = 9;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4c)
    {
        inline int indices[2] = {0,2};
        inline auto indices_ct = tuple{0_ct,2_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);

        inline int shape[2] = {8,8};
        inline auto shape_ct = tuple{8_ct,8_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);

        inline f2<int> striding[2] = {f2(1),f2(9)};
        inline auto striding_ct = tuple{f2(1_ct),f2(9_ct)};
        NMTOOLS_CAST_INDEX_ARRAYS(striding);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4c)
    {
        inline int result = 18;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4d)
    {
        inline int indices[2] = {1,0};
        inline auto indices_ct = tuple{1_ct,0_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);

        inline int shape[2] = {8,8};
        inline auto shape_ct = tuple{8_ct,8_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);

        inline f2<int> striding[2] = {f2(1),f2(9)};
        inline auto striding_ct = tuple{f2(1_ct),f2(9_ct)};
        NMTOOLS_CAST_INDEX_ARRAYS(striding);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4d)
    {
        inline int result = 1;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4e)
    {
        inline int indices[2] = {1,1};
        inline auto indices_ct = tuple{1_ct,1_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);

        inline int shape[2] = {8,8};
        inline auto shape_ct = tuple{8_ct,8_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);

        inline f2<int> striding[2] = {f2(1),f2(9)};
        inline auto striding_ct = tuple{f2(1_ct),f2(9_ct)};
        NMTOOLS_CAST_INDEX_ARRAYS(striding);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4e)
    {
        inline int result = 8;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4f)
    {
        inline int indices[2] = {1,2};
        inline auto indices_ct = tuple{1_ct,2_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);

        inline int shape[2] = {8,8};
        inline auto shape_ct = tuple{8_ct,8_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);

        inline f2<int> striding[2] = {f2(1),f2(9)};
        inline auto striding_ct = tuple{f2(1_ct),f2(9_ct)};
        NMTOOLS_CAST_INDEX_ARRAYS(striding);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4f)
    {
        inline int result = 19;
    }
}

#endif // NMTOOLS_TESTING_DATA_INDEX_COMPUTE_OFFSET_HPP