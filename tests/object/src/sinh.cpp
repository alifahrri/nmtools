#include "nmtools/array/ufuncs/sinh.hpp"
#include "nmtools/core/context/object.hpp"
#include "nmtools/testing/data/array/sinh.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;

#define OBJECT_SINH_SUBCASE(case_name, a, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, sinh, case_name); \
    using namespace args; \
    auto object = nmtools::array(a,nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(object) ); \
    auto result = object.sinh(__VA_ARGS__); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define SINH_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, sinh, case_name); \
    using namespace args; \
    auto result = nmtools::sinh(__VA_ARGS__, nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("sinh(case1)" * doctest::test_suite("array::sinh"))
{
    SINH_SUBCASE( case1,   a);
    SINH_SUBCASE( case1, a_a);
    SINH_SUBCASE( case1, a_f);
    SINH_SUBCASE( case1, a_d);
    SINH_SUBCASE( case1, a_h);

    OBJECT_SINH_SUBCASE( case1,   a);
    OBJECT_SINH_SUBCASE( case1, a_a);
    OBJECT_SINH_SUBCASE( case1, a_f);
    OBJECT_SINH_SUBCASE( case1, a_d);
    OBJECT_SINH_SUBCASE( case1, a_h);
}