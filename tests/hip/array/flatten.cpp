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

#include "nmtools/array/flatten.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/evaluator/hip.hpp"
#include "nmtools/testing/data/array/flatten.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace hip = na::hip;

#define FLATTEN_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(flatten, case_name); \
    using namespace args; \
    auto result = na::flatten(__VA_ARGS__, hip::default_context()); \
    auto expect = na::flatten(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

TEST_CASE("flatten(case1)" * doctest::test_suite("array::flatten"))
{
    // FLATTEN_SUBCASE(case1, array);
    // FLATTEN_SUBCASE(case1, array_a);
    // FLATTEN_SUBCASE(case1, array_f);
    // FLATTEN_SUBCASE(case1, array_h);
    // FLATTEN_SUBCASE(case1, array_d);

    // FLATTEN_SUBCASE(case1, array_cs_fb);
    // FLATTEN_SUBCASE(case1, array_cs_hb);
    // FLATTEN_SUBCASE(case1, array_cs_db);

    FLATTEN_SUBCASE(case1, array_fs_fb);
    FLATTEN_SUBCASE(case1, array_fs_hb);
    FLATTEN_SUBCASE(case1, array_fs_db);

    FLATTEN_SUBCASE(case1, array_hs_fb);
    FLATTEN_SUBCASE(case1, array_hs_hb);
    FLATTEN_SUBCASE(case1, array_hs_db);

    FLATTEN_SUBCASE(case1, array_ds_fb);
    FLATTEN_SUBCASE(case1, array_ds_hb);
    FLATTEN_SUBCASE(case1, array_ds_db);

    // FLATTEN_SUBCASE(case1, array_ls_fb);
    // FLATTEN_SUBCASE(case1, array_ls_hb);
    // FLATTEN_SUBCASE(case1, array_ls_db);
}

TEST_CASE("flatten(case2)" * doctest::test_suite("array::flatten"))
{
    // FLATTEN_SUBCASE(case2, array);
    // FLATTEN_SUBCASE(case2, array_a);
    // FLATTEN_SUBCASE(case2, array_f);
    // FLATTEN_SUBCASE(case2, array_h);
    // FLATTEN_SUBCASE(case2, array_d);

    // FLATTEN_SUBCASE(case2, array_cs_fb);
    // FLATTEN_SUBCASE(case2, array_cs_hb);
    // FLATTEN_SUBCASE(case2, array_cs_db);

    FLATTEN_SUBCASE(case2, array_fs_fb);
    FLATTEN_SUBCASE(case2, array_fs_hb);
    FLATTEN_SUBCASE(case2, array_fs_db);

    FLATTEN_SUBCASE(case2, array_hs_fb);
    FLATTEN_SUBCASE(case2, array_hs_hb);
    FLATTEN_SUBCASE(case2, array_hs_db);

    FLATTEN_SUBCASE(case2, array_ds_fb);
    FLATTEN_SUBCASE(case2, array_ds_hb);
    FLATTEN_SUBCASE(case2, array_ds_db);

    // FLATTEN_SUBCASE(case2, array_ls_fb);
    // FLATTEN_SUBCASE(case2, array_ls_hb);
    // FLATTEN_SUBCASE(case2, array_ls_db);
}

TEST_CASE("flatten(case3)" * doctest::test_suite("array::flatten"))
{
    // FLATTEN_SUBCASE(case3, array);
    // FLATTEN_SUBCASE(case3, array_a);
    // FLATTEN_SUBCASE(case3, array_f);
    // FLATTEN_SUBCASE(case3, array_h);
    // FLATTEN_SUBCASE(case3, array_d);

    // FLATTEN_SUBCASE(case3, array_cs_fb);
    // FLATTEN_SUBCASE(case3, array_cs_hb);
    // FLATTEN_SUBCASE(case3, array_cs_db);

    FLATTEN_SUBCASE(case3, array_fs_fb);
    FLATTEN_SUBCASE(case3, array_fs_hb);
    FLATTEN_SUBCASE(case3, array_fs_db);

    FLATTEN_SUBCASE(case3, array_hs_fb);
    FLATTEN_SUBCASE(case3, array_hs_hb);
    FLATTEN_SUBCASE(case3, array_hs_db);

    FLATTEN_SUBCASE(case3, array_ds_fb);
    FLATTEN_SUBCASE(case3, array_ds_hb);
    FLATTEN_SUBCASE(case3, array_ds_db);

    // FLATTEN_SUBCASE(case3, array_ls_fb);
    // FLATTEN_SUBCASE(case3, array_ls_hb);
    // FLATTEN_SUBCASE(case3, array_ls_db);
}

TEST_CASE("flatten(case4)" * doctest::test_suite("array::flatten"))
{
    // FLATTEN_SUBCASE(case4, array);
    // FLATTEN_SUBCASE(case4, array_a);
    // FLATTEN_SUBCASE(case4, array_f);
    // FLATTEN_SUBCASE(case4, array_h);
    // FLATTEN_SUBCASE(case4, array_d);

    // FLATTEN_SUBCASE(case4, array_cs_fb);
    // FLATTEN_SUBCASE(case4, array_cs_hb);
    // FLATTEN_SUBCASE(case4, array_cs_db);

    FLATTEN_SUBCASE(case4, array_fs_fb);
    FLATTEN_SUBCASE(case4, array_fs_hb);
    FLATTEN_SUBCASE(case4, array_fs_db);

    FLATTEN_SUBCASE(case4, array_hs_fb);
    FLATTEN_SUBCASE(case4, array_hs_hb);
    FLATTEN_SUBCASE(case4, array_hs_db);

    FLATTEN_SUBCASE(case4, array_ds_fb);
    FLATTEN_SUBCASE(case4, array_ds_hb);
    FLATTEN_SUBCASE(case4, array_ds_db);

    // FLATTEN_SUBCASE(case4, array_ls_fb);
    // FLATTEN_SUBCASE(case4, array_ls_hb);
    // FLATTEN_SUBCASE(case4, array_ls_db);
}