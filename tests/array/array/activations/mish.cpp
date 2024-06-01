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

#include "nmtools/array/array/activations/mish.hpp"
#include "nmtools/testing/data/array/mish.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;

#define RUN_mish_impl(...) \
nm::array::mish(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs mish fn to callable lambda
#define RUN_mish(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("mish-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_mish_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_mish(case_name, ...) \
RUN_mish_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define MISH_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(activations, mish, case_name); \
    using namespace args; \
    auto result = RUN_mish(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("mish(case1)" * doctest::test_suite("array::mish"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MISH_SUBCASE(case1, a);
    MISH_SUBCASE(case1, a_a);
    MISH_SUBCASE(case1, a_f);
    MISH_SUBCASE(case1, a_h);
    MISH_SUBCASE(case1, a_d);

    #else
    MISH_SUBCASE(case1, a_cs_fb);
    MISH_SUBCASE(case1, a_cs_hb);
    MISH_SUBCASE(case1, a_cs_db);

    MISH_SUBCASE(case1, a_fs_fb);
    MISH_SUBCASE(case1, a_fs_hb);
    MISH_SUBCASE(case1, a_fs_db);

    MISH_SUBCASE(case1, a_hs_fb);
    MISH_SUBCASE(case1, a_hs_hb);
    MISH_SUBCASE(case1, a_hs_db);

    MISH_SUBCASE(case1, a_ds_fb);
    MISH_SUBCASE(case1, a_ds_hb);
    MISH_SUBCASE(case1, a_ds_db);

    MISH_SUBCASE(case1, a_ls_fb);
    MISH_SUBCASE(case1, a_ls_hb);
    MISH_SUBCASE(case1, a_ls_db);
    #endif
}