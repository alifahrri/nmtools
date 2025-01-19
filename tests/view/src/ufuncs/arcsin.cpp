#include "nmtools/array/ufuncs/arcsin.hpp"
#include "nmtools/testing/data/array/arcsin.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define RUN_arcsin_impl(...) \
nm::view::arcsin(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs arcsin fn to callable lambda
#define RUN_arcsin(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("arcsin-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_arcsin_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_arcsin(case_name, ...) \
RUN_arcsin_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define ARCSIN_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, arcsin, case_name); \
    using namespace args; \
    auto result = RUN_arcsin(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("arcsin(case1)" * doctest::test_suite("view::arcsin"))
{
    ARCSIN_SUBCASE( case1,   a);
    ARCSIN_SUBCASE( case1, a_a);
    ARCSIN_SUBCASE( case1, a_f);
    ARCSIN_SUBCASE( case1, a_d);
    ARCSIN_SUBCASE( case1, a_h);
}