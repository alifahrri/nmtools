#include "nmtools/array/ufuncs/logical_not.hpp"
#include "nmtools/testing/data/array/logical_not.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>
#include <algorithm> // std::max

namespace nm = nmtools;
namespace na = nm::array;

#define RUN_logical_not_impl(...) \
nm::array::logical_not(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs logical_not fn to callable lambda
#define RUN_logical_not(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("logical_not-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_logical_not_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_logical_not(case_name, ...) \
RUN_logical_not_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define LOGICAL_NOT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, logical_not, case_name); \
    using namespace args; \
    auto result = RUN_logical_not(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("logical_not(case1)" * doctest::test_suite("array::logical_not"))
{
    LOGICAL_NOT_SUBCASE( case1,   a );
    LOGICAL_NOT_SUBCASE( case1, a_a );
    LOGICAL_NOT_SUBCASE( case1, a_f );
    // TODO: drop support for vector of bool
    #if 0
    LOGICAL_NOT_SUBCASE( case1, a_d );
    LOGICAL_NOT_SUBCASE( case1, a_h );
    #endif
}