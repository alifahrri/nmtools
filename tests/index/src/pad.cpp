#include "nmtools/index/pad.hpp"
#include "nmtools/array/pad.hpp"
#include "nmtools/testing/data/index/pad.hpp"
#include "nmtools/testing/doctest.hpp"

#define SHAPE_PAD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index, shape_pad, case_name); \
    using namespace args; \
    auto result = nmtools::index::shape_pad(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

#define PARSE_PAD_WIDTH_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index, parse_pad_width, case_name); \
    using namespace args; \
    auto result = nmtools::index::parse_pad_width(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::pads ); \
}

TEST_CASE("parse_pad_width(case1)" * doctest::test_suite("index::parse_pad_width"))
{
    PARSE_PAD_WIDTH_SUBCASE( case1, pad_width );
    PARSE_PAD_WIDTH_SUBCASE( case1, pad_width_a );
    PARSE_PAD_WIDTH_SUBCASE( case1, pad_width_f );
    PARSE_PAD_WIDTH_SUBCASE( case1, pad_width_h );
    PARSE_PAD_WIDTH_SUBCASE( case1, pad_width_d );
}

TEST_CASE("parse_pad_width(case2)" * doctest::test_suite("index::parse_pad_width"))
{
    PARSE_PAD_WIDTH_SUBCASE( case2, pad_width );
    PARSE_PAD_WIDTH_SUBCASE( case2, pad_width_a );
    PARSE_PAD_WIDTH_SUBCASE( case2, pad_width_f );
    PARSE_PAD_WIDTH_SUBCASE( case2, pad_width_h );
    PARSE_PAD_WIDTH_SUBCASE( case2, pad_width_d );
}

TEST_CASE("parse_pad_width(case3)" * doctest::test_suite("index::parse_pad_width"))
{
    PARSE_PAD_WIDTH_SUBCASE( case3, pad_width );
    PARSE_PAD_WIDTH_SUBCASE( case3, pad_width_a );
    PARSE_PAD_WIDTH_SUBCASE( case3, pad_width_f );
    PARSE_PAD_WIDTH_SUBCASE( case3, pad_width_h );
    PARSE_PAD_WIDTH_SUBCASE( case3, pad_width_d );
}

TEST_CASE("parse_pad_width(case4)" * doctest::test_suite("index::parse_pad_width"))
{
    PARSE_PAD_WIDTH_SUBCASE( case4, pad_width );
    PARSE_PAD_WIDTH_SUBCASE( case4, pad_width_a );
    PARSE_PAD_WIDTH_SUBCASE( case4, pad_width_f );
    PARSE_PAD_WIDTH_SUBCASE( case4, pad_width_h );
    PARSE_PAD_WIDTH_SUBCASE( case4, pad_width_d );
}

TEST_CASE("parse_pad_width(case5)" * doctest::test_suite("index::parse_pad_width"))
{
    PARSE_PAD_WIDTH_SUBCASE( case5, pad_width );
    PARSE_PAD_WIDTH_SUBCASE( case5, pad_width_a );
    PARSE_PAD_WIDTH_SUBCASE( case5, pad_width_f );
    PARSE_PAD_WIDTH_SUBCASE( case5, pad_width_h );
    PARSE_PAD_WIDTH_SUBCASE( case5, pad_width_d );
}

TEST_CASE("shape_pad(case1)" * doctest::test_suite("index::shape_pad"))
{
    SHAPE_PAD_SUBCASE( case1, shape, pads );
    SHAPE_PAD_SUBCASE( case1, shape_a, pads_a );
    SHAPE_PAD_SUBCASE( case1, shape_v, pads_v );
    SHAPE_PAD_SUBCASE( case1, shape_f, pads_f );
    SHAPE_PAD_SUBCASE( case1, shape_h, pads_h );
    SHAPE_PAD_SUBCASE( case1, shape_ct, pads_ct );

    SHAPE_PAD_SUBCASE( case1, shape_ct, pads );
    SHAPE_PAD_SUBCASE( case1, shape_ct, pads_a );
    SHAPE_PAD_SUBCASE( case1, shape_ct, pads_v );
    SHAPE_PAD_SUBCASE( case1, shape_ct, pads_f );
    SHAPE_PAD_SUBCASE( case1, shape_ct, pads_h );

    SHAPE_PAD_SUBCASE( case1, shape, pads_ct );
    SHAPE_PAD_SUBCASE( case1, shape_a, pads_ct );
    SHAPE_PAD_SUBCASE( case1, shape_v, pads_ct );
    SHAPE_PAD_SUBCASE( case1, shape_f, pads_ct );
    SHAPE_PAD_SUBCASE( case1, shape_h, pads_ct );
}

TEST_CASE("shape_pad(case2)" * doctest::test_suite("index::shape_pad"))
{
    SHAPE_PAD_SUBCASE( case2, shape, pads );
    SHAPE_PAD_SUBCASE( case2, shape_a, pads_a );
    SHAPE_PAD_SUBCASE( case2, shape_v, pads_v );
    SHAPE_PAD_SUBCASE( case2, shape_f, pads_f );
    SHAPE_PAD_SUBCASE( case2, shape_h, pads_h );
}

TEST_CASE("shape_pad(case3)" * doctest::test_suite("index::shape_pad"))
{
    SHAPE_PAD_SUBCASE( case3, shape, pads );
    SHAPE_PAD_SUBCASE( case3, shape_a, pads_a );
    SHAPE_PAD_SUBCASE( case3, shape_v, pads_v );
    SHAPE_PAD_SUBCASE( case3, shape_f, pads_f );
    SHAPE_PAD_SUBCASE( case3, shape_h, pads_h );
}

