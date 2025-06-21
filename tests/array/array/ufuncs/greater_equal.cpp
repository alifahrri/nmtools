#include "nmtools/array/ufuncs/greater_equal.hpp"
#include "nmtools/testing/data/array/greater_equal.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>
#include <algorithm> // std::max

namespace nm = nmtools;
namespace na = nmtools;

#define RUN_greater_equal_impl(...) \
nmtools::greater_equal(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs greater_equal fn to callable lambda
#define RUN_greater_equal(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("greater_equal-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_greater_equal_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_greater_equal(case_name, ...) \
RUN_greater_equal_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define GREATER_EQUAL_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, greater_equal, case_name); \
    using namespace args; \
    auto result = RUN_greater_equal(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("greater_equal(case1)" * doctest::test_suite("array::greater_equal"))
{
    GREATER_EQUAL_SUBCASE( case1,   a,   b );
    GREATER_EQUAL_SUBCASE( case1, a_a, b_a );
    GREATER_EQUAL_SUBCASE( case1, a_f, b_f );
    // TODO: drop support for vector of bool
    #if 0
    GREATER_EQUAL_SUBCASE( case1, a_d, b_d );
    GREATER_EQUAL_SUBCASE( case1, a_h, b_h );
    #endif
}

TEST_CASE("greater_equal(case2)" * doctest::test_suite("array::greater_equal"))
{
    GREATER_EQUAL_SUBCASE( case2,   a, b );
    GREATER_EQUAL_SUBCASE( case2, a_a, b );
    GREATER_EQUAL_SUBCASE( case2, a_f, b );
    // TODO: drop support for vector of bool
    #if 0
    GREATER_EQUAL_SUBCASE( case2, a_d, b );
    GREATER_EQUAL_SUBCASE( case2, a_h, b );
    #endif
}