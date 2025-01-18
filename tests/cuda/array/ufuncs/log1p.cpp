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

#include "nmtools/array/array/ufuncs/log1p.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/array/evaluator/cuda.hpp"
#include "nmtools/testing/data/array/log1p.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace cuda = na::cuda;

#define LOG1P_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, log1p, case_name); \
    using namespace args; \
    auto result = na::log1p(__VA_ARGS__, cuda::default_context()); \
    auto expect = na::log1p(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

TEST_CASE("log1p(case1)" * doctest::test_suite("array::log1p"))
{
    // LOG1P_SUBCASE(case1, a);
    // LOG1P_SUBCASE(case1, a_a);
    // LOG1P_SUBCASE(case1, a_f);
    // LOG1P_SUBCASE(case1, a_h);
    // LOG1P_SUBCASE(case1, a_d);

    // LOG1P_SUBCASE(case1, a_cs_fb);
    // LOG1P_SUBCASE(case1, a_cs_hb);
    // LOG1P_SUBCASE(case1, a_cs_db);

    LOG1P_SUBCASE(case1, a_fs_fb);
    LOG1P_SUBCASE(case1, a_fs_hb);
    LOG1P_SUBCASE(case1, a_fs_db);

    LOG1P_SUBCASE(case1, a_hs_fb);
    LOG1P_SUBCASE(case1, a_hs_hb);
    LOG1P_SUBCASE(case1, a_hs_db);

    LOG1P_SUBCASE(case1, a_ds_fb);
    LOG1P_SUBCASE(case1, a_ds_hb);
    LOG1P_SUBCASE(case1, a_ds_db);

    // LOG1P_SUBCASE(case1, a_ls_fb);
    // LOG1P_SUBCASE(case1, a_ls_hb);
    // LOG1P_SUBCASE(case1, a_ls_db);
}