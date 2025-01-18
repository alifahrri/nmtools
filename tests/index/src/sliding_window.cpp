#include "nmtools/array/sliding_window.hpp"
#include "nmtools/testing/data/index/sliding_window.hpp"
#include "nmtools/testing/doctest.hpp"

#define SHAPE_SLIDING_WINDOW_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index, shape_sliding_window, case_name); \
    using namespace args; \
    auto result = nmtools::index::shape_sliding_window(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL_MSG_ATTRIBUTES( result, expect::dst_shape, __VA_ARGS__ ); \
}

#define SLIDING_WINDOW_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index, sliding_window, case_name); \
    using namespace args; \
    auto result = nmtools::index::sliding_window(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL_MSG_ATTRIBUTES( result, expect::expected, __VA_ARGS__ ); \
}

TEST_CASE("shape_sliding_window(case1)" * doctest::test_suite("index::shape_sliding_window"))
{
    SHAPE_SLIDING_WINDOW_SUBCASE( case1, src_shape, window_shape );
    SHAPE_SLIDING_WINDOW_SUBCASE( case1, src_shape_a, window_shape );
    SHAPE_SLIDING_WINDOW_SUBCASE( case1, src_shape_v, window_shape );
    SHAPE_SLIDING_WINDOW_SUBCASE( case1, src_shape_f, window_shape );
    SHAPE_SLIDING_WINDOW_SUBCASE( case1, src_shape_h, window_shape );

    SHAPE_SLIDING_WINDOW_SUBCASE( case1, src_shape_ct, window_shape_ct );
    SHAPE_SLIDING_WINDOW_SUBCASE( case1, src_shape_cl, window_shape_cl );
}

TEST_CASE("shape_sliding_window(case2)" * doctest::test_suite("index::shape_sliding_window"))
{
    SHAPE_SLIDING_WINDOW_SUBCASE( case2, src_shape, window_shape );
    SHAPE_SLIDING_WINDOW_SUBCASE( case2, src_shape_a, window_shape_a );
    SHAPE_SLIDING_WINDOW_SUBCASE( case2, src_shape_v, window_shape_v );
    SHAPE_SLIDING_WINDOW_SUBCASE( case2, src_shape_f, window_shape_f );
    SHAPE_SLIDING_WINDOW_SUBCASE( case2, src_shape_h, window_shape_h );

    SHAPE_SLIDING_WINDOW_SUBCASE( case2, src_shape_ct, window_shape_ct );
    SHAPE_SLIDING_WINDOW_SUBCASE( case2, src_shape_cl, window_shape_cl );
}

TEST_CASE("shape_sliding_window(case3)" * doctest::test_suite("index::shape_sliding_window"))
{
    SHAPE_SLIDING_WINDOW_SUBCASE( case3, src_shape, window_shape, axis );
    SHAPE_SLIDING_WINDOW_SUBCASE( case3, src_shape_a, window_shape, axis );
    SHAPE_SLIDING_WINDOW_SUBCASE( case3, src_shape_v, window_shape, axis );
    SHAPE_SLIDING_WINDOW_SUBCASE( case3, src_shape_f, window_shape, axis );
    SHAPE_SLIDING_WINDOW_SUBCASE( case3, src_shape_h, window_shape, axis );

    SHAPE_SLIDING_WINDOW_SUBCASE( case3, src_shape_ct, window_shape_ct, axis_ct );
    SHAPE_SLIDING_WINDOW_SUBCASE( case3, src_shape_cl, window_shape_cl, axis_cl );
}

TEST_CASE("shape_sliding_window(case4)" * doctest::test_suite("index::shape_sliding_window"))
{
    SHAPE_SLIDING_WINDOW_SUBCASE( case4, src_shape, window_shape, axis );
    SHAPE_SLIDING_WINDOW_SUBCASE( case4, src_shape_a, window_shape_a, axis_a );
    SHAPE_SLIDING_WINDOW_SUBCASE( case4, src_shape_v, window_shape_v, axis_v );
    SHAPE_SLIDING_WINDOW_SUBCASE( case4, src_shape_f, window_shape_f, axis_f );
    SHAPE_SLIDING_WINDOW_SUBCASE( case4, src_shape_h, window_shape_h, axis_h );

    SHAPE_SLIDING_WINDOW_SUBCASE( case4, src_shape_ct, window_shape_ct, axis_ct );
    SHAPE_SLIDING_WINDOW_SUBCASE( case4, src_shape_cl, window_shape_cl, axis_cl );
}

TEST_CASE("shape_sliding_window(case5)" * doctest::test_suite("index::shape_sliding_window"))
{
    SHAPE_SLIDING_WINDOW_SUBCASE( case5, src_shape, window_shape );
    SHAPE_SLIDING_WINDOW_SUBCASE( case5, src_shape_a, window_shape_a );
    SHAPE_SLIDING_WINDOW_SUBCASE( case5, src_shape_v, window_shape_v );
    SHAPE_SLIDING_WINDOW_SUBCASE( case5, src_shape_f, window_shape_f );
    SHAPE_SLIDING_WINDOW_SUBCASE( case5, src_shape_h, window_shape_h );

    SHAPE_SLIDING_WINDOW_SUBCASE( case5, src_shape_ct, window_shape_ct );
    SHAPE_SLIDING_WINDOW_SUBCASE( case5, src_shape_cl, window_shape_cl );
}

TEST_CASE("shape_sliding_window(case6)" * doctest::test_suite("index::shape_sliding_window"))
{
    SHAPE_SLIDING_WINDOW_SUBCASE( case6, src_shape, window_shape, axis );
    SHAPE_SLIDING_WINDOW_SUBCASE( case6, src_shape_a, window_shape_a, axis_a );
    SHAPE_SLIDING_WINDOW_SUBCASE( case6, src_shape_v, window_shape_v, axis_v );
    SHAPE_SLIDING_WINDOW_SUBCASE( case6, src_shape_f, window_shape_f, axis_f );
    SHAPE_SLIDING_WINDOW_SUBCASE( case6, src_shape_h, window_shape_h, axis_h );

    SHAPE_SLIDING_WINDOW_SUBCASE( case6, src_shape_ct, window_shape_ct, axis_ct );
    SHAPE_SLIDING_WINDOW_SUBCASE( case6, src_shape_cl, window_shape_cl, axis_cl );
}

