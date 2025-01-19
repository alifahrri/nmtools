#include "nmtools/array/activations/hardshrink.hpp"
#include "nmtools/testing/data/array/hardshrink.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace view = nmtools::view;

#define RUN_hardshrink_impl(...) \
nm::view::hardshrink(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs hardshrink fn to callable lambda
#define RUN_hardshrink(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("hardshrink-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_hardshrink_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_hardshrink(case_name, ...) \
RUN_hardshrink_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define HARDSHRINK_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(activations, hardshrink, case_name); \
    using namespace args; \
    auto result = RUN_hardshrink(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("hardshrink(case1)" * doctest::test_suite("view::hardshrink"))
{
    HARDSHRINK_SUBCASE(case1, a);
    HARDSHRINK_SUBCASE(case1, a_a);
    HARDSHRINK_SUBCASE(case1, a_f);
    HARDSHRINK_SUBCASE(case1, a_h);
    HARDSHRINK_SUBCASE(case1, a_d);
}

TEST_CASE("hardshrink(case2)" * doctest::test_suite("view::hardshrink"))
{
    HARDSHRINK_SUBCASE(case2, a, lambda);
    HARDSHRINK_SUBCASE(case2, a_a, lambda);
    HARDSHRINK_SUBCASE(case2, a_f, lambda);
    HARDSHRINK_SUBCASE(case2, a_h, lambda);
    HARDSHRINK_SUBCASE(case2, a_d, lambda);
}