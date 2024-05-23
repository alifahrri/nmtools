#include "nmtools/array/view/ufuncs/subtract.hpp"
#include "nmtools/testing/data/array/subtract.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define SUBTRACT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, subtract, case_name); \
    using namespace args; \
    auto result = view::subtract(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("subtract(case1)" * doctest::test_suite("view::subtract"))
{
    SUBTRACT_SUBCASE( case1,   a,   b );
    SUBTRACT_SUBCASE( case1, a_a, b_a );
    SUBTRACT_SUBCASE( case1, a_f, b_f );
    SUBTRACT_SUBCASE( case1, a_d, b_d );
    SUBTRACT_SUBCASE( case1, a_h, b_h );
}

TEST_CASE("subtract(case2)" * doctest::test_suite("view::subtract"))
{
    SUBTRACT_SUBCASE( case2,   a, b );
    SUBTRACT_SUBCASE( case2, a_a, b );
    SUBTRACT_SUBCASE( case2, a_f, b );
    SUBTRACT_SUBCASE( case2, a_d, b );
    SUBTRACT_SUBCASE( case2, a_h, b );
}

#define REDUCE_SUBTRACT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, reduce_subtract, case_name); \
    using namespace args; \
    auto result = view::reduce_subtract(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("reduce_subtract(case1)" * doctest::test_suite("view::reduce_subtract"))
{
    REDUCE_SUBTRACT_SUBCASE( case1,   a, axis );
    REDUCE_SUBTRACT_SUBCASE( case1, a_a, axis );
    REDUCE_SUBTRACT_SUBCASE( case1, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_SUBTRACT_SUBCASE( case1, a_d, axis );
    REDUCE_SUBTRACT_SUBCASE( case1, a_f, axis );
}

TEST_CASE("reduce_subtract(case2)" * doctest::test_suite("view::reduce_subtract"))
{
    REDUCE_SUBTRACT_SUBCASE( case2,   a, axis );
    REDUCE_SUBTRACT_SUBCASE( case2, a_a, axis );
    REDUCE_SUBTRACT_SUBCASE( case2, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_SUBTRACT_SUBCASE( case2, a_d, axis );
    REDUCE_SUBTRACT_SUBCASE( case2, a_f, axis );
}

TEST_CASE("reduce_subtract(case3)" * doctest::test_suite("view::reduce_subtract"))
{
    REDUCE_SUBTRACT_SUBCASE( case3,   a, axis );
    REDUCE_SUBTRACT_SUBCASE( case3, a_a, axis );
    REDUCE_SUBTRACT_SUBCASE( case3, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_SUBTRACT_SUBCASE( case3, a_d, axis );
    REDUCE_SUBTRACT_SUBCASE( case3, a_f, axis );
}

TEST_CASE("reduce_subtract(case4)" * doctest::test_suite("view::reduce_subtract"))
{
    REDUCE_SUBTRACT_SUBCASE( case4,   a, axis, dtype, initial );
    REDUCE_SUBTRACT_SUBCASE( case4, a_a, axis, dtype, initial );
    REDUCE_SUBTRACT_SUBCASE( case4, a_f, axis, dtype, initial );
    REDUCE_SUBTRACT_SUBCASE( case4, a_f, axis, dtype, initial );
}

TEST_CASE("reduce_subtract(case5)" * doctest::test_suite("view::reduce_subtract"))
{
    REDUCE_SUBTRACT_SUBCASE( case5,   a, axis, dtype, initial, keepdims );
    REDUCE_SUBTRACT_SUBCASE( case5, a_a, axis, dtype, initial, keepdims );
    REDUCE_SUBTRACT_SUBCASE( case5, a_f, axis, dtype, initial, keepdims );
    REDUCE_SUBTRACT_SUBCASE( case5, a_f, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_subtract(case6)" * doctest::test_suite("view::reduce_subtract"))
{
    REDUCE_SUBTRACT_SUBCASE( case6,   a, axis, dtype, initial, keepdims );
    REDUCE_SUBTRACT_SUBCASE( case6, a_a, axis, dtype, initial, keepdims );
    REDUCE_SUBTRACT_SUBCASE( case6, a_f, axis, dtype, initial, keepdims );
    REDUCE_SUBTRACT_SUBCASE( case6, a_f, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_subtract(case7)" * doctest::test_suite("view::reduce_subtract"))
{
    REDUCE_SUBTRACT_SUBCASE( case7,   a, axis, dtype, initial, keepdims );
    REDUCE_SUBTRACT_SUBCASE( case7, a_a, axis, dtype, initial, keepdims );
    REDUCE_SUBTRACT_SUBCASE( case7, a_f, axis, dtype, initial, keepdims );
    REDUCE_SUBTRACT_SUBCASE( case7, a_f, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_subtract(case8)" * doctest::test_suite("view::reduce_subtract"))
{
    REDUCE_SUBTRACT_SUBCASE( case8,   a, axis, dtype, initial, keepdims );
    REDUCE_SUBTRACT_SUBCASE( case8, a_a, axis, dtype, initial, keepdims );
    REDUCE_SUBTRACT_SUBCASE( case8, a_f, axis, dtype, initial, keepdims );
    REDUCE_SUBTRACT_SUBCASE( case8, a_f, axis, dtype, initial, keepdims );
}

#define ACCUMULATE_SUBTRACT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, accumulate_subtract, case_name); \
    using namespace args; \
    auto result = view::accumulate_subtract(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("accumulate_subtract(case1)" * doctest::test_suite("view::accumulate_subtract"))
{
    ACCUMULATE_SUBTRACT_SUBCASE( case1,   a, axis );
    ACCUMULATE_SUBTRACT_SUBCASE( case1, a_a, axis );
    ACCUMULATE_SUBTRACT_SUBCASE( case1, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_SUBTRACT_SUBCASE( case1, a_d, axis );
    ACCUMULATE_SUBTRACT_SUBCASE( case1, a_h, axis );
}

TEST_CASE("accumulate_subtract(case2)" * doctest::test_suite("view::accumulate_subtract"))
{
    ACCUMULATE_SUBTRACT_SUBCASE( case2,   a, axis );
    ACCUMULATE_SUBTRACT_SUBCASE( case2, a_a, axis );
    ACCUMULATE_SUBTRACT_SUBCASE( case2, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_SUBTRACT_SUBCASE( case2, a_d, axis );
    ACCUMULATE_SUBTRACT_SUBCASE( case2, a_h, axis );
}

TEST_CASE("accumulate_subtract(case3)" * doctest::test_suite("view::accumulate_subtract"))
{
    ACCUMULATE_SUBTRACT_SUBCASE( case3,   a, axis );
    ACCUMULATE_SUBTRACT_SUBCASE( case3, a_a, axis );
    ACCUMULATE_SUBTRACT_SUBCASE( case3, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_SUBTRACT_SUBCASE( case3, a_d, axis );
    ACCUMULATE_SUBTRACT_SUBCASE( case3, a_h, axis );
}

#define OUTER_SUBTRACT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, outer_subtract, case_name); \
    using namespace args; \
    auto result = view::outer_subtract( __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("outer_subtract(case1)" * doctest::test_suite("view::outer_subtract"))
{
    OUTER_SUBTRACT_SUBCASE( case1,   a,   b );
    OUTER_SUBTRACT_SUBCASE( case1, a_a, b_a );
    OUTER_SUBTRACT_SUBCASE( case1, a_f, b_f );
    OUTER_SUBTRACT_SUBCASE( case1, a_d, b_d );
    OUTER_SUBTRACT_SUBCASE( case1, a_h, b_h );
}