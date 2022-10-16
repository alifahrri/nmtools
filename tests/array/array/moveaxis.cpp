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
inline auto name##_ds_db = nmtools::cast(name, nmtools::array::kind::ndarray_ds_db);
#endif

#if defined(NMTOOLS_TESTING_GENERIC_NDARRAY) && defined(NMTOOLS_TESTING_CONSTEXPR)
#define NMTOOLS_CONSTEXPR_CAST_ARRAYS_EXTRA(name) \
constexpr inline auto name##_cs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_fb); \
constexpr inline auto name##_cs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_hb); \
constexpr inline auto name##_fs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_fs_fb); \
constexpr inline auto name##_fs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_fs_hb); \
constexpr inline auto name##_hs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_hs_fb); \
constexpr inline auto name##_hs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_hs_hb);
#endif

#include "nmtools/array/array/moveaxis.hpp"
#include "nmtools/testing/data/array/moveaxis.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;

#define RUN_moveaxis_impl(...) \
nm::array::moveaxis(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs moveaxis fn to callable lambda
#define RUN_moveaxis(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("array::moveaxis-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_moveaxis_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_moveaxis(case_name, ...) \
RUN_moveaxis_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define MOVEAXIS_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, moveaxis, case_name); \
    using namespace args; \
    auto result = RUN_moveaxis(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define CONSTEXPR_MOVEAXIS_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, constexpr_moveaxis, case_name); \
    using namespace args; \
    constexpr auto result = RUN_moveaxis(case_name, __VA_ARGS__); \
    NMTOOLS_STATIC_ASSERT_CLOSE( result, expect::result ); \
}

#ifndef NMTOOLS_TESTING_CONSTEXPR

TEST_CASE("moveaxis(case1)" * doctest::test_suite("array::moveaxis"))
{
    MOVEAXIS_SUBCASE( case1, a, source, destination );
    MOVEAXIS_SUBCASE( case1, a_a, source, destination );
    MOVEAXIS_SUBCASE( case1, a_f, source, destination );
    MOVEAXIS_SUBCASE( case1, a_d, source, destination );
    MOVEAXIS_SUBCASE( case1, a_h, source, destination );
}

TEST_CASE("moveaxis(case2)" * doctest::test_suite("array::moveaxis"))
{
    MOVEAXIS_SUBCASE( case2, a, source, destination );
    MOVEAXIS_SUBCASE( case2, a_a, source, destination );
    MOVEAXIS_SUBCASE( case2, a_f, source, destination );
    MOVEAXIS_SUBCASE( case2, a_d, source, destination );
    MOVEAXIS_SUBCASE( case2, a_h, source, destination );
}

TEST_CASE("moveaxis(case3)" * doctest::test_suite("array::moveaxis"))
{
    MOVEAXIS_SUBCASE( case3, a, source, destination );
    MOVEAXIS_SUBCASE( case3, a_a, source, destination );
    MOVEAXIS_SUBCASE( case3, a_f, source, destination );
    MOVEAXIS_SUBCASE( case3, a_d, source, destination );
    MOVEAXIS_SUBCASE( case3, a_h, source, destination );
}

TEST_CASE("moveaxis(case4)" * doctest::test_suite("array::moveaxis"))
{
    MOVEAXIS_SUBCASE( case4, a, source, destination );
    MOVEAXIS_SUBCASE( case4, a_a, source, destination );
    MOVEAXIS_SUBCASE( case4, a_f, source, destination );
    MOVEAXIS_SUBCASE( case4, a_d, source, destination );
    MOVEAXIS_SUBCASE( case4, a_h, source, destination );
}

TEST_CASE("moveaxis(case5)" * doctest::test_suite("array::moveaxis"))
{
    MOVEAXIS_SUBCASE( case5, a, source, destination );
    MOVEAXIS_SUBCASE( case5, a_a, source, destination );
    MOVEAXIS_SUBCASE( case5, a_f, source, destination );
    MOVEAXIS_SUBCASE( case5, a_d, source, destination );
    MOVEAXIS_SUBCASE( case5, a_h, source, destination );
}

TEST_CASE("moveaxis(case6)" * doctest::test_suite("array::moveaxis"))
{
    MOVEAXIS_SUBCASE( case6, a, source, destination );
    MOVEAXIS_SUBCASE( case6, a_a, source, destination );
    MOVEAXIS_SUBCASE( case6, a_f, source, destination );
    MOVEAXIS_SUBCASE( case6, a_d, source, destination );
    MOVEAXIS_SUBCASE( case6, a_h, source, destination );
}

