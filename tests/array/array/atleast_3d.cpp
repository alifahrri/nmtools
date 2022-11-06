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

#if defined(NMTOOLS_TESTING_GENERIC_NDARRAY) && defined(NMTOOLS_TESTING_CONSTEXPR)
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
#include "nmtools/testing/data/array/atleast_3d.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>
#include <tuple>

#define RUN_atleast_3d_impl(...) \
nmtools::array::atleast_3d(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nmtools::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs atleast_3d fn to callable lambda
#define RUN_atleast_3d(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("atleast_3d-") + #case_name; \
    auto name  = nmtools::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_atleast_3d_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_atleast_3d(case_name, ...) \
RUN_atleast_3d_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define ATLEAST_3D_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, atleast_3d, case_name); \
    using namespace args; \
    auto result = RUN_atleast_3d(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::dim(result), expect::dim ); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define CONSTEXPR_ATLEAST_3D_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, constexpr_atleast_3d, case_name); \
    using namespace args; \
    constexpr auto result = RUN_atleast_3d(case_name, __VA_ARGS__); \
    NMTOOLS_STATIC_ASSERT_EQUAL( nmtools::dim(result), expect::dim ); \
    NMTOOLS_STATIC_ASSERT_EQUAL( nmtools::shape(result), expect::shape ); \
    NMTOOLS_STATIC_ASSERT_CLOSE( result, expect::result ); \
}

#ifndef NMTOOLS_TESTING_CONSTEXPR

TEST_CASE("atleast_3d(case1)" * doctest::test_suite("array::atleast_3d"))
{
    ATLEAST_3D_SUBCASE( case1, a );
}