TEST_CASE("shape_sliding_window(case7)" * doctest::test_suite("index::shape_sliding_window"))
{
    SHAPE_SLIDING_WINDOW_SUBCASE( case7, src_shape, window_shape, axis );
    SHAPE_SLIDING_WINDOW_SUBCASE( case7, src_shape_a, window_shape_a, axis_a );
    SHAPE_SLIDING_WINDOW_SUBCASE( case7, src_shape_v, window_shape_v, axis_v );
    SHAPE_SLIDING_WINDOW_SUBCASE( case7, src_shape_f, window_shape_f, axis_f );
    SHAPE_SLIDING_WINDOW_SUBCASE( case7, src_shape_h, window_shape_h, axis_h );

    SHAPE_SLIDING_WINDOW_SUBCASE( case7, src_shape_ct, window_shape_ct, axis_ct );
    SHAPE_SLIDING_WINDOW_SUBCASE( case7, src_shape_cl, window_shape_cl, axis_cl );
}

TEST_CASE("shape_sliding_window(case8)" * doctest::test_suite("index::shape_sliding_window"))
{
    SHAPE_SLIDING_WINDOW_SUBCASE( case8, src_shape, window_shape, axis );
    SHAPE_SLIDING_WINDOW_SUBCASE( case8, src_shape_a, window_shape_a, axis_a );
    SHAPE_SLIDING_WINDOW_SUBCASE( case8, src_shape_v, window_shape_v, axis_v );
    SHAPE_SLIDING_WINDOW_SUBCASE( case8, src_shape_f, window_shape_f, axis_f );
    SHAPE_SLIDING_WINDOW_SUBCASE( case8, src_shape_h, window_shape_h, axis_h );

    SHAPE_SLIDING_WINDOW_SUBCASE( case8, src_shape_ct, window_shape_ct, axis_ct );
    SHAPE_SLIDING_WINDOW_SUBCASE( case8, src_shape_cl, window_shape_cl, axis_cl );
}

TEST_CASE("shape_sliding_window(case9)" * doctest::test_suite("index::shape_sliding_window"))
{
    SHAPE_SLIDING_WINDOW_SUBCASE( case9, src_shape, window_shape );
    SHAPE_SLIDING_WINDOW_SUBCASE( case9, src_shape_a, window_shape_a );
    SHAPE_SLIDING_WINDOW_SUBCASE( case9, src_shape_v, window_shape_v );
    SHAPE_SLIDING_WINDOW_SUBCASE( case9, src_shape_f, window_shape_f );
    SHAPE_SLIDING_WINDOW_SUBCASE( case9, src_shape_h, window_shape_h );

    SHAPE_SLIDING_WINDOW_SUBCASE( case9, src_shape_ct, window_shape_ct );
    SHAPE_SLIDING_WINDOW_SUBCASE( case9, src_shape_cl, window_shape_cl );
}

TEST_CASE("shape_sliding_window(case10)" * doctest::test_suite("index::shape_sliding_window"))
{
    SHAPE_SLIDING_WINDOW_SUBCASE( case10, src_shape, window_shape, axis );
    SHAPE_SLIDING_WINDOW_SUBCASE( case10, src_shape_a, window_shape_a, axis_a );
    SHAPE_SLIDING_WINDOW_SUBCASE( case10, src_shape_v, window_shape_v, axis_v );
    SHAPE_SLIDING_WINDOW_SUBCASE( case10, src_shape_f, window_shape_f, axis_f );
    SHAPE_SLIDING_WINDOW_SUBCASE( case10, src_shape_h, window_shape_h, axis_h );

    SHAPE_SLIDING_WINDOW_SUBCASE( case10, src_shape_ct, window_shape_ct, axis_ct );
    SHAPE_SLIDING_WINDOW_SUBCASE( case10, src_shape_cl, window_shape_cl, axis_cl );
}

TEST_CASE("sliding_window(case1a)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case1a, indices, dst_shape, src_shape, window_shape );
    SLIDING_WINDOW_SUBCASE( case1a, indices_a, dst_shape_a, src_shape_a, window_shape_a );
    SLIDING_WINDOW_SUBCASE( case1a, indices_v, dst_shape_v, src_shape_v, window_shape_v );
    SLIDING_WINDOW_SUBCASE( case1a, indices_f, dst_shape_f, src_shape_f, window_shape_f );
    SLIDING_WINDOW_SUBCASE( case1a, indices_h, dst_shape_h, src_shape_h, window_shape_h );
}

TEST_CASE("sliding_window(case1b)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case1b, indices, dst_shape, src_shape, window_shape );
    SLIDING_WINDOW_SUBCASE( case1b, indices_a, dst_shape_a, src_shape_a, window_shape_a );
    SLIDING_WINDOW_SUBCASE( case1b, indices_v, dst_shape_v, src_shape_v, window_shape_v );
    SLIDING_WINDOW_SUBCASE( case1b, indices_f, dst_shape_f, src_shape_f, window_shape_f );
    SLIDING_WINDOW_SUBCASE( case1b, indices_h, dst_shape_h, src_shape_h, window_shape_h );
}

TEST_CASE("sliding_window(case1c)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case1c, indices, dst_shape, src_shape, window_shape );
    SLIDING_WINDOW_SUBCASE( case1c, indices_a, dst_shape_a, src_shape_a, window_shape_a );
    SLIDING_WINDOW_SUBCASE( case1c, indices_v, dst_shape_v, src_shape_v, window_shape_v );
    SLIDING_WINDOW_SUBCASE( case1c, indices_f, dst_shape_f, src_shape_f, window_shape_f );
    SLIDING_WINDOW_SUBCASE( case1c, indices_h, dst_shape_h, src_shape_h, window_shape_h );
}

