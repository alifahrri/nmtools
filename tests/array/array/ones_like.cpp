#include "nmtools/array/ones_like.hpp"
#include "nmtools/testing/data/array/ones_like.hpp"
#include "nmtools/testing/doctest.hpp"

#define ONES_LIKE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( array, ones_like, case_name ); \
    using namespace args; \
    auto result = nmtools::ones_like(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("ones_like(case1)" * doctest::test_suite("array::ones_like"))
{
    ONES_LIKE_SUBCASE( case1, a );
    ONES_LIKE_SUBCASE( case1, a_a );
    ONES_LIKE_SUBCASE( case1, a_f );
    ONES_LIKE_SUBCASE( case1, a_h );
    ONES_LIKE_SUBCASE( case1, a_d );
}

TEST_CASE("ones_like(case2)" * doctest::test_suite("array::ones_like"))
{
    ONES_LIKE_SUBCASE( case2, a );
    ONES_LIKE_SUBCASE( case2, a_a );
    ONES_LIKE_SUBCASE( case2, a_f );
    ONES_LIKE_SUBCASE( case2, a_h );
    ONES_LIKE_SUBCASE( case2, a_d );
}

TEST_CASE("ones_like(case3)" * doctest::test_suite("array::ones_like"))
{
    ONES_LIKE_SUBCASE( case3, a, dtype );
    ONES_LIKE_SUBCASE( case3, a_a, dtype );
    ONES_LIKE_SUBCASE( case3, a_f, dtype );
    ONES_LIKE_SUBCASE( case3, a_h, dtype );
    ONES_LIKE_SUBCASE( case3, a_d, dtype );
}