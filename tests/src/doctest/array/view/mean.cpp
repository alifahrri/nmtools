#include "nmtools/array/view/mean.hpp"
#include "nmtools/testing/data/array/mean.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;

#define RUN_mean_impl(...) \
nm::view::mean(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs mean fn to callable lambda
#define RUN_mean(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("mean-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_mean_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_mean(case_name, ...) \
RUN_mean_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define MEAN_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, mean, case_name); \
    using namespace args; \
    auto result = RUN_mean(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("mean(case1)" * doctest::test_suite("view::mean"))
{
    MEAN_SUBCASE(case1, a, axis);
    MEAN_SUBCASE(case1, a_a, axis);
    MEAN_SUBCASE(case1, a_f, axis);
    MEAN_SUBCASE(case1, a_h, axis);
    // NOTE: dynamic-size, dynamic-dim ndarray not supported yet, not supported by reducer
    // TODO: support dynamic-size, dynamic-dim ndarray, by generalizing reducer
    // MEAN_SUBCASE(case1, a_d, axis);
}

TEST_CASE("mean(case2)" * doctest::test_suite("view::mean"))
{
    MEAN_SUBCASE(case2, a, axis);
    MEAN_SUBCASE(case2, a_a, axis);
    MEAN_SUBCASE(case2, a_f, axis);
    MEAN_SUBCASE(case2, a_h, axis);
    // NOTE: dynamic-size, dynamic-dim ndarray not supported yet, not supported by reducer
    // TODO: support dynamic-size, dynamic-dim ndarray, by generalizing reducer
    // MEAN_SUBCASE(case2, a_d, axis);
}

TEST_CASE("mean(case3)" * doctest::test_suite("view::mean"))
{
    MEAN_SUBCASE(case3, a, axis);
    MEAN_SUBCASE(case3, a_a, axis);
    MEAN_SUBCASE(case3, a_f, axis);
    MEAN_SUBCASE(case3, a_h, axis);
    // NOTE: dynamic-size, dynamic-dim ndarray not supported yet, not supported by reducer
    // TODO: support dynamic-size, dynamic-dim ndarray, by generalizing reducer
    // MEAN_SUBCASE(case3, a_d, axis);
}

TEST_CASE("mean(case4)" * doctest::test_suite("view::mean"))
{
    MEAN_SUBCASE(case4, a, axis);
    MEAN_SUBCASE(case4, a_a, axis);
    MEAN_SUBCASE(case4, a_f, axis);
    MEAN_SUBCASE(case4, a_h, axis);
    // NOTE: dynamic-size, dynamic-dim ndarray not supported yet, not supported by reducer
    // TODO: support dynamic-size, dynamic-dim ndarray, by generalizing reducer
    // MEAN_SUBCASE(case4, a_d, axis);
}

TEST_CASE("mean(case5)" * doctest::test_suite("view::mean"))
{
    MEAN_SUBCASE(case5, a, axis);
    MEAN_SUBCASE(case5, a_a, axis);
    MEAN_SUBCASE(case5, a_f, axis);
    MEAN_SUBCASE(case5, a_h, axis);
    // NOTE: dynamic-size, dynamic-dim ndarray not supported yet, not supported by reducer
    // TODO: support dynamic-size, dynamic-dim ndarray, by generalizing reducer
    // MEAN_SUBCASE(case4, a_d, axis);
}