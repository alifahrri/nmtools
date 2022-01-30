#include "nmtools/testing/data/array/pooling.hpp"
#include "nmtools/array/view/pooling.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;

#define RUN_max_pool2d_impl(...) \
nm::view::max_pool2d(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs max_pool2d fn to callable lambda
#define RUN_max_pool2d(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("max_pool2d-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_max_pool2d_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_max_pool2d(case_name, ...) \
RUN_max_pool2d_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define MAX_POOL2D_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, max_pool2d, case_name); \
    using namespace args; \
    auto result = RUN_max_pool2d(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("max_pool2d(case1)" * doctest::test_suite("view::max_pool2d"))
{
    MAX_POOL2D_SUBCASE( case1, array, kernel_size, stride, ceil_mode );
    MAX_POOL2D_SUBCASE( case1, array_a, kernel_size_a, stride_a, ceil_mode );
    MAX_POOL2D_SUBCASE( case1, array_v, kernel_size_v, stride_v, ceil_mode );
    MAX_POOL2D_SUBCASE( case1, array_f, kernel_size_f, stride_f, ceil_mode );
    MAX_POOL2D_SUBCASE( case1, array_h, kernel_size_h, stride_h, ceil_mode );
}

TEST_CASE("max_pool2d(case2)" * doctest::test_suite("view::max_pool2d"))
{
    MAX_POOL2D_SUBCASE( case2, array, kernel_size, stride, ceil_mode );
    MAX_POOL2D_SUBCASE( case2, array_a, kernel_size_a, stride_a, ceil_mode );
    MAX_POOL2D_SUBCASE( case2, array_v, kernel_size_v, stride_v, ceil_mode );
    MAX_POOL2D_SUBCASE( case2, array_f, kernel_size_f, stride_f, ceil_mode );
    MAX_POOL2D_SUBCASE( case2, array_h, kernel_size_h, stride_h, ceil_mode );
}

TEST_CASE("max_pool2d(case3)" * doctest::test_suite("view::max_pool2d"))
{
    MAX_POOL2D_SUBCASE( case3, array, kernel_size, stride, ceil_mode );
    MAX_POOL2D_SUBCASE( case3, array_a, kernel_size_a, stride_a, ceil_mode );
    MAX_POOL2D_SUBCASE( case3, array_v, kernel_size_v, stride_v, ceil_mode );
    MAX_POOL2D_SUBCASE( case3, array_f, kernel_size_f, stride_f, ceil_mode );
    MAX_POOL2D_SUBCASE( case3, array_h, kernel_size_h, stride_h, ceil_mode );
}

TEST_CASE("max_pool2d(case4)" * doctest::test_suite("view::max_pool2d"))
{
    MAX_POOL2D_SUBCASE( case4, array, kernel_size, stride, ceil_mode );
    MAX_POOL2D_SUBCASE( case4, array_a, kernel_size_a, stride_a, ceil_mode );
    MAX_POOL2D_SUBCASE( case4, array_v, kernel_size_v, stride_v, ceil_mode );
    MAX_POOL2D_SUBCASE( case4, array_f, kernel_size_f, stride_f, ceil_mode );
    MAX_POOL2D_SUBCASE( case4, array_h, kernel_size_h, stride_h, ceil_mode );
}

TEST_CASE("max_pool2d(case5)" * doctest::test_suite("view::max_pool2d"))
{
    MAX_POOL2D_SUBCASE( case5, array, kernel_size, stride, ceil_mode );
    MAX_POOL2D_SUBCASE( case5, array_a, kernel_size_a, stride_a, ceil_mode );
    MAX_POOL2D_SUBCASE( case5, array_v, kernel_size_v, stride_v, ceil_mode );
    MAX_POOL2D_SUBCASE( case5, array_f, kernel_size_f, stride_f, ceil_mode );
    MAX_POOL2D_SUBCASE( case5, array_h, kernel_size_h, stride_h, ceil_mode );
}

TEST_CASE("max_pool2d(case6)" * doctest::test_suite("view::max_pool2d"))
{
    MAX_POOL2D_SUBCASE( case6, array, kernel_size, stride, ceil_mode );
    MAX_POOL2D_SUBCASE( case6, array_a, kernel_size_a, stride_a, ceil_mode );
    MAX_POOL2D_SUBCASE( case6, array_v, kernel_size_v, stride_v, ceil_mode );
    MAX_POOL2D_SUBCASE( case6, array_f, kernel_size_f, stride_f, ceil_mode );
    MAX_POOL2D_SUBCASE( case6, array_h, kernel_size_h, stride_h, ceil_mode );
}

TEST_CASE("max_pool2d(case7)" * doctest::test_suite("view::max_pool2d"))
{
    MAX_POOL2D_SUBCASE( case7, array, kernel_size, stride, ceil_mode );
    MAX_POOL2D_SUBCASE( case7, array_a, kernel_size_a, stride_a, ceil_mode );
    MAX_POOL2D_SUBCASE( case7, array_v, kernel_size_v, stride_v, ceil_mode );
    MAX_POOL2D_SUBCASE( case7, array_f, kernel_size_f, stride_f, ceil_mode );
    MAX_POOL2D_SUBCASE( case7, array_h, kernel_size_h, stride_h, ceil_mode );
}

TEST_CASE("max_pool2d(case8)" * doctest::test_suite("view::max_pool2d"))
{
    MAX_POOL2D_SUBCASE( case8, array, kernel_size, stride, ceil_mode );
    MAX_POOL2D_SUBCASE( case8, array_a, kernel_size_a, stride_a, ceil_mode );
    MAX_POOL2D_SUBCASE( case8, array_v, kernel_size_v, stride_v, ceil_mode );
    MAX_POOL2D_SUBCASE( case8, array_f, kernel_size_f, stride_f, ceil_mode );
    MAX_POOL2D_SUBCASE( case8, array_h, kernel_size_h, stride_h, ceil_mode );
}

TEST_CASE("max_pool2d(case9)" * doctest::test_suite("view::max_pool2d"))
{
    MAX_POOL2D_SUBCASE( case9, array, kernel_size, stride, ceil_mode );
    MAX_POOL2D_SUBCASE( case9, array_a, kernel_size_a, stride_a, ceil_mode );
    MAX_POOL2D_SUBCASE( case9, array_v, kernel_size_v, stride_v, ceil_mode );
    MAX_POOL2D_SUBCASE( case9, array_f, kernel_size_f, stride_f, ceil_mode );
    MAX_POOL2D_SUBCASE( case9, array_h, kernel_size_h, stride_h, ceil_mode );
}

TEST_CASE("max_pool2d(case10)" * doctest::test_suite("view::max_pool2d"))
{
    MAX_POOL2D_SUBCASE( case10, array, kernel_size, stride, ceil_mode );
    MAX_POOL2D_SUBCASE( case10, array_a, kernel_size_a, stride_a, ceil_mode );
    MAX_POOL2D_SUBCASE( case10, array_v, kernel_size_v, stride_v, ceil_mode );
    MAX_POOL2D_SUBCASE( case10, array_f, kernel_size_f, stride_f, ceil_mode );
    MAX_POOL2D_SUBCASE( case10, array_h, kernel_size_h, stride_h, ceil_mode );
}

#define RUN_avg_pool2d_impl(...) \
nm::view::avg_pool2d(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs avg_pool2d fn to callable lambda
#define RUN_avg_pool2d(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("avg_pool2d-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_avg_pool2d_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_avg_pool2d(case_name, ...) \
RUN_avg_pool2d_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define AVG_POOL2D_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, avg_pool2d, case_name); \
    using namespace args; \
    auto result = RUN_avg_pool2d(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("avg_pool2d(case1)" * doctest::test_suite("view::avg_pool2d"))
{
    AVG_POOL2D_SUBCASE( case1, array, kernel_size, stride, ceil_mode );
    AVG_POOL2D_SUBCASE( case1, array_a, kernel_size_a, stride_a, ceil_mode );
    AVG_POOL2D_SUBCASE( case1, array_v, kernel_size_v, stride_v, ceil_mode );
    AVG_POOL2D_SUBCASE( case1, array_f, kernel_size_f, stride_f, ceil_mode );
    AVG_POOL2D_SUBCASE( case1, array_h, kernel_size_h, stride_h, ceil_mode );
}

TEST_CASE("avg_pool2d(case2)" * doctest::test_suite("view::avg_pool2d"))
{
    AVG_POOL2D_SUBCASE( case2, array, kernel_size, stride, ceil_mode );
    AVG_POOL2D_SUBCASE( case2, array_a, kernel_size_a, stride_a, ceil_mode );
    AVG_POOL2D_SUBCASE( case2, array_v, kernel_size_v, stride_v, ceil_mode );
    AVG_POOL2D_SUBCASE( case2, array_f, kernel_size_f, stride_f, ceil_mode );
    AVG_POOL2D_SUBCASE( case2, array_h, kernel_size_h, stride_h, ceil_mode );
}

TEST_CASE("avg_pool2d(case3)" * doctest::test_suite("view::avg_pool2d"))
{
    AVG_POOL2D_SUBCASE( case3, array, kernel_size, stride, ceil_mode );
    AVG_POOL2D_SUBCASE( case3, array_a, kernel_size_a, stride_a, ceil_mode );
    AVG_POOL2D_SUBCASE( case3, array_v, kernel_size_v, stride_v, ceil_mode );
    AVG_POOL2D_SUBCASE( case3, array_f, kernel_size_f, stride_f, ceil_mode );
    AVG_POOL2D_SUBCASE( case3, array_h, kernel_size_h, stride_h, ceil_mode );
}

TEST_CASE("avg_pool2d(case4)" * doctest::test_suite("view::avg_pool2d"))
{
    AVG_POOL2D_SUBCASE( case4, array, kernel_size, stride, ceil_mode );
    AVG_POOL2D_SUBCASE( case4, array_a, kernel_size_a, stride_a, ceil_mode );
    AVG_POOL2D_SUBCASE( case4, array_v, kernel_size_v, stride_v, ceil_mode );
    AVG_POOL2D_SUBCASE( case4, array_f, kernel_size_f, stride_f, ceil_mode );
    AVG_POOL2D_SUBCASE( case4, array_h, kernel_size_h, stride_h, ceil_mode );
}

TEST_CASE("avg_pool2d(case5)" * doctest::test_suite("view::avg_pool2d"))
{
    AVG_POOL2D_SUBCASE( case5, array, kernel_size, stride, ceil_mode );
    AVG_POOL2D_SUBCASE( case5, array_a, kernel_size_a, stride_a, ceil_mode );
    AVG_POOL2D_SUBCASE( case5, array_v, kernel_size_v, stride_v, ceil_mode );
    AVG_POOL2D_SUBCASE( case5, array_f, kernel_size_f, stride_f, ceil_mode );
    AVG_POOL2D_SUBCASE( case5, array_h, kernel_size_h, stride_h, ceil_mode );
}

TEST_CASE("avg_pool2d(case6)" * doctest::test_suite("view::avg_pool2d"))
{
    AVG_POOL2D_SUBCASE( case6, array, kernel_size, stride, ceil_mode );
    AVG_POOL2D_SUBCASE( case6, array_a, kernel_size_a, stride_a, ceil_mode );
    AVG_POOL2D_SUBCASE( case6, array_v, kernel_size_v, stride_v, ceil_mode );
    AVG_POOL2D_SUBCASE( case6, array_f, kernel_size_f, stride_f, ceil_mode );
    AVG_POOL2D_SUBCASE( case6, array_h, kernel_size_h, stride_h, ceil_mode );
}

TEST_CASE("avg_pool2d(case7)" * doctest::test_suite("view::avg_pool2d"))
{
    AVG_POOL2D_SUBCASE( case7, array, kernel_size, stride, ceil_mode );
    AVG_POOL2D_SUBCASE( case7, array_a, kernel_size_a, stride_a, ceil_mode );
    AVG_POOL2D_SUBCASE( case7, array_v, kernel_size_v, stride_v, ceil_mode );
    AVG_POOL2D_SUBCASE( case7, array_f, kernel_size_f, stride_f, ceil_mode );
    AVG_POOL2D_SUBCASE( case7, array_h, kernel_size_h, stride_h, ceil_mode );
}


TEST_CASE("avg_pool2d(case8)" * doctest::test_suite("view::avg_pool2d"))
{
    AVG_POOL2D_SUBCASE( case8, array, kernel_size, stride, ceil_mode );
    AVG_POOL2D_SUBCASE( case8, array_a, kernel_size_a, stride_a, ceil_mode );
    AVG_POOL2D_SUBCASE( case8, array_v, kernel_size_v, stride_v, ceil_mode );
    AVG_POOL2D_SUBCASE( case8, array_f, kernel_size_f, stride_f, ceil_mode );
    AVG_POOL2D_SUBCASE( case8, array_h, kernel_size_h, stride_h, ceil_mode );
}


TEST_CASE("avg_pool2d(case9)" * doctest::test_suite("view::avg_pool2d"))
{
    AVG_POOL2D_SUBCASE( case9, array, kernel_size, stride, ceil_mode );
    AVG_POOL2D_SUBCASE( case9, array_a, kernel_size_a, stride_a, ceil_mode );
    AVG_POOL2D_SUBCASE( case9, array_v, kernel_size_v, stride_v, ceil_mode );
    AVG_POOL2D_SUBCASE( case9, array_f, kernel_size_f, stride_f, ceil_mode );
    AVG_POOL2D_SUBCASE( case9, array_h, kernel_size_h, stride_h, ceil_mode );
}


TEST_CASE("avg_pool2d(case10)" * doctest::test_suite("view::avg_pool2d"))
{
    AVG_POOL2D_SUBCASE( case10, array, kernel_size, stride, ceil_mode );
    AVG_POOL2D_SUBCASE( case10, array_a, kernel_size_a, stride_a, ceil_mode );
    AVG_POOL2D_SUBCASE( case10, array_v, kernel_size_v, stride_v, ceil_mode );
    AVG_POOL2D_SUBCASE( case10, array_f, kernel_size_f, stride_f, ceil_mode );
    AVG_POOL2D_SUBCASE( case10, array_h, kernel_size_h, stride_h, ceil_mode );
}