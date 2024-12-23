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

#include "nmtools/array/array/conv3d.hpp"
#include "nmtools/testing/data/array/conv3d.hpp"
#include "nmtools/testing/doctest.hpp"

#define CONV3D_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, conv3d, case_name); \
    using namespace args; \
    auto result = nmtools::array::conv3d(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("conv3d(case1i)" * doctest::test_suite("array::conv3d"))
{
    [[maybe_unused]] auto padding = nmtools::None;
    [[maybe_unused]] auto dilation = nmtools::None;

    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONV3D_SUBCASE( case1i, input, weight, bias, stride_ct, padding, dilation, groups_ct );
    CONV3D_SUBCASE( case1i, input_a, weight_a, bias_a, stride_ct, padding, dilation, groups_ct );
    CONV3D_SUBCASE( case1i, input_f, weight_f, bias_f, stride_ct, padding, dilation, groups_ct );
    CONV3D_SUBCASE( case1i, input_h, weight_h, bias_h, stride, padding, dilation, groups );
    CONV3D_SUBCASE( case1i, input_d, weight_d, bias_d, stride, padding, dilation, groups );
    #else
    #endif
}