TEST_CASE("shape_pad(case4)" * doctest::test_suite("index::shape_pad"))
{
    SHAPE_PAD_SUBCASE( case4, shape, pads );
    SHAPE_PAD_SUBCASE( case4, shape_a, pads_a );
    SHAPE_PAD_SUBCASE( case4, shape_v, pads_v );
    SHAPE_PAD_SUBCASE( case4, shape_f, pads_f );
    SHAPE_PAD_SUBCASE( case4, shape_h, pads_h );
}

TEST_CASE("shape_pad(case5)" * doctest::test_suite("index::shape_pad"))
{
    SHAPE_PAD_SUBCASE( case5, shape, pads );
    SHAPE_PAD_SUBCASE( case5, shape_a, pads_a );
    SHAPE_PAD_SUBCASE( case5, shape_v, pads_v );
    SHAPE_PAD_SUBCASE( case5, shape_f, pads_f );
    SHAPE_PAD_SUBCASE( case5, shape_h, pads_h );
}

TEST_CASE("shape_pad(case6)" * doctest::test_suite("index::shape_pad"))
{
    SHAPE_PAD_SUBCASE( case6, shape, pads );
}

#define CONSTEXPR_SHAPE_PAD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index, constexpr_shape_pad, case_name); \
    using namespace args; \
    constexpr auto result = nmtools::index::shape_pad(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("shape_pad(case1)" * doctest::test_suite("index::constexpr_shape_pad"))
{
    CONSTEXPR_SHAPE_PAD_SUBCASE( case1, shape, pads );
    CONSTEXPR_SHAPE_PAD_SUBCASE( case1, shape_a, pads_a );
    CONSTEXPR_SHAPE_PAD_SUBCASE( case1, shape_f, pads_f );
    CONSTEXPR_SHAPE_PAD_SUBCASE( case1, shape_h, pads_h );
}

TEST_CASE("shape_pad(case2)" * doctest::test_suite("index::constexpr_shape_pad"))
{
    CONSTEXPR_SHAPE_PAD_SUBCASE( case2, shape, pads );
    CONSTEXPR_SHAPE_PAD_SUBCASE( case2, shape_a, pads_a );
    CONSTEXPR_SHAPE_PAD_SUBCASE( case2, shape_f, pads_f );
    CONSTEXPR_SHAPE_PAD_SUBCASE( case2, shape_h, pads_h );
}

TEST_CASE("shape_pad(case3)" * doctest::test_suite("index::constexpr_shape_pad"))
{
    CONSTEXPR_SHAPE_PAD_SUBCASE( case3, shape, pads );
    CONSTEXPR_SHAPE_PAD_SUBCASE( case3, shape_a, pads_a );
    CONSTEXPR_SHAPE_PAD_SUBCASE( case3, shape_f, pads_f );
    CONSTEXPR_SHAPE_PAD_SUBCASE( case3, shape_h, pads_h );
}

TEST_CASE("shape_pad(case4)" * doctest::test_suite("index::constexpr_shape_pad"))
{
    CONSTEXPR_SHAPE_PAD_SUBCASE( case4, shape, pads );
    CONSTEXPR_SHAPE_PAD_SUBCASE( case4, shape_a, pads_a );
    CONSTEXPR_SHAPE_PAD_SUBCASE( case4, shape_f, pads_f );
    CONSTEXPR_SHAPE_PAD_SUBCASE( case4, shape_h, pads_h );
}

TEST_CASE("shape_pad(case5)" * doctest::test_suite("index::constexpr_shape_pad"))
{
    CONSTEXPR_SHAPE_PAD_SUBCASE( case5, shape, pads );
    CONSTEXPR_SHAPE_PAD_SUBCASE( case5, shape_a, pads_a );
    CONSTEXPR_SHAPE_PAD_SUBCASE( case5, shape_f, pads_f );
    CONSTEXPR_SHAPE_PAD_SUBCASE( case5, shape_h, pads_h );
}

TEST_CASE("shape_pad(case6)" * doctest::test_suite("index::constexpr_shape_pad"))
{
    CONSTEXPR_SHAPE_PAD_SUBCASE( case6, shape, pads );
}

#define INDEX_PAD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index, pad, case_name); \
    using namespace args; \
    auto result = nmtools::index::pad(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("pad(case1)" * doctest::test_suite("index::pad"))
{
    INDEX_PAD_SUBCASE( case1, indices, src_shape, dst_shape, pads );
    INDEX_PAD_SUBCASE( case1, indices_a, src_shape_a, dst_shape_a, pads_a );
    INDEX_PAD_SUBCASE( case1, indices_v, src_shape_v, dst_shape_v, pads_v );
    INDEX_PAD_SUBCASE( case1, indices_f, src_shape_f, dst_shape_f, pads_f );
    INDEX_PAD_SUBCASE( case1, indices_h, src_shape_h, dst_shape_h, pads_h );
    INDEX_PAD_SUBCASE( case1, indices_a, src_shape_a, dst_shape_a, pads_a );
}

TEST_CASE("pad(case2)" * doctest::test_suite("index::pad"))
{
    INDEX_PAD_SUBCASE( case2, indices, src_shape, dst_shape, pads );
    INDEX_PAD_SUBCASE( case2, indices_a, src_shape_a, dst_shape_a, pads_a );
    INDEX_PAD_SUBCASE( case2, indices_v, src_shape_v, dst_shape_v, pads_v );
    INDEX_PAD_SUBCASE( case2, indices_f, src_shape_f, dst_shape_f, pads_f );
    INDEX_PAD_SUBCASE( case2, indices_h, src_shape_h, dst_shape_h, pads_h );
    INDEX_PAD_SUBCASE( case2, indices_a, src_shape_a, dst_shape_a, pads_a );
}