#include "nmtools/array/view/activations/hardswish.hpp"
#include "nmtools/testing/data/array/hardswish.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace view = nmtools::view;

#define RUN_hardswish_impl(...) \
nm::view::hardswish(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs hardswish fn to callable lambda
#define RUN_hardswish(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("hardswish-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_hardswish_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_hardswish(case_name, ...) \
RUN_hardswish_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define HARDSWISH_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(activations, hardswish, case_name); \
    using namespace args; \
    auto result = RUN_hardswish(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("hardswish(case1)" * doctest::test_suite("view::hardswish"))
{
    HARDSWISH_SUBCASE(case1, a);
    HARDSWISH_SUBCASE(case1, a_a);
    HARDSWISH_SUBCASE(case1, a_f);
    HARDSWISH_SUBCASE(case1, a_h);
    HARDSWISH_SUBCASE(case1, a_d);
}