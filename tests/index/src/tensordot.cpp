#include "nmtools/array/view/tensordot.hpp"
#include "nmtools/testing/data/index/tensordot.hpp"
#include "nmtools/testing/doctest.hpp"

#define TENSORDOT_LHS_TRANSPOSE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index,tensordot_lhs_transpose,case_name) \
    auto result = nmtools::index::tensordot_lhs_transpose(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("tensordot_lhs_transpose(case1a)" * doctest::test_suite("index::tensordot_lhs_transpose"))
{
    TENSORDOT_LHS_TRANSPOSE_SUBCASE( case1a, dim, axes );
    TENSORDOT_LHS_TRANSPOSE_SUBCASE( case1a, dim_ct, axes_ct );
}

TEST_CASE("tensordot_lhs_transpose(case2a)" * doctest::test_suite("index::tensordot_lhs_transpose"))
{
    TENSORDOT_LHS_TRANSPOSE_SUBCASE( case2a, dim, axes );
    TENSORDOT_LHS_TRANSPOSE_SUBCASE( case2a, dim_ct, axes_ct );
}

TEST_CASE("tensordot_lhs_transpose(case2b)" * doctest::test_suite("index::tensordot_lhs_transpose"))
{
    TENSORDOT_LHS_TRANSPOSE_SUBCASE( case2b, dim, axes );
    TENSORDOT_LHS_TRANSPOSE_SUBCASE( case2b, dim_ct, axes_ct );
}

TEST_CASE("tensordot_lhs_transpose(case2e)" * doctest::test_suite("index::tensordot_lhs_transpose"))
{
    TENSORDOT_LHS_TRANSPOSE_SUBCASE( case2e, dim, axes );
    TENSORDOT_LHS_TRANSPOSE_SUBCASE( case2e, dim, axes_a );
    TENSORDOT_LHS_TRANSPOSE_SUBCASE( case2e, dim, axes_f );
    TENSORDOT_LHS_TRANSPOSE_SUBCASE( case2e, dim, axes_h );
    TENSORDOT_LHS_TRANSPOSE_SUBCASE( case2e, dim, axes_v );
    TENSORDOT_LHS_TRANSPOSE_SUBCASE( case2e, dim_ct, axes_ct );
}

TEST_CASE("tensordot_lhs_transpose(case2h)" * doctest::test_suite("index::tensordot_lhs_transpose"))
{
    TENSORDOT_LHS_TRANSPOSE_SUBCASE( case2h, dim, axes );
    TENSORDOT_LHS_TRANSPOSE_SUBCASE( case2h, dim, axes_a );
    TENSORDOT_LHS_TRANSPOSE_SUBCASE( case2h, dim, axes_f );
    TENSORDOT_LHS_TRANSPOSE_SUBCASE( case2h, dim, axes_h );
    TENSORDOT_LHS_TRANSPOSE_SUBCASE( case2h, dim, axes_v );
    TENSORDOT_LHS_TRANSPOSE_SUBCASE( case2h, dim_ct, axes_ct );
}

TEST_CASE("tensordot_lhs_transpose(case3a)" * doctest::test_suite("index::tensordot_lhs_transpose"))
{
    TENSORDOT_LHS_TRANSPOSE_SUBCASE( case3a, dim, axes );
    TENSORDOT_LHS_TRANSPOSE_SUBCASE( case3a, dim_ct, axes_ct );
}

TEST_CASE("tensordot_lhs_transpose(case3b)" * doctest::test_suite("index::tensordot_lhs_transpose"))
{
    TENSORDOT_LHS_TRANSPOSE_SUBCASE( case3b, dim, axes );
    TENSORDOT_LHS_TRANSPOSE_SUBCASE( case3b, dim_ct, axes_ct );
}

TEST_CASE("tensordot_lhs_transpose(case3d)" * doctest::test_suite("index::tensordot_lhs_transpose"))
{
    TENSORDOT_LHS_TRANSPOSE_SUBCASE( case3d, dim, axes );
    TENSORDOT_LHS_TRANSPOSE_SUBCASE( case3d, dim_ct, axes_ct );
}

TEST_CASE("tensordot_lhs_transpose(case3e)" * doctest::test_suite("index::tensordot_lhs_transpose"))
{
    TENSORDOT_LHS_TRANSPOSE_SUBCASE( case3e, dim, axes );
    TENSORDOT_LHS_TRANSPOSE_SUBCASE( case3e, dim_ct, axes_ct );
}

#define TENSORDOT_RHS_TRANSPOSE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index,tensordot_rhs_transpose,case_name); \
    auto result = nmtools::index::tensordot_rhs_transpose(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("tensordot_rhs_transpose(case1a)" * doctest::test_suite("index::tensordot_lhs_transpose"))
{
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case1a, dim, axes );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case1a, dim, axes_a );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case1a, dim, axes_f );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case1a, dim, axes_h );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case1a, dim, axes_v );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case1a, dim_ct, axes_ct );
}

