#include "nmtools/array/ufuncs/ceil.hpp"
#include "nmtools/testing/data/array/ceil.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;

#define RUN_ceil_impl(...) \
nm::array::ceil(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs ceil fn to callable lambda
#define RUN_ceil(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("ceil-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_ceil_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_ceil(case_name, ...) \
RUN_ceil_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define CEIL_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, ceil, case_name); \
    using namespace args; \
    auto result = RUN_ceil(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("ceil(case1)" * doctest::test_suite("array::ceil"))
{
    CEIL_SUBCASE( case1,   a);
    CEIL_SUBCASE( case1, a_a);
    CEIL_SUBCASE( case1, a_f);
    CEIL_SUBCASE( case1, a_d);
    CEIL_SUBCASE( case1, a_h);
}