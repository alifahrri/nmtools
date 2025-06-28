#if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
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
#endif

#include "nmtools/array/stack.hpp"
#include "nmtools/testing/data/array/stack.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace meta = nm::meta;

#define STACK_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( stack, case_name ) \
    using namespace args; \
    auto result = nmtools::stack(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("stack(case1)" * doctest::test_suite("array::stack"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    STACK_SUBCASE( case1, a, b );
    STACK_SUBCASE( case1, a_a, b_a );
    STACK_SUBCASE( case1, a_f, b_f );
    STACK_SUBCASE( case1, a_d, b_d );
    STACK_SUBCASE( case1, a_h, b_h );
    #else
    STACK_SUBCASE( case1, a_cs_fb, b_cs_fb );
    STACK_SUBCASE( case1, a_cs_hb, b_cs_hb );
    STACK_SUBCASE( case1, a_cs_db, b_cs_db );

    STACK_SUBCASE( case1, a_fs_fb, b_fs_fb );
    STACK_SUBCASE( case1, a_fs_hb, b_fs_hb );
    STACK_SUBCASE( case1, a_fs_db, b_fs_db );

    STACK_SUBCASE( case1, a_hs_fb, b_hs_fb );
    STACK_SUBCASE( case1, a_hs_hb, b_hs_hb );
    STACK_SUBCASE( case1, a_hs_db, b_hs_db );

    STACK_SUBCASE( case1, a_ds_fb, b_ds_fb );
    STACK_SUBCASE( case1, a_ds_hb, b_ds_hb );
    STACK_SUBCASE( case1, a_ds_db, b_ds_db );

    STACK_SUBCASE( case1, a_ls_fb, b_ls_fb );
    STACK_SUBCASE( case1, a_ls_hb, b_ls_hb );
    STACK_SUBCASE( case1, a_ls_db, b_ls_db );
    #endif
}

TEST_CASE("stack(case2)" * doctest::test_suite("array::stack"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    STACK_SUBCASE( case2, a, b, axis );
    STACK_SUBCASE( case2, a_a, b_a, axis );
    STACK_SUBCASE( case2, a_f, b_f, axis );
    STACK_SUBCASE( case2, a_d, b_d, axis );
    STACK_SUBCASE( case2, a_h, b_h, axis );
    #else
    STACK_SUBCASE( case2, a_cs_fb, b_cs_fb, axis );
    STACK_SUBCASE( case2, a_cs_hb, b_cs_hb, axis );
    STACK_SUBCASE( case2, a_cs_db, b_cs_db, axis );

    STACK_SUBCASE( case2, a_fs_fb, b_fs_fb, axis );
    STACK_SUBCASE( case2, a_fs_hb, b_fs_hb, axis );
    STACK_SUBCASE( case2, a_fs_db, b_fs_db, axis );

    STACK_SUBCASE( case2, a_hs_fb, b_hs_fb, axis );
    STACK_SUBCASE( case2, a_hs_hb, b_hs_hb, axis );
    STACK_SUBCASE( case2, a_hs_db, b_hs_db, axis );

    STACK_SUBCASE( case2, a_ds_fb, b_ds_fb, axis );
    STACK_SUBCASE( case2, a_ds_hb, b_ds_hb, axis );
    STACK_SUBCASE( case2, a_ds_db, b_ds_db, axis );

    STACK_SUBCASE( case2, a_ls_fb, b_ls_fb, axis );
    STACK_SUBCASE( case2, a_ls_hb, b_ls_hb, axis );
    STACK_SUBCASE( case2, a_ls_db, b_ls_db, axis );
    #endif
}

TEST_CASE("stack(case3)" * doctest::test_suite("array::stack"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    STACK_SUBCASE( case3, a, b );
    STACK_SUBCASE( case3, a_a, b_a );
    STACK_SUBCASE( case3, a_f, b_f );
    STACK_SUBCASE( case3, a_d, b_d );
    STACK_SUBCASE( case3, a_h, b_h );
    #else
    STACK_SUBCASE( case3, a_cs_fb, b_cs_fb );
    STACK_SUBCASE( case3, a_cs_hb, b_cs_hb );
    STACK_SUBCASE( case3, a_cs_db, b_cs_db );

    STACK_SUBCASE( case3, a_fs_fb, b_fs_fb );
    STACK_SUBCASE( case3, a_fs_hb, b_fs_hb );
    STACK_SUBCASE( case3, a_fs_db, b_fs_db );

    STACK_SUBCASE( case3, a_hs_fb, b_hs_fb );
    STACK_SUBCASE( case3, a_hs_hb, b_hs_hb );
    STACK_SUBCASE( case3, a_hs_db, b_hs_db );

    STACK_SUBCASE( case3, a_ds_fb, b_ds_fb );
    STACK_SUBCASE( case3, a_ds_hb, b_ds_hb );
    STACK_SUBCASE( case3, a_ds_db, b_ds_db );

    STACK_SUBCASE( case3, a_ls_fb, b_ls_fb );
    STACK_SUBCASE( case3, a_ls_hb, b_ls_hb );
    STACK_SUBCASE( case3, a_ls_db, b_ls_db );
    #endif
}

TEST_CASE("stack(case4)" * doctest::test_suite("array::stack"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    STACK_SUBCASE( case4, a, b, axis );
    STACK_SUBCASE( case4, a_a, b_a, axis );
    STACK_SUBCASE( case4, a_f, b_f, axis );
    STACK_SUBCASE( case4, a_d, b_d, axis );
    STACK_SUBCASE( case4, a_h, b_h, axis );
    #else
    STACK_SUBCASE( case4, a_cs_fb, b_cs_fb, axis );
    STACK_SUBCASE( case4, a_cs_hb, b_cs_hb, axis );
    STACK_SUBCASE( case4, a_cs_db, b_cs_db, axis );

    STACK_SUBCASE( case4, a_fs_fb, b_fs_fb, axis );
    STACK_SUBCASE( case4, a_fs_hb, b_fs_hb, axis );
    STACK_SUBCASE( case4, a_fs_db, b_fs_db, axis );

    STACK_SUBCASE( case4, a_hs_fb, b_hs_fb, axis );
    STACK_SUBCASE( case4, a_hs_hb, b_hs_hb, axis );
    STACK_SUBCASE( case4, a_hs_db, b_hs_db, axis );

    STACK_SUBCASE( case4, a_ds_fb, b_ds_fb, axis );
    STACK_SUBCASE( case4, a_ds_hb, b_ds_hb, axis );
    STACK_SUBCASE( case4, a_ds_db, b_ds_db, axis );

    STACK_SUBCASE( case4, a_ls_fb, b_ls_fb, axis );
    STACK_SUBCASE( case4, a_ls_hb, b_ls_hb, axis );
    STACK_SUBCASE( case4, a_ls_db, b_ls_db, axis );
    #endif
}

TEST_CASE("stack(case5)" * doctest::test_suite("array::stack"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    STACK_SUBCASE( case5, a, b, axis );
    STACK_SUBCASE( case5, a_a, b_a, axis );
    STACK_SUBCASE( case5, a_f, b_f, axis );
    STACK_SUBCASE( case5, a_d, b_d, axis );
    STACK_SUBCASE( case5, a_h, b_h, axis );
    #else
    STACK_SUBCASE( case5, a_cs_fb, b_cs_fb, axis );
    STACK_SUBCASE( case5, a_cs_hb, b_cs_hb, axis );
    STACK_SUBCASE( case5, a_cs_db, b_cs_db, axis );

    STACK_SUBCASE( case5, a_fs_fb, b_fs_fb, axis );
    STACK_SUBCASE( case5, a_fs_hb, b_fs_hb, axis );
    STACK_SUBCASE( case5, a_fs_db, b_fs_db, axis );

    STACK_SUBCASE( case5, a_hs_fb, b_hs_fb, axis );
    STACK_SUBCASE( case5, a_hs_hb, b_hs_hb, axis );
    STACK_SUBCASE( case5, a_hs_db, b_hs_db, axis );

    STACK_SUBCASE( case5, a_ds_fb, b_ds_fb, axis );
    STACK_SUBCASE( case5, a_ds_hb, b_ds_hb, axis );
    STACK_SUBCASE( case5, a_ds_db, b_ds_db, axis );

    STACK_SUBCASE( case5, a_ls_fb, b_ls_fb, axis );
    STACK_SUBCASE( case5, a_ls_hb, b_ls_hb, axis );
    STACK_SUBCASE( case5, a_ls_db, b_ls_db, axis );
    #endif
}