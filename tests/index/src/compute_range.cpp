#include "nmtools/index/slice.hpp"
#include "nmtools/testing/data/index/compute_range.hpp"
#include "nmtools/testing/doctest.hpp"

using namespace nmtools::literals;

#define COMPUTE_RANGE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index, compute_range, case_name); \
    using namespace args; \
    auto result = nmtools::index::compute_range(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("compute_range(case1)" * doctest::test_suite("index::compute_range"))
{
    COMPUTE_RANGE_SUBCASE(case1, si, start, stop, step);
}

TEST_CASE("compute_range(case2)" * doctest::test_suite("index::compute_range"))
{
    COMPUTE_RANGE_SUBCASE(case2, si, start, stop, step);
}

TEST_CASE("compute_range(case3)" * doctest::test_suite("index::compute_range"))
{
    COMPUTE_RANGE_SUBCASE(case3, si, start, stop, step);
}

TEST_CASE("compute_range(case4)" * doctest::test_suite("index::compute_range"))
{
    COMPUTE_RANGE_SUBCASE(case4, si, start, stop, step);
}

TEST_CASE("compute_range(case5)" * doctest::test_suite("index::compute_range"))
{
    COMPUTE_RANGE_SUBCASE(case5, si, start, stop, step);
}

TEST_CASE("compute_range(case6)" * doctest::test_suite("index::compute_range"))
{
    COMPUTE_RANGE_SUBCASE(case6, si, start, stop, step);
}

TEST_CASE("compute_range(case7)" * doctest::test_suite("index::compute_range"))
{
    COMPUTE_RANGE_SUBCASE(case7, si, start, stop, step);
}

TEST_CASE("compute_range(case8)" * doctest::test_suite("index::compute_range"))
{
    COMPUTE_RANGE_SUBCASE(case8, si, start, stop, step);
}

TEST_CASE("compute_range(case9)" * doctest::test_suite("index::compute_range"))
{
    COMPUTE_RANGE_SUBCASE(case9, si, start, stop, step);
}

TEST_CASE("compute_range(case10)" * doctest::test_suite("index::compute_range"))
{
    COMPUTE_RANGE_SUBCASE(case10, si, start, stop, step);
}

TEST_CASE("compute_range(case11)" * doctest::test_suite("index::compute_range"))
{
    COMPUTE_RANGE_SUBCASE(case11, si, start, stop, step);
}

TEST_CASE("compute_range(case12)" * doctest::test_suite("index::compute_range"))
{
    COMPUTE_RANGE_SUBCASE(case12, si, start, stop, step);
}
