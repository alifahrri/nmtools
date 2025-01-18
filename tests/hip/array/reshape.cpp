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

#include "nmtools/array/array/reshape.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/array/evaluator/hip.hpp"
#include "nmtools/testing/data/array/reshape.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace hip = na::hip;

#define RESHAPE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(reshape, case_name); \
    using namespace args; \
    auto result = na::reshape(__VA_ARGS__, hip::default_context()); \
    auto expect = na::reshape(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

TEST_CASE("reshape(case1)" * doctest::test_suite("array::reshape"))
{
    // RESHAPE_SUBCASE(case1, array, newshape);
    // RESHAPE_SUBCASE(case1, array_a, newshape);
    // RESHAPE_SUBCASE(case1, array_f, newshape);
    // RESHAPE_SUBCASE(case1, array_h, newshape);
    // RESHAPE_SUBCASE(case1, array_d, newshape);

    // RESHAPE_SUBCASE(case1, array_cs_fb, newshape);
    // RESHAPE_SUBCASE(case1, array_cs_hb, newshape);
    // RESHAPE_SUBCASE(case1, array_cs_db, newshape);

    RESHAPE_SUBCASE(case1, array_fs_fb, newshape);
    RESHAPE_SUBCASE(case1, array_fs_hb, newshape);
    RESHAPE_SUBCASE(case1, array_fs_db, newshape);

    RESHAPE_SUBCASE(case1, array_hs_fb, newshape);
    RESHAPE_SUBCASE(case1, array_hs_hb, newshape);
    RESHAPE_SUBCASE(case1, array_hs_db, newshape);

    RESHAPE_SUBCASE(case1, array_ds_fb, newshape);
    RESHAPE_SUBCASE(case1, array_ds_hb, newshape);
    RESHAPE_SUBCASE(case1, array_ds_db, newshape);

    // RESHAPE_SUBCASE(case1, array_ls_fb, newshape);
    // RESHAPE_SUBCASE(case1, array_ls_hb, newshape);
    // RESHAPE_SUBCASE(case1, array_ls_db, newshape);
}