#include "nmtools/array/ufuncs/bitwise_and.hpp"
#include "nmtools/testing/data/array/bitwise_and.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nmtools;
namespace view = nm::view;

#define RUN_bitwise_and_impl(...) \
nmtools::bitwise_and(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs bitwise_and fn to callable lambda
#define RUN_bitwise_and(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("bitwise_and-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_bitwise_and_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_bitwise_and(case_name, ...) \
RUN_bitwise_and_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define BITWISE_AND_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, bitwise_and, case_name); \
    using namespace args; \
    auto result = RUN_bitwise_and(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("bitwise_and(case1)" * doctest::test_suite("array::bitwise_and"))
{
    BITWISE_AND_SUBCASE( case1,   a,   b );
    BITWISE_AND_SUBCASE( case1, a_a, b_a );
    BITWISE_AND_SUBCASE( case1, a_f, b_f );
    BITWISE_AND_SUBCASE( case1, a_d, b_d );
    BITWISE_AND_SUBCASE( case1, a_h, b_h );
}

TEST_CASE("bitwise_and(case2)" * doctest::test_suite("array::bitwise_and"))
{
    BITWISE_AND_SUBCASE( case2,   a, b );
    BITWISE_AND_SUBCASE( case2, a_a, b );
    BITWISE_AND_SUBCASE( case2, a_f, b );
    BITWISE_AND_SUBCASE( case2, a_d, b );
    BITWISE_AND_SUBCASE( case2, a_h, b );
}