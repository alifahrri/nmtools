#include "nmtools/tilekit/tilekit.hpp"
#include "nmtools/tilekit/vector.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/ndarray.hpp"

namespace nm = nmtools;
namespace tk = nmtools::tilekit;

using nmtools_tuple, nmtools_array;
using namespace nmtools::literals;

TEST_CASE("vector(case1)" * doctest::test_suite("tilekit"))
{
    int a[4][12] = {
        { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11},
        {12,13,14,15,16,17,18,19,20,21,22,23},
        {24,25,26,27,28,29,30,31,32,33,34,35},
        {36,37,38,39,40,41,42,43,44,45,46,47},
    };
    auto array = nm::array(a);
    auto tile_shape = tuple{2_ct,4_ct};
    auto src_shape  = nm::shape(array);
    {
        auto tile_ndoffset = tuple{0,0};
        auto src_strides = nm::index::compute_strides(src_shape);
        int expected[2] = {12,1};
        NMTOOLS_ASSERT_EQUAL( src_strides, expected );

        auto off = nm::index::compute_offset(tile_ndoffset,src_strides);
        NMTOOLS_ASSERT_EQUAL( off, 0 );
    }
    {
        auto tile_ndoffset = tuple{0,0};
        auto block_a = tk::vector::load(array,tile_ndoffset,tile_shape);
        int expected[2][4] = {
            { 0, 1, 2, 3},
            {12,13,14,15},
        };
        NMTOOLS_ASSERT_EQUAL( block_a, expected );
    }
    {
        auto tile_ndoffset = tuple{0,4};
        auto block_a = tk::vector::load(array,tile_ndoffset,tile_shape);
        int expected[2][4] = {
            { 4, 5, 6, 7},
            {16,17,18,19},
        };
        NMTOOLS_ASSERT_EQUAL( block_a, expected );
    }
}

TEST_CASE("vector(case2)" * doctest::test_suite("tilekit"))
{
    int a[4][14] = {
        { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13},
        {14,15,16,17,18,19,20,21,22,23,24,25,26,27},
        {28,29,30,31,32,33,34,35,36,37,38,39,40,41},
        {42,43,44,45,46,47,48,49,50,51,52,53,54,55},
    };
    auto array      = nm::array(a);
    auto tile_shape = tuple{2_ct,4_ct};
    auto ctx        = tk::vector::Context;
    auto padding    = nm::True;
    {
        auto tile_ndoffset = tuple{0,0};
        auto block_a = tk::load(ctx,array,tile_ndoffset,tile_shape,padding);
        int expected[2][4] = {
            { 0, 1, 2, 3},
            {14,15,16,17},
        };
        NMTOOLS_ASSERT_EQUAL( block_a, expected );
    }
    {
        auto tile_ndoffset = tuple{2,12};
        auto block_a = tk::load(ctx,array,tile_ndoffset,tile_shape,padding);
        int expected[2][4] = {
            {40,41,0,0},
            {54,55,0,0},
        };
        NMTOOLS_ASSERT_EQUAL( block_a, expected );
    }
}

