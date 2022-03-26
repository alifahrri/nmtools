#include "nmtools/array/view/ufuncs/logical_xor.hpp"
#include "nmtools/testing/data/array/logical_xor.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>
#include <algorithm> // std::max

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define RUN_logical_xor_impl(...) \
nm::view::logical_xor(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs logical_xor fn to callable lambda
#define RUN_logical_xor(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("logical_xor-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_logical_xor_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_logical_xor(case_name, ...) \
RUN_logical_xor_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define LOGICAL_XOR_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, logical_xor, case_name); \
    using namespace args; \
    auto result = RUN_logical_xor(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("logical_xor(case1)" * doctest::test_suite("view::logical_xor"))
{
    LOGICAL_XOR_SUBCASE( case1,   a,   b );
    LOGICAL_XOR_SUBCASE( case1, a_a, b_a );
    LOGICAL_XOR_SUBCASE( case1, a_v, b_v );
    LOGICAL_XOR_SUBCASE( case1, a_f, b_f );
    LOGICAL_XOR_SUBCASE( case1, a_d, b_d );
    LOGICAL_XOR_SUBCASE( case1, a_h, b_h );
}

TEST_CASE("logical_xor(case2)" * doctest::test_suite("view::logical_xor"))
{
    LOGICAL_XOR_SUBCASE( case2,   a, b );
    LOGICAL_XOR_SUBCASE( case2, a_a, b );
    LOGICAL_XOR_SUBCASE( case2, a_v, b );
    LOGICAL_XOR_SUBCASE( case2, a_f, b );
    LOGICAL_XOR_SUBCASE( case2, a_d, b );
    LOGICAL_XOR_SUBCASE( case2, a_h, b );
}

#define LOGICAL_XOR_FIXED_SHAPE_SUBCASE(subcase_name, expected_shape, ...) \
SUBCASE(#subcase_name) \
{ \
    auto result = RUN_logical_xor(subcase_name, __VA_ARGS__); \
    using result_t = decltype(result); \
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, result_t ); \
    NMTOOLS_STATIC_ASSERT_EQUAL( meta::fixed_ndarray_shape_v<result_t>, expected_shape ); \
}

TEST_CASE("logical_xor(fixed_shape)" * doctest::test_suite("view::logical_xor"))
{
    namespace meta = nmtools::meta;
    {
        int A[1][3] = {{1,2,3}};
        int B[3][1] = {{4},{5},{6}};
        constexpr auto expected_shape = std::array{3,3};
        LOGICAL_XOR_FIXED_SHAPE_SUBCASE( raw, expected_shape, A, B );
    }
    {
        auto A = std::array{1,2,3};
        auto B = std::array{std::array{4,5,6}};
        constexpr auto expected_shape = std::array{3};
        LOGICAL_XOR_FIXED_SHAPE_SUBCASE( array, expected_shape, A, B );
    }
    {
        auto A = na::fixed_ndarray{{1,2,3}};
        auto B = na::fixed_ndarray{{{1,2,3},{4,5,6}}};
        constexpr auto expected_shape = std::array{2,3};
        LOGICAL_XOR_FIXED_SHAPE_SUBCASE( fixed_ndarray, expected_shape, A, B );
    }
}

#define RUN_reduce_logical_xor_impl(...) \
nm::view::reduce_logical_xor(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs reduce_logical_xor fn to callable lambda
#define RUN_reduce_logical_xor(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("reduce_logical_xor-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_reduce_logical_xor_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_reduce_logical_xor(case_name, ...) \
RUN_reduce_logical_xor_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define REDUCE_LOGICAL_XOR_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, reduce_logical_xor, case_name); \
    using namespace args; \
    auto result = RUN_reduce_logical_xor(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("reduce_logical_xor(case1)" * doctest::test_suite("view::reduce_logical_xor"))
{
    REDUCE_LOGICAL_XOR_SUBCASE( case1,   a, axis );
    REDUCE_LOGICAL_XOR_SUBCASE( case1, a_a, axis );
    REDUCE_LOGICAL_XOR_SUBCASE( case1, a_v, axis );
    REDUCE_LOGICAL_XOR_SUBCASE( case1, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_LOGICAL_XOR_SUBCASE( case1, a_d, axis );
    REDUCE_LOGICAL_XOR_SUBCASE( case1, a_f, axis );
}

TEST_CASE("reduce_logical_xor(case2)" * doctest::test_suite("view::reduce_logical_xor"))
{
    REDUCE_LOGICAL_XOR_SUBCASE( case2,   a, axis );
    REDUCE_LOGICAL_XOR_SUBCASE( case2, a_a, axis );
    REDUCE_LOGICAL_XOR_SUBCASE( case2, a_v, axis );
    REDUCE_LOGICAL_XOR_SUBCASE( case2, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_LOGICAL_XOR_SUBCASE( case2, a_d, axis );
    REDUCE_LOGICAL_XOR_SUBCASE( case2, a_f, axis );
}

TEST_CASE("reduce_logical_xor(case3)" * doctest::test_suite("view::reduce_logical_xor"))
{
    REDUCE_LOGICAL_XOR_SUBCASE( case3,   a, axis );
    REDUCE_LOGICAL_XOR_SUBCASE( case3, a_a, axis );
    REDUCE_LOGICAL_XOR_SUBCASE( case3, a_v, axis );
    REDUCE_LOGICAL_XOR_SUBCASE( case3, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_LOGICAL_XOR_SUBCASE( case3, a_d, axis );
    REDUCE_LOGICAL_XOR_SUBCASE( case3, a_f, axis );
}

TEST_CASE("reduce_logical_xor(case4)" * doctest::test_suite("view::reduce_logical_xor"))
{
    REDUCE_LOGICAL_XOR_SUBCASE( case4,   a, axis );
    REDUCE_LOGICAL_XOR_SUBCASE( case4, a_a, axis );
    REDUCE_LOGICAL_XOR_SUBCASE( case4, a_v, axis );
    REDUCE_LOGICAL_XOR_SUBCASE( case4, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_LOGICAL_XOR_SUBCASE( case4, a_d, axis );
    REDUCE_LOGICAL_XOR_SUBCASE( case4, a_f, axis );
}

TEST_CASE("reduce_logical_xor(case5)" * doctest::test_suite("view::reduce_logical_xor"))
{
    REDUCE_LOGICAL_XOR_SUBCASE( case5,   a, axis );
    REDUCE_LOGICAL_XOR_SUBCASE( case5, a_a, axis );
    REDUCE_LOGICAL_XOR_SUBCASE( case5, a_v, axis );
    REDUCE_LOGICAL_XOR_SUBCASE( case5, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_LOGICAL_XOR_SUBCASE( case5, a_d, axis );
    REDUCE_LOGICAL_XOR_SUBCASE( case5, a_f, axis );
}

TEST_CASE("reduce_logical_xor(case6)" * doctest::test_suite("view::reduce_logical_xor"))
{
    REDUCE_LOGICAL_XOR_SUBCASE( case6,   a, axis );
    REDUCE_LOGICAL_XOR_SUBCASE( case6, a_a, axis );
    REDUCE_LOGICAL_XOR_SUBCASE( case6, a_v, axis );
    REDUCE_LOGICAL_XOR_SUBCASE( case6, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_LOGICAL_XOR_SUBCASE( case6, a_d, axis );
    REDUCE_LOGICAL_XOR_SUBCASE( case6, a_f, axis );
}