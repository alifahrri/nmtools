#include "nmtools/array/array/ufuncs/sinh.hpp"
#include "nmtools/testing/data/array/sinh.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

// lower testing precision for sinh
#undef  NMTOOLS_TESTING_PRECISION
#define NMTOOLS_TESTING_PRECISION 7e-5

namespace nm = nmtools;
namespace na = nm::array;

#define RUN_sinh_impl(...) \
nm::array::sinh(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs sinh fn to callable lambda
#define RUN_sinh(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("sinh-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_sinh_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_sinh(case_name, ...) \
RUN_sinh_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define SINH_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, sinh, case_name); \
    using namespace args; \
    auto result = RUN_sinh(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("sinh(case1)" * doctest::test_suite("array::sinh"))
{
    SINH_SUBCASE( case1,   a);
    SINH_SUBCASE( case1, a_a);
    SINH_SUBCASE( case1, a_f);
    SINH_SUBCASE( case1, a_d);
    SINH_SUBCASE( case1, a_h);
}