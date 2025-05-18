#include "nmtools/array/ufuncs/minimum.hpp"
#include "nmtools/testing/data/array/minimum.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define MINIMUM_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, minimum, case_name); \
    using namespace args; \
    auto result = view::minimum(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("minimum(case1)" * doctest::test_suite("view::minimum"))
{
    MINIMUM_SUBCASE( case1,   a,   b );
    MINIMUM_SUBCASE( case1, a_a, b_a );
    MINIMUM_SUBCASE( case1, a_f, b_f );
    MINIMUM_SUBCASE( case1, a_d, b_d );
    MINIMUM_SUBCASE( case1, a_h, b_h );
}

TEST_CASE("minimum(case2)" * doctest::test_suite("view::minimum"))
{
    MINIMUM_SUBCASE( case2,   a, b );
    MINIMUM_SUBCASE( case2, a_a, b );
    MINIMUM_SUBCASE( case2, a_f, b );
    MINIMUM_SUBCASE( case2, a_d, b );
    MINIMUM_SUBCASE( case2, a_h, b );
}

#define REDUCE_MINIMUM_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, reduce_minimum, case_name); \
    using namespace args; \
    auto result = view::reduce_minimum(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("reduce_minimum(case1)" * doctest::test_suite("view::reduce_minimum"))
{
    REDUCE_MINIMUM_SUBCASE( case1,   a, axis );
    REDUCE_MINIMUM_SUBCASE( case1, a_a, axis );
    REDUCE_MINIMUM_SUBCASE( case1, a_f, axis );
    REDUCE_MINIMUM_SUBCASE( case1, a_d, axis );
    REDUCE_MINIMUM_SUBCASE( case1, a_h, axis );
}

TEST_CASE("reduce_minimum(case2)" * doctest::test_suite("view::reduce_minimum"))
{
    REDUCE_MINIMUM_SUBCASE( case2,   a, axis );
    REDUCE_MINIMUM_SUBCASE( case2, a_a, axis );
    REDUCE_MINIMUM_SUBCASE( case2, a_f, axis );
    REDUCE_MINIMUM_SUBCASE( case2, a_d, axis );
    REDUCE_MINIMUM_SUBCASE( case2, a_h, axis );
}

TEST_CASE("reduce_minimum(case3)" * doctest::test_suite("view::reduce_minimum"))
{
    REDUCE_MINIMUM_SUBCASE( case3,   a, axis );
    REDUCE_MINIMUM_SUBCASE( case3, a_a, axis );
    REDUCE_MINIMUM_SUBCASE( case3, a_f, axis );
    REDUCE_MINIMUM_SUBCASE( case3, a_d, axis );
    REDUCE_MINIMUM_SUBCASE( case3, a_h, axis );
}

TEST_CASE("reduce_minimum(case4)" * doctest::test_suite("view::reduce_minimum"))
{
    REDUCE_MINIMUM_SUBCASE( case4,   a, axis );
    REDUCE_MINIMUM_SUBCASE( case4, a_a, axis );
    REDUCE_MINIMUM_SUBCASE( case4, a_f, axis );
    REDUCE_MINIMUM_SUBCASE( case4, a_d, axis );
    REDUCE_MINIMUM_SUBCASE( case4, a_h, axis );
}

TEST_CASE("reduce_minimum(case5)" * doctest::test_suite("view::reduce_minimum"))
{
    REDUCE_MINIMUM_SUBCASE( case5,   a, axis );
    REDUCE_MINIMUM_SUBCASE( case5, a_a, axis );
    REDUCE_MINIMUM_SUBCASE( case5, a_f, axis );
    REDUCE_MINIMUM_SUBCASE( case5, a_d, axis );
    REDUCE_MINIMUM_SUBCASE( case5, a_h, axis );
}

TEST_CASE("reduce_minimum(case6)" * doctest::test_suite("view::reduce_minimum"))
{
    REDUCE_MINIMUM_SUBCASE( case6,   a, axis );
    REDUCE_MINIMUM_SUBCASE( case6, a_a, axis );
    REDUCE_MINIMUM_SUBCASE( case6, a_f, axis );
    REDUCE_MINIMUM_SUBCASE( case6, a_d, axis );
    REDUCE_MINIMUM_SUBCASE( case6, a_h, axis );
}

TEST_CASE("reduce_minimum(case7)" * doctest::test_suite("view::reduce_minimum"))
{
    REDUCE_MINIMUM_SUBCASE( case7,   a, axis, dtype, initial );
    REDUCE_MINIMUM_SUBCASE( case7, a_a, axis, dtype, initial );
    REDUCE_MINIMUM_SUBCASE( case7, a_f, axis, dtype, initial );
    REDUCE_MINIMUM_SUBCASE( case7, a_h, axis, dtype, initial );
    REDUCE_MINIMUM_SUBCASE( case7, a_d, axis, dtype, initial );
}

TEST_CASE("reduce_minimum(case8)" * doctest::test_suite("view::reduce_minimum"))
{
    REDUCE_MINIMUM_SUBCASE( case8,   a, axis, dtype, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case8, a_a, axis, dtype, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case8, a_f, axis, dtype, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case8, a_h, axis, dtype, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case8, a_d, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_minimum(case9)" * doctest::test_suite("view::reduce_minimum"))
{
    REDUCE_MINIMUM_SUBCASE( case9,   a, axis, dtype, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case9, a_a, axis, dtype, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case9, a_f, axis, dtype, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case9, a_h, axis, dtype, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case9, a_d, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_minimum(case10)" * doctest::test_suite("view::reduce_minimum"))
{
    REDUCE_MINIMUM_SUBCASE( case10,   a, axis, dtype, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case10, a_a, axis, dtype, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case10, a_f, axis, dtype, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case10, a_h, axis, dtype, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case10, a_d, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_minimum(case11)" * doctest::test_suite("view::reduce_minimum"))
{
    REDUCE_MINIMUM_SUBCASE( case11,   a, axis, dtype, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case11, a_a, axis, dtype, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case11, a_f, axis, dtype, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case11, a_h, axis, dtype, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case11, a_d, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_minimum(case12)" * doctest::test_suite("view::reduce_minimum"))
{
    REDUCE_MINIMUM_SUBCASE( case12,   a, axis, dtype, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case12, a_a, axis, dtype, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case12, a_f, axis, dtype, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case12, a_h, axis, dtype, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case12, a_d, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_minimum(case13)" * doctest::test_suite("view::reduce_minimum"))
{
    REDUCE_MINIMUM_SUBCASE( case13,   a, axis );
    REDUCE_MINIMUM_SUBCASE( case13, a_a, axis );
    REDUCE_MINIMUM_SUBCASE( case13, a_f, axis );
    REDUCE_MINIMUM_SUBCASE( case13, a_h, axis );
    REDUCE_MINIMUM_SUBCASE( case13, a_d, axis );
}

TEST_CASE("reduce_minimum(case14)" * doctest::test_suite("view::reduce_minimum"))
{
    REDUCE_MINIMUM_SUBCASE( case14,   a, axis, nm::None, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case14, a_a, axis, nm::None, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case14, a_f, axis, nm::None, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case14, a_h, axis, nm::None, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case14, a_d, axis, nm::None, initial, keepdims );
}

TEST_CASE("reduce_minimum(case15)" * doctest::test_suite("view::reduce_minimum"))
{
    REDUCE_MINIMUM_SUBCASE( case15,   a, axis, nm::None, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case15, a_a, axis, nm::None, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case15, a_f, axis, nm::None, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case15, a_h, axis, nm::None, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case15, a_d, axis, nm::None, initial, keepdims );
}

TEST_CASE("reduce_minimum(case16)" * doctest::test_suite("view::reduce_minimum"))
{
    REDUCE_MINIMUM_SUBCASE( case16,   a, axis, nm::None, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case16, a_a, axis, nm::None, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case16, a_f, axis, nm::None, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case16, a_h, axis, nm::None, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case16, a_d, axis, nm::None, initial, keepdims );
}

TEST_CASE("reduce_minimum(case17)" * doctest::test_suite("view::reduce_minimum"))
{
    REDUCE_MINIMUM_SUBCASE( case17,   a, axis, nm::None, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case17, a_a, axis, nm::None, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case17, a_f, axis, nm::None, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case17, a_h, axis, nm::None, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case17, a_d, axis, nm::None, initial, keepdims );
}


TEST_CASE("reduce_minimum(case18)" * doctest::test_suite("view::reduce_minimum"))
{
    REDUCE_MINIMUM_SUBCASE( case18, a, axis, dtype, initial, keepdims, mask );
    REDUCE_MINIMUM_SUBCASE( case18, a_a, axis, dtype, initial, keepdims, mask );
    REDUCE_MINIMUM_SUBCASE( case18, a_f, axis, dtype, initial, keepdims, mask );
    // REDUCE_MINIMUM_SUBCASE( case18, a_h, axis, dtype, initial, keepdims, mask );
    // REDUCE_MINIMUM_SUBCASE( case18, a_d, axis, dtype, initial, keepdims, mask );
}

TEST_CASE("reduce_minimum(case19)" * doctest::test_suite("view::reduce_minimum"))
{
    REDUCE_MINIMUM_SUBCASE( case19, a, axis, dtype, initial, keepdims, mask );
    REDUCE_MINIMUM_SUBCASE( case19, a_a, axis, dtype, initial, keepdims, mask );
    REDUCE_MINIMUM_SUBCASE( case19, a_f, axis, dtype, initial, keepdims, mask );
    // REDUCE_MINIMUM_SUBCASE( case19, a_h, axis, dtype, initial, keepdims, mask );
    // REDUCE_MINIMUM_SUBCASE( case19, a_d, axis, dtype, initial, keepdims, mask );
}

TEST_CASE("reduce_minimum(case20)" * doctest::test_suite("view::reduce_minimum"))
{
    REDUCE_MINIMUM_SUBCASE( case20, a, axis, dtype, initial, keepdims, mask );
    REDUCE_MINIMUM_SUBCASE( case20, a_a, axis, dtype, initial, keepdims, mask );
    REDUCE_MINIMUM_SUBCASE( case20, a_f, axis, dtype, initial, keepdims, mask );
    // REDUCE_MINIMUM_SUBCASE( case20, a_h, axis, dtype, initial, keepdims, mask );
    // REDUCE_MINIMUM_SUBCASE( case20, a_d, axis, dtype, initial, keepdims, mask );
}

TEST_CASE("reduce_minimum(case21)" * doctest::test_suite("view::reduce_minimum"))
{
    REDUCE_MINIMUM_SUBCASE( case21, a, axis, dtype, initial, keepdims, mask );
    REDUCE_MINIMUM_SUBCASE( case21, a_a, axis, dtype, initial, keepdims, mask );
    REDUCE_MINIMUM_SUBCASE( case21, a_f, axis, dtype, initial, keepdims, mask );
    // REDUCE_MINIMUM_SUBCASE( case21, a_h, axis, dtype, initial, keepdims, mask );
    // REDUCE_MINIMUM_SUBCASE( case21, a_d, axis, dtype, initial, keepdims, mask );
}

TEST_CASE("reduce_minimum(case22)" * doctest::test_suite("view::reduce_minimum"))
{
    REDUCE_MINIMUM_SUBCASE( case22, a, axis, dtype, initial, keepdims, mask );
    REDUCE_MINIMUM_SUBCASE( case22, a_a, axis, dtype, initial, keepdims, mask );
    REDUCE_MINIMUM_SUBCASE( case22, a_f, axis, dtype, initial, keepdims, mask );
    // REDUCE_MINIMUM_SUBCASE( case22, a_h, axis, dtype, initial, keepdims, mask );
    // REDUCE_MINIMUM_SUBCASE( case22, a_d, axis, dtype, initial, keepdims, mask );
}

TEST_CASE("reduce_minimum(case23)" * doctest::test_suite("view::reduce_minimum"))
{
    REDUCE_MINIMUM_SUBCASE( case23, a, axis, dtype, initial, keepdims, mask );
    REDUCE_MINIMUM_SUBCASE( case23, a_a, axis, dtype, initial, keepdims, mask );
    REDUCE_MINIMUM_SUBCASE( case23, a_f, axis, dtype, initial, keepdims, mask );
    // REDUCE_MINIMUM_SUBCASE( case23, a_h, axis, dtype, initial, keepdims, mask );
    // REDUCE_MINIMUM_SUBCASE( case23, a_d, axis, dtype, initial, keepdims, mask );
}

TEST_CASE("reduce_minimum(case24)" * doctest::test_suite("view::reduce_minimum"))
{
    REDUCE_MINIMUM_SUBCASE( case24, a, axis, dtype, initial, keepdims, mask );
    REDUCE_MINIMUM_SUBCASE( case24, a_a, axis, dtype, initial, keepdims, mask );
    REDUCE_MINIMUM_SUBCASE( case24, a_f, axis, dtype, initial, keepdims, mask );
    // REDUCE_MINIMUM_SUBCASE( case24, a_h, axis, dtype, initial, keepdims, mask );
    // REDUCE_MINIMUM_SUBCASE( case24, a_d, axis, dtype, initial, keepdims, mask );
}

TEST_CASE("reduce_minimum(case25)" * doctest::test_suite("view::reduce_minimum"))
{
    REDUCE_MINIMUM_SUBCASE( case25, a, axis, dtype, initial, keepdims, mask );
    REDUCE_MINIMUM_SUBCASE( case25, a_a, axis, dtype, initial, keepdims, mask );
    REDUCE_MINIMUM_SUBCASE( case25, a_f, axis, dtype, initial, keepdims, mask );
    // REDUCE_MINIMUM_SUBCASE( case25, a_h, axis, dtype, initial, keepdims, mask );
    // REDUCE_MINIMUM_SUBCASE( case25, a_d, axis, dtype, initial, keepdims, mask );
}

TEST_CASE("reduce_minimum(case26)" * doctest::test_suite("view::reduce_minimum"))
{
    REDUCE_MINIMUM_SUBCASE( case26, a, axis, dtype, initial, keepdims, mask );
    REDUCE_MINIMUM_SUBCASE( case26, a_a, axis, dtype, initial, keepdims, mask );
    REDUCE_MINIMUM_SUBCASE( case26, a_f, axis, dtype, initial, keepdims, mask );
    // REDUCE_MINIMUM_SUBCASE( case26, a_h, axis, dtype, initial, keepdims, mask );
    // REDUCE_MINIMUM_SUBCASE( case26, a_d, axis, dtype, initial, keepdims, mask );
}

TEST_CASE("reduce_minimum(case27)" * doctest::test_suite("view::reduce_minimum"))
{
    REDUCE_MINIMUM_SUBCASE( case27, a, axis, dtype, initial, keepdims, mask );
    REDUCE_MINIMUM_SUBCASE( case27, a_a, axis, dtype, initial, keepdims, mask );
    REDUCE_MINIMUM_SUBCASE( case27, a_f, axis, dtype, initial, keepdims, mask );
    // REDUCE_MINIMUM_SUBCASE( case27, a_h, axis, dtype, initial, keepdims, mask );
    // REDUCE_MINIMUM_SUBCASE( case27, a_d, axis, dtype, initial, keepdims, mask );
}

TEST_CASE("reduce_minimum(case28)" * doctest::test_suite("view::reduce_minimum"))
{
    // auto dtype = nm::int32;
    REDUCE_MINIMUM_SUBCASE( case28, a, axis, nm::int32, initial, keepdims, mask );
    REDUCE_MINIMUM_SUBCASE( case28, a_a, axis, nm::int32, initial, keepdims, mask );
    REDUCE_MINIMUM_SUBCASE( case28, a_f, axis, nm::int32, initial, keepdims, mask );
    // REDUCE_MINIMUM_SUBCASE( case28, a_h, axis, dtype, initial, keepdims, mask );
    // REDUCE_MINIMUM_SUBCASE( case28, a_d, axis, dtype, initial, keepdims, mask );
}

#define ACCUMULATE_MINIMUM_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, accumulate_minimum, case_name); \
    using namespace args; \
    auto result = view::accumulate_minimum(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("accumulate_minimum(case1)" * doctest::test_suite("view::accumulate_minimum"))
{
    ACCUMULATE_MINIMUM_SUBCASE( case1,   a, axis );
    ACCUMULATE_MINIMUM_SUBCASE( case1, a_a, axis );
    ACCUMULATE_MINIMUM_SUBCASE( case1, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_MINIMUM_SUBCASE( case1, a_d, axis );
    ACCUMULATE_MINIMUM_SUBCASE( case1, a_f, axis );
}

TEST_CASE("accumulate_minimum(case2)" * doctest::test_suite("view::accumulate_minimum"))
{
    ACCUMULATE_MINIMUM_SUBCASE( case2,   a, axis );
    ACCUMULATE_MINIMUM_SUBCASE( case2, a_a, axis );
    ACCUMULATE_MINIMUM_SUBCASE( case2, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_MINIMUM_SUBCASE( case2, a_d, axis );
    ACCUMULATE_MINIMUM_SUBCASE( case2, a_f, axis );
}

TEST_CASE("accumulate_minimum(case3)" * doctest::test_suite("view::accumulate_minimum"))
{
    ACCUMULATE_MINIMUM_SUBCASE( case3,   a, axis );
    ACCUMULATE_MINIMUM_SUBCASE( case3, a_a, axis );
    ACCUMULATE_MINIMUM_SUBCASE( case3, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_MINIMUM_SUBCASE( case3, a_d, axis );
    ACCUMULATE_MINIMUM_SUBCASE( case3, a_f, axis );
}

#define OUTER_MINIMUM_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, outer_minimum, case_name); \
    using namespace args; \
    auto result = view::outer_minimum(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("outer_minimum(case1)" * doctest::test_suite("view::outer_minimum"))
{
    OUTER_MINIMUM_SUBCASE( case1,   a,   b );
    OUTER_MINIMUM_SUBCASE( case1, a_a, b_a );
    OUTER_MINIMUM_SUBCASE( case1, a_f, b_f );
    OUTER_MINIMUM_SUBCASE( case1, a_d, b_d );
    OUTER_MINIMUM_SUBCASE( case1, a_h, b_h );
}