TEST_CASE("atleast_3d(case2)" * doctest::test_suite("array::atleast_3d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    ATLEAST_3D_SUBCASE( case2, a );
    ATLEAST_3D_SUBCASE( case2, a_a );
    ATLEAST_3D_SUBCASE( case2, a_f );
    ATLEAST_3D_SUBCASE( case2, a_d );
    ATLEAST_3D_SUBCASE( case2, a_h );

    #else
    ATLEAST_3D_SUBCASE( case2, a_cs_fb );
    ATLEAST_3D_SUBCASE( case2, a_cs_hb );
    ATLEAST_3D_SUBCASE( case2, a_cs_db );

    ATLEAST_3D_SUBCASE( case2, a_fs_fb );
    ATLEAST_3D_SUBCASE( case2, a_fs_hb );
    ATLEAST_3D_SUBCASE( case2, a_fs_db );

    ATLEAST_3D_SUBCASE( case2, a_hs_fb );
    ATLEAST_3D_SUBCASE( case2, a_hs_hb );
    ATLEAST_3D_SUBCASE( case2, a_hs_db );

    ATLEAST_3D_SUBCASE( case2, a_ds_fb );
    ATLEAST_3D_SUBCASE( case2, a_ds_hb );
    ATLEAST_3D_SUBCASE( case2, a_ds_db );

    ATLEAST_3D_SUBCASE( case2, a_ls_fb );
    ATLEAST_3D_SUBCASE( case2, a_ls_hb );
    ATLEAST_3D_SUBCASE( case2, a_ls_db );
    #endif
}

TEST_CASE("atleast_3d(case3)" * doctest::test_suite("array::atleast_3d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    ATLEAST_3D_SUBCASE( case3, a );
    ATLEAST_3D_SUBCASE( case3, a_a );
    ATLEAST_3D_SUBCASE( case3, a_f );
    ATLEAST_3D_SUBCASE( case3, a_d );
    ATLEAST_3D_SUBCASE( case3, a_h );
   
    #else
    ATLEAST_3D_SUBCASE( case3, a_cs_fb );
    ATLEAST_3D_SUBCASE( case3, a_cs_hb );
    ATLEAST_3D_SUBCASE( case3, a_cs_db );

    ATLEAST_3D_SUBCASE( case3, a_fs_fb );
    ATLEAST_3D_SUBCASE( case3, a_fs_hb );
    ATLEAST_3D_SUBCASE( case3, a_fs_db );

    ATLEAST_3D_SUBCASE( case3, a_hs_fb );
    ATLEAST_3D_SUBCASE( case3, a_hs_hb );
    ATLEAST_3D_SUBCASE( case3, a_hs_db );

    ATLEAST_3D_SUBCASE( case3, a_ds_fb );
    ATLEAST_3D_SUBCASE( case3, a_ds_hb );
    ATLEAST_3D_SUBCASE( case3, a_ds_db );

    ATLEAST_3D_SUBCASE( case3, a_ls_fb );
    ATLEAST_3D_SUBCASE( case3, a_ls_hb );
    ATLEAST_3D_SUBCASE( case3, a_ls_db );
    #endif
}

TEST_CASE("atleast_3d(case4)" * doctest::test_suite("array::atleast_3d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    ATLEAST_3D_SUBCASE( case4, a );
    ATLEAST_3D_SUBCASE( case4, a_a );
    ATLEAST_3D_SUBCASE( case4, a_f );
    ATLEAST_3D_SUBCASE( case4, a_d );
    ATLEAST_3D_SUBCASE( case4, a_h );

    #else
    ATLEAST_3D_SUBCASE( case4, a_cs_fb );
    ATLEAST_3D_SUBCASE( case4, a_cs_hb );
    ATLEAST_3D_SUBCASE( case4, a_cs_db );

    ATLEAST_3D_SUBCASE( case4, a_fs_fb );
    ATLEAST_3D_SUBCASE( case4, a_fs_hb );
    ATLEAST_3D_SUBCASE( case4, a_fs_db );

    ATLEAST_3D_SUBCASE( case4, a_hs_fb );
    ATLEAST_3D_SUBCASE( case4, a_hs_hb );
    ATLEAST_3D_SUBCASE( case4, a_hs_db );

    ATLEAST_3D_SUBCASE( case4, a_ds_fb );
    ATLEAST_3D_SUBCASE( case4, a_ds_hb );
    ATLEAST_3D_SUBCASE( case4, a_ds_db );

    ATLEAST_3D_SUBCASE( case4, a_ls_fb );
    ATLEAST_3D_SUBCASE( case4, a_ls_hb );
    ATLEAST_3D_SUBCASE( case4, a_ls_db );
    #endif
}

TEST_CASE("atleast_3d(case5)" * doctest::test_suite("array::atleast_3d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    ATLEAST_3D_SUBCASE( case5, a );
    ATLEAST_3D_SUBCASE( case5, a_a );
    ATLEAST_3D_SUBCASE( case5, a_f );
    ATLEAST_3D_SUBCASE( case5, a_d );
    ATLEAST_3D_SUBCASE( case5, a_h );
   
    #else
    ATLEAST_3D_SUBCASE( case5, a_cs_fb );
    ATLEAST_3D_SUBCASE( case5, a_cs_hb );
    ATLEAST_3D_SUBCASE( case5, a_cs_db );

    ATLEAST_3D_SUBCASE( case5, a_fs_fb );
    ATLEAST_3D_SUBCASE( case5, a_fs_hb );
    ATLEAST_3D_SUBCASE( case5, a_fs_db );

    ATLEAST_3D_SUBCASE( case5, a_hs_fb );
    ATLEAST_3D_SUBCASE( case5, a_hs_hb );
    ATLEAST_3D_SUBCASE( case5, a_hs_db );

    ATLEAST_3D_SUBCASE( case5, a_ds_fb );
    ATLEAST_3D_SUBCASE( case5, a_ds_hb );
    ATLEAST_3D_SUBCASE( case5, a_ds_db );

    ATLEAST_3D_SUBCASE( case5, a_ls_fb );
    ATLEAST_3D_SUBCASE( case5, a_ls_hb );
    ATLEAST_3D_SUBCASE( case5, a_ls_db );
    #endif
}

#else // (NMTOOLS_TESTING_CONSTEXPR)

TEST_CASE("atleast_3d(case1)" * doctest::test_suite("array::constexpr_atleast_3d"))
{
    CONSTEXPR_ATLEAST_3D_SUBCASE( case1, a );
}

TEST_CASE("atleast_3d(case2)" * doctest::test_suite("array::constexpr_atleast_3d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_ATLEAST_3D_SUBCASE( case2, a );
    CONSTEXPR_ATLEAST_3D_SUBCASE( case2, a_a );
    CONSTEXPR_ATLEAST_3D_SUBCASE( case2, a_f );
    CONSTEXPR_ATLEAST_3D_SUBCASE( case2, a_h );

    #else
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
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_ATLEAST_3D_SUBCASE( case3, a );
    CONSTEXPR_ATLEAST_3D_SUBCASE( case3, a_a );
    CONSTEXPR_ATLEAST_3D_SUBCASE( case3, a_f );
    CONSTEXPR_ATLEAST_3D_SUBCASE( case3, a_h );
   
    #else
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
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_ATLEAST_3D_SUBCASE( case4, a );
    CONSTEXPR_ATLEAST_3D_SUBCASE( case4, a_a );
    CONSTEXPR_ATLEAST_3D_SUBCASE( case4, a_f );
    CONSTEXPR_ATLEAST_3D_SUBCASE( case4, a_h );

    #else
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
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_ATLEAST_3D_SUBCASE( case5, a );
    CONSTEXPR_ATLEAST_3D_SUBCASE( case5, a_a );
    CONSTEXPR_ATLEAST_3D_SUBCASE( case5, a_f );
    CONSTEXPR_ATLEAST_3D_SUBCASE( case5, a_h );
   
    #else
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

#endif

#if 0
namespace array = nmtools::array;
namespace meta = nmtools::meta;

TEST_CASE("atleast_3d(traits)" * doctest::test_suite("array::atleast_3d"))
{
    SUBCASE("fixed_ndarray(int)")
    {
        int a = 1;
        auto array = array::atleast_3d(a);
        using array_t = decltype(array);
        constexpr auto is_fixed = meta::is_fixed_shape_v<array_t>;
        NMTOOLS_STATIC_ASSERT_EQUAL( is_fixed, true );
    }
    SUBCASE("!fixed_ndarray(std::vector)")
    {
        auto a = nmtools_list{1,2};
        auto array = array::atleast_3d(a);
        using array_t = decltype(array);
        constexpr auto is_fixed = meta::is_fixed_shape_v<array_t>;
        NMTOOLS_STATIC_ASSERT_EQUAL( is_fixed, false );
    }
}
#endif