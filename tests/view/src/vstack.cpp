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

#include "nmtools/array/view/vstack.hpp"
#include "nmtools/testing/data/array/vstack.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;

#define VSTACK_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( vstack, case_name ) \
    using namespace args; \
    auto result = nmtools::view::vstack(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("vstack(case1)" * doctest::test_suite("view::vstack"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    VSTACK_SUBCASE( case1, a, b );
    VSTACK_SUBCASE( case1, a_a, b_a );
    VSTACK_SUBCASE( case1, a_f, b_f );
    VSTACK_SUBCASE( case1, a_d, b_d );
    VSTACK_SUBCASE( case1, a_h, b_h );
    #else
    VSTACK_SUBCASE( case1, a_cs_fb, b_cs_fb );
    VSTACK_SUBCASE( case1, a_cs_hb, b_cs_hb );
    VSTACK_SUBCASE( case1, a_cs_db, b_cs_db );

    VSTACK_SUBCASE( case1, a_fs_fb, b_fs_fb );
    VSTACK_SUBCASE( case1, a_fs_hb, b_fs_hb );
    VSTACK_SUBCASE( case1, a_fs_db, b_fs_db );

    VSTACK_SUBCASE( case1, a_hs_fb, b_hs_fb );
    VSTACK_SUBCASE( case1, a_hs_hb, b_hs_hb );
    VSTACK_SUBCASE( case1, a_hs_db, b_hs_db );

    VSTACK_SUBCASE( case1, a_ds_fb, b_ds_fb );
    VSTACK_SUBCASE( case1, a_ds_hb, b_ds_hb );
    VSTACK_SUBCASE( case1, a_ds_db, b_ds_db );

    VSTACK_SUBCASE( case1, a_ls_fb, b_ls_fb );
    VSTACK_SUBCASE( case1, a_ls_hb, b_ls_hb );
    VSTACK_SUBCASE( case1, a_ls_db, b_ls_db );
    #endif
}

TEST_CASE("vstack(case2)" * doctest::test_suite("view::vstack"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    VSTACK_SUBCASE( case2, a, b );
    VSTACK_SUBCASE( case2, a_a, b_a );
    VSTACK_SUBCASE( case2, a_f, b_f );
    VSTACK_SUBCASE( case2, a_d, b_d );
    VSTACK_SUBCASE( case2, a_h, b_h );
    #else
    VSTACK_SUBCASE( case2, a_cs_fb, b_cs_fb );
    VSTACK_SUBCASE( case2, a_cs_hb, b_cs_hb );
    VSTACK_SUBCASE( case2, a_cs_db, b_cs_db );

    VSTACK_SUBCASE( case2, a_fs_fb, b_fs_fb );
    VSTACK_SUBCASE( case2, a_fs_hb, b_fs_hb );
    VSTACK_SUBCASE( case2, a_fs_db, b_fs_db );

    VSTACK_SUBCASE( case2, a_hs_fb, b_hs_fb );
    VSTACK_SUBCASE( case2, a_hs_hb, b_hs_hb );
    VSTACK_SUBCASE( case2, a_hs_db, b_hs_db );

    VSTACK_SUBCASE( case2, a_ds_fb, b_ds_fb );
    VSTACK_SUBCASE( case2, a_ds_hb, b_ds_hb );
    VSTACK_SUBCASE( case2, a_ds_db, b_ds_db );

    VSTACK_SUBCASE( case2, a_ls_fb, b_ls_fb );
    VSTACK_SUBCASE( case2, a_ls_hb, b_ls_hb );
    VSTACK_SUBCASE( case2, a_ls_db, b_ls_db );
    #endif
}

TEST_CASE("vstack(case3)" * doctest::test_suite("view::vstack"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    VSTACK_SUBCASE( case3, a, b );
    VSTACK_SUBCASE( case3, a_a, b_a );
    VSTACK_SUBCASE( case3, a_f, b_f );
    VSTACK_SUBCASE( case3, a_d, b_d );
    VSTACK_SUBCASE( case3, a_h, b_h );
    #else
    VSTACK_SUBCASE( case3, a_cs_fb, b_cs_fb );
    VSTACK_SUBCASE( case3, a_cs_hb, b_cs_hb );
    VSTACK_SUBCASE( case3, a_cs_db, b_cs_db );

    VSTACK_SUBCASE( case3, a_fs_fb, b_fs_fb );
    VSTACK_SUBCASE( case3, a_fs_hb, b_fs_hb );
    VSTACK_SUBCASE( case3, a_fs_db, b_fs_db );

    VSTACK_SUBCASE( case3, a_hs_fb, b_hs_fb );
    VSTACK_SUBCASE( case3, a_hs_hb, b_hs_hb );
    VSTACK_SUBCASE( case3, a_hs_db, b_hs_db );

    VSTACK_SUBCASE( case3, a_ds_fb, b_ds_fb );
    VSTACK_SUBCASE( case3, a_ds_hb, b_ds_hb );
    VSTACK_SUBCASE( case3, a_ds_db, b_ds_db );

    VSTACK_SUBCASE( case3, a_ls_fb, b_ls_fb );
    VSTACK_SUBCASE( case3, a_ls_hb, b_ls_hb );
    VSTACK_SUBCASE( case3, a_ls_db, b_ls_db );
    #endif
}