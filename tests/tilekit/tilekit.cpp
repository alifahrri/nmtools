#include "nmtools/tilekit/tilekit.hpp"
#include "nmtools/tilekit/scalar.hpp"
#include "nmtools/array/transpose.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace view = nm::view;
namespace tk = nmtools::tilekit;

using nmtools_tuple;
using nmtools_array;
using namespace nmtools::literals;

NMTOOLS_TESTING_DECLARE_CASE(tilekit, compute_block_shape)
{
    using namespace literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr inline int array_shape[2] = {4,12};
        constexpr inline int tile_shape[2] = {2,4};
        NMTOOLS_CAST_INDEX_ARRAYS(array_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(tile_shape)

        inline auto array_shape_ct = nmtools_tuple{4_ct,12_ct};
        inline auto tile_shape_ct  = nmtools_tuple{2_ct,4_ct};

        inline auto array_shape_mx1 = nmtools_tuple{4,12_ct};
        inline auto tile_shape_mx1  = nmtools_tuple{2,4_ct};

        inline auto array_shape_nl1 = nmtools_array{nullable_int(),nullable_int(12)};
        inline auto tile_shape_nl1  = nmtools_array{nullable_int(),nullable_int(4)};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline auto expected = nmtools_array{2,3};
        inline auto expected_nl1 = nmtools_array{nullable_int(),nullable_int(3)};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int array_shape[2] = {1024,1024};
        inline int tile_shape[2] = {2,4};
        NMTOOLS_CAST_INDEX_ARRAYS(array_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(tile_shape)

        inline auto array_shape_ct = nmtools_tuple{1024_ct,1024_ct};
        inline auto tile_shape_ct  = nmtools_tuple{2_ct,4_ct};

        inline auto array_shape_mx1 = nmtools_tuple{1024,1024_ct};
        inline auto tile_shape_mx1  = nmtools_tuple{2,4_ct};

        inline auto array_shape_mx2 = nmtools_tuple{1024_ct,1024};
        inline auto tile_shape_mx2  = nmtools_tuple{2_ct,4_ct};

        inline auto array_shape_nl1 = nmtools_array{nullable_int(),nullable_int(1024)};
        inline auto tile_shape_nl1  = nmtools_array{nullable_int(),nullable_int(4)};

        inline auto array_shape_nl2 = nmtools_array{nullable_int(1024),nullable_int()};
        inline auto tile_shape_nl2  = nmtools_array{nullable_int(2),nullable_int()};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline auto expected = nmtools_array{512,256};
        inline auto expected_nl1 = nmtools_array{nullable_int(),nullable_int(256)};
        inline auto expected_nl2 = nmtools_array{nullable_int(512),nullable_int()};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int array_shape[2] = {1024,1026};
        inline int tile_shape[2] = {2,4};
        inline auto padding = True;
        NMTOOLS_CAST_INDEX_ARRAYS(array_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(tile_shape)

        inline auto array_shape_ct = nmtools_tuple{1024_ct,1026_ct};
        inline auto tile_shape_ct  = nmtools_tuple{2_ct,4_ct};

        inline auto array_shape_mx1 = nmtools_tuple{1024,1026_ct};
        inline auto tile_shape_mx1  = nmtools_tuple{2,4_ct};

        inline auto array_shape_mx2 = nmtools_tuple{1024_ct,1026};
        inline auto tile_shape_mx2  = nmtools_tuple{2_ct,4_ct};

        inline auto array_shape_nl1 = nmtools_array{nullable_int(),nullable_int(1026)};
        inline auto tile_shape_nl1  = nmtools_array{nullable_int(),nullable_int(4)};

        inline auto array_shape_nl2 = nmtools_array{nullable_int(1024),nullable_int()};
        inline auto tile_shape_nl2  = nmtools_array{nullable_int(2),nullable_int()};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline auto expected = nmtools_array{512,257};
        inline auto expected_nl1 = nmtools_array{nullable_int(),nullable_int(257)};
        inline auto expected_nl2 = nmtools_array{nullable_int(512),nullable_int()};
    }
}

#define COMPUTE_BLOCK_SHAPE_EXPECTED_SUBCASE(case_name, expected, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(tilekit,compute_block_shape,case_name); \
    using namespace args; \
    auto result = nmtools::tilekit::compute_block_shape(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::expected ); \
}

#define COMPUTE_BLOCK_SHAPE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(tilekit,compute_block_shape,case_name); \
    using namespace args; \
    auto result = nmtools::tilekit::compute_block_shape(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::expected ); \
}

