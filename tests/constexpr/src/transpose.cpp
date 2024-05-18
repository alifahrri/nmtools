#define NMTOOLS_CONSTEXPR_CAST_ARRAYS_EXTRA(name) \
constexpr inline auto name##_cs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_fb); \
constexpr inline auto name##_cs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_hb); \
constexpr inline auto name##_fs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_fs_fb); \
constexpr inline auto name##_fs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_fs_hb); \
constexpr inline auto name##_hs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_hs_fb); \
constexpr inline auto name##_hs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_hs_hb);

#include "nmtools/array/array/transpose.hpp"
#include "nmtools/constants.hpp"
#include "nmtools/testing/data/constexpr/transpose.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;

#define CONSTEXPR_TRANSPOSE_SUBCASE(case_name, array, axes) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS( constexpr_transpose, case_name ); \
    constexpr auto array = na::transpose(args::array, args::axes); \
    NMTOOLS_STATIC_ASSERT_CLOSE( array, expect::expected ); \
}

TEST_CASE("transpose(case1)" * doctest::test_suite("array::constexpr_transpose"))
{
    CONSTEXPR_TRANSPOSE_SUBCASE( case1, array, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case1, array_a, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case1, array_f, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case1, array_h, axes_a );

    CONSTEXPR_TRANSPOSE_SUBCASE( case1, array_cs_fb, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case1, array_cs_hb, axes_a );

    CONSTEXPR_TRANSPOSE_SUBCASE( case1, array_fs_fb, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case1, array_fs_hb, axes_a );

    CONSTEXPR_TRANSPOSE_SUBCASE( case1, array_hs_fb, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case1, array_hs_hb, axes_a );
}

TEST_CASE("transpose(case2)" * doctest::test_suite("array::constexpr_transpose"))
{
    CONSTEXPR_TRANSPOSE_SUBCASE( case2, array, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case2, array_a, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case2, array_f, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case2, array_h, axes_a );

    CONSTEXPR_TRANSPOSE_SUBCASE( case2, array_cs_fb, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case2, array_cs_hb, axes_a );

    CONSTEXPR_TRANSPOSE_SUBCASE( case2, array_fs_fb, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case2, array_fs_hb, axes_a );

    CONSTEXPR_TRANSPOSE_SUBCASE( case2, array_hs_fb, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case2, array_hs_hb, axes_a );
}

TEST_CASE("transpose(case3)" * doctest::test_suite("array::constexpr_transpose"))
{
    CONSTEXPR_TRANSPOSE_SUBCASE( case3, array, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case3, array_a, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case3, array_f, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case3, array_h, axes_a );

    CONSTEXPR_TRANSPOSE_SUBCASE( case3, array_cs_fb, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case3, array_cs_hb, axes_a );

    CONSTEXPR_TRANSPOSE_SUBCASE( case3, array_fs_fb, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case3, array_fs_hb, axes_a );

    CONSTEXPR_TRANSPOSE_SUBCASE( case3, array_hs_fb, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case3, array_hs_hb, axes_a );
}

TEST_CASE("transpose(case4)" * doctest::test_suite("array::constexpr_transpose"))
{
    CONSTEXPR_TRANSPOSE_SUBCASE( case4, array, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case4, array_a, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case4, array_f, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case4, array_h, axes_a );

    CONSTEXPR_TRANSPOSE_SUBCASE( case4, array_cs_fb, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case4, array_cs_hb, axes_a );

    CONSTEXPR_TRANSPOSE_SUBCASE( case4, array_fs_fb, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case4, array_fs_hb, axes_a );

    CONSTEXPR_TRANSPOSE_SUBCASE( case4, array_hs_fb, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case4, array_hs_hb, axes_a );
}

