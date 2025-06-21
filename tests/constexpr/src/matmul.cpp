#define NMTOOLS_CONSTEXPR_CAST_ARRAYS_EXTRA(name) \
constexpr inline auto name##_cs_fb = nmtools::cast(name, nmtools::kind::ndarray_cs_fb); \
constexpr inline auto name##_cs_hb = nmtools::cast(name, nmtools::kind::ndarray_cs_hb); \
constexpr inline auto name##_fs_fb = nmtools::cast(name, nmtools::kind::ndarray_fs_fb); \
constexpr inline auto name##_fs_hb = nmtools::cast(name, nmtools::kind::ndarray_fs_hb); \
constexpr inline auto name##_hs_fb = nmtools::cast(name, nmtools::kind::ndarray_hs_fb); \
constexpr inline auto name##_hs_hb = nmtools::cast(name, nmtools::kind::ndarray_hs_hb); \
constexpr inline auto name##_ls_fb = nmtools::cast(name, nmtools::kind::ndarray_ls_fb); \
constexpr inline auto name##_ls_hb = nmtools::cast(name, nmtools::kind::ndarray_ls_hb);

#include "nmtools/array/matmul.hpp"
#include "nmtools/testing/data/constexpr/matmul.hpp"
#include "nmtools/testing/doctest.hpp"

