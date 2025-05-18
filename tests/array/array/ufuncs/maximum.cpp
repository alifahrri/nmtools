#include "nmtools/array/ufuncs/maximum.hpp"
#include "nmtools/testing/data/array/maximum.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>
#include <algorithm> // std::max

namespace nm = nmtools;
namespace na = nm::array;

#define MAXIMUM_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, maximum, case_name); \
    using namespace args; \
    auto result = nmtools::array::maximum(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("maximum(case1)" * doctest::test_suite("array::maximum"))
{
    MAXIMUM_SUBCASE( case1,   a,   b );
    MAXIMUM_SUBCASE( case1, a_a, b_a );
    MAXIMUM_SUBCASE( case1, a_f, b_f );
    MAXIMUM_SUBCASE( case1, a_d, b_d );
    MAXIMUM_SUBCASE( case1, a_h, b_h );
}

TEST_CASE("maximum(case2)" * doctest::test_suite("array::maximum"))
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
    auto result = nmtools::array::reduce_maximum(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("reduce_maximum(case1)" * doctest::test_suite("array::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case1,   a, axis );
    REDUCE_MAXIMUM_SUBCASE( case1, a_a, axis );
    REDUCE_MAXIMUM_SUBCASE( case1, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_MAXIMUM_SUBCASE( case1, a_d, axis );
    REDUCE_MAXIMUM_SUBCASE( case1, a_h, axis );
}

TEST_CASE("reduce_maximum(case2)" * doctest::test_suite("array::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case2,   a, axis );
    REDUCE_MAXIMUM_SUBCASE( case2, a_a, axis );
    REDUCE_MAXIMUM_SUBCASE( case2, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_MAXIMUM_SUBCASE( case2, a_d, axis );
    REDUCE_MAXIMUM_SUBCASE( case2, a_h, axis );
}

TEST_CASE("reduce_maximum(case3)" * doctest::test_suite("array::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case3,   a, axis );
    REDUCE_MAXIMUM_SUBCASE( case3, a_a, axis );
    REDUCE_MAXIMUM_SUBCASE( case3, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_MAXIMUM_SUBCASE( case3, a_d, axis );
    REDUCE_MAXIMUM_SUBCASE( case3, a_h, axis );
}

TEST_CASE("reduce_maximum(case4)" * doctest::test_suite("array::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case4,   a, axis );
    REDUCE_MAXIMUM_SUBCASE( case4, a_a, axis );
    REDUCE_MAXIMUM_SUBCASE( case4, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_MAXIMUM_SUBCASE( case4, a_d, axis );
    REDUCE_MAXIMUM_SUBCASE( case4, a_h, axis );
}

TEST_CASE("reduce_maximum(case5)" * doctest::test_suite("array::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case5,   a, axis );
    REDUCE_MAXIMUM_SUBCASE( case5, a_a, axis );
    REDUCE_MAXIMUM_SUBCASE( case5, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_MAXIMUM_SUBCASE( case5, a_d, axis );
    REDUCE_MAXIMUM_SUBCASE( case5, a_h, axis );
}

TEST_CASE("reduce_maximum(case6)" * doctest::test_suite("array::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case6,   a, axis );
    REDUCE_MAXIMUM_SUBCASE( case6, a_a, axis );
    REDUCE_MAXIMUM_SUBCASE( case6, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_MAXIMUM_SUBCASE( case6, a_d, axis );
    REDUCE_MAXIMUM_SUBCASE( case6, a_h, axis );
}

TEST_CASE("reduce_maximum(case7)" * doctest::test_suite("array::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case7,   a, axis, dtype, initial );
    REDUCE_MAXIMUM_SUBCASE( case7, a_a, axis, dtype, initial );
    REDUCE_MAXIMUM_SUBCASE( case7, a_f, axis, dtype, initial );
    REDUCE_MAXIMUM_SUBCASE( case7, a_h, axis, dtype, initial );
}

TEST_CASE("reduce_maximum(case8)" * doctest::test_suite("array::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case8,   a, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case8, a_a, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case8, a_f, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case8, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_maximum(case9)" * doctest::test_suite("array::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case9,   a, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case9, a_a, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case9, a_f, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case9, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_maximum(case10)" * doctest::test_suite("array::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case10,   a, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case10, a_a, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case10, a_f, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case10, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_maximum(case11)" * doctest::test_suite("array::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case11,   a, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case11, a_a, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case11, a_f, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case11, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_maximum(case12)" * doctest::test_suite("array::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case12,   a, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case12, a_a, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case12, a_f, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case12, a_h, axis, dtype, initial, keepdims );
}


TEST_CASE("reduce_maximum(case13)" * doctest::test_suite("array::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case13,   a, axis );
    REDUCE_MAXIMUM_SUBCASE( case13, a_a, axis );
    REDUCE_MAXIMUM_SUBCASE( case13, a_f, axis );
    REDUCE_MAXIMUM_SUBCASE( case13, a_h, axis );
}

TEST_CASE("reduce_maximum(case14)" * doctest::test_suite("array::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case14,   a, axis, nm::None, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case14, a_a, axis, nm::None, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case14, a_f, axis, nm::None, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case14, a_h, axis, nm::None, initial, keepdims );
}

TEST_CASE("reduce_maximum(case15)" * doctest::test_suite("array::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case15,   a, axis, nm::None, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case15, a_a, axis, nm::None, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case15, a_f, axis, nm::None, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case15, a_h, axis, nm::None, initial, keepdims );
}

TEST_CASE("reduce_maximum(case16)" * doctest::test_suite("array::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case16,   a, axis, nm::None, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case16, a_a, axis, nm::None, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case16, a_f, axis, nm::None, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case16, a_h, axis, nm::None, initial, keepdims );
}

TEST_CASE("reduce_maximum(case17)" * doctest::test_suite("array::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case17,   a, axis, nm::None, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case17, a_a, axis, nm::None, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case17, a_f, axis, nm::None, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case17, a_h, axis, nm::None, initial, keepdims );
}

TEST_CASE("reduce_maximum(case18)" * doctest::test_suite("array::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case18, a, axis, dtype, initial, keepdims, mask );
    REDUCE_MAXIMUM_SUBCASE( case18, a_a, axis, dtype, initial, keepdims, mask );
    REDUCE_MAXIMUM_SUBCASE( case18, a_f, axis, dtype, initial, keepdims, mask );
    // REDUCE_MAXIMUM_SUBCASE( case18, a_h, axis, dtype, initial, keepdims, mask );
    // REDUCE_MAXIMUM_SUBCASE( case18, a_d, axis, dtype, initial, keepdims, mask );
}

TEST_CASE("reduce_maximum(case19)" * doctest::test_suite("array::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case19, a, axis, dtype, initial, keepdims, mask );
    REDUCE_MAXIMUM_SUBCASE( case19, a_a, axis, dtype, initial, keepdims, mask );
    REDUCE_MAXIMUM_SUBCASE( case19, a_f, axis, dtype, initial, keepdims, mask );
    // REDUCE_MAXIMUM_SUBCASE( case19, a_h, axis, dtype, initial, keepdims, mask );
    // REDUCE_MAXIMUM_SUBCASE( case19, a_d, axis, dtype, initial, keepdims, mask );
}

TEST_CASE("reduce_maximum(case20)" * doctest::test_suite("array::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case20, a, axis, dtype, initial, keepdims, mask );
    REDUCE_MAXIMUM_SUBCASE( case20, a_a, axis, dtype, initial, keepdims, mask );
    REDUCE_MAXIMUM_SUBCASE( case20, a_f, axis, dtype, initial, keepdims, mask );
    // REDUCE_MAXIMUM_SUBCASE( case20, a_h, axis, dtype, initial, keepdims, mask );
    // REDUCE_MAXIMUM_SUBCASE( case20, a_d, axis, dtype, initial, keepdims, mask );
}

TEST_CASE("reduce_maximum(case21)" * doctest::test_suite("array::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case21, a, axis, dtype, initial, keepdims, mask );
    REDUCE_MAXIMUM_SUBCASE( case21, a_a, axis, dtype, initial, keepdims, mask );
    REDUCE_MAXIMUM_SUBCASE( case21, a_f, axis, dtype, initial, keepdims, mask );
    // REDUCE_MAXIMUM_SUBCASE( case21, a_h, axis, dtype, initial, keepdims, mask );
    // REDUCE_MAXIMUM_SUBCASE( case21, a_d, axis, dtype, initial, keepdims, mask );
}

TEST_CASE("reduce_maximum(case22)" * doctest::test_suite("array::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case22, a, axis, dtype, initial, keepdims, mask );
    REDUCE_MAXIMUM_SUBCASE( case22, a_a, axis, dtype, initial, keepdims, mask );
    REDUCE_MAXIMUM_SUBCASE( case22, a_f, axis, dtype, initial, keepdims, mask );
    // REDUCE_MAXIMUM_SUBCASE( case22, a_h, axis, dtype, initial, keepdims, mask );
    // REDUCE_MAXIMUM_SUBCASE( case22, a_d, axis, dtype, initial, keepdims, mask );
}

TEST_CASE("reduce_maximum(case23)" * doctest::test_suite("array::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case23, a, axis, dtype, initial, keepdims, mask );
    REDUCE_MAXIMUM_SUBCASE( case23, a_a, axis, dtype, initial, keepdims, mask );
    REDUCE_MAXIMUM_SUBCASE( case23, a_f, axis, dtype, initial, keepdims, mask );
    // REDUCE_MAXIMUM_SUBCASE( case23, a_h, axis, dtype, initial, keepdims, mask );
    // REDUCE_MAXIMUM_SUBCASE( case23, a_d, axis, dtype, initial, keepdims, mask );
}

TEST_CASE("reduce_maximum(case24)" * doctest::test_suite("array::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case24, a, axis, dtype, initial, keepdims, mask );
    REDUCE_MAXIMUM_SUBCASE( case24, a_a, axis, dtype, initial, keepdims, mask );
    REDUCE_MAXIMUM_SUBCASE( case24, a_f, axis, dtype, initial, keepdims, mask );
    // REDUCE_MAXIMUM_SUBCASE( case24, a_h, axis, dtype, initial, keepdims, mask );
    // REDUCE_MAXIMUM_SUBCASE( case24, a_d, axis, dtype, initial, keepdims, mask );
}

TEST_CASE("reduce_maximum(case25)" * doctest::test_suite("array::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case25, a, axis, dtype, initial, keepdims, mask );
    REDUCE_MAXIMUM_SUBCASE( case25, a_a, axis, dtype, initial, keepdims, mask );
    REDUCE_MAXIMUM_SUBCASE( case25, a_f, axis, dtype, initial, keepdims, mask );
    // REDUCE_MAXIMUM_SUBCASE( case25, a_h, axis, dtype, initial, keepdims, mask );
    // REDUCE_MAXIMUM_SUBCASE( case25, a_d, axis, dtype, initial, keepdims, mask );
}

TEST_CASE("reduce_maximum(case26)" * doctest::test_suite("array::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case26, a, axis, dtype, initial, keepdims, mask );
    REDUCE_MAXIMUM_SUBCASE( case26, a_a, axis, dtype, initial, keepdims, mask );
    REDUCE_MAXIMUM_SUBCASE( case26, a_f, axis, dtype, initial, keepdims, mask );
    // REDUCE_MAXIMUM_SUBCASE( case26, a_h, axis, dtype, initial, keepdims, mask );
    // REDUCE_MAXIMUM_SUBCASE( case26, a_d, axis, dtype, initial, keepdims, mask );
}

TEST_CASE("reduce_maximum(case27)" * doctest::test_suite("array::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case27, a, axis, dtype, initial, keepdims, mask );
    REDUCE_MAXIMUM_SUBCASE( case27, a_a, axis, dtype, initial, keepdims, mask );
    REDUCE_MAXIMUM_SUBCASE( case27, a_f, axis, dtype, initial, keepdims, mask );
    // REDUCE_MAXIMUM_SUBCASE( case27, a_h, axis, dtype, initial, keepdims, mask );
    // REDUCE_MAXIMUM_SUBCASE( case27, a_d, axis, dtype, initial, keepdims, mask );
}

TEST_CASE("reduce_maximum(case28)" * doctest::test_suite("array::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case28, a, axis, dtype, initial, keepdims, mask );
    REDUCE_MAXIMUM_SUBCASE( case28, a_a, axis, dtype, initial, keepdims, mask );
    REDUCE_MAXIMUM_SUBCASE( case28, a_f, axis, dtype, initial, keepdims, mask );
    // REDUCE_MAXIMUM_SUBCASE( case28, a_h, axis, dtype, initial, keepdims, mask );
    // REDUCE_MAXIMUM_SUBCASE( case28, a_d, axis, dtype, initial, keepdims, mask );
}

#define ACCUMULATE_MAXIMUM_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, accumulate_maximum, case_name); \
    using namespace args; \
    auto result = nmtools::array::accumulate_maximum(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("accumulate_maximum(case1)" * doctest::test_suite("array::accumulate_maximum"))
{
    ACCUMULATE_MAXIMUM_SUBCASE( case1,   a, axis );
    ACCUMULATE_MAXIMUM_SUBCASE( case1, a_a, axis );
    ACCUMULATE_MAXIMUM_SUBCASE( case1, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_MAXIMUM_SUBCASE( case1, a_d, axis );
    ACCUMULATE_MAXIMUM_SUBCASE( case1, a_f, axis );
}

TEST_CASE("accumulate_maximum(case2)" * doctest::test_suite("array::accumulate_maximum"))
{
    ACCUMULATE_MAXIMUM_SUBCASE( case2,   a, axis );
    ACCUMULATE_MAXIMUM_SUBCASE( case2, a_a, axis );
    ACCUMULATE_MAXIMUM_SUBCASE( case2, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_MAXIMUM_SUBCASE( case2, a_d, axis );
    ACCUMULATE_MAXIMUM_SUBCASE( case2, a_f, axis );
}

TEST_CASE("accumulate_maximum(case3)" * doctest::test_suite("array::accumulate_maximum"))
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
    auto result = nmtools::array::outer_maximum(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("outer_maximum(case1)" * doctest::test_suite("array::outer_maximum"))
{
    OUTER_MAXIMUM_SUBCASE( case1,   a,   b );
    OUTER_MAXIMUM_SUBCASE( case1, a_a, b_a );
    // TODO: remove support for nested vector as ndarray
    OUTER_MAXIMUM_SUBCASE( case1, a_f, b_f );
    OUTER_MAXIMUM_SUBCASE( case1, a_d, b_d );
    OUTER_MAXIMUM_SUBCASE( case1, a_h, b_h );
}