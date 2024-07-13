#define NMTOOLS_CAST_ARRAYS_NESTED_VEC(...)

#if defined(NMTOOLS_TESTING_GENERIC_NDARRAY) && defined(NMTOOLS_BUILD_CONSTEXPR_TESTS)
#define NMTOOLS_CONSTEXPR_CAST_ARRAYS_EXTRA(name) \
constexpr inline auto name##_cs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_fb); \
constexpr inline auto name##_cs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_hb); \
constexpr inline auto name##_fs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_fs_fb); \
constexpr inline auto name##_fs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_fs_hb); \
constexpr inline auto name##_hs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_hs_fb); \
constexpr inline auto name##_hs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_hs_hb); \
constexpr inline auto name##_ls_fb = nmtools::cast(name, nmtools::array::kind::ndarray_ls_fb); \
constexpr inline auto name##_ls_hb = nmtools::cast(name, nmtools::array::kind::ndarray_ls_hb);
#endif

#include "nmtools/array/array/conv.hpp"
#include "nmtools/testing/data/constexpr/conv2d.hpp"
#include "nmtools/testing/doctest.hpp"

using nmtools::None;

#define CONSTEXPR_CONV2D_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, constexpr_conv2d, case_name); \
    using namespace args; \
    constexpr auto result = nmtools::array::conv2d( __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("constexpr_conv2d(case1)" * doctest::test_suite("array::conv2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_CONV2D_SUBCASE( case1, input, weight, None, stride_ct );
    CONSTEXPR_CONV2D_SUBCASE( case1, input_a, weight_a, None, stride_ct );
    CONSTEXPR_CONV2D_SUBCASE( case1, input_f, weight_f, None, stride_ct );
    CONSTEXPR_CONV2D_SUBCASE( case1, input_h, weight_h, None, stride_ct );
    #else
    CONSTEXPR_CONV2D_SUBCASE( case1, input_cs_fb, weight_cs_fb, None, stride_ct );
    CONSTEXPR_CONV2D_SUBCASE( case1, input_cs_hb, weight_cs_hb, None, stride_ct );

    CONSTEXPR_CONV2D_SUBCASE( case1, input_fs_fb, weight_fs_fb, None, stride_ct );
    CONSTEXPR_CONV2D_SUBCASE( case1, input_fs_hb, weight_fs_hb, None, stride_ct );

    CONSTEXPR_CONV2D_SUBCASE( case1, input_hs_fb, weight_hs_fb, None, stride_ct );
    CONSTEXPR_CONV2D_SUBCASE( case1, input_hs_hb, weight_hs_hb, None, stride_ct );

    CONSTEXPR_CONV2D_SUBCASE( case1, input_ls_fb, weight_ls_fb, None, stride_ct );
    CONSTEXPR_CONV2D_SUBCASE( case1, input_ls_hb, weight_ls_hb, None, stride_ct );

    CONSTEXPR_CONV2D_SUBCASE( case1, input_cs_fb, weight_cs_fb, None, stride_cl );
    CONSTEXPR_CONV2D_SUBCASE( case1, input_cs_hb, weight_cs_hb, None, stride_cl );

    CONSTEXPR_CONV2D_SUBCASE( case1, input_fs_fb, weight_fs_fb, None, stride_cl );
    CONSTEXPR_CONV2D_SUBCASE( case1, input_fs_hb, weight_fs_hb, None, stride_cl );

    CONSTEXPR_CONV2D_SUBCASE( case1, input_hs_fb, weight_hs_fb, None, stride_cl );
    CONSTEXPR_CONV2D_SUBCASE( case1, input_hs_hb, weight_hs_hb, None, stride_cl );

    CONSTEXPR_CONV2D_SUBCASE( case1, input_ls_fb, weight_ls_fb, None, stride_cl );
    CONSTEXPR_CONV2D_SUBCASE( case1, input_ls_hb, weight_ls_hb, None, stride_cl );

    //////////////////////////////////////////////////////////////////////////////

    CONSTEXPR_CONV2D_SUBCASE( case1, input_fs_fb, weight_cs_fb, None, stride_cl );
    CONSTEXPR_CONV2D_SUBCASE( case1, input_fs_hb, weight_cs_hb, None, stride_cl );

    CONSTEXPR_CONV2D_SUBCASE( case1, input_hs_fb, weight_cs_fb, None, stride_cl );
    CONSTEXPR_CONV2D_SUBCASE( case1, input_hs_hb, weight_cs_hb, None, stride_cl );

    CONSTEXPR_CONV2D_SUBCASE( case1, input_ls_fb, weight_cs_fb, None, stride_cl );
    CONSTEXPR_CONV2D_SUBCASE( case1, input_ls_hb, weight_cs_hb, None, stride_cl );

    CONSTEXPR_CONV2D_SUBCASE( case1, input_cs_fb, weight_fs_fb, None, stride_cl );
    CONSTEXPR_CONV2D_SUBCASE( case1, input_cs_hb, weight_fs_hb, None, stride_cl );

    CONSTEXPR_CONV2D_SUBCASE( case1, input_hs_fb, weight_fs_fb, None, stride_cl );
    CONSTEXPR_CONV2D_SUBCASE( case1, input_hs_hb, weight_fs_hb, None, stride_cl );

    CONSTEXPR_CONV2D_SUBCASE( case1, input_ls_fb, weight_fs_fb, None, stride_cl );
    CONSTEXPR_CONV2D_SUBCASE( case1, input_ls_hb, weight_fs_hb, None, stride_cl );

    CONSTEXPR_CONV2D_SUBCASE( case1, input_cs_fb, weight_ls_fb, None, stride_cl );
    CONSTEXPR_CONV2D_SUBCASE( case1, input_cs_hb, weight_ls_hb, None, stride_cl );

    CONSTEXPR_CONV2D_SUBCASE( case1, input_fs_fb, weight_ls_fb, None, stride_cl );
    CONSTEXPR_CONV2D_SUBCASE( case1, input_fs_hb, weight_ls_hb, None, stride_cl );

    CONSTEXPR_CONV2D_SUBCASE( case1, input_hs_fb, weight_ls_fb, None, stride_cl );
    CONSTEXPR_CONV2D_SUBCASE( case1, input_hs_hb, weight_ls_hb, None, stride_cl );

    CONSTEXPR_CONV2D_SUBCASE( case1, input_cs_fb, weight_hs_fb, None, stride_cl );
    CONSTEXPR_CONV2D_SUBCASE( case1, input_cs_hb, weight_hs_hb, None, stride_cl );

    CONSTEXPR_CONV2D_SUBCASE( case1, input_fs_fb, weight_hs_fb, None, stride_cl );
    CONSTEXPR_CONV2D_SUBCASE( case1, input_fs_hb, weight_hs_hb, None, stride_cl );

    CONSTEXPR_CONV2D_SUBCASE( case1, input_ls_fb, weight_hs_fb, None, stride_cl );
    CONSTEXPR_CONV2D_SUBCASE( case1, input_ls_hb, weight_hs_hb, None, stride_cl );
    #endif
}

TEST_CASE("constexpr_conv2d(case2)" * doctest::test_suite("array::conv2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_CONV2D_SUBCASE( case2, input, weight, None, stride_ct );
    CONSTEXPR_CONV2D_SUBCASE( case2, input_a, weight_a, None, stride_ct );
    CONSTEXPR_CONV2D_SUBCASE( case2, input_f, weight_f, None, stride_ct );
    CONSTEXPR_CONV2D_SUBCASE( case2, input_h, weight_h, None, stride_ct );
    #else
    CONSTEXPR_CONV2D_SUBCASE( case2, input_cs_fb, weight_cs_fb, None, stride_ct );
    CONSTEXPR_CONV2D_SUBCASE( case2, input_cs_hb, weight_cs_hb, None, stride_ct );

    CONSTEXPR_CONV2D_SUBCASE( case2, input_fs_fb, weight_fs_fb, None, stride_ct );
    CONSTEXPR_CONV2D_SUBCASE( case2, input_fs_hb, weight_fs_hb, None, stride_ct );

    CONSTEXPR_CONV2D_SUBCASE( case2, input_hs_fb, weight_hs_fb, None, stride_ct );
    CONSTEXPR_CONV2D_SUBCASE( case2, input_hs_hb, weight_hs_hb, None, stride_ct );

    CONSTEXPR_CONV2D_SUBCASE( case2, input_ls_fb, weight_ls_fb, None, stride_ct );
    CONSTEXPR_CONV2D_SUBCASE( case2, input_ls_hb, weight_ls_hb, None, stride_ct );
    #endif
}

TEST_CASE("constexpr_conv2d(case3)" * doctest::test_suite("array::conv2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_CONV2D_SUBCASE( case3, input, weight, None, stride_ct );
    CONSTEXPR_CONV2D_SUBCASE( case3, input_a, weight_a, None, stride_ct );
    CONSTEXPR_CONV2D_SUBCASE( case3, input_f, weight_f, None, stride_ct );
    CONSTEXPR_CONV2D_SUBCASE( case3, input_h, weight_h, None, stride_ct );
    #else
    CONSTEXPR_CONV2D_SUBCASE( case3, input_cs_fb, weight_cs_fb, None, stride_ct );
    CONSTEXPR_CONV2D_SUBCASE( case3, input_cs_hb, weight_cs_hb, None, stride_ct );

    CONSTEXPR_CONV2D_SUBCASE( case3, input_fs_fb, weight_fs_fb, None, stride_ct );
    CONSTEXPR_CONV2D_SUBCASE( case3, input_fs_hb, weight_fs_hb, None, stride_ct );

    CONSTEXPR_CONV2D_SUBCASE( case3, input_hs_fb, weight_hs_fb, None, stride_ct );
    CONSTEXPR_CONV2D_SUBCASE( case3, input_hs_hb, weight_hs_hb, None, stride_ct );

    CONSTEXPR_CONV2D_SUBCASE( case3, input_ls_fb, weight_ls_fb, None, stride_ct );
    CONSTEXPR_CONV2D_SUBCASE( case3, input_ls_hb, weight_ls_hb, None, stride_ct );
    #endif
}

TEST_CASE("constexpr_conv2d(case4)" * doctest::test_suite("array::conv2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_CONV2D_SUBCASE( case4, input, weight, None, stride_ct );
    CONSTEXPR_CONV2D_SUBCASE( case4, input_a, weight_a, None, stride_ct );
    CONSTEXPR_CONV2D_SUBCASE( case4, input_f, weight_f, None, stride_ct );
    CONSTEXPR_CONV2D_SUBCASE( case4, input_h, weight_h, None, stride_ct );
    #else
    CONSTEXPR_CONV2D_SUBCASE( case4, input_cs_fb, weight_cs_fb, None, stride_ct );
    CONSTEXPR_CONV2D_SUBCASE( case4, input_cs_hb, weight_cs_hb, None, stride_ct );

    CONSTEXPR_CONV2D_SUBCASE( case4, input_fs_fb, weight_fs_fb, None, stride_ct );
    CONSTEXPR_CONV2D_SUBCASE( case4, input_fs_hb, weight_fs_hb, None, stride_ct );

    CONSTEXPR_CONV2D_SUBCASE( case4, input_hs_fb, weight_hs_fb, None, stride_ct );
    CONSTEXPR_CONV2D_SUBCASE( case4, input_hs_hb, weight_hs_hb, None, stride_ct );

    CONSTEXPR_CONV2D_SUBCASE( case4, input_ls_fb, weight_ls_fb, None, stride_ct );
    CONSTEXPR_CONV2D_SUBCASE( case4, input_ls_hb, weight_ls_hb, None, stride_ct );
    #endif
}