#include "nmtools/array/view/ufuncs/fmod.hpp"
#include "nmtools/testing/data/array/fmod.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define RUN_fmod_impl(...) \
nm::view::fmod(__VA_ARGS__);

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
    NMTOOLS_TESTING_DECLARE_NS(view, fmod, case_name); \
    using namespace args; \
    auto result = RUN_fmod(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("fmod(case1)" * doctest::test_suite("view::fmod"))
{
    FMOD_SUBCASE( case1,   a,   b );
    FMOD_SUBCASE( case1, a_a, b_a );
    FMOD_SUBCASE( case1, a_v, b_v );
    FMOD_SUBCASE( case1, a_f, b_f );
    FMOD_SUBCASE( case1, a_d, b_d );
    FMOD_SUBCASE( case1, a_h, b_h );
}

TEST_CASE("fmod(case2)" * doctest::test_suite("view::fmod"))
{
    FMOD_SUBCASE( case2,   a, b );
    FMOD_SUBCASE( case2, a_a, b );
    FMOD_SUBCASE( case2, a_v, b );
    FMOD_SUBCASE( case2, a_f, b );
    FMOD_SUBCASE( case2, a_d, b );
    FMOD_SUBCASE( case2, a_h, b );
}

#define RUN_reduce_fmod_impl(...) \
nm::view::reduce_fmod(__VA_ARGS__);

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
    NMTOOLS_TESTING_DECLARE_NS(view, reduce_fmod, case_name); \
    using namespace args; \
    auto result = RUN_reduce_fmod(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("reduce_fmod(case1)" * doctest::test_suite("view::reduce_fmod"))
{
    REDUCE_FMOD_SUBCASE( case1,   a, axis );
    REDUCE_FMOD_SUBCASE( case1, a_a, axis );
    REDUCE_FMOD_SUBCASE( case1, a_v, axis );
    REDUCE_FMOD_SUBCASE( case1, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_FMOD_SUBCASE( case1, a_d, axis );
    REDUCE_FMOD_SUBCASE( case1, a_f, axis );
}

TEST_CASE("reduce_fmod(case2)" * doctest::test_suite("view::reduce_fmod"))
{
    REDUCE_FMOD_SUBCASE( case2,   a, axis );
    REDUCE_FMOD_SUBCASE( case2, a_a, axis );
    REDUCE_FMOD_SUBCASE( case2, a_v, axis );
    REDUCE_FMOD_SUBCASE( case2, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_FMOD_SUBCASE( case2, a_d, axis );
    REDUCE_FMOD_SUBCASE( case2, a_f, axis );
}

TEST_CASE("reduce_fmod(case3)" * doctest::test_suite("view::reduce_fmod"))
{
    REDUCE_FMOD_SUBCASE( case3,   a, axis );
    REDUCE_FMOD_SUBCASE( case3, a_a, axis );
    REDUCE_FMOD_SUBCASE( case3, a_v, axis );
    REDUCE_FMOD_SUBCASE( case3, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_FMOD_SUBCASE( case3, a_d, axis );
    REDUCE_FMOD_SUBCASE( case3, a_f, axis );
}

TEST_CASE("reduce_fmod(case4)" * doctest::test_suite("view::reduce_fmod"))
{
    REDUCE_FMOD_SUBCASE( case4,   a, axis, dtype, initial );
    REDUCE_FMOD_SUBCASE( case4, a_a, axis, dtype, initial );
    REDUCE_FMOD_SUBCASE( case4, a_v, axis, dtype, initial );
    REDUCE_FMOD_SUBCASE( case4, a_f, axis, dtype, initial );
    REDUCE_FMOD_SUBCASE( case4, a_f, axis, dtype, initial );
}

TEST_CASE("reduce_fmod(case5)" * doctest::test_suite("view::reduce_fmod"))
{
    REDUCE_FMOD_SUBCASE( case5,   a, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case5, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case5, a_v, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case5, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case5, a_f, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_fmod(case6)" * doctest::test_suite("view::reduce_fmod"))
{
    REDUCE_FMOD_SUBCASE( case6,   a, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case6, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case6, a_v, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case6, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case6, a_f, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_fmod(case7)" * doctest::test_suite("view::reduce_fmod"))
{
    REDUCE_FMOD_SUBCASE( case7,   a, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case7, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case7, a_v, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case7, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case7, a_f, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_fmod(case8)" * doctest::test_suite("view::reduce_fmod"))
{
    REDUCE_FMOD_SUBCASE( case8,   a, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case8, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case8, a_v, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case8, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case8, a_f, axis, dtype, initial, keepdims );
}

#define RUN_accumulate_fmod_impl(...) \
nm::view::accumulate_fmod(__VA_ARGS__);

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
    NMTOOLS_TESTING_DECLARE_NS(view, accumulate_fmod, case_name); \
    using namespace args; \
    auto result = RUN_accumulate_fmod(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("accumulate_fmod(case1)" * doctest::test_suite("view::accumulate_fmod"))
{
    ACCUMULATE_FMOD_SUBCASE( case1,   a, axis );
    ACCUMULATE_FMOD_SUBCASE( case1, a_a, axis );
    ACCUMULATE_FMOD_SUBCASE( case1, a_v, axis );
    ACCUMULATE_FMOD_SUBCASE( case1, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_FMOD_SUBCASE( case1, a_d, axis );
    ACCUMULATE_FMOD_SUBCASE( case1, a_f, axis );
}

TEST_CASE("accumulate_fmod(case2)" * doctest::test_suite("view::accumulate_fmod"))
{
    ACCUMULATE_FMOD_SUBCASE( case2,   a, axis );
    ACCUMULATE_FMOD_SUBCASE( case2, a_a, axis );
    ACCUMULATE_FMOD_SUBCASE( case2, a_v, axis );
    ACCUMULATE_FMOD_SUBCASE( case2, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_FMOD_SUBCASE( case2, a_d, axis );
    ACCUMULATE_FMOD_SUBCASE( case2, a_f, axis );
}

TEST_CASE("accumulate_fmod(case3)" * doctest::test_suite("view::accumulate_fmod"))
{
    ACCUMULATE_FMOD_SUBCASE( case3,   a, axis );
    ACCUMULATE_FMOD_SUBCASE( case3, a_a, axis );
    ACCUMULATE_FMOD_SUBCASE( case3, a_v, axis );
    ACCUMULATE_FMOD_SUBCASE( case3, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_FMOD_SUBCASE( case3, a_d, axis );
    ACCUMULATE_FMOD_SUBCASE( case3, a_f, axis );
}

#define RUN_outer_fmod_impl(...) \
nm::view::outer_fmod(__VA_ARGS__);

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
    NMTOOLS_TESTING_DECLARE_NS(view, outer_fmod, case_name); \
    using namespace args; \
    auto result = RUN_outer_fmod(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("outer_fmod(case1)" * doctest::test_suite("view::outer_fmod"))
{
    OUTER_FMOD_SUBCASE( case1,   a,   b );
    OUTER_FMOD_SUBCASE( case1, a_a, b_a );
    OUTER_FMOD_SUBCASE( case1, a_v, b_v );
    OUTER_FMOD_SUBCASE( case1, a_f, b_f );
    OUTER_FMOD_SUBCASE( case1, a_d, b_d );
    OUTER_FMOD_SUBCASE( case1, a_h, b_h );
}