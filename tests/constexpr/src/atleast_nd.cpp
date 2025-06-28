#if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
#define NMTOOLS_CONSTEXPR_CAST_ARRAYS_EXTRA(name) \
constexpr inline auto name##_cs_fb = nmtools::cast(name, nmtools::kind::ndarray_cs_fb); \
constexpr inline auto name##_cs_hb = nmtools::cast(name, nmtools::kind::ndarray_cs_hb); \
constexpr inline auto name##_fs_fb = nmtools::cast(name, nmtools::kind::ndarray_fs_fb); \
constexpr inline auto name##_fs_hb = nmtools::cast(name, nmtools::kind::ndarray_fs_hb); \
constexpr inline auto name##_hs_fb = nmtools::cast(name, nmtools::kind::ndarray_hs_fb); \
constexpr inline auto name##_hs_hb = nmtools::cast(name, nmtools::kind::ndarray_hs_hb); \
constexpr inline auto name##_ls_fb = nmtools::cast(name, nmtools::kind::ndarray_ls_fb); \
constexpr inline auto name##_ls_hb = nmtools::cast(name, nmtools::kind::ndarray_ls_hb);
#endif

#include "nmtools/array/atleast_nd.hpp"
#include "nmtools/testing/data/constexpr/atleast_nd.hpp"
#include "nmtools/testing/doctest.hpp"

#define CONSTEXPR_ATLEAST_ND_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, constexpr_atleast_nd, case_name); \
    using namespace args; \
    constexpr auto result = nmtools::atleast_nd(__VA_ARGS__); \
    NMTOOLS_STATIC_ASSERT_EQUAL( nmtools::shape(result), expect::shape ); \
    NMTOOLS_STATIC_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("atleast_nd(case1)" * doctest::test_suite("array::constexpr_atleast_nd"))
{
    CONSTEXPR_ATLEAST_ND_SUBCASE( case1, a, nd );
}

TEST_CASE("atleast_nd(case2)" * doctest::test_suite("array::constexpr_atleast_nd"))
{
    CONSTEXPR_ATLEAST_ND_SUBCASE( case2, a, nd );
    CONSTEXPR_ATLEAST_ND_SUBCASE( case2, a_a, nd );
    CONSTEXPR_ATLEAST_ND_SUBCASE( case2, a_f, nd );
    CONSTEXPR_ATLEAST_ND_SUBCASE( case2, a_h, nd );

    #if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_ATLEAST_ND_SUBCASE( case2, a_cs_fb, nd );
    CONSTEXPR_ATLEAST_ND_SUBCASE( case2, a_cs_hb, nd );

    CONSTEXPR_ATLEAST_ND_SUBCASE( case2, a_fs_fb, nd );
    CONSTEXPR_ATLEAST_ND_SUBCASE( case2, a_fs_hb, nd );

    CONSTEXPR_ATLEAST_ND_SUBCASE( case2, a_hs_fb, nd );
    CONSTEXPR_ATLEAST_ND_SUBCASE( case2, a_hs_hb, nd );

    CONSTEXPR_ATLEAST_ND_SUBCASE( case2, a_ls_fb, nd );
    CONSTEXPR_ATLEAST_ND_SUBCASE( case2, a_ls_hb, nd );
    #endif
}

TEST_CASE("atleast_nd(case3)" * doctest::test_suite("array::constexpr_atleast_nd"))
{
    CONSTEXPR_ATLEAST_ND_SUBCASE( case3, a, nd );
    CONSTEXPR_ATLEAST_ND_SUBCASE( case3, a_a, nd );
    CONSTEXPR_ATLEAST_ND_SUBCASE( case3, a_f, nd );
    CONSTEXPR_ATLEAST_ND_SUBCASE( case3, a_h, nd );
   
    #if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_ATLEAST_ND_SUBCASE( case3, a_cs_fb, nd );
    CONSTEXPR_ATLEAST_ND_SUBCASE( case3, a_cs_hb, nd );

    CONSTEXPR_ATLEAST_ND_SUBCASE( case3, a_fs_fb, nd );
    CONSTEXPR_ATLEAST_ND_SUBCASE( case3, a_fs_hb, nd );

    CONSTEXPR_ATLEAST_ND_SUBCASE( case3, a_hs_fb, nd );
    CONSTEXPR_ATLEAST_ND_SUBCASE( case3, a_hs_hb, nd );

    CONSTEXPR_ATLEAST_ND_SUBCASE( case3, a_ls_fb, nd );
    CONSTEXPR_ATLEAST_ND_SUBCASE( case3, a_ls_hb, nd );
    #endif
}

TEST_CASE("atleast_nd(case4)" * doctest::test_suite("array::constexpr_atleast_nd"))
{
    CONSTEXPR_ATLEAST_ND_SUBCASE( case4, a, nd );
    CONSTEXPR_ATLEAST_ND_SUBCASE( case4, a_a, nd );
    CONSTEXPR_ATLEAST_ND_SUBCASE( case4, a_f, nd );
    CONSTEXPR_ATLEAST_ND_SUBCASE( case4, a_h, nd );

    #if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_ATLEAST_ND_SUBCASE( case4, a_cs_fb, nd );
    CONSTEXPR_ATLEAST_ND_SUBCASE( case4, a_cs_hb, nd );

    CONSTEXPR_ATLEAST_ND_SUBCASE( case4, a_fs_fb, nd );
    CONSTEXPR_ATLEAST_ND_SUBCASE( case4, a_fs_hb, nd );

    CONSTEXPR_ATLEAST_ND_SUBCASE( case4, a_hs_fb, nd );
    CONSTEXPR_ATLEAST_ND_SUBCASE( case4, a_hs_hb, nd );

    CONSTEXPR_ATLEAST_ND_SUBCASE( case4, a_ls_fb, nd );
    CONSTEXPR_ATLEAST_ND_SUBCASE( case4, a_ls_hb, nd );
    #endif
}

TEST_CASE("atleast_nd(case5)" * doctest::test_suite("array::constexpr_atleast_nd"))
{
    CONSTEXPR_ATLEAST_ND_SUBCASE( case5, a, nd );
    CONSTEXPR_ATLEAST_ND_SUBCASE( case5, a_a, nd );
    CONSTEXPR_ATLEAST_ND_SUBCASE( case5, a_f, nd );
    CONSTEXPR_ATLEAST_ND_SUBCASE( case5, a_h, nd );
   
    #if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_ATLEAST_ND_SUBCASE( case5, a_cs_fb, nd );
    CONSTEXPR_ATLEAST_ND_SUBCASE( case5, a_cs_hb, nd );

    CONSTEXPR_ATLEAST_ND_SUBCASE( case5, a_fs_fb, nd );
    CONSTEXPR_ATLEAST_ND_SUBCASE( case5, a_fs_hb, nd );

    CONSTEXPR_ATLEAST_ND_SUBCASE( case5, a_hs_fb, nd );
    CONSTEXPR_ATLEAST_ND_SUBCASE( case5, a_hs_hb, nd );

    CONSTEXPR_ATLEAST_ND_SUBCASE( case5, a_ls_fb, nd );
    CONSTEXPR_ATLEAST_ND_SUBCASE( case5, a_ls_hb, nd );
    #endif
}