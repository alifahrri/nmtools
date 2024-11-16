#include "nmtools/array/index/split.hpp"
#include "nmtools/testing/data/index/split.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/utility/apply_isequal.hpp"

#define SPLIT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, split, case_name); \
    using namespace args; \
    auto result = nmtools::index::split(__VA_ARGS__); \
    auto lhs = nmtools::get<0>(result); \
    auto rhs = nmtools::get<1>(result); \
    NMTOOLS_ASSERT_EQUAL( lhs, expect::lhs ); \
    NMTOOLS_ASSERT_EQUAL( rhs, expect::rhs ); \
}

TEST_CASE("split(case1)" * doctest::test_suite("view::detail::split"))
{
    SPLIT_SUBCASE( case1, shape, N );
    SPLIT_SUBCASE( case1, shape_a, N );
    SPLIT_SUBCASE( case1, shape_v, N );
    SPLIT_SUBCASE( case1, shape_f, N );
    SPLIT_SUBCASE( case1, shape_h, N );
}

TEST_CASE("split(case2)" * doctest::test_suite("view::detail::split"))
{
    SPLIT_SUBCASE( case2, shape, N );
    SPLIT_SUBCASE( case2, shape_a, N );
    SPLIT_SUBCASE( case2, shape_v, N );
    SPLIT_SUBCASE( case2, shape_f, N );
    SPLIT_SUBCASE( case2, shape_h, N );
}

TEST_CASE("split(case3)" * doctest::test_suite("view::detail::split"))
{
    SPLIT_SUBCASE( case3, shape, N );
    SPLIT_SUBCASE( case3, shape_a, N );
    SPLIT_SUBCASE( case3, shape_v, N );
    SPLIT_SUBCASE( case3, shape_f, N );
    SPLIT_SUBCASE( case3, shape_h, N );
}

TEST_CASE("split(case4)" * doctest::test_suite("view::detail::split"))
{
    SPLIT_SUBCASE( case4, shape, N );
    SPLIT_SUBCASE( case4, shape_a, N );
    SPLIT_SUBCASE( case4, shape_v, N );
    SPLIT_SUBCASE( case4, shape_f, N );
    SPLIT_SUBCASE( case4, shape_h, N );
}

TEST_CASE("split(case5)" * doctest::test_suite("view::detail::split"))
{
    SPLIT_SUBCASE( case5, shape, N );
    SPLIT_SUBCASE( case5, shape_a, N );
    SPLIT_SUBCASE( case5, shape_v, N );
    SPLIT_SUBCASE( case5, shape_f, N );
    SPLIT_SUBCASE( case5, shape_h, N );
}

TEST_CASE("split(case6)" * doctest::test_suite("view::detail::split"))
{
    SPLIT_SUBCASE( case6, shape, N );
    SPLIT_SUBCASE( case6, shape_a, N );
    SPLIT_SUBCASE( case6, shape_v, N );
    SPLIT_SUBCASE( case6, shape_f, N );
    SPLIT_SUBCASE( case6, shape_h, N );
}

TEST_CASE("split(case7)" * doctest::test_suite("view::detail::split"))
{
    SPLIT_SUBCASE( case7, shape, N );
}