#include "nmtools/array/ufuncs/fmax.hpp"
#include "nmtools/testing/data/array/fmax.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/constants.hpp" // Required for None, True, False

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
    REDUCE_FMAX_SUBCASE( case1, a_d, axis );
    REDUCE_FMAX_SUBCASE( case1, a_h, axis );
}

TEST_CASE("reduce_fmax(case2)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case2,   a, axis );
    REDUCE_FMAX_SUBCASE( case2, a_a, axis );
    REDUCE_FMAX_SUBCASE( case2, a_f, axis );
    REDUCE_FMAX_SUBCASE( case2, a_d, axis );
    REDUCE_FMAX_SUBCASE( case2, a_h, axis );
}

TEST_CASE("reduce_fmax(case3)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case3,   a, axis );
    REDUCE_FMAX_SUBCASE( case3, a_a, axis );
    REDUCE_FMAX_SUBCASE( case3, a_f, axis );
    REDUCE_FMAX_SUBCASE( case3, a_d, axis );
    REDUCE_FMAX_SUBCASE( case3, a_h, axis );
}

TEST_CASE("reduce_fmax(case4)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case4,   a, axis );
    REDUCE_FMAX_SUBCASE( case4, a_a, axis );
    REDUCE_FMAX_SUBCASE( case4, a_f, axis );
    REDUCE_FMAX_SUBCASE( case4, a_d, axis );
    REDUCE_FMAX_SUBCASE( case4, a_h, axis );
}

TEST_CASE("reduce_fmax(case5)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case5,   a, axis );
    REDUCE_FMAX_SUBCASE( case5, a_a, axis );
    REDUCE_FMAX_SUBCASE( case5, a_f, axis );
    REDUCE_FMAX_SUBCASE( case5, a_d, axis );
    REDUCE_FMAX_SUBCASE( case5, a_h, axis );
}

TEST_CASE("reduce_fmax(case6)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case6,   a, axis );
    REDUCE_FMAX_SUBCASE( case6, a_a, axis );
    REDUCE_FMAX_SUBCASE( case6, a_f, axis );
    REDUCE_FMAX_SUBCASE( case6, a_d, axis );
    REDUCE_FMAX_SUBCASE( case6, a_h, axis );
}

TEST_CASE("reduce_fmax(case7)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case7,   a, axis, dtype, initial );
    REDUCE_FMAX_SUBCASE( case7, a_a, axis, dtype, initial );
    REDUCE_FMAX_SUBCASE( case7, a_f, axis, dtype, initial );
    REDUCE_FMAX_SUBCASE( case7, a_h, axis, dtype, initial );
    REDUCE_FMAX_SUBCASE( case7, a_d, axis, dtype, initial );
}

TEST_CASE("reduce_fmax(case8)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case8,   a, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case8, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case8, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case8, a_h, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case8, a_d, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_fmax(case9)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case9,   a, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case9, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case9, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case9, a_h, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case9, a_d, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_fmax(case10)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case10,   a, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case10, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case10, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case10, a_h, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case10, a_d, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_fmax(case11)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case11,   a, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case11, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case11, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case11, a_h, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case11, a_d, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_fmax(case12)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case12,   a, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case12, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case12, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case12, a_h, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case12, a_d, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_fmax(case13)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case13,   a, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case13, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case13, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case13, a_h, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case13, a_d, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_fmax(case14)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case14,   a, axis );
    REDUCE_FMAX_SUBCASE( case14, a_a, axis );
    REDUCE_FMAX_SUBCASE( case14, a_f, axis );
    REDUCE_FMAX_SUBCASE( case14, a_h, axis );
    REDUCE_FMAX_SUBCASE( case14, a_d, axis );
}

TEST_CASE("reduce_fmax(case15)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case15,   a, axis, nm::None, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case15, a_a, axis, nm::None, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case15, a_f, axis, nm::None, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case15, a_h, axis, nm::None, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case15, a_d, axis, nm::None, initial, keepdims );
}

TEST_CASE("reduce_fmax(case16)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case16,   a, axis, nm::None, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case16, a_a, axis, nm::None, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case16, a_f, axis, nm::None, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case16, a_h, axis, nm::None, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case16, a_d, axis, nm::None, initial, keepdims );
}

