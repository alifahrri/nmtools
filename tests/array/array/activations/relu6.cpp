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

#include "nmtools/array/array/activations/relu6.hpp"
#include "nmtools/testing/data/array/relu6.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;

#define RUN_relu6_impl(...) \
nm::array::relu6(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs relu6 fn to callable lambda
#define RUN_relu6(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("relu6-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_relu6_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_relu6(case_name, ...) \
RUN_relu6_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define RELU6_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(activations, relu6, case_name); \
    using namespace args; \
    auto result = RUN_relu6(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define CONSTEXPR_RELU6_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(activations, constexpr_relu6, case_name); \
    using namespace args; \
    constexpr auto result = RUN_relu6(case_name, __VA_ARGS__); \
    NMTOOLS_STATIC_ASSERT_CLOSE( result, expect::result ); \
}

#ifndef NMTOOLS_BUILD_CONSTEXPR_TESTS

TEST_CASE("relu6(case1)" * doctest::test_suite("array::relu6"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    RELU6_SUBCASE(case1, a);
    RELU6_SUBCASE(case1, a_a);
    RELU6_SUBCASE(case1, a_f);
    RELU6_SUBCASE(case1, a_h);
    RELU6_SUBCASE(case1, a_d);

    #else
    RELU6_SUBCASE(case1, a_cs_fb);
    RELU6_SUBCASE(case1, a_cs_hb);
    RELU6_SUBCASE(case1, a_cs_db);

    RELU6_SUBCASE(case1, a_fs_fb);
    RELU6_SUBCASE(case1, a_fs_hb);
    RELU6_SUBCASE(case1, a_fs_db);

    RELU6_SUBCASE(case1, a_hs_fb);
    RELU6_SUBCASE(case1, a_hs_hb);
    RELU6_SUBCASE(case1, a_hs_db);

    RELU6_SUBCASE(case1, a_ds_fb);
    RELU6_SUBCASE(case1, a_ds_hb);
    RELU6_SUBCASE(case1, a_ds_db);

    RELU6_SUBCASE(case1, a_ls_fb);
    RELU6_SUBCASE(case1, a_ls_hb);
    RELU6_SUBCASE(case1, a_ls_db);
    #endif
}

#else // NMTOOLS_BUILD_CONSTEXPR_TESTS

TEST_CASE("relu6(case1)" * doctest::test_suite("array::constexpr_relu6"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_RELU6_SUBCASE(case1, a);
    CONSTEXPR_RELU6_SUBCASE(case1, a_a);
    CONSTEXPR_RELU6_SUBCASE(case1, a_f);
    CONSTEXPR_RELU6_SUBCASE(case1, a_h);

    #else
    CONSTEXPR_RELU6_SUBCASE(case1, a_cs_fb);
    CONSTEXPR_RELU6_SUBCASE(case1, a_cs_hb);

    CONSTEXPR_RELU6_SUBCASE(case1, a_fs_fb);
    CONSTEXPR_RELU6_SUBCASE(case1, a_fs_hb);

    CONSTEXPR_RELU6_SUBCASE(case1, a_hs_fb);
    CONSTEXPR_RELU6_SUBCASE(case1, a_hs_hb);

    CONSTEXPR_RELU6_SUBCASE(case1, a_ls_fb);
    CONSTEXPR_RELU6_SUBCASE(case1, a_ls_hb);
    #endif
}

#endif