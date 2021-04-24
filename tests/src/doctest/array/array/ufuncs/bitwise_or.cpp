#include "nmtools/array/array/ufuncs/bitwise_or.hpp"
#include "nmtools/testing/data/array/bitwise_or.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define RUN_bitwise_or_impl(...) \
nm::array::bitwise_or(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs bitwise_or fn to callable lambda
#define RUN_bitwise_or(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("bitwise_or-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_bitwise_or_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_bitwise_or(case_name, ...) \
RUN_bitwise_or_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define BITWISE_OR_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, bitwise_or, case_name); \
    using namespace args; \
    auto result = RUN_bitwise_or(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("bitwise_or(case1)" * doctest::test_suite("array::bitwise_or"))
{
    BITWISE_OR_SUBCASE( case1,   a,   b );
    BITWISE_OR_SUBCASE( case1, a_a, b_a );
    BITWISE_OR_SUBCASE( case1, a_v, b_v );
    BITWISE_OR_SUBCASE( case1, a_f, b_f );
    BITWISE_OR_SUBCASE( case1, a_d, b_d );
    BITWISE_OR_SUBCASE( case1, a_h, b_h );
}

TEST_CASE("bitwise_or(case2)" * doctest::test_suite("array::bitwise_or"))
{
    BITWISE_OR_SUBCASE( case2,   a, b );
    BITWISE_OR_SUBCASE( case2, a_a, b );
    BITWISE_OR_SUBCASE( case2, a_v, b );
    BITWISE_OR_SUBCASE( case2, a_f, b );
    BITWISE_OR_SUBCASE( case2, a_d, b );
    BITWISE_OR_SUBCASE( case2, a_h, b );
}