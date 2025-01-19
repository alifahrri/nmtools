#include "nmtools/index/resize.hpp"
#include "nmtools/testing/data/index/resize.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;

#define SHAPE_RESIZE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index, shape_resize, case_name); \
    using namespace args; \
    auto result = nm::index::shape_resize(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::expected ); \
}

#define RESIZE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index, resize, case_name); \
    using namespace args; \
    auto result = nm::index::resize(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::expected ); \
}

TEST_CASE("shape_resize(case1)" * doctest::test_suite("index::shape_resize"))
{
    SHAPE_RESIZE_SUBCASE( case1,   src_shape, dst_shape );
    SHAPE_RESIZE_SUBCASE( case1, src_shape_a, dst_shape_a );
    SHAPE_RESIZE_SUBCASE( case1, src_shape_v, dst_shape_v );
    SHAPE_RESIZE_SUBCASE( case1, src_shape_h, dst_shape_h );
    SHAPE_RESIZE_SUBCASE( case1, src_shape_f, dst_shape_f );

    SHAPE_RESIZE_SUBCASE( case1, src_shape_ct, dst_shape_ct );
    SHAPE_RESIZE_SUBCASE( case1, src_shape_cl, dst_shape_cl );

    SHAPE_RESIZE_SUBCASE( case1, src_shape_ct, dst_shape_a );
    SHAPE_RESIZE_SUBCASE( case1, src_shape_ct, dst_shape_v );
    SHAPE_RESIZE_SUBCASE( case1, src_shape_ct, dst_shape_h );
    SHAPE_RESIZE_SUBCASE( case1, src_shape_ct, dst_shape_f );

    SHAPE_RESIZE_SUBCASE( case1, src_shape_a, dst_shape_ct );
    SHAPE_RESIZE_SUBCASE( case1, src_shape_v, dst_shape_ct );
    SHAPE_RESIZE_SUBCASE( case1, src_shape_h, dst_shape_ct );
    SHAPE_RESIZE_SUBCASE( case1, src_shape_f, dst_shape_ct );
}

TEST_CASE("shape_resize(case2)" * doctest::test_suite("index::shape_resize"))
{
    SHAPE_RESIZE_SUBCASE( case2,   src_shape, dst_shape );
    SHAPE_RESIZE_SUBCASE( case2, src_shape_a, dst_shape_a );
    SHAPE_RESIZE_SUBCASE( case2, src_shape_v, dst_shape_v );
    SHAPE_RESIZE_SUBCASE( case2, src_shape_h, dst_shape_h );
    SHAPE_RESIZE_SUBCASE( case2, src_shape_f, dst_shape_f );

    SHAPE_RESIZE_SUBCASE( case2, src_shape_ct, dst_shape_ct );
    SHAPE_RESIZE_SUBCASE( case2, src_shape_cl, dst_shape_cl );

    SHAPE_RESIZE_SUBCASE( case2, src_shape_ct, dst_shape_a );
    SHAPE_RESIZE_SUBCASE( case2, src_shape_ct, dst_shape_v );
    SHAPE_RESIZE_SUBCASE( case2, src_shape_ct, dst_shape_h );
    SHAPE_RESIZE_SUBCASE( case2, src_shape_ct, dst_shape_f );

    SHAPE_RESIZE_SUBCASE( case2, src_shape_a, dst_shape_ct );
    SHAPE_RESIZE_SUBCASE( case2, src_shape_v, dst_shape_ct );
    SHAPE_RESIZE_SUBCASE( case2, src_shape_h, dst_shape_ct );
    SHAPE_RESIZE_SUBCASE( case2, src_shape_f, dst_shape_ct );
}

TEST_CASE("shape_resize(case3)" * doctest::test_suite("index::shape_resize"))
{
    SHAPE_RESIZE_SUBCASE( case3,   src_shape, dst_shape );
    SHAPE_RESIZE_SUBCASE( case3, src_shape_a, dst_shape_a );
    SHAPE_RESIZE_SUBCASE( case3, src_shape_v, dst_shape_v );
    SHAPE_RESIZE_SUBCASE( case3, src_shape_h, dst_shape_h );
    SHAPE_RESIZE_SUBCASE( case3, src_shape_f, dst_shape_f );

    SHAPE_RESIZE_SUBCASE( case3, src_shape_ct, dst_shape_ct );
    SHAPE_RESIZE_SUBCASE( case3, src_shape_cl, dst_shape_cl );

    SHAPE_RESIZE_SUBCASE( case3, src_shape_ct, dst_shape_a );
    SHAPE_RESIZE_SUBCASE( case3, src_shape_ct, dst_shape_v );
    SHAPE_RESIZE_SUBCASE( case3, src_shape_ct, dst_shape_h );
    SHAPE_RESIZE_SUBCASE( case3, src_shape_ct, dst_shape_f );

    SHAPE_RESIZE_SUBCASE( case3, src_shape_a, dst_shape_ct );
    SHAPE_RESIZE_SUBCASE( case3, src_shape_v, dst_shape_ct );
    SHAPE_RESIZE_SUBCASE( case3, src_shape_h, dst_shape_ct );
    SHAPE_RESIZE_SUBCASE( case3, src_shape_f, dst_shape_ct );
}

