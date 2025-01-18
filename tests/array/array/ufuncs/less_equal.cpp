#include "nmtools/array/ufuncs/less_equal.hpp"
#include "nmtools/testing/data/array/less_equal.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>
#include <algorithm> // std::max

namespace nm = nmtools;
namespace na = nm::array;

#define RUN_less_equal_impl(...) \
nm::array::less_equal(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs less_equal fn to callable lambda
#define RUN_less_equal(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("less_equal-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_less_equal_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_less_equal(case_name, ...) \
RUN_less_equal_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define LESS_EQUAL_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, less_equal, case_name); \
    using namespace args; \
    auto result = RUN_less_equal(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("less_equal(case1)" * doctest::test_suite("array::less_equal"))
{
    LESS_EQUAL_SUBCASE( case1,   a,   b );
    LESS_EQUAL_SUBCASE( case1, a_a, b_a );
    LESS_EQUAL_SUBCASE( case1, a_f, b_f );
    // TODO: drop support for vector of bool
    #if 0
    LESS_EQUAL_SUBCASE( case1, a_d, b_d );
    LESS_EQUAL_SUBCASE( case1, a_h, b_h );
    #endif
}

TEST_CASE("less_equal(case2)" * doctest::test_suite("array::less_equal"))
{
    LESS_EQUAL_SUBCASE( case2,   a, b );
    LESS_EQUAL_SUBCASE( case2, a_a, b );
    LESS_EQUAL_SUBCASE( case2, a_f, b );
    // TODO: drop support for vector of bool
    #if 0
    LESS_EQUAL_SUBCASE( case2, a_d, b );
    LESS_EQUAL_SUBCASE( case2, a_h, b );
    #endif
}