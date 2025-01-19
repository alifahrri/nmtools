#include "nmtools/index/reshape.hpp"
#include "nmtools/testing/data/index/reshape.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
using namespace nm::literals;

#define CONSTEXPR_SHAPE_RESHAPE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(constexpr_shape_reshape, case_name); \
    using namespace args; \
    constexpr auto result = nmtools::index::shape_reshape(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

#define SHAPE_RESHAPE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(shape_reshape, case_name); \
    using namespace args; \
    auto result = nmtools::index::shape_reshape(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("shape_reshape(case1)" * doctest::test_suite("index::shape_reshape"))
{
    SHAPE_RESHAPE_SUBCASE( case1, shape, newshape );
    SHAPE_RESHAPE_SUBCASE( case1, shape_a, newshape_a );
    SHAPE_RESHAPE_SUBCASE( case1, shape_f, newshape_f );
    SHAPE_RESHAPE_SUBCASE( case1, shape_v, newshape_v );
    SHAPE_RESHAPE_SUBCASE( case1, shape_h, newshape_h );

    SHAPE_RESHAPE_SUBCASE( case1, shape, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case1, shape_a, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case1, shape_f, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case1, shape_v, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case1, shape_h, newshape_ct );
}

TEST_CASE("shape_reshape(case2)" * doctest::test_suite("index::shape_reshape"))
{
    SHAPE_RESHAPE_SUBCASE( case2, shape, newshape );
    SHAPE_RESHAPE_SUBCASE( case2, shape_a, newshape_a );
    SHAPE_RESHAPE_SUBCASE( case2, shape_f, newshape_f );
    SHAPE_RESHAPE_SUBCASE( case2, shape_v, newshape_v );
    SHAPE_RESHAPE_SUBCASE( case2, shape_h, newshape_h );

    SHAPE_RESHAPE_SUBCASE( case2, shape, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case2, shape_a, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case2, shape_f, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case2, shape_v, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case2, shape_h, newshape_ct );
}

TEST_CASE("shape_reshape(case3)" * doctest::test_suite("index::shape_reshape"))
{
    SHAPE_RESHAPE_SUBCASE( case3, shape, newshape );
    SHAPE_RESHAPE_SUBCASE( case3, shape_a, newshape_a );
    SHAPE_RESHAPE_SUBCASE( case3, shape_f, newshape_f );
    SHAPE_RESHAPE_SUBCASE( case3, shape_v, newshape_v );
    SHAPE_RESHAPE_SUBCASE( case3, shape_h, newshape_h );

    SHAPE_RESHAPE_SUBCASE( case3, shape, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case3, shape_a, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case3, shape_f, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case3, shape_v, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case3, shape_h, newshape_ct );
}

TEST_CASE("shape_reshape(case4)" * doctest::test_suite("index::shape_reshape"))
{
    SHAPE_RESHAPE_SUBCASE( case4, shape, newshape );
    SHAPE_RESHAPE_SUBCASE( case4, shape_a, newshape_a );
    SHAPE_RESHAPE_SUBCASE( case4, shape_f, newshape_f );
    SHAPE_RESHAPE_SUBCASE( case4, shape_v, newshape_v );
    SHAPE_RESHAPE_SUBCASE( case4, shape_h, newshape_h );

    SHAPE_RESHAPE_SUBCASE( case4, shape, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case4, shape_a, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case4, shape_f, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case4, shape_v, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case4, shape_h, newshape_ct );
}

TEST_CASE("shape_reshape(case5)" * doctest::test_suite("index::shape_reshape"))
{
    SHAPE_RESHAPE_SUBCASE( case5, shape, newshape );
    SHAPE_RESHAPE_SUBCASE( case5, shape_a, newshape_a );
    SHAPE_RESHAPE_SUBCASE( case5, shape_f, newshape_f );
    SHAPE_RESHAPE_SUBCASE( case5, shape_v, newshape_v );
    SHAPE_RESHAPE_SUBCASE( case5, shape_h, newshape_h );

    SHAPE_RESHAPE_SUBCASE( case5, shape, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case5, shape_a, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case5, shape_f, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case5, shape_v, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case5, shape_h, newshape_ct );
}

TEST_CASE("shape_reshape(case6)" * doctest::test_suite("index::shape_reshape"))
{
    SHAPE_RESHAPE_SUBCASE( case6, shape, newshape );
    SHAPE_RESHAPE_SUBCASE( case6, shape_a, newshape_a );
    SHAPE_RESHAPE_SUBCASE( case6, shape_f, newshape_f );
    SHAPE_RESHAPE_SUBCASE( case6, shape_v, newshape_v );
    SHAPE_RESHAPE_SUBCASE( case6, shape_h, newshape_h );

    SHAPE_RESHAPE_SUBCASE( case6, shape, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case6, shape_a, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case6, shape_f, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case6, shape_v, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case6, shape_h, newshape_ct );
}

TEST_CASE("shape_reshape(case7)" * doctest::test_suite("index::shape_reshape"))
{
    SHAPE_RESHAPE_SUBCASE( case7, shape, newshape );
    SHAPE_RESHAPE_SUBCASE( case7, shape_a, newshape_a );
    SHAPE_RESHAPE_SUBCASE( case7, shape_f, newshape_f );
    SHAPE_RESHAPE_SUBCASE( case7, shape_v, newshape_v );
    SHAPE_RESHAPE_SUBCASE( case7, shape_h, newshape_h );

    SHAPE_RESHAPE_SUBCASE( case7, shape, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case7, shape_a, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case7, shape_f, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case7, shape_v, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case7, shape_h, newshape_ct );
}

TEST_CASE("shape_reshape(case8)" * doctest::test_suite("index::shape_reshape"))
{
    SHAPE_RESHAPE_SUBCASE( case8, shape, newshape );
    SHAPE_RESHAPE_SUBCASE( case8, shape_a, newshape_a );
    SHAPE_RESHAPE_SUBCASE( case8, shape_f, newshape_f );
    SHAPE_RESHAPE_SUBCASE( case8, shape_v, newshape_v );
    SHAPE_RESHAPE_SUBCASE( case8, shape_h, newshape_h );

    SHAPE_RESHAPE_SUBCASE( case8, shape, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case8, shape_a, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case8, shape_f, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case8, shape_v, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case8, shape_h, newshape_ct );
}

TEST_CASE("shape_reshape(case9)" * doctest::test_suite("index::shape_reshape"))
{
    SHAPE_RESHAPE_SUBCASE( case9, shape, newshape );
    SHAPE_RESHAPE_SUBCASE( case9, shape_a, newshape_a );
    SHAPE_RESHAPE_SUBCASE( case9, shape_f, newshape_f );
    SHAPE_RESHAPE_SUBCASE( case9, shape_v, newshape_v );
    SHAPE_RESHAPE_SUBCASE( case9, shape_h, newshape_h );

    SHAPE_RESHAPE_SUBCASE( case9, shape, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case9, shape_a, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case9, shape_f, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case9, shape_v, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case9, shape_h, newshape_ct );
}

TEST_CASE("shape_reshape(case10)" * doctest::test_suite("index::shape_reshape"))
{
    SHAPE_RESHAPE_SUBCASE( case10, shape, newshape );
    SHAPE_RESHAPE_SUBCASE( case10, shape_a, newshape_a );
    SHAPE_RESHAPE_SUBCASE( case10, shape_f, newshape_f );
    SHAPE_RESHAPE_SUBCASE( case10, shape_v, newshape_v );
    SHAPE_RESHAPE_SUBCASE( case10, shape_h, newshape_h );

    SHAPE_RESHAPE_SUBCASE( case10, shape, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case10, shape_a, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case10, shape_f, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case10, shape_v, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case10, shape_h, newshape_ct );
}

TEST_CASE("shape_reshape(case11)" * doctest::test_suite("index::shape_reshape"))
{
    SHAPE_RESHAPE_SUBCASE( case11, shape, newshape );
    SHAPE_RESHAPE_SUBCASE( case11, shape_a, newshape_a );
    SHAPE_RESHAPE_SUBCASE( case11, shape_f, newshape_f );
    SHAPE_RESHAPE_SUBCASE( case11, shape_v, newshape_v );
    SHAPE_RESHAPE_SUBCASE( case11, shape_h, newshape_h );

    SHAPE_RESHAPE_SUBCASE( case11, shape, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case11, shape_a, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case11, shape_f, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case11, shape_v, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case11, shape_h, newshape_ct );
}

TEST_CASE("shape_reshape(case12)" * doctest::test_suite("index::shape_reshape"))
{
    SHAPE_RESHAPE_SUBCASE( case12, shape, newshape );
    SHAPE_RESHAPE_SUBCASE( case12, shape_a, newshape_a );
    SHAPE_RESHAPE_SUBCASE( case12, shape_f, newshape_f );
    SHAPE_RESHAPE_SUBCASE( case12, shape_v, newshape_v );
    SHAPE_RESHAPE_SUBCASE( case12, shape_h, newshape_h );

    SHAPE_RESHAPE_SUBCASE( case12, shape, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case12, shape_a, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case12, shape_f, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case12, shape_v, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case12, shape_h, newshape_ct );
}

TEST_CASE("shape_reshape(case1)" * doctest::test_suite("index::constexpr_shape_reshape"))
{
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case1, shape, newshape );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case1, shape_a, newshape_a );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case1, shape_f, newshape_f );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case1, shape_h, newshape_h );

    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case1, shape_ct, newshape_ct );

    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case1, shape, newshape_ct );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case1, shape_a, newshape_ct );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case1, shape_f, newshape_ct );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case1, shape_h, newshape_ct );
}

