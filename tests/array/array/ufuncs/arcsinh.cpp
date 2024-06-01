#include "nmtools/array/array/ufuncs/arcsinh.hpp"
#include "nmtools/testing/data/array/arcsinh.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define RUN_arcsinh_impl(...) \
nm::array::arcsinh(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs arcsinh fn to callable lambda
#define RUN_arcsinh(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("arcsinh-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_arcsinh_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_arcsinh(case_name, ...) \
RUN_arcsinh_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define ARCSINH_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, arcsinh, case_name); \
    using namespace args; \
    auto result = RUN_arcsinh(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("arcsinh(case1)" * doctest::test_suite("array::arcsinh"))
{
    ARCSINH_SUBCASE( case1,   a);
    ARCSINH_SUBCASE( case1, a_a);
    ARCSINH_SUBCASE( case1, a_f);
    ARCSINH_SUBCASE( case1, a_d);
    ARCSINH_SUBCASE( case1, a_h);
}