TEST_CASE("shape_resize(case4)" * doctest::test_suite("index::shape_resize"))
{
    SHAPE_RESIZE_SUBCASE( case4,   src_shape, dst_shape );
    SHAPE_RESIZE_SUBCASE( case4, src_shape_a, dst_shape_a );
    SHAPE_RESIZE_SUBCASE( case4, src_shape_v, dst_shape_v );
    SHAPE_RESIZE_SUBCASE( case4, src_shape_h, dst_shape_h );
    SHAPE_RESIZE_SUBCASE( case4, src_shape_f, dst_shape_f );

    SHAPE_RESIZE_SUBCASE( case4, src_shape_ct, dst_shape_ct );
    SHAPE_RESIZE_SUBCASE( case4, src_shape_cl, dst_shape_cl );

    SHAPE_RESIZE_SUBCASE( case4, src_shape_ct, dst_shape_a );
    SHAPE_RESIZE_SUBCASE( case4, src_shape_ct, dst_shape_v );
    SHAPE_RESIZE_SUBCASE( case4, src_shape_ct, dst_shape_h );
    SHAPE_RESIZE_SUBCASE( case4, src_shape_ct, dst_shape_f );

    SHAPE_RESIZE_SUBCASE( case4, src_shape_a, dst_shape_ct );
    SHAPE_RESIZE_SUBCASE( case4, src_shape_v, dst_shape_ct );
    SHAPE_RESIZE_SUBCASE( case4, src_shape_h, dst_shape_ct );
    SHAPE_RESIZE_SUBCASE( case4, src_shape_f, dst_shape_ct );
}

TEST_CASE("resize(case1)" * doctest::test_suite("index::resize"))
{
    RESIZE_SUBCASE( case1, indices_a, src_shape_a, dst_shape_a );
    RESIZE_SUBCASE( case1, indices_v, src_shape_v, dst_shape_v );
    RESIZE_SUBCASE( case1, indices_h, src_shape_h, dst_shape_h );
    RESIZE_SUBCASE( case1, indices_f, src_shape_f, dst_shape_f );
}

TEST_CASE("resize(case2)" * doctest::test_suite("index::resize"))
{
    RESIZE_SUBCASE( case2, indices_a, src_shape_a, dst_shape_a );
    RESIZE_SUBCASE( case2, indices_v, src_shape_v, dst_shape_v );
    RESIZE_SUBCASE( case2, indices_h, src_shape_h, dst_shape_h );
    RESIZE_SUBCASE( case2, indices_f, src_shape_f, dst_shape_f );
}

TEST_CASE("resize(case3)" * doctest::test_suite("index::resize"))
{
    RESIZE_SUBCASE( case3, indices_a, src_shape_a, dst_shape_a );
    RESIZE_SUBCASE( case3, indices_v, src_shape_v, dst_shape_v );
    RESIZE_SUBCASE( case3, indices_h, src_shape_h, dst_shape_h );
    RESIZE_SUBCASE( case3, indices_f, src_shape_f, dst_shape_f );
}

TEST_CASE("resize(case4)" * doctest::test_suite("index::resize"))
{
    RESIZE_SUBCASE( case4, indices_a, src_shape_a, dst_shape_a );
    RESIZE_SUBCASE( case4, indices_v, src_shape_v, dst_shape_v );
    RESIZE_SUBCASE( case4, indices_h, src_shape_h, dst_shape_h );
    RESIZE_SUBCASE( case4, indices_f, src_shape_f, dst_shape_f );
}

TEST_CASE("resize(case5)" * doctest::test_suite("index::resize"))
{
    RESIZE_SUBCASE( case5, indices_a, src_shape_a, dst_shape_a );
    RESIZE_SUBCASE( case5, indices_v, src_shape_v, dst_shape_v );
    RESIZE_SUBCASE( case5, indices_h, src_shape_h, dst_shape_h );
    RESIZE_SUBCASE( case5, indices_f, src_shape_f, dst_shape_f );
}

TEST_CASE("resize(case6)" * doctest::test_suite("index::resize"))
{
    RESIZE_SUBCASE( case6, indices_a, src_shape_a, dst_shape_a );
    RESIZE_SUBCASE( case6, indices_v, src_shape_v, dst_shape_v );
    RESIZE_SUBCASE( case6, indices_h, src_shape_h, dst_shape_h );
    RESIZE_SUBCASE( case6, indices_f, src_shape_f, dst_shape_f );
}

TEST_CASE("resize(case7)" * doctest::test_suite("index::resize"))
{
    RESIZE_SUBCASE( case7, indices_a, src_shape_a, dst_shape_a );
    RESIZE_SUBCASE( case7, indices_v, src_shape_v, dst_shape_v );
    RESIZE_SUBCASE( case7, indices_h, src_shape_h, dst_shape_h );
    RESIZE_SUBCASE( case7, indices_f, src_shape_f, dst_shape_f );
}

