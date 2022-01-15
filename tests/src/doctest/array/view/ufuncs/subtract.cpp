#include "nmtools/array/view/ufuncs/subtract.hpp"
#include "nmtools/testing/data/array/subtract.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define RUN_subtract_impl(...) \
nm::view::subtract(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs subtract fn to callable lambda
#define RUN_subtract(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("subtract-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_subtract_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_subtract(case_name, ...) \
RUN_subtract_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define SUBTRACT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, subtract, case_name); \
    using namespace args; \
    auto result = RUN_subtract(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("subtract(case1)" * doctest::test_suite("view::subtract"))
{
    SUBTRACT_SUBCASE( case1,   a,   b );
    SUBTRACT_SUBCASE( case1, a_a, b_a );
    SUBTRACT_SUBCASE( case1, a_v, b_v );
    SUBTRACT_SUBCASE( case1, a_f, b_f );
    SUBTRACT_SUBCASE( case1, a_d, b_d );
    SUBTRACT_SUBCASE( case1, a_h, b_h );
}

TEST_CASE("subtract(case2)" * doctest::test_suite("view::subtract"))
{
    SUBTRACT_SUBCASE( case2,   a, b );
    SUBTRACT_SUBCASE( case2, a_a, b );
    SUBTRACT_SUBCASE( case2, a_v, b );
    SUBTRACT_SUBCASE( case2, a_f, b );
    SUBTRACT_SUBCASE( case2, a_d, b );
    SUBTRACT_SUBCASE( case2, a_h, b );
}

#define SUBTRACT_FIXED_SHAPE_SUBCASE(subcase_name, expected_shape, ...) \
SUBCASE(#subcase_name) \
{ \
    auto result = RUN_subtract(subcase_name, __VA_ARGS__); \
    using result_t = decltype(result); \
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, result_t ); \
    NMTOOLS_STATIC_ASSERT_EQUAL( meta::fixed_ndarray_shape_v<result_t>, expected_shape ); \
}

TEST_CASE("subtract(fixed_shape)" * doctest::test_suite("view::subtract"))
{
    namespace meta = nmtools::meta;
    {
        int A[1][3] = {{1,2,3}};
        int B[3][1] = {{4},{5},{6}};
        constexpr auto expected_shape = std::array{3,3};
        SUBTRACT_FIXED_SHAPE_SUBCASE( raw, expected_shape, A, B );
    }
    {
        auto A = std::array{1,2,3};
        auto B = std::array{std::array{4,5,6}};
        constexpr auto expected_shape = std::array{3};
        SUBTRACT_FIXED_SHAPE_SUBCASE( array, expected_shape, A, B );
    }
    {
        auto A = na::fixed_ndarray{{1,2,3}};
        auto B = na::fixed_ndarray{{{1,2,3},{4,5,6}}};
        constexpr auto expected_shape = std::array{2,3};
        SUBTRACT_FIXED_SHAPE_SUBCASE( fixed_ndarray, expected_shape, A, B );
    }
}

#define RUN_reduce_subtract_impl(...) \
nm::view::reduce_subtract(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs reduce_subtract fn to callable lambda
#define RUN_reduce_subtract(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("reduce_subtract-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_reduce_subtract_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_reduce_subtract(case_name, ...) \
RUN_reduce_subtract_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define REDUCE_SUBTRACT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, reduce_subtract, case_name); \
    using namespace args; \
    auto result = RUN_reduce_subtract(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("reduce_subtract(case1)" * doctest::test_suite("view::reduce_subtract"))
{
    REDUCE_SUBTRACT_SUBCASE( case1,   a, axis );
    REDUCE_SUBTRACT_SUBCASE( case1, a_a, axis );
    REDUCE_SUBTRACT_SUBCASE( case1, a_v, axis );
    REDUCE_SUBTRACT_SUBCASE( case1, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_SUBTRACT_SUBCASE( case1, a_d, axis );
    REDUCE_SUBTRACT_SUBCASE( case1, a_f, axis );
}

TEST_CASE("reduce_subtract(case2)" * doctest::test_suite("view::reduce_subtract"))
{
    REDUCE_SUBTRACT_SUBCASE( case2,   a, axis );
    REDUCE_SUBTRACT_SUBCASE( case2, a_a, axis );
    REDUCE_SUBTRACT_SUBCASE( case2, a_v, axis );
    REDUCE_SUBTRACT_SUBCASE( case2, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_SUBTRACT_SUBCASE( case2, a_d, axis );
    REDUCE_SUBTRACT_SUBCASE( case2, a_f, axis );
}

TEST_CASE("reduce_subtract(case3)" * doctest::test_suite("view::reduce_subtract"))
{
    REDUCE_SUBTRACT_SUBCASE( case3,   a, axis );
    REDUCE_SUBTRACT_SUBCASE( case3, a_a, axis );
    REDUCE_SUBTRACT_SUBCASE( case3, a_v, axis );
    REDUCE_SUBTRACT_SUBCASE( case3, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_SUBTRACT_SUBCASE( case3, a_d, axis );
    REDUCE_SUBTRACT_SUBCASE( case3, a_f, axis );
}

TEST_CASE("reduce_subtract(case4)" * doctest::test_suite("view::reduce_subtract"))
{
    REDUCE_SUBTRACT_SUBCASE( case4,   a, axis, dtype, initial );
    REDUCE_SUBTRACT_SUBCASE( case4, a_a, axis, dtype, initial );
    REDUCE_SUBTRACT_SUBCASE( case4, a_v, axis, dtype, initial );
    REDUCE_SUBTRACT_SUBCASE( case4, a_f, axis, dtype, initial );
    REDUCE_SUBTRACT_SUBCASE( case4, a_f, axis, dtype, initial );
}

TEST_CASE("reduce_subtract(case5)" * doctest::test_suite("view::reduce_subtract"))
{
    REDUCE_SUBTRACT_SUBCASE( case5,   a, axis, dtype, initial, keepdims );
    REDUCE_SUBTRACT_SUBCASE( case5, a_a, axis, dtype, initial, keepdims );
    REDUCE_SUBTRACT_SUBCASE( case5, a_v, axis, dtype, initial, keepdims );
    REDUCE_SUBTRACT_SUBCASE( case5, a_f, axis, dtype, initial, keepdims );
    REDUCE_SUBTRACT_SUBCASE( case5, a_f, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_subtract(case6)" * doctest::test_suite("view::reduce_subtract"))
{
    REDUCE_SUBTRACT_SUBCASE( case6,   a, axis, dtype, initial, keepdims );
    REDUCE_SUBTRACT_SUBCASE( case6, a_a, axis, dtype, initial, keepdims );
    REDUCE_SUBTRACT_SUBCASE( case6, a_v, axis, dtype, initial, keepdims );
    REDUCE_SUBTRACT_SUBCASE( case6, a_f, axis, dtype, initial, keepdims );
    REDUCE_SUBTRACT_SUBCASE( case6, a_f, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_subtract(case7)" * doctest::test_suite("view::reduce_subtract"))
{
    REDUCE_SUBTRACT_SUBCASE( case7,   a, axis, dtype, initial, keepdims );
    REDUCE_SUBTRACT_SUBCASE( case7, a_a, axis, dtype, initial, keepdims );
    REDUCE_SUBTRACT_SUBCASE( case7, a_v, axis, dtype, initial, keepdims );
    REDUCE_SUBTRACT_SUBCASE( case7, a_f, axis, dtype, initial, keepdims );
    REDUCE_SUBTRACT_SUBCASE( case7, a_f, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_subtract(case8)" * doctest::test_suite("view::reduce_subtract"))
{
    REDUCE_SUBTRACT_SUBCASE( case8,   a, axis, dtype, initial, keepdims );
    REDUCE_SUBTRACT_SUBCASE( case8, a_a, axis, dtype, initial, keepdims );
    REDUCE_SUBTRACT_SUBCASE( case8, a_v, axis, dtype, initial, keepdims );
    REDUCE_SUBTRACT_SUBCASE( case8, a_f, axis, dtype, initial, keepdims );
    REDUCE_SUBTRACT_SUBCASE( case8, a_f, axis, dtype, initial, keepdims );
}

#define RUN_accumulate_subtract_impl(...) \
nm::view::accumulate_subtract(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs accumulate_subtract fn to callable lambda
#define RUN_accumulate_subtract(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("accumulate_subtract-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_accumulate_subtract_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_accumulate_subtract(case_name, ...) \
RUN_accumulate_subtract_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define ACCUMULATE_SUBTRACT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, accumulate_subtract, case_name); \
    using namespace args; \
    auto result = RUN_accumulate_subtract(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("accumulate_subtract(case1)" * doctest::test_suite("view::accumulate_subtract"))
{
    ACCUMULATE_SUBTRACT_SUBCASE( case1,   a, axis );
    ACCUMULATE_SUBTRACT_SUBCASE( case1, a_a, axis );
    ACCUMULATE_SUBTRACT_SUBCASE( case1, a_v, axis );
    ACCUMULATE_SUBTRACT_SUBCASE( case1, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_SUBTRACT_SUBCASE( case1, a_d, axis );
    ACCUMULATE_SUBTRACT_SUBCASE( case1, a_h, axis );
}

TEST_CASE("accumulate_subtract(case2)" * doctest::test_suite("view::accumulate_subtract"))
{
    ACCUMULATE_SUBTRACT_SUBCASE( case2,   a, axis );
    ACCUMULATE_SUBTRACT_SUBCASE( case2, a_a, axis );
    ACCUMULATE_SUBTRACT_SUBCASE( case2, a_v, axis );
    ACCUMULATE_SUBTRACT_SUBCASE( case2, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_SUBTRACT_SUBCASE( case2, a_d, axis );
    ACCUMULATE_SUBTRACT_SUBCASE( case2, a_h, axis );
}

TEST_CASE("accumulate_subtract(case3)" * doctest::test_suite("view::accumulate_subtract"))
{
    ACCUMULATE_SUBTRACT_SUBCASE( case3,   a, axis );
    ACCUMULATE_SUBTRACT_SUBCASE( case3, a_a, axis );
    ACCUMULATE_SUBTRACT_SUBCASE( case3, a_v, axis );
    ACCUMULATE_SUBTRACT_SUBCASE( case3, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_SUBTRACT_SUBCASE( case3, a_d, axis );
    ACCUMULATE_SUBTRACT_SUBCASE( case3, a_h, axis );
}

#define RUN_outer_subtract_impl(...) \
nm::view::outer_subtract(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs outer_subtract fn to callable lambda
#define RUN_outer_subtract(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("outer_subtract-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_outer_subtract_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_outer_subtract(case_name, ...) \
RUN_outer_subtract_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define OUTER_SUBTRACT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, outer_subtract, case_name); \
    using namespace args; \
    auto result = RUN_outer_subtract(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("outer_subtract(case1)" * doctest::test_suite("view::outer_subtract"))
{
    OUTER_SUBTRACT_SUBCASE( case1,   a,   b );
    OUTER_SUBTRACT_SUBCASE( case1, a_a, b_a );
    OUTER_SUBTRACT_SUBCASE( case1, a_v, b_v );
    OUTER_SUBTRACT_SUBCASE( case1, a_f, b_f );
    OUTER_SUBTRACT_SUBCASE( case1, a_d, b_d );
    OUTER_SUBTRACT_SUBCASE( case1, a_h, b_h );
}