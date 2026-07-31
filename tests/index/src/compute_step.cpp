#include "nmtools/index/slice.hpp"
#include "nmtools/testing/data/index/compute_step.hpp"
#include "nmtools/testing/doctest.hpp"

using namespace nmtools::literals;

#define COMPUTE_STEP_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index, compute_step, case_name); \
    using namespace args; \
    auto result = nmtools::index::compute_step(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("compute_step(case1)" * doctest::test_suite("index::compute_step"))
{
    COMPUTE_STEP_SUBCASE(case1, step);
}

TEST_CASE("compute_step(case2)" * doctest::test_suite("index::compute_step"))
{
    COMPUTE_STEP_SUBCASE(case2, step);
}

TEST_CASE("compute_step(case3)" * doctest::test_suite("index::compute_step"))
{
    COMPUTE_STEP_SUBCASE(case3, step);
}

TEST_CASE("compute_step(case4)" * doctest::test_suite("index::compute_step"))
{
    COMPUTE_STEP_SUBCASE(case4, step);
}
