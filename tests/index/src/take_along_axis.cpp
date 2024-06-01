#include "nmtools/array/index/take_along_axis.hpp"
#include "nmtools/testing/data/array/take_along_axis.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;

#define RUN_shape_take_along_axis_impl(...) \
nm::index::shape_take_along_axis(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs shape_take_along_axis fn to callable lambda
#define RUN_shape_take_along_axis(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("shape_take_along_axis-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_shape_take_along_axis_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_shape_take_along_axis(case_name, ...) \
RUN_shape_take_along_axis_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define SHAPE_TAKE_ALONG_AXIS_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index, shape_take_along_axis, case_name); \
    using namespace args; \
    auto result = RUN_shape_take_along_axis(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("shape_take_along_axis(case1)" * doctest::test_suite("index::shape_take_along_axis"))
{
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case1, shape, indices, axis_u );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case1, shape_a, indices_a, axis_u );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case1, shape_v, indices_v, axis_u );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case1, shape_f, indices_f, axis_u );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case1, shape_h, indices_h, axis_u );

    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case1, shape, indices, axis_i );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case1, shape_a, indices_a, axis_i );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case1, shape_v, indices_v, axis_i );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case1, shape_f, indices_f, axis_i );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case1, shape_h, indices_h, axis_i );
}

TEST_CASE("shape_take_along_axis(case2)" * doctest::test_suite("index::shape_take_along_axis"))
{
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case2, shape, indices, axis_u );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case2, shape_a, indices_a, axis_u );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case2, shape_v, indices_v, axis_u );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case2, shape_f, indices_f, axis_u );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case2, shape_h, indices_h, axis_u );

    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case2, shape, indices, axis_i );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case2, shape_a, indices_a, axis_i );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case2, shape_v, indices_v, axis_i );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case2, shape_f, indices_f, axis_i );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case2, shape_h, indices_h, axis_i );
}

TEST_CASE("shape_take_along_axis(case3)" * doctest::test_suite("index::shape_take_along_axis"))
{
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case3, shape, indices, axis_u );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case3, shape_a, indices_a, axis_u );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case3, shape_v, indices_v, axis_u );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case3, shape_f, indices_f, axis_u );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case3, shape_h, indices_h, axis_u );

    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case3, shape, indices, axis_i );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case3, shape_a, indices_a, axis_i );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case3, shape_v, indices_v, axis_i );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case3, shape_f, indices_f, axis_i );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case3, shape_h, indices_h, axis_i );
}

TEST_CASE("shape_take_along_axis(case4)" * doctest::test_suite("index::shape_take_along_axis"))
{
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case4, shape, indices, axis_u );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case4, shape_a, indices_a, axis_u );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case4, shape_v, indices_v, axis_u );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case4, shape_f, indices_f, axis_u );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case4, shape_h, indices_h, axis_u );

    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case4, shape, indices, axis_i );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case4, shape_a, indices_a, axis_i );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case4, shape_v, indices_v, axis_i );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case4, shape_f, indices_f, axis_i );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case4, shape_h, indices_h, axis_i );
}

TEST_CASE("shape_take_along_axis(case5)" * doctest::test_suite("index::shape_take_along_axis"))
{
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case5, shape, indices, axis_u );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case5, shape_a, indices_a, axis_u );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case5, shape_v, indices_v, axis_u );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case5, shape_f, indices_f, axis_u );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case5, shape_h, indices_h, axis_u );

    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case5, shape, indices, axis_i );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case5, shape_a, indices_a, axis_i );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case5, shape_v, indices_v, axis_i );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case5, shape_f, indices_f, axis_i );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case5, shape_h, indices_h, axis_i );
}

TEST_CASE("shape_take_along_axis(case6)" * doctest::test_suite("index::shape_take_along_axis"))
{
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case6, shape, indices, axis_u );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case6, shape_a, indices_a, axis_u );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case6, shape_v, indices_v, axis_u );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case6, shape_f, indices_f, axis_u );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case6, shape_h, indices_h, axis_u );

    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case6, shape, indices, axis_i );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case6, shape_a, indices_a, axis_i );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case6, shape_v, indices_v, axis_i );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case6, shape_f, indices_f, axis_i );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case6, shape_h, indices_h, axis_i );
}

