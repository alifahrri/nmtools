#include "nmtools/index/repeat.hpp"
#include "nmtools/ndarray/dynamic.hpp"
#include "nmtools/ndarray/hybrid.hpp"
#include "nmtools/ndarray/fixed.hpp"
#include "nmtools/testing/data/index/repeat.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;

using namespace nm::literals;

#define RUN_shape_repeat_impl(...) \
nm::index::shape_repeat(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs shape_repeat fn to callable lambda
#define RUN_shape_repeat(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("shape_repeat-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_shape_repeat_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_shape_repeat(case_name, ...) \
RUN_shape_repeat_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define SHAPE_REPEAT_SUBCASE(case_name,ashape,repeats,axis) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(shape_repeat, case_name); \
    auto shape = RUN_shape_repeat(case_name, args::ashape, args::repeats, args::axis); \
    NMTOOLS_ASSERT_EQUAL( shape, expect::shape ); \
}

#define CONSTEXPR_SHAPE_REPEAT_SUBCASE(case_name,ashape,repeats,axis) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(constexpr_shape_repeat, case_name); \
    constexpr auto shape = RUN_shape_repeat_impl( args::ashape, args::repeats, args::axis ); \
    NMTOOLS_ASSERT_EQUAL( shape, expect::shape ); \
}

TEST_CASE("shape_repeat(case1)" * doctest::test_suite("index::shape_repeat"))
{
    SHAPE_REPEAT_SUBCASE( case1, shape, repeats, axis );
    SHAPE_REPEAT_SUBCASE( case1, shape_a, repeats, axis );
    SHAPE_REPEAT_SUBCASE( case1, shape_v, repeats, axis );
    SHAPE_REPEAT_SUBCASE( case1, shape_f, repeats, axis );
    SHAPE_REPEAT_SUBCASE( case1, shape_h, repeats, axis );

    SHAPE_REPEAT_SUBCASE( case1, shape_ct, repeats, axis );
    SHAPE_REPEAT_SUBCASE( case1, shape_cl, repeats, axis );

    SHAPE_REPEAT_SUBCASE( case1, shape_ct, repeats_ct, axis );
    SHAPE_REPEAT_SUBCASE( case1, shape_cl, repeats_ct, axis );
}

TEST_CASE("shape_repeat(case2)" * doctest::test_suite("index::shape_repeat"))
{
    SHAPE_REPEAT_SUBCASE( case2, shape, repeats, axis );
    SHAPE_REPEAT_SUBCASE( case2, shape_a, repeats, axis );
    SHAPE_REPEAT_SUBCASE( case2, shape_v, repeats, axis );
    SHAPE_REPEAT_SUBCASE( case2, shape_f, repeats, axis );
    SHAPE_REPEAT_SUBCASE( case2, shape_h, repeats, axis );

    SHAPE_REPEAT_SUBCASE( case2, shape_ct, repeats, axis );
    SHAPE_REPEAT_SUBCASE( case2, shape_cl, repeats, axis );

    SHAPE_REPEAT_SUBCASE( case2, shape_ct, repeats, axis_ct );
    SHAPE_REPEAT_SUBCASE( case2, shape_cl, repeats, axis_ct );

    SHAPE_REPEAT_SUBCASE( case2, shape_ct, repeats_ct, axis_ct );
    SHAPE_REPEAT_SUBCASE( case2, shape_cl, repeats_ct, axis_ct );
}

TEST_CASE("shape_repeat(case3)" * doctest::test_suite("index::shape_repeat"))
{
    SHAPE_REPEAT_SUBCASE( case3, shape, repeats, axis );
    SHAPE_REPEAT_SUBCASE( case3, shape_a, repeats, axis );
    SHAPE_REPEAT_SUBCASE( case3, shape_v, repeats, axis );
    SHAPE_REPEAT_SUBCASE( case3, shape_f, repeats, axis );
    SHAPE_REPEAT_SUBCASE( case3, shape_h, repeats, axis );

    SHAPE_REPEAT_SUBCASE( case3, shape_ct, repeats, axis );
    SHAPE_REPEAT_SUBCASE( case3, shape_cl, repeats, axis );

    SHAPE_REPEAT_SUBCASE( case3, shape_ct, repeats, axis_ct );
    SHAPE_REPEAT_SUBCASE( case3, shape_cl, repeats, axis_ct );

    SHAPE_REPEAT_SUBCASE( case3, shape_ct, repeats_ct, axis_ct );
    SHAPE_REPEAT_SUBCASE( case3, shape_cl, repeats_ct, axis_ct );
}