NMTOOLS_TESTING_DECLARE_CASE(vector, compute_src_indices)
{
    using namespace literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int tile_indices[3] = {0,0,0};
        inline int src_ndoffset[3] = {0,0,0};

        NMTOOLS_CAST_INDEX_ARRAYS(tile_indices)
        NMTOOLS_CAST_INDEX_ARRAYS(src_ndoffset)

        inline auto tile_indices_ct = nmtools_tuple{0_ct,0_ct,0_ct};
        inline auto src_ndoffset_ct = nmtools_tuple{0_ct,0_ct,0_ct};

        inline auto tile_indices_nl1 = nmtools_array{nullable_int(),nullable_int(),nullable_int(0)};
        inline auto src_ndoffset_nl1 = nmtools_array{nullable_int(),nullable_int(),nullable_int(0)};

        inline auto tile_indices_nl2 = nmtools_array{nullable_int(),nullable_int(0),nullable_int()};
        inline auto src_ndoffset_nl2 = nmtools_array{nullable_int(),nullable_int(0),nullable_int()};

        inline auto tile_indices_mx1 = nmtools_tuple{0,0,0_ct};
        inline auto src_ndoffset_mx1 = nmtools_tuple{0,0,0_ct};

        inline auto tile_indices_mx2 = nmtools_tuple{0,0_ct,0};
        inline auto src_ndoffset_mx2 = nmtools_tuple{0,0_ct,0};

        inline auto num_lane = 4_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int expected[3] = {0,0,0};
        inline auto expected_nl1 = nmtools_array{nullable_int(),nullable_int(),nullable_int(0)};
        inline auto expected_nl2 = nmtools_array{nullable_int(),nullable_int(0),nullable_int()};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int tile_indices[3] = {0,1,0};
        inline int src_ndoffset[3] = {0,2,0};

        NMTOOLS_CAST_INDEX_ARRAYS(tile_indices)
        NMTOOLS_CAST_INDEX_ARRAYS(src_ndoffset)

        inline auto tile_indices_ct = nmtools_tuple{0_ct,1_ct,0_ct};
        inline auto src_ndoffset_ct = nmtools_tuple{0_ct,2_ct,0_ct};

        inline auto tile_indices_nl1 = nmtools_array{nullable_int(),nullable_int(),nullable_int(0)};
        inline auto src_ndoffset_nl1 = nmtools_array{nullable_int(),nullable_int(),nullable_int(0)};

        inline auto tile_indices_nl2 = nmtools_array{nullable_int(),nullable_int(1),nullable_int()};
        inline auto src_ndoffset_nl2 = nmtools_array{nullable_int(),nullable_int(2),nullable_int()};

        inline auto tile_indices_mx1 = nmtools_tuple{0,1,0_ct};
        inline auto src_ndoffset_mx1 = nmtools_tuple{0,2,0_ct};

        inline auto tile_indices_mx2 = nmtools_tuple{0,1_ct,0};
        inline auto src_ndoffset_mx2 = nmtools_tuple{0,2_ct,0};

        inline auto num_lane = 4_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int expected[3] = {0,3,0};
        inline auto expected_nl1 = nmtools_array{nullable_int(),nullable_int(),nullable_int(0)};
        inline auto expected_nl2 = nmtools_array{nullable_int(),nullable_int(3),nullable_int()};
    }
}

#define COMPUTE_SRC_INDICES_EXPECTED_SUBCASE(case_name, expected, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(vector,compute_src_indices,case_name); \
    using namespace args; \
    auto result = nmtools::tilekit::vector::compute_src_indices(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::expected ); \
}

#define COMPUTE_SRC_INDICES_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(vector,compute_src_indices,case_name); \
    using namespace args; \
    auto result = nmtools::tilekit::vector::compute_src_indices(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::expected ); \
}

TEST_CASE("compute_src_indices(case1)" * doctest::test_suite("vector"))
{
    COMPUTE_SRC_INDICES_SUBCASE(case1, tile_indices, src_ndoffset, num_lane);
    COMPUTE_SRC_INDICES_SUBCASE(case1, tile_indices_a, src_ndoffset_a, num_lane);
    COMPUTE_SRC_INDICES_SUBCASE(case1, tile_indices_v, src_ndoffset_v, num_lane);
    COMPUTE_SRC_INDICES_SUBCASE(case1, tile_indices_f, src_ndoffset_f, num_lane);
    COMPUTE_SRC_INDICES_SUBCASE(case1, tile_indices_h, src_ndoffset_h, num_lane);

    COMPUTE_SRC_INDICES_EXPECTED_SUBCASE(case1, expected_nl1, tile_indices_nl1, src_ndoffset_nl1, num_lane);
    COMPUTE_SRC_INDICES_EXPECTED_SUBCASE(case1, expected_nl2, tile_indices_nl2, src_ndoffset_nl2, num_lane);

    COMPUTE_SRC_INDICES_SUBCASE(case1, tile_indices_mx1, src_ndoffset_mx1, num_lane);
    COMPUTE_SRC_INDICES_SUBCASE(case1, tile_indices_mx2, src_ndoffset_mx2, num_lane);

    COMPUTE_SRC_INDICES_SUBCASE(case1, tile_indices_ct, src_ndoffset_ct, num_lane);
}