TEST_CASE("sliding_window(case1d)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case1d, indices, dst_shape, src_shape, window_shape );
    SLIDING_WINDOW_SUBCASE( case1d, indices_a, dst_shape_a, src_shape_a, window_shape_a );
    SLIDING_WINDOW_SUBCASE( case1d, indices_v, dst_shape_v, src_shape_v, window_shape_v );
    SLIDING_WINDOW_SUBCASE( case1d, indices_f, dst_shape_f, src_shape_f, window_shape_f );
    SLIDING_WINDOW_SUBCASE( case1d, indices_h, dst_shape_h, src_shape_h, window_shape_h );
}

TEST_CASE("sliding_window(case1e)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case1e, indices, dst_shape, src_shape, window_shape );
    SLIDING_WINDOW_SUBCASE( case1e, indices_a, dst_shape_a, src_shape_a, window_shape_a );
    SLIDING_WINDOW_SUBCASE( case1e, indices_v, dst_shape_v, src_shape_v, window_shape_v );
    SLIDING_WINDOW_SUBCASE( case1e, indices_f, dst_shape_f, src_shape_f, window_shape_f );
    SLIDING_WINDOW_SUBCASE( case1e, indices_h, dst_shape_h, src_shape_h, window_shape_h );
}

TEST_CASE("sliding_window(case1f)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case1f, indices, dst_shape, src_shape, window_shape );
    SLIDING_WINDOW_SUBCASE( case1f, indices_a, dst_shape_a, src_shape_a, window_shape_a );
    SLIDING_WINDOW_SUBCASE( case1f, indices_v, dst_shape_v, src_shape_v, window_shape_v );
    SLIDING_WINDOW_SUBCASE( case1f, indices_f, dst_shape_f, src_shape_f, window_shape_f );
    SLIDING_WINDOW_SUBCASE( case1f, indices_h, dst_shape_h, src_shape_h, window_shape_h );
}

TEST_CASE("sliding_window(case1g)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case1g, indices, dst_shape, src_shape, window_shape );
    SLIDING_WINDOW_SUBCASE( case1g, indices_a, dst_shape_a, src_shape_a, window_shape_a );
    SLIDING_WINDOW_SUBCASE( case1g, indices_v, dst_shape_v, src_shape_v, window_shape_v );
    SLIDING_WINDOW_SUBCASE( case1g, indices_f, dst_shape_f, src_shape_f, window_shape_f );
    SLIDING_WINDOW_SUBCASE( case1g, indices_h, dst_shape_h, src_shape_h, window_shape_h );
}

TEST_CASE("sliding_window(case1h)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case1h, indices, dst_shape, src_shape, window_shape );
    SLIDING_WINDOW_SUBCASE( case1h, indices_a, dst_shape_a, src_shape_a, window_shape_a );
    SLIDING_WINDOW_SUBCASE( case1h, indices_v, dst_shape_v, src_shape_v, window_shape_v );
    SLIDING_WINDOW_SUBCASE( case1h, indices_f, dst_shape_f, src_shape_f, window_shape_f );
    SLIDING_WINDOW_SUBCASE( case1h, indices_h, dst_shape_h, src_shape_h, window_shape_h );
}

TEST_CASE("sliding_window(case1i)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case1i, indices, dst_shape, src_shape, window_shape );
    SLIDING_WINDOW_SUBCASE( case1i, indices_a, dst_shape_a, src_shape_a, window_shape_a );
    SLIDING_WINDOW_SUBCASE( case1i, indices_v, dst_shape_v, src_shape_v, window_shape_v );
    SLIDING_WINDOW_SUBCASE( case1i, indices_f, dst_shape_f, src_shape_f, window_shape_f );
    SLIDING_WINDOW_SUBCASE( case1i, indices_h, dst_shape_h, src_shape_h, window_shape_h );
}

TEST_CASE("sliding_window(case1j)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case1j, indices, dst_shape, src_shape, window_shape );
    SLIDING_WINDOW_SUBCASE( case1j, indices_a, dst_shape_a, src_shape_a, window_shape_a );
    SLIDING_WINDOW_SUBCASE( case1j, indices_v, dst_shape_v, src_shape_v, window_shape_v );
    SLIDING_WINDOW_SUBCASE( case1j, indices_f, dst_shape_f, src_shape_f, window_shape_f );
    SLIDING_WINDOW_SUBCASE( case1j, indices_h, dst_shape_h, src_shape_h, window_shape_h );
}

TEST_CASE("sliding_window(case1k)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case1k, indices, dst_shape, src_shape, window_shape );
    SLIDING_WINDOW_SUBCASE( case1k, indices_a, dst_shape_a, src_shape_a, window_shape_a );
    SLIDING_WINDOW_SUBCASE( case1k, indices_v, dst_shape_v, src_shape_v, window_shape_v );
    SLIDING_WINDOW_SUBCASE( case1k, indices_f, dst_shape_f, src_shape_f, window_shape_f );
    SLIDING_WINDOW_SUBCASE( case1k, indices_h, dst_shape_h, src_shape_h, window_shape_h );
}

TEST_CASE("sliding_window(case1l)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case1l, indices, dst_shape, src_shape, window_shape );
    SLIDING_WINDOW_SUBCASE( case1l, indices_a, dst_shape_a, src_shape_a, window_shape_a );
    SLIDING_WINDOW_SUBCASE( case1l, indices_v, dst_shape_v, src_shape_v, window_shape_v );
    SLIDING_WINDOW_SUBCASE( case1l, indices_f, dst_shape_f, src_shape_f, window_shape_f );
    SLIDING_WINDOW_SUBCASE( case1l, indices_h, dst_shape_h, src_shape_h, window_shape_h );
}

