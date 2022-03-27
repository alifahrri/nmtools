#include "nmtools/array/array/ufuncs/log.hpp"
#include "nmtools/testing/data/array/log.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;

#define RUN_log_impl(...) \
nm::array::log(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs log fn to callable lambda
#define RUN_log(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("log-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_log_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_log(case_name, ...) \
RUN_log_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define LOG_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, log, case_name); \
    using namespace args; \
    auto result = RUN_log(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("log(case1)" * doctest::test_suite("array::log"))
{
    LOG_SUBCASE( case1,   a);
    LOG_SUBCASE( case1, a_a);
    LOG_SUBCASE( case1, a_v);
    LOG_SUBCASE( case1, a_f);
    LOG_SUBCASE( case1, a_d);
    LOG_SUBCASE( case1, a_h);
}