#include "nmtools/array/ufuncs/log.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/data/array/log.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;

#define OBJECT_LOG_SUBCASE(case_name, a, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, log, case_name); \
    using namespace args; \
    auto object = nm::array(a,nm::Object); \
    auto result = object.log(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define LOG_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, log, case_name); \
    using namespace args; \
    auto result = nm::log(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("log(case1)" * doctest::test_suite("array::log"))
{
    LOG_SUBCASE( case1,   a);
    LOG_SUBCASE( case1, a_a);
    LOG_SUBCASE( case1, a_f);
    LOG_SUBCASE( case1, a_d);
    LOG_SUBCASE( case1, a_h);

    OBJECT_LOG_SUBCASE( case1,   a);
    OBJECT_LOG_SUBCASE( case1, a_a);
    OBJECT_LOG_SUBCASE( case1, a_f);
    OBJECT_LOG_SUBCASE( case1, a_d);
    OBJECT_LOG_SUBCASE( case1, a_h);
}