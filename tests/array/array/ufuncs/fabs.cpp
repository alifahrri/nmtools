#include "nmtools/array/array/ufuncs/fabs.hpp"
#include "nmtools/testing/data/array/fabs.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define RUN_fabs_impl(...) \
nm::array::fabs(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs fabs fn to callable lambda
#define RUN_fabs(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("fabs-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_fabs_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_fabs(case_name, ...) \
RUN_fabs_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define FABS_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, fabs, case_name); \
    using namespace args; \
    auto result = RUN_fabs(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("fabs(case1)" * doctest::test_suite("array::fabs"))
{
    FABS_SUBCASE( case1,   a);
    FABS_SUBCASE( case1, a_a);
    FABS_SUBCASE( case1, a_f);
    FABS_SUBCASE( case1, a_d);
    FABS_SUBCASE( case1, a_h);
}