#include "nmtools/array/array/matmul.hpp"
#include "nmtools/testing/data/array/matmul.hpp"
#include "nmtools/testing/doctest.hpp"

#define RUN_matmul_impl(...) \
nmtools::array::matmul(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs matmul fn to callable lambda
#define RUN_matmul(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("matmul-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_matmul_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_matmul(case_name, ...) \
RUN_matmul_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define MATMUL_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, matmul, case_name); \
    using namespace args; \
    auto result = RUN_matmul(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("matmul(case1)" * doctest::test_suite("array::matmul"))
{
    MATMUL_SUBCASE( case1, lhs, rhs );
    MATMUL_SUBCASE( case1, lhs_a, rhs_a );
    MATMUL_SUBCASE( case1, lhs_f, rhs_f );
    MATMUL_SUBCASE( case1, lhs_h, rhs_h );
    // TODO: support slice for dynamic ndarray
    // MATMUL_SUBCASE( case1, lhs_d, rhs_d );
}

TEST_CASE("matmul(case2)" * doctest::test_suite("array::matmul"))
{
    MATMUL_SUBCASE( case2, lhs, rhs );
    MATMUL_SUBCASE( case2, lhs_a, rhs_a );
    MATMUL_SUBCASE( case2, lhs_f, rhs_f );
    MATMUL_SUBCASE( case2, lhs_h, rhs_h );
    // TODO: support slice for dynamic ndarray
    // MATMUL_SUBCASE( case2, lhs_d, rhs_d );
}

TEST_CASE("matmul(case3)" * doctest::test_suite("array::matmul"))
{
    MATMUL_SUBCASE( case3, lhs, rhs );
    MATMUL_SUBCASE( case3, lhs_a, rhs_a );
    MATMUL_SUBCASE( case3, lhs_f, rhs_f );
    MATMUL_SUBCASE( case3, lhs_h, rhs_h );
    // TODO: support slice for dynamic ndarray
    // MATMUL_SUBCASE( case3, lhs_d, rhs_d );
}

TEST_CASE("matmul(case4)" * doctest::test_suite("array::matmul"))
{
    MATMUL_SUBCASE( case4, lhs, rhs );
    MATMUL_SUBCASE( case4, lhs_a, rhs_a );
    MATMUL_SUBCASE( case4, lhs_f, rhs_f );
    MATMUL_SUBCASE( case4, lhs_h, rhs_h );
    // TODO: support slice for dynamic ndarray
    // MATMUL_SUBCASE( case4, lhs_d, rhs_d );
}

TEST_CASE("matmul(case5)" * doctest::test_suite("array::matmul"))
{
    MATMUL_SUBCASE( case5, lhs, rhs );
    MATMUL_SUBCASE( case5, lhs_a, rhs_a );
    MATMUL_SUBCASE( case5, lhs_f, rhs_f );
    MATMUL_SUBCASE( case5, lhs_h, rhs_h );
    // TODO: support slice for dynamic ndarray
    // MATMUL_SUBCASE( case5, lhs_d, rhs_d );
}

TEST_CASE("matmul(case6)" * doctest::test_suite("array::matmul"))
{
    MATMUL_SUBCASE( case6, lhs, rhs );
    MATMUL_SUBCASE( case6, lhs_a, rhs_a );
    MATMUL_SUBCASE( case6, lhs_f, rhs_f );
    MATMUL_SUBCASE( case6, lhs_h, rhs_h );
    // TODO: support slice for dynamic ndarray
    // MATMUL_SUBCASE( case6, lhs_d, rhs_d );
}