TEST_CASE("shape_reshape(case2)" * doctest::test_suite("index::constexpr_shape_reshape"))
{
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case2, shape, newshape );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case2, shape_a, newshape_a );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case2, shape_f, newshape_f );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case2, shape_h, newshape_h );

    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case2, shape_ct, newshape_ct );

    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case2, shape, newshape_ct );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case2, shape_a, newshape_ct );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case2, shape_f, newshape_ct );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case2, shape_h, newshape_ct );
}

TEST_CASE("shape_reshape(case3)" * doctest::test_suite("index::constexpr_shape_reshape"))
{
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case3, shape, newshape );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case3, shape_a, newshape_a );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case3, shape_f, newshape_f );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case3, shape_h, newshape_h );

    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case3, shape_ct, newshape_ct );

    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case3, shape, newshape_ct );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case3, shape_a, newshape_ct );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case3, shape_f, newshape_ct );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case3, shape_h, newshape_ct );
}

TEST_CASE("shape_reshape(case4)" * doctest::test_suite("index::constexpr_shape_reshape"))
{
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case4, shape, newshape );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case4, shape_a, newshape_a );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case4, shape_f, newshape_f );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case4, shape_h, newshape_h );

    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case4, shape_ct, newshape_ct );

    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case4, shape, newshape_ct );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case4, shape_a, newshape_ct );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case4, shape_f, newshape_ct );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case4, shape_h, newshape_ct );
}

