#include "nmtools/array/activations/softshrink.hpp"
#include "nmtools/testing/data/array/softshrink.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace view = nmtools::view;

#define RUN_softshrink_impl(...) \
nm::view::softshrink(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs softshrink fn to callable lambda
#define RUN_softshrink(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("softshrink-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_softshrink_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_softshrink(case_name, ...) \
RUN_softshrink_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define SOFTSHRINK_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(activations, softshrink, case_name); \
    using namespace args; \
    auto result = RUN_softshrink(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("softshrink(case1)" * doctest::test_suite("view::softshrink"))
{
    SOFTSHRINK_SUBCASE(case1, a);
    SOFTSHRINK_SUBCASE(case1, a_a);
    SOFTSHRINK_SUBCASE(case1, a_f);
    SOFTSHRINK_SUBCASE(case1, a_h);
    SOFTSHRINK_SUBCASE(case1, a_d);
}