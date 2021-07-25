#include "nmtools/array/array/sum.hpp"
#include "nmtools/testing/data/array/add.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace array = nm::array;

#define RUN_sum_impl(...) \
nm::array::sum(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs sum fn to callable lambda
#define RUN_sum(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("sum-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_sum_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_sum(case_name, ...) \
RUN_sum_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define SUM_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    /* using test case from reduce_add since they're basically the same */ \
    NMTOOLS_TESTING_DECLARE_NS(view, reduce_add, case_name); \
    using namespace args; \
    auto result = RUN_sum(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("sum(case1)" * doctest::test_suite("array::sum"))
{
    SUM_SUBCASE( case1,   a, axis );
    SUM_SUBCASE( case1, a_a, axis );
    SUM_SUBCASE( case1, a_v, axis );
    SUM_SUBCASE( case1, a_f, axis );
    // not yet supported,
    // cant figure out apply_slice for dynamic dim array yet
    // SUM_SUBCASE( case1, a_d, axis );
    SUM_SUBCASE( case1, a_h, axis );
}

TEST_CASE("sum(case2)" * doctest::test_suite("array::sum"))
{
    SUM_SUBCASE( case2,   a, axis );
    SUM_SUBCASE( case2, a_a, axis );
    SUM_SUBCASE( case2, a_v, axis );
    SUM_SUBCASE( case2, a_f, axis );
    SUM_SUBCASE( case2, a_h, axis );
}

TEST_CASE("sum(case3)" * doctest::test_suite("array::sum"))
{
    SUM_SUBCASE( case3,   a, axis );
    SUM_SUBCASE( case3, a_a, axis );
    SUM_SUBCASE( case3, a_v, axis );
    SUM_SUBCASE( case3, a_f, axis );
    SUM_SUBCASE( case3, a_h, axis );
}

TEST_CASE("sum(case4)" * doctest::test_suite("array::sum"))
{
    SUM_SUBCASE( case4,   a,   axis );
    SUM_SUBCASE( case4, a_a, axis_a );
    SUM_SUBCASE( case4, a_v, axis_v );
    SUM_SUBCASE( case4, a_f, axis_f );
    SUM_SUBCASE( case4, a_h, axis_h );
}

TEST_CASE("sum(case5)" * doctest::test_suite("array::sum"))
{
    SUM_SUBCASE( case5,   a,   axis );
    SUM_SUBCASE( case5, a_a, axis_a );
    SUM_SUBCASE( case5, a_v, axis_v );
    SUM_SUBCASE( case5, a_f, axis_f );
    SUM_SUBCASE( case5, a_h, axis_h );
}

TEST_CASE("sum(case6)" * doctest::test_suite("array::sum"))
{
    SUM_SUBCASE( case6,   a,   axis );
    SUM_SUBCASE( case6, a_a, axis_a );
    SUM_SUBCASE( case6, a_v, axis_v );
    SUM_SUBCASE( case6, a_f, axis_f );
    SUM_SUBCASE( case6, a_h, axis_h );
}

TEST_CASE("sum(case7)" * doctest::test_suite("array::sum"))
{
    SUM_SUBCASE( case7,   a, axis, dtype );
    SUM_SUBCASE( case7, a_a, axis, dtype );
    SUM_SUBCASE( case7, a_v, axis, dtype );
    SUM_SUBCASE( case7, a_f, axis, dtype );
    SUM_SUBCASE( case7, a_h, axis, dtype );
}

TEST_CASE("sum(case8)" * doctest::test_suite("array::sum"))
{
    SUM_SUBCASE( case8,   a, axis, dtype, initial );
    SUM_SUBCASE( case8, a_a, axis, dtype, initial );
    SUM_SUBCASE( case8, a_v, axis, dtype, initial );
    SUM_SUBCASE( case8, a_f, axis, dtype, initial );
    SUM_SUBCASE( case8, a_h, axis, dtype, initial );
}

TEST_CASE("sum(case9)" * doctest::test_suite("array::sum"))
{
    SUM_SUBCASE( case9,   a, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case9, a_a, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case9, a_v, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case9, a_f, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case9, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("sum(case10)" * doctest::test_suite("array::sum"))
{
    SUM_SUBCASE( case10,   a, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case10, a_a, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case10, a_v, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case10, a_f, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case10, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("sum(case11)" * doctest::test_suite("array::sum"))
{
    SUM_SUBCASE( case11,   a, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case11, a_a, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case11, a_v, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case11, a_f, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case11, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("sum(case12)" * doctest::test_suite("array::sum"))
{
    SUM_SUBCASE( case12,   a, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case12, a_a, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case12, a_v, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case12, a_f, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case12, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("sum(case13)" * doctest::test_suite("array::sum"))
{
    SUM_SUBCASE( case13,   a, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case13, a_a, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case13, a_v, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case13, a_f, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case13, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("sum(case14)" * doctest::test_suite("array::sum"))
{
    SUM_SUBCASE( case14,   a, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case14, a_a, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case14, a_v, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case14, a_f, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case14, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("sum(case15)" * doctest::test_suite("array::sum"))
{
    SUM_SUBCASE( case15,   a, axis );
    SUM_SUBCASE( case15, a_a, axis );
    SUM_SUBCASE( case15, a_v, axis );
    SUM_SUBCASE( case15, a_f, axis );
    SUM_SUBCASE( case15, a_h, axis );
}

TEST_CASE("sum(case16)" * doctest::test_suite("array::sum"))
{
    SUM_SUBCASE( case16,   a, axis, nmtools::None, initial );
    SUM_SUBCASE( case16, a_a, axis, nmtools::None, initial );
    SUM_SUBCASE( case16, a_v, axis, nmtools::None, initial );
    SUM_SUBCASE( case16, a_f, axis, nmtools::None, initial );
    SUM_SUBCASE( case16, a_h, axis, nmtools::None, initial );
}

TEST_CASE("sum(case17)" * doctest::test_suite("array::sum"))
{
    SUM_SUBCASE( case17,   a, axis, nmtools::None, initial, keepdims );
    SUM_SUBCASE( case17, a_a, axis, nmtools::None, initial, keepdims );
    SUM_SUBCASE( case17, a_v, axis, nmtools::None, initial, keepdims );
    SUM_SUBCASE( case17, a_f, axis, nmtools::None, initial, keepdims );
    SUM_SUBCASE( case17, a_h, axis, nmtools::None, initial, keepdims );
}

TEST_CASE("sum(case18)" * doctest::test_suite("array::sum"))
{
    SUM_SUBCASE( case18,   a, axis, nmtools::None, initial, keepdims );
    SUM_SUBCASE( case18, a_a, axis, nmtools::None, initial, keepdims );
    SUM_SUBCASE( case18, a_v, axis, nmtools::None, initial, keepdims );
    SUM_SUBCASE( case18, a_f, axis, nmtools::None, initial, keepdims );
    SUM_SUBCASE( case18, a_h, axis, nmtools::None, initial, keepdims );
}

TEST_CASE("sum(case19)" * doctest::test_suite("array::sum"))
{
    SUM_SUBCASE( case19,   a, axis, nmtools::None, initial, keepdims );
    SUM_SUBCASE( case19, a_a, axis, nmtools::None, initial, keepdims );
    SUM_SUBCASE( case19, a_v, axis, nmtools::None, initial, keepdims );
    SUM_SUBCASE( case19, a_f, axis, nmtools::None, initial, keepdims );
    SUM_SUBCASE( case19, a_h, axis, nmtools::None, initial, keepdims );
}

TEST_CASE("sum(case20)" * doctest::test_suite("array::sum"))
{
    SUM_SUBCASE( case20,   a, axis, nmtools::None, initial, keepdims );
    SUM_SUBCASE( case20, a_a, axis, nmtools::None, initial, keepdims );
    SUM_SUBCASE( case20, a_v, axis, nmtools::None, initial, keepdims );
    SUM_SUBCASE( case20, a_f, axis, nmtools::None, initial, keepdims );
    SUM_SUBCASE( case20, a_h, axis, nmtools::None, initial, keepdims );
}