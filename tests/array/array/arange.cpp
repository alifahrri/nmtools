#include "nmtools/array/array/arange.hpp"
#include "nmtools/testing/data/array/arange.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>
#include <tuple>

#define RUN_arange_impl(...) \
nm::array::arange(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs arange fn to callable lambda
#define RUN_arange(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("arange-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_arange_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_arange(case_name, ...) \
RUN_arange_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define ARANGE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, arange, case_name); \
    using namespace args; \
    auto result = RUN_arange(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("arange(case1)" * doctest::test_suite("array::arange"))
{
    ARANGE_SUBCASE(case1, stop, dtype );
}

TEST_CASE("arange(case2)" * doctest::test_suite("array::arange"))
{
    ARANGE_SUBCASE(case2, start, stop, dtype );
}

TEST_CASE("arange(case3)" * doctest::test_suite("array::arange"))
{
    ARANGE_SUBCASE(case3, start, stop, step, dtype );
}

TEST_CASE("arange(case4)" * doctest::test_suite("array::arange"))
{
    ARANGE_SUBCASE(case4, start, stop, step, dtype );
}

TEST_CASE("arange(case5)" * doctest::test_suite("array::arange"))
{
    ARANGE_SUBCASE(case5, stop );
}

TEST_CASE("arange(case6)" * doctest::test_suite("array::arange"))
{
    ARANGE_SUBCASE(case6, start, stop );
}

TEST_CASE("arange(case7)" * doctest::test_suite("array::arange"))
{
    ARANGE_SUBCASE(case7, start, stop, step );
}

TEST_CASE("arange(case8)" * doctest::test_suite("array::arange"))
{
    ARANGE_SUBCASE(case8, start, stop, step );
}

TEST_CASE("arange(case9)" * doctest::test_suite("array::arange"))
{
    ARANGE_SUBCASE(case9, start, stop, step );
}