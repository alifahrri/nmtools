#include "nmtools/array/ufuncs/arctan.hpp"
#include "nmtools/testing/data/array/arctan.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define RUN_arctan_impl(...) \
nm::array::arctan(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs arctan fn to callable lambda
#define RUN_arctan(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("arctan-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_arctan_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_arctan(case_name, ...) \
RUN_arctan_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define ARCTAN_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, arctan, case_name); \
    using namespace args; \
    auto result = RUN_arctan(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("arctan(case1)" * doctest::test_suite("array::arctan"))
{
    ARCTAN_SUBCASE( case1,   a);
    ARCTAN_SUBCASE( case1, a_a);
    ARCTAN_SUBCASE( case1, a_f);
    ARCTAN_SUBCASE( case1, a_d);
    ARCTAN_SUBCASE( case1, a_h);
}