#include "nmtools/core/cast.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/testing/data/array/cast.hpp"

#define CAST_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, cast, case_name); \
    using namespace args; \
    auto result = nmtools::view::cast(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::expected) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}

TEST_CASE("cast(case1)" * doctest::test_suite("view::cast"))
{
    CAST_SUBCASE( case1, array, dtype );
    CAST_SUBCASE( case1, array_a, dtype );
    CAST_SUBCASE( case1, array_f, dtype );
    CAST_SUBCASE( case1, array_h, dtype );
    CAST_SUBCASE( case1, array_d, dtype );
}

TEST_CASE("cast(case2)" * doctest::test_suite("view::cast"))
{
    CAST_SUBCASE( case2, array, dtype );
    CAST_SUBCASE( case2, array_a, dtype );
    CAST_SUBCASE( case2, array_f, dtype );
    CAST_SUBCASE( case2, array_h, dtype );
    CAST_SUBCASE( case2, array_d, dtype );
}