TEST_CASE("compute_block_shape(case1)" * doctest::test_suite("tilekit"))
{
    COMPUTE_BLOCK_SHAPE_SUBCASE(case1, array_shape_a, tile_shape_a);
    COMPUTE_BLOCK_SHAPE_SUBCASE(case1, array_shape_v, tile_shape_v);
    COMPUTE_BLOCK_SHAPE_SUBCASE(case1, array_shape_f, tile_shape_f);
    COMPUTE_BLOCK_SHAPE_SUBCASE(case1, array_shape_h, tile_shape_h);

    COMPUTE_BLOCK_SHAPE_SUBCASE(case1, array_shape_ct, tile_shape_ct);

    COMPUTE_BLOCK_SHAPE_SUBCASE(case1, array_shape_mx1, tile_shape_mx1);

    COMPUTE_BLOCK_SHAPE_EXPECTED_SUBCASE(case1, expected_nl1, array_shape_nl1, tile_shape_nl1);
}

TEST_CASE("compute_block_shape(case2)" * doctest::test_suite("tilekit"))
{
    COMPUTE_BLOCK_SHAPE_SUBCASE(case2, array_shape_a, tile_shape_a);
    COMPUTE_BLOCK_SHAPE_SUBCASE(case2, array_shape_v, tile_shape_v);
    COMPUTE_BLOCK_SHAPE_SUBCASE(case2, array_shape_f, tile_shape_f);
    COMPUTE_BLOCK_SHAPE_SUBCASE(case2, array_shape_h, tile_shape_h);

    COMPUTE_BLOCK_SHAPE_SUBCASE(case2, array_shape_ct, tile_shape_ct);

    COMPUTE_BLOCK_SHAPE_SUBCASE(case2, array_shape_mx1, tile_shape_mx1);
    COMPUTE_BLOCK_SHAPE_SUBCASE(case2, array_shape_mx2, tile_shape_mx2);

    COMPUTE_BLOCK_SHAPE_EXPECTED_SUBCASE(case2, expected_nl1, array_shape_nl1, tile_shape_nl1);
    COMPUTE_BLOCK_SHAPE_EXPECTED_SUBCASE(case2, expected_nl2, array_shape_nl2, tile_shape_nl2);
}

TEST_CASE("compute_block_shape(case3)" * doctest::test_suite("tilekit"))
{
    COMPUTE_BLOCK_SHAPE_SUBCASE(case3, array_shape_a, tile_shape_a, padding);
    COMPUTE_BLOCK_SHAPE_SUBCASE(case3, array_shape_v, tile_shape_v, padding);
    COMPUTE_BLOCK_SHAPE_SUBCASE(case3, array_shape_f, tile_shape_f, padding);
    COMPUTE_BLOCK_SHAPE_SUBCASE(case3, array_shape_h, tile_shape_h, padding);

    COMPUTE_BLOCK_SHAPE_SUBCASE(case3, array_shape_ct, tile_shape_ct, padding);

    COMPUTE_BLOCK_SHAPE_SUBCASE(case3, array_shape_mx1, tile_shape_mx1, padding);
    COMPUTE_BLOCK_SHAPE_SUBCASE(case3, array_shape_mx2, tile_shape_mx2, padding);

    COMPUTE_BLOCK_SHAPE_EXPECTED_SUBCASE(case3, expected_nl1, array_shape_nl1, tile_shape_nl1, padding);
    COMPUTE_BLOCK_SHAPE_EXPECTED_SUBCASE(case3, expected_nl2, array_shape_nl2, tile_shape_nl2, padding);
}

