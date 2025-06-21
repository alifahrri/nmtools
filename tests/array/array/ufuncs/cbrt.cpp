#include "nmtools/array/ufuncs/cbrt.hpp"
#include "nmtools/testing/data/array/cbrt.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nmtools;

#define RUN_cbrt_impl(...) \
nmtools::cbrt(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs cbrt fn to callable lambda
#define RUN_cbrt(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("cbrt-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_cbrt_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_cbrt(case_name, ...) \
RUN_cbrt_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define CBRT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, cbrt, case_name); \
    using namespace args; \
    auto result = RUN_cbrt(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("cbrt(case1)" * doctest::test_suite("array::cbrt"))
{
    CBRT_SUBCASE( case1,   a);
    CBRT_SUBCASE( case1, a_a);
    CBRT_SUBCASE( case1, a_f);
    CBRT_SUBCASE( case1, a_d);
    CBRT_SUBCASE( case1, a_h);
}