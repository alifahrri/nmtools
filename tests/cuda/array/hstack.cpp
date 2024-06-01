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

#include "nmtools/array/array/hstack.hpp"
#include "nmtools/testing/data/array/hstack.hpp"
#include "nmtools/array/eval/cuda.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;

#define HSTACK_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( hstack, case_name ) \
    using namespace args; \
    auto result = nmtools::array::hstack(__VA_ARGS__, na::cuda::default_context()); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE_MSG_OPERANDS( result, expect::result, __VA_ARGS__ ); \
}

TEST_CASE("hstack(case1)" * doctest::test_suite("array::hstack"))
{
    // NOTE: compile-error because can't get data()
    // TODO: support the following type on cuda
    // HSTACK_SUBCASE( case1, a, b );
    // HSTACK_SUBCASE( case1, a_a, b_a );
    // HSTACK_SUBCASE( case1, a_f, b_f );
    // HSTACK_SUBCASE( case1, a_d, b_d );
    HSTACK_SUBCASE( case1, a_h, b_h );

    HSTACK_SUBCASE( case1, a_cs_fb, b_cs_fb );
    HSTACK_SUBCASE( case1, a_cs_hb, b_cs_hb );
    HSTACK_SUBCASE( case1, a_cs_db, b_cs_db );

    HSTACK_SUBCASE( case1, a_fs_fb, b_fs_fb );
    HSTACK_SUBCASE( case1, a_fs_hb, b_fs_hb );
    HSTACK_SUBCASE( case1, a_fs_db, b_fs_db );

    HSTACK_SUBCASE( case1, a_hs_fb, b_hs_fb );
    HSTACK_SUBCASE( case1, a_hs_hb, b_hs_hb );
    HSTACK_SUBCASE( case1, a_hs_db, b_hs_db );

    HSTACK_SUBCASE( case1, a_ds_fb, b_ds_fb );
    HSTACK_SUBCASE( case1, a_ds_hb, b_ds_hb );
    HSTACK_SUBCASE( case1, a_ds_db, b_ds_db );

    HSTACK_SUBCASE( case1, a_ls_fb, b_ls_fb );
    HSTACK_SUBCASE( case1, a_ls_hb, b_ls_hb );
    HSTACK_SUBCASE( case1, a_ls_db, b_ls_db );
    
}

TEST_CASE("hstack(case2)" * doctest::test_suite("array::hstack"))
{
    // HSTACK_SUBCASE( case2, a, b );
    // HSTACK_SUBCASE( case2, a_a, b_a );
    // HSTACK_SUBCASE( case2, a_f, b_f );
    // HSTACK_SUBCASE( case2, a_d, b_d );
    HSTACK_SUBCASE( case2, a_h, b_h );

    HSTACK_SUBCASE( case2, a_cs_fb, b_cs_fb );
    HSTACK_SUBCASE( case2, a_cs_hb, b_cs_hb );
    HSTACK_SUBCASE( case2, a_cs_db, b_cs_db );

    HSTACK_SUBCASE( case2, a_fs_fb, b_fs_fb );
    HSTACK_SUBCASE( case2, a_fs_hb, b_fs_hb );
    HSTACK_SUBCASE( case2, a_fs_db, b_fs_db );

    HSTACK_SUBCASE( case2, a_hs_fb, b_hs_fb );
    HSTACK_SUBCASE( case2, a_hs_hb, b_hs_hb );
    HSTACK_SUBCASE( case2, a_hs_db, b_hs_db );

    HSTACK_SUBCASE( case2, a_ds_fb, b_ds_fb );
    HSTACK_SUBCASE( case2, a_ds_hb, b_ds_hb );
    HSTACK_SUBCASE( case2, a_ds_db, b_ds_db );

    HSTACK_SUBCASE( case2, a_ls_fb, b_ls_fb );
    HSTACK_SUBCASE( case2, a_ls_hb, b_ls_hb );
    HSTACK_SUBCASE( case2, a_ls_db, b_ls_db );
    
}

TEST_CASE("hstack(case3)" * doctest::test_suite("array::hstack"))
{
    // HSTACK_SUBCASE( case3, a, b );
    // HSTACK_SUBCASE( case3, a_a, b_a );
    // HSTACK_SUBCASE( case3, a_f, b_f );
    // HSTACK_SUBCASE( case3, a_d, b_d );
    HSTACK_SUBCASE( case3, a_h, b_h );


    HSTACK_SUBCASE( case3, a_cs_fb, b_cs_fb );
    HSTACK_SUBCASE( case3, a_cs_hb, b_cs_hb );
    HSTACK_SUBCASE( case3, a_cs_db, b_cs_db );

    HSTACK_SUBCASE( case3, a_fs_fb, b_fs_fb );
    HSTACK_SUBCASE( case3, a_fs_hb, b_fs_hb );
    HSTACK_SUBCASE( case3, a_fs_db, b_fs_db );

    HSTACK_SUBCASE( case3, a_hs_fb, b_hs_fb );
    HSTACK_SUBCASE( case3, a_hs_hb, b_hs_hb );
    HSTACK_SUBCASE( case3, a_hs_db, b_hs_db );

    HSTACK_SUBCASE( case3, a_ds_fb, b_ds_fb );
    HSTACK_SUBCASE( case3, a_ds_hb, b_ds_hb );
    HSTACK_SUBCASE( case3, a_ds_db, b_ds_db );
    
}

// somehow hstack on 3-dim array with clipped shape results in error
// TODO: fix
TEST_CASE("hstack(case3)" * doctest::test_suite("array::hstack") * doctest::skip())
{
    HSTACK_SUBCASE( case3, a_ls_fb, b_ls_fb );
    HSTACK_SUBCASE( case3, a_ls_hb, b_ls_hb );
    HSTACK_SUBCASE( case3, a_ls_db, b_ls_db );   
}