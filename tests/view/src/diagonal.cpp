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

#include "nmtools/array/diagonal.hpp"
#include "nmtools/testing/data/array/diagonal.hpp"
#include "nmtools/testing/doctest.hpp"

#define DIAGONAL_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( array, diagonal, case_name ); \
    using namespace args; \
    auto result = nmtools::view::diagonal(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("diagonal(case1)" * doctest::test_suite("view::diagonal"))
{
    SUBCASE("meta")
    {
        NMTOOLS_TESTING_USE_CASE( array, diagonal, case1 );
        {
            auto result = nmtools::view::diagonal( a );
            using result_t = decltype(result);
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, result_t );
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, result_t );
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, result_t );
        }
        {
            auto result = nmtools::view::diagonal( a_a );
            using result_t = decltype(result);
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, result_t );
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, result_t );
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, result_t );
        }
        {
            auto result = nmtools::view::diagonal( a_f );
            using result_t = decltype(result);
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, result_t );
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, result_t );
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, result_t );
        }
        {
            auto result = nmtools::view::diagonal( a_h );
            using result_t = decltype(result);
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, result_t );
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, result_t );
            NMTOOLS_STATIC_CHECK_TRAIT( !meta::is_fixed_shape, result_t );
        }
        {
            auto result = nmtools::view::diagonal( a_d );
            using result_t = decltype(result);
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, result_t );
            NMTOOLS_STATIC_CHECK_TRAIT( !meta::is_fixed_dim, result_t );
            NMTOOLS_STATIC_CHECK_TRAIT( !meta::is_fixed_shape, result_t );
        }
    }
    DIAGONAL_SUBCASE( case1, a );
    DIAGONAL_SUBCASE( case1, a_a );
    DIAGONAL_SUBCASE( case1, a_f );
    DIAGONAL_SUBCASE( case1, a_h );
    DIAGONAL_SUBCASE( case1, a_d );
}

TEST_CASE("diagonal(case2)" * doctest::test_suite("view::diagonal"))
{
    DIAGONAL_SUBCASE( case2, a, offset );
    DIAGONAL_SUBCASE( case2, a_a, offset );
    DIAGONAL_SUBCASE( case2, a_f, offset );
    DIAGONAL_SUBCASE( case2, a_h, offset );
    DIAGONAL_SUBCASE( case2, a_d, offset );
}

TEST_CASE("diagonal(case3)" * doctest::test_suite("view::diagonal"))
{
    DIAGONAL_SUBCASE( case3, a, offset );
    DIAGONAL_SUBCASE( case3, a_a, offset );
    DIAGONAL_SUBCASE( case3, a_f, offset );
    DIAGONAL_SUBCASE( case3, a_h, offset );
    DIAGONAL_SUBCASE( case3, a_d, offset );
}

TEST_CASE("diagonal(case4)" * doctest::test_suite("view::diagonal"))
{
    DIAGONAL_SUBCASE( case4, a, offset, axis1, axis2 );
    DIAGONAL_SUBCASE( case4, a_a, offset, axis1, axis2 );
    DIAGONAL_SUBCASE( case4, a_f, offset, axis1, axis2 );
    DIAGONAL_SUBCASE( case4, a_h, offset, axis1, axis2 );
    DIAGONAL_SUBCASE( case4, a_d, offset, axis1, axis2 );
}

TEST_CASE("diagonal(case5)" * doctest::test_suite("view::diagonal"))
{
    DIAGONAL_SUBCASE( case5, a, offset, axis1,axis2 );
    DIAGONAL_SUBCASE( case5, a_a, offset, axis1,axis2 );
    DIAGONAL_SUBCASE( case5, a_f, offset, axis1,axis2 );
    DIAGONAL_SUBCASE( case5, a_h, offset, axis1,axis2 );
    DIAGONAL_SUBCASE( case5, a_d, offset, axis1,axis2 );
}

TEST_CASE("diagonal(case6)" * doctest::test_suite("view::diagonal"))
{
    DIAGONAL_SUBCASE( case6, a, offset, axis1, axis2 );
    DIAGONAL_SUBCASE( case6, a_a, offset, axis1, axis2 );
    DIAGONAL_SUBCASE( case6, a_f, offset, axis1, axis2 );
    DIAGONAL_SUBCASE( case6, a_h, offset, axis1, axis2 );
    DIAGONAL_SUBCASE( case6, a_d, offset, axis1, axis2 );
}

