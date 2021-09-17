#include "nmtools/array/array/activations/relu.hpp"
#include "nmtools/testing/data/array/relu.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;

#define RUN_relu_impl(...) \
nm::array::relu(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs relu fn to callable lambda
#define RUN_relu(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("relu-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_relu_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_relu(case_name, ...) \
RUN_relu_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define RELU_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(activations, relu, case_name); \
    using namespace args; \
    auto result = RUN_relu(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("relu(case1)" * doctest::test_suite("array::relu"))
{
    RELU_SUBCASE(case1, a);
    RELU_SUBCASE(case1, a_a);
    RELU_SUBCASE(case1, a_f);
    RELU_SUBCASE(case1, a_h);
    RELU_SUBCASE(case1, a_d);
}