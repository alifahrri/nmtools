#if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
#define NMTOOLS_CAST_ARRAYS_EXTRA(name) \
inline auto name##_cs_fb = nmtools::cast(name, nmtools::kind::ndarray_cs_fb); \
inline auto name##_cs_hb = nmtools::cast(name, nmtools::kind::ndarray_cs_hb); \
inline auto name##_cs_db = nmtools::cast(name, nmtools::kind::ndarray_cs_db); \
inline auto name##_fs_fb = nmtools::cast(name, nmtools::kind::ndarray_fs_fb); \
inline auto name##_fs_hb = nmtools::cast(name, nmtools::kind::ndarray_fs_hb); \
inline auto name##_fs_db = nmtools::cast(name, nmtools::kind::ndarray_fs_db); \
inline auto name##_hs_fb = nmtools::cast(name, nmtools::kind::ndarray_hs_fb); \
inline auto name##_hs_hb = nmtools::cast(name, nmtools::kind::ndarray_hs_hb); \
inline auto name##_hs_db = nmtools::cast(name, nmtools::kind::ndarray_hs_db); \
inline auto name##_ds_fb = nmtools::cast(name, nmtools::kind::ndarray_ds_fb); \
inline auto name##_ds_hb = nmtools::cast(name, nmtools::kind::ndarray_ds_hb); \
inline auto name##_ds_db = nmtools::cast(name, nmtools::kind::ndarray_ds_db); \
inline auto name##_ls_fb = nmtools::cast(name, nmtools::kind::ndarray_ls_fb); \
inline auto name##_ls_hb = nmtools::cast(name, nmtools::kind::ndarray_ls_hb); \
inline auto name##_ls_db = nmtools::cast(name, nmtools::kind::ndarray_ls_db);
#endif

#include "nmtools/core/stride.hpp"
#include "nmtools/testing/data/array/stride.hpp"
#include "nmtools/testing/doctest.hpp"

#define STRIDE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( array, stride, case_name ); \
    auto result = nmtools::view::stride(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::expected) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}

#define CONSTEXPR_STRIDE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( array, constexpr_stride, case_name ); \
    constexpr auto result = nmtools::view::stride(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::expected) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}

TEST_CASE("stride(case1)" * doctest::test_suite("view::stride"))
{
    STRIDE_SUBCASE( case1, x, shape, striding );
    STRIDE_SUBCASE( case1, x, shape_a, striding_a );
    STRIDE_SUBCASE( case1, x, shape_f, striding_f );
    STRIDE_SUBCASE( case1, x, shape_h, striding_h );
    STRIDE_SUBCASE( case1, x, shape_v, striding_v );

    STRIDE_SUBCASE( case1, x, shape_ct, striding_ct );
    STRIDE_SUBCASE( case1, x, shape_mx1, striding_mx1 );
    STRIDE_SUBCASE( case1, x, shape_mx2, striding_mx2 );
}

TEST_CASE("stride(case2)" * doctest::test_suite("view::stride"))
{
    STRIDE_SUBCASE( case2, x, shape, striding );
    STRIDE_SUBCASE( case2, x, shape_a, striding_a );
    STRIDE_SUBCASE( case2, x, shape_f, striding_f );
    STRIDE_SUBCASE( case2, x, shape_h, striding_h );
    STRIDE_SUBCASE( case2, x, shape_v, striding_v );

    STRIDE_SUBCASE( case2, x, shape_ct, striding_ct );
    STRIDE_SUBCASE( case2, x, shape_mx1, striding_mx1 );
    STRIDE_SUBCASE( case2, x, shape_mx2, striding_mx2 );
}

TEST_CASE("stride(case3)" * doctest::test_suite("view::stride"))
{
    STRIDE_SUBCASE( case3, x, shape, striding );
    STRIDE_SUBCASE( case3, x, shape_a, striding_a );
    STRIDE_SUBCASE( case3, x, shape_f, striding_f );
    STRIDE_SUBCASE( case3, x, shape_h, striding_h );
    STRIDE_SUBCASE( case3, x, shape_v, striding_v );

    STRIDE_SUBCASE( case3, x, shape_ct, striding_ct );
    STRIDE_SUBCASE( case3, x, shape_mx1, striding_mx1 );
    STRIDE_SUBCASE( case3, x, shape_mx2, striding_mx2 );
}

