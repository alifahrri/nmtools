#include "nmtools/array/array/ufuncs/rint.hpp"
#include "nmtools/testing/data/array/rint.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;

#define RUN_rint_impl(...) \
nm::array::rint(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs rint fn to callable lambda
#define RUN_rint(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("rint-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_rint_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_rint(case_name, ...) \
RUN_rint_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define RINT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, rint, case_name); \
    using namespace args; \
    auto result = RUN_rint(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("rint(case1)" * doctest::test_suite("array::rint"))
{
    RINT_SUBCASE( case1,   a);
    RINT_SUBCASE( case1, a_a);
    RINT_SUBCASE( case1, a_f);
    RINT_SUBCASE( case1, a_d);
    RINT_SUBCASE( case1, a_h);
}