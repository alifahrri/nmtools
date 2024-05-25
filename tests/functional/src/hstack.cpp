#if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
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
#endif

#include "nmtools/array/functional/hstack.hpp"
#include "nmtools/testing/data/array/hstack.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace fn = nmtools::functional;

#define TESTING_NAMESPACE hstack

#define FUNCTIONAL_SUBCASE(subcase_name, function, ...) \
SUBCASE(#subcase_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS( TESTING_NAMESPACE, subcase_name ); \
    using namespace args; \
    auto result = function (__VA_ARGS__); \
    NMTOOLS_REQUIRE_EQUAL( nm::shape(result), nm::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define BINARY_FUNCTIONAL_SUBCASE(subcase_name, function, a, b) \
SUBCASE(#subcase_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS( TESTING_NAMESPACE, subcase_name ); \
    using namespace args; \
    auto result = function (a) (b); \
    NMTOOLS_REQUIRE_EQUAL( nm::shape(result), nm::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("hstack(case1)" * doctest::test_suite("functional::hstack"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    FUNCTIONAL_SUBCASE( case1, fn::hstack, a, b );
    FUNCTIONAL_SUBCASE( case1, fn::hstack, a_a, b_a );
    FUNCTIONAL_SUBCASE( case1, fn::hstack, a_f, b_f );
    FUNCTIONAL_SUBCASE( case1, fn::hstack, a_d, b_d );
    FUNCTIONAL_SUBCASE( case1, fn::hstack, a_h, b_h );
    #else
    FUNCTIONAL_SUBCASE( case1, fn::hstack, a_cs_fb, b_cs_fb );
    FUNCTIONAL_SUBCASE( case1, fn::hstack, a_cs_hb, b_cs_hb );
    FUNCTIONAL_SUBCASE( case1, fn::hstack, a_cs_db, b_cs_db );

    FUNCTIONAL_SUBCASE( case1, fn::hstack, a_fs_fb, b_fs_fb );
    FUNCTIONAL_SUBCASE( case1, fn::hstack, a_fs_hb, b_fs_hb );
    FUNCTIONAL_SUBCASE( case1, fn::hstack, a_fs_db, b_fs_db );

    FUNCTIONAL_SUBCASE( case1, fn::hstack, a_hs_fb, b_hs_fb );
    FUNCTIONAL_SUBCASE( case1, fn::hstack, a_hs_hb, b_hs_hb );
    FUNCTIONAL_SUBCASE( case1, fn::hstack, a_hs_db, b_hs_db );

    FUNCTIONAL_SUBCASE( case1, fn::hstack, a_ds_fb, b_ds_fb );
    FUNCTIONAL_SUBCASE( case1, fn::hstack, a_ds_hb, b_ds_hb );
    FUNCTIONAL_SUBCASE( case1, fn::hstack, a_ds_db, b_ds_db );

    FUNCTIONAL_SUBCASE( case1, fn::hstack, a_ls_fb, b_ls_fb );
    FUNCTIONAL_SUBCASE( case1, fn::hstack, a_ls_hb, b_ls_hb );
    FUNCTIONAL_SUBCASE( case1, fn::hstack, a_ls_db, b_ls_db );
    #endif
}

TEST_CASE("hstack(case2)" * doctest::test_suite("functional::hstack"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    FUNCTIONAL_SUBCASE( case2, fn::hstack, a, b );
    FUNCTIONAL_SUBCASE( case2, fn::hstack, a_a, b_a );
    FUNCTIONAL_SUBCASE( case2, fn::hstack, a_f, b_f );
    FUNCTIONAL_SUBCASE( case2, fn::hstack, a_d, b_d );
    FUNCTIONAL_SUBCASE( case2, fn::hstack, a_h, b_h );
    #else
    FUNCTIONAL_SUBCASE( case2, fn::hstack, a_cs_fb, b_cs_fb );
    FUNCTIONAL_SUBCASE( case2, fn::hstack, a_cs_hb, b_cs_hb );
    FUNCTIONAL_SUBCASE( case2, fn::hstack, a_cs_db, b_cs_db );

    FUNCTIONAL_SUBCASE( case2, fn::hstack, a_fs_fb, b_fs_fb );
    FUNCTIONAL_SUBCASE( case2, fn::hstack, a_fs_hb, b_fs_hb );
    FUNCTIONAL_SUBCASE( case2, fn::hstack, a_fs_db, b_fs_db );

    FUNCTIONAL_SUBCASE( case2, fn::hstack, a_hs_fb, b_hs_fb );
    FUNCTIONAL_SUBCASE( case2, fn::hstack, a_hs_hb, b_hs_hb );
    FUNCTIONAL_SUBCASE( case2, fn::hstack, a_hs_db, b_hs_db );

    FUNCTIONAL_SUBCASE( case2, fn::hstack, a_ds_fb, b_ds_fb );
    FUNCTIONAL_SUBCASE( case2, fn::hstack, a_ds_hb, b_ds_hb );
    FUNCTIONAL_SUBCASE( case2, fn::hstack, a_ds_db, b_ds_db );

    FUNCTIONAL_SUBCASE( case2, fn::hstack, a_ls_fb, b_ls_fb );
    FUNCTIONAL_SUBCASE( case2, fn::hstack, a_ls_hb, b_ls_hb );
    FUNCTIONAL_SUBCASE( case2, fn::hstack, a_ls_db, b_ls_db );
    #endif
}

TEST_CASE("hstack(case3)" * doctest::test_suite("functional::hstack"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    FUNCTIONAL_SUBCASE( case3, fn::hstack, a, b );
    FUNCTIONAL_SUBCASE( case3, fn::hstack, a_a, b_a );
    FUNCTIONAL_SUBCASE( case3, fn::hstack, a_f, b_f );
    FUNCTIONAL_SUBCASE( case3, fn::hstack, a_d, b_d );
    FUNCTIONAL_SUBCASE( case3, fn::hstack, a_h, b_h );
    #else
    FUNCTIONAL_SUBCASE( case3, fn::hstack, a_cs_fb, b_cs_fb );
    FUNCTIONAL_SUBCASE( case3, fn::hstack, a_cs_hb, b_cs_hb );
    FUNCTIONAL_SUBCASE( case3, fn::hstack, a_cs_db, b_cs_db );

    FUNCTIONAL_SUBCASE( case3, fn::hstack, a_fs_fb, b_fs_fb );
    FUNCTIONAL_SUBCASE( case3, fn::hstack, a_fs_hb, b_fs_hb );
    FUNCTIONAL_SUBCASE( case3, fn::hstack, a_fs_db, b_fs_db );

    FUNCTIONAL_SUBCASE( case3, fn::hstack, a_hs_fb, b_hs_fb );
    FUNCTIONAL_SUBCASE( case3, fn::hstack, a_hs_hb, b_hs_hb );
    FUNCTIONAL_SUBCASE( case3, fn::hstack, a_hs_db, b_hs_db );

    FUNCTIONAL_SUBCASE( case3, fn::hstack, a_ds_fb, b_ds_fb );
    FUNCTIONAL_SUBCASE( case3, fn::hstack, a_ds_hb, b_ds_hb );
    FUNCTIONAL_SUBCASE( case3, fn::hstack, a_ds_db, b_ds_db );

    // TODO: fix
    #if 0
    FUNCTIONAL_SUBCASE( case3, fn::hstack, a_ls_fb, b_ls_fb );
    FUNCTIONAL_SUBCASE( case3, fn::hstack, a_ls_hb, b_ls_hb );
    FUNCTIONAL_SUBCASE( case3, fn::hstack, a_ls_db, b_ls_db );
    #endif
    #endif
}

TEST_CASE("hstack(case1)" * doctest::test_suite("functional::hstack"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    BINARY_FUNCTIONAL_SUBCASE( case1, fn::hstack, a, b );
    BINARY_FUNCTIONAL_SUBCASE( case1, fn::hstack, a_a, b_a );
    BINARY_FUNCTIONAL_SUBCASE( case1, fn::hstack, a_f, b_f );
    BINARY_FUNCTIONAL_SUBCASE( case1, fn::hstack, a_d, b_d );
    BINARY_FUNCTIONAL_SUBCASE( case1, fn::hstack, a_h, b_h );
    #else
    BINARY_FUNCTIONAL_SUBCASE( case1, fn::hstack, a_cs_fb, b_cs_fb );
    BINARY_FUNCTIONAL_SUBCASE( case1, fn::hstack, a_cs_hb, b_cs_hb );
    BINARY_FUNCTIONAL_SUBCASE( case1, fn::hstack, a_cs_db, b_cs_db );

    BINARY_FUNCTIONAL_SUBCASE( case1, fn::hstack, a_fs_fb, b_fs_fb );
    BINARY_FUNCTIONAL_SUBCASE( case1, fn::hstack, a_fs_hb, b_fs_hb );
    BINARY_FUNCTIONAL_SUBCASE( case1, fn::hstack, a_fs_db, b_fs_db );

    BINARY_FUNCTIONAL_SUBCASE( case1, fn::hstack, a_hs_fb, b_hs_fb );
    BINARY_FUNCTIONAL_SUBCASE( case1, fn::hstack, a_hs_hb, b_hs_hb );
    BINARY_FUNCTIONAL_SUBCASE( case1, fn::hstack, a_hs_db, b_hs_db );

    BINARY_FUNCTIONAL_SUBCASE( case1, fn::hstack, a_ds_fb, b_ds_fb );
    BINARY_FUNCTIONAL_SUBCASE( case1, fn::hstack, a_ds_hb, b_ds_hb );
    BINARY_FUNCTIONAL_SUBCASE( case1, fn::hstack, a_ds_db, b_ds_db );

    BINARY_FUNCTIONAL_SUBCASE( case1, fn::hstack, a_ls_fb, b_ls_fb );
    BINARY_FUNCTIONAL_SUBCASE( case1, fn::hstack, a_ls_hb, b_ls_hb );
    BINARY_FUNCTIONAL_SUBCASE( case1, fn::hstack, a_ls_db, b_ls_db );
    #endif
}

TEST_CASE("hstack(case2)" * doctest::test_suite("functional::hstack"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    BINARY_FUNCTIONAL_SUBCASE( case2, fn::hstack, a, b );
    BINARY_FUNCTIONAL_SUBCASE( case2, fn::hstack, a_a, b_a );
    BINARY_FUNCTIONAL_SUBCASE( case2, fn::hstack, a_f, b_f );
    BINARY_FUNCTIONAL_SUBCASE( case2, fn::hstack, a_d, b_d );
    BINARY_FUNCTIONAL_SUBCASE( case2, fn::hstack, a_h, b_h );
    #else
    BINARY_FUNCTIONAL_SUBCASE( case2, fn::hstack, a_cs_fb, b_cs_fb );
    BINARY_FUNCTIONAL_SUBCASE( case2, fn::hstack, a_cs_hb, b_cs_hb );
    BINARY_FUNCTIONAL_SUBCASE( case2, fn::hstack, a_cs_db, b_cs_db );

    BINARY_FUNCTIONAL_SUBCASE( case2, fn::hstack, a_fs_fb, b_fs_fb );
    BINARY_FUNCTIONAL_SUBCASE( case2, fn::hstack, a_fs_hb, b_fs_hb );
    BINARY_FUNCTIONAL_SUBCASE( case2, fn::hstack, a_fs_db, b_fs_db );

    BINARY_FUNCTIONAL_SUBCASE( case2, fn::hstack, a_hs_fb, b_hs_fb );
    BINARY_FUNCTIONAL_SUBCASE( case2, fn::hstack, a_hs_hb, b_hs_hb );
    BINARY_FUNCTIONAL_SUBCASE( case2, fn::hstack, a_hs_db, b_hs_db );

    BINARY_FUNCTIONAL_SUBCASE( case2, fn::hstack, a_ds_fb, b_ds_fb );
    BINARY_FUNCTIONAL_SUBCASE( case2, fn::hstack, a_ds_hb, b_ds_hb );
    BINARY_FUNCTIONAL_SUBCASE( case2, fn::hstack, a_ds_db, b_ds_db );

    BINARY_FUNCTIONAL_SUBCASE( case2, fn::hstack, a_ls_fb, b_ls_fb );
    BINARY_FUNCTIONAL_SUBCASE( case2, fn::hstack, a_ls_hb, b_ls_hb );
    BINARY_FUNCTIONAL_SUBCASE( case2, fn::hstack, a_ls_db, b_ls_db );
    #endif
}

TEST_CASE("hstack(case3)" * doctest::test_suite("functional::hstack"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    BINARY_FUNCTIONAL_SUBCASE( case3, fn::hstack, a, b );
    BINARY_FUNCTIONAL_SUBCASE( case3, fn::hstack, a_a, b_a );
    BINARY_FUNCTIONAL_SUBCASE( case3, fn::hstack, a_f, b_f );
    BINARY_FUNCTIONAL_SUBCASE( case3, fn::hstack, a_d, b_d );
    BINARY_FUNCTIONAL_SUBCASE( case3, fn::hstack, a_h, b_h );
    #else
    BINARY_FUNCTIONAL_SUBCASE( case3, fn::hstack, a_cs_fb, b_cs_fb );
    BINARY_FUNCTIONAL_SUBCASE( case3, fn::hstack, a_cs_hb, b_cs_hb );
    BINARY_FUNCTIONAL_SUBCASE( case3, fn::hstack, a_cs_db, b_cs_db );

    BINARY_FUNCTIONAL_SUBCASE( case3, fn::hstack, a_fs_fb, b_fs_fb );
    BINARY_FUNCTIONAL_SUBCASE( case3, fn::hstack, a_fs_hb, b_fs_hb );
    BINARY_FUNCTIONAL_SUBCASE( case3, fn::hstack, a_fs_db, b_fs_db );

    BINARY_FUNCTIONAL_SUBCASE( case3, fn::hstack, a_hs_fb, b_hs_fb );
    BINARY_FUNCTIONAL_SUBCASE( case3, fn::hstack, a_hs_hb, b_hs_hb );
    BINARY_FUNCTIONAL_SUBCASE( case3, fn::hstack, a_hs_db, b_hs_db );

    BINARY_FUNCTIONAL_SUBCASE( case3, fn::hstack, a_ds_fb, b_ds_fb );
    BINARY_FUNCTIONAL_SUBCASE( case3, fn::hstack, a_ds_hb, b_ds_hb );
    BINARY_FUNCTIONAL_SUBCASE( case3, fn::hstack, a_ds_db, b_ds_db );

    // TODO: fix
    #if 0
    BINARY_FUNCTIONAL_SUBCASE( case3, fn::hstack, a_ls_fb, b_ls_fb );
    BINARY_FUNCTIONAL_SUBCASE( case3, fn::hstack, a_ls_hb, b_ls_hb );
    BINARY_FUNCTIONAL_SUBCASE( case3, fn::hstack, a_ls_db, b_ls_db );
    #endif
    #endif
}