#include "nmtools/core/broadcast_to.hpp"
#include "nmtools/testing/data/index/broadcast_to.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;

#define BROADCAST_TO_STRIDES_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index,broadcast_to_strides,case_name); \
    auto result = nmtools::index::broadcast_to_strides(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

#define BROADCAST_TO_STRIDES_EXPECTED_SUBCASE(case_name, result, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index,broadcast_to_strides,case_name); \
    auto result = nmtools::index::broadcast_to_strides(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("broadcast_to_strides(case1)" * doctest::test_suite("index::broadcast_to_strides"))
{
    BROADCAST_TO_STRIDES_SUBCASE( case1, src_shape, dst_shape );
    BROADCAST_TO_STRIDES_SUBCASE( case1, src_shape_a, dst_shape_a );
    BROADCAST_TO_STRIDES_SUBCASE( case1, src_shape_f, dst_shape_f );
    BROADCAST_TO_STRIDES_SUBCASE( case1, src_shape_h, dst_shape_h );
    BROADCAST_TO_STRIDES_SUBCASE( case1, src_shape_v, dst_shape_v );

    BROADCAST_TO_STRIDES_SUBCASE( case1, src_shape_ct, dst_shape_ct );

    BROADCAST_TO_STRIDES_EXPECTED_SUBCASE(case1, result_nl1, src_shape_nl1, dst_shape_nl1 );    

    BROADCAST_TO_STRIDES_SUBCASE( case1, src_shape_mx1, dst_shape_mx1 );
}

TEST_CASE("broadcast_to_strides(case2)" * doctest::test_suite("index::broadcast_to_strides"))
{
    BROADCAST_TO_STRIDES_SUBCASE( case2, src_shape, dst_shape );
    BROADCAST_TO_STRIDES_SUBCASE( case2, src_shape_a, dst_shape_a );
    BROADCAST_TO_STRIDES_SUBCASE( case2, src_shape_f, dst_shape_f );
    BROADCAST_TO_STRIDES_SUBCASE( case2, src_shape_h, dst_shape_h );
    BROADCAST_TO_STRIDES_SUBCASE( case2, src_shape_v, dst_shape_v );

    BROADCAST_TO_STRIDES_SUBCASE( case2, src_shape_ct, dst_shape_ct );

    BROADCAST_TO_STRIDES_EXPECTED_SUBCASE(case2, result_nl1, src_shape_nl1, dst_shape_nl1 );

    BROADCAST_TO_STRIDES_SUBCASE( case2, src_shape_mx1, dst_shape_mx1 );
}

TEST_CASE("broadcast_to_strides(case3)" * doctest::test_suite("index::broadcast_to_strides"))
{
    BROADCAST_TO_STRIDES_SUBCASE( case3, src_shape, dst_shape );
    BROADCAST_TO_STRIDES_SUBCASE( case3, src_shape_a, dst_shape_a );
    BROADCAST_TO_STRIDES_SUBCASE( case3, src_shape_f, dst_shape_f );
    BROADCAST_TO_STRIDES_SUBCASE( case3, src_shape_h, dst_shape_h );
    BROADCAST_TO_STRIDES_SUBCASE( case3, src_shape_v, dst_shape_v );

    BROADCAST_TO_STRIDES_SUBCASE( case3, src_shape_ct, dst_shape_ct );

    BROADCAST_TO_STRIDES_EXPECTED_SUBCASE(case3, result_nl1, src_shape_nl1, dst_shape_nl1 );

    BROADCAST_TO_STRIDES_SUBCASE( case3, src_shape_mx1, dst_shape_mx1 );
}

TEST_CASE("broadcast_to_strides(case4)" * doctest::test_suite("index::broadcast_to_strides"))
{
    BROADCAST_TO_STRIDES_SUBCASE( case4, src_shape, dst_shape );
    BROADCAST_TO_STRIDES_SUBCASE( case4, src_shape_a, dst_shape_a );
    BROADCAST_TO_STRIDES_SUBCASE( case4, src_shape_f, dst_shape_f );
    BROADCAST_TO_STRIDES_SUBCASE( case4, src_shape_h, dst_shape_h );
    BROADCAST_TO_STRIDES_SUBCASE( case4, src_shape_v, dst_shape_v );

    BROADCAST_TO_STRIDES_SUBCASE( case4, src_shape_ct, dst_shape_ct );

    BROADCAST_TO_STRIDES_EXPECTED_SUBCASE(case4, result_nl1, src_shape_nl1, dst_shape_nl1 );

    BROADCAST_TO_STRIDES_SUBCASE( case4, src_shape_mx1, dst_shape_mx1 );
}

#define BROADCAST_TO_V2_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index,broadcast_to_v2,case_name); \
    auto result = nmtools::index::broadcast_to_v2(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

#define BROADCAST_TO_V2_RESULT_SUBCASE(case_name, result, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index,broadcast_to_v2,case_name); \
    auto result = nmtools::index::broadcast_to_v2(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("broadcast_to_v2(case1a)" * doctest::test_suite("index::broadcast_to_v2"))
{
    BROADCAST_TO_V2_SUBCASE( case1a, indices, src_shape, dst_strides, src_strides );
    BROADCAST_TO_V2_SUBCASE( case1a, indices, src_shape_a, dst_strides_a, src_strides_a );
    BROADCAST_TO_V2_SUBCASE( case1a, indices, src_shape_f, dst_strides_f, src_strides_f );
    BROADCAST_TO_V2_SUBCASE( case1a, indices, src_shape_h, dst_strides_h, src_strides_h );
    BROADCAST_TO_V2_SUBCASE( case1a, indices, src_shape_v, dst_strides_v, src_strides_v );
    BROADCAST_TO_V2_SUBCASE( case1a, indices, src_shape_sv, dst_strides_sv, src_strides_sv );

    BROADCAST_TO_V2_SUBCASE( case1a, indices_ct, src_shape_ct, dst_strides_ct, src_strides_ct );

    BROADCAST_TO_V2_RESULT_SUBCASE( case1a, result_nl1, indices_nl1, src_shape_nl1, dst_strides_nl1, src_strides_nl1 );

    BROADCAST_TO_V2_SUBCASE( case1a, indices_mx1, src_shape_mx1, dst_strides_mx1, src_strides_mx1 );
}

TEST_CASE("broadcast_to_v2(case1b)" * doctest::test_suite("index::broadcast_to_v2"))
{
    BROADCAST_TO_V2_SUBCASE( case1b, indices, src_shape, dst_strides, src_strides );
    BROADCAST_TO_V2_SUBCASE( case1b, indices, src_shape_a, dst_strides_a, src_strides_a );
    BROADCAST_TO_V2_SUBCASE( case1b, indices, src_shape_f, dst_strides_f, src_strides_f );
    BROADCAST_TO_V2_SUBCASE( case1b, indices, src_shape_h, dst_strides_h, src_strides_h );
    BROADCAST_TO_V2_SUBCASE( case1b, indices, src_shape_v, dst_strides_v, src_strides_v );
    BROADCAST_TO_V2_SUBCASE( case1b, indices, src_shape_sv, dst_strides_sv, src_strides_sv );

    BROADCAST_TO_V2_SUBCASE( case1b, indices_ct, src_shape_ct, dst_strides_ct, src_strides_ct );

    BROADCAST_TO_V2_RESULT_SUBCASE( case1b, result_nl1, indices_nl1, src_shape_nl1, dst_strides_nl1, src_strides_nl1 );

    BROADCAST_TO_V2_SUBCASE( case1b, indices_mx1, src_shape_mx1, dst_strides_mx1, src_strides_mx1 );
}

TEST_CASE("broadcast_to_v2(case1c)" * doctest::test_suite("index::broadcast_to_v2"))
{
    BROADCAST_TO_V2_SUBCASE( case1c, indices, src_shape, dst_strides, src_strides );
    BROADCAST_TO_V2_SUBCASE( case1c, indices, src_shape_a, dst_strides_a, src_strides_a );
    BROADCAST_TO_V2_SUBCASE( case1c, indices, src_shape_f, dst_strides_f, src_strides_f );
    BROADCAST_TO_V2_SUBCASE( case1c, indices, src_shape_h, dst_strides_h, src_strides_h );
    BROADCAST_TO_V2_SUBCASE( case1c, indices, src_shape_v, dst_strides_v, src_strides_v );
    BROADCAST_TO_V2_SUBCASE( case1c, indices, src_shape_sv, dst_strides_sv, src_strides_sv );

    BROADCAST_TO_V2_SUBCASE( case1c, indices_ct, src_shape_ct, dst_strides_ct, src_strides_ct );

    BROADCAST_TO_V2_RESULT_SUBCASE( case1c, result_nl1, indices_nl1, src_shape_nl1, dst_strides_nl1, src_strides_nl1 );

    BROADCAST_TO_V2_SUBCASE( case1c, indices_mx1, src_shape_mx1, dst_strides_mx1, src_strides_mx1 );
}

TEST_CASE("broadcast_to_v2(case1d)" * doctest::test_suite("index::broadcast_to_v2"))
{
    BROADCAST_TO_V2_SUBCASE( case1d, indices, src_shape, dst_strides, src_strides );
    BROADCAST_TO_V2_SUBCASE( case1d, indices, src_shape_a, dst_strides_a, src_strides_a );
    BROADCAST_TO_V2_SUBCASE( case1d, indices, src_shape_f, dst_strides_f, src_strides_f );
    BROADCAST_TO_V2_SUBCASE( case1d, indices, src_shape_h, dst_strides_h, src_strides_h );
    BROADCAST_TO_V2_SUBCASE( case1d, indices, src_shape_v, dst_strides_v, src_strides_v );
    BROADCAST_TO_V2_SUBCASE( case1d, indices, src_shape_sv, dst_strides_sv, src_strides_sv );

    BROADCAST_TO_V2_SUBCASE( case1d, indices_ct, src_shape_ct, dst_strides_ct, src_strides_ct );

    BROADCAST_TO_V2_RESULT_SUBCASE( case1d, result_nl1, indices_nl1, src_shape_nl1, dst_strides_nl1, src_strides_nl1 );

    BROADCAST_TO_V2_SUBCASE( case1d, indices_mx1, src_shape_mx1, dst_strides_mx1, src_strides_mx1 );
}

TEST_CASE("broadcast_to_v2(case1e)" * doctest::test_suite("index::broadcast_to_v2"))
{
    BROADCAST_TO_V2_SUBCASE( case1e, indices, src_shape, dst_strides, src_strides );
    BROADCAST_TO_V2_SUBCASE( case1e, indices, src_shape_a, dst_strides_a, src_strides_a );
    BROADCAST_TO_V2_SUBCASE( case1e, indices, src_shape_f, dst_strides_f, src_strides_f );
    BROADCAST_TO_V2_SUBCASE( case1e, indices, src_shape_h, dst_strides_h, src_strides_h );
    BROADCAST_TO_V2_SUBCASE( case1e, indices, src_shape_v, dst_strides_v, src_strides_v );
    BROADCAST_TO_V2_SUBCASE( case1e, indices, src_shape_sv, dst_strides_sv, src_strides_sv );

    BROADCAST_TO_V2_SUBCASE( case1e, indices_ct, src_shape_ct, dst_strides_ct, src_strides_ct );

    BROADCAST_TO_V2_RESULT_SUBCASE( case1e, result_nl1, indices_nl1, src_shape_nl1, dst_strides_nl1, src_strides_nl1 );

    BROADCAST_TO_V2_SUBCASE( case1e, indices_mx1, src_shape_mx1, dst_strides_mx1, src_strides_mx1 );
}

TEST_CASE("broadcast_to_v2(case1f)" * doctest::test_suite("index::broadcast_to_v2"))
{
    BROADCAST_TO_V2_SUBCASE( case1f, indices, src_shape, dst_strides, src_strides );
    BROADCAST_TO_V2_SUBCASE( case1f, indices, src_shape_a, dst_strides_a, src_strides_a );
    BROADCAST_TO_V2_SUBCASE( case1f, indices, src_shape_f, dst_strides_f, src_strides_f );
    BROADCAST_TO_V2_SUBCASE( case1f, indices, src_shape_h, dst_strides_h, src_strides_h );
    BROADCAST_TO_V2_SUBCASE( case1f, indices, src_shape_v, dst_strides_v, src_strides_v );
    BROADCAST_TO_V2_SUBCASE( case1f, indices, src_shape_sv, dst_strides_sv, src_strides_sv );

    BROADCAST_TO_V2_SUBCASE( case1f, indices_ct, src_shape_ct, dst_strides_ct, src_strides_ct );

    BROADCAST_TO_V2_RESULT_SUBCASE( case1f, result_nl1, indices_nl1, src_shape_nl1, dst_strides_nl1, src_strides_nl1 );

    BROADCAST_TO_V2_SUBCASE( case1f, indices_mx1, src_shape_mx1, dst_strides_mx1, src_strides_mx1 );
}

TEST_CASE("broadcast_to_v2(case1g)" * doctest::test_suite("index::broadcast_to_v2"))
{
    BROADCAST_TO_V2_SUBCASE( case1g, indices, src_shape, dst_strides, src_strides );
    BROADCAST_TO_V2_SUBCASE( case1g, indices, src_shape_a, dst_strides_a, src_strides_a );
    BROADCAST_TO_V2_SUBCASE( case1g, indices, src_shape_f, dst_strides_f, src_strides_f );
    BROADCAST_TO_V2_SUBCASE( case1g, indices, src_shape_h, dst_strides_h, src_strides_h );
    BROADCAST_TO_V2_SUBCASE( case1g, indices, src_shape_v, dst_strides_v, src_strides_v );
    BROADCAST_TO_V2_SUBCASE( case1g, indices, src_shape_sv, dst_strides_sv, src_strides_sv );

    BROADCAST_TO_V2_SUBCASE( case1g, indices_ct, src_shape_ct, dst_strides_ct, src_strides_ct );

    BROADCAST_TO_V2_RESULT_SUBCASE( case1g, result_nl1, indices_nl1, src_shape_nl1, dst_strides_nl1, src_strides_nl1 );

    BROADCAST_TO_V2_SUBCASE( case1g, indices_mx1, src_shape_mx1, dst_strides_mx1, src_strides_mx1 );
}

TEST_CASE("broadcast_to_v2(case2a)" * doctest::test_suite("index::broadcast_to_v2"))
{
    BROADCAST_TO_V2_SUBCASE( case2a, indices, src_shape, dst_strides, src_strides );
    BROADCAST_TO_V2_SUBCASE( case2a, indices, src_shape_a, dst_strides_a, src_strides_a );
    BROADCAST_TO_V2_SUBCASE( case2a, indices, src_shape_f, dst_strides_f, src_strides_f );
    BROADCAST_TO_V2_SUBCASE( case2a, indices, src_shape_h, dst_strides_h, src_strides_h );
    BROADCAST_TO_V2_SUBCASE( case2a, indices, src_shape_v, dst_strides_v, src_strides_v );
    BROADCAST_TO_V2_SUBCASE( case2a, indices, src_shape_sv, dst_strides_sv, src_strides_sv );

    BROADCAST_TO_V2_SUBCASE( case2a, indices_ct, src_shape_ct, dst_strides_ct, src_strides_ct );

    BROADCAST_TO_V2_RESULT_SUBCASE( case2a, result_nl1, indices_nl1, src_shape_nl1, dst_strides_nl1, src_strides_nl1 );

    BROADCAST_TO_V2_SUBCASE( case2a, indices_mx1, src_shape_mx1, dst_strides_mx1, src_strides_mx1 );
}

TEST_CASE("broadcast_to_v2(case2b)" * doctest::test_suite("index::broadcast_to_v2"))
{
    BROADCAST_TO_V2_SUBCASE( case2b, indices, src_shape, dst_strides, src_strides );
    BROADCAST_TO_V2_SUBCASE( case2b, indices, src_shape_a, dst_strides_a, src_strides_a );
    BROADCAST_TO_V2_SUBCASE( case2b, indices, src_shape_f, dst_strides_f, src_strides_f );
    BROADCAST_TO_V2_SUBCASE( case2b, indices, src_shape_h, dst_strides_h, src_strides_h );
    BROADCAST_TO_V2_SUBCASE( case2b, indices, src_shape_v, dst_strides_v, src_strides_v );
    BROADCAST_TO_V2_SUBCASE( case2b, indices, src_shape_sv, dst_strides_sv, src_strides_sv );

    BROADCAST_TO_V2_SUBCASE( case2b, indices_ct, src_shape_ct, dst_strides_ct, src_strides_ct );

    BROADCAST_TO_V2_RESULT_SUBCASE( case2b, result_nl1, indices_nl1, src_shape_nl1, dst_strides_nl1, src_strides_nl1 );

    BROADCAST_TO_V2_SUBCASE( case2b, indices_mx1, src_shape_mx1, dst_strides_mx1, src_strides_mx1 );
}

TEST_CASE("broadcast_to_v2(case2c)" * doctest::test_suite("index::broadcast_to_v2"))
{
    BROADCAST_TO_V2_SUBCASE( case2c, indices, src_shape, dst_strides, src_strides );
    BROADCAST_TO_V2_SUBCASE( case2c, indices, src_shape_a, dst_strides_a, src_strides_a );
    BROADCAST_TO_V2_SUBCASE( case2c, indices, src_shape_f, dst_strides_f, src_strides_f );
    BROADCAST_TO_V2_SUBCASE( case2c, indices, src_shape_h, dst_strides_h, src_strides_h );
    BROADCAST_TO_V2_SUBCASE( case2c, indices, src_shape_v, dst_strides_v, src_strides_v );
    BROADCAST_TO_V2_SUBCASE( case2c, indices, src_shape_sv, dst_strides_sv, src_strides_sv );

    BROADCAST_TO_V2_SUBCASE( case2c, indices_ct, src_shape_ct, dst_strides_ct, src_strides_ct );

    BROADCAST_TO_V2_RESULT_SUBCASE( case2c, result_nl1, indices_nl1, src_shape_nl1, dst_strides_nl1, src_strides_nl1 );

    BROADCAST_TO_V2_SUBCASE( case2c, indices_mx1, src_shape_mx1, dst_strides_mx1, src_strides_mx1 );
}

TEST_CASE("broadcast_to_v2(case2d)" * doctest::test_suite("index::broadcast_to_v2"))
{
    BROADCAST_TO_V2_SUBCASE( case2d, indices, src_shape, dst_strides, src_strides );
    BROADCAST_TO_V2_SUBCASE( case2d, indices, src_shape_a, dst_strides_a, src_strides_a );
    BROADCAST_TO_V2_SUBCASE( case2d, indices, src_shape_f, dst_strides_f, src_strides_f );
    BROADCAST_TO_V2_SUBCASE( case2d, indices, src_shape_h, dst_strides_h, src_strides_h );
    BROADCAST_TO_V2_SUBCASE( case2d, indices, src_shape_v, dst_strides_v, src_strides_v );
    BROADCAST_TO_V2_SUBCASE( case2d, indices, src_shape_sv, dst_strides_sv, src_strides_sv );

    BROADCAST_TO_V2_SUBCASE( case2d, indices_ct, src_shape_ct, dst_strides_ct, src_strides_ct );

    BROADCAST_TO_V2_RESULT_SUBCASE( case2d, result_nl1, indices_nl1, src_shape_nl1, dst_strides_nl1, src_strides_nl1 );

    BROADCAST_TO_V2_SUBCASE( case2d, indices_mx1, src_shape_mx1, dst_strides_mx1, src_strides_mx1 );
}

TEST_CASE("broadcast_to_v2(case2e)" * doctest::test_suite("index::broadcast_to_v2"))
{
    BROADCAST_TO_V2_SUBCASE( case2e, indices, src_shape, dst_strides, src_strides );
    BROADCAST_TO_V2_SUBCASE( case2e, indices, src_shape_a, dst_strides_a, src_strides_a );
    BROADCAST_TO_V2_SUBCASE( case2e, indices, src_shape_f, dst_strides_f, src_strides_f );
    BROADCAST_TO_V2_SUBCASE( case2e, indices, src_shape_h, dst_strides_h, src_strides_h );
    BROADCAST_TO_V2_SUBCASE( case2e, indices, src_shape_v, dst_strides_v, src_strides_v );
    BROADCAST_TO_V2_SUBCASE( case2e, indices, src_shape_sv, dst_strides_sv, src_strides_sv );

    BROADCAST_TO_V2_SUBCASE( case2e, indices_ct, src_shape_ct, dst_strides_ct, src_strides_ct );

    BROADCAST_TO_V2_RESULT_SUBCASE( case2e, result_nl1, indices_nl1, src_shape_nl1, dst_strides_nl1, src_strides_nl1 );

    BROADCAST_TO_V2_SUBCASE( case2e, indices_mx1, src_shape_mx1, dst_strides_mx1, src_strides_mx1 );
}

TEST_CASE("broadcast_to_v2(case2f)" * doctest::test_suite("index::broadcast_to_v2"))
{
    BROADCAST_TO_V2_SUBCASE( case2f, indices, src_shape, dst_strides, src_strides );
    BROADCAST_TO_V2_SUBCASE( case2f, indices, src_shape_a, dst_strides_a, src_strides_a );
    BROADCAST_TO_V2_SUBCASE( case2f, indices, src_shape_f, dst_strides_f, src_strides_f );
    BROADCAST_TO_V2_SUBCASE( case2f, indices, src_shape_h, dst_strides_h, src_strides_h );
    BROADCAST_TO_V2_SUBCASE( case2f, indices, src_shape_v, dst_strides_v, src_strides_v );
    BROADCAST_TO_V2_SUBCASE( case2f, indices, src_shape_sv, dst_strides_sv, src_strides_sv );

    BROADCAST_TO_V2_SUBCASE( case2f, indices_ct, src_shape_ct, dst_strides_ct, src_strides_ct );

    BROADCAST_TO_V2_RESULT_SUBCASE( case2f, result_nl1, indices_nl1, src_shape_nl1, dst_strides_nl1, src_strides_nl1 );

    BROADCAST_TO_V2_SUBCASE( case2f, indices_mx1, src_shape_mx1, dst_strides_mx1, src_strides_mx1 );
}

TEST_CASE("broadcast_to_v2(case3a)" * doctest::test_suite("index::broadcast_to_v2"))
{
    BROADCAST_TO_V2_SUBCASE( case3a, indices, src_shape, dst_strides, src_strides );
    BROADCAST_TO_V2_SUBCASE( case3a, indices, src_shape_a, dst_strides_a, src_strides_a );
    BROADCAST_TO_V2_SUBCASE( case3a, indices, src_shape_f, dst_strides_f, src_strides_f );
    BROADCAST_TO_V2_SUBCASE( case3a, indices, src_shape_h, dst_strides_h, src_strides_h );
    BROADCAST_TO_V2_SUBCASE( case3a, indices, src_shape_v, dst_strides_v, src_strides_v );
    BROADCAST_TO_V2_SUBCASE( case3a, indices, src_shape_sv, dst_strides_sv, src_strides_sv );

    BROADCAST_TO_V2_SUBCASE( case3a, indices_ct, src_shape_ct, dst_strides_ct, src_strides_ct );

    BROADCAST_TO_V2_RESULT_SUBCASE( case3a, result_nl1, indices_nl1, src_shape_nl1, dst_strides_nl1, src_strides_nl1 );

    BROADCAST_TO_V2_SUBCASE( case3a, indices_mx1, src_shape_mx1, dst_strides_mx1, src_strides_mx1 );
}

TEST_CASE("broadcast_to_v2(case3b)" * doctest::test_suite("index::broadcast_to_v2"))
{
    BROADCAST_TO_V2_SUBCASE( case3b, indices, src_shape, dst_strides, src_strides );
    BROADCAST_TO_V2_SUBCASE( case3b, indices, src_shape_a, dst_strides_a, src_strides_a );
    BROADCAST_TO_V2_SUBCASE( case3b, indices, src_shape_f, dst_strides_f, src_strides_f );
    BROADCAST_TO_V2_SUBCASE( case3b, indices, src_shape_h, dst_strides_h, src_strides_h );
    BROADCAST_TO_V2_SUBCASE( case3b, indices, src_shape_v, dst_strides_v, src_strides_v );
    BROADCAST_TO_V2_SUBCASE( case3b, indices, src_shape_sv, dst_strides_sv, src_strides_sv );

    BROADCAST_TO_V2_SUBCASE( case3b, indices_ct, src_shape_ct, dst_strides_ct, src_strides_ct );

    BROADCAST_TO_V2_RESULT_SUBCASE( case3b, result_nl1, indices_nl1, src_shape_nl1, dst_strides_nl1, src_strides_nl1 );

    BROADCAST_TO_V2_SUBCASE( case3b, indices_mx1, src_shape_mx1, dst_strides_mx1, src_strides_mx1 );
}

TEST_CASE("broadcast_to_v2(case3c)" * doctest::test_suite("index::broadcast_to_v2"))
{
    BROADCAST_TO_V2_SUBCASE( case3c, indices, src_shape, dst_strides, src_strides );
    BROADCAST_TO_V2_SUBCASE( case3c, indices, src_shape_a, dst_strides_a, src_strides_a );
    BROADCAST_TO_V2_SUBCASE( case3c, indices, src_shape_f, dst_strides_f, src_strides_f );
    BROADCAST_TO_V2_SUBCASE( case3c, indices, src_shape_h, dst_strides_h, src_strides_h );
    BROADCAST_TO_V2_SUBCASE( case3c, indices, src_shape_v, dst_strides_v, src_strides_v );
    BROADCAST_TO_V2_SUBCASE( case3c, indices, src_shape_sv, dst_strides_sv, src_strides_sv );

    BROADCAST_TO_V2_SUBCASE( case3c, indices_ct, src_shape_ct, dst_strides_ct, src_strides_ct );

    BROADCAST_TO_V2_RESULT_SUBCASE( case3c, result_nl1, indices_nl1, src_shape_nl1, dst_strides_nl1, src_strides_nl1 );

    BROADCAST_TO_V2_SUBCASE( case3c, indices_mx1, src_shape_mx1, dst_strides_mx1, src_strides_mx1 );
}

TEST_CASE("broadcast_to_v2(case3d)" * doctest::test_suite("index::broadcast_to_v2"))
{
    BROADCAST_TO_V2_SUBCASE( case3d, indices, src_shape, dst_strides, src_strides );
    BROADCAST_TO_V2_SUBCASE( case3d, indices, src_shape_a, dst_strides_a, src_strides_a );
    BROADCAST_TO_V2_SUBCASE( case3d, indices, src_shape_f, dst_strides_f, src_strides_f );
    BROADCAST_TO_V2_SUBCASE( case3d, indices, src_shape_h, dst_strides_h, src_strides_h );
    BROADCAST_TO_V2_SUBCASE( case3d, indices, src_shape_v, dst_strides_v, src_strides_v );
    BROADCAST_TO_V2_SUBCASE( case3d, indices, src_shape_sv, dst_strides_sv, src_strides_sv );

    BROADCAST_TO_V2_SUBCASE( case3d, indices_ct, src_shape_ct, dst_strides_ct, src_strides_ct );

    BROADCAST_TO_V2_RESULT_SUBCASE( case3d, result_nl1, indices_nl1, src_shape_nl1, dst_strides_nl1, src_strides_nl1 );

    BROADCAST_TO_V2_SUBCASE( case3d, indices_mx1, src_shape_mx1, dst_strides_mx1, src_strides_mx1 );
}

TEST_CASE("broadcast_to_v2(case3e)" * doctest::test_suite("index::broadcast_to_v2"))
{
    BROADCAST_TO_V2_SUBCASE( case3e, indices, src_shape, dst_strides, src_strides );
    BROADCAST_TO_V2_SUBCASE( case3e, indices, src_shape_a, dst_strides_a, src_strides_a );
    BROADCAST_TO_V2_SUBCASE( case3e, indices, src_shape_f, dst_strides_f, src_strides_f );
    BROADCAST_TO_V2_SUBCASE( case3e, indices, src_shape_h, dst_strides_h, src_strides_h );
    BROADCAST_TO_V2_SUBCASE( case3e, indices, src_shape_v, dst_strides_v, src_strides_v );
    BROADCAST_TO_V2_SUBCASE( case3e, indices, src_shape_sv, dst_strides_sv, src_strides_sv );

    BROADCAST_TO_V2_SUBCASE( case3e, indices_ct, src_shape_ct, dst_strides_ct, src_strides_ct );

    BROADCAST_TO_V2_RESULT_SUBCASE( case3e, result_nl1, indices_nl1, src_shape_nl1, dst_strides_nl1, src_strides_nl1 );

    BROADCAST_TO_V2_SUBCASE( case3e, indices_mx1, src_shape_mx1, dst_strides_mx1, src_strides_mx1 );
}

TEST_CASE("broadcast_to_v2(case3f)" * doctest::test_suite("index::broadcast_to_v2"))
{
    BROADCAST_TO_V2_SUBCASE( case3f, indices, src_shape, dst_strides, src_strides );
    BROADCAST_TO_V2_SUBCASE( case3f, indices, src_shape_a, dst_strides_a, src_strides_a );
    BROADCAST_TO_V2_SUBCASE( case3f, indices, src_shape_f, dst_strides_f, src_strides_f );
    BROADCAST_TO_V2_SUBCASE( case3f, indices, src_shape_h, dst_strides_h, src_strides_h );
    BROADCAST_TO_V2_SUBCASE( case3f, indices, src_shape_v, dst_strides_v, src_strides_v );
    BROADCAST_TO_V2_SUBCASE( case3f, indices, src_shape_sv, dst_strides_sv, src_strides_sv );

    BROADCAST_TO_V2_SUBCASE( case3f, indices_ct, src_shape_ct, dst_strides_ct, src_strides_ct );

    BROADCAST_TO_V2_RESULT_SUBCASE( case3f, result_nl1, indices_nl1, src_shape_nl1, dst_strides_nl1, src_strides_nl1 );

    BROADCAST_TO_V2_SUBCASE( case3f, indices_mx1, src_shape_mx1, dst_strides_mx1, src_strides_mx1 );
}

TEST_CASE("broadcast_to_v2(case3g)" * doctest::test_suite("index::broadcast_to_v2"))
{
    BROADCAST_TO_V2_SUBCASE( case3g, indices, src_shape, dst_strides, src_strides );
    BROADCAST_TO_V2_SUBCASE( case3g, indices, src_shape_a, dst_strides_a, src_strides_a );
    BROADCAST_TO_V2_SUBCASE( case3g, indices, src_shape_f, dst_strides_f, src_strides_f );
    BROADCAST_TO_V2_SUBCASE( case3g, indices, src_shape_h, dst_strides_h, src_strides_h );
    BROADCAST_TO_V2_SUBCASE( case3g, indices, src_shape_v, dst_strides_v, src_strides_v );
    BROADCAST_TO_V2_SUBCASE( case3g, indices, src_shape_sv, dst_strides_sv, src_strides_sv );

    BROADCAST_TO_V2_SUBCASE( case3g, indices_ct, src_shape_ct, dst_strides_ct, src_strides_ct );

    BROADCAST_TO_V2_RESULT_SUBCASE( case3g, result_nl1, indices_nl1, src_shape_nl1, dst_strides_nl1, src_strides_nl1 );

    BROADCAST_TO_V2_SUBCASE( case3g, indices_mx1, src_shape_mx1, dst_strides_mx1, src_strides_mx1 );
}

TEST_CASE("broadcast_to_v2(case4a)" * doctest::test_suite("index::broadcast_to_v2"))
{
    BROADCAST_TO_V2_SUBCASE( case4a, indices, src_shape, dst_strides, src_strides );
    BROADCAST_TO_V2_SUBCASE( case4a, indices, src_shape_a, dst_strides_a, src_strides_a );
    BROADCAST_TO_V2_SUBCASE( case4a, indices, src_shape_f, dst_strides_f, src_strides_f );
    BROADCAST_TO_V2_SUBCASE( case4a, indices, src_shape_h, dst_strides_h, src_strides_h );
    BROADCAST_TO_V2_SUBCASE( case4a, indices, src_shape_v, dst_strides_v, src_strides_v );
    BROADCAST_TO_V2_SUBCASE( case4a, indices, src_shape_sv, dst_strides_sv, src_strides_sv );

    BROADCAST_TO_V2_SUBCASE( case4a, indices_ct, src_shape_ct, dst_strides_ct, src_strides_ct );

    BROADCAST_TO_V2_RESULT_SUBCASE( case4a, result_nl1, indices_nl1, src_shape_nl1, dst_strides_nl1, src_strides_nl1 );

    BROADCAST_TO_V2_SUBCASE( case4a, indices_mx1, src_shape_mx1, dst_strides_mx1, src_strides_mx1 );
}

TEST_CASE("broadcast_to_v2(case4b)" * doctest::test_suite("index::broadcast_to_v2"))
{
    BROADCAST_TO_V2_SUBCASE( case4b, indices, src_shape, dst_strides, src_strides );
    BROADCAST_TO_V2_SUBCASE( case4b, indices, src_shape_a, dst_strides_a, src_strides_a );
    BROADCAST_TO_V2_SUBCASE( case4b, indices, src_shape_f, dst_strides_f, src_strides_f );
    BROADCAST_TO_V2_SUBCASE( case4b, indices, src_shape_h, dst_strides_h, src_strides_h );
    BROADCAST_TO_V2_SUBCASE( case4b, indices, src_shape_v, dst_strides_v, src_strides_v );
    BROADCAST_TO_V2_SUBCASE( case4b, indices, src_shape_sv, dst_strides_sv, src_strides_sv );

    BROADCAST_TO_V2_SUBCASE( case4b, indices_ct, src_shape_ct, dst_strides_ct, src_strides_ct );

    BROADCAST_TO_V2_RESULT_SUBCASE( case4b, result_nl1, indices_nl1, src_shape_nl1, dst_strides_nl1, src_strides_nl1 );

    BROADCAST_TO_V2_SUBCASE( case4b, indices_mx1, src_shape_mx1, dst_strides_mx1, src_strides_mx1 );
}

TEST_CASE("broadcast_to_v2(case4c)" * doctest::test_suite("index::broadcast_to_v2"))
{
    BROADCAST_TO_V2_SUBCASE( case4c, indices, src_shape, dst_strides, src_strides );
    BROADCAST_TO_V2_SUBCASE( case4c, indices, src_shape_a, dst_strides_a, src_strides_a );
    BROADCAST_TO_V2_SUBCASE( case4c, indices, src_shape_f, dst_strides_f, src_strides_f );
    BROADCAST_TO_V2_SUBCASE( case4c, indices, src_shape_h, dst_strides_h, src_strides_h );
    BROADCAST_TO_V2_SUBCASE( case4c, indices, src_shape_v, dst_strides_v, src_strides_v );
    BROADCAST_TO_V2_SUBCASE( case4c, indices, src_shape_sv, dst_strides_sv, src_strides_sv );

    BROADCAST_TO_V2_SUBCASE( case4c, indices_ct, src_shape_ct, dst_strides_ct, src_strides_ct );

    BROADCAST_TO_V2_RESULT_SUBCASE( case4c, result_nl1, indices_nl1, src_shape_nl1, dst_strides_nl1, src_strides_nl1 );

    BROADCAST_TO_V2_SUBCASE( case4c, indices_mx1, src_shape_mx1, dst_strides_mx1, src_strides_mx1 );
}

TEST_CASE("broadcast_to_v2(case4d)" * doctest::test_suite("index::broadcast_to_v2"))
{
    BROADCAST_TO_V2_SUBCASE( case4d, indices, src_shape, dst_strides, src_strides );
    BROADCAST_TO_V2_SUBCASE( case4d, indices, src_shape_a, dst_strides_a, src_strides_a );
    BROADCAST_TO_V2_SUBCASE( case4d, indices, src_shape_f, dst_strides_f, src_strides_f );
    BROADCAST_TO_V2_SUBCASE( case4d, indices, src_shape_h, dst_strides_h, src_strides_h );
    BROADCAST_TO_V2_SUBCASE( case4d, indices, src_shape_v, dst_strides_v, src_strides_v );
    BROADCAST_TO_V2_SUBCASE( case4d, indices, src_shape_sv, dst_strides_sv, src_strides_sv );

    BROADCAST_TO_V2_SUBCASE( case4d, indices_ct, src_shape_ct, dst_strides_ct, src_strides_ct );

    BROADCAST_TO_V2_RESULT_SUBCASE( case4d, result_nl1, indices_nl1, src_shape_nl1, dst_strides_nl1, src_strides_nl1 );

    BROADCAST_TO_V2_SUBCASE( case4d, indices_mx1, src_shape_mx1, dst_strides_mx1, src_strides_mx1 );
}

TEST_CASE("broadcast_to_v2(case4e)" * doctest::test_suite("index::broadcast_to_v2"))
{
    BROADCAST_TO_V2_SUBCASE( case4e, indices, src_shape, dst_strides, src_strides );
    BROADCAST_TO_V2_SUBCASE( case4e, indices, src_shape_a, dst_strides_a, src_strides_a );
    BROADCAST_TO_V2_SUBCASE( case4e, indices, src_shape_f, dst_strides_f, src_strides_f );
    BROADCAST_TO_V2_SUBCASE( case4e, indices, src_shape_h, dst_strides_h, src_strides_h );
    BROADCAST_TO_V2_SUBCASE( case4e, indices, src_shape_v, dst_strides_v, src_strides_v );
    BROADCAST_TO_V2_SUBCASE( case4e, indices, src_shape_sv, dst_strides_sv, src_strides_sv );

    BROADCAST_TO_V2_SUBCASE( case4e, indices_ct, src_shape_ct, dst_strides_ct, src_strides_ct );

    BROADCAST_TO_V2_RESULT_SUBCASE( case4e, result_nl1, indices_nl1, src_shape_nl1, dst_strides_nl1, src_strides_nl1 );

    BROADCAST_TO_V2_SUBCASE( case4e, indices_mx1, src_shape_mx1, dst_strides_mx1, src_strides_mx1 );
}

TEST_CASE("broadcast_to_v2(case4f)" * doctest::test_suite("index::broadcast_to_v2"))
{
    BROADCAST_TO_V2_SUBCASE( case4f, indices, src_shape, dst_strides, src_strides );
    BROADCAST_TO_V2_SUBCASE( case4f, indices, src_shape_a, dst_strides_a, src_strides_a );
    BROADCAST_TO_V2_SUBCASE( case4f, indices, src_shape_f, dst_strides_f, src_strides_f );
    BROADCAST_TO_V2_SUBCASE( case4f, indices, src_shape_h, dst_strides_h, src_strides_h );
    BROADCAST_TO_V2_SUBCASE( case4f, indices, src_shape_v, dst_strides_v, src_strides_v );
    BROADCAST_TO_V2_SUBCASE( case4f, indices, src_shape_sv, dst_strides_sv, src_strides_sv );

    BROADCAST_TO_V2_SUBCASE( case4f, indices_ct, src_shape_ct, dst_strides_ct, src_strides_ct );

    BROADCAST_TO_V2_RESULT_SUBCASE( case4f, result_nl1, indices_nl1, src_shape_nl1, dst_strides_nl1, src_strides_nl1 );

    BROADCAST_TO_V2_SUBCASE( case4f, indices_mx1, src_shape_mx1, dst_strides_mx1, src_strides_mx1 );
}

TEST_CASE("broadcast_to_v2(case4g)" * doctest::test_suite("index::broadcast_to_v2"))
{
    BROADCAST_TO_V2_SUBCASE( case4g, indices, src_shape, dst_strides, src_strides );
    BROADCAST_TO_V2_SUBCASE( case4g, indices, src_shape_a, dst_strides_a, src_strides_a );
    BROADCAST_TO_V2_SUBCASE( case4g, indices, src_shape_f, dst_strides_f, src_strides_f );
    BROADCAST_TO_V2_SUBCASE( case4g, indices, src_shape_h, dst_strides_h, src_strides_h );
    BROADCAST_TO_V2_SUBCASE( case4g, indices, src_shape_v, dst_strides_v, src_strides_v );
    BROADCAST_TO_V2_SUBCASE( case4g, indices, src_shape_sv, dst_strides_sv, src_strides_sv );

    BROADCAST_TO_V2_SUBCASE( case4g, indices_ct, src_shape_ct, dst_strides_ct, src_strides_ct );

    BROADCAST_TO_V2_RESULT_SUBCASE( case4g, result_nl1, indices_nl1, src_shape_nl1, dst_strides_nl1, src_strides_nl1 );

    BROADCAST_TO_V2_SUBCASE( case4g, indices_mx1, src_shape_mx1, dst_strides_mx1, src_strides_mx1 );
}