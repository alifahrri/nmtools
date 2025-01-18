#include "nmtools/array/ufuncs/arccos.hpp"
#include "nmtools/testing/data/array/arccos.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define RUN_arccos_impl(...) \
nm::array::arccos(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs arccos fn to callable lambda
#define RUN_arccos(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("arccos-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_arccos_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_arccos(case_name, ...) \
RUN_arccos_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define ARCCOS_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, arccos, case_name); \
    using namespace args; \
    auto result = RUN_arccos(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("arccos(case1)" * doctest::test_suite("array::arccos"))
{
    ARCCOS_SUBCASE( case1,   a);
    ARCCOS_SUBCASE( case1, a_a);
    ARCCOS_SUBCASE( case1, a_f);
    ARCCOS_SUBCASE( case1, a_d);
    ARCCOS_SUBCASE( case1, a_h);
}