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

#include "nmtools/array/relu6.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/evaluator/cuda.hpp"
#include "nmtools/testing/data/array/relu6.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace cuda = na::cuda;

#define RELU6_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(activations, relu6, case_name); \
    using namespace args; \
    auto result = na::relu6(__VA_ARGS__, cuda::default_context()); \
    auto expect = na::relu6(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

TEST_CASE("relu6(case1)" * doctest::test_suite("array::relu6"))
{
    // RELU6_SUBCASE(case1, a);
    // RELU6_SUBCASE(case1, a_a);
    // RELU6_SUBCASE(case1, a_f);
    // RELU6_SUBCASE(case1, a_h);
    // RELU6_SUBCASE(case1, a_d);

    // RELU6_SUBCASE(case1, a_cs_fb);
    // RELU6_SUBCASE(case1, a_cs_hb);
    // RELU6_SUBCASE(case1, a_cs_db);

    RELU6_SUBCASE(case1, a_fs_fb);
    RELU6_SUBCASE(case1, a_fs_hb);
    RELU6_SUBCASE(case1, a_fs_db);

    RELU6_SUBCASE(case1, a_hs_fb);
    RELU6_SUBCASE(case1, a_hs_hb);
    RELU6_SUBCASE(case1, a_hs_db);

    RELU6_SUBCASE(case1, a_ds_fb);
    RELU6_SUBCASE(case1, a_ds_hb);
    RELU6_SUBCASE(case1, a_ds_db);

    // RELU6_SUBCASE(case1, a_ls_fb);
    // RELU6_SUBCASE(case1, a_ls_hb);
    // RELU6_SUBCASE(case1, a_ls_db);
}