#include "nmtools/array/ufuncs/greater.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/data/array/greater.hpp"
#include "nmtools/testing/doctest.hpp"

#include <algorithm> // std::max

namespace nm = nmtools;

#define OBJECT_GREATER_SUBCASE(case_name, a, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, greater, case_name); \
    using namespace args; \
    auto object = nmtools::array(a,nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(object) ); \
    auto result = object.greater( __VA_ARGS__); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define GREATER_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, greater, case_name); \
    using namespace args; \
    auto result = nmtools::greater( __VA_ARGS__,nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("greater(case1)" * doctest::test_suite("array::greater"))
{
    GREATER_SUBCASE( case1,   a,   b );
    GREATER_SUBCASE( case1, a_a, b_a );
    GREATER_SUBCASE( case1, a_f, b_f );
    GREATER_SUBCASE( case1, a_d, b_d );
    GREATER_SUBCASE( case1, a_h, b_h );

    OBJECT_GREATER_SUBCASE( case1,   a,   b );
    OBJECT_GREATER_SUBCASE( case1, a_a, b_a );
    OBJECT_GREATER_SUBCASE( case1, a_f, b_f );
    OBJECT_GREATER_SUBCASE( case1, a_d, b_d );
    OBJECT_GREATER_SUBCASE( case1, a_h, b_h );
}