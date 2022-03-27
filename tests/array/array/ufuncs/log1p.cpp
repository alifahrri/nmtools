#include "nmtools/array/array/ufuncs/log1p.hpp"
#include "nmtools/testing/data/array/log1p.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;

#define RUN_log1p_impl(...) \
nm::array::log1p(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs log1p fn to callable lambda
#define RUN_log1p(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("log1p-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_log1p_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_log1p(case_name, ...) \
RUN_log1p_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define LOG1P_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, log1p, case_name); \
    using namespace args; \
    auto result = RUN_log1p(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("log1p(case1)" * doctest::test_suite("array::log1p"))
{
    LOG1P_SUBCASE( case1,   a);
    LOG1P_SUBCASE( case1, a_a);
    LOG1P_SUBCASE( case1, a_v);
    LOG1P_SUBCASE( case1, a_f);
    LOG1P_SUBCASE( case1, a_d);
    LOG1P_SUBCASE( case1, a_h);
}