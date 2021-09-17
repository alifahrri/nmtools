#include "nmtools/array/view/activations/elu.hpp"
#include "nmtools/testing/data/array/elu.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace view = nmtools::view;

#define RUN_elu_impl(...) \
nm::view::elu(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs elu fn to callable lambda
#define RUN_elu(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("elu-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_elu_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_elu(case_name, ...) \
RUN_elu_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define ELU_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(activations, elu, case_name); \
    using namespace args; \
    auto result = RUN_elu(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("elu(case1)" * doctest::test_suite("view::elu"))
{
    ELU_SUBCASE(case1, a);
    ELU_SUBCASE(case1, a_a);
    ELU_SUBCASE(case1, a_f);
    ELU_SUBCASE(case1, a_h);
    ELU_SUBCASE(case1, a_d);
}

TEST_CASE("elu(case2)" * doctest::test_suite("view::elu"))
{
    ELU_SUBCASE(case2, a, alpha);
    ELU_SUBCASE(case2, a_a, alpha);
    ELU_SUBCASE(case2, a_f, alpha);
    ELU_SUBCASE(case2, a_h, alpha);
    ELU_SUBCASE(case2, a_d, alpha);
}