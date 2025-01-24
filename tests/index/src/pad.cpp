#include "nmtools/index/pad.hpp"
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

TEST_CASE("shape_pad(case1)" * doctest::test_suite("index::shape_pad"))
{
    SHAPE_PAD_SUBCASE( case1, shape, pad_width );
    SHAPE_PAD_SUBCASE( case1, shape_a, pad_width_a );
    SHAPE_PAD_SUBCASE( case1, shape_v, pad_width_v );
    SHAPE_PAD_SUBCASE( case1, shape_f, pad_width_f );
    SHAPE_PAD_SUBCASE( case1, shape_h, pad_width_h );
    SHAPE_PAD_SUBCASE( case1, shape_ct, pad_width_ct );

    SHAPE_PAD_SUBCASE( case1, shape_ct, pad_width );
    SHAPE_PAD_SUBCASE( case1, shape_ct, pad_width_a );
    SHAPE_PAD_SUBCASE( case1, shape_ct, pad_width_v );
    SHAPE_PAD_SUBCASE( case1, shape_ct, pad_width_f );
    SHAPE_PAD_SUBCASE( case1, shape_ct, pad_width_h );

    SHAPE_PAD_SUBCASE( case1, shape, pad_width_ct );
    SHAPE_PAD_SUBCASE( case1, shape_a, pad_width_ct );
    SHAPE_PAD_SUBCASE( case1, shape_v, pad_width_ct );
    SHAPE_PAD_SUBCASE( case1, shape_f, pad_width_ct );
    SHAPE_PAD_SUBCASE( case1, shape_h, pad_width_ct );
}

TEST_CASE("shape_pad(case2)" * doctest::test_suite("index::shape_pad"))
{
    SHAPE_PAD_SUBCASE( case2, shape, pad_width );
    SHAPE_PAD_SUBCASE( case2, shape_a, pad_width_a );
    SHAPE_PAD_SUBCASE( case2, shape_v, pad_width_v );
    SHAPE_PAD_SUBCASE( case2, shape_f, pad_width_f );
    SHAPE_PAD_SUBCASE( case2, shape_h, pad_width_h );
}

TEST_CASE("shape_pad(case3)" * doctest::test_suite("index::shape_pad"))
{
    SHAPE_PAD_SUBCASE( case3, shape, pad_width );
    SHAPE_PAD_SUBCASE( case3, shape_a, pad_width_a );
    SHAPE_PAD_SUBCASE( case3, shape_v, pad_width_v );
    SHAPE_PAD_SUBCASE( case3, shape_f, pad_width_f );
    SHAPE_PAD_SUBCASE( case3, shape_h, pad_width_h );
}

TEST_CASE("shape_pad(case4)" * doctest::test_suite("index::shape_pad"))
{
    SHAPE_PAD_SUBCASE( case4, shape, pad_width );
    SHAPE_PAD_SUBCASE( case4, shape_a, pad_width_a );
    SHAPE_PAD_SUBCASE( case4, shape_v, pad_width_v );
    SHAPE_PAD_SUBCASE( case4, shape_f, pad_width_f );
    SHAPE_PAD_SUBCASE( case4, shape_h, pad_width_h );
}

TEST_CASE("shape_pad(case5)" * doctest::test_suite("index::shape_pad"))
{
    SHAPE_PAD_SUBCASE( case5, shape, pad_width );
    SHAPE_PAD_SUBCASE( case5, shape_a, pad_width_a );
    SHAPE_PAD_SUBCASE( case5, shape_v, pad_width_v );
    SHAPE_PAD_SUBCASE( case5, shape_f, pad_width_f );
    SHAPE_PAD_SUBCASE( case5, shape_h, pad_width_h );
}

TEST_CASE("shape_pad(case6)" * doctest::test_suite("index::shape_pad"))
{
    SHAPE_PAD_SUBCASE( case6, shape, pad_width );
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
    CONSTEXPR_SHAPE_PAD_SUBCASE( case1, shape, pad_width );
    CONSTEXPR_SHAPE_PAD_SUBCASE( case1, shape_a, pad_width_a );
    CONSTEXPR_SHAPE_PAD_SUBCASE( case1, shape_f, pad_width_f );
    CONSTEXPR_SHAPE_PAD_SUBCASE( case1, shape_h, pad_width_h );
}

