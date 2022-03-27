#include "nmtools/array/view/activations/softsign.hpp"
#include "nmtools/testing/data/array/softsign.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace view = nmtools::view;

#define RUN_softsign_impl(...) \
nm::view::softsign(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs softsign fn to callable lambda
#define RUN_softsign(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("softsign-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_softsign_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_softsign(case_name, ...) \
RUN_softsign_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define SOFTSIGN_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(activations, softsign, case_name); \
    using namespace args; \
    auto result = RUN_softsign(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("softsign(case1)" * doctest::test_suite("view::softsign"))
{
    SOFTSIGN_SUBCASE(case1, a);
    SOFTSIGN_SUBCASE(case1, a_a);
    SOFTSIGN_SUBCASE(case1, a_f);
    SOFTSIGN_SUBCASE(case1, a_h);
    SOFTSIGN_SUBCASE(case1, a_d);
}