TEST_CASE("reduce_fmax(case17)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case17,   a, axis, nm::None, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case17, a_a, axis, nm::None, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case17, a_f, axis, nm::None, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case17, a_h, axis, nm::None, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case17, a_d, axis, nm::None, initial, keepdims );
}

TEST_CASE("reduce_fmax(case18)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case18,   a, axis, nm::None, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case18, a_a, axis, nm::None, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case18, a_f, axis, nm::None, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case18, a_h, axis, nm::None, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case18, a_d, axis, nm::None, initial, keepdims );
}

// Test cases for reduce_fmax with where argument (cases 19-29)
TEST_CASE("reduce_fmax(case19)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case19, a, axis, nm::None, fmax_initial, nm::False, mask );
    REDUCE_FMAX_SUBCASE( case19, a_a, axis, nm::None, fmax_initial, nm::False, mask );
    REDUCE_FMAX_SUBCASE( case19, a_f, axis, nm::None, fmax_initial, nm::False, mask );
    REDUCE_FMAX_SUBCASE( case19, a_h, axis, nm::None, fmax_initial, nm::False, mask );
    REDUCE_FMAX_SUBCASE( case19, a_d, axis, nm::None, fmax_initial, nm::False, mask );
}

TEST_CASE("reduce_fmax(case20)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case20, a, axis, nm::None, -1.0f, nm::True, mask );
    REDUCE_FMAX_SUBCASE( case20, a_a, axis, nm::None, -1.0f, nm::True, mask );
    REDUCE_FMAX_SUBCASE( case20, a_f, axis, nm::None, -1.0f, nm::True, mask );
    REDUCE_FMAX_SUBCASE( case20, a_h, axis, nm::None, -1.0f, nm::True, mask );
    REDUCE_FMAX_SUBCASE( case20, a_d, axis, nm::None, -1.0f, nm::True, mask );
}

TEST_CASE("reduce_fmax(case21)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case21, a, axis, nm::None, fmax_initial, nm::True, mask );
    REDUCE_FMAX_SUBCASE( case21, a_a, axis, nm::None, fmax_initial, nm::True, mask );
    REDUCE_FMAX_SUBCASE( case21, a_f, axis, nm::None, fmax_initial, nm::True, mask );
    REDUCE_FMAX_SUBCASE( case21, a_h, axis, nm::None, fmax_initial, nm::True, mask );
    REDUCE_FMAX_SUBCASE( case21, a_d, axis, nm::None, fmax_initial, nm::True, mask );
}

TEST_CASE("reduce_fmax(case22)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case22, a, axis, nm::None, fmax_initial, nm::False, mask );
    REDUCE_FMAX_SUBCASE( case22, a_a, axis, nm::None, fmax_initial, nm::False, mask );
    REDUCE_FMAX_SUBCASE( case22, a_f, axis, nm::None, fmax_initial, nm::False, mask );
    REDUCE_FMAX_SUBCASE( case22, a_h, axis, nm::None, fmax_initial, nm::False, mask );
    REDUCE_FMAX_SUBCASE( case22, a_d, axis, nm::None, fmax_initial, nm::False, mask );
}

TEST_CASE("reduce_fmax(case23)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case23, a, axis, nm::None, 100.0f, nm::False, mask );
    REDUCE_FMAX_SUBCASE( case23, a_a, axis, nm::None, 100.0f, nm::False, mask );
    REDUCE_FMAX_SUBCASE( case23, a_f, axis, nm::None, 100.0f, nm::False, mask );
    REDUCE_FMAX_SUBCASE( case23, a_h, axis, nm::None, 100.0f, nm::False, mask );
    REDUCE_FMAX_SUBCASE( case23, a_d, axis, nm::None, 100.0f, nm::False, mask );
}

TEST_CASE("reduce_fmax(case24)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case24, a, axis, nm::None, fmax_initial, nm::False, mask );
    REDUCE_FMAX_SUBCASE( case24, a_a, axis, nm::None, fmax_initial, nm::False, mask );
    REDUCE_FMAX_SUBCASE( case24, a_f, axis, nm::None, fmax_initial, nm::False, mask );
    REDUCE_FMAX_SUBCASE( case24, a_h, axis, nm::None, fmax_initial, nm::False, mask );
    REDUCE_FMAX_SUBCASE( case24, a_d, axis, nm::None, fmax_initial, nm::False, mask );
}