TEST_CASE("sliding_window(case1m)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case1m, indices, dst_shape, src_shape, window_shape );
    SLIDING_WINDOW_SUBCASE( case1m, indices_a, dst_shape_a, src_shape_a, window_shape_a );
    SLIDING_WINDOW_SUBCASE( case1m, indices_v, dst_shape_v, src_shape_v, window_shape_v );
    SLIDING_WINDOW_SUBCASE( case1m, indices_f, dst_shape_f, src_shape_f, window_shape_f );
    SLIDING_WINDOW_SUBCASE( case1m, indices_h, dst_shape_h, src_shape_h, window_shape_h );
}

TEST_CASE("sliding_window(case1n)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case1n, indices, dst_shape, src_shape, window_shape );
    SLIDING_WINDOW_SUBCASE( case1n, indices_a, dst_shape_a, src_shape_a, window_shape_a );
    SLIDING_WINDOW_SUBCASE( case1n, indices_v, dst_shape_v, src_shape_v, window_shape_v );
    SLIDING_WINDOW_SUBCASE( case1n, indices_f, dst_shape_f, src_shape_f, window_shape_f );
    SLIDING_WINDOW_SUBCASE( case1n, indices_h, dst_shape_h, src_shape_h, window_shape_h );
}

TEST_CASE("sliding_window(case1o)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case1o, indices, dst_shape, src_shape, window_shape );
    SLIDING_WINDOW_SUBCASE( case1o, indices_a, dst_shape_a, src_shape_a, window_shape_a );
    SLIDING_WINDOW_SUBCASE( case1o, indices_v, dst_shape_v, src_shape_v, window_shape_v );
    SLIDING_WINDOW_SUBCASE( case1o, indices_f, dst_shape_f, src_shape_f, window_shape_f );
    SLIDING_WINDOW_SUBCASE( case1o, indices_h, dst_shape_h, src_shape_h, window_shape_h );
}

TEST_CASE("sliding_window(case1p)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case1p, indices, dst_shape, src_shape, window_shape );
    SLIDING_WINDOW_SUBCASE( case1p, indices_a, dst_shape_a, src_shape_a, window_shape_a );
    SLIDING_WINDOW_SUBCASE( case1p, indices_v, dst_shape_v, src_shape_v, window_shape_v );
    SLIDING_WINDOW_SUBCASE( case1p, indices_f, dst_shape_f, src_shape_f, window_shape_f );
    SLIDING_WINDOW_SUBCASE( case1p, indices_h, dst_shape_h, src_shape_h, window_shape_h );
}

TEST_CASE("sliding_window(case1q)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case1q, indices, dst_shape, src_shape, window_shape );
    SLIDING_WINDOW_SUBCASE( case1q, indices_a, dst_shape_a, src_shape_a, window_shape_a );
    SLIDING_WINDOW_SUBCASE( case1q, indices_v, dst_shape_v, src_shape_v, window_shape_v );
    SLIDING_WINDOW_SUBCASE( case1q, indices_f, dst_shape_f, src_shape_f, window_shape_f );
    SLIDING_WINDOW_SUBCASE( case1q, indices_h, dst_shape_h, src_shape_h, window_shape_h );
}

TEST_CASE("sliding_window(case1r)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case1r, indices, dst_shape, src_shape, window_shape );
    SLIDING_WINDOW_SUBCASE( case1r, indices_a, dst_shape_a, src_shape_a, window_shape_a );
    SLIDING_WINDOW_SUBCASE( case1r, indices_v, dst_shape_v, src_shape_v, window_shape_v );
    SLIDING_WINDOW_SUBCASE( case1r, indices_f, dst_shape_f, src_shape_f, window_shape_f );
    SLIDING_WINDOW_SUBCASE( case1r, indices_h, dst_shape_h, src_shape_h, window_shape_h );
}

TEST_CASE("sliding_window(case1s)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case1s, indices, dst_shape, src_shape, window_shape );
    SLIDING_WINDOW_SUBCASE( case1s, indices_a, dst_shape_a, src_shape_a, window_shape_a );
    SLIDING_WINDOW_SUBCASE( case1s, indices_v, dst_shape_v, src_shape_v, window_shape_v );
    SLIDING_WINDOW_SUBCASE( case1s, indices_f, dst_shape_f, src_shape_f, window_shape_f );
    SLIDING_WINDOW_SUBCASE( case1s, indices_h, dst_shape_h, src_shape_h, window_shape_h );
}

TEST_CASE("sliding_window(case1t)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case1t, indices, dst_shape, src_shape, window_shape );
    SLIDING_WINDOW_SUBCASE( case1t, indices_a, dst_shape_a, src_shape_a, window_shape_a );
    SLIDING_WINDOW_SUBCASE( case1t, indices_v, dst_shape_v, src_shape_v, window_shape_v );
    SLIDING_WINDOW_SUBCASE( case1t, indices_f, dst_shape_f, src_shape_f, window_shape_f );
    SLIDING_WINDOW_SUBCASE( case1t, indices_h, dst_shape_h, src_shape_h, window_shape_h );
}

TEST_CASE("sliding_window(case1u)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case1u, indices, dst_shape, src_shape, window_shape );
    SLIDING_WINDOW_SUBCASE( case1u, indices_a, dst_shape_a, src_shape_a, window_shape_a );
    SLIDING_WINDOW_SUBCASE( case1u, indices_v, dst_shape_v, src_shape_v, window_shape_v );
    SLIDING_WINDOW_SUBCASE( case1u, indices_f, dst_shape_f, src_shape_f, window_shape_f );
    SLIDING_WINDOW_SUBCASE( case1u, indices_h, dst_shape_h, src_shape_h, window_shape_h );
}

