#include "nmtools/array/kron.hpp"
#include "nmtools/testing/data/index/kron.hpp"
#include "nmtools/testing/doctest.hpp"

#define KRON_DST_TRANSPOSE_SUBCASE(case_name,...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( index, kron_dst_transpose, case_name ); \
    auto result = nmtools::index::kron_dst_transpose( __VA_ARGS__ ); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("kron_dst_transpose(case1a)" * doctest::test_suite("index::kron_dst_transpose"))
{
    KRON_DST_TRANSPOSE_SUBCASE( case1a, lhs_dim, rhs_dim );
    KRON_DST_TRANSPOSE_SUBCASE( case1a, lhs_dim_ct, rhs_dim_ct );
    KRON_DST_TRANSPOSE_SUBCASE( case1a, lhs_dim_cl, rhs_dim_cl );
}

TEST_CASE("kron_dst_transpose(case1b)" * doctest::test_suite("index::kron_dst_transpose"))
{
    KRON_DST_TRANSPOSE_SUBCASE( case1b, lhs_dim, rhs_dim );
    KRON_DST_TRANSPOSE_SUBCASE( case1b, lhs_dim_ct, rhs_dim_ct );
    KRON_DST_TRANSPOSE_SUBCASE( case1b, lhs_dim_cl, rhs_dim_cl );
}

TEST_CASE("kron_dst_transpose(case1c)" * doctest::test_suite("index::kron_dst_transpose"))
{
    KRON_DST_TRANSPOSE_SUBCASE( case1c, lhs_dim, rhs_dim );
    KRON_DST_TRANSPOSE_SUBCASE( case1c, lhs_dim_ct, rhs_dim_ct );
    KRON_DST_TRANSPOSE_SUBCASE( case1c, lhs_dim_cl, rhs_dim_cl );
}

TEST_CASE("kron_dst_transpose(case1d)" * doctest::test_suite("index::kron_dst_transpose"))
{
    KRON_DST_TRANSPOSE_SUBCASE( case1d, lhs_dim, rhs_dim );
    KRON_DST_TRANSPOSE_SUBCASE( case1d, lhs_dim_ct, rhs_dim_ct );
    KRON_DST_TRANSPOSE_SUBCASE( case1d, lhs_dim_cl, rhs_dim_cl );
}

TEST_CASE("kron_dst_transpose(case1e)" * doctest::test_suite("index::kron_dst_transpose"))
{
    KRON_DST_TRANSPOSE_SUBCASE( case1e, lhs_dim, rhs_dim );
    KRON_DST_TRANSPOSE_SUBCASE( case1e, lhs_dim_ct, rhs_dim_ct );
    KRON_DST_TRANSPOSE_SUBCASE( case1e, lhs_dim_cl, rhs_dim_cl );
}

TEST_CASE("kron_dst_transpose(case2a)" * doctest::test_suite("index::kron_dst_transpose"))
{
    KRON_DST_TRANSPOSE_SUBCASE( case2a, lhs_dim, rhs_dim );
    KRON_DST_TRANSPOSE_SUBCASE( case2a, lhs_dim_ct, rhs_dim_ct );
    KRON_DST_TRANSPOSE_SUBCASE( case2a, lhs_dim_cl, rhs_dim_cl );
}

TEST_CASE("kron_dst_transpose(case2b)" * doctest::test_suite("index::kron_dst_transpose"))
{
    KRON_DST_TRANSPOSE_SUBCASE( case2b, lhs_dim, rhs_dim );
    KRON_DST_TRANSPOSE_SUBCASE( case2b, lhs_dim_ct, rhs_dim_ct );
    KRON_DST_TRANSPOSE_SUBCASE( case2b, lhs_dim_cl, rhs_dim_cl );
}

TEST_CASE("kron_dst_transpose(case2c)" * doctest::test_suite("index::kron_dst_transpose"))
{
    KRON_DST_TRANSPOSE_SUBCASE( case2c, lhs_dim, rhs_dim );
    KRON_DST_TRANSPOSE_SUBCASE( case2c, lhs_dim_ct, rhs_dim_ct );
    KRON_DST_TRANSPOSE_SUBCASE( case2c, lhs_dim_cl, rhs_dim_cl );
}

TEST_CASE("kron_dst_transpose(case2d)" * doctest::test_suite("index::kron_dst_transpose"))
{
    KRON_DST_TRANSPOSE_SUBCASE( case2d, lhs_dim, rhs_dim );
    KRON_DST_TRANSPOSE_SUBCASE( case2d, lhs_dim_ct, rhs_dim_ct );
    KRON_DST_TRANSPOSE_SUBCASE( case2d, lhs_dim_cl, rhs_dim_cl );
}

TEST_CASE("kron_dst_transpose(case2e)" * doctest::test_suite("index::kron_dst_transpose"))
{
    KRON_DST_TRANSPOSE_SUBCASE( case2e, lhs_dim, rhs_dim );
    KRON_DST_TRANSPOSE_SUBCASE( case2e, lhs_dim_ct, rhs_dim_ct );
    KRON_DST_TRANSPOSE_SUBCASE( case2e, lhs_dim_cl, rhs_dim_cl );
}

