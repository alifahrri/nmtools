#include "nmtools/array/array/ufuncs/tanh.hpp"
#include "nmtools/testing/data/array/tanh.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;

#define RUN_tanh_impl(...) \
nm::array::tanh(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs tanh fn to callable lambda
#define RUN_tanh(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("tanh-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_tanh_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_tanh(case_name, ...) \
RUN_tanh_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define TANH_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, tanh, case_name); \
    using namespace args; \
    auto result = RUN_tanh(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("tanh(case1)" * doctest::test_suite("array::tanh"))
{
    TANH_SUBCASE( case1,   a);
    TANH_SUBCASE( case1, a_a);
    TANH_SUBCASE( case1, a_f);
    TANH_SUBCASE( case1, a_d);
    TANH_SUBCASE( case1, a_h);
}