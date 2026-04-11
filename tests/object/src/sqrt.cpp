#include "nmtools/array/ufuncs/sqrt.hpp"
#include "nmtools/core/context/object.hpp"
#include "nmtools/testing/data/array/sqrt.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;

#define OBJECT_SQRT_SUBCASE(case_name, a, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, sqrt, case_name); \
    using namespace args; \
    auto object = nm::array(a,nm::Object); \
    auto result = object.sqrt(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define SQRT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, sqrt, case_name); \
    using namespace args; \
    auto result = nmtools::sqrt(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("sqrt(case1)" * doctest::test_suite("array::sqrt"))
{
    SQRT_SUBCASE( case1,   a);
    SQRT_SUBCASE( case1, a_a);
    SQRT_SUBCASE( case1, a_f);
    SQRT_SUBCASE( case1, a_d);
    SQRT_SUBCASE( case1, a_h);

    OBJECT_SQRT_SUBCASE( case1,   a);
    OBJECT_SQRT_SUBCASE( case1, a_a);
    OBJECT_SQRT_SUBCASE( case1, a_f);
    OBJECT_SQRT_SUBCASE( case1, a_d);
    OBJECT_SQRT_SUBCASE( case1, a_h);
}