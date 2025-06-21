#include "nmtools/array/ufuncs/multiply.hpp"
#include "nmtools/testing/data/array/multiply.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace view = nm::view;

#define MULTIPLY_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, multiply, case_name); \
    using namespace args; \
    auto result = view::multiply(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("multiply(case1)" * doctest::test_suite("view::multiply"))
{
    MULTIPLY_SUBCASE( case1,   a,   b );
    MULTIPLY_SUBCASE( case1, a_a, b_a );
    MULTIPLY_SUBCASE( case1, a_f, b_f );
    MULTIPLY_SUBCASE( case1, a_d, b_d );
    MULTIPLY_SUBCASE( case1, a_h, b_h );
}

TEST_CASE("multiply(case2)" * doctest::test_suite("view::multiply"))
{
    MULTIPLY_SUBCASE( case2,   a, b );
    MULTIPLY_SUBCASE( case2, a_a, b );
    MULTIPLY_SUBCASE( case2, a_f, b );
    MULTIPLY_SUBCASE( case2, a_d, b );
    MULTIPLY_SUBCASE( case2, a_h, b );
}

#define REDUCE_MULTIPLY_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, reduce_multiply, case_name); \
    using namespace args; \
    auto result = view::reduce_multiply(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("reduce_multiply(case1)" * doctest::test_suite("view::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case1,   a, axis );
    REDUCE_MULTIPLY_SUBCASE( case1, a_a, axis );
    REDUCE_MULTIPLY_SUBCASE( case1, a_f, axis );
    // reduce doesnt work with dynamic ndarray for now
    // REDUCE_MULTIPLY_SUBCASE( case1, a_d, axis );
    REDUCE_MULTIPLY_SUBCASE( case1, a_h, axis );
}

TEST_CASE("reduce_multiply(case2)" * doctest::test_suite("view::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case2,   a, axis );
    REDUCE_MULTIPLY_SUBCASE( case2, a_a, axis );
    REDUCE_MULTIPLY_SUBCASE( case2, a_f, axis );
    REDUCE_MULTIPLY_SUBCASE( case2, a_h, axis );
}

TEST_CASE("reduce_multiply(case3)" * doctest::test_suite("view::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case3,   a, axis );
    REDUCE_MULTIPLY_SUBCASE( case3, a_a, axis );
    REDUCE_MULTIPLY_SUBCASE( case3, a_f, axis );
    REDUCE_MULTIPLY_SUBCASE( case3, a_h, axis );
}

TEST_CASE("reduce_multiply(case4)" * doctest::test_suite("view::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case4,   a, axis );
    REDUCE_MULTIPLY_SUBCASE( case4, a_a, axis );
    REDUCE_MULTIPLY_SUBCASE( case4, a_f, axis );
    REDUCE_MULTIPLY_SUBCASE( case4, a_h, axis );
}

TEST_CASE("reduce_multiply(case5)" * doctest::test_suite("view::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case5,   a, axis );
    REDUCE_MULTIPLY_SUBCASE( case5, a_a, axis );
    REDUCE_MULTIPLY_SUBCASE( case5, a_f, axis );
    REDUCE_MULTIPLY_SUBCASE( case5, a_h, axis );
}

TEST_CASE("reduce_multiply(case6)" * doctest::test_suite("view::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case6,   a, axis );
    REDUCE_MULTIPLY_SUBCASE( case6, a_a, axis );
    REDUCE_MULTIPLY_SUBCASE( case6, a_f, axis );
    REDUCE_MULTIPLY_SUBCASE( case6, a_h, axis );
}

// TEST_CASE("reduce_multiply(case7)" * doctest::test_suite("view::reduce_multiply"))
// {
//     REDUCE_MULTIPLY_SUBCASE( case7,   a, axis );
//     REDUCE_MULTIPLY_SUBCASE( case7, a_a, axis 
//     REDUCE_MULTIPLY_SUBCASE( case7, a_f, axis );
//     REDUCE_MULTIPLY_SUBCASE( case7, a_h, axis );
// }

TEST_CASE("reduce_multiply(case8)" * doctest::test_suite("view::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case8,   a, axis, dtype, initial );
    REDUCE_MULTIPLY_SUBCASE( case8, a_a, axis, dtype, initial );
    REDUCE_MULTIPLY_SUBCASE( case8, a_f, axis, dtype, initial );
    REDUCE_MULTIPLY_SUBCASE( case8, a_h, axis, dtype, initial );
}

TEST_CASE("reduce_multiply(case9)" * doctest::test_suite("view::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case9,   a, axis, dtype, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case9, a_a, axis, dtype, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case9, a_f, axis, dtype, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case9, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_multiply(case10)" * doctest::test_suite("view::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case10,   a, axis, dtype, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case10, a_a, axis, dtype, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case10, a_f, axis, dtype, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case10, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_multiply(case11)" * doctest::test_suite("view::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case11,   a, axis, dtype, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case11, a_a, axis, dtype, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case11, a_f, axis, dtype, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case11, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_multiply(case12)" * doctest::test_suite("view::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case12,   a, axis, dtype, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case12, a_a, axis, dtype, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case12, a_f, axis, dtype, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case12, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_multiply(case13)" * doctest::test_suite("view::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case13,   a, axis, dtype, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case13, a_a, axis, dtype, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case13, a_f, axis, dtype, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case13, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_multiply(case14)" * doctest::test_suite("view::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case14,   a, axis );
    REDUCE_MULTIPLY_SUBCASE( case14, a_a, axis );
    REDUCE_MULTIPLY_SUBCASE( case14, a_f, axis );
    REDUCE_MULTIPLY_SUBCASE( case14, a_h, axis );
}

TEST_CASE("reduce_multiply(case15)" * doctest::test_suite("view::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case15,   a, axis, nm::None, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case15, a_a, axis, nm::None, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case15, a_f, axis, nm::None, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case15, a_h, axis, nm::None, initial, keepdims );
}

TEST_CASE("reduce_multiply(case16)" * doctest::test_suite("view::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case16,   a, axis, nm::None, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case16, a_a, axis, nm::None, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case16, a_f, axis, nm::None, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case16, a_h, axis, nm::None, initial, keepdims );
}

TEST_CASE("reduce_multiply(case17)" * doctest::test_suite("view::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case17,   a, axis, nm::None, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case17, a_a, axis, nm::None, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case17, a_f, axis, nm::None, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case17, a_h, axis, nm::None, initial, keepdims );
}

TEST_CASE("reduce_multiply(case18)" * doctest::test_suite("view::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case18,   a, axis, nm::None, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case18, a_a, axis, nm::None, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case18, a_f, axis, nm::None, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case18, a_h, axis, nm::None, initial, keepdims );
}

#define ACCUMULATE_MULTIPLY_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, accumulate_multiply, case_name); \
    using namespace args; \
    auto result = view::accumulate_multiply(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("accumulate_multiply(case1)" * doctest::test_suite("view::accumulate_multiply"))
{
    ACCUMULATE_MULTIPLY_SUBCASE( case1,   a, axis );
    ACCUMULATE_MULTIPLY_SUBCASE( case1, a_a, axis );
    ACCUMULATE_MULTIPLY_SUBCASE( case1, a_f, axis );
    // reduce doesnt work with dynamic ndarray for now
    // ACCUMULATE_MULTIPLY_SUBCASE( case1, a_d, axis );
    ACCUMULATE_MULTIPLY_SUBCASE( case1, a_h, axis );
}

TEST_CASE("accumulate_multiply(case2)" * doctest::test_suite("view::accumulate_multiply"))
{
    ACCUMULATE_MULTIPLY_SUBCASE( case2,   a, axis );
    ACCUMULATE_MULTIPLY_SUBCASE( case2, a_a, axis );
    ACCUMULATE_MULTIPLY_SUBCASE( case2, a_f, axis );
    // reduce doesnt work with dynamic ndarray for now
    // ACCUMULATE_MULTIPLY_SUBCASE( case2, a_d, axis );
    ACCUMULATE_MULTIPLY_SUBCASE( case2, a_h, axis );
}

TEST_CASE("accumulate_multiply(case3)" * doctest::test_suite("view::accumulate_multiply"))
{
    ACCUMULATE_MULTIPLY_SUBCASE( case3,   a, axis );
    ACCUMULATE_MULTIPLY_SUBCASE( case3, a_a, axis );
    ACCUMULATE_MULTIPLY_SUBCASE( case3, a_f, axis );
    // reduce doesnt work with dynamic ndarray for now
    // ACCUMULATE_MULTIPLY_SUBCASE( case3, a_d, axis );
    ACCUMULATE_MULTIPLY_SUBCASE( case3, a_h, axis );
}

#define OUTER_MULTIPLY_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, outer_multiply, case_name); \
    using namespace args; \
    auto result = view::outer_multiply(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("outer_multiply(case1)" * doctest::test_suite("view::outer_multiply"))
{
    OUTER_MULTIPLY_SUBCASE( case1,   a,   b );
    OUTER_MULTIPLY_SUBCASE( case1, a_a, b_a );
    OUTER_MULTIPLY_SUBCASE( case1, a_f, b_f );
    OUTER_MULTIPLY_SUBCASE( case1, a_d, b_d );
    OUTER_MULTIPLY_SUBCASE( case1, a_h, b_h );
}