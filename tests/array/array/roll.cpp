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

#include "nmtools/array/array/roll.hpp"
#include "nmtools/testing/data/array/roll.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;

#define ROLL_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(roll, case_name) \
    using namespace args; \
    auto result = na::roll(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("roll(case1a)" * doctest::test_suite("array::roll"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    ROLL_SUBCASE( case1a, array, shift );
    ROLL_SUBCASE( case1a, array_a, shift );
    ROLL_SUBCASE( case1a, array_f, shift );
    ROLL_SUBCASE( case1a, array_d, shift );
    ROLL_SUBCASE( case1a, array_h, shift );

    ROLL_SUBCASE( case1a, array, shift_ct );
    ROLL_SUBCASE( case1a, array_a, shift_ct );
    ROLL_SUBCASE( case1a, array_f, shift_ct );
    ROLL_SUBCASE( case1a, array_d, shift_ct );
    ROLL_SUBCASE( case1a, array_h, shift_ct );

    ROLL_SUBCASE( case1a, array, shift_cl );
    ROLL_SUBCASE( case1a, array_a, shift_cl );
    ROLL_SUBCASE( case1a, array_f, shift_cl );
    ROLL_SUBCASE( case1a, array_d, shift_cl );
    ROLL_SUBCASE( case1a, array_h, shift_cl );
    #else
    ROLL_SUBCASE( case1a, array_cs_fb, shift );
    ROLL_SUBCASE( case1a, array_cs_hb, shift );
    ROLL_SUBCASE( case1a, array_cs_db, shift );

    ROLL_SUBCASE( case1a, array_fs_fb, shift );
    ROLL_SUBCASE( case1a, array_fs_hb, shift );
    ROLL_SUBCASE( case1a, array_fs_db, shift );

    ROLL_SUBCASE( case1a, array_hs_fb, shift );
    ROLL_SUBCASE( case1a, array_hs_hb, shift );
    ROLL_SUBCASE( case1a, array_hs_db, shift );

    ROLL_SUBCASE( case1a, array_ds_fb, shift );
    ROLL_SUBCASE( case1a, array_ds_hb, shift );
    ROLL_SUBCASE( case1a, array_ds_db, shift );

    ROLL_SUBCASE( case1a, array_ls_fb, shift );
    ROLL_SUBCASE( case1a, array_ls_hb, shift );
    ROLL_SUBCASE( case1a, array_ls_db, shift );

    ROLL_SUBCASE( case1a, array_cs_fb, shift_ct );
    ROLL_SUBCASE( case1a, array_cs_hb, shift_ct );
    ROLL_SUBCASE( case1a, array_cs_db, shift_ct );

    ROLL_SUBCASE( case1a, array_fs_fb, shift_ct );
    ROLL_SUBCASE( case1a, array_fs_hb, shift_ct );
    ROLL_SUBCASE( case1a, array_fs_db, shift_ct );

    ROLL_SUBCASE( case1a, array_hs_fb, shift_ct );
    ROLL_SUBCASE( case1a, array_hs_hb, shift_ct );
    ROLL_SUBCASE( case1a, array_hs_db, shift_ct );

    ROLL_SUBCASE( case1a, array_ds_fb, shift_ct );
    ROLL_SUBCASE( case1a, array_ds_hb, shift_ct );
    ROLL_SUBCASE( case1a, array_ds_db, shift_ct );

    ROLL_SUBCASE( case1a, array_ls_fb, shift_ct );
    ROLL_SUBCASE( case1a, array_ls_hb, shift_ct );
    ROLL_SUBCASE( case1a, array_ls_db, shift_ct );

    ROLL_SUBCASE( case1a, array_cs_fb, shift_cl );
    ROLL_SUBCASE( case1a, array_cs_hb, shift_cl );
    ROLL_SUBCASE( case1a, array_cs_db, shift_cl );

    ROLL_SUBCASE( case1a, array_fs_fb, shift_cl );
    ROLL_SUBCASE( case1a, array_fs_hb, shift_cl );
    ROLL_SUBCASE( case1a, array_fs_db, shift_cl );

    ROLL_SUBCASE( case1a, array_hs_fb, shift_cl );
    ROLL_SUBCASE( case1a, array_hs_hb, shift_cl );
    ROLL_SUBCASE( case1a, array_hs_db, shift_cl );

    ROLL_SUBCASE( case1a, array_ds_fb, shift_cl );
    ROLL_SUBCASE( case1a, array_ds_hb, shift_cl );
    ROLL_SUBCASE( case1a, array_ds_db, shift_cl );

    ROLL_SUBCASE( case1a, array_ls_fb, shift_cl );
    ROLL_SUBCASE( case1a, array_ls_hb, shift_cl );
    ROLL_SUBCASE( case1a, array_ls_db, shift_cl );
    #endif
}

TEST_CASE("roll(case1b)" * doctest::test_suite("array::roll"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    ROLL_SUBCASE( case1b, array, shift );
    ROLL_SUBCASE( case1b, array_a, shift );
    ROLL_SUBCASE( case1b, array_f, shift );
    ROLL_SUBCASE( case1b, array_d, shift );
    ROLL_SUBCASE( case1b, array_h, shift );
    #else
    ROLL_SUBCASE( case1b, array_cs_fb, shift );
    ROLL_SUBCASE( case1b, array_cs_hb, shift );
    ROLL_SUBCASE( case1b, array_cs_db, shift );

    ROLL_SUBCASE( case1b, array_fs_fb, shift );
    ROLL_SUBCASE( case1b, array_fs_hb, shift );
    ROLL_SUBCASE( case1b, array_fs_db, shift );

    ROLL_SUBCASE( case1b, array_hs_fb, shift );
    ROLL_SUBCASE( case1b, array_hs_hb, shift );
    ROLL_SUBCASE( case1b, array_hs_db, shift );

    ROLL_SUBCASE( case1b, array_ds_fb, shift );
    ROLL_SUBCASE( case1b, array_ds_hb, shift );
    ROLL_SUBCASE( case1b, array_ds_db, shift );

    ROLL_SUBCASE( case1b, array_ls_fb, shift );
    ROLL_SUBCASE( case1b, array_ls_hb, shift );
    ROLL_SUBCASE( case1b, array_ls_db, shift );
    #endif
}

TEST_CASE("roll(case1c)" * doctest::test_suite("array::roll"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    ROLL_SUBCASE( case1c, array, shift );
    ROLL_SUBCASE( case1c, array_a, shift );
    ROLL_SUBCASE( case1c, array_f, shift );
    ROLL_SUBCASE( case1c, array_d, shift );
    ROLL_SUBCASE( case1c, array_h, shift );
    #else
    ROLL_SUBCASE( case1c, array_cs_fb, shift );
    ROLL_SUBCASE( case1c, array_cs_hb, shift );
    ROLL_SUBCASE( case1c, array_cs_db, shift );

    ROLL_SUBCASE( case1c, array_fs_fb, shift );
    ROLL_SUBCASE( case1c, array_fs_hb, shift );
    ROLL_SUBCASE( case1c, array_fs_db, shift );

    ROLL_SUBCASE( case1c, array_hs_fb, shift );
    ROLL_SUBCASE( case1c, array_hs_hb, shift );
    ROLL_SUBCASE( case1c, array_hs_db, shift );

    ROLL_SUBCASE( case1c, array_ds_fb, shift );
    ROLL_SUBCASE( case1c, array_ds_hb, shift );
    ROLL_SUBCASE( case1c, array_ds_db, shift );

    ROLL_SUBCASE( case1c, array_ls_fb, shift );
    ROLL_SUBCASE( case1c, array_ls_hb, shift );
    ROLL_SUBCASE( case1c, array_ls_db, shift );
    #endif
}

TEST_CASE("roll(case2a)" * doctest::test_suite("array::roll"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    ROLL_SUBCASE( case2a, array, shift );
    ROLL_SUBCASE( case2a, array_a, shift );
    ROLL_SUBCASE( case2a, array_f, shift );
    ROLL_SUBCASE( case2a, array_d, shift );
    ROLL_SUBCASE( case2a, array_h, shift );

    ROLL_SUBCASE( case2a, array, shift_ct );
    ROLL_SUBCASE( case2a, array_a, shift_ct );
    ROLL_SUBCASE( case2a, array_f, shift_ct );
    ROLL_SUBCASE( case2a, array_d, shift_ct );
    ROLL_SUBCASE( case2a, array_h, shift_ct );

    ROLL_SUBCASE( case2a, array, shift_cl );
    ROLL_SUBCASE( case2a, array_a, shift_cl );
    ROLL_SUBCASE( case2a, array_f, shift_cl );
    ROLL_SUBCASE( case2a, array_d, shift_cl );
    ROLL_SUBCASE( case2a, array_h, shift_cl );
    #else
    ROLL_SUBCASE( case2a, array_cs_fb, shift );
    ROLL_SUBCASE( case2a, array_cs_hb, shift );
    ROLL_SUBCASE( case2a, array_cs_db, shift );

    ROLL_SUBCASE( case2a, array_fs_fb, shift );
    ROLL_SUBCASE( case2a, array_fs_hb, shift );
    ROLL_SUBCASE( case2a, array_fs_db, shift );

    ROLL_SUBCASE( case2a, array_hs_fb, shift );
    ROLL_SUBCASE( case2a, array_hs_hb, shift );
    ROLL_SUBCASE( case2a, array_hs_db, shift );

    ROLL_SUBCASE( case2a, array_ds_fb, shift );
    ROLL_SUBCASE( case2a, array_ds_hb, shift );
    ROLL_SUBCASE( case2a, array_ds_db, shift );

    ROLL_SUBCASE( case2a, array_ls_fb, shift );
    ROLL_SUBCASE( case2a, array_ls_hb, shift );
    ROLL_SUBCASE( case2a, array_ls_db, shift );

    ROLL_SUBCASE( case2a, array_cs_fb, shift_ct );
    ROLL_SUBCASE( case2a, array_cs_hb, shift_ct );
    ROLL_SUBCASE( case2a, array_cs_db, shift_ct );

    ROLL_SUBCASE( case2a, array_fs_fb, shift_ct );
    ROLL_SUBCASE( case2a, array_fs_hb, shift_ct );
    ROLL_SUBCASE( case2a, array_fs_db, shift_ct );

    ROLL_SUBCASE( case2a, array_hs_fb, shift_ct );
    ROLL_SUBCASE( case2a, array_hs_hb, shift_ct );
    ROLL_SUBCASE( case2a, array_hs_db, shift_ct );

    ROLL_SUBCASE( case2a, array_ds_fb, shift_ct );
    ROLL_SUBCASE( case2a, array_ds_hb, shift_ct );
    ROLL_SUBCASE( case2a, array_ds_db, shift_ct );

    ROLL_SUBCASE( case2a, array_ls_fb, shift_ct );
    ROLL_SUBCASE( case2a, array_ls_hb, shift_ct );
    ROLL_SUBCASE( case2a, array_ls_db, shift_ct );

    ROLL_SUBCASE( case2a, array_cs_fb, shift_cl );
    ROLL_SUBCASE( case2a, array_cs_hb, shift_cl );
    ROLL_SUBCASE( case2a, array_cs_db, shift_cl );

    ROLL_SUBCASE( case2a, array_fs_fb, shift_cl );
    ROLL_SUBCASE( case2a, array_fs_hb, shift_cl );
    ROLL_SUBCASE( case2a, array_fs_db, shift_cl );

    ROLL_SUBCASE( case2a, array_hs_fb, shift_cl );
    ROLL_SUBCASE( case2a, array_hs_hb, shift_cl );
    ROLL_SUBCASE( case2a, array_hs_db, shift_cl );

    ROLL_SUBCASE( case2a, array_ds_fb, shift_cl );
    ROLL_SUBCASE( case2a, array_ds_hb, shift_cl );
    ROLL_SUBCASE( case2a, array_ds_db, shift_cl );

    ROLL_SUBCASE( case2a, array_ls_fb, shift_cl );
    ROLL_SUBCASE( case2a, array_ls_hb, shift_cl );
    ROLL_SUBCASE( case2a, array_ls_db, shift_cl );
    #endif
}

TEST_CASE("roll(case2b)" * doctest::test_suite("array::roll"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    ROLL_SUBCASE( case2b, array, shift );
    ROLL_SUBCASE( case2b, array_a, shift );
    ROLL_SUBCASE( case2b, array_f, shift );
    ROLL_SUBCASE( case2b, array_d, shift );
    ROLL_SUBCASE( case2b, array_h, shift );
    #else
    ROLL_SUBCASE( case2b, array_cs_fb, shift );
    ROLL_SUBCASE( case2b, array_cs_hb, shift );
    ROLL_SUBCASE( case2b, array_cs_db, shift );

    ROLL_SUBCASE( case2b, array_fs_fb, shift );
    ROLL_SUBCASE( case2b, array_fs_hb, shift );
    ROLL_SUBCASE( case2b, array_fs_db, shift );

    ROLL_SUBCASE( case2b, array_hs_fb, shift );
    ROLL_SUBCASE( case2b, array_hs_hb, shift );
    ROLL_SUBCASE( case2b, array_hs_db, shift );

    ROLL_SUBCASE( case2b, array_ds_fb, shift );
    ROLL_SUBCASE( case2b, array_ds_hb, shift );
    ROLL_SUBCASE( case2b, array_ds_db, shift );

    ROLL_SUBCASE( case2b, array_ls_fb, shift );
    ROLL_SUBCASE( case2b, array_ls_hb, shift );
    ROLL_SUBCASE( case2b, array_ls_db, shift );
    #endif
}

TEST_CASE("roll(case2c)" * doctest::test_suite("array::roll"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    ROLL_SUBCASE( case2c, array, shift, axis );
    ROLL_SUBCASE( case2c, array_a, shift, axis );
    ROLL_SUBCASE( case2c, array_f, shift, axis );
    ROLL_SUBCASE( case2c, array_d, shift, axis );
    ROLL_SUBCASE( case2c, array_h, shift, axis );

    ROLL_SUBCASE( case2c, array, shift_ct, axis_ct );
    ROLL_SUBCASE( case2c, array_a, shift_ct, axis_ct );
    ROLL_SUBCASE( case2c, array_f, shift_ct, axis_ct );
    ROLL_SUBCASE( case2c, array_d, shift_ct, axis_ct );
    ROLL_SUBCASE( case2c, array_h, shift_ct, axis_ct );

    ROLL_SUBCASE( case2c, array, shift_cl, axis_cl );
    ROLL_SUBCASE( case2c, array_a, shift_cl, axis_cl );
    ROLL_SUBCASE( case2c, array_f, shift_cl, axis_cl );
    ROLL_SUBCASE( case2c, array_d, shift_cl, axis_cl );
    ROLL_SUBCASE( case2c, array_h, shift_cl, axis_cl );

    ROLL_SUBCASE( case2c, array, shift_ct, axis_cl );
    ROLL_SUBCASE( case2c, array_a, shift_ct, axis_cl );
    ROLL_SUBCASE( case2c, array_f, shift_ct, axis_cl );
    ROLL_SUBCASE( case2c, array_d, shift_ct, axis_cl );
    ROLL_SUBCASE( case2c, array_h, shift_ct, axis_cl );

    ROLL_SUBCASE( case2c, array, shift_ct, axis_ct );
    ROLL_SUBCASE( case2c, array_a, shift_ct, axis_ct );
    ROLL_SUBCASE( case2c, array_f, shift_ct, axis_ct );
    ROLL_SUBCASE( case2c, array_d, shift_ct, axis_ct );
    ROLL_SUBCASE( case2c, array_h, shift_ct, axis_ct );
    #else
    ROLL_SUBCASE( case2c, array_cs_fb, shift, axis );
    ROLL_SUBCASE( case2c, array_cs_hb, shift, axis );
    ROLL_SUBCASE( case2c, array_cs_db, shift, axis );

    ROLL_SUBCASE( case2c, array_fs_fb, shift, axis );
    ROLL_SUBCASE( case2c, array_fs_hb, shift, axis );
    ROLL_SUBCASE( case2c, array_fs_db, shift, axis );

    ROLL_SUBCASE( case2c, array_hs_fb, shift, axis );
    ROLL_SUBCASE( case2c, array_hs_hb, shift, axis );
    ROLL_SUBCASE( case2c, array_hs_db, shift, axis );

    ROLL_SUBCASE( case2c, array_ds_fb, shift, axis );
    ROLL_SUBCASE( case2c, array_ds_hb, shift, axis );
    ROLL_SUBCASE( case2c, array_ds_db, shift, axis );

    ROLL_SUBCASE( case2c, array_ls_fb, shift, axis );
    ROLL_SUBCASE( case2c, array_ls_hb, shift, axis );
    ROLL_SUBCASE( case2c, array_ls_db, shift, axis );

    ROLL_SUBCASE( case2c, array_cs_fb, shift_ct, axis_ct );
    ROLL_SUBCASE( case2c, array_cs_hb, shift_ct, axis_ct );
    ROLL_SUBCASE( case2c, array_cs_db, shift_ct, axis_ct );

    ROLL_SUBCASE( case2c, array_fs_fb, shift_ct, axis_ct );
    ROLL_SUBCASE( case2c, array_fs_hb, shift_ct, axis_ct );
    ROLL_SUBCASE( case2c, array_fs_db, shift_ct, axis_ct );

    ROLL_SUBCASE( case2c, array_hs_fb, shift_ct, axis_ct );
    ROLL_SUBCASE( case2c, array_hs_hb, shift_ct, axis_ct );
    ROLL_SUBCASE( case2c, array_hs_db, shift_ct, axis_ct );

    ROLL_SUBCASE( case2c, array_ds_fb, shift_ct, axis_ct );
    ROLL_SUBCASE( case2c, array_ds_hb, shift_ct, axis_ct );
    ROLL_SUBCASE( case2c, array_ds_db, shift_ct, axis_ct );

    ROLL_SUBCASE( case2c, array_ls_fb, shift_ct, axis_ct );
    ROLL_SUBCASE( case2c, array_ls_hb, shift_ct, axis_ct );
    ROLL_SUBCASE( case2c, array_ls_db, shift_ct, axis_ct );

    ROLL_SUBCASE( case2c, array_cs_fb, shift_cl, axis_cl );
    ROLL_SUBCASE( case2c, array_cs_hb, shift_cl, axis_cl );
    ROLL_SUBCASE( case2c, array_cs_db, shift_cl, axis_cl );

    ROLL_SUBCASE( case2c, array_fs_fb, shift_cl, axis_cl );
    ROLL_SUBCASE( case2c, array_fs_hb, shift_cl, axis_cl );
    ROLL_SUBCASE( case2c, array_fs_db, shift_cl, axis_cl );

    ROLL_SUBCASE( case2c, array_hs_fb, shift_cl, axis_cl );
    ROLL_SUBCASE( case2c, array_hs_hb, shift_cl, axis_cl );
    ROLL_SUBCASE( case2c, array_hs_db, shift_cl, axis_cl );

    ROLL_SUBCASE( case2c, array_ds_fb, shift_cl, axis_cl );
    ROLL_SUBCASE( case2c, array_ds_hb, shift_cl, axis_cl );
    ROLL_SUBCASE( case2c, array_ds_db, shift_cl, axis_cl );

    ROLL_SUBCASE( case2c, array_ls_fb, shift_cl, axis_cl );
    ROLL_SUBCASE( case2c, array_ls_hb, shift_cl, axis_cl );
    ROLL_SUBCASE( case2c, array_ls_db, shift_cl, axis_cl );
    #endif
}

TEST_CASE("roll(case2d)" * doctest::test_suite("array::roll"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    ROLL_SUBCASE( case2d, array, shift, axis );
    ROLL_SUBCASE( case2d, array_a, shift, axis );
    ROLL_SUBCASE( case2d, array_f, shift, axis );
    ROLL_SUBCASE( case2d, array_d, shift, axis );
    ROLL_SUBCASE( case2d, array_h, shift, axis );

    ROLL_SUBCASE( case2d, array, shift_ct, axis_ct );
    ROLL_SUBCASE( case2d, array_a, shift_ct, axis_ct );
    ROLL_SUBCASE( case2d, array_f, shift_ct, axis_ct );
    ROLL_SUBCASE( case2d, array_d, shift_ct, axis_ct );
    ROLL_SUBCASE( case2d, array_h, shift_ct, axis_ct );

    ROLL_SUBCASE( case2d, array, shift_cl, axis_cl );
    ROLL_SUBCASE( case2d, array_a, shift_cl, axis_cl );
    ROLL_SUBCASE( case2d, array_f, shift_cl, axis_cl );
    ROLL_SUBCASE( case2d, array_d, shift_cl, axis_cl );
    ROLL_SUBCASE( case2d, array_h, shift_cl, axis_cl );
    #else
    ROLL_SUBCASE( case2d, array_cs_fb, shift, axis );
    ROLL_SUBCASE( case2d, array_cs_hb, shift, axis );
    ROLL_SUBCASE( case2d, array_cs_db, shift, axis );

    ROLL_SUBCASE( case2d, array_fs_fb, shift, axis );
    ROLL_SUBCASE( case2d, array_fs_hb, shift, axis );
    ROLL_SUBCASE( case2d, array_fs_db, shift, axis );

    ROLL_SUBCASE( case2d, array_hs_fb, shift, axis );
    ROLL_SUBCASE( case2d, array_hs_hb, shift, axis );
    ROLL_SUBCASE( case2d, array_hs_db, shift, axis );

    ROLL_SUBCASE( case2d, array_ds_fb, shift, axis );
    ROLL_SUBCASE( case2d, array_ds_hb, shift, axis );
    ROLL_SUBCASE( case2d, array_ds_db, shift, axis );

    ROLL_SUBCASE( case2d, array_ls_fb, shift, axis );
    ROLL_SUBCASE( case2d, array_ls_hb, shift, axis );
    ROLL_SUBCASE( case2d, array_ls_db, shift, axis );

    ROLL_SUBCASE( case2d, array_cs_fb, shift_ct, axis_ct );
    ROLL_SUBCASE( case2d, array_cs_hb, shift_ct, axis_ct );
    ROLL_SUBCASE( case2d, array_cs_db, shift_ct, axis_ct );

    ROLL_SUBCASE( case2d, array_fs_fb, shift_ct, axis_ct );
    ROLL_SUBCASE( case2d, array_fs_hb, shift_ct, axis_ct );
    ROLL_SUBCASE( case2d, array_fs_db, shift_ct, axis_ct );

    ROLL_SUBCASE( case2d, array_hs_fb, shift_ct, axis_ct );
    ROLL_SUBCASE( case2d, array_hs_hb, shift_ct, axis_ct );
    ROLL_SUBCASE( case2d, array_hs_db, shift_ct, axis_ct );

    ROLL_SUBCASE( case2d, array_ds_fb, shift_ct, axis_ct );
    ROLL_SUBCASE( case2d, array_ds_hb, shift_ct, axis_ct );
    ROLL_SUBCASE( case2d, array_ds_db, shift_ct, axis_ct );

    ROLL_SUBCASE( case2d, array_ls_fb, shift_ct, axis_ct );
    ROLL_SUBCASE( case2d, array_ls_hb, shift_ct, axis_ct );
    ROLL_SUBCASE( case2d, array_ls_db, shift_ct, axis_ct );

    ROLL_SUBCASE( case2d, array_cs_fb, shift_cl, axis_cl );
    ROLL_SUBCASE( case2d, array_cs_hb, shift_cl, axis_cl );
    ROLL_SUBCASE( case2d, array_cs_db, shift_cl, axis_cl );

    ROLL_SUBCASE( case2d, array_fs_fb, shift_cl, axis );
    ROLL_SUBCASE( case2d, array_fs_hb, shift_cl, axis );
    ROLL_SUBCASE( case2d, array_fs_db, shift_cl, axis );

    ROLL_SUBCASE( case2d, array_hs_fb, shift_cl, axis_cl );
    ROLL_SUBCASE( case2d, array_hs_hb, shift_cl, axis_cl );
    ROLL_SUBCASE( case2d, array_hs_db, shift_cl, axis_cl );

    ROLL_SUBCASE( case2d, array_ds_fb, shift_cl, axis_cl );
    ROLL_SUBCASE( case2d, array_ds_hb, shift_cl, axis_cl );
    ROLL_SUBCASE( case2d, array_ds_db, shift_cl, axis_cl );

    ROLL_SUBCASE( case2d, array_ls_fb, shift_cl, axis_cl );
    ROLL_SUBCASE( case2d, array_ls_hb, shift_cl, axis_cl );
    ROLL_SUBCASE( case2d, array_ls_db, shift_cl, axis_cl );
    #endif
}

TEST_CASE("roll(case2e)" * doctest::test_suite("array::roll"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    ROLL_SUBCASE( case2e, array, shift, axis );
    ROLL_SUBCASE( case2e, array_a, shift, axis );
    ROLL_SUBCASE( case2e, array_f, shift, axis );
    ROLL_SUBCASE( case2e, array_d, shift, axis );
    ROLL_SUBCASE( case2e, array_h, shift, axis );

    ROLL_SUBCASE( case2e, array, shift_ct, axis_ct );
    ROLL_SUBCASE( case2e, array_a, shift_ct, axis_ct );
    ROLL_SUBCASE( case2e, array_f, shift_ct, axis_ct );
    ROLL_SUBCASE( case2e, array_d, shift_ct, axis_ct );
    ROLL_SUBCASE( case2e, array_h, shift_ct, axis_ct );

    ROLL_SUBCASE( case2e, array, shift_cl, axis_cl );
    ROLL_SUBCASE( case2e, array_a, shift_cl, axis_cl );
    ROLL_SUBCASE( case2e, array_f, shift_cl, axis_cl );
    ROLL_SUBCASE( case2e, array_d, shift_cl, axis_cl );
    ROLL_SUBCASE( case2e, array_h, shift_cl, axis_cl );
    #else
    ROLL_SUBCASE( case2e, array_cs_fb, shift, axis );
    ROLL_SUBCASE( case2e, array_cs_hb, shift, axis );
    ROLL_SUBCASE( case2e, array_cs_db, shift, axis );

    ROLL_SUBCASE( case2e, array_fs_fb, shift, axis );
    ROLL_SUBCASE( case2e, array_fs_hb, shift, axis );
    ROLL_SUBCASE( case2e, array_fs_db, shift, axis );

    ROLL_SUBCASE( case2e, array_hs_fb, shift, axis );
    ROLL_SUBCASE( case2e, array_hs_hb, shift, axis );
    ROLL_SUBCASE( case2e, array_hs_db, shift, axis );

    ROLL_SUBCASE( case2e, array_ds_fb, shift, axis );
    ROLL_SUBCASE( case2e, array_ds_hb, shift, axis );
    ROLL_SUBCASE( case2e, array_ds_db, shift, axis );

    ROLL_SUBCASE( case2e, array_ls_fb, shift, axis );
    ROLL_SUBCASE( case2e, array_ls_hb, shift, axis );
    ROLL_SUBCASE( case2e, array_ls_db, shift, axis );

    ROLL_SUBCASE( case2e, array_cs_fb, shift_ct, axis_ct );
    ROLL_SUBCASE( case2e, array_cs_hb, shift_ct, axis_ct );
    ROLL_SUBCASE( case2e, array_cs_db, shift_ct, axis_ct );

    ROLL_SUBCASE( case2e, array_fs_fb, shift_ct, axis_ct );
    ROLL_SUBCASE( case2e, array_fs_hb, shift_ct, axis_ct );
    ROLL_SUBCASE( case2e, array_fs_db, shift_ct, axis_ct );

    ROLL_SUBCASE( case2e, array_hs_fb, shift_ct, axis_ct );
    ROLL_SUBCASE( case2e, array_hs_hb, shift_ct, axis_ct );
    ROLL_SUBCASE( case2e, array_hs_db, shift_ct, axis_ct );

    ROLL_SUBCASE( case2e, array_ds_fb, shift_ct, axis_ct );
    ROLL_SUBCASE( case2e, array_ds_hb, shift_ct, axis_ct );
    ROLL_SUBCASE( case2e, array_ds_db, shift_ct, axis_ct );

    ROLL_SUBCASE( case2e, array_ls_fb, shift_ct, axis_ct );
    ROLL_SUBCASE( case2e, array_ls_hb, shift_ct, axis_ct );
    ROLL_SUBCASE( case2e, array_ls_db, shift_ct, axis_ct );

    ROLL_SUBCASE( case2e, array_cs_fb, shift_cl, axis_cl );
    ROLL_SUBCASE( case2e, array_cs_hb, shift_cl, axis_cl );
    ROLL_SUBCASE( case2e, array_cs_db, shift_cl, axis_cl );

    ROLL_SUBCASE( case2e, array_fs_fb, shift_cl, axis_cl );
    ROLL_SUBCASE( case2e, array_fs_hb, shift_cl, axis_cl );
    ROLL_SUBCASE( case2e, array_fs_db, shift_cl, axis_cl );

    ROLL_SUBCASE( case2e, array_hs_fb, shift_cl, axis_cl );
    ROLL_SUBCASE( case2e, array_hs_hb, shift_cl, axis_cl );
    ROLL_SUBCASE( case2e, array_hs_db, shift_cl, axis_cl );

    ROLL_SUBCASE( case2e, array_ds_fb, shift_cl, axis_cl );
    ROLL_SUBCASE( case2e, array_ds_hb, shift_cl, axis_cl );
    ROLL_SUBCASE( case2e, array_ds_db, shift_cl, axis_cl );

    ROLL_SUBCASE( case2e, array_ls_fb, shift_cl, axis_cl );
    ROLL_SUBCASE( case2e, array_ls_hb, shift_cl, axis_cl );
    ROLL_SUBCASE( case2e, array_ls_db, shift_cl, axis_cl );
    #endif
}

TEST_CASE("roll(case3a)" * doctest::test_suite("array::roll"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    ROLL_SUBCASE( case3a, array, shift );
    ROLL_SUBCASE( case3a, array_a, shift );
    ROLL_SUBCASE( case3a, array_f, shift );
    ROLL_SUBCASE( case3a, array_d, shift );
    ROLL_SUBCASE( case3a, array_h, shift );
    #else
    ROLL_SUBCASE( case3a, array_cs_fb, shift );
    ROLL_SUBCASE( case3a, array_cs_hb, shift );
    ROLL_SUBCASE( case3a, array_cs_db, shift );

    ROLL_SUBCASE( case3a, array_fs_fb, shift );
    ROLL_SUBCASE( case3a, array_fs_hb, shift );
    ROLL_SUBCASE( case3a, array_fs_db, shift );

    ROLL_SUBCASE( case3a, array_hs_fb, shift );
    ROLL_SUBCASE( case3a, array_hs_hb, shift );
    ROLL_SUBCASE( case3a, array_hs_db, shift );

    ROLL_SUBCASE( case3a, array_ds_fb, shift );
    ROLL_SUBCASE( case3a, array_ds_hb, shift );
    ROLL_SUBCASE( case3a, array_ds_db, shift );

    ROLL_SUBCASE( case3a, array_ls_fb, shift );
    ROLL_SUBCASE( case3a, array_ls_hb, shift );
    ROLL_SUBCASE( case3a, array_ls_db, shift );
    #endif
}

TEST_CASE("roll(case3b)" * doctest::test_suite("array::roll"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    ROLL_SUBCASE( case3b, array, shift, axis );
    ROLL_SUBCASE( case3b, array_a, shift, axis );
    ROLL_SUBCASE( case3b, array_f, shift, axis );
    ROLL_SUBCASE( case3b, array_d, shift, axis );
    ROLL_SUBCASE( case3b, array_h, shift, axis );
    #else
    ROLL_SUBCASE( case3b, array_cs_fb, shift, axis );
    ROLL_SUBCASE( case3b, array_cs_hb, shift, axis );
    ROLL_SUBCASE( case3b, array_cs_db, shift, axis );

    ROLL_SUBCASE( case3b, array_fs_fb, shift, axis );
    ROLL_SUBCASE( case3b, array_fs_hb, shift, axis );
    ROLL_SUBCASE( case3b, array_fs_db, shift, axis );

    ROLL_SUBCASE( case3b, array_hs_fb, shift, axis );
    ROLL_SUBCASE( case3b, array_hs_hb, shift, axis );
    ROLL_SUBCASE( case3b, array_hs_db, shift, axis );

    ROLL_SUBCASE( case3b, array_ds_fb, shift, axis );
    ROLL_SUBCASE( case3b, array_ds_hb, shift, axis );
    ROLL_SUBCASE( case3b, array_ds_db, shift, axis );

    ROLL_SUBCASE( case3b, array_ls_fb, shift, axis );
    ROLL_SUBCASE( case3b, array_ls_hb, shift, axis );
    ROLL_SUBCASE( case3b, array_ls_db, shift, axis );
    #endif
}

TEST_CASE("roll(case3c)" * doctest::test_suite("array::roll"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    ROLL_SUBCASE( case3c, array, shift, axis );
    ROLL_SUBCASE( case3c, array_a, shift, axis );
    ROLL_SUBCASE( case3c, array_f, shift, axis );
    ROLL_SUBCASE( case3c, array_d, shift, axis );
    ROLL_SUBCASE( case3c, array_h, shift, axis );
    #else
    ROLL_SUBCASE( case3c, array_cs_fb, shift, axis );
    ROLL_SUBCASE( case3c, array_cs_hb, shift, axis );
    ROLL_SUBCASE( case3c, array_cs_db, shift, axis );

    ROLL_SUBCASE( case3c, array_fs_fb, shift, axis );
    ROLL_SUBCASE( case3c, array_fs_hb, shift, axis );
    ROLL_SUBCASE( case3c, array_fs_db, shift, axis );

    ROLL_SUBCASE( case3c, array_hs_fb, shift, axis );
    ROLL_SUBCASE( case3c, array_hs_hb, shift, axis );
    ROLL_SUBCASE( case3c, array_hs_db, shift, axis );

    ROLL_SUBCASE( case3c, array_ds_fb, shift, axis );
    ROLL_SUBCASE( case3c, array_ds_hb, shift, axis );
    ROLL_SUBCASE( case3c, array_ds_db, shift, axis );

    ROLL_SUBCASE( case3c, array_ls_fb, shift, axis );
    ROLL_SUBCASE( case3c, array_ls_hb, shift, axis );
    ROLL_SUBCASE( case3c, array_ls_db, shift, axis );
    #endif
}

TEST_CASE("roll(case3d)" * doctest::test_suite("array::roll"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    ROLL_SUBCASE( case3d, array, shift, axis );
    ROLL_SUBCASE( case3d, array_a, shift, axis );
    ROLL_SUBCASE( case3d, array_f, shift, axis );
    ROLL_SUBCASE( case3d, array_d, shift, axis );
    ROLL_SUBCASE( case3d, array_h, shift, axis );
    #else
    ROLL_SUBCASE( case3d, array_cs_fb, shift, axis );
    ROLL_SUBCASE( case3d, array_cs_hb, shift, axis );
    ROLL_SUBCASE( case3d, array_cs_db, shift, axis );

    ROLL_SUBCASE( case3d, array_fs_fb, shift, axis );
    ROLL_SUBCASE( case3d, array_fs_hb, shift, axis );
    ROLL_SUBCASE( case3d, array_fs_db, shift, axis );

    ROLL_SUBCASE( case3d, array_hs_fb, shift, axis );
    ROLL_SUBCASE( case3d, array_hs_hb, shift, axis );
    ROLL_SUBCASE( case3d, array_hs_db, shift, axis );

    ROLL_SUBCASE( case3d, array_ds_fb, shift, axis );
    ROLL_SUBCASE( case3d, array_ds_hb, shift, axis );
    ROLL_SUBCASE( case3d, array_ds_db, shift, axis );

    ROLL_SUBCASE( case3d, array_ls_fb, shift, axis );
    ROLL_SUBCASE( case3d, array_ls_hb, shift, axis );
    ROLL_SUBCASE( case3d, array_ls_db, shift, axis );
    #endif
}

TEST_CASE("roll(case3e)" * doctest::test_suite("array::roll"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    ROLL_SUBCASE( case3e, array, shift, axis );
    ROLL_SUBCASE( case3e, array_a, shift, axis );
    ROLL_SUBCASE( case3e, array_f, shift, axis );
    ROLL_SUBCASE( case3e, array_d, shift, axis );
    ROLL_SUBCASE( case3e, array_h, shift, axis );
    #else
    ROLL_SUBCASE( case3e, array_cs_fb, shift, axis );
    ROLL_SUBCASE( case3e, array_cs_hb, shift, axis );
    ROLL_SUBCASE( case3e, array_cs_db, shift, axis );

    ROLL_SUBCASE( case3e, array_fs_fb, shift, axis );
    ROLL_SUBCASE( case3e, array_fs_hb, shift, axis );
    ROLL_SUBCASE( case3e, array_fs_db, shift, axis );

    ROLL_SUBCASE( case3e, array_hs_fb, shift, axis );
    ROLL_SUBCASE( case3e, array_hs_hb, shift, axis );
    ROLL_SUBCASE( case3e, array_hs_db, shift, axis );

    ROLL_SUBCASE( case3e, array_ds_fb, shift, axis );
    ROLL_SUBCASE( case3e, array_ds_hb, shift, axis );
    ROLL_SUBCASE( case3e, array_ds_db, shift, axis );

    ROLL_SUBCASE( case3e, array_ls_fb, shift, axis );
    ROLL_SUBCASE( case3e, array_ls_hb, shift, axis );
    ROLL_SUBCASE( case3e, array_ls_db, shift, axis );
    #endif
}

TEST_CASE("roll(case3f)" * doctest::test_suite("array::roll"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    ROLL_SUBCASE( case3f, array, shift, axis );
    ROLL_SUBCASE( case3f, array_a, shift, axis );
    ROLL_SUBCASE( case3f, array_f, shift, axis );
    ROLL_SUBCASE( case3f, array_d, shift, axis );
    ROLL_SUBCASE( case3f, array_h, shift, axis );
    #else
    ROLL_SUBCASE( case3f, array_cs_fb, shift, axis );
    ROLL_SUBCASE( case3f, array_cs_hb, shift, axis );
    ROLL_SUBCASE( case3f, array_cs_db, shift, axis );

    ROLL_SUBCASE( case3f, array_fs_fb, shift, axis );
    ROLL_SUBCASE( case3f, array_fs_hb, shift, axis );
    ROLL_SUBCASE( case3f, array_fs_db, shift, axis );

    ROLL_SUBCASE( case3f, array_hs_fb, shift, axis );
    ROLL_SUBCASE( case3f, array_hs_hb, shift, axis );
    ROLL_SUBCASE( case3f, array_hs_db, shift, axis );

    ROLL_SUBCASE( case3f, array_ds_fb, shift, axis );
    ROLL_SUBCASE( case3f, array_ds_hb, shift, axis );
    ROLL_SUBCASE( case3f, array_ds_db, shift, axis );

    ROLL_SUBCASE( case3f, array_ls_fb, shift, axis );
    ROLL_SUBCASE( case3f, array_ls_hb, shift, axis );
    ROLL_SUBCASE( case3f, array_ls_db, shift, axis );
    #endif
}

TEST_CASE("roll(case3g)" * doctest::test_suite("array::roll"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    ROLL_SUBCASE( case3g, array, shift, axis );
    ROLL_SUBCASE( case3g, array_a, shift, axis );
    ROLL_SUBCASE( case3g, array_f, shift, axis );
    ROLL_SUBCASE( case3g, array_d, shift, axis );
    ROLL_SUBCASE( case3g, array_h, shift, axis );
    #else
    ROLL_SUBCASE( case3g, array_cs_fb, shift, axis );
    ROLL_SUBCASE( case3g, array_cs_hb, shift, axis );
    ROLL_SUBCASE( case3g, array_cs_db, shift, axis );

    ROLL_SUBCASE( case3g, array_fs_fb, shift, axis );
    ROLL_SUBCASE( case3g, array_fs_hb, shift, axis );
    ROLL_SUBCASE( case3g, array_fs_db, shift, axis );

    ROLL_SUBCASE( case3g, array_hs_fb, shift, axis );
    ROLL_SUBCASE( case3g, array_hs_hb, shift, axis );
    ROLL_SUBCASE( case3g, array_hs_db, shift, axis );

    ROLL_SUBCASE( case3g, array_ds_fb, shift, axis );
    ROLL_SUBCASE( case3g, array_ds_hb, shift, axis );
    ROLL_SUBCASE( case3g, array_ds_db, shift, axis );

    ROLL_SUBCASE( case3g, array_ls_fb, shift, axis );
    ROLL_SUBCASE( case3g, array_ls_hb, shift, axis );
    ROLL_SUBCASE( case3g, array_ls_db, shift, axis );
    #endif
}

TEST_CASE("roll(case3h)" * doctest::test_suite("array::roll"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    ROLL_SUBCASE( case3h, array, shift, axis );
    ROLL_SUBCASE( case3h, array_a, shift, axis );
    ROLL_SUBCASE( case3h, array_f, shift, axis );
    ROLL_SUBCASE( case3h, array_d, shift, axis );
    ROLL_SUBCASE( case3h, array_h, shift, axis );
    #else
    ROLL_SUBCASE( case3h, array_cs_fb, shift, axis );
    ROLL_SUBCASE( case3h, array_cs_hb, shift, axis );
    ROLL_SUBCASE( case3h, array_cs_db, shift, axis );

    ROLL_SUBCASE( case3h, array_fs_fb, shift, axis );
    ROLL_SUBCASE( case3h, array_fs_hb, shift, axis );
    ROLL_SUBCASE( case3h, array_fs_db, shift, axis );

    ROLL_SUBCASE( case3h, array_hs_fb, shift, axis );
    ROLL_SUBCASE( case3h, array_hs_hb, shift, axis );
    ROLL_SUBCASE( case3h, array_hs_db, shift, axis );

    ROLL_SUBCASE( case3h, array_ds_fb, shift, axis );
    ROLL_SUBCASE( case3h, array_ds_hb, shift, axis );
    ROLL_SUBCASE( case3h, array_ds_db, shift, axis );

    ROLL_SUBCASE( case3h, array_ls_fb, shift, axis );
    ROLL_SUBCASE( case3h, array_ls_hb, shift, axis );
    ROLL_SUBCASE( case3h, array_ls_db, shift, axis );
    #endif
}