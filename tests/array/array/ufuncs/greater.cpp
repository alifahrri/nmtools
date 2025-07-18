#include "nmtools/array/ufuncs/greater.hpp"
#include "nmtools/testing/data/array/greater.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>
#include <algorithm> // std::max

namespace nm = nmtools;
namespace na = nmtools;

#define RUN_greater_impl(...) \
nmtools::greater(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs greater fn to callable lambda
#define RUN_greater(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("greater-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_greater_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_greater(case_name, ...) \
RUN_greater_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define GREATER_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, greater, case_name); \
    using namespace args; \
    auto result = RUN_greater(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("greater(case1)" * doctest::test_suite("array::greater"))
{
    GREATER_SUBCASE( case1,   a,   b );
    GREATER_SUBCASE( case1, a_a, b_a );
    GREATER_SUBCASE( case1, a_f, b_f );
    // TODO: drop support for vector of bool
    #if 0
    GREATER_SUBCASE( case1, a_d, b_d );
    GREATER_SUBCASE( case1, a_h, b_h );
    #endif
}

TEST_CASE("greater(case2)" * doctest::test_suite("array::greater"))
{
    GREATER_SUBCASE( case2,   a, b );
    GREATER_SUBCASE( case2, a_a, b );
    GREATER_SUBCASE( case2, a_f, b );
    // TODO: drop support for vector of bool
    #if 0
    GREATER_SUBCASE( case2, a_d, b );
    GREATER_SUBCASE( case2, a_h, b );
    #endif
}