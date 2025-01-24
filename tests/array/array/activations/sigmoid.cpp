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

#include "nmtools/array/activations/sigmoid.hpp"
#include "nmtools/testing/data/array/sigmoid.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;

#define RUN_sigmoid_impl(...) \
nm::array::sigmoid(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs sigmoid fn to callable lambda
#define RUN_sigmoid(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("sigmoid-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_sigmoid_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_sigmoid(case_name, ...) \
RUN_sigmoid_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define SIGMOID_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(activations, sigmoid, case_name); \
    using namespace args; \
    auto result = RUN_sigmoid(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("sigmoid(case1)" * doctest::test_suite("array::sigmoid"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SIGMOID_SUBCASE(case1, a);
    SIGMOID_SUBCASE(case1, a_a);
    SIGMOID_SUBCASE(case1, a_f);
    SIGMOID_SUBCASE(case1, a_h);
    SIGMOID_SUBCASE(case1, a_d);

    #else
    SIGMOID_SUBCASE(case1, a_cs_fb);
    SIGMOID_SUBCASE(case1, a_cs_hb);
    SIGMOID_SUBCASE(case1, a_cs_db);

    SIGMOID_SUBCASE(case1, a_fs_fb);
    SIGMOID_SUBCASE(case1, a_fs_hb);
    SIGMOID_SUBCASE(case1, a_fs_db);

    SIGMOID_SUBCASE(case1, a_hs_fb);
    SIGMOID_SUBCASE(case1, a_hs_hb);
    SIGMOID_SUBCASE(case1, a_hs_db);

    SIGMOID_SUBCASE(case1, a_ds_fb);
    SIGMOID_SUBCASE(case1, a_ds_hb);
    SIGMOID_SUBCASE(case1, a_ds_db);

    SIGMOID_SUBCASE(case1, a_ls_fb);
    SIGMOID_SUBCASE(case1, a_ls_hb);
    SIGMOID_SUBCASE(case1, a_ls_db);
    #endif
}