TEST_CASE("stride(case4)" * doctest::test_suite("view::stride"))
{
    STRIDE_SUBCASE( case4, x, shape, striding );
    STRIDE_SUBCASE( case4, x, shape_a, striding_a );
    STRIDE_SUBCASE( case4, x, shape_f, striding_f );
    STRIDE_SUBCASE( case4, x, shape_h, striding_h );
    STRIDE_SUBCASE( case4, x, shape_v, striding_v );

    STRIDE_SUBCASE( case4, x, shape_ct, striding_ct );
    STRIDE_SUBCASE( case4, x, shape_mx1, striding_mx1 );
    STRIDE_SUBCASE( case4, x, shape_mx2, striding_mx2 );
}

TEST_CASE("stride(case5)" * doctest::test_suite("view::stride") * doctest::skip())
{
    STRIDE_SUBCASE( case5, x, shape, striding );
}

TEST_CASE("stride(case6)" * doctest::test_suite("view::stride"))
{
    STRIDE_SUBCASE( case6, x, shape, striding );
    STRIDE_SUBCASE( case6, x, shape_a, striding_a );
    STRIDE_SUBCASE( case6, x, shape_f, striding_f );
    STRIDE_SUBCASE( case6, x, shape_h, striding_h );
    STRIDE_SUBCASE( case6, x, shape_v, striding_v );

    STRIDE_SUBCASE( case6, x, shape_ct, striding_ct );
    STRIDE_SUBCASE( case6, x, shape_mx1, striding_mx1 );
}

TEST_CASE("stride(case7)" * doctest::test_suite("view::stride"))
{
    STRIDE_SUBCASE( case7, x, shape, striding );
    STRIDE_SUBCASE( case7, x, shape_a, striding_a );
    STRIDE_SUBCASE( case7, x, shape_f, striding_f );
    STRIDE_SUBCASE( case7, x, shape_h, striding_h );
    STRIDE_SUBCASE( case7, x, shape_v, striding_v );

    STRIDE_SUBCASE( case7, x, shape_ct, striding_ct );
    STRIDE_SUBCASE( case7, x, shape_mx1, striding_mx1 );
}

TEST_CASE("stride(case8)" * doctest::test_suite("view::stride"))
{
    STRIDE_SUBCASE( case8, x, shape, striding );
    STRIDE_SUBCASE( case8, x, shape_a, striding_a );
    STRIDE_SUBCASE( case8, x, shape_f, striding_f );
    STRIDE_SUBCASE( case8, x, shape_h, striding_h );
    STRIDE_SUBCASE( case8, x, shape_v, striding_v );

    STRIDE_SUBCASE( case8, x, shape_ct, striding_ct );
    STRIDE_SUBCASE( case8, x, shape_mx1, striding_mx1 );
    STRIDE_SUBCASE( case8, x, shape_mx2, striding_mx2 );
}

TEST_CASE("stride(case9)" * doctest::test_suite("view::stride"))
{
    STRIDE_SUBCASE( case9, x, shape, striding );
    STRIDE_SUBCASE( case9, x, shape_a, striding_a );
    STRIDE_SUBCASE( case9, x, shape_f, striding_f );
    STRIDE_SUBCASE( case9, x, shape_h, striding_h );
    STRIDE_SUBCASE( case9, x, shape_v, striding_v );

    STRIDE_SUBCASE( case9, x, shape_ct, striding_ct );
    STRIDE_SUBCASE( case9, x, shape_mx1, striding_mx1 );
    STRIDE_SUBCASE( case9, x, shape_mx2, striding_mx2 );
}

TEST_CASE("stride(case10)" * doctest::test_suite("view::stride") * doctest::skip())
{
    STRIDE_SUBCASE( case10, x, shape, striding );
}

TEST_CASE("stride(case11)" * doctest::test_suite("view::stride"))
{
    STRIDE_SUBCASE( case11, x, nested_shape_a, nested_striding_a );
}

TEST_CASE("stride(case12)" * doctest::test_suite("view::stride"))
{
    STRIDE_SUBCASE( case12, x, shape, striding );
    STRIDE_SUBCASE( case12, x, shape_a, striding_a );
    STRIDE_SUBCASE( case12, x, shape_f, striding_f );
    STRIDE_SUBCASE( case12, x, shape_h, striding_h );
    STRIDE_SUBCASE( case12, x, shape_v, striding_v );

    STRIDE_SUBCASE( case12, x, shape_ct, striding_ct );
    STRIDE_SUBCASE( case12, x, shape_mx1, striding_mx1 );
    STRIDE_SUBCASE( case12, x, shape_mx2, striding_mx2 );
}

