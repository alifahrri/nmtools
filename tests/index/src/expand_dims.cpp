#include "nmtools/array/index/expand_dims.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/testing/data/index/expand_dims.hpp"
#include "nmtools/testing/doctest.hpp"

#include "nmtools/stl.hpp"

namespace nm = nmtools;
namespace na = nm::array;

using namespace nm::literals;

#define SHAPE_EXPAND_DIMS_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index, shape_expand_dims, case_name); \
    using namespace args; \
    auto result = nmtools::index::shape_expand_dims(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::expected ); \
}

TEST_CASE("shape_expand_dims(case1)" * doctest::test_suite("index::shape_expand_dims"))
{
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape, axes );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_a, axes_a );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_f, axes_f );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_h, axes_h );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_v, axes_v );

    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_ct, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_cl, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_cl, axes_cl );

    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_a, axes_a );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_a, axes_f );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_a, axes_h );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_a, axes_v );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_a, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_a, axes_cl );

    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_f, axes_a );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_f, axes_f );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_f, axes_h );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_f, axes_v );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_f, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_f, axes_cl );

    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_h, axes_a );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_h, axes_f );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_h, axes_h );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_h, axes_v );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_h, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_h, axes_cl );

    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_v, axes_a );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_v, axes_f );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_v, axes_h );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_v, axes_v );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_v, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_v, axes_cl );

    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_ct, axes_a );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_ct, axes_f );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_ct, axes_h );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_ct, axes_v );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_ct, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_ct, axes_cl );

    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_cl, axes_a );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_cl, axes_f );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_cl, axes_h );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_cl, axes_v );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_cl, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_cl, axes_cl );
}

TEST_CASE("shape_expand_dims(case2)" * doctest::test_suite("index::shape_expand_dims"))
{
    SHAPE_EXPAND_DIMS_SUBCASE( case2, shape, axes );
    SHAPE_EXPAND_DIMS_SUBCASE( case2, shape_a, axes_a );
    SHAPE_EXPAND_DIMS_SUBCASE( case2, shape_f, axes_f );
    SHAPE_EXPAND_DIMS_SUBCASE( case2, shape_h, axes_h );
    SHAPE_EXPAND_DIMS_SUBCASE( case2, shape_v, axes_v );

    SHAPE_EXPAND_DIMS_SUBCASE( case2, shape_ct, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case2, shape_cl, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case2, shape_cl, axes_cl );
}

TEST_CASE("shape_expand_dims(case3)" * doctest::test_suite("index::shape_expand_dims"))
{
    SHAPE_EXPAND_DIMS_SUBCASE( case3, shape, axes );
    SHAPE_EXPAND_DIMS_SUBCASE( case3, shape_a, axes_a );
    SHAPE_EXPAND_DIMS_SUBCASE( case3, shape_f, axes_f );
    SHAPE_EXPAND_DIMS_SUBCASE( case3, shape_h, axes_h );
    SHAPE_EXPAND_DIMS_SUBCASE( case3, shape_v, axes_v );

    SHAPE_EXPAND_DIMS_SUBCASE( case3, shape_ct, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case3, shape_cl, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case3, shape_cl, axes_cl );
}

TEST_CASE("shape_expand_dims(case4)" * doctest::test_suite("index::shape_expand_dims"))
{
    SHAPE_EXPAND_DIMS_SUBCASE( case4, shape, axes );
    SHAPE_EXPAND_DIMS_SUBCASE( case4, shape_a, axes_a );
    SHAPE_EXPAND_DIMS_SUBCASE( case4, shape_f, axes_f );
    SHAPE_EXPAND_DIMS_SUBCASE( case4, shape_h, axes_h );
    SHAPE_EXPAND_DIMS_SUBCASE( case4, shape_v, axes_v );

    SHAPE_EXPAND_DIMS_SUBCASE( case4, shape_ct, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case4, shape_cl, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case4, shape_cl, axes_cl );
}

TEST_CASE("shape_expand_dims(case5)" * doctest::test_suite("index::shape_expand_dims"))
{
    SHAPE_EXPAND_DIMS_SUBCASE( case5, shape, axes );
    SHAPE_EXPAND_DIMS_SUBCASE( case5, shape_a, axes_a );
    SHAPE_EXPAND_DIMS_SUBCASE( case5, shape_f, axes_f );
    SHAPE_EXPAND_DIMS_SUBCASE( case5, shape_h, axes_h );
    SHAPE_EXPAND_DIMS_SUBCASE( case5, shape_v, axes_v );

    SHAPE_EXPAND_DIMS_SUBCASE( case5, shape_ct, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case5, shape_cl, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case5, shape_cl, axes_cl );
}

TEST_CASE("shape_expand_dims(case6)" * doctest::test_suite("index::shape_expand_dims"))
{
    SHAPE_EXPAND_DIMS_SUBCASE( case6, shape, axes );
    SHAPE_EXPAND_DIMS_SUBCASE( case6, shape_a, axes_a );
    SHAPE_EXPAND_DIMS_SUBCASE( case6, shape_f, axes_f );
    SHAPE_EXPAND_DIMS_SUBCASE( case6, shape_h, axes_h );
    SHAPE_EXPAND_DIMS_SUBCASE( case6, shape_v, axes_v );

    SHAPE_EXPAND_DIMS_SUBCASE( case6, shape_ct, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case6, shape_cl, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case6, shape_cl, axes_cl );
}

