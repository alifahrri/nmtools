#include "nmtools/array/array/instance_norm.hpp"
#include "nmtools/testing/data/array/instance_norm.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace view = nmtools::view;

#define INSTANCE_NORM_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, instance_norm, case_name); \
    using namespace args; \
    auto result = nmtools::array::instance_norm(__VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define INSTANCE_NORM_1D_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, instance_norm, case_name); \
    using namespace args; \
    auto result = nmtools::array::instance_norm_1d(__VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define INSTANCE_NORM_2D_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, instance_norm, case_name); \
    using namespace args; \
    auto result = nmtools::array::instance_norm_2d(__VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

using namespace nmtools::literals;

TEST_CASE("instance_norm(case1)" * doctest::test_suite("array::instance_norm"))
{
    INSTANCE_NORM_SUBCASE( case1, input,   weight,   bias,   2_ct );
    INSTANCE_NORM_SUBCASE( case1, input_a, weight_a, bias_a, 2_ct );
    INSTANCE_NORM_SUBCASE( case1, input_f, weight_f, bias_f, 2_ct );
    INSTANCE_NORM_SUBCASE( case1, input_h, weight_h, bias_h, 2_ct );
    INSTANCE_NORM_SUBCASE( case1, input_d, weight_d, bias_d, 2_ct );

    INSTANCE_NORM_2D_SUBCASE( case1, input,   weight,   bias );
    INSTANCE_NORM_2D_SUBCASE( case1, input_a, weight_a, bias_a );
    INSTANCE_NORM_2D_SUBCASE( case1, input_f, weight_f, bias_f );
    INSTANCE_NORM_2D_SUBCASE( case1, input_h, weight_h, bias_h );
    INSTANCE_NORM_2D_SUBCASE( case1, input_d, weight_d, bias_d );
}

TEST_CASE("instance_norm(case2)" * doctest::test_suite("array::instance_norm"))
{
    INSTANCE_NORM_SUBCASE( case2, input,   weight,   bias,   1_ct );
    INSTANCE_NORM_SUBCASE( case2, input_a, weight_a, bias_a, 1_ct );
    INSTANCE_NORM_SUBCASE( case2, input_f, weight_f, bias_f, 1_ct );
    INSTANCE_NORM_SUBCASE( case2, input_h, weight_h, bias_h, 1_ct );
    INSTANCE_NORM_SUBCASE( case2, input_d, weight_d, bias_d, 1_ct );

    INSTANCE_NORM_1D_SUBCASE( case2, input,   weight,   bias );
    INSTANCE_NORM_1D_SUBCASE( case2, input_a, weight_a, bias_a );
    INSTANCE_NORM_1D_SUBCASE( case2, input_f, weight_f, bias_f );
    INSTANCE_NORM_1D_SUBCASE( case2, input_h, weight_h, bias_h );
    INSTANCE_NORM_1D_SUBCASE( case2, input_d, weight_d, bias_d );
}