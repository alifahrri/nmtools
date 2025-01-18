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

#include "nmtools/array/array/atleast_2d.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/array/evaluator/hip.hpp"
#include "nmtools/testing/data/array/atleast_2d.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace hip = na::hip;

#define ATLEAST_2D_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, atleast_2d, case_name); \
    using namespace args; \
    auto result = na::atleast_2d(__VA_ARGS__, hip::default_context()); \
    auto expect = na::atleast_2d(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

// TEST_CASE("atleast_2d(case1)" * doctest::test_suite("array::atleast_2d"))
// {
//     ATLEAST_2D_SUBCASE(case1, a);
// }

TEST_CASE("atleast_2d(case2)" * doctest::test_suite("array::atleast_2d"))
{
    // ATLEAST_2D_SUBCASE(case2, a);
    // ATLEAST_2D_SUBCASE(case2, a_a);
    // ATLEAST_2D_SUBCASE(case2, a_f);
    // ATLEAST_2D_SUBCASE(case2, a_h);
    // ATLEAST_2D_SUBCASE(case2, a_d);

    // ATLEAST_2D_SUBCASE(case2, a_cs_fb);
    // ATLEAST_2D_SUBCASE(case2, a_cs_hb);
    // ATLEAST_2D_SUBCASE(case2, a_cs_db);

    ATLEAST_2D_SUBCASE(case2, a_fs_fb);
    ATLEAST_2D_SUBCASE(case2, a_fs_hb);
    ATLEAST_2D_SUBCASE(case2, a_fs_db);

    ATLEAST_2D_SUBCASE(case2, a_hs_fb);
    ATLEAST_2D_SUBCASE(case2, a_hs_hb);
    ATLEAST_2D_SUBCASE(case2, a_hs_db);

    ATLEAST_2D_SUBCASE(case2, a_ds_fb);
    ATLEAST_2D_SUBCASE(case2, a_ds_hb);
    ATLEAST_2D_SUBCASE(case2, a_ds_db);

    // ATLEAST_2D_SUBCASE(case2, a_ls_fb);
    // ATLEAST_2D_SUBCASE(case2, a_ls_hb);
    // ATLEAST_2D_SUBCASE(case2, a_ls_db);
}

TEST_CASE("atleast_2d(case3)" * doctest::test_suite("array::atleast_2d"))
{
    // ATLEAST_2D_SUBCASE(case3, a);
    // ATLEAST_2D_SUBCASE(case3, a_a);
    // ATLEAST_2D_SUBCASE(case3, a_f);
    // ATLEAST_2D_SUBCASE(case3, a_h);
    // ATLEAST_2D_SUBCASE(case3, a_d);

    // ATLEAST_2D_SUBCASE(case3, a_cs_fb);
    // ATLEAST_2D_SUBCASE(case3, a_cs_hb);
    // ATLEAST_2D_SUBCASE(case3, a_cs_db);

    ATLEAST_2D_SUBCASE(case3, a_fs_fb);
    ATLEAST_2D_SUBCASE(case3, a_fs_hb);
    ATLEAST_2D_SUBCASE(case3, a_fs_db);

    ATLEAST_2D_SUBCASE(case3, a_hs_fb);
    ATLEAST_2D_SUBCASE(case3, a_hs_hb);
    ATLEAST_2D_SUBCASE(case3, a_hs_db);

    ATLEAST_2D_SUBCASE(case3, a_ds_fb);
    ATLEAST_2D_SUBCASE(case3, a_ds_hb);
    ATLEAST_2D_SUBCASE(case3, a_ds_db);

    // ATLEAST_2D_SUBCASE(case3, a_ls_fb);
    // ATLEAST_2D_SUBCASE(case3, a_ls_hb);
    // ATLEAST_2D_SUBCASE(case3, a_ls_db);
}

TEST_CASE("atleast_2d(case4)" * doctest::test_suite("array::atleast_2d"))
{
    // ATLEAST_2D_SUBCASE(case4, a);
    // ATLEAST_2D_SUBCASE(case4, a_a);
    // ATLEAST_2D_SUBCASE(case4, a_f);
    // ATLEAST_2D_SUBCASE(case4, a_h);
    // ATLEAST_2D_SUBCASE(case4, a_d);

    // ATLEAST_2D_SUBCASE(case4, a_cs_fb);
    // ATLEAST_2D_SUBCASE(case4, a_cs_hb);
    // ATLEAST_2D_SUBCASE(case4, a_cs_db);

    ATLEAST_2D_SUBCASE(case4, a_fs_fb);
    ATLEAST_2D_SUBCASE(case4, a_fs_hb);
    ATLEAST_2D_SUBCASE(case4, a_fs_db);

    ATLEAST_2D_SUBCASE(case4, a_hs_fb);
    ATLEAST_2D_SUBCASE(case4, a_hs_hb);
    ATLEAST_2D_SUBCASE(case4, a_hs_db);

    ATLEAST_2D_SUBCASE(case4, a_ds_fb);
    ATLEAST_2D_SUBCASE(case4, a_ds_hb);
    ATLEAST_2D_SUBCASE(case4, a_ds_db);

    // ATLEAST_2D_SUBCASE(case4, a_ls_fb);
    // ATLEAST_2D_SUBCASE(case4, a_ls_hb);
    // ATLEAST_2D_SUBCASE(case4, a_ls_db);
}