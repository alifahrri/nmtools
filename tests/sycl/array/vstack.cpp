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

#include "nmtools/array/array/vstack.hpp"
#include "nmtools/testing/data/array/vstack.hpp"
#include "nmtools/array/eval/sycl.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;

#define VSTACK_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( vstack, case_name ) \
    using namespace args; \
    auto result = nmtools::array::vstack(__VA_ARGS__,na::sycl::default_context()); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

// TODO: fix runtime error: 
// /workspaces/nmtools/tests/sycl/array/vstack.cpp:37:
// TEST SUITE: array::vstack
// TEST CASE:  vstack(case1)
//   case1

// /workspaces/nmtools/tests/sycl/array/vstack.cpp:37: FATAL ERROR: test case CRASHED: SIGFPE - Floating point error signal

// ===============================================================================
// /workspaces/nmtools/tests/sycl/array/vstack.cpp:37:
// TEST SUITE: array::vstack
// TEST CASE:  vstack(case1)

// DEEPEST SUBCASE STACK REACHED (DIFFERENT FROM THE CURRENT ONE):
//   case1

// ===============================================================================
// [doctest] test cases: 1 | 0 passed | 1 failed | 463 skipped
// [doctest] assertions: 0 | 0 passed | 0 failed |
// [doctest] Status: FAILURE!
// [1]    14224 floating point exception (core dumped)  ./tests/sycl/numeric-tests-sycl-doctest -tc="vstack(case1)"
TEST_CASE("vstack(case1)" * doctest::test_suite("array::vstack") * doctest::skip())
{
    // TODO: support the following types for sycl
    // VSTACK_SUBCASE( case1, a, b );
    // VSTACK_SUBCASE( case1, a_a, b_a );
    // VSTACK_SUBCASE( case1, a_f, b_f );
    // VSTACK_SUBCASE( case1, a_d, b_d );
    VSTACK_SUBCASE( case1, a_h, b_h );

    VSTACK_SUBCASE( case1, a_cs_fb, b_cs_fb );
    VSTACK_SUBCASE( case1, a_cs_hb, b_cs_hb );
    VSTACK_SUBCASE( case1, a_cs_db, b_cs_db );

    VSTACK_SUBCASE( case1, a_fs_fb, b_fs_fb );
    VSTACK_SUBCASE( case1, a_fs_hb, b_fs_hb );
    VSTACK_SUBCASE( case1, a_fs_db, b_fs_db );

    VSTACK_SUBCASE( case1, a_hs_fb, b_hs_fb );
    VSTACK_SUBCASE( case1, a_hs_hb, b_hs_hb );
    VSTACK_SUBCASE( case1, a_hs_db, b_hs_db );

    VSTACK_SUBCASE( case1, a_ds_fb, b_ds_fb );
    VSTACK_SUBCASE( case1, a_ds_hb, b_ds_hb );
    VSTACK_SUBCASE( case1, a_ds_db, b_ds_db );

    VSTACK_SUBCASE( case1, a_ls_fb, b_ls_fb );
    VSTACK_SUBCASE( case1, a_ls_hb, b_ls_hb );
    VSTACK_SUBCASE( case1, a_ls_db, b_ls_db );

}

TEST_CASE("vstack(case2)" * doctest::test_suite("array::vstack"))
{
    // TODO: support the following types for sycl
    // VSTACK_SUBCASE( case2, a, b );
    // VSTACK_SUBCASE( case2, a_a, b_a );
    // VSTACK_SUBCASE( case2, a_f, b_f );
    // VSTACK_SUBCASE( case2, a_d, b_d );
    VSTACK_SUBCASE( case2, a_h, b_h );

    VSTACK_SUBCASE( case2, a_cs_fb, b_cs_fb );
    VSTACK_SUBCASE( case2, a_cs_hb, b_cs_hb );
    VSTACK_SUBCASE( case2, a_cs_db, b_cs_db );

    VSTACK_SUBCASE( case2, a_fs_fb, b_fs_fb );
    VSTACK_SUBCASE( case2, a_fs_hb, b_fs_hb );
    VSTACK_SUBCASE( case2, a_fs_db, b_fs_db );

    VSTACK_SUBCASE( case2, a_hs_fb, b_hs_fb );
    VSTACK_SUBCASE( case2, a_hs_hb, b_hs_hb );
    VSTACK_SUBCASE( case2, a_hs_db, b_hs_db );

    VSTACK_SUBCASE( case2, a_ds_fb, b_ds_fb );
    VSTACK_SUBCASE( case2, a_ds_hb, b_ds_hb );
    VSTACK_SUBCASE( case2, a_ds_db, b_ds_db );

    VSTACK_SUBCASE( case2, a_ls_fb, b_ls_fb );
    VSTACK_SUBCASE( case2, a_ls_hb, b_ls_hb );
    VSTACK_SUBCASE( case2, a_ls_db, b_ls_db );

}

TEST_CASE("vstack(case3)" * doctest::test_suite("array::vstack"))
{
    // TODO: support the following types for sycl
    // VSTACK_SUBCASE( case3, a, b );
    // VSTACK_SUBCASE( case3, a_a, b_a );
    // VSTACK_SUBCASE( case3, a_f, b_f );
    // VSTACK_SUBCASE( case3, a_d, b_d );
    VSTACK_SUBCASE( case3, a_h, b_h );

    VSTACK_SUBCASE( case3, a_cs_fb, b_cs_fb );
    VSTACK_SUBCASE( case3, a_cs_hb, b_cs_hb );
    VSTACK_SUBCASE( case3, a_cs_db, b_cs_db );

    VSTACK_SUBCASE( case3, a_fs_fb, b_fs_fb );
    VSTACK_SUBCASE( case3, a_fs_hb, b_fs_hb );
    VSTACK_SUBCASE( case3, a_fs_db, b_fs_db );

    VSTACK_SUBCASE( case3, a_hs_fb, b_hs_fb );
    VSTACK_SUBCASE( case3, a_hs_hb, b_hs_hb );
    VSTACK_SUBCASE( case3, a_hs_db, b_hs_db );

    VSTACK_SUBCASE( case3, a_ds_fb, b_ds_fb );
    VSTACK_SUBCASE( case3, a_ds_hb, b_ds_hb );
    VSTACK_SUBCASE( case3, a_ds_db, b_ds_db );

    VSTACK_SUBCASE( case3, a_ls_fb, b_ls_fb );
    VSTACK_SUBCASE( case3, a_ls_hb, b_ls_hb );
    VSTACK_SUBCASE( case3, a_ls_db, b_ls_db );

}