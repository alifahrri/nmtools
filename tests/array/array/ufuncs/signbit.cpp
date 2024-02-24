#include "nmtools/array/array/ufuncs/signbit.hpp"
#include "nmtools/testing/data/array/signbit.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>
#include <algorithm> // std::max

namespace nm = nmtools;
namespace na = nm::array;

#define RUN_signbit_impl(...) \
nm::array::signbit(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs signbit fn to callable lambda
#define RUN_signbit(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("signbit-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_signbit_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_signbit(case_name, ...) \
RUN_signbit_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define SIGNBIT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, signbit, case_name); \
    using namespace args; \
    auto result = RUN_signbit(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("signbit(case1)" * doctest::test_suite("array::signbit"))
{
    SIGNBIT_SUBCASE( case1,   a );
    SIGNBIT_SUBCASE( case1, a_a );
    SIGNBIT_SUBCASE( case1, a_f );
    // TODO: drop support for vector of bool
    #if 0
    SIGNBIT_SUBCASE( case1, a_d );
    SIGNBIT_SUBCASE( case1, a_h );
    #endif
}