TEST_CASE("shape_repeat(case4)" * doctest::test_suite("index::shape_repeat"))
{
    SHAPE_REPEAT_SUBCASE( case4, shape, repeats, axis );
    SHAPE_REPEAT_SUBCASE( case4, shape_a, repeats, axis );
    SHAPE_REPEAT_SUBCASE( case4, shape_v, repeats, axis );
    SHAPE_REPEAT_SUBCASE( case4, shape_f, repeats, axis );
    SHAPE_REPEAT_SUBCASE( case4, shape_h, repeats, axis );

    SHAPE_REPEAT_SUBCASE( case4, shape_ct, repeats_ct, axis_ct );
    SHAPE_REPEAT_SUBCASE( case4, shape_cl, repeats_cl, axis_ct );

    SHAPE_REPEAT_SUBCASE( case4, shape_ct, repeats_ct, axis );
    SHAPE_REPEAT_SUBCASE( case4, shape_cl, repeats_cl, axis );

    SHAPE_REPEAT_SUBCASE( case4, shape_ct, repeats, axis );
    SHAPE_REPEAT_SUBCASE( case4, shape_cl, repeats, axis );

    SHAPE_REPEAT_SUBCASE( case4, shape_ct, repeats_cl, axis );
    SHAPE_REPEAT_SUBCASE( case4, shape_cl, repeats_ct, axis );

    SHAPE_REPEAT_SUBCASE( case4, shape_ct, repeats_cl, axis_ct );
    SHAPE_REPEAT_SUBCASE( case4, shape_cl, repeats_ct, axis_ct );
}

TEST_CASE("shape_repeat(case5)" * doctest::test_suite("index::shape_repeat"))
{
    SHAPE_REPEAT_SUBCASE( case5, shape, repeats, axis );
    SHAPE_REPEAT_SUBCASE( case5, shape_a, repeats, axis );
    SHAPE_REPEAT_SUBCASE( case5, shape_v, repeats, axis );
    SHAPE_REPEAT_SUBCASE( case5, shape_f, repeats, axis );
    SHAPE_REPEAT_SUBCASE( case5, shape_h, repeats, axis );

    SHAPE_REPEAT_SUBCASE( case5, shape_ct, repeats_ct, axis_ct );
}

TEST_CASE("shape_repeat(case1)" * doctest::test_suite("index::constexpr_shape_repeat"))
{
    CONSTEXPR_SHAPE_REPEAT_SUBCASE( case1, shape, repeats, axis );
    CONSTEXPR_SHAPE_REPEAT_SUBCASE( case1, shape_a, repeats, axis );
    CONSTEXPR_SHAPE_REPEAT_SUBCASE( case1, shape_f, repeats, axis );
    CONSTEXPR_SHAPE_REPEAT_SUBCASE( case1, shape_h, repeats, axis );
}

TEST_CASE("shape_repeat(case2)" * doctest::test_suite("index::constexpr_shape_repeat"))
{
    CONSTEXPR_SHAPE_REPEAT_SUBCASE( case2, shape, repeats, axis );
    CONSTEXPR_SHAPE_REPEAT_SUBCASE( case2, shape_a, repeats, axis );
    CONSTEXPR_SHAPE_REPEAT_SUBCASE( case2, shape_f, repeats, axis );
    CONSTEXPR_SHAPE_REPEAT_SUBCASE( case2, shape_h, repeats, axis );
}

TEST_CASE("shape_repeat(case3)" * doctest::test_suite("index::constexpr_shape_repeat"))
{
    CONSTEXPR_SHAPE_REPEAT_SUBCASE( case3, shape, repeats, axis );
    CONSTEXPR_SHAPE_REPEAT_SUBCASE( case3, shape_a, repeats, axis );
    CONSTEXPR_SHAPE_REPEAT_SUBCASE( case3, shape_f, repeats, axis );
    CONSTEXPR_SHAPE_REPEAT_SUBCASE( case3, shape_h, repeats, axis );
}

