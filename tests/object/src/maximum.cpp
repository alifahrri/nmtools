#include "nmtools/array/ufuncs/maximum.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/data/array/maximum.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;

#define OBJECT_MAXIMUM_SUBCASE(case_name, a, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, maximum, case_name); \
    using namespace args; \
    auto object = nmtools::array(a,nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(object) ); \
    auto result = object.maximum(__VA_ARGS__); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define MAXIMUM_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, maximum, case_name); \
    using namespace args; \
    auto result = nmtools::maximum(__VA_ARGS__, nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
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

    OBJECT_MAXIMUM_SUBCASE( case1,   a,   b );
    OBJECT_MAXIMUM_SUBCASE( case1, a_a, b_a );
    OBJECT_MAXIMUM_SUBCASE( case1, a_f, b_f );
    OBJECT_MAXIMUM_SUBCASE( case1, a_d, b_d );
    OBJECT_MAXIMUM_SUBCASE( case1, a_h, b_h );
}

TEST_CASE("maximum(case2)" * doctest::test_suite("array::maximum"))
{
    MAXIMUM_SUBCASE( case2,   a, b );
    MAXIMUM_SUBCASE( case2, a_a, b );
    MAXIMUM_SUBCASE( case2, a_f, b );
    MAXIMUM_SUBCASE( case2, a_d, b );
    MAXIMUM_SUBCASE( case2, a_h, b );

    OBJECT_MAXIMUM_SUBCASE( case2,   a, b );
    OBJECT_MAXIMUM_SUBCASE( case2, a_a, b );
    OBJECT_MAXIMUM_SUBCASE( case2, a_f, b );
    OBJECT_MAXIMUM_SUBCASE( case2, a_d, b );
    OBJECT_MAXIMUM_SUBCASE( case2, a_h, b );
}

