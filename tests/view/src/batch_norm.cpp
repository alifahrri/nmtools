#if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
#define NMTOOLS_CAST_ARRAYS_EXTRA(name) \
inline auto name##_cs_fb = nmtools::cast(name, nmtools::kind::ndarray_cs_fb); \
inline auto name##_cs_hb = nmtools::cast(name, nmtools::kind::ndarray_cs_hb); \
inline auto name##_cs_db = nmtools::cast(name, nmtools::kind::ndarray_cs_db); \
inline auto name##_fs_fb = nmtools::cast(name, nmtools::kind::ndarray_fs_fb); \
inline auto name##_fs_hb = nmtools::cast(name, nmtools::kind::ndarray_fs_hb); \
inline auto name##_fs_db = nmtools::cast(name, nmtools::kind::ndarray_fs_db); \
inline auto name##_hs_fb = nmtools::cast(name, nmtools::kind::ndarray_hs_fb); \
inline auto name##_hs_hb = nmtools::cast(name, nmtools::kind::ndarray_hs_hb); \
inline auto name##_hs_db = nmtools::cast(name, nmtools::kind::ndarray_hs_db); \
inline auto name##_ds_fb = nmtools::cast(name, nmtools::kind::ndarray_ds_fb); \
inline auto name##_ds_hb = nmtools::cast(name, nmtools::kind::ndarray_ds_hb); \
inline auto name##_ds_db = nmtools::cast(name, nmtools::kind::ndarray_ds_db);
#endif

#include "nmtools/array/batch_norm.hpp"
#include "nmtools/testing/data/array/batch_norm.hpp"
#include "nmtools/testing/doctest.hpp"

// TODO: improve precision
#undef NMTOOLS_TESTING_PRECISION
#define NMTOOLS_TESTING_PRECISION (1e-4)

