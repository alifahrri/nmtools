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

#include "nmtools/array/array/activations/celu.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/array/eval/sycl.hpp"
#include "nmtools/testing/data/array/celu.hpp"

namespace nm = nmtools;
namespace na = nm::array;

#define CELU_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(activations, celu, case_name); \
    using namespace args; \
    auto result = na::celu(__VA_ARGS__, na::sycl::default_context()); \
    auto expect = na::celu(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

TEST_CASE("celu(case1)" * doctest::test_suite("array::celu"))
{
    auto alpha = 1.0f;

    // CELU_SUBCASE(case1, a, alpha);
    // CELU_SUBCASE(case1, a_a, alpha);
    // CELU_SUBCASE(case1, a_f, alpha);
    CELU_SUBCASE(case1, a_h, alpha);
    // CELU_SUBCASE(case1, a_d, alpha);

    CELU_SUBCASE(case1, a_cs_fb, alpha);
    CELU_SUBCASE(case1, a_cs_hb, alpha);
    CELU_SUBCASE(case1, a_cs_db, alpha);

    CELU_SUBCASE(case1, a_fs_fb, alpha);
    CELU_SUBCASE(case1, a_fs_hb, alpha);
    CELU_SUBCASE(case1, a_fs_db, alpha);

    CELU_SUBCASE(case1, a_hs_fb, alpha);
    CELU_SUBCASE(case1, a_hs_hb, alpha);
    CELU_SUBCASE(case1, a_hs_db, alpha);

    CELU_SUBCASE(case1, a_ds_fb, alpha);
    CELU_SUBCASE(case1, a_ds_hb, alpha);
    CELU_SUBCASE(case1, a_ds_db, alpha);

    CELU_SUBCASE(case1, a_ls_fb, alpha);
    CELU_SUBCASE(case1, a_ls_hb, alpha);
    CELU_SUBCASE(case1, a_ls_db, alpha);
}

TEST_CASE("celu(case2)" * doctest::test_suite("array::celu"))
{
    // CELU_SUBCASE(case2, a, alpha);
    // CELU_SUBCASE(case2, a_a, alpha);
    // CELU_SUBCASE(case2, a_f, alpha);
    CELU_SUBCASE(case2, a_h, alpha);
    // CELU_SUBCASE(case2, a_d, alpha);

    CELU_SUBCASE(case2, a_cs_fb, alpha);
    CELU_SUBCASE(case2, a_cs_hb, alpha);
    CELU_SUBCASE(case2, a_cs_db, alpha);

    CELU_SUBCASE(case2, a_fs_fb, alpha);
    CELU_SUBCASE(case2, a_fs_hb, alpha);
    CELU_SUBCASE(case2, a_fs_db, alpha);

    CELU_SUBCASE(case2, a_hs_fb, alpha);
    CELU_SUBCASE(case2, a_hs_hb, alpha);
    CELU_SUBCASE(case2, a_hs_db, alpha);

    CELU_SUBCASE(case2, a_ds_fb, alpha);
    CELU_SUBCASE(case2, a_ds_hb, alpha);
    CELU_SUBCASE(case2, a_ds_db, alpha);

    CELU_SUBCASE(case2, a_ls_fb, alpha);
    CELU_SUBCASE(case2, a_ls_hb, alpha);
    CELU_SUBCASE(case2, a_ls_db, alpha);
}