TEST_CASE("shape_reshape(case5)" * doctest::test_suite("index::constexpr_shape_reshape"))
{
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case5, shape, newshape );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case5, shape_a, newshape_a );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case5, shape_f, newshape_f );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case5, shape_h, newshape_h );

    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case5, shape_ct, newshape_ct );

    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case5, shape, newshape_ct );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case5, shape_a, newshape_ct );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case5, shape_f, newshape_ct );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case5, shape_h, newshape_ct );
}

TEST_CASE("shape_reshape(case6)" * doctest::test_suite("index::constexpr_shape_reshape"))
{
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case6, shape, newshape );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case6, shape_a, newshape_a );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case6, shape_f, newshape_f );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case6, shape_h, newshape_h );

    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case6, shape_ct, newshape_ct );

    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case6, shape, newshape_ct );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case6, shape_a, newshape_ct );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case6, shape_f, newshape_ct );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case6, shape_h, newshape_ct );
}

TEST_CASE("shape_reshape(case7)" * doctest::test_suite("index::constexpr_shape_reshape"))
{
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case7, shape, newshape );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case7, shape_a, newshape_a );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case7, shape_f, newshape_f );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case7, shape_h, newshape_h );

    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case7, shape_ct, newshape_ct );

    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case7, shape, newshape_ct );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case7, shape_a, newshape_ct );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case7, shape_f, newshape_ct );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case7, shape_h, newshape_ct );
}

TEST_CASE("shape_reshape(case8)" * doctest::test_suite("index::constexpr_shape_reshape"))
{
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case8, shape, newshape );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case8, shape_a, newshape_a );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case8, shape_f, newshape_f );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case8, shape_h, newshape_h );

    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case8, shape_ct, newshape_ct );

    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case8, shape, newshape_ct );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case8, shape_a, newshape_ct );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case8, shape_f, newshape_ct );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case8, shape_h, newshape_ct );
}

TEST_CASE("shape_reshape(case9)" * doctest::test_suite("index::constexpr_shape_reshape"))
{
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case9, shape, newshape );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case9, shape_a, newshape_a );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case9, shape_f, newshape_f );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case9, shape_h, newshape_h );

    // triggers compile time error, as it should be
    // CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case9, shape_ct, newshape_ct );

    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case9, shape, newshape_ct );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case9, shape_a, newshape_ct );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case9, shape_f, newshape_ct );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case9, shape_h, newshape_ct );
}

TEST_CASE("shape_reshape(case10)" * doctest::test_suite("index::constexpr_shape_reshape"))
{
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case10, shape, newshape );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case10, shape_a, newshape_a );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case10, shape_f, newshape_f );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case10, shape_h, newshape_h );

    // CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case10, shape_ct, newshape_ct );

    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case10, shape, newshape_ct );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case10, shape_a, newshape_ct );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case10, shape_f, newshape_ct );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case10, shape_h, newshape_ct );
}

TEST_CASE("shape_reshape(case11)" * doctest::test_suite("index::constexpr_shape_reshape"))
{
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case11, shape, newshape );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case11, shape_a, newshape_a );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case11, shape_f, newshape_f );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case11, shape_h, newshape_h );

    // CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case11, shape_ct, newshape_ct );

    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case11, shape, newshape_ct );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case11, shape_a, newshape_ct );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case11, shape_f, newshape_ct );
    CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case11, shape_h, newshape_ct );
}

// TEST_CASE("shape_reshape(case12)" * doctest::test_suite("index::constexpr_shape_reshape"))
// {
//     CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case12, shape, newshape );
//     CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case12, shape_a, newshape_a );
//     CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case12, shape_f, newshape_f );
//     CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case12, shape_h, newshape_h );

//     CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case12, shape_ct, newshape_ct );

//     CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case12, shape, newshape_ct );
//     CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case12, shape_a, newshape_ct );
//     CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case12, shape_f, newshape_ct );
//     CONSTEXPR_SHAPE_RESHAPE_SUBCASE( case12, shape_h, newshape_ct );
// }