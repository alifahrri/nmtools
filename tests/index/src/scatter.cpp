#include "nmtools/index/scatter.hpp"
#include "nmtools/testing/data/index/scatter.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
using namespace nm::literals;

#define CONSTEXPR_SCATTER_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(constexpr_scatter, case_name); \
    using namespace args; \
    constexpr auto result = nmtools::index::scatter(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::expected ); \
}

#define SCATTER_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(scatter, case_name); \
    using namespace args; \
    auto result = nmtools::index::scatter(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::expected ); \
}

#define SCATTER_EXPECTED_SUBCASE(case_name, expected, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(scatter, case_name); \
    using namespace args; \
    auto result = nmtools::index::scatter(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::expected ); \
}

TEST_CASE("scatter(case1)" * doctest::test_suite("index::scatter"))
{
    SCATTER_SUBCASE( case1, indices, order );
    SCATTER_SUBCASE( case1, indices_a, order_a );
    SCATTER_SUBCASE( case1, indices_f, order_f );
    SCATTER_SUBCASE( case1, indices_v, order_v );
    SCATTER_SUBCASE( case1, indices_h, order_h );

    SCATTER_SUBCASE( case1, indices_ct, order_ct );
    SCATTER_SUBCASE( case1, indices_a, order_ct );
    SCATTER_SUBCASE( case1, indices_f, order_ct );
    SCATTER_SUBCASE( case1, indices_v, order_ct );
    SCATTER_SUBCASE( case1, indices_h, order_ct );

    SCATTER_SUBCASE( case1, indices_ct, order );
    SCATTER_SUBCASE( case1, indices_ct, order_a );
    SCATTER_SUBCASE( case1, indices_ct, order_f );
    SCATTER_SUBCASE( case1, indices_ct, order_v );
    SCATTER_SUBCASE( case1, indices_ct, order_h );

    SCATTER_EXPECTED_SUBCASE( case1, expected_nl1, indices_nl1, order );
    SCATTER_EXPECTED_SUBCASE( case1, expected_nl2, indices_nl2, order );

    SCATTER_SUBCASE( case1, indices_mx1, order_ct );
    SCATTER_SUBCASE( case1, indices_mx2, order_ct );
}

TEST_CASE("scatter(case2)" * doctest::test_suite("index::scatter"))
{
    SCATTER_SUBCASE( case2, indices, order );
    SCATTER_SUBCASE( case2, indices_a, order_a );
    SCATTER_SUBCASE( case2, indices_f, order_f );
    SCATTER_SUBCASE( case2, indices_v, order_v );
    SCATTER_SUBCASE( case2, indices_h, order_h );

    SCATTER_SUBCASE( case2, indices_ct, order_ct );
    SCATTER_SUBCASE( case2, indices_a, order_ct );
    SCATTER_SUBCASE( case2, indices_f, order_ct );
    SCATTER_SUBCASE( case2, indices_v, order_ct );
    SCATTER_SUBCASE( case2, indices_h, order_ct );

    SCATTER_SUBCASE( case2, indices_ct, order );
    SCATTER_SUBCASE( case2, indices_ct, order_a );
    SCATTER_SUBCASE( case2, indices_ct, order_f );
    SCATTER_SUBCASE( case2, indices_ct, order_v );
    SCATTER_SUBCASE( case2, indices_ct, order_h );

    SCATTER_EXPECTED_SUBCASE( case2, expected_nl1, indices_nl1, order );
    SCATTER_EXPECTED_SUBCASE( case2, expected_nl2, indices_nl2, order );

    SCATTER_SUBCASE( case2, indices_mx1, order_ct );
    SCATTER_SUBCASE( case2, indices_mx2, order_ct );
}

TEST_CASE("scatter(case3)" * doctest::test_suite("index::scatter"))
{
    SCATTER_SUBCASE( case3, indices, order );
    SCATTER_SUBCASE( case3, indices_a, order_a );
    SCATTER_SUBCASE( case3, indices_f, order_f );
    SCATTER_SUBCASE( case3, indices_v, order_v );
    SCATTER_SUBCASE( case3, indices_h, order_h );

    SCATTER_SUBCASE( case3, indices_ct, order_ct );
    SCATTER_SUBCASE( case3, indices_a, order_ct );
    SCATTER_SUBCASE( case3, indices_f, order_ct );
    SCATTER_SUBCASE( case3, indices_v, order_ct );
    SCATTER_SUBCASE( case3, indices_h, order_ct );

    SCATTER_SUBCASE( case3, indices_ct, order );
    SCATTER_SUBCASE( case3, indices_ct, order_a );
    SCATTER_SUBCASE( case3, indices_ct, order_f );
    SCATTER_SUBCASE( case3, indices_ct, order_v );
    SCATTER_SUBCASE( case3, indices_ct, order_h );

    SCATTER_EXPECTED_SUBCASE( case3, expected_nl1, indices_nl1, order );
    SCATTER_EXPECTED_SUBCASE( case3, expected_nl2, indices_nl2, order );

    SCATTER_SUBCASE( case3, indices_mx1, order_ct );
    SCATTER_SUBCASE( case3, indices_mx2, order_ct );
}