TEST_CASE("shape_pad(case2)" * doctest::test_suite("index::constexpr_shape_pad"))
{
    CONSTEXPR_SHAPE_PAD_SUBCASE( case2, shape, pad_width );
    CONSTEXPR_SHAPE_PAD_SUBCASE( case2, shape_a, pad_width_a );
    CONSTEXPR_SHAPE_PAD_SUBCASE( case2, shape_f, pad_width_f );
    CONSTEXPR_SHAPE_PAD_SUBCASE( case2, shape_h, pad_width_h );
}

TEST_CASE("shape_pad(case3)" * doctest::test_suite("index::constexpr_shape_pad"))
{
    CONSTEXPR_SHAPE_PAD_SUBCASE( case3, shape, pad_width );
    CONSTEXPR_SHAPE_PAD_SUBCASE( case3, shape_a, pad_width_a );
    CONSTEXPR_SHAPE_PAD_SUBCASE( case3, shape_f, pad_width_f );
    CONSTEXPR_SHAPE_PAD_SUBCASE( case3, shape_h, pad_width_h );
}

TEST_CASE("shape_pad(case4)" * doctest::test_suite("index::constexpr_shape_pad"))
{
    CONSTEXPR_SHAPE_PAD_SUBCASE( case4, shape, pad_width );
    CONSTEXPR_SHAPE_PAD_SUBCASE( case4, shape_a, pad_width_a );
    CONSTEXPR_SHAPE_PAD_SUBCASE( case4, shape_f, pad_width_f );
    CONSTEXPR_SHAPE_PAD_SUBCASE( case4, shape_h, pad_width_h );
}

TEST_CASE("shape_pad(case5)" * doctest::test_suite("index::constexpr_shape_pad"))
{
    CONSTEXPR_SHAPE_PAD_SUBCASE( case5, shape, pad_width );
    CONSTEXPR_SHAPE_PAD_SUBCASE( case5, shape_a, pad_width_a );
    CONSTEXPR_SHAPE_PAD_SUBCASE( case5, shape_f, pad_width_f );
    CONSTEXPR_SHAPE_PAD_SUBCASE( case5, shape_h, pad_width_h );
}

TEST_CASE("shape_pad(case6)" * doctest::test_suite("index::constexpr_shape_pad"))
{
    CONSTEXPR_SHAPE_PAD_SUBCASE( case6, shape, pad_width );
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
    INDEX_PAD_SUBCASE( case1, indices, src_shape, dst_shape, pad_width );
    INDEX_PAD_SUBCASE( case1, indices_a, src_shape_a, dst_shape_a, pad_width_a );
    INDEX_PAD_SUBCASE( case1, indices_v, src_shape_v, dst_shape_v, pad_width_v );
    INDEX_PAD_SUBCASE( case1, indices_f, src_shape_f, dst_shape_f, pad_width_f );
    INDEX_PAD_SUBCASE( case1, indices_h, src_shape_h, dst_shape_h, pad_width_h );
    INDEX_PAD_SUBCASE( case1, indices_a, src_shape_a, dst_shape_a, pad_width_a );
}

TEST_CASE("pad(case2)" * doctest::test_suite("index::pad"))
{
    INDEX_PAD_SUBCASE( case2, indices, src_shape, dst_shape, pad_width );
    INDEX_PAD_SUBCASE( case2, indices_a, src_shape_a, dst_shape_a, pad_width_a );
    INDEX_PAD_SUBCASE( case2, indices_v, src_shape_v, dst_shape_v, pad_width_v );
    INDEX_PAD_SUBCASE( case2, indices_f, src_shape_f, dst_shape_f, pad_width_f );
    INDEX_PAD_SUBCASE( case2, indices_h, src_shape_h, dst_shape_h, pad_width_h );
    INDEX_PAD_SUBCASE( case2, indices_a, src_shape_a, dst_shape_a, pad_width_a );
}