TEST_CASE("stride(case13)" * doctest::test_suite("view::stride"))
{
    STRIDE_SUBCASE( case13, x, shape, striding );
    STRIDE_SUBCASE( case13, x, shape_a, striding_a );
    STRIDE_SUBCASE( case13, x, shape_f, striding_f );
    STRIDE_SUBCASE( case13, x, shape_h, striding_h );
    STRIDE_SUBCASE( case13, x, shape_v, striding_v );

    STRIDE_SUBCASE( case13, x, shape_ct, striding_ct );
    STRIDE_SUBCASE( case13, x, shape_mx1, striding_mx1 );
    STRIDE_SUBCASE( case13, x, shape_mx2, striding_mx2 );
}

TEST_CASE("stride(case14)" * doctest::test_suite("view::stride"))
{
    STRIDE_SUBCASE( case14, x, nested_shape_ct, nested_striding_ct );
}

TEST_CASE("stride(case15)" * doctest::test_suite("view::stride"))
{
    STRIDE_SUBCASE( case15, x, shape, striding );
    STRIDE_SUBCASE( case15, x, shape_a, striding_a );
    STRIDE_SUBCASE( case15, x, shape_f, striding_f );
    STRIDE_SUBCASE( case15, x, shape_h, striding_h );
    STRIDE_SUBCASE( case15, x, shape_v, striding_v );

    STRIDE_SUBCASE( case15, x, shape_ct, striding_ct );
    STRIDE_SUBCASE( case15, x, shape_mx1, striding_mx1 );
    STRIDE_SUBCASE( case15, x, shape_mx2, striding_mx2 );
}

TEST_CASE("stride(case16)" * doctest::test_suite("view::stride"))
{
    STRIDE_SUBCASE( case16, x, shape, striding );
    STRIDE_SUBCASE( case16, x, shape_a, striding_a );
    STRIDE_SUBCASE( case16, x, shape_f, striding_f );
    STRIDE_SUBCASE( case16, x, shape_h, striding_h );
    STRIDE_SUBCASE( case16, x, shape_v, striding_v );

    STRIDE_SUBCASE( case16, x, shape_ct, striding_ct );
    STRIDE_SUBCASE( case16, x, shape_mx1, striding_mx1 );
    STRIDE_SUBCASE( case16, x, shape_mx2, striding_mx2 );
}

TEST_CASE("stride(case17)" * doctest::test_suite("view::stride"))
{
    STRIDE_SUBCASE( case17, x, shape, striding );
    STRIDE_SUBCASE( case17, x, shape_a, striding_a );
    STRIDE_SUBCASE( case17, x, shape_f, striding_f );
    STRIDE_SUBCASE( case17, x, shape_h, striding_h );
    STRIDE_SUBCASE( case17, x, shape_v, striding_v );

    STRIDE_SUBCASE( case17, x, shape_ct, striding_ct );
    STRIDE_SUBCASE( case17, x, shape_mx1, striding_mx1 );
    STRIDE_SUBCASE( case17, x, shape_mx2, striding_mx2 );
}

TEST_CASE("stride(case18)" * doctest::test_suite("view::stride"))
{
    STRIDE_SUBCASE( case18, x, nested_shape_a, nested_striding_a );
    STRIDE_SUBCASE( case18, x, nested_shape_f, nested_striding_f );
    STRIDE_SUBCASE( case18, x, nested_shape_h, nested_striding_h );
    STRIDE_SUBCASE( case18, x, nested_shape_v, nested_striding_v );

    STRIDE_SUBCASE( case18, x, nested_shape_ct, nested_striding_ct );
}

TEST_CASE("stride(case19)" * doctest::test_suite("view::stride"))
{
    STRIDE_SUBCASE( case19, x, shape, striding );
    STRIDE_SUBCASE( case19, x, shape_a, striding_a );
    STRIDE_SUBCASE( case19, x, shape_f, striding_f );
    STRIDE_SUBCASE( case19, x, shape_h, striding_h );
    STRIDE_SUBCASE( case19, x, shape_v, striding_v );

    STRIDE_SUBCASE( case19, x, shape_ct, striding_ct );
    STRIDE_SUBCASE( case19, x, shape_mx1, striding_mx1 );
    STRIDE_SUBCASE( case19, x, shape_mx2, striding_mx2 );
}

TEST_CASE("stride(case20)" * doctest::test_suite("view::stride"))
{
    STRIDE_SUBCASE( case20, x, shape, striding );
    STRIDE_SUBCASE( case20, x, shape_a, striding_a );
    STRIDE_SUBCASE( case20, x, shape_f, striding_f );
    STRIDE_SUBCASE( case20, x, shape_h, striding_h );
    STRIDE_SUBCASE( case20, x, shape_v, striding_v );

    STRIDE_SUBCASE( case20, x, shape_ct, striding_ct );
    STRIDE_SUBCASE( case20, x, shape_mx1, striding_mx1 );
    STRIDE_SUBCASE( case20, x, shape_mx2, striding_mx2 );
}