TEST_CASE("compute_src_indices(case2)" * doctest::test_suite("vector"))
{
    COMPUTE_SRC_INDICES_SUBCASE(case2, tile_indices, src_ndoffset, num_lane);
    COMPUTE_SRC_INDICES_SUBCASE(case2, tile_indices_a, src_ndoffset_a, num_lane);
    COMPUTE_SRC_INDICES_SUBCASE(case2, tile_indices_v, src_ndoffset_v, num_lane);
    COMPUTE_SRC_INDICES_SUBCASE(case2, tile_indices_f, src_ndoffset_f, num_lane);
    COMPUTE_SRC_INDICES_SUBCASE(case2, tile_indices_h, src_ndoffset_h, num_lane);

    COMPUTE_SRC_INDICES_EXPECTED_SUBCASE(case2, expected_nl1, tile_indices_nl1, src_ndoffset_nl1, num_lane);
    COMPUTE_SRC_INDICES_EXPECTED_SUBCASE(case2, expected_nl2, tile_indices_nl2, src_ndoffset_nl2, num_lane);

    COMPUTE_SRC_INDICES_SUBCASE(case2, tile_indices_mx1, src_ndoffset_mx1, num_lane);
    COMPUTE_SRC_INDICES_SUBCASE(case2, tile_indices_mx2, src_ndoffset_mx2, num_lane);

    COMPUTE_SRC_INDICES_SUBCASE(case2, tile_indices_ct, src_ndoffset_ct, num_lane);
}

TEST_CASE("nditer(case1d)" * doctest::test_suite("tilekit"))
{
    int buffer[2][8] = {
        {0,1, 2, 3, 4, 5, 6, 7},
        {8,9,10,11,12,13,14,15},
    };
    auto inp = nm::array(buffer);
    auto out = nm::zeros(array{2}, nm::int32);

    auto out_shape  = array{2};
    auto inp_shape  = array{2,8};
    auto tile_shape = tuple{2_ct,4_ct};

    auto axis = nm::ct_v<-1>;

    auto src_nditer = tk::nditer(inp_shape,tile_shape);
    auto inp_nditer = tk::moveaxis(
        src_nditer
        , axis
        , nm::ct_v<1>
    );

    auto axis_0_iter = tk::iter_shape(inp_nditer,0);
    auto axis_1_iter = tk::iter_shape(inp_nditer,1);

    NMTOOLS_ASSERT_EQUAL( src_nditer.shape(), (array{1,2,2}) );
    NMTOOLS_ASSERT_EQUAL( inp_nditer.shape(), (array{1,2,2}) );
    NMTOOLS_ASSERT_EQUAL( axis_0_iter, 1 );
    NMTOOLS_ASSERT_EQUAL( axis_1_iter, 2 );

    auto ctx = tk::vector::Context;

    auto dtype = nm::int32;
    auto accumulator = nm::Array::zeros(tile_shape,dtype,ctx);
    {
        auto i = 0;
        auto j = 0;

        auto tile_offset = tk::packed_at(inp_nditer,i,j);
        NMTOOLS_ASSERT_EQUAL( tile_offset, (array{0,0}) );

        auto block = tk::load(ctx,inp,tile_offset,tile_shape);
        int expected[2][4] = {
            {0,1, 2, 3},
            {8,9,10,11},
        };
        NMTOOLS_ASSERT_EQUAL( block, expected );

        accumulator = accumulator + block;
        NMTOOLS_ASSERT_EQUAL( accumulator, expected );
    }

    {
        auto i = 0;
        auto j = 1;

        auto tile_offset = tk::packed_at(inp_nditer,i,j);
        NMTOOLS_ASSERT_EQUAL( tile_offset, (array{0,4}) );

        auto block = tk::load(ctx,inp,tile_offset,tile_shape);
        int expected[2][4] = {
            { 4, 5, 6, 7},
            {12,13,14,15},
        };
        NMTOOLS_ASSERT_EQUAL( block, expected );

        accumulator = accumulator + block;

        int expected2[2][4] = {
            { 4, 6, 8,10},
            {20,22,24,26},
        };
        NMTOOLS_ASSERT_EQUAL( accumulator, expected2 );
    }

    {
        auto i = 0;

        int expected[2] = {28,92};

        auto result = accumulator.sum(axis);
        NMTOOLS_ASSERT_EQUAL( result, expected );

        auto out_tile_shape = nm::shape(result);
        NMTOOLS_ASSERT_EQUAL( out_tile_shape, array{2} );

        auto out_nditer = tk::nditer(out_shape,out_tile_shape);
        NMTOOLS_ASSERT_EQUAL( out_nditer.shape(), (array{1,1}) );

        auto res_offset = tk::packed_at(out_nditer,i);
        NMTOOLS_ASSERT_EQUAL( res_offset, (array{0}) );

        tk::store(ctx,out,res_offset,result);
        NMTOOLS_ASSERT_EQUAL( out, expected );
    }
}