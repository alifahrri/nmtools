#include "nmtools/array/ufuncs/cosh.hpp"
#include "nmtools/core/context/object.hpp"
#include "nmtools/testing/data/array/cosh.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;

#define OBJECT_COSH_SUBCASE(case_name, a, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, cosh, case_name); \
    using namespace args; \
    auto object = nmtools::array(a,nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(object) ); \
    auto result = object.cosh(__VA_ARGS__); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define COSH_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, cosh, case_name); \
    using namespace args; \
    auto result = nmtools::cosh(__VA_ARGS__, nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("cosh(case1)" * doctest::test_suite("array::cosh"))
{
    COSH_SUBCASE( case1,   a);
    COSH_SUBCASE( case1, a_a);
    COSH_SUBCASE( case1, a_f);
    COSH_SUBCASE( case1, a_d);
    COSH_SUBCASE( case1, a_h);

    OBJECT_COSH_SUBCASE( case1,   a);
    OBJECT_COSH_SUBCASE( case1, a_a);
    OBJECT_COSH_SUBCASE( case1, a_f);
    OBJECT_COSH_SUBCASE( case1, a_d);
    OBJECT_COSH_SUBCASE( case1, a_h);
}