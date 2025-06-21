#include "nmtools/array/kron.hpp"
#include "nmtools/testing/data/array/kron.hpp"
#include "nmtools/testing/doctest.hpp"

#define KRON_SUBCASE(case_name,...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array,kron,case_name); \
    auto result = nmtools::kron(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("kron(case1a)" * doctest::test_suite("array::kron"))
{
    KRON_SUBCASE( case1a, a, b );
    KRON_SUBCASE( case1a, a_a, b_a );
    KRON_SUBCASE( case1a, a_f, b_f );
    KRON_SUBCASE( case1a, a_h, b_h );
    KRON_SUBCASE( case1a, a_d, b_d );
}

TEST_CASE("kron(case1b)" * doctest::test_suite("array::kron"))
{
    KRON_SUBCASE( case1b, a, b );
    KRON_SUBCASE( case1b, a_a, b_a );
    KRON_SUBCASE( case1b, a_f, b_f );
    KRON_SUBCASE( case1b, a_h, b_h );
    KRON_SUBCASE( case1b, a_d, b_d );
}

TEST_CASE("kron(case1c)" * doctest::test_suite("array::kron"))
{
    KRON_SUBCASE( case1c, a, b );
    KRON_SUBCASE( case1c, a_a, b_a );
    KRON_SUBCASE( case1c, a_f, b_f );
    KRON_SUBCASE( case1c, a_h, b_h );
    KRON_SUBCASE( case1c, a_d, b_d );
}

TEST_CASE("kron(case1d)" * doctest::test_suite("array::kron"))
{
    KRON_SUBCASE( case1d, a, b );
    KRON_SUBCASE( case1d, a_a, b_a );
    KRON_SUBCASE( case1d, a_f, b_f );
    KRON_SUBCASE( case1d, a_h, b_h );
    KRON_SUBCASE( case1d, a_d, b_d );
}

TEST_CASE("kron(case1e)" * doctest::test_suite("array::kron"))
{
    KRON_SUBCASE( case1e, a, b );
    KRON_SUBCASE( case1e, a_a, b_a );
    KRON_SUBCASE( case1e, a_f, b_f );
    KRON_SUBCASE( case1e, a_h, b_h );
    KRON_SUBCASE( case1e, a_d, b_d );
}

TEST_CASE("kron(case2a)" * doctest::test_suite("array::kron"))
{
    KRON_SUBCASE( case2a, a, b );
    KRON_SUBCASE( case2a, a_a, b_a );
    KRON_SUBCASE( case2a, a_f, b_f );
    KRON_SUBCASE( case2a, a_h, b_h );
    KRON_SUBCASE( case2a, a_d, b_d );
}

TEST_CASE("kron(case2b)" * doctest::test_suite("array::kron"))
{
    KRON_SUBCASE( case2b, a, b );
    KRON_SUBCASE( case2b, a_a, b_a );
    KRON_SUBCASE( case2b, a_f, b_f );
    KRON_SUBCASE( case2b, a_h, b_h );
    KRON_SUBCASE( case2b, a_d, b_d );
}

TEST_CASE("kron(case2c)" * doctest::test_suite("array::kron"))
{
    KRON_SUBCASE( case2c, a, b );
    KRON_SUBCASE( case2c, a_a, b_a );
    KRON_SUBCASE( case2c, a_f, b_f );
    KRON_SUBCASE( case2c, a_h, b_h );
    KRON_SUBCASE( case2c, a_d, b_d );
}

TEST_CASE("kron(case2d)" * doctest::test_suite("array::kron"))
{
    KRON_SUBCASE( case2d, a, b );
    KRON_SUBCASE( case2d, a_a, b_a );
    KRON_SUBCASE( case2d, a_f, b_f );
    KRON_SUBCASE( case2d, a_h, b_h );
    KRON_SUBCASE( case2d, a_d, b_d );
}

TEST_CASE("kron(case2e)" * doctest::test_suite("array::kron"))
{
    KRON_SUBCASE( case2e, a, b );
    KRON_SUBCASE( case2e, a_a, b_a );
    KRON_SUBCASE( case2e, a_f, b_f );
    KRON_SUBCASE( case2e, a_h, b_h );
    KRON_SUBCASE( case2e, a_d, b_d );
}

TEST_CASE("kron(case2f)" * doctest::test_suite("array::kron"))
{
    KRON_SUBCASE( case2f, a, b );
    KRON_SUBCASE( case2f, a_a, b_a );
    KRON_SUBCASE( case2f, a_f, b_f );
    KRON_SUBCASE( case2f, a_h, b_h );
    KRON_SUBCASE( case2f, a_d, b_d );
}

TEST_CASE("kron(case2g)" * doctest::test_suite("array::kron"))
{
    KRON_SUBCASE( case2g, a, b );
    KRON_SUBCASE( case2g, a_a, b_a );
    KRON_SUBCASE( case2g, a_f, b_f );
    KRON_SUBCASE( case2g, a_h, b_h );
    KRON_SUBCASE( case2g, a_d, b_d );
}

TEST_CASE("kron(case2h)" * doctest::test_suite("array::kron"))
{
    KRON_SUBCASE( case2h, a, b );
    KRON_SUBCASE( case2h, a_a, b_a );
    KRON_SUBCASE( case2h, a_f, b_f );
    KRON_SUBCASE( case2h, a_h, b_h );
    KRON_SUBCASE( case2h, a_d, b_d );
}

TEST_CASE("kron(case3a)" * doctest::test_suite("array::kron"))
{
    KRON_SUBCASE( case3a, a, b );
    KRON_SUBCASE( case3a, a_a, b_a );
    KRON_SUBCASE( case3a, a_f, b_f );
    KRON_SUBCASE( case3a, a_h, b_h );
    KRON_SUBCASE( case3a, a_d, b_d );
}

TEST_CASE("kron(case3b)" * doctest::test_suite("array::kron"))
{
    KRON_SUBCASE( case3b, a, b );
    KRON_SUBCASE( case3b, a_a, b_a );
    KRON_SUBCASE( case3b, a_f, b_f );
    KRON_SUBCASE( case3b, a_h, b_h );
    KRON_SUBCASE( case3b, a_d, b_d );
}

TEST_CASE("kron(case3d)" * doctest::test_suite("array::kron"))
{
    KRON_SUBCASE( case3d, a, b );
    KRON_SUBCASE( case3d, a_a, b_a );
    KRON_SUBCASE( case3d, a_f, b_f );
    KRON_SUBCASE( case3d, a_h, b_h );
    KRON_SUBCASE( case3d, a_d, b_d );
}

TEST_CASE("kron(case3e)" * doctest::test_suite("array::kron"))
{
    KRON_SUBCASE( case3e, a, b );
    KRON_SUBCASE( case3e, a_a, b_a );
    KRON_SUBCASE( case3e, a_f, b_f );
    KRON_SUBCASE( case3e, a_h, b_h );
    KRON_SUBCASE( case3e, a_d, b_d );
}

TEST_CASE("kron(case3f)" * doctest::test_suite("array::kron"))
{
    KRON_SUBCASE( case3f, a, b );
    KRON_SUBCASE( case3f, a_a, b_a );
    KRON_SUBCASE( case3f, a_f, b_f );
    KRON_SUBCASE( case3f, a_h, b_h );
    KRON_SUBCASE( case3f, a_d, b_d );
}

TEST_CASE("kron(case3g)" * doctest::test_suite("array::kron"))
{
    KRON_SUBCASE( case3g, a, b );
    KRON_SUBCASE( case3g, a_a, b_a );
    KRON_SUBCASE( case3g, a_f, b_f );
    KRON_SUBCASE( case3g, a_h, b_h );
    KRON_SUBCASE( case3g, a_d, b_d );
}

TEST_CASE("kron(case3h)" * doctest::test_suite("array::kron"))
{
    KRON_SUBCASE( case3h, a, b );
    KRON_SUBCASE( case3h, a_a, b_a );
    KRON_SUBCASE( case3h, a_f, b_f );
    KRON_SUBCASE( case3h, a_h, b_h );
    KRON_SUBCASE( case3h, a_d, b_d );
}

TEST_CASE("kron(case4a)" * doctest::test_suite("array::kron"))
{
    KRON_SUBCASE( case4a, a, b );
    KRON_SUBCASE( case4a, a_a, b_a );
    KRON_SUBCASE( case4a, a_f, b_f );
    KRON_SUBCASE( case4a, a_h, b_h );
    KRON_SUBCASE( case4a, a_d, b_d );
}

TEST_CASE("kron(case4b)" * doctest::test_suite("array::kron"))
{
    KRON_SUBCASE( case4b, a, b );
    KRON_SUBCASE( case4b, a_a, b_a );
    KRON_SUBCASE( case4b, a_f, b_f );
    KRON_SUBCASE( case4b, a_h, b_h );
    KRON_SUBCASE( case4b, a_d, b_d );
}

TEST_CASE("kron(case4c)" * doctest::test_suite("array::kron"))
{
    KRON_SUBCASE( case4c, a, b );
    KRON_SUBCASE( case4c, a_a, b_a );
    KRON_SUBCASE( case4c, a_f, b_f );
    KRON_SUBCASE( case4c, a_h, b_h );
    KRON_SUBCASE( case4c, a_d, b_d );
}

TEST_CASE("kron(case4d)" * doctest::test_suite("array::kron"))
{
    KRON_SUBCASE( case4d, a, b );
    KRON_SUBCASE( case4d, a_a, b_a );
    KRON_SUBCASE( case4d, a_f, b_f );
    KRON_SUBCASE( case4d, a_h, b_h );
    KRON_SUBCASE( case4d, a_d, b_d );
}

TEST_CASE("kron(case5a)" * doctest::test_suite("array::kron"))
{
    KRON_SUBCASE( case5a, a, b );
    KRON_SUBCASE( case5a, a_a, b_a );
    KRON_SUBCASE( case5a, a_f, b_f );
    KRON_SUBCASE( case5a, a_h, b_h );
    KRON_SUBCASE( case5a, a_d, b_d );
}

TEST_CASE("kron(case6a)" * doctest::test_suite("array::kron"))
{
    KRON_SUBCASE( case6a, a, b );
    KRON_SUBCASE( case6a, a_a, b_a );
    KRON_SUBCASE( case6a, a_f, b_f );
    KRON_SUBCASE( case6a, a_h, b_h );
    KRON_SUBCASE( case6a, a_d, b_d );
}