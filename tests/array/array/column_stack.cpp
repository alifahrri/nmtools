#include "nmtools/array/column_stack.hpp"
#include "nmtools/testing/data/array/column_stack.hpp"
#include "nmtools/testing/doctest.hpp"

#define COLUMN_STACK_SUBCASE( case_name, ... ) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( array, column_stack, case_name ); \
    auto result = nmtools::column_stack( __VA_ARGS__ ); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("column_stack(case1)" * doctest::test_suite("array::column_stack"))
{
    COLUMN_STACK_SUBCASE( case1, a, b );
    COLUMN_STACK_SUBCASE( case1, a_a, b_a );
    COLUMN_STACK_SUBCASE( case1, a_f, b_f );
    COLUMN_STACK_SUBCASE( case1, a_h, b_h );
    COLUMN_STACK_SUBCASE( case1, a_d, b_d );
}

TEST_CASE("column_stack(case2)" * doctest::test_suite("array::column_stack"))
{
    COLUMN_STACK_SUBCASE( case2, a, b );
    COLUMN_STACK_SUBCASE( case2, a_a, b_a );
    COLUMN_STACK_SUBCASE( case2, a_f, b_f );
    COLUMN_STACK_SUBCASE( case2, a_h, b_h );
    COLUMN_STACK_SUBCASE( case2, a_d, b_d );
}

TEST_CASE("column_stack(case3)" * doctest::test_suite("array::column_stack"))
{
    COLUMN_STACK_SUBCASE( case3, a, b );
    COLUMN_STACK_SUBCASE( case3, a_a, b_a );
    COLUMN_STACK_SUBCASE( case3, a_f, b_f );
    COLUMN_STACK_SUBCASE( case3, a_h, b_h );
    COLUMN_STACK_SUBCASE( case3, a_d, b_d );
}