#define RUN_batch_norm_impl(...) \
nmtools::view::batch_norm(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nmtools::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs batch_norm fn to callable lambda
#define RUN_batch_norm(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("view::batch_norm-") + #case_name; \
    auto name  = nmtools::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_batch_norm_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_batch_norm(case_name, ...) \
RUN_batch_norm_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define BATCH_NORM_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, batch_norm, case_name); \
    using namespace args; \
    auto result = RUN_batch_norm(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("batch_norm(case1)" * doctest::test_suite("view::batch_norm"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    BATCH_NORM_SUBCASE( case1, input, mean, var, weight, bias );
    BATCH_NORM_SUBCASE( case1, input_a, mean_a, var_a, weight_a, bias_a );
    BATCH_NORM_SUBCASE( case1, input_f, mean_f, var_f, weight_f, bias_f );
    // TODO: fix compilation
    // BATCH_NORM_SUBCASE( case1, input_h, mean_h, var_h, weight_h, bias_h );
    // BATCH_NORM_SUBCASE( case1, input_d, mean_d, var_d, weight_d, bias_d );

    #else
    BATCH_NORM_SUBCASE( case1, input_cs_fb, mean_cs_fb, var_cs_fb, weight_cs_fb, bias_cs_fb );
    BATCH_NORM_SUBCASE( case1, input_cs_hb, mean_cs_hb, var_cs_hb, weight_cs_hb, bias_cs_hb );
    BATCH_NORM_SUBCASE( case1, input_cs_db, mean_cs_db, var_cs_db, weight_cs_db, bias_cs_db );

    BATCH_NORM_SUBCASE( case1, input_fs_fb, mean_fs_fb, var_fs_fb, weight_fs_fb, bias_fs_fb );
    BATCH_NORM_SUBCASE( case1, input_fs_hb, mean_fs_hb, var_fs_hb, weight_fs_hb, bias_fs_hb );
    BATCH_NORM_SUBCASE( case1, input_fs_db, mean_fs_db, var_fs_db, weight_fs_db, bias_fs_db );

    BATCH_NORM_SUBCASE( case1, input_hs_fb, mean_hs_fb, var_hs_fb, weight_hs_fb, bias_hs_fb );
    BATCH_NORM_SUBCASE( case1, input_hs_hb, mean_hs_hb, var_hs_hb, weight_hs_hb, bias_hs_hb );
    BATCH_NORM_SUBCASE( case1, input_hs_db, mean_hs_db, var_hs_db, weight_hs_db, bias_hs_db );

    BATCH_NORM_SUBCASE( case1, input_ds_fb, mean_ds_fb, var_ds_fb, weight_ds_fb, bias_ds_fb );
    BATCH_NORM_SUBCASE( case1, input_ds_hb, mean_ds_hb, var_ds_hb, weight_ds_hb, bias_ds_hb );
    BATCH_NORM_SUBCASE( case1, input_ds_db, mean_ds_db, var_ds_db, weight_ds_db, bias_ds_db );


    BATCH_NORM_SUBCASE( case1, input_cs_fb, mean_fs_fb, var_cs_fb, weight_cs_fb, bias_cs_fb );
    BATCH_NORM_SUBCASE( case1, input_cs_hb, mean_fs_hb, var_cs_hb, weight_cs_hb, bias_cs_hb );
    BATCH_NORM_SUBCASE( case1, input_cs_db, mean_fs_db, var_cs_db, weight_cs_db, bias_cs_db );

    BATCH_NORM_SUBCASE( case1, input_hs_fb, mean_fs_fb, var_hs_fb, weight_hs_fb, bias_hs_fb );
    BATCH_NORM_SUBCASE( case1, input_hs_hb, mean_fs_hb, var_hs_hb, weight_hs_hb, bias_hs_hb );
    BATCH_NORM_SUBCASE( case1, input_hs_db, mean_fs_db, var_hs_db, weight_hs_db, bias_hs_db );

    BATCH_NORM_SUBCASE( case1, input_ds_fb, mean_fs_fb, var_ds_fb, weight_ds_fb, bias_ds_fb );
    BATCH_NORM_SUBCASE( case1, input_ds_hb, mean_fs_hb, var_ds_hb, weight_ds_hb, bias_ds_hb );
    BATCH_NORM_SUBCASE( case1, input_ds_db, mean_fs_db, var_ds_db, weight_ds_db, bias_ds_db );


    BATCH_NORM_SUBCASE( case1, input_cs_fb, mean_hs_fb, var_cs_fb, weight_cs_fb, bias_cs_fb );
    BATCH_NORM_SUBCASE( case1, input_cs_hb, mean_hs_hb, var_cs_hb, weight_cs_hb, bias_cs_hb );
    BATCH_NORM_SUBCASE( case1, input_cs_db, mean_hs_db, var_cs_db, weight_cs_db, bias_cs_db );

    BATCH_NORM_SUBCASE( case1, input_fs_fb, mean_hs_fb, var_fs_fb, weight_fs_fb, bias_fs_fb );
    BATCH_NORM_SUBCASE( case1, input_fs_hb, mean_hs_hb, var_fs_hb, weight_fs_hb, bias_fs_hb );
    BATCH_NORM_SUBCASE( case1, input_fs_db, mean_hs_db, var_fs_db, weight_fs_db, bias_fs_db );

    BATCH_NORM_SUBCASE( case1, input_ds_fb, mean_hs_fb, var_ds_fb, weight_ds_fb, bias_ds_fb );
    BATCH_NORM_SUBCASE( case1, input_ds_hb, mean_hs_hb, var_ds_hb, weight_ds_hb, bias_ds_hb );
    BATCH_NORM_SUBCASE( case1, input_ds_db, mean_hs_db, var_ds_db, weight_ds_db, bias_ds_db );

    BATCH_NORM_SUBCASE( case1, input_cs_fb, mean_ds_fb, var_cs_fb, weight_cs_fb, bias_cs_fb );
    BATCH_NORM_SUBCASE( case1, input_cs_hb, mean_ds_hb, var_cs_hb, weight_cs_hb, bias_cs_hb );
    BATCH_NORM_SUBCASE( case1, input_cs_db, mean_ds_db, var_cs_db, weight_cs_db, bias_cs_db );

    BATCH_NORM_SUBCASE( case1, input_fs_fb, mean_ds_fb, var_fs_fb, weight_fs_fb, bias_fs_fb );
    BATCH_NORM_SUBCASE( case1, input_fs_hb, mean_ds_hb, var_fs_hb, weight_fs_hb, bias_fs_hb );
    BATCH_NORM_SUBCASE( case1, input_fs_db, mean_ds_db, var_fs_db, weight_fs_db, bias_fs_db );

    BATCH_NORM_SUBCASE( case1, input_hs_fb, mean_ds_fb, var_hs_fb, weight_hs_fb, bias_hs_fb );
    BATCH_NORM_SUBCASE( case1, input_hs_hb, mean_ds_hb, var_hs_hb, weight_hs_hb, bias_hs_hb );
    BATCH_NORM_SUBCASE( case1, input_hs_db, mean_ds_db, var_hs_db, weight_hs_db, bias_hs_db );


    BATCH_NORM_SUBCASE( case1, input_cs_fb, mean_fs_fb, var_cs_fb, weight_hs_fb, bias_ds_fb );
    BATCH_NORM_SUBCASE( case1, input_cs_hb, mean_fs_hb, var_cs_hb, weight_hs_hb, bias_ds_hb );
    BATCH_NORM_SUBCASE( case1, input_cs_db, mean_fs_db, var_cs_db, weight_hs_db, bias_ds_db );

    BATCH_NORM_SUBCASE( case1, input_hs_fb, mean_fs_fb, var_cs_fb, weight_hs_fb, bias_ds_fb );
    BATCH_NORM_SUBCASE( case1, input_hs_hb, mean_fs_hb, var_cs_hb, weight_hs_hb, bias_ds_hb );
    BATCH_NORM_SUBCASE( case1, input_hs_db, mean_fs_db, var_cs_db, weight_hs_db, bias_ds_db );

    BATCH_NORM_SUBCASE( case1, input_ds_fb, mean_fs_fb, var_cs_fb, weight_hs_fb, bias_ds_fb );
    BATCH_NORM_SUBCASE( case1, input_ds_hb, mean_fs_hb, var_cs_hb, weight_hs_hb, bias_ds_hb );
    BATCH_NORM_SUBCASE( case1, input_ds_db, mean_fs_db, var_cs_db, weight_hs_db, bias_ds_db );
    #endif
}

TEST_CASE("batch_norm(case2)" * doctest::test_suite("view::batch_norm"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    BATCH_NORM_SUBCASE( case2, input, mean, var, weight, bias );
    BATCH_NORM_SUBCASE( case2, input_a, mean_a, var_a, weight_a, bias_a );
    BATCH_NORM_SUBCASE( case2, input_f, mean_f, var_f, weight_f, bias_f );
    // TODO: fix compilation
    // BATCH_NORM_SUBCASE( case2, input_h, mean_h, var_h, weight_h, bias_h );
    // BATCH_NORM_SUBCASE( case2, input_d, mean_d, var_d, weight_d, bias_d );

    #else
    BATCH_NORM_SUBCASE( case2, input_cs_fb, mean_cs_fb, var_cs_fb, weight_cs_fb, bias_cs_fb );
    BATCH_NORM_SUBCASE( case2, input_cs_hb, mean_cs_hb, var_cs_hb, weight_cs_hb, bias_cs_hb );
    BATCH_NORM_SUBCASE( case2, input_cs_db, mean_cs_db, var_cs_db, weight_cs_db, bias_cs_db );

    BATCH_NORM_SUBCASE( case2, input_fs_fb, mean_fs_fb, var_fs_fb, weight_fs_fb, bias_fs_fb );
    BATCH_NORM_SUBCASE( case2, input_fs_hb, mean_fs_hb, var_fs_hb, weight_fs_hb, bias_fs_hb );
    BATCH_NORM_SUBCASE( case2, input_fs_db, mean_fs_db, var_fs_db, weight_fs_db, bias_fs_db );

    BATCH_NORM_SUBCASE( case2, input_hs_fb, mean_hs_fb, var_hs_fb, weight_hs_fb, bias_hs_fb );
    BATCH_NORM_SUBCASE( case2, input_hs_hb, mean_hs_hb, var_hs_hb, weight_hs_hb, bias_hs_hb );
    BATCH_NORM_SUBCASE( case2, input_hs_db, mean_hs_db, var_hs_db, weight_hs_db, bias_hs_db );

    BATCH_NORM_SUBCASE( case2, input_ds_fb, mean_ds_fb, var_ds_fb, weight_ds_fb, bias_ds_fb );
    BATCH_NORM_SUBCASE( case2, input_ds_hb, mean_ds_hb, var_ds_hb, weight_ds_hb, bias_ds_hb );
    BATCH_NORM_SUBCASE( case2, input_ds_db, mean_ds_db, var_ds_db, weight_ds_db, bias_ds_db );


    BATCH_NORM_SUBCASE( case2, input_cs_fb, mean_fs_fb, var_cs_fb, weight_cs_fb, bias_cs_fb );
    BATCH_NORM_SUBCASE( case2, input_cs_hb, mean_fs_hb, var_cs_hb, weight_cs_hb, bias_cs_hb );
    BATCH_NORM_SUBCASE( case2, input_cs_db, mean_fs_db, var_cs_db, weight_cs_db, bias_cs_db );

    BATCH_NORM_SUBCASE( case2, input_hs_fb, mean_fs_fb, var_hs_fb, weight_hs_fb, bias_hs_fb );
    BATCH_NORM_SUBCASE( case2, input_hs_hb, mean_fs_hb, var_hs_hb, weight_hs_hb, bias_hs_hb );
    BATCH_NORM_SUBCASE( case2, input_hs_db, mean_fs_db, var_hs_db, weight_hs_db, bias_hs_db );

    BATCH_NORM_SUBCASE( case2, input_ds_fb, mean_fs_fb, var_ds_fb, weight_ds_fb, bias_ds_fb );
    BATCH_NORM_SUBCASE( case2, input_ds_hb, mean_fs_hb, var_ds_hb, weight_ds_hb, bias_ds_hb );
    BATCH_NORM_SUBCASE( case2, input_ds_db, mean_fs_db, var_ds_db, weight_ds_db, bias_ds_db );


    BATCH_NORM_SUBCASE( case2, input_cs_fb, mean_hs_fb, var_cs_fb, weight_cs_fb, bias_cs_fb );
    BATCH_NORM_SUBCASE( case2, input_cs_hb, mean_hs_hb, var_cs_hb, weight_cs_hb, bias_cs_hb );
    BATCH_NORM_SUBCASE( case2, input_cs_db, mean_hs_db, var_cs_db, weight_cs_db, bias_cs_db );

    BATCH_NORM_SUBCASE( case2, input_fs_fb, mean_hs_fb, var_fs_fb, weight_fs_fb, bias_fs_fb );
    BATCH_NORM_SUBCASE( case2, input_fs_hb, mean_hs_hb, var_fs_hb, weight_fs_hb, bias_fs_hb );
    BATCH_NORM_SUBCASE( case2, input_fs_db, mean_hs_db, var_fs_db, weight_fs_db, bias_fs_db );

    BATCH_NORM_SUBCASE( case2, input_ds_fb, mean_hs_fb, var_ds_fb, weight_ds_fb, bias_ds_fb );
    BATCH_NORM_SUBCASE( case2, input_ds_hb, mean_hs_hb, var_ds_hb, weight_ds_hb, bias_ds_hb );
    BATCH_NORM_SUBCASE( case2, input_ds_db, mean_hs_db, var_ds_db, weight_ds_db, bias_ds_db );

    BATCH_NORM_SUBCASE( case2, input_cs_fb, mean_ds_fb, var_cs_fb, weight_cs_fb, bias_cs_fb );
    BATCH_NORM_SUBCASE( case2, input_cs_hb, mean_ds_hb, var_cs_hb, weight_cs_hb, bias_cs_hb );
    BATCH_NORM_SUBCASE( case2, input_cs_db, mean_ds_db, var_cs_db, weight_cs_db, bias_cs_db );

    BATCH_NORM_SUBCASE( case2, input_fs_fb, mean_ds_fb, var_fs_fb, weight_fs_fb, bias_fs_fb );
    BATCH_NORM_SUBCASE( case2, input_fs_hb, mean_ds_hb, var_fs_hb, weight_fs_hb, bias_fs_hb );
    BATCH_NORM_SUBCASE( case2, input_fs_db, mean_ds_db, var_fs_db, weight_fs_db, bias_fs_db );

    BATCH_NORM_SUBCASE( case2, input_hs_fb, mean_ds_fb, var_hs_fb, weight_hs_fb, bias_hs_fb );
    BATCH_NORM_SUBCASE( case2, input_hs_hb, mean_ds_hb, var_hs_hb, weight_hs_hb, bias_hs_hb );
    BATCH_NORM_SUBCASE( case2, input_hs_db, mean_ds_db, var_hs_db, weight_hs_db, bias_hs_db );


    BATCH_NORM_SUBCASE( case2, input_cs_fb, mean_fs_fb, var_cs_fb, weight_hs_fb, bias_ds_fb );
    BATCH_NORM_SUBCASE( case2, input_cs_hb, mean_fs_hb, var_cs_hb, weight_hs_hb, bias_ds_hb );
    BATCH_NORM_SUBCASE( case2, input_cs_db, mean_fs_db, var_cs_db, weight_hs_db, bias_ds_db );

    BATCH_NORM_SUBCASE( case2, input_hs_fb, mean_fs_fb, var_cs_fb, weight_hs_fb, bias_ds_fb );
    BATCH_NORM_SUBCASE( case2, input_hs_hb, mean_fs_hb, var_cs_hb, weight_hs_hb, bias_ds_hb );
    BATCH_NORM_SUBCASE( case2, input_hs_db, mean_fs_db, var_cs_db, weight_hs_db, bias_ds_db );

    BATCH_NORM_SUBCASE( case2, input_ds_fb, mean_fs_fb, var_cs_fb, weight_hs_fb, bias_ds_fb );
    BATCH_NORM_SUBCASE( case2, input_ds_hb, mean_fs_hb, var_cs_hb, weight_hs_hb, bias_ds_hb );
    BATCH_NORM_SUBCASE( case2, input_ds_db, mean_fs_db, var_cs_db, weight_hs_db, bias_ds_db );
    #endif
}