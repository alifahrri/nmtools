#include "nmtools/array/view/ufuncs/add.hpp"
#include "nmtools/testing/data/array/add.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define RUN_add_impl(...) \
nm::view::add(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs add fn to callable lambda
#define RUN_add(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("add-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_add_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_add(case_name, ...) \
RUN_add_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define ADD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, add, case_name); \
    using namespace args; \
    auto result = RUN_add(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("add(case1)" * doctest::test_suite("view::add"))
{
    ADD_SUBCASE( case1,   a,   b );
    ADD_SUBCASE( case1, a_a, b_a );
    ADD_SUBCASE( case1, a_v, b_v );
    ADD_SUBCASE( case1, a_f, b_f );
    ADD_SUBCASE( case1, a_d, b_d );
    ADD_SUBCASE( case1, a_h, b_h );
}

TEST_CASE("add(case2)" * doctest::test_suite("view::add"))
{
    ADD_SUBCASE( case2,   a, b );
    ADD_SUBCASE( case2, a_a, b );
    ADD_SUBCASE( case2, a_v, b );
    ADD_SUBCASE( case2, a_f, b );
    ADD_SUBCASE( case2, a_d, b );
    ADD_SUBCASE( case2, a_h, b );
}

TEST_CASE("add(case3)" * doctest::test_suite("view::add"))
{
    ADD_SUBCASE(case3, a, b);
}

#define RUN_reduce_add_impl(...) \
nm::view::reduce_add(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs reduce_add fn to callable lambda
#define RUN_reduce_add(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("reduce_add-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_reduce_add_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_reduce_add(case_name, ...) \
RUN_reduce_add_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define REDUCE_ADD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, reduce_add, case_name); \
    using namespace args; \
    auto result = RUN_reduce_add(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("reduce_add(case1)" * doctest::test_suite("view::reduce_add"))
{
    REDUCE_ADD_SUBCASE( case1,   a, axis );
    REDUCE_ADD_SUBCASE( case1, a_a, axis );
    REDUCE_ADD_SUBCASE( case1, a_v, axis );
    REDUCE_ADD_SUBCASE( case1, a_f, axis );
    // not yet supported,
    // cant figure out apply_slice for dynamic dim array yet
    // REDUCE_ADD_SUBCASE( case1, a_d, axis );
    REDUCE_ADD_SUBCASE( case1, a_h, axis );
}

TEST_CASE("reduce_add(case2)" * doctest::test_suite("view::reduce_add"))
{
    REDUCE_ADD_SUBCASE( case2,   a, axis );
    REDUCE_ADD_SUBCASE( case2, a_a, axis );
    REDUCE_ADD_SUBCASE( case2, a_v, axis );
    REDUCE_ADD_SUBCASE( case2, a_f, axis );
    REDUCE_ADD_SUBCASE( case2, a_h, axis );
}

TEST_CASE("reduce_add(case3)" * doctest::test_suite("view::reduce_add"))
{
    REDUCE_ADD_SUBCASE( case3,   a, axis );
    REDUCE_ADD_SUBCASE( case3, a_a, axis );
    REDUCE_ADD_SUBCASE( case3, a_v, axis );
    REDUCE_ADD_SUBCASE( case3, a_f, axis );
    REDUCE_ADD_SUBCASE( case3, a_h, axis );
}

TEST_CASE("reduce_add(case4)" * doctest::test_suite("view::reduce_add"))
{
    REDUCE_ADD_SUBCASE( case4,   a,   axis );
    REDUCE_ADD_SUBCASE( case4, a_a, axis_a );
    REDUCE_ADD_SUBCASE( case4, a_v, axis_v );
    REDUCE_ADD_SUBCASE( case4, a_f, axis_f );
    REDUCE_ADD_SUBCASE( case4, a_h, axis_h );
}

TEST_CASE("reduce_add(case5)" * doctest::test_suite("view::reduce_add"))
{
    REDUCE_ADD_SUBCASE( case5,   a,   axis );
    REDUCE_ADD_SUBCASE( case5, a_a, axis_a );
    REDUCE_ADD_SUBCASE( case5, a_v, axis_v );
    REDUCE_ADD_SUBCASE( case5, a_f, axis_f );
    REDUCE_ADD_SUBCASE( case5, a_h, axis_h );
}

TEST_CASE("reduce_add(case6)" * doctest::test_suite("view::reduce_add"))
{
    REDUCE_ADD_SUBCASE( case6,   a,   axis );
    REDUCE_ADD_SUBCASE( case6, a_a, axis_a );
    REDUCE_ADD_SUBCASE( case6, a_v, axis_v );
    REDUCE_ADD_SUBCASE( case6, a_f, axis_f );
    REDUCE_ADD_SUBCASE( case6, a_h, axis_h );
}

TEST_CASE("reduce_add(case7)" * doctest::test_suite("view::reduce_add"))
{
    REDUCE_ADD_SUBCASE( case7,   a, axis, dtype );
    REDUCE_ADD_SUBCASE( case7, a_a, axis, dtype );
    REDUCE_ADD_SUBCASE( case7, a_v, axis, dtype );
    REDUCE_ADD_SUBCASE( case7, a_f, axis, dtype );
    REDUCE_ADD_SUBCASE( case7, a_h, axis, dtype );
}

TEST_CASE("reduce_add(case8)" * doctest::test_suite("view::reduce_add"))
{
    REDUCE_ADD_SUBCASE( case8,   a, axis, dtype, initial );
    REDUCE_ADD_SUBCASE( case8, a_a, axis, dtype, initial );
    REDUCE_ADD_SUBCASE( case8, a_v, axis, dtype, initial );
    REDUCE_ADD_SUBCASE( case8, a_f, axis, dtype, initial );
    REDUCE_ADD_SUBCASE( case8, a_h, axis, dtype, initial );
}

TEST_CASE("reduce_add(case9)" * doctest::test_suite("view::reduce_add"))
{
    REDUCE_ADD_SUBCASE( case9,   a, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case9, a_a, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case9, a_v, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case9, a_f, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case9, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_add(case10)" * doctest::test_suite("view::reduce_add"))
{
    REDUCE_ADD_SUBCASE( case10,   a, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case10, a_a, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case10, a_v, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case10, a_f, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case10, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_add(case11)" * doctest::test_suite("view::reduce_add"))
{
    REDUCE_ADD_SUBCASE( case11,   a, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case11, a_a, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case11, a_v, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case11, a_f, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case11, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_add(case12)" * doctest::test_suite("view::reduce_add"))
{
    REDUCE_ADD_SUBCASE( case12,   a, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case12, a_a, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case12, a_v, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case12, a_f, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case12, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_add(case13)" * doctest::test_suite("view::reduce_add"))
{
    REDUCE_ADD_SUBCASE( case13,   a, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case13, a_a, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case13, a_v, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case13, a_f, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case13, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_add(case14)" * doctest::test_suite("view::reduce_add"))
{
    REDUCE_ADD_SUBCASE( case14,   a, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case14, a_a, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case14, a_v, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case14, a_f, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case14, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_add(case15)" * doctest::test_suite("view::reduce_add"))
{
    REDUCE_ADD_SUBCASE( case15,   a, axis );
    REDUCE_ADD_SUBCASE( case15, a_a, axis );
    REDUCE_ADD_SUBCASE( case15, a_v, axis );
    REDUCE_ADD_SUBCASE( case15, a_f, axis );
    REDUCE_ADD_SUBCASE( case15, a_h, axis );
}

TEST_CASE("reduce_add(case16)" * doctest::test_suite("view::reduce_add"))
{
    REDUCE_ADD_SUBCASE( case16,   a, axis, nmtools::None, initial );
    REDUCE_ADD_SUBCASE( case16, a_a, axis, nmtools::None, initial );
    REDUCE_ADD_SUBCASE( case16, a_v, axis, nmtools::None, initial );
    REDUCE_ADD_SUBCASE( case16, a_f, axis, nmtools::None, initial );
    REDUCE_ADD_SUBCASE( case16, a_h, axis, nmtools::None, initial );
}

TEST_CASE("reduce_add(case17)" * doctest::test_suite("view::reduce_add"))
{
    REDUCE_ADD_SUBCASE( case17,   a, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case17, a_a, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case17, a_v, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case17, a_f, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case17, a_h, axis, nmtools::None, initial, keepdims );
}

TEST_CASE("reduce_add(case18)" * doctest::test_suite("view::reduce_add"))
{
    REDUCE_ADD_SUBCASE( case18,   a, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case18, a_a, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case18, a_v, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case18, a_f, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case18, a_h, axis, nmtools::None, initial, keepdims );
}

TEST_CASE("reduce_add(case19)" * doctest::test_suite("view::reduce_add"))
{
    REDUCE_ADD_SUBCASE( case19,   a, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case19, a_a, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case19, a_v, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case19, a_f, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case19, a_h, axis, nmtools::None, initial, keepdims );
}

TEST_CASE("reduce_add(case20)" * doctest::test_suite("view::reduce_add"))
{
    REDUCE_ADD_SUBCASE( case20,   a, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case20, a_a, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case20, a_v, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case20, a_f, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case20, a_h, axis, nmtools::None, initial, keepdims );
}

TEST_CASE("reduce_add(case21)" * doctest::test_suite("view::reduce_add"))
{
    REDUCE_ADD_SUBCASE( case21,   a, axis, dtype );
    REDUCE_ADD_SUBCASE( case21, a_a, axis, dtype );
    // TODO: remove support for nested std::vector
    // REDUCE_ADD_SUBCASE( case21, a_v, axis, dtype );
    REDUCE_ADD_SUBCASE( case21, a_f, axis, dtype );
    REDUCE_ADD_SUBCASE( case21, a_h, axis, dtype );
}

TEST_CASE("reduce_add(case22)" * doctest::test_suite("view::reduce_add"))
{
    REDUCE_ADD_SUBCASE( case22,   a, axis, dtype );
    REDUCE_ADD_SUBCASE( case22, a_a, axis, dtype );
    // TODO: remove support for nested std::vector
    // REDUCE_ADD_SUBCASE( case22, a_v, axis, dtype );
    REDUCE_ADD_SUBCASE( case22, a_f, axis, dtype );
    REDUCE_ADD_SUBCASE( case22, a_h, axis, dtype );
}

#define RUN_accumulate_add_impl(...) \
nm::view::accumulate_add(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs accumulate_add fn to callable lambda
#define RUN_accumulate_add(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("accumulate_add-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_accumulate_add_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_accumulate_add(case_name, ...) \
RUN_accumulate_add_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define ACCUMULATE_ADD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, accumulate_add, case_name); \
    using namespace args; \
    auto result = RUN_accumulate_add(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("accumulate_add(case1)" * doctest::test_suite("view::accumulate_add"))
{
    ACCUMULATE_ADD_SUBCASE( case1,   a, axis );
    ACCUMULATE_ADD_SUBCASE( case1, a_a, axis );
    ACCUMULATE_ADD_SUBCASE( case1, a_v, axis );
    ACCUMULATE_ADD_SUBCASE( case1, a_f, axis );
    // not yet supported,
    // cant figure out apply_slice for dynamic dim array yet
    // ACCUMULATE_ADD_SUBCASE( case1, a_d, axis );
    ACCUMULATE_ADD_SUBCASE( case1, a_h, axis );
}

TEST_CASE("accumulate_add(case2)" * doctest::test_suite("view::accumulate_add"))
{
    ACCUMULATE_ADD_SUBCASE( case2,   a, axis );
    ACCUMULATE_ADD_SUBCASE( case2, a_a, axis );
    ACCUMULATE_ADD_SUBCASE( case2, a_v, axis );
    ACCUMULATE_ADD_SUBCASE( case2, a_f, axis );
    // not yet supported,
    // cant figure out apply_slice for dynamic dim array yet
    // ACCUMULATE_ADD_SUBCASE( case2, a_d, axis );
    ACCUMULATE_ADD_SUBCASE( case2, a_h, axis );
}

TEST_CASE("accumulate_add(case3)" * doctest::test_suite("view::accumulate_add"))
{
    ACCUMULATE_ADD_SUBCASE( case3,   a, axis );
    ACCUMULATE_ADD_SUBCASE( case3, a_a, axis );
    ACCUMULATE_ADD_SUBCASE( case3, a_v, axis );
    ACCUMULATE_ADD_SUBCASE( case3, a_f, axis );
    // not yet supported,
    // cant figure out apply_slice for dynamic dim array yet
    // ACCUMULATE_ADD_SUBCASE( case3, a_d, axis );
    ACCUMULATE_ADD_SUBCASE( case3, a_h, axis );
}

#define RUN_outer_add_impl(...) \
nm::view::outer_add(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs outer_add fn to callable lambda
#define RUN_outer_add(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("outer_add-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_outer_add_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_outer_add(case_name, ...) \
RUN_outer_add_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define OUTER_ADD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, outer_add, case_name); \
    using namespace args; \
    auto result = RUN_outer_add(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("outer_add(case1)" * doctest::test_suite("view::outer_add"))
{
    OUTER_ADD_SUBCASE( case1,   a,   b );
    OUTER_ADD_SUBCASE( case1, a_a, b_a );
    OUTER_ADD_SUBCASE( case1, a_v, b_v );
    OUTER_ADD_SUBCASE( case1, a_f, b_f );
    OUTER_ADD_SUBCASE( case1, a_d, b_d );
    OUTER_ADD_SUBCASE( case1, a_h, b_h );
}

#define ADD_FIXED_SHAPE_SUBCASE(subcase_name, expected_shape, ...) \
SUBCASE(#subcase_name) \
{ \
    auto result = RUN_add(subcase_name, __VA_ARGS__); \
    using result_t = decltype(result); \
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, result_t ); \
    NMTOOLS_STATIC_ASSERT_EQUAL( meta::fixed_ndarray_shape_v<result_t>, expected_shape ); \
}

TEST_CASE("add(fixed_shape)" * doctest::test_suite("view::add"))
{
    namespace meta = nmtools::meta;
    {
        int A[1][3] = {{1,2,3}};
        int B[3][1] = {{4},{5},{6}};
        constexpr auto expected_shape = std::array{3,3};
        ADD_FIXED_SHAPE_SUBCASE( raw, expected_shape, A, B );
    }
    {
        auto A = std::array{1,2,3};
        auto B = std::array{std::array{4,5,6}};
        constexpr auto expected_shape = std::array{3};
        ADD_FIXED_SHAPE_SUBCASE( array, expected_shape, A, B );
    }
    {
        auto A = na::fixed_ndarray{{1,2,3}};
        auto B = na::fixed_ndarray{{{1,2,3},{4,5,6}}};
        constexpr auto expected_shape = std::array{2,3};
        ADD_FIXED_SHAPE_SUBCASE( fixed_ndarray, expected_shape, A, B );
    }
}