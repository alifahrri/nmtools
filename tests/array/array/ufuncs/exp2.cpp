#include "nmtools/array/ufuncs/exp2.hpp"
#include "nmtools/testing/data/array/exp2.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define RUN_exp2_impl(...) \
nm::array::exp2(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs exp2 fn to callable lambda
#define RUN_exp2(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("exp2-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_exp2_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_exp2(case_name, ...) \
RUN_exp2_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define EXP2_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, exp2, case_name); \
    using namespace args; \
    auto result = RUN_exp2(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("exp2(case1)" * doctest::test_suite("array::exp2"))
{
    EXP2_SUBCASE( case1,   a);
    EXP2_SUBCASE( case1, a_a);
    EXP2_SUBCASE( case1, a_f);
    EXP2_SUBCASE( case1, a_d);
    EXP2_SUBCASE( case1, a_h);
}