TEST_CASE("moveaxis(case7)" * doctest::test_suite("array::moveaxis"))
{
    MOVEAXIS_SUBCASE( case7, a, source, destination );
    MOVEAXIS_SUBCASE( case7, a_a, source, destination );
    MOVEAXIS_SUBCASE( case7, a_f, source, destination );
    MOVEAXIS_SUBCASE( case7, a_d, source, destination );
    MOVEAXIS_SUBCASE( case7, a_h, source, destination );
}

TEST_CASE("moveaxis(case8)" * doctest::test_suite("array::moveaxis"))
{
    MOVEAXIS_SUBCASE( case8, a, source, destination );
    MOVEAXIS_SUBCASE( case8, a_a, source, destination );
    MOVEAXIS_SUBCASE( case8, a_f, source, destination );
    MOVEAXIS_SUBCASE( case8, a_d, source, destination );
    MOVEAXIS_SUBCASE( case8, a_h, source, destination );
}

TEST_CASE("moveaxis(case9)" * doctest::test_suite("array::moveaxis"))
{
    MOVEAXIS_SUBCASE( case9, a, source, destination );
    MOVEAXIS_SUBCASE( case9, a_a, source, destination );
    MOVEAXIS_SUBCASE( case9, a_f, source, destination );
    MOVEAXIS_SUBCASE( case9, a_d, source, destination );
    MOVEAXIS_SUBCASE( case9, a_h, source, destination );
}

#else // NMTOOLS_TESTING_CONSTEXPR

TEST_CASE("moveaxis(case1)" * doctest::test_suite("array::constexpr_moveaxis"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)

    CONSTEXPR_MOVEAXIS_SUBCASE( case1, a, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case1, a_a, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case1, a_f, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case1, a_h, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case1, a, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case1, a_a, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case1, a_f, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case1, a_h, source_ct, destination_ct );
    #else

    CONSTEXPR_MOVEAXIS_SUBCASE( case1, a_cs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case1, a_cs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case1, a_fs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case1, a_fs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case1, a_hs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case1, a_hs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case1, a_cs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case1, a_cs_hb, source_ct, destination_ct );

    CONSTEXPR_MOVEAXIS_SUBCASE( case1, a_fs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case1, a_fs_hb, source_ct, destination_ct );

    CONSTEXPR_MOVEAXIS_SUBCASE( case1, a_hs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case1, a_hs_hb, source_ct, destination_ct );

    #endif
}

