#if 1
#define NMTOOLS_CAST_ARRAYS_EXTRA(name) \
inline auto name##_cs_fb = nmtools::cast(name, nmtools::kind::ndarray_cs_fb); \
inline auto name##_cs_hb = nmtools::cast(name, nmtools::kind::ndarray_cs_hb); \
inline auto name##_cs_db = nmtools::cast(name, nmtools::kind::ndarray_cs_db); \
inline auto name##_fs_fb = nmtools::cast(name, nmtools::kind::ndarray_cs_fb); \
inline auto name##_fs_hb = nmtools::cast(name, nmtools::kind::ndarray_cs_hb); \
inline auto name##_fs_db = nmtools::cast(name, nmtools::kind::ndarray_cs_db); \
inline auto name##_hs_fb = nmtools::cast(name, nmtools::kind::ndarray_cs_fb); \
inline auto name##_hs_hb = nmtools::cast(name, nmtools::kind::ndarray_cs_hb); \
inline auto name##_hs_db = nmtools::cast(name, nmtools::kind::ndarray_cs_db); \
inline auto name##_ds_fb = nmtools::cast(name, nmtools::kind::ndarray_cs_fb); \
inline auto name##_ds_hb = nmtools::cast(name, nmtools::kind::ndarray_cs_hb); \
inline auto name##_ds_db = nmtools::cast(name, nmtools::kind::ndarray_cs_db);
#endif

#define NMTOOLS_TESTING_PRECISION (1e-3)

#include "nmtools/array/ufuncs/rad2deg.hpp"
#include "nmtools/testing/data/array/rad2deg.hpp"
#include "nmtools/testing/doctest.hpp"

#define RAD2DEG_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, rad2deg, case_name); \
    using namespace args; \
    auto result = nmtools::view::rad2deg(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("rad2deg(case1)" * doctest::test_suite("view::rad2deg"))
{
    RAD2DEG_SUBCASE( case1,   a);
    RAD2DEG_SUBCASE( case1, a_a);
    RAD2DEG_SUBCASE( case1, a_f);
    RAD2DEG_SUBCASE( case1, a_d);
    RAD2DEG_SUBCASE( case1, a_h);

    RAD2DEG_SUBCASE( case1, a_cs_fb );
    RAD2DEG_SUBCASE( case1, a_cs_hb );
    RAD2DEG_SUBCASE( case1, a_cs_db );

    RAD2DEG_SUBCASE( case1, a_fs_fb );
    RAD2DEG_SUBCASE( case1, a_fs_hb );
    RAD2DEG_SUBCASE( case1, a_fs_db );

    RAD2DEG_SUBCASE( case1, a_hs_fb );
    RAD2DEG_SUBCASE( case1, a_hs_hb );
    RAD2DEG_SUBCASE( case1, a_hs_db );

    RAD2DEG_SUBCASE( case1, a_ds_fb );
    RAD2DEG_SUBCASE( case1, a_ds_hb );
    RAD2DEG_SUBCASE( case1, a_ds_db );
}

TEST_CASE("rad2deg(case2)" * doctest::test_suite("view::rad2deg"))
{
    RAD2DEG_SUBCASE( case2,   a);
    RAD2DEG_SUBCASE( case2, a_a);
    RAD2DEG_SUBCASE( case2, a_f);
    RAD2DEG_SUBCASE( case2, a_d);
    RAD2DEG_SUBCASE( case2, a_h);

    RAD2DEG_SUBCASE( case2, a_cs_fb );
    RAD2DEG_SUBCASE( case2, a_cs_hb );
    RAD2DEG_SUBCASE( case2, a_cs_db );

    RAD2DEG_SUBCASE( case2, a_fs_fb );
    RAD2DEG_SUBCASE( case2, a_fs_hb );
    RAD2DEG_SUBCASE( case2, a_fs_db );

    RAD2DEG_SUBCASE( case2, a_hs_fb );
    RAD2DEG_SUBCASE( case2, a_hs_hb );
    RAD2DEG_SUBCASE( case2, a_hs_db );

    RAD2DEG_SUBCASE( case2, a_ds_fb );
    RAD2DEG_SUBCASE( case2, a_ds_hb );
    RAD2DEG_SUBCASE( case2, a_ds_db );
}