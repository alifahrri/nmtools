#include "nmtools/array/view/ufuncs/square.hpp"
#include "nmtools/testing/data/array/square.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define RUN_square_impl(...) \
nm::view::square(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs square fn to callable lambda
#define RUN_square(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("square-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_square_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_square(case_name, ...) \
RUN_square_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define SQUARE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, square, case_name); \
    using namespace args; \
    auto result = RUN_square(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("square(case1)" * doctest::test_suite("view::square"))
{
    SQUARE_SUBCASE( case1,   a);
    SQUARE_SUBCASE( case1, a_a);
    SQUARE_SUBCASE( case1, a_f);
    SQUARE_SUBCASE( case1, a_d);
    SQUARE_SUBCASE( case1, a_h);
}