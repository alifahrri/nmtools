#include "nmtools/array/batch_norm.hpp"
#include "nmtools/testing/data/array/batch_norm.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/context/default.hpp"

// TODO: improve precision
#undef NMTOOLS_TESTING_PRECISION
#define NMTOOLS_TESTING_PRECISION (1e-4)

#define BATCH_NORM_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, batch_norm, case_name); \
    using namespace args; \
    auto result = nmtools::batch_norm(__VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("batch_norm(case1)" * doctest::test_suite("array::batch_norm"))
{
    BATCH_NORM_SUBCASE( case1, input, mean, var, weight, bias );
    BATCH_NORM_SUBCASE( case1, input_a, mean_a, var_a, weight_a, bias_a );
    BATCH_NORM_SUBCASE( case1, input_f, mean_f, var_f, weight_f, bias_f );
    BATCH_NORM_SUBCASE( case1, input_h, mean_h, var_h, weight_h, bias_h );
    BATCH_NORM_SUBCASE( case1, input_d, mean_d, var_d, weight_d, bias_d );
}

TEST_CASE("batch_norm(case2)" * doctest::test_suite("array::batch_norm"))
{
    BATCH_NORM_SUBCASE( case2, input, mean, var, weight, bias );
    BATCH_NORM_SUBCASE( case2, input_a, mean_a, var_a, weight_a, bias_a );
    BATCH_NORM_SUBCASE( case2, input_f, mean_f, var_f, weight_f, bias_f );
    BATCH_NORM_SUBCASE( case2, input_h, mean_h, var_h, weight_h, bias_h );
    BATCH_NORM_SUBCASE( case2, input_d, mean_d, var_d, weight_d, bias_d );
}