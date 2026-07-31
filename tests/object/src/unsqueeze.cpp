#include "nmtools/array/unsqueeze.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/data/array/unsqueeze.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;

#define OBJECT_UNSQUEEZE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(unsqueeze, case_name); \
    using namespace args; \
    auto object = nmtools::array(__VA_ARGS__); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(object) ); \
    auto result = object.unsqueeze(axis); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define UNSQUEEZE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(unsqueeze, case_name); \
    using namespace args; \
    auto result = nmtools::unsqueeze(__VA_ARGS__, axis, nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("unsqueeze(case1)" * doctest::test_suite("array::unsqueeze"))
{
    UNSQUEEZE_SUBCASE( case1,   array );
    UNSQUEEZE_SUBCASE( case1, array_a );
    UNSQUEEZE_SUBCASE( case1, array_f );
    UNSQUEEZE_SUBCASE( case1, array_h );
    UNSQUEEZE_SUBCASE( case1, array_d );

    OBJECT_UNSQUEEZE_SUBCASE( case1,   array, nmtools::Object );
    OBJECT_UNSQUEEZE_SUBCASE( case1, array_a, nmtools::Object );
    OBJECT_UNSQUEEZE_SUBCASE( case1, array_f, nmtools::Object );
    OBJECT_UNSQUEEZE_SUBCASE( case1, array_h, nmtools::Object );
    OBJECT_UNSQUEEZE_SUBCASE( case1, array_d, nmtools::Object );
}

TEST_CASE("unsqueeze(case2)" * doctest::test_suite("array::unsqueeze"))
{
    UNSQUEEZE_SUBCASE( case2,   array );
    UNSQUEEZE_SUBCASE( case2, array_a );
    UNSQUEEZE_SUBCASE( case2, array_f );
    UNSQUEEZE_SUBCASE( case2, array_h );
    UNSQUEEZE_SUBCASE( case2, array_d );

    OBJECT_UNSQUEEZE_SUBCASE( case2,   array, nmtools::Object );
    OBJECT_UNSQUEEZE_SUBCASE( case2, array_a, nmtools::Object );
    OBJECT_UNSQUEEZE_SUBCASE( case2, array_f, nmtools::Object );
    OBJECT_UNSQUEEZE_SUBCASE( case2, array_h, nmtools::Object );
    OBJECT_UNSQUEEZE_SUBCASE( case2, array_d, nmtools::Object );
}

TEST_CASE("unsqueeze(case3)" * doctest::test_suite("array::unsqueeze"))
{
    UNSQUEEZE_SUBCASE( case3,   array );
    UNSQUEEZE_SUBCASE( case3, array_a );
    UNSQUEEZE_SUBCASE( case3, array_f );
    UNSQUEEZE_SUBCASE( case3, array_h );
    UNSQUEEZE_SUBCASE( case3, array_d );

    OBJECT_UNSQUEEZE_SUBCASE( case3,   array, nmtools::Object );
    OBJECT_UNSQUEEZE_SUBCASE( case3, array_a, nmtools::Object );
    OBJECT_UNSQUEEZE_SUBCASE( case3, array_f, nmtools::Object );
    OBJECT_UNSQUEEZE_SUBCASE( case3, array_h, nmtools::Object );
    OBJECT_UNSQUEEZE_SUBCASE( case3, array_d, nmtools::Object );
}

TEST_CASE("unsqueeze(case4)" * doctest::test_suite("array::unsqueeze"))
{
    UNSQUEEZE_SUBCASE( case4,   array );
    UNSQUEEZE_SUBCASE( case4, array_a );
    UNSQUEEZE_SUBCASE( case4, array_f );
    UNSQUEEZE_SUBCASE( case4, array_h );
    UNSQUEEZE_SUBCASE( case4, array_d );

    OBJECT_UNSQUEEZE_SUBCASE( case4,   array, nmtools::Object );
    OBJECT_UNSQUEEZE_SUBCASE( case4, array_a, nmtools::Object );
    OBJECT_UNSQUEEZE_SUBCASE( case4, array_f, nmtools::Object );
    OBJECT_UNSQUEEZE_SUBCASE( case4, array_h, nmtools::Object );
    OBJECT_UNSQUEEZE_SUBCASE( case4, array_d, nmtools::Object );
}

TEST_CASE("unsqueeze(case5)" * doctest::test_suite("array::unsqueeze"))
{
    UNSQUEEZE_SUBCASE( case5,   array );
    UNSQUEEZE_SUBCASE( case5, array_a );
    UNSQUEEZE_SUBCASE( case5, array_f );
    UNSQUEEZE_SUBCASE( case5, array_h );
    UNSQUEEZE_SUBCASE( case5, array_d );

    OBJECT_UNSQUEEZE_SUBCASE( case5,   array, nmtools::Object );
    OBJECT_UNSQUEEZE_SUBCASE( case5, array_a, nmtools::Object );
    OBJECT_UNSQUEEZE_SUBCASE( case5, array_f, nmtools::Object );
    OBJECT_UNSQUEEZE_SUBCASE( case5, array_h, nmtools::Object );
    OBJECT_UNSQUEEZE_SUBCASE( case5, array_d, nmtools::Object );
}

TEST_CASE("unsqueeze(case6)" * doctest::test_suite("array::unsqueeze"))
{
    UNSQUEEZE_SUBCASE( case6,   array );
    UNSQUEEZE_SUBCASE( case6, array_a );
    UNSQUEEZE_SUBCASE( case6, array_f );
    UNSQUEEZE_SUBCASE( case6, array_h );
    UNSQUEEZE_SUBCASE( case6, array_d );

    OBJECT_UNSQUEEZE_SUBCASE( case6,   array, nmtools::Object );
    OBJECT_UNSQUEEZE_SUBCASE( case6, array_a, nmtools::Object );
    OBJECT_UNSQUEEZE_SUBCASE( case6, array_f, nmtools::Object );
    OBJECT_UNSQUEEZE_SUBCASE( case6, array_h, nmtools::Object );
    OBJECT_UNSQUEEZE_SUBCASE( case6, array_d, nmtools::Object );
}

TEST_CASE("unsqueeze(case7)" * doctest::test_suite("array::unsqueeze"))
{
    UNSQUEEZE_SUBCASE( case7,   array );
    UNSQUEEZE_SUBCASE( case7, array_a );
    UNSQUEEZE_SUBCASE( case7, array_f );
    UNSQUEEZE_SUBCASE( case7, array_h );
    UNSQUEEZE_SUBCASE( case7, array_d );

    OBJECT_UNSQUEEZE_SUBCASE( case7,   array, nmtools::Object );
    OBJECT_UNSQUEEZE_SUBCASE( case7, array_a, nmtools::Object );
    OBJECT_UNSQUEEZE_SUBCASE( case7, array_f, nmtools::Object );
    OBJECT_UNSQUEEZE_SUBCASE( case7, array_h, nmtools::Object );
    OBJECT_UNSQUEEZE_SUBCASE( case7, array_d, nmtools::Object );
}

TEST_CASE("unsqueeze(case8)" * doctest::test_suite("array::unsqueeze"))
{
    UNSQUEEZE_SUBCASE( case8,   array );
    UNSQUEEZE_SUBCASE( case8, array_a );
    UNSQUEEZE_SUBCASE( case8, array_f );
    UNSQUEEZE_SUBCASE( case8, array_h );
    UNSQUEEZE_SUBCASE( case8, array_d );

    OBJECT_UNSQUEEZE_SUBCASE( case8,   array, nmtools::Object );
    OBJECT_UNSQUEEZE_SUBCASE( case8, array_a, nmtools::Object );
    OBJECT_UNSQUEEZE_SUBCASE( case8, array_f, nmtools::Object );
    OBJECT_UNSQUEEZE_SUBCASE( case8, array_h, nmtools::Object );
    OBJECT_UNSQUEEZE_SUBCASE( case8, array_d, nmtools::Object );
}

TEST_CASE("unsqueeze(case9)" * doctest::test_suite("array::unsqueeze"))
{
    UNSQUEEZE_SUBCASE( case9,   array );
    UNSQUEEZE_SUBCASE( case9, array_a );
    UNSQUEEZE_SUBCASE( case9, array_f );
    UNSQUEEZE_SUBCASE( case9, array_h );
    UNSQUEEZE_SUBCASE( case9, array_d );

    OBJECT_UNSQUEEZE_SUBCASE( case9,   array, nmtools::Object );
    OBJECT_UNSQUEEZE_SUBCASE( case9, array_a, nmtools::Object );
    OBJECT_UNSQUEEZE_SUBCASE( case9, array_f, nmtools::Object );
    OBJECT_UNSQUEEZE_SUBCASE( case9, array_h, nmtools::Object );
    OBJECT_UNSQUEEZE_SUBCASE( case9, array_d, nmtools::Object );
}