TEST_CASE("scatter(case1)" * doctest::test_suite("index::constexpr_scatter"))
{
    CONSTEXPR_SCATTER_SUBCASE( case1, indices, order );
    CONSTEXPR_SCATTER_SUBCASE( case1, indices_a, order_a );
    CONSTEXPR_SCATTER_SUBCASE( case1, indices_f, order_f );
    CONSTEXPR_SCATTER_SUBCASE( case1, indices_h, order_h );

    CONSTEXPR_SCATTER_SUBCASE( case1, indices_ct, order_ct );

    CONSTEXPR_SCATTER_SUBCASE( case1, indices, order_ct );
    CONSTEXPR_SCATTER_SUBCASE( case1, indices_a, order_ct );
    CONSTEXPR_SCATTER_SUBCASE( case1, indices_f, order_ct );
    CONSTEXPR_SCATTER_SUBCASE( case1, indices_h, order_ct );

    CONSTEXPR_SCATTER_SUBCASE( case1, indices_ct, order );
    CONSTEXPR_SCATTER_SUBCASE( case1, indices_ct, order_a );
    CONSTEXPR_SCATTER_SUBCASE( case1, indices_ct, order_f );
    CONSTEXPR_SCATTER_SUBCASE( case1, indices_ct, order_h );
}

TEST_CASE("scatter(case2)" * doctest::test_suite("index::constexpr_scatter"))
{
    CONSTEXPR_SCATTER_SUBCASE( case2, indices, order );
    CONSTEXPR_SCATTER_SUBCASE( case2, indices_a, order_a );
    CONSTEXPR_SCATTER_SUBCASE( case2, indices_f, order_f );
    CONSTEXPR_SCATTER_SUBCASE( case2, indices_h, order_h );

    CONSTEXPR_SCATTER_SUBCASE( case2, indices_ct, order_ct );

    CONSTEXPR_SCATTER_SUBCASE( case2, indices, order_ct );
    CONSTEXPR_SCATTER_SUBCASE( case2, indices_a, order_ct );
    CONSTEXPR_SCATTER_SUBCASE( case2, indices_f, order_ct );
    CONSTEXPR_SCATTER_SUBCASE( case2, indices_h, order_ct );

    CONSTEXPR_SCATTER_SUBCASE( case2, indices_ct, order );
    CONSTEXPR_SCATTER_SUBCASE( case2, indices_ct, order_a );
    CONSTEXPR_SCATTER_SUBCASE( case2, indices_ct, order_f );
    CONSTEXPR_SCATTER_SUBCASE( case2, indices_ct, order_h );
}

TEST_CASE("scatter(case3)" * doctest::test_suite("index::constexpr_scatter"))
{
    CONSTEXPR_SCATTER_SUBCASE( case3, indices, order );
    CONSTEXPR_SCATTER_SUBCASE( case3, indices_a, order_a );
    CONSTEXPR_SCATTER_SUBCASE( case3, indices_f, order_f );
    CONSTEXPR_SCATTER_SUBCASE( case3, indices_h, order_h );

    CONSTEXPR_SCATTER_SUBCASE( case3, indices_ct, order_ct );

    CONSTEXPR_SCATTER_SUBCASE( case3, indices, order_ct );
    CONSTEXPR_SCATTER_SUBCASE( case3, indices_a, order_ct );
    CONSTEXPR_SCATTER_SUBCASE( case3, indices_f, order_ct );
    CONSTEXPR_SCATTER_SUBCASE( case3, indices_h, order_ct );

    CONSTEXPR_SCATTER_SUBCASE( case3, indices_ct, order );
    CONSTEXPR_SCATTER_SUBCASE( case3, indices_ct, order_a );
    CONSTEXPR_SCATTER_SUBCASE( case3, indices_ct, order_f );
    CONSTEXPR_SCATTER_SUBCASE( case3, indices_ct, order_h );
}