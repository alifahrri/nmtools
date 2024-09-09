#include "nmtools/array/view/tril.hpp"
#include "nmtools/testing/data/index/tril.hpp"
#include "nmtools/testing/doctest.hpp"

#define SHAPE_TRIL_SUBCASE( case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index,shape_tril,case_name); \
    using namespace args; \
    auto result = nmtools::index::shape_tril(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

#define TRIL_SUBCASE( case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index,tril,case_name); \
    using namespace args; \
    auto result = nmtools::index::tril(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("shape_tril(case1)" * doctest::test_suite("index::shape_tril"))
{
    SHAPE_TRIL_SUBCASE( case1, src_shape );
    SHAPE_TRIL_SUBCASE( case1, src_shape_a );
    SHAPE_TRIL_SUBCASE( case1, src_shape_f );
    SHAPE_TRIL_SUBCASE( case1, src_shape_h );
    SHAPE_TRIL_SUBCASE( case1, src_shape_v );

    SHAPE_TRIL_SUBCASE( case1, src_shape_ct );
}

TEST_CASE("shape_tril(case2)" * doctest::test_suite("index::shape_tril"))
{
    SHAPE_TRIL_SUBCASE( case2, src_shape );
    SHAPE_TRIL_SUBCASE( case2, src_shape_a );
    SHAPE_TRIL_SUBCASE( case2, src_shape_f );
    SHAPE_TRIL_SUBCASE( case2, src_shape_h );
    SHAPE_TRIL_SUBCASE( case2, src_shape_v );

    SHAPE_TRIL_SUBCASE( case2, src_shape_ct );
}

TEST_CASE("shape_tril(case3)" * doctest::test_suite("index::shape_tril"))
{
    SHAPE_TRIL_SUBCASE( case3, src_shape );
    SHAPE_TRIL_SUBCASE( case3, src_shape_a );
    SHAPE_TRIL_SUBCASE( case3, src_shape_f );
    SHAPE_TRIL_SUBCASE( case3, src_shape_h );
    SHAPE_TRIL_SUBCASE( case3, src_shape_v );

    SHAPE_TRIL_SUBCASE( case3, src_shape_ct );
}

TEST_CASE("tril(case1a1)" * doctest::test_suite("index::tril"))
{
    TRIL_SUBCASE( case1a1, src_shape, indices, k );
    TRIL_SUBCASE( case1a1, src_shape_a, indices_a, k );
    TRIL_SUBCASE( case1a1, src_shape_f, indices_f, k );
    TRIL_SUBCASE( case1a1, src_shape_h, indices_h, k );
    TRIL_SUBCASE( case1a1, src_shape_v, indices_v, k );

    TRIL_SUBCASE( case1a1, src_shape_ct, indices, k_ct );
}

TEST_CASE("tril(case1a2)" * doctest::test_suite("index::tril"))
{
    TRIL_SUBCASE( case1a2, src_shape, indices, k );
    TRIL_SUBCASE( case1a2, src_shape_a, indices_a, k );
    TRIL_SUBCASE( case1a2, src_shape_f, indices_f, k );
    TRIL_SUBCASE( case1a2, src_shape_h, indices_h, k );
    TRIL_SUBCASE( case1a2, src_shape_v, indices_v, k );

    TRIL_SUBCASE( case1a2, src_shape_ct, indices, k_ct );
}

TEST_CASE("tril(case1a3)" * doctest::test_suite("index::tril"))
{
    TRIL_SUBCASE( case1a3, src_shape, indices, k );
    TRIL_SUBCASE( case1a3, src_shape_a, indices_a, k );
    TRIL_SUBCASE( case1a3, src_shape_f, indices_f, k );
    TRIL_SUBCASE( case1a3, src_shape_h, indices_h, k );
    TRIL_SUBCASE( case1a3, src_shape_v, indices_v, k );

    TRIL_SUBCASE( case1a3, src_shape_ct, indices, k_ct );
}

TEST_CASE("tril(case1a4)" * doctest::test_suite("index::tril"))
{
    TRIL_SUBCASE( case1a4, src_shape, indices, k );
    TRIL_SUBCASE( case1a4, src_shape_a, indices_a, k );
    TRIL_SUBCASE( case1a4, src_shape_f, indices_f, k );
    TRIL_SUBCASE( case1a4, src_shape_h, indices_h, k );
    TRIL_SUBCASE( case1a4, src_shape_v, indices_v, k );

    TRIL_SUBCASE( case1a4, src_shape_ct, indices, k_ct );
}

TEST_CASE("tril(case1a5)" * doctest::test_suite("index::tril"))
{
    TRIL_SUBCASE( case1a5, src_shape, indices, k );
    TRIL_SUBCASE( case1a5, src_shape_a, indices_a, k );
    TRIL_SUBCASE( case1a5, src_shape_f, indices_f, k );
    TRIL_SUBCASE( case1a5, src_shape_h, indices_h, k );
    TRIL_SUBCASE( case1a5, src_shape_v, indices_v, k );

    TRIL_SUBCASE( case1a5, src_shape_ct, indices, k_ct );
}

TEST_CASE("tril(case1a6)" * doctest::test_suite("index::tril"))
{
    TRIL_SUBCASE( case1a6, src_shape, indices, k );
    TRIL_SUBCASE( case1a6, src_shape_a, indices_a, k );
    TRIL_SUBCASE( case1a6, src_shape_f, indices_f, k );
    TRIL_SUBCASE( case1a6, src_shape_h, indices_h, k );
    TRIL_SUBCASE( case1a6, src_shape_v, indices_v, k );

    TRIL_SUBCASE( case1a6, src_shape_ct, indices, k_ct );
}

TEST_CASE("tril(case1a7)" * doctest::test_suite("index::tril"))
{
    TRIL_SUBCASE( case1a7, src_shape, indices, k );
    TRIL_SUBCASE( case1a7, src_shape_a, indices_a, k );
    TRIL_SUBCASE( case1a7, src_shape_f, indices_f, k );
    TRIL_SUBCASE( case1a7, src_shape_h, indices_h, k );
    TRIL_SUBCASE( case1a7, src_shape_v, indices_v, k );

    TRIL_SUBCASE( case1a7, src_shape_ct, indices, k_ct );
}

TEST_CASE("tril(case1a8" * doctest::test_suite("index::tril"))
{
    TRIL_SUBCASE( case1a8, src_shape, indices, k );
    TRIL_SUBCASE( case1a8, src_shape_a, indices_a, k );
    TRIL_SUBCASE( case1a8, src_shape_f, indices_f, k );
    TRIL_SUBCASE( case1a8, src_shape_h, indices_h, k );
    TRIL_SUBCASE( case1a8, src_shape_v, indices_v, k );

    TRIL_SUBCASE( case1a8, src_shape_ct, indices, k_ct );
}

TEST_CASE("tril(case1a9)" * doctest::test_suite("index::tril"))
{
    TRIL_SUBCASE( case1a9, src_shape, indices, k );
    TRIL_SUBCASE( case1a9, src_shape_a, indices_a, k );
    TRIL_SUBCASE( case1a9, src_shape_f, indices_f, k );
    TRIL_SUBCASE( case1a9, src_shape_h, indices_h, k );
    TRIL_SUBCASE( case1a9, src_shape_v, indices_v, k );

    TRIL_SUBCASE( case1a9, src_shape_ct, indices, k_ct );
}

TEST_CASE("tril(case1a10)" * doctest::test_suite("index::tril"))
{
    TRIL_SUBCASE( case1a10, src_shape, indices, k );
    TRIL_SUBCASE( case1a10, src_shape_a, indices_a, k );
    TRIL_SUBCASE( case1a10, src_shape_f, indices_f, k );
    TRIL_SUBCASE( case1a10, src_shape_h, indices_h, k );
    TRIL_SUBCASE( case1a10, src_shape_v, indices_v, k );

    TRIL_SUBCASE( case1a10, src_shape_ct, indices, k_ct );
}

TEST_CASE("tril(case1a11)" * doctest::test_suite("index::tril"))
{
    TRIL_SUBCASE( case1a11, src_shape, indices, k );
    TRIL_SUBCASE( case1a11, src_shape_a, indices_a, k );
    TRIL_SUBCASE( case1a11, src_shape_f, indices_f, k );
    TRIL_SUBCASE( case1a11, src_shape_h, indices_h, k );
    TRIL_SUBCASE( case1a11, src_shape_v, indices_v, k );

    TRIL_SUBCASE( case1a11, src_shape_ct, indices, k_ct );
}

TEST_CASE("tril(case1a12)" * doctest::test_suite("index::tril"))
{
    TRIL_SUBCASE( case1a12, src_shape, indices, k );
    TRIL_SUBCASE( case1a12, src_shape_a, indices_a, k );
    TRIL_SUBCASE( case1a12, src_shape_f, indices_f, k );
    TRIL_SUBCASE( case1a12, src_shape_h, indices_h, k );
    TRIL_SUBCASE( case1a12, src_shape_v, indices_v, k );

    TRIL_SUBCASE( case1a12, src_shape_ct, indices, k_ct );
}

TEST_CASE("tril(case1b1)" * doctest::test_suite("index::tril"))
{
    TRIL_SUBCASE( case1b1, src_shape, indices, k );
    TRIL_SUBCASE( case1b1, src_shape_a, indices_a, k );
    TRIL_SUBCASE( case1b1, src_shape_f, indices_f, k );
    TRIL_SUBCASE( case1b1, src_shape_h, indices_h, k );
    TRIL_SUBCASE( case1b1, src_shape_v, indices_v, k );

    TRIL_SUBCASE( case1b1, src_shape_ct, indices, k_ct );
}

TEST_CASE("tril(case1b2)" * doctest::test_suite("index::tril"))
{
    TRIL_SUBCASE( case1b2, src_shape, indices, k );
    TRIL_SUBCASE( case1b2, src_shape_a, indices_a, k );
    TRIL_SUBCASE( case1b2, src_shape_f, indices_f, k );
    TRIL_SUBCASE( case1b2, src_shape_h, indices_h, k );
    TRIL_SUBCASE( case1b2, src_shape_v, indices_v, k );

    TRIL_SUBCASE( case1b2, src_shape_ct, indices, k_ct );
}

TEST_CASE("tril(case1b3)" * doctest::test_suite("index::tril"))
{
    TRIL_SUBCASE( case1b3, src_shape, indices, k );
    TRIL_SUBCASE( case1b3, src_shape_a, indices_a, k );
    TRIL_SUBCASE( case1b3, src_shape_f, indices_f, k );
    TRIL_SUBCASE( case1b3, src_shape_h, indices_h, k );
    TRIL_SUBCASE( case1b3, src_shape_v, indices_v, k );

    TRIL_SUBCASE( case1b3, src_shape_ct, indices, k_ct );
}

TEST_CASE("tril(case1b4)" * doctest::test_suite("index::tril"))
{
    TRIL_SUBCASE( case1b4, src_shape, indices, k );
    TRIL_SUBCASE( case1b4, src_shape_a, indices_a, k );
    TRIL_SUBCASE( case1b4, src_shape_f, indices_f, k );
    TRIL_SUBCASE( case1b4, src_shape_h, indices_h, k );
    TRIL_SUBCASE( case1b4, src_shape_v, indices_v, k );

    TRIL_SUBCASE( case1b4, src_shape_ct, indices, k_ct );
}

TEST_CASE("tril(case1b5)" * doctest::test_suite("index::tril"))
{
    TRIL_SUBCASE( case1b5, src_shape, indices, k );
    TRIL_SUBCASE( case1b5, src_shape_a, indices_a, k );
    TRIL_SUBCASE( case1b5, src_shape_f, indices_f, k );
    TRIL_SUBCASE( case1b5, src_shape_h, indices_h, k );
    TRIL_SUBCASE( case1b5, src_shape_v, indices_v, k );

    TRIL_SUBCASE( case1b5, src_shape_ct, indices, k_ct );
}

TEST_CASE("tril(case1b6)" * doctest::test_suite("index::tril"))
{
    TRIL_SUBCASE( case1b6, src_shape, indices, k );
    TRIL_SUBCASE( case1b6, src_shape_a, indices_a, k );
    TRIL_SUBCASE( case1b6, src_shape_f, indices_f, k );
    TRIL_SUBCASE( case1b6, src_shape_h, indices_h, k );
    TRIL_SUBCASE( case1b6, src_shape_v, indices_v, k );

    TRIL_SUBCASE( case1b6, src_shape_ct, indices, k_ct );
}

TEST_CASE("tril(case1b7)" * doctest::test_suite("index::tril"))
{
    TRIL_SUBCASE( case1b7, src_shape, indices, k );
    TRIL_SUBCASE( case1b7, src_shape_a, indices_a, k );
    TRIL_SUBCASE( case1b7, src_shape_f, indices_f, k );
    TRIL_SUBCASE( case1b7, src_shape_h, indices_h, k );
    TRIL_SUBCASE( case1b7, src_shape_v, indices_v, k );

    TRIL_SUBCASE( case1b7, src_shape_ct, indices, k_ct );
}

TEST_CASE("tril(case1b8)" * doctest::test_suite("index::tril"))
{
    TRIL_SUBCASE( case1b8, src_shape, indices, k );
    TRIL_SUBCASE( case1b8, src_shape_a, indices_a, k );
    TRIL_SUBCASE( case1b8, src_shape_f, indices_f, k );
    TRIL_SUBCASE( case1b8, src_shape_h, indices_h, k );
    TRIL_SUBCASE( case1b8, src_shape_v, indices_v, k );

    TRIL_SUBCASE( case1b8, src_shape_ct, indices, k_ct );
}

TEST_CASE("tril(case1b9)" * doctest::test_suite("index::tril"))
{
    TRIL_SUBCASE( case1b9, src_shape, indices, k );
    TRIL_SUBCASE( case1b9, src_shape_a, indices_a, k );
    TRIL_SUBCASE( case1b9, src_shape_f, indices_f, k );
    TRIL_SUBCASE( case1b9, src_shape_h, indices_h, k );
    TRIL_SUBCASE( case1b9, src_shape_v, indices_v, k );

    TRIL_SUBCASE( case1b9, src_shape_ct, indices, k_ct );
}

TEST_CASE("tril(case1b10)" * doctest::test_suite("index::tril"))
{
    TRIL_SUBCASE( case1b10, src_shape, indices, k );
    TRIL_SUBCASE( case1b10, src_shape_a, indices_a, k );
    TRIL_SUBCASE( case1b10, src_shape_f, indices_f, k );
    TRIL_SUBCASE( case1b10, src_shape_h, indices_h, k );
    TRIL_SUBCASE( case1b10, src_shape_v, indices_v, k );

    TRIL_SUBCASE( case1b10, src_shape_ct, indices, k_ct );
}

TEST_CASE("tril(case1b11)" * doctest::test_suite("index::tril"))
{
    TRIL_SUBCASE( case1b11, src_shape, indices, k );
    TRIL_SUBCASE( case1b11, src_shape_a, indices_a, k );
    TRIL_SUBCASE( case1b11, src_shape_f, indices_f, k );
    TRIL_SUBCASE( case1b11, src_shape_h, indices_h, k );
    TRIL_SUBCASE( case1b11, src_shape_v, indices_v, k );

    TRIL_SUBCASE( case1b11, src_shape_ct, indices, k_ct );
}

TEST_CASE("tril(case1b12)" * doctest::test_suite("index::tril"))
{
    TRIL_SUBCASE( case1b12, src_shape, indices, k );
    TRIL_SUBCASE( case1b12, src_shape_a, indices_a, k );
    TRIL_SUBCASE( case1b12, src_shape_f, indices_f, k );
    TRIL_SUBCASE( case1b12, src_shape_h, indices_h, k );
    TRIL_SUBCASE( case1b12, src_shape_v, indices_v, k );

    TRIL_SUBCASE( case1b12, src_shape_ct, indices, k_ct );
}

TEST_CASE("tril(case3a1)" * doctest::test_suite("index::tril"))
{
    TRIL_SUBCASE( case3a1, src_shape, indices, k );
    TRIL_SUBCASE( case3a1, src_shape_a, indices_a, k );
    TRIL_SUBCASE( case3a1, src_shape_f, indices_f, k );
    TRIL_SUBCASE( case3a1, src_shape_h, indices_h, k );
    TRIL_SUBCASE( case3a1, src_shape_v, indices_v, k );

    TRIL_SUBCASE( case3a1, src_shape_ct, indices, k_ct );
}

TEST_CASE("tril(case3a2)" * doctest::test_suite("index::tril"))
{
    TRIL_SUBCASE( case3a2, src_shape, indices, k );
    TRIL_SUBCASE( case3a2, src_shape_a, indices_a, k );
    TRIL_SUBCASE( case3a2, src_shape_f, indices_f, k );
    TRIL_SUBCASE( case3a2, src_shape_h, indices_h, k );
    TRIL_SUBCASE( case3a2, src_shape_v, indices_v, k );

    TRIL_SUBCASE( case3a2, src_shape_ct, indices, k_ct );
}

TEST_CASE("tril(case3a3)" * doctest::test_suite("index::tril"))
{
    TRIL_SUBCASE( case3a3, src_shape, indices, k );
    TRIL_SUBCASE( case3a3, src_shape_a, indices_a, k );
    TRIL_SUBCASE( case3a3, src_shape_f, indices_f, k );
    TRIL_SUBCASE( case3a3, src_shape_h, indices_h, k );
    TRIL_SUBCASE( case3a3, src_shape_v, indices_v, k );

    TRIL_SUBCASE( case3a3, src_shape_ct, indices, k_ct );
}

TEST_CASE("tril(case3a4)" * doctest::test_suite("index::tril"))
{
    TRIL_SUBCASE( case3a4, src_shape, indices, k );
    TRIL_SUBCASE( case3a4, src_shape_a, indices_a, k );
    TRIL_SUBCASE( case3a4, src_shape_f, indices_f, k );
    TRIL_SUBCASE( case3a4, src_shape_h, indices_h, k );
    TRIL_SUBCASE( case3a4, src_shape_v, indices_v, k );

    TRIL_SUBCASE( case3a4, src_shape_ct, indices, k_ct );
}

TEST_CASE("tril(case3a5)" * doctest::test_suite("index::tril"))
{
    TRIL_SUBCASE( case3a5, src_shape, indices, k );
    TRIL_SUBCASE( case3a5, src_shape_a, indices_a, k );
    TRIL_SUBCASE( case3a5, src_shape_f, indices_f, k );
    TRIL_SUBCASE( case3a5, src_shape_h, indices_h, k );
    TRIL_SUBCASE( case3a5, src_shape_v, indices_v, k );

    TRIL_SUBCASE( case3a5, src_shape_ct, indices, k_ct );
}

TEST_CASE("tril(case3a6)" * doctest::test_suite("index::tril"))
{
    TRIL_SUBCASE( case3a6, src_shape, indices, k );
    TRIL_SUBCASE( case3a6, src_shape_a, indices_a, k );
    TRIL_SUBCASE( case3a6, src_shape_f, indices_f, k );
    TRIL_SUBCASE( case3a6, src_shape_h, indices_h, k );
    TRIL_SUBCASE( case3a6, src_shape_v, indices_v, k );

    TRIL_SUBCASE( case3a6, src_shape_ct, indices, k_ct );
}

TEST_CASE("tril(case3a7)" * doctest::test_suite("index::tril"))
{
    TRIL_SUBCASE( case3a7, src_shape, indices, k );
    TRIL_SUBCASE( case3a7, src_shape_a, indices_a, k );
    TRIL_SUBCASE( case3a7, src_shape_f, indices_f, k );
    TRIL_SUBCASE( case3a7, src_shape_h, indices_h, k );
    TRIL_SUBCASE( case3a7, src_shape_v, indices_v, k );

    TRIL_SUBCASE( case3a7, src_shape_ct, indices, k_ct );
}

TEST_CASE("tril(case3a8)" * doctest::test_suite("index::tril"))
{
    TRIL_SUBCASE( case3a8, src_shape, indices, k );
    TRIL_SUBCASE( case3a8, src_shape_a, indices_a, k );
    TRIL_SUBCASE( case3a8, src_shape_f, indices_f, k );
    TRIL_SUBCASE( case3a8, src_shape_h, indices_h, k );
    TRIL_SUBCASE( case3a8, src_shape_v, indices_v, k );

    TRIL_SUBCASE( case3a8, src_shape_ct, indices, k_ct );
}

TEST_CASE("tril(case3a9)" * doctest::test_suite("index::tril"))
{
    TRIL_SUBCASE( case3a9, src_shape, indices, k );
    TRIL_SUBCASE( case3a9, src_shape_a, indices_a, k );
    TRIL_SUBCASE( case3a9, src_shape_f, indices_f, k );
    TRIL_SUBCASE( case3a9, src_shape_h, indices_h, k );
    TRIL_SUBCASE( case3a9, src_shape_v, indices_v, k );

    TRIL_SUBCASE( case3a9, src_shape_ct, indices, k_ct );
}