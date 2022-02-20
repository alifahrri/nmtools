#include "nmtools/array/view/batch_norm.hpp"
#include "nmtools/testing/data/array/batch_norm.hpp"
#include "nmtools/testing/doctest.hpp"

// TODO: improve precision
#undef NMTOOLS_TESTING_OUTPUT_PRECISION
#define NMTOOLS_TESTING_OUTPUT_PRECISION (1e-4)

#define RUN_batch_norm_impl(...) \
nmtools::view::batch_norm(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
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
    NMTOOLS_TESTING_DECLARE_NS(array, batch_norm, case_name); \
    using namespace args; \
    auto result = RUN_batch_norm(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("batch_norm(case1)" * doctest::test_suite("view::batch_norm"))
{
    BATCH_NORM_SUBCASE( case1, input, mean, var, weight, bias );
    BATCH_NORM_SUBCASE( case1, input_a, mean_a, var_a, weight_a, bias_a );
    BATCH_NORM_SUBCASE( case1, input_f, mean_f, var_f, weight_f, bias_f );
    BATCH_NORM_SUBCASE( case1, input_h, mean_h, var_h, weight_h, bias_h );
    BATCH_NORM_SUBCASE( case1, input_d, mean_d, var_d, weight_d, bias_d );
}

TEST_CASE("batch_norm(case2)" * doctest::test_suite("view::batch_norm"))
{
    BATCH_NORM_SUBCASE( case2, input, mean, var, weight, bias );
    BATCH_NORM_SUBCASE( case2, input_a, mean_a, var_a, weight_a, bias_a );
    BATCH_NORM_SUBCASE( case2, input_f, mean_f, var_f, weight_f, bias_f );
    BATCH_NORM_SUBCASE( case2, input_h, mean_h, var_h, weight_h, bias_h );
    BATCH_NORM_SUBCASE( case2, input_d, mean_d, var_d, weight_d, bias_d );
}