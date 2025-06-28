#include "nmtools/array/ufuncs/fmin.hpp"
#include "nmtools/testing/data/array/fmin.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nmtools;

#define RUN_fmin_impl(...) \
nmtools::fmin(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs fmin fn to callable lambda
#define RUN_fmin(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("fmin-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_fmin_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_fmin(case_name, ...) \
RUN_fmin_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define FMIN_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, fmin, case_name); \
    using namespace args; \
    auto result = RUN_fmin(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("fmin(case1)" * doctest::test_suite("array::fmin"))
{
    FMIN_SUBCASE( case1,   a,   b );
    FMIN_SUBCASE( case1, a_a, b_a );
    FMIN_SUBCASE( case1, a_f, b_f );
    FMIN_SUBCASE( case1, a_d, b_d );
    FMIN_SUBCASE( case1, a_h, b_h );
}

TEST_CASE("fmin(case2)" * doctest::test_suite("array::fmin"))
{
    FMIN_SUBCASE( case2,   a, b );
    FMIN_SUBCASE( case2, a_a, b );
    FMIN_SUBCASE( case2, a_f, b );
    FMIN_SUBCASE( case2, a_d, b );
    FMIN_SUBCASE( case2, a_h, b );
}

#define RUN_reduce_fmin_impl(...) \
nmtools::fmin.reduce(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs reduce_fmin fn to callable lambda
#define RUN_reduce_fmin(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("reduce_fmin-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_reduce_fmin_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_reduce_fmin(case_name, ...) \
RUN_reduce_fmin_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define REDUCE_FMIN_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, reduce_fmin, case_name); \
    using namespace args; \
    auto result = RUN_reduce_fmin(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("reduce_fmin(case1)" * doctest::test_suite("array::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case1,   a, axis );
    REDUCE_FMIN_SUBCASE( case1, a_a, axis );
    REDUCE_FMIN_SUBCASE( case1, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_FMIN_SUBCASE( case1, a_d, axis );
    REDUCE_FMIN_SUBCASE( case1, a_f, axis );
}

TEST_CASE("reduce_fmin(case2)" * doctest::test_suite("array::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case2,   a, axis );
    REDUCE_FMIN_SUBCASE( case2, a_a, axis );
    REDUCE_FMIN_SUBCASE( case2, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_FMIN_SUBCASE( case2, a_d, axis );
    REDUCE_FMIN_SUBCASE( case2, a_f, axis );
}

TEST_CASE("reduce_fmin(case3)" * doctest::test_suite("array::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case3,   a, axis );
    REDUCE_FMIN_SUBCASE( case3, a_a, axis );
    REDUCE_FMIN_SUBCASE( case3, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_FMIN_SUBCASE( case3, a_d, axis );
    REDUCE_FMIN_SUBCASE( case3, a_f, axis );
}

TEST_CASE("reduce_fmin(case4)" * doctest::test_suite("array::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case4,   a, axis );
    REDUCE_FMIN_SUBCASE( case4, a_a, axis );
    REDUCE_FMIN_SUBCASE( case4, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_FMIN_SUBCASE( case4, a_d, axis );
    REDUCE_FMIN_SUBCASE( case4, a_f, axis );
}

TEST_CASE("reduce_fmin(case5)" * doctest::test_suite("array::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case5,   a, axis );
    REDUCE_FMIN_SUBCASE( case5, a_a, axis );
    REDUCE_FMIN_SUBCASE( case5, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_FMIN_SUBCASE( case5, a_d, axis );
    REDUCE_FMIN_SUBCASE( case5, a_f, axis );
}

TEST_CASE("reduce_fmin(case6)" * doctest::test_suite("array::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case6,   a, axis );
    REDUCE_FMIN_SUBCASE( case6, a_a, axis );
    REDUCE_FMIN_SUBCASE( case6, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_FMIN_SUBCASE( case6, a_d, axis );
    REDUCE_FMIN_SUBCASE( case6, a_f, axis );
}

TEST_CASE("reduce_fmin(case7)" * doctest::test_suite("array::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case7,   a, axis, dtype, initial );
    REDUCE_FMIN_SUBCASE( case7, a_a, axis, dtype, initial );
    REDUCE_FMIN_SUBCASE( case7, a_f, axis, dtype, initial );
    REDUCE_FMIN_SUBCASE( case7, a_f, axis, dtype, initial );
}

TEST_CASE("reduce_fmin(case8)" * doctest::test_suite("array::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case8,   a, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case8, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case8, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case8, a_f, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_fmin(case9)" * doctest::test_suite("array::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case9,   a, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case9, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case9, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case9, a_f, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_fmin(case10)" * doctest::test_suite("array::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case10,   a, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case10, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case10, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case10, a_f, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_fmin(case11)" * doctest::test_suite("array::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case11,   a, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case11, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case11, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case11, a_f, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_fmin(case12)" * doctest::test_suite("array::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case12,   a, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case12, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case12, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case12, a_f, axis, dtype, initial, keepdims );
}

#define RUN_accumulate_fmin_impl(...) \
nmtools::fmin.accumulate(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs accumulate_fmin fn to callable lambda
#define RUN_accumulate_fmin(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("accumulate_fmin-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_accumulate_fmin_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_accumulate_fmin(case_name, ...) \
RUN_accumulate_fmin_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define ACCUMULATE_FMIN_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, accumulate_fmin, case_name); \
    using namespace args; \
    auto result = RUN_accumulate_fmin(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("accumulate_fmin(case1)" * doctest::test_suite("array::accumulate_fmin"))
{
    ACCUMULATE_FMIN_SUBCASE( case1,   a, axis );
    ACCUMULATE_FMIN_SUBCASE( case1, a_a, axis );
    ACCUMULATE_FMIN_SUBCASE( case1, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_FMIN_SUBCASE( case1, a_d, axis );
    ACCUMULATE_FMIN_SUBCASE( case1, a_f, axis );
}

TEST_CASE("accumulate_fmin(case2)" * doctest::test_suite("array::accumulate_fmin"))
{
    ACCUMULATE_FMIN_SUBCASE( case2,   a, axis );
    ACCUMULATE_FMIN_SUBCASE( case2, a_a, axis );
    ACCUMULATE_FMIN_SUBCASE( case2, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_FMIN_SUBCASE( case2, a_d, axis );
    ACCUMULATE_FMIN_SUBCASE( case2, a_f, axis );
}

TEST_CASE("accumulate_fmin(case3)" * doctest::test_suite("array::accumulate_fmin"))
{
    ACCUMULATE_FMIN_SUBCASE( case3,   a, axis );
    ACCUMULATE_FMIN_SUBCASE( case3, a_a, axis );
    ACCUMULATE_FMIN_SUBCASE( case3, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_FMIN_SUBCASE( case3, a_d, axis );
    ACCUMULATE_FMIN_SUBCASE( case3, a_f, axis );
}

#define RUN_outer_fmin_impl(...) \
nmtools::fmin.outer(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs outer_fmin fn to callable lambda
#define RUN_outer_fmin(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("outer_fmin-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_outer_fmin_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_outer_fmin(case_name, ...) \
RUN_outer_fmin_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define OUTER_FMIN_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, outer_fmin, case_name); \
    using namespace args; \
    auto result = RUN_outer_fmin(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("outer_fmin(case1)" * doctest::test_suite("array::outer_fmin"))
{
    OUTER_FMIN_SUBCASE( case1,   a,   b );
    OUTER_FMIN_SUBCASE( case1, a_a, b_a );
    // TODO: remove support for nested vector as ndarray
    OUTER_FMIN_SUBCASE( case1, a_f, b_f );
    OUTER_FMIN_SUBCASE( case1, a_d, b_d );
    OUTER_FMIN_SUBCASE( case1, a_h, b_h );
}