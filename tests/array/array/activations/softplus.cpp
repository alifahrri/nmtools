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

#include "nmtools/array/activations/softplus.hpp"
#include "nmtools/testing/data/array/softplus.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;

#define RUN_softplus_impl(...) \
nm::array::softplus(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs softplus fn to callable lambda
#define RUN_softplus(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("softplus-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_softplus_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_softplus(case_name, ...) \
RUN_softplus_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define SOFTPLUS_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(activations, softplus, case_name); \
    using namespace args; \
    auto result = RUN_softplus(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("softplus(case1)" * doctest::test_suite("array::softplus"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SOFTPLUS_SUBCASE(case1, a);
    SOFTPLUS_SUBCASE(case1, a_a);
    SOFTPLUS_SUBCASE(case1, a_f);
    SOFTPLUS_SUBCASE(case1, a_h);
    SOFTPLUS_SUBCASE(case1, a_d);

    #else
    SOFTPLUS_SUBCASE(case1, a_cs_fb);
    SOFTPLUS_SUBCASE(case1, a_cs_hb);
    SOFTPLUS_SUBCASE(case1, a_cs_db);

    SOFTPLUS_SUBCASE(case1, a_fs_fb);
    SOFTPLUS_SUBCASE(case1, a_fs_hb);
    SOFTPLUS_SUBCASE(case1, a_fs_db);

    SOFTPLUS_SUBCASE(case1, a_hs_fb);
    SOFTPLUS_SUBCASE(case1, a_hs_hb);
    SOFTPLUS_SUBCASE(case1, a_hs_db);

    SOFTPLUS_SUBCASE(case1, a_ds_fb);
    SOFTPLUS_SUBCASE(case1, a_ds_hb);
    SOFTPLUS_SUBCASE(case1, a_ds_db);

    SOFTPLUS_SUBCASE(case1, a_ls_fb);
    SOFTPLUS_SUBCASE(case1, a_ls_hb);
    SOFTPLUS_SUBCASE(case1, a_ls_db);
    #endif
}