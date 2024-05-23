#include "nmtools/array/view/ufuncs/power.hpp"
#include "nmtools/testing/data/array/power.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define POWER_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, power, case_name); \
    using namespace args; \
    auto result = view::power( __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("power(case1)" * doctest::test_suite("view::power"))
{
    POWER_SUBCASE( case1,   a,   b );
    POWER_SUBCASE( case1, a_a, b_a );
    // POWER_SUBCASE( case1, a_f, b_f );
    POWER_SUBCASE( case1, a_d, b_d );
    POWER_SUBCASE( case1, a_h, b_h );
}

TEST_CASE("power(case2)" * doctest::test_suite("view::power"))
{
    POWER_SUBCASE( case2,   a, b );
    POWER_SUBCASE( case2, a_a, b );
    // POWER_SUBCASE( case2, a_f, b );
    POWER_SUBCASE( case2, a_d, b );
    POWER_SUBCASE( case2, a_h, b );
}

#define REDUCE_POWER_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, reduce_power, case_name); \
    using namespace args; \
    auto result = view::reduce_power(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("reduce_power(case1)" * doctest::test_suite("view::reduce_power"))
{
    REDUCE_POWER_SUBCASE( case1,   a, axis );
    REDUCE_POWER_SUBCASE( case1, a_a, axis );
    // REDUCE_POWER_SUBCASE( case1, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_POWER_SUBCASE( case1, a_d, axis );
    // REDUCE_POWER_SUBCASE( case1, a_f, axis );
}

// may fail, not yet figured out casting for this case,
// this case results in bigger number than case3
// while current (promoted) casting still works for case3
TEST_CASE("reduce_power(case2)" * doctest::test_suite("view::reduce_power") * doctest::may_fail(true))
{
    REDUCE_POWER_SUBCASE( case2,   a, axis, dtype );
    REDUCE_POWER_SUBCASE( case2, a_a, axis, dtype );
    // REDUCE_POWER_SUBCASE( case2, a_f, axis, dtype );
    // dynamic dim array not supported yet
    // REDUCE_POWER_SUBCASE( case2, a_d, axis, dtype );
    // REDUCE_POWER_SUBCASE( case2, a_f, axis, dtype );
}

TEST_CASE("reduce_power(case3)" * doctest::test_suite("view::reduce_power"))
{
    REDUCE_POWER_SUBCASE( case3,   a, axis, dtype );
    REDUCE_POWER_SUBCASE( case3, a_a, axis, dtype );
    // REDUCE_POWER_SUBCASE( case3, a_f, axis, dtype );
    // dynamic dim array not supported yet
    // REDUCE_POWER_SUBCASE( case3, a_d, axis, dtype );
    // REDUCE_POWER_SUBCASE( case3, a_f, axis, dtype );
}

TEST_CASE("reduce_power(case4)" * doctest::test_suite("view::reduce_power"))
{
    REDUCE_POWER_SUBCASE( case4,   a, axis, dtype, initial );
    REDUCE_POWER_SUBCASE( case4, a_a, axis, dtype, initial );
    // REDUCE_POWER_SUBCASE( case4, a_f, axis, dtype, initial );
    // REDUCE_POWER_SUBCASE( case4, a_f, axis, dtype, initial );
}

TEST_CASE("reduce_power(case5)" * doctest::test_suite("view::reduce_power"))
{
    REDUCE_POWER_SUBCASE( case5,   a, axis, dtype, initial );
    REDUCE_POWER_SUBCASE( case5, a_a, axis, dtype, initial );
    // REDUCE_POWER_SUBCASE( case5, a_f, axis, dtype, initial );
    // REDUCE_POWER_SUBCASE( case5, a_f, axis, dtype, initial );
}

TEST_CASE("reduce_power(case6)" * doctest::test_suite("view::reduce_power"))
{
    REDUCE_POWER_SUBCASE( case6,   a, axis, dtype, initial, keepdims );
    REDUCE_POWER_SUBCASE( case6, a_a, axis, dtype, initial, keepdims );
    // REDUCE_POWER_SUBCASE( case6, a_f, axis, dtype, initial, keepdims );
    // REDUCE_POWER_SUBCASE( case6, a_f, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_power(case7)" * doctest::test_suite("view::reduce_power"))
{
    REDUCE_POWER_SUBCASE( case7,   a, axis, dtype, initial, keepdims );
    REDUCE_POWER_SUBCASE( case7, a_a, axis, dtype, initial, keepdims );
    // REDUCE_POWER_SUBCASE( case7, a_f, axis, dtype, initial, keepdims );
    // REDUCE_POWER_SUBCASE( case7, a_f, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_power(case8)" * doctest::test_suite("view::reduce_power"))
{
    REDUCE_POWER_SUBCASE( case8,   a, axis, dtype, initial, keepdims );
    REDUCE_POWER_SUBCASE( case8, a_a, axis, dtype, initial, keepdims );
    // REDUCE_POWER_SUBCASE( case8, a_f, axis, dtype, initial, keepdims );
    // REDUCE_POWER_SUBCASE( case8, a_f, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_power(case9)" * doctest::test_suite("view::reduce_power"))
{
    REDUCE_POWER_SUBCASE( case9,   a, axis, dtype, initial, keepdims );
    REDUCE_POWER_SUBCASE( case9, a_a, axis, dtype, initial, keepdims );
    // REDUCE_POWER_SUBCASE( case9, a_f, axis, dtype, initial, keepdims );
    // REDUCE_POWER_SUBCASE( case9, a_f, axis, dtype, initial, keepdims );
}

#define ACCUMULATE_POWER_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, accumulate_power, case_name); \
    using namespace args; \
    auto result = view::accumulate_power(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("accumulate_power(case1)" * doctest::test_suite("view::accumulate_power"))
{
    ACCUMULATE_POWER_SUBCASE( case1,   a, axis );
    ACCUMULATE_POWER_SUBCASE( case1, a_a, axis );
    // ACCUMULATE_POWER_SUBCASE( case1, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_POWER_SUBCASE( case1, a_d, axis );
    // NOTE: something wrong with fixed ndarray and long long (?)
    // TODO: fix
    // ACCUMULATE_POWER_SUBCASE( case1, a_f, axis );
}

TEST_CASE("accumulate_power(case2)" * doctest::test_suite("view::accumulate_power"))
{
    ACCUMULATE_POWER_SUBCASE( case2,   a, axis );
    ACCUMULATE_POWER_SUBCASE( case2, a_a, axis );
    // ACCUMULATE_POWER_SUBCASE( case2, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_POWER_SUBCASE( case2, a_d, axis );
    // ACCUMULATE_POWER_SUBCASE( case2, a_f, axis );
}

#define OUTER_POWER_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, outer_power, case_name); \
    using namespace args; \
    auto result = view::outer_power(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("outer_power(case1)" * doctest::test_suite("view::outer_power"))
{
    OUTER_POWER_SUBCASE( case1,   a,   b );
    OUTER_POWER_SUBCASE( case1, a_a, b_a );
    // OUTER_POWER_SUBCASE( case1, a_f, b_f );
    OUTER_POWER_SUBCASE( case1, a_d, b_d );
    OUTER_POWER_SUBCASE( case1, a_h, b_h );
}