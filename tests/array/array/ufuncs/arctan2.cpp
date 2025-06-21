#include "nmtools/array/ufuncs/arctan2.hpp"
#include "nmtools/testing/data/array/arctan2.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nmtools;
namespace view = nm::view;

#define RUN_arctan2_impl(...) \
nmtools::arctan2(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs arctan2 fn to callable lambda
#define RUN_arctan2(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("arctan2-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_arctan2_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_arctan2(case_name, ...) \
RUN_arctan2_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define ARCTAN2_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, arctan2, case_name); \
    using namespace args; \
    auto result = RUN_arctan2(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("arctan2(case1)" * doctest::test_suite("array::arctan2"))
{
    ARCTAN2_SUBCASE( case1,   a,   b );
    ARCTAN2_SUBCASE( case1, a_a, b_a );
    ARCTAN2_SUBCASE( case1, a_f, b_f );
    ARCTAN2_SUBCASE( case1, a_d, b_d );
    ARCTAN2_SUBCASE( case1, a_h, b_h );
}