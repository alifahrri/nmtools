#if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
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
#endif

#include "nmtools/array/leaky_relu.hpp"
#include "nmtools/testing/data/array/leaky_relu.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/context/default.hpp"

namespace nm = nmtools;

#define LEAKY_RELU_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(activations, leaky_relu, case_name); \
    using namespace args; \
    auto result = nm::leaky_relu(__VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("leaky_relu(case1)" * doctest::test_suite("array::leaky_relu"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    LEAKY_RELU_SUBCASE(case1, a);
    LEAKY_RELU_SUBCASE(case1, a_a);
    LEAKY_RELU_SUBCASE(case1, a_f);
    LEAKY_RELU_SUBCASE(case1, a_h);
    LEAKY_RELU_SUBCASE(case1, a_d);

    #else
    LEAKY_RELU_SUBCASE(case1, a_cs_fb);
    LEAKY_RELU_SUBCASE(case1, a_cs_hb);
    LEAKY_RELU_SUBCASE(case1, a_cs_db);

    LEAKY_RELU_SUBCASE(case1, a_fs_fb);
    LEAKY_RELU_SUBCASE(case1, a_fs_hb);
    LEAKY_RELU_SUBCASE(case1, a_fs_db);

    LEAKY_RELU_SUBCASE(case1, a_hs_fb);
    LEAKY_RELU_SUBCASE(case1, a_hs_hb);
    LEAKY_RELU_SUBCASE(case1, a_hs_db);

    LEAKY_RELU_SUBCASE(case1, a_ds_fb);
    LEAKY_RELU_SUBCASE(case1, a_ds_hb);
    LEAKY_RELU_SUBCASE(case1, a_ds_db);

    LEAKY_RELU_SUBCASE(case1, a_ls_fb);
    LEAKY_RELU_SUBCASE(case1, a_ls_hb);
    LEAKY_RELU_SUBCASE(case1, a_ls_db);
    #endif
}