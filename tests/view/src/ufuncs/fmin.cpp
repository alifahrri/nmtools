#include "nmtools/array/ufuncs/fmin.hpp"
#include "nmtools/testing/data/array/fmin.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;

#define FMIN_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, fmin, case_name); \
    using namespace args; \
    auto result = view::fmin(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("fmin(case1)" * doctest::test_suite("view::fmin"))
{
    FMIN_SUBCASE( case1,   a,   b );
    FMIN_SUBCASE( case1, a_a, b_a );
    FMIN_SUBCASE( case1, a_f, b_f );
    FMIN_SUBCASE( case1, a_d, b_d );
    FMIN_SUBCASE( case1, a_h, b_h );
}

TEST_CASE("fmin(case2)" * doctest::test_suite("view::fmin"))
{
    FMIN_SUBCASE( case2,   a, b );
    FMIN_SUBCASE( case2, a_a, b );
    FMIN_SUBCASE( case2, a_f, b );
    FMIN_SUBCASE( case2, a_d, b );
    FMIN_SUBCASE( case2, a_h, b );
}

#define REDUCE_FMIN_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, reduce_fmin, case_name); \
    using namespace args; \
    auto result = view::reduce_fmin(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("reduce_fmin(case1)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case1,   a, axis );
    REDUCE_FMIN_SUBCASE( case1, a_a, axis );
    REDUCE_FMIN_SUBCASE( case1, a_f, axis );
    REDUCE_FMIN_SUBCASE( case1, a_d, axis );
    REDUCE_FMIN_SUBCASE( case1, a_h, axis );
}

TEST_CASE("reduce_fmin(case2)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case2,   a, axis );
    REDUCE_FMIN_SUBCASE( case2, a_a, axis );
    REDUCE_FMIN_SUBCASE( case2, a_f, axis );
    REDUCE_FMIN_SUBCASE( case2, a_d, axis );
    REDUCE_FMIN_SUBCASE( case2, a_h, axis );
}

TEST_CASE("reduce_fmin(case3)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case3,   a, axis );
    REDUCE_FMIN_SUBCASE( case3, a_a, axis );
    REDUCE_FMIN_SUBCASE( case3, a_f, axis );
    REDUCE_FMIN_SUBCASE( case3, a_d, axis );
    REDUCE_FMIN_SUBCASE( case3, a_h, axis );
}

TEST_CASE("reduce_fmin(case4)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case4,   a, axis );
    REDUCE_FMIN_SUBCASE( case4, a_a, axis );
    REDUCE_FMIN_SUBCASE( case4, a_f, axis );
    REDUCE_FMIN_SUBCASE( case4, a_d, axis );
    REDUCE_FMIN_SUBCASE( case4, a_h, axis );
}

TEST_CASE("reduce_fmin(case5)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case5,   a, axis );
    REDUCE_FMIN_SUBCASE( case5, a_a, axis );
    REDUCE_FMIN_SUBCASE( case5, a_f, axis );
    REDUCE_FMIN_SUBCASE( case5, a_d, axis );
    REDUCE_FMIN_SUBCASE( case5, a_h, axis );
}

TEST_CASE("reduce_fmin(case6)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case6,   a, axis );
    REDUCE_FMIN_SUBCASE( case6, a_a, axis );
    REDUCE_FMIN_SUBCASE( case6, a_f, axis );
    REDUCE_FMIN_SUBCASE( case6, a_d, axis );
    REDUCE_FMIN_SUBCASE( case6, a_h, axis );
}

TEST_CASE("reduce_fmin(case7)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case7,   a, axis, dtype, initial );
    REDUCE_FMIN_SUBCASE( case7, a_a, axis, dtype, initial );
    REDUCE_FMIN_SUBCASE( case7, a_f, axis, dtype, initial );
    REDUCE_FMIN_SUBCASE( case7, a_h, axis, dtype, initial );
    REDUCE_FMIN_SUBCASE( case7, a_d, axis, dtype, initial );
}

TEST_CASE("reduce_fmin(case8)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case8,   a, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case8, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case8, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case8, a_h, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case8, a_d, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_fmin(case9)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case9,   a, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case9, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case9, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case9, a_h, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case9, a_d, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_fmin(case10)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case10,   a, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case10, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case10, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case10, a_h, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case10, a_d, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_fmin(case11)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case11,   a, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case11, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case11, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case11, a_h, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case11, a_d, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_fmin(case12)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case12,   a, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case12, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case12, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case12, a_h, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case12, a_d, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_fmin(case13)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case13,   a, axis );
    REDUCE_FMIN_SUBCASE( case13, a_a, axis );
    REDUCE_FMIN_SUBCASE( case13, a_f, axis );
    REDUCE_FMIN_SUBCASE( case13, a_h, axis );
    REDUCE_FMIN_SUBCASE( case13, a_d, axis );
}

TEST_CASE("reduce_fmin(case14)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case14,   a, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case14, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case14, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case14, a_h, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case14, a_d, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_fmin(case15)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case15,   a, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case15, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case15, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case15, a_h, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case15, a_d, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_fmin(case16)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case16,   a, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case16, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case16, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case16, a_h, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case16, a_d, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_fmin(case17)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case17,   a, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case17, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case17, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case17, a_h, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case17, a_d, axis, dtype, initial, keepdims );
}

// New test cases for reduce_fmin with where argument (cases 18-28)
TEST_CASE("reduce_fmin(case18)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case18, a, axis, dtype, initial, keepdims, mask );
    REDUCE_FMIN_SUBCASE( case18, a_a, axis, dtype, initial, keepdims, mask );
    REDUCE_FMIN_SUBCASE( case18, a_f, axis, dtype, initial, keepdims, mask );
    REDUCE_FMIN_SUBCASE( case18, a_h, axis, dtype, initial, keepdims, mask );
    REDUCE_FMIN_SUBCASE( case18, a_d, axis, dtype, initial, keepdims, mask );
}

TEST_CASE("reduce_fmin(case19)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case19, a, axis, dtype, initial, keepdims, mask );
    REDUCE_FMIN_SUBCASE( case19, a_a, axis, dtype, initial, keepdims, mask );
    REDUCE_FMIN_SUBCASE( case19, a_f, axis, dtype, initial, keepdims, mask );
    REDUCE_FMIN_SUBCASE( case19, a_h, axis, dtype, initial, keepdims, mask );
    REDUCE_FMIN_SUBCASE( case19, a_d, axis, dtype, initial, keepdims, mask );
}

TEST_CASE("reduce_fmin(case20)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case20, a, axis, dtype, initial, keepdims, mask );
    REDUCE_FMIN_SUBCASE( case20, a_a, axis, dtype, initial, keepdims, mask );
    REDUCE_FMIN_SUBCASE( case20, a_f, axis, dtype, initial, keepdims, mask );
    REDUCE_FMIN_SUBCASE( case20, a_h, axis, dtype, initial, keepdims, mask );
    REDUCE_FMIN_SUBCASE( case20, a_d, axis, dtype, initial, keepdims, mask );
}

TEST_CASE("reduce_fmin(case21)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case21, a, axis, dtype, initial, keepdims, mask );
    REDUCE_FMIN_SUBCASE( case21, a_a, axis, dtype, initial, keepdims, mask );
    REDUCE_FMIN_SUBCASE( case21, a_f, axis, dtype, initial, keepdims, mask );
    REDUCE_FMIN_SUBCASE( case21, a_h, axis, dtype, initial, keepdims, mask );
    REDUCE_FMIN_SUBCASE( case21, a_d, axis, dtype, initial, keepdims, mask );
}

TEST_CASE("reduce_fmin(case22)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case22, a, axis, dtype, initial, keepdims, mask );
    REDUCE_FMIN_SUBCASE( case22, a_a, axis, dtype, initial, keepdims, mask );
    REDUCE_FMIN_SUBCASE( case22, a_f, axis, dtype, initial, keepdims, mask );
    REDUCE_FMIN_SUBCASE( case22, a_h, axis, dtype, initial, keepdims, mask );
    REDUCE_FMIN_SUBCASE( case22, a_d, axis, dtype, initial, keepdims, mask );
}

TEST_CASE("reduce_fmin(case23)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case23, a, axis, dtype, initial, keepdims, mask );
    REDUCE_FMIN_SUBCASE( case23, a_a, axis, dtype, initial, keepdims, mask );
    REDUCE_FMIN_SUBCASE( case23, a_f, axis, dtype, initial, keepdims, mask );
    REDUCE_FMIN_SUBCASE( case23, a_h, axis, dtype, initial, keepdims, mask );
    REDUCE_FMIN_SUBCASE( case23, a_d, axis, dtype, initial, keepdims, mask );
}

TEST_CASE("reduce_fmin(case24)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case24, a, axis, dtype, initial, keepdims, mask );
    REDUCE_FMIN_SUBCASE( case24, a_a, axis, dtype, initial, keepdims, mask );
    REDUCE_FMIN_SUBCASE( case24, a_f, axis, dtype, initial, keepdims, mask );
    REDUCE_FMIN_SUBCASE( case24, a_h, axis, dtype, initial, keepdims, mask );
    REDUCE_FMIN_SUBCASE( case24, a_d, axis, dtype, initial, keepdims, mask );
}

TEST_CASE("reduce_fmin(case25)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case25, a, axis, dtype, initial, keepdims, mask );
    REDUCE_FMIN_SUBCASE( case25, a_a, axis, dtype, initial, keepdims, mask );
    REDUCE_FMIN_SUBCASE( case25, a_f, axis, dtype, initial, keepdims, mask );
    REDUCE_FMIN_SUBCASE( case25, a_h, axis, dtype, initial, keepdims, mask );
    REDUCE_FMIN_SUBCASE( case25, a_d, axis, dtype, initial, keepdims, mask );
}

TEST_CASE("reduce_fmin(case26)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case26, a, axis, dtype, initial, keepdims, mask );
    REDUCE_FMIN_SUBCASE( case26, a_a, axis, dtype, initial, keepdims, mask );
    REDUCE_FMIN_SUBCASE( case26, a_f, axis, dtype, initial, keepdims, mask );
    REDUCE_FMIN_SUBCASE( case26, a_h, axis, dtype, initial, keepdims, mask );
    REDUCE_FMIN_SUBCASE( case26, a_d, axis, dtype, initial, keepdims, mask );
}

TEST_CASE("reduce_fmin(case27)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case27, a, axis, dtype, initial, keepdims, mask );
    REDUCE_FMIN_SUBCASE( case27, a_a, axis, dtype, initial, keepdims, mask );
    REDUCE_FMIN_SUBCASE( case27, a_f, axis, dtype, initial, keepdims, mask );
    REDUCE_FMIN_SUBCASE( case27, a_h, axis, dtype, initial, keepdims, mask );
    REDUCE_FMIN_SUBCASE( case27, a_d, axis, dtype, initial, keepdims, mask );
}

TEST_CASE("reduce_fmin(case28)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case28, a, axis, dtype, initial, keepdims, mask );
    REDUCE_FMIN_SUBCASE( case28, a_a, axis, dtype, initial, keepdims, mask );
    REDUCE_FMIN_SUBCASE( case28, a_f, axis, dtype, initial, keepdims, mask );
    REDUCE_FMIN_SUBCASE( case28, a_h, axis, dtype, initial, keepdims, mask );
    REDUCE_FMIN_SUBCASE( case28, a_d, axis, dtype, initial, keepdims, mask );
}

#define ACCUMULATE_FMIN_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, accumulate_fmin, case_name); \
    using namespace args; \
    auto result = view::accumulate_fmin(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("accumulate_fmin(case1)" * doctest::test_suite("view::accumulate_fmin"))
{
    ACCUMULATE_FMIN_SUBCASE( case1,   a, axis );
    ACCUMULATE_FMIN_SUBCASE( case1, a_a, axis );
    ACCUMULATE_FMIN_SUBCASE( case1, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_FMIN_SUBCASE( case1, a_d, axis );
    // ACCUMULATE_FMIN_SUBCASE( case1, a_h, axis );
}

TEST_CASE("accumulate_fmin(case2)" * doctest::test_suite("view::accumulate_fmin"))
{
    ACCUMULATE_FMIN_SUBCASE( case2,   a, axis );
    ACCUMULATE_FMIN_SUBCASE( case2, a_a, axis );
    ACCUMULATE_FMIN_SUBCASE( case2, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_FMIN_SUBCASE( case2, a_d, axis );
    // ACCUMULATE_FMIN_SUBCASE( case2, a_h, axis );
}

TEST_CASE("accumulate_fmin(case3)" * doctest::test_suite("view::accumulate_fmin"))
{
    ACCUMULATE_FMIN_SUBCASE( case3,   a, axis );
    ACCUMULATE_FMIN_SUBCASE( case3, a_a, axis );
    ACCUMULATE_FMIN_SUBCASE( case3, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_FMIN_SUBCASE( case3, a_d, axis );
    // ACCUMULATE_FMIN_SUBCASE( case3, a_h, axis );
}

#define OUTER_FMIN_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, outer_fmin, case_name); \
    using namespace args; \
    auto result = view::outer_fmin(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("outer_fmin(case1)" * doctest::test_suite("view::outer_fmin"))
{
    OUTER_FMIN_SUBCASE( case1,   a,   b );
    OUTER_FMIN_SUBCASE( case1, a_a, b_a );
    OUTER_FMIN_SUBCASE( case1, a_f, b_f );
    OUTER_FMIN_SUBCASE( case1, a_d, b_d );
    OUTER_FMIN_SUBCASE( case1, a_h, b_h );
}