TEST_CASE("transpose(case5)" * doctest::test_suite("array::constexpr_transpose"))
{
    CONSTEXPR_TRANSPOSE_SUBCASE( case5, array, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case5, array_a, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case5, array_f, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case5, array_h, axes_a );

    CONSTEXPR_TRANSPOSE_SUBCASE( case5, array_cs_fb, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case5, array_cs_hb, axes_a );

    CONSTEXPR_TRANSPOSE_SUBCASE( case5, array_fs_fb, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case5, array_fs_hb, axes_a );

    CONSTEXPR_TRANSPOSE_SUBCASE( case5, array_hs_fb, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case5, array_hs_hb, axes_a );
}

TEST_CASE("transpose(case6)" * doctest::test_suite("array::constexpr_transpose"))
{
    CONSTEXPR_TRANSPOSE_SUBCASE( case6, array, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case6, array_a, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case6, array_f, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case6, array_h, axes_a );

    CONSTEXPR_TRANSPOSE_SUBCASE( case6, array_cs_fb, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case6, array_cs_hb, axes_a );

    CONSTEXPR_TRANSPOSE_SUBCASE( case6, array_fs_fb, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case6, array_fs_hb, axes_a );

    CONSTEXPR_TRANSPOSE_SUBCASE( case6, array_hs_fb, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case6, array_hs_hb, axes_a );
}

TEST_CASE("transpose(case7)" * doctest::test_suite("array::constexpr_transpose"))
{
    CONSTEXPR_TRANSPOSE_SUBCASE( case7, array, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case7, array_a, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case7, array_f, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case7, array_h, axes_a );

    CONSTEXPR_TRANSPOSE_SUBCASE( case7, array_cs_fb, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case7, array_cs_hb, axes_a );

    CONSTEXPR_TRANSPOSE_SUBCASE( case7, array_fs_fb, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case7, array_fs_hb, axes_a );

    CONSTEXPR_TRANSPOSE_SUBCASE( case7, array_hs_fb, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case7, array_hs_hb, axes_a );
}

TEST_CASE("transpose(case8)" * doctest::test_suite("array::constexpr_transpose"))
{
    CONSTEXPR_TRANSPOSE_SUBCASE( case8, array, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case8, array_a, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case8, array_f, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case8, array_h, axes_a );

    CONSTEXPR_TRANSPOSE_SUBCASE( case8, array_cs_fb, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case8, array_cs_hb, axes_a );

    CONSTEXPR_TRANSPOSE_SUBCASE( case8, array_fs_fb, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case8, array_fs_hb, axes_a );

    CONSTEXPR_TRANSPOSE_SUBCASE( case8, array_hs_fb, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case8, array_hs_hb, axes_a );
}

TEST_CASE("transpose(case9)" * doctest::test_suite("array::constexpr_transpose"))
{
    CONSTEXPR_TRANSPOSE_SUBCASE( case9, array, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case9, array_a, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case9, array_f, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case9, array_h, axes_a );

    CONSTEXPR_TRANSPOSE_SUBCASE( case9, array_cs_fb, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case9, array_cs_hb, axes_a );

    CONSTEXPR_TRANSPOSE_SUBCASE( case9, array_fs_fb, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case9, array_fs_hb, axes_a );

    CONSTEXPR_TRANSPOSE_SUBCASE( case9, array_hs_fb, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case9, array_hs_hb, axes_a );
}

TEST_CASE("transpose(case10)" * doctest::test_suite("array::transpose"))
{
    CONSTEXPR_TRANSPOSE_SUBCASE( case10, array, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case10, array_a, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case10, array_f, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case10, array_h, axes_a );

    CONSTEXPR_TRANSPOSE_SUBCASE( case10, array_cs_fb, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case10, array_cs_hb, axes_a );

    CONSTEXPR_TRANSPOSE_SUBCASE( case10, array_fs_fb, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case10, array_fs_hb, axes_a );

    CONSTEXPR_TRANSPOSE_SUBCASE( case10, array_hs_fb, axes_a );
    CONSTEXPR_TRANSPOSE_SUBCASE( case10, array_hs_hb, axes_a );
}