#if 1
TEST_CASE("moveaxis(case2)" * doctest::test_suite("array::constexpr_moveaxis"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_MOVEAXIS_SUBCASE( case2, a, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case2, a_a, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case2, a_f, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case2, a_h, source, destination );
    #else

    CONSTEXPR_MOVEAXIS_SUBCASE( case2, a_cs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case2, a_cs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case2, a_fs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case2, a_fs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case2, a_hs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case2, a_hs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case2, a_cs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case2, a_cs_hb, source_ct, destination_ct );

    CONSTEXPR_MOVEAXIS_SUBCASE( case2, a_fs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case2, a_fs_hb, source_ct, destination_ct );

    CONSTEXPR_MOVEAXIS_SUBCASE( case2, a_hs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case2, a_hs_hb, source_ct, destination_ct );

    #endif
}

TEST_CASE("moveaxis(case3)" * doctest::test_suite("array::constexpr_moveaxis"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_MOVEAXIS_SUBCASE( case3, a, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case3, a_a, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case3, a_f, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case3, a_h, source, destination );
    #else


    CONSTEXPR_MOVEAXIS_SUBCASE( case3, a_cs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case3, a_cs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case3, a_fs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case3, a_fs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case3, a_hs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case3, a_hs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case3, a_cs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case3, a_cs_hb, source_ct, destination_ct );

    CONSTEXPR_MOVEAXIS_SUBCASE( case3, a_fs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case3, a_fs_hb, source_ct, destination_ct );

    CONSTEXPR_MOVEAXIS_SUBCASE( case3, a_hs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case3, a_hs_hb, source_ct, destination_ct );

    #endif
}

TEST_CASE("moveaxis(case4)" * doctest::test_suite("array::constexpr_moveaxis"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_MOVEAXIS_SUBCASE( case4, a, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case4, a_a, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case4, a_f, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case4, a_h, source, destination );
    #else

    CONSTEXPR_MOVEAXIS_SUBCASE( case4, a_cs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case4, a_cs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case4, a_fs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case4, a_fs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case4, a_hs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case4, a_hs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case4, a_cs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case4, a_cs_hb, source_ct, destination_ct );

    CONSTEXPR_MOVEAXIS_SUBCASE( case4, a_fs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case4, a_fs_hb, source_ct, destination_ct );

    CONSTEXPR_MOVEAXIS_SUBCASE( case4, a_hs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case4, a_hs_hb, source_ct, destination_ct );

    #endif
}

TEST_CASE("moveaxis(case5)" * doctest::test_suite("array::constexpr_moveaxis"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_MOVEAXIS_SUBCASE( case5, a, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case5, a_a, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case5, a_f, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case5, a_h, source, destination );
    #else

    CONSTEXPR_MOVEAXIS_SUBCASE( case5, a_cs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case5, a_cs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case5, a_fs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case5, a_fs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case5, a_hs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case5, a_hs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case5, a_cs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case5, a_cs_hb, source_ct, destination_ct );

    CONSTEXPR_MOVEAXIS_SUBCASE( case5, a_fs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case5, a_fs_hb, source_ct, destination_ct );

    CONSTEXPR_MOVEAXIS_SUBCASE( case5, a_hs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case5, a_hs_hb, source_ct, destination_ct );

    #endif
}

TEST_CASE("moveaxis(case6)" * doctest::test_suite("array::constexpr_moveaxis"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_MOVEAXIS_SUBCASE( case6, a, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case6, a_a, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case6, a_f, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case6, a_h, source, destination );
    #else

    CONSTEXPR_MOVEAXIS_SUBCASE( case6, a_cs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case6, a_cs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case6, a_fs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case6, a_fs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case6, a_hs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case6, a_hs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case6, a_cs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case6, a_cs_hb, source_ct, destination_ct );

    CONSTEXPR_MOVEAXIS_SUBCASE( case6, a_fs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case6, a_fs_hb, source_ct, destination_ct );

    CONSTEXPR_MOVEAXIS_SUBCASE( case6, a_hs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case6, a_hs_hb, source_ct, destination_ct );

    #endif
}

TEST_CASE("moveaxis(case7)" * doctest::test_suite("array::constexpr_moveaxis"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_MOVEAXIS_SUBCASE( case7, a, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case7, a_a, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case7, a_f, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case7, a_h, source, destination );
    #else

    CONSTEXPR_MOVEAXIS_SUBCASE( case7, a_cs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case7, a_cs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case7, a_fs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case7, a_fs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case7, a_hs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case7, a_hs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case7, a_cs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case7, a_cs_hb, source_ct, destination_ct );

    CONSTEXPR_MOVEAXIS_SUBCASE( case7, a_fs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case7, a_fs_hb, source_ct, destination_ct );

    CONSTEXPR_MOVEAXIS_SUBCASE( case7, a_hs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case7, a_hs_hb, source_ct, destination_ct );

    #endif
}

TEST_CASE("moveaxis(case8)" * doctest::test_suite("array::constexpr_moveaxis"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_MOVEAXIS_SUBCASE( case8, a, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case8, a_a, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case8, a_f, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case8, a_h, source, destination );
    #else

    CONSTEXPR_MOVEAXIS_SUBCASE( case8, a_cs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case8, a_cs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case8, a_fs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case8, a_fs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case8, a_hs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case8, a_hs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case8, a_cs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case8, a_cs_hb, source_ct, destination_ct );

    CONSTEXPR_MOVEAXIS_SUBCASE( case8, a_fs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case8, a_fs_hb, source_ct, destination_ct );

    CONSTEXPR_MOVEAXIS_SUBCASE( case8, a_hs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case8, a_hs_hb, source_ct, destination_ct );

    #endif
}

TEST_CASE("moveaxis(case9)" * doctest::test_suite("array::constexpr_moveaxis"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_MOVEAXIS_SUBCASE( case9, a, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case9, a_a, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case9, a_f, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case9, a_h, source, destination );
    #else

    CONSTEXPR_MOVEAXIS_SUBCASE( case9, a_cs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case9, a_cs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case9, a_fs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case9, a_fs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case9, a_hs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case9, a_hs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case9, a_cs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case9, a_cs_hb, source_ct, destination_ct );

    CONSTEXPR_MOVEAXIS_SUBCASE( case9, a_fs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case9, a_fs_hb, source_ct, destination_ct );

    CONSTEXPR_MOVEAXIS_SUBCASE( case9, a_hs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case9, a_hs_hb, source_ct, destination_ct );

    #endif
}

#endif

#endif // NMTOOLS_TESTING_CONSTEXPR