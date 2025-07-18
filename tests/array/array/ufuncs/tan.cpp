#include "nmtools/array/ufuncs/tan.hpp"
#include "nmtools/testing/data/array/tan.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nmtools;

#define RUN_tan_impl(...) \
nmtools::tan(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs tan fn to callable lambda
#define RUN_tan(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("tan-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_tan_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_tan(case_name, ...) \
RUN_tan_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define TAN_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, tan, case_name); \
    using namespace args; \
    auto result = RUN_tan(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("tan(case1)" * doctest::test_suite("array::tan"))
{
    TAN_SUBCASE( case1,   a);
    TAN_SUBCASE( case1, a_a);
    TAN_SUBCASE( case1, a_f);
    TAN_SUBCASE( case1, a_d);
    TAN_SUBCASE( case1, a_h);
}