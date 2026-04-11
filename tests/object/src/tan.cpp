#include "nmtools/array/ufuncs/tan.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/data/array/tan.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;

#define OBJECT_TAN_SUBCASE(case_name, a, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, tan, case_name); \
    using namespace args; \
    auto object = nmtools::array(a,nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(object) ); \
    auto result = object.tan(__VA_ARGS__); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define TAN_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, tan, case_name); \
    using namespace args; \
    auto result = nmtools::tan(__VA_ARGS__, nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("tan(case1)" * doctest::test_suite("array::tan"))
{
    TAN_SUBCASE( case1,   a);
    TAN_SUBCASE( case1, a_a);
    TAN_SUBCASE( case1, a_f);
    TAN_SUBCASE( case1, a_d);
    TAN_SUBCASE( case1, a_h);

    OBJECT_TAN_SUBCASE( case1,   a);
    OBJECT_TAN_SUBCASE( case1, a_a);
    OBJECT_TAN_SUBCASE( case1, a_f);
    OBJECT_TAN_SUBCASE( case1, a_d);
    OBJECT_TAN_SUBCASE( case1, a_h);
}