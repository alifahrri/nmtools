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

#include "nmtools/array/array/activations/relu.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/array/evaluator/sycl.hpp"
#include "nmtools/testing/data/array/relu.hpp"

namespace nm = nmtools;
namespace na = nm::array;

#define RELU_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(activations, relu, case_name); \
    using namespace args; \
    auto result = na::relu(__VA_ARGS__, na::sycl::default_context()); \
    auto expect = na::relu(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

TEST_CASE("relu(case1)" * doctest::test_suite("array::relu"))
{
    // RELU_SUBCASE(case1, a);
    // RELU_SUBCASE(case1, a_a);
    // RELU_SUBCASE(case1, a_f);
    RELU_SUBCASE(case1, a_h);
    // RELU_SUBCASE(case1, a_d);

    RELU_SUBCASE(case1, a_cs_fb);
    RELU_SUBCASE(case1, a_cs_hb);
    RELU_SUBCASE(case1, a_cs_db);

    RELU_SUBCASE(case1, a_fs_fb);
    RELU_SUBCASE(case1, a_fs_hb);
    RELU_SUBCASE(case1, a_fs_db);

    RELU_SUBCASE(case1, a_hs_fb);
    RELU_SUBCASE(case1, a_hs_hb);
    RELU_SUBCASE(case1, a_hs_db);

    RELU_SUBCASE(case1, a_ds_fb);
    RELU_SUBCASE(case1, a_ds_hb);
    RELU_SUBCASE(case1, a_ds_db);

    RELU_SUBCASE(case1, a_ls_fb);
    RELU_SUBCASE(case1, a_ls_hb);
    RELU_SUBCASE(case1, a_ls_db);
}