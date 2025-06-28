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

#include "nmtools/array/activations/leaky_relu.hpp"
#include "nmtools/evaluator/hip.hpp"
#include "nmtools/testing/data/array/leaky_relu.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace hip = na::hip;

#define LEAKY_RELU_SUBCASE(case_name, ...) \
{ \
    NMTOOLS_TESTING_USE_CASE(activations, leaky_relu, case_name); \
    using namespace args; \
    auto result = na::leaky_relu(__VA_ARGS__, hip::default_context()); \
    auto expect = na::leaky_relu(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

TEST_CASE("leaky_relu(case1)" * doctest::test_suite("array::leaky_relu"))
{
    auto negative_slope = 0.01f;

    // LEAKY_RELU_SUBCASE(case1, a, negative_slope);
    // LEAKY_RELU_SUBCASE(case1, a_a, negative_slope);
    // LEAKY_RELU_SUBCASE(case1, a_f, negative_slope);
    // LEAKY_RELU_SUBCASE(case1, a_h, negative_slope);
    // LEAKY_RELU_SUBCASE(case1, a_d, negative_slope);

    // LEAKY_RELU_SUBCASE(case1, a_cs_fb, negative_slope);
    // LEAKY_RELU_SUBCASE(case1, a_cs_hb, negative_slope);
    // LEAKY_RELU_SUBCASE(case1, a_cs_db, negative_slope);

    LEAKY_RELU_SUBCASE(case1, a_fs_fb, negative_slope);
    LEAKY_RELU_SUBCASE(case1, a_fs_hb, negative_slope);
    LEAKY_RELU_SUBCASE(case1, a_fs_db, negative_slope);

    LEAKY_RELU_SUBCASE(case1, a_hs_fb, negative_slope);
    LEAKY_RELU_SUBCASE(case1, a_hs_hb, negative_slope);
    LEAKY_RELU_SUBCASE(case1, a_hs_db, negative_slope);

    LEAKY_RELU_SUBCASE(case1, a_ds_fb, negative_slope);
    LEAKY_RELU_SUBCASE(case1, a_ds_hb, negative_slope);
    LEAKY_RELU_SUBCASE(case1, a_ds_db, negative_slope);

    // LEAKY_RELU_SUBCASE(case1, a_ls_fb, negative_slope);
    // LEAKY_RELU_SUBCASE(case1, a_ls_hb, negative_slope);
    // LEAKY_RELU_SUBCASE(case1, a_ls_db, negative_slope);
}

