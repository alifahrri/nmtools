#include "nmtools/array/ufuncs/maximum.hpp"
#include "nmtools/testing/data/array/maximum.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define MAXIMUM_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, maximum, case_name); \
    using namespace args; \
    auto result = view::maximum(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("maximum(case1)" * doctest::test_suite("view::maximum"))
{
    MAXIMUM_SUBCASE( case1,   a,   b );
    MAXIMUM_SUBCASE( case1, a_a, b_a );
    MAXIMUM_SUBCASE( case1, a_f, b_f );
    MAXIMUM_SUBCASE( case1, a_d, b_d );
    MAXIMUM_SUBCASE( case1, a_h, b_h );
}

TEST_CASE("maximum(case2)" * doctest::test_suite("view::maximum"))
{
    MAXIMUM_SUBCASE( case2,   a, b );
    MAXIMUM_SUBCASE( case2, a_a, b );
    MAXIMUM_SUBCASE( case2, a_f, b );
    MAXIMUM_SUBCASE( case2, a_d, b );
    MAXIMUM_SUBCASE( case2, a_h, b );
}

#define REDUCE_MAXIMUM_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, reduce_maximum, case_name); \
    using namespace args; \
    auto result = view::reduce_maximum( __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("reduce_maximum(case1)" * doctest::test_suite("view::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case1,   a, axis );
    REDUCE_MAXIMUM_SUBCASE( case1, a_a, axis );
    REDUCE_MAXIMUM_SUBCASE( case1, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_MAXIMUM_SUBCASE( case1, a_d, axis );
    REDUCE_MAXIMUM_SUBCASE( case1, a_h, axis );
}

TEST_CASE("reduce_maximum(case2)" * doctest::test_suite("view::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case2,   a, axis );
    REDUCE_MAXIMUM_SUBCASE( case2, a_a, axis );
    REDUCE_MAXIMUM_SUBCASE( case2, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_MAXIMUM_SUBCASE( case2, a_d, axis );
    REDUCE_MAXIMUM_SUBCASE( case2, a_h, axis );
}

TEST_CASE("reduce_maximum(case3)" * doctest::test_suite("view::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case3,   a, axis );
    REDUCE_MAXIMUM_SUBCASE( case3, a_a, axis );
    REDUCE_MAXIMUM_SUBCASE( case3, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_MAXIMUM_SUBCASE( case3, a_d, axis );
    REDUCE_MAXIMUM_SUBCASE( case3, a_h, axis );
}

TEST_CASE("reduce_maximum(case4)" * doctest::test_suite("view::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case4,   a, axis );
    REDUCE_MAXIMUM_SUBCASE( case4, a_a, axis );
    REDUCE_MAXIMUM_SUBCASE( case4, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_MAXIMUM_SUBCASE( case4, a_d, axis );
    REDUCE_MAXIMUM_SUBCASE( case4, a_h, axis );
}

TEST_CASE("reduce_maximum(case5)" * doctest::test_suite("view::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case5,   a, axis );
    REDUCE_MAXIMUM_SUBCASE( case5, a_a, axis );
    REDUCE_MAXIMUM_SUBCASE( case5, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_MAXIMUM_SUBCASE( case5, a_d, axis );
    REDUCE_MAXIMUM_SUBCASE( case5, a_h, axis );
}

TEST_CASE("reduce_maximum(case6)" * doctest::test_suite("view::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case6,   a, axis );
    REDUCE_MAXIMUM_SUBCASE( case6, a_a, axis );
    REDUCE_MAXIMUM_SUBCASE( case6, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_MAXIMUM_SUBCASE( case6, a_d, axis );
    REDUCE_MAXIMUM_SUBCASE( case6, a_h, axis );
}

TEST_CASE("reduce_maximum(case7)" * doctest::test_suite("view::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case7,   a, axis, dtype, initial );
    REDUCE_MAXIMUM_SUBCASE( case7, a_a, axis, dtype, initial );
    REDUCE_MAXIMUM_SUBCASE( case7, a_f, axis, dtype, initial );
    REDUCE_MAXIMUM_SUBCASE( case7, a_h, axis, dtype, initial );
}

TEST_CASE("reduce_maximum(case8)" * doctest::test_suite("view::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case8,   a, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case8, a_a, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case8, a_f, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case8, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_maximum(case9)" * doctest::test_suite("view::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case9,   a, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case9, a_a, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case9, a_f, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case9, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_maximum(case10)" * doctest::test_suite("view::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case10,   a, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case10, a_a, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case10, a_f, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case10, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_maximum(case11)" * doctest::test_suite("view::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case11,   a, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case11, a_a, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case11, a_f, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case11, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_maximum(case12)" * doctest::test_suite("view::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case12,   a, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case12, a_a, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case12, a_f, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case12, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_maximum(case13)" * doctest::test_suite("view::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case13,   a, axis );
    REDUCE_MAXIMUM_SUBCASE( case13, a_a, axis );
    REDUCE_MAXIMUM_SUBCASE( case13, a_f, axis );
    REDUCE_MAXIMUM_SUBCASE( case13, a_h, axis );
}

TEST_CASE("reduce_maximum(case14)" * doctest::test_suite("view::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case14,   a, axis, nm::None, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case14, a_a, axis, nm::None, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case14, a_f, axis, nm::None, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case14, a_h, axis, nm::None, initial, keepdims );
}

TEST_CASE("reduce_maximum(case15)" * doctest::test_suite("view::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case15,   a, axis, nm::None, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case15, a_a, axis, nm::None, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case15, a_f, axis, nm::None, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case15, a_h, axis, nm::None, initial, keepdims );
}

TEST_CASE("reduce_maximum(case16)" * doctest::test_suite("view::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case16,   a, axis, nm::None, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case16, a_a, axis, nm::None, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case16, a_f, axis, nm::None, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case16, a_h, axis, nm::None, initial, keepdims );
}

TEST_CASE("reduce_maximum(case17)" * doctest::test_suite("view::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case17,   a, axis, nm::None, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case17, a_a, axis, nm::None, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case17, a_f, axis, nm::None, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case17, a_h, axis, nm::None, initial, keepdims );
}

#define ACCUMULATE_MAXIMUM_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, accumulate_maximum, case_name); \
    using namespace args; \
    auto result = view::accumulate_maximum(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("accumulate_maximum(case1)" * doctest::test_suite("view::accumulate_maximum"))
{
    ACCUMULATE_MAXIMUM_SUBCASE( case1,   a, axis );
    ACCUMULATE_MAXIMUM_SUBCASE( case1, a_a, axis );
    ACCUMULATE_MAXIMUM_SUBCASE( case1, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_MAXIMUM_SUBCASE( case1, a_d, axis );
    ACCUMULATE_MAXIMUM_SUBCASE( case1, a_f, axis );
}

TEST_CASE("accumulate_maximum(case2)" * doctest::test_suite("view::accumulate_maximum"))
{
    ACCUMULATE_MAXIMUM_SUBCASE( case2,   a, axis );
    ACCUMULATE_MAXIMUM_SUBCASE( case2, a_a, axis );
    ACCUMULATE_MAXIMUM_SUBCASE( case2, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_MAXIMUM_SUBCASE( case2, a_d, axis );
    ACCUMULATE_MAXIMUM_SUBCASE( case2, a_f, axis );
}

TEST_CASE("accumulate_maximum(case3)" * doctest::test_suite("view::accumulate_maximum"))
{
    ACCUMULATE_MAXIMUM_SUBCASE( case3,   a, axis );
    ACCUMULATE_MAXIMUM_SUBCASE( case3, a_a, axis );
    ACCUMULATE_MAXIMUM_SUBCASE( case3, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_MAXIMUM_SUBCASE( case3, a_d, axis );
    ACCUMULATE_MAXIMUM_SUBCASE( case3, a_f, axis );
}

#define OUTER_MAXIMUM_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, outer_maximum, case_name); \
    using namespace args; \
    auto result = view::outer_maximum(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("outer_maximum(case1)" * doctest::test_suite("view::outer_maximum"))
{
    OUTER_MAXIMUM_SUBCASE( case1,   a,   b );
    OUTER_MAXIMUM_SUBCASE( case1, a_a, b_a );
    OUTER_MAXIMUM_SUBCASE( case1, a_f, b_f );
    OUTER_MAXIMUM_SUBCASE( case1, a_d, b_d );
    OUTER_MAXIMUM_SUBCASE( case1, a_h, b_h );
}