TEST_CASE("constexpr_stride(case1)" * doctest::test_suite("view::stride"))
{
    CONSTEXPR_STRIDE_SUBCASE( case1, x, shape, striding );
    CONSTEXPR_STRIDE_SUBCASE( case1, x, shape_a, striding_a );
    CONSTEXPR_STRIDE_SUBCASE( case1, x, shape_f, striding_f );
    CONSTEXPR_STRIDE_SUBCASE( case1, x, shape_h, striding_h );

    CONSTEXPR_STRIDE_SUBCASE( case1, x, shape_ct, striding_ct );
    CONSTEXPR_STRIDE_SUBCASE( case1, x, shape_mx1, striding_mx1 );
    CONSTEXPR_STRIDE_SUBCASE( case1, x, shape_mx2, striding_mx2 );
}

TEST_CASE("constexpr_stride(case2)" * doctest::test_suite("view::stride"))
{
    CONSTEXPR_STRIDE_SUBCASE( case2, x, shape, striding );
    CONSTEXPR_STRIDE_SUBCASE( case2, x, shape_a, striding_a );
    CONSTEXPR_STRIDE_SUBCASE( case2, x, shape_f, striding_f );
    CONSTEXPR_STRIDE_SUBCASE( case2, x, shape_h, striding_h );

    CONSTEXPR_STRIDE_SUBCASE( case2, x, shape_ct, striding_ct );
    CONSTEXPR_STRIDE_SUBCASE( case2, x, shape_mx1, striding_mx1 );
    CONSTEXPR_STRIDE_SUBCASE( case2, x, shape_mx2, striding_mx2 );
}

TEST_CASE("constexpr_stride(case3)" * doctest::test_suite("view::stride"))
{
    CONSTEXPR_STRIDE_SUBCASE( case3, x, shape, striding );
    CONSTEXPR_STRIDE_SUBCASE( case3, x, shape_a, striding_a );
    CONSTEXPR_STRIDE_SUBCASE( case3, x, shape_f, striding_f );
    CONSTEXPR_STRIDE_SUBCASE( case3, x, shape_h, striding_h );

    CONSTEXPR_STRIDE_SUBCASE( case3, x, shape_ct, striding_ct );
    CONSTEXPR_STRIDE_SUBCASE( case3, x, shape_mx1, striding_mx1 );
    CONSTEXPR_STRIDE_SUBCASE( case3, x, shape_mx2, striding_mx2 );
}

TEST_CASE("constexpr_stride(case4)" * doctest::test_suite("view::stride"))
{
    CONSTEXPR_STRIDE_SUBCASE( case4, x, nested_shape_a, nested_striding_a );
    CONSTEXPR_STRIDE_SUBCASE( case4, x, nested_shape_f, nested_striding_f );
    CONSTEXPR_STRIDE_SUBCASE( case4, x, nested_shape_h, nested_striding_h );

    CONSTEXPR_STRIDE_SUBCASE( case4, x, nested_shape_ct, nested_striding_ct );
}

TEST_CASE("constexpr_stride(case5)" * doctest::test_suite("view::stride"))
{
    CONSTEXPR_STRIDE_SUBCASE( case5, x, shape, striding );
    CONSTEXPR_STRIDE_SUBCASE( case5, x, shape_a, striding_a );
    CONSTEXPR_STRIDE_SUBCASE( case5, x, shape_f, striding_f );
    CONSTEXPR_STRIDE_SUBCASE( case5, x, shape_h, striding_h );

    CONSTEXPR_STRIDE_SUBCASE( case5, x, shape_ct, striding_ct );
    CONSTEXPR_STRIDE_SUBCASE( case5, x, shape_mx1, striding_mx1 );
    CONSTEXPR_STRIDE_SUBCASE( case5, x, shape_mx2, striding_mx2 );
}

TEST_CASE("constexpr_stride(case6)" * doctest::test_suite("view::stride"))
{
    CONSTEXPR_STRIDE_SUBCASE( case6, x, shape, striding );
    CONSTEXPR_STRIDE_SUBCASE( case6, x, shape_a, striding_a );
    CONSTEXPR_STRIDE_SUBCASE( case6, x, shape_f, striding_f );
    CONSTEXPR_STRIDE_SUBCASE( case6, x, shape_h, striding_h );

    CONSTEXPR_STRIDE_SUBCASE( case6, x, shape_ct, striding_ct );
    CONSTEXPR_STRIDE_SUBCASE( case6, x, shape_mx1, striding_mx1 );
    CONSTEXPR_STRIDE_SUBCASE( case6, x, shape_mx2, striding_mx2 );
}