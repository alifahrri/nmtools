#include "nmtools/array/repeat.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/data/array/repeat.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;

#define OBJECT_REPEAT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, repeat, case_name); \
    using namespace args; \
    auto object = nmtools::array(__VA_ARGS__); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(object) ); \
    auto result = object.repeat(repeats, axis); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define REPEAT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, repeat, case_name); \
    using namespace args; \
    auto result = nmtools::repeat(__VA_ARGS__, repeats, axis, nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("repeat(case1)" * doctest::test_suite("array::repeat"))
{
    REPEAT_SUBCASE( case1,   array );
    REPEAT_SUBCASE( case1, array_a );
    REPEAT_SUBCASE( case1, array_f );
    REPEAT_SUBCASE( case1, array_h );
    REPEAT_SUBCASE( case1, array_d );

    OBJECT_REPEAT_SUBCASE( case1,   array, nmtools::Object );
    OBJECT_REPEAT_SUBCASE( case1, array_a, nmtools::Object );
    OBJECT_REPEAT_SUBCASE( case1, array_f, nmtools::Object );
    OBJECT_REPEAT_SUBCASE( case1, array_h, nmtools::Object );
    OBJECT_REPEAT_SUBCASE( case1, array_d, nmtools::Object );
}

TEST_CASE("repeat(case2)" * doctest::test_suite("array::repeat"))
{
    REPEAT_SUBCASE( case2,   array );
    REPEAT_SUBCASE( case2, array_a );
    REPEAT_SUBCASE( case2, array_f );
    REPEAT_SUBCASE( case2, array_h );
    REPEAT_SUBCASE( case2, array_d );

    OBJECT_REPEAT_SUBCASE( case2,   array, nmtools::Object );
    OBJECT_REPEAT_SUBCASE( case2, array_a, nmtools::Object );
    OBJECT_REPEAT_SUBCASE( case2, array_f, nmtools::Object );
    OBJECT_REPEAT_SUBCASE( case2, array_h, nmtools::Object );
    OBJECT_REPEAT_SUBCASE( case2, array_d, nmtools::Object );
}

TEST_CASE("repeat(case3)" * doctest::test_suite("array::repeat"))
{
    REPEAT_SUBCASE( case3,   array );
    REPEAT_SUBCASE( case3, array_a );
    REPEAT_SUBCASE( case3, array_f );
    REPEAT_SUBCASE( case3, array_h );
    REPEAT_SUBCASE( case3, array_d );

    OBJECT_REPEAT_SUBCASE( case3,   array, nmtools::Object );
    OBJECT_REPEAT_SUBCASE( case3, array_a, nmtools::Object );
    OBJECT_REPEAT_SUBCASE( case3, array_f, nmtools::Object );
    OBJECT_REPEAT_SUBCASE( case3, array_h, nmtools::Object );
    OBJECT_REPEAT_SUBCASE( case3, array_d, nmtools::Object );
}

TEST_CASE("repeat(case4)" * doctest::test_suite("array::repeat"))
{
    REPEAT_SUBCASE( case4,   array );
    REPEAT_SUBCASE( case4, array_a );
    REPEAT_SUBCASE( case4, array_f );
    REPEAT_SUBCASE( case4, array_h );
    REPEAT_SUBCASE( case4, array_d );

    OBJECT_REPEAT_SUBCASE( case4,   array, nmtools::Object );
    OBJECT_REPEAT_SUBCASE( case4, array_a, nmtools::Object );
    OBJECT_REPEAT_SUBCASE( case4, array_f, nmtools::Object );
    OBJECT_REPEAT_SUBCASE( case4, array_h, nmtools::Object );
    OBJECT_REPEAT_SUBCASE( case4, array_d, nmtools::Object );
}

TEST_CASE("repeat(case5)" * doctest::test_suite("array::repeat"))
{
    REPEAT_SUBCASE( case5,   array );
    REPEAT_SUBCASE( case5, array_a );
    REPEAT_SUBCASE( case5, array_f );
    REPEAT_SUBCASE( case5, array_h );
    REPEAT_SUBCASE( case5, array_d );

    OBJECT_REPEAT_SUBCASE( case5,   array, nmtools::Object );
    OBJECT_REPEAT_SUBCASE( case5, array_a, nmtools::Object );
    OBJECT_REPEAT_SUBCASE( case5, array_f, nmtools::Object );
    OBJECT_REPEAT_SUBCASE( case5, array_h, nmtools::Object );
    OBJECT_REPEAT_SUBCASE( case5, array_d, nmtools::Object );
}

TEST_CASE("repeat(case6)" * doctest::test_suite("array::repeat"))
{
    REPEAT_SUBCASE( case6,   array );
    REPEAT_SUBCASE( case6, array_a );
    REPEAT_SUBCASE( case6, array_f );
    REPEAT_SUBCASE( case6, array_h );
    REPEAT_SUBCASE( case6, array_d );

    OBJECT_REPEAT_SUBCASE( case6,   array, nmtools::Object );
    OBJECT_REPEAT_SUBCASE( case6, array_a, nmtools::Object );
    OBJECT_REPEAT_SUBCASE( case6, array_f, nmtools::Object );
    OBJECT_REPEAT_SUBCASE( case6, array_h, nmtools::Object );
    OBJECT_REPEAT_SUBCASE( case6, array_d, nmtools::Object );
}
