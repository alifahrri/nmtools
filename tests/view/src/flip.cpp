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
inline auto name##_ds_db = nmtools::cast(name, nmtools::array::kind::ndarray_ds_db);
#endif

#include "nmtools/array/flip.hpp"
#include "nmtools/testing/data/array/flip.hpp"
#include "nmtools/testing/data/array/fliplr.hpp"
#include "nmtools/testing/data/array/flipud.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;

#define FLIP_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(flip, case_name); \
    using namespace args; \
    auto result = nmtools::view::flip(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

#define FLIPLR_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(fliplr, case_name); \
    using namespace args; \
    auto result = nmtools::view::fliplr(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

#define FLIPUD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(flipud, case_name); \
    using namespace args; \
    auto result = nmtools::view::flipud(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("flip(case1)" * doctest::test_suite("view::flip"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    FLIP_SUBCASE(case1,   array, axis );
    FLIP_SUBCASE(case1, array_a, axis );
    FLIP_SUBCASE(case1, array_f, axis );
    FLIP_SUBCASE(case1, array_h, axis );
    // TODO: support flip for dynamic ndarray
    // FLIP_SUBCASE(case1, array_d, axis );

    #else
    FLIP_SUBCASE(case1, array_cs_fb, axis );
    FLIP_SUBCASE(case1, array_cs_hb, axis );
    FLIP_SUBCASE(case1, array_cs_db, axis );

    FLIP_SUBCASE(case1, array_fs_fb, axis );
    FLIP_SUBCASE(case1, array_fs_hb, axis );
    FLIP_SUBCASE(case1, array_fs_db, axis );

    // TODO: fix
    // FLIP_SUBCASE(case1, array_hs_fb, axis );
    // FLIP_SUBCASE(case1, array_hs_hb, axis );
    // FLIP_SUBCASE(case1, array_hs_db, axis );

    // TODO: fix compile
    // FLIP_SUBCASE(case1, array_ds_fb, axis );
    // FLIP_SUBCASE(case1, array_ds_hb, axis );
    // FLIP_SUBCASE(case1, array_ds_db, axis );
    #endif
}

TEST_CASE("flip(case2)" * doctest::test_suite("view::flip"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    FLIP_SUBCASE(case2,   array, axis );
    FLIP_SUBCASE(case2, array_a, axis );
    FLIP_SUBCASE(case2, array_f, axis );
    FLIP_SUBCASE(case2, array_h, axis );
    // FLIP_SUBCASE(case2, array_d, axis );

    #else
    FLIP_SUBCASE(case2, array_cs_fb, axis );
    FLIP_SUBCASE(case2, array_cs_hb, axis );
    FLIP_SUBCASE(case2, array_cs_db, axis );

    FLIP_SUBCASE(case2, array_fs_fb, axis );
    FLIP_SUBCASE(case2, array_fs_hb, axis );
    FLIP_SUBCASE(case2, array_fs_db, axis );

    // FLIP_SUBCASE(case2, array_hs_fb, axis );
    // FLIP_SUBCASE(case2, array_hs_hb, axis );
    // FLIP_SUBCASE(case2, array_hs_db, axis );

    // FLIP_SUBCASE(case2, array_ds_fb, axis );
    // FLIP_SUBCASE(case2, array_ds_hb, axis );
    // FLIP_SUBCASE(case2, array_ds_db, axis );
    #endif
}

TEST_CASE("flip(case3)" * doctest::test_suite("view::flip"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    FLIP_SUBCASE(case3,   array, axis );
    FLIP_SUBCASE(case3, array_a, axis );
    FLIP_SUBCASE(case3, array_f, axis );
    FLIP_SUBCASE(case3, array_h, axis );
    // FLIP_SUBCASE(case3, array_d, axis );

    #else
    FLIP_SUBCASE(case3, array_cs_fb, axis );
    FLIP_SUBCASE(case3, array_cs_hb, axis );
    FLIP_SUBCASE(case3, array_cs_db, axis );

    FLIP_SUBCASE(case3, array_fs_fb, axis );
    FLIP_SUBCASE(case3, array_fs_hb, axis );
    FLIP_SUBCASE(case3, array_fs_db, axis );

    // FLIP_SUBCASE(case3, array_hs_fb, axis );
    // FLIP_SUBCASE(case3, array_hs_hb, axis );
    // FLIP_SUBCASE(case3, array_hs_db, axis );

    // FLIP_SUBCASE(case3, array_ds_fb, axis );
    // FLIP_SUBCASE(case3, array_ds_hb, axis );
    // FLIP_SUBCASE(case3, array_ds_db, axis );
    #endif
}

TEST_CASE("flip(case4)" * doctest::test_suite("view::flip"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    FLIP_SUBCASE(case4,   array,   axis );
    FLIP_SUBCASE(case4, array_a, axis_a );
    FLIP_SUBCASE(case4, array_f, axis_f );
    FLIP_SUBCASE(case4, array_h, axis_h );
    // FLIP_SUBCASE(case4, array_d, axis_d );

    #else
    FLIP_SUBCASE(case4, array_cs_fb, axis );
    FLIP_SUBCASE(case4, array_cs_hb, axis );
    FLIP_SUBCASE(case4, array_cs_db, axis );

    FLIP_SUBCASE(case4, array_fs_fb, axis );
    FLIP_SUBCASE(case4, array_fs_hb, axis );
    FLIP_SUBCASE(case4, array_fs_db, axis );

    // FLIP_SUBCASE(case4, array_hs_fb, axis );
    // FLIP_SUBCASE(case4, array_hs_hb, axis );
    // FLIP_SUBCASE(case4, array_hs_db, axis );

    // FLIP_SUBCASE(case4, array_ds_fb, axis );
    // FLIP_SUBCASE(case4, array_ds_hb, axis );
    // FLIP_SUBCASE(case4, array_ds_db, axis );
    #endif
}

TEST_CASE("flipud(case1)" * doctest::test_suite("view::flipud"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    FLIPUD_SUBCASE(case1,   array );
    FLIPUD_SUBCASE(case1, array_a );
    FLIPUD_SUBCASE(case1, array_f );
    FLIPUD_SUBCASE(case1, array_h );
    // TODO: support flipud for dynamic ndarray
    // FLIPUD_SUBCASE(case1, array_d );

    #else
    FLIPUD_SUBCASE(case1, array_cs_fb );
    FLIPUD_SUBCASE(case1, array_cs_hb );
    FLIPUD_SUBCASE(case1, array_cs_db );

    FLIPUD_SUBCASE(case1, array_fs_fb );
    FLIPUD_SUBCASE(case1, array_fs_hb );
    FLIPUD_SUBCASE(case1, array_fs_db );

    // TODO: fix
    // FLIPUD_SUBCASE(case1, array_hs_fb );
    // FLIPUD_SUBCASE(case1, array_hs_hb );
    // FLIPUD_SUBCASE(case1, array_hs_db );

    // TODO: fix compile
    // FLIPUD_SUBCASE(case1, array_ds_fb );
    // FLIPUD_SUBCASE(case1, array_ds_hb );
    // FLIPUD_SUBCASE(case1, array_ds_db );
    #endif
}

TEST_CASE("flipud(case2)" * doctest::test_suite("view::flipud"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    FLIPUD_SUBCASE(case2,   array );
    FLIPUD_SUBCASE(case2, array_a );
    FLIPUD_SUBCASE(case2, array_f );
    FLIPUD_SUBCASE(case2, array_h );
    // FLIPUD_SUBCASE(case2, array_d );

    #else
    FLIPUD_SUBCASE(case2, array_cs_fb );
    FLIPUD_SUBCASE(case2, array_cs_hb );
    FLIPUD_SUBCASE(case2, array_cs_db );

    FLIPUD_SUBCASE(case2, array_fs_fb );
    FLIPUD_SUBCASE(case2, array_fs_hb );
    FLIPUD_SUBCASE(case2, array_fs_db );

    // FLIPUD_SUBCASE(case2, array_hs_fb );
    // FLIPUD_SUBCASE(case2, array_hs_hb );
    // FLIPUD_SUBCASE(case2, array_hs_db );

    // FLIPUD_SUBCASE(case2, array_ds_fb );
    // FLIPUD_SUBCASE(case2, array_ds_hb );
    // FLIPUD_SUBCASE(case2, array_ds_db );
    #endif
}

TEST_CASE("flipud(case3)" * doctest::test_suite("view::flipud"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    FLIPUD_SUBCASE(case3,   array );
    FLIPUD_SUBCASE(case3, array_a );
    FLIPUD_SUBCASE(case3, array_f );
    FLIPUD_SUBCASE(case3, array_h );
    // FLIPUD_SUBCASE(case3, array_d );

    #else
    FLIPUD_SUBCASE(case3, array_cs_fb );
    FLIPUD_SUBCASE(case3, array_cs_hb );
    FLIPUD_SUBCASE(case3, array_cs_db );

    FLIPUD_SUBCASE(case3, array_fs_fb );
    FLIPUD_SUBCASE(case3, array_fs_hb );
    FLIPUD_SUBCASE(case3, array_fs_db );

    // FLIPUD_SUBCASE(case3, array_hs_fb );
    // FLIPUD_SUBCASE(case3, array_hs_hb );
    // FLIPUD_SUBCASE(case3, array_hs_db );

    // FLIPUD_SUBCASE(case3, array_ds_fb );
    // FLIPUD_SUBCASE(case3, array_ds_hb );
    // FLIPUD_SUBCASE(case3, array_ds_db );
    #endif
}

TEST_CASE("flipud(case4)" * doctest::test_suite("view::flipud"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    FLIPUD_SUBCASE(case4,   array );
    FLIPUD_SUBCASE(case4, array_a );
    FLIPUD_SUBCASE(case4, array_f );
    FLIPUD_SUBCASE(case4, array_h );
    // FLIPUD_SUBCASE(case4, array_d );

    #else
    FLIPUD_SUBCASE(case4, array_cs_fb );
    FLIPUD_SUBCASE(case4, array_cs_hb );
    FLIPUD_SUBCASE(case4, array_cs_db );

    FLIPUD_SUBCASE(case4, array_fs_fb );
    FLIPUD_SUBCASE(case4, array_fs_hb );
    FLIPUD_SUBCASE(case4, array_fs_db );

    // FLIPUD_SUBCASE(case4, array_hs_fb );
    // FLIPUD_SUBCASE(case4, array_hs_hb );
    // FLIPUD_SUBCASE(case4, array_hs_db );

    // FLIPUD_SUBCASE(case4, array_ds_fb );
    // FLIPUD_SUBCASE(case4, array_ds_hb );
    // FLIPUD_SUBCASE(case4, array_ds_db );
    #endif
}

TEST_CASE("fliplr(case1)" * doctest::test_suite("view::fliplr"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    FLIPLR_SUBCASE(case1,   array );
    FLIPLR_SUBCASE(case1, array_a );
    FLIPLR_SUBCASE(case1, array_f );
    FLIPLR_SUBCASE(case1, array_h );
    // TODO: support fliplr for dynamic ndarray
    // FLIPLR_SUBCASE(case1, array_d );

    #else
    FLIPLR_SUBCASE(case1, array_cs_fb );
    FLIPLR_SUBCASE(case1, array_cs_hb );
    FLIPLR_SUBCASE(case1, array_cs_db );

    FLIPLR_SUBCASE(case1, array_fs_fb );
    FLIPLR_SUBCASE(case1, array_fs_hb );
    FLIPLR_SUBCASE(case1, array_fs_db );

    // TODO: fix
    // FLIPLR_SUBCASE(case1, array_hs_fb );
    // FLIPLR_SUBCASE(case1, array_hs_hb );
    // FLIPLR_SUBCASE(case1, array_hs_db );

    // TODO: fix compile
    // FLIPLR_SUBCASE(case1, array_ds_fb );
    // FLIPLR_SUBCASE(case1, array_ds_hb );
    // FLIPLR_SUBCASE(case1, array_ds_db );
    #endif
}

TEST_CASE("fliplr(case2)" * doctest::test_suite("view::fliplr"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    FLIPLR_SUBCASE(case2,   array );
    FLIPLR_SUBCASE(case2, array_a );
    FLIPLR_SUBCASE(case2, array_f );
    FLIPLR_SUBCASE(case2, array_h );
    // FLIPLR_SUBCASE(case2, array_d );

    #else
    FLIPLR_SUBCASE(case2, array_cs_fb );
    FLIPLR_SUBCASE(case2, array_cs_hb );
    FLIPLR_SUBCASE(case2, array_cs_db );

    FLIPLR_SUBCASE(case2, array_fs_fb );
    FLIPLR_SUBCASE(case2, array_fs_hb );
    FLIPLR_SUBCASE(case2, array_fs_db );

    // FLIPLR_SUBCASE(case2, array_hs_fb );
    // FLIPLR_SUBCASE(case2, array_hs_hb );
    // FLIPLR_SUBCASE(case2, array_hs_db );

    // FLIPLR_SUBCASE(case2, array_ds_fb );
    // FLIPLR_SUBCASE(case2, array_ds_hb );
    // FLIPLR_SUBCASE(case2, array_ds_db );
    #endif
}

TEST_CASE("fliplr(case3)" * doctest::test_suite("view::fliplr"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    FLIPLR_SUBCASE(case3,   array );
    FLIPLR_SUBCASE(case3, array_a );
    FLIPLR_SUBCASE(case3, array_f );
    FLIPLR_SUBCASE(case3, array_h );
    // FLIPLR_SUBCASE(case3, array_d );

    #else
    FLIPLR_SUBCASE(case3, array_cs_fb );
    FLIPLR_SUBCASE(case3, array_cs_hb );
    FLIPLR_SUBCASE(case3, array_cs_db );

    FLIPLR_SUBCASE(case3, array_fs_fb );
    FLIPLR_SUBCASE(case3, array_fs_hb );
    FLIPLR_SUBCASE(case3, array_fs_db );

    // FLIPLR_SUBCASE(case3, array_hs_fb );
    // FLIPLR_SUBCASE(case3, array_hs_hb );
    // FLIPLR_SUBCASE(case3, array_hs_db );

    // FLIPLR_SUBCASE(case3, array_ds_fb );
    // FLIPLR_SUBCASE(case3, array_ds_hb );
    // FLIPLR_SUBCASE(case3, array_ds_db );
    #endif
}