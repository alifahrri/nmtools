#include "nmtools/array/array/ufuncs/trunc.hpp"
#include "nmtools/testing/data/array/trunc.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;

#define RUN_trunc_impl(...) \
nm::array::trunc(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs trunc fn to callable lambda
#define RUN_trunc(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("trunc-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_trunc_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_trunc(case_name, ...) \
RUN_trunc_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define TRUNC_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, trunc, case_name); \
    using namespace args; \
    auto result = RUN_trunc(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("trunc(case1)" * doctest::test_suite("array::trunc"))
{
    TRUNC_SUBCASE( case1,   a);
    TRUNC_SUBCASE( case1, a_a);
    TRUNC_SUBCASE( case1, a_f);
    TRUNC_SUBCASE( case1, a_d);
    TRUNC_SUBCASE( case1, a_h);
}