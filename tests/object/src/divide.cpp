#include "nmtools/array/ufuncs/divide.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/data/array/divide.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nmtools;
namespace view = nm::view;

#define OBJECT_DIVIDE_SUBCASE(case_name, lhs, rhs) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, divide, case_name); \
    using namespace args; \
    auto object = nmtools::array(lhs); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(object) ); \
    auto result = object / rhs; \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define DIVIDE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, divide, case_name); \
    using namespace args; \
    auto result = nmtools::divide(__VA_ARGS__, nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("divide(case1)" * doctest::test_suite("array::divide"))
{
    DIVIDE_SUBCASE( case1,   a,   b );
    DIVIDE_SUBCASE( case1, a_a, b_a );
    DIVIDE_SUBCASE( case1, a_f, b_f );
    DIVIDE_SUBCASE( case1, a_d, b_d );
    DIVIDE_SUBCASE( case1, a_h, b_h );

    OBJECT_DIVIDE_SUBCASE( case1,   a,   b );
    OBJECT_DIVIDE_SUBCASE( case1, a_a, b_a );
    OBJECT_DIVIDE_SUBCASE( case1, a_f, b_f );
    OBJECT_DIVIDE_SUBCASE( case1, a_d, b_d );
    OBJECT_DIVIDE_SUBCASE( case1, a_h, b_h );
}

TEST_CASE("divide(case2)" * doctest::test_suite("array::divide"))
{
    DIVIDE_SUBCASE( case2,   a, b );
    DIVIDE_SUBCASE( case2, a_a, b );
    DIVIDE_SUBCASE( case2, a_f, b );
    DIVIDE_SUBCASE( case2, a_d, b );
    DIVIDE_SUBCASE( case2, a_h, b );

    OBJECT_DIVIDE_SUBCASE( case2,   a, b );
    OBJECT_DIVIDE_SUBCASE( case2, a_a, b );
    OBJECT_DIVIDE_SUBCASE( case2, a_f, b );
    OBJECT_DIVIDE_SUBCASE( case2, a_d, b );
    OBJECT_DIVIDE_SUBCASE( case2, a_h, b );
}