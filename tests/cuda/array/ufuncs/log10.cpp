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

#include "nmtools/array/array/ufuncs/log10.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/array/eval/cuda.hpp"
#include "nmtools/testing/data/array/log10.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace cuda = na::cuda;

#define LOG10_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, log10, case_name); \
    using namespace args; \
    auto result = na::log10(__VA_ARGS__, cuda::default_context()); \
    auto expect = na::log10(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

TEST_CASE("log10(case1)" * doctest::test_suite("array::log10"))
{
    // LOG10_SUBCASE(case1, a);
    // LOG10_SUBCASE(case1, a_a);
    // LOG10_SUBCASE(case1, a_f);
    // LOG10_SUBCASE(case1, a_h);
    // LOG10_SUBCASE(case1, a_d);

    // LOG10_SUBCASE(case1, a_cs_fb);
    // LOG10_SUBCASE(case1, a_cs_hb);
    // LOG10_SUBCASE(case1, a_cs_db);

    LOG10_SUBCASE(case1, a_fs_fb);
    LOG10_SUBCASE(case1, a_fs_hb);
    LOG10_SUBCASE(case1, a_fs_db);

    LOG10_SUBCASE(case1, a_hs_fb);
    LOG10_SUBCASE(case1, a_hs_hb);
    LOG10_SUBCASE(case1, a_hs_db);

    LOG10_SUBCASE(case1, a_ds_fb);
    LOG10_SUBCASE(case1, a_ds_hb);
    LOG10_SUBCASE(case1, a_ds_db);

    // LOG10_SUBCASE(case1, a_ls_fb);
    // LOG10_SUBCASE(case1, a_ls_hb);
    // LOG10_SUBCASE(case1, a_ls_db);
}