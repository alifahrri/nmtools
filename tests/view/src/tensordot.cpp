#include "nmtools/array/view/tensordot.hpp"
#include "nmtools/testing/data/array/tensordot.hpp"
#include "nmtools/testing/doctest.hpp"

#define TENSORDOT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array,tensordot,case_name); \
    auto result = nmtools::view::tensordot(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("tensordot(case1a)" * doctest::test_suite("view::tensordot"))
{
    // TODO: fix
    // TENSORDOT_SUBCASE( case1a, a, b, axes );
    TENSORDOT_SUBCASE( case1a, a, b, axes_ct );
    TENSORDOT_SUBCASE( case1a, a_a, b_a, axes_ct );
    TENSORDOT_SUBCASE( case1a, a_f, b_f, axes_ct );
    TENSORDOT_SUBCASE( case1a, a_h, b_h, axes_ct );
    // TENSORDOT_SUBCASE( case1a, a_d, b_d, axes_ct );
}

TEST_CASE("tensordot(case2a)" * doctest::test_suite("view::tensordot"))
{
    TENSORDOT_SUBCASE( case2a, a, b );
    TENSORDOT_SUBCASE( case2a, a_a, b_a );
    TENSORDOT_SUBCASE( case2a, a_f, b_f );
    TENSORDOT_SUBCASE( case2a, a_h, b_h );
    // TODO: fix
    // TENSORDOT_SUBCASE( case2a, a_d, b_d );
}

TEST_CASE("tensordot(case2b)" * doctest::test_suite("view::tensordot"))
{
    TENSORDOT_SUBCASE( case2b, a, b );
    TENSORDOT_SUBCASE( case2b, a_a, b_a );
    TENSORDOT_SUBCASE( case2b, a_f, b_f );
    TENSORDOT_SUBCASE( case2b, a_h, b_h );
    TENSORDOT_SUBCASE( case2b, a_d, b_d );
}

TEST_CASE("tensordot(case2c)" * doctest::test_suite("view::tensordot"))
{
    TENSORDOT_SUBCASE( case2c, a, b );
    TENSORDOT_SUBCASE( case2c, a_a, b_a );
    TENSORDOT_SUBCASE( case2c, a_f, b_f );
    TENSORDOT_SUBCASE( case2c, a_h, b_h );
    TENSORDOT_SUBCASE( case2c, a_d, b_d );
}

TEST_CASE("tensordot(case2d)" * doctest::test_suite("view::tensordot"))
{
    TENSORDOT_SUBCASE( case2d, a, b );
    TENSORDOT_SUBCASE( case2d, a_a, b_a );
    TENSORDOT_SUBCASE( case2d, a_f, b_f );
    TENSORDOT_SUBCASE( case2d, a_h, b_h );
    TENSORDOT_SUBCASE( case2d, a_d, b_d );
}

TEST_CASE("tensordot(case2e)" * doctest::test_suite("view::tensordot"))
{
    TENSORDOT_SUBCASE( case2e, a, b, axes );
    TENSORDOT_SUBCASE( case2e, a_a, b_a, axes );
    TENSORDOT_SUBCASE( case2e, a_f, b_f, axes );
    TENSORDOT_SUBCASE( case2e, a_h, b_h, axes );
    TENSORDOT_SUBCASE( case2e, a_d, b_d, axes );

    TENSORDOT_SUBCASE( case2e, a, b, axes_ct );
    TENSORDOT_SUBCASE( case2e, a_a, b_a, axes_ct );
    TENSORDOT_SUBCASE( case2e, a_f, b_f, axes_ct );
    TENSORDOT_SUBCASE( case2e, a_h, b_h, axes_ct );
    TENSORDOT_SUBCASE( case2e, a_d, b_d, axes_ct );
}

TEST_CASE("tensordot(case2f)" * doctest::test_suite("view::tensordot"))
{
    TENSORDOT_SUBCASE( case2f, a, b, axes );
    TENSORDOT_SUBCASE( case2f, a_a, b_a, axes );
    TENSORDOT_SUBCASE( case2f, a_f, b_f, axes );
    TENSORDOT_SUBCASE( case2f, a_h, b_h, axes );
    TENSORDOT_SUBCASE( case2f, a_d, b_d, axes );

    TENSORDOT_SUBCASE( case2f, a, b, axes_ct );
    TENSORDOT_SUBCASE( case2f, a_a, b_a, axes_ct );
    TENSORDOT_SUBCASE( case2f, a_f, b_f, axes_ct );
    TENSORDOT_SUBCASE( case2f, a_h, b_h, axes_ct );
    TENSORDOT_SUBCASE( case2f, a_d, b_d, axes_ct );
}

TEST_CASE("tensordot(case2f)" * doctest::test_suite("view::tensordot"))
{
    TENSORDOT_SUBCASE( case2f, a, b, axes );
    TENSORDOT_SUBCASE( case2f, a_a, b_a, axes );
    TENSORDOT_SUBCASE( case2f, a_f, b_f, axes );
    TENSORDOT_SUBCASE( case2f, a_h, b_h, axes );
    TENSORDOT_SUBCASE( case2f, a_d, b_d, axes );

    TENSORDOT_SUBCASE( case2f, a, b, axes_ct );
    TENSORDOT_SUBCASE( case2f, a_a, b_a, axes_ct );
    TENSORDOT_SUBCASE( case2f, a_f, b_f, axes_ct );
    TENSORDOT_SUBCASE( case2f, a_h, b_h, axes_ct );
    TENSORDOT_SUBCASE( case2f, a_d, b_d, axes_ct );
}

TEST_CASE("tensordot(case2g)" * doctest::test_suite("view::tensordot"))
{
    TENSORDOT_SUBCASE( case2g, a, b, axes );
    TENSORDOT_SUBCASE( case2g, a_a, b_a, axes );
    TENSORDOT_SUBCASE( case2g, a_f, b_f, axes );
    TENSORDOT_SUBCASE( case2g, a_h, b_h, axes );
    TENSORDOT_SUBCASE( case2g, a_d, b_d, axes );

    TENSORDOT_SUBCASE( case2g, a, b, axes_ct );
    TENSORDOT_SUBCASE( case2g, a_a, b_a, axes_ct );
    TENSORDOT_SUBCASE( case2g, a_f, b_f, axes_ct );
    TENSORDOT_SUBCASE( case2g, a_h, b_h, axes_ct );
    TENSORDOT_SUBCASE( case2g, a_d, b_d, axes_ct );

}

TEST_CASE("tensordot(case2h)" * doctest::test_suite("view::tensordot"))
{
    TENSORDOT_SUBCASE( case2h, a, b, axes );
    TENSORDOT_SUBCASE( case2h, a_a, b_a, axes );
    TENSORDOT_SUBCASE( case2h, a_f, b_f, axes );
    TENSORDOT_SUBCASE( case2h, a_h, b_h, axes );
    TENSORDOT_SUBCASE( case2h, a_d, b_d, axes );

    TENSORDOT_SUBCASE( case2h, a, b, axes_ct );
    TENSORDOT_SUBCASE( case2h, a_a, b_a, axes_ct );
    TENSORDOT_SUBCASE( case2h, a_f, b_f, axes_ct );
    TENSORDOT_SUBCASE( case2h, a_h, b_h, axes_ct );
    TENSORDOT_SUBCASE( case2h, a_d, b_d, axes_ct );
}

TEST_CASE("tensordot(case2i)" * doctest::test_suite("view::tensordot"))
{
    TENSORDOT_SUBCASE( case2i, a, b, axes );
    TENSORDOT_SUBCASE( case2i, a_a, b_a, axes );
    TENSORDOT_SUBCASE( case2i, a_f, b_f, axes );
    TENSORDOT_SUBCASE( case2i, a_h, b_h, axes );
    TENSORDOT_SUBCASE( case2i, a_d, b_d, axes );

    TENSORDOT_SUBCASE( case2i, a, b, axes_ct );
    TENSORDOT_SUBCASE( case2i, a_a, b_a, axes_ct );
    TENSORDOT_SUBCASE( case2i, a_f, b_f, axes_ct );
    TENSORDOT_SUBCASE( case2i, a_h, b_h, axes_ct );
    TENSORDOT_SUBCASE( case2i, a_d, b_d, axes_ct );
}

TEST_CASE("tensordot(case2j)" * doctest::test_suite("view::tensordot"))
{
    TENSORDOT_SUBCASE( case2j, a, b, axes );
    TENSORDOT_SUBCASE( case2j, a_a, b_a, axes );
    TENSORDOT_SUBCASE( case2j, a_f, b_f, axes );
    TENSORDOT_SUBCASE( case2j, a_h, b_h, axes );
    TENSORDOT_SUBCASE( case2j, a_d, b_d, axes );

    TENSORDOT_SUBCASE( case2j, a, b, axes_ct );
    TENSORDOT_SUBCASE( case2j, a_a, b_a, axes_ct );
    TENSORDOT_SUBCASE( case2j, a_f, b_f, axes_ct );
    TENSORDOT_SUBCASE( case2j, a_h, b_h, axes_ct );
    TENSORDOT_SUBCASE( case2j, a_d, b_d, axes_ct );
}

TEST_CASE("tensordot(case3a)" * doctest::test_suite("view::tensordot"))
{
    TENSORDOT_SUBCASE( case3a, a, b );
    TENSORDOT_SUBCASE( case3a, a_a, b_a );
    TENSORDOT_SUBCASE( case3a, a_f, b_f );
    TENSORDOT_SUBCASE( case3a, a_h, b_h );
    TENSORDOT_SUBCASE( case3a, a_d, b_d );
}

TEST_CASE("tensordot(case3b)" * doctest::test_suite("view::tensordot"))
{
    TENSORDOT_SUBCASE( case3b, a, b, axes );
    TENSORDOT_SUBCASE( case3b, a_a, b_a, axes );
    TENSORDOT_SUBCASE( case3b, a_f, b_f, axes );
    TENSORDOT_SUBCASE( case3b, a_h, b_h, axes );
    TENSORDOT_SUBCASE( case3b, a_d, b_d, axes );

    TENSORDOT_SUBCASE( case3b, a, b, axes_ct );
    TENSORDOT_SUBCASE( case3b, a_a, b_a, axes_ct );
    TENSORDOT_SUBCASE( case3b, a_f, b_f, axes_ct );
    TENSORDOT_SUBCASE( case3b, a_h, b_h, axes_ct );
    TENSORDOT_SUBCASE( case3b, a_d, b_d, axes_ct );
}

TEST_CASE("tensordot(case3c)" * doctest::test_suite("view::tensordot"))
{
    TENSORDOT_SUBCASE( case3c, a, b, axes );
    TENSORDOT_SUBCASE( case3c, a_a, b_a, axes );
    TENSORDOT_SUBCASE( case3c, a_f, b_f, axes );
    TENSORDOT_SUBCASE( case3c, a_h, b_h, axes );
    TENSORDOT_SUBCASE( case3c, a_d, b_d, axes );

    TENSORDOT_SUBCASE( case3c, a, b, axes_ct );
    TENSORDOT_SUBCASE( case3c, a_a, b_a, axes_ct );
    TENSORDOT_SUBCASE( case3c, a_f, b_f, axes_ct );
    TENSORDOT_SUBCASE( case3c, a_h, b_h, axes_ct );
    TENSORDOT_SUBCASE( case3c, a_d, b_d, axes_ct );
}


TEST_CASE("tensordot(case3d)" * doctest::test_suite("view::tensordot"))
{
    TENSORDOT_SUBCASE( case3d, a, b, axes );
    TENSORDOT_SUBCASE( case3d, a_a, b_a, axes );
    TENSORDOT_SUBCASE( case3d, a_f, b_f, axes );
    TENSORDOT_SUBCASE( case3d, a_h, b_h, axes );
    TENSORDOT_SUBCASE( case3d, a_d, b_d, axes );

    TENSORDOT_SUBCASE( case3d, a, b, axes_ct );
    TENSORDOT_SUBCASE( case3d, a_a, b_a, axes_ct );
    TENSORDOT_SUBCASE( case3d, a_f, b_f, axes_ct );
    TENSORDOT_SUBCASE( case3d, a_h, b_h, axes_ct );
    TENSORDOT_SUBCASE( case3d, a_d, b_d, axes_ct );
}

TEST_CASE("tensordot(case3e)" * doctest::test_suite("view::tensordot"))
{
    // TODO: fix compilation
    // TENSORDOT_SUBCASE( case3e, a, b, axes );
    // TENSORDOT_SUBCASE( case3e, a_a, b_a, axes );
    // TENSORDOT_SUBCASE( case3e, a_f, b_f, axes );
    // TENSORDOT_SUBCASE( case3e, a_h, b_h, axes );
    // TENSORDOT_SUBCASE( case3e, a_d, b_d, axes );

    TENSORDOT_SUBCASE( case3e, a, b, axes_ct );
    TENSORDOT_SUBCASE( case3e, a_a, b_a, axes_ct );
    TENSORDOT_SUBCASE( case3e, a_f, b_f, axes_ct );
    TENSORDOT_SUBCASE( case3e, a_h, b_h, axes_ct );
    // TENSORDOT_SUBCASE( case3e, a_d, b_d, axes_ct );
}

TEST_CASE("tensordot(case4a)" * doctest::test_suite("view::tensordot"))
{
    TENSORDOT_SUBCASE( case4a, a, b, axes );
    TENSORDOT_SUBCASE( case4a, a_a, b_a, axes );
    TENSORDOT_SUBCASE( case4a, a_f, b_f, axes );
    TENSORDOT_SUBCASE( case4a, a_h, b_h, axes );
    TENSORDOT_SUBCASE( case4a, a_d, b_d, axes );

    TENSORDOT_SUBCASE( case4a, a, b, axes_ct );
    TENSORDOT_SUBCASE( case4a, a_a, b_a, axes_ct );
    TENSORDOT_SUBCASE( case4a, a_f, b_f, axes_ct );
    TENSORDOT_SUBCASE( case4a, a_h, b_h, axes_ct );
    TENSORDOT_SUBCASE( case4a, a_d, b_d, axes_ct );
}

TEST_CASE("tensordot(case4b)" * doctest::test_suite("view::tensordot"))
{
    TENSORDOT_SUBCASE( case4b, a, b, axes );
    TENSORDOT_SUBCASE( case4b, a_a, b_a, axes );
    TENSORDOT_SUBCASE( case4b, a_f, b_f, axes );
    TENSORDOT_SUBCASE( case4b, a_h, b_h, axes );
    TENSORDOT_SUBCASE( case4b, a_d, b_d, axes );

    TENSORDOT_SUBCASE( case4b, a, b, axes_ct );
    TENSORDOT_SUBCASE( case4b, a_a, b_a, axes_ct );
    TENSORDOT_SUBCASE( case4b, a_f, b_f, axes_ct );
    TENSORDOT_SUBCASE( case4b, a_h, b_h, axes_ct );
    TENSORDOT_SUBCASE( case4b, a_d, b_d, axes_ct );
}