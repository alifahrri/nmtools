#include "nmtools/array/ufuncs/isinf.hpp"
#include "nmtools/testing/data/array/isinf.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>
#include <algorithm> // std::max

namespace nm = nmtools;
namespace na = nm::array;

#define RUN_isinf_impl(...) \
nm::array::isinf(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs isinf fn to callable lambda
#define RUN_isinf(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("isinf-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_isinf_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_isinf(case_name, ...) \
RUN_isinf_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define ISINF_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, isinf, case_name); \
    using namespace args; \
    auto result = RUN_isinf(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("isinf(case1)" * doctest::test_suite("array::isinf"))
{
    ISINF_SUBCASE( case1,   a );
    ISINF_SUBCASE( case1, a_a );
    ISINF_SUBCASE( case1, a_f );
    // TODO: drop support for vector of bool
    #if 0
    ISINF_SUBCASE( case1, a_d );
    ISINF_SUBCASE( case1, a_h );
    #endif
}