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

#include "nmtools/array/array/activations/hardshrink.hpp"
#include "nmtools/array/evaluator/hip.hpp"
#include "nmtools/testing/data/array/hardshrink.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace hip = na::hip;

#define HARDSHRINK_SUBCASE(case_name, ...) \
{ \
    NMTOOLS_TESTING_USE_CASE(activations, hardshrink, case_name); \
    using namespace args; \
    auto result = na::hardshrink(__VA_ARGS__, hip::default_context()); \
    auto expect = na::hardshrink(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

TEST_CASE("hardshrink(case1)" * doctest::test_suite("array::hardshrink"))
{
    auto lambda = 0.5f;

    // HARDSHRINK_SUBCASE(case1, a, lambda);
    // HARDSHRINK_SUBCASE(case1, a_a, lambda);
    // HARDSHRINK_SUBCASE(case1, a_f, lambda);
    // HARDSHRINK_SUBCASE(case1, a_h, lambda);
    // HARDSHRINK_SUBCASE(case1, a_d, lambda);

    // HARDSHRINK_SUBCASE(case1, a_cs_fb, lambda);
    // HARDSHRINK_SUBCASE(case1, a_cs_hb, lambda);
    // HARDSHRINK_SUBCASE(case1, a_cs_db, lambda);

    HARDSHRINK_SUBCASE(case1, a_fs_fb, lambda);
    HARDSHRINK_SUBCASE(case1, a_fs_hb, lambda);
    HARDSHRINK_SUBCASE(case1, a_fs_db, lambda);

    HARDSHRINK_SUBCASE(case1, a_hs_fb, lambda);
    HARDSHRINK_SUBCASE(case1, a_hs_hb, lambda);
    HARDSHRINK_SUBCASE(case1, a_hs_db, lambda);

    HARDSHRINK_SUBCASE(case1, a_ds_fb, lambda);
    HARDSHRINK_SUBCASE(case1, a_ds_hb, lambda);
    HARDSHRINK_SUBCASE(case1, a_ds_db, lambda);

    // HARDSHRINK_SUBCASE(case1, a_ls_fb, lambda);
    // HARDSHRINK_SUBCASE(case1, a_ls_hb, lambda);
    // HARDSHRINK_SUBCASE(case1, a_ls_db, lambda);
}

TEST_CASE("hardshrink(case2)" * doctest::test_suite("array::hardshrink"))
{
    // HARDSHRINK_SUBCASE(case2, a, lambda);
    // HARDSHRINK_SUBCASE(case2, a_a, lambda);
    // HARDSHRINK_SUBCASE(case2, a_f, lambda);
    // HARDSHRINK_SUBCASE(case2, a_h, lambda);
    // HARDSHRINK_SUBCASE(case2, a_d, lambda);

    // HARDSHRINK_SUBCASE(case2, a_cs_fb, lambda);
    // HARDSHRINK_SUBCASE(case2, a_cs_hb, lambda);
    // HARDSHRINK_SUBCASE(case2, a_cs_db, lambda);

    HARDSHRINK_SUBCASE(case2, a_fs_fb, lambda);
    HARDSHRINK_SUBCASE(case2, a_fs_hb, lambda);
    HARDSHRINK_SUBCASE(case2, a_fs_db, lambda);

    HARDSHRINK_SUBCASE(case2, a_hs_fb, lambda);
    HARDSHRINK_SUBCASE(case2, a_hs_hb, lambda);
    HARDSHRINK_SUBCASE(case2, a_hs_db, lambda);

    HARDSHRINK_SUBCASE(case2, a_ds_fb, lambda);
    HARDSHRINK_SUBCASE(case2, a_ds_hb, lambda);
    HARDSHRINK_SUBCASE(case2, a_ds_db, lambda);

    // HARDSHRINK_SUBCASE(case2, a_ls_fb, lambda);
    // HARDSHRINK_SUBCASE(case2, a_ls_hb, lambda);
    // HARDSHRINK_SUBCASE(case2, a_ls_db, lambda);
}