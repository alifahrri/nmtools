#include "nmtools/index/compute_strides.hpp"
#include "nmtools/testing/data/index/compute_blocked_strides.hpp"
#include "nmtools/utility/isequal.hpp"
#include "nmtools/testing/doctest.hpp"

using nmtools::utils::isequal;
using namespace nmtools::literals;

#define COMPUTE_BLOCKED_STRIDES_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(compute_blocked_strides, case_name); \
    using namespace args; \
    auto result = nmtools::index::compute_blocked_strides(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL_MSG_ATTRIBUTES( result, expect::result, __VA_ARGS__ ); \
}

#define CONSTEXPR_COMPUTE_BLOCKED_STRIDES_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(compute_blocked_strides, case_name); \
    using namespace args; \
    constexpr auto result = nmtools::index::compute_blocked_strides(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL_MSG_ATTRIBUTES( result, expect::result, __VA_ARGS__ ); \
}

// note: only fixed-size shape/block variants are supported because
// grid shapes and the nested result type need compile-time length
#define COMPUTE_BLOCKED_STRIDES_ALL_SUBCASES(case_name) \
    COMPUTE_BLOCKED_STRIDES_SUBCASE(case_name, shape, block, grid_order, inner_order); \
    COMPUTE_BLOCKED_STRIDES_SUBCASE(case_name, shape_a, block_a, grid_order, inner_order); \
    COMPUTE_BLOCKED_STRIDES_SUBCASE(case_name, shape_f, block_f, grid_order, inner_order); \
    CONSTEXPR_COMPUTE_BLOCKED_STRIDES_SUBCASE(case_name, shape_ct, block_ct, grid_order, inner_order);

TEST_CASE("compute_blocked_strides(case1)" * doctest::test_suite("index::compute_blocked_strides"))
{
    // blocked column major, matches testing/data/array/stride.hpp case18
    COMPUTE_BLOCKED_STRIDES_ALL_SUBCASES(case1)
}

TEST_CASE("compute_blocked_strides(case2)" * doctest::test_suite("index::compute_blocked_strides"))
{
    COMPUTE_BLOCKED_STRIDES_ALL_SUBCASES(case2)
}

TEST_CASE("compute_blocked_strides(case3)" * doctest::test_suite("index::compute_blocked_strides"))
{
    COMPUTE_BLOCKED_STRIDES_ALL_SUBCASES(case3)
}

TEST_CASE("compute_blocked_strides(case4)" * doctest::test_suite("index::compute_blocked_strides"))
{
    COMPUTE_BLOCKED_STRIDES_ALL_SUBCASES(case4)
}

TEST_CASE("compute_blocked_strides(case5)" * doctest::test_suite("index::compute_blocked_strides"))
{
    COMPUTE_BLOCKED_STRIDES_ALL_SUBCASES(case5)
}
