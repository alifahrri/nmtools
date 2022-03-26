#include "nmtools/array/array/expand_dims.hpp"
#include "nmtools/testing/data/array/expand_dims.hpp"
#include "nmtools/testing/doctest.hpp"

#include <array>
#include <tuple>
#include <vector>

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;

#define RUN_impl(...) \
nm::array::expand_dims(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs expand_dims fn to callable lambda
#define RUN_expand_dims(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("expand_dims-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_expand_dims(case_name, ...) \
RUN_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define EXPAND_DIMS_SUBCASE(case_name, array, axis) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(expand_dims, case_name); \
    auto array_ref = RUN_expand_dims(case_name, args::array, args::axis); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(array_ref), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( array_ref, expect::expected ); \
}

TEST_CASE("expand_dims(case1)" * doctest::test_suite("array::expand_dims"))
{
    EXPAND_DIMS_SUBCASE( case1, array,   axis_a );
    EXPAND_DIMS_SUBCASE( case1, array_a, axis_a );
    EXPAND_DIMS_SUBCASE( case1, array_v, axis_a );
    EXPAND_DIMS_SUBCASE( case1, array_f, axis_a );
    EXPAND_DIMS_SUBCASE( case1, array_d, axis_a );
    EXPAND_DIMS_SUBCASE( case1, array_h, axis_a );
}

TEST_CASE("expand_dims(case2)" * doctest::test_suite("array::expand_dims"))
{
    EXPAND_DIMS_SUBCASE( case2, array,   axis );
    EXPAND_DIMS_SUBCASE( case2, array_a, axis );
    EXPAND_DIMS_SUBCASE( case2, array_v, axis );
    EXPAND_DIMS_SUBCASE( case2, array_f, axis );
    EXPAND_DIMS_SUBCASE( case2, array_d, axis );
    EXPAND_DIMS_SUBCASE( case2, array_h, axis );
}

TEST_CASE("expand_dims(case3)" * doctest::test_suite("array::expand_dims"))
{
    EXPAND_DIMS_SUBCASE( case3, array,   axis );
    EXPAND_DIMS_SUBCASE( case3, array_a, axis );
    EXPAND_DIMS_SUBCASE( case3, array_v, axis );
    EXPAND_DIMS_SUBCASE( case3, array_f, axis );
    EXPAND_DIMS_SUBCASE( case3, array_d, axis );
    EXPAND_DIMS_SUBCASE( case3, array_h, axis );
}

TEST_CASE("expand_dims(case4)" * doctest::test_suite("array::expand_dims"))
{
    EXPAND_DIMS_SUBCASE( case4, array,   axis_a );
    EXPAND_DIMS_SUBCASE( case4, array_a, axis_a );
    EXPAND_DIMS_SUBCASE( case4, array_v, axis_a );
    EXPAND_DIMS_SUBCASE( case4, array_f, axis_a );
    EXPAND_DIMS_SUBCASE( case4, array_d, axis_a );
    EXPAND_DIMS_SUBCASE( case4, array_h, axis_a );
}

TEST_CASE("expand_dims(case5)" * doctest::test_suite("array::expand_dims"))
{
    EXPAND_DIMS_SUBCASE( case5, array,   axis_a );
    EXPAND_DIMS_SUBCASE( case5, array_a, axis_a );
    EXPAND_DIMS_SUBCASE( case5, array_v, axis_a );
    EXPAND_DIMS_SUBCASE( case5, array_f, axis_a );
    EXPAND_DIMS_SUBCASE( case5, array_d, axis_a );
    EXPAND_DIMS_SUBCASE( case5, array_h, axis_a );
}

TEST_CASE("expand_dims(case6)" * doctest::test_suite("array::expand_dims"))
{
    EXPAND_DIMS_SUBCASE( case6, array,   axis );
    EXPAND_DIMS_SUBCASE( case6, array_a, axis );
    EXPAND_DIMS_SUBCASE( case6, array_v, axis );
    EXPAND_DIMS_SUBCASE( case6, array_f, axis );
    EXPAND_DIMS_SUBCASE( case6, array_d, axis );
    EXPAND_DIMS_SUBCASE( case6, array_h, axis );
}

TEST_CASE("expand_dims(case7)" * doctest::test_suite("array::expand_dims"))
{
    EXPAND_DIMS_SUBCASE( case7, array,   axis );
    EXPAND_DIMS_SUBCASE( case7, array_a, axis );
    EXPAND_DIMS_SUBCASE( case7, array_v, axis );
    EXPAND_DIMS_SUBCASE( case7, array_f, axis );
    EXPAND_DIMS_SUBCASE( case7, array_d, axis );
    EXPAND_DIMS_SUBCASE( case7, array_h, axis );
}

TEST_CASE("expand_dims(case8)" * doctest::test_suite("array::expand_dims"))
{
    EXPAND_DIMS_SUBCASE( case8, array,   axis );
    EXPAND_DIMS_SUBCASE( case8, array_a, axis );
    EXPAND_DIMS_SUBCASE( case8, array_v, axis );
    EXPAND_DIMS_SUBCASE( case8, array_f, axis );
    EXPAND_DIMS_SUBCASE( case8, array_d, axis );
    EXPAND_DIMS_SUBCASE( case8, array_h, axis );
}

TEST_CASE("expand_dims(case9)" * doctest::test_suite("array::expand_dims"))
{
    EXPAND_DIMS_SUBCASE( case9, array,   axis );
    EXPAND_DIMS_SUBCASE( case9, array_a, axis );
    EXPAND_DIMS_SUBCASE( case9, array_v, axis );
    EXPAND_DIMS_SUBCASE( case9, array_f, axis );
    EXPAND_DIMS_SUBCASE( case9, array_d, axis );
    EXPAND_DIMS_SUBCASE( case9, array_h, axis );
}

TEST_CASE("expand_dims(case10)" * doctest::test_suite("array::expand_dims"))
{
    EXPAND_DIMS_SUBCASE( case10, array,   axis_a );
    EXPAND_DIMS_SUBCASE( case10, array_a, axis_a );
    EXPAND_DIMS_SUBCASE( case10, array_v, axis_a );
    EXPAND_DIMS_SUBCASE( case10, array_f, axis_a );
    EXPAND_DIMS_SUBCASE( case10, array_d, axis_a );
    EXPAND_DIMS_SUBCASE( case10, array_h, axis_a );
}