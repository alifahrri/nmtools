#include "nmtools/array/ufuncs/isfinite.hpp"
#include "nmtools/testing/data/array/isfinite.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>
#include <algorithm> // std::max

namespace nm = nmtools;
namespace na = nmtools;

#define RUN_isfinite_impl(...) \
nmtools::isfinite(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs isfinite fn to callable lambda
#define RUN_isfinite(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("isfinite-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_isfinite_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_isfinite(case_name, ...) \
RUN_isfinite_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define ISFINITE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, isfinite, case_name); \
    using namespace args; \
    auto result = RUN_isfinite(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("isfinite(case1)" * doctest::test_suite("array::isfinite"))
{
    ISFINITE_SUBCASE( case1,   a );
    ISFINITE_SUBCASE( case1, a_a );
    ISFINITE_SUBCASE( case1, a_f );
    // TODO: drop support for vector of bool
    #if 0
    ISFINITE_SUBCASE( case1, a_d );
    ISFINITE_SUBCASE( case1, a_h );
    #endif
}