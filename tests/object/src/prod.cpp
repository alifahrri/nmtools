#include "nmtools/array/prod.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/data/array/multiply.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace array = nmtools;

#define OBJECT_PROD_SUBCASE(case_name, a, ...) \
SUBCASE(#case_name) \
{ \
    /* using test case from reduce_multiply since they're basically the same */ \
    NMTOOLS_TESTING_USE_CASE(view, reduce_multiply, case_name); \
    using namespace args; \
    auto object = nmtools::array(a,nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(object) ); \
    auto result = object.prod(__VA_ARGS__); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define PROD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    /* using test case from reduce_multiply since they're basically the same */ \
    NMTOOLS_TESTING_USE_CASE(view, reduce_multiply, case_name); \
    using namespace args; \
    auto result = nmtools::prod(__VA_ARGS__, nmtools::Object); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("prod(case1)" * doctest::test_suite("array::prod"))
{
    PROD_SUBCASE( case1,   a, axis );
    PROD_SUBCASE( case1, a_a, axis );
    PROD_SUBCASE( case1, a_f, axis );
    PROD_SUBCASE( case1, a_h, axis );

    // not yet supported,
    // cant figure out apply_slice for dynamic dim array yet
    // PROD_SUBCASE( case1, a_d, axis );

    OBJECT_PROD_SUBCASE( case1,   a, axis );
    OBJECT_PROD_SUBCASE( case1, a_a, axis );
    OBJECT_PROD_SUBCASE( case1, a_f, axis );
    OBJECT_PROD_SUBCASE( case1, a_h, axis );
}

// TEST_CASE("prod(case7)" * doctest::test_suite("array::prod"))
// {
//     PROD_SUBCASE( case7,   a, axis, dtype );
//     PROD_SUBCASE( case7, a_a, axis, dtype );
//     PROD_SUBCASE( case7, a_f, axis, dtype );
//     PROD_SUBCASE( case7, a_h, axis, dtype );

//     OBJECT_PROD_SUBCASE( case7,   a, axis, dtype );
//     OBJECT_PROD_SUBCASE( case7, a_a, axis, dtype );
//     OBJECT_PROD_SUBCASE( case7, a_f, axis, dtype );
//     OBJECT_PROD_SUBCASE( case7, a_h, axis, dtype );
// }

TEST_CASE("prod(case8)" * doctest::test_suite("array::prod"))
{
    PROD_SUBCASE( case8,   a, axis, dtype, initial );
    PROD_SUBCASE( case8, a_a, axis, dtype, initial );
    PROD_SUBCASE( case8, a_f, axis, dtype, initial );
    PROD_SUBCASE( case8, a_h, axis, dtype, initial );

    OBJECT_PROD_SUBCASE( case8,   a, axis, dtype, initial );
    OBJECT_PROD_SUBCASE( case8, a_a, axis, dtype, initial );
    OBJECT_PROD_SUBCASE( case8, a_f, axis, dtype, initial );
    OBJECT_PROD_SUBCASE( case8, a_h, axis, dtype, initial );
}

TEST_CASE("prod(case9)" * doctest::test_suite("array::prod"))
{
    PROD_SUBCASE( case9,   a, axis, dtype, initial, keepdims );
    PROD_SUBCASE( case9, a_a, axis, dtype, initial, keepdims );
    PROD_SUBCASE( case9, a_f, axis, dtype, initial, keepdims );
    PROD_SUBCASE( case9, a_h, axis, dtype, initial, keepdims );

    OBJECT_PROD_SUBCASE( case9,   a, axis, dtype, initial, keepdims );
    OBJECT_PROD_SUBCASE( case9, a_a, axis, dtype, initial, keepdims );
    OBJECT_PROD_SUBCASE( case9, a_f, axis, dtype, initial, keepdims );
    OBJECT_PROD_SUBCASE( case9, a_h, axis, dtype, initial, keepdims );
}