#if 1
#define NMTOOLS_CAST_ARRAYS_EXTRA(name) \
inline auto name##_cs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_fb); \
inline auto name##_cs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_hb); \
inline auto name##_cs_db = nmtools::cast(name, nmtools::array::kind::ndarray_cs_db); \
inline auto name##_fs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_fb); \
inline auto name##_fs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_hb); \
inline auto name##_fs_db = nmtools::cast(name, nmtools::array::kind::ndarray_cs_db); \
inline auto name##_hs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_fb); \
inline auto name##_hs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_hb); \
inline auto name##_hs_db = nmtools::cast(name, nmtools::array::kind::ndarray_cs_db); \
inline auto name##_ds_fb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_fb); \
inline auto name##_ds_hb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_hb); \
inline auto name##_ds_db = nmtools::cast(name, nmtools::array::kind::ndarray_cs_db);
#endif

#include "nmtools/array/ufuncs/deg2rad.hpp"
#include "nmtools/testing/data/array/deg2rad.hpp"
#include "nmtools/testing/doctest.hpp"

#define DEG2RAD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, deg2rad, case_name); \
    using namespace args; \
    auto result = nmtools::view::deg2rad(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("deg2rad(case1)" * doctest::test_suite("view::deg2rad"))
{
    DEG2RAD_SUBCASE( case1,   a);
    DEG2RAD_SUBCASE( case1, a_a);
    DEG2RAD_SUBCASE( case1, a_f);
    DEG2RAD_SUBCASE( case1, a_d);
    DEG2RAD_SUBCASE( case1, a_h);

    DEG2RAD_SUBCASE( case1, a_cs_fb );
    DEG2RAD_SUBCASE( case1, a_cs_hb );
    DEG2RAD_SUBCASE( case1, a_cs_db );

    DEG2RAD_SUBCASE( case1, a_fs_fb );
    DEG2RAD_SUBCASE( case1, a_fs_hb );
    DEG2RAD_SUBCASE( case1, a_fs_db );

    DEG2RAD_SUBCASE( case1, a_hs_fb );
    DEG2RAD_SUBCASE( case1, a_hs_hb );
    DEG2RAD_SUBCASE( case1, a_hs_db );

    DEG2RAD_SUBCASE( case1, a_ds_fb );
    DEG2RAD_SUBCASE( case1, a_ds_hb );
    DEG2RAD_SUBCASE( case1, a_ds_db );
}

TEST_CASE("deg2rad(case2)" * doctest::test_suite("view::deg2rad"))
{
    DEG2RAD_SUBCASE( case2,   a);
    DEG2RAD_SUBCASE( case2, a_a);
    DEG2RAD_SUBCASE( case2, a_f);
    DEG2RAD_SUBCASE( case2, a_d);
    DEG2RAD_SUBCASE( case2, a_h);

    DEG2RAD_SUBCASE( case2, a_cs_fb );
    DEG2RAD_SUBCASE( case2, a_cs_hb );
    DEG2RAD_SUBCASE( case2, a_cs_db );

    DEG2RAD_SUBCASE( case2, a_fs_fb );
    DEG2RAD_SUBCASE( case2, a_fs_hb );
    DEG2RAD_SUBCASE( case2, a_fs_db );

    DEG2RAD_SUBCASE( case2, a_hs_fb );
    DEG2RAD_SUBCASE( case2, a_hs_hb );
    DEG2RAD_SUBCASE( case2, a_hs_db );

    DEG2RAD_SUBCASE( case2, a_ds_fb );
    DEG2RAD_SUBCASE( case2, a_ds_hb );
    DEG2RAD_SUBCASE( case2, a_ds_db );
}