#define OBJECT_REDUCE_MAXIMUM_SUBCASE(case_name, a, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, reduce_maximum, case_name); \
    using namespace args; \
    auto object = nmtools::array(a,nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(object) ); \
    auto result = object.reduce_maximum(__VA_ARGS__); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define REDUCE_MAXIMUM_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, reduce_maximum, case_name); \
    using namespace args; \
    auto result = nmtools::maximum.reduce(__VA_ARGS__,nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("reduce_maximum(case1)" * doctest::test_suite("array::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case1,   a, axis );
    REDUCE_MAXIMUM_SUBCASE( case1, a_a, axis );
    REDUCE_MAXIMUM_SUBCASE( case1, a_f, axis );
    REDUCE_MAXIMUM_SUBCASE( case1, a_d, axis );
    REDUCE_MAXIMUM_SUBCASE( case1, a_h, axis );

    OBJECT_REDUCE_MAXIMUM_SUBCASE( case1,   a, axis );
    OBJECT_REDUCE_MAXIMUM_SUBCASE( case1, a_a, axis );
    OBJECT_REDUCE_MAXIMUM_SUBCASE( case1, a_f, axis );
    OBJECT_REDUCE_MAXIMUM_SUBCASE( case1, a_d, axis );
    OBJECT_REDUCE_MAXIMUM_SUBCASE( case1, a_h, axis );
}

TEST_CASE("reduce_maximum(case7)" * doctest::test_suite("array::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case7,   a, axis, dtype, initial );
    REDUCE_MAXIMUM_SUBCASE( case7, a_a, axis, dtype, initial );
    REDUCE_MAXIMUM_SUBCASE( case7, a_f, axis, dtype, initial );
    REDUCE_MAXIMUM_SUBCASE( case7, a_h, axis, dtype, initial );

    OBJECT_REDUCE_MAXIMUM_SUBCASE( case7,   a, axis, dtype, initial );
    OBJECT_REDUCE_MAXIMUM_SUBCASE( case7, a_a, axis, dtype, initial );
    OBJECT_REDUCE_MAXIMUM_SUBCASE( case7, a_f, axis, dtype, initial );
    OBJECT_REDUCE_MAXIMUM_SUBCASE( case7, a_h, axis, dtype, initial );
}

TEST_CASE("reduce_maximum(case8)" * doctest::test_suite("array::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case8,   a, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case8, a_a, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case8, a_f, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case8, a_h, axis, dtype, initial, keepdims );

    OBJECT_REDUCE_MAXIMUM_SUBCASE( case8,   a, axis, dtype, initial, keepdims );
    OBJECT_REDUCE_MAXIMUM_SUBCASE( case8, a_a, axis, dtype, initial, keepdims );
    OBJECT_REDUCE_MAXIMUM_SUBCASE( case8, a_f, axis, dtype, initial, keepdims );
    OBJECT_REDUCE_MAXIMUM_SUBCASE( case8, a_h, axis, dtype, initial, keepdims );
}

#define OBJECT_ACCUMULATE_MAXIMUM_SUBCASE(case_name, a, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, accumulate_maximum, case_name); \
    using namespace args; \
    auto object = nmtools::array(a,nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(object) ); \
    auto result = object.accumulate_maximum(__VA_ARGS__); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define ACCUMULATE_MAXIMUM_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, accumulate_maximum, case_name); \
    using namespace args; \
    auto result = nmtools::maximum.accumulate(__VA_ARGS__, nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("accumulate_maximum(case1)" * doctest::test_suite("array::accumulate_maximum"))
{
    ACCUMULATE_MAXIMUM_SUBCASE( case1,   a, axis );
    ACCUMULATE_MAXIMUM_SUBCASE( case1, a_a, axis );
    ACCUMULATE_MAXIMUM_SUBCASE( case1, a_f, axis );
    ACCUMULATE_MAXIMUM_SUBCASE( case1, a_d, axis );
    ACCUMULATE_MAXIMUM_SUBCASE( case1, a_f, axis );

    OBJECT_ACCUMULATE_MAXIMUM_SUBCASE( case1,   a, axis );
    OBJECT_ACCUMULATE_MAXIMUM_SUBCASE( case1, a_a, axis );
    OBJECT_ACCUMULATE_MAXIMUM_SUBCASE( case1, a_f, axis );
    OBJECT_ACCUMULATE_MAXIMUM_SUBCASE( case1, a_d, axis );
    OBJECT_ACCUMULATE_MAXIMUM_SUBCASE( case1, a_f, axis );
}

#define OBJECT_OUTER_MAXIMUM_SUBCASE(case_name, a, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, outer_maximum, case_name); \
    using namespace args; \
    auto object = nmtools::array(a,nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(object) ); \
    auto result = object.outer_maximum( __VA_ARGS__); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define OUTER_MAXIMUM_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, outer_maximum, case_name); \
    using namespace args; \
    auto result = nmtools::maximum.outer( __VA_ARGS__, nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("outer_maximum(case1)" * doctest::test_suite("array::outer_maximum"))
{
    OUTER_MAXIMUM_SUBCASE( case1,   a,   b );
    OUTER_MAXIMUM_SUBCASE( case1, a_a, b_a );
    OUTER_MAXIMUM_SUBCASE( case1, a_f, b_f );
    OUTER_MAXIMUM_SUBCASE( case1, a_d, b_d );
    OUTER_MAXIMUM_SUBCASE( case1, a_h, b_h );

    OBJECT_OUTER_MAXIMUM_SUBCASE( case1,   a,   b );
    OBJECT_OUTER_MAXIMUM_SUBCASE( case1, a_a, b_a );
    OBJECT_OUTER_MAXIMUM_SUBCASE( case1, a_f, b_f );
    OBJECT_OUTER_MAXIMUM_SUBCASE( case1, a_d, b_d );
    OBJECT_OUTER_MAXIMUM_SUBCASE( case1, a_h, b_h );
}