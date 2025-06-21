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

#include "nmtools/array/broadcast_to.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/evaluator/hip.hpp"
#include "nmtools/testing/data/array/broadcast_to.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace hip = na::hip;

#define BROADCAST_TO_SUBCASE(case_name, array, shape) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(broadcast_to, case_name); \
    auto result = na::broadcast_to(args::array, args::shape, hip::default_context()); \
    auto expect = na::broadcast_to(args::array, args::shape); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_EQUAL( result, expect ); \
}

// TODO: fix runtime
TEST_CASE("broadcast_to(case1)" * doctest::test_suite("array::broadcast_to"))
{
    BROADCAST_TO_SUBCASE( case1, x_a, shape );

    BROADCAST_TO_SUBCASE( case1, x_fs_fb, shape );
    BROADCAST_TO_SUBCASE( case1, x_fs_hb, shape );
    BROADCAST_TO_SUBCASE( case1, x_fs_db, shape );

    BROADCAST_TO_SUBCASE( case1, x_hs_fb, shape );
    BROADCAST_TO_SUBCASE( case1, x_hs_hb, shape );
    BROADCAST_TO_SUBCASE( case1, x_hs_db, shape );

    BROADCAST_TO_SUBCASE( case1, x_ds_fb, shape );
    BROADCAST_TO_SUBCASE( case1, x_ds_hb, shape );
    BROADCAST_TO_SUBCASE( case1, x_ds_db, shape );

    // TODO: support eh following combo
    // BROADCAST_TO_SUBCASE( case1, x_ls_fb, shape );
    // BROADCAST_TO_SUBCASE( case1, x_ls_hb, shape );
    // BROADCAST_TO_SUBCASE( case1, x_ls_db, shape );

    // BROADCAST_TO_SUBCASE( case1, x_f, shape );
    // BROADCAST_TO_SUBCASE( case1, x_d, shape );
    // BROADCAST_TO_SUBCASE( case1, x_h, shape );
}

TEST_CASE("broadcast_to(case2)" * doctest::test_suite("array::broadcast_to"))
{
    BROADCAST_TO_SUBCASE( case2, x_a, shape );

    BROADCAST_TO_SUBCASE( case2, x_fs_fb, shape );
    BROADCAST_TO_SUBCASE( case2, x_fs_hb, shape );
    BROADCAST_TO_SUBCASE( case2, x_fs_db, shape );

    BROADCAST_TO_SUBCASE( case2, x_hs_fb, shape );
    BROADCAST_TO_SUBCASE( case2, x_hs_hb, shape );
    BROADCAST_TO_SUBCASE( case2, x_hs_db, shape );

    BROADCAST_TO_SUBCASE( case2, x_ds_fb, shape );
    BROADCAST_TO_SUBCASE( case2, x_ds_hb, shape );
    BROADCAST_TO_SUBCASE( case2, x_ds_db, shape );
}

TEST_CASE("broadcast_to(case3)" * doctest::test_suite("array::broadcast_to"))
{
    BROADCAST_TO_SUBCASE( case3, x_a, shape );

    BROADCAST_TO_SUBCASE( case3, x_fs_fb, shape );
    BROADCAST_TO_SUBCASE( case3, x_fs_hb, shape );
    BROADCAST_TO_SUBCASE( case3, x_fs_db, shape );

    BROADCAST_TO_SUBCASE( case3, x_hs_fb, shape );
    BROADCAST_TO_SUBCASE( case3, x_hs_hb, shape );
    BROADCAST_TO_SUBCASE( case3, x_hs_db, shape );

    BROADCAST_TO_SUBCASE( case3, x_ds_fb, shape );
    BROADCAST_TO_SUBCASE( case3, x_ds_hb, shape );
    BROADCAST_TO_SUBCASE( case3, x_ds_db, shape );
}