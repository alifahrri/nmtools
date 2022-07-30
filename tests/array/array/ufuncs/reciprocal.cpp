#include "nmtools/array/array/ufuncs/reciprocal.hpp"
#include "nmtools/testing/data/array/reciprocal.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;

#define RUN_reciprocal_impl(...) \
nm::array::reciprocal(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs reciprocal fn to callable lambda
#define RUN_reciprocal(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("reciprocal-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_reciprocal_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_reciprocal(case_name, ...) \
RUN_reciprocal_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define RECIPROCAL_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, reciprocal, case_name); \
    using namespace args; \
    auto result = RUN_reciprocal(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("reciprocal(case1)" * doctest::test_suite("array::reciprocal"))
{
    RECIPROCAL_SUBCASE( case1,   a);
    RECIPROCAL_SUBCASE( case1, a_a);
    RECIPROCAL_SUBCASE( case1, a_f);
    RECIPROCAL_SUBCASE( case1, a_d);
    RECIPROCAL_SUBCASE( case1, a_h);
}