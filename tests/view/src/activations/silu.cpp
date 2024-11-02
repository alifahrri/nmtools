#include "nmtools/array/view/activations/silu.hpp"
#include "nmtools/testing/data/array/silu.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace view = nmtools::view;

#define RUN_silu_impl(...) \
nm::view::silu(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs silu fn to callable lambda
#define RUN_silu(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("silu-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_silu_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_silu(case_name, ...) \
RUN_silu_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define SILU_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(activations, silu, case_name); \
    using namespace args; \
    auto result = RUN_silu(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("silu(case1)" * doctest::test_suite("view::silu"))
{
    SILU_SUBCASE(case1, a);
    SILU_SUBCASE(case1, a_a);
    SILU_SUBCASE(case1, a_f);
    SILU_SUBCASE(case1, a_h);
    SILU_SUBCASE(case1, a_d);
}