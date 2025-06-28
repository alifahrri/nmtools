#define NMTOOLS_CONSTEXPR_CAST_ARRAYS_EXTRA(name) \
constexpr inline auto name##_cs_fb = nmtools::cast(name, nmtools::kind::ndarray_cs_fb); \
constexpr inline auto name##_cs_hb = nmtools::cast(name, nmtools::kind::ndarray_cs_hb); \
constexpr inline auto name##_fs_fb = nmtools::cast(name, nmtools::kind::ndarray_fs_fb); \
constexpr inline auto name##_fs_hb = nmtools::cast(name, nmtools::kind::ndarray_fs_hb); \
constexpr inline auto name##_hs_fb = nmtools::cast(name, nmtools::kind::ndarray_hs_fb); \
constexpr inline auto name##_hs_hb = nmtools::cast(name, nmtools::kind::ndarray_hs_hb); \
constexpr inline auto name##_ls_fb = nmtools::cast(name, nmtools::kind::ndarray_ls_fb); \
constexpr inline auto name##_ls_hb = nmtools::cast(name, nmtools::kind::ndarray_ls_hb);

#include "nmtools/array/pad.hpp"
#include "nmtools/testing/data/constexpr/pad.hpp"
#include "nmtools/testing/doctest.hpp"

#define CONSTEXPR_PAD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, constexpr_pad, case_name); \
    using namespace args; \
    constexpr auto result = nmtools::pad2(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("constexpr_pad(case1)" * doctest::test_suite("array::pad2"))
{
    CONSTEXPR_PAD_SUBCASE( case1, array, pads_ct );
    CONSTEXPR_PAD_SUBCASE( case1, array_a, pads_ct );
    CONSTEXPR_PAD_SUBCASE( case1, array_f, pads_ct );

    CONSTEXPR_PAD_SUBCASE( case1, array_cs_fb, pads_ct );
    CONSTEXPR_PAD_SUBCASE( case1, array_cs_hb, pads_ct );

    // NOTE: padding may increase the shape & size, can't know the upper bound if only src size is known
    #if 0
    CONSTEXPR_PAD_SUBCASE( case1, array_fs_fb, pads_ct );
    CONSTEXPR_PAD_SUBCASE( case1, array_fs_hb, pads_ct );

    CONSTEXPR_PAD_SUBCASE( case1, array_hs_fb, pads_ct );
    CONSTEXPR_PAD_SUBCASE( case1, array_hs_hb, pads_ct );
    #endif

    CONSTEXPR_PAD_SUBCASE( case1, array_ls_fb, pads_ct );
    CONSTEXPR_PAD_SUBCASE( case1, array_ls_hb, pads_ct );

    CONSTEXPR_PAD_SUBCASE( case1, array_cs_fb, pads_cl );
    CONSTEXPR_PAD_SUBCASE( case1, array_cs_hb, pads_cl );

    CONSTEXPR_PAD_SUBCASE( case1, array_ls_fb, pads_cl );
    CONSTEXPR_PAD_SUBCASE( case1, array_ls_hb, pads_cl );
}

TEST_CASE("constexpr_pad(case2)" * doctest::test_suite("array::pad2"))
{
    CONSTEXPR_PAD_SUBCASE( case2, array, pads_ct );
    CONSTEXPR_PAD_SUBCASE( case2, array_a, pads_ct );
    CONSTEXPR_PAD_SUBCASE( case2, array_f, pads_ct );

    CONSTEXPR_PAD_SUBCASE( case2, array_cs_fb, pads_ct );
    CONSTEXPR_PAD_SUBCASE( case2, array_cs_hb, pads_ct );

    CONSTEXPR_PAD_SUBCASE( case2, array_ls_fb, pads_ct );
    CONSTEXPR_PAD_SUBCASE( case2, array_ls_hb, pads_ct );

    CONSTEXPR_PAD_SUBCASE( case2, array_cs_fb, pads_cl );
    CONSTEXPR_PAD_SUBCASE( case2, array_cs_hb, pads_cl );

    CONSTEXPR_PAD_SUBCASE( case2, array_ls_fb, pads_cl );
    CONSTEXPR_PAD_SUBCASE( case2, array_ls_hb, pads_cl );
}

TEST_CASE("constexpr_pad(case3)" * doctest::test_suite("array::pad2"))
{
    CONSTEXPR_PAD_SUBCASE( case3, array, pads_ct );
    CONSTEXPR_PAD_SUBCASE( case3, array_a, pads_ct );
    CONSTEXPR_PAD_SUBCASE( case3, array_f, pads_ct );

    CONSTEXPR_PAD_SUBCASE( case3, array_cs_fb, pads_ct );
    CONSTEXPR_PAD_SUBCASE( case3, array_cs_hb, pads_ct );

    CONSTEXPR_PAD_SUBCASE( case3, array_ls_fb, pads_ct );
    CONSTEXPR_PAD_SUBCASE( case3, array_ls_hb, pads_ct );

    CONSTEXPR_PAD_SUBCASE( case3, array_cs_fb, pads_cl );
    CONSTEXPR_PAD_SUBCASE( case3, array_cs_hb, pads_cl );

    CONSTEXPR_PAD_SUBCASE( case3, array_ls_fb, pads_cl );
    CONSTEXPR_PAD_SUBCASE( case3, array_ls_hb, pads_cl );
}

TEST_CASE("constexpr_pad(case4)" * doctest::test_suite("array::pad2"))
{
    CONSTEXPR_PAD_SUBCASE( case4, array, pads_ct );
    CONSTEXPR_PAD_SUBCASE( case4, array_a, pads_ct );
    CONSTEXPR_PAD_SUBCASE( case4, array_f, pads_ct );

    CONSTEXPR_PAD_SUBCASE( case4, array_cs_fb, pads_ct );
    CONSTEXPR_PAD_SUBCASE( case4, array_cs_hb, pads_ct );

    CONSTEXPR_PAD_SUBCASE( case4, array_ls_fb, pads_ct );
    CONSTEXPR_PAD_SUBCASE( case4, array_ls_hb, pads_ct );

    CONSTEXPR_PAD_SUBCASE( case4, array_cs_fb, pads_cl );
    CONSTEXPR_PAD_SUBCASE( case4, array_cs_hb, pads_cl );

    CONSTEXPR_PAD_SUBCASE( case4, array_ls_fb, pads_cl );
    CONSTEXPR_PAD_SUBCASE( case4, array_ls_hb, pads_cl );
}

TEST_CASE("constexpr_pad(case5)" * doctest::test_suite("array::pad2"))
{
    CONSTEXPR_PAD_SUBCASE( case5, array, pads_ct );
    CONSTEXPR_PAD_SUBCASE( case5, array_a, pads_ct );
    CONSTEXPR_PAD_SUBCASE( case5, array_f, pads_ct );

    CONSTEXPR_PAD_SUBCASE( case5, array_cs_fb, pads_ct );
    CONSTEXPR_PAD_SUBCASE( case5, array_cs_hb, pads_ct );

    CONSTEXPR_PAD_SUBCASE( case5, array_ls_fb, pads_ct );
    CONSTEXPR_PAD_SUBCASE( case5, array_ls_hb, pads_ct );

    CONSTEXPR_PAD_SUBCASE( case5, array_cs_fb, pads_cl );
    CONSTEXPR_PAD_SUBCASE( case5, array_cs_hb, pads_cl );

    CONSTEXPR_PAD_SUBCASE( case5, array_ls_fb, pads_cl );
    CONSTEXPR_PAD_SUBCASE( case5, array_ls_hb, pads_cl );
}