#include "nmtools/array/view/activations/log_sigmoid.hpp"
#include "nmtools/testing/data/array/log_sigmoid.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace view = nmtools::view;

#define RUN_log_sigmoid_impl(...) \
nm::view::log_sigmoid(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs log_sigmoid fn to callable lambda
#define RUN_log_sigmoid(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("log_sigmoid-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_log_sigmoid_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_log_sigmoid(case_name, ...) \
RUN_log_sigmoid_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define LOG_SIGMOID_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(activations, log_sigmoid, case_name); \
    using namespace args; \
    auto result = RUN_log_sigmoid(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("log_sigmoid(case1)" * doctest::test_suite("view::log_sigmoid"))
{
    LOG_SIGMOID_SUBCASE(case1, a);
    LOG_SIGMOID_SUBCASE(case1, a_a);
    LOG_SIGMOID_SUBCASE(case1, a_f);
    LOG_SIGMOID_SUBCASE(case1, a_h);
    LOG_SIGMOID_SUBCASE(case1, a_d);
}