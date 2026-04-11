#include "nmtools/array/ufuncs/sin.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/data/array/sin.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;

#define OBJECT_SIN_SUBCASE(case_name, a, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, sin, case_name); \
    using namespace args; \
    auto object = nmtools::array(a,nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(object) ); \
    auto result = object.sin(__VA_ARGS__); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define SIN_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, sin, case_name); \
    using namespace args; \
    auto result = nmtools::sin(__VA_ARGS__, nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("sin(case1)" * doctest::test_suite("array::sin"))
{
    SIN_SUBCASE( case1,   a);
    SIN_SUBCASE( case1, a_a);
    SIN_SUBCASE( case1, a_f);
    SIN_SUBCASE( case1, a_d);
    SIN_SUBCASE( case1, a_h);

    OBJECT_SIN_SUBCASE( case1,   a);
    OBJECT_SIN_SUBCASE( case1, a_a);
    OBJECT_SIN_SUBCASE( case1, a_f);
    OBJECT_SIN_SUBCASE( case1, a_d);
    OBJECT_SIN_SUBCASE( case1, a_h);
}