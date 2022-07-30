#include "nmtools/array/array/ufuncs/sqrt.hpp"
#include "nmtools/testing/data/array/sqrt.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;

#define RUN_sqrt_impl(...) \
nm::array::sqrt(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs sqrt fn to callable lambda
#define RUN_sqrt(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("sqrt-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_sqrt_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_sqrt(case_name, ...) \
RUN_sqrt_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define SQRT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, sqrt, case_name); \
    using namespace args; \
    auto result = RUN_sqrt(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("sqrt(case1)" * doctest::test_suite("array::sqrt"))
{
    SQRT_SUBCASE( case1,   a);
    SQRT_SUBCASE( case1, a_a);
    SQRT_SUBCASE( case1, a_f);
    SQRT_SUBCASE( case1, a_d);
    SQRT_SUBCASE( case1, a_h);
}