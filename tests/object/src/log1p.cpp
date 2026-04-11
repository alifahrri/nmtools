#include "nmtools/array/ufuncs/log1p.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/data/array/log1p.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;

#define OBJECT_LOG1P_SUBCASE(case_name, a, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, log1p, case_name); \
    using namespace args; \
    auto object = nm::array(a,nm::Object); \
    auto result = object.log1p(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define LOG1P_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, log1p, case_name); \
    using namespace args; \
    auto result = nm::log1p(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("log1p(case1)" * doctest::test_suite("array::log1p"))
{
    LOG1P_SUBCASE( case1,   a);
    LOG1P_SUBCASE( case1, a_a);
    LOG1P_SUBCASE( case1, a_f);
    LOG1P_SUBCASE( case1, a_d);
    LOG1P_SUBCASE( case1, a_h);

    OBJECT_LOG1P_SUBCASE( case1,   a);
    OBJECT_LOG1P_SUBCASE( case1, a_a);
    OBJECT_LOG1P_SUBCASE( case1, a_f);
    OBJECT_LOG1P_SUBCASE( case1, a_d);
    OBJECT_LOG1P_SUBCASE( case1, a_h);
}