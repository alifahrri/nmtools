#include "nmtools/array/index/nonzero.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/testing/data/index/nonzero.hpp"

#define NONZERO_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(nonzero, case_name); \
    using namespace args; \
    auto result = ::nmtools::index::nonzero(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL_MSG_ATTRIBUTES( result, expect::result, __VA_ARGS__ ); \
} \

TEST_CASE("nonzero(case1)" * doctest::test_suite("index::nonzero"))
{
    NONZERO_SUBCASE( case1, x );
    NONZERO_SUBCASE( case1, x_a );
    NONZERO_SUBCASE( case1, x_v );
    NONZERO_SUBCASE( case1, x_f );
    NONZERO_SUBCASE( case1, x_h );

    NONZERO_SUBCASE( case1, m_x_a );
    NONZERO_SUBCASE( case1, m_x_v );
    NONZERO_SUBCASE( case1, m_x_f );
    NONZERO_SUBCASE( case1, m_x_h );

    NONZERO_SUBCASE( case1, x_ct );
    NONZERO_SUBCASE( case1, x_cl );
}

TEST_CASE("nonzero(case2)" * doctest::test_suite("index::nonzero"))
{
    NONZERO_SUBCASE( case2, x );
    NONZERO_SUBCASE( case2, x_a );
    NONZERO_SUBCASE( case2, x_v );
    NONZERO_SUBCASE( case2, x_f );
    NONZERO_SUBCASE( case2, x_h );

    NONZERO_SUBCASE( case2, m_x_a );
    NONZERO_SUBCASE( case2, m_x_v );
    NONZERO_SUBCASE( case2, m_x_f );
    NONZERO_SUBCASE( case2, m_x_h );

    NONZERO_SUBCASE( case2, x_ct );
    NONZERO_SUBCASE( case2, x_cl );
}

TEST_CASE("nonzero(case3)" * doctest::test_suite("index::nonzero"))
{
    NONZERO_SUBCASE( case3, x );
    NONZERO_SUBCASE( case3, x_a );
    NONZERO_SUBCASE( case3, x_v );
    NONZERO_SUBCASE( case3, x_f );
    NONZERO_SUBCASE( case3, x_h );

    NONZERO_SUBCASE( case3, m_x_a );
    NONZERO_SUBCASE( case3, m_x_v );
    NONZERO_SUBCASE( case3, m_x_f );
    NONZERO_SUBCASE( case3, m_x_h );
}