TEST_CASE("tensordot_rhs_transpose(case2a)" * doctest::test_suite("index::tensordot_lhs_transpose"))
{
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case2a, dim, axes );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case2a, dim, axes_a );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case2a, dim, axes_f );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case2a, dim, axes_h );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case2a, dim, axes_v );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case2a, dim_ct, axes_ct );
}

TEST_CASE("tensordot_rhs_transpose(case2b)" * doctest::test_suite("index::tensordot_lhs_transpose"))
{
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case2b, dim, axes );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case2b, dim, axes_a );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case2b, dim, axes_f );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case2b, dim, axes_h );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case2b, dim, axes_v );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case2b, dim_ct, axes_ct );
}

TEST_CASE("tensordot_rhs_transpose(case2d)" * doctest::test_suite("index::tensordot_lhs_transpose"))
{
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case2d, dim, axes );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case2d, dim, axes_a );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case2d, dim, axes_f );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case2d, dim, axes_h );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case2d, dim, axes_v );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case2d, dim_ct, axes_ct );
}

TEST_CASE("tensordot_rhs_transpose(case2e)" * doctest::test_suite("index::tensordot_lhs_transpose"))
{
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case2e, dim, axes );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case2e, dim, axes_a );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case2e, dim, axes_f );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case2e, dim, axes_h );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case2e, dim, axes_v );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case2e, dim_ct, axes_ct );
}

TEST_CASE("tensordot_rhs_transpose(case2g)" * doctest::test_suite("index::tensordot_lhs_transpose"))
{
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case2g, dim, axes );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case2g, dim, axes_a );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case2g, dim, axes_f );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case2g, dim, axes_h );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case2g, dim, axes_v );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case2g, dim_ct, axes_ct );
}

TEST_CASE("tensordot_rhs_transpose(case2i)" * doctest::test_suite("index::tensordot_lhs_transpose"))
{
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case2i, dim, axes );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case2i, dim, axes_a );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case2i, dim, axes_f );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case2i, dim, axes_h );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case2i, dim, axes_v );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case2i, dim_ct, axes_ct );
}

TEST_CASE("tensordot_rhs_transpose(case2j)" * doctest::test_suite("index::tensordot_lhs_transpose"))
{
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case2j, dim, axes );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case2j, dim, axes_a );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case2j, dim, axes_f );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case2j, dim, axes_h );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case2j, dim, axes_v );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case2j, dim_ct, axes_ct );
}

TEST_CASE("tensordot_rhs_transpose(case3a)" * doctest::test_suite("index::tensordot_lhs_transpose"))
{
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case3a, dim, axes );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case3a, dim, axes_a );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case3a, dim, axes_f );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case3a, dim, axes_h );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case3a, dim, axes_v );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case3a, dim_ct, axes_ct );
}

TEST_CASE("tensordot_rhs_transpose(case3c)" * doctest::test_suite("index::tensordot_lhs_transpose"))
{
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case3c, dim, axes );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case3c, dim, axes_a );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case3c, dim, axes_f );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case3c, dim, axes_h );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case3c, dim, axes_v );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case3c, dim_ct, axes_ct );
}

TEST_CASE("tensordot_rhs_transpose(case3d)" * doctest::test_suite("index::tensordot_lhs_transpose"))
{
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case3d, dim, axes );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case3d, dim, axes_a );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case3d, dim, axes_f );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case3d, dim, axes_h );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case3d, dim, axes_v );
    TENSORDOT_RHS_TRANSPOSE_SUBCASE( case3d, dim_ct, axes_ct );
}

#define TENSORDOT_LHS_RESHAPE_SUBCASE(case_name,...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( index, tensordot_lhs_reshape, case_name ); \
    auto result = nmtools::index::tensordot_lhs_reshape(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("tensordot_lhs_reshape(case1a)" * doctest::test_suite("index::tensordot_lhs_reshape"))
{
    TENSORDOT_LHS_RESHAPE_SUBCASE( case1a, lhs_shape, rhs_shape, lhs_axes );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case1a, lhs_shape_a, rhs_shape_a, lhs_axes_a );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case1a, lhs_shape_f, rhs_shape_f, lhs_axes_f );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case1a, lhs_shape_h, rhs_shape_h, lhs_axes_h );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case1a, lhs_shape_v, rhs_shape_v, lhs_axes_v );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case1a, lhs_shape_ct, rhs_shape_ct, lhs_axes_ct );
}

