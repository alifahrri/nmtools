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

#include "nmtools/array/view/mutable_flatten.hpp"
#include "nmtools/testing/data/array/flatten.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;

#define MUTABLE_FLATTEN_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(flatten,case_name); \
    using namespace args; \
    auto result = view::mutable_flatten(__VA_ARGS__); \
    NMTOOLS_REQUIRE_EQUAL( nmtools::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}

TEST_CASE("mutable_flatten(case1)" * doctest::test_suite("view::mutable_flatten"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MUTABLE_FLATTEN_SUBCASE( case1, array );
    MUTABLE_FLATTEN_SUBCASE( case1, array_a );
    MUTABLE_FLATTEN_SUBCASE( case1, array_f );
    MUTABLE_FLATTEN_SUBCASE( case1, array_d );
    MUTABLE_FLATTEN_SUBCASE( case1, array_h );

    #else
    MUTABLE_FLATTEN_SUBCASE( case1, array_cs_fb );
    MUTABLE_FLATTEN_SUBCASE( case1, array_cs_hb );
    MUTABLE_FLATTEN_SUBCASE( case1, array_cs_db );

    MUTABLE_FLATTEN_SUBCASE( case1, array_fs_fb );
    MUTABLE_FLATTEN_SUBCASE( case1, array_fs_hb );
    MUTABLE_FLATTEN_SUBCASE( case1, array_fs_db );

    MUTABLE_FLATTEN_SUBCASE( case1, array_hs_fb );
    MUTABLE_FLATTEN_SUBCASE( case1, array_hs_hb );
    MUTABLE_FLATTEN_SUBCASE( case1, array_hs_db );

    MUTABLE_FLATTEN_SUBCASE( case1, array_ds_fb );
    MUTABLE_FLATTEN_SUBCASE( case1, array_ds_hb );
    MUTABLE_FLATTEN_SUBCASE( case1, array_ds_db );

    MUTABLE_FLATTEN_SUBCASE( case1, array_ls_fb );
    MUTABLE_FLATTEN_SUBCASE( case1, array_ls_hb );
    // rejected by ndarray_t at compile-time
    // MUTABLE_FLATTEN_SUBCASE( case1, array_ls_db );
    #endif
}

TEST_CASE("mutable_flatten(case2)" * doctest::test_suite("view::mutable_flatten"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MUTABLE_FLATTEN_SUBCASE( case2, array );
    MUTABLE_FLATTEN_SUBCASE( case2, array_a );
    MUTABLE_FLATTEN_SUBCASE( case2, array_f );
    MUTABLE_FLATTEN_SUBCASE( case2, array_d );
    MUTABLE_FLATTEN_SUBCASE( case2, array_h );

    #else
    MUTABLE_FLATTEN_SUBCASE( case2, array_cs_fb );
    MUTABLE_FLATTEN_SUBCASE( case2, array_cs_hb );
    MUTABLE_FLATTEN_SUBCASE( case2, array_cs_db );

    MUTABLE_FLATTEN_SUBCASE( case2, array_fs_fb );
    MUTABLE_FLATTEN_SUBCASE( case2, array_fs_hb );
    MUTABLE_FLATTEN_SUBCASE( case2, array_fs_db );

    MUTABLE_FLATTEN_SUBCASE( case2, array_hs_fb );
    MUTABLE_FLATTEN_SUBCASE( case2, array_hs_hb );
    MUTABLE_FLATTEN_SUBCASE( case2, array_hs_db );

    MUTABLE_FLATTEN_SUBCASE( case2, array_ds_fb );
    MUTABLE_FLATTEN_SUBCASE( case2, array_ds_hb );
    MUTABLE_FLATTEN_SUBCASE( case2, array_ds_db );

    MUTABLE_FLATTEN_SUBCASE( case2, array_ls_fb );
    MUTABLE_FLATTEN_SUBCASE( case2, array_ls_hb );
    MUTABLE_FLATTEN_SUBCASE( case2, array_ls_db );
    #endif
}

TEST_CASE("mutable_flatten(case3)" * doctest::test_suite("view::mutable_flatten"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MUTABLE_FLATTEN_SUBCASE( case3, array );
    MUTABLE_FLATTEN_SUBCASE( case3, array_a );
    MUTABLE_FLATTEN_SUBCASE( case3, array_f );
    MUTABLE_FLATTEN_SUBCASE( case3, array_d );
    MUTABLE_FLATTEN_SUBCASE( case3, array_h );

    #else
    MUTABLE_FLATTEN_SUBCASE( case3, array_cs_fb );
    MUTABLE_FLATTEN_SUBCASE( case3, array_cs_hb );
    MUTABLE_FLATTEN_SUBCASE( case3, array_cs_db );

    MUTABLE_FLATTEN_SUBCASE( case3, array_fs_fb );
    MUTABLE_FLATTEN_SUBCASE( case3, array_fs_hb );
    MUTABLE_FLATTEN_SUBCASE( case3, array_fs_db );

    MUTABLE_FLATTEN_SUBCASE( case3, array_hs_fb );
    MUTABLE_FLATTEN_SUBCASE( case3, array_hs_hb );
    MUTABLE_FLATTEN_SUBCASE( case3, array_hs_db );

    MUTABLE_FLATTEN_SUBCASE( case3, array_ds_fb );
    MUTABLE_FLATTEN_SUBCASE( case3, array_ds_hb );
    MUTABLE_FLATTEN_SUBCASE( case3, array_ds_db );

    MUTABLE_FLATTEN_SUBCASE( case3, array_ls_fb );
    MUTABLE_FLATTEN_SUBCASE( case3, array_ls_hb );
    MUTABLE_FLATTEN_SUBCASE( case3, array_ls_db );
    #endif
}

TEST_CASE("mutable_flatten(case4)" * doctest::test_suite("view::mutable_flatten"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MUTABLE_FLATTEN_SUBCASE( case4, array );
    MUTABLE_FLATTEN_SUBCASE( case4, array_a );
    MUTABLE_FLATTEN_SUBCASE( case4, array_f );
    MUTABLE_FLATTEN_SUBCASE( case4, array_d );
    MUTABLE_FLATTEN_SUBCASE( case4, array_h );

    #else
    MUTABLE_FLATTEN_SUBCASE( case4, array_cs_fb );
    MUTABLE_FLATTEN_SUBCASE( case4, array_cs_hb );
    MUTABLE_FLATTEN_SUBCASE( case4, array_cs_db );

    MUTABLE_FLATTEN_SUBCASE( case4, array_fs_fb );
    MUTABLE_FLATTEN_SUBCASE( case4, array_fs_hb );
    MUTABLE_FLATTEN_SUBCASE( case4, array_fs_db );

    MUTABLE_FLATTEN_SUBCASE( case4, array_hs_fb );
    MUTABLE_FLATTEN_SUBCASE( case4, array_hs_hb );
    MUTABLE_FLATTEN_SUBCASE( case4, array_hs_db );

    MUTABLE_FLATTEN_SUBCASE( case4, array_ds_fb );
    MUTABLE_FLATTEN_SUBCASE( case4, array_ds_hb );
    MUTABLE_FLATTEN_SUBCASE( case4, array_ds_db );

    MUTABLE_FLATTEN_SUBCASE( case4, array_ls_fb );
    MUTABLE_FLATTEN_SUBCASE( case4, array_ls_hb );
    MUTABLE_FLATTEN_SUBCASE( case4, array_ls_db );
    #endif
}

TEST_CASE("mutable_flatten(case5)" * doctest::test_suite("view::mutable_flatten"))
{
    MUTABLE_FLATTEN_SUBCASE( case5, array );
}