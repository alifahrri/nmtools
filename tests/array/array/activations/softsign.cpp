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

#include "nmtools/array/array/activations/softsign.hpp"
#include "nmtools/testing/data/array/softsign.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace array = nmtools::array;

#define RUN_softsign_impl(...) \
nm::array::softsign(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs softsign fn to callable lambda
#define RUN_softsign(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("softsign-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_softsign_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_softsign(case_name, ...) \
RUN_softsign_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define SOFTSIGN_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(activations, softsign, case_name); \
    using namespace args; \
    auto result = RUN_softsign(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("softsign(case1)" * doctest::test_suite("array::softsign"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SOFTSIGN_SUBCASE(case1, a);
    SOFTSIGN_SUBCASE(case1, a_a);
    SOFTSIGN_SUBCASE(case1, a_f);
    SOFTSIGN_SUBCASE(case1, a_h);
    SOFTSIGN_SUBCASE(case1, a_d);

    #else
    SOFTSIGN_SUBCASE(case1, a_cs_fb);
    SOFTSIGN_SUBCASE(case1, a_cs_hb);
    SOFTSIGN_SUBCASE(case1, a_cs_db);

    SOFTSIGN_SUBCASE(case1, a_fs_fb);
    SOFTSIGN_SUBCASE(case1, a_fs_hb);
    SOFTSIGN_SUBCASE(case1, a_fs_db);

    SOFTSIGN_SUBCASE(case1, a_hs_fb);
    SOFTSIGN_SUBCASE(case1, a_hs_hb);
    SOFTSIGN_SUBCASE(case1, a_hs_db);

    SOFTSIGN_SUBCASE(case1, a_ds_fb);
    SOFTSIGN_SUBCASE(case1, a_ds_hb);
    SOFTSIGN_SUBCASE(case1, a_ds_db);

    SOFTSIGN_SUBCASE(case1, a_ls_fb);
    SOFTSIGN_SUBCASE(case1, a_ls_hb);
    SOFTSIGN_SUBCASE(case1, a_ls_db);
    #endif
}