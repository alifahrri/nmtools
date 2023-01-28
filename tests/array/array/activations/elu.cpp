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

#include "nmtools/array/array/activations/elu.hpp"
#include "nmtools/testing/data/array/elu.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;

#define RUN_elu_impl(...) \
nm::array::elu(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs elu fn to callable lambda
#define RUN_elu(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("elu-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_elu_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_elu(case_name, ...) \
RUN_elu_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define ELU_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(activations, elu, case_name); \
    using namespace args; \
    auto result = RUN_elu(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("elu(case1)" * doctest::test_suite("array::elu"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    ELU_SUBCASE(case1, a);
    ELU_SUBCASE(case1, a_a);
    ELU_SUBCASE(case1, a_f);
    ELU_SUBCASE(case1, a_h);
    ELU_SUBCASE(case1, a_d);

    #else
    ELU_SUBCASE(case1, a_cs_fb);
    ELU_SUBCASE(case1, a_cs_hb);
    ELU_SUBCASE(case1, a_cs_db);

    ELU_SUBCASE(case1, a_fs_fb);
    ELU_SUBCASE(case1, a_fs_hb);
    ELU_SUBCASE(case1, a_fs_db);

    ELU_SUBCASE(case1, a_hs_fb);
    ELU_SUBCASE(case1, a_hs_hb);
    ELU_SUBCASE(case1, a_hs_db);

    ELU_SUBCASE(case1, a_ds_fb);
    ELU_SUBCASE(case1, a_ds_hb);
    ELU_SUBCASE(case1, a_ds_db);

    ELU_SUBCASE(case1, a_ls_fb);
    ELU_SUBCASE(case1, a_ls_hb);
    ELU_SUBCASE(case1, a_ls_db);
    #endif
}

TEST_CASE("elu(case2)" * doctest::test_suite("array::elu"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    ELU_SUBCASE(case2, a, alpha);
    ELU_SUBCASE(case2, a_a, alpha);
    ELU_SUBCASE(case2, a_f, alpha);
    ELU_SUBCASE(case2, a_h, alpha);
    ELU_SUBCASE(case2, a_d, alpha);
    
    #else
    ELU_SUBCASE(case2, a_cs_fb, alpha);
    ELU_SUBCASE(case2, a_cs_hb, alpha);
    ELU_SUBCASE(case2, a_cs_db, alpha);

    ELU_SUBCASE(case2, a_fs_fb, alpha);
    ELU_SUBCASE(case2, a_fs_hb, alpha);
    ELU_SUBCASE(case2, a_fs_db, alpha);

    ELU_SUBCASE(case2, a_hs_fb, alpha);
    ELU_SUBCASE(case2, a_hs_hb, alpha);
    ELU_SUBCASE(case2, a_hs_db, alpha);

    ELU_SUBCASE(case2, a_ds_fb, alpha);
    ELU_SUBCASE(case2, a_ds_hb, alpha);
    ELU_SUBCASE(case2, a_ds_db, alpha);

    ELU_SUBCASE(case2, a_ls_fb, alpha);
    ELU_SUBCASE(case2, a_ls_hb, alpha);
    ELU_SUBCASE(case2, a_ls_db, alpha);
    #endif
}