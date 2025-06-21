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

#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/evaluator/hip.hpp"
#include "nmtools/array/arange.hpp"
#include "nmtools/array/reshape.hpp"
#include "nmtools/testing/data/array/add.hpp"

namespace nm = nmtools;
namespace ix = nm::index;
namespace na = nmtools;

#define ADD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, add, case_name); \
    using namespace args; \
    auto result = na::add(__VA_ARGS__, na::hip::default_context()); \
    auto expect = na::add(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

#define HIP_ADD_SUBCASE(...) \
{ \
    auto result = na::add(__VA_ARGS__, na::hip::default_context()); \
    auto expect = na::add(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

TEST_CASE("add(case1)" * doctest::test_suite("array::add"))
{
    // ADD_SUBCASE(case1, a, b);
    // ADD_SUBCASE(case1, a_a, b_a);
    // ADD_SUBCASE(case1, a_f, b_f);
    // ADD_SUBCASE(case1, a_h, b_h);
    // ADD_SUBCASE(case1, a_d, b_d);

    // ADD_SUBCASE(case1, a_cs_fb, b_cs_fb);
    // ADD_SUBCASE(case1, a_cs_hb, b_cs_hb);
    // ADD_SUBCASE(case1, a_cs_db, b_cs_db);

    ADD_SUBCASE(case1, a_fs_fb, b_fs_fb);
    ADD_SUBCASE(case1, a_fs_hb, b_fs_hb);
    ADD_SUBCASE(case1, a_fs_db, b_fs_db);

    ADD_SUBCASE(case1, a_hs_fb, b_hs_fb);
    ADD_SUBCASE(case1, a_hs_hb, b_hs_hb);
    ADD_SUBCASE(case1, a_hs_db, b_hs_db);

    ADD_SUBCASE(case1, a_ds_fb, b_ds_fb);
    ADD_SUBCASE(case1, a_ds_hb, b_ds_hb);
    ADD_SUBCASE(case1, a_ds_db, b_ds_db);

    // ADD_SUBCASE(case1, a_ls_fb, b_ls_fb);
    // ADD_SUBCASE(case1, a_ls_hb, b_ls_hb);
    // ADD_SUBCASE(case1, a_ls_db, b_ls_db);
}

TEST_CASE("add(case1)" * doctest::test_suite("array::add"))
{
    auto lhs_shape = nmtools_array{128};
    auto lhs_numel = ix::product(lhs_shape);
    auto lhs_start = 0;
    auto lhs_stop  = lhs_start + lhs_numel;
    auto lhs_step  = 1;
    auto lhs_flat  = na::arange(lhs_start,lhs_stop,lhs_step);

    auto rhs_shape = nmtools_array{128};
    auto rhs_numel = ix::product(rhs_shape);
    auto rhs_start = 0;
    auto rhs_stop  = rhs_start + rhs_numel;
    auto rhs_step  = 1;
    auto rhs_flat  = na::arange(rhs_start,rhs_stop,rhs_step);

    auto lhs = na::reshape(lhs_flat,lhs_shape);
    auto rhs = na::reshape(rhs_flat,rhs_shape);

    HIP_ADD_SUBCASE( lhs, rhs );
}