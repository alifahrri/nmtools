#include "nmtools/array/trace.hpp"
#include "nmtools/testing/data/array/trace.hpp"
#include "nmtools/testing/doctest.hpp"

#define TRACE_SUBCASE(case_name,...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( array, trace, case_name ); \
    auto result = nmtools::trace(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("trace(case1)" * doctest::test_suite("array::trace"))
{
    SUBCASE("meta")
    {
        NMTOOLS_TESTING_USE_CASE( array, trace, case1 );
        {
            auto result = nmtools::trace( a );
            using result_t = decltype(result);
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, result_t );
        }
    }
    // TODO: fix
    // TRACE_SUBCASE( case1, a );
    // TRACE_SUBCASE( case1, a_a );
    // TRACE_SUBCASE( case1, a_f );
    // TRACE_SUBCASE( case1, a_h );
    // TRACE_SUBCASE( case1, a_d );
}

TEST_CASE("trace(case3)" * doctest::test_suite("array::trace"))
{
    TRACE_SUBCASE( case3, a, offset, axis1, axis2 );
    TRACE_SUBCASE( case3, a_a, offset, axis1, axis2 );
    TRACE_SUBCASE( case3, a_f, offset, axis1, axis2 );
    TRACE_SUBCASE( case3, a_h, offset, axis1, axis2 );
    TRACE_SUBCASE( case3, a_d, offset, axis1, axis2 );

    TRACE_SUBCASE( case3, a, offset_ct, axis1_ct, axis2_ct );
    TRACE_SUBCASE( case3, a_a, offset_ct, axis1_ct, axis2_ct );
    TRACE_SUBCASE( case3, a_f, offset_ct, axis1_ct, axis2_ct );
}

TEST_CASE("trace(case4)" * doctest::test_suite("array::trace"))
{
    TRACE_SUBCASE( case4, a, offset, axis1, axis2 );
    TRACE_SUBCASE( case4, a_a, offset, axis1, axis2 );
    TRACE_SUBCASE( case4, a_f, offset, axis1, axis2 );
    TRACE_SUBCASE( case4, a_h, offset, axis1, axis2 );
    TRACE_SUBCASE( case4, a_d, offset, axis1, axis2 );

    TRACE_SUBCASE( case4, a, offset_ct, axis1_ct, axis2_ct );
    TRACE_SUBCASE( case4, a_a, offset_ct, axis1_ct, axis2_ct );
    TRACE_SUBCASE( case4, a_f, offset_ct, axis1_ct, axis2_ct );
}

TEST_CASE("trace(case5)" * doctest::test_suite("array::trace"))
{
    TRACE_SUBCASE( case5, a, offset, axis1, axis2 );
    TRACE_SUBCASE( case5, a_a, offset, axis1, axis2 );
    TRACE_SUBCASE( case5, a_f, offset, axis1, axis2 );
    TRACE_SUBCASE( case5, a_h, offset, axis1, axis2 );
    TRACE_SUBCASE( case5, a_d, offset, axis1, axis2 );

    TRACE_SUBCASE( case5, a, offset_ct, axis1_ct, axis2_ct );
    TRACE_SUBCASE( case5, a_a, offset_ct, axis1_ct, axis2_ct );
    TRACE_SUBCASE( case5, a_f, offset_ct, axis1_ct, axis2_ct );
}

TEST_CASE("trace(case6)" * doctest::test_suite("array::trace"))
{
    TRACE_SUBCASE( case6, a, offset, axis1, axis2 );
    TRACE_SUBCASE( case6, a_a, offset, axis1, axis2 );
    TRACE_SUBCASE( case6, a_f, offset, axis1, axis2 );
    TRACE_SUBCASE( case6, a_h, offset, axis1, axis2 );
    TRACE_SUBCASE( case6, a_d, offset, axis1, axis2 );

    TRACE_SUBCASE( case6, a, offset_ct, axis1_ct, axis2_ct );
    TRACE_SUBCASE( case6, a_a, offset_ct, axis1_ct, axis2_ct );
    TRACE_SUBCASE( case6, a_f, offset_ct, axis1_ct, axis2_ct );
}

TEST_CASE("trace(case7)" * doctest::test_suite("array::trace"))
{
    TRACE_SUBCASE( case7, a, offset, axis1, axis2 );
    TRACE_SUBCASE( case7, a_a, offset, axis1, axis2 );
    TRACE_SUBCASE( case7, a_f, offset, axis1, axis2 );
    TRACE_SUBCASE( case7, a_h, offset, axis1, axis2 );
    TRACE_SUBCASE( case7, a_d, offset, axis1, axis2 );

    TRACE_SUBCASE( case7, a, offset_ct, axis1_ct, axis2_ct );
    TRACE_SUBCASE( case7, a_a, offset_ct, axis1_ct, axis2_ct );
    TRACE_SUBCASE( case7, a_f, offset_ct, axis1_ct, axis2_ct );
}

