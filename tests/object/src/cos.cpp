#include "nmtools/array/ufuncs/cos.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/data/array/cos.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;

#undef NMTOOLS_TESTING_PRECISION
#define NMTOOLS_TESTING_PRECISION (1e-3)

#define OBJECT_COS_SUBCASE(case_name, a, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, cos, case_name); \
    using namespace args; \
    auto object = nmtools::array(a,nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(object) ); \
    auto result = object.cos(__VA_ARGS__); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define COS_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, cos, case_name); \
    using namespace args; \
    auto result = nmtools::cos(__VA_ARGS__, nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("cos(case1)" * doctest::test_suite("array::cos"))
{
    COS_SUBCASE( case1,   a);
    COS_SUBCASE( case1, a_a);
    COS_SUBCASE( case1, a_f);
    COS_SUBCASE( case1, a_d);
    COS_SUBCASE( case1, a_h);

    OBJECT_COS_SUBCASE( case1,   a);
    OBJECT_COS_SUBCASE( case1, a_a);
    OBJECT_COS_SUBCASE( case1, a_f);
    OBJECT_COS_SUBCASE( case1, a_d);
    OBJECT_COS_SUBCASE( case1, a_h);
}