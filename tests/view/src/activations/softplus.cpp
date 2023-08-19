#include "nmtools/array/view/activations/softplus.hpp"
#include "nmtools/testing/data/array/softplus.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace view = nmtools::view;

#define RUN_softplus_impl(...) \
nm::view::softplus(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs softplus fn to callable lambda
#define RUN_softplus(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("softplus-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_softplus_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_softplus(case_name, ...) \
RUN_softplus_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define SOFTPLUS_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(activations, softplus, case_name); \
    using namespace args; \
    auto result = RUN_softplus(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("softplus(case1)" * doctest::test_suite("view::softplus"))
{
    SOFTPLUS_SUBCASE(case1, a);
    SOFTPLUS_SUBCASE(case1, a_a);
    SOFTPLUS_SUBCASE(case1, a_f);
    SOFTPLUS_SUBCASE(case1, a_h);
    SOFTPLUS_SUBCASE(case1, a_d);
}