#include "nmtools/array/array/ufuncs/fmod.hpp"
#include "nmtools/testing/data/array/fmod.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;

#define RUN_fmod_impl(...) \
nm::array::fmod(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs fmod fn to callable lambda
#define RUN_fmod(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("fmod-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_fmod_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_fmod(case_name, ...) \
RUN_fmod_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define FMOD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, fmod, case_name); \
    using namespace args; \
    auto result = RUN_fmod(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("fmod(case1)" * doctest::test_suite("array::fmod"))
{
    FMOD_SUBCASE( case1,   a,   b );
    FMOD_SUBCASE( case1, a_a, b_a );
    FMOD_SUBCASE( case1, a_f, b_f );
    FMOD_SUBCASE( case1, a_d, b_d );
    FMOD_SUBCASE( case1, a_h, b_h );
}

TEST_CASE("fmod(case2)" * doctest::test_suite("array::fmod"))
{
    FMOD_SUBCASE( case2,   a, b );
    FMOD_SUBCASE( case2, a_a, b );
    FMOD_SUBCASE( case2, a_f, b );
    FMOD_SUBCASE( case2, a_d, b );
    FMOD_SUBCASE( case2, a_h, b );
}

#define RUN_reduce_fmod_impl(...) \
nm::array::fmod.reduce(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs reduce_fmod fn to callable lambda
#define RUN_reduce_fmod(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("reduce_fmod-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_reduce_fmod_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_reduce_fmod(case_name, ...) \
RUN_reduce_fmod_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define REDUCE_FMOD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, reduce_fmod, case_name); \
    using namespace args; \
    auto result = RUN_reduce_fmod(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("reduce_fmod(case1)" * doctest::test_suite("array::reduce_fmod"))
{
    REDUCE_FMOD_SUBCASE( case1,   a, axis );
    REDUCE_FMOD_SUBCASE( case1, a_a, axis );
    REDUCE_FMOD_SUBCASE( case1, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_FMOD_SUBCASE( case1, a_d, axis );
    REDUCE_FMOD_SUBCASE( case1, a_f, axis );
}

TEST_CASE("reduce_fmod(case2)" * doctest::test_suite("array::reduce_fmod"))
{
    REDUCE_FMOD_SUBCASE( case2,   a, axis );
    REDUCE_FMOD_SUBCASE( case2, a_a, axis );
    REDUCE_FMOD_SUBCASE( case2, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_FMOD_SUBCASE( case2, a_d, axis );
    REDUCE_FMOD_SUBCASE( case2, a_f, axis );
}

TEST_CASE("reduce_fmod(case3)" * doctest::test_suite("array::reduce_fmod"))
{
    REDUCE_FMOD_SUBCASE( case3,   a, axis );
    REDUCE_FMOD_SUBCASE( case3, a_a, axis );
    REDUCE_FMOD_SUBCASE( case3, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_FMOD_SUBCASE( case3, a_d, axis );
    REDUCE_FMOD_SUBCASE( case3, a_f, axis );
}

TEST_CASE("reduce_fmod(case4)" * doctest::test_suite("array::reduce_fmod"))
{
    REDUCE_FMOD_SUBCASE( case4,   a, axis, dtype, initial );
    REDUCE_FMOD_SUBCASE( case4, a_a, axis, dtype, initial );
    REDUCE_FMOD_SUBCASE( case4, a_f, axis, dtype, initial );
    REDUCE_FMOD_SUBCASE( case4, a_f, axis, dtype, initial );
}

TEST_CASE("reduce_fmod(case5)" * doctest::test_suite("array::reduce_fmod"))
{
    REDUCE_FMOD_SUBCASE( case5,   a, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case5, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case5, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case5, a_f, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_fmod(case6)" * doctest::test_suite("array::reduce_fmod"))
{
    REDUCE_FMOD_SUBCASE( case6,   a, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case6, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case6, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case6, a_f, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_fmod(case7)" * doctest::test_suite("array::reduce_fmod"))
{
    REDUCE_FMOD_SUBCASE( case7,   a, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case7, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case7, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case7, a_f, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_fmod(case8)" * doctest::test_suite("array::reduce_fmod"))
{
    REDUCE_FMOD_SUBCASE( case8,   a, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case8, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case8, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case8, a_f, axis, dtype, initial, keepdims );
}

#define RUN_accumulate_fmod_impl(...) \
nm::array::fmod.accumulate(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs accumulate_fmod fn to callable lambda
#define RUN_accumulate_fmod(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("accumulate_fmod-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_accumulate_fmod_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_accumulate_fmod(case_name, ...) \
RUN_accumulate_fmod_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define ACCUMULATE_FMOD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, accumulate_fmod, case_name); \
    using namespace args; \
    auto result = RUN_accumulate_fmod(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("accumulate_fmod(case1)" * doctest::test_suite("array::accumulate_fmod"))
{
    ACCUMULATE_FMOD_SUBCASE( case1,   a, axis );
    ACCUMULATE_FMOD_SUBCASE( case1, a_a, axis );
    ACCUMULATE_FMOD_SUBCASE( case1, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_FMOD_SUBCASE( case1, a_d, axis );
    ACCUMULATE_FMOD_SUBCASE( case1, a_f, axis );
}

TEST_CASE("accumulate_fmod(case2)" * doctest::test_suite("array::accumulate_fmod"))
{
    ACCUMULATE_FMOD_SUBCASE( case2,   a, axis );
    ACCUMULATE_FMOD_SUBCASE( case2, a_a, axis );
    ACCUMULATE_FMOD_SUBCASE( case2, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_FMOD_SUBCASE( case2, a_d, axis );
    ACCUMULATE_FMOD_SUBCASE( case2, a_f, axis );
}

TEST_CASE("accumulate_fmod(case3)" * doctest::test_suite("array::accumulate_fmod"))
{
    ACCUMULATE_FMOD_SUBCASE( case3,   a, axis );
    ACCUMULATE_FMOD_SUBCASE( case3, a_a, axis );
    ACCUMULATE_FMOD_SUBCASE( case3, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_FMOD_SUBCASE( case3, a_d, axis );
    ACCUMULATE_FMOD_SUBCASE( case3, a_f, axis );
}

#define RUN_outer_fmod_impl(...) \
nm::array::fmod.outer(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs outer_fmod fn to callable lambda
#define RUN_outer_fmod(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("outer_fmod-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_outer_fmod_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_outer_fmod(case_name, ...) \
RUN_outer_fmod_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define OUTER_FMOD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, outer_fmod, case_name); \
    using namespace args; \
    auto result = RUN_outer_fmod(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("outer_fmod(case1)" * doctest::test_suite("array::outer_fmod"))
{
    OUTER_FMOD_SUBCASE( case1,   a,   b );
    OUTER_FMOD_SUBCASE( case1, a_a, b_a );
    // TODO: remove support for nested vector as ndarray
    OUTER_FMOD_SUBCASE( case1, a_f, b_f );
    OUTER_FMOD_SUBCASE( case1, a_d, b_d );
    OUTER_FMOD_SUBCASE( case1, a_h, b_h );
}