#include "nmtools/array/ufuncs/right_shift.hpp"
#include "nmtools/testing/data/array/right_shift.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace view = nm::view;

#define RIGHT_SHIFT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, right_shift, case_name); \
    using namespace args; \
    auto result = view::right_shift(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("right_shift(case1)" * doctest::test_suite("view::right_shift"))
{
    RIGHT_SHIFT_SUBCASE( case1,   a,   b );
    RIGHT_SHIFT_SUBCASE( case1, a_a, b_a );
    RIGHT_SHIFT_SUBCASE( case1, a_f, b_f );
    RIGHT_SHIFT_SUBCASE( case1, a_d, b_d );
    RIGHT_SHIFT_SUBCASE( case1, a_h, b_h );
}

TEST_CASE("right_shift(case2)" * doctest::test_suite("view::right_shift"))
{
    RIGHT_SHIFT_SUBCASE( case2,   a, b );
    RIGHT_SHIFT_SUBCASE( case2, a_a, b );
    RIGHT_SHIFT_SUBCASE( case2, a_f, b );
    RIGHT_SHIFT_SUBCASE( case2, a_d, b );
    RIGHT_SHIFT_SUBCASE( case2, a_h, b );
}

#define REDUCE_RIGHT_SHIFT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, reduce_right_shift, case_name); \
    using namespace args; \
    auto result = view::reduce_right_shift( __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("reduce_right_shift(case1)" * doctest::test_suite("view::reduce_right_shift"))
{
    REDUCE_RIGHT_SHIFT_SUBCASE( case1,   a, axis );
    REDUCE_RIGHT_SHIFT_SUBCASE( case1, a_a, axis );
    REDUCE_RIGHT_SHIFT_SUBCASE( case1, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_RIGHT_SHIFT_SUBCASE( case1, a_d, axis );
    REDUCE_RIGHT_SHIFT_SUBCASE( case1, a_h, axis );
}

TEST_CASE("reduce_right_shift(case2)" * doctest::test_suite("view::reduce_right_shift"))
{
    REDUCE_RIGHT_SHIFT_SUBCASE( case2,   a, axis );
    REDUCE_RIGHT_SHIFT_SUBCASE( case2, a_a, axis );
    REDUCE_RIGHT_SHIFT_SUBCASE( case2, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_RIGHT_SHIFT_SUBCASE( case2, a_d, axis );
    REDUCE_RIGHT_SHIFT_SUBCASE( case2, a_h, axis );
}

TEST_CASE("reduce_right_shift(case3)" * doctest::test_suite("view::reduce_right_shift"))
{
    REDUCE_RIGHT_SHIFT_SUBCASE( case3,   a, axis );
    REDUCE_RIGHT_SHIFT_SUBCASE( case3, a_a, axis );
    REDUCE_RIGHT_SHIFT_SUBCASE( case3, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_RIGHT_SHIFT_SUBCASE( case3, a_d, axis );
    REDUCE_RIGHT_SHIFT_SUBCASE( case3, a_h, axis );
}

TEST_CASE("reduce_right_shift(case4)" * doctest::test_suite("view::reduce_right_shift"))
{
    REDUCE_RIGHT_SHIFT_SUBCASE( case4,   a, axis, dtype, initial );
    REDUCE_RIGHT_SHIFT_SUBCASE( case4, a_a, axis, dtype, initial );
    REDUCE_RIGHT_SHIFT_SUBCASE( case4, a_f, axis, dtype, initial );
    REDUCE_RIGHT_SHIFT_SUBCASE( case4, a_h, axis, dtype, initial );
}

TEST_CASE("reduce_right_shift(case5)" * doctest::test_suite("view::reduce_right_shift"))
{
    REDUCE_RIGHT_SHIFT_SUBCASE( case5,   a, axis, dtype, initial, keepdims );
    REDUCE_RIGHT_SHIFT_SUBCASE( case5, a_a, axis, dtype, initial, keepdims );
    REDUCE_RIGHT_SHIFT_SUBCASE( case5, a_f, axis, dtype, initial, keepdims );
    REDUCE_RIGHT_SHIFT_SUBCASE( case5, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_right_shift(case6)" * doctest::test_suite("view::reduce_right_shift"))
{
    REDUCE_RIGHT_SHIFT_SUBCASE( case6,   a, axis, dtype, initial, keepdims );
    REDUCE_RIGHT_SHIFT_SUBCASE( case6, a_a, axis, dtype, initial, keepdims );
    REDUCE_RIGHT_SHIFT_SUBCASE( case6, a_f, axis, dtype, initial, keepdims );
    REDUCE_RIGHT_SHIFT_SUBCASE( case6, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_right_shift(case7)" * doctest::test_suite("view::reduce_right_shift"))
{
    REDUCE_RIGHT_SHIFT_SUBCASE( case7,   a, axis, dtype, initial, keepdims );
    REDUCE_RIGHT_SHIFT_SUBCASE( case7, a_a, axis, dtype, initial, keepdims );
    REDUCE_RIGHT_SHIFT_SUBCASE( case7, a_f, axis, dtype, initial, keepdims );
    REDUCE_RIGHT_SHIFT_SUBCASE( case7, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_right_shift(case8)" * doctest::test_suite("view::reduce_right_shift"))
{
    REDUCE_RIGHT_SHIFT_SUBCASE( case8,   a, axis, dtype, initial, keepdims );
    REDUCE_RIGHT_SHIFT_SUBCASE( case8, a_a, axis, dtype, initial, keepdims );
    REDUCE_RIGHT_SHIFT_SUBCASE( case8, a_f, axis, dtype, initial, keepdims );
    REDUCE_RIGHT_SHIFT_SUBCASE( case8, a_h, axis, dtype, initial, keepdims );
}

#define ACCUMULATE_RIGHT_SHIFT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, accumulate_right_shift, case_name); \
    using namespace args; \
    auto result = view::accumulate_right_shift(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("accumulate_right_shift(case1)" * doctest::test_suite("view::accumulate_right_shift"))
{
    ACCUMULATE_RIGHT_SHIFT_SUBCASE( case1,   a, axis );
    ACCUMULATE_RIGHT_SHIFT_SUBCASE( case1, a_a, axis );
    ACCUMULATE_RIGHT_SHIFT_SUBCASE( case1, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_RIGHT_SHIFT_SUBCASE( case1, a_d, axis );
    ACCUMULATE_RIGHT_SHIFT_SUBCASE( case1, a_h, axis );
}

TEST_CASE("accumulate_right_shift(case2)" * doctest::test_suite("view::accumulate_right_shift"))
{
    ACCUMULATE_RIGHT_SHIFT_SUBCASE( case2,   a, axis );
    ACCUMULATE_RIGHT_SHIFT_SUBCASE( case2, a_a, axis );
    ACCUMULATE_RIGHT_SHIFT_SUBCASE( case2, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_RIGHT_SHIFT_SUBCASE( case2, a_d, axis );
    ACCUMULATE_RIGHT_SHIFT_SUBCASE( case2, a_h, axis );
}

TEST_CASE("accumulate_right_shift(case3)" * doctest::test_suite("view::accumulate_right_shift"))
{
    ACCUMULATE_RIGHT_SHIFT_SUBCASE( case3,   a, axis );
    ACCUMULATE_RIGHT_SHIFT_SUBCASE( case3, a_a, axis );
    ACCUMULATE_RIGHT_SHIFT_SUBCASE( case3, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_RIGHT_SHIFT_SUBCASE( case3, a_d, axis );
    ACCUMULATE_RIGHT_SHIFT_SUBCASE( case3, a_h, axis );
}

#define OUTER_RIGHT_SHIFT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, outer_right_shift, case_name); \
    using namespace args; \
    auto result = view::outer_right_shift(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("outer_right_shift(case1)" * doctest::test_suite("view::outer_right_shift"))
{
    OUTER_RIGHT_SHIFT_SUBCASE( case1,   a,   b );
    OUTER_RIGHT_SHIFT_SUBCASE( case1, a_a, b_a );
    OUTER_RIGHT_SHIFT_SUBCASE( case1, a_f, b_f );
    OUTER_RIGHT_SHIFT_SUBCASE( case1, a_d, b_d );
    OUTER_RIGHT_SHIFT_SUBCASE( case1, a_h, b_h );
}