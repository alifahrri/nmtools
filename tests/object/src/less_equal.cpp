#include "nmtools/array/ufuncs/less_equal.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/data/array/less_equal.hpp"
#include "nmtools/testing/doctest.hpp"

#include <algorithm> // std::max

namespace nm = nmtools;

#define OBJECT_LESS_EQUAL_SUBCASE(case_name, a, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, less_equal, case_name); \
    using namespace args; \
    auto object = nmtools::array(a,nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(object) ); \
    auto result = object.less_equal( __VA_ARGS__); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define LESS_EQUAL_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, less_equal, case_name); \
    using namespace args; \
    auto result = nmtools::less_equal( __VA_ARGS__,nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("less_equal(case1)" * doctest::test_suite("array::less_equal"))
{
    LESS_EQUAL_SUBCASE( case1,   a,   b );
    LESS_EQUAL_SUBCASE( case1, a_a, b_a );
    LESS_EQUAL_SUBCASE( case1, a_f, b_f );
    LESS_EQUAL_SUBCASE( case1, a_d, b_d );
    LESS_EQUAL_SUBCASE( case1, a_h, b_h );

    OBJECT_LESS_EQUAL_SUBCASE( case1,   a,   b );
    OBJECT_LESS_EQUAL_SUBCASE( case1, a_a, b_a );
    OBJECT_LESS_EQUAL_SUBCASE( case1, a_f, b_f );
    OBJECT_LESS_EQUAL_SUBCASE( case1, a_d, b_d );
    OBJECT_LESS_EQUAL_SUBCASE( case1, a_h, b_h );
}