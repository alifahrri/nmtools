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

#include "nmtools/array/compress.hpp"
#include "nmtools/testing/data/array/compress.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;

#define COMPRESS_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, compress, case_name); \
    using namespace args; \
    auto result = nmtools::view::compress(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("compress(case1)" * doctest::test_suite("view::compress"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    COMPRESS_SUBCASE( case1,   condition,   array, axis );
    COMPRESS_SUBCASE( case1, condition_a, array_a, axis );
    COMPRESS_SUBCASE( case1, condition_f, array_f, axis );
    // TODO: enable this for nostl
    #ifndef NMTOOLS_DISABLE_STL
    COMPRESS_SUBCASE( case1, condition_v, array_d, axis );
    #endif
    COMPRESS_SUBCASE( case1, condition_h, array_h, axis );

    #else
    // condition in compress view must be index array

    COMPRESS_SUBCASE( case1, condition_cs_fb, array_cs_fb, axis );
    COMPRESS_SUBCASE( case1, condition_cs_hb, array_cs_hb, axis );
    COMPRESS_SUBCASE( case1, condition_cs_db, array_cs_db, axis );

    COMPRESS_SUBCASE( case1, condition_cs_fb, array_fs_fb, axis );
    COMPRESS_SUBCASE( case1, condition_cs_hb, array_fs_hb, axis );
    COMPRESS_SUBCASE( case1, condition_cs_db, array_fs_db, axis );

    COMPRESS_SUBCASE( case1, condition_cs_fb, array_hs_fb, axis );
    COMPRESS_SUBCASE( case1, condition_cs_hb, array_hs_hb, axis );
    COMPRESS_SUBCASE( case1, condition_cs_db, array_hs_db, axis );

    COMPRESS_SUBCASE( case1, condition_cs_fb, array_ds_fb, axis );
    COMPRESS_SUBCASE( case1, condition_cs_hb, array_ds_hb, axis );
    COMPRESS_SUBCASE( case1, condition_cs_db, array_ds_db, axis );

    COMPRESS_SUBCASE( case1, condition_cs_fb, array_ls_fb, axis );
    COMPRESS_SUBCASE( case1, condition_cs_hb, array_ls_hb, axis );
    COMPRESS_SUBCASE( case1, condition_cs_db, array_ls_db, axis );

    COMPRESS_SUBCASE( case1, condition_fs_fb, array_fs_fb, axis );
    COMPRESS_SUBCASE( case1, condition_fs_hb, array_fs_hb, axis );
    COMPRESS_SUBCASE( case1, condition_fs_db, array_fs_db, axis );

    COMPRESS_SUBCASE( case1, condition_fs_fb, array_cs_fb, axis );
    COMPRESS_SUBCASE( case1, condition_fs_hb, array_cs_hb, axis );
    COMPRESS_SUBCASE( case1, condition_fs_db, array_cs_db, axis );

    COMPRESS_SUBCASE( case1, condition_fs_fb, array_hs_fb, axis );
    COMPRESS_SUBCASE( case1, condition_fs_hb, array_hs_hb, axis );
    COMPRESS_SUBCASE( case1, condition_fs_db, array_hs_db, axis );

    COMPRESS_SUBCASE( case1, condition_fs_fb, array_ds_fb, axis );
    COMPRESS_SUBCASE( case1, condition_fs_hb, array_ds_hb, axis );
    COMPRESS_SUBCASE( case1, condition_fs_db, array_ds_db, axis );

    COMPRESS_SUBCASE( case1, condition_fs_fb, array_ls_fb, axis );
    COMPRESS_SUBCASE( case1, condition_fs_hb, array_ls_hb, axis );
    COMPRESS_SUBCASE( case1, condition_fs_db, array_ls_db, axis );

    COMPRESS_SUBCASE( case1, condition_ls_fb, array_ls_fb, axis );
    COMPRESS_SUBCASE( case1, condition_ls_hb, array_ls_hb, axis );
    COMPRESS_SUBCASE( case1, condition_ls_db, array_ls_db, axis );

    COMPRESS_SUBCASE( case1, condition_ls_fb, array_cs_fb, axis );
    COMPRESS_SUBCASE( case1, condition_ls_hb, array_cs_hb, axis );
    COMPRESS_SUBCASE( case1, condition_ls_db, array_cs_db, axis );

    COMPRESS_SUBCASE( case1, condition_ls_fb, array_fs_fb, axis );
    COMPRESS_SUBCASE( case1, condition_ls_hb, array_fs_hb, axis );
    COMPRESS_SUBCASE( case1, condition_ls_db, array_fs_db, axis );

    COMPRESS_SUBCASE( case1, condition_ls_fb, array_hs_fb, axis );
    COMPRESS_SUBCASE( case1, condition_ls_hb, array_hs_hb, axis );
    COMPRESS_SUBCASE( case1, condition_ls_db, array_hs_db, axis );

    COMPRESS_SUBCASE( case1, condition_ls_fb, array_ds_fb, axis );
    COMPRESS_SUBCASE( case1, condition_ls_hb, array_ds_hb, axis );
    COMPRESS_SUBCASE( case1, condition_ls_db, array_ds_db, axis );
    #endif
}

TEST_CASE("compress(case2)" * doctest::test_suite("view::compress"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    COMPRESS_SUBCASE( case2,   condition,   array, axis );
    COMPRESS_SUBCASE( case2, condition_a, array_a, axis );
    COMPRESS_SUBCASE( case2, condition_f, array_f, axis );
    #ifndef NMTOOLS_DISABLE_STL
    COMPRESS_SUBCASE( case2, condition_v, array_d, axis );
    #endif
    COMPRESS_SUBCASE( case2, condition_h, array_h, axis );

    #else
    COMPRESS_SUBCASE( case2, condition_cs_fb, array_cs_fb, axis );
    COMPRESS_SUBCASE( case2, condition_cs_hb, array_cs_hb, axis );
    COMPRESS_SUBCASE( case2, condition_cs_db, array_cs_db, axis );

    COMPRESS_SUBCASE( case2, condition_cs_fb, array_fs_fb, axis );
    COMPRESS_SUBCASE( case2, condition_cs_hb, array_fs_hb, axis );
    COMPRESS_SUBCASE( case2, condition_cs_db, array_fs_db, axis );

    COMPRESS_SUBCASE( case2, condition_cs_fb, array_hs_fb, axis );
    COMPRESS_SUBCASE( case2, condition_cs_hb, array_hs_hb, axis );
    COMPRESS_SUBCASE( case2, condition_cs_db, array_hs_db, axis );

    COMPRESS_SUBCASE( case2, condition_cs_fb, array_ds_fb, axis );
    COMPRESS_SUBCASE( case2, condition_cs_hb, array_ds_hb, axis );
    COMPRESS_SUBCASE( case2, condition_cs_db, array_ds_db, axis );

    COMPRESS_SUBCASE( case2, condition_cs_fb, array_ls_fb, axis );
    COMPRESS_SUBCASE( case2, condition_cs_hb, array_ls_hb, axis );
    COMPRESS_SUBCASE( case2, condition_cs_db, array_ls_db, axis );

    COMPRESS_SUBCASE( case2, condition_fs_fb, array_fs_fb, axis );
    COMPRESS_SUBCASE( case2, condition_fs_hb, array_fs_hb, axis );
    COMPRESS_SUBCASE( case2, condition_fs_db, array_fs_db, axis );

    COMPRESS_SUBCASE( case2, condition_fs_fb, array_cs_fb, axis );
    COMPRESS_SUBCASE( case2, condition_fs_hb, array_cs_hb, axis );
    COMPRESS_SUBCASE( case2, condition_fs_db, array_cs_db, axis );

    COMPRESS_SUBCASE( case2, condition_fs_fb, array_hs_fb, axis );
    COMPRESS_SUBCASE( case2, condition_fs_hb, array_hs_hb, axis );
    COMPRESS_SUBCASE( case2, condition_fs_db, array_hs_db, axis );

    COMPRESS_SUBCASE( case2, condition_fs_fb, array_ds_fb, axis );
    COMPRESS_SUBCASE( case2, condition_fs_hb, array_ds_hb, axis );
    COMPRESS_SUBCASE( case2, condition_fs_db, array_ds_db, axis );

    COMPRESS_SUBCASE( case2, condition_fs_fb, array_ls_fb, axis );
    COMPRESS_SUBCASE( case2, condition_fs_hb, array_ls_hb, axis );
    COMPRESS_SUBCASE( case2, condition_fs_db, array_ls_db, axis );

    COMPRESS_SUBCASE( case2, condition_ls_fb, array_fs_fb, axis );
    COMPRESS_SUBCASE( case2, condition_ls_hb, array_fs_hb, axis );
    COMPRESS_SUBCASE( case2, condition_ls_db, array_fs_db, axis );

    COMPRESS_SUBCASE( case2, condition_ls_fb, array_cs_fb, axis );
    COMPRESS_SUBCASE( case2, condition_ls_hb, array_cs_hb, axis );
    COMPRESS_SUBCASE( case2, condition_ls_db, array_cs_db, axis );

    COMPRESS_SUBCASE( case2, condition_ls_fb, array_hs_fb, axis );
    COMPRESS_SUBCASE( case2, condition_ls_hb, array_hs_hb, axis );
    COMPRESS_SUBCASE( case2, condition_ls_db, array_hs_db, axis );

    COMPRESS_SUBCASE( case2, condition_ls_fb, array_ds_fb, axis );
    COMPRESS_SUBCASE( case2, condition_ls_hb, array_ds_hb, axis );
    COMPRESS_SUBCASE( case2, condition_ls_db, array_ds_db, axis );

    COMPRESS_SUBCASE( case2, condition_ls_fb, array_ls_fb, axis );
    COMPRESS_SUBCASE( case2, condition_ls_hb, array_ls_hb, axis );
    COMPRESS_SUBCASE( case2, condition_ls_db, array_ls_db, axis );
    #endif
}

TEST_CASE("compress(case3)" * doctest::test_suite("view::compress"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    COMPRESS_SUBCASE( case3,   condition,   array, axis );
    COMPRESS_SUBCASE( case3, condition_a, array_a, axis );
    COMPRESS_SUBCASE( case3, condition_f, array_f, axis );
    #ifndef NMTOOLS_DISABLE_STL
    COMPRESS_SUBCASE( case3, condition_v, array_d, axis );
    #endif
    COMPRESS_SUBCASE( case3, condition_h, array_h, axis );

    #else
    COMPRESS_SUBCASE( case3, condition_cs_fb, array_cs_fb, axis );
    COMPRESS_SUBCASE( case3, condition_cs_hb, array_cs_hb, axis );
    COMPRESS_SUBCASE( case3, condition_cs_db, array_cs_db, axis );

    COMPRESS_SUBCASE( case3, condition_cs_fb, array_fs_fb, axis );
    COMPRESS_SUBCASE( case3, condition_cs_hb, array_fs_hb, axis );
    COMPRESS_SUBCASE( case3, condition_cs_db, array_fs_db, axis );

    COMPRESS_SUBCASE( case3, condition_cs_fb, array_hs_fb, axis );
    COMPRESS_SUBCASE( case3, condition_cs_hb, array_hs_hb, axis );
    COMPRESS_SUBCASE( case3, condition_cs_db, array_hs_db, axis );

    COMPRESS_SUBCASE( case3, condition_cs_fb, array_ds_fb, axis );
    COMPRESS_SUBCASE( case3, condition_cs_hb, array_ds_hb, axis );
    COMPRESS_SUBCASE( case3, condition_cs_db, array_ds_db, axis );

    COMPRESS_SUBCASE( case3, condition_cs_fb, array_ls_fb, axis );
    COMPRESS_SUBCASE( case3, condition_cs_hb, array_ls_hb, axis );
    COMPRESS_SUBCASE( case3, condition_cs_db, array_ls_db, axis );

    COMPRESS_SUBCASE( case3, condition_fs_fb, array_fs_fb, axis );
    COMPRESS_SUBCASE( case3, condition_fs_hb, array_fs_hb, axis );
    COMPRESS_SUBCASE( case3, condition_fs_db, array_fs_db, axis );

    COMPRESS_SUBCASE( case3, condition_fs_fb, array_cs_fb, axis );
    COMPRESS_SUBCASE( case3, condition_fs_hb, array_cs_hb, axis );
    COMPRESS_SUBCASE( case3, condition_fs_db, array_cs_db, axis );

    COMPRESS_SUBCASE( case3, condition_fs_fb, array_hs_fb, axis );
    COMPRESS_SUBCASE( case3, condition_fs_hb, array_hs_hb, axis );
    COMPRESS_SUBCASE( case3, condition_fs_db, array_hs_db, axis );

    COMPRESS_SUBCASE( case3, condition_fs_fb, array_ds_fb, axis );
    COMPRESS_SUBCASE( case3, condition_fs_hb, array_ds_hb, axis );
    COMPRESS_SUBCASE( case3, condition_fs_db, array_ds_db, axis );

    COMPRESS_SUBCASE( case3, condition_fs_fb, array_ls_fb, axis );
    COMPRESS_SUBCASE( case3, condition_fs_hb, array_ls_hb, axis );
    COMPRESS_SUBCASE( case3, condition_fs_db, array_ls_db, axis );

    COMPRESS_SUBCASE( case3, condition_ls_fb, array_fs_fb, axis );
    COMPRESS_SUBCASE( case3, condition_ls_hb, array_fs_hb, axis );
    COMPRESS_SUBCASE( case3, condition_ls_db, array_fs_db, axis );

    COMPRESS_SUBCASE( case3, condition_ls_fb, array_cs_fb, axis );
    COMPRESS_SUBCASE( case3, condition_ls_hb, array_cs_hb, axis );
    COMPRESS_SUBCASE( case3, condition_ls_db, array_cs_db, axis );

    COMPRESS_SUBCASE( case3, condition_ls_fb, array_hs_fb, axis );
    COMPRESS_SUBCASE( case3, condition_ls_hb, array_hs_hb, axis );
    COMPRESS_SUBCASE( case3, condition_ls_db, array_hs_db, axis );

    COMPRESS_SUBCASE( case3, condition_ls_fb, array_ds_fb, axis );
    COMPRESS_SUBCASE( case3, condition_ls_hb, array_ds_hb, axis );
    COMPRESS_SUBCASE( case3, condition_ls_db, array_ds_db, axis );

    COMPRESS_SUBCASE( case3, condition_ls_fb, array_ls_fb, axis );
    COMPRESS_SUBCASE( case3, condition_ls_hb, array_ls_hb, axis );
    COMPRESS_SUBCASE( case3, condition_ls_db, array_ls_db, axis );
    #endif
}

TEST_CASE("compress(case4)" * doctest::test_suite("view::compress"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    COMPRESS_SUBCASE( case4,   condition,   array, axis );
    COMPRESS_SUBCASE( case4, condition_a, array_a, axis );
    COMPRESS_SUBCASE( case4, condition_f, array_f, axis );
    #ifndef NMTOOLS_DISABLE_STL
    COMPRESS_SUBCASE( case4, condition_v, array_d, axis );
    #endif
    COMPRESS_SUBCASE( case4, condition_h, array_h, axis );

    #else
    COMPRESS_SUBCASE( case4, condition_cs_fb, array_cs_fb, axis );
    COMPRESS_SUBCASE( case4, condition_cs_hb, array_cs_hb, axis );
    COMPRESS_SUBCASE( case4, condition_cs_db, array_cs_db, axis );

    COMPRESS_SUBCASE( case4, condition_cs_fb, array_fs_fb, axis );
    COMPRESS_SUBCASE( case4, condition_cs_hb, array_fs_hb, axis );
    COMPRESS_SUBCASE( case4, condition_cs_db, array_fs_db, axis );

    COMPRESS_SUBCASE( case4, condition_cs_fb, array_hs_fb, axis );
    COMPRESS_SUBCASE( case4, condition_cs_hb, array_hs_hb, axis );
    COMPRESS_SUBCASE( case4, condition_cs_db, array_hs_db, axis );

    COMPRESS_SUBCASE( case4, condition_cs_fb, array_ds_fb, axis );
    COMPRESS_SUBCASE( case4, condition_cs_hb, array_ds_hb, axis );
    COMPRESS_SUBCASE( case4, condition_cs_db, array_ds_db, axis );

    COMPRESS_SUBCASE( case4, condition_cs_fb, array_ls_fb, axis );
    COMPRESS_SUBCASE( case4, condition_cs_hb, array_ls_hb, axis );
    COMPRESS_SUBCASE( case4, condition_cs_db, array_ls_db, axis );

    COMPRESS_SUBCASE( case4, condition_fs_fb, array_fs_fb, axis );
    COMPRESS_SUBCASE( case4, condition_fs_hb, array_fs_hb, axis );
    COMPRESS_SUBCASE( case4, condition_fs_db, array_fs_db, axis );

    COMPRESS_SUBCASE( case4, condition_fs_fb, array_cs_fb, axis );
    COMPRESS_SUBCASE( case4, condition_fs_hb, array_cs_hb, axis );
    COMPRESS_SUBCASE( case4, condition_fs_db, array_cs_db, axis );

    COMPRESS_SUBCASE( case4, condition_fs_fb, array_hs_fb, axis );
    COMPRESS_SUBCASE( case4, condition_fs_hb, array_hs_hb, axis );
    COMPRESS_SUBCASE( case4, condition_fs_db, array_hs_db, axis );

    COMPRESS_SUBCASE( case4, condition_fs_fb, array_ds_fb, axis );
    COMPRESS_SUBCASE( case4, condition_fs_hb, array_ds_hb, axis );
    COMPRESS_SUBCASE( case4, condition_fs_db, array_ds_db, axis );

    COMPRESS_SUBCASE( case4, condition_fs_fb, array_ls_fb, axis );
    COMPRESS_SUBCASE( case4, condition_fs_hb, array_ls_hb, axis );
    COMPRESS_SUBCASE( case4, condition_fs_db, array_ls_db, axis );
    #endif
}

TEST_CASE("compress(case5)" * doctest::test_suite("view::compress"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    COMPRESS_SUBCASE( case5, condition,   array, axis );
    COMPRESS_SUBCASE( case5, condition, array_a, axis );
    COMPRESS_SUBCASE( case5, condition, array_f, axis );
    COMPRESS_SUBCASE( case5, condition, array_d, axis );
    COMPRESS_SUBCASE( case5, condition, array_h, axis );

    #else
    COMPRESS_SUBCASE( case5, condition, array_cs_fb, axis );
    COMPRESS_SUBCASE( case5, condition, array_cs_hb, axis );
    COMPRESS_SUBCASE( case5, condition, array_cs_db, axis );

    COMPRESS_SUBCASE( case5, condition, array_fs_fb, axis );
    COMPRESS_SUBCASE( case5, condition, array_fs_hb, axis );
    COMPRESS_SUBCASE( case5, condition, array_fs_db, axis );

    COMPRESS_SUBCASE( case5, condition, array_hs_fb, axis );
    COMPRESS_SUBCASE( case5, condition, array_hs_hb, axis );
    COMPRESS_SUBCASE( case5, condition, array_hs_db, axis );

    COMPRESS_SUBCASE( case5, condition, array_ds_fb, axis );
    COMPRESS_SUBCASE( case5, condition, array_ds_hb, axis );
    COMPRESS_SUBCASE( case5, condition, array_ds_db, axis );

    COMPRESS_SUBCASE( case5, condition, array_ls_fb, axis );
    COMPRESS_SUBCASE( case5, condition, array_ls_hb, axis );
    COMPRESS_SUBCASE( case5, condition, array_ls_db, axis );
    #endif
}