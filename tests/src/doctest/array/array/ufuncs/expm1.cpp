#include "nmtools/array/array/ufuncs/expm1.hpp"
#include "nmtools/testing/data/array/expm1.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

// lower testing precision for expm1
#undef NMTOOLS_TESTING_OUTPUT_PRECISION
#define NMTOOLS_TESTING_OUTPUT_PRECISION 1e-5

namespace nm = nmtools;
namespace na = nm::array;

#define RUN_expm1_impl(...) \
nm::array::expm1(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs expm1 fn to callable lambda
#define RUN_expm1(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("expm1-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_expm1_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_expm1(case_name, ...) \
RUN_expm1_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define EXPM1_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, expm1, case_name); \
    using namespace args; \
    auto result = RUN_expm1(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("expm1(case1)" * doctest::test_suite("array::expm1"))
{
    EXPM1_SUBCASE( case1,   a);
    EXPM1_SUBCASE( case1, a_a);
    EXPM1_SUBCASE( case1, a_v);
    EXPM1_SUBCASE( case1, a_f);
    EXPM1_SUBCASE( case1, a_d);
    EXPM1_SUBCASE( case1, a_h);
}