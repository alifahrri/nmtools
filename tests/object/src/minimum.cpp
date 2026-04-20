#include "nmtools/array/ufuncs/minimum.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/data/array/minimum.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;

#define OBJECT_MINIMUM_SUBCASE(case_name, a, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, minimum, case_name); \
    using namespace args; \
    auto object = nmtools::array(a,nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(object) ); \
    auto result = object.minimum(__VA_ARGS__); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define MINIMUM_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, minimum, case_name); \
    using namespace args; \
    auto result = nmtools::minimum(__VA_ARGS__, nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("minimum(case1)" * doctest::test_suite("array::minimum"))
{
    MINIMUM_SUBCASE( case1,   a,   b );
    MINIMUM_SUBCASE( case1, a_a, b_a );
    MINIMUM_SUBCASE( case1, a_f, b_f );
    MINIMUM_SUBCASE( case1, a_d, b_d );
    MINIMUM_SUBCASE( case1, a_h, b_h );

    OBJECT_MINIMUM_SUBCASE( case1,   a,   b );
    OBJECT_MINIMUM_SUBCASE( case1, a_a, b_a );
    OBJECT_MINIMUM_SUBCASE( case1, a_f, b_f );
    OBJECT_MINIMUM_SUBCASE( case1, a_d, b_d );
    OBJECT_MINIMUM_SUBCASE( case1, a_h, b_h );
}

TEST_CASE("minimum(case2)" * doctest::test_suite("array::minimum"))
{
    MINIMUM_SUBCASE( case2,   a, b );
    MINIMUM_SUBCASE( case2, a_a, b );
    MINIMUM_SUBCASE( case2, a_f, b );
    MINIMUM_SUBCASE( case2, a_d, b );
    MINIMUM_SUBCASE( case2, a_h, b );

    OBJECT_MINIMUM_SUBCASE( case2,   a, b );
    OBJECT_MINIMUM_SUBCASE( case2, a_a, b );
    OBJECT_MINIMUM_SUBCASE( case2, a_f, b );
    OBJECT_MINIMUM_SUBCASE( case2, a_d, b );
    OBJECT_MINIMUM_SUBCASE( case2, a_h, b );
}

#define OBJECT_REDUCE_MINIMUM_SUBCASE(case_name, a, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, reduce_minimum, case_name); \
    using namespace args; \
    auto object = nmtools::array(a,nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(object) ); \
    auto result = object.reduce_minimum(__VA_ARGS__); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define REDUCE_MINIMUM_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, reduce_minimum, case_name); \
    using namespace args; \
    auto result = nmtools::minimum.reduce(__VA_ARGS__,nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("reduce_minimum(case1)" * doctest::test_suite("array::reduce_minimum"))
{
    REDUCE_MINIMUM_SUBCASE( case1,   a, axis );
    REDUCE_MINIMUM_SUBCASE( case1, a_a, axis );
    REDUCE_MINIMUM_SUBCASE( case1, a_f, axis );
    REDUCE_MINIMUM_SUBCASE( case1, a_d, axis );
    REDUCE_MINIMUM_SUBCASE( case1, a_h, axis );

    OBJECT_REDUCE_MINIMUM_SUBCASE( case1,   a, axis );
    OBJECT_REDUCE_MINIMUM_SUBCASE( case1, a_a, axis );
    OBJECT_REDUCE_MINIMUM_SUBCASE( case1, a_f, axis );
    OBJECT_REDUCE_MINIMUM_SUBCASE( case1, a_d, axis );
    OBJECT_REDUCE_MINIMUM_SUBCASE( case1, a_h, axis );
}

TEST_CASE("reduce_minimum(case7)" * doctest::test_suite("array::reduce_minimum"))
{
    REDUCE_MINIMUM_SUBCASE( case7,   a, axis, dtype, initial );
    REDUCE_MINIMUM_SUBCASE( case7, a_a, axis, dtype, initial );
    REDUCE_MINIMUM_SUBCASE( case7, a_f, axis, dtype, initial );
    REDUCE_MINIMUM_SUBCASE( case7, a_h, axis, dtype, initial );

    OBJECT_REDUCE_MINIMUM_SUBCASE( case7,   a, axis, dtype, initial );
    OBJECT_REDUCE_MINIMUM_SUBCASE( case7, a_a, axis, dtype, initial );
    OBJECT_REDUCE_MINIMUM_SUBCASE( case7, a_f, axis, dtype, initial );
    OBJECT_REDUCE_MINIMUM_SUBCASE( case7, a_h, axis, dtype, initial );
}

TEST_CASE("reduce_minimum(case8)" * doctest::test_suite("array::reduce_minimum"))
{
    REDUCE_MINIMUM_SUBCASE( case8,   a, axis, dtype, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case8, a_a, axis, dtype, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case8, a_f, axis, dtype, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case8, a_h, axis, dtype, initial, keepdims );

    OBJECT_REDUCE_MINIMUM_SUBCASE( case8,   a, axis, dtype, initial, keepdims );
    OBJECT_REDUCE_MINIMUM_SUBCASE( case8, a_a, axis, dtype, initial, keepdims );
    OBJECT_REDUCE_MINIMUM_SUBCASE( case8, a_f, axis, dtype, initial, keepdims );
    OBJECT_REDUCE_MINIMUM_SUBCASE( case8, a_h, axis, dtype, initial, keepdims );
}

#define OBJECT_ACCUMULATE_MINIMUM_SUBCASE(case_name, a, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, accumulate_minimum, case_name); \
    using namespace args; \
    auto object = nmtools::array(a,nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(object) ); \
    auto result = object.accumulate_minimum(__VA_ARGS__); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define ACCUMULATE_MINIMUM_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, accumulate_minimum, case_name); \
    using namespace args; \
    auto result = nmtools::minimum.accumulate(__VA_ARGS__, nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("accumulate_minimum(case1)" * doctest::test_suite("array::accumulate_minimum"))
{
    ACCUMULATE_MINIMUM_SUBCASE( case1,   a, axis );
    ACCUMULATE_MINIMUM_SUBCASE( case1, a_a, axis );
    ACCUMULATE_MINIMUM_SUBCASE( case1, a_f, axis );
    ACCUMULATE_MINIMUM_SUBCASE( case1, a_d, axis );
    ACCUMULATE_MINIMUM_SUBCASE( case1, a_f, axis );

    OBJECT_ACCUMULATE_MINIMUM_SUBCASE( case1,   a, axis );
    OBJECT_ACCUMULATE_MINIMUM_SUBCASE( case1, a_a, axis );
    OBJECT_ACCUMULATE_MINIMUM_SUBCASE( case1, a_f, axis );
    OBJECT_ACCUMULATE_MINIMUM_SUBCASE( case1, a_d, axis );
    OBJECT_ACCUMULATE_MINIMUM_SUBCASE( case1, a_f, axis );
}

#define OBJECT_OUTER_MINIMUM_SUBCASE(case_name, a, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, outer_minimum, case_name); \
    using namespace args; \
    auto object = nmtools::array(a,nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(object) ); \
    auto result = object.outer_minimum( __VA_ARGS__); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define OUTER_MINIMUM_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, outer_minimum, case_name); \
    using namespace args; \
    auto result = nmtools::minimum.outer( __VA_ARGS__, nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("outer_minimum(case1)" * doctest::test_suite("array::outer_minimum"))
{
    OUTER_MINIMUM_SUBCASE( case1,   a,   b );
    OUTER_MINIMUM_SUBCASE( case1, a_a, b_a );
    OUTER_MINIMUM_SUBCASE( case1, a_f, b_f );
    OUTER_MINIMUM_SUBCASE( case1, a_d, b_d );
    OUTER_MINIMUM_SUBCASE( case1, a_h, b_h );

    OBJECT_OUTER_MINIMUM_SUBCASE( case1,   a,   b );
    OBJECT_OUTER_MINIMUM_SUBCASE( case1, a_a, b_a );
    OBJECT_OUTER_MINIMUM_SUBCASE( case1, a_f, b_f );
    OBJECT_OUTER_MINIMUM_SUBCASE( case1, a_d, b_d );
    OBJECT_OUTER_MINIMUM_SUBCASE( case1, a_h, b_h );
}