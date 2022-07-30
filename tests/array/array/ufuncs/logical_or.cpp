#include "nmtools/array/array/ufuncs/logical_or.hpp"
#include "nmtools/testing/data/array/logical_or.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>
#include <algorithm> // std::max

namespace nm = nmtools;
namespace na = nm::array;

#define RUN_logical_or_impl(...) \
nm::array::logical_or(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs logical_or fn to callable lambda
#define RUN_logical_or(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("logical_or-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_logical_or_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_logical_or(case_name, ...) \
RUN_logical_or_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define LOGICAL_OR_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, logical_or, case_name); \
    using namespace args; \
    auto result = RUN_logical_or(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("logical_or(case1)" * doctest::test_suite("array::logical_or"))
{
    LOGICAL_OR_SUBCASE( case1,   a,   b );
    LOGICAL_OR_SUBCASE( case1, a_a, b_a );
    LOGICAL_OR_SUBCASE( case1, a_f, b_f );
    LOGICAL_OR_SUBCASE( case1, a_d, b_d );
    LOGICAL_OR_SUBCASE( case1, a_h, b_h );
}

TEST_CASE("logical_or(case2)" * doctest::test_suite("array::logical_or"))
{
    LOGICAL_OR_SUBCASE( case2,   a, b );
    LOGICAL_OR_SUBCASE( case2, a_a, b );
    LOGICAL_OR_SUBCASE( case2, a_f, b );
    LOGICAL_OR_SUBCASE( case2, a_d, b );
    LOGICAL_OR_SUBCASE( case2, a_h, b );
}