TEST_CASE("shape_repeat(case4)" * doctest::test_suite("index::constexpr_shape_repeat"))
{
    CONSTEXPR_SHAPE_REPEAT_SUBCASE( case4, shape, repeats, axis );
    CONSTEXPR_SHAPE_REPEAT_SUBCASE( case4, shape_a, repeats, axis );
    CONSTEXPR_SHAPE_REPEAT_SUBCASE( case4, shape_f, repeats, axis );
    CONSTEXPR_SHAPE_REPEAT_SUBCASE( case4, shape_h, repeats, axis );
}

TEST_CASE("shape_repeat(case5)" * doctest::test_suite("index::constexpr_shape_repeat"))
{
    CONSTEXPR_SHAPE_REPEAT_SUBCASE( case5, shape, repeats, axis );
    CONSTEXPR_SHAPE_REPEAT_SUBCASE( case5, shape_a, repeats, axis );
    CONSTEXPR_SHAPE_REPEAT_SUBCASE( case5, shape_f, repeats, axis );
    CONSTEXPR_SHAPE_REPEAT_SUBCASE( case5, shape_h, repeats, axis );
}

#include "nmtools/index/repeat.hpp"
#include "nmtools/index/as_tuple.hpp"
#include "nmtools/meta.hpp"

#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;

