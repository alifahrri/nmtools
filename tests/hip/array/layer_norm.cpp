#include "nmtools/evaluator/hip.hpp"
#include "nmtools/array/layer_norm.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/testing/data/array/layer_norm.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools::array;
namespace fn = nmtools::functional;
namespace meta = nm::meta;
namespace view = nmtools::view;

// TODO: fix to accept maybe type
using nmtools_array, nmtools_tuple, nmtools::unwrap;

#define HIP_TEST(fn,...) \
{ \
    auto expect = na::fn(__VA_ARGS__); \
    auto result = na::fn(__VA_ARGS__,na::hip::default_context()); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

#define HIP_LINEAR_TEST(fun,...) \
{ \
    auto ctx = na::hip::default_context(); \
    auto expect = na::fun(__VA_ARGS__); \
    auto view   = view::fun(__VA_ARGS__); \
    auto result = ctx->eval(view); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

#define LAYER_NORM_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, layer_norm, case_name); \
    using namespace args; \
    auto result = nmtools::array::layer_norm(__VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

// infinite loop?
#if 1
TEST_CASE("layer_norm(case1)" * doctest::test_suite("array::layer_norm"))
{
    auto gen   = na::random_engine();
    auto dtype = nm::float32;

    auto input = na::random(array{1,5,2,2},dtype,gen);
    auto weight = na::random(array{5,2,2},dtype,gen);
    auto bias = na::random(array{5,2,2},dtype,gen);

    HIP_LINEAR_TEST(layer_norm,input,weight,bias);
}
#endif

#if 0

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

#endif