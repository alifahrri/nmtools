#include "nmtools/array/ufuncs/bitwise_xor.hpp"
#include "nmtools/testing/data/array/bitwise_xor.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nmtools;

#define RUN_bitwise_xor_impl(...) \
nmtools::bitwise_xor(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs bitwise_xor fn to callable lambda
#define RUN_bitwise_xor(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("bitwise_xor-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_bitwise_xor_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_bitwise_xor(case_name, ...) \
RUN_bitwise_xor_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define BITWISE_XOR_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, bitwise_xor, case_name); \
    using namespace args; \
    auto result = RUN_bitwise_xor(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("bitwise_xor(case1)" * doctest::test_suite("array::bitwise_xor"))
{
    BITWISE_XOR_SUBCASE( case1,   a,   b );
    BITWISE_XOR_SUBCASE( case1, a_a, b_a );
    BITWISE_XOR_SUBCASE( case1, a_f, b_f );
    BITWISE_XOR_SUBCASE( case1, a_d, b_d );
    BITWISE_XOR_SUBCASE( case1, a_h, b_h );
}

TEST_CASE("bitwise_xor(case2)" * doctest::test_suite("array::bitwise_xor"))
{
    BITWISE_XOR_SUBCASE( case2,   a, b );
    BITWISE_XOR_SUBCASE( case2, a_a, b );
    BITWISE_XOR_SUBCASE( case2, a_f, b );
    BITWISE_XOR_SUBCASE( case2, a_d, b );
    BITWISE_XOR_SUBCASE( case2, a_h, b );
}