TEST_CASE("ndoffset(case1)" * doctest::test_suite("tilekit"))
{
    auto array_shape = tuple{4_ct,12_ct};
    auto tile_shape  = tuple{2_ct,4_ct};

    auto ndoffset = tk::ndoffset(array_shape,tile_shape);

    NMTOOLS_ASSERT_EQUAL( ndoffset.size(), 6_ct );
    NMTOOLS_ASSERT_EQUAL( ndoffset[0], (tuple{0,0}) );
    NMTOOLS_ASSERT_EQUAL( ndoffset[1], (tuple{0,4}) );
    NMTOOLS_ASSERT_EQUAL( ndoffset[2], (tuple{0,8}) );
    NMTOOLS_ASSERT_EQUAL( ndoffset[3], (tuple{2,0}) );
    NMTOOLS_ASSERT_EQUAL( ndoffset[4], (tuple{2,4}) );
    NMTOOLS_ASSERT_EQUAL( ndoffset[5], (tuple{2,8}) );
}

TEST_CASE("ndoffset(case2)" * doctest::test_suite("tilekit"))
{
    auto array_shape = tuple{2_ct,4_ct,4_ct};
    auto tile_shape  = tuple{2_ct,2_ct,4_ct};

    auto ndoffset = tk::ndoffset(array_shape,tile_shape);

    NMTOOLS_ASSERT_EQUAL( ndoffset.size(), 2 );
    NMTOOLS_ASSERT_EQUAL( ndoffset[0], (tuple{0,0,0}) );
    NMTOOLS_ASSERT_EQUAL( ndoffset[1], (tuple{0,2,0}) );
}

TEST_CASE("ndoffset(case3)" * doctest::test_suite("tilekit"))
{
    auto array_shape = tuple{1024_ct,1024_ct};
    auto tile_shape  = tuple{2_ct,4_ct};

    auto ndoffset = tk::ndoffset(array_shape,tile_shape);

    NMTOOLS_ASSERT_EQUAL( ndoffset.size(), 131072 );
    NMTOOLS_ASSERT_EQUAL( ndoffset[0], (tuple{0,0}) );
    NMTOOLS_ASSERT_EQUAL( ndoffset[1], (tuple{0,4}) );
    NMTOOLS_ASSERT_EQUAL( ndoffset[2], (tuple{0,8}) );
}

TEST_CASE("nditer(case1)" * doctest::test_suite("tilekit"))
{
    auto a_shape = array{4,8};
    auto t_shape = tuple{2_ct,4_ct};

    auto nditer = tk::nditer(a_shape, t_shape);

    NMTOOLS_ASSERT_EQUAL( nditer.iter_shape(), (array{2,2}) );
    NMTOOLS_ASSERT_EQUAL( (nditer(0,0)), (array{0,0}));
    NMTOOLS_ASSERT_EQUAL( (nditer(0,1)), (array{0,4}));
    NMTOOLS_ASSERT_EQUAL( (nditer(1,0)), (array{2,0}));
    NMTOOLS_ASSERT_EQUAL( (nditer(1,1)), (array{2,4}));

    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_ndarray, decltype(nditer) );

    NMTOOLS_ASSERT_EQUAL( nditer.shape(), (array{2,2,2}) );
    int expected[2][2][2] = {
        {
            {0,0},
            {0,4},
        },
        {
            {2,0},
            {2,4},
        },
    };
    NMTOOLS_ASSERT_EQUAL( nditer, expected );
}

TEST_CASE("nditer(case1b)" * doctest::test_suite("tilekit"))
{
    auto a_shape = array{4,8};
    auto t_shape = tuple{2_ct,4_ct};

    auto nditer = tk::nditer(a_shape, t_shape);
    auto result = view::transpose(nditer,array{1,0,2});

    NMTOOLS_ASSERT_EQUAL( nditer.shape(), (array{2,2,2}) );
    int expected[2][2][2] = {
        {
            {0,0},
            {2,0},
        },
        {
            {0,4},
            {2,4},
        },
    };
    NMTOOLS_ASSERT_EQUAL( result, expected );
}

