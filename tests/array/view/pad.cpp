#include "nmtools/array/view/pad.hpp"
#include "nmtools/testing/data/array/pad.hpp"
#include "nmtools/testing/doctest.hpp"

#define RUN_shape_pad_impl(...) \
nmtools::index::shape_pad(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs shape_pad fn to callable lambda
#define RUN_shape_pad(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("shape_pad-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_shape_pad_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_shape_pad(case_name, ...) \
RUN_shape_pad_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define SHAPE_PAD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(index, shape_pad, case_name); \
    using namespace args; \
    auto result = RUN_shape_pad(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("shape_pad(case1)" * doctest::test_suite("index::shape_pad"))
{
    SHAPE_PAD_SUBCASE( case1, shape, pad_width );
    SHAPE_PAD_SUBCASE( case1, shape_a, pad_width_a );
    SHAPE_PAD_SUBCASE( case1, shape_v, pad_width_v );
    SHAPE_PAD_SUBCASE( case1, shape_f, pad_width_f );
    SHAPE_PAD_SUBCASE( case1, shape_h, pad_width_h );
    // dynamic dimension not supported yet
    // SHAPE_PAD_SUBCASE( case1, shape_d, pad_width_d );
}

TEST_CASE("shape_pad(case2)" * doctest::test_suite("index::shape_pad"))
{
    SHAPE_PAD_SUBCASE( case2, shape, pad_width );
    SHAPE_PAD_SUBCASE( case2, shape_a, pad_width_a );
    SHAPE_PAD_SUBCASE( case2, shape_v, pad_width_v );
    SHAPE_PAD_SUBCASE( case2, shape_f, pad_width_f );
    SHAPE_PAD_SUBCASE( case2, shape_h, pad_width_h );
    // dynamic dimension not supported yet
    // SHAPE_PAD_SUBCASE( case2, shape_d, pad_width_d );
}

TEST_CASE("shape_pad(case3)" * doctest::test_suite("index::shape_pad"))
{
    SHAPE_PAD_SUBCASE( case3, shape, pad_width );
    SHAPE_PAD_SUBCASE( case3, shape_a, pad_width_a );
    SHAPE_PAD_SUBCASE( case3, shape_v, pad_width_v );
    SHAPE_PAD_SUBCASE( case3, shape_f, pad_width_f );
    SHAPE_PAD_SUBCASE( case3, shape_h, pad_width_h );
    // dynamic dimension not supported yet
    // SHAPE_PAD_SUBCASE( case3, shape_d, pad_width_d );
}

TEST_CASE("shape_pad(case4)" * doctest::test_suite("index::shape_pad"))
{
    SHAPE_PAD_SUBCASE( case4, shape, pad_width );
    SHAPE_PAD_SUBCASE( case4, shape_a, pad_width_a );
    SHAPE_PAD_SUBCASE( case4, shape_v, pad_width_v );
    SHAPE_PAD_SUBCASE( case4, shape_f, pad_width_f );
    SHAPE_PAD_SUBCASE( case4, shape_h, pad_width_h );
    // dynamic dimension not supported yet
    // SHAPE_PAD_SUBCASE( case4, shape_d, pad_width_d );
}

TEST_CASE("shape_pad(case5)" * doctest::test_suite("index::shape_pad"))
{
    SHAPE_PAD_SUBCASE( case5, shape, pad_width );
    SHAPE_PAD_SUBCASE( case5, shape_a, pad_width_a );
    SHAPE_PAD_SUBCASE( case5, shape_v, pad_width_v );
    SHAPE_PAD_SUBCASE( case5, shape_f, pad_width_f );
    SHAPE_PAD_SUBCASE( case5, shape_h, pad_width_h );
    // dynamic dimension not supported yet
    // SHAPE_PAD_SUBCASE( case5, shape_d, pad_width_d );
}

#define RUN_index_pad_impl(...) \
nmtools::index::pad(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs pad fn to callable lambda
#define RUN_index_pad(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("index::pad-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_index_pad_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_index_pad(case_name, ...) \
RUN_index_pad_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define INDEX_PAD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(index, pad, case_name); \
    using namespace args; \
    auto result = RUN_index_pad(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("pad(case1)" * doctest::test_suite("index::pad"))
{
    INDEX_PAD_SUBCASE( case1, indices, src_shape, dst_shape, pad_width );
    INDEX_PAD_SUBCASE( case1, indices_a, src_shape_a, dst_shape_a, pad_width_a );
    INDEX_PAD_SUBCASE( case1, indices_v, src_shape_v, dst_shape_v, pad_width_v );
    INDEX_PAD_SUBCASE( case1, indices_f, src_shape_f, dst_shape_f, pad_width_f );
    INDEX_PAD_SUBCASE( case1, indices_h, src_shape_h, dst_shape_h, pad_width_h );
    INDEX_PAD_SUBCASE( case1, indices_a, src_shape_a, dst_shape_a, pad_width_a );
}

TEST_CASE("pad(case2)" * doctest::test_suite("index::pad"))
{
    INDEX_PAD_SUBCASE( case2, indices, src_shape, dst_shape, pad_width );
    INDEX_PAD_SUBCASE( case2, indices_a, src_shape_a, dst_shape_a, pad_width_a );
    INDEX_PAD_SUBCASE( case2, indices_v, src_shape_v, dst_shape_v, pad_width_v );
    INDEX_PAD_SUBCASE( case2, indices_f, src_shape_f, dst_shape_f, pad_width_f );
    INDEX_PAD_SUBCASE( case2, indices_h, src_shape_h, dst_shape_h, pad_width_h );
    INDEX_PAD_SUBCASE( case2, indices_a, src_shape_a, dst_shape_a, pad_width_a );
}

#define RUN_pad_impl(...) \
nmtools::view::pad(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs pad fn to callable lambda
#define RUN_pad(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("view::pad-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_pad_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_pad(case_name, ...) \
RUN_pad_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define PAD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, pad, case_name); \
    using namespace args; \
    auto result = RUN_pad(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

static_assert( nmtools::meta::is_ndarray_v<int[3][2]> );

TEST_CASE("pad(case1)" * doctest::test_suite("view::pad"))
{
    PAD_SUBCASE( case1, array, pad_width );
    PAD_SUBCASE( case1, array_a, pad_width_a );
    PAD_SUBCASE( case1, array_f, pad_width_f );
    PAD_SUBCASE( case1, array_h, pad_width_h );
    PAD_SUBCASE( case1, array_d, pad_width_a );
}

TEST_CASE("pad(case2)" * doctest::test_suite("view::pad"))
{
    PAD_SUBCASE( case2, array, pad_width );
    PAD_SUBCASE( case2, array_a, pad_width_a );
    PAD_SUBCASE( case2, array_f, pad_width_f );
    PAD_SUBCASE( case2, array_h, pad_width_h );
    PAD_SUBCASE( case2, array_d, pad_width_a );
}

TEST_CASE("pad(case3)" * doctest::test_suite("view::pad"))
{
    PAD_SUBCASE( case3, array, pad_width );
    PAD_SUBCASE( case3, array_a, pad_width_a );
    PAD_SUBCASE( case3, array_f, pad_width_f );
    PAD_SUBCASE( case3, array_h, pad_width_h );
    PAD_SUBCASE( case3, array_d, pad_width_a );
}

TEST_CASE("pad(case4)" * doctest::test_suite("view::pad"))
{
    PAD_SUBCASE( case4, array, pad_width );
    PAD_SUBCASE( case4, array_a, pad_width_a );
    PAD_SUBCASE( case4, array_f, pad_width_f );
    PAD_SUBCASE( case4, array_h, pad_width_h );
    PAD_SUBCASE( case4, array_d, pad_width_a );
}

TEST_CASE("pad(case5)" * doctest::test_suite("view::pad"))
{
    PAD_SUBCASE( case5, array, pad_width );
    PAD_SUBCASE( case5, array_a, pad_width_a );
    PAD_SUBCASE( case5, array_f, pad_width_f );
    PAD_SUBCASE( case5, array_h, pad_width_h );
    PAD_SUBCASE( case5, array_d, pad_width_a );
}