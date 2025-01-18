#include "nmtools/array/activations/leaky_relu.hpp"
#include "nmtools/testing/data/array/leaky_relu.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace view = nmtools::view;

#define RUN_leaky_relu_impl(...) \
nm::view::leaky_relu(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs leaky_relu fn to callable lambda
#define RUN_leaky_relu(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("leaky_relu-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_leaky_relu_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_leaky_relu(case_name, ...) \
RUN_leaky_relu_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define LEAKY_RELU_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(activations, leaky_relu, case_name); \
    using namespace args; \
    auto result = RUN_leaky_relu(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("leaky_relu(case1)" * doctest::test_suite("view::leaky_relu"))
{
    LEAKY_RELU_SUBCASE(case1, a);
    LEAKY_RELU_SUBCASE(case1, a_a);
    LEAKY_RELU_SUBCASE(case1, a_f);
    LEAKY_RELU_SUBCASE(case1, a_h);
    LEAKY_RELU_SUBCASE(case1, a_d);
}