TEST_CASE("shape_take_along_axis(case7)" * doctest::test_suite("index::shape_take_along_axis"))
{
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case7, shape, indices, axis_u );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case7, shape_a, indices_a, axis_u );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case7, shape_v, indices_v, axis_u );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case7, shape_f, indices_f, axis_u );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case7, shape_h, indices_h, axis_u );

    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case7, shape, indices, axis_i );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case7, shape_a, indices_a, axis_i );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case7, shape_v, indices_v, axis_i );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case7, shape_f, indices_f, axis_i );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case7, shape_h, indices_h, axis_i );
}

TEST_CASE("shape_take_along_axis(case8)" * doctest::test_suite("index::shape_take_along_axis"))
{
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case8, shape, indices, axis_u );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case8, shape_a, indices_a, axis_u );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case8, shape_v, indices_v, axis_u );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case8, shape_f, indices_f, axis_u );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case8, shape_h, indices_h, axis_u );

    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case8, shape, indices, axis_i );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case8, shape_a, indices_a, axis_i );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case8, shape_v, indices_v, axis_i );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case8, shape_f, indices_f, axis_i );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case8, shape_h, indices_h, axis_i );
}

TEST_CASE("shape_take_along_axis(case9)" * doctest::test_suite("index::shape_take_along_axis"))
{
    // NOTE: triggers compile error as it should be
    // SHAPE_TAKE_ALONG_AXIS_SUBCASE( case9, shape, indices, axis_u );
    // SHAPE_TAKE_ALONG_AXIS_SUBCASE( case9, shape_a, indices_a, axis_u );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case9, shape_v, indices_v, axis_u );
    // SHAPE_TAKE_ALONG_AXIS_SUBCASE( case9, shape_f, indices_f, axis_u );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case9, shape_h, indices_h, axis_u );

    // SHAPE_TAKE_ALONG_AXIS_SUBCASE( case9, shape, indices, axis_i );
    // SHAPE_TAKE_ALONG_AXIS_SUBCASE( case9, shape_a, indices_a, axis_i );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case9, shape_v, indices_v, axis_i );
    // SHAPE_TAKE_ALONG_AXIS_SUBCASE( case9, shape_f, indices_f, axis_i );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case9, shape_h, indices_h, axis_i );
}

TEST_CASE("shape_take_along_axis(case10)" * doctest::test_suite("index::shape_take_along_axis"))
{
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case10, shape, indices, axis_u );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case10, shape_a, indices_a, axis_u );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case10, shape_v, indices_v, axis_u );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case10, shape_f, indices_f, axis_u );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case10, shape_h, indices_h, axis_u );

    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case10, shape, indices, axis_i );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case10, shape_a, indices_a, axis_i );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case10, shape_v, indices_v, axis_i );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case10, shape_f, indices_f, axis_i );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case10, shape_h, indices_h, axis_i );
}

TEST_CASE("shape_take_along_axis(case11)" * doctest::test_suite("index::shape_take_along_axis"))
{
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case11, shape, indices, axis_u );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case11, shape_a, indices_a, axis_u );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case11, shape_v, indices_v, axis_u );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case11, shape_f, indices_f, axis_u );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case11, shape_h, indices_h, axis_u );

    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case11, shape, indices, axis_i );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case11, shape_a, indices_a, axis_i );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case11, shape_v, indices_v, axis_i );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case11, shape_f, indices_f, axis_i );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case11, shape_h, indices_h, axis_i );
}

TEST_CASE("shape_take_along_axis(case12)" * doctest::test_suite("index::shape_take_along_axis"))
{
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case12, shape, indices, axis_u );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case12, shape_a, indices_a, axis_u );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case12, shape_v, indices_v, axis_u );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case12, shape_f, indices_f, axis_u );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case12, shape_h, indices_h, axis_u );

    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case12, shape, indices, axis_i );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case12, shape_a, indices_a, axis_i );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case12, shape_v, indices_v, axis_i );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case12, shape_f, indices_f, axis_i );
    SHAPE_TAKE_ALONG_AXIS_SUBCASE( case12, shape_h, indices_h, axis_i );
}