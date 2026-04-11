#include "nmtools/array/sum.hpp"
#include "nmtools/core/context/object.hpp"
#include "nmtools/testing/data/array/add.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace array = nmtools;

#define OBJECT_SUM_SUBCASE(case_name, a, ...) \
SUBCASE(#case_name) \
{ \
    /* using test case from reduce_add since they're basically the same */ \
    NMTOOLS_TESTING_USE_CASE(view, reduce_add, case_name); \
    using namespace args; \
    auto object = nmtools::array(a,nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(object) ); \
    auto result = object.sum(__VA_ARGS__); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define SUM_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    /* using test case from reduce_add since they're basically the same */ \
    NMTOOLS_TESTING_USE_CASE(view, reduce_add, case_name); \
    using namespace args; \
    auto result = nmtools::sum(__VA_ARGS__, nmtools::Object); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("sum(case1)" * doctest::test_suite("array::sum"))
{
    SUM_SUBCASE( case1,   a, axis );
    SUM_SUBCASE( case1, a_a, axis );
    SUM_SUBCASE( case1, a_f, axis );
    SUM_SUBCASE( case1, a_h, axis );

    // not yet supported,
    // cant figure out apply_slice for dynamic dim array yet
    // SUM_SUBCASE( case1, a_d, axis );

    OBJECT_SUM_SUBCASE( case1,   a, axis );
    OBJECT_SUM_SUBCASE( case1, a_a, axis );
    OBJECT_SUM_SUBCASE( case1, a_f, axis );
    OBJECT_SUM_SUBCASE( case1, a_h, axis );
}

TEST_CASE("sum(case7)" * doctest::test_suite("array::sum"))
{
    SUM_SUBCASE( case7,   a, axis, dtype );
    SUM_SUBCASE( case7, a_a, axis, dtype );
    SUM_SUBCASE( case7, a_f, axis, dtype );
    SUM_SUBCASE( case7, a_h, axis, dtype );

    OBJECT_SUM_SUBCASE( case7,   a, axis, dtype );
    OBJECT_SUM_SUBCASE( case7, a_a, axis, dtype );
    OBJECT_SUM_SUBCASE( case7, a_f, axis, dtype );
    OBJECT_SUM_SUBCASE( case7, a_h, axis, dtype );
}

TEST_CASE("sum(case8)" * doctest::test_suite("array::sum"))
{
    SUM_SUBCASE( case8,   a, axis, dtype, initial );
    SUM_SUBCASE( case8, a_a, axis, dtype, initial );
    SUM_SUBCASE( case8, a_f, axis, dtype, initial );
    SUM_SUBCASE( case8, a_h, axis, dtype, initial );

    OBJECT_SUM_SUBCASE( case8,   a, axis, dtype, initial );
    OBJECT_SUM_SUBCASE( case8, a_a, axis, dtype, initial );
    OBJECT_SUM_SUBCASE( case8, a_f, axis, dtype, initial );
    OBJECT_SUM_SUBCASE( case8, a_h, axis, dtype, initial );
}

TEST_CASE("sum(case9)" * doctest::test_suite("array::sum"))
{
    SUM_SUBCASE( case9,   a, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case9, a_a, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case9, a_f, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case9, a_h, axis, dtype, initial, keepdims );

    OBJECT_SUM_SUBCASE( case9,   a, axis, dtype, initial, keepdims );
    OBJECT_SUM_SUBCASE( case9, a_a, axis, dtype, initial, keepdims );
    OBJECT_SUM_SUBCASE( case9, a_f, axis, dtype, initial, keepdims );
    OBJECT_SUM_SUBCASE( case9, a_h, axis, dtype, initial, keepdims );
}