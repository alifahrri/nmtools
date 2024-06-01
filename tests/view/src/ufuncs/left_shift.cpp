#include "nmtools/array/view/ufuncs/left_shift.hpp"
#include "nmtools/testing/data/array/left_shift.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define LEFT_SHIFT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, left_shift, case_name); \
    using namespace args; \
    auto result = view::left_shift(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("left_shift(case1)" * doctest::test_suite("view::left_shift"))
{
    LEFT_SHIFT_SUBCASE( case1,   a,   b );
    LEFT_SHIFT_SUBCASE( case1, a_a, b_a );
    LEFT_SHIFT_SUBCASE( case1, a_f, b_f );
    LEFT_SHIFT_SUBCASE( case1, a_d, b_d );
    LEFT_SHIFT_SUBCASE( case1, a_h, b_h );
}

TEST_CASE("left_shift(case2)" * doctest::test_suite("view::left_shift"))
{
    LEFT_SHIFT_SUBCASE( case2,   a, b );
    LEFT_SHIFT_SUBCASE( case2, a_a, b );
    LEFT_SHIFT_SUBCASE( case2, a_f, b );
    LEFT_SHIFT_SUBCASE( case2, a_d, b );
    LEFT_SHIFT_SUBCASE( case2, a_h, b );
}

#define REDUCE_LEFT_SHIFT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, reduce_left_shift, case_name); \
    using namespace args; \
    auto result = view::reduce_left_shift(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("reduce_left_shift(case1)" * doctest::test_suite("view::reduce_left_shift"))
{
    REDUCE_LEFT_SHIFT_SUBCASE( case1,   a, axis );
    REDUCE_LEFT_SHIFT_SUBCASE( case1, a_a, axis );
    REDUCE_LEFT_SHIFT_SUBCASE( case1, a_f, axis );
    REDUCE_LEFT_SHIFT_SUBCASE( case1, a_h, axis );
    // dynamic dim array not supported yet
    // REDUCE_LEFT_SHIFT_SUBCASE( case1, a_d, axis );
}

TEST_CASE("reduce_left_shift(case2)" * doctest::test_suite("view::reduce_left_shift"))
{
    REDUCE_LEFT_SHIFT_SUBCASE( case2,   a, axis );
    REDUCE_LEFT_SHIFT_SUBCASE( case2, a_a, axis );
    REDUCE_LEFT_SHIFT_SUBCASE( case2, a_f, axis );
    REDUCE_LEFT_SHIFT_SUBCASE( case2, a_h, axis );
    // dynamic dim array not supported yet
    // REDUCE_LEFT_SHIFT_SUBCASE( case2, a_d, axis );
}

TEST_CASE("reduce_left_shift(case3)" * doctest::test_suite("view::reduce_left_shift"))
{
    REDUCE_LEFT_SHIFT_SUBCASE( case3,   a, axis );
    REDUCE_LEFT_SHIFT_SUBCASE( case3, a_a, axis );
    REDUCE_LEFT_SHIFT_SUBCASE( case3, a_f, axis );
    REDUCE_LEFT_SHIFT_SUBCASE( case3, a_h, axis );
    // dynamic dim array not supported yet
    // REDUCE_LEFT_SHIFT_SUBCASE( case3, a_d, axis );
}

TEST_CASE("reduce_left_shift(case4)" * doctest::test_suite("view::reduce_left_shift"))
{
    REDUCE_LEFT_SHIFT_SUBCASE( case4,   a, axis, dtype );
    REDUCE_LEFT_SHIFT_SUBCASE( case4, a_a, axis, dtype );
    REDUCE_LEFT_SHIFT_SUBCASE( case4, a_f, axis, dtype );
    REDUCE_LEFT_SHIFT_SUBCASE( case4, a_h, axis, dtype );
}

TEST_CASE("reduce_left_shift(case5)" * doctest::test_suite("view::reduce_left_shift"))
{
    REDUCE_LEFT_SHIFT_SUBCASE( case5,   a, axis, dtype, initial );
    REDUCE_LEFT_SHIFT_SUBCASE( case5, a_a, axis, dtype, initial );
    REDUCE_LEFT_SHIFT_SUBCASE( case5, a_f, axis, dtype, initial );
    REDUCE_LEFT_SHIFT_SUBCASE( case5, a_h, axis, dtype, initial );
}

TEST_CASE("reduce_left_shift(case6)" * doctest::test_suite("view::reduce_left_shift"))
{
    REDUCE_LEFT_SHIFT_SUBCASE( case6,   a, axis, dtype, initial, keepdims );
    REDUCE_LEFT_SHIFT_SUBCASE( case6, a_a, axis, dtype, initial, keepdims );
    REDUCE_LEFT_SHIFT_SUBCASE( case6, a_f, axis, dtype, initial, keepdims );
    REDUCE_LEFT_SHIFT_SUBCASE( case6, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_left_shift(case7)" * doctest::test_suite("view::reduce_left_shift"))
{
    REDUCE_LEFT_SHIFT_SUBCASE( case7,   a, axis, dtype, initial, keepdims );
    REDUCE_LEFT_SHIFT_SUBCASE( case7, a_a, axis, dtype, initial, keepdims );
    REDUCE_LEFT_SHIFT_SUBCASE( case7, a_f, axis, dtype, initial, keepdims );
    REDUCE_LEFT_SHIFT_SUBCASE( case7, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_left_shift(case8)" * doctest::test_suite("view::reduce_left_shift"))
{
    REDUCE_LEFT_SHIFT_SUBCASE( case8,   a, axis, dtype, initial, keepdims );
    REDUCE_LEFT_SHIFT_SUBCASE( case8, a_a, axis, dtype, initial, keepdims );
    REDUCE_LEFT_SHIFT_SUBCASE( case8, a_f, axis, dtype, initial, keepdims );
    REDUCE_LEFT_SHIFT_SUBCASE( case8, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_left_shift(case9)" * doctest::test_suite("view::reduce_left_shift"))
{
    REDUCE_LEFT_SHIFT_SUBCASE( case9,   a, axis, dtype, initial, keepdims );
    REDUCE_LEFT_SHIFT_SUBCASE( case9, a_a, axis, dtype, initial, keepdims );
    REDUCE_LEFT_SHIFT_SUBCASE( case9, a_f, axis, dtype, initial, keepdims );
    REDUCE_LEFT_SHIFT_SUBCASE( case9, a_h, axis, dtype, initial, keepdims );
}

#define ACCUMULATE_LEFT_SHIFT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, accumulate_left_shift, case_name); \
    using namespace args; \
    auto result = view::accumulate_left_shift(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("accumulate_left_shift(case1)" * doctest::test_suite("view::accumulate_left_shift"))
{
    ACCUMULATE_LEFT_SHIFT_SUBCASE( case1,   a, axis );
    ACCUMULATE_LEFT_SHIFT_SUBCASE( case1, a_a, axis );
    ACCUMULATE_LEFT_SHIFT_SUBCASE( case1, a_f, axis );
    ACCUMULATE_LEFT_SHIFT_SUBCASE( case1, a_h, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_LEFT_SHIFT_SUBCASE( case1, a_d, axis );
}

TEST_CASE("accumulate_left_shift(case2)" * doctest::test_suite("view::accumulate_left_shift"))
{
    ACCUMULATE_LEFT_SHIFT_SUBCASE( case2,   a, axis );
    ACCUMULATE_LEFT_SHIFT_SUBCASE( case2, a_a, axis );
    ACCUMULATE_LEFT_SHIFT_SUBCASE( case2, a_f, axis );
    ACCUMULATE_LEFT_SHIFT_SUBCASE( case2, a_h, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_LEFT_SHIFT_SUBCASE( case2, a_d, axis );
}

TEST_CASE("accumulate_left_shift(case3)" * doctest::test_suite("view::accumulate_left_shift"))
{
    ACCUMULATE_LEFT_SHIFT_SUBCASE( case3,   a, axis );
    ACCUMULATE_LEFT_SHIFT_SUBCASE( case3, a_a, axis );
    ACCUMULATE_LEFT_SHIFT_SUBCASE( case3, a_f, axis );
    ACCUMULATE_LEFT_SHIFT_SUBCASE( case3, a_h, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_LEFT_SHIFT_SUBCASE( case3, a_d, axis );
}

#define OUTER_LEFT_SHIFT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, outer_left_shift, case_name); \
    using namespace args; \
    auto result = view::outer_left_shift(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("outer_left_shift(case1)" * doctest::test_suite("view::outer_left_shift"))
{
    OUTER_LEFT_SHIFT_SUBCASE( case1,   a,   b );
    OUTER_LEFT_SHIFT_SUBCASE( case1, a_a, b_a );
    OUTER_LEFT_SHIFT_SUBCASE( case1, a_f, b_f );
    OUTER_LEFT_SHIFT_SUBCASE( case1, a_d, b_d );
    OUTER_LEFT_SHIFT_SUBCASE( case1, a_h, b_h );
}