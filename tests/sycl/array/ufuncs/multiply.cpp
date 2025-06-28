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

#include "nmtools/array/ufuncs/multiply.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/evaluator/sycl.hpp"
#include "nmtools/testing/data/array/multiply.hpp"

namespace nm = nmtools;
namespace na = nmtools;

#define MULTIPLY_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, multiply, case_name); \
    using namespace args; \
    auto result = na::multiply(__VA_ARGS__, na::sycl::default_context()); \
    auto expect = na::multiply(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

// TODO: fix SIGFPE, floating point error signal
TEST_CASE("multiply(case1)" * doctest::test_suite("array::multiply") * doctest::skip())
{
    // MULTIPLY_SUBCASE(case1, a, b);
    // MULTIPLY_SUBCASE(case1, a_a, b_a);
    // MULTIPLY_SUBCASE(case1, a_f, b_f);
    // MULTIPLY_SUBCASE(case1, a_h, b_h);
    // MULTIPLY_SUBCASE(case1, a_d, b_d);

    // MULTIPLY_SUBCASE(case1, a_cs_fb, b_cs_fb);
    // MULTIPLY_SUBCASE(case1, a_cs_hb, b_cs_hb);
    // MULTIPLY_SUBCASE(case1, a_cs_db, b_cs_db);

    MULTIPLY_SUBCASE(case1, a_fs_fb, b_fs_fb);
    MULTIPLY_SUBCASE(case1, a_fs_hb, b_fs_hb);
    MULTIPLY_SUBCASE(case1, a_fs_db, b_fs_db);

    MULTIPLY_SUBCASE(case1, a_hs_fb, b_hs_fb);
    MULTIPLY_SUBCASE(case1, a_hs_hb, b_hs_hb);
    MULTIPLY_SUBCASE(case1, a_hs_db, b_hs_db);

    MULTIPLY_SUBCASE(case1, a_ds_fb, b_ds_fb);
    MULTIPLY_SUBCASE(case1, a_ds_hb, b_ds_hb);
    MULTIPLY_SUBCASE(case1, a_ds_db, b_ds_db);

    // MULTIPLY_SUBCASE(case1, a_ls_fb, b_ls_fb);
    // MULTIPLY_SUBCASE(case1, a_ls_hb, b_ls_hb);
    // MULTIPLY_SUBCASE(case1, a_ls_db, b_ls_db);
}