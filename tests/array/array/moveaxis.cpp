#include "nmtools/array/array/moveaxis.hpp"
#include "nmtools/testing/data/array/moveaxis.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;

#define RUN_moveaxis_impl(...) \
nm::array::moveaxis(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs moveaxis fn to callable lambda
#define RUN_moveaxis(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("array::moveaxis-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_moveaxis_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_moveaxis(case_name, ...) \
RUN_moveaxis_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define MOVEAXIS_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, moveaxis, case_name); \
    using namespace args; \
    auto result = RUN_moveaxis(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("moveaxis(case1)" * doctest::test_suite("array::moveaxis"))
{
    MOVEAXIS_SUBCASE( case1, a, source, destination );
    MOVEAXIS_SUBCASE( case1, a_a, source, destination );
    MOVEAXIS_SUBCASE( case1, a_f, source, destination );
    MOVEAXIS_SUBCASE( case1, a_d, source, destination );
    MOVEAXIS_SUBCASE( case1, a_h, source, destination );
}

TEST_CASE("moveaxis(case2)" * doctest::test_suite("array::moveaxis"))
{
    MOVEAXIS_SUBCASE( case2, a, source, destination );
    MOVEAXIS_SUBCASE( case2, a_a, source, destination );
    MOVEAXIS_SUBCASE( case2, a_f, source, destination );
    MOVEAXIS_SUBCASE( case2, a_d, source, destination );
    MOVEAXIS_SUBCASE( case2, a_h, source, destination );
}

TEST_CASE("moveaxis(case3)" * doctest::test_suite("array::moveaxis"))
{
    MOVEAXIS_SUBCASE( case3, a, source, destination );
    MOVEAXIS_SUBCASE( case3, a_a, source, destination );
    MOVEAXIS_SUBCASE( case3, a_f, source, destination );
    MOVEAXIS_SUBCASE( case3, a_d, source, destination );
    MOVEAXIS_SUBCASE( case3, a_h, source, destination );
}

TEST_CASE("moveaxis(case4)" * doctest::test_suite("array::moveaxis"))
{
    MOVEAXIS_SUBCASE( case4, a, source, destination );
    MOVEAXIS_SUBCASE( case4, a_a, source, destination );
    MOVEAXIS_SUBCASE( case4, a_f, source, destination );
    MOVEAXIS_SUBCASE( case4, a_d, source, destination );
    MOVEAXIS_SUBCASE( case4, a_h, source, destination );
}

TEST_CASE("moveaxis(case5)" * doctest::test_suite("array::moveaxis"))
{
    MOVEAXIS_SUBCASE( case5, a, source, destination );
    MOVEAXIS_SUBCASE( case5, a_a, source, destination );
    MOVEAXIS_SUBCASE( case5, a_f, source, destination );
    MOVEAXIS_SUBCASE( case5, a_d, source, destination );
    MOVEAXIS_SUBCASE( case5, a_h, source, destination );
}

TEST_CASE("moveaxis(case6)" * doctest::test_suite("array::moveaxis"))
{
    MOVEAXIS_SUBCASE( case6, a, source, destination );
    MOVEAXIS_SUBCASE( case6, a_a, source, destination );
    MOVEAXIS_SUBCASE( case6, a_f, source, destination );
    MOVEAXIS_SUBCASE( case6, a_d, source, destination );
    MOVEAXIS_SUBCASE( case6, a_h, source, destination );
}

TEST_CASE("moveaxis(case7)" * doctest::test_suite("array::moveaxis"))
{
    MOVEAXIS_SUBCASE( case7, a, source, destination );
    MOVEAXIS_SUBCASE( case7, a_a, source, destination );
    MOVEAXIS_SUBCASE( case7, a_f, source, destination );
    MOVEAXIS_SUBCASE( case7, a_d, source, destination );
    MOVEAXIS_SUBCASE( case7, a_h, source, destination );
}

TEST_CASE("moveaxis(case8)" * doctest::test_suite("array::moveaxis"))
{
    MOVEAXIS_SUBCASE( case8, a, source, destination );
    MOVEAXIS_SUBCASE( case8, a_a, source, destination );
    MOVEAXIS_SUBCASE( case8, a_f, source, destination );
    MOVEAXIS_SUBCASE( case8, a_d, source, destination );
    MOVEAXIS_SUBCASE( case8, a_h, source, destination );
}

TEST_CASE("moveaxis(case9)" * doctest::test_suite("array::moveaxis"))
{
    MOVEAXIS_SUBCASE( case9, a, source, destination );
    MOVEAXIS_SUBCASE( case9, a_a, source, destination );
    MOVEAXIS_SUBCASE( case9, a_f, source, destination );
    MOVEAXIS_SUBCASE( case9, a_d, source, destination );
    MOVEAXIS_SUBCASE( case9, a_h, source, destination );
}