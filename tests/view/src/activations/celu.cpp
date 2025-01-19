#include "nmtools/array/activations/celu.hpp"
#include "nmtools/testing/data/array/celu.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace view = nmtools::view;

#define RUN_celu_impl(...) \
nm::view::celu(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs celu fn to callable lambda
#define RUN_celu(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("celu-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_celu_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_celu(case_name, ...) \
RUN_celu_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define CELU_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(activations, celu, case_name); \
    using namespace args; \
    auto result = RUN_celu(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("celu(case1)" * doctest::test_suite("view::celu"))
{
    CELU_SUBCASE(case1, a);
    CELU_SUBCASE(case1, a_a);
    CELU_SUBCASE(case1, a_f);
    CELU_SUBCASE(case1, a_h);
    CELU_SUBCASE(case1, a_d);
}

TEST_CASE("celu(case2)" * doctest::test_suite("view::celu"))
{
    CELU_SUBCASE(case2, a, alpha);
    CELU_SUBCASE(case2, a_a, alpha);
    CELU_SUBCASE(case2, a_f, alpha);
    CELU_SUBCASE(case2, a_h, alpha);
    CELU_SUBCASE(case2, a_d, alpha);
}