#include "nmtools/array/ufuncs/multiply.hpp"
#include "nmtools/testing/data/array/multiply.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;

#define MULTIPLY_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, multiply, case_name); \
    using namespace args; \
    auto result = nmtools::array::multiply( __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("multiply(case1)" * doctest::test_suite("array::multiply"))
{
    MULTIPLY_SUBCASE( case1,   a,   b );
    MULTIPLY_SUBCASE( case1, a_a, b_a );
    MULTIPLY_SUBCASE( case1, a_f, b_f );
    MULTIPLY_SUBCASE( case1, a_d, b_d );
    MULTIPLY_SUBCASE( case1, a_h, b_h );
}

TEST_CASE("multiply(case2)" * doctest::test_suite("array::multiply"))
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
    auto result = nmtools::array::reduce_multiply(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("reduce_multiply(case1)" * doctest::test_suite("array::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case1,   a, axis );
    REDUCE_MULTIPLY_SUBCASE( case1, a_a, axis );
    REDUCE_MULTIPLY_SUBCASE( case1, a_f, axis );
    // reduce doesnt work with dynamic ndarray for now
    // REDUCE_MULTIPLY_SUBCASE( case1, a_d, axis );
    REDUCE_MULTIPLY_SUBCASE( case1, a_h, axis );
}

TEST_CASE("reduce_multiply(case2)" * doctest::test_suite("array::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case2,   a, axis );
    REDUCE_MULTIPLY_SUBCASE( case2, a_a, axis );
    REDUCE_MULTIPLY_SUBCASE( case2, a_f, axis );
    REDUCE_MULTIPLY_SUBCASE( case2, a_h, axis );
}

TEST_CASE("reduce_multiply(case3)" * doctest::test_suite("array::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case3,   a, axis );
    REDUCE_MULTIPLY_SUBCASE( case3, a_a, axis );
    REDUCE_MULTIPLY_SUBCASE( case3, a_f, axis );
    REDUCE_MULTIPLY_SUBCASE( case3, a_h, axis );
}

TEST_CASE("reduce_multiply(case4)" * doctest::test_suite("array::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case4,   a, axis );
    REDUCE_MULTIPLY_SUBCASE( case4, a_a, axis );
    REDUCE_MULTIPLY_SUBCASE( case4, a_f, axis );
    REDUCE_MULTIPLY_SUBCASE( case4, a_h, axis );
}

TEST_CASE("reduce_multiply(case5)" * doctest::test_suite("array::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case5,   a, axis );
    REDUCE_MULTIPLY_SUBCASE( case5, a_a, axis );
    REDUCE_MULTIPLY_SUBCASE( case5, a_f, axis );
    REDUCE_MULTIPLY_SUBCASE( case5, a_h, axis );
}

TEST_CASE("reduce_multiply(case6)" * doctest::test_suite("array::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case6,   a, axis );
    REDUCE_MULTIPLY_SUBCASE( case6, a_a, axis );
    REDUCE_MULTIPLY_SUBCASE( case6, a_f, axis );
    REDUCE_MULTIPLY_SUBCASE( case6, a_h, axis );
}

// TEST_CASE("reduce_multiply(case7)" * doctest::test_suite("array::reduce_multiply"))
// {
//     REDUCE_MULTIPLY_SUBCASE( case7,   a, axis );
//     REDUCE_MULTIPLY_SUBCASE( case7, a_a, axis 
//     REDUCE_MULTIPLY_SUBCASE( case7, a_f, axis );
//     REDUCE_MULTIPLY_SUBCASE( case7, a_h, axis );
// }

TEST_CASE("reduce_multiply(case8)" * doctest::test_suite("array::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case8,   a, axis, dtype, initial );
    REDUCE_MULTIPLY_SUBCASE( case8, a_a, axis, dtype, initial );
    REDUCE_MULTIPLY_SUBCASE( case8, a_f, axis, dtype, initial );
    REDUCE_MULTIPLY_SUBCASE( case8, a_h, axis, dtype, initial );
}

TEST_CASE("reduce_multiply(case9)" * doctest::test_suite("array::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case9,   a, axis, dtype, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case9, a_a, axis, dtype, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case9, a_f, axis, dtype, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case9, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_multiply(case10)" * doctest::test_suite("array::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case10,   a, axis, dtype, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case10, a_a, axis, dtype, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case10, a_f, axis, dtype, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case10, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_multiply(case11)" * doctest::test_suite("array::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case11,   a, axis, dtype, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case11, a_a, axis, dtype, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case11, a_f, axis, dtype, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case11, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_multiply(case12)" * doctest::test_suite("array::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case12,   a, axis, dtype, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case12, a_a, axis, dtype, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case12, a_f, axis, dtype, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case12, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_multiply(case13)" * doctest::test_suite("array::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case13,   a, axis, dtype, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case13, a_a, axis, dtype, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case13, a_f, axis, dtype, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case13, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_multiply(case14)" * doctest::test_suite("array::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case14,   a, axis );
    REDUCE_MULTIPLY_SUBCASE( case14, a_a, axis );
    REDUCE_MULTIPLY_SUBCASE( case14, a_f, axis );
    REDUCE_MULTIPLY_SUBCASE( case14, a_h, axis );
}

TEST_CASE("reduce_multiply(case15)" * doctest::test_suite("array::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case15,   a, axis, nm::None, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case15, a_a, axis, nm::None, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case15, a_f, axis, nm::None, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case15, a_h, axis, nm::None, initial, keepdims );
}

TEST_CASE("reduce_multiply(case16)" * doctest::test_suite("array::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case16,   a, axis, nm::None, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case16, a_a, axis, nm::None, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case16, a_f, axis, nm::None, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case16, a_h, axis, nm::None, initial, keepdims );
}

TEST_CASE("reduce_multiply(case17)" * doctest::test_suite("array::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case17,   a, axis, nm::None, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case17, a_a, axis, nm::None, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case17, a_f, axis, nm::None, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case17, a_h, axis, nm::None, initial, keepdims );
}

TEST_CASE("reduce_multiply(case18)" * doctest::test_suite("array::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case18,   a, axis, nm::None, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case18, a_a, axis, nm::None, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case18, a_f, axis, nm::None, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case18, a_h, axis, nm::None, initial, keepdims );
}

TEST_CASE("reduce_multiply(case19)" * doctest::test_suite("array::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case19, a, axis, nm::None, nm::None, nm::False, mask );
    REDUCE_MULTIPLY_SUBCASE( case19, a_a, axis, nm::None, nm::None, nm::False, mask );
    REDUCE_MULTIPLY_SUBCASE( case19, a_f, axis, nm::None, nm::None, nm::False, mask );
    // REDUCE_MULTIPLY_SUBCASE( case19, a_h, axis, nm::None, nm::None, nm::False, mask );
}

TEST_CASE("reduce_multiply(case20)" * doctest::test_suite("array::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case20, a, axis, nm::None, initial, keepdims, mask );
    REDUCE_MULTIPLY_SUBCASE( case20, a_a, axis, nm::None, initial, keepdims, mask );
    REDUCE_MULTIPLY_SUBCASE( case20, a_f, axis, nm::None, initial, keepdims, mask );
    // REDUCE_MULTIPLY_SUBCASE( case20, a_h, axis, nm::None, initial, keepdims, mask );
}

TEST_CASE("reduce_multiply(case21)" * doctest::test_suite("array::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case21, a, axis, nm::None, nm::None, keepdims, mask );
    REDUCE_MULTIPLY_SUBCASE( case21, a_a, axis, nm::None, nm::None, keepdims, mask );
    REDUCE_MULTIPLY_SUBCASE( case21, a_f, axis, nm::None, nm::None, keepdims, mask );
    // REDUCE_MULTIPLY_SUBCASE( case21, a_h, axis, nm::None, nm::None, keepdims, mask );
}

TEST_CASE("reduce_multiply(case22)" * doctest::test_suite("array::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case22, a, axis, nm::None, nm::None, nm::False, mask );
    REDUCE_MULTIPLY_SUBCASE( case22, a_a, axis, nm::None, nm::None, nm::False, mask );
    REDUCE_MULTIPLY_SUBCASE( case22, a_f, axis, nm::None, nm::None, nm::False, mask );
    // REDUCE_MULTIPLY_SUBCASE( case22, a_h, axis, nm::None, nm::None, nm::False, mask );
}

TEST_CASE("reduce_multiply(case23)" * doctest::test_suite("array::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case23, a, axis, nm::None, initial, nm::False, mask );
    REDUCE_MULTIPLY_SUBCASE( case23, a_a, axis, nm::None, initial, nm::False, mask );
    REDUCE_MULTIPLY_SUBCASE( case23, a_f, axis, nm::None, initial, nm::False, mask );
    // REDUCE_MULTIPLY_SUBCASE( case23, a_h, axis, nm::None, initial, nm::False, mask );
}

TEST_CASE("reduce_multiply(case24)" * doctest::test_suite("array::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case24, a, axis, nm::None, nm::None, nm::False, mask );
    REDUCE_MULTIPLY_SUBCASE( case24, a_a, axis, nm::None, nm::None, nm::False, mask );
    REDUCE_MULTIPLY_SUBCASE( case24, a_f, axis, nm::None, nm::None, nm::False, mask );
    // REDUCE_MULTIPLY_SUBCASE( case24, a_h, axis, nm::None, nm::None, nm::False, mask );
}

TEST_CASE("reduce_multiply(case25)" * doctest::test_suite("array::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case25, a, axis, nm::None, nm::None, nm::False, mask );
    REDUCE_MULTIPLY_SUBCASE( case25, a_a, axis, nm::None, nm::None, nm::False, mask );
    REDUCE_MULTIPLY_SUBCASE( case25, a_f, axis, nm::None, nm::None, nm::False, mask );
    // REDUCE_MULTIPLY_SUBCASE( case25, a_h, axis, nm::None, nm::None, nm::False, mask );
}

TEST_CASE("reduce_multiply(case26)" * doctest::test_suite("array::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case26, a, axis, nm::None, initial, keepdims, mask );
    REDUCE_MULTIPLY_SUBCASE( case26, a_a, axis, nm::None, initial, keepdims, mask );
    REDUCE_MULTIPLY_SUBCASE( case26, a_f, axis, nm::None, initial, keepdims, mask );
    // REDUCE_MULTIPLY_SUBCASE( case26, a_h, axis, nm::None, initial, keepdims, mask );
}

TEST_CASE("reduce_multiply(case27)" * doctest::test_suite("array::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case27, a, axis, nm::None, initial, keepdims, mask );
    REDUCE_MULTIPLY_SUBCASE( case27, a_a, axis, nm::None, initial, keepdims, mask );
    REDUCE_MULTIPLY_SUBCASE( case27, a_f, axis, nm::None, initial, keepdims, mask );
    // REDUCE_MULTIPLY_SUBCASE( case27, a_h, axis, nm::None, initial, keepdims, mask );
}

TEST_CASE("reduce_multiply(case28)" * doctest::test_suite("array::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case28, a, axis, nm::None, initial, keepdims, mask );
    REDUCE_MULTIPLY_SUBCASE( case28, a_a, axis, nm::None, initial, keepdims, mask );
    REDUCE_MULTIPLY_SUBCASE( case28, a_f, axis, nm::None, initial, keepdims, mask );
    // REDUCE_MULTIPLY_SUBCASE( case28, a_h, axis, nm::None, initial, keepdims, mask );
}

TEST_CASE("reduce_multiply(case29)" * doctest::test_suite("array::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case29, a, axis, nm::None, initial, keepdims, mask );
    REDUCE_MULTIPLY_SUBCASE( case29, a_a, axis, nm::None, initial, keepdims, mask );
    REDUCE_MULTIPLY_SUBCASE( case29, a_f, axis, nm::None, initial, keepdims, mask );
    // REDUCE_MULTIPLY_SUBCASE( case29, a_h, axis, nm::None, initial, keepdims, mask );
}

#define ACCUMULATE_MULTIPLY_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, accumulate_multiply, case_name); \
    using namespace args; \
    auto result = nmtools::array::accumulate_multiply(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("accumulate_multiply(case1)" * doctest::test_suite("array::accumulate_multiply"))
{
    ACCUMULATE_MULTIPLY_SUBCASE( case1,   a, axis );
    ACCUMULATE_MULTIPLY_SUBCASE( case1, a_a, axis );
    ACCUMULATE_MULTIPLY_SUBCASE( case1, a_f, axis );
    // reduce doesnt work with dynamic ndarray for now
    // ACCUMULATE_MULTIPLY_SUBCASE( case1, a_d, axis );
    ACCUMULATE_MULTIPLY_SUBCASE( case1, a_h, axis );
}

TEST_CASE("accumulate_multiply(case2)" * doctest::test_suite("array::accumulate_multiply"))
{
    ACCUMULATE_MULTIPLY_SUBCASE( case2,   a, axis );
    ACCUMULATE_MULTIPLY_SUBCASE( case2, a_a, axis );
    ACCUMULATE_MULTIPLY_SUBCASE( case2, a_f, axis );
    // reduce doesnt work with dynamic ndarray for now
    // ACCUMULATE_MULTIPLY_SUBCASE( case2, a_d, axis );
    ACCUMULATE_MULTIPLY_SUBCASE( case2, a_h, axis );
}

TEST_CASE("accumulate_multiply(case3)" * doctest::test_suite("array::accumulate_multiply"))
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
    auto result = nmtools::array::outer_multiply(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("outer_multiply(case1)" * doctest::test_suite("array::outer_multiply"))
{
    OUTER_MULTIPLY_SUBCASE( case1,   a,   b );
    OUTER_MULTIPLY_SUBCASE( case1, a_a, b_a );
    // TODO: remove support for nested vector as ndarray
    OUTER_MULTIPLY_SUBCASE( case1, a_f, b_f );
    OUTER_MULTIPLY_SUBCASE( case1, a_d, b_d );
    OUTER_MULTIPLY_SUBCASE( case1, a_h, b_h );
}