#define CONSTEXPR_MATMUL_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, constexpr_matmul, case_name); \
    using namespace args; \
    constexpr auto result = nmtools::matmul(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

// NOTE: std::tuple<none_t...> is not constexpr-friendly: https://godbolt.org/z/Y3GMs5roo
#ifdef NMTOOLS_DISABLE_STL

TEST_CASE("constexpr_matmul(case1)" * doctest::test_suite("array::matmul"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_MATMUL_SUBCASE( case1, lhs, rhs );
    CONSTEXPR_MATMUL_SUBCASE( case1, lhs_a, rhs_a );
    CONSTEXPR_MATMUL_SUBCASE( case1, lhs_f, rhs_f );
    #else
    CONSTEXPR_MATMUL_SUBCASE( case1, lhs_cs_fb, rhs_cs_fb );
    CONSTEXPR_MATMUL_SUBCASE( case1, lhs_cs_hb, rhs_cs_hb );

    // changed to matmulv2, missing some compile-time shape inference
    // TODO: fix compile-time shape inference
    #if 0
    CONSTEXPR_MATMUL_SUBCASE( case1, lhs_fs_fb, rhs_fs_fb );
    CONSTEXPR_MATMUL_SUBCASE( case1, lhs_fs_hb, rhs_fs_hb );

    CONSTEXPR_MATMUL_SUBCASE( case1, lhs_ls_fb, rhs_ls_fb );
    CONSTEXPR_MATMUL_SUBCASE( case1, lhs_ls_hb, rhs_ls_hb );

    CONSTEXPR_MATMUL_SUBCASE( case1, lhs_cs_fb, rhs_fs_fb );
    CONSTEXPR_MATMUL_SUBCASE( case1, lhs_cs_hb, rhs_fs_hb );

    CONSTEXPR_MATMUL_SUBCASE( case1, lhs_ls_fb, rhs_fs_fb );
    CONSTEXPR_MATMUL_SUBCASE( case1, lhs_ls_hb, rhs_fs_hb );

    CONSTEXPR_MATMUL_SUBCASE( case1, lhs_fs_fb, rhs_cs_fb );
    CONSTEXPR_MATMUL_SUBCASE( case1, lhs_fs_hb, rhs_cs_hb );

    CONSTEXPR_MATMUL_SUBCASE( case1, lhs_ls_fb, rhs_cs_fb );
    CONSTEXPR_MATMUL_SUBCASE( case1, lhs_ls_hb, rhs_cs_hb );

    CONSTEXPR_MATMUL_SUBCASE( case1, lhs_cs_fb, rhs_ls_fb );
    CONSTEXPR_MATMUL_SUBCASE( case1, lhs_cs_hb, rhs_ls_hb );

    CONSTEXPR_MATMUL_SUBCASE( case1, lhs_fs_fb, rhs_ls_fb );
    CONSTEXPR_MATMUL_SUBCASE( case1, lhs_fs_hb, rhs_ls_hb );
    #endif
    #endif
}

TEST_CASE("constexpr_matmul(case2)" * doctest::test_suite("array::matmul"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_MATMUL_SUBCASE( case2, lhs, rhs );
    CONSTEXPR_MATMUL_SUBCASE( case2, lhs_a, rhs_a );
    CONSTEXPR_MATMUL_SUBCASE( case2, lhs_f, rhs_f );
    #else
    CONSTEXPR_MATMUL_SUBCASE( case2, lhs_cs_fb, rhs_cs_fb );
    CONSTEXPR_MATMUL_SUBCASE( case2, lhs_cs_hb, rhs_cs_hb );

    // changed to matmulv2, missing some compile-time shape inference
    // TODO: fix compile-time shape inference
    #if 0
    CONSTEXPR_MATMUL_SUBCASE( case2, lhs_fs_fb, rhs_fs_fb );
    CONSTEXPR_MATMUL_SUBCASE( case2, lhs_fs_hb, rhs_fs_hb );

    CONSTEXPR_MATMUL_SUBCASE( case2, lhs_ls_fb, rhs_ls_fb );
    CONSTEXPR_MATMUL_SUBCASE( case2, lhs_ls_hb, rhs_ls_hb );

    CONSTEXPR_MATMUL_SUBCASE( case2, lhs_cs_fb, rhs_fs_fb );
    CONSTEXPR_MATMUL_SUBCASE( case2, lhs_cs_hb, rhs_fs_hb );

    CONSTEXPR_MATMUL_SUBCASE( case2, lhs_ls_fb, rhs_fs_fb );
    CONSTEXPR_MATMUL_SUBCASE( case2, lhs_ls_hb, rhs_fs_hb );

    CONSTEXPR_MATMUL_SUBCASE( case2, lhs_fs_fb, rhs_cs_fb );
    CONSTEXPR_MATMUL_SUBCASE( case2, lhs_fs_hb, rhs_cs_hb );

    CONSTEXPR_MATMUL_SUBCASE( case2, lhs_ls_fb, rhs_cs_fb );
    CONSTEXPR_MATMUL_SUBCASE( case2, lhs_ls_hb, rhs_cs_hb );

    CONSTEXPR_MATMUL_SUBCASE( case2, lhs_cs_fb, rhs_ls_fb );
    CONSTEXPR_MATMUL_SUBCASE( case2, lhs_cs_hb, rhs_ls_hb );

    CONSTEXPR_MATMUL_SUBCASE( case2, lhs_fs_fb, rhs_ls_fb );
    CONSTEXPR_MATMUL_SUBCASE( case2, lhs_fs_hb, rhs_ls_hb );
    #endif
    #endif
}

TEST_CASE("constexpr_matmul(case3)" * doctest::test_suite("array::matmul"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_MATMUL_SUBCASE( case3, lhs, rhs );
    CONSTEXPR_MATMUL_SUBCASE( case3, lhs_a, rhs_a );
    CONSTEXPR_MATMUL_SUBCASE( case3, lhs_f, rhs_f );
    #else
    CONSTEXPR_MATMUL_SUBCASE( case3, lhs_cs_fb, rhs_cs_fb );
    CONSTEXPR_MATMUL_SUBCASE( case3, lhs_cs_hb, rhs_cs_hb );

    // changed to matmulv2, missing some compile-time shape inference
    // TODO: fix compile-time shape inference
    #if 0
    CONSTEXPR_MATMUL_SUBCASE( case3, lhs_fs_fb, rhs_fs_fb );
    CONSTEXPR_MATMUL_SUBCASE( case3, lhs_fs_hb, rhs_fs_hb );

    CONSTEXPR_MATMUL_SUBCASE( case3, lhs_ls_fb, rhs_ls_fb );
    CONSTEXPR_MATMUL_SUBCASE( case3, lhs_ls_hb, rhs_ls_hb );

    CONSTEXPR_MATMUL_SUBCASE( case3, lhs_cs_fb, rhs_fs_fb );
    CONSTEXPR_MATMUL_SUBCASE( case3, lhs_cs_hb, rhs_fs_hb );

    CONSTEXPR_MATMUL_SUBCASE( case3, lhs_ls_fb, rhs_fs_fb );
    CONSTEXPR_MATMUL_SUBCASE( case3, lhs_ls_hb, rhs_fs_hb );

    CONSTEXPR_MATMUL_SUBCASE( case3, lhs_fs_fb, rhs_cs_fb );
    CONSTEXPR_MATMUL_SUBCASE( case3, lhs_fs_hb, rhs_cs_hb );

    CONSTEXPR_MATMUL_SUBCASE( case3, lhs_ls_fb, rhs_cs_fb );
    CONSTEXPR_MATMUL_SUBCASE( case3, lhs_ls_hb, rhs_cs_hb );

    CONSTEXPR_MATMUL_SUBCASE( case3, lhs_cs_fb, rhs_ls_fb );
    CONSTEXPR_MATMUL_SUBCASE( case3, lhs_cs_hb, rhs_ls_hb );

    CONSTEXPR_MATMUL_SUBCASE( case3, lhs_fs_fb, rhs_ls_fb );
    CONSTEXPR_MATMUL_SUBCASE( case3, lhs_fs_hb, rhs_ls_hb );
    #endif
    #endif
}

TEST_CASE("constexpr_matmul(case4)" * doctest::test_suite("array::matmul"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_MATMUL_SUBCASE( case4, lhs, rhs );
    CONSTEXPR_MATMUL_SUBCASE( case4, lhs_a, rhs_a );
    CONSTEXPR_MATMUL_SUBCASE( case4, lhs_f, rhs_f );
    #else
    CONSTEXPR_MATMUL_SUBCASE( case4, lhs_cs_fb, rhs_cs_fb );
    CONSTEXPR_MATMUL_SUBCASE( case4, lhs_cs_hb, rhs_cs_hb );

    // changed to matmulv2, missing some compile-time shape inference
    // TODO: fix compile-time shape inference
    #if 0
    CONSTEXPR_MATMUL_SUBCASE( case4, lhs_fs_fb, rhs_fs_fb );
    CONSTEXPR_MATMUL_SUBCASE( case4, lhs_fs_hb, rhs_fs_hb );

    CONSTEXPR_MATMUL_SUBCASE( case4, lhs_ls_fb, rhs_ls_fb );
    CONSTEXPR_MATMUL_SUBCASE( case4, lhs_ls_hb, rhs_ls_hb );

    CONSTEXPR_MATMUL_SUBCASE( case4, lhs_cs_fb, rhs_fs_fb );
    CONSTEXPR_MATMUL_SUBCASE( case4, lhs_cs_hb, rhs_fs_hb );

    CONSTEXPR_MATMUL_SUBCASE( case4, lhs_ls_fb, rhs_fs_fb );
    CONSTEXPR_MATMUL_SUBCASE( case4, lhs_ls_hb, rhs_fs_hb );

    CONSTEXPR_MATMUL_SUBCASE( case4, lhs_fs_fb, rhs_cs_fb );
    CONSTEXPR_MATMUL_SUBCASE( case4, lhs_fs_hb, rhs_cs_hb );

    CONSTEXPR_MATMUL_SUBCASE( case4, lhs_ls_fb, rhs_cs_fb );
    CONSTEXPR_MATMUL_SUBCASE( case4, lhs_ls_hb, rhs_cs_hb );

    CONSTEXPR_MATMUL_SUBCASE( case4, lhs_cs_fb, rhs_ls_fb );
    CONSTEXPR_MATMUL_SUBCASE( case4, lhs_cs_hb, rhs_ls_hb );

    CONSTEXPR_MATMUL_SUBCASE( case4, lhs_fs_fb, rhs_ls_fb );
    CONSTEXPR_MATMUL_SUBCASE( case4, lhs_fs_hb, rhs_ls_hb );
    #endif
    #endif
}

TEST_CASE("constexpr_matmul(case5)" * doctest::test_suite("array::matmul"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_MATMUL_SUBCASE( case5, lhs, rhs );
    CONSTEXPR_MATMUL_SUBCASE( case5, lhs_a, rhs_a );
    CONSTEXPR_MATMUL_SUBCASE( case5, lhs_f, rhs_f );
    #else
    CONSTEXPR_MATMUL_SUBCASE( case5, lhs_cs_fb, rhs_cs_fb );
    CONSTEXPR_MATMUL_SUBCASE( case5, lhs_cs_hb, rhs_cs_hb );

    // changed to matmulv2, missing some compile-time shape inference
    // TODO: fix compile-time shape inference
    #if 0
    CONSTEXPR_MATMUL_SUBCASE( case5, lhs_fs_fb, rhs_fs_fb );
    CONSTEXPR_MATMUL_SUBCASE( case5, lhs_fs_hb, rhs_fs_hb );

    CONSTEXPR_MATMUL_SUBCASE( case5, lhs_ls_fb, rhs_ls_fb );
    CONSTEXPR_MATMUL_SUBCASE( case5, lhs_ls_hb, rhs_ls_hb );

    CONSTEXPR_MATMUL_SUBCASE( case5, lhs_cs_fb, rhs_fs_fb );
    CONSTEXPR_MATMUL_SUBCASE( case5, lhs_cs_hb, rhs_fs_hb );

    CONSTEXPR_MATMUL_SUBCASE( case5, lhs_ls_fb, rhs_fs_fb );
    CONSTEXPR_MATMUL_SUBCASE( case5, lhs_ls_hb, rhs_fs_hb );

    CONSTEXPR_MATMUL_SUBCASE( case5, lhs_fs_fb, rhs_cs_fb );
    CONSTEXPR_MATMUL_SUBCASE( case5, lhs_fs_hb, rhs_cs_hb );

    CONSTEXPR_MATMUL_SUBCASE( case5, lhs_ls_fb, rhs_cs_fb );
    CONSTEXPR_MATMUL_SUBCASE( case5, lhs_ls_hb, rhs_cs_hb );

    CONSTEXPR_MATMUL_SUBCASE( case5, lhs_cs_fb, rhs_ls_fb );
    CONSTEXPR_MATMUL_SUBCASE( case5, lhs_cs_hb, rhs_ls_hb );

    CONSTEXPR_MATMUL_SUBCASE( case5, lhs_fs_fb, rhs_ls_fb );
    CONSTEXPR_MATMUL_SUBCASE( case5, lhs_fs_hb, rhs_ls_hb );
    #endif
    #endif
}

TEST_CASE("constexpr_matmul(case6)" * doctest::test_suite("array::matmul"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_MATMUL_SUBCASE( case6, lhs, rhs );
    CONSTEXPR_MATMUL_SUBCASE( case6, lhs_a, rhs_a );
    CONSTEXPR_MATMUL_SUBCASE( case6, lhs_f, rhs_f );
    #else
    CONSTEXPR_MATMUL_SUBCASE( case6, lhs_cs_fb, rhs_cs_fb );
    CONSTEXPR_MATMUL_SUBCASE( case6, lhs_cs_hb, rhs_cs_hb );

    // changed to matmulv2, missing some compile-time shape inference
    // TODO: fix compile-time shape inference
    #if 0
    CONSTEXPR_MATMUL_SUBCASE( case6, lhs_fs_fb, rhs_fs_fb );
    CONSTEXPR_MATMUL_SUBCASE( case6, lhs_fs_hb, rhs_fs_hb );

    CONSTEXPR_MATMUL_SUBCASE( case6, lhs_ls_fb, rhs_ls_fb );
    CONSTEXPR_MATMUL_SUBCASE( case6, lhs_ls_hb, rhs_ls_hb );

    CONSTEXPR_MATMUL_SUBCASE( case6, lhs_cs_fb, rhs_fs_fb );
    CONSTEXPR_MATMUL_SUBCASE( case6, lhs_cs_hb, rhs_fs_hb );

    CONSTEXPR_MATMUL_SUBCASE( case6, lhs_ls_fb, rhs_fs_fb );
    CONSTEXPR_MATMUL_SUBCASE( case6, lhs_ls_hb, rhs_fs_hb );

    CONSTEXPR_MATMUL_SUBCASE( case6, lhs_fs_fb, rhs_cs_fb );
    CONSTEXPR_MATMUL_SUBCASE( case6, lhs_fs_hb, rhs_cs_hb );

    CONSTEXPR_MATMUL_SUBCASE( case6, lhs_ls_fb, rhs_cs_fb );
    CONSTEXPR_MATMUL_SUBCASE( case6, lhs_ls_hb, rhs_cs_hb );

    CONSTEXPR_MATMUL_SUBCASE( case6, lhs_cs_fb, rhs_ls_fb );
    CONSTEXPR_MATMUL_SUBCASE( case6, lhs_cs_hb, rhs_ls_hb );

    CONSTEXPR_MATMUL_SUBCASE( case6, lhs_fs_fb, rhs_ls_fb );
    CONSTEXPR_MATMUL_SUBCASE( case6, lhs_fs_hb, rhs_ls_hb );
    #endif
    #endif
}

#endif // NMTOOLS_TESTING_DISABLE_STL