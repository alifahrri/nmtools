#define NMTOOLS_CAST_ARRAYS_NESTED_VEC(...)

#if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
#define NMTOOLS_CAST_ARRAYS_EXTRA(name) \
inline auto name##_cs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_fb); \
inline auto name##_cs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_hb); \
inline auto name##_cs_db = nmtools::cast(name, nmtools::array::kind::ndarray_cs_db); \
inline auto name##_fs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_fs_fb); \
inline auto name##_fs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_fs_hb); \
inline auto name##_fs_db = nmtools::cast(name, nmtools::array::kind::ndarray_fs_db); \
inline auto name##_hs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_hs_fb); \
inline auto name##_hs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_hs_hb); \
inline auto name##_hs_db = nmtools::cast(name, nmtools::array::kind::ndarray_hs_db); \
inline auto name##_ds_fb = nmtools::cast(name, nmtools::array::kind::ndarray_ds_fb); \
inline auto name##_ds_hb = nmtools::cast(name, nmtools::array::kind::ndarray_ds_hb); \
inline auto name##_ds_db = nmtools::cast(name, nmtools::array::kind::ndarray_ds_db); \
inline auto name##_ls_fb = nmtools::cast(name, nmtools::array::kind::ndarray_ls_fb); \
inline auto name##_ls_hb = nmtools::cast(name, nmtools::array::kind::ndarray_ls_hb); \
inline auto name##_ls_db = nmtools::cast(name, nmtools::array::kind::ndarray_ls_db);
#endif

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
#include "nmtools/testing/data/array/conv.hpp"
#include "nmtools/testing/doctest.hpp"

