#include "nmtools/array/ufuncs/log2.hpp"
#include "nmtools/core/context/object.hpp"
#include "nmtools/testing/data/array/log2.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;

#define OBJECT_LOG2_SUBCASE(case_name, a, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, log2, case_name); \
    using namespace args; \
    auto object = nm::array(a,nm::Object); \
    auto result = object.log2(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define LOG2_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, log2, case_name); \
    using namespace args; \
    auto result = nm::log2(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("log2(case1)" * doctest::test_suite("array::log2"))
{
    LOG2_SUBCASE( case1,   a);
    LOG2_SUBCASE( case1, a_a);
    LOG2_SUBCASE( case1, a_f);
    LOG2_SUBCASE( case1, a_d);
    LOG2_SUBCASE( case1, a_h);

    OBJECT_LOG2_SUBCASE( case1,   a);
    OBJECT_LOG2_SUBCASE( case1, a_a);
    OBJECT_LOG2_SUBCASE( case1, a_f);
    OBJECT_LOG2_SUBCASE( case1, a_d);
    OBJECT_LOG2_SUBCASE( case1, a_h);
}