#include "nmtools/array/array/ufuncs/cosh.hpp"
#include "nmtools/testing/data/array/cosh.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

// lower testing precision for cosh
#undef NMTOOLS_TESTING_PRECISION
#define NMTOOLS_TESTING_PRECISION 1e-5

namespace nm = nmtools;
namespace na = nm::array;

#define RUN_cosh_impl(...) \
nm::array::cosh(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs cosh fn to callable lambda
#define RUN_cosh(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("cosh-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_cosh_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_cosh(case_name, ...) \
RUN_cosh_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define COSH_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, cosh, case_name); \
    using namespace args; \
    auto result = RUN_cosh(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("cosh(case1)" * doctest::test_suite("array::cosh"))
{
    COSH_SUBCASE( case1,   a);
    COSH_SUBCASE( case1, a_a);
    COSH_SUBCASE( case1, a_f);
    COSH_SUBCASE( case1, a_d);
    COSH_SUBCASE( case1, a_h);
}