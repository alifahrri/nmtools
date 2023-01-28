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

#include "nmtools/array/array/activations/celu.hpp"
#include "nmtools/testing/data/array/celu.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;

#define RUN_celu_impl(...) \
nm::array::celu(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs celu fn to callable lambda
#define RUN_celu(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("celu-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_celu_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_celu(case_name, ...) \
RUN_celu_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define CELU_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(activations, celu, case_name); \
    using namespace args; \
    auto result = RUN_celu(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("celu(case1)" * doctest::test_suite("array::celu"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CELU_SUBCASE(case1, a);
    CELU_SUBCASE(case1, a_a);
    CELU_SUBCASE(case1, a_f);
    CELU_SUBCASE(case1, a_h);
    CELU_SUBCASE(case1, a_d);

    #else
    CELU_SUBCASE(case1, a_cs_fb);
    CELU_SUBCASE(case1, a_cs_hb);
    CELU_SUBCASE(case1, a_cs_db);

    CELU_SUBCASE(case1, a_fs_fb);
    CELU_SUBCASE(case1, a_fs_hb);
    CELU_SUBCASE(case1, a_fs_db);

    CELU_SUBCASE(case1, a_hs_fb);
    CELU_SUBCASE(case1, a_hs_hb);
    CELU_SUBCASE(case1, a_hs_db);

    CELU_SUBCASE(case1, a_ds_fb);
    CELU_SUBCASE(case1, a_ds_hb);
    CELU_SUBCASE(case1, a_ds_db);

    CELU_SUBCASE(case1, a_ls_fb);
    CELU_SUBCASE(case1, a_ls_hb);
    CELU_SUBCASE(case1, a_ls_db);
    #endif
}

TEST_CASE("celu(case2)" * doctest::test_suite("array::celu"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CELU_SUBCASE(case2, a, alpha);
    CELU_SUBCASE(case2, a_a, alpha);
    CELU_SUBCASE(case2, a_f, alpha);
    CELU_SUBCASE(case2, a_h, alpha);
    CELU_SUBCASE(case2, a_d, alpha);

    #else
    CELU_SUBCASE(case2, a_cs_fb, alpha);
    CELU_SUBCASE(case2, a_cs_hb, alpha);
    CELU_SUBCASE(case2, a_cs_db, alpha);

    CELU_SUBCASE(case2, a_fs_fb, alpha);
    CELU_SUBCASE(case2, a_fs_hb, alpha);
    CELU_SUBCASE(case2, a_fs_db, alpha);

    CELU_SUBCASE(case2, a_hs_fb, alpha);
    CELU_SUBCASE(case2, a_hs_hb, alpha);
    CELU_SUBCASE(case2, a_hs_db, alpha);

    CELU_SUBCASE(case2, a_ds_fb, alpha);
    CELU_SUBCASE(case2, a_ds_hb, alpha);
    CELU_SUBCASE(case2, a_ds_db, alpha);

    CELU_SUBCASE(case2, a_ls_fb, alpha);
    CELU_SUBCASE(case2, a_ls_hb, alpha);
    CELU_SUBCASE(case2, a_ls_db, alpha);
    #endif
}