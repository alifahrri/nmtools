#if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
#define NMTOOLS_CONSTEXPR_CAST_ARRAYS_EXTRA(name) \
constexpr inline auto name##_cs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_fb); \
constexpr inline auto name##_cs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_hb); \
constexpr inline auto name##_fs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_fs_fb); \
constexpr inline auto name##_fs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_fs_hb); \
constexpr inline auto name##_hs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_hs_fb); \
constexpr inline auto name##_hs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_hs_hb); \
constexpr inline auto name##_ls_fb = nmtools::cast(name, nmtools::array::kind::ndarray_ls_fb); \
constexpr inline auto name##_ls_hb = nmtools::cast(name, nmtools::array::kind::ndarray_ls_hb);
#endif

#include "nmtools/array/array/atleast_3d.hpp"
#include "nmtools/testing/data/constexpr/atleast_3d.hpp"
#include "nmtools/testing/doctest.hpp"

#define CONSTEXPR_ATLEAST_3D_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, constexpr_atleast_3d, case_name); \
    using namespace args; \
    constexpr auto result = nmtools::array::atleast_3d(__VA_ARGS__); \
    NMTOOLS_STATIC_ASSERT_EQUAL( nmtools::shape(result), expect::shape ); \
    NMTOOLS_STATIC_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("atleast_3d(case1)" * doctest::test_suite("array::constexpr_atleast_3d"))
{
    CONSTEXPR_ATLEAST_3D_SUBCASE( case1, a );
}

TEST_CASE("atleast_3d(case2)" * doctest::test_suite("array::constexpr_atleast_3d"))
{
    CONSTEXPR_ATLEAST_3D_SUBCASE( case2, a );
    CONSTEXPR_ATLEAST_3D_SUBCASE( case2, a_a );
    CONSTEXPR_ATLEAST_3D_SUBCASE( case2, a_f );
    CONSTEXPR_ATLEAST_3D_SUBCASE( case2, a_h );

    #if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_ATLEAST_3D_SUBCASE( case2, a_cs_fb );
    CONSTEXPR_ATLEAST_3D_SUBCASE( case2, a_cs_hb );

    CONSTEXPR_ATLEAST_3D_SUBCASE( case2, a_fs_fb );
    CONSTEXPR_ATLEAST_3D_SUBCASE( case2, a_fs_hb );

    CONSTEXPR_ATLEAST_3D_SUBCASE( case2, a_hs_fb );
    CONSTEXPR_ATLEAST_3D_SUBCASE( case2, a_hs_hb );

    CONSTEXPR_ATLEAST_3D_SUBCASE( case2, a_ls_fb );
    CONSTEXPR_ATLEAST_3D_SUBCASE( case2, a_ls_hb );
    #endif
}

TEST_CASE("atleast_3d(case3)" * doctest::test_suite("array::constexpr_atleast_3d"))
{
    CONSTEXPR_ATLEAST_3D_SUBCASE( case3, a );
    CONSTEXPR_ATLEAST_3D_SUBCASE( case3, a_a );
    CONSTEXPR_ATLEAST_3D_SUBCASE( case3, a_f );
    CONSTEXPR_ATLEAST_3D_SUBCASE( case3, a_h );
   
    #if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_ATLEAST_3D_SUBCASE( case3, a_cs_fb );
    CONSTEXPR_ATLEAST_3D_SUBCASE( case3, a_cs_hb );

    CONSTEXPR_ATLEAST_3D_SUBCASE( case3, a_fs_fb );
    CONSTEXPR_ATLEAST_3D_SUBCASE( case3, a_fs_hb );

    CONSTEXPR_ATLEAST_3D_SUBCASE( case3, a_hs_fb );
    CONSTEXPR_ATLEAST_3D_SUBCASE( case3, a_hs_hb );

    CONSTEXPR_ATLEAST_3D_SUBCASE( case3, a_ls_fb );
    CONSTEXPR_ATLEAST_3D_SUBCASE( case3, a_ls_hb );
    #endif
}

TEST_CASE("atleast_3d(case4)" * doctest::test_suite("array::constexpr_atleast_3d"))
{
    CONSTEXPR_ATLEAST_3D_SUBCASE( case4, a );
    CONSTEXPR_ATLEAST_3D_SUBCASE( case4, a_a );
    CONSTEXPR_ATLEAST_3D_SUBCASE( case4, a_f );
    CONSTEXPR_ATLEAST_3D_SUBCASE( case4, a_h );

    #if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_ATLEAST_3D_SUBCASE( case4, a_cs_fb );
    CONSTEXPR_ATLEAST_3D_SUBCASE( case4, a_cs_hb );

    CONSTEXPR_ATLEAST_3D_SUBCASE( case4, a_fs_fb );
    CONSTEXPR_ATLEAST_3D_SUBCASE( case4, a_fs_hb );

    CONSTEXPR_ATLEAST_3D_SUBCASE( case4, a_hs_fb );
    CONSTEXPR_ATLEAST_3D_SUBCASE( case4, a_hs_hb );

    CONSTEXPR_ATLEAST_3D_SUBCASE( case4, a_ls_fb );
    CONSTEXPR_ATLEAST_3D_SUBCASE( case4, a_ls_hb );
    #endif
}

TEST_CASE("atleast_3d(case5)" * doctest::test_suite("array::constexpr_atleast_3d"))
{
    CONSTEXPR_ATLEAST_3D_SUBCASE( case5, a );
    CONSTEXPR_ATLEAST_3D_SUBCASE( case5, a_a );
    CONSTEXPR_ATLEAST_3D_SUBCASE( case5, a_f );
    CONSTEXPR_ATLEAST_3D_SUBCASE( case5, a_h );
   
    #if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_ATLEAST_3D_SUBCASE( case5, a_cs_fb );
    CONSTEXPR_ATLEAST_3D_SUBCASE( case5, a_cs_hb );

    CONSTEXPR_ATLEAST_3D_SUBCASE( case5, a_fs_fb );
    CONSTEXPR_ATLEAST_3D_SUBCASE( case5, a_fs_hb );

    CONSTEXPR_ATLEAST_3D_SUBCASE( case5, a_hs_fb );
    CONSTEXPR_ATLEAST_3D_SUBCASE( case5, a_hs_hb );

    CONSTEXPR_ATLEAST_3D_SUBCASE( case5, a_ls_fb );
    CONSTEXPR_ATLEAST_3D_SUBCASE( case5, a_ls_hb );
    #endif
}