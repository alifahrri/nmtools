#include "nmtools/array/view/ufuncs/logical_and.hpp"
#include "nmtools/testing/data/array/logical_and.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>
#include <algorithm> // std::max

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define RUN_logical_and_impl(...) \
nm::view::logical_and(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs logical_and fn to callable lambda
#define RUN_logical_and(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("logical_and-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_logical_and_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_logical_and(case_name, ...) \
RUN_logical_and_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define LOGICAL_AND_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, logical_and, case_name); \
    using namespace args; \
    auto result = RUN_logical_and(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("logical_and(case1)" * doctest::test_suite("view::logical_and"))
{
    LOGICAL_AND_SUBCASE( case1,   a,   b );
    LOGICAL_AND_SUBCASE( case1, a_a, b_a );
    LOGICAL_AND_SUBCASE( case1, a_f, b_f );
    LOGICAL_AND_SUBCASE( case1, a_d, b_d );
    LOGICAL_AND_SUBCASE( case1, a_h, b_h );
}

TEST_CASE("logical_and(case2)" * doctest::test_suite("view::logical_and"))
{
    LOGICAL_AND_SUBCASE( case2,   a, b );
    LOGICAL_AND_SUBCASE( case2, a_a, b );
    LOGICAL_AND_SUBCASE( case2, a_f, b );
    LOGICAL_AND_SUBCASE( case2, a_d, b );
    LOGICAL_AND_SUBCASE( case2, a_h, b );
}

#define LOGICAL_AND_FIXED_SHAPE_SUBCASE(subcase_name, expected_shape, ...) \
SUBCASE(#subcase_name) \
{ \
    auto result = RUN_logical_and(subcase_name, __VA_ARGS__); \
    using result_t = decltype(result); \
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, result_t ); \
    NMTOOLS_STATIC_ASSERT_EQUAL( meta::fixed_ndarray_shape_v<result_t>, expected_shape ); \
}

// TODO: fix
#if 0
TEST_CASE("logical_and(fixed_shape)" * doctest::test_suite("view::logical_and"))
{
    namespace meta = nmtools::meta;
    {
        int A[1][3] = {{1,2,3}};
        int B[3][1] = {{4},{5},{6}};
        constexpr auto expected_shape = std::array{3,3};
        LOGICAL_AND_FIXED_SHAPE_SUBCASE( raw, expected_shape, A, B );
    }
    {
        auto A = std::array{1,2,3};
        auto B = std::array{std::array{4,5,6}};
        constexpr auto expected_shape = std::array{3};
        LOGICAL_AND_FIXED_SHAPE_SUBCASE( array, expected_shape, A, B );
    }
    {
        auto A = na::fixed_ndarray{{1,2,3}};
        auto B = na::fixed_ndarray{{{1,2,3},{4,5,6}}};
        constexpr auto expected_shape = std::array{2,3};
        LOGICAL_AND_FIXED_SHAPE_SUBCASE( fixed_ndarray, expected_shape, A, B );
    }
}
#endif

#define RUN_reduce_logical_and_impl(...) \
nm::view::reduce_logical_and(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs reduce_logical_and fn to callable lambda
#define RUN_reduce_logical_and(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("reduce_logical_and-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_reduce_logical_and_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_reduce_logical_and(case_name, ...) \
RUN_reduce_logical_and_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define REDUCE_LOGICAL_AND_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, reduce_logical_and, case_name); \
    using namespace args; \
    auto result = RUN_reduce_logical_and(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("reduce_logical_and(case1)" * doctest::test_suite("view::reduce_logical_and"))
{
    REDUCE_LOGICAL_AND_SUBCASE( case1,   a, axis );
    REDUCE_LOGICAL_AND_SUBCASE( case1, a_a, axis );
    REDUCE_LOGICAL_AND_SUBCASE( case1, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_LOGICAL_AND_SUBCASE( case1, a_d, axis );
    REDUCE_LOGICAL_AND_SUBCASE( case1, a_f, axis );
}

TEST_CASE("reduce_logical_and(case2)" * doctest::test_suite("view::reduce_logical_and"))
{
    REDUCE_LOGICAL_AND_SUBCASE( case2,   a, axis );
    REDUCE_LOGICAL_AND_SUBCASE( case2, a_a, axis );
    REDUCE_LOGICAL_AND_SUBCASE( case2, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_LOGICAL_AND_SUBCASE( case2, a_d, axis );
    REDUCE_LOGICAL_AND_SUBCASE( case2, a_f, axis );
}

TEST_CASE("reduce_logical_and(case3)" * doctest::test_suite("view::reduce_logical_and"))
{
    REDUCE_LOGICAL_AND_SUBCASE( case3,   a, axis );
    REDUCE_LOGICAL_AND_SUBCASE( case3, a_a, axis );
    REDUCE_LOGICAL_AND_SUBCASE( case3, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_LOGICAL_AND_SUBCASE( case3, a_d, axis );
    REDUCE_LOGICAL_AND_SUBCASE( case3, a_f, axis );
}

TEST_CASE("reduce_logical_and(case4)" * doctest::test_suite("view::reduce_logical_and"))
{
    REDUCE_LOGICAL_AND_SUBCASE( case4,   a, axis );
    REDUCE_LOGICAL_AND_SUBCASE( case4, a_a, axis );
    REDUCE_LOGICAL_AND_SUBCASE( case4, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_LOGICAL_AND_SUBCASE( case4, a_d, axis );
    REDUCE_LOGICAL_AND_SUBCASE( case4, a_f, axis );
}

TEST_CASE("reduce_logical_and(case5)" * doctest::test_suite("view::reduce_logical_and"))
{
    REDUCE_LOGICAL_AND_SUBCASE( case5,   a, axis );
    REDUCE_LOGICAL_AND_SUBCASE( case5, a_a, axis );
    REDUCE_LOGICAL_AND_SUBCASE( case5, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_LOGICAL_AND_SUBCASE( case5, a_d, axis );
    REDUCE_LOGICAL_AND_SUBCASE( case5, a_f, axis );
}

TEST_CASE("reduce_logical_and(case6)" * doctest::test_suite("view::reduce_logical_and"))
{
    REDUCE_LOGICAL_AND_SUBCASE( case6,   a, axis );
    REDUCE_LOGICAL_AND_SUBCASE( case6, a_a, axis );
    REDUCE_LOGICAL_AND_SUBCASE( case6, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_LOGICAL_AND_SUBCASE( case6, a_d, axis );
    REDUCE_LOGICAL_AND_SUBCASE( case6, a_f, axis );
}