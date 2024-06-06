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

#include "nmtools/array/array/flip.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/array/eval/hip.hpp"
#include "nmtools/testing/data/array/flip.hpp"
#include "nmtools/testing/data/array/fliplr.hpp"
#include "nmtools/testing/data/array/flipud.hpp"

namespace nm = nmtools;
namespace na = nm::array;

#define FLIP_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(flip, case_name); \
    using namespace args; \
    auto result = na::flip(__VA_ARGS__, na::hip::default_context()); \
    auto expect = na::flip(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

#define FLIPLR_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(fliplr, case_name); \
    using namespace args; \
    auto result = na::fliplr(__VA_ARGS__, na::hip::default_context()); \
    auto expect = na::fliplr(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

#define FLIPUD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(flipud, case_name); \
    using namespace args; \
    auto result = na::flipud(__VA_ARGS__, na::hip::default_context()); \
    auto expect = na::flipud(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

TEST_CASE("flip(case1)" * doctest::test_suite("array::flip"))
{
    // FLIP_SUBCASE(case1, array, axis);
    // FLIP_SUBCASE(case1, array_a, axis);
    // FLIP_SUBCASE(case1, array_f, axis);
    // FLIP_SUBCASE(case1, array_h, axis);
    // FLIP_SUBCASE(case1, array_d, axis);

    FLIP_SUBCASE(case1, array_cs_fb, axis);
    FLIP_SUBCASE(case1, array_cs_hb, axis);
    FLIP_SUBCASE(case1, array_cs_db, axis);

    FLIP_SUBCASE(case1, array_fs_fb, axis);
    FLIP_SUBCASE(case1, array_fs_hb, axis);
    FLIP_SUBCASE(case1, array_fs_db, axis);

    // TODO: fix, probably as_static doesn't work properly for flip args
    #if 0
    FLIP_SUBCASE(case1, array_hs_fb, axis);
    FLIP_SUBCASE(case1, array_hs_hb, axis);
    FLIP_SUBCASE(case1, array_hs_db, axis);

    FLIP_SUBCASE(case1, array_ds_fb, axis);
    FLIP_SUBCASE(case1, array_ds_hb, axis);
    FLIP_SUBCASE(case1, array_ds_db, axis);
    #endif

    FLIP_SUBCASE(case1, array_ls_fb, axis);
    FLIP_SUBCASE(case1, array_ls_hb, axis);
    FLIP_SUBCASE(case1, array_ls_db, axis);
}

TEST_CASE("flip(case2)" * doctest::test_suite("array::flip"))
{
    // FLIP_SUBCASE(case2, array, axis);
    // FLIP_SUBCASE(case2, array_a, axis);
    // FLIP_SUBCASE(case2, array_f, axis);
    // FLIP_SUBCASE(case2, array_h, axis);
    // FLIP_SUBCASE(case2, array_d, axis);

    FLIP_SUBCASE(case2, array_cs_fb, axis);
    FLIP_SUBCASE(case2, array_cs_hb, axis);
    FLIP_SUBCASE(case2, array_cs_db, axis);

    FLIP_SUBCASE(case2, array_fs_fb, axis);
    FLIP_SUBCASE(case2, array_fs_hb, axis);
    FLIP_SUBCASE(case2, array_fs_db, axis);

    // TODO: fix, probably as_static doesn't work properly for flip args
    #if 0
    FLIP_SUBCASE(case2, array_hs_fb, axis);
    FLIP_SUBCASE(case2, array_hs_hb, axis);
    FLIP_SUBCASE(case2, array_hs_db, axis);

    FLIP_SUBCASE(case2, array_ds_fb, axis);
    FLIP_SUBCASE(case2, array_ds_hb, axis);
    FLIP_SUBCASE(case2, array_ds_db, axis);
    #endif

    FLIP_SUBCASE(case2, array_ls_fb, axis);
    FLIP_SUBCASE(case2, array_ls_hb, axis);
    FLIP_SUBCASE(case2, array_ls_db, axis);
}

TEST_CASE("flip(case3)" * doctest::test_suite("array::flip"))
{
    // FLIP_SUBCASE(case3, array, axis);
    // FLIP_SUBCASE(case3, array_a, axis);
    // FLIP_SUBCASE(case3, array_f, axis);
    // FLIP_SUBCASE(case3, array_h, axis);
    // FLIP_SUBCASE(case3, array_d, axis);

    FLIP_SUBCASE(case3, array_cs_fb, axis);
    FLIP_SUBCASE(case3, array_cs_hb, axis);
    FLIP_SUBCASE(case3, array_cs_db, axis);

    FLIP_SUBCASE(case3, array_fs_fb, axis);
    FLIP_SUBCASE(case3, array_fs_hb, axis);
    FLIP_SUBCASE(case3, array_fs_db, axis);

    // TODO: fix, probably as_static doesn't work properly for flip args
    #if 0
    FLIP_SUBCASE(case3, array_hs_fb, axis);
    FLIP_SUBCASE(case3, array_hs_hb, axis);
    FLIP_SUBCASE(case3, array_hs_db, axis);

    FLIP_SUBCASE(case3, array_ds_fb, axis);
    FLIP_SUBCASE(case3, array_ds_hb, axis);
    FLIP_SUBCASE(case3, array_ds_db, axis);
    #endif

    FLIP_SUBCASE(case3, array_ls_fb, axis);
    FLIP_SUBCASE(case3, array_ls_hb, axis);
    FLIP_SUBCASE(case3, array_ls_db, axis);
}

TEST_CASE("flip(case4)" * doctest::test_suite("array::flip"))
{
    // FLIP_SUBCASE(case4, array, axis_a);
    // FLIP_SUBCASE(case4, array_a, axis_a);
    // FLIP_SUBCASE(case4, array_f, axis_a);
    // FLIP_SUBCASE(case4, array_h, axis_a);
    // FLIP_SUBCASE(case4, array_d, axis_a);

    FLIP_SUBCASE(case4, array_cs_fb, axis_a);
    FLIP_SUBCASE(case4, array_cs_hb, axis_a);
    FLIP_SUBCASE(case4, array_cs_db, axis_a);

    FLIP_SUBCASE(case4, array_fs_fb, axis_a);
    FLIP_SUBCASE(case4, array_fs_hb, axis_a);
    FLIP_SUBCASE(case4, array_fs_db, axis_a);

    // TODO: fix, probably as_static doesn't work properly for flip args
    #if 0
    FLIP_SUBCASE(case4, array_hs_fb, axis_a);
    FLIP_SUBCASE(case4, array_hs_hb, axis_a);
    FLIP_SUBCASE(case4, array_hs_db, axis_a);

    FLIP_SUBCASE(case4, array_ds_fb, axis_a);
    FLIP_SUBCASE(case4, array_ds_hb, axis_a);
    FLIP_SUBCASE(case4, array_ds_db, axis_a);
    #endif

    // FLIP_SUBCASE(case4, array_ls_fb, axis_a);
    // FLIP_SUBCASE(case4, array_ls_hb, axis_a);
    // FLIP_SUBCASE(case4, array_ls_db, axis_a);
}

TEST_CASE("fliplr(case1)" * doctest::test_suite("array::fliplr") )
{
    // FLIPLR_SUBCASE(case1, array );
    // FLIPLR_SUBCASE(case1, array_a );
    // FLIPLR_SUBCASE(case1, array_f );
    // FLIPLR_SUBCASE(case1, array_h );
    // FLIPLR_SUBCASE(case1, array_d );

    FLIPLR_SUBCASE(case1, array_cs_fb );
    FLIPLR_SUBCASE(case1, array_cs_hb );
    FLIPLR_SUBCASE(case1, array_cs_db );

    FLIPLR_SUBCASE(case1, array_fs_fb );
    FLIPLR_SUBCASE(case1, array_fs_hb );
    FLIPLR_SUBCASE(case1, array_fs_db );

    // TODO: fix, probably as_static doesn't work properly for flip args
    #if 0
    FLIPLR_SUBCASE(case1, array_hs_fb );
    FLIPLR_SUBCASE(case1, array_hs_hb );
    FLIPLR_SUBCASE(case1, array_hs_db );

    FLIPLR_SUBCASE(case1, array_ds_fb );
    FLIPLR_SUBCASE(case1, array_ds_hb );
    FLIPLR_SUBCASE(case1, array_ds_db );
    #endif

    FLIPLR_SUBCASE(case1, array_ls_fb );
    FLIPLR_SUBCASE(case1, array_ls_hb );
    FLIPLR_SUBCASE(case1, array_ls_db );
}

TEST_CASE("fliplr(case2)" * doctest::test_suite("array::fliplr"))
{
    // FLIPLR_SUBCASE(case2, array );
    // FLIPLR_SUBCASE(case2, array_a );
    // FLIPLR_SUBCASE(case2, array_f );
    // FLIPLR_SUBCASE(case2, array_h );
    // FLIPLR_SUBCASE(case2, array_d );

    FLIPLR_SUBCASE(case2, array_cs_fb );
    FLIPLR_SUBCASE(case2, array_cs_hb );
    FLIPLR_SUBCASE(case2, array_cs_db );

    FLIPLR_SUBCASE(case2, array_fs_fb );
    FLIPLR_SUBCASE(case2, array_fs_hb );
    FLIPLR_SUBCASE(case2, array_fs_db );

    // TODO: fix, probably as_static doesn't work properly for flip args
    #if 0
    FLIPLR_SUBCASE(case2, array_hs_fb );
    FLIPLR_SUBCASE(case2, array_hs_hb );
    FLIPLR_SUBCASE(case2, array_hs_db );

    FLIPLR_SUBCASE(case2, array_ds_fb );
    FLIPLR_SUBCASE(case2, array_ds_hb );
    FLIPLR_SUBCASE(case2, array_ds_db );
    #endif

    FLIPLR_SUBCASE(case2, array_ls_fb );
    FLIPLR_SUBCASE(case2, array_ls_hb );
    FLIPLR_SUBCASE(case2, array_ls_db );
}

TEST_CASE("fliplr(case3)" * doctest::test_suite("array::fliplr"))
{
    // FLIPLR_SUBCASE(case3, array );
    // FLIPLR_SUBCASE(case3, array_a );
    // FLIPLR_SUBCASE(case3, array_f );
    // FLIPLR_SUBCASE(case3, array_h );
    // FLIPLR_SUBCASE(case3, array_d );

    FLIPLR_SUBCASE(case3, array_cs_fb );
    FLIPLR_SUBCASE(case3, array_cs_hb );
    FLIPLR_SUBCASE(case3, array_cs_db );

    FLIPLR_SUBCASE(case3, array_fs_fb );
    FLIPLR_SUBCASE(case3, array_fs_hb );
    FLIPLR_SUBCASE(case3, array_fs_db );

    // TODO: fix, probably as_static doesn't work properly for flip args
    #if 0
    FLIPLR_SUBCASE(case3, array_hs_fb );
    FLIPLR_SUBCASE(case3, array_hs_hb );
    FLIPLR_SUBCASE(case3, array_hs_db );

    FLIPLR_SUBCASE(case3, array_ds_fb );
    FLIPLR_SUBCASE(case3, array_ds_hb );
    FLIPLR_SUBCASE(case3, array_ds_db );
    #endif

    FLIPLR_SUBCASE(case3, array_ls_fb );
    FLIPLR_SUBCASE(case3, array_ls_hb );
    FLIPLR_SUBCASE(case3, array_ls_db );
}

TEST_CASE("flipud(case1)" * doctest::test_suite("array::flipud") )
{
    // FLIPUD_SUBCASE(case1, array );
    // FLIPUD_SUBCASE(case1, array_a );
    // FLIPUD_SUBCASE(case1, array_f );
    // FLIPUD_SUBCASE(case1, array_h );
    // FLIPUD_SUBCASE(case1, array_d );

    FLIPUD_SUBCASE(case1, array_cs_fb );
    FLIPUD_SUBCASE(case1, array_cs_hb );
    FLIPUD_SUBCASE(case1, array_cs_db );

    FLIPUD_SUBCASE(case1, array_fs_fb );
    FLIPUD_SUBCASE(case1, array_fs_hb );
    FLIPUD_SUBCASE(case1, array_fs_db );

    // TODO: fix, probably as_static doesn't work properly for flip args
    #if 0
    FLIPUD_SUBCASE(case1, array_hs_fb );
    FLIPUD_SUBCASE(case1, array_hs_hb );
    FLIPUD_SUBCASE(case1, array_hs_db );

    FLIPUD_SUBCASE(case1, array_ds_fb );
    FLIPUD_SUBCASE(case1, array_ds_hb );
    FLIPUD_SUBCASE(case1, array_ds_db );
    #endif

    FLIPUD_SUBCASE(case1, array_ls_fb );
    FLIPUD_SUBCASE(case1, array_ls_hb );
    FLIPUD_SUBCASE(case1, array_ls_db );
}

TEST_CASE("flipud(case2)" * doctest::test_suite("array::flipud"))
{
    // FLIPUD_SUBCASE(case2, array );
    // FLIPUD_SUBCASE(case2, array_a );
    // FLIPUD_SUBCASE(case2, array_f );
    // FLIPUD_SUBCASE(case2, array_h );
    // FLIPUD_SUBCASE(case2, array_d );

    FLIPUD_SUBCASE(case2, array_cs_fb );
    FLIPUD_SUBCASE(case2, array_cs_hb );
    FLIPUD_SUBCASE(case2, array_cs_db );

    FLIPUD_SUBCASE(case2, array_fs_fb );
    FLIPUD_SUBCASE(case2, array_fs_hb );
    FLIPUD_SUBCASE(case2, array_fs_db );

    // TODO: fix, probably as_static doesn't work properly for flip args
    #if 0
    FLIPUD_SUBCASE(case2, array_hs_fb );
    FLIPUD_SUBCASE(case2, array_hs_hb );
    FLIPUD_SUBCASE(case2, array_hs_db );

    FLIPUD_SUBCASE(case2, array_ds_fb );
    FLIPUD_SUBCASE(case2, array_ds_hb );
    FLIPUD_SUBCASE(case2, array_ds_db );
    #endif

    FLIPUD_SUBCASE(case2, array_ls_fb );
    FLIPUD_SUBCASE(case2, array_ls_hb );
    FLIPUD_SUBCASE(case2, array_ls_db );
}

TEST_CASE("flipud(case3)" * doctest::test_suite("array::flipud"))
{
    // FLIPUD_SUBCASE(case3, array );
    // FLIPUD_SUBCASE(case3, array_a );
    // FLIPUD_SUBCASE(case3, array_f );
    // FLIPUD_SUBCASE(case3, array_h );
    // FLIPUD_SUBCASE(case3, array_d );

    FLIPUD_SUBCASE(case3, array_cs_fb );
    FLIPUD_SUBCASE(case3, array_cs_hb );
    FLIPUD_SUBCASE(case3, array_cs_db );

    FLIPUD_SUBCASE(case3, array_fs_fb );
    FLIPUD_SUBCASE(case3, array_fs_hb );
    FLIPUD_SUBCASE(case3, array_fs_db );

    // TODO: fix, probably as_static doesn't work properly for flip args
    #if 0
    FLIPUD_SUBCASE(case3, array_hs_fb );
    FLIPUD_SUBCASE(case3, array_hs_hb );
    FLIPUD_SUBCASE(case3, array_hs_db );

    FLIPUD_SUBCASE(case3, array_ds_fb );
    FLIPUD_SUBCASE(case3, array_ds_hb );
    FLIPUD_SUBCASE(case3, array_ds_db );
    #endif

    FLIPUD_SUBCASE(case3, array_ls_fb );
    FLIPUD_SUBCASE(case3, array_ls_hb );
    FLIPUD_SUBCASE(case3, array_ls_db );
}