#include "nmtools/array/array/repeat.hpp"
#include "nmtools/testing/data/array/repeat.hpp"
#include "nmtools/constants.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>
#include <tuple>

namespace nm = nmtools;
namespace na = nm::array;

#define RUN_impl(...) \
nm::array::repeat(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs repeat fn to callable lambda
#define RUN_repeat(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("repeat-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_repeat(case_name, ...) \
RUN_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define REPEAT_SUBCASE(case_name, array_input, repeats, axis) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, repeat, case_name); \
    auto array_array = RUN_repeat(case_name, args::array_input, args::repeats, args::axis); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(array_array), expect::shape ); \
    NMTOOLS_ASSERT_EQUAL( nm::dim(array_array), expect::dim ); \
    NMTOOLS_ASSERT_CLOSE( array_array, expect::result ); \
}

TEST_CASE("repeat(case1)" * doctest::test_suite("array::repeat"))
{
    REPEAT_SUBCASE(case1, array_a, repeats, axis);
    REPEAT_SUBCASE(case1, array_f, repeats, axis);
    REPEAT_SUBCASE(case1, array_d, repeats, axis);
    REPEAT_SUBCASE(case1, array_h, repeats, axis);
}

TEST_CASE("repeat(case2)" * doctest::test_suite("array::repeat"))
{
    REPEAT_SUBCASE(case2, array_a, repeats, axis);
    REPEAT_SUBCASE(case2, array_f, repeats, axis);
    REPEAT_SUBCASE(case2, array_d, repeats, axis);
    REPEAT_SUBCASE(case2, array_h, repeats, axis);
}

TEST_CASE("repeat(case3)" * doctest::test_suite("array::repeat"))
{
    REPEAT_SUBCASE(case3, array_a, repeats, axis);
    REPEAT_SUBCASE(case3, array_f, repeats, axis);
    REPEAT_SUBCASE(case3, array_d, repeats, axis);
    REPEAT_SUBCASE(case3, array_h, repeats, axis);
}

TEST_CASE("repeat(case4)" * doctest::test_suite("array::repeat"))
{
    REPEAT_SUBCASE(case4, array_a, repeats, axis);
    REPEAT_SUBCASE(case4, array_f, repeats, axis);
    REPEAT_SUBCASE(case4, array_d, repeats, axis);
    REPEAT_SUBCASE(case4, array_h, repeats, axis);
}

TEST_CASE("repeat(case5)" * doctest::test_suite("array::repeat"))
{
    REPEAT_SUBCASE(case5, array_a, repeats, axis);
    REPEAT_SUBCASE(case5, array_f, repeats, axis);
    REPEAT_SUBCASE(case5, array_d, repeats, axis);
    REPEAT_SUBCASE(case5, array_h, repeats, axis);
}

TEST_CASE("repeat(case6)" * doctest::test_suite("array::repeat"))
{
    REPEAT_SUBCASE(case6, array_a, repeats, axis);
    REPEAT_SUBCASE(case6, array_f, repeats, axis);
    REPEAT_SUBCASE(case6, array_d, repeats, axis);
    REPEAT_SUBCASE(case6, array_h, repeats, axis);
}