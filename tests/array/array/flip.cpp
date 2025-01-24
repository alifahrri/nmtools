#include "nmtools/array/flip.hpp"
#include "nmtools/testing/data/array/flip.hpp"
#include "nmtools/testing/data/array/fliplr.hpp"
#include "nmtools/testing/data/array/flipud.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;

#define FLIP_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(flip, case_name); \
    using namespace args; \
    auto result = nmtools::array::flip(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

#define FLIPLR_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(fliplr, case_name); \
    using namespace args; \
    auto result = nmtools::array::fliplr(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

#define FLIPUD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(flipud, case_name); \
    using namespace args; \
    auto result = nmtools::array::flipud(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("flip(case1)" * doctest::test_suite("array::flip"))
{
    FLIP_SUBCASE(case1,   array, axis );
    FLIP_SUBCASE(case1, array_a, axis );
    FLIP_SUBCASE(case1, array_f, axis );
    FLIP_SUBCASE(case1, array_h, axis );
    // FLIP_SUBCASE(case1, array_d, axis );
}

TEST_CASE("flip(case2)" * doctest::test_suite("array::flip"))
{
    FLIP_SUBCASE(case2,   array, axis );
    FLIP_SUBCASE(case2, array_a, axis );
    FLIP_SUBCASE(case2, array_f, axis );
    FLIP_SUBCASE(case2, array_h, axis );
    // FLIP_SUBCASE(case2, array_d, axis );
}

TEST_CASE("flip(case3)" * doctest::test_suite("array::flip"))
{
    FLIP_SUBCASE(case3,   array, axis );
    FLIP_SUBCASE(case3, array_a, axis );
    FLIP_SUBCASE(case3, array_f, axis );
    FLIP_SUBCASE(case3, array_h, axis );
    // FLIP_SUBCASE(case3, array_d, axis );
}

TEST_CASE("flip(case4)" * doctest::test_suite("array::flip"))
{
    FLIP_SUBCASE(case4,   array,   axis );
    FLIP_SUBCASE(case4, array_a, axis_a );
    FLIP_SUBCASE(case4, array_f, axis_f );
    FLIP_SUBCASE(case4, array_h, axis_h );
    // FLIP_SUBCASE(case4, array_d, axis_d );
}

TEST_CASE("fliplr(case1)" * doctest::test_suite("array::fliplr"))
{
    FLIPLR_SUBCASE(case1,   array );
    FLIPLR_SUBCASE(case1, array_a );
    FLIPLR_SUBCASE(case1, array_f );
    FLIPLR_SUBCASE(case1, array_h );
    // FLIPLR_SUBCASE(case1, array_d );
}

TEST_CASE("fliplr(case2)" * doctest::test_suite("array::fliplr"))
{
    FLIPLR_SUBCASE(case2,   array );
    FLIPLR_SUBCASE(case2, array_a );
    FLIPLR_SUBCASE(case2, array_f );
    FLIPLR_SUBCASE(case2, array_h );
    // FLIPLR_SUBCASE(case2, array_d );
}

TEST_CASE("fliplr(case3)" * doctest::test_suite("array::fliplr"))
{
    FLIPLR_SUBCASE(case3,   array );
    FLIPLR_SUBCASE(case3, array_a );
    FLIPLR_SUBCASE(case3, array_f );
    FLIPLR_SUBCASE(case3, array_h );
    // FLIPLR_SUBCASE(case3, array_d );
}

TEST_CASE("flipud(case1)" * doctest::test_suite("array::flipud"))
{
    FLIPUD_SUBCASE(case1,   array );
    FLIPUD_SUBCASE(case1, array_a );
    FLIPUD_SUBCASE(case1, array_f );
    FLIPUD_SUBCASE(case1, array_h );
    // FLIPUD_SUBCASE(case1, array_d );
}

TEST_CASE("flipud(case2)" * doctest::test_suite("array::flipud"))
{
    FLIPUD_SUBCASE(case2,   array );
    FLIPUD_SUBCASE(case2, array_a );
    FLIPUD_SUBCASE(case2, array_f );
    FLIPUD_SUBCASE(case2, array_h );
    // FLIPUD_SUBCASE(case2, array_d );
}

TEST_CASE("flipud(case3)" * doctest::test_suite("array::flipud"))
{
    FLIPUD_SUBCASE(case3,   array );
    FLIPUD_SUBCASE(case3, array_a );
    FLIPUD_SUBCASE(case3, array_f );
    FLIPUD_SUBCASE(case3, array_h );
    // FLIPUD_SUBCASE(case3, array_d );
}