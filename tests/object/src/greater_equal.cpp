#include "nmtools/array/ufuncs/greater_equal.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/data/array/greater_equal.hpp"
#include "nmtools/testing/doctest.hpp"

#include <algorithm> // std::max

namespace nm = nmtools;

#define OBJECT_GREATER_EQUAL_SUBCASE(case_name, a, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, greater_equal, case_name); \
    using namespace args; \
    auto object = nmtools::array(a,nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(object) ); \
    auto result = object.greater_equal( __VA_ARGS__); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define GREATER_EQUAL_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, greater_equal, case_name); \
    using namespace args; \
    auto result = nmtools::greater_equal( __VA_ARGS__,nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("greater_equal(case1)" * doctest::test_suite("array::greater_equal"))
{
    GREATER_EQUAL_SUBCASE( case1,   a,   b );
    GREATER_EQUAL_SUBCASE( case1, a_a, b_a );
    GREATER_EQUAL_SUBCASE( case1, a_f, b_f );
    GREATER_EQUAL_SUBCASE( case1, a_d, b_d );
    GREATER_EQUAL_SUBCASE( case1, a_h, b_h );

    OBJECT_GREATER_EQUAL_SUBCASE( case1,   a,   b );
    OBJECT_GREATER_EQUAL_SUBCASE( case1, a_a, b_a );
    OBJECT_GREATER_EQUAL_SUBCASE( case1, a_f, b_f );
    OBJECT_GREATER_EQUAL_SUBCASE( case1, a_d, b_d );
    OBJECT_GREATER_EQUAL_SUBCASE( case1, a_h, b_h );
}