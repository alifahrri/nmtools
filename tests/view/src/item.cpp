#include "nmtools/array/item.hpp"
#include "nmtools/testing/data/array/item.hpp"
#include "nmtools/testing/doctest.hpp"

#define ITEM_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( array, item, case_name ); \
    using namespace args; \
    auto result = nmtools::view::item( __VA_ARGS__ ); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("item(case1)" * doctest::test_suite("view::item"))
{
    SUBCASE("meta")
    {
        NMTOOLS_TESTING_USE_CASE( array, item, case1 );
        {
            auto result = nmtools::view::item( a );
            using result_t = decltype(result);
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, result_t );
        }
    }
    ITEM_SUBCASE( case1, a );
    ITEM_SUBCASE( case1, a_a );
    ITEM_SUBCASE( case1, a_f );
    ITEM_SUBCASE( case1, a_h );
    ITEM_SUBCASE( case1, a_d );
}

TEST_CASE("item(case1b)" * doctest::test_suite("view::item"))
{
    ITEM_SUBCASE( case1b, a );
    ITEM_SUBCASE( case1b, a_a );
    ITEM_SUBCASE( case1b, a_f );
    ITEM_SUBCASE( case1b, a_h );
    ITEM_SUBCASE( case1b, a_d );
}

TEST_CASE("item(case1c)" * doctest::test_suite("view::item"))
{
    ITEM_SUBCASE( case1c, a );
}

TEST_CASE("item(case1d)" * doctest::test_suite("view::item"))
{
    ITEM_SUBCASE( case1d, a_e1 );
    ITEM_SUBCASE( case1d, a_e2 );
}

TEST_CASE("item(case2)" * doctest::test_suite("view::item"))
{
    ITEM_SUBCASE( case2, a, idx );
    ITEM_SUBCASE( case2, a_a, idx );
    ITEM_SUBCASE( case2, a_f, idx );
    ITEM_SUBCASE( case2, a_h, idx );
    ITEM_SUBCASE( case2, a_d, idx );

    ITEM_SUBCASE( case2, a, idx_ct );
}

TEST_CASE("item(case2b)" * doctest::test_suite("view::item"))
{
    ITEM_SUBCASE( case2b, a, idx );
    ITEM_SUBCASE( case2b, a_a, idx );
    ITEM_SUBCASE( case2b, a_f, idx );
    ITEM_SUBCASE( case2b, a_h, idx );
    ITEM_SUBCASE( case2b, a_d, idx );

    // ITEM_SUBCASE( case2b, a, idx_ct );
}

TEST_CASE("item(case3)" * doctest::test_suite("view::item"))
{
    ITEM_SUBCASE( case3, a, idx );
    ITEM_SUBCASE( case3, a_a, idx );
    ITEM_SUBCASE( case3, a_f, idx );
    ITEM_SUBCASE( case3, a_h, idx );
    ITEM_SUBCASE( case3, a_d, idx );
}

TEST_CASE("item(case4)" * doctest::test_suite("view::item"))
{
    ITEM_SUBCASE( case4, a, idx );
    ITEM_SUBCASE( case4, a_a, idx_a );
    // ITEM_SUBCASE( case4, a_f, idx_f );
    // ITEM_SUBCASE( case4, a_h, idx_h );
    ITEM_SUBCASE( case4, a_f, idx );
    ITEM_SUBCASE( case4, a_h, idx );
    ITEM_SUBCASE( case4, a_d, idx_v );
}

TEST_CASE("item(case4b)" * doctest::test_suite("view::item"))
{
    // ITEM_SUBCASE( case4b, a, idx );
    // ITEM_SUBCASE( case4b, a_a, idx_a );
    // ITEM_SUBCASE( case4b, a_f, idx_f );
    // ITEM_SUBCASE( case4b, a_h, idx_h );
    // ITEM_SUBCASE( case4b, a_f, idx );
    // ITEM_SUBCASE( case4b, a_h, idx );

    ITEM_SUBCASE( case4b, a_d, idx_v );
}

TEST_CASE("item(case5)" * doctest::test_suite("view::item"))
{
    ITEM_SUBCASE( case5, a, idx );
    ITEM_SUBCASE( case5, a_a, idx_a );
    // ITEM_SUBCASE( case5, a_f, idx_f );
    // ITEM_SUBCASE( case5, a_h, idx_h );
    ITEM_SUBCASE( case5, a_f, idx );
    ITEM_SUBCASE( case5, a_h, idx );
    ITEM_SUBCASE( case5, a_d, idx_v );
}

#ifndef NMTOOLS_TESTING_MINIMIZE_FOOTPRINT
TEST_CASE("item(case6)" * doctest::test_suite("view::item"))
{
    ITEM_SUBCASE( case6, a, idx );
    ITEM_SUBCASE( case6, a_a, idx_a );
    // ITEM_SUBCASE( case6, a_f, idx_f );
    // ITEM_SUBCASE( case6, a_h, idx_h );
    ITEM_SUBCASE( case6, a_f, idx );
    ITEM_SUBCASE( case6, a_h, idx );
    ITEM_SUBCASE( case6, a_d, idx_v );
}

TEST_CASE("item(case7)" * doctest::test_suite("view::item"))
{
    ITEM_SUBCASE( case7, a, idx );
    ITEM_SUBCASE( case7, a_a, idx_a );
    // ITEM_SUBCASE( case7, a_f, idx_f );
    // ITEM_SUBCASE( case7, a_h, idx_h );
    ITEM_SUBCASE( case7, a_f, idx );
    ITEM_SUBCASE( case7, a_h, idx );
    ITEM_SUBCASE( case7, a_d, idx_v );
}

TEST_CASE("item(case8)" * doctest::test_suite("view::item"))
{
    ITEM_SUBCASE( case8, a, idx );
    ITEM_SUBCASE( case8, a_a, idx );
    ITEM_SUBCASE( case8, a_f, idx );
    ITEM_SUBCASE( case8, a_h, idx );
    ITEM_SUBCASE( case8, a_d, idx );
}
#endif // NMTOOLS_TESTING_MINIMIZE_FOOTPRINT
