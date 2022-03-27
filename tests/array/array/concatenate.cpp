#include "nmtools/array/array/concatenate.hpp"
#include "nmtools/testing/data/array/concatenate.hpp"

#include "nmtools/constants.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>
#include <tuple>

namespace nm = nmtools;
namespace na = nm::array;

#define RUN_impl(...) \
nm::array::concatenate(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs concatenate fn to callable lambda
#define RUN_concatenate(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("concatenate-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_concatenate(case_name, ...) \
RUN_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define CONCATENATE_SUBCASE(case_name, lhs, rhs, axis) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, concatenate, case_name); \
    auto array_ref = RUN_concatenate(case_name, args::lhs, args::rhs, args::axis); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(array_ref), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( array_ref, expect::expected ); \
}


// @note not supported yet
// TEST_CASE("concatenate(raw)" * doctest::test_suite("array::concatenate"))
// {
//     CONCATENATE_SUBCASE(case1, lhs, rhs, axis);
// }

TEST_CASE("concatenate(case1)" * doctest::test_suite("array::concatenate"))
{
    CONCATENATE_SUBCASE(case1, lhs_a, rhs_a, axis);
    CONCATENATE_SUBCASE(case1, lhs_v, rhs_v, axis);
    CONCATENATE_SUBCASE(case1, lhs_f, rhs_f, axis);
    CONCATENATE_SUBCASE(case1, lhs_d, rhs_d, axis);
    CONCATENATE_SUBCASE(case1, lhs_h, rhs_h, axis);
}

TEST_CASE("concatenate(case2)" * doctest::test_suite("array::concatenate"))
{
    CONCATENATE_SUBCASE(case2, lhs_a, rhs_a, axis);
    CONCATENATE_SUBCASE(case2, lhs_v, rhs_v, axis);
    CONCATENATE_SUBCASE(case2, lhs_f, rhs_f, axis);
    CONCATENATE_SUBCASE(case2, lhs_d, rhs_d, axis);
    CONCATENATE_SUBCASE(case2, lhs_h, rhs_h, axis);
}

TEST_CASE("concatenate(case3)" * doctest::test_suite("array::concatenate"))
{
    CONCATENATE_SUBCASE(case3, lhs_a, rhs_a, axis);
    // TODO: remove nested std vector support
    // CONCATENATE_SUBCASE(case3, lhs_v, rhs_v, axis);
    CONCATENATE_SUBCASE(case3, lhs_f, rhs_f, axis);
    CONCATENATE_SUBCASE(case3, lhs_d, rhs_d, axis);
    CONCATENATE_SUBCASE(case3, lhs_h, rhs_h, axis);
}

TEST_CASE("concatenate(case4)" * doctest::test_suite("array::concatenate"))
{
    CONCATENATE_SUBCASE(case4, lhs_a, rhs_a, axis);
    CONCATENATE_SUBCASE(case4, lhs_v, rhs_v, axis);
    CONCATENATE_SUBCASE(case4, lhs_f, rhs_f, axis);
    CONCATENATE_SUBCASE(case4, lhs_d, rhs_d, axis);
    CONCATENATE_SUBCASE(case4, lhs_h, rhs_h, axis);
}