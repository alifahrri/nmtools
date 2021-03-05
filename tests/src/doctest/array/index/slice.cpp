#include "nmtools/array/index/slice.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/constants.hpp"

#include <vector>
#include <array>
#include <tuple>

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

#define CAST_ARRAYS(name) \
auto name##_a = cast(name, kind::nested_arr); \
auto name##_v = cast(name, kind::nested_vec); \
auto name##_f = cast(name, kind::fixed); \
auto name##_d = cast(name, kind::dynamic); \
auto name##_h = cast(name, kind::hybrid); \

using std::tuple;

NMTOOLS_TESTING_DECLARE_CASE(index, shape_slice)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int shape[3] = {2,3,2};
        auto slice0 = tuple{None,None};
        auto slice1 = tuple{0,1};
        auto slice2 = tuple{None,None};
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int result[3] = {2,1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        int shape[3] = {2,3,2};
        auto slice0 = tuple{None,None};
        auto slice1 = tuple{None,None};
        auto slice2 = tuple{None,None};
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        int result[3] = {2,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        int shape[3] = {2,3,2};
        auto slice0 = tuple{1,2};
        auto slice1 = tuple{0,1};
        auto slice2 = tuple{None,None};
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        int result[3] = {1,1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        int shape[3] = {2,3,2};
        auto slice0 = tuple{1,3};
        auto slice1 = tuple{0,1};
        auto slice2 = tuple{None,None};
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        int result[3] = {1,1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        int shape[3] = {2,3,2};
        auto slice0 = tuple{None,None};
        auto slice1 = tuple{0,2};
        auto slice2 = tuple{None,-1};
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        int result[3] = {2,2,1};
    }
}

#define RUN_shape_slice_impl(...) \
nm::index::shape_slice(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs shape_slice fn to callable lambda
#define RUN_shape_slice(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("shape_slice-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_shape_slice_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_shape_slice(case_name, ...) \
RUN_shape_slice_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define SHAPE_SLICE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(index, shape_slice, case_name); \
    using namespace args; \
    auto result = RUN_shape_slice(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("shape_slice(case1)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case1,   shape, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case1, shape_a, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case1, shape_v, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case1, shape_f, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case1, shape_d, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case1, shape_h, slice0, slice1, slice2);
}

TEST_CASE("shape_slice(case2)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case2,   shape, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case2, shape_a, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case2, shape_v, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case2, shape_f, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case2, shape_d, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case2, shape_h, slice0, slice1, slice2);
}

TEST_CASE("shape_slice(case3)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case3,   shape, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case3, shape_a, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case3, shape_v, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case3, shape_f, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case3, shape_d, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case3, shape_h, slice0, slice1, slice2);
}

TEST_CASE("shape_slice(case4)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case4,   shape, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case4, shape_a, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case4, shape_v, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case4, shape_f, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case4, shape_d, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case4, shape_h, slice0, slice1, slice2);
}

TEST_CASE("shape_slice(case5)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case5,   shape, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case5, shape_a, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case5, shape_v, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case5, shape_f, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case5, shape_d, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case5, shape_h, slice0, slice1, slice2);
}

NMTOOLS_TESTING_DECLARE_CASE(index, slice)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int indices[3] = {0,0,1};
        int shape[3] = {2,3,2};
        auto slice0 = tuple{None,None};
        auto slice1 = tuple{0,1};
        auto slice2 = tuple{None,None};
        CAST_ARRAYS(indices)
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        // int result[3] = {2,1,2};
        int result[3] = {0,0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        int indices[3] = {1,2,0};
        int shape[3] = {2,3,2};
        auto slice0 = tuple{None,None};
        auto slice1 = tuple{None,None};
        auto slice2 = tuple{None,None};
        CAST_ARRAYS(indices)
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        // int result[3] = {2,3,2};
        int result[3] = {1,2,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        int indices[3] = {0,0,1};
        int shape[3] = {2,3,2};
        auto slice0 = tuple{1,2};
        auto slice1 = tuple{0,1};
        auto slice2 = tuple{None,None};
        CAST_ARRAYS(indices)
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        // int result[3] = {1,1,2};
        int result[3] = {1,0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        int indices[3] = {0,0,1};
        int shape[3] = {2,3,2};
        auto slice0 = tuple{1,3};
        auto slice1 = tuple{0,1};
        auto slice2 = tuple{None,None};
        CAST_ARRAYS(indices)
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        // int result[3] = {1,1,2};
        int result[3] = {1,0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        int indices[3] = {1,1,0};
        int shape[3] = {2,3,2};
        auto slice0 = tuple{None,None};
        auto slice1 = tuple{0,2};
        auto slice2 = tuple{None,-1};
        CAST_ARRAYS(indices)
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        // int result[3] = {2,2,1};
        int result[3] = {1,1,0};
    }
}

#define RUN_slice_impl(...) \
nm::index::slice(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs slice fn to callable lambda
#define RUN_slice(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("slice-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_slice_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_slice(case_name, ...) \
RUN_slice_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define SLICE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(index, slice, case_name); \
    using namespace args; \
    auto result = RUN_slice(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("slice(case1)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case1,   indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case1, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case1, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case1, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case1, indices_d, shape_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case1, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case2)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case2, indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case2, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case2, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case2, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case2, indices_d, shape_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case2, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case3)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case3, indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case3, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case3, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case3, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case3, indices_d, shape_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case3, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case4)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case4, indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case4, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case4, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case4, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case4, indices_d, shape_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case4, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case5)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case5, indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case5, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case5, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case5, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case5, indices_d, shape_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case5, indices_h, shape_h, slice0, slice1, slice2);
}