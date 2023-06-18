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

#include "nmtools/array/array/ufuncs/add.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/array/eval/cuda.hpp"
#include "nmtools/testing/data/array/add.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace cuda = na::cuda;

#define OUTER_ADD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, outer_add, case_name); \
    using namespace args; \
    auto result = na::add.outer(__VA_ARGS__, cuda::default_context()); \
    auto expect = na::add.outer(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

TEST_CASE("outer_add(case1)" * doctest::test_suite("array::add.outer"))
{
    // OUTER_ADD_SUBCASE(case1, a, b);
    // OUTER_ADD_SUBCASE(case1, a_a, b_a);
    // OUTER_ADD_SUBCASE(case1, a_f, b_f);
    // OUTER_ADD_SUBCASE(case1, a_h, b_h);
    // OUTER_ADD_SUBCASE(case1, a_d, b_d);

    // OUTER_ADD_SUBCASE(case1, a_cs_fb, b_cs_fb);
    // OUTER_ADD_SUBCASE(case1, a_cs_hb, b_cs_hb);
    // OUTER_ADD_SUBCASE(case1, a_cs_db, b_cs_db);

    OUTER_ADD_SUBCASE(case1, a_fs_fb, b_fs_fb);
    OUTER_ADD_SUBCASE(case1, a_fs_hb, b_fs_hb);
    OUTER_ADD_SUBCASE(case1, a_fs_db, b_fs_db);

    OUTER_ADD_SUBCASE(case1, a_hs_fb, b_hs_fb);
    OUTER_ADD_SUBCASE(case1, a_hs_hb, b_hs_hb);
    OUTER_ADD_SUBCASE(case1, a_hs_db, b_hs_db);

    OUTER_ADD_SUBCASE(case1, a_ds_fb, b_ds_fb);
    OUTER_ADD_SUBCASE(case1, a_ds_hb, b_ds_hb);
    OUTER_ADD_SUBCASE(case1, a_ds_db, b_ds_db);

    // OUTER_ADD_SUBCASE(case1, a_ls_fb, b_ls_fb);
    // OUTER_ADD_SUBCASE(case1, a_ls_hb, b_ls_hb);
    // OUTER_ADD_SUBCASE(case1, a_ls_db, b_ls_db);
}