TEST_CASE("shape_expand_dims(case7)" * doctest::test_suite("index::shape_expand_dims"))
{
    SHAPE_EXPAND_DIMS_SUBCASE( case7, shape, axes );
    SHAPE_EXPAND_DIMS_SUBCASE( case7, shape_a, axes_a );
    SHAPE_EXPAND_DIMS_SUBCASE( case7, shape_f, axes_f );
    SHAPE_EXPAND_DIMS_SUBCASE( case7, shape_h, axes_h );
    SHAPE_EXPAND_DIMS_SUBCASE( case7, shape_v, axes_v );

    SHAPE_EXPAND_DIMS_SUBCASE( case7, shape_ct, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case7, shape_cl, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case7, shape_cl, axes_cl );
}

TEST_CASE("shape_expand_dims(case8)" * doctest::test_suite("index::shape_expand_dims"))
{
    SHAPE_EXPAND_DIMS_SUBCASE( case8, shape, axes );
    SHAPE_EXPAND_DIMS_SUBCASE( case8, shape_a, axes_a );
    SHAPE_EXPAND_DIMS_SUBCASE( case8, shape_f, axes_f );
    SHAPE_EXPAND_DIMS_SUBCASE( case8, shape_h, axes_h );
    SHAPE_EXPAND_DIMS_SUBCASE( case8, shape_v, axes_v );

    SHAPE_EXPAND_DIMS_SUBCASE( case8, shape_ct, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case8, shape_cl, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case8, shape_cl, axes_cl );
}

TEST_CASE("shape_expand_dims(case9)" * doctest::test_suite("index::shape_expand_dims"))
{
    SHAPE_EXPAND_DIMS_SUBCASE( case9, shape, axes );
    SHAPE_EXPAND_DIMS_SUBCASE( case9, shape_a, axes_a );
    SHAPE_EXPAND_DIMS_SUBCASE( case9, shape_f, axes_f );
    SHAPE_EXPAND_DIMS_SUBCASE( case9, shape_h, axes_h );
    SHAPE_EXPAND_DIMS_SUBCASE( case9, shape_v, axes_v );

    SHAPE_EXPAND_DIMS_SUBCASE( case9, shape_ct, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case9, shape_cl, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case9, shape_cl, axes_cl );
}

TEST_CASE("shape_expand_dims(case10)" * doctest::test_suite("index::shape_expand_dims"))
{
    SHAPE_EXPAND_DIMS_SUBCASE( case10, shape, axes );
    SHAPE_EXPAND_DIMS_SUBCASE( case10, shape_a, axes_a );
    SHAPE_EXPAND_DIMS_SUBCASE( case10, shape_f, axes_f );
    SHAPE_EXPAND_DIMS_SUBCASE( case10, shape_h, axes_h );
    SHAPE_EXPAND_DIMS_SUBCASE( case10, shape_v, axes_v );

    SHAPE_EXPAND_DIMS_SUBCASE( case10, shape_ct, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case10, shape_cl, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case10, shape_cl, axes_cl );
}

TEST_CASE("shape_expand_dims(case11)" * doctest::test_suite("index::shape_expand_dims"))
{
    SHAPE_EXPAND_DIMS_SUBCASE( case11, shape, axes );
    SHAPE_EXPAND_DIMS_SUBCASE( case11, shape_a, axes_a );
    SHAPE_EXPAND_DIMS_SUBCASE( case11, shape_f, axes_f );
    SHAPE_EXPAND_DIMS_SUBCASE( case11, shape_h, axes_h );
    SHAPE_EXPAND_DIMS_SUBCASE( case11, shape_v, axes_v );

    SHAPE_EXPAND_DIMS_SUBCASE( case11, shape_ct, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case11, shape_cl, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case11, shape_cl, axes_cl );
}

TEST_CASE("shape_expand_dims(case12)" * doctest::test_suite("index::shape_expand_dims"))
{
    SHAPE_EXPAND_DIMS_SUBCASE( case12, shape, axes );
    SHAPE_EXPAND_DIMS_SUBCASE( case12, shape_a, axes_a );
    SHAPE_EXPAND_DIMS_SUBCASE( case12, shape_f, axes_f );
    SHAPE_EXPAND_DIMS_SUBCASE( case12, shape_h, axes_h );
    SHAPE_EXPAND_DIMS_SUBCASE( case12, shape_v, axes_v );

    SHAPE_EXPAND_DIMS_SUBCASE( case12, shape_ct, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case12, shape_cl, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case12, shape_cl, axes_cl );
}

TEST_CASE("shape_expand_dims(case13)" * doctest::test_suite("index::shape_expand_dims"))
{
    SHAPE_EXPAND_DIMS_SUBCASE( case13, shape, axes );
    SHAPE_EXPAND_DIMS_SUBCASE( case13, shape_a, axes_a );
    SHAPE_EXPAND_DIMS_SUBCASE( case13, shape_f, axes_f );
    SHAPE_EXPAND_DIMS_SUBCASE( case13, shape_h, axes_h );
    SHAPE_EXPAND_DIMS_SUBCASE( case13, shape_v, axes_v );

    SHAPE_EXPAND_DIMS_SUBCASE( case13, shape_ct, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case13, shape_cl, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case13, shape_cl, axes_cl );
}