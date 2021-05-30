#include "nmtools/array/view/ufuncs/maximum.hpp"
#include "nmtools/testing/data/array/maximum.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>
#include <algorithm> // std::max

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define RUN_maximum_impl(...) \
nm::view::maximum(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs maximum fn to callable lambda
#define RUN_maximum(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("maximum-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_maximum_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_maximum(case_name, ...) \
RUN_maximum_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define MAXIMUM_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, maximum, case_name); \
    using namespace args; \
    auto result = RUN_maximum(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("maximum(case1)" * doctest::test_suite("view::maximum"))
{
    MAXIMUM_SUBCASE( case1,   a,   b );
    MAXIMUM_SUBCASE( case1, a_a, b_a );
    MAXIMUM_SUBCASE( case1, a_v, b_v );
    MAXIMUM_SUBCASE( case1, a_f, b_f );
    MAXIMUM_SUBCASE( case1, a_d, b_d );
    MAXIMUM_SUBCASE( case1, a_h, b_h );
}

TEST_CASE("maximum(case2)" * doctest::test_suite("view::maximum"))
{
    MAXIMUM_SUBCASE( case2,   a, b );
    MAXIMUM_SUBCASE( case2, a_a, b );
    MAXIMUM_SUBCASE( case2, a_v, b );
    MAXIMUM_SUBCASE( case2, a_f, b );
    MAXIMUM_SUBCASE( case2, a_d, b );
    MAXIMUM_SUBCASE( case2, a_h, b );
}

#define MAXIMUM_FIXED_SHAPE_SUBCASE(subcase_name, expected_shape, ...) \
SUBCASE(#subcase_name) \
{ \
    auto result = RUN_maximum(subcase_name, __VA_ARGS__); \
    using result_t = decltype(result); \
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, result_t ); \
    NMTOOLS_STATIC_ASSERT_EQUAL( meta::fixed_ndarray_shape_v<result_t>, expected_shape ); \
}

TEST_CASE("maximum(fixed_shape)" * doctest::test_suite("view::maximum"))
{
    namespace meta = nmtools::meta;
    {
        int A[1][3] = {{1,2,3}};
        int B[3][1] = {{4},{5},{6}};
        constexpr auto expected_shape = std::array{3,3};
        MAXIMUM_FIXED_SHAPE_SUBCASE( raw, expected_shape, A, B );
    }
    {
        auto A = std::array{1,2,3};
        auto B = std::array{std::array{4,5,6}};
        constexpr auto expected_shape = std::array{3};
        MAXIMUM_FIXED_SHAPE_SUBCASE( array, expected_shape, A, B );
    }
    {
        auto A = na::fixed_ndarray{{1,2,3}};
        auto B = na::fixed_ndarray{{{1,2,3},{4,5,6}}};
        constexpr auto expected_shape = std::array{2,3};
        MAXIMUM_FIXED_SHAPE_SUBCASE( fixed_ndarray, expected_shape, A, B );
    }
}

#define RUN_reduce_maximum_impl(...) \
nm::view::reduce_maximum(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs reduce_maximum fn to callable lambda
#define RUN_reduce_maximum(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("reduce_maximum-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_reduce_maximum_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_reduce_maximum(case_name, ...) \
RUN_reduce_maximum_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define REDUCE_MAXIMUM_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, reduce_maximum, case_name); \
    using namespace args; \
    auto result = RUN_reduce_maximum(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("reduce_maximum(case1)" * doctest::test_suite("view::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case1,   a, axis );
    REDUCE_MAXIMUM_SUBCASE( case1, a_a, axis );
    REDUCE_MAXIMUM_SUBCASE( case1, a_v, axis );
    REDUCE_MAXIMUM_SUBCASE( case1, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_MAXIMUM_SUBCASE( case1, a_d, axis );
    REDUCE_MAXIMUM_SUBCASE( case1, a_h, axis );
}

TEST_CASE("reduce_maximum(case2)" * doctest::test_suite("view::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case2,   a, axis );
    REDUCE_MAXIMUM_SUBCASE( case2, a_a, axis );
    REDUCE_MAXIMUM_SUBCASE( case2, a_v, axis );
    REDUCE_MAXIMUM_SUBCASE( case2, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_MAXIMUM_SUBCASE( case2, a_d, axis );
    REDUCE_MAXIMUM_SUBCASE( case2, a_h, axis );
}

TEST_CASE("reduce_maximum(case3)" * doctest::test_suite("view::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case3,   a, axis );
    REDUCE_MAXIMUM_SUBCASE( case3, a_a, axis );
    REDUCE_MAXIMUM_SUBCASE( case3, a_v, axis );
    REDUCE_MAXIMUM_SUBCASE( case3, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_MAXIMUM_SUBCASE( case3, a_d, axis );
    REDUCE_MAXIMUM_SUBCASE( case3, a_h, axis );
}

TEST_CASE("reduce_maximum(case4)" * doctest::test_suite("view::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case4,   a, axis );
    REDUCE_MAXIMUM_SUBCASE( case4, a_a, axis );
    REDUCE_MAXIMUM_SUBCASE( case4, a_v, axis );
    REDUCE_MAXIMUM_SUBCASE( case4, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_MAXIMUM_SUBCASE( case4, a_d, axis );
    REDUCE_MAXIMUM_SUBCASE( case4, a_h, axis );
}

TEST_CASE("reduce_maximum(case5)" * doctest::test_suite("view::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case5,   a, axis );
    REDUCE_MAXIMUM_SUBCASE( case5, a_a, axis );
    REDUCE_MAXIMUM_SUBCASE( case5, a_v, axis );
    REDUCE_MAXIMUM_SUBCASE( case5, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_MAXIMUM_SUBCASE( case5, a_d, axis );
    REDUCE_MAXIMUM_SUBCASE( case5, a_h, axis );
}

TEST_CASE("reduce_maximum(case6)" * doctest::test_suite("view::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case6,   a, axis );
    REDUCE_MAXIMUM_SUBCASE( case6, a_a, axis );
    REDUCE_MAXIMUM_SUBCASE( case6, a_v, axis );
    REDUCE_MAXIMUM_SUBCASE( case6, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_MAXIMUM_SUBCASE( case6, a_d, axis );
    REDUCE_MAXIMUM_SUBCASE( case6, a_h, axis );
}

TEST_CASE("reduce_maximum(case7)" * doctest::test_suite("view::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case7,   a, axis, dtype, initial );
    REDUCE_MAXIMUM_SUBCASE( case7, a_a, axis, dtype, initial );
    REDUCE_MAXIMUM_SUBCASE( case7, a_v, axis, dtype, initial );
    REDUCE_MAXIMUM_SUBCASE( case7, a_f, axis, dtype, initial );
    REDUCE_MAXIMUM_SUBCASE( case7, a_h, axis, dtype, initial );
}

TEST_CASE("reduce_maximum(case8)" * doctest::test_suite("view::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case8,   a, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case8, a_a, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case8, a_v, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case8, a_f, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case8, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_maximum(case9)" * doctest::test_suite("view::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case9,   a, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case9, a_a, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case9, a_v, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case9, a_f, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case9, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_maximum(case10)" * doctest::test_suite("view::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case10,   a, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case10, a_a, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case10, a_v, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case10, a_f, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case10, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_maximum(case11)" * doctest::test_suite("view::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case11,   a, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case11, a_a, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case11, a_v, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case11, a_f, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case11, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_maximum(case12)" * doctest::test_suite("view::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case12,   a, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case12, a_a, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case12, a_v, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case12, a_f, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case12, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_maximum(case13)" * doctest::test_suite("view::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case13,   a, axis );
    REDUCE_MAXIMUM_SUBCASE( case13, a_a, axis );
    REDUCE_MAXIMUM_SUBCASE( case13, a_v, axis );
    REDUCE_MAXIMUM_SUBCASE( case13, a_f, axis );
    REDUCE_MAXIMUM_SUBCASE( case13, a_h, axis );
}

TEST_CASE("reduce_maximum(case14)" * doctest::test_suite("view::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case14,   a, axis, nm::None, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case14, a_a, axis, nm::None, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case14, a_v, axis, nm::None, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case14, a_f, axis, nm::None, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case14, a_h, axis, nm::None, initial, keepdims );
}

TEST_CASE("reduce_maximum(case15)" * doctest::test_suite("view::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case15,   a, axis, nm::None, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case15, a_a, axis, nm::None, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case15, a_v, axis, nm::None, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case15, a_f, axis, nm::None, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case15, a_h, axis, nm::None, initial, keepdims );
}

TEST_CASE("reduce_maximum(case16)" * doctest::test_suite("view::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case16,   a, axis, nm::None, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case16, a_a, axis, nm::None, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case16, a_v, axis, nm::None, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case16, a_f, axis, nm::None, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case16, a_h, axis, nm::None, initial, keepdims );
}

TEST_CASE("reduce_maximum(case17)" * doctest::test_suite("view::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case17,   a, axis, nm::None, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case17, a_a, axis, nm::None, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case17, a_v, axis, nm::None, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case17, a_f, axis, nm::None, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case17, a_h, axis, nm::None, initial, keepdims );
}

#define RUN_accumulate_maximum_impl(...) \
nm::view::accumulate_maximum(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs accumulate_maximum fn to callable lambda
#define RUN_accumulate_maximum(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("accumulate_maximum-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_accumulate_maximum_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_accumulate_maximum(case_name, ...) \
RUN_accumulate_maximum_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define ACCUMULATE_MAXIMUM_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, accumulate_maximum, case_name); \
    using namespace args; \
    auto result = RUN_accumulate_maximum(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("accumulate_maximum(case1)" * doctest::test_suite("view::accumulate_maximum"))
{
    ACCUMULATE_MAXIMUM_SUBCASE( case1,   a, axis );
    ACCUMULATE_MAXIMUM_SUBCASE( case1, a_a, axis );
    ACCUMULATE_MAXIMUM_SUBCASE( case1, a_v, axis );
    ACCUMULATE_MAXIMUM_SUBCASE( case1, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_MAXIMUM_SUBCASE( case1, a_d, axis );
    ACCUMULATE_MAXIMUM_SUBCASE( case1, a_f, axis );
}

TEST_CASE("accumulate_maximum(case2)" * doctest::test_suite("view::accumulate_maximum"))
{
    ACCUMULATE_MAXIMUM_SUBCASE( case2,   a, axis );
    ACCUMULATE_MAXIMUM_SUBCASE( case2, a_a, axis );
    ACCUMULATE_MAXIMUM_SUBCASE( case2, a_v, axis );
    ACCUMULATE_MAXIMUM_SUBCASE( case2, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_MAXIMUM_SUBCASE( case2, a_d, axis );
    ACCUMULATE_MAXIMUM_SUBCASE( case2, a_f, axis );
}

TEST_CASE("accumulate_maximum(case3)" * doctest::test_suite("view::accumulate_maximum"))
{
    ACCUMULATE_MAXIMUM_SUBCASE( case3,   a, axis );
    ACCUMULATE_MAXIMUM_SUBCASE( case3, a_a, axis );
    ACCUMULATE_MAXIMUM_SUBCASE( case3, a_v, axis );
    ACCUMULATE_MAXIMUM_SUBCASE( case3, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_MAXIMUM_SUBCASE( case3, a_d, axis );
    ACCUMULATE_MAXIMUM_SUBCASE( case3, a_f, axis );
}

#define RUN_outer_maximum_impl(...) \
nm::view::outer_maximum(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs outer_maximum fn to callable lambda
#define RUN_outer_maximum(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("outer_maximum-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_outer_maximum_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_outer_maximum(case_name, ...) \
RUN_outer_maximum_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define OUTER_MAXIMUM_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, outer_maximum, case_name); \
    using namespace args; \
    auto result = RUN_outer_maximum(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("outer_maximum(case1)" * doctest::test_suite("view::outer_maximum"))
{
    OUTER_MAXIMUM_SUBCASE( case1,   a,   b );
    OUTER_MAXIMUM_SUBCASE( case1, a_a, b_a );
    OUTER_MAXIMUM_SUBCASE( case1, a_v, b_v );
    OUTER_MAXIMUM_SUBCASE( case1, a_f, b_f );
    OUTER_MAXIMUM_SUBCASE( case1, a_d, b_d );
    OUTER_MAXIMUM_SUBCASE( case1, a_h, b_h );
}