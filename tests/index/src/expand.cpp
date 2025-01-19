#include "nmtools/array/expand.hpp"
#include "nmtools/testing/data/index/expand.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;

#define SHAPE_EXPAND(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index,shape_expand,case_name); \
    using namespace args; \
    auto result = nmtools::index::shape_expand(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

#define INDEX_EXPAND(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index,expand,case_name); \
    using namespace args; \
    auto result = nmtools::index::expand(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("shape_expand(case1)" * doctest::test_suite("index::shape_expand"))
{
    SHAPE_EXPAND( case1, src_shape, axis, spacing );
    SHAPE_EXPAND( case1, src_shape_a, axis, spacing );
    SHAPE_EXPAND( case1, src_shape_f, axis, spacing );
    SHAPE_EXPAND( case1, src_shape_h, axis, spacing );
    SHAPE_EXPAND( case1, src_shape_v, axis, spacing );

    SHAPE_EXPAND( case1, src_shape_ct, axis_ct, spacing_ct );
}

TEST_CASE("shape_expand(case2)" * doctest::test_suite("index::shape_expand"))
{
    SHAPE_EXPAND( case2, src_shape, axis, spacing );
    SHAPE_EXPAND( case2, src_shape_a, axis, spacing );
    SHAPE_EXPAND( case2, src_shape_f, axis, spacing );
    SHAPE_EXPAND( case2, src_shape_h, axis, spacing );
    SHAPE_EXPAND( case2, src_shape_v, axis, spacing );

    SHAPE_EXPAND( case2, src_shape_ct, axis_ct, spacing_ct );
}

TEST_CASE("shape_expand(case3)" * doctest::test_suite("index::shape_expand"))
{
    SHAPE_EXPAND( case3, src_shape, axis, spacing );
    SHAPE_EXPAND( case3, src_shape_a, axis, spacing );
    SHAPE_EXPAND( case3, src_shape_f, axis, spacing );
    SHAPE_EXPAND( case3, src_shape_h, axis, spacing );
    SHAPE_EXPAND( case3, src_shape_v, axis, spacing );

    SHAPE_EXPAND( case3, src_shape_ct, axis_ct, spacing_ct );
}

TEST_CASE("shape_expand(case4)" * doctest::test_suite("index::shape_expand"))
{
    SHAPE_EXPAND( case4, src_shape, axis, spacing );
    SHAPE_EXPAND( case4, src_shape_a, axis, spacing );
    SHAPE_EXPAND( case4, src_shape_f, axis, spacing );
    SHAPE_EXPAND( case4, src_shape_h, axis, spacing );
    SHAPE_EXPAND( case4, src_shape_v, axis, spacing );

    SHAPE_EXPAND( case4, src_shape_ct, axis_ct, spacing_ct );
}

TEST_CASE("shape_expand(case5)" * doctest::test_suite("index::shape_expand"))
{
    SHAPE_EXPAND( case5, src_shape, axis, spacing );
    SHAPE_EXPAND( case5, src_shape_a, axis, spacing );
    SHAPE_EXPAND( case5, src_shape_f, axis, spacing );
    SHAPE_EXPAND( case5, src_shape_h, axis, spacing );
    SHAPE_EXPAND( case5, src_shape_v, axis, spacing );

    SHAPE_EXPAND( case5, src_shape_ct, axis_ct, spacing_ct );
}

TEST_CASE("shape_expand(case6)" * doctest::test_suite("index::shape_expand"))
{
    SHAPE_EXPAND( case6, src_shape, axis, spacing );
    SHAPE_EXPAND( case6, src_shape_a, axis, spacing );
    SHAPE_EXPAND( case6, src_shape_f, axis, spacing );
    SHAPE_EXPAND( case6, src_shape_h, axis, spacing );
    SHAPE_EXPAND( case6, src_shape_v, axis, spacing );

    SHAPE_EXPAND( case6, src_shape_ct, axis_ct, spacing_ct );
}

TEST_CASE("shape_expand(case7)" * doctest::test_suite("index::shape_expand"))
{
    SHAPE_EXPAND( case7, src_shape, axis, spacing );
    SHAPE_EXPAND( case7, src_shape_a, axis, spacing );
    SHAPE_EXPAND( case7, src_shape_f, axis, spacing );
    SHAPE_EXPAND( case7, src_shape_h, axis, spacing );
    SHAPE_EXPAND( case7, src_shape_v, axis, spacing );

    SHAPE_EXPAND( case7, src_shape_ct, axis_ct, spacing_ct );
}

/***********************************************************************/

TEST_CASE("index_expand(case1a)" * doctest::test_suite("index::expand"))
{
    INDEX_EXPAND( case1a, indices, src_shape, axis, spacing );
    INDEX_EXPAND( case1a, indices_a, src_shape_a, axis, spacing );
    INDEX_EXPAND( case1a, indices_f, src_shape_f, axis, spacing );
    INDEX_EXPAND( case1a, indices_h, src_shape_h, axis, spacing );
    INDEX_EXPAND( case1a, indices_v, src_shape_v, axis, spacing );
}

TEST_CASE("index_expand(case1b)" * doctest::test_suite("index::expand"))
{
    INDEX_EXPAND( case1b, indices, src_shape, axis, spacing );
    INDEX_EXPAND( case1b, indices_a, src_shape_a, axis, spacing );
    INDEX_EXPAND( case1b, indices_f, src_shape_f, axis, spacing );
    INDEX_EXPAND( case1b, indices_h, src_shape_h, axis, spacing );
    INDEX_EXPAND( case1b, indices_v, src_shape_v, axis, spacing );
}

TEST_CASE("index_expand(case1c)" * doctest::test_suite("index::expand"))
{
    INDEX_EXPAND( case1c, indices, src_shape, axis, spacing );
    INDEX_EXPAND( case1c, indices_a, src_shape_a, axis, spacing );
    INDEX_EXPAND( case1c, indices_f, src_shape_f, axis, spacing );
    INDEX_EXPAND( case1c, indices_h, src_shape_h, axis, spacing );
    INDEX_EXPAND( case1c, indices_v, src_shape_v, axis, spacing );
}

TEST_CASE("index_expand(case1d)" * doctest::test_suite("index::expand"))
{
    INDEX_EXPAND( case1d, indices, src_shape, axis, spacing );
    INDEX_EXPAND( case1d, indices_a, src_shape_a, axis, spacing );
    INDEX_EXPAND( case1d, indices_f, src_shape_f, axis, spacing );
    INDEX_EXPAND( case1d, indices_h, src_shape_h, axis, spacing );
    INDEX_EXPAND( case1d, indices_v, src_shape_v, axis, spacing );
}

TEST_CASE("index_expand(case1e)" * doctest::test_suite("index::expand"))
{
    INDEX_EXPAND( case1e, indices, src_shape, axis, spacing );
    INDEX_EXPAND( case1e, indices_a, src_shape_a, axis, spacing );
    INDEX_EXPAND( case1e, indices_f, src_shape_f, axis, spacing );
    INDEX_EXPAND( case1e, indices_h, src_shape_h, axis, spacing );
    INDEX_EXPAND( case1e, indices_v, src_shape_v, axis, spacing );
}

TEST_CASE("index_expand(case1f)" * doctest::test_suite("index::expand"))
{
    INDEX_EXPAND( case1f, indices, src_shape, axis, spacing );
    INDEX_EXPAND( case1f, indices_a, src_shape_a, axis, spacing );
    INDEX_EXPAND( case1f, indices_f, src_shape_f, axis, spacing );
    INDEX_EXPAND( case1f, indices_h, src_shape_h, axis, spacing );
    INDEX_EXPAND( case1f, indices_v, src_shape_v, axis, spacing );
}

TEST_CASE("index_expand(case1g)" * doctest::test_suite("index::expand"))
{
    INDEX_EXPAND( case1g, indices, src_shape, axis, spacing );
    INDEX_EXPAND( case1g, indices_a, src_shape_a, axis, spacing );
    INDEX_EXPAND( case1g, indices_f, src_shape_f, axis, spacing );
    INDEX_EXPAND( case1g, indices_h, src_shape_h, axis, spacing );
    INDEX_EXPAND( case1g, indices_v, src_shape_v, axis, spacing );
}

TEST_CASE("index_expand(case1h)" * doctest::test_suite("index::expand"))
{
    INDEX_EXPAND( case1h, indices, src_shape, axis, spacing );
    INDEX_EXPAND( case1h, indices_a, src_shape_a, axis, spacing );
    INDEX_EXPAND( case1h, indices_f, src_shape_f, axis, spacing );
    INDEX_EXPAND( case1h, indices_h, src_shape_h, axis, spacing );
    INDEX_EXPAND( case1h, indices_v, src_shape_v, axis, spacing );
}

TEST_CASE("index_expand(case1i)" * doctest::test_suite("index::expand"))
{
    INDEX_EXPAND( case1i, indices, src_shape, axis, spacing );
    INDEX_EXPAND( case1i, indices_a, src_shape_a, axis, spacing );
    INDEX_EXPAND( case1i, indices_f, src_shape_f, axis, spacing );
    INDEX_EXPAND( case1i, indices_h, src_shape_h, axis, spacing );
    INDEX_EXPAND( case1i, indices_v, src_shape_v, axis, spacing );
}

TEST_CASE("index_expand(case1j)" * doctest::test_suite("index::expand"))
{
    INDEX_EXPAND( case1j, indices, src_shape, axis, spacing );
    INDEX_EXPAND( case1j, indices_a, src_shape_a, axis, spacing );
    INDEX_EXPAND( case1j, indices_f, src_shape_f, axis, spacing );
    INDEX_EXPAND( case1j, indices_h, src_shape_h, axis, spacing );
    INDEX_EXPAND( case1j, indices_v, src_shape_v, axis, spacing );
}

TEST_CASE("index_expand(case1k)" * doctest::test_suite("index::expand"))
{
    INDEX_EXPAND( case1k, indices, src_shape, axis, spacing );
    INDEX_EXPAND( case1k, indices_a, src_shape_a, axis, spacing );
    INDEX_EXPAND( case1k, indices_f, src_shape_f, axis, spacing );
    INDEX_EXPAND( case1k, indices_h, src_shape_h, axis, spacing );
    INDEX_EXPAND( case1k, indices_v, src_shape_v, axis, spacing );
}

/***********************************************************************/

TEST_CASE("index_expand(case2aa)" * doctest::test_suite("index::expand"))
{
    INDEX_EXPAND( case2aa, indices, src_shape, axis, spacing );
    INDEX_EXPAND( case2aa, indices_a, src_shape_a, axis, spacing );
    INDEX_EXPAND( case2aa, indices_f, src_shape_f, axis, spacing );
    INDEX_EXPAND( case2aa, indices_h, src_shape_h, axis, spacing );
    INDEX_EXPAND( case2aa, indices_v, src_shape_v, axis, spacing );
}

TEST_CASE("index_expand(case2ab)" * doctest::test_suite("index::expand"))
{
    INDEX_EXPAND( case2ab, indices, src_shape, axis, spacing );
    INDEX_EXPAND( case2ab, indices_a, src_shape_a, axis, spacing );
    INDEX_EXPAND( case2ab, indices_f, src_shape_f, axis, spacing );
    INDEX_EXPAND( case2ab, indices_h, src_shape_h, axis, spacing );
    INDEX_EXPAND( case2ab, indices_v, src_shape_v, axis, spacing );
}

TEST_CASE("index_expand(case2ac)" * doctest::test_suite("index::expand"))
{
    INDEX_EXPAND( case2ac, indices, src_shape, axis, spacing );
    INDEX_EXPAND( case2ad, indices_a, src_shape_a, axis, spacing );
    INDEX_EXPAND( case2ad, indices_f, src_shape_f, axis, spacing );
    INDEX_EXPAND( case2ad, indices_h, src_shape_h, axis, spacing );
    INDEX_EXPAND( case2ad, indices_v, src_shape_v, axis, spacing );
}

TEST_CASE("index_expand(case2ad)" * doctest::test_suite("index::expand"))
{
    INDEX_EXPAND( case2ad, indices, src_shape, axis, spacing );
    INDEX_EXPAND( case2ad, indices_a, src_shape_a, axis, spacing );
    INDEX_EXPAND( case2ad, indices_f, src_shape_f, axis, spacing );
    INDEX_EXPAND( case2ad, indices_h, src_shape_h, axis, spacing );
    INDEX_EXPAND( case2ad, indices_v, src_shape_v, axis, spacing );
}

TEST_CASE("index_expand(case2ae)" * doctest::test_suite("index::expand"))
{
    INDEX_EXPAND( case2ae, indices, src_shape, axis, spacing );
    INDEX_EXPAND( case2ae, indices_a, src_shape_a, axis, spacing );
    INDEX_EXPAND( case2ae, indices_f, src_shape_f, axis, spacing );
    INDEX_EXPAND( case2ae, indices_h, src_shape_h, axis, spacing );
    INDEX_EXPAND( case2ae, indices_v, src_shape_v, axis, spacing );
}

TEST_CASE("index_expand(case2ba)" * doctest::test_suite("index::expand"))
{
    INDEX_EXPAND( case2ba, indices, src_shape, axis, spacing );
    INDEX_EXPAND( case2ba, indices_a, src_shape_a, axis, spacing );
    INDEX_EXPAND( case2ba, indices_f, src_shape_f, axis, spacing );
    INDEX_EXPAND( case2ba, indices_h, src_shape_h, axis, spacing );
    INDEX_EXPAND( case2ba, indices_v, src_shape_v, axis, spacing );
}

TEST_CASE("index_expand(case2bb)" * doctest::test_suite("index::expand"))
{
    INDEX_EXPAND( case2bb, indices, src_shape, axis, spacing );
    INDEX_EXPAND( case2bb, indices_a, src_shape_a, axis, spacing );
    INDEX_EXPAND( case2bb, indices_f, src_shape_f, axis, spacing );
    INDEX_EXPAND( case2bb, indices_h, src_shape_h, axis, spacing );
    INDEX_EXPAND( case2bb, indices_v, src_shape_v, axis, spacing );
}

TEST_CASE("index_expand(case2bc)" * doctest::test_suite("index::expand"))
{
    INDEX_EXPAND( case2bc, indices, src_shape, axis, spacing );
    INDEX_EXPAND( case2bc, indices_a, src_shape_a, axis, spacing );
    INDEX_EXPAND( case2bc, indices_f, src_shape_f, axis, spacing );
    INDEX_EXPAND( case2bc, indices_h, src_shape_h, axis, spacing );
    INDEX_EXPAND( case2bc, indices_v, src_shape_v, axis, spacing );
}

TEST_CASE("index_expand(case2ca)" * doctest::test_suite("index::expand"))
{
    INDEX_EXPAND( case2ca, indices, src_shape, axis, spacing );
    INDEX_EXPAND( case2ca, indices_a, src_shape_a, axis, spacing );
    INDEX_EXPAND( case2ca, indices_f, src_shape_f, axis, spacing );
    INDEX_EXPAND( case2ca, indices_h, src_shape_h, axis, spacing );
    INDEX_EXPAND( case2ca, indices_v, src_shape_v, axis, spacing );
}

TEST_CASE("index_expand(case2cb)" * doctest::test_suite("index::expand"))
{
    INDEX_EXPAND( case2cb, indices, src_shape, axis, spacing );
    INDEX_EXPAND( case2cb, indices_a, src_shape_a, axis, spacing );
    INDEX_EXPAND( case2cb, indices_f, src_shape_f, axis, spacing );
    INDEX_EXPAND( case2cb, indices_h, src_shape_h, axis, spacing );
    INDEX_EXPAND( case2cb, indices_v, src_shape_v, axis, spacing );
}

TEST_CASE("index_expand(case2cc)" * doctest::test_suite("index::expand"))
{
    INDEX_EXPAND( case2cc, indices, src_shape, axis, spacing );
    INDEX_EXPAND( case2cc, indices_a, src_shape_a, axis, spacing );
    INDEX_EXPAND( case2cc, indices_f, src_shape_f, axis, spacing );
    INDEX_EXPAND( case2cc, indices_h, src_shape_h, axis, spacing );
    INDEX_EXPAND( case2cc, indices_v, src_shape_v, axis, spacing );
}

TEST_CASE("index_expand(case2cd)" * doctest::test_suite("index::expand"))
{
    INDEX_EXPAND( case2cd, indices, src_shape, axis, spacing );
    INDEX_EXPAND( case2cd, indices_a, src_shape_a, axis, spacing );
    INDEX_EXPAND( case2cd, indices_f, src_shape_f, axis, spacing );
    INDEX_EXPAND( case2cd, indices_h, src_shape_h, axis, spacing );
    INDEX_EXPAND( case2cd, indices_v, src_shape_v, axis, spacing );
}

TEST_CASE("index_expand(case2ce)" * doctest::test_suite("index::expand"))
{
    INDEX_EXPAND( case2ce, indices, src_shape, axis, spacing );
    INDEX_EXPAND( case2ce, indices_a, src_shape_a, axis, spacing );
    INDEX_EXPAND( case2ce, indices_f, src_shape_f, axis, spacing );
    INDEX_EXPAND( case2ce, indices_h, src_shape_h, axis, spacing );
    INDEX_EXPAND( case2ce, indices_v, src_shape_v, axis, spacing );
}