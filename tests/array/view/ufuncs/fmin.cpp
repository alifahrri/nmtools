#include "nmtools/array/view/ufuncs/fmin.hpp"
#include "nmtools/testing/data/array/fmin.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define RUN_fmin_impl(...) \
nm::view::fmin(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
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
    NMTOOLS_TESTING_DECLARE_NS(view, fmin, case_name); \
    using namespace args; \
    auto result = RUN_fmin(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("fmin(case1)" * doctest::test_suite("view::fmin"))
{
    FMIN_SUBCASE( case1,   a,   b );
    FMIN_SUBCASE( case1, a_a, b_a );
    FMIN_SUBCASE( case1, a_f, b_f );
    FMIN_SUBCASE( case1, a_d, b_d );
    FMIN_SUBCASE( case1, a_h, b_h );
}

TEST_CASE("fmin(case2)" * doctest::test_suite("view::fmin"))
{
    FMIN_SUBCASE( case2,   a, b );
    FMIN_SUBCASE( case2, a_a, b );
    FMIN_SUBCASE( case2, a_f, b );
    FMIN_SUBCASE( case2, a_d, b );
    FMIN_SUBCASE( case2, a_h, b );
}

#define FMIN_FIXED_SHAPE_SUBCASE(subcase_name, expected_shape, ...) \
SUBCASE(#subcase_name) \
{ \
    auto result = RUN_fmin(subcase_name, __VA_ARGS__); \
    using result_t = decltype(result); \
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, result_t ); \
    NMTOOLS_STATIC_ASSERT_EQUAL( meta::fixed_ndarray_shape_v<result_t>, expected_shape ); \
}

// TODO: fix
#if 0
TEST_CASE("fmin(fixed_shape)" * doctest::test_suite("view::fmin"))
{
    namespace meta = nmtools::meta;
    {
        int A[1][3] = {{1,2,3}};
        int B[3][1] = {{4},{5},{6}};
        constexpr auto expected_shape = std::array{3,3};
        FMIN_FIXED_SHAPE_SUBCASE( raw, expected_shape, A, B );
    }
    {
        auto A = std::array{1,2,3};
        auto B = std::array{std::array{4,5,6}};
        constexpr auto expected_shape = std::array{3};
        FMIN_FIXED_SHAPE_SUBCASE( array, expected_shape, A, B );
    }
    {
        auto A = na::fixed_ndarray{{1,2,3}};
        auto B = na::fixed_ndarray{{{1,2,3},{4,5,6}}};
        constexpr auto expected_shape = std::array{2,3};
        FMIN_FIXED_SHAPE_SUBCASE( fixed_ndarray, expected_shape, A, B );
    }
}
#endif

#define RUN_reduce_fmin_impl(...) \
nm::view::reduce_fmin(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
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
    NMTOOLS_TESTING_DECLARE_NS(view, reduce_fmin, case_name); \
    using namespace args; \
    auto result = RUN_reduce_fmin(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("reduce_fmin(case1)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case1,   a, axis );
    REDUCE_FMIN_SUBCASE( case1, a_a, axis );
    REDUCE_FMIN_SUBCASE( case1, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_FMIN_SUBCASE( case1, a_d, axis );
    REDUCE_FMIN_SUBCASE( case1, a_f, axis );
}

TEST_CASE("reduce_fmin(case2)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case2,   a, axis );
    REDUCE_FMIN_SUBCASE( case2, a_a, axis );
    REDUCE_FMIN_SUBCASE( case2, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_FMIN_SUBCASE( case2, a_d, axis );
    REDUCE_FMIN_SUBCASE( case2, a_f, axis );
}

TEST_CASE("reduce_fmin(case3)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case3,   a, axis );
    REDUCE_FMIN_SUBCASE( case3, a_a, axis );
    REDUCE_FMIN_SUBCASE( case3, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_FMIN_SUBCASE( case3, a_d, axis );
    REDUCE_FMIN_SUBCASE( case3, a_f, axis );
}

TEST_CASE("reduce_fmin(case4)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case4,   a, axis );
    REDUCE_FMIN_SUBCASE( case4, a_a, axis );
    REDUCE_FMIN_SUBCASE( case4, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_FMIN_SUBCASE( case4, a_d, axis );
    REDUCE_FMIN_SUBCASE( case4, a_f, axis );
}

TEST_CASE("reduce_fmin(case5)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case5,   a, axis );
    REDUCE_FMIN_SUBCASE( case5, a_a, axis );
    REDUCE_FMIN_SUBCASE( case5, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_FMIN_SUBCASE( case5, a_d, axis );
    REDUCE_FMIN_SUBCASE( case5, a_f, axis );
}

TEST_CASE("reduce_fmin(case6)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case6,   a, axis );
    REDUCE_FMIN_SUBCASE( case6, a_a, axis );
    REDUCE_FMIN_SUBCASE( case6, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_FMIN_SUBCASE( case6, a_d, axis );
    REDUCE_FMIN_SUBCASE( case6, a_f, axis );
}

TEST_CASE("reduce_fmin(case7)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case7,   a, axis, dtype, initial );
    REDUCE_FMIN_SUBCASE( case7, a_a, axis, dtype, initial );
    REDUCE_FMIN_SUBCASE( case7, a_f, axis, dtype, initial );
    REDUCE_FMIN_SUBCASE( case7, a_f, axis, dtype, initial );
}

TEST_CASE("reduce_fmin(case8)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case8,   a, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case8, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case8, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case8, a_f, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_fmin(case9)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case9,   a, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case9, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case9, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case9, a_f, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_fmin(case10)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case10,   a, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case10, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case10, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case10, a_f, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_fmin(case11)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case11,   a, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case11, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case11, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case11, a_f, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_fmin(case12)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case12,   a, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case12, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case12, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case12, a_f, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_fmin(case13)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case13,   a, axis );
    REDUCE_FMIN_SUBCASE( case13, a_a, axis );
    REDUCE_FMIN_SUBCASE( case13, a_f, axis );
    REDUCE_FMIN_SUBCASE( case13, a_f, axis );
}

TEST_CASE("reduce_fmin(case14)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case14,   a, axis, nm::None, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case14, a_a, axis, nm::None, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case14, a_f, axis, nm::None, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case14, a_f, axis, nm::None, initial, keepdims );
}

TEST_CASE("reduce_fmin(case15)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case15,   a, axis, nm::None, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case15, a_a, axis, nm::None, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case15, a_f, axis, nm::None, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case15, a_f, axis, nm::None, initial, keepdims );
}

TEST_CASE("reduce_fmin(case15)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case15,   a, axis, nm::None, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case15, a_a, axis, nm::None, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case15, a_f, axis, nm::None, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case15, a_f, axis, nm::None, initial, keepdims );
}

TEST_CASE("reduce_fmin(case16)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case16,   a, axis, nm::None, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case16, a_a, axis, nm::None, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case16, a_f, axis, nm::None, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case16, a_f, axis, nm::None, initial, keepdims );
}

#define RUN_accumulate_fmin_impl(...) \
nm::view::accumulate_fmin(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
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
    NMTOOLS_TESTING_DECLARE_NS(view, accumulate_fmin, case_name); \
    using namespace args; \
    auto result = RUN_accumulate_fmin(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("accumulate_fmin(case1)" * doctest::test_suite("view::accumulate_fmin"))
{
    ACCUMULATE_FMIN_SUBCASE( case1,   a, axis );
    ACCUMULATE_FMIN_SUBCASE( case1, a_a, axis );
    ACCUMULATE_FMIN_SUBCASE( case1, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_FMIN_SUBCASE( case1, a_d, axis );
    ACCUMULATE_FMIN_SUBCASE( case1, a_f, axis );
}

TEST_CASE("accumulate_fmin(case2)" * doctest::test_suite("view::accumulate_fmin"))
{
    ACCUMULATE_FMIN_SUBCASE( case2,   a, axis );
    ACCUMULATE_FMIN_SUBCASE( case2, a_a, axis );
    ACCUMULATE_FMIN_SUBCASE( case2, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_FMIN_SUBCASE( case2, a_d, axis );
    ACCUMULATE_FMIN_SUBCASE( case2, a_f, axis );
}

TEST_CASE("accumulate_fmin(case3)" * doctest::test_suite("view::accumulate_fmin"))
{
    ACCUMULATE_FMIN_SUBCASE( case3,   a, axis );
    ACCUMULATE_FMIN_SUBCASE( case3, a_a, axis );
    ACCUMULATE_FMIN_SUBCASE( case3, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_FMIN_SUBCASE( case3, a_d, axis );
    ACCUMULATE_FMIN_SUBCASE( case3, a_f, axis );
}

#define RUN_outer_fmin_impl(...) \
nm::view::outer_fmin(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
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
    NMTOOLS_TESTING_DECLARE_NS(view, outer_fmin, case_name); \
    using namespace args; \
    auto result = RUN_outer_fmin(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("outer_fmin(case1)" * doctest::test_suite("view::outer_fmin"))
{
    OUTER_FMIN_SUBCASE( case1,   a,   b );
    OUTER_FMIN_SUBCASE( case1, a_a, b_a );
    OUTER_FMIN_SUBCASE( case1, a_f, b_f );
    OUTER_FMIN_SUBCASE( case1, a_d, b_d );
    OUTER_FMIN_SUBCASE( case1, a_h, b_h );
}