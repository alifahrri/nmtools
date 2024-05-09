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

#if defined(NMTOOLS_TESTING_GENERIC_NDARRAY) && defined(NMTOOLS_BUILD_CONSTEXPR_TESTS)
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

#include "nmtools/array/array/pad.hpp"
#include "nmtools/testing/data/array/pad.hpp"
#include "nmtools/testing/doctest.hpp"

#define RUN_pad_impl(...) \
nmtools::array::pad(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs pad fn to callable lambda
#define RUN_pad(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("array::pad-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_pad_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_pad(case_name, ...) \
RUN_pad_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define PAD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, pad, case_name); \
    using namespace args; \
    auto result = RUN_pad(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

#define CONSTEXPR_PAD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, constexpr_pad, case_name); \
    using namespace args; \
    constexpr auto result = RUN_pad(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

#ifndef NMTOOLS_BUILD_CONSTEXPR_TESTS

TEST_CASE("pad(case1)" * doctest::test_suite("array::pad"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    PAD_SUBCASE( case1, array, pad_width );
    PAD_SUBCASE( case1, array_a, pad_width_a );
    PAD_SUBCASE( case1, array_f, pad_width_f );
    PAD_SUBCASE( case1, array_h, pad_width_h );
    PAD_SUBCASE( case1, array_d, pad_width_a );

    #else
    PAD_SUBCASE( case1, array_cs_fb, pad_width_a );
    PAD_SUBCASE( case1, array_cs_hb, pad_width_a );
    PAD_SUBCASE( case1, array_cs_db, pad_width_a );

    PAD_SUBCASE( case1, array_fs_fb, pad_width_a );
    PAD_SUBCASE( case1, array_fs_hb, pad_width_a );
    PAD_SUBCASE( case1, array_fs_db, pad_width_a );

    PAD_SUBCASE( case1, array_hs_fb, pad_width_a );
    PAD_SUBCASE( case1, array_hs_hb, pad_width_a );
    PAD_SUBCASE( case1, array_hs_db, pad_width_a );

    PAD_SUBCASE( case1, array_ds_fb, pad_width_a );
    PAD_SUBCASE( case1, array_ds_hb, pad_width_a );
    PAD_SUBCASE( case1, array_ds_db, pad_width_a );

    PAD_SUBCASE( case1, array_ls_fb, pad_width_a );
    PAD_SUBCASE( case1, array_ls_hb, pad_width_a );
    PAD_SUBCASE( case1, array_ls_db, pad_width_a );
    #endif
}

TEST_CASE("pad(case2)" * doctest::test_suite("array::pad"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    PAD_SUBCASE( case2, array, pad_width );
    PAD_SUBCASE( case2, array_a, pad_width_a );
    PAD_SUBCASE( case2, array_f, pad_width_f );
    PAD_SUBCASE( case2, array_h, pad_width_h );
    PAD_SUBCASE( case2, array_d, pad_width_a );

    #else
    PAD_SUBCASE( case2, array_cs_fb, pad_width_a );
    PAD_SUBCASE( case2, array_cs_hb, pad_width_a );
    PAD_SUBCASE( case2, array_cs_db, pad_width_a );

    PAD_SUBCASE( case2, array_fs_fb, pad_width_a );
    PAD_SUBCASE( case2, array_fs_hb, pad_width_a );
    PAD_SUBCASE( case2, array_fs_db, pad_width_a );

    PAD_SUBCASE( case2, array_hs_fb, pad_width_a );
    PAD_SUBCASE( case2, array_hs_hb, pad_width_a );
    PAD_SUBCASE( case2, array_hs_db, pad_width_a );

    PAD_SUBCASE( case2, array_ds_fb, pad_width_a );
    PAD_SUBCASE( case2, array_ds_hb, pad_width_a );
    PAD_SUBCASE( case2, array_ds_db, pad_width_a );
    #endif
}

TEST_CASE("pad(case3)" * doctest::test_suite("array::pad"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    PAD_SUBCASE( case3, array, pad_width );
    PAD_SUBCASE( case3, array_a, pad_width_a );
    PAD_SUBCASE( case3, array_f, pad_width_f );
    PAD_SUBCASE( case3, array_h, pad_width_h );
    PAD_SUBCASE( case3, array_d, pad_width_a );

    #else
    PAD_SUBCASE( case3, array_cs_fb, pad_width_a );
    PAD_SUBCASE( case3, array_cs_hb, pad_width_a );
    PAD_SUBCASE( case3, array_cs_db, pad_width_a );

    PAD_SUBCASE( case3, array_fs_fb, pad_width_a );
    PAD_SUBCASE( case3, array_fs_hb, pad_width_a );
    PAD_SUBCASE( case3, array_fs_db, pad_width_a );

    PAD_SUBCASE( case3, array_hs_fb, pad_width_a );
    PAD_SUBCASE( case3, array_hs_hb, pad_width_a );
    PAD_SUBCASE( case3, array_hs_db, pad_width_a );

    PAD_SUBCASE( case3, array_ds_fb, pad_width_a );
    PAD_SUBCASE( case3, array_ds_hb, pad_width_a );
    PAD_SUBCASE( case3, array_ds_db, pad_width_a );
    #endif
}

TEST_CASE("pad(case4)" * doctest::test_suite("array::pad"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    PAD_SUBCASE( case4, array, pad_width );
    PAD_SUBCASE( case4, array_a, pad_width_a );
    PAD_SUBCASE( case4, array_f, pad_width_f );
    PAD_SUBCASE( case4, array_h, pad_width_h );
    PAD_SUBCASE( case4, array_d, pad_width_a );

    #else
    PAD_SUBCASE( case4, array_cs_fb, pad_width_a );
    PAD_SUBCASE( case4, array_cs_hb, pad_width_a );
    PAD_SUBCASE( case4, array_cs_db, pad_width_a );

    PAD_SUBCASE( case4, array_fs_fb, pad_width_a );
    PAD_SUBCASE( case4, array_fs_hb, pad_width_a );
    PAD_SUBCASE( case4, array_fs_db, pad_width_a );

    PAD_SUBCASE( case4, array_hs_fb, pad_width_a );
    PAD_SUBCASE( case4, array_hs_hb, pad_width_a );
    PAD_SUBCASE( case4, array_hs_db, pad_width_a );

    PAD_SUBCASE( case4, array_ds_fb, pad_width_a );
    PAD_SUBCASE( case4, array_ds_hb, pad_width_a );
    PAD_SUBCASE( case4, array_ds_db, pad_width_a );
    #endif
}

TEST_CASE("pad(case5)" * doctest::test_suite("array::pad"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    PAD_SUBCASE( case5, array, pad_width );
    PAD_SUBCASE( case5, array_a, pad_width_a );
    PAD_SUBCASE( case5, array_f, pad_width_f );
    PAD_SUBCASE( case5, array_h, pad_width_h );
    PAD_SUBCASE( case5, array_d, pad_width_a );

    #else
    PAD_SUBCASE( case5, array_cs_fb, pad_width_a );
    PAD_SUBCASE( case5, array_cs_hb, pad_width_a );
    PAD_SUBCASE( case5, array_cs_db, pad_width_a );

    PAD_SUBCASE( case5, array_fs_fb, pad_width_a );
    PAD_SUBCASE( case5, array_fs_hb, pad_width_a );
    PAD_SUBCASE( case5, array_fs_db, pad_width_a );

    PAD_SUBCASE( case5, array_hs_fb, pad_width_a );
    PAD_SUBCASE( case5, array_hs_hb, pad_width_a );
    PAD_SUBCASE( case5, array_hs_db, pad_width_a );

    PAD_SUBCASE( case5, array_ds_fb, pad_width_a );
    PAD_SUBCASE( case5, array_ds_hb, pad_width_a );
    PAD_SUBCASE( case5, array_ds_db, pad_width_a );
    #endif
}

#else

TEST_CASE("constexpr_pad(case1)" * doctest::test_suite("array::pad"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_PAD_SUBCASE( case1, array, pad_width_ct );
    CONSTEXPR_PAD_SUBCASE( case1, array_a, pad_width_ct );
    CONSTEXPR_PAD_SUBCASE( case1, array_f, pad_width_ct );

    #else
    CONSTEXPR_PAD_SUBCASE( case1, array_cs_fb, pad_width_ct );
    CONSTEXPR_PAD_SUBCASE( case1, array_cs_hb, pad_width_ct );

    // NOTE: padding may increase the shape & size, can't know the upper bound if only src size is known
    #if 0
    CONSTEXPR_PAD_SUBCASE( case1, array_fs_fb, pad_width_ct );
    CONSTEXPR_PAD_SUBCASE( case1, array_fs_hb, pad_width_ct );

    CONSTEXPR_PAD_SUBCASE( case1, array_hs_fb, pad_width_ct );
    CONSTEXPR_PAD_SUBCASE( case1, array_hs_hb, pad_width_ct );
    #endif

    CONSTEXPR_PAD_SUBCASE( case1, array_ls_fb, pad_width_ct );
    CONSTEXPR_PAD_SUBCASE( case1, array_ls_hb, pad_width_ct );

    CONSTEXPR_PAD_SUBCASE( case1, array_cs_fb, pad_width_cl );
    CONSTEXPR_PAD_SUBCASE( case1, array_cs_hb, pad_width_cl );

    CONSTEXPR_PAD_SUBCASE( case1, array_ls_fb, pad_width_cl );
    CONSTEXPR_PAD_SUBCASE( case1, array_ls_hb, pad_width_cl );
    #endif
}

TEST_CASE("constexpr_pad(case2)" * doctest::test_suite("array::pad"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_PAD_SUBCASE( case2, array, pad_width_ct );
    CONSTEXPR_PAD_SUBCASE( case2, array_a, pad_width_ct );
    CONSTEXPR_PAD_SUBCASE( case2, array_f, pad_width_ct );

    #else
    CONSTEXPR_PAD_SUBCASE( case2, array_cs_fb, pad_width_ct );
    CONSTEXPR_PAD_SUBCASE( case2, array_cs_hb, pad_width_ct );

    CONSTEXPR_PAD_SUBCASE( case2, array_ls_fb, pad_width_ct );
    CONSTEXPR_PAD_SUBCASE( case2, array_ls_hb, pad_width_ct );

    CONSTEXPR_PAD_SUBCASE( case2, array_cs_fb, pad_width_cl );
    CONSTEXPR_PAD_SUBCASE( case2, array_cs_hb, pad_width_cl );

    CONSTEXPR_PAD_SUBCASE( case2, array_ls_fb, pad_width_cl );
    CONSTEXPR_PAD_SUBCASE( case2, array_ls_hb, pad_width_cl );
    #endif
}

TEST_CASE("constexpr_pad(case3)" * doctest::test_suite("array::pad"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_PAD_SUBCASE( case3, array, pad_width_ct );
    CONSTEXPR_PAD_SUBCASE( case3, array_a, pad_width_ct );
    CONSTEXPR_PAD_SUBCASE( case3, array_f, pad_width_ct );

    #else
    CONSTEXPR_PAD_SUBCASE( case3, array_cs_fb, pad_width_ct );
    CONSTEXPR_PAD_SUBCASE( case3, array_cs_hb, pad_width_ct );

    CONSTEXPR_PAD_SUBCASE( case3, array_ls_fb, pad_width_ct );
    CONSTEXPR_PAD_SUBCASE( case3, array_ls_hb, pad_width_ct );

    CONSTEXPR_PAD_SUBCASE( case3, array_cs_fb, pad_width_cl );
    CONSTEXPR_PAD_SUBCASE( case3, array_cs_hb, pad_width_cl );

    CONSTEXPR_PAD_SUBCASE( case3, array_ls_fb, pad_width_cl );
    CONSTEXPR_PAD_SUBCASE( case3, array_ls_hb, pad_width_cl );
    #endif
}

TEST_CASE("constexpr_pad(case4)" * doctest::test_suite("array::pad"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_PAD_SUBCASE( case4, array, pad_width_ct );
    CONSTEXPR_PAD_SUBCASE( case4, array_a, pad_width_ct );
    CONSTEXPR_PAD_SUBCASE( case4, array_f, pad_width_ct );

    #else
    CONSTEXPR_PAD_SUBCASE( case4, array_cs_fb, pad_width_ct );
    CONSTEXPR_PAD_SUBCASE( case4, array_cs_hb, pad_width_ct );

    CONSTEXPR_PAD_SUBCASE( case4, array_ls_fb, pad_width_ct );
    CONSTEXPR_PAD_SUBCASE( case4, array_ls_hb, pad_width_ct );

    CONSTEXPR_PAD_SUBCASE( case4, array_cs_fb, pad_width_cl );
    CONSTEXPR_PAD_SUBCASE( case4, array_cs_hb, pad_width_cl );

    CONSTEXPR_PAD_SUBCASE( case4, array_ls_fb, pad_width_cl );
    CONSTEXPR_PAD_SUBCASE( case4, array_ls_hb, pad_width_cl );
    #endif
}

TEST_CASE("constexpr_pad(case5)" * doctest::test_suite("array::pad"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_PAD_SUBCASE( case5, array, pad_width_ct );
    CONSTEXPR_PAD_SUBCASE( case5, array_a, pad_width_ct );
    CONSTEXPR_PAD_SUBCASE( case5, array_f, pad_width_ct );

    #else
    CONSTEXPR_PAD_SUBCASE( case5, array_cs_fb, pad_width_ct );
    CONSTEXPR_PAD_SUBCASE( case5, array_cs_hb, pad_width_ct );

    CONSTEXPR_PAD_SUBCASE( case5, array_ls_fb, pad_width_ct );
    CONSTEXPR_PAD_SUBCASE( case5, array_ls_hb, pad_width_ct );

    CONSTEXPR_PAD_SUBCASE( case5, array_cs_fb, pad_width_cl );
    CONSTEXPR_PAD_SUBCASE( case5, array_cs_hb, pad_width_cl );

    CONSTEXPR_PAD_SUBCASE( case5, array_ls_fb, pad_width_cl );
    CONSTEXPR_PAD_SUBCASE( case5, array_ls_hb, pad_width_cl );
    #endif
}

#endif // NMTOOLS_BUILD_CONSTEXPR_TESTS