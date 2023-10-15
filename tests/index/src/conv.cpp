#include "nmtools/array/index/conv.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/utils/apply_isequal.hpp"
#include "nmtools/utils/apply_to_string.hpp"

#include "nmtools/utility/flatten_either.hpp"
#include "nmtools/testing/data/array/conv.hpp"

namespace nm = nmtools;
namespace na = nm::array;

#define RUN_shape_conv2d_impl(...) \
nm::index::shape_conv2d(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs shape_conv2d fn to callable lambda
#define RUN_shape_conv2d(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("shape_conv2d-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_shape_conv2d_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_shape_conv2d(case_name, ...) \
RUN_shape_conv2d_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define SHAPE_CONV2D_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(index, shape_conv2d, case_name); \
    using namespace args; \
    auto result = RUN_shape_conv2d(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("shape_conv2d(case1)" * doctest::test_suite("index"))
{
    SHAPE_CONV2D_SUBCASE( case1, shape, out_channels, kernel_size, stride, padding, dilations );
    SHAPE_CONV2D_SUBCASE( case1, shape_a, out_channels, kernel_size_a, stride_a, padding_a, dilations_a );
    SHAPE_CONV2D_SUBCASE( case1, shape_v, out_channels, kernel_size_v, stride_v, padding_v, dilations_v );
    SHAPE_CONV2D_SUBCASE( case1, shape_f, out_channels, kernel_size_f, stride_f, padding_f, dilations_f );
    SHAPE_CONV2D_SUBCASE( case1, shape_h, out_channels, kernel_size_h, stride_h, padding_h, dilations_h );
}

TEST_CASE("shape_conv2d(case2)" * doctest::test_suite("index"))
{
    SHAPE_CONV2D_SUBCASE( case2, shape, out_channels, kernel_size, stride, padding, dilations );
    SHAPE_CONV2D_SUBCASE( case2, shape_a, out_channels, kernel_size_a, stride_a, padding_a, dilations_a );
    SHAPE_CONV2D_SUBCASE( case2, shape_v, out_channels, kernel_size_v, stride_v, padding_v, dilations_v );
    SHAPE_CONV2D_SUBCASE( case2, shape_f, out_channels, kernel_size_f, stride_f, padding_f, dilations_f );
    SHAPE_CONV2D_SUBCASE( case2, shape_h, out_channels, kernel_size_h, stride_h, padding_h, dilations_h );
}

TEST_CASE("shape_conv2d(case3)" * doctest::test_suite("index"))
{
    SHAPE_CONV2D_SUBCASE( case3, shape, out_channels, kernel_size, stride, padding, dilations );
    SHAPE_CONV2D_SUBCASE( case3, shape_a, out_channels, kernel_size_a, stride_a, padding_a, dilations_a );
    SHAPE_CONV2D_SUBCASE( case3, shape_v, out_channels, kernel_size_v, stride_v, padding_v, dilations_v );
    SHAPE_CONV2D_SUBCASE( case3, shape_f, out_channels, kernel_size_f, stride_f, padding_f, dilations_f );
    SHAPE_CONV2D_SUBCASE( case3, shape_h, out_channels, kernel_size_h, stride_h, padding_h, dilations_h );
}

TEST_CASE("shape_conv2d(case4)" * doctest::test_suite("index"))
{
    SHAPE_CONV2D_SUBCASE( case4, shape, out_channels, kernel_size, stride, padding, dilations );
    SHAPE_CONV2D_SUBCASE( case4, shape_a, out_channels, kernel_size_a, stride_a, padding_a, dilations_a );
    SHAPE_CONV2D_SUBCASE( case4, shape_v, out_channels, kernel_size_v, stride_v, padding_v, dilations_v );
    SHAPE_CONV2D_SUBCASE( case4, shape_f, out_channels, kernel_size_f, stride_f, padding_f, dilations_f );
    SHAPE_CONV2D_SUBCASE( case4, shape_h, out_channels, kernel_size_h, stride_h, padding_h, dilations_h );
}

TEST_CASE("shape_conv2d(case5)" * doctest::test_suite("index"))
{
    SHAPE_CONV2D_SUBCASE( case5, shape, out_channels, kernel_size, stride, padding, dilations );
    SHAPE_CONV2D_SUBCASE( case5, shape_a, out_channels, kernel_size_a, stride_a, padding_a, dilations_a );
    SHAPE_CONV2D_SUBCASE( case5, shape_v, out_channels, kernel_size_v, stride_v, padding_v, dilations_v );
    SHAPE_CONV2D_SUBCASE( case5, shape_f, out_channels, kernel_size_f, stride_f, padding_f, dilations_f );
    SHAPE_CONV2D_SUBCASE( case5, shape_h, out_channels, kernel_size_h, stride_h, padding_h, dilations_h );
}

TEST_CASE("shape_conv2d(case6)" * doctest::test_suite("index"))
{
    SHAPE_CONV2D_SUBCASE( case6, shape, out_channels, kernel_size, stride, padding, dilations );
    SHAPE_CONV2D_SUBCASE( case6, shape_a, out_channels, kernel_size_a, stride_a, padding_a, dilations_a );
    SHAPE_CONV2D_SUBCASE( case6, shape_v, out_channels, kernel_size_v, stride_v, padding_v, dilations_v );
    SHAPE_CONV2D_SUBCASE( case6, shape_f, out_channels, kernel_size_f, stride_f, padding_f, dilations_f );
    SHAPE_CONV2D_SUBCASE( case6, shape_h, out_channels, kernel_size_h, stride_h, padding_h, dilations_h );
}

TEST_CASE("shape_conv2d(case7)" * doctest::test_suite("index"))
{
    SHAPE_CONV2D_SUBCASE( case7, shape, out_channels, kernel_size, stride, padding, dilations );
    SHAPE_CONV2D_SUBCASE( case7, shape_a, out_channels, kernel_size_a, stride_a, padding_a, dilations_a );
    SHAPE_CONV2D_SUBCASE( case7, shape_v, out_channels, kernel_size_v, stride_v, padding_v, dilations_v );
    SHAPE_CONV2D_SUBCASE( case7, shape_f, out_channels, kernel_size_f, stride_f, padding_f, dilations_f );
    SHAPE_CONV2D_SUBCASE( case7, shape_h, out_channels, kernel_size_h, stride_h, padding_h, dilations_h );
}

TEST_CASE("shape_conv2d(case8)" * doctest::test_suite("index"))
{
    SHAPE_CONV2D_SUBCASE( case8, shape, out_channels, kernel_size, stride, padding, dilations );
    SHAPE_CONV2D_SUBCASE( case8, shape_a, out_channels, kernel_size_a, stride_a, padding_a, dilations_a );
    SHAPE_CONV2D_SUBCASE( case8, shape_v, out_channels, kernel_size_v, stride_v, padding_v, dilations_v );
    SHAPE_CONV2D_SUBCASE( case8, shape_f, out_channels, kernel_size_f, stride_f, padding_f, dilations_f );
    SHAPE_CONV2D_SUBCASE( case8, shape_h, out_channels, kernel_size_h, stride_h, padding_h, dilations_h );
}

TEST_CASE("shape_conv2d(case9)" * doctest::test_suite("index"))
{
    SHAPE_CONV2D_SUBCASE( case9, shape, out_channels, kernel_size, stride, padding, dilations );
    SHAPE_CONV2D_SUBCASE( case9, shape_a, out_channels, kernel_size_a, stride_a, padding_a, dilations_a );
    SHAPE_CONV2D_SUBCASE( case9, shape_v, out_channels, kernel_size_v, stride_v, padding_v, dilations_v );
    SHAPE_CONV2D_SUBCASE( case9, shape_f, out_channels, kernel_size_f, stride_f, padding_f, dilations_f );
    SHAPE_CONV2D_SUBCASE( case9, shape_h, out_channels, kernel_size_h, stride_h, padding_h, dilations_h );
}

TEST_CASE("shape_conv2d(case10)" * doctest::test_suite("index"))
{
    SHAPE_CONV2D_SUBCASE( case10, shape, out_channels, kernel_size, stride, padding, dilations );
    SHAPE_CONV2D_SUBCASE( case10, shape_a, out_channels, kernel_size_a, stride_a, padding_a, dilations_a );
    SHAPE_CONV2D_SUBCASE( case10, shape_v, out_channels, kernel_size_v, stride_v, padding_v, dilations_v );
    SHAPE_CONV2D_SUBCASE( case10, shape_f, out_channels, kernel_size_f, stride_f, padding_f, dilations_f );
    SHAPE_CONV2D_SUBCASE( case10, shape_h, out_channels, kernel_size_h, stride_h, padding_h, dilations_h );
}

TEST_CASE("shape_conv2d(case11)" * doctest::test_suite("index"))
{
    SHAPE_CONV2D_SUBCASE( case11, shape, out_channels, kernel_size, stride, padding, dilations );
    SHAPE_CONV2D_SUBCASE( case11, shape_a, out_channels, kernel_size_a, stride_a, padding_a, dilations_a );
    SHAPE_CONV2D_SUBCASE( case11, shape_v, out_channels, kernel_size_v, stride_v, padding_v, dilations_v );
    SHAPE_CONV2D_SUBCASE( case11, shape_f, out_channels, kernel_size_f, stride_f, padding_f, dilations_f );
    SHAPE_CONV2D_SUBCASE( case11, shape_h, out_channels, kernel_size_h, stride_h, padding_h, dilations_h );
}

TEST_CASE("shape_conv2d(case12)" * doctest::test_suite("index"))
{
    SHAPE_CONV2D_SUBCASE( case12, shape, out_channels, kernel_size, stride, padding, dilations );
    SHAPE_CONV2D_SUBCASE( case12, shape_a, out_channels, kernel_size_a, stride_a, padding_a, dilations_a );
    SHAPE_CONV2D_SUBCASE( case12, shape_v, out_channels, kernel_size_v, stride_v, padding_v, dilations_v );
    SHAPE_CONV2D_SUBCASE( case12, shape_f, out_channels, kernel_size_f, stride_f, padding_f, dilations_f );
    SHAPE_CONV2D_SUBCASE( case12, shape_h, out_channels, kernel_size_h, stride_h, padding_h, dilations_h );
}

TEST_CASE("shape_conv2d(case13)" * doctest::test_suite("index"))
{
    SHAPE_CONV2D_SUBCASE( case13, shape, out_channels, kernel_size, stride, padding, dilations );
    SHAPE_CONV2D_SUBCASE( case13, shape_a, out_channels, kernel_size_a, stride_a, padding_a, dilations_a );
    SHAPE_CONV2D_SUBCASE( case13, shape_v, out_channels, kernel_size_v, stride_v, padding_v, dilations_v );
    SHAPE_CONV2D_SUBCASE( case13, shape_f, out_channels, kernel_size_f, stride_f, padding_f, dilations_f );
    SHAPE_CONV2D_SUBCASE( case13, shape_h, out_channels, kernel_size_h, stride_h, padding_h, dilations_h );
}

TEST_CASE("shape_conv2d(case14)" * doctest::test_suite("index"))
{
    SHAPE_CONV2D_SUBCASE( case14, shape, out_channels, kernel_size, stride, padding, dilations );
    SHAPE_CONV2D_SUBCASE( case14, shape_a, out_channels, kernel_size_a, stride_a, padding_a, dilations_a );
    SHAPE_CONV2D_SUBCASE( case14, shape_v, out_channels, kernel_size_v, stride_v, padding_v, dilations_v );
    SHAPE_CONV2D_SUBCASE( case14, shape_f, out_channels, kernel_size_f, stride_f, padding_f, dilations_f );
    SHAPE_CONV2D_SUBCASE( case14, shape_h, out_channels, kernel_size_h, stride_h, padding_h, dilations_h );
}

TEST_CASE("shape_conv2d(case15)" * doctest::test_suite("index"))
{
    SHAPE_CONV2D_SUBCASE( case15, shape, out_channels, kernel_size, stride, padding, dilations );
    SHAPE_CONV2D_SUBCASE( case15, shape_a, out_channels, kernel_size_a, stride_a, padding_a, dilations_a );
    SHAPE_CONV2D_SUBCASE( case15, shape_v, out_channels, kernel_size_v, stride_v, padding_v, dilations_v );
    SHAPE_CONV2D_SUBCASE( case15, shape_f, out_channels, kernel_size_f, stride_f, padding_f, dilations_f );
    SHAPE_CONV2D_SUBCASE( case15, shape_h, out_channels, kernel_size_h, stride_h, padding_h, dilations_h );
}

#define RUN_slice_conv2d_impl(...) \
nm::index::slice_conv2d(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs slice_conv2d fn to callable lambda
#define RUN_slice_conv2d(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("slice_conv2d-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_slice_conv2d_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_slice_conv2d(case_name, ...) \
RUN_slice_conv2d_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define SLICE_CONV2D_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(index, slice_conv2d, case_name); \
    using namespace args; \
    auto result = RUN_slice_conv2d(case_name, __VA_ARGS__); \
    for (size_t i=0; i<nm::len(result); i++) { \
        auto res = nm::at(result,i); \
        auto exp = nm::at(expect::result,i); \
        auto flat_res = nm::flatten_either(res); \
        auto flat_exp = nm::flatten_either(exp); \
        auto res_lptr = nm::get<0>(flat_res); \
        auto res_rptr = nm::get<1>(flat_res); \
        auto exp_lptr = nm::get<0>(flat_exp); \
        auto exp_rptr = nm::get<1>(flat_exp); \
        if (res_lptr && exp_lptr) { \
            NMTOOLS_ASSERT_EQUAL( *res_lptr, *exp_lptr ) \
        } else { \
            NMTOOLS_ASSERT_EQUAL( *res_rptr, *exp_rptr ) \
        } \
    } \
}

// TODO: fix flatten_either error: invalid conversion from ‘const long unsigned int*’ to ‘long unsigned int*’
#ifndef NMTOOLS_DISABLE_STL
TEST_CASE("slice_conv2d(case1)" * doctest::test_suite("index"))
{
    SLICE_CONV2D_SUBCASE( case1, indices, src_shape, kernel_size, stride, dilations );
    SLICE_CONV2D_SUBCASE( case1, indices_a, src_shape_a, kernel_size_a, stride_a, dilations_a );
    SLICE_CONV2D_SUBCASE( case1, indices_v, src_shape_v, kernel_size_v, stride_v, dilations_v );
    SLICE_CONV2D_SUBCASE( case1, indices_f, src_shape_f, kernel_size_f, stride_f, dilations_f );
    SLICE_CONV2D_SUBCASE( case1, indices_h, src_shape_h, kernel_size_h, stride_h, dilations_h );
}

TEST_CASE("slice_conv2d(case2)" * doctest::test_suite("index"))
{
    SLICE_CONV2D_SUBCASE( case2, indices, src_shape, kernel_size, stride, dilations );
    SLICE_CONV2D_SUBCASE( case2, indices_a, src_shape_a, kernel_size_a, stride_a, dilations_a );
    SLICE_CONV2D_SUBCASE( case2, indices_v, src_shape_v, kernel_size_v, stride_v, dilations_v );
    SLICE_CONV2D_SUBCASE( case2, indices_f, src_shape_f, kernel_size_f, stride_f, dilations_f );
    SLICE_CONV2D_SUBCASE( case2, indices_h, src_shape_h, kernel_size_h, stride_h, dilations_h );
}

TEST_CASE("slice_conv2d(case3)" * doctest::test_suite("index"))
{
    SLICE_CONV2D_SUBCASE( case3, indices, src_shape, kernel_size, stride, dilations );
    SLICE_CONV2D_SUBCASE( case3, indices_a, src_shape_a, kernel_size_a, stride_a, dilations_a );
    SLICE_CONV2D_SUBCASE( case3, indices_v, src_shape_v, kernel_size_v, stride_v, dilations_v );
    SLICE_CONV2D_SUBCASE( case3, indices_f, src_shape_f, kernel_size_f, stride_f, dilations_f );
    SLICE_CONV2D_SUBCASE( case3, indices_h, src_shape_h, kernel_size_h, stride_h, dilations_h );
}

TEST_CASE("slice_conv2d(case4)" * doctest::test_suite("index"))
{
    SLICE_CONV2D_SUBCASE( case4, indices, src_shape, kernel_size, stride, dilations );
    SLICE_CONV2D_SUBCASE( case4, indices_a, src_shape_a, kernel_size_a, stride_a, dilations_a );
    SLICE_CONV2D_SUBCASE( case4, indices_v, src_shape_v, kernel_size_v, stride_v, dilations_v );
    SLICE_CONV2D_SUBCASE( case4, indices_f, src_shape_f, kernel_size_f, stride_f, dilations_f );
    SLICE_CONV2D_SUBCASE( case4, indices_h, src_shape_h, kernel_size_h, stride_h, dilations_h );
}

TEST_CASE("slice_conv2d(case5)" * doctest::test_suite("index"))
{
    SLICE_CONV2D_SUBCASE( case5, indices, src_shape, kernel_size, stride, dilations );
    SLICE_CONV2D_SUBCASE( case5, indices_a, src_shape_a, kernel_size_a, stride_a, dilations_a );
    SLICE_CONV2D_SUBCASE( case5, indices_v, src_shape_v, kernel_size_v, stride_v, dilations_v );
    SLICE_CONV2D_SUBCASE( case5, indices_f, src_shape_f, kernel_size_f, stride_f, dilations_f );
    SLICE_CONV2D_SUBCASE( case5, indices_h, src_shape_h, kernel_size_h, stride_h, dilations_h );
}

TEST_CASE("slice_conv2d(case6)" * doctest::test_suite("index"))
{
    SLICE_CONV2D_SUBCASE( case6, indices, src_shape, kernel_size, stride, dilations );
    SLICE_CONV2D_SUBCASE( case6, indices_a, src_shape_a, kernel_size_a, stride_a, dilations_a );
    SLICE_CONV2D_SUBCASE( case6, indices_v, src_shape_v, kernel_size_v, stride_v, dilations_v );
    SLICE_CONV2D_SUBCASE( case6, indices_f, src_shape_f, kernel_size_f, stride_f, dilations_f );
    SLICE_CONV2D_SUBCASE( case6, indices_h, src_shape_h, kernel_size_h, stride_h, dilations_h );
}

TEST_CASE("slice_conv2d(case7)" * doctest::test_suite("index"))
{
    SLICE_CONV2D_SUBCASE( case7, indices, src_shape, kernel_size, stride, dilations );
    SLICE_CONV2D_SUBCASE( case7, indices_a, src_shape_a, kernel_size_a, stride_a, dilations_a );
    SLICE_CONV2D_SUBCASE( case7, indices_v, src_shape_v, kernel_size_v, stride_v, dilations_v );
    SLICE_CONV2D_SUBCASE( case7, indices_f, src_shape_f, kernel_size_f, stride_f, dilations_f );
    SLICE_CONV2D_SUBCASE( case7, indices_h, src_shape_h, kernel_size_h, stride_h, dilations_h );
}

TEST_CASE("slice_conv2d(case8)" * doctest::test_suite("index"))
{
    SLICE_CONV2D_SUBCASE( case8, indices, src_shape, kernel_size, stride, dilations );
    SLICE_CONV2D_SUBCASE( case8, indices_a, src_shape_a, kernel_size_a, stride_a, dilations_a );
    SLICE_CONV2D_SUBCASE( case8, indices_v, src_shape_v, kernel_size_v, stride_v, dilations_v );
    SLICE_CONV2D_SUBCASE( case8, indices_f, src_shape_f, kernel_size_f, stride_f, dilations_f );
    SLICE_CONV2D_SUBCASE( case8, indices_h, src_shape_h, kernel_size_h, stride_h, dilations_h );
}

TEST_CASE("slice_conv2d(case9)" * doctest::test_suite("index"))
{
    SLICE_CONV2D_SUBCASE( case9, indices, src_shape, kernel_size, stride, dilations );
    SLICE_CONV2D_SUBCASE( case9, indices_a, src_shape_a, kernel_size_a, stride_a, dilations_a );
    SLICE_CONV2D_SUBCASE( case9, indices_v, src_shape_v, kernel_size_v, stride_v, dilations_v );
    SLICE_CONV2D_SUBCASE( case9, indices_f, src_shape_f, kernel_size_f, stride_f, dilations_f );
    SLICE_CONV2D_SUBCASE( case9, indices_h, src_shape_h, kernel_size_h, stride_h, dilations_h );
}

TEST_CASE("slice_conv2d(case10)" * doctest::test_suite("index"))
{
    SLICE_CONV2D_SUBCASE( case10, indices, src_shape, kernel_size, stride, dilations, groups );
    SLICE_CONV2D_SUBCASE( case10, indices_a, src_shape_a, kernel_size_a, stride_a, dilations_a, groups );
    SLICE_CONV2D_SUBCASE( case10, indices_v, src_shape_v, kernel_size_v, stride_v, dilations_v, groups );
    SLICE_CONV2D_SUBCASE( case10, indices_f, src_shape_f, kernel_size_f, stride_f, dilations_f, groups );
    SLICE_CONV2D_SUBCASE( case10, indices_h, src_shape_h, kernel_size_h, stride_h, dilations_h, groups );
}

TEST_CASE("slice_conv2d(case11)" * doctest::test_suite("index"))
{
    SLICE_CONV2D_SUBCASE( case11, indices, src_shape, kernel_size, stride, dilations, groups );
    SLICE_CONV2D_SUBCASE( case11, indices_a, src_shape_a, kernel_size_a, stride_a, dilations_a, groups );
    SLICE_CONV2D_SUBCASE( case11, indices_v, src_shape_v, kernel_size_v, stride_v, dilations_v, groups );
    SLICE_CONV2D_SUBCASE( case11, indices_f, src_shape_f, kernel_size_f, stride_f, dilations_f, groups );
    SLICE_CONV2D_SUBCASE( case11, indices_h, src_shape_h, kernel_size_h, stride_h, dilations_h, groups );
}
#endif