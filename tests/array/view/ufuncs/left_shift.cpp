#include "nmtools/array/view/ufuncs/left_shift.hpp"
#include "nmtools/testing/data/array/left_shift.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define RUN_left_shift_impl(...) \
nm::view::left_shift(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs left_shift fn to callable lambda
#define RUN_left_shift(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("left_shift-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_left_shift_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_left_shift(case_name, ...) \
RUN_left_shift_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define LEFT_SHIFT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, left_shift, case_name); \
    using namespace args; \
    auto result = RUN_left_shift(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("left_shift(case1)" * doctest::test_suite("view::left_shift"))
{
    LEFT_SHIFT_SUBCASE( case1,   a,   b );
    LEFT_SHIFT_SUBCASE( case1, a_a, b_a );
    LEFT_SHIFT_SUBCASE( case1, a_f, b_f );
    LEFT_SHIFT_SUBCASE( case1, a_d, b_d );
    LEFT_SHIFT_SUBCASE( case1, a_h, b_h );
}

TEST_CASE("left_shift(case2)" * doctest::test_suite("view::left_shift"))
{
    LEFT_SHIFT_SUBCASE( case2,   a, b );
    LEFT_SHIFT_SUBCASE( case2, a_a, b );
    LEFT_SHIFT_SUBCASE( case2, a_f, b );
    LEFT_SHIFT_SUBCASE( case2, a_d, b );
    LEFT_SHIFT_SUBCASE( case2, a_h, b );
}

#define LEFT_SHIFT_FIXED_SHAPE_SUBCASE(subcase_name, expected_shape, ...) \
SUBCASE(#subcase_name) \
{ \
    auto result = RUN_left_shift(subcase_name, __VA_ARGS__); \
    using result_t = decltype(result); \
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, result_t ); \
    NMTOOLS_STATIC_ASSERT_EQUAL( meta::fixed_ndarray_shape_v<result_t>, expected_shape ); \
}

// TODO: fix
#if 0
TEST_CASE("left_shift(fixed_shape)" * doctest::test_suite("view::left_shift"))
{
    namespace meta = nmtools::meta;
    {
        int A[1][3] = {{1,2,3}};
        int B[3][1] = {{4},{5},{6}};
        constexpr auto expected_shape = std::array{3,3};
        LEFT_SHIFT_FIXED_SHAPE_SUBCASE( raw, expected_shape, A, B );
    }
    {
        auto A = std::array{1,2,3};
        auto B = std::array{std::array{4,5,6}};
        constexpr auto expected_shape = std::array{3};
        LEFT_SHIFT_FIXED_SHAPE_SUBCASE( array, expected_shape, A, B );
    }
    {
        auto A = na::fixed_ndarray{{1,2,3}};
        auto B = na::fixed_ndarray{{{1,2,3},{4,5,6}}};
        constexpr auto expected_shape = std::array{2,3};
        LEFT_SHIFT_FIXED_SHAPE_SUBCASE( fixed_ndarray, expected_shape, A, B );
    }
}
#endif

#define RUN_reduce_left_shift_impl(...) \
nm::view::reduce_left_shift(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs reduce_left_shift fn to callable lambda
#define RUN_reduce_left_shift(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("reduce_left_shift-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_reduce_left_shift_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_reduce_left_shift(case_name, ...) \
RUN_reduce_left_shift_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define REDUCE_LEFT_SHIFT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, reduce_left_shift, case_name); \
    using namespace args; \
    auto result = RUN_reduce_left_shift(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("reduce_left_shift(case1)" * doctest::test_suite("view::reduce_left_shift"))
{
    REDUCE_LEFT_SHIFT_SUBCASE( case1,   a, axis );
    REDUCE_LEFT_SHIFT_SUBCASE( case1, a_a, axis );
    REDUCE_LEFT_SHIFT_SUBCASE( case1, a_f, axis );
    REDUCE_LEFT_SHIFT_SUBCASE( case1, a_h, axis );
    // dynamic dim array not supported yet
    // REDUCE_LEFT_SHIFT_SUBCASE( case1, a_d, axis );
}

TEST_CASE("reduce_left_shift(case2)" * doctest::test_suite("view::reduce_left_shift"))
{
    REDUCE_LEFT_SHIFT_SUBCASE( case2,   a, axis );
    REDUCE_LEFT_SHIFT_SUBCASE( case2, a_a, axis );
    REDUCE_LEFT_SHIFT_SUBCASE( case2, a_f, axis );
    REDUCE_LEFT_SHIFT_SUBCASE( case2, a_h, axis );
    // dynamic dim array not supported yet
    // REDUCE_LEFT_SHIFT_SUBCASE( case2, a_d, axis );
}

TEST_CASE("reduce_left_shift(case3)" * doctest::test_suite("view::reduce_left_shift"))
{
    REDUCE_LEFT_SHIFT_SUBCASE( case3,   a, axis );
    REDUCE_LEFT_SHIFT_SUBCASE( case3, a_a, axis );
    REDUCE_LEFT_SHIFT_SUBCASE( case3, a_f, axis );
    REDUCE_LEFT_SHIFT_SUBCASE( case3, a_h, axis );
    // dynamic dim array not supported yet
    // REDUCE_LEFT_SHIFT_SUBCASE( case3, a_d, axis );
}

TEST_CASE("reduce_left_shift(case4)" * doctest::test_suite("view::reduce_left_shift"))
{
    REDUCE_LEFT_SHIFT_SUBCASE( case4,   a, axis, dtype );
    REDUCE_LEFT_SHIFT_SUBCASE( case4, a_a, axis, dtype );
    REDUCE_LEFT_SHIFT_SUBCASE( case4, a_f, axis, dtype );
    REDUCE_LEFT_SHIFT_SUBCASE( case4, a_h, axis, dtype );
}

TEST_CASE("reduce_left_shift(case5)" * doctest::test_suite("view::reduce_left_shift"))
{
    REDUCE_LEFT_SHIFT_SUBCASE( case5,   a, axis, dtype, initial );
    REDUCE_LEFT_SHIFT_SUBCASE( case5, a_a, axis, dtype, initial );
    REDUCE_LEFT_SHIFT_SUBCASE( case5, a_f, axis, dtype, initial );
    REDUCE_LEFT_SHIFT_SUBCASE( case5, a_h, axis, dtype, initial );
}

TEST_CASE("reduce_left_shift(case6)" * doctest::test_suite("view::reduce_left_shift"))
{
    REDUCE_LEFT_SHIFT_SUBCASE( case6,   a, axis, dtype, initial, keepdims );
    REDUCE_LEFT_SHIFT_SUBCASE( case6, a_a, axis, dtype, initial, keepdims );
    REDUCE_LEFT_SHIFT_SUBCASE( case6, a_f, axis, dtype, initial, keepdims );
    REDUCE_LEFT_SHIFT_SUBCASE( case6, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_left_shift(case7)" * doctest::test_suite("view::reduce_left_shift"))
{
    REDUCE_LEFT_SHIFT_SUBCASE( case7,   a, axis, dtype, initial, keepdims );
    REDUCE_LEFT_SHIFT_SUBCASE( case7, a_a, axis, dtype, initial, keepdims );
    REDUCE_LEFT_SHIFT_SUBCASE( case7, a_f, axis, dtype, initial, keepdims );
    REDUCE_LEFT_SHIFT_SUBCASE( case7, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_left_shift(case8)" * doctest::test_suite("view::reduce_left_shift"))
{
    REDUCE_LEFT_SHIFT_SUBCASE( case8,   a, axis, dtype, initial, keepdims );
    REDUCE_LEFT_SHIFT_SUBCASE( case8, a_a, axis, dtype, initial, keepdims );
    REDUCE_LEFT_SHIFT_SUBCASE( case8, a_f, axis, dtype, initial, keepdims );
    REDUCE_LEFT_SHIFT_SUBCASE( case8, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_left_shift(case9)" * doctest::test_suite("view::reduce_left_shift"))
{
    REDUCE_LEFT_SHIFT_SUBCASE( case9,   a, axis, dtype, initial, keepdims );
    REDUCE_LEFT_SHIFT_SUBCASE( case9, a_a, axis, dtype, initial, keepdims );
    REDUCE_LEFT_SHIFT_SUBCASE( case9, a_f, axis, dtype, initial, keepdims );
    REDUCE_LEFT_SHIFT_SUBCASE( case9, a_h, axis, dtype, initial, keepdims );
}

#define RUN_accumulate_left_shift_impl(...) \
nm::view::accumulate_left_shift(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs accumulate_left_shift fn to callable lambda
#define RUN_accumulate_left_shift(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("accumulate_left_shift-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_accumulate_left_shift_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_accumulate_left_shift(case_name, ...) \
RUN_accumulate_left_shift_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define ACCUMULATE_LEFT_SHIFT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, accumulate_left_shift, case_name); \
    using namespace args; \
    auto result = RUN_accumulate_left_shift(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("accumulate_left_shift(case1)" * doctest::test_suite("view::accumulate_left_shift"))
{
    ACCUMULATE_LEFT_SHIFT_SUBCASE( case1,   a, axis );
    ACCUMULATE_LEFT_SHIFT_SUBCASE( case1, a_a, axis );
    ACCUMULATE_LEFT_SHIFT_SUBCASE( case1, a_f, axis );
    ACCUMULATE_LEFT_SHIFT_SUBCASE( case1, a_h, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_LEFT_SHIFT_SUBCASE( case1, a_d, axis );
}

TEST_CASE("accumulate_left_shift(case2)" * doctest::test_suite("view::accumulate_left_shift"))
{
    ACCUMULATE_LEFT_SHIFT_SUBCASE( case2,   a, axis );
    ACCUMULATE_LEFT_SHIFT_SUBCASE( case2, a_a, axis );
    ACCUMULATE_LEFT_SHIFT_SUBCASE( case2, a_f, axis );
    ACCUMULATE_LEFT_SHIFT_SUBCASE( case2, a_h, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_LEFT_SHIFT_SUBCASE( case2, a_d, axis );
}

TEST_CASE("accumulate_left_shift(case3)" * doctest::test_suite("view::accumulate_left_shift"))
{
    ACCUMULATE_LEFT_SHIFT_SUBCASE( case3,   a, axis );
    ACCUMULATE_LEFT_SHIFT_SUBCASE( case3, a_a, axis );
    ACCUMULATE_LEFT_SHIFT_SUBCASE( case3, a_f, axis );
    ACCUMULATE_LEFT_SHIFT_SUBCASE( case3, a_h, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_LEFT_SHIFT_SUBCASE( case3, a_d, axis );
}

#define RUN_outer_left_shift_impl(...) \
nm::view::outer_left_shift(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs outer_left_shift fn to callable lambda
#define RUN_outer_left_shift(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("outer_left_shift-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_outer_left_shift_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_outer_left_shift(case_name, ...) \
RUN_outer_left_shift_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define OUTER_LEFT_SHIFT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, outer_left_shift, case_name); \
    using namespace args; \
    auto result = RUN_outer_left_shift(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("outer_left_shift(case1)" * doctest::test_suite("view::outer_left_shift"))
{
    OUTER_LEFT_SHIFT_SUBCASE( case1,   a,   b );
    OUTER_LEFT_SHIFT_SUBCASE( case1, a_a, b_a );
    OUTER_LEFT_SHIFT_SUBCASE( case1, a_f, b_f );
    OUTER_LEFT_SHIFT_SUBCASE( case1, a_d, b_d );
    OUTER_LEFT_SHIFT_SUBCASE( case1, a_h, b_h );
}