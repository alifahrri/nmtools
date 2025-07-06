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

#include "nmtools/array/softshrink.hpp"
#include "nmtools/evaluator/hip.hpp"
#include "nmtools/testing/data/array/softshrink.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace hip = na::hip;

#define SOFTSHRINK_SUBCASE(case_name, ...) \
{ \
    NMTOOLS_TESTING_USE_CASE(activations, softshrink, case_name); \
    using namespace args; \
    auto result = na::softshrink(__VA_ARGS__, hip::default_context()); \
    auto expect = na::softshrink(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

TEST_CASE("softshrink(case1)" * doctest::test_suite("array::softshrink"))
{
    auto lambda = 0.01f;

    // SOFTSHRINK_SUBCASE(case1, a, lambda);
    // SOFTSHRINK_SUBCASE(case1, a_a, lambda);
    // SOFTSHRINK_SUBCASE(case1, a_f, lambda);
    // SOFTSHRINK_SUBCASE(case1, a_h, lambda);
    // SOFTSHRINK_SUBCASE(case1, a_d, lambda);

    // SOFTSHRINK_SUBCASE(case1, a_cs_fb, lambda);
    // SOFTSHRINK_SUBCASE(case1, a_cs_hb, lambda);
    // SOFTSHRINK_SUBCASE(case1, a_cs_db, lambda);

    SOFTSHRINK_SUBCASE(case1, a_fs_fb, lambda);
    SOFTSHRINK_SUBCASE(case1, a_fs_hb, lambda);
    SOFTSHRINK_SUBCASE(case1, a_fs_db, lambda);

    SOFTSHRINK_SUBCASE(case1, a_hs_fb, lambda);
    SOFTSHRINK_SUBCASE(case1, a_hs_hb, lambda);
    SOFTSHRINK_SUBCASE(case1, a_hs_db, lambda);

    SOFTSHRINK_SUBCASE(case1, a_ds_fb, lambda);
    SOFTSHRINK_SUBCASE(case1, a_ds_hb, lambda);
    SOFTSHRINK_SUBCASE(case1, a_ds_db, lambda);

    // SOFTSHRINK_SUBCASE(case1, a_ls_fb, lambda);
    // SOFTSHRINK_SUBCASE(case1, a_ls_hb, lambda);
    // SOFTSHRINK_SUBCASE(case1, a_ls_db, lambda);
}