TEST_CASE("tensordot_lhs_reshape(case2a)" * doctest::test_suite("index::tensordot_lhs_reshape"))
{
    TENSORDOT_LHS_RESHAPE_SUBCASE( case2a, lhs_shape, rhs_shape, lhs_axes );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case2a, lhs_shape_a, rhs_shape_a, lhs_axes_a );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case2a, lhs_shape_f, rhs_shape_f, lhs_axes_f );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case2a, lhs_shape_h, rhs_shape_h, lhs_axes_h );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case2a, lhs_shape_v, rhs_shape_v, lhs_axes_v );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case2a, lhs_shape_ct, rhs_shape_ct, lhs_axes_ct );
}

TEST_CASE("tensordot_lhs_reshape(case2b)" * doctest::test_suite("index::tensordot_lhs_reshape"))
{
    TENSORDOT_LHS_RESHAPE_SUBCASE( case2b, lhs_shape, rhs_shape, lhs_axes );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case2b, lhs_shape_a, rhs_shape_a, lhs_axes_a );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case2b, lhs_shape_f, rhs_shape_f, lhs_axes_f );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case2b, lhs_shape_h, rhs_shape_h, lhs_axes_h );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case2b, lhs_shape_v, rhs_shape_v, lhs_axes_v );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case2b, lhs_shape_ct, rhs_shape_ct, lhs_axes_ct );
}

TEST_CASE("tensordot_lhs_reshape(case2c)" * doctest::test_suite("index::tensordot_lhs_reshape"))
{
    TENSORDOT_LHS_RESHAPE_SUBCASE( case2c, lhs_shape, rhs_shape, lhs_axes );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case2c, lhs_shape_a, rhs_shape_a, lhs_axes_a );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case2c, lhs_shape_f, rhs_shape_f, lhs_axes_f );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case2c, lhs_shape_h, rhs_shape_h, lhs_axes_h );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case2c, lhs_shape_v, rhs_shape_v, lhs_axes_v );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case2c, lhs_shape_ct, rhs_shape_ct, lhs_axes_ct );
}

TEST_CASE("tensordot_lhs_reshape(case2d)" * doctest::test_suite("index::tensordot_lhs_reshape"))
{
    TENSORDOT_LHS_RESHAPE_SUBCASE( case2d, lhs_shape, rhs_shape, lhs_axes );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case2d, lhs_shape_a, rhs_shape_a, lhs_axes_a );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case2d, lhs_shape_f, rhs_shape_f, lhs_axes_f );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case2d, lhs_shape_h, rhs_shape_h, lhs_axes_h );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case2d, lhs_shape_v, rhs_shape_v, lhs_axes_v );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case2d, lhs_shape_ct, rhs_shape_ct, lhs_axes_ct );
}

TEST_CASE("tensordot_lhs_reshape(case2e)" * doctest::test_suite("index::tensordot_lhs_reshape"))
{
    TENSORDOT_LHS_RESHAPE_SUBCASE( case2e, lhs_shape, rhs_shape, lhs_axes );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case2e, lhs_shape_a, rhs_shape_a, lhs_axes_a );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case2e, lhs_shape_f, rhs_shape_f, lhs_axes_f );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case2e, lhs_shape_h, rhs_shape_h, lhs_axes_h );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case2e, lhs_shape_v, rhs_shape_v, lhs_axes_v );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case2e, lhs_shape_ct, rhs_shape_ct, lhs_axes_ct );
}

TEST_CASE("tensordot_lhs_reshape(case2f)" * doctest::test_suite("index::tensordot_lhs_reshape"))
{
    TENSORDOT_LHS_RESHAPE_SUBCASE( case2f, lhs_shape, rhs_shape, lhs_axes );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case2f, lhs_shape_a, rhs_shape_a, lhs_axes_a );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case2f, lhs_shape_f, rhs_shape_f, lhs_axes_f );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case2f, lhs_shape_h, rhs_shape_h, lhs_axes_h );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case2f, lhs_shape_v, rhs_shape_v, lhs_axes_v );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case2f, lhs_shape_ct, rhs_shape_ct, lhs_axes_ct );
}