TEST_CASE("resize(case8)" * doctest::test_suite("index::resize"))
{
    RESIZE_SUBCASE( case8, indices_a, src_shape_a, dst_shape_a );
    RESIZE_SUBCASE( case8, indices_v, src_shape_v, dst_shape_v );
    RESIZE_SUBCASE( case8, indices_h, src_shape_h, dst_shape_h );
    RESIZE_SUBCASE( case8, indices_f, src_shape_f, dst_shape_f );
}

TEST_CASE("resize(case9)" * doctest::test_suite("index::resize"))
{
    RESIZE_SUBCASE( case9, indices_a, src_shape_a, dst_shape_a );
    RESIZE_SUBCASE( case9, indices_v, src_shape_v, dst_shape_v );
    RESIZE_SUBCASE( case9, indices_h, src_shape_h, dst_shape_h );
    RESIZE_SUBCASE( case9, indices_f, src_shape_f, dst_shape_f );
}

TEST_CASE("resize(case10)" * doctest::test_suite("index::resize"))
{
    RESIZE_SUBCASE( case10, indices_a, src_shape_a, dst_shape_a );
    RESIZE_SUBCASE( case10, indices_v, src_shape_v, dst_shape_v );
    RESIZE_SUBCASE( case10, indices_h, src_shape_h, dst_shape_h );
    RESIZE_SUBCASE( case10, indices_f, src_shape_f, dst_shape_f );
}

TEST_CASE("resize(case11)" * doctest::test_suite("index::resize"))
{
    RESIZE_SUBCASE( case11, indices_a, src_shape_a, dst_shape_a );
    RESIZE_SUBCASE( case11, indices_v, src_shape_v, dst_shape_v );
    RESIZE_SUBCASE( case11, indices_h, src_shape_h, dst_shape_h );
    RESIZE_SUBCASE( case11, indices_f, src_shape_f, dst_shape_f );
}

TEST_CASE("resize(case12)" * doctest::test_suite("index::resize"))
{
    RESIZE_SUBCASE( case12, indices_a, src_shape_a, dst_shape_a );
    RESIZE_SUBCASE( case12, indices_v, src_shape_v, dst_shape_v );
    RESIZE_SUBCASE( case12, indices_h, src_shape_h, dst_shape_h );
    RESIZE_SUBCASE( case12, indices_f, src_shape_f, dst_shape_f );
}

TEST_CASE("resize(case13)" * doctest::test_suite("index::resize"))
{
    RESIZE_SUBCASE( case13, indices_a, src_shape_a, dst_shape_a );
    RESIZE_SUBCASE( case13, indices_v, src_shape_v, dst_shape_v );
    RESIZE_SUBCASE( case13, indices_h, src_shape_h, dst_shape_h );
    RESIZE_SUBCASE( case13, indices_f, src_shape_f, dst_shape_f );
}

TEST_CASE("resize(case14)" * doctest::test_suite("index::resize"))
{
    RESIZE_SUBCASE( case14, indices_a, src_shape_a, dst_shape_a );
    RESIZE_SUBCASE( case14, indices_v, src_shape_v, dst_shape_v );
    RESIZE_SUBCASE( case14, indices_h, src_shape_h, dst_shape_h );
    RESIZE_SUBCASE( case14, indices_f, src_shape_f, dst_shape_f );
}

TEST_CASE("resize(case15)" * doctest::test_suite("index::resize"))
{
    RESIZE_SUBCASE( case15, indices_a, src_shape_a, dst_shape_a );
    RESIZE_SUBCASE( case15, indices_v, src_shape_v, dst_shape_v );
    RESIZE_SUBCASE( case15, indices_h, src_shape_h, dst_shape_h );
    RESIZE_SUBCASE( case15, indices_f, src_shape_f, dst_shape_f );
}

TEST_CASE("resize(case17)" * doctest::test_suite("index::resize"))
{
    RESIZE_SUBCASE( case17, indices_a, src_shape_a, dst_shape_a );
    RESIZE_SUBCASE( case17, indices_v, src_shape_v, dst_shape_v );
    RESIZE_SUBCASE( case17, indices_h, src_shape_h, dst_shape_h );
    RESIZE_SUBCASE( case17, indices_f, src_shape_f, dst_shape_f );
}

TEST_CASE("resize(case18)" * doctest::test_suite("index::resize"))
{
    RESIZE_SUBCASE( case18, indices_a, src_shape_a, dst_shape_a );
    RESIZE_SUBCASE( case18, indices_v, src_shape_v, dst_shape_v );
    RESIZE_SUBCASE( case18, indices_h, src_shape_h, dst_shape_h );
    RESIZE_SUBCASE( case18, indices_f, src_shape_f, dst_shape_f );
}