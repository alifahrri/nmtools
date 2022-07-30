#include "nmtools/array/view/ufuncs/minimum.hpp"
#include "nmtools/testing/data/array/minimum.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>
#include <algorithm> // std::min

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define RUN_minimum_impl(...) \
nm::view::minimum(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs minimum fn to callable lambda
#define RUN_minimum(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("minimum-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_minimum_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_minimum(case_name, ...) \
RUN_minimum_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define MINIMUM_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, minimum, case_name); \
    using namespace args; \
    auto result = RUN_minimum(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("minimum(case1)" * doctest::test_suite("view::minimum"))
{
    MINIMUM_SUBCASE( case1,   a,   b );
    MINIMUM_SUBCASE( case1, a_a, b_a );
    MINIMUM_SUBCASE( case1, a_f, b_f );
    MINIMUM_SUBCASE( case1, a_d, b_d );
    MINIMUM_SUBCASE( case1, a_h, b_h );
}

TEST_CASE("minimum(case2)" * doctest::test_suite("view::minimum"))
{
    MINIMUM_SUBCASE( case2,   a, b );
    MINIMUM_SUBCASE( case2, a_a, b );
    MINIMUM_SUBCASE( case2, a_f, b );
    MINIMUM_SUBCASE( case2, a_d, b );
    MINIMUM_SUBCASE( case2, a_h, b );
}

#define MINIMUM_FIXED_SHAPE_SUBCASE(subcase_name, expected_shape, ...) \
SUBCASE(#subcase_name) \
{ \
    auto result = RUN_minimum(subcase_name, __VA_ARGS__); \
    using result_t = decltype(result); \
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, result_t ); \
    NMTOOLS_STATIC_ASSERT_EQUAL( meta::fixed_ndarray_shape_v<result_t>, expected_shape ); \
}

TEST_CASE("minimum(fixed_shape)" * doctest::test_suite("view::minimum"))
{
    namespace meta = nmtools::meta;
    {
        int A[1][3] = {{1,2,3}};
        int B[3][1] = {{4},{5},{6}};
        constexpr auto expected_shape = std::array{3,3};
        MINIMUM_FIXED_SHAPE_SUBCASE( raw, expected_shape, A, B );
    }
    {
        auto A = std::array{1,2,3};
        auto B = std::array{std::array{4,5,6}};
        constexpr auto expected_shape = std::array{3};
        MINIMUM_FIXED_SHAPE_SUBCASE( array, expected_shape, A, B );
    }
    {
        auto A = na::fixed_ndarray{{1,2,3}};
        auto B = na::fixed_ndarray{{{1,2,3},{4,5,6}}};
        constexpr auto expected_shape = std::array{2,3};
        MINIMUM_FIXED_SHAPE_SUBCASE( fixed_ndarray, expected_shape, A, B );
    }
}

#define RUN_reduce_minimum_impl(...) \
nm::view::reduce_minimum(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs reduce_minimum fn to callable lambda
#define RUN_reduce_minimum(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("reduce_minimum-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_reduce_minimum_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_reduce_minimum(case_name, ...) \
RUN_reduce_minimum_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define REDUCE_MINIMUM_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, reduce_minimum, case_name); \
    using namespace args; \
    auto result = RUN_reduce_minimum(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("reduce_minimum(case1)" * doctest::test_suite("view::reduce_minimum"))
{
    REDUCE_MINIMUM_SUBCASE( case1,   a, axis );
    REDUCE_MINIMUM_SUBCASE( case1, a_a, axis );
    REDUCE_MINIMUM_SUBCASE( case1, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_MINIMUM_SUBCASE( case1, a_d, axis );
    REDUCE_MINIMUM_SUBCASE( case1, a_h, axis );
}

TEST_CASE("reduce_minimum(case2)" * doctest::test_suite("view::reduce_minimum"))
{
    REDUCE_MINIMUM_SUBCASE( case2,   a, axis );
    REDUCE_MINIMUM_SUBCASE( case2, a_a, axis );
    REDUCE_MINIMUM_SUBCASE( case2, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_MINIMUM_SUBCASE( case2, a_d, axis );
    REDUCE_MINIMUM_SUBCASE( case2, a_h, axis );
}

TEST_CASE("reduce_minimum(case3)" * doctest::test_suite("view::reduce_minimum"))
{
    REDUCE_MINIMUM_SUBCASE( case3,   a, axis );
    REDUCE_MINIMUM_SUBCASE( case3, a_a, axis );
    REDUCE_MINIMUM_SUBCASE( case3, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_MINIMUM_SUBCASE( case3, a_d, axis );
    REDUCE_MINIMUM_SUBCASE( case3, a_h, axis );
}

TEST_CASE("reduce_minimum(case4)" * doctest::test_suite("view::reduce_minimum"))
{
    REDUCE_MINIMUM_SUBCASE( case4,   a, axis );
    REDUCE_MINIMUM_SUBCASE( case4, a_a, axis );
    REDUCE_MINIMUM_SUBCASE( case4, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_MINIMUM_SUBCASE( case4, a_d, axis );
    REDUCE_MINIMUM_SUBCASE( case4, a_h, axis );
}

TEST_CASE("reduce_minimum(case5)" * doctest::test_suite("view::reduce_minimum"))
{
    REDUCE_MINIMUM_SUBCASE( case5,   a, axis );
    REDUCE_MINIMUM_SUBCASE( case5, a_a, axis );
    REDUCE_MINIMUM_SUBCASE( case5, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_MINIMUM_SUBCASE( case5, a_d, axis );
    REDUCE_MINIMUM_SUBCASE( case5, a_h, axis );
}

TEST_CASE("reduce_minimum(case6)" * doctest::test_suite("view::reduce_minimum"))
{
    REDUCE_MINIMUM_SUBCASE( case6,   a, axis );
    REDUCE_MINIMUM_SUBCASE( case6, a_a, axis );
    REDUCE_MINIMUM_SUBCASE( case6, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_MINIMUM_SUBCASE( case6, a_d, axis );
    REDUCE_MINIMUM_SUBCASE( case6, a_h, axis );
}

TEST_CASE("reduce_minimum(case7)" * doctest::test_suite("view::reduce_minimum"))
{
    REDUCE_MINIMUM_SUBCASE( case7,   a, axis, dtype, initial );
    REDUCE_MINIMUM_SUBCASE( case7, a_a, axis, dtype, initial );
    REDUCE_MINIMUM_SUBCASE( case7, a_f, axis, dtype, initial );
    REDUCE_MINIMUM_SUBCASE( case7, a_h, axis, dtype, initial );
}

TEST_CASE("reduce_minimum(case8)" * doctest::test_suite("view::reduce_minimum"))
{
    REDUCE_MINIMUM_SUBCASE( case8,   a, axis, dtype, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case8, a_a, axis, dtype, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case8, a_f, axis, dtype, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case8, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_minimum(case9)" * doctest::test_suite("view::reduce_minimum"))
{
    REDUCE_MINIMUM_SUBCASE( case9,   a, axis, dtype, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case9, a_a, axis, dtype, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case9, a_f, axis, dtype, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case9, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_minimum(case10)" * doctest::test_suite("view::reduce_minimum"))
{
    REDUCE_MINIMUM_SUBCASE( case10,   a, axis, dtype, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case10, a_a, axis, dtype, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case10, a_f, axis, dtype, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case10, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_minimum(case11)" * doctest::test_suite("view::reduce_minimum"))
{
    REDUCE_MINIMUM_SUBCASE( case11,   a, axis, dtype, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case11, a_a, axis, dtype, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case11, a_f, axis, dtype, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case11, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_minimum(case12)" * doctest::test_suite("view::reduce_minimum"))
{
    REDUCE_MINIMUM_SUBCASE( case12,   a, axis, dtype, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case12, a_a, axis, dtype, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case12, a_f, axis, dtype, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case12, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_minimum(case13)" * doctest::test_suite("view::reduce_minimum"))
{
    REDUCE_MINIMUM_SUBCASE( case13,   a, axis );
    REDUCE_MINIMUM_SUBCASE( case13, a_a, axis );
    REDUCE_MINIMUM_SUBCASE( case13, a_f, axis );
    REDUCE_MINIMUM_SUBCASE( case13, a_h, axis );
}

TEST_CASE("reduce_minimum(case14)" * doctest::test_suite("view::reduce_minimum"))
{
    REDUCE_MINIMUM_SUBCASE( case14,   a, axis, nm::None, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case14, a_a, axis, nm::None, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case14, a_f, axis, nm::None, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case14, a_h, axis, nm::None, initial, keepdims );
}

TEST_CASE("reduce_minimum(case15)" * doctest::test_suite("view::reduce_minimum"))
{
    REDUCE_MINIMUM_SUBCASE( case15,   a, axis, nm::None, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case15, a_a, axis, nm::None, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case15, a_f, axis, nm::None, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case15, a_h, axis, nm::None, initial, keepdims );
}

TEST_CASE("reduce_minimum(case16)" * doctest::test_suite("view::reduce_minimum"))
{
    REDUCE_MINIMUM_SUBCASE( case16,   a, axis, nm::None, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case16, a_a, axis, nm::None, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case16, a_f, axis, nm::None, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case16, a_h, axis, nm::None, initial, keepdims );
}

TEST_CASE("reduce_minimum(case17)" * doctest::test_suite("view::reduce_minimum"))
{
    REDUCE_MINIMUM_SUBCASE( case17,   a, axis, nm::None, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case17, a_a, axis, nm::None, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case17, a_f, axis, nm::None, initial, keepdims );
    REDUCE_MINIMUM_SUBCASE( case17, a_h, axis, nm::None, initial, keepdims );
}

#define RUN_accumulate_minimum_impl(...) \
nm::view::accumulate_minimum(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs accumulate_minimum fn to callable lambda
#define RUN_accumulate_minimum(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("accumulate_minimum-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_accumulate_minimum_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_accumulate_minimum(case_name, ...) \
RUN_accumulate_minimum_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define ACCUMULATE_MINIMUM_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, accumulate_minimum, case_name); \
    using namespace args; \
    auto result = RUN_accumulate_minimum(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("accumulate_minimum(case1)" * doctest::test_suite("view::accumulate_minimum"))
{
    ACCUMULATE_MINIMUM_SUBCASE( case1,   a, axis );
    ACCUMULATE_MINIMUM_SUBCASE( case1, a_a, axis );
    ACCUMULATE_MINIMUM_SUBCASE( case1, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_MINIMUM_SUBCASE( case1, a_d, axis );
    ACCUMULATE_MINIMUM_SUBCASE( case1, a_f, axis );
}

TEST_CASE("accumulate_minimum(case2)" * doctest::test_suite("view::accumulate_minimum"))
{
    ACCUMULATE_MINIMUM_SUBCASE( case2,   a, axis );
    ACCUMULATE_MINIMUM_SUBCASE( case2, a_a, axis );
    ACCUMULATE_MINIMUM_SUBCASE( case2, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_MINIMUM_SUBCASE( case2, a_d, axis );
    ACCUMULATE_MINIMUM_SUBCASE( case2, a_f, axis );
}

TEST_CASE("accumulate_minimum(case3)" * doctest::test_suite("view::accumulate_minimum"))
{
    ACCUMULATE_MINIMUM_SUBCASE( case3,   a, axis );
    ACCUMULATE_MINIMUM_SUBCASE( case3, a_a, axis );
    ACCUMULATE_MINIMUM_SUBCASE( case3, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_MINIMUM_SUBCASE( case3, a_d, axis );
    ACCUMULATE_MINIMUM_SUBCASE( case3, a_f, axis );
}

#define RUN_outer_minimum_impl(...) \
nm::view::outer_minimum(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs outer_minimum fn to callable lambda
#define RUN_outer_minimum(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("outer_minimum-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_outer_minimum_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_outer_minimum(case_name, ...) \
RUN_outer_minimum_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define OUTER_MINIMUM_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, outer_minimum, case_name); \
    using namespace args; \
    auto result = RUN_outer_minimum(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("outer_minimum(case1)" * doctest::test_suite("view::outer_minimum"))
{
    OUTER_MINIMUM_SUBCASE( case1,   a,   b );
    OUTER_MINIMUM_SUBCASE( case1, a_a, b_a );
    OUTER_MINIMUM_SUBCASE( case1, a_f, b_f );
    OUTER_MINIMUM_SUBCASE( case1, a_d, b_d );
    OUTER_MINIMUM_SUBCASE( case1, a_h, b_h );
}