TEST_CASE("sliding_window(case1v)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case1v, indices, dst_shape, src_shape, window_shape );
    SLIDING_WINDOW_SUBCASE( case1v, indices_a, dst_shape_a, src_shape_a, window_shape_a );
    SLIDING_WINDOW_SUBCASE( case1v, indices_v, dst_shape_v, src_shape_v, window_shape_v );
    SLIDING_WINDOW_SUBCASE( case1v, indices_f, dst_shape_f, src_shape_f, window_shape_f );
    SLIDING_WINDOW_SUBCASE( case1v, indices_h, dst_shape_h, src_shape_h, window_shape_h );
}

TEST_CASE("sliding_window(case1w)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case1w, indices, dst_shape, src_shape, window_shape );
    SLIDING_WINDOW_SUBCASE( case1w, indices_a, dst_shape_a, src_shape_a, window_shape_a );
    SLIDING_WINDOW_SUBCASE( case1w, indices_v, dst_shape_v, src_shape_v, window_shape_v );
    SLIDING_WINDOW_SUBCASE( case1w, indices_f, dst_shape_f, src_shape_f, window_shape_f );
    SLIDING_WINDOW_SUBCASE( case1w, indices_h, dst_shape_h, src_shape_h, window_shape_h );
}

TEST_CASE("sliding_window(case2a)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case2a, indices, dst_shape, src_shape, window_shape );
    SLIDING_WINDOW_SUBCASE( case2a, indices_a, dst_shape_a, src_shape_a, window_shape );
    SLIDING_WINDOW_SUBCASE( case2a, indices_v, dst_shape_v, src_shape_v, window_shape );
    SLIDING_WINDOW_SUBCASE( case2a, indices_f, dst_shape_f, src_shape_f, window_shape );
    SLIDING_WINDOW_SUBCASE( case2a, indices_h, dst_shape_h, src_shape_h, window_shape );
}

TEST_CASE("sliding_window(case2b)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case2b, indices, dst_shape, src_shape, window_shape );
    SLIDING_WINDOW_SUBCASE( case2b, indices_a, dst_shape_a, src_shape_a, window_shape );
    SLIDING_WINDOW_SUBCASE( case2b, indices_v, dst_shape_v, src_shape_v, window_shape );
    SLIDING_WINDOW_SUBCASE( case2b, indices_f, dst_shape_f, src_shape_f, window_shape );
    SLIDING_WINDOW_SUBCASE( case2b, indices_h, dst_shape_h, src_shape_h, window_shape );
}

TEST_CASE("sliding_window(case2c)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case2c, indices, dst_shape, src_shape, window_shape );
    SLIDING_WINDOW_SUBCASE( case2c, indices_a, dst_shape_a, src_shape_a, window_shape );
    SLIDING_WINDOW_SUBCASE( case2c, indices_v, dst_shape_v, src_shape_v, window_shape );
    SLIDING_WINDOW_SUBCASE( case2c, indices_f, dst_shape_f, src_shape_f, window_shape );
    SLIDING_WINDOW_SUBCASE( case2c, indices_h, dst_shape_h, src_shape_h, window_shape );
}

TEST_CASE("sliding_window(case2d)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case2d, indices, dst_shape, src_shape, window_shape );
    SLIDING_WINDOW_SUBCASE( case2d, indices_a, dst_shape_a, src_shape_a, window_shape );
    SLIDING_WINDOW_SUBCASE( case2d, indices_v, dst_shape_v, src_shape_v, window_shape );
    SLIDING_WINDOW_SUBCASE( case2d, indices_f, dst_shape_f, src_shape_f, window_shape );
    SLIDING_WINDOW_SUBCASE( case2d, indices_h, dst_shape_h, src_shape_h, window_shape );
}

TEST_CASE("sliding_window(case2e)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case2e, indices, dst_shape, src_shape, window_shape );
    SLIDING_WINDOW_SUBCASE( case2e, indices_a, dst_shape_a, src_shape_a, window_shape );
    SLIDING_WINDOW_SUBCASE( case2e, indices_v, dst_shape_v, src_shape_v, window_shape );
    SLIDING_WINDOW_SUBCASE( case2e, indices_f, dst_shape_f, src_shape_f, window_shape );
    SLIDING_WINDOW_SUBCASE( case2e, indices_h, dst_shape_h, src_shape_h, window_shape );
}

TEST_CASE("sliding_window(case2f)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case2f, indices, dst_shape, src_shape, window_shape );
    SLIDING_WINDOW_SUBCASE( case2f, indices_a, dst_shape_a, src_shape_a, window_shape );
    SLIDING_WINDOW_SUBCASE( case2f, indices_v, dst_shape_v, src_shape_v, window_shape );
    SLIDING_WINDOW_SUBCASE( case2f, indices_f, dst_shape_f, src_shape_f, window_shape );
    SLIDING_WINDOW_SUBCASE( case2f, indices_h, dst_shape_h, src_shape_h, window_shape );
}

TEST_CASE("sliding_window(case2g)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case2g, indices, dst_shape, src_shape, window_shape );
    SLIDING_WINDOW_SUBCASE( case2g, indices_a, dst_shape_a, src_shape_a, window_shape );
    SLIDING_WINDOW_SUBCASE( case2g, indices_v, dst_shape_v, src_shape_v, window_shape );
    SLIDING_WINDOW_SUBCASE( case2g, indices_f, dst_shape_f, src_shape_f, window_shape );
    SLIDING_WINDOW_SUBCASE( case2g, indices_h, dst_shape_h, src_shape_h, window_shape );
}

TEST_CASE("sliding_window(case2h)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case2h, indices, dst_shape, src_shape, window_shape );
    SLIDING_WINDOW_SUBCASE( case2h, indices_a, dst_shape_a, src_shape_a, window_shape );
    SLIDING_WINDOW_SUBCASE( case2h, indices_v, dst_shape_v, src_shape_v, window_shape );
    SLIDING_WINDOW_SUBCASE( case2h, indices_f, dst_shape_f, src_shape_f, window_shape );
    SLIDING_WINDOW_SUBCASE( case2h, indices_h, dst_shape_h, src_shape_h, window_shape );
}

