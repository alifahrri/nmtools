#include "nmtools/utl/algorithm.hpp"
#include "nmtools/testing/doctest.hpp"

NMTOOLS_TESTING_DECLARE_CASE(utl,insertion_sort)
{
    namespace utl = nmtools::utl;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        auto array = utl::array{5,2,9,1,5,6};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        auto expected = utl::array{1,2,5,5,6,9};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        auto array = utl::array{1,2,3,4,5};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        auto expected = utl::array{1,2,3,4,5};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        auto array = utl::array{5,4,3,2,1};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        auto expected = utl::array{1,2,3,4,5};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        auto array = utl::array{7,7,7,7};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        auto expected = utl::array{7,7,7,7};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        auto array = utl::array{3,-1,0,-5};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        auto expected = utl::array{-5,-1,0,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        auto array = utl::array{0.0f,0.5f,0.477f,1.0f};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        auto expected = utl::array{0.0f,0.477f,0.5f,1.0f};
    }
}

#define INSERTION_SORT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(utl,insertion_sort,case_name); \
    using namespace args; \
    auto result = nmtools::utl::insertion_sort(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::expected ); \
}

TEST_CASE("insertion_sort(case1)" * doctest::test_suite("utl"))
{
    INSERTION_SORT_SUBCASE( case1, array );
}

TEST_CASE("insertion_sort(case2)" * doctest::test_suite("utl"))
{
    INSERTION_SORT_SUBCASE( case2, array );
}

TEST_CASE("insertion_sort(case3)" * doctest::test_suite("utl"))
{
    INSERTION_SORT_SUBCASE( case3, array );
}

TEST_CASE("insertion_sort(case4)" * doctest::test_suite("utl"))
{
    INSERTION_SORT_SUBCASE( case4, array );
}

TEST_CASE("insertion_sort(case5)" * doctest::test_suite("utl"))
{
    INSERTION_SORT_SUBCASE( case5, array );
}

TEST_CASE("insertion_sort(case6)" * doctest::test_suite("utl"))
{
    INSERTION_SORT_SUBCASE( case6, array );
}