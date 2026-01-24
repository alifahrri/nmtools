#include "nmtools/tilekit/tilekit.hpp"
#include "nmtools/tilekit/vector.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/ndarray.hpp"

namespace nm = nmtools;
namespace tk = nmtools::tilekit;

using nmtools_tuple;
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
    auto src_shape  = nm::shape(a);
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

TEST_CASE("vector.compute_load_offset" * doctest::test_suite("tilekit"))
{
    auto tile_shape = tuple{2_ct,4_ct};
    auto src_shape  = tuple{4_ct,12_ct};
    const auto dtype = nm::float32;
    const auto bit_width = nm::ct_v<128>;
    {
        auto tile_ndoffset = tuple{0,0};
        auto tile_offset = 0;
        auto memory_offset = tk::vector::compute_load_offset(dtype,bit_width,tile_offset,tile_ndoffset,tile_shape,src_shape);
        NMTOOLS_ASSERT_EQUAL( memory_offset, 0 );
    }
    {
        auto tile_ndoffset = tuple{0,0};
        auto tile_offset = 1;
        auto memory_offset = tk::vector::compute_load_offset(dtype,bit_width,tile_offset,tile_ndoffset,tile_shape,src_shape);
        NMTOOLS_ASSERT_EQUAL( memory_offset, 12 );
    }
    {
        auto tile_ndoffset = tuple{0,4};
        auto tile_offset = 0;
        auto memory_offset = tk::vector::compute_load_offset(dtype,bit_width,tile_offset,tile_ndoffset,tile_shape,src_shape);
        NMTOOLS_ASSERT_EQUAL( memory_offset, 4 );
    }
    {
        auto tile_ndoffset = tuple{0,4};
        auto tile_offset = 1;
        auto memory_offset = tk::vector::compute_load_offset(dtype,bit_width,tile_offset,tile_ndoffset,tile_shape,src_shape);
        NMTOOLS_ASSERT_EQUAL( memory_offset, 16 );
    }
}

TEST_CASE("vector.compute_load_offset" * doctest::test_suite("tilekit"))
{
    auto tile_shape = tuple{1_ct,2_ct,4_ct};
    auto src_shape  = tuple{1_ct,4_ct,12_ct};
    const auto dtype = nm::float32;
    const auto bit_width = nm::ct_v<128>;
    {
        auto tile_ndoffset = tuple{0,0,0};
        auto tile_offset = 0;
        auto memory_offset = tk::vector::compute_load_offset(dtype,bit_width,tile_offset,tile_ndoffset,tile_shape,src_shape);
        NMTOOLS_ASSERT_EQUAL( memory_offset, 0 );
    }
    {
        auto tile_ndoffset = tuple{0,0,0};
        auto tile_offset = 1;
        auto memory_offset = tk::vector::compute_load_offset(dtype,bit_width,tile_offset,tile_ndoffset,tile_shape,src_shape);
        NMTOOLS_ASSERT_EQUAL( memory_offset, 12 );
    }
    {
        auto tile_ndoffset = tuple{0,0,4};
        auto tile_offset = 0;
        auto memory_offset = tk::vector::compute_load_offset(dtype,bit_width,tile_offset,tile_ndoffset,tile_shape,src_shape);
        NMTOOLS_ASSERT_EQUAL( memory_offset, 4 );
    }
    {
        auto tile_ndoffset = tuple{0,0,4};
        auto tile_offset = 1;
        auto memory_offset = tk::vector::compute_load_offset(dtype,bit_width,tile_offset,tile_ndoffset,tile_shape,src_shape);
        NMTOOLS_ASSERT_EQUAL( memory_offset, 16 );
    }
}

TEST_CASE("vector.compute_load_offset" * doctest::test_suite("tilekit"))
{
    auto tile_shape = tuple{3_ct,8_ct};
    auto src_shape  = tuple{3_ct,16_ct};
    const auto dtype = nm::float32;
    const auto bit_width = nm::ct_v<128>;
    {
        auto tile_ndoffset = tuple{0,0};
        auto tile_offset   = 1;
        auto memory_offset = tk::vector::compute_load_offset(dtype,bit_width,tile_offset,tile_ndoffset,tile_shape,src_shape);
        NMTOOLS_ASSERT_EQUAL( memory_offset, 4 );
    }
    {
        auto tile_ndoffset = tuple{0,0};
        auto tile_offset   = 2;
        auto memory_offset = tk::vector::compute_load_offset(dtype,bit_width,tile_offset,tile_ndoffset,tile_shape,src_shape);
        NMTOOLS_ASSERT_EQUAL( memory_offset, 16 );
    }
    {
        auto tile_ndoffset = tuple{0,0};
        auto tile_offset   = 5;
        auto memory_offset = tk::vector::compute_load_offset(dtype,bit_width,tile_offset,tile_ndoffset,tile_shape,src_shape);
        NMTOOLS_ASSERT_EQUAL( memory_offset, 36 );
    }
    {
        auto tile_ndoffset = tuple{0,8};
        auto tile_offset   = 1;
        auto memory_offset = tk::vector::compute_load_offset(dtype,bit_width,tile_offset,tile_ndoffset,tile_shape,src_shape);
        NMTOOLS_ASSERT_EQUAL( memory_offset, 12 );
    }
}