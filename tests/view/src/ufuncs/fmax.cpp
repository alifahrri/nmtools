#include "nmtools/array/view/ufuncs/fmax.hpp"
#include "nmtools/testing/data/array/fmax.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define FMAX_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, fmax, case_name); \
    using namespace args; \
    auto result = view::fmax(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("fmax(case1)" * doctest::test_suite("view::fmax"))
{
    FMAX_SUBCASE( case1,   a,   b );
    FMAX_SUBCASE( case1, a_a, b_a );
    FMAX_SUBCASE( case1, a_f, b_f );
    FMAX_SUBCASE( case1, a_d, b_d );
    FMAX_SUBCASE( case1, a_h, b_h );
}

TEST_CASE("fmax(case2)" * doctest::test_suite("view::fmax"))
{
    FMAX_SUBCASE( case2,   a, b );
    FMAX_SUBCASE( case2, a_a, b );
    FMAX_SUBCASE( case2, a_f, b );
    FMAX_SUBCASE( case2, a_d, b );
    FMAX_SUBCASE( case2, a_h, b );
}

#define REDUCE_FMAX_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, reduce_fmax, case_name); \
    using namespace args; \
    auto result = view::reduce_fmax(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("reduce_fmax(case1)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case1,   a, axis );
    REDUCE_FMAX_SUBCASE( case1, a_a, axis );
    REDUCE_FMAX_SUBCASE( case1, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_FMAX_SUBCASE( case1, a_d, axis );
    REDUCE_FMAX_SUBCASE( case1, a_f, axis );
}

TEST_CASE("reduce_fmax(case2)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case2,   a, axis );
    REDUCE_FMAX_SUBCASE( case2, a_a, axis );
    REDUCE_FMAX_SUBCASE( case2, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_FMAX_SUBCASE( case2, a_d, axis );
    REDUCE_FMAX_SUBCASE( case2, a_f, axis );
}

TEST_CASE("reduce_fmax(case3)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case3,   a, axis );
    REDUCE_FMAX_SUBCASE( case3, a_a, axis );
    REDUCE_FMAX_SUBCASE( case3, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_FMAX_SUBCASE( case3, a_d, axis );
    REDUCE_FMAX_SUBCASE( case3, a_f, axis );
}

TEST_CASE("reduce_fmax(case4)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case4,   a, axis );
    REDUCE_FMAX_SUBCASE( case4, a_a, axis );
    REDUCE_FMAX_SUBCASE( case4, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_FMAX_SUBCASE( case4, a_d, axis );
    REDUCE_FMAX_SUBCASE( case4, a_f, axis );
}

TEST_CASE("reduce_fmax(case5)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case5,   a, axis );
    REDUCE_FMAX_SUBCASE( case5, a_a, axis );
    REDUCE_FMAX_SUBCASE( case5, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_FMAX_SUBCASE( case5, a_d, axis );
    REDUCE_FMAX_SUBCASE( case5, a_f, axis );
}

TEST_CASE("reduce_fmax(case6)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case6,   a, axis );
    REDUCE_FMAX_SUBCASE( case6, a_a, axis );
    REDUCE_FMAX_SUBCASE( case6, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_FMAX_SUBCASE( case6, a_d, axis );
    REDUCE_FMAX_SUBCASE( case6, a_f, axis );
}

TEST_CASE("reduce_fmax(case7)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case7,   a, axis, dtype, initial );
    REDUCE_FMAX_SUBCASE( case7, a_a, axis, dtype, initial );
    REDUCE_FMAX_SUBCASE( case7, a_f, axis, dtype, initial );
    REDUCE_FMAX_SUBCASE( case7, a_f, axis, dtype, initial );
}

TEST_CASE("reduce_fmax(case8)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case8,   a, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case8, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case8, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case8, a_f, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_fmax(case9)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case9,   a, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case9, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case9, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case9, a_f, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_fmax(case10)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case10,   a, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case10, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case10, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case10, a_f, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_fmax(case11)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case11,   a, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case11, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case11, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case11, a_f, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_fmax(case12)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case12,   a, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case12, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case12, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case12, a_f, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_fmax(case13)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case13,   a, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case13, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case13, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case13, a_f, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_fmax(case14)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case14,   a, axis );
    REDUCE_FMAX_SUBCASE( case14, a_a, axis );
    REDUCE_FMAX_SUBCASE( case14, a_f, axis );
    REDUCE_FMAX_SUBCASE( case14, a_f, axis );
}

TEST_CASE("reduce_fmax(case15)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case15,   a, axis, nm::None, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case15, a_a, axis, nm::None, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case15, a_f, axis, nm::None, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case15, a_f, axis, nm::None, initial, keepdims );
}

TEST_CASE("reduce_fmax(case16)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case16,   a, axis, nm::None, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case16, a_a, axis, nm::None, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case16, a_f, axis, nm::None, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case16, a_f, axis, nm::None, initial, keepdims );
}

TEST_CASE("reduce_fmax(case17)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case17,   a, axis, nm::None, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case17, a_a, axis, nm::None, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case17, a_f, axis, nm::None, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case17, a_f, axis, nm::None, initial, keepdims );
}

TEST_CASE("reduce_fmax(case18)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case18,   a, axis, nm::None, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case18, a_a, axis, nm::None, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case18, a_f, axis, nm::None, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case18, a_f, axis, nm::None, initial, keepdims );
}

#define ACCUMULATE_FMAX_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, accumulate_fmax, case_name); \
    using namespace args; \
    auto result = view::accumulate_fmax(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("accumulate_fmax(case1)" * doctest::test_suite("view::accumulate_fmax"))
{
    ACCUMULATE_FMAX_SUBCASE( case1,   a, axis );
    ACCUMULATE_FMAX_SUBCASE( case1, a_a, axis );
    ACCUMULATE_FMAX_SUBCASE( case1, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_FMAX_SUBCASE( case1, a_d, axis );
    ACCUMULATE_FMAX_SUBCASE( case1, a_f, axis );
}

TEST_CASE("accumulate_fmax(case2)" * doctest::test_suite("view::accumulate_fmax"))
{
    ACCUMULATE_FMAX_SUBCASE( case2,   a, axis );
    ACCUMULATE_FMAX_SUBCASE( case2, a_a, axis );
    ACCUMULATE_FMAX_SUBCASE( case2, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_FMAX_SUBCASE( case2, a_d, axis );
    ACCUMULATE_FMAX_SUBCASE( case2, a_f, axis );
}

TEST_CASE("accumulate_fmax(case3)" * doctest::test_suite("view::accumulate_fmax"))
{
    ACCUMULATE_FMAX_SUBCASE( case3,   a, axis );
    ACCUMULATE_FMAX_SUBCASE( case3, a_a, axis );
    ACCUMULATE_FMAX_SUBCASE( case3, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_FMAX_SUBCASE( case3, a_d, axis );
    ACCUMULATE_FMAX_SUBCASE( case3, a_f, axis );
}

#define OUTER_FMAX_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, outer_fmax, case_name); \
    using namespace args; \
    auto result = view::outer_fmax(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("outer_fmax(case1)" * doctest::test_suite("view::outer_fmax"))
{
    OUTER_FMAX_SUBCASE( case1,   a,   b );
    OUTER_FMAX_SUBCASE( case1, a_a, b_a );
    OUTER_FMAX_SUBCASE( case1, a_f, b_f );
    OUTER_FMAX_SUBCASE( case1, a_d, b_d );
    OUTER_FMAX_SUBCASE( case1, a_h, b_h );
}