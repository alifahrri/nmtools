#include "nmtools/array/view/ufuncs/fmax.hpp"
#include "nmtools/testing/data/array/fmax.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define RUN_fmax_impl(...) \
nm::view::fmax(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs fmax fn to callable lambda
#define RUN_fmax(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("fmax-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_fmax_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_fmax(case_name, ...) \
RUN_fmax_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define FMAX_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, fmax, case_name); \
    using namespace args; \
    auto result = RUN_fmax(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("fmax(case1)" * doctest::test_suite("view::fmax"))
{
    FMAX_SUBCASE( case1,   a,   b );
    FMAX_SUBCASE( case1, a_a, b_a );
    FMAX_SUBCASE( case1, a_v, b_v );
    FMAX_SUBCASE( case1, a_f, b_f );
    FMAX_SUBCASE( case1, a_d, b_d );
    FMAX_SUBCASE( case1, a_h, b_h );
}

TEST_CASE("fmax(case2)" * doctest::test_suite("view::fmax"))
{
    FMAX_SUBCASE( case2,   a, b );
    FMAX_SUBCASE( case2, a_a, b );
    FMAX_SUBCASE( case2, a_v, b );
    FMAX_SUBCASE( case2, a_f, b );
    FMAX_SUBCASE( case2, a_d, b );
    FMAX_SUBCASE( case2, a_h, b );
}

#define FMAX_FIXED_SHAPE_SUBCASE(subcase_name, expected_shape, ...) \
SUBCASE(#subcase_name) \
{ \
    auto result = RUN_fmax(subcase_name, __VA_ARGS__); \
    using result_t = decltype(result); \
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, result_t ); \
    NMTOOLS_STATIC_ASSERT_EQUAL( meta::fixed_ndarray_shape_v<result_t>, expected_shape ); \
}

TEST_CASE("fmax(fixed_shape)" * doctest::test_suite("view::fmax"))
{
    namespace meta = nmtools::meta;
    {
        int A[1][3] = {{1,2,3}};
        int B[3][1] = {{4},{5},{6}};
        constexpr auto expected_shape = std::array{3,3};
        FMAX_FIXED_SHAPE_SUBCASE( raw, expected_shape, A, B );
    }
    {
        auto A = std::array{1,2,3};
        auto B = std::array{std::array{4,5,6}};
        constexpr auto expected_shape = std::array{3};
        FMAX_FIXED_SHAPE_SUBCASE( array, expected_shape, A, B );
    }
    {
        auto A = na::fixed_ndarray{{1,2,3}};
        auto B = na::fixed_ndarray{{{1,2,3},{4,5,6}}};
        constexpr auto expected_shape = std::array{2,3};
        FMAX_FIXED_SHAPE_SUBCASE( fixed_ndarray, expected_shape, A, B );
    }
}

#define RUN_reduce_fmax_impl(...) \
nm::view::reduce_fmax(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs reduce_fmax fn to callable lambda
#define RUN_reduce_fmax(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("reduce_fmax-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_reduce_fmax_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_reduce_fmax(case_name, ...) \
RUN_reduce_fmax_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define REDUCE_FMAX_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, reduce_fmax, case_name); \
    using namespace args; \
    auto result = RUN_reduce_fmax(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("reduce_fmax(case1)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case1,   a, axis );
    REDUCE_FMAX_SUBCASE( case1, a_a, axis );
    REDUCE_FMAX_SUBCASE( case1, a_v, axis );
    REDUCE_FMAX_SUBCASE( case1, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_FMAX_SUBCASE( case1, a_d, axis );
    REDUCE_FMAX_SUBCASE( case1, a_f, axis );
}

TEST_CASE("reduce_fmax(case2)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case2,   a, axis );
    REDUCE_FMAX_SUBCASE( case2, a_a, axis );
    REDUCE_FMAX_SUBCASE( case2, a_v, axis );
    REDUCE_FMAX_SUBCASE( case2, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_FMAX_SUBCASE( case2, a_d, axis );
    REDUCE_FMAX_SUBCASE( case2, a_f, axis );
}

TEST_CASE("reduce_fmax(case3)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case3,   a, axis );
    REDUCE_FMAX_SUBCASE( case3, a_a, axis );
    REDUCE_FMAX_SUBCASE( case3, a_v, axis );
    REDUCE_FMAX_SUBCASE( case3, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_FMAX_SUBCASE( case3, a_d, axis );
    REDUCE_FMAX_SUBCASE( case3, a_f, axis );
}

TEST_CASE("reduce_fmax(case4)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case4,   a, axis );
    REDUCE_FMAX_SUBCASE( case4, a_a, axis );
    REDUCE_FMAX_SUBCASE( case4, a_v, axis );
    REDUCE_FMAX_SUBCASE( case4, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_FMAX_SUBCASE( case4, a_d, axis );
    REDUCE_FMAX_SUBCASE( case4, a_f, axis );
}

TEST_CASE("reduce_fmax(case5)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case5,   a, axis );
    REDUCE_FMAX_SUBCASE( case5, a_a, axis );
    REDUCE_FMAX_SUBCASE( case5, a_v, axis );
    REDUCE_FMAX_SUBCASE( case5, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_FMAX_SUBCASE( case5, a_d, axis );
    REDUCE_FMAX_SUBCASE( case5, a_f, axis );
}

TEST_CASE("reduce_fmax(case6)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case6,   a, axis );
    REDUCE_FMAX_SUBCASE( case6, a_a, axis );
    REDUCE_FMAX_SUBCASE( case6, a_v, axis );
    REDUCE_FMAX_SUBCASE( case6, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_FMAX_SUBCASE( case6, a_d, axis );
    REDUCE_FMAX_SUBCASE( case6, a_f, axis );
}

TEST_CASE("reduce_fmax(case7)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case7,   a, axis, dtype, initial );
    REDUCE_FMAX_SUBCASE( case7, a_a, axis, dtype, initial );
    REDUCE_FMAX_SUBCASE( case7, a_v, axis, dtype, initial );
    REDUCE_FMAX_SUBCASE( case7, a_f, axis, dtype, initial );
    REDUCE_FMAX_SUBCASE( case7, a_f, axis, dtype, initial );
}

TEST_CASE("reduce_fmax(case8)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case8,   a, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case8, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case8, a_v, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case8, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case8, a_f, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_fmax(case9)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case9,   a, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case9, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case9, a_v, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case9, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case9, a_f, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_fmax(case10)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case10,   a, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case10, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case10, a_v, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case10, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case10, a_f, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_fmax(case11)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case11,   a, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case11, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case11, a_v, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case11, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case11, a_f, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_fmax(case12)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case12,   a, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case12, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case12, a_v, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case12, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case12, a_f, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_fmax(case13)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case13,   a, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case13, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case13, a_v, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case13, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case13, a_f, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_fmax(case14)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case14,   a, axis );
    REDUCE_FMAX_SUBCASE( case14, a_a, axis );
    REDUCE_FMAX_SUBCASE( case14, a_v, axis );
    REDUCE_FMAX_SUBCASE( case14, a_f, axis );
    REDUCE_FMAX_SUBCASE( case14, a_f, axis );
}

TEST_CASE("reduce_fmax(case15)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case15,   a, axis, nm::None, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case15, a_a, axis, nm::None, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case15, a_v, axis, nm::None, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case15, a_f, axis, nm::None, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case15, a_f, axis, nm::None, initial, keepdims );
}

TEST_CASE("reduce_fmax(case16)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case16,   a, axis, nm::None, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case16, a_a, axis, nm::None, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case16, a_v, axis, nm::None, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case16, a_f, axis, nm::None, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case16, a_f, axis, nm::None, initial, keepdims );
}

TEST_CASE("reduce_fmax(case17)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case17,   a, axis, nm::None, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case17, a_a, axis, nm::None, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case17, a_v, axis, nm::None, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case17, a_f, axis, nm::None, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case17, a_f, axis, nm::None, initial, keepdims );
}

TEST_CASE("reduce_fmax(case18)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case18,   a, axis, nm::None, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case18, a_a, axis, nm::None, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case18, a_v, axis, nm::None, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case18, a_f, axis, nm::None, initial, keepdims );
    REDUCE_FMAX_SUBCASE( case18, a_f, axis, nm::None, initial, keepdims );
}

#define RUN_accumulate_fmax_impl(...) \
nm::view::accumulate_fmax(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs accumulate_fmax fn to callable lambda
#define RUN_accumulate_fmax(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("accumulate_fmax-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_accumulate_fmax_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_accumulate_fmax(case_name, ...) \
RUN_accumulate_fmax_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define ACCUMULATE_FMAX_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, accumulate_fmax, case_name); \
    using namespace args; \
    auto result = RUN_accumulate_fmax(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("accumulate_fmax(case1)" * doctest::test_suite("view::accumulate_fmax"))
{
    ACCUMULATE_FMAX_SUBCASE( case1,   a, axis );
    ACCUMULATE_FMAX_SUBCASE( case1, a_a, axis );
    ACCUMULATE_FMAX_SUBCASE( case1, a_v, axis );
    ACCUMULATE_FMAX_SUBCASE( case1, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_FMAX_SUBCASE( case1, a_d, axis );
    ACCUMULATE_FMAX_SUBCASE( case1, a_f, axis );
}

TEST_CASE("accumulate_fmax(case2)" * doctest::test_suite("view::accumulate_fmax"))
{
    ACCUMULATE_FMAX_SUBCASE( case2,   a, axis );
    ACCUMULATE_FMAX_SUBCASE( case2, a_a, axis );
    ACCUMULATE_FMAX_SUBCASE( case2, a_v, axis );
    ACCUMULATE_FMAX_SUBCASE( case2, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_FMAX_SUBCASE( case2, a_d, axis );
    ACCUMULATE_FMAX_SUBCASE( case2, a_f, axis );
}

TEST_CASE("accumulate_fmax(case3)" * doctest::test_suite("view::accumulate_fmax"))
{
    ACCUMULATE_FMAX_SUBCASE( case3,   a, axis );
    ACCUMULATE_FMAX_SUBCASE( case3, a_a, axis );
    ACCUMULATE_FMAX_SUBCASE( case3, a_v, axis );
    ACCUMULATE_FMAX_SUBCASE( case3, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_FMAX_SUBCASE( case3, a_d, axis );
    ACCUMULATE_FMAX_SUBCASE( case3, a_f, axis );
}

#define RUN_outer_fmax_impl(...) \
nm::view::outer_fmax(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs outer_fmax fn to callable lambda
#define RUN_outer_fmax(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("outer_fmax-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_outer_fmax_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_outer_fmax(case_name, ...) \
RUN_outer_fmax_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define OUTER_FMAX_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, outer_fmax, case_name); \
    using namespace args; \
    auto result = RUN_outer_fmax(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("outer_fmax(case1)" * doctest::test_suite("view::outer_fmax"))
{
    OUTER_FMAX_SUBCASE( case1,   a,   b );
    OUTER_FMAX_SUBCASE( case1, a_a, b_a );
    OUTER_FMAX_SUBCASE( case1, a_v, b_v );
    OUTER_FMAX_SUBCASE( case1, a_f, b_f );
    OUTER_FMAX_SUBCASE( case1, a_d, b_d );
    OUTER_FMAX_SUBCASE( case1, a_h, b_h );
}