#include "nmtools/array/view/ufuncs/bitwise_and.hpp"
#include "nmtools/testing/data/array/bitwise_and.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define RUN_bitwise_and_impl(...) \
nm::view::bitwise_and(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs bitwise_and fn to callable lambda
#define RUN_bitwise_and(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("bitwise_and-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_bitwise_and_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_bitwise_and(case_name, ...) \
RUN_bitwise_and_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define BITWISE_AND_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, bitwise_and, case_name); \
    using namespace args; \
    auto result = RUN_bitwise_and(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("bitwise_and(case1)" * doctest::test_suite("view::bitwise_and"))
{
    BITWISE_AND_SUBCASE( case1,   a,   b );
    BITWISE_AND_SUBCASE( case1, a_a, b_a );
    BITWISE_AND_SUBCASE( case1, a_f, b_f );
    BITWISE_AND_SUBCASE( case1, a_d, b_d );
    BITWISE_AND_SUBCASE( case1, a_h, b_h );
}

TEST_CASE("bitwise_and(case2)" * doctest::test_suite("view::bitwise_and"))
{
    BITWISE_AND_SUBCASE( case2,   a, b );
    BITWISE_AND_SUBCASE( case2, a_a, b );
    BITWISE_AND_SUBCASE( case2, a_f, b );
    BITWISE_AND_SUBCASE( case2, a_d, b );
    BITWISE_AND_SUBCASE( case2, a_h, b );
}

#define BITWISE_AND_FIXED_SHAPE_SUBCASE(subcase_name, expected_shape, ...) \
SUBCASE(#subcase_name) \
{ \
    auto result = RUN_bitwise_and(subcase_name, __VA_ARGS__); \
    using result_t = decltype(result); \
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, result_t ); \
    NMTOOLS_STATIC_ASSERT_EQUAL( meta::fixed_ndarray_shape_v<result_t>, expected_shape ); \
}

// TODO: fix
#if 0
TEST_CASE("bitwise_and(fixed_shape)" * doctest::test_suite("view::bitwise_and"))
{
    namespace meta = nmtools::meta;
    {
        int A[1][3] = {{1,2,3}};
        int B[3][1] = {{4},{5},{6}};
        constexpr auto expected_shape = std::array{3,3};
        BITWISE_AND_FIXED_SHAPE_SUBCASE( raw, expected_shape, A, B );
    }
    {
        auto A = std::array{1,2,3};
        auto B = std::array{std::array{4,5,6}};
        constexpr auto expected_shape = std::array{3};
        BITWISE_AND_FIXED_SHAPE_SUBCASE( array, expected_shape, A, B );
    }
    {
        auto A = na::fixed_ndarray{{1,2,3}};
        auto B = na::fixed_ndarray{{{1,2,3},{4,5,6}}};
        constexpr auto expected_shape = std::array{2,3};
        BITWISE_AND_FIXED_SHAPE_SUBCASE( fixed_ndarray, expected_shape, A, B );
    }
}
#endif