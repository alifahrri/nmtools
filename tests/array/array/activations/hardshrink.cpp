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

#include "nmtools/array/array/activations/hardshrink.hpp"
#include "nmtools/testing/data/array/hardshrink.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;

#define RUN_hardshrink_impl(...) \
nm::array::hardshrink(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs hardshrink fn to callable lambda
#define RUN_hardshrink(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("hardshrink-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_hardshrink_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_hardshrink(case_name, ...) \
RUN_hardshrink_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define HARDSHRINK_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(activations, hardshrink, case_name); \
    using namespace args; \
    auto result = RUN_hardshrink(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("hardshrink(case1)" * doctest::test_suite("array::hardshrink"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    HARDSHRINK_SUBCASE(case1, a);
    HARDSHRINK_SUBCASE(case1, a_a);
    HARDSHRINK_SUBCASE(case1, a_f);
    HARDSHRINK_SUBCASE(case1, a_h);
    HARDSHRINK_SUBCASE(case1, a_d);

    #else
    HARDSHRINK_SUBCASE(case1, a_cs_fb);
    HARDSHRINK_SUBCASE(case1, a_cs_hb);
    HARDSHRINK_SUBCASE(case1, a_cs_db);

    HARDSHRINK_SUBCASE(case1, a_fs_fb);
    HARDSHRINK_SUBCASE(case1, a_fs_hb);
    HARDSHRINK_SUBCASE(case1, a_fs_db);

    HARDSHRINK_SUBCASE(case1, a_hs_fb);
    HARDSHRINK_SUBCASE(case1, a_hs_hb);
    HARDSHRINK_SUBCASE(case1, a_hs_db);

    HARDSHRINK_SUBCASE(case1, a_ds_fb);
    HARDSHRINK_SUBCASE(case1, a_ds_hb);
    HARDSHRINK_SUBCASE(case1, a_ds_db);

    HARDSHRINK_SUBCASE(case1, a_ls_fb);
    HARDSHRINK_SUBCASE(case1, a_ls_hb);
    HARDSHRINK_SUBCASE(case1, a_ls_db);
    #endif
}

TEST_CASE("hardshrink(case2)" * doctest::test_suite("array::hardshrink"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    HARDSHRINK_SUBCASE(case2, a, lambda);
    HARDSHRINK_SUBCASE(case2, a_a, lambda);
    HARDSHRINK_SUBCASE(case2, a_f, lambda);
    HARDSHRINK_SUBCASE(case2, a_h, lambda);
    HARDSHRINK_SUBCASE(case2, a_d, lambda);

    #else
    HARDSHRINK_SUBCASE(case2, a_cs_fb, lambda);
    HARDSHRINK_SUBCASE(case2, a_cs_hb, lambda);
    HARDSHRINK_SUBCASE(case2, a_cs_db, lambda);

    HARDSHRINK_SUBCASE(case2, a_fs_fb, lambda);
    HARDSHRINK_SUBCASE(case2, a_fs_hb, lambda);
    HARDSHRINK_SUBCASE(case2, a_fs_db, lambda);

    HARDSHRINK_SUBCASE(case2, a_hs_fb, lambda);
    HARDSHRINK_SUBCASE(case2, a_hs_hb, lambda);
    HARDSHRINK_SUBCASE(case2, a_hs_db, lambda);

    HARDSHRINK_SUBCASE(case2, a_ds_fb, lambda);
    HARDSHRINK_SUBCASE(case2, a_ds_hb, lambda);
    HARDSHRINK_SUBCASE(case2, a_ds_db, lambda);

    HARDSHRINK_SUBCASE(case2, a_ls_fb, lambda);
    HARDSHRINK_SUBCASE(case2, a_ls_hb, lambda);
    HARDSHRINK_SUBCASE(case2, a_ls_db, lambda);
    #endif
}