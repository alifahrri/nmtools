#include "nmtools/array/array/cumsum.hpp"
#include "nmtools/testing/data/array/add.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace array = nm::array;

#define RUN_cumsum_impl(...) \
nm::array::cumsum(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs cumsum fn to callable lambda
#define RUN_cumsum(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("cumsum-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_cumsum_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_cumsum(case_name, ...) \
RUN_cumsum_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define CUMSUM_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    /* using test case from accumulate_add since they're basically the same */ \
    NMTOOLS_TESTING_DECLARE_NS(view, accumulate_add, case_name); \
    using namespace args; \
    auto result = RUN_cumsum(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("cumsum(case1)" * doctest::test_suite("array::cumsum"))
{
    CUMSUM_SUBCASE( case1,   a, axis );
    CUMSUM_SUBCASE( case1, a_a, axis );
    CUMSUM_SUBCASE( case1, a_v, axis );
    CUMSUM_SUBCASE( case1, a_f, axis );
    // not yet supported,
    // cant figure out apply_slice for dynamic dim array yet
    // CUMSUM_SUBCASE( case1, a_d, axis );
    CUMSUM_SUBCASE( case1, a_h, axis );
}

TEST_CASE("cumsum(case2)" * doctest::test_suite("array::cumsum"))
{
    CUMSUM_SUBCASE( case2,   a, axis );
    CUMSUM_SUBCASE( case2, a_a, axis );
    CUMSUM_SUBCASE( case2, a_v, axis );
    CUMSUM_SUBCASE( case2, a_f, axis );
    // not yet supported,
    // cant figure out apply_slice for dynamic dim array yet
    // CUMSUM_SUBCASE( case2, a_d, axis );
    CUMSUM_SUBCASE( case2, a_h, axis );
}

TEST_CASE("cumsum(case3)" * doctest::test_suite("array::cumsum"))
{
    CUMSUM_SUBCASE( case3,   a, axis );
    CUMSUM_SUBCASE( case3, a_a, axis );
    CUMSUM_SUBCASE( case3, a_v, axis );
    CUMSUM_SUBCASE( case3, a_f, axis );
    // not yet supported,
    // cant figure out apply_slice for dynamic dim array yet
    // CUMSUM_SUBCASE( case3, a_d, axis );
    CUMSUM_SUBCASE( case3, a_h, axis );
}