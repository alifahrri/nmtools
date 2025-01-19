#include "nmtools/array/ufuncs/floor.hpp"
#include "nmtools/testing/data/array/floor.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;

#define RUN_floor_impl(...) \
nm::array::floor(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs floor fn to callable lambda
#define RUN_floor(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("floor-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_floor_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_floor(case_name, ...) \
RUN_floor_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define FLOOR_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, floor, case_name); \
    using namespace args; \
    auto result = RUN_floor(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("floor(case1)" * doctest::test_suite("array::floor"))
{
    FLOOR_SUBCASE( case1,   a);
    FLOOR_SUBCASE( case1, a_a);
    FLOOR_SUBCASE( case1, a_f);
    FLOOR_SUBCASE( case1, a_d);
    FLOOR_SUBCASE( case1, a_h);
}