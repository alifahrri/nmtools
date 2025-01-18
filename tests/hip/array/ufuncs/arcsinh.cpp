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

#include "nmtools/array/array/ufuncs/arcsinh.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/array/evaluator/hip.hpp"
#include "nmtools/testing/data/array/arcsinh.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace hip = na::hip;

#define ARCSINH_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, arcsinh, case_name); \
    using namespace args; \
    auto result = na::arcsinh(__VA_ARGS__, hip::default_context()); \
    auto expect = na::arcsinh(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

TEST_CASE("arcsinh(case1)" * doctest::test_suite("array::arcsinh"))
{
    // ARCSINH_SUBCASE(case1, a);
    // ARCSINH_SUBCASE(case1, a_a);
    // ARCSINH_SUBCASE(case1, a_f);
    // ARCSINH_SUBCASE(case1, a_h);
    // ARCSINH_SUBCASE(case1, a_d);

    // ARCSINH_SUBCASE(case1, a_cs_fb);
    // ARCSINH_SUBCASE(case1, a_cs_hb);
    // ARCSINH_SUBCASE(case1, a_cs_db);

    ARCSINH_SUBCASE(case1, a_fs_fb);
    ARCSINH_SUBCASE(case1, a_fs_hb);
    ARCSINH_SUBCASE(case1, a_fs_db);

    ARCSINH_SUBCASE(case1, a_hs_fb);
    ARCSINH_SUBCASE(case1, a_hs_hb);
    ARCSINH_SUBCASE(case1, a_hs_db);

    ARCSINH_SUBCASE(case1, a_ds_fb);
    ARCSINH_SUBCASE(case1, a_ds_hb);
    ARCSINH_SUBCASE(case1, a_ds_db);

    // ARCSINH_SUBCASE(case1, a_ls_fb);
    // ARCSINH_SUBCASE(case1, a_ls_hb);
    // ARCSINH_SUBCASE(case1, a_ls_db);
}