#define NMTOOLS_CONSTEXPR_CAST_ARRAYS_EXTRA(name) \
constexpr inline auto name##_cs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_fb); \
constexpr inline auto name##_cs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_hb); \
constexpr inline auto name##_fs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_fs_fb); \
constexpr inline auto name##_fs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_fs_hb); \
constexpr inline auto name##_hs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_hs_fb); \
constexpr inline auto name##_hs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_hs_hb); \
constexpr inline auto name##_ls_fb = nmtools::cast(name, nmtools::array::kind::ndarray_ls_fb); \
constexpr inline auto name##_ls_hb = nmtools::cast(name, nmtools::array::kind::ndarray_ls_hb);

#include "nmtools/array/array/pad.hpp"
#include "nmtools/testing/data/constexpr/pad.hpp"
#include "nmtools/testing/doctest.hpp"

#define CONSTEXPR_PAD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, constexpr_pad, case_name); \
    using namespace args; \
    constexpr auto result = nmtools::array::pad(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("constexpr_pad(case1)" * doctest::test_suite("array::pad"))
{
    CONSTEXPR_PAD_SUBCASE( case1, array, pad_width_ct );
    CONSTEXPR_PAD_SUBCASE( case1, array_a, pad_width_ct );
    CONSTEXPR_PAD_SUBCASE( case1, array_f, pad_width_ct );

    CONSTEXPR_PAD_SUBCASE( case1, array_cs_fb, pad_width_ct );
    CONSTEXPR_PAD_SUBCASE( case1, array_cs_hb, pad_width_ct );

    // NOTE: padding may increase the shape & size, can't know the upper bound if only src size is known
    #if 0
    CONSTEXPR_PAD_SUBCASE( case1, array_fs_fb, pad_width_ct );
    CONSTEXPR_PAD_SUBCASE( case1, array_fs_hb, pad_width_ct );

    CONSTEXPR_PAD_SUBCASE( case1, array_hs_fb, pad_width_ct );
    CONSTEXPR_PAD_SUBCASE( case1, array_hs_hb, pad_width_ct );
    #endif

    CONSTEXPR_PAD_SUBCASE( case1, array_ls_fb, pad_width_ct );
    CONSTEXPR_PAD_SUBCASE( case1, array_ls_hb, pad_width_ct );

    CONSTEXPR_PAD_SUBCASE( case1, array_cs_fb, pad_width_cl );
    CONSTEXPR_PAD_SUBCASE( case1, array_cs_hb, pad_width_cl );

    CONSTEXPR_PAD_SUBCASE( case1, array_ls_fb, pad_width_cl );
    CONSTEXPR_PAD_SUBCASE( case1, array_ls_hb, pad_width_cl );
}

TEST_CASE("constexpr_pad(case2)" * doctest::test_suite("array::pad"))
{
    CONSTEXPR_PAD_SUBCASE( case2, array, pad_width_ct );
    CONSTEXPR_PAD_SUBCASE( case2, array_a, pad_width_ct );
    CONSTEXPR_PAD_SUBCASE( case2, array_f, pad_width_ct );

    CONSTEXPR_PAD_SUBCASE( case2, array_cs_fb, pad_width_ct );
    CONSTEXPR_PAD_SUBCASE( case2, array_cs_hb, pad_width_ct );

    CONSTEXPR_PAD_SUBCASE( case2, array_ls_fb, pad_width_ct );
    CONSTEXPR_PAD_SUBCASE( case2, array_ls_hb, pad_width_ct );

    CONSTEXPR_PAD_SUBCASE( case2, array_cs_fb, pad_width_cl );
    CONSTEXPR_PAD_SUBCASE( case2, array_cs_hb, pad_width_cl );

    CONSTEXPR_PAD_SUBCASE( case2, array_ls_fb, pad_width_cl );
    CONSTEXPR_PAD_SUBCASE( case2, array_ls_hb, pad_width_cl );
}

TEST_CASE("constexpr_pad(case3)" * doctest::test_suite("array::pad"))
{
    CONSTEXPR_PAD_SUBCASE( case3, array, pad_width_ct );
    CONSTEXPR_PAD_SUBCASE( case3, array_a, pad_width_ct );
    CONSTEXPR_PAD_SUBCASE( case3, array_f, pad_width_ct );

    CONSTEXPR_PAD_SUBCASE( case3, array_cs_fb, pad_width_ct );
    CONSTEXPR_PAD_SUBCASE( case3, array_cs_hb, pad_width_ct );

    CONSTEXPR_PAD_SUBCASE( case3, array_ls_fb, pad_width_ct );
    CONSTEXPR_PAD_SUBCASE( case3, array_ls_hb, pad_width_ct );

    CONSTEXPR_PAD_SUBCASE( case3, array_cs_fb, pad_width_cl );
    CONSTEXPR_PAD_SUBCASE( case3, array_cs_hb, pad_width_cl );

    CONSTEXPR_PAD_SUBCASE( case3, array_ls_fb, pad_width_cl );
    CONSTEXPR_PAD_SUBCASE( case3, array_ls_hb, pad_width_cl );
}

TEST_CASE("constexpr_pad(case4)" * doctest::test_suite("array::pad"))
{
    CONSTEXPR_PAD_SUBCASE( case4, array, pad_width_ct );
    CONSTEXPR_PAD_SUBCASE( case4, array_a, pad_width_ct );
    CONSTEXPR_PAD_SUBCASE( case4, array_f, pad_width_ct );

    CONSTEXPR_PAD_SUBCASE( case4, array_cs_fb, pad_width_ct );
    CONSTEXPR_PAD_SUBCASE( case4, array_cs_hb, pad_width_ct );

    CONSTEXPR_PAD_SUBCASE( case4, array_ls_fb, pad_width_ct );
    CONSTEXPR_PAD_SUBCASE( case4, array_ls_hb, pad_width_ct );

    CONSTEXPR_PAD_SUBCASE( case4, array_cs_fb, pad_width_cl );
    CONSTEXPR_PAD_SUBCASE( case4, array_cs_hb, pad_width_cl );

    CONSTEXPR_PAD_SUBCASE( case4, array_ls_fb, pad_width_cl );
    CONSTEXPR_PAD_SUBCASE( case4, array_ls_hb, pad_width_cl );
}

TEST_CASE("constexpr_pad(case5)" * doctest::test_suite("array::pad"))
{
    CONSTEXPR_PAD_SUBCASE( case5, array, pad_width_ct );
    CONSTEXPR_PAD_SUBCASE( case5, array_a, pad_width_ct );
    CONSTEXPR_PAD_SUBCASE( case5, array_f, pad_width_ct );

    CONSTEXPR_PAD_SUBCASE( case5, array_cs_fb, pad_width_ct );
    CONSTEXPR_PAD_SUBCASE( case5, array_cs_hb, pad_width_ct );

    CONSTEXPR_PAD_SUBCASE( case5, array_ls_fb, pad_width_ct );
    CONSTEXPR_PAD_SUBCASE( case5, array_ls_hb, pad_width_ct );

    CONSTEXPR_PAD_SUBCASE( case5, array_cs_fb, pad_width_cl );
    CONSTEXPR_PAD_SUBCASE( case5, array_cs_hb, pad_width_cl );

    CONSTEXPR_PAD_SUBCASE( case5, array_ls_fb, pad_width_cl );
    CONSTEXPR_PAD_SUBCASE( case5, array_ls_hb, pad_width_cl );
}