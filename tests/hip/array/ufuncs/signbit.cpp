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

#include "nmtools/array/array/ufuncs/signbit.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/array/eval/hip.hpp"
#include "nmtools/testing/data/array/signbit.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace hip = na::hip;

#define SIGNBIT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, signbit, case_name); \
    using namespace args; \
    auto result = na::signbit(__VA_ARGS__, hip::default_context()); \
    auto expect = na::signbit(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

TEST_CASE("signbit(case1)" * doctest::test_suite("array::signbit"))
{
    // SIGNBIT_SUBCASE(case1, a);
    // SIGNBIT_SUBCASE(case1, a_a);
    // SIGNBIT_SUBCASE(case1, a_f);
    // SIGNBIT_SUBCASE(case1, a_h);
    // SIGNBIT_SUBCASE(case1, a_d);

    // SIGNBIT_SUBCASE(case1, a_cs_fb);
    // SIGNBIT_SUBCASE(case1, a_cs_hb);
    // SIGNBIT_SUBCASE(case1, a_cs_db);

    SIGNBIT_SUBCASE(case1, a_fs_fb);
    SIGNBIT_SUBCASE(case1, a_fs_hb);
    SIGNBIT_SUBCASE(case1, a_fs_db);

    SIGNBIT_SUBCASE(case1, a_hs_fb);
    SIGNBIT_SUBCASE(case1, a_hs_hb);
    SIGNBIT_SUBCASE(case1, a_hs_db);

    SIGNBIT_SUBCASE(case1, a_ds_fb);
    SIGNBIT_SUBCASE(case1, a_ds_hb);
    SIGNBIT_SUBCASE(case1, a_ds_db);

    // SIGNBIT_SUBCASE(case1, a_ls_fb);
    // SIGNBIT_SUBCASE(case1, a_ls_hb);
    // SIGNBIT_SUBCASE(case1, a_ls_db);
}