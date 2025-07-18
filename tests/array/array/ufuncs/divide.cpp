#include "nmtools/array/ufuncs/divide.hpp"
#include "nmtools/testing/data/array/divide.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nmtools;
namespace view = nm::view;

#define RUN_divide_impl(...) \
nmtools::divide(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs divide fn to callable lambda
#define RUN_divide(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("divide-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_divide_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_divide(case_name, ...) \
RUN_divide_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define DIVIDE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, divide, case_name); \
    using namespace args; \
    auto result = RUN_divide(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("divide(case1)" * doctest::test_suite("array::divide"))
{
    DIVIDE_SUBCASE( case1,   a,   b );
    DIVIDE_SUBCASE( case1, a_a, b_a );
    DIVIDE_SUBCASE( case1, a_f, b_f );
    DIVIDE_SUBCASE( case1, a_d, b_d );
    DIVIDE_SUBCASE( case1, a_h, b_h );
}

TEST_CASE("divide(case2)" * doctest::test_suite("array::divide"))
{
    DIVIDE_SUBCASE( case2,   a, b );
    DIVIDE_SUBCASE( case2, a_a, b );
    DIVIDE_SUBCASE( case2, a_f, b );
    DIVIDE_SUBCASE( case2, a_d, b );
    DIVIDE_SUBCASE( case2, a_h, b );
}