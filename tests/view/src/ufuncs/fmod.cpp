#include "nmtools/array/view/ufuncs/fmod.hpp"
#include "nmtools/testing/data/array/fmod.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define FMOD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, fmod, case_name); \
    using namespace args; \
    auto result = view::fmod( __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("fmod(case1)" * doctest::test_suite("view::fmod"))
{
    FMOD_SUBCASE( case1,   a,   b );
    FMOD_SUBCASE( case1, a_a, b_a );
    FMOD_SUBCASE( case1, a_f, b_f );
    FMOD_SUBCASE( case1, a_d, b_d );
    FMOD_SUBCASE( case1, a_h, b_h );
}

TEST_CASE("fmod(case2)" * doctest::test_suite("view::fmod"))
{
    FMOD_SUBCASE( case2,   a, b );
    FMOD_SUBCASE( case2, a_a, b );
    FMOD_SUBCASE( case2, a_f, b );
    FMOD_SUBCASE( case2, a_d, b );
    FMOD_SUBCASE( case2, a_h, b );
}

#define REDUCE_FMOD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, reduce_fmod, case_name); \
    using namespace args; \
    auto result = view::reduce_fmod(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("reduce_fmod(case1)" * doctest::test_suite("view::reduce_fmod"))
{
    REDUCE_FMOD_SUBCASE( case1,   a, axis );
    REDUCE_FMOD_SUBCASE( case1, a_a, axis );
    REDUCE_FMOD_SUBCASE( case1, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_FMOD_SUBCASE( case1, a_d, axis );
    REDUCE_FMOD_SUBCASE( case1, a_f, axis );
}

TEST_CASE("reduce_fmod(case2)" * doctest::test_suite("view::reduce_fmod"))
{
    REDUCE_FMOD_SUBCASE( case2,   a, axis );
    REDUCE_FMOD_SUBCASE( case2, a_a, axis );
    REDUCE_FMOD_SUBCASE( case2, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_FMOD_SUBCASE( case2, a_d, axis );
    REDUCE_FMOD_SUBCASE( case2, a_f, axis );
}

TEST_CASE("reduce_fmod(case3)" * doctest::test_suite("view::reduce_fmod"))
{
    REDUCE_FMOD_SUBCASE( case3,   a, axis );
    REDUCE_FMOD_SUBCASE( case3, a_a, axis );
    REDUCE_FMOD_SUBCASE( case3, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_FMOD_SUBCASE( case3, a_d, axis );
    REDUCE_FMOD_SUBCASE( case3, a_f, axis );
}

TEST_CASE("reduce_fmod(case4)" * doctest::test_suite("view::reduce_fmod"))
{
    REDUCE_FMOD_SUBCASE( case4,   a, axis, dtype, initial );
    REDUCE_FMOD_SUBCASE( case4, a_a, axis, dtype, initial );
    REDUCE_FMOD_SUBCASE( case4, a_f, axis, dtype, initial );
    REDUCE_FMOD_SUBCASE( case4, a_f, axis, dtype, initial );
}

TEST_CASE("reduce_fmod(case5)" * doctest::test_suite("view::reduce_fmod"))
{
    REDUCE_FMOD_SUBCASE( case5,   a, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case5, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case5, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case5, a_f, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_fmod(case6)" * doctest::test_suite("view::reduce_fmod"))
{
    REDUCE_FMOD_SUBCASE( case6,   a, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case6, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case6, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case6, a_f, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_fmod(case7)" * doctest::test_suite("view::reduce_fmod"))
{
    REDUCE_FMOD_SUBCASE( case7,   a, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case7, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case7, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case7, a_f, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_fmod(case8)" * doctest::test_suite("view::reduce_fmod"))
{
    REDUCE_FMOD_SUBCASE( case8,   a, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case8, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case8, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case8, a_f, axis, dtype, initial, keepdims );
}

#define ACCUMULATE_FMOD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, accumulate_fmod, case_name); \
    using namespace args; \
    auto result = view::accumulate_fmod(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("accumulate_fmod(case1)" * doctest::test_suite("view::accumulate_fmod"))
{
    ACCUMULATE_FMOD_SUBCASE( case1,   a, axis );
    ACCUMULATE_FMOD_SUBCASE( case1, a_a, axis );
    ACCUMULATE_FMOD_SUBCASE( case1, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_FMOD_SUBCASE( case1, a_d, axis );
    ACCUMULATE_FMOD_SUBCASE( case1, a_f, axis );
}

TEST_CASE("accumulate_fmod(case2)" * doctest::test_suite("view::accumulate_fmod"))
{
    ACCUMULATE_FMOD_SUBCASE( case2,   a, axis );
    ACCUMULATE_FMOD_SUBCASE( case2, a_a, axis );
    ACCUMULATE_FMOD_SUBCASE( case2, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_FMOD_SUBCASE( case2, a_d, axis );
    ACCUMULATE_FMOD_SUBCASE( case2, a_f, axis );
}

TEST_CASE("accumulate_fmod(case3)" * doctest::test_suite("view::accumulate_fmod"))
{
    ACCUMULATE_FMOD_SUBCASE( case3,   a, axis );
    ACCUMULATE_FMOD_SUBCASE( case3, a_a, axis );
    ACCUMULATE_FMOD_SUBCASE( case3, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_FMOD_SUBCASE( case3, a_d, axis );
    ACCUMULATE_FMOD_SUBCASE( case3, a_f, axis );
}

#define OUTER_FMOD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, outer_fmod, case_name); \
    using namespace args; \
    auto result = view::outer_fmod(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("outer_fmod(case1)" * doctest::test_suite("view::outer_fmod"))
{
    OUTER_FMOD_SUBCASE( case1,   a,   b );
    OUTER_FMOD_SUBCASE( case1, a_a, b_a );
    OUTER_FMOD_SUBCASE( case1, a_f, b_f );
    OUTER_FMOD_SUBCASE( case1, a_d, b_d );
    OUTER_FMOD_SUBCASE( case1, a_h, b_h );
}