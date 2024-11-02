#include "nmtools/array/view/activations/selu.hpp"
#include "nmtools/testing/data/array/selu.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace view = nmtools::view;

#define RUN_selu_impl(...) \
nm::view::selu(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs selu fn to callable lambda
#define RUN_selu(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("selu-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_selu_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_selu(case_name, ...) \
RUN_selu_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define SELU_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(activations, selu, case_name); \
    using namespace args; \
    auto result = RUN_selu(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("selu(case1)" * doctest::test_suite("view::selu"))
{
    SELU_SUBCASE(case1, a);
    SELU_SUBCASE(case1, a_a);
    SELU_SUBCASE(case1, a_f);
    SELU_SUBCASE(case1, a_h);
    SELU_SUBCASE(case1, a_d);
}