TEST_CASE("diagonal(case7)" * doctest::test_suite("view::diagonal"))
{
    DIAGONAL_SUBCASE( case7, a, offset, axis1, axis2 );
    DIAGONAL_SUBCASE( case7, a_a, offset, axis1, axis2 );
    DIAGONAL_SUBCASE( case7, a_f, offset, axis1, axis2 );
    DIAGONAL_SUBCASE( case7, a_h, offset, axis1, axis2 );
    DIAGONAL_SUBCASE( case7, a_d, offset, axis1, axis2 );
}

TEST_CASE("diagonal(case8)" * doctest::test_suite("view::diagonal"))
{
    DIAGONAL_SUBCASE( case8, a, offset, axis1, axis2 );
    DIAGONAL_SUBCASE( case8, a_a, offset, axis1, axis2 );
    DIAGONAL_SUBCASE( case8, a_f, offset, axis1, axis2 );
    DIAGONAL_SUBCASE( case8, a_h, offset, axis1, axis2 );
    DIAGONAL_SUBCASE( case8, a_d, offset, axis1, axis2 );
}

TEST_CASE("diagonal(case9)" * doctest::test_suite("view::diagonal"))
{
    DIAGONAL_SUBCASE( case9, a, offset, axis1, axis2 );
    DIAGONAL_SUBCASE( case9, a_a, offset, axis1, axis2 );
    DIAGONAL_SUBCASE( case9, a_f, offset, axis1, axis2 );
    DIAGONAL_SUBCASE( case9, a_h, offset, axis1, axis2 );
    DIAGONAL_SUBCASE( case9, a_d, offset, axis1, axis2 );
}

TEST_CASE("diagonal(case10)" * doctest::test_suite("view::diagonal"))
{
    DIAGONAL_SUBCASE( case10, a, offset, axis1, axis2 );
    DIAGONAL_SUBCASE( case10, a_a, offset, axis1, axis2 );
    DIAGONAL_SUBCASE( case10, a_f, offset, axis1, axis2 );
    DIAGONAL_SUBCASE( case10, a_h, offset, axis1, axis2 );
    DIAGONAL_SUBCASE( case10, a_d, offset, axis1, axis2 );
}

TEST_CASE("diagonal(case11)" * doctest::test_suite("view::diagonal"))
{
    DIAGONAL_SUBCASE( case11, a, offset, axis1, axis2 );
    DIAGONAL_SUBCASE( case11, a_a, offset, axis1, axis2 );
    DIAGONAL_SUBCASE( case11, a_f, offset, axis1, axis2 );
    DIAGONAL_SUBCASE( case11, a_h, offset, axis1, axis2 );
    DIAGONAL_SUBCASE( case11, a_d, offset, axis1, axis2 );
}

TEST_CASE("diagonal(case12)" * doctest::test_suite("view::diagonal"))
{
    DIAGONAL_SUBCASE( case12, a, offset, axis1, axis2 );
    DIAGONAL_SUBCASE( case12, a_a, offset, axis1, axis2 );
    DIAGONAL_SUBCASE( case12, a_f, offset, axis1, axis2 );
    DIAGONAL_SUBCASE( case12, a_h, offset, axis1, axis2 );
    DIAGONAL_SUBCASE( case12, a_d, offset, axis1, axis2 );
}

TEST_CASE("diagonal(case13)" * doctest::test_suite("view::diagonal"))
{
    DIAGONAL_SUBCASE( case13, a, offset, axis1, axis2 );
    DIAGONAL_SUBCASE( case13, a_a, offset, axis1, axis2 );
    DIAGONAL_SUBCASE( case13, a_f, offset, axis1, axis2 );
    DIAGONAL_SUBCASE( case13, a_h, offset, axis1, axis2 );
    DIAGONAL_SUBCASE( case13, a_d, offset, axis1, axis2 );
}

TEST_CASE("diagonal(case14)" * doctest::test_suite("view::diagonal"))
{
    DIAGONAL_SUBCASE( case14, a, offset, axis1, axis2 );
    DIAGONAL_SUBCASE( case14, a_a, offset, axis1, axis2 );
    DIAGONAL_SUBCASE( case14, a_f, offset, axis1, axis2 );
    DIAGONAL_SUBCASE( case14, a_h, offset, axis1, axis2 );
    DIAGONAL_SUBCASE( case14, a_d, offset, axis1, axis2 );
}