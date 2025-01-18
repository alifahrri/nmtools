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

#include "nmtools/array/array/ufuncs/exp2.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/array/evaluator/hip.hpp"
#include "nmtools/testing/data/array/exp2.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace hip = na::hip;

#define EXP2_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, exp2, case_name); \
    using namespace args; \
    auto result = na::exp2(__VA_ARGS__, hip::default_context()); \
    auto expect = na::exp2(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

TEST_CASE("exp2(case1)" * doctest::test_suite("array::exp2"))
{
    // EXP2_SUBCASE(case1, a);
    // EXP2_SUBCASE(case1, a_a);
    // EXP2_SUBCASE(case1, a_f);
    // EXP2_SUBCASE(case1, a_h);
    // EXP2_SUBCASE(case1, a_d);

    // EXP2_SUBCASE(case1, a_cs_fb);
    // EXP2_SUBCASE(case1, a_cs_hb);
    // EXP2_SUBCASE(case1, a_cs_db);

    EXP2_SUBCASE(case1, a_fs_fb);
    EXP2_SUBCASE(case1, a_fs_hb);
    EXP2_SUBCASE(case1, a_fs_db);

    EXP2_SUBCASE(case1, a_hs_fb);
    EXP2_SUBCASE(case1, a_hs_hb);
    EXP2_SUBCASE(case1, a_hs_db);

    EXP2_SUBCASE(case1, a_ds_fb);
    EXP2_SUBCASE(case1, a_ds_hb);
    EXP2_SUBCASE(case1, a_ds_db);

    // EXP2_SUBCASE(case1, a_ls_fb);
    // EXP2_SUBCASE(case1, a_ls_hb);
    // EXP2_SUBCASE(case1, a_ls_db);
}