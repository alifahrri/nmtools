#include "nmtools/array/view/linspace.hpp"
#include "nmtools/testing/data/array/linspace.hpp"
#include "nmtools/utility/apply_isclose.hpp"
#include "nmtools/testing/doctest.hpp"

#define LINSPACE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( array, linspace, case_name ); \
    using namespace args; \
    auto result = nmtools::view::linspace( __VA_ARGS__ ); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define APPLY_LINSPACE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( array, linspace, case_name ); \
    using namespace args; \
    auto result = nmtools::view::linspace( __VA_ARGS__ ); \
    NMTOOLS_ASSERT_APPLY_CLOSE( result, expect::result ); \
}


TEST_CASE("linspace(case1)" * doctest::test_suite("view::linspace"))
{
    LINSPACE_SUBCASE( case1, start, stop, num );
    LINSPACE_SUBCASE( case1, start, stop, num_ct );
}

TEST_CASE("linspace(case2)" * doctest::test_suite("view::linspace"))
{
    LINSPACE_SUBCASE( case2, start, stop, num, endpoint );
    LINSPACE_SUBCASE( case2, start, stop, num_ct, endpoint );
}

TEST_CASE("linspace(case3)" * doctest::test_suite("view::linspace"))
{
    APPLY_LINSPACE_SUBCASE( case3, start, stop, num, endpoint, retstep );
    APPLY_LINSPACE_SUBCASE( case3, start, stop, num_ct, endpoint, retstep );
}

TEST_CASE("linspace(case4)" * doctest::test_suite("view::linspace"))
{
    LINSPACE_SUBCASE( case4, start, stop, num );
    LINSPACE_SUBCASE( case4, start, stop, num_ct );
}

TEST_CASE("linspace(case5)" * doctest::test_suite("view::linspace"))
{
    LINSPACE_SUBCASE( case5, start, stop, num, endpoint );
    LINSPACE_SUBCASE( case5, start, stop, num_ct, endpoint );
}

TEST_CASE("linspace(case6)" * doctest::test_suite("view::linspace"))
{
    LINSPACE_SUBCASE( case6, start, stop, num );
    LINSPACE_SUBCASE( case6, start, stop, num_ct );
}

TEST_CASE("linspace(case7)" * doctest::test_suite("view::linspace"))
{
    LINSPACE_SUBCASE( case7, start, stop, num, endpoint );
    LINSPACE_SUBCASE( case7, start, stop, num_ct, endpoint );
}