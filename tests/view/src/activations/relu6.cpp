#include "nmtools/array/view/activations/relu6.hpp"
#include "nmtools/testing/data/array/relu6.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace view = nmtools::view;

#define RUN_relu6_impl(...) \
nm::view::relu6(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs relu6 fn to callable lambda
#define RUN_relu6(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("relu6-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_relu6_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_relu6(case_name, ...) \
RUN_relu6_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define RELU6_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(activations, relu6, case_name); \
    using namespace args; \
    auto result = RUN_relu6(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("relu6(case1)" * doctest::test_suite("view::relu6"))
{
    RELU6_SUBCASE(case1, a);
    RELU6_SUBCASE(case1, a_a);
    RELU6_SUBCASE(case1, a_f);
    RELU6_SUBCASE(case1, a_h);
    RELU6_SUBCASE(case1, a_d);
}