#include "nmtools/index/add_indices.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/testing/data/index/add_indices.hpp"

#define ADD_INDICES_RESULT_SUBCASE(case_name, res, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index, add_indices, case_name); \
    auto result = nmtools::index::add_indices(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::res ); \
}

#define ADD_INDICES_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index, add_indices, case_name); \
    auto result = nmtools::index::add_indices(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("add_indices(case1)" * doctest::test_suite("index::add_indices"))
{
    ADD_INDICES_SUBCASE( case1, lhs_indices, rhs_indices );
    ADD_INDICES_SUBCASE( case1, lhs_indices_a, rhs_indices_a );
    ADD_INDICES_SUBCASE( case1, lhs_indices_v, rhs_indices_v );
    ADD_INDICES_SUBCASE( case1, lhs_indices_f, rhs_indices_f );
    ADD_INDICES_SUBCASE( case1, lhs_indices_sv, rhs_indices_sv );

    ADD_INDICES_RESULT_SUBCASE( case1, result_nl1, lhs_indices_nl1, rhs_indices_nl1 );
    ADD_INDICES_RESULT_SUBCASE( case1, result_nl2, lhs_indices_nl2, rhs_indices_nl2 );

    ADD_INDICES_SUBCASE( case1, lhs_indices_mx1, rhs_indices_mx1 );
    ADD_INDICES_SUBCASE( case1, lhs_indices_mx2, rhs_indices_mx2 );

    ADD_INDICES_SUBCASE( case1, lhs_indices_ct, rhs_indices_ct );
    ADD_INDICES_SUBCASE( case1, lhs_indices_ct, rhs_indices_ct );
}

TEST_CASE("add_indices(case2)" * doctest::test_suite("index::add_indices"))
{
    ADD_INDICES_SUBCASE( case2, lhs_indices, rhs_indices );
    ADD_INDICES_SUBCASE( case2, lhs_indices_a, rhs_indices_a );
    ADD_INDICES_SUBCASE( case2, lhs_indices_v, rhs_indices_v );
    ADD_INDICES_SUBCASE( case2, lhs_indices_f, rhs_indices_f );
    ADD_INDICES_SUBCASE( case2, lhs_indices_sv, rhs_indices_sv );

    ADD_INDICES_RESULT_SUBCASE( case2, result_nl1, lhs_indices_nl1, rhs_indices_nl1 );
    ADD_INDICES_RESULT_SUBCASE( case2, result, lhs_indices_nl2, rhs_indices_nl2 );

    ADD_INDICES_SUBCASE( case2, lhs_indices_mx1, rhs_indices_mx1 );

    ADD_INDICES_SUBCASE( case2, lhs_indices_ct, rhs_indices_ct );
    ADD_INDICES_SUBCASE( case2, lhs_indices_ct, rhs_indices_ct );
}