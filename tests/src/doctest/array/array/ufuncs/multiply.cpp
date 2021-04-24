#include "nmtools/array/array/ufuncs/multiply.hpp"
#include "nmtools/testing/data/array/multiply.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;

#define RUN_multiply_impl(...) \
nm::view::multiply(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs multiply fn to callable lambda
#define RUN_multiply(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("multiply-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_multiply_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_multiply(case_name, ...) \
RUN_multiply_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define MULTIPLY_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, multiply, case_name); \
    using namespace args; \
    auto result = RUN_multiply(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("multiply(case1)" * doctest::test_suite("array::multiply"))
{
    MULTIPLY_SUBCASE( case1,   a,   b );
    MULTIPLY_SUBCASE( case1, a_a, b_a );
    MULTIPLY_SUBCASE( case1, a_v, b_v );
    MULTIPLY_SUBCASE( case1, a_f, b_f );
    MULTIPLY_SUBCASE( case1, a_d, b_d );
    MULTIPLY_SUBCASE( case1, a_h, b_h );
}

TEST_CASE("multiply(case2)" * doctest::test_suite("array::multiply"))
{
    MULTIPLY_SUBCASE( case2,   a, b );
    MULTIPLY_SUBCASE( case2, a_a, b );
    MULTIPLY_SUBCASE( case2, a_v, b );
    MULTIPLY_SUBCASE( case2, a_f, b );
    MULTIPLY_SUBCASE( case2, a_d, b );
    MULTIPLY_SUBCASE( case2, a_h, b );
}

#define RUN_reduce_multiply_impl(...) \
nm::array::multiply.reduce(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs reduce_multiply fn to callable lambda
#define RUN_reduce_multiply(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("reduce_multiply-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_reduce_multiply_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_reduce_multiply(case_name, ...) \
RUN_reduce_multiply_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define REDUCE_MULTIPLY_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, reduce_multiply, case_name); \
    using namespace args; \
    auto result = RUN_reduce_multiply(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("reduce_multiply(case1)" * doctest::test_suite("array::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case1,   a, axis );
    REDUCE_MULTIPLY_SUBCASE( case1, a_a, axis );
    REDUCE_MULTIPLY_SUBCASE( case1, a_v, axis );
    REDUCE_MULTIPLY_SUBCASE( case1, a_f, axis );
    // reduce doesnt work with dynamic ndarray for now
    // REDUCE_MULTIPLY_SUBCASE( case1, a_d, axis );
    REDUCE_MULTIPLY_SUBCASE( case1, a_h, axis );
}

TEST_CASE("reduce_multiply(case2)" * doctest::test_suite("array::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case2,   a, axis );
    REDUCE_MULTIPLY_SUBCASE( case2, a_a, axis );
    REDUCE_MULTIPLY_SUBCASE( case2, a_v, axis );
    REDUCE_MULTIPLY_SUBCASE( case2, a_f, axis );
    REDUCE_MULTIPLY_SUBCASE( case2, a_h, axis );
}

TEST_CASE("reduce_multiply(case3)" * doctest::test_suite("array::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case3,   a, axis );
    REDUCE_MULTIPLY_SUBCASE( case3, a_a, axis );
    REDUCE_MULTIPLY_SUBCASE( case3, a_v, axis );
    REDUCE_MULTIPLY_SUBCASE( case3, a_f, axis );
    REDUCE_MULTIPLY_SUBCASE( case3, a_h, axis );
}

TEST_CASE("reduce_multiply(case4)" * doctest::test_suite("array::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case4,   a, axis );
    REDUCE_MULTIPLY_SUBCASE( case4, a_a, axis );
    REDUCE_MULTIPLY_SUBCASE( case4, a_v, axis );
    REDUCE_MULTIPLY_SUBCASE( case4, a_f, axis );
    REDUCE_MULTIPLY_SUBCASE( case4, a_h, axis );
}

TEST_CASE("reduce_multiply(case5)" * doctest::test_suite("array::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case5,   a, axis );
    REDUCE_MULTIPLY_SUBCASE( case5, a_a, axis );
    REDUCE_MULTIPLY_SUBCASE( case5, a_v, axis );
    REDUCE_MULTIPLY_SUBCASE( case5, a_f, axis );
    REDUCE_MULTIPLY_SUBCASE( case5, a_h, axis );
}

TEST_CASE("reduce_multiply(case6)" * doctest::test_suite("array::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case6,   a, axis );
    REDUCE_MULTIPLY_SUBCASE( case6, a_a, axis );
    REDUCE_MULTIPLY_SUBCASE( case6, a_v, axis );
    REDUCE_MULTIPLY_SUBCASE( case6, a_f, axis );
    REDUCE_MULTIPLY_SUBCASE( case6, a_h, axis );
}

// TEST_CASE("reduce_multiply(case7)" * doctest::test_suite("array::reduce_multiply"))
// {
//     REDUCE_MULTIPLY_SUBCASE( case7,   a, axis );
//     REDUCE_MULTIPLY_SUBCASE( case7, a_a, axis );
//     REDUCE_MULTIPLY_SUBCASE( case7, a_v, axis );
//     REDUCE_MULTIPLY_SUBCASE( case7, a_f, axis );
//     REDUCE_MULTIPLY_SUBCASE( case7, a_h, axis );
// }

TEST_CASE("reduce_multiply(case8)" * doctest::test_suite("array::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case8,   a, axis, dtype, initial );
    REDUCE_MULTIPLY_SUBCASE( case8, a_a, axis, dtype, initial );
    REDUCE_MULTIPLY_SUBCASE( case8, a_v, axis, dtype, initial );
    REDUCE_MULTIPLY_SUBCASE( case8, a_f, axis, dtype, initial );
    REDUCE_MULTIPLY_SUBCASE( case8, a_h, axis, dtype, initial );
}

TEST_CASE("reduce_multiply(case9)" * doctest::test_suite("array::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case9,   a, axis, dtype, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case9, a_a, axis, dtype, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case9, a_v, axis, dtype, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case9, a_f, axis, dtype, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case9, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_multiply(case10)" * doctest::test_suite("array::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case10,   a, axis, dtype, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case10, a_a, axis, dtype, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case10, a_v, axis, dtype, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case10, a_f, axis, dtype, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case10, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_multiply(case11)" * doctest::test_suite("array::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case11,   a, axis, dtype, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case11, a_a, axis, dtype, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case11, a_v, axis, dtype, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case11, a_f, axis, dtype, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case11, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_multiply(case12)" * doctest::test_suite("array::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case12,   a, axis, dtype, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case12, a_a, axis, dtype, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case12, a_v, axis, dtype, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case12, a_f, axis, dtype, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case12, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_multiply(case13)" * doctest::test_suite("array::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case13,   a, axis, dtype, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case13, a_a, axis, dtype, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case13, a_v, axis, dtype, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case13, a_f, axis, dtype, initial, keepdims );
    REDUCE_MULTIPLY_SUBCASE( case13, a_h, axis, dtype, initial, keepdims );
}

#define RUN_accumulate_multiply_impl(...) \
nm::array::multiply.accumulate(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs accumulate_multiply fn to callable lambda
#define RUN_accumulate_multiply(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("accumulate_multiply-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_accumulate_multiply_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_accumulate_multiply(case_name, ...) \
RUN_accumulate_multiply_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define ACCUMULATE_MULTIPLY_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, accumulate_multiply, case_name); \
    using namespace args; \
    auto result = RUN_accumulate_multiply(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("accumulate_multiply(case1)" * doctest::test_suite("array::accumulate_multiply"))
{
    ACCUMULATE_MULTIPLY_SUBCASE( case1,   a, axis );
    ACCUMULATE_MULTIPLY_SUBCASE( case1, a_a, axis );
    ACCUMULATE_MULTIPLY_SUBCASE( case1, a_v, axis );
    ACCUMULATE_MULTIPLY_SUBCASE( case1, a_f, axis );
    // reduce doesnt work with dynamic ndarray for now
    // ACCUMULATE_MULTIPLY_SUBCASE( case1, a_d, axis );
    ACCUMULATE_MULTIPLY_SUBCASE( case1, a_h, axis );
}

TEST_CASE("accumulate_multiply(case2)" * doctest::test_suite("array::accumulate_multiply"))
{
    ACCUMULATE_MULTIPLY_SUBCASE( case2,   a, axis );
    ACCUMULATE_MULTIPLY_SUBCASE( case2, a_a, axis );
    ACCUMULATE_MULTIPLY_SUBCASE( case2, a_v, axis );
    ACCUMULATE_MULTIPLY_SUBCASE( case2, a_f, axis );
    // reduce doesnt work with dynamic ndarray for now
    // ACCUMULATE_MULTIPLY_SUBCASE( case2, a_d, axis );
    ACCUMULATE_MULTIPLY_SUBCASE( case2, a_h, axis );
}

TEST_CASE("accumulate_multiply(case3)" * doctest::test_suite("array::accumulate_multiply"))
{
    ACCUMULATE_MULTIPLY_SUBCASE( case3,   a, axis );
    ACCUMULATE_MULTIPLY_SUBCASE( case3, a_a, axis );
    ACCUMULATE_MULTIPLY_SUBCASE( case3, a_v, axis );
    ACCUMULATE_MULTIPLY_SUBCASE( case3, a_f, axis );
    // reduce doesnt work with dynamic ndarray for now
    // ACCUMULATE_MULTIPLY_SUBCASE( case3, a_d, axis );
    ACCUMULATE_MULTIPLY_SUBCASE( case3, a_h, axis );
}

#define RUN_outer_multiply_impl(...) \
nm::array::multiply.outer(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs outer_multiply fn to callable lambda
#define RUN_outer_multiply(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("outer_multiply-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_outer_multiply_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_outer_multiply(case_name, ...) \
RUN_outer_multiply_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define OUTER_MULTIPLY_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, outer_multiply, case_name); \
    using namespace args; \
    auto result = RUN_outer_multiply(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("outer_multiply(case1)" * doctest::test_suite("array::outer_multiply"))
{
    OUTER_MULTIPLY_SUBCASE( case1,   a,   b );
    OUTER_MULTIPLY_SUBCASE( case1, a_a, b_a );
    OUTER_MULTIPLY_SUBCASE( case1, a_v, b_v );
    OUTER_MULTIPLY_SUBCASE( case1, a_f, b_f );
    OUTER_MULTIPLY_SUBCASE( case1, a_d, b_d );
    OUTER_MULTIPLY_SUBCASE( case1, a_h, b_h );
}