#include "nmtools/array/view/activations/mish.hpp"
#include "nmtools/testing/data/array/mish.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace view = nmtools::view;

#define RUN_mish_impl(...) \
nm::view::mish(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs mish fn to callable lambda
#define RUN_mish(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("mish-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_mish_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_mish(case_name, ...) \
RUN_mish_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define MISH_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(activations, mish, case_name); \
    using namespace args; \
    auto result = RUN_mish(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("mish(case1)" * doctest::test_suite("view::mish"))
{
    MISH_SUBCASE(case1, a);
    MISH_SUBCASE(case1, a_a);
    MISH_SUBCASE(case1, a_f);
    MISH_SUBCASE(case1, a_h);
    MISH_SUBCASE(case1, a_d);
}