#define RUN_impl(...) \
nm::index::repeat(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
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

#define REPEAT_SUBCASE(case_name, shape, indices, repeats, axis) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(repeat, case_name); \
    auto result = RUN_repeat(case_name, args::shape, args::indices, args::repeats, args::axis); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("repeat(case1)" * doctest::test_suite("index::repeat"))
{
    REPEAT_SUBCASE(case1, shape_a, indices, repeats, axis);
    REPEAT_SUBCASE(case1, shape_v, indices, repeats, axis);
    REPEAT_SUBCASE(case1, shape_f, indices, repeats, axis);
    REPEAT_SUBCASE(case1, shape_h, indices, repeats, axis);
    
    REPEAT_SUBCASE(case1, shape_ct, indices, repeats, axis);
    REPEAT_SUBCASE(case1, shape_cl, indices, repeats, axis);
}

TEST_CASE("repeat(case2)" * doctest::test_suite("index::repeat"))
{
    REPEAT_SUBCASE(case2, shape_a, indices, repeats, axis);
    REPEAT_SUBCASE(case2, shape_v, indices, repeats, axis);
    REPEAT_SUBCASE(case2, shape_f, indices, repeats, axis);
    REPEAT_SUBCASE(case2, shape_h, indices, repeats, axis);
    
    REPEAT_SUBCASE(case2, shape_ct, indices, repeats, axis);
    REPEAT_SUBCASE(case2, shape_cl, indices, repeats, axis);
}

TEST_CASE("repeat(case3)" * doctest::test_suite("index::repeat"))
{
    REPEAT_SUBCASE(case3, shape_a, indices, repeats, axis);
    REPEAT_SUBCASE(case3, shape_v, indices, repeats, axis);
    REPEAT_SUBCASE(case3, shape_f, indices, repeats, axis);
    REPEAT_SUBCASE(case3, shape_h, indices, repeats, axis);
    
    REPEAT_SUBCASE(case3, shape_ct, indices, repeats, axis);
    REPEAT_SUBCASE(case3, shape_cl, indices, repeats, axis);
}

TEST_CASE("repeat(case4)" * doctest::test_suite("index::repeat"))
{
    REPEAT_SUBCASE(case4, shape_a, indices, repeats, axis);
    REPEAT_SUBCASE(case4, shape_v, indices, repeats, axis);
    REPEAT_SUBCASE(case4, shape_f, indices, repeats, axis);
    REPEAT_SUBCASE(case4, shape_h, indices, repeats, axis);
    
    REPEAT_SUBCASE(case4, shape_ct, indices, repeats, axis);
    REPEAT_SUBCASE(case4, shape_cl, indices, repeats, axis);
}

TEST_CASE("repeat(case5)" * doctest::test_suite("index::repeat"))
{
    REPEAT_SUBCASE(case5, shape_a, indices, repeats, axis);
    REPEAT_SUBCASE(case5, shape_v, indices, repeats, axis);
    REPEAT_SUBCASE(case5, shape_f, indices, repeats, axis);
    REPEAT_SUBCASE(case5, shape_h, indices, repeats, axis);
    
    REPEAT_SUBCASE(case5, shape_ct, indices, repeats, axis);
    REPEAT_SUBCASE(case5, shape_cl, indices, repeats, axis);
}

TEST_CASE("repeat(case6)" * doctest::test_suite("index::repeat"))
{
    // REPEAT_SUBCASE(case6, shape_a, indices, repeats, axis);
    // REPEAT_SUBCASE(case6, shape_v, indices, repeats, axis);
    // REPEAT_SUBCASE(case6, shape_f, indices, repeats, axis);
    // REPEAT_SUBCASE(case6, shape_h, indices, repeats, axis);
    
    // REPEAT_SUBCASE(case6, shape_ct, indices, repeats, axis);
    // REPEAT_SUBCASE(case6, shape_cl, indices, repeats, axis);

    // REPEAT_SUBCASE(case6, shape_ct, indices, repeats_ct, axis);
    // REPEAT_SUBCASE(case6, shape_cl, indices, repeats_ct, axis);

    REPEAT_SUBCASE(case6, shape_ct, indices, repeats_cl, axis);
    REPEAT_SUBCASE(case6, shape_cl, indices, repeats_cl, axis);
}

TEST_CASE("repeat(case7)" * doctest::test_suite("index::repeat"))
{
    REPEAT_SUBCASE(case7, shape_a, indices, repeats, axis);
    REPEAT_SUBCASE(case7, shape_v, indices, repeats, axis);
    REPEAT_SUBCASE(case7, shape_f, indices, repeats, axis);
    REPEAT_SUBCASE(case7, shape_h, indices, repeats, axis);
    
    REPEAT_SUBCASE(case7, shape_ct, indices, repeats, axis);
    REPEAT_SUBCASE(case7, shape_cl, indices, repeats, axis);

    REPEAT_SUBCASE(case7, shape_ct, indices, repeats_ct, axis);
    REPEAT_SUBCASE(case7, shape_cl, indices, repeats_ct, axis);

    REPEAT_SUBCASE(case7, shape_ct, indices, repeats_cl, axis);
    REPEAT_SUBCASE(case7, shape_cl, indices, repeats_cl, axis);
}

TEST_CASE("repeat(case8)" * doctest::test_suite("index::repeat"))
{
    REPEAT_SUBCASE(case8, shape_a, indices, repeats, axis);
    REPEAT_SUBCASE(case8, shape_v, indices, repeats, axis);
    REPEAT_SUBCASE(case8, shape_f, indices, repeats, axis);
    REPEAT_SUBCASE(case8, shape_h, indices, repeats, axis);
    
    REPEAT_SUBCASE(case8, shape_ct, indices, repeats, axis);
    REPEAT_SUBCASE(case8, shape_cl, indices, repeats, axis);
}

TEST_CASE("repeat(case9)" * doctest::test_suite("index::repeat"))
{
    REPEAT_SUBCASE(case9, shape_a, indices, repeats, axis);
    REPEAT_SUBCASE(case9, shape_v, indices, repeats, axis);
    REPEAT_SUBCASE(case9, shape_f, indices, repeats, axis);
    REPEAT_SUBCASE(case9, shape_h, indices, repeats, axis);
    
    REPEAT_SUBCASE(case9, shape_ct, indices, repeats, axis);
    REPEAT_SUBCASE(case9, shape_cl, indices, repeats, axis);
}

TEST_CASE("repeat(case10)" * doctest::test_suite("index::repeat"))
{
    REPEAT_SUBCASE(case10, shape_a, indices, repeats, axis);
    REPEAT_SUBCASE(case10, shape_v, indices, repeats, axis);
    REPEAT_SUBCASE(case10, shape_f, indices, repeats, axis);
    REPEAT_SUBCASE(case10, shape_h, indices, repeats, axis);
    
    REPEAT_SUBCASE(case10, shape_ct, indices, repeats, axis);
    REPEAT_SUBCASE(case10, shape_cl, indices, repeats, axis);
}

TEST_CASE("repeat(case10)" * doctest::test_suite("index::repeat"))
{
    REPEAT_SUBCASE(case11, shape_a, indices, repeats, axis);
    REPEAT_SUBCASE(case11, shape_v, indices, repeats, axis);
    REPEAT_SUBCASE(case11, shape_f, indices, repeats, axis);
    REPEAT_SUBCASE(case11, shape_h, indices, repeats, axis);
    
    REPEAT_SUBCASE(case11, shape_ct, indices, repeats, axis);
    REPEAT_SUBCASE(case11, shape_cl, indices, repeats, axis);
}