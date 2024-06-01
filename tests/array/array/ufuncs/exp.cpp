#include "nmtools/array/array/ufuncs/exp.hpp"
#include "nmtools/testing/data/array/exp.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;

#define RUN_exp_impl(...) \
nm::array::exp(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs exp fn to callable lambda
#define RUN_exp(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("exp-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_exp_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_exp(case_name, ...) \
RUN_exp_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define EXP_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, exp, case_name); \
    using namespace args; \
    auto result = RUN_exp(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("exp(case1)" * doctest::test_suite("array::exp"))
{
    EXP_SUBCASE( case1,   a);
    EXP_SUBCASE( case1, a_a);
    EXP_SUBCASE( case1, a_f);
    EXP_SUBCASE( case1, a_d);
    EXP_SUBCASE( case1, a_h);
}