TEST_CASE("kron_dst_transpose(case2f)" * doctest::test_suite("index::kron_dst_transpose"))
{
    KRON_DST_TRANSPOSE_SUBCASE( case2f, lhs_dim, rhs_dim );
    KRON_DST_TRANSPOSE_SUBCASE( case2f, lhs_dim_ct, rhs_dim_ct );
    KRON_DST_TRANSPOSE_SUBCASE( case2f, lhs_dim_cl, rhs_dim_cl );
}

TEST_CASE("kron_dst_transpose(case3a)" * doctest::test_suite("index::kron_dst_transpose"))
{
    KRON_DST_TRANSPOSE_SUBCASE( case3a, lhs_dim, rhs_dim );
    KRON_DST_TRANSPOSE_SUBCASE( case3a, lhs_dim_ct, rhs_dim_ct );
    KRON_DST_TRANSPOSE_SUBCASE( case3a, lhs_dim_cl, rhs_dim_cl );
}

TEST_CASE("kron_dst_transpose(case3b)" * doctest::test_suite("index::kron_dst_transpose"))
{
    KRON_DST_TRANSPOSE_SUBCASE( case3b, lhs_dim, rhs_dim );
    KRON_DST_TRANSPOSE_SUBCASE( case3b, lhs_dim_ct, rhs_dim_ct );
    KRON_DST_TRANSPOSE_SUBCASE( case3b, lhs_dim_cl, rhs_dim_cl );
}

TEST_CASE("kron_dst_transpose(case3c)" * doctest::test_suite("index::kron_dst_transpose"))
{
    KRON_DST_TRANSPOSE_SUBCASE( case3c, lhs_dim, rhs_dim );
    KRON_DST_TRANSPOSE_SUBCASE( case3c, lhs_dim_ct, rhs_dim_ct );
    KRON_DST_TRANSPOSE_SUBCASE( case3c, lhs_dim_cl, rhs_dim_cl );
}

TEST_CASE("kron_dst_transpose(case3d)" * doctest::test_suite("index::kron_dst_transpose"))
{
    KRON_DST_TRANSPOSE_SUBCASE( case3d, lhs_dim, rhs_dim );
    KRON_DST_TRANSPOSE_SUBCASE( case3d, lhs_dim_ct, rhs_dim_ct );
    KRON_DST_TRANSPOSE_SUBCASE( case3d, lhs_dim_cl, rhs_dim_cl );
}

TEST_CASE("kron_dst_transpose(case4a)" * doctest::test_suite("index::kron_dst_transpose"))
{
    KRON_DST_TRANSPOSE_SUBCASE( case4a, lhs_dim, rhs_dim );
    KRON_DST_TRANSPOSE_SUBCASE( case4a, lhs_dim_ct, rhs_dim_ct );
    KRON_DST_TRANSPOSE_SUBCASE( case4a, lhs_dim_cl, rhs_dim_cl );
}

TEST_CASE("kron_dst_transpose(case4b)" * doctest::test_suite("index::kron_dst_transpose"))
{
    KRON_DST_TRANSPOSE_SUBCASE( case4b, lhs_dim, rhs_dim );
    KRON_DST_TRANSPOSE_SUBCASE( case4b, lhs_dim_ct, rhs_dim_ct );
    KRON_DST_TRANSPOSE_SUBCASE( case4b, lhs_dim_cl, rhs_dim_cl );
}

TEST_CASE("kron_dst_transpose(case4c)" * doctest::test_suite("index::kron_dst_transpose"))
{
    KRON_DST_TRANSPOSE_SUBCASE( case4c, lhs_dim, rhs_dim );
    KRON_DST_TRANSPOSE_SUBCASE( case4c, lhs_dim_ct, rhs_dim_ct );
    KRON_DST_TRANSPOSE_SUBCASE( case4c, lhs_dim_cl, rhs_dim_cl );
}

TEST_CASE("kron_dst_transpose(case4d)" * doctest::test_suite("index::kron_dst_transpose"))
{
    KRON_DST_TRANSPOSE_SUBCASE( case4d, lhs_dim, rhs_dim );
    KRON_DST_TRANSPOSE_SUBCASE( case4d, lhs_dim_ct, rhs_dim_ct );
    KRON_DST_TRANSPOSE_SUBCASE( case4d, lhs_dim_cl, rhs_dim_cl );
}

TEST_CASE("kron_dst_transpose(case5a)" * doctest::test_suite("index::kron_dst_transpose"))
{
    KRON_DST_TRANSPOSE_SUBCASE( case5a, lhs_dim, rhs_dim );
    KRON_DST_TRANSPOSE_SUBCASE( case5a, lhs_dim_ct, rhs_dim_ct );
    KRON_DST_TRANSPOSE_SUBCASE( case5a, lhs_dim_cl, rhs_dim_cl );
}

TEST_CASE("kron_dst_transpose(case6a)" * doctest::test_suite("index::kron_dst_transpose"))
{
    KRON_DST_TRANSPOSE_SUBCASE( case6a, lhs_dim, rhs_dim );
    KRON_DST_TRANSPOSE_SUBCASE( case6a, lhs_dim_ct, rhs_dim_ct );
    KRON_DST_TRANSPOSE_SUBCASE( case6a, lhs_dim_cl, rhs_dim_cl );
}