TEST_CASE("reduce_fmax(case25)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case25, a, axis, nm::None, fmax_initial, nm::True, mask );
    REDUCE_FMAX_SUBCASE( case25, a_a, axis, nm::None, fmax_initial, nm::True, mask );
    REDUCE_FMAX_SUBCASE( case25, a_f, axis, nm::None, fmax_initial, nm::True, mask );
    REDUCE_FMAX_SUBCASE( case25, a_h, axis, nm::None, fmax_initial, nm::True, mask );
    REDUCE_FMAX_SUBCASE( case25, a_d, axis, nm::None, fmax_initial, nm::True, mask );
}

TEST_CASE("reduce_fmax(case26)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case26, a, axis, nm::None, 5.5f, nm::True, mask );
    REDUCE_FMAX_SUBCASE( case26, a_a, axis, nm::None, 5.5f, nm::True, mask );
    REDUCE_FMAX_SUBCASE( case26, a_f, axis, nm::None, 5.5f, nm::True, mask );
    REDUCE_FMAX_SUBCASE( case26, a_h, axis, nm::None, 5.5f, nm::True, mask );
    REDUCE_FMAX_SUBCASE( case26, a_d, axis, nm::None, 5.5f, nm::True, mask );
}

TEST_CASE("reduce_fmax(case27)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case27, a, axis, nm::None, 15.0f, nm::True, mask );
    REDUCE_FMAX_SUBCASE( case27, a_a, axis, nm::None, 15.0f, nm::True, mask );
    REDUCE_FMAX_SUBCASE( case27, a_f, axis, nm::None, 15.0f, nm::True, mask );
    REDUCE_FMAX_SUBCASE( case27, a_h, axis, nm::None, 15.0f, nm::True, mask );
    REDUCE_FMAX_SUBCASE( case27, a_d, axis, nm::None, 15.0f, nm::True, mask );
}

TEST_CASE("reduce_fmax(case28)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case28, a, axis, nm::None, 15.0f, nm::False, mask );
    REDUCE_FMAX_SUBCASE( case28, a_a, axis, nm::None, 15.0f, nm::False, mask );
    REDUCE_FMAX_SUBCASE( case28, a_f, axis, nm::None, 15.0f, nm::False, mask );
    REDUCE_FMAX_SUBCASE( case28, a_h, axis, nm::None, 15.0f, nm::False, mask );
    REDUCE_FMAX_SUBCASE( case28, a_d, axis, nm::None, 15.0f, nm::False, mask );
}

TEST_CASE("reduce_fmax(case29)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case29, a, axis, nm::None, fmax_initial, nm::False, mask );
    REDUCE_FMAX_SUBCASE( case29, a_a, axis, nm::None, fmax_initial, nm::False, mask );
    REDUCE_FMAX_SUBCASE( case29, a_f, axis, nm::None, fmax_initial, nm::False, mask );
    REDUCE_FMAX_SUBCASE( case29, a_h, axis, nm::None, fmax_initial, nm::False, mask );
    REDUCE_FMAX_SUBCASE( case29, a_d, axis, nm::None, fmax_initial, nm::False, mask );
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
    // ACCUMULATE_FMAX_SUBCASE( case1, a_d, axis );
    // ACCUMULATE_FMAX_SUBCASE( case1, a_h, axis );
}

TEST_CASE("accumulate_fmax(case2)" * doctest::test_suite("view::accumulate_fmax"))
{
    ACCUMULATE_FMAX_SUBCASE( case2,   a, axis );
    ACCUMULATE_FMAX_SUBCASE( case2, a_a, axis );
    ACCUMULATE_FMAX_SUBCASE( case2, a_f, axis );
    // ACCUMULATE_FMAX_SUBCASE( case2, a_d, axis );
    // ACCUMULATE_FMAX_SUBCASE( case2, a_h, axis );
}

TEST_CASE("accumulate_fmax(case3)" * doctest::test_suite("view::accumulate_fmax"))
{
    ACCUMULATE_FMAX_SUBCASE( case3,   a, axis );
    ACCUMULATE_FMAX_SUBCASE( case3, a_a, axis );
    ACCUMULATE_FMAX_SUBCASE( case3, a_f, axis );
    // ACCUMULATE_FMAX_SUBCASE( case3, a_d, axis );
    // ACCUMULATE_FMAX_SUBCASE( case3, a_h, axis );
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
