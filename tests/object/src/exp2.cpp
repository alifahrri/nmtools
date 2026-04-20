#include "nmtools/array/ufuncs/exp2.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/data/array/exp2.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;

#define OBJECT_EXP2_SUBCASE(case_name, a, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, exp2, case_name); \
    using namespace args; \
    auto object = nm::array(a,nm::Object); \
    auto result = object.exp2(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}


#define EXP2_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, exp2, case_name); \
    using namespace args; \
    auto result = nm::exp2(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("exp2(case1)" * doctest::test_suite("array::exp2"))
{
    EXP2_SUBCASE( case1,   a);
    EXP2_SUBCASE( case1, a_a);
    EXP2_SUBCASE( case1, a_f);
    EXP2_SUBCASE( case1, a_d);
    EXP2_SUBCASE( case1, a_h);

    OBJECT_EXP2_SUBCASE( case1,   a);
    OBJECT_EXP2_SUBCASE( case1, a_a);
    OBJECT_EXP2_SUBCASE( case1, a_f);
    OBJECT_EXP2_SUBCASE( case1, a_d);
    OBJECT_EXP2_SUBCASE( case1, a_h);
}