TEST_CASE("sliding_window(case2i)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case2i, indices, dst_shape, src_shape, window_shape );
    SLIDING_WINDOW_SUBCASE( case2i, indices_a, dst_shape_a, src_shape_a, window_shape );
    SLIDING_WINDOW_SUBCASE( case2i, indices_v, dst_shape_v, src_shape_v, window_shape );
    SLIDING_WINDOW_SUBCASE( case2i, indices_f, dst_shape_f, src_shape_f, window_shape );
    SLIDING_WINDOW_SUBCASE( case2i, indices_h, dst_shape_h, src_shape_h, window_shape );
}

TEST_CASE("sliding_window(case2j)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case2j, indices, dst_shape, src_shape, window_shape );
    SLIDING_WINDOW_SUBCASE( case2j, indices_a, dst_shape_a, src_shape_a, window_shape );
    SLIDING_WINDOW_SUBCASE( case2j, indices_v, dst_shape_v, src_shape_v, window_shape );
    SLIDING_WINDOW_SUBCASE( case2j, indices_f, dst_shape_f, src_shape_f, window_shape );
    SLIDING_WINDOW_SUBCASE( case2j, indices_h, dst_shape_h, src_shape_h, window_shape );
}

TEST_CASE("sliding_window(case2k)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case2k, indices, dst_shape, src_shape, window_shape );
    SLIDING_WINDOW_SUBCASE( case2k, indices_a, dst_shape_a, src_shape_a, window_shape );
    SLIDING_WINDOW_SUBCASE( case2k, indices_v, dst_shape_v, src_shape_v, window_shape );
    SLIDING_WINDOW_SUBCASE( case2k, indices_f, dst_shape_f, src_shape_f, window_shape );
    SLIDING_WINDOW_SUBCASE( case2k, indices_h, dst_shape_h, src_shape_h, window_shape );
}

TEST_CASE("sliding_window(case2l)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case2l, indices, dst_shape, src_shape, window_shape );
    SLIDING_WINDOW_SUBCASE( case2l, indices_a, dst_shape_a, src_shape_a, window_shape );
    SLIDING_WINDOW_SUBCASE( case2l, indices_v, dst_shape_v, src_shape_v, window_shape );
    SLIDING_WINDOW_SUBCASE( case2l, indices_f, dst_shape_f, src_shape_f, window_shape );
    SLIDING_WINDOW_SUBCASE( case2l, indices_h, dst_shape_h, src_shape_h, window_shape );
}

TEST_CASE("sliding_window(case3a)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case3a, indices, dst_shape, src_shape, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case3a, indices_a, dst_shape_a, src_shape_a, window_shape_a, axis_a );
    SLIDING_WINDOW_SUBCASE( case3a, indices_v, dst_shape_v, src_shape_v, window_shape_v, axis_v );
    SLIDING_WINDOW_SUBCASE( case3a, indices_f, dst_shape_f, src_shape_f, window_shape_f, axis_f );
    SLIDING_WINDOW_SUBCASE( case3a, indices_h, dst_shape_h, src_shape_h, window_shape_h, axis_h );
}

TEST_CASE("sliding_window(case3b)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case3b, indices, dst_shape, src_shape, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case3b, indices_a, dst_shape_a, src_shape_a, window_shape_a, axis_a );
    SLIDING_WINDOW_SUBCASE( case3b, indices_v, dst_shape_v, src_shape_v, window_shape_v, axis_v );
    SLIDING_WINDOW_SUBCASE( case3b, indices_f, dst_shape_f, src_shape_f, window_shape_f, axis_f );
    SLIDING_WINDOW_SUBCASE( case3b, indices_h, dst_shape_h, src_shape_h, window_shape_h, axis_h );
}

TEST_CASE("sliding_window(case3c)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case3c, indices, dst_shape, src_shape, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case3c, indices_a, dst_shape_a, src_shape_a, window_shape_a, axis_a );
    SLIDING_WINDOW_SUBCASE( case3c, indices_v, dst_shape_v, src_shape_v, window_shape_v, axis_v );
    SLIDING_WINDOW_SUBCASE( case3c, indices_f, dst_shape_f, src_shape_f, window_shape_f, axis_f );
    SLIDING_WINDOW_SUBCASE( case3c, indices_h, dst_shape_h, src_shape_h, window_shape_h, axis_h );
}

TEST_CASE("sliding_window(case3a)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case3d, indices, dst_shape, src_shape, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case3d, indices_a, dst_shape_a, src_shape_a, window_shape_a, axis_a );
    SLIDING_WINDOW_SUBCASE( case3d, indices_v, dst_shape_v, src_shape_v, window_shape_v, axis_v );
    SLIDING_WINDOW_SUBCASE( case3d, indices_f, dst_shape_f, src_shape_f, window_shape_f, axis_f );
    SLIDING_WINDOW_SUBCASE( case3d, indices_h, dst_shape_h, src_shape_h, window_shape_h, axis_h );
}

TEST_CASE("sliding_window(case3a)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case3e, indices, dst_shape, src_shape, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case3e, indices_a, dst_shape_a, src_shape_a, window_shape_a, axis_a );
    SLIDING_WINDOW_SUBCASE( case3e, indices_v, dst_shape_v, src_shape_v, window_shape_v, axis_v );
    SLIDING_WINDOW_SUBCASE( case3e, indices_f, dst_shape_f, src_shape_f, window_shape_f, axis_f );
    SLIDING_WINDOW_SUBCASE( case3e, indices_h, dst_shape_h, src_shape_h, window_shape_h, axis_h );
}

