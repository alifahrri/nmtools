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

#include "nmtools/array/array/ufuncs/isfinite.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/array/eval/cuda.hpp"
#include "nmtools/testing/data/array/isfinite.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace cuda = na::cuda;

#define ISFINITE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, isfinite, case_name); \
    using namespace args; \
    auto result = na::isfinite(__VA_ARGS__, cuda::default_context()); \
    auto expect = na::isfinite(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

TEST_CASE("isfinite(case1)" * doctest::test_suite("array::isfinite"))
{
    // ISFINITE_SUBCASE(case1, a);
    // ISFINITE_SUBCASE(case1, a_a);
    // ISFINITE_SUBCASE(case1, a_f);
    // ISFINITE_SUBCASE(case1, a_h);
    // ISFINITE_SUBCASE(case1, a_d);

    // ISFINITE_SUBCASE(case1, a_cs_fb);
    // ISFINITE_SUBCASE(case1, a_cs_hb);
    // ISFINITE_SUBCASE(case1, a_cs_db);

    ISFINITE_SUBCASE(case1, a_fs_fb);
    ISFINITE_SUBCASE(case1, a_fs_hb);
    ISFINITE_SUBCASE(case1, a_fs_db);

    ISFINITE_SUBCASE(case1, a_hs_fb);
    ISFINITE_SUBCASE(case1, a_hs_hb);
    ISFINITE_SUBCASE(case1, a_hs_db);

    ISFINITE_SUBCASE(case1, a_ds_fb);
    ISFINITE_SUBCASE(case1, a_ds_hb);
    ISFINITE_SUBCASE(case1, a_ds_db);

    // ISFINITE_SUBCASE(case1, a_ls_fb);
    // ISFINITE_SUBCASE(case1, a_ls_hb);
    // ISFINITE_SUBCASE(case1, a_ls_db);
}