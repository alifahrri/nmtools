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

#include "nmtools/array/array/concatenate.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/array/eval/cuda.hpp"
#include "nmtools/testing/data/array/concatenate.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace cuda = na::cuda;

#define CONCATENATE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, concatenate, case_name); \
    using namespace args; \
    auto result = na::concatenate(__VA_ARGS__, cuda::default_context()); \
    auto expect = na::concatenate(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

TEST_CASE("concatenate(case1)" * doctest::test_suite("array::concatenate"))
{
    // CONCATENATE_SUBCASE(case1, lhs, rhs, axis);
    // CONCATENATE_SUBCASE(case1, lhs_a, rhs_a, axis);
    // CONCATENATE_SUBCASE(case1, lhs_f, rhs_f, axis);
    // CONCATENATE_SUBCASE(case1, lhs_h, rhs_h, axis);
    // CONCATENATE_SUBCASE(case1, lhs_d, rhs_d, axis);

    // CONCATENATE_SUBCASE(case1, lhs_cs_fb, rhs_cs_fb, axis);
    // CONCATENATE_SUBCASE(case1, lhs_cs_hb, rhs_cs_hb, axis);
    // CONCATENATE_SUBCASE(case1, lhs_cs_db, rhs_cs_db, axis);

    CONCATENATE_SUBCASE(case1, lhs_fs_fb, rhs_fs_fb, axis);
    CONCATENATE_SUBCASE(case1, lhs_fs_hb, rhs_fs_hb, axis);
    CONCATENATE_SUBCASE(case1, lhs_fs_db, rhs_fs_db, axis);

    CONCATENATE_SUBCASE(case1, lhs_hs_fb, rhs_hs_fb, axis);
    CONCATENATE_SUBCASE(case1, lhs_hs_hb, rhs_hs_hb, axis);
    CONCATENATE_SUBCASE(case1, lhs_hs_db, rhs_hs_db, axis);

    CONCATENATE_SUBCASE(case1, lhs_ds_fb, rhs_ds_fb, axis);
    CONCATENATE_SUBCASE(case1, lhs_ds_hb, rhs_ds_hb, axis);
    CONCATENATE_SUBCASE(case1, lhs_ds_db, rhs_ds_db, axis);

    // CONCATENATE_SUBCASE(case1, lhs_ls_fb, rhs_ls_fb, axis);
    // CONCATENATE_SUBCASE(case1, lhs_ls_hb, rhs_ls_hb, axis);
    // CONCATENATE_SUBCASE(case1, lhs_ls_db, rhs_ls_db, axis);
}