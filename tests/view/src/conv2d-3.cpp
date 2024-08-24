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

#include "nmtools/array/view/conv2d.hpp"
#include "nmtools/testing/data/array/conv2d.hpp"
#include "nmtools/testing/doctest.hpp"

#define CONV2D_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, conv2dv2, case_name); \
    using namespace args; \
    auto result = nmtools::view::conv2dv2(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("conv2d(case3)" * doctest::test_suite("view::conv2dv2"))
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
    #endif
}