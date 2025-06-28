#define NMTOOLS_CAST_ARRAYS_EXTRA(name) \
inline auto name##_cs_fb = nmtools::cast(name, nmtools::kind::ndarray_cs_fb); \
inline auto name##_cs_hb = nmtools::cast(name, nmtools::kind::ndarray_cs_hb); \
inline auto name##_cs_db = nmtools::cast(name, nmtools::kind::ndarray_cs_db); \
inline auto name##_fs_fb = nmtools::cast(name, nmtools::kind::ndarray_fs_fb); \
inline auto name##_fs_hb = nmtools::cast(name, nmtools::kind::ndarray_fs_hb); \
inline auto name##_fs_db = nmtools::cast(name, nmtools::kind::ndarray_fs_db); \
inline auto name##_hs_fb = nmtools::cast(name, nmtools::kind::ndarray_hs_fb); \
inline auto name##_hs_hb = nmtools::cast(name, nmtools::kind::ndarray_hs_hb); \
inline auto name##_hs_db = nmtools::cast(name, nmtools::kind::ndarray_hs_db); \
inline auto name##_ds_fb = nmtools::cast(name, nmtools::kind::ndarray_ds_fb); \
inline auto name##_ds_hb = nmtools::cast(name, nmtools::kind::ndarray_ds_hb); \
inline auto name##_ds_db = nmtools::cast(name, nmtools::kind::ndarray_ds_db); \
inline auto name##_ls_fb = nmtools::cast(name, nmtools::kind::ndarray_ls_fb); \
inline auto name##_ls_hb = nmtools::cast(name, nmtools::kind::ndarray_ls_hb); \
inline auto name##_ls_db = nmtools::cast(name, nmtools::kind::ndarray_ls_db);

#include "nmtools/array/activations/hardtanh.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/evaluator/cuda.hpp"
#include "nmtools/testing/data/array/hardtanh.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace cuda = na::cuda;

#define HARDTANH_SUBCASE(case_name,...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(activations, hardtanh, case_name); \
    using namespace args; \
    auto result = na::hardtanh(__VA_ARGS__, cuda::default_context()); \
    auto expect = na::hardtanh(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

TEST_CASE("hardtanh(case1)" * doctest::test_suite("array::hardtanh"))
{
    auto min_val = -1.0f;
    auto max_val =  1.0f;

    // HARDTANH_SUBCASE(case1, a, min_val, max_val);
    // HARDTANH_SUBCASE(case1, a_a, min_val, max_val);
    // HARDTANH_SUBCASE(case1, a_f, min_val, max_val);
    // HARDTANH_SUBCASE(case1, a_h, min_val, max_val);
    // HARDTANH_SUBCASE(case1, a_d, min_val, max_val);

    // HARDTANH_SUBCASE(case1, a_cs_fb, min_val, max_val);
    // HARDTANH_SUBCASE(case1, a_cs_hb, min_val, max_val);
    // HARDTANH_SUBCASE(case1, a_cs_db, min_val, max_val);

    HARDTANH_SUBCASE(case1, a_fs_fb, min_val, max_val);
    HARDTANH_SUBCASE(case1, a_fs_hb, min_val, max_val);
    HARDTANH_SUBCASE(case1, a_fs_db, min_val, max_val);

    HARDTANH_SUBCASE(case1, a_hs_fb, min_val, max_val);
    HARDTANH_SUBCASE(case1, a_hs_hb, min_val, max_val);
    HARDTANH_SUBCASE(case1, a_hs_db, min_val, max_val);

    HARDTANH_SUBCASE(case1, a_ds_fb, min_val, max_val);
    HARDTANH_SUBCASE(case1, a_ds_hb, min_val, max_val);
    HARDTANH_SUBCASE(case1, a_ds_db, min_val, max_val);

    // HARDTANH_SUBCASE(case1, a_ls_fb, min_val, max_val);
    // HARDTANH_SUBCASE(case1, a_ls_hb, min_val, max_val);
    // HARDTANH_SUBCASE(case1, a_ls_db, min_val, max_val);
}