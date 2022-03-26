#include "nmtools/array/array/ufuncs/right_shift.hpp"
#include "nmtools/testing/data/array/right_shift.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;

#define RUN_right_shift_impl(...) \
nm::array::right_shift(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs right_shift fn to callable lambda
#define RUN_right_shift(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("right_shift-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_right_shift_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_right_shift(case_name, ...) \
RUN_right_shift_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define RIGHT_SHIFT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, right_shift, case_name); \
    using namespace args; \
    auto result = RUN_right_shift(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("right_shift(case1)" * doctest::test_suite("view::right_shift"))
{
    RIGHT_SHIFT_SUBCASE( case1,   a,   b );
    RIGHT_SHIFT_SUBCASE( case1, a_a, b_a );
    RIGHT_SHIFT_SUBCASE( case1, a_v, b_v );
    RIGHT_SHIFT_SUBCASE( case1, a_f, b_f );
    RIGHT_SHIFT_SUBCASE( case1, a_d, b_d );
    RIGHT_SHIFT_SUBCASE( case1, a_h, b_h );
}

TEST_CASE("right_shift(case2)" * doctest::test_suite("view::right_shift"))
{
    RIGHT_SHIFT_SUBCASE( case2,   a, b );
    RIGHT_SHIFT_SUBCASE( case2, a_a, b );
    RIGHT_SHIFT_SUBCASE( case2, a_v, b );
    RIGHT_SHIFT_SUBCASE( case2, a_f, b );
    RIGHT_SHIFT_SUBCASE( case2, a_d, b );
    RIGHT_SHIFT_SUBCASE( case2, a_h, b );
}

#define RUN_reduce_right_shift_impl(...) \
nm::array::right_shift.reduce(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs reduce_right_shift fn to callable lambda
#define RUN_reduce_right_shift(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("reduce_right_shift-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_reduce_right_shift_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_reduce_right_shift(case_name, ...) \
RUN_reduce_right_shift_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define REDUCE_RIGHT_SHIFT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, reduce_right_shift, case_name); \
    using namespace args; \
    auto result = RUN_reduce_right_shift(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("reduce_right_shift(case1)" * doctest::test_suite("array::reduce_right_shift"))
{
    REDUCE_RIGHT_SHIFT_SUBCASE( case1,   a, axis );
    REDUCE_RIGHT_SHIFT_SUBCASE( case1, a_a, axis );
    REDUCE_RIGHT_SHIFT_SUBCASE( case1, a_v, axis );
    REDUCE_RIGHT_SHIFT_SUBCASE( case1, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_RIGHT_SHIFT_SUBCASE( case1, a_d, axis );
    REDUCE_RIGHT_SHIFT_SUBCASE( case1, a_h, axis );
}

TEST_CASE("reduce_right_shift(case2)" * doctest::test_suite("array::reduce_right_shift"))
{
    REDUCE_RIGHT_SHIFT_SUBCASE( case2,   a, axis );
    REDUCE_RIGHT_SHIFT_SUBCASE( case2, a_a, axis );
    REDUCE_RIGHT_SHIFT_SUBCASE( case2, a_v, axis );
    REDUCE_RIGHT_SHIFT_SUBCASE( case2, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_RIGHT_SHIFT_SUBCASE( case2, a_d, axis );
    REDUCE_RIGHT_SHIFT_SUBCASE( case2, a_h, axis );
}

TEST_CASE("reduce_right_shift(case3)" * doctest::test_suite("array::reduce_right_shift"))
{
    REDUCE_RIGHT_SHIFT_SUBCASE( case3,   a, axis );
    REDUCE_RIGHT_SHIFT_SUBCASE( case3, a_a, axis );
    REDUCE_RIGHT_SHIFT_SUBCASE( case3, a_v, axis );
    REDUCE_RIGHT_SHIFT_SUBCASE( case3, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_RIGHT_SHIFT_SUBCASE( case3, a_d, axis );
    REDUCE_RIGHT_SHIFT_SUBCASE( case3, a_h, axis );
}

TEST_CASE("reduce_right_shift(case4)" * doctest::test_suite("array::reduce_right_shift"))
{
    REDUCE_RIGHT_SHIFT_SUBCASE( case4,   a, axis, dtype, initial );
    REDUCE_RIGHT_SHIFT_SUBCASE( case4, a_a, axis, dtype, initial );
    REDUCE_RIGHT_SHIFT_SUBCASE( case4, a_v, axis, dtype, initial );
    REDUCE_RIGHT_SHIFT_SUBCASE( case4, a_f, axis, dtype, initial );
    REDUCE_RIGHT_SHIFT_SUBCASE( case4, a_h, axis, dtype, initial );
}

TEST_CASE("reduce_right_shift(case5)" * doctest::test_suite("array::reduce_right_shift"))
{
    REDUCE_RIGHT_SHIFT_SUBCASE( case5,   a, axis, dtype, initial, keepdims );
    REDUCE_RIGHT_SHIFT_SUBCASE( case5, a_a, axis, dtype, initial, keepdims );
    REDUCE_RIGHT_SHIFT_SUBCASE( case5, a_v, axis, dtype, initial, keepdims );
    REDUCE_RIGHT_SHIFT_SUBCASE( case5, a_f, axis, dtype, initial, keepdims );
    REDUCE_RIGHT_SHIFT_SUBCASE( case5, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_right_shift(case6)" * doctest::test_suite("array::reduce_right_shift"))
{
    REDUCE_RIGHT_SHIFT_SUBCASE( case6,   a, axis, dtype, initial, keepdims );
    REDUCE_RIGHT_SHIFT_SUBCASE( case6, a_a, axis, dtype, initial, keepdims );
    REDUCE_RIGHT_SHIFT_SUBCASE( case6, a_v, axis, dtype, initial, keepdims );
    REDUCE_RIGHT_SHIFT_SUBCASE( case6, a_f, axis, dtype, initial, keepdims );
    REDUCE_RIGHT_SHIFT_SUBCASE( case6, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_right_shift(case7)" * doctest::test_suite("array::reduce_right_shift"))
{
    REDUCE_RIGHT_SHIFT_SUBCASE( case7,   a, axis, dtype, initial, keepdims );
    REDUCE_RIGHT_SHIFT_SUBCASE( case7, a_a, axis, dtype, initial, keepdims );
    REDUCE_RIGHT_SHIFT_SUBCASE( case7, a_v, axis, dtype, initial, keepdims );
    REDUCE_RIGHT_SHIFT_SUBCASE( case7, a_f, axis, dtype, initial, keepdims );
    REDUCE_RIGHT_SHIFT_SUBCASE( case7, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_right_shift(case8)" * doctest::test_suite("array::reduce_right_shift"))
{
    REDUCE_RIGHT_SHIFT_SUBCASE( case8,   a, axis, dtype, initial, keepdims );
    REDUCE_RIGHT_SHIFT_SUBCASE( case8, a_a, axis, dtype, initial, keepdims );
    REDUCE_RIGHT_SHIFT_SUBCASE( case8, a_v, axis, dtype, initial, keepdims );
    REDUCE_RIGHT_SHIFT_SUBCASE( case8, a_f, axis, dtype, initial, keepdims );
    REDUCE_RIGHT_SHIFT_SUBCASE( case8, a_h, axis, dtype, initial, keepdims );
}

#define RUN_accumulate_right_shift_impl(...) \
nm::array::right_shift.accumulate(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs accumulate_right_shift fn to callable lambda
#define RUN_accumulate_right_shift(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("accumulate_right_shift-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_accumulate_right_shift_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_accumulate_right_shift(case_name, ...) \
RUN_accumulate_right_shift_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define ACCUMULATE_RIGHT_SHIFT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, accumulate_right_shift, case_name); \
    using namespace args; \
    auto result = RUN_accumulate_right_shift(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("accumulate_right_shift(case1)" * doctest::test_suite("array::accumulate_right_shift"))
{
    ACCUMULATE_RIGHT_SHIFT_SUBCASE( case1,   a, axis );
    ACCUMULATE_RIGHT_SHIFT_SUBCASE( case1, a_a, axis );
    ACCUMULATE_RIGHT_SHIFT_SUBCASE( case1, a_v, axis );
    ACCUMULATE_RIGHT_SHIFT_SUBCASE( case1, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_RIGHT_SHIFT_SUBCASE( case1, a_d, axis );
    ACCUMULATE_RIGHT_SHIFT_SUBCASE( case1, a_h, axis );
}

TEST_CASE("accumulate_right_shift(case2)" * doctest::test_suite("array::accumulate_right_shift"))
{
    ACCUMULATE_RIGHT_SHIFT_SUBCASE( case2,   a, axis );
    ACCUMULATE_RIGHT_SHIFT_SUBCASE( case2, a_a, axis );
    ACCUMULATE_RIGHT_SHIFT_SUBCASE( case2, a_v, axis );
    ACCUMULATE_RIGHT_SHIFT_SUBCASE( case2, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_RIGHT_SHIFT_SUBCASE( case2, a_d, axis );
    ACCUMULATE_RIGHT_SHIFT_SUBCASE( case2, a_h, axis );
}

TEST_CASE("accumulate_right_shift(case3)" * doctest::test_suite("array::accumulate_right_shift"))
{
    ACCUMULATE_RIGHT_SHIFT_SUBCASE( case3,   a, axis );
    ACCUMULATE_RIGHT_SHIFT_SUBCASE( case3, a_a, axis );
    ACCUMULATE_RIGHT_SHIFT_SUBCASE( case3, a_v, axis );
    ACCUMULATE_RIGHT_SHIFT_SUBCASE( case3, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_RIGHT_SHIFT_SUBCASE( case3, a_d, axis );
    ACCUMULATE_RIGHT_SHIFT_SUBCASE( case3, a_h, axis );
}

#define RUN_outer_right_shift_impl(...) \
nm::array::right_shift.outer(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs outer_right_shift fn to callable lambda
#define RUN_outer_right_shift(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("outer_right_shift-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_outer_right_shift_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_outer_right_shift(case_name, ...) \
RUN_outer_right_shift_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define OUTER_RIGHT_SHIFT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, outer_right_shift, case_name); \
    using namespace args; \
    auto result = RUN_outer_right_shift(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("outer_right_shift(case1)" * doctest::test_suite("array::outer_right_shift"))
{
    OUTER_RIGHT_SHIFT_SUBCASE( case1,   a,   b );
    OUTER_RIGHT_SHIFT_SUBCASE( case1, a_a, b_a );
    // OUTER_RIGHT_SHIFT_SUBCASE( case1, a_v, b_v );
    OUTER_RIGHT_SHIFT_SUBCASE( case1, a_f, b_f );
    OUTER_RIGHT_SHIFT_SUBCASE( case1, a_d, b_d );
    OUTER_RIGHT_SHIFT_SUBCASE( case1, a_h, b_h );
}