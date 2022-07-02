#include "nmtools/array/array/conv.hpp"
#include "nmtools/testing/data/array/conv.hpp"
#include "nmtools/testing/doctest.hpp"

#define RUN_conv2d_impl(...) \
nmtools::array::conv2d(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nmtools::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs conv2d fn to callable lambda
#define RUN_conv2d(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("array::conv2d-") + #case_name; \
    auto name  = nmtools::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_conv2d_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_conv2d(case_name, ...) \
RUN_conv2d_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define CONV2D_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, conv2d, case_name); \
    using namespace args; \
    auto result = RUN_conv2d(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

using nmtools::None;

TEST_CASE("conv2d(case1)" * doctest::test_suite("array::conv2d"))
{
    {
        NMTOOLS_TESTING_DECLARE_NS(array, conv2d, case1);
        using namespace args;
        [[maybe_unused]] auto result = RUN_conv2d(case_name, input, weight);
    }
    CONV2D_SUBCASE( case1, input, weight );
    CONV2D_SUBCASE( case1, input_a, weight_a );
    CONV2D_SUBCASE( case1, input_f, weight_f );
    CONV2D_SUBCASE( case1, input_h, weight_h );
    CONV2D_SUBCASE( case1, input_d, weight_d );
}

TEST_CASE("conv2d(case2)" * doctest::test_suite("array::conv2d"))
{
    // CONV2D_SUBCASE( case2, input, weight );
    // CONV2D_SUBCASE( case2, input_a, weight_a );
    CONV2D_SUBCASE( case2, input_f, weight_f );
    // CONV2D_SUBCASE( case2, input_h, weight_h );
    // CONV2D_SUBCASE( case2, input_d, weight_d );
}

TEST_CASE("conv2d(case3)" * doctest::test_suite("array::conv2d"))
{
    CONV2D_SUBCASE( case3, input, weight );
    CONV2D_SUBCASE( case3, input_a, weight_a );
    CONV2D_SUBCASE( case3, input_f, weight_f );
    CONV2D_SUBCASE( case3, input_h, weight_h );
    CONV2D_SUBCASE( case3, input_d, weight_d );
}

TEST_CASE("conv2d(case4)" * doctest::test_suite("array::conv2d"))
{
    CONV2D_SUBCASE( case4, input, weight );
    CONV2D_SUBCASE( case4, input_a, weight_a );
    CONV2D_SUBCASE( case4, input_f, weight_f );
    CONV2D_SUBCASE( case4, input_h, weight_h );
    CONV2D_SUBCASE( case4, input_d, weight_d );

    CONV2D_SUBCASE( case4, input, weight, None, stride );
    CONV2D_SUBCASE( case4, input_a, weight_a, None, stride_a );
    CONV2D_SUBCASE( case4, input_f, weight_f, None, stride_f );
    CONV2D_SUBCASE( case4, input_h, weight_h, None, stride_h );
    // NOTE: stride must be index array
    // CONV2D_SUBCASE( case4, input_d, weight_d, stride_d );
    CONV2D_SUBCASE( case4, input_d, weight_d, None, stride_v );
}

TEST_CASE("conv2d(case5)" * doctest::test_suite("array::conv2d"))
{
    CONV2D_SUBCASE( case5, input, weight, None, stride );
    CONV2D_SUBCASE( case5, input_a, weight_a, None, stride_a );
    CONV2D_SUBCASE( case5, input_f, weight_f, None, stride_f );
    CONV2D_SUBCASE( case5, input_h, weight_h, None, stride_h );
    // NOTE: stride must be index array
    // CONV2D_SUBCASE( case5, input_d, weight_d, stride_d );
    CONV2D_SUBCASE( case5, input_d, weight_d, None, stride_v );
}

TEST_CASE("conv2d(case6)" * doctest::test_suite("array::conv2d"))
{
    CONV2D_SUBCASE( case6, input, weight, None, stride );
    CONV2D_SUBCASE( case6, input_a, weight_a, None, stride_a );
    CONV2D_SUBCASE( case6, input_f, weight_f, None, stride_f );
    CONV2D_SUBCASE( case6, input_h, weight_h, None, stride_h );
    CONV2D_SUBCASE( case6, input_d, weight_d, None, stride_v );
}

TEST_CASE("conv2d(case7)" * doctest::test_suite("array::conv2d"))
{
    CONV2D_SUBCASE( case7, input, weight, None, stride );
    CONV2D_SUBCASE( case7, input_a, weight_a, None, stride_a );
    CONV2D_SUBCASE( case7, input_f, weight_f, None, stride_f );
    CONV2D_SUBCASE( case7, input_h, weight_h, None, stride_h );
    CONV2D_SUBCASE( case7, input_d, weight_d, None, stride_v );
}

TEST_CASE("conv2d(case8)" * doctest::test_suite("array::conv2d"))
{
    CONV2D_SUBCASE( case8, input, weight, None, stride );
    CONV2D_SUBCASE( case8, input_a, weight_a, None, stride_a );
    CONV2D_SUBCASE( case8, input_f, weight_f, None, stride_f );
    CONV2D_SUBCASE( case8, input_h, weight_h, None, stride_h );
    CONV2D_SUBCASE( case8, input_d, weight_d, None, stride_v );
}

TEST_CASE("conv2d(case9)" * doctest::test_suite("array::conv2d"))
{
    CONV2D_SUBCASE( case9, input, weight, None, stride );
    CONV2D_SUBCASE( case9, input_a, weight_a, None, stride_a );
    CONV2D_SUBCASE( case9, input_f, weight_f, None, stride_f );
    CONV2D_SUBCASE( case9, input_h, weight_h, None, stride_h );
    CONV2D_SUBCASE( case9, input_d, weight_d, None, stride_v );
}

TEST_CASE("conv2d(case10)" * doctest::test_suite("array::conv2d"))
{
    CONV2D_SUBCASE( case10, input, weight, None, stride );
    CONV2D_SUBCASE( case10, input_a, weight_a, None, stride_a );
    CONV2D_SUBCASE( case10, input_f, weight_f, None, stride_f );
    CONV2D_SUBCASE( case10, input_h, weight_h, None, stride_h );
    CONV2D_SUBCASE( case10, input_d, weight_d, None, stride_v );
}

TEST_CASE("conv2d(case11)" * doctest::test_suite("array::conv2d"))
{
    CONV2D_SUBCASE( case11, input, weight, None, stride, padding );
    CONV2D_SUBCASE( case11, input_a, weight_a, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_f, weight_f, None, stride_f, padding_f );
    CONV2D_SUBCASE( case11, input_h, weight_h, None, stride_h, padding_h );
    CONV2D_SUBCASE( case11, input_d, weight_d, None, stride_v, padding_v );
}

TEST_CASE("conv2d(case12)" * doctest::test_suite("array::conv2d"))
{
    CONV2D_SUBCASE( case12, input, weight, None, stride, padding );
    CONV2D_SUBCASE( case12, input_a, weight_a, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_f, weight_f, None, stride_f, padding_f );
    CONV2D_SUBCASE( case12, input_h, weight_h, None, stride_h, padding_h );
    CONV2D_SUBCASE( case12, input_d, weight_d, None, stride_v, padding_v );
}

TEST_CASE("conv2d(case13)" * doctest::test_suite("array::conv2d"))
{
    CONV2D_SUBCASE( case13, input, weight, None, stride, padding );
    CONV2D_SUBCASE( case13, input_a, weight_a, None, stride, padding );
    CONV2D_SUBCASE( case13, input_f, weight_f, None, stride, padding );
    CONV2D_SUBCASE( case13, input_h, weight_h, None, stride, padding );
    CONV2D_SUBCASE( case13, input_d, weight_d, None, stride, padding );
}

TEST_CASE("conv2d(case14)" * doctest::test_suite("array::conv2d"))
{
    CONV2D_SUBCASE( case14, input, weight, None, stride, padding );
    CONV2D_SUBCASE( case14, input_a, weight_a, None, stride, padding );
    CONV2D_SUBCASE( case14, input_f, weight_f, None, stride, padding );
    CONV2D_SUBCASE( case14, input_h, weight_h, None, stride, padding );
    CONV2D_SUBCASE( case14, input_d, weight_d, None, stride, padding );
}

TEST_CASE("conv2d(case15)" * doctest::test_suite("array::conv2d"))
{
    CONV2D_SUBCASE( case15, input, weight, None, stride, padding );
    CONV2D_SUBCASE( case15, input_a, weight_a, None, stride, padding );
    CONV2D_SUBCASE( case15, input_f, weight_f, None, stride, padding );
    CONV2D_SUBCASE( case15, input_h, weight_h, None, stride, padding );
    CONV2D_SUBCASE( case15, input_d, weight_d, None, stride, padding );
}

TEST_CASE("conv2d(case16)" * doctest::test_suite("array::conv2d"))
{
    CONV2D_SUBCASE( case16, input, weight, bias, stride, padding );
    CONV2D_SUBCASE( case16, input_a, weight_a, bias_a, stride, padding );
    CONV2D_SUBCASE( case16, input_f, weight_f, bias_f, stride, padding );
    CONV2D_SUBCASE( case16, input_h, weight_h, bias_h, stride, padding );
    CONV2D_SUBCASE( case16, input_d, weight_d, bias_d, stride, padding );
}