TEST_CASE("sliding_window(case3a)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case3f, indices, dst_shape, src_shape, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case3f, indices_a, dst_shape_a, src_shape_a, window_shape_a, axis_a );
    SLIDING_WINDOW_SUBCASE( case3f, indices_v, dst_shape_v, src_shape_v, window_shape_v, axis_v );
    SLIDING_WINDOW_SUBCASE( case3f, indices_f, dst_shape_f, src_shape_f, window_shape_f, axis_f );
    SLIDING_WINDOW_SUBCASE( case3f, indices_h, dst_shape_h, src_shape_h, window_shape_h, axis_h );
}

TEST_CASE("sliding_window(case3a)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case3g, indices, dst_shape, src_shape, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case3g, indices_a, dst_shape_a, src_shape_a, window_shape_a, axis_a );
    SLIDING_WINDOW_SUBCASE( case3g, indices_v, dst_shape_v, src_shape_v, window_shape_v, axis_v );
    SLIDING_WINDOW_SUBCASE( case3g, indices_f, dst_shape_f, src_shape_f, window_shape_f, axis_f );
    SLIDING_WINDOW_SUBCASE( case3g, indices_h, dst_shape_h, src_shape_h, window_shape_h, axis_h );
}

TEST_CASE("sliding_window(case3a)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case3h, indices, dst_shape, src_shape, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case3h, indices_a, dst_shape_a, src_shape_a, window_shape_a, axis_a );
    SLIDING_WINDOW_SUBCASE( case3h, indices_v, dst_shape_v, src_shape_v, window_shape_v, axis_v );
    SLIDING_WINDOW_SUBCASE( case3h, indices_f, dst_shape_f, src_shape_f, window_shape_f, axis_f );
    SLIDING_WINDOW_SUBCASE( case3h, indices_h, dst_shape_h, src_shape_h, window_shape_h, axis_h );
}

TEST_CASE("sliding_window(case3a)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case3i, indices, dst_shape, src_shape, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case3i, indices_a, dst_shape_a, src_shape_a, window_shape_a, axis_a );
    SLIDING_WINDOW_SUBCASE( case3i, indices_v, dst_shape_v, src_shape_v, window_shape_v, axis_v );
    SLIDING_WINDOW_SUBCASE( case3i, indices_f, dst_shape_f, src_shape_f, window_shape_f, axis_f );
    SLIDING_WINDOW_SUBCASE( case3i, indices_h, dst_shape_h, src_shape_h, window_shape_h, axis_h );
}

TEST_CASE("sliding_window(case3a)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case3j, indices, dst_shape, src_shape, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case3j, indices_a, dst_shape_a, src_shape_a, window_shape_a, axis_a );
    SLIDING_WINDOW_SUBCASE( case3j, indices_v, dst_shape_v, src_shape_v, window_shape_v, axis_v );
    SLIDING_WINDOW_SUBCASE( case3j, indices_f, dst_shape_f, src_shape_f, window_shape_f, axis_f );
    SLIDING_WINDOW_SUBCASE( case3j, indices_h, dst_shape_h, src_shape_h, window_shape_h, axis_h );
}

TEST_CASE("sliding_window(case3a)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case3k, indices, dst_shape, src_shape, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case3k, indices_a, dst_shape_a, src_shape_a, window_shape_a, axis_a );
    SLIDING_WINDOW_SUBCASE( case3k, indices_v, dst_shape_v, src_shape_v, window_shape_v, axis_v );
    SLIDING_WINDOW_SUBCASE( case3k, indices_f, dst_shape_f, src_shape_f, window_shape_f, axis_f );
    SLIDING_WINDOW_SUBCASE( case3k, indices_h, dst_shape_h, src_shape_h, window_shape_h, axis_h );
}

TEST_CASE("sliding_window(case3a)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case3l, indices, dst_shape, src_shape, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case3l, indices_a, dst_shape_a, src_shape_a, window_shape_a, axis_a );
    SLIDING_WINDOW_SUBCASE( case3l, indices_v, dst_shape_v, src_shape_v, window_shape_v, axis_v );
    SLIDING_WINDOW_SUBCASE( case3l, indices_f, dst_shape_f, src_shape_f, window_shape_f, axis_f );
    SLIDING_WINDOW_SUBCASE( case3l, indices_h, dst_shape_h, src_shape_h, window_shape_h, axis_h );
}

TEST_CASE("sliding_window(case3a)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case3m, indices, dst_shape, src_shape, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case3m, indices_a, dst_shape_a, src_shape_a, window_shape_a, axis_a );
    SLIDING_WINDOW_SUBCASE( case3m, indices_v, dst_shape_v, src_shape_v, window_shape_v, axis_v );
    SLIDING_WINDOW_SUBCASE( case3m, indices_f, dst_shape_f, src_shape_f, window_shape_f, axis_f );
    SLIDING_WINDOW_SUBCASE( case3m, indices_h, dst_shape_h, src_shape_h, window_shape_h, axis_h );
}

TEST_CASE("sliding_window(case3a)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case3n, indices, dst_shape, src_shape, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case3n, indices_a, dst_shape_a, src_shape_a, window_shape_a, axis_a );
    SLIDING_WINDOW_SUBCASE( case3n, indices_v, dst_shape_v, src_shape_v, window_shape_v, axis_v );
    SLIDING_WINDOW_SUBCASE( case3n, indices_f, dst_shape_f, src_shape_f, window_shape_f, axis_f );
    SLIDING_WINDOW_SUBCASE( case3n, indices_h, dst_shape_h, src_shape_h, window_shape_h, axis_h );
}

TEST_CASE("sliding_window(case3a)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case3o, indices, dst_shape, src_shape, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case3o, indices_a, dst_shape_a, src_shape_a, window_shape_a, axis_a );
    SLIDING_WINDOW_SUBCASE( case3o, indices_v, dst_shape_v, src_shape_v, window_shape_v, axis_v );
    SLIDING_WINDOW_SUBCASE( case3o, indices_f, dst_shape_f, src_shape_f, window_shape_f, axis_f );
    SLIDING_WINDOW_SUBCASE( case3o, indices_h, dst_shape_h, src_shape_h, window_shape_h, axis_h );
}