TEST_CASE("tensordot_lhs_reshape(case2h)" * doctest::test_suite("index::tensordot_lhs_reshape"))
{
    TENSORDOT_LHS_RESHAPE_SUBCASE( case2h, lhs_shape, rhs_shape, lhs_axes );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case2h, lhs_shape_a, rhs_shape_a, lhs_axes_a );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case2h, lhs_shape_f, rhs_shape_f, lhs_axes_f );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case2h, lhs_shape_h, rhs_shape_h, lhs_axes_h );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case2h, lhs_shape_v, rhs_shape_v, lhs_axes_v );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case2h, lhs_shape_ct, rhs_shape_ct, lhs_axes_ct );
}

TEST_CASE("tensordot_lhs_reshape(case2j)" * doctest::test_suite("index::tensordot_lhs_reshape"))
{
    TENSORDOT_LHS_RESHAPE_SUBCASE( case2j, lhs_shape, rhs_shape, lhs_axes );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case2j, lhs_shape_a, rhs_shape_a, lhs_axes_a );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case2j, lhs_shape_f, rhs_shape_f, lhs_axes_f );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case2j, lhs_shape_h, rhs_shape_h, lhs_axes_h );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case2j, lhs_shape_v, rhs_shape_v, lhs_axes_v );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case2j, lhs_shape_ct, rhs_shape_ct, lhs_axes_ct );
}

TEST_CASE("tensordot_lhs_reshape(case3a)" * doctest::test_suite("index::tensordot_lhs_reshape"))
{
    TENSORDOT_LHS_RESHAPE_SUBCASE( case3a, lhs_shape, rhs_shape, lhs_axes );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case3a, lhs_shape_a, rhs_shape_a, lhs_axes_a );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case3a, lhs_shape_f, rhs_shape_f, lhs_axes_f );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case3a, lhs_shape_h, rhs_shape_h, lhs_axes_h );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case3a, lhs_shape_v, rhs_shape_v, lhs_axes_v );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case3a, lhs_shape_ct, rhs_shape_ct, lhs_axes_ct );
}

TEST_CASE("tensordot_lhs_reshape(case3b)" * doctest::test_suite("index::tensordot_lhs_reshape"))
{
    TENSORDOT_LHS_RESHAPE_SUBCASE( case3b, lhs_shape, rhs_shape, lhs_axes );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case3b, lhs_shape_a, rhs_shape_a, lhs_axes_a );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case3b, lhs_shape_f, rhs_shape_f, lhs_axes_f );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case3b, lhs_shape_h, rhs_shape_h, lhs_axes_h );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case3b, lhs_shape_v, rhs_shape_v, lhs_axes_v );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case3b, lhs_shape_ct, rhs_shape_ct, lhs_axes_ct );
}

TEST_CASE("tensordot_lhs_reshape(case3c)" * doctest::test_suite("index::tensordot_lhs_reshape"))
{
    TENSORDOT_LHS_RESHAPE_SUBCASE( case3c, lhs_shape, rhs_shape, lhs_axes );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case3c, lhs_shape_a, rhs_shape_a, lhs_axes_a );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case3c, lhs_shape_f, rhs_shape_f, lhs_axes_f );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case3c, lhs_shape_h, rhs_shape_h, lhs_axes_h );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case3c, lhs_shape_v, rhs_shape_v, lhs_axes_v );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case3c, lhs_shape_ct, rhs_shape_ct, lhs_axes_ct );
}

TEST_CASE("tensordot_lhs_reshape(case3d)" * doctest::test_suite("index::tensordot_lhs_reshape"))
{
    TENSORDOT_LHS_RESHAPE_SUBCASE( case3d, lhs_shape, rhs_shape, lhs_axes );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case3d, lhs_shape_a, rhs_shape_a, lhs_axes_a );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case3d, lhs_shape_f, rhs_shape_f, lhs_axes_f );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case3d, lhs_shape_h, rhs_shape_h, lhs_axes_h );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case3d, lhs_shape_v, rhs_shape_v, lhs_axes_v );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case3d, lhs_shape_ct, rhs_shape_ct, lhs_axes_ct );
}

TEST_CASE("tensordot_lhs_reshape(case3e)" * doctest::test_suite("index::tensordot_lhs_reshape"))
{
    TENSORDOT_LHS_RESHAPE_SUBCASE( case3e, lhs_shape, rhs_shape, lhs_axes );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case3e, lhs_shape_a, rhs_shape_a, lhs_axes_a );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case3e, lhs_shape_f, rhs_shape_f, lhs_axes_f );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case3e, lhs_shape_h, rhs_shape_h, lhs_axes_h );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case3e, lhs_shape_v, rhs_shape_v, lhs_axes_v );
    TENSORDOT_LHS_RESHAPE_SUBCASE( case3e, lhs_shape_ct, rhs_shape_ct, lhs_axes_ct );
}