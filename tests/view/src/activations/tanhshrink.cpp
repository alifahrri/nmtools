#include "nmtools/array/activations/tanhshrink.hpp"
#include "nmtools/testing/data/array/tanhshrink.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace view = nmtools::view;

#define RUN_tanhshrink_impl(...) \
nm::view::tanhshrink(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs tanhshrink fn to callable lambda
#define RUN_tanhshrink(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("tanhshrink-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_tanhshrink_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_tanhshrink(case_name, ...) \
RUN_tanhshrink_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define TANHSHRINK_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(activations, tanhshrink, case_name); \
    using namespace args; \
    auto result = RUN_tanhshrink(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("tanhshrink(case1)" * doctest::test_suite("view::tanhshrink"))
{
    TANHSHRINK_SUBCASE(case1, a);
    TANHSHRINK_SUBCASE(case1, a_a);
    TANHSHRINK_SUBCASE(case1, a_f);
    TANHSHRINK_SUBCASE(case1, a_h);
    TANHSHRINK_SUBCASE(case1, a_d);
}