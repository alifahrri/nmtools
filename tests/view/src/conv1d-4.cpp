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

#include "nmtools/array/conv1d.hpp"
#include "nmtools/testing/data/array/conv1d.hpp"
#include "nmtools/testing/doctest.hpp"

#define CONV1D_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, conv1d, case_name); \
    using namespace args; \
    auto result = nmtools::view::conv1d(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("conv1d(case4)" * doctest::test_suite("view::conv1d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONV1D_SUBCASE( case4, input, weight );
    CONV1D_SUBCASE( case4, input_a, weight_a );
    CONV1D_SUBCASE( case4, input_f, weight_f );
    CONV1D_SUBCASE( case4, input_h, weight_h );
    CONV1D_SUBCASE( case4, input_d, weight_d );
    #else
    CONV1D_SUBCASE( case4, input_cs_fb, weight_cs_fb );
    CONV1D_SUBCASE( case4, input_cs_hb, weight_cs_hb );
    CONV1D_SUBCASE( case4, input_cs_db, weight_cs_db );

    CONV1D_SUBCASE( case4, input_fs_fb, weight_fs_fb );
    CONV1D_SUBCASE( case4, input_fs_hb, weight_fs_hb );
    CONV1D_SUBCASE( case4, input_fs_db, weight_fs_db );

    CONV1D_SUBCASE( case4, input_hs_fb, weight_hs_fb );
    CONV1D_SUBCASE( case4, input_hs_hb, weight_hs_hb );
    CONV1D_SUBCASE( case4, input_hs_db, weight_hs_db );

    CONV1D_SUBCASE( case4, input_ds_fb, weight_ds_fb );
    CONV1D_SUBCASE( case4, input_ds_hb, weight_ds_hb );
    CONV1D_SUBCASE( case4, input_ds_db, weight_ds_db );

    CONV1D_SUBCASE( case4, input_ls_fb, weight_ls_fb );
    CONV1D_SUBCASE( case4, input_ls_hb, weight_ls_hb );
    CONV1D_SUBCASE( case4, input_ls_db, weight_ls_db );
    #endif
}