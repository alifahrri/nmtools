#define NMTOOLS_CAST_ARRAYS_EXTRA(name) \
inline auto name##_cs_fb = nmtools::cast(name, nmtools::kind::ndarray_cs_fb); \
inline auto name##_cs_hb = nmtools::cast(name, nmtools::kind::ndarray_cs_hb); \
inline auto name##_cs_db = nmtools::cast(name, nmtools::kind::ndarray_cs_hb); \
inline auto name##_fs_fb = nmtools::cast(name, nmtools::kind::ndarray_fs_fb); \
inline auto name##_fs_hb = nmtools::cast(name, nmtools::kind::ndarray_fs_hb); \
inline auto name##_fs_db = nmtools::cast(name, nmtools::kind::ndarray_fs_hb); \
inline auto name##_hs_fb = nmtools::cast(name, nmtools::kind::ndarray_hs_fb); \
inline auto name##_hs_hb = nmtools::cast(name, nmtools::kind::ndarray_hs_hb); \
inline auto name##_hs_db = nmtools::cast(name, nmtools::kind::ndarray_hs_hb); \
inline auto name##_ds_fb = nmtools::cast(name, nmtools::kind::ndarray_ds_fb); \
inline auto name##_ds_hb = nmtools::cast(name, nmtools::kind::ndarray_ds_hb); \
inline auto name##_ds_db = nmtools::cast(name, nmtools::kind::ndarray_ds_hb); \
inline auto name##_ls_fb = nmtools::cast(name, nmtools::kind::ndarray_ls_fb); \
inline auto name##_ls_hb = nmtools::cast(name, nmtools::kind::ndarray_ls_hb); \
inline auto name##_ls_db = nmtools::cast(name, nmtools::kind::ndarray_ls_hb);

#if defined(NMTOOLS_TESTING_GENERIC_NDARRAY) && defined(NMTOOLS_BUILD_CONSTEXPR_TESTS)
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

#include "nmtools/array/ufuncs/subtract.hpp"
#include "nmtools/testing/data/array/subtract.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
using namespace nmtools::literals;

#define UNROLL_SUBTRACT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, subtract, case_name); \
    using namespace args; \
    auto result = nmtools::subtract(__VA_ARGS__, nmtools::Unroll); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define UNROLL_REDUCE_SUBTRACT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, reduce_subtract, case_name); \
    using namespace args; \
    auto result = nmtools::subtract.reduce(__VA_ARGS__, nmtools::Unroll); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define UNROLL_ACCUMULATE_SUBTRACT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, accumulate_subtract, case_name); \
    using namespace args; \
    auto result = nmtools::subtract.accumulate(__VA_ARGS__, nmtools::Unroll); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define UNROLL_OUTER_SUBTRACT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, outer_subtract, case_name); \
    using namespace args; \
    auto result = nmtools::subtract.outer(__VA_ARGS__, nmtools::Unroll); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("subtract(case1)" * doctest::test_suite("unroll_context::subtract"))
{
    UNROLL_SUBTRACT_SUBCASE( case1, a, b );
    UNROLL_SUBTRACT_SUBCASE( case1, a_f, b_f );

    UNROLL_SUBTRACT_SUBCASE( case1, a_cs_fb, b_cs_fb );
    UNROLL_SUBTRACT_SUBCASE( case1, a_cs_hb, b_cs_hb );
    UNROLL_SUBTRACT_SUBCASE( case1, a_cs_db, b_cs_db );
}

TEST_CASE("subtract(case2)" * doctest::test_suite("unroll_context::subtract"))
{
    UNROLL_SUBTRACT_SUBCASE( case2, a, b );
    UNROLL_SUBTRACT_SUBCASE( case2, a_f, b );

    UNROLL_SUBTRACT_SUBCASE( case2, a_cs_fb, b );
    UNROLL_SUBTRACT_SUBCASE( case2, a_cs_hb, b );
    UNROLL_SUBTRACT_SUBCASE( case2, a_cs_db, b );
}

TEST_CASE("accumulate_subtract(case1)" * doctest::test_suite("unroll_context::accumulate_subtract"))
{
    UNROLL_ACCUMULATE_SUBTRACT_SUBCASE( case1, a, axis_ct );
    UNROLL_ACCUMULATE_SUBTRACT_SUBCASE( case1, a_f, axis_ct );

    UNROLL_ACCUMULATE_SUBTRACT_SUBCASE( case1, a_cs_fb, axis_ct );
    UNROLL_ACCUMULATE_SUBTRACT_SUBCASE( case1, a_cs_hb, axis_ct );
    UNROLL_ACCUMULATE_SUBTRACT_SUBCASE( case1, a_cs_db, axis_ct );
}

TEST_CASE("accumulate_subtract(case2)" * doctest::test_suite("unroll_context::accumulate_subtract"))
{
    UNROLL_ACCUMULATE_SUBTRACT_SUBCASE( case2, a, axis_ct );
    UNROLL_ACCUMULATE_SUBTRACT_SUBCASE( case2, a_f, axis_ct );

    UNROLL_ACCUMULATE_SUBTRACT_SUBCASE( case2, a_cs_fb, axis_ct );
    UNROLL_ACCUMULATE_SUBTRACT_SUBCASE( case2, a_cs_hb, axis_ct );
    UNROLL_ACCUMULATE_SUBTRACT_SUBCASE( case2, a_cs_db, axis_ct );
}

TEST_CASE("outer_subtract(case1)" * doctest::test_suite("unroll_context::outer_subtract"))
{
    UNROLL_OUTER_SUBTRACT_SUBCASE( case1, a, b );
    UNROLL_OUTER_SUBTRACT_SUBCASE( case1, a_f, b_f );

    UNROLL_OUTER_SUBTRACT_SUBCASE( case1, a_cs_fb, b_cs_fb );
    UNROLL_OUTER_SUBTRACT_SUBCASE( case1, a_cs_hb, b_cs_hb );
    UNROLL_OUTER_SUBTRACT_SUBCASE( case1, a_cs_db, b_cs_db );
}