#define CONV2D_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, conv2d, case_name); \
    using namespace args; \
    auto result = nmtools::array::conv2d(__VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

using nmtools::None;

#define CONSTEXPR_CONV2D_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, constexpr_conv2d, case_name); \
    using namespace args; \
    constexpr auto result = nmtools::view::conv2d( __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#ifndef NMTOOLS_BUILD_CONSTEXPR_TESTS

TEST_CASE("conv2d(case1)" * doctest::test_suite("array::conv2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONV2D_SUBCASE( case1, input, weight );
    CONV2D_SUBCASE( case1, input_a, weight_a );
    CONV2D_SUBCASE( case1, input_f, weight_f );
    CONV2D_SUBCASE( case1, input_h, weight_h );
    CONV2D_SUBCASE( case1, input_d, weight_d );

    #else
    CONV2D_SUBCASE( case1, input_cs_fb, weight_cs_fb );
    CONV2D_SUBCASE( case1, input_cs_hb, weight_cs_hb );
    CONV2D_SUBCASE( case1, input_cs_db, weight_cs_db );

    CONV2D_SUBCASE( case1, input_fs_fb, weight_fs_fb );
    CONV2D_SUBCASE( case1, input_fs_hb, weight_fs_hb );
    CONV2D_SUBCASE( case1, input_fs_db, weight_fs_db );

    CONV2D_SUBCASE( case1, input_hs_fb, weight_hs_fb );
    CONV2D_SUBCASE( case1, input_hs_hb, weight_hs_hb );
    CONV2D_SUBCASE( case1, input_hs_db, weight_hs_db );

    CONV2D_SUBCASE( case1, input_ds_fb, weight_ds_fb );
    CONV2D_SUBCASE( case1, input_ds_hb, weight_ds_hb );
    CONV2D_SUBCASE( case1, input_ds_db, weight_ds_db );

    CONV2D_SUBCASE( case1, input_ls_fb, weight_ls_fb );
    CONV2D_SUBCASE( case1, input_ls_hb, weight_ls_hb );
    CONV2D_SUBCASE( case1, input_ls_db, weight_ls_db );

    CONV2D_SUBCASE( case1, input_fs_fb, weight_cs_fb );
    CONV2D_SUBCASE( case1, input_fs_hb, weight_cs_hb );
    CONV2D_SUBCASE( case1, input_fs_db, weight_cs_db );

    CONV2D_SUBCASE( case1, input_hs_fb, weight_cs_fb );
    CONV2D_SUBCASE( case1, input_hs_hb, weight_cs_hb );
    CONV2D_SUBCASE( case1, input_hs_db, weight_cs_db );

    CONV2D_SUBCASE( case1, input_ds_fb, weight_cs_fb );
    CONV2D_SUBCASE( case1, input_ds_hb, weight_cs_hb );
    CONV2D_SUBCASE( case1, input_ds_db, weight_cs_db );

    CONV2D_SUBCASE( case1, input_ls_fb, weight_cs_fb );
    CONV2D_SUBCASE( case1, input_ls_hb, weight_cs_hb );
    CONV2D_SUBCASE( case1, input_ls_db, weight_cs_db );

    CONV2D_SUBCASE( case1, input_cs_fb, weight_fs_fb );
    CONV2D_SUBCASE( case1, input_cs_hb, weight_fs_hb );
    CONV2D_SUBCASE( case1, input_cs_db, weight_fs_db );

    CONV2D_SUBCASE( case1, input_hs_fb, weight_fs_fb );
    CONV2D_SUBCASE( case1, input_hs_hb, weight_fs_hb );
    CONV2D_SUBCASE( case1, input_hs_db, weight_fs_db );

    CONV2D_SUBCASE( case1, input_ds_fb, weight_fs_fb );
    CONV2D_SUBCASE( case1, input_ds_hb, weight_fs_hb );
    CONV2D_SUBCASE( case1, input_ds_db, weight_fs_db );

    CONV2D_SUBCASE( case1, input_ls_fb, weight_fs_fb );
    CONV2D_SUBCASE( case1, input_ls_hb, weight_fs_hb );
    CONV2D_SUBCASE( case1, input_ls_db, weight_fs_db );

    CONV2D_SUBCASE( case1, input_cs_fb, weight_hs_fb );
    CONV2D_SUBCASE( case1, input_cs_hb, weight_hs_hb );
    CONV2D_SUBCASE( case1, input_cs_db, weight_hs_db );

    CONV2D_SUBCASE( case1, input_fs_fb, weight_hs_fb );
    CONV2D_SUBCASE( case1, input_fs_hb, weight_hs_hb );
    CONV2D_SUBCASE( case1, input_fs_db, weight_hs_db );

    CONV2D_SUBCASE( case1, input_ds_fb, weight_hs_fb );
    CONV2D_SUBCASE( case1, input_ds_hb, weight_hs_hb );
    CONV2D_SUBCASE( case1, input_ds_db, weight_hs_db );

    CONV2D_SUBCASE( case1, input_ls_fb, weight_hs_fb );
    CONV2D_SUBCASE( case1, input_ls_hb, weight_hs_hb );
    CONV2D_SUBCASE( case1, input_ls_db, weight_hs_db );

    CONV2D_SUBCASE( case1, input_cs_fb, weight_ds_fb );
    CONV2D_SUBCASE( case1, input_cs_hb, weight_ds_hb );
    CONV2D_SUBCASE( case1, input_cs_db, weight_ds_db );

    CONV2D_SUBCASE( case1, input_fs_fb, weight_ds_fb );
    CONV2D_SUBCASE( case1, input_fs_hb, weight_ds_hb );
    CONV2D_SUBCASE( case1, input_fs_db, weight_ds_db );

    CONV2D_SUBCASE( case1, input_hs_fb, weight_ds_fb );
    CONV2D_SUBCASE( case1, input_hs_hb, weight_ds_hb );
    CONV2D_SUBCASE( case1, input_hs_db, weight_ds_db );

    CONV2D_SUBCASE( case1, input_ls_fb, weight_ds_fb );
    CONV2D_SUBCASE( case1, input_ls_hb, weight_ds_hb );
    CONV2D_SUBCASE( case1, input_ls_db, weight_ds_db );

    CONV2D_SUBCASE( case1, input_cs_fb, weight_ls_fb );
    CONV2D_SUBCASE( case1, input_cs_hb, weight_ls_hb );
    CONV2D_SUBCASE( case1, input_cs_db, weight_ls_db );

    CONV2D_SUBCASE( case1, input_fs_fb, weight_ls_fb );
    CONV2D_SUBCASE( case1, input_fs_hb, weight_ls_hb );
    CONV2D_SUBCASE( case1, input_fs_db, weight_ls_db );

    CONV2D_SUBCASE( case1, input_hs_fb, weight_ls_fb );
    CONV2D_SUBCASE( case1, input_hs_hb, weight_ls_hb );
    CONV2D_SUBCASE( case1, input_hs_db, weight_ls_db );
    #endif
}


TEST_CASE("conv2d(case2)" * doctest::test_suite("array::conv2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONV2D_SUBCASE( case2, input, weight );
    CONV2D_SUBCASE( case2, input_a, weight_a );
    CONV2D_SUBCASE( case2, input_f, weight_f );
    CONV2D_SUBCASE( case2, input_h, weight_h );
    CONV2D_SUBCASE( case2, input_d, weight_d );

    #else
    CONV2D_SUBCASE( case2, input_cs_fb, weight_cs_fb );
    CONV2D_SUBCASE( case2, input_cs_hb, weight_cs_hb );
    CONV2D_SUBCASE( case2, input_cs_db, weight_cs_db );

    CONV2D_SUBCASE( case2, input_fs_fb, weight_fs_fb );
    CONV2D_SUBCASE( case2, input_fs_hb, weight_fs_hb );
    CONV2D_SUBCASE( case2, input_fs_db, weight_fs_db );

    CONV2D_SUBCASE( case2, input_hs_fb, weight_hs_fb );
    CONV2D_SUBCASE( case2, input_hs_hb, weight_hs_hb );
    CONV2D_SUBCASE( case2, input_hs_db, weight_hs_db );

    CONV2D_SUBCASE( case2, input_ds_fb, weight_ds_fb );
    CONV2D_SUBCASE( case2, input_ds_hb, weight_ds_hb );
    CONV2D_SUBCASE( case2, input_ds_db, weight_ds_db );

    CONV2D_SUBCASE( case2, input_ls_fb, weight_ls_fb );
    CONV2D_SUBCASE( case2, input_ls_hb, weight_ls_hb );
    CONV2D_SUBCASE( case2, input_ls_db, weight_ls_db );

    CONV2D_SUBCASE( case2, input_fs_fb, weight_cs_fb );
    CONV2D_SUBCASE( case2, input_fs_hb, weight_cs_hb );
    CONV2D_SUBCASE( case2, input_fs_db, weight_cs_db );

    CONV2D_SUBCASE( case2, input_hs_fb, weight_cs_fb );
    CONV2D_SUBCASE( case2, input_hs_hb, weight_cs_hb );
    CONV2D_SUBCASE( case2, input_hs_db, weight_cs_db );

    CONV2D_SUBCASE( case2, input_ds_fb, weight_cs_fb );
    CONV2D_SUBCASE( case2, input_ds_hb, weight_cs_hb );
    CONV2D_SUBCASE( case2, input_ds_db, weight_cs_db );

    CONV2D_SUBCASE( case2, input_ls_fb, weight_cs_fb );
    CONV2D_SUBCASE( case2, input_ls_hb, weight_cs_hb );
    CONV2D_SUBCASE( case2, input_ls_db, weight_cs_db );

    CONV2D_SUBCASE( case2, input_cs_fb, weight_fs_fb );
    CONV2D_SUBCASE( case2, input_cs_hb, weight_fs_hb );
    CONV2D_SUBCASE( case2, input_cs_db, weight_fs_db );

    CONV2D_SUBCASE( case2, input_hs_fb, weight_fs_fb );
    CONV2D_SUBCASE( case2, input_hs_hb, weight_fs_hb );
    CONV2D_SUBCASE( case2, input_hs_db, weight_fs_db );

    CONV2D_SUBCASE( case2, input_ds_fb, weight_fs_fb );
    CONV2D_SUBCASE( case2, input_ds_hb, weight_fs_hb );
    CONV2D_SUBCASE( case2, input_ds_db, weight_fs_db );

    CONV2D_SUBCASE( case2, input_ls_fb, weight_fs_fb );
    CONV2D_SUBCASE( case2, input_ls_hb, weight_fs_hb );
    CONV2D_SUBCASE( case2, input_ls_db, weight_fs_db );

    CONV2D_SUBCASE( case2, input_cs_fb, weight_hs_fb );
    CONV2D_SUBCASE( case2, input_cs_hb, weight_hs_hb );
    CONV2D_SUBCASE( case2, input_cs_db, weight_hs_db );

    CONV2D_SUBCASE( case2, input_fs_fb, weight_hs_fb );
    CONV2D_SUBCASE( case2, input_fs_hb, weight_hs_hb );
    CONV2D_SUBCASE( case2, input_fs_db, weight_hs_db );

    CONV2D_SUBCASE( case2, input_ds_fb, weight_hs_fb );
    CONV2D_SUBCASE( case2, input_ds_hb, weight_hs_hb );
    CONV2D_SUBCASE( case2, input_ds_db, weight_hs_db );

    CONV2D_SUBCASE( case2, input_ls_fb, weight_hs_fb );
    CONV2D_SUBCASE( case2, input_ls_hb, weight_hs_hb );
    CONV2D_SUBCASE( case2, input_ls_db, weight_hs_db );

    CONV2D_SUBCASE( case2, input_cs_fb, weight_ds_fb );
    CONV2D_SUBCASE( case2, input_cs_hb, weight_ds_hb );
    CONV2D_SUBCASE( case2, input_cs_db, weight_ds_db );

    CONV2D_SUBCASE( case2, input_fs_fb, weight_ds_fb );
    CONV2D_SUBCASE( case2, input_fs_hb, weight_ds_hb );
    CONV2D_SUBCASE( case2, input_fs_db, weight_ds_db );

    CONV2D_SUBCASE( case2, input_hs_fb, weight_ds_fb );
    CONV2D_SUBCASE( case2, input_hs_hb, weight_ds_hb );
    CONV2D_SUBCASE( case2, input_hs_db, weight_ds_db );

    CONV2D_SUBCASE( case2, input_ls_fb, weight_ds_fb );
    CONV2D_SUBCASE( case2, input_ls_hb, weight_ds_hb );
    CONV2D_SUBCASE( case2, input_ls_db, weight_ds_db );

    CONV2D_SUBCASE( case2, input_cs_fb, weight_ls_fb );
    CONV2D_SUBCASE( case2, input_cs_hb, weight_ls_hb );
    CONV2D_SUBCASE( case2, input_cs_db, weight_ls_db );

    CONV2D_SUBCASE( case2, input_fs_fb, weight_ls_fb );
    CONV2D_SUBCASE( case2, input_fs_hb, weight_ls_hb );
    CONV2D_SUBCASE( case2, input_fs_db, weight_ls_db );

    CONV2D_SUBCASE( case2, input_hs_fb, weight_ls_fb );
    CONV2D_SUBCASE( case2, input_hs_hb, weight_ls_hb );
    CONV2D_SUBCASE( case2, input_hs_db, weight_ls_db );
    #endif
}


TEST_CASE("conv2d(case3)" * doctest::test_suite("array::conv2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONV2D_SUBCASE( case3, input, weight );
    CONV2D_SUBCASE( case3, input_a, weight_a );
    CONV2D_SUBCASE( case3, input_f, weight_f );
    CONV2D_SUBCASE( case3, input_h, weight_h );
    CONV2D_SUBCASE( case3, input_d, weight_d );

    #else
    CONV2D_SUBCASE( case3, input_cs_fb, weight_cs_fb );
    CONV2D_SUBCASE( case3, input_cs_hb, weight_cs_hb );
    CONV2D_SUBCASE( case3, input_cs_db, weight_cs_db );

    CONV2D_SUBCASE( case3, input_fs_fb, weight_fs_fb );
    CONV2D_SUBCASE( case3, input_fs_hb, weight_fs_hb );
    CONV2D_SUBCASE( case3, input_fs_db, weight_fs_db );

    CONV2D_SUBCASE( case3, input_hs_fb, weight_hs_fb );
    CONV2D_SUBCASE( case3, input_hs_hb, weight_hs_hb );
    CONV2D_SUBCASE( case3, input_hs_db, weight_hs_db );

    CONV2D_SUBCASE( case3, input_ds_fb, weight_ds_fb );
    CONV2D_SUBCASE( case3, input_ds_hb, weight_ds_hb );
    CONV2D_SUBCASE( case3, input_ds_db, weight_ds_db );

    CONV2D_SUBCASE( case3, input_ls_fb, weight_ls_fb );
    CONV2D_SUBCASE( case3, input_ls_hb, weight_ls_hb );
    CONV2D_SUBCASE( case3, input_ls_db, weight_ls_db );

    CONV2D_SUBCASE( case3, input_fs_fb, weight_cs_fb );
    CONV2D_SUBCASE( case3, input_fs_hb, weight_cs_hb );
    CONV2D_SUBCASE( case3, input_fs_db, weight_cs_db );

    CONV2D_SUBCASE( case3, input_hs_fb, weight_cs_fb );
    CONV2D_SUBCASE( case3, input_hs_hb, weight_cs_hb );
    CONV2D_SUBCASE( case3, input_hs_db, weight_cs_db );

    CONV2D_SUBCASE( case3, input_ds_fb, weight_cs_fb );
    CONV2D_SUBCASE( case3, input_ds_hb, weight_cs_hb );
    CONV2D_SUBCASE( case3, input_ds_db, weight_cs_db );

    CONV2D_SUBCASE( case3, input_ls_fb, weight_cs_fb );
    CONV2D_SUBCASE( case3, input_ls_hb, weight_cs_hb );
    CONV2D_SUBCASE( case3, input_ls_db, weight_cs_db );

    CONV2D_SUBCASE( case3, input_cs_fb, weight_fs_fb );
    CONV2D_SUBCASE( case3, input_cs_hb, weight_fs_hb );
    CONV2D_SUBCASE( case3, input_cs_db, weight_fs_db );

    CONV2D_SUBCASE( case3, input_hs_fb, weight_fs_fb );
    CONV2D_SUBCASE( case3, input_hs_hb, weight_fs_hb );
    CONV2D_SUBCASE( case3, input_hs_db, weight_fs_db );

    CONV2D_SUBCASE( case3, input_ds_fb, weight_fs_fb );
    CONV2D_SUBCASE( case3, input_ds_hb, weight_fs_hb );
    CONV2D_SUBCASE( case3, input_ds_db, weight_fs_db );

    CONV2D_SUBCASE( case3, input_ls_fb, weight_fs_fb );
    CONV2D_SUBCASE( case3, input_ls_hb, weight_fs_hb );
    CONV2D_SUBCASE( case3, input_ls_db, weight_fs_db );

    CONV2D_SUBCASE( case3, input_cs_fb, weight_hs_fb );
    CONV2D_SUBCASE( case3, input_cs_hb, weight_hs_hb );
    CONV2D_SUBCASE( case3, input_cs_db, weight_hs_db );

    CONV2D_SUBCASE( case3, input_fs_fb, weight_hs_fb );
    CONV2D_SUBCASE( case3, input_fs_hb, weight_hs_hb );
    CONV2D_SUBCASE( case3, input_fs_db, weight_hs_db );

    CONV2D_SUBCASE( case3, input_ds_fb, weight_hs_fb );
    CONV2D_SUBCASE( case3, input_ds_hb, weight_hs_hb );
    CONV2D_SUBCASE( case3, input_ds_db, weight_hs_db );

    CONV2D_SUBCASE( case3, input_ls_fb, weight_hs_fb );
    CONV2D_SUBCASE( case3, input_ls_hb, weight_hs_hb );
    CONV2D_SUBCASE( case3, input_ls_db, weight_hs_db );

    CONV2D_SUBCASE( case3, input_cs_fb, weight_ds_fb );
    CONV2D_SUBCASE( case3, input_cs_hb, weight_ds_hb );
    CONV2D_SUBCASE( case3, input_cs_db, weight_ds_db );

    CONV2D_SUBCASE( case3, input_fs_fb, weight_ds_fb );
    CONV2D_SUBCASE( case3, input_fs_hb, weight_ds_hb );
    CONV2D_SUBCASE( case3, input_fs_db, weight_ds_db );

    CONV2D_SUBCASE( case3, input_hs_fb, weight_ds_fb );
    CONV2D_SUBCASE( case3, input_hs_hb, weight_ds_hb );
    CONV2D_SUBCASE( case3, input_hs_db, weight_ds_db );

    CONV2D_SUBCASE( case3, input_ls_fb, weight_ds_fb );
    CONV2D_SUBCASE( case3, input_ls_hb, weight_ds_hb );
    CONV2D_SUBCASE( case3, input_ls_db, weight_ds_db );

    CONV2D_SUBCASE( case3, input_cs_fb, weight_ls_fb );
    CONV2D_SUBCASE( case3, input_cs_hb, weight_ls_hb );
    CONV2D_SUBCASE( case3, input_cs_db, weight_ls_db );

    CONV2D_SUBCASE( case3, input_fs_fb, weight_ls_fb );
    CONV2D_SUBCASE( case3, input_fs_hb, weight_ls_hb );
    CONV2D_SUBCASE( case3, input_fs_db, weight_ls_db );

    CONV2D_SUBCASE( case3, input_hs_fb, weight_ls_fb );
    CONV2D_SUBCASE( case3, input_hs_hb, weight_ls_hb );
    CONV2D_SUBCASE( case3, input_hs_db, weight_ls_db );
    #endif
}


TEST_CASE("conv2d(case4)" * doctest::test_suite("array::conv2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONV2D_SUBCASE( case4, input, weight, None, stride );
    CONV2D_SUBCASE( case4, input_a, weight_a, None, stride_a );
    CONV2D_SUBCASE( case4, input_f, weight_f, None, stride_f );
    CONV2D_SUBCASE( case4, input_h, weight_h, None, stride_h );
    CONV2D_SUBCASE( case4, input_d, weight_d, None, stride_v );

    #else
    CONV2D_SUBCASE( case4, input_cs_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case4, input_cs_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case4, input_cs_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case4, input_fs_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case4, input_fs_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case4, input_fs_db, weight_fs_db, None, stride_a );

    CONV2D_SUBCASE( case4, input_hs_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case4, input_hs_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case4, input_hs_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case4, input_ds_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case4, input_ds_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case4, input_ds_db, weight_ds_db, None, stride_a );

    CONV2D_SUBCASE( case4, input_ls_fb, weight_ls_fb, None, stride_a );
    CONV2D_SUBCASE( case4, input_ls_hb, weight_ls_hb, None, stride_a );
    CONV2D_SUBCASE( case4, input_ls_db, weight_ls_db, None, stride_a );

    CONV2D_SUBCASE( case4, input_fs_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case4, input_fs_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case4, input_fs_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case4, input_hs_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case4, input_hs_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case4, input_hs_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case4, input_ds_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case4, input_ds_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case4, input_ds_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case4, input_ls_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case4, input_ls_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case4, input_ls_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case4, input_cs_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case4, input_cs_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case4, input_cs_db, weight_fs_db, None, stride_a );

    CONV2D_SUBCASE( case4, input_hs_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case4, input_hs_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case4, input_hs_db, weight_fs_db, None, stride_a );

    CONV2D_SUBCASE( case4, input_ds_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case4, input_ds_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case4, input_ds_db, weight_fs_db, None, stride_a );

    CONV2D_SUBCASE( case4, input_ls_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case4, input_ls_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case4, input_ls_db, weight_fs_db, None, stride_a );

    CONV2D_SUBCASE( case4, input_cs_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case4, input_cs_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case4, input_cs_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case4, input_fs_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case4, input_fs_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case4, input_fs_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case4, input_ds_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case4, input_ds_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case4, input_ds_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case4, input_ls_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case4, input_ls_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case4, input_ls_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case4, input_cs_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case4, input_cs_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case4, input_cs_db, weight_ds_db, None, stride_a );

    CONV2D_SUBCASE( case4, input_fs_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case4, input_fs_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case4, input_fs_db, weight_ds_db, None, stride_a );

    CONV2D_SUBCASE( case4, input_hs_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case4, input_hs_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case4, input_hs_db, weight_ds_db, None, stride_a );

    CONV2D_SUBCASE( case4, input_ls_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case4, input_ls_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case4, input_ls_db, weight_ds_db, None, stride_a );

    CONV2D_SUBCASE( case4, input_cs_fb, weight_ls_fb, None, stride_a );
    CONV2D_SUBCASE( case4, input_cs_hb, weight_ls_hb, None, stride_a );
    CONV2D_SUBCASE( case4, input_cs_db, weight_ls_db, None, stride_a );

    CONV2D_SUBCASE( case4, input_fs_fb, weight_ls_fb, None, stride_a );
    CONV2D_SUBCASE( case4, input_fs_hb, weight_ls_hb, None, stride_a );
    CONV2D_SUBCASE( case4, input_fs_db, weight_ls_db, None, stride_a );

    CONV2D_SUBCASE( case4, input_hs_fb, weight_ls_fb, None, stride_a );
    CONV2D_SUBCASE( case4, input_hs_hb, weight_ls_hb, None, stride_a );
    CONV2D_SUBCASE( case4, input_hs_db, weight_ls_db, None, stride_a );

    CONV2D_SUBCASE( case4, input_ds_fb, weight_ls_fb, None, stride_a );
    CONV2D_SUBCASE( case4, input_ds_hb, weight_ls_hb, None, stride_a );
    CONV2D_SUBCASE( case4, input_ds_db, weight_ls_db, None, stride_a );
    #endif
}

#else

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

#endif