TEST_CASE("trace(case8)" * doctest::test_suite("array::trace"))
{
    TRACE_SUBCASE( case8, a, offset, axis1, axis2 );
    TRACE_SUBCASE( case8, a_a, offset, axis1, axis2 );
    TRACE_SUBCASE( case8, a_f, offset, axis1, axis2 );
    TRACE_SUBCASE( case8, a_h, offset, axis1, axis2 );
    TRACE_SUBCASE( case8, a_d, offset, axis1, axis2 );

    TRACE_SUBCASE( case8, a, offset_ct, axis1_ct, axis2_ct );
    TRACE_SUBCASE( case8, a_a, offset_ct, axis1_ct, axis2_ct );
    TRACE_SUBCASE( case8, a_f, offset_ct, axis1_ct, axis2_ct );
}

TEST_CASE("trace(case9)" * doctest::test_suite("array::trace"))
{
    TRACE_SUBCASE( case9, a, offset, axis1, axis2 );
    TRACE_SUBCASE( case9, a_a, offset, axis1, axis2 );
    TRACE_SUBCASE( case9, a_f, offset, axis1, axis2 );
    TRACE_SUBCASE( case9, a_h, offset, axis1, axis2 );
    TRACE_SUBCASE( case9, a_d, offset, axis1, axis2 );

    TRACE_SUBCASE( case9, a, offset_ct, axis1_ct, axis2_ct );
    TRACE_SUBCASE( case9, a_a, offset_ct, axis1_ct, axis2_ct );
    TRACE_SUBCASE( case9, a_f, offset_ct, axis1_ct, axis2_ct );
}

TEST_CASE("trace(case10)" * doctest::test_suite("array::trace"))
{
    TRACE_SUBCASE( case10, a, offset, axis1, axis2 );
    TRACE_SUBCASE( case10, a_a, offset, axis1, axis2 );
    TRACE_SUBCASE( case10, a_f, offset, axis1, axis2 );
    TRACE_SUBCASE( case10, a_h, offset, axis1, axis2 );
    TRACE_SUBCASE( case10, a_d, offset, axis1, axis2 );

    TRACE_SUBCASE( case10, a, offset_ct, axis1_ct, axis2_ct );
    TRACE_SUBCASE( case10, a_a, offset_ct, axis1_ct, axis2_ct );
    TRACE_SUBCASE( case10, a_f, offset_ct, axis1_ct, axis2_ct );
}

TEST_CASE("trace(case11)" * doctest::test_suite("array::trace"))
{
    TRACE_SUBCASE( case11, a, offset, axis1, axis2 );
    TRACE_SUBCASE( case11, a_a, offset, axis1, axis2 );
    TRACE_SUBCASE( case11, a_f, offset, axis1, axis2 );
    TRACE_SUBCASE( case11, a_h, offset, axis1, axis2 );
    TRACE_SUBCASE( case11, a_d, offset, axis1, axis2 );

    TRACE_SUBCASE( case11, a, offset_ct, axis1_ct, axis2_ct );
    TRACE_SUBCASE( case11, a_a, offset_ct, axis1_ct, axis2_ct );
    TRACE_SUBCASE( case11, a_f, offset_ct, axis1_ct, axis2_ct );
}

TEST_CASE("trace(case12)" * doctest::test_suite("array::trace"))
{
    TRACE_SUBCASE( case12, a, offset, axis1, axis2 );
    TRACE_SUBCASE( case12, a_a, offset, axis1, axis2 );
    TRACE_SUBCASE( case12, a_f, offset, axis1, axis2 );
    TRACE_SUBCASE( case12, a_h, offset, axis1, axis2 );
    TRACE_SUBCASE( case12, a_d, offset, axis1, axis2 );

    TRACE_SUBCASE( case12, a, offset_ct, axis1_ct, axis2_ct );
    TRACE_SUBCASE( case12, a_a, offset_ct, axis1_ct, axis2_ct );
    TRACE_SUBCASE( case12, a_f, offset_ct, axis1_ct, axis2_ct );
}

TEST_CASE("trace(case13)" * doctest::test_suite("array::trace"))
{
    TRACE_SUBCASE( case13, a, offset, axis1, axis2 );
    TRACE_SUBCASE( case13, a_a, offset, axis1, axis2 );
    TRACE_SUBCASE( case13, a_f, offset, axis1, axis2 );
    TRACE_SUBCASE( case13, a_h, offset, axis1, axis2 );
    TRACE_SUBCASE( case13, a_d, offset, axis1, axis2 );

    TRACE_SUBCASE( case13, a, offset_ct, axis1_ct, axis2_ct );
    TRACE_SUBCASE( case13, a_a, offset_ct, axis1_ct, axis2_ct );
    TRACE_SUBCASE( case13, a_f, offset_ct, axis1_ct, axis2_ct );
}

TEST_CASE("trace(case14)" * doctest::test_suite("array::trace"))
{
    TRACE_SUBCASE( case14, a, offset, axis1, axis2, dtype );
    TRACE_SUBCASE( case14, a_a, offset, axis1, axis2, dtype );
    TRACE_SUBCASE( case14, a_f, offset, axis1, axis2, dtype );
    TRACE_SUBCASE( case14, a_h, offset, axis1, axis2, dtype );
    TRACE_SUBCASE( case14, a_d, offset, axis1, axis2, dtype );

    TRACE_SUBCASE( case14, a, offset_ct, axis1_ct, axis2_ct, dtype );
    TRACE_SUBCASE( case14, a_a, offset_ct, axis1_ct, axis2_ct, dtype );
    TRACE_SUBCASE( case14, a_f, offset_ct, axis1_ct, axis2_ct, dtype );
}