TEST_CASE("sliding_window(case3p)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case3p, indices, dst_shape, src_shape, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case3p, indices_a, dst_shape_a, src_shape_a, window_shape_a, axis_a );
    SLIDING_WINDOW_SUBCASE( case3p, indices_v, dst_shape_v, src_shape_v, window_shape_v, axis_v );
    SLIDING_WINDOW_SUBCASE( case3p, indices_f, dst_shape_f, src_shape_f, window_shape_f, axis_f );
    SLIDING_WINDOW_SUBCASE( case3p, indices_h, dst_shape_h, src_shape_h, window_shape_h, axis_h );
}

TEST_CASE("sliding_window(case3q)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case3q, indices, dst_shape, src_shape, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case3q, indices_a, dst_shape_a, src_shape_a, window_shape_a, axis_a );
    SLIDING_WINDOW_SUBCASE( case3q, indices_v, dst_shape_v, src_shape_v, window_shape_v, axis_v );
    SLIDING_WINDOW_SUBCASE( case3q, indices_f, dst_shape_f, src_shape_f, window_shape_f, axis_f );
    SLIDING_WINDOW_SUBCASE( case3q, indices_h, dst_shape_h, src_shape_h, window_shape_h, axis_h );
}

TEST_CASE("sliding_window(case4a)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case4a, indices, dst_shape, src_shape, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case4a, indices_a, dst_shape_a, src_shape_a, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case4a, indices_v, dst_shape_v, src_shape_v, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case4a, indices_f, dst_shape_f, src_shape_f, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case4a, indices_h, dst_shape_h, src_shape_h, window_shape, axis );
}

TEST_CASE("sliding_window(case4b)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case4b, indices, dst_shape, src_shape, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case4b, indices_a, dst_shape_a, src_shape_a, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case4b, indices_v, dst_shape_v, src_shape_v, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case4b, indices_f, dst_shape_f, src_shape_f, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case4b, indices_h, dst_shape_h, src_shape_h, window_shape, axis );
}

TEST_CASE("sliding_window(case4c)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case4c, indices, dst_shape, src_shape, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case4c, indices_a, dst_shape_a, src_shape_a, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case4c, indices_v, dst_shape_v, src_shape_v, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case4c, indices_f, dst_shape_f, src_shape_f, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case4c, indices_h, dst_shape_h, src_shape_h, window_shape, axis );
}

TEST_CASE("sliding_window(case4d)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case4d, indices, dst_shape, src_shape, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case4d, indices_a, dst_shape_a, src_shape_a, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case4d, indices_v, dst_shape_v, src_shape_v, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case4d, indices_f, dst_shape_f, src_shape_f, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case4d, indices_h, dst_shape_h, src_shape_h, window_shape, axis );
}

TEST_CASE("sliding_window(case4e)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case4e, indices, dst_shape, src_shape, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case4e, indices_a, dst_shape_a, src_shape_a, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case4e, indices_v, dst_shape_v, src_shape_v, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case4e, indices_f, dst_shape_f, src_shape_f, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case4e, indices_h, dst_shape_h, src_shape_h, window_shape, axis );
}

TEST_CASE("sliding_window(case4f)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case4f, indices, dst_shape, src_shape, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case4f, indices_a, dst_shape_a, src_shape_a, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case4f, indices_v, dst_shape_v, src_shape_v, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case4f, indices_f, dst_shape_f, src_shape_f, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case4f, indices_h, dst_shape_h, src_shape_h, window_shape, axis );
}

TEST_CASE("sliding_window(case4g)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case4g, indices, dst_shape, src_shape, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case4g, indices_a, dst_shape_a, src_shape_a, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case4g, indices_v, dst_shape_v, src_shape_v, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case4g, indices_f, dst_shape_f, src_shape_f, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case4g, indices_h, dst_shape_h, src_shape_h, window_shape, axis );
}

TEST_CASE("sliding_window(case4h)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case4h, indices, dst_shape, src_shape, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case4h, indices_a, dst_shape_a, src_shape_a, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case4h, indices_v, dst_shape_v, src_shape_v, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case4h, indices_f, dst_shape_f, src_shape_f, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case4h, indices_h, dst_shape_h, src_shape_h, window_shape, axis );
}

TEST_CASE("sliding_window(case4i)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case4i, indices, dst_shape, src_shape, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case4i, indices_a, dst_shape_a, src_shape_a, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case4i, indices_v, dst_shape_v, src_shape_v, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case4i, indices_f, dst_shape_f, src_shape_f, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case4i, indices_h, dst_shape_h, src_shape_h, window_shape, axis );
}

TEST_CASE("sliding_window(case4j)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case4j, indices, dst_shape, src_shape, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case4j, indices_a, dst_shape_a, src_shape_a, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case4j, indices_v, dst_shape_v, src_shape_v, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case4j, indices_f, dst_shape_f, src_shape_f, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case4j, indices_h, dst_shape_h, src_shape_h, window_shape, axis );
}

TEST_CASE("sliding_window(case4k)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case4k, indices, dst_shape, src_shape, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case4k, indices_a, dst_shape_a, src_shape_a, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case4k, indices_v, dst_shape_v, src_shape_v, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case4k, indices_f, dst_shape_f, src_shape_f, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case4k, indices_h, dst_shape_h, src_shape_h, window_shape, axis );
}

TEST_CASE("sliding_window(case4l)" * doctest::test_suite("index::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case4l, indices, dst_shape, src_shape, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case4l, indices_a, dst_shape_a, src_shape_a, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case4l, indices_v, dst_shape_v, src_shape_v, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case4l, indices_f, dst_shape_f, src_shape_f, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case4l, indices_h, dst_shape_h, src_shape_h, window_shape, axis );
}