#include "nmtools/array/layer_norm.hpp"
#include "nmtools/testing/data/array/layer_norm.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace view = nmtools::view;

#define LAYER_NORM_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, layer_norm, case_name); \
    using namespace args; \
    auto result = nmtools::array::layer_norm(__VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

// subtract mean part of layer norm
#define LAYER_NORM_SUBTRACT_MEAN_SUBCASE(case_name, input, axis) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, layer_norm_subtract_mean, case_name); \
    using namespace args; \
    auto result = view::subtract(input,view::mean(input,axis,nm::None,nm::True)); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("layer_norm(case1)" * doctest::test_suite("array::layer_norm"))
{
    LAYER_NORM_SUBCASE( case1, input,   weight, bias );
    LAYER_NORM_SUBCASE( case1, input_a, weight_a, bias_a );
    LAYER_NORM_SUBCASE( case1, input_f, weight_f, bias_f );
    LAYER_NORM_SUBCASE( case1, input_h, weight_h, bias_h );
    LAYER_NORM_SUBCASE( case1, input_d, weight_d, bias_d );
}

TEST_CASE("layer_norm(case2)" * doctest::test_suite("array::layer_norm"))
{
    LAYER_NORM_SUBCASE( case2, input,   weight,   bias );
    LAYER_NORM_SUBCASE( case2, input_a, weight_a, bias_a );
    LAYER_NORM_SUBCASE( case2, input_f, weight_f, bias_f );
    LAYER_NORM_SUBCASE( case2, input_h, weight_h, bias_h );
    LAYER_NORM_SUBCASE( case2, input_d, weight_d, bias_d );
}

TEST_CASE("layer_norm(case3)" * doctest::test_suite("array::layer_norm"))
{
    LAYER_NORM_SUBCASE( case3, input,   weight,   bias );
    LAYER_NORM_SUBCASE( case3, input_a, weight_a, bias_a );
    LAYER_NORM_SUBCASE( case3, input_f, weight_f, bias_f );
    LAYER_NORM_SUBCASE( case3, input_h, weight_h, bias_h );
    LAYER_NORM_SUBCASE( case3, input_d, weight_d, bias_d );
}