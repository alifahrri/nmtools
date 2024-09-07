#include "nmtools/array/array/expand.hpp"
#include "nmtools/testing/data/array/expand.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;

#define EXPAND_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
   NMTOOLS_TESTING_USE_CASE( array, expand, case_name ); \
   using namespace args; \
   auto result = nmtools::array::expand(__VA_ARGS__) ; \
   NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect::result) ); \
   NMTOOLS_ASSERT_CLOSE_MSG_OPERANDS( result, expect::result, __VA_ARGS__ ); \
}

// TODO: fix runtime crash on utl
#ifndef NMTOOLS_DISABLE_STL
TEST_CASE("expand(case1)" * doctest::test_suite("array::expand"))
{
    EXPAND_SUBCASE( case1,   input, axis, spacing, fill_value );
    EXPAND_SUBCASE( case1, input_a, axis, spacing, fill_value );
    EXPAND_SUBCASE( case1, input_f, axis, spacing, fill_value );
    EXPAND_SUBCASE( case1, input_h, axis, spacing, fill_value );
    EXPAND_SUBCASE( case1, input_d, axis, spacing, fill_value );
}

TEST_CASE("expand(case2)" * doctest::test_suite("array::expand"))
{
    EXPAND_SUBCASE( case2, input, axis, spacing );
    EXPAND_SUBCASE( case2, input_a, axis, spacing );
    EXPAND_SUBCASE( case2, input_f, axis, spacing );
    EXPAND_SUBCASE( case2, input_h, axis, spacing );
    EXPAND_SUBCASE( case2, input_d, axis, spacing );
}

TEST_CASE("expand(case3)" * doctest::test_suite("array::expand"))
{
    EXPAND_SUBCASE( case3, input, axis );
    EXPAND_SUBCASE( case3, input_a, axis );
    EXPAND_SUBCASE( case3, input_f, axis );
    EXPAND_SUBCASE( case3, input_h, axis );
    EXPAND_SUBCASE( case3, input_d, axis );
}
#endif

// TODO: fix runtime crash on utl
#ifndef NMTOOLS_DISABLE_STL
TEST_CASE("expand(case4)" * doctest::test_suite("array::expand"))
{
    EXPAND_SUBCASE( case4, input, axis, spacing, fill_value );
    EXPAND_SUBCASE( case4, input_a, axis, spacing, fill_value );
    EXPAND_SUBCASE( case4, input_f, axis, spacing, fill_value );
    EXPAND_SUBCASE( case4, input_h, axis, spacing, fill_value );
    EXPAND_SUBCASE( case4, input_d, axis, spacing, fill_value );
}

TEST_CASE("expand(case5)" * doctest::test_suite("array::expand"))
{
    EXPAND_SUBCASE( case5, input, axis );
    EXPAND_SUBCASE( case5, input_a, axis );
    EXPAND_SUBCASE( case5, input_f, axis );
    EXPAND_SUBCASE( case5, input_h, axis );
    EXPAND_SUBCASE( case5, input_d, axis );
}

TEST_CASE("expand(case6)" * doctest::test_suite("array::expand"))
{
    EXPAND_SUBCASE( case6, input, axis, spacing );
    EXPAND_SUBCASE( case6, input_a, axis, spacing );
    EXPAND_SUBCASE( case6, input_f, axis, spacing );
    EXPAND_SUBCASE( case6, input_h, axis, spacing );
    EXPAND_SUBCASE( case6, input_d, axis, spacing );
}
#endif

TEST_CASE("expand(case7)" * doctest::test_suite("array::expand"))
{
    EXPAND_SUBCASE( case7, input, axis );
    EXPAND_SUBCASE( case7, input_a, axis );
    EXPAND_SUBCASE( case7, input_f, axis );
    EXPAND_SUBCASE( case7, input_h, axis );
    EXPAND_SUBCASE( case7, input_d, axis );
}

// TODO: fix runtime crash on utl
#ifndef NMTOOLS_DISABLE_STL
TEST_CASE("expand(case8)" * doctest::test_suite("array::expand"))
{
    EXPAND_SUBCASE( case8, input, axis );
    EXPAND_SUBCASE( case8, input_a, axis );
    EXPAND_SUBCASE( case8, input_f, axis );
    EXPAND_SUBCASE( case8, input_h, axis );
    EXPAND_SUBCASE( case8, input_d, axis );
}
#endif