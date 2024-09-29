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

#include "nmtools/array/view/swapaxes.hpp"
#include "nmtools/testing/data/array/swapaxes.hpp"
#include "nmtools/testing/doctest.hpp"

#define SWAPAXES_SUBCASE( case_name, ... ) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( array, swapaxes, case_name ); \
    using namespace args; \
    auto result = nmtools::view::swapaxes(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("swapaxes(case1)" * doctest::test_suite("view::swapaxes"))
{
    SWAPAXES_SUBCASE( case1, a, axis1, axis2 );
    SWAPAXES_SUBCASE( case1, a_a, axis1, axis2 );
    SWAPAXES_SUBCASE( case1, a_f, axis1, axis2 );
    SWAPAXES_SUBCASE( case1, a_h, axis1, axis2 );
    SWAPAXES_SUBCASE( case1, a_d, axis1, axis2 );

    SWAPAXES_SUBCASE( case1, a, axis1_ct, axis2_ct );
    SWAPAXES_SUBCASE( case1, a_a, axis1_ct, axis2_ct );
    SWAPAXES_SUBCASE( case1, a_f, axis1_ct, axis2_ct );
    SWAPAXES_SUBCASE( case1, a_h, axis1_ct, axis2_ct );
    SWAPAXES_SUBCASE( case1, a_d, axis1_ct, axis2_ct );
}

TEST_CASE("swapaxes(case2)" * doctest::test_suite("view::swapaxes"))
{
    SWAPAXES_SUBCASE( case2, a, axis1, axis2 );
    SWAPAXES_SUBCASE( case2, a_a, axis1, axis2 );
    SWAPAXES_SUBCASE( case2, a_f, axis1, axis2 );
    SWAPAXES_SUBCASE( case2, a_h, axis1, axis2 );
    SWAPAXES_SUBCASE( case2, a_d, axis1, axis2 );

    SWAPAXES_SUBCASE( case2, a, axis1_ct, axis2_ct );
    SWAPAXES_SUBCASE( case2, a_a, axis1_ct, axis2_ct );
    SWAPAXES_SUBCASE( case2, a_f, axis1_ct, axis2_ct );
    SWAPAXES_SUBCASE( case2, a_h, axis1_ct, axis2_ct );
    SWAPAXES_SUBCASE( case2, a_d, axis1_ct, axis2_ct );
}

TEST_CASE("swapaxes(case3)" * doctest::test_suite("view::swapaxes"))
{
    SWAPAXES_SUBCASE( case3, a, axis1, axis2 );
    SWAPAXES_SUBCASE( case3, a_a, axis1, axis2 );
    SWAPAXES_SUBCASE( case3, a_f, axis1, axis2 );
    SWAPAXES_SUBCASE( case3, a_h, axis1, axis2 );
    SWAPAXES_SUBCASE( case3, a_d, axis1, axis2 );

    SWAPAXES_SUBCASE( case3, a, axis1_ct, axis2_ct );
    SWAPAXES_SUBCASE( case3, a_a, axis1_ct, axis2_ct );
    SWAPAXES_SUBCASE( case3, a_f, axis1_ct, axis2_ct );
    SWAPAXES_SUBCASE( case3, a_h, axis1_ct, axis2_ct );
    SWAPAXES_SUBCASE( case3, a_d, axis1_ct, axis2_ct );
}

TEST_CASE("swapaxes(case4)" * doctest::test_suite("view::swapaxes"))
{
    SWAPAXES_SUBCASE( case4, a, axis1, axis2 );
    SWAPAXES_SUBCASE( case4, a_a, axis1, axis2 );
    SWAPAXES_SUBCASE( case4, a_f, axis1, axis2 );
    SWAPAXES_SUBCASE( case4, a_h, axis1, axis2 );
    SWAPAXES_SUBCASE( case4, a_d, axis1, axis2 );

    SWAPAXES_SUBCASE( case4, a, axis1_ct, axis2_ct );
    SWAPAXES_SUBCASE( case4, a_a, axis1_ct, axis2_ct );
    SWAPAXES_SUBCASE( case4, a_f, axis1_ct, axis2_ct );
    SWAPAXES_SUBCASE( case4, a_h, axis1_ct, axis2_ct );
    SWAPAXES_SUBCASE( case4, a_d, axis1_ct, axis2_ct );
}