TEST_CASE("nditer(case1b)" * doctest::test_suite("tilekit"))
{
    auto a_shape = array{4,8};
    auto t_shape = tuple{2_ct,4_ct};

    auto nditer = tk::nditer(a_shape, t_shape);
    auto result = tk::moveaxis(nditer,nm::ct_v<0>,nm::ct_v<1>);


    NMTOOLS_ASSERT_EQUAL( (tk::iter_shape(result,0)), 2 );
    NMTOOLS_ASSERT_EQUAL( (tk::iter_shape(result,1)), 2 );
    NMTOOLS_ASSERT_EQUAL( result.shape(), (array{2,2,2}) );

    int expected[2][2][2] = {
        {
            {0,0},
            {2,0},
        },
        {
            {0,4},
            {2,4},
        },
    };
    NMTOOLS_ASSERT_EQUAL( result, expected );

    static_assert( nm::fixed_dim_v<decltype(nditer)> == 3 );
    static_assert( nm::fixed_dim_v<decltype(result)> == 3 );

    NMTOOLS_ASSERT_EQUAL( (tk::packed_at(result,0,0)), (array{0,0}));
    NMTOOLS_ASSERT_EQUAL( (tk::packed_at(result,0,1)), (array{2,0}));
    NMTOOLS_ASSERT_EQUAL( (tk::packed_at(result,1,0)), (array{0,4}));
    NMTOOLS_ASSERT_EQUAL( (tk::packed_at(result,1,1)), (array{2,4}));

    auto out_tile_shape = tuple{8_ct};
    auto out_shape  = array{8};
    auto out_nditer = tk::nditer(out_shape,out_tile_shape);
    NMTOOLS_ASSERT_EQUAL( out_nditer.shape(), (array{1,1}) );

    NMTOOLS_ASSERT_EQUAL( (tk::packed_at(out_nditer,0)), (array{0}));
}

TEST_CASE("nditer(case1c)" * doctest::test_suite("tilekit"))
{
    int inp[2][8] = {
        {0,1, 2, 3, 4, 5, 6, 7},
        {8,9,10,11,12,13,14,15},
    };
    auto inp_shape  = array{2,8};
    auto tile_shape = tuple{2_ct,4_ct};

    auto axis = 0_ct;

    auto src_nditer = tk::nditer(inp_shape,tile_shape);
    auto inp_nditer = tk::moveaxis(
        src_nditer
        , axis
        , nm::ct_v<1>
    );

    auto axis_0_iter = tk::iter_shape(inp_nditer,0);
    auto axis_1_iter = tk::iter_shape(inp_nditer,1);

    NMTOOLS_ASSERT_EQUAL( src_nditer.shape(), (array{1,2,2}) );
    NMTOOLS_ASSERT_EQUAL( inp_nditer.shape(), (array{2,1,2}) );
    NMTOOLS_ASSERT_EQUAL( axis_0_iter, 2 );
    NMTOOLS_ASSERT_EQUAL( axis_1_iter, 1 );

    auto ctx = tk::Scalar;

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
    }

    {
        auto i = 1;
        auto j = 0;

        auto tile_offset = tk::packed_at(inp_nditer,i,j);
        NMTOOLS_ASSERT_EQUAL( tile_offset, (array{0,4}) );

        auto block = tk::load(ctx,inp,tile_offset,tile_shape);
        int expected[2][4] = {
            { 4, 5, 6, 7},
            {12,13,14,15},
        };
        NMTOOLS_ASSERT_EQUAL( block, expected );
    }
}

TEST_CASE("nditer(case2)" * doctest::test_suite("tilekit"))
{
    auto a_shape = array{4,12};
    auto t_shape = tuple{2_ct,4_ct};

    auto nditer = tk::nditer(a_shape, t_shape);

    NMTOOLS_ASSERT_EQUAL( nditer.iter_shape(), (array{2,3}) );
    NMTOOLS_ASSERT_EQUAL( nditer(0,0), (array{0,0}) );
    NMTOOLS_ASSERT_EQUAL( nditer(0,1), (array{0,4}) );
    NMTOOLS_ASSERT_EQUAL( nditer(0,2), (array{0,8}) );
    NMTOOLS_ASSERT_EQUAL( nditer(1,0), (array{2,0}) );
    NMTOOLS_ASSERT_EQUAL( nditer(1,1), (array{2,4}) );
    NMTOOLS_ASSERT_EQUAL( nditer(1,2), (array{2,8}) );

    NMTOOLS_ASSERT_EQUAL( nditer.shape(), (array{2,3,2}) );
    int expected[2][3][2] = {
        {
            {0,0},
            {0,4},
            {0,8},
        },
        {
            {2,0},
            {2,4},
            {2,8},
        },
    };
    NMTOOLS_ASSERT_EQUAL( nditer, expected );
}

