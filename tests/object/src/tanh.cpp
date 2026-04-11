#include "nmtools/array/ufuncs/tanh.hpp"
#include "nmtools/core/context/object.hpp"
#include "nmtools/testing/data/array/tanh.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;

#define OBJECT_TANH_SUBCASE(case_name, a, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, tanh, case_name); \
    using namespace args; \
    auto object = nmtools::array(a,nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(object) ); \
    auto result = object.tanh(__VA_ARGS__); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define TANH_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, tanh, case_name); \
    using namespace args; \
    auto result = nmtools::tanh(__VA_ARGS__, nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("tanh(case1)" * doctest::test_suite("array::tanh"))
{
    TANH_SUBCASE( case1,   a);
    TANH_SUBCASE( case1, a_a);
    TANH_SUBCASE( case1, a_f);
    TANH_SUBCASE( case1, a_d);
    TANH_SUBCASE( case1, a_h);

    OBJECT_TANH_SUBCASE( case1,   a);
    OBJECT_TANH_SUBCASE( case1, a_a);
    OBJECT_TANH_SUBCASE( case1, a_f);
    OBJECT_TANH_SUBCASE( case1, a_d);
    OBJECT_TANH_SUBCASE( case1, a_h);
}