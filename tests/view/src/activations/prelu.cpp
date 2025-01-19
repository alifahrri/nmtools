#include "nmtools/array/activations/prelu.hpp"
#include "nmtools/testing/data/array/prelu.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace view = nmtools::view;

#define RUN_prelu_impl(...) \
nm::view::prelu(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs prelu fn to callable lambda
#define RUN_prelu(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("prelu-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_prelu_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_prelu(case_name, ...) \
RUN_prelu_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define PRELU_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(activations, prelu, case_name); \
    using namespace args; \
    auto result = RUN_prelu(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("prelu(case1)" * doctest::test_suite("view::prelu"))
{
    PRELU_SUBCASE(case1, a);
    PRELU_SUBCASE(case1, a_a);
    PRELU_SUBCASE(case1, a_f);
    PRELU_SUBCASE(case1, a_h);
    PRELU_SUBCASE(case1, a_d);
}