TEST_CASE("load(case1)" * doctest::test_suite("tilekit"))
{
    int a[4][12] = {
        { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11},
        {12,13,14,15,16,17,18,19,20,21,22,23},
        {24,25,26,27,28,29,30,31,32,33,34,35},
        {36,37,38,39,40,41,42,43,44,45,46,47},
    };
    auto array = nm::array(a);
    auto tile_shape = tuple{2_ct,4_ct};
    auto ctx = nm::None;
    {
        auto tile_ndoffset = tuple{0,0};
        auto block_a = tk::load(ctx,array,tile_ndoffset,tile_shape);
        int expected[2][4] = {
            { 0, 1, 2, 3},
            {12,13,14,15},
        };
        NMTOOLS_ASSERT_EQUAL( block_a, expected );
    }
    {
        auto tile_ndoffset = tuple{0,4};
        auto block_a = tk::load(ctx,array,tile_ndoffset,tile_shape);
        int expected[2][4] = {
            { 4, 5, 6, 7},
            {16,17,18,19},
        };
        NMTOOLS_ASSERT_EQUAL( block_a, expected );
    }
}

TEST_CASE("load(case2)" * doctest::test_suite("tilekit"))
{
    int a[4][14] = {
        { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13},
        {14,15,16,17,18,19,20,21,22,23,24,25,26,27},
        {28,29,30,31,32,33,34,35,36,37,38,39,40,41},
        {42,43,44,45,46,47,48,49,50,51,52,53,54,55},
    };
    auto array      = nm::array(a);
    auto tile_shape = tuple{2_ct,4_ct};
    auto ctx        = tk::Scalar;
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

TEST_CASE("store(case2)" * doctest::test_suite("tilekit"))
{
    int a[4][14] = {
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    };
    auto array     = nm::array(a);
    auto ctx       = tk::Scalar;
    auto padding   = nm::True;
    constexpr auto tile_shape = tuple{2_ct,4_ct};
    {
        auto tile_ndoffset = tuple{0,0};
        auto store = tk::store_t<tk::scalar_t,nm::remove_cvref_t<decltype(array)>,nm::remove_cvref_t<decltype(padding)>>{};
        int block[2][4] = {
            { 0, 1, 2, 3},
            {14,15,16,17},
        };
        auto result = nm::array(block,tile_shape);
        store(ctx,array,tile_ndoffset,result,padding);

        int expected[4][14] = {
            { 0, 1, 2, 3,0,0,0,0,0,0,0,0,0,0},
            {14,15,16,17,0,0,0,0,0,0,0,0,0,0},
            { 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0},
            { 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0},
        };
        NMTOOLS_ASSERT_EQUAL( array, expected );
    }
    {
        auto tile_ndoffset = tuple{2,12};
        auto store = tk::store_t<tk::scalar_t,nm::remove_cvref_t<decltype(array)>,nm::remove_cvref_t<decltype(padding)>>{};
        int block[2][4] = {
            {40,41,0,0},
            {54,55,0,0},
        };
        auto result = nm::array(block,tile_shape);
        store(ctx,array,tile_ndoffset,result,padding);

        int expected[4][14] = {
            { 0, 1, 2, 3,0,0,0,0,0,0,0,0, 0, 0},
            {14,15,16,17,0,0,0,0,0,0,0,0, 0, 0},
            { 0, 0, 0, 0,0,0,0,0,0,0,0,0,40,41},
            { 0, 0, 0, 0,0,0,0,0,0,0,0,0,54,55},
        };
        NMTOOLS_ASSERT_EQUAL( array, expected );
    }
}