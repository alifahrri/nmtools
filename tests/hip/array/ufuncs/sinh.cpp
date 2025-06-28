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

#include "nmtools/array/ufuncs/sinh.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/evaluator/hip.hpp"
#include "nmtools/testing/data/array/sinh.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace hip = na::hip;

#undef NMTOOLS_TESTING_PRECISION
#define NMTOOLS_TESTING_PRECISION 1e-3

#define SINH_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, sinh, case_name); \
    using namespace args; \
    auto result = na::sinh(__VA_ARGS__, hip::default_context()); \
    auto expect = na::sinh(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

TEST_CASE("sinh(case1)" * doctest::test_suite("array::sinh"))
{
    // SINH_SUBCASE(case1, a);
    // SINH_SUBCASE(case1, a_a);
    // SINH_SUBCASE(case1, a_f);
    // SINH_SUBCASE(case1, a_h);
    // SINH_SUBCASE(case1, a_d);

    // SINH_SUBCASE(case1, a_cs_fb);
    // SINH_SUBCASE(case1, a_cs_hb);
    // SINH_SUBCASE(case1, a_cs_db);

    SINH_SUBCASE(case1, a_fs_fb);
    SINH_SUBCASE(case1, a_fs_hb);
    SINH_SUBCASE(case1, a_fs_db);

    SINH_SUBCASE(case1, a_hs_fb);
    SINH_SUBCASE(case1, a_hs_hb);
    SINH_SUBCASE(case1, a_hs_db);

    SINH_SUBCASE(case1, a_ds_fb);
    SINH_SUBCASE(case1, a_ds_hb);
    SINH_SUBCASE(case1, a_ds_db);

    // SINH_SUBCASE(case1, a_ls_fb);
    // SINH_SUBCASE(case1, a_ls_hb);
    // SINH_SUBCASE(case1, a_ls_db);
}