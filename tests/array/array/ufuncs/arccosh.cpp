#include "nmtools/array/array/ufuncs/arccosh.hpp"
#include "nmtools/testing/data/array/arccosh.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define RUN_arccosh_impl(...) \
nm::array::arccosh(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs arccosh fn to callable lambda
#define RUN_arccosh(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("arccosh-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_arccosh_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_arccosh(case_name, ...) \
RUN_arccosh_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define ARCCOSH_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, arccosh, case_name); \
    using namespace args; \
    auto result = RUN_arccosh(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("arccosh(case1)" * doctest::test_suite("array::arccosh"))
{
    ARCCOSH_SUBCASE( case1,   a);
    ARCCOSH_SUBCASE( case1, a_a);
    ARCCOSH_SUBCASE( case1, a_f);
    ARCCOSH_SUBCASE( case1, a_d);
    ARCCOSH_SUBCASE( case1, a_h);
}