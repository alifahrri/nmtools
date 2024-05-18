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

#include "nmtools/array/array/moveaxis.hpp"
#include "nmtools/testing/data/array/moveaxis.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;

#define MOVEAXIS_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, moveaxis, case_name); \
    using namespace args; \
    auto result = nmtools::array::moveaxis(__VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("moveaxis(case1)" * doctest::test_suite("array::moveaxis"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MOVEAXIS_SUBCASE( case1, a, source, destination );
    MOVEAXIS_SUBCASE( case1, a_a, source, destination );
    MOVEAXIS_SUBCASE( case1, a_f, source, destination );
    MOVEAXIS_SUBCASE( case1, a_d, source, destination );
    MOVEAXIS_SUBCASE( case1, a_h, source, destination );

    #else
    MOVEAXIS_SUBCASE( case1, a_cs_fb, source, destination );
    MOVEAXIS_SUBCASE( case1, a_cs_hb, source, destination );
    MOVEAXIS_SUBCASE( case1, a_cs_db, source, destination );

    MOVEAXIS_SUBCASE( case1, a_fs_fb, source, destination );
    MOVEAXIS_SUBCASE( case1, a_fs_hb, source, destination );
    MOVEAXIS_SUBCASE( case1, a_fs_db, source, destination );

    MOVEAXIS_SUBCASE( case1, a_hs_fb, source, destination );
    MOVEAXIS_SUBCASE( case1, a_hs_hb, source, destination );
    MOVEAXIS_SUBCASE( case1, a_hs_db, source, destination );

    MOVEAXIS_SUBCASE( case1, a_ds_fb, source, destination );
    MOVEAXIS_SUBCASE( case1, a_ds_hb, source, destination );
    MOVEAXIS_SUBCASE( case1, a_ds_db, source, destination );

    MOVEAXIS_SUBCASE( case1, a_ls_fb, source, destination );
    MOVEAXIS_SUBCASE( case1, a_ls_hb, source, destination );
    MOVEAXIS_SUBCASE( case1, a_ls_db, source, destination );
    #endif
}

TEST_CASE("moveaxis(case2)" * doctest::test_suite("array::moveaxis"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MOVEAXIS_SUBCASE( case2, a, source, destination );
    MOVEAXIS_SUBCASE( case2, a_a, source, destination );
    MOVEAXIS_SUBCASE( case2, a_f, source, destination );
    MOVEAXIS_SUBCASE( case2, a_d, source, destination );
    MOVEAXIS_SUBCASE( case2, a_h, source, destination );

    #else
    MOVEAXIS_SUBCASE( case2, a_cs_fb, source, destination );
    MOVEAXIS_SUBCASE( case2, a_cs_hb, source, destination );
    MOVEAXIS_SUBCASE( case2, a_cs_db, source, destination );

    MOVEAXIS_SUBCASE( case2, a_fs_fb, source, destination );
    MOVEAXIS_SUBCASE( case2, a_fs_hb, source, destination );
    MOVEAXIS_SUBCASE( case2, a_fs_db, source, destination );

    MOVEAXIS_SUBCASE( case2, a_hs_fb, source, destination );
    MOVEAXIS_SUBCASE( case2, a_hs_hb, source, destination );
    MOVEAXIS_SUBCASE( case2, a_hs_db, source, destination );

    MOVEAXIS_SUBCASE( case2, a_ds_fb, source, destination );
    MOVEAXIS_SUBCASE( case2, a_ds_hb, source, destination );
    MOVEAXIS_SUBCASE( case2, a_ds_db, source, destination );

    MOVEAXIS_SUBCASE( case2, a_ls_fb, source, destination );
    MOVEAXIS_SUBCASE( case2, a_ls_hb, source, destination );
    MOVEAXIS_SUBCASE( case2, a_ls_db, source, destination );
    #endif
}

TEST_CASE("moveaxis(case3)" * doctest::test_suite("array::moveaxis"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MOVEAXIS_SUBCASE( case3, a, source, destination );
    MOVEAXIS_SUBCASE( case3, a_a, source, destination );
    MOVEAXIS_SUBCASE( case3, a_f, source, destination );
    MOVEAXIS_SUBCASE( case3, a_d, source, destination );
    MOVEAXIS_SUBCASE( case3, a_h, source, destination );

    #else
    MOVEAXIS_SUBCASE( case3, a_cs_fb, source, destination );
    MOVEAXIS_SUBCASE( case3, a_cs_hb, source, destination );
    MOVEAXIS_SUBCASE( case3, a_cs_db, source, destination );

    MOVEAXIS_SUBCASE( case3, a_fs_fb, source, destination );
    MOVEAXIS_SUBCASE( case3, a_fs_hb, source, destination );
    MOVEAXIS_SUBCASE( case3, a_fs_db, source, destination );

    MOVEAXIS_SUBCASE( case3, a_hs_fb, source, destination );
    MOVEAXIS_SUBCASE( case3, a_hs_hb, source, destination );
    MOVEAXIS_SUBCASE( case3, a_hs_db, source, destination );

    MOVEAXIS_SUBCASE( case3, a_ds_fb, source, destination );
    MOVEAXIS_SUBCASE( case3, a_ds_hb, source, destination );
    MOVEAXIS_SUBCASE( case3, a_ds_db, source, destination );

    MOVEAXIS_SUBCASE( case3, a_ls_fb, source, destination );
    MOVEAXIS_SUBCASE( case3, a_ls_hb, source, destination );
    MOVEAXIS_SUBCASE( case3, a_ls_db, source, destination );
    #endif
}

TEST_CASE("moveaxis(case4)" * doctest::test_suite("array::moveaxis"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MOVEAXIS_SUBCASE( case4, a, source, destination );
    MOVEAXIS_SUBCASE( case4, a_a, source, destination );
    MOVEAXIS_SUBCASE( case4, a_f, source, destination );
    MOVEAXIS_SUBCASE( case4, a_d, source, destination );
    MOVEAXIS_SUBCASE( case4, a_h, source, destination );

    #else
    MOVEAXIS_SUBCASE( case4, a_cs_fb, source, destination );
    MOVEAXIS_SUBCASE( case4, a_cs_hb, source, destination );
    MOVEAXIS_SUBCASE( case4, a_cs_db, source, destination );

    MOVEAXIS_SUBCASE( case4, a_fs_fb, source, destination );
    MOVEAXIS_SUBCASE( case4, a_fs_hb, source, destination );
    MOVEAXIS_SUBCASE( case4, a_fs_db, source, destination );

    MOVEAXIS_SUBCASE( case4, a_hs_fb, source, destination );
    MOVEAXIS_SUBCASE( case4, a_hs_hb, source, destination );
    MOVEAXIS_SUBCASE( case4, a_hs_db, source, destination );

    MOVEAXIS_SUBCASE( case4, a_ds_fb, source, destination );
    MOVEAXIS_SUBCASE( case4, a_ds_hb, source, destination );
    MOVEAXIS_SUBCASE( case4, a_ds_db, source, destination );

    MOVEAXIS_SUBCASE( case4, a_ls_fb, source, destination );
    MOVEAXIS_SUBCASE( case4, a_ls_hb, source, destination );
    MOVEAXIS_SUBCASE( case4, a_ls_db, source, destination );
    #endif
}

TEST_CASE("moveaxis(case5)" * doctest::test_suite("array::moveaxis"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MOVEAXIS_SUBCASE( case5, a, source, destination );
    MOVEAXIS_SUBCASE( case5, a_a, source, destination );
    MOVEAXIS_SUBCASE( case5, a_f, source, destination );
    MOVEAXIS_SUBCASE( case5, a_d, source, destination );
    MOVEAXIS_SUBCASE( case5, a_h, source, destination );

    #else
    MOVEAXIS_SUBCASE( case5, a_cs_fb, source, destination );
    MOVEAXIS_SUBCASE( case5, a_cs_hb, source, destination );
    MOVEAXIS_SUBCASE( case5, a_cs_db, source, destination );

    MOVEAXIS_SUBCASE( case5, a_fs_fb, source, destination );
    MOVEAXIS_SUBCASE( case5, a_fs_hb, source, destination );
    MOVEAXIS_SUBCASE( case5, a_fs_db, source, destination );

    MOVEAXIS_SUBCASE( case5, a_hs_fb, source, destination );
    MOVEAXIS_SUBCASE( case5, a_hs_hb, source, destination );
    MOVEAXIS_SUBCASE( case5, a_hs_db, source, destination );

    MOVEAXIS_SUBCASE( case5, a_ds_fb, source, destination );
    MOVEAXIS_SUBCASE( case5, a_ds_hb, source, destination );
    MOVEAXIS_SUBCASE( case5, a_ds_db, source, destination );

    MOVEAXIS_SUBCASE( case5, a_ls_fb, source, destination );
    MOVEAXIS_SUBCASE( case5, a_ls_hb, source, destination );
    MOVEAXIS_SUBCASE( case5, a_ls_db, source, destination );
    #endif
}

TEST_CASE("moveaxis(case6)" * doctest::test_suite("array::moveaxis"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MOVEAXIS_SUBCASE( case6, a, source, destination );
    MOVEAXIS_SUBCASE( case6, a_a, source, destination );
    MOVEAXIS_SUBCASE( case6, a_f, source, destination );
    MOVEAXIS_SUBCASE( case6, a_d, source, destination );
    MOVEAXIS_SUBCASE( case6, a_h, source, destination );

    #else
    MOVEAXIS_SUBCASE( case6, a_cs_fb, source, destination );
    MOVEAXIS_SUBCASE( case6, a_cs_hb, source, destination );
    MOVEAXIS_SUBCASE( case6, a_cs_db, source, destination );

    MOVEAXIS_SUBCASE( case6, a_fs_fb, source, destination );
    MOVEAXIS_SUBCASE( case6, a_fs_hb, source, destination );
    MOVEAXIS_SUBCASE( case6, a_fs_db, source, destination );

    MOVEAXIS_SUBCASE( case6, a_hs_fb, source, destination );
    MOVEAXIS_SUBCASE( case6, a_hs_hb, source, destination );
    MOVEAXIS_SUBCASE( case6, a_hs_db, source, destination );

    MOVEAXIS_SUBCASE( case6, a_ds_fb, source, destination );
    MOVEAXIS_SUBCASE( case6, a_ds_hb, source, destination );
    MOVEAXIS_SUBCASE( case6, a_ds_db, source, destination );

    MOVEAXIS_SUBCASE( case6, a_ls_fb, source, destination );
    MOVEAXIS_SUBCASE( case6, a_ls_hb, source, destination );
    MOVEAXIS_SUBCASE( case6, a_ls_db, source, destination );
    #endif
}

TEST_CASE("moveaxis(case7)" * doctest::test_suite("array::moveaxis"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MOVEAXIS_SUBCASE( case7, a, source, destination );
    MOVEAXIS_SUBCASE( case7, a_a, source, destination );
    MOVEAXIS_SUBCASE( case7, a_f, source, destination );
    MOVEAXIS_SUBCASE( case7, a_d, source, destination );
    MOVEAXIS_SUBCASE( case7, a_h, source, destination );

    #else
    MOVEAXIS_SUBCASE( case7, a_cs_fb, source, destination );
    MOVEAXIS_SUBCASE( case7, a_cs_hb, source, destination );
    MOVEAXIS_SUBCASE( case7, a_cs_db, source, destination );

    MOVEAXIS_SUBCASE( case7, a_fs_fb, source, destination );
    MOVEAXIS_SUBCASE( case7, a_fs_hb, source, destination );
    MOVEAXIS_SUBCASE( case7, a_fs_db, source, destination );

    MOVEAXIS_SUBCASE( case7, a_hs_fb, source, destination );
    MOVEAXIS_SUBCASE( case7, a_hs_hb, source, destination );
    MOVEAXIS_SUBCASE( case7, a_hs_db, source, destination );

    MOVEAXIS_SUBCASE( case7, a_ds_fb, source, destination );
    MOVEAXIS_SUBCASE( case7, a_ds_hb, source, destination );
    MOVEAXIS_SUBCASE( case7, a_ds_db, source, destination );

    MOVEAXIS_SUBCASE( case7, a_ls_fb, source, destination );
    MOVEAXIS_SUBCASE( case7, a_ls_hb, source, destination );
    MOVEAXIS_SUBCASE( case7, a_ls_db, source, destination );
    #endif
}

TEST_CASE("moveaxis(case8)" * doctest::test_suite("array::moveaxis"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MOVEAXIS_SUBCASE( case8, a, source, destination );
    MOVEAXIS_SUBCASE( case8, a_a, source, destination );
    MOVEAXIS_SUBCASE( case8, a_f, source, destination );
    MOVEAXIS_SUBCASE( case8, a_d, source, destination );
    MOVEAXIS_SUBCASE( case8, a_h, source, destination );

    #else
    MOVEAXIS_SUBCASE( case8, a_cs_fb, source, destination );
    MOVEAXIS_SUBCASE( case8, a_cs_hb, source, destination );
    MOVEAXIS_SUBCASE( case8, a_cs_db, source, destination );

    MOVEAXIS_SUBCASE( case8, a_fs_fb, source, destination );
    MOVEAXIS_SUBCASE( case8, a_fs_hb, source, destination );
    MOVEAXIS_SUBCASE( case8, a_fs_db, source, destination );

    MOVEAXIS_SUBCASE( case8, a_hs_fb, source, destination );
    MOVEAXIS_SUBCASE( case8, a_hs_hb, source, destination );
    MOVEAXIS_SUBCASE( case8, a_hs_db, source, destination );

    MOVEAXIS_SUBCASE( case8, a_ds_fb, source, destination );
    MOVEAXIS_SUBCASE( case8, a_ds_hb, source, destination );
    MOVEAXIS_SUBCASE( case8, a_ds_db, source, destination );

    MOVEAXIS_SUBCASE( case8, a_ls_fb, source, destination );
    MOVEAXIS_SUBCASE( case8, a_ls_hb, source, destination );
    MOVEAXIS_SUBCASE( case8, a_ls_db, source, destination );
    #endif
}

TEST_CASE("moveaxis(case9)" * doctest::test_suite("array::moveaxis"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MOVEAXIS_SUBCASE( case9, a, source, destination );
    MOVEAXIS_SUBCASE( case9, a_a, source, destination );
    MOVEAXIS_SUBCASE( case9, a_f, source, destination );
    MOVEAXIS_SUBCASE( case9, a_d, source, destination );
    MOVEAXIS_SUBCASE( case9, a_h, source, destination );

    #else
    MOVEAXIS_SUBCASE( case9, a_cs_fb, source, destination );
    MOVEAXIS_SUBCASE( case9, a_cs_hb, source, destination );
    MOVEAXIS_SUBCASE( case9, a_cs_db, source, destination );

    MOVEAXIS_SUBCASE( case9, a_fs_fb, source, destination );
    MOVEAXIS_SUBCASE( case9, a_fs_hb, source, destination );
    MOVEAXIS_SUBCASE( case9, a_fs_db, source, destination );

    MOVEAXIS_SUBCASE( case9, a_hs_fb, source, destination );
    MOVEAXIS_SUBCASE( case9, a_hs_hb, source, destination );
    MOVEAXIS_SUBCASE( case9, a_hs_db, source, destination );

    MOVEAXIS_SUBCASE( case9, a_ds_fb, source, destination );
    MOVEAXIS_SUBCASE( case9, a_ds_hb, source, destination );
    MOVEAXIS_SUBCASE( case9, a_ds_db, source, destination );

    MOVEAXIS_SUBCASE( case9, a_ls_fb, source, destination );
    MOVEAXIS_SUBCASE( case9, a_ls_hb, source, destination );
    MOVEAXIS_SUBCASE( case9, a_ls_db, source, destination );
    #endif
}