#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/testing/testing.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

// TODO: add index vector kind, do not use nested vec
#ifndef PLATFORMIO
#define CAST_ARRAYS(name) \
inline auto name##_a = cast(name, kind::nested_arr); \
inline auto name##_v = cast(name, kind::nested_vec); \
inline auto name##_f = cast(name, kind::fixed); \
inline auto name##_d = cast(name, kind::dynamic); \
inline auto name##_h = cast(name, kind::hybrid);
#else
#define CAST_ARRAYS(name) \
inline auto name##_a = cast(name, kind::nested_arr); \
inline auto name##_f = cast(name, kind::fixed); \
inline auto name##_h = cast(name, kind::hybrid);
#endif // PLATFORMIO

NMTOOLS_TESTING_DECLARE_CASE(index, normalize_axis)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int axis[3] = {-1,-2,-3};
        inline int ndim = 3;
        CAST_ARRAYS(axis);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[3] = {2,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int axis[3] = {-1,-2,3};
        inline int ndim = 3;
        CAST_ARRAYS(axis);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        // AxisError: axis 3 is out of bounds for array of dimension 3
        inline auto result = meta::Nothing;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int axis[3] = {-1,2,-3};
        inline int ndim = 3;
        CAST_ARRAYS(axis);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[3] = {2,2,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int axis = -3;
        inline int ndim = 3;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result = 0;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int axis = 3;
        inline int ndim = 3;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline auto result = meta::Nothing;
    }
}

#include "nmtools/array/index/normalize_axis.hpp"
#include "nmtools/testing/doctest.hpp"

#define RUN_impl(...) \
nm::index::normalize_axis(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs normalize_axis fn to callable lambda
#define RUN_normalize_axis(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("normalize_axis-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_normalize_axis(case_name, ...) \
RUN_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define NORMALIZE_AXIS_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(index, normalize_axis, case_name); \
    using namespace args; \
    auto result = RUN_normalize_axis(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
} \


TEST_CASE("normalize_axis(case1)" * doctest::test_suite("index::normalize_axis"))
{
    NORMALIZE_AXIS_SUBCASE( case1, axis, ndim );
    NORMALIZE_AXIS_SUBCASE( case1, axis_a, ndim );
    NORMALIZE_AXIS_SUBCASE( case1, axis_v, ndim );
    NORMALIZE_AXIS_SUBCASE( case1, axis_f, ndim );
    NORMALIZE_AXIS_SUBCASE( case1, axis_h, ndim );
}

TEST_CASE("normalize_axis(case2)" * doctest::test_suite("index::normalize_axis"))
{
    NORMALIZE_AXIS_SUBCASE( case2, axis, ndim );
    NORMALIZE_AXIS_SUBCASE( case2, axis_a, ndim );
    NORMALIZE_AXIS_SUBCASE( case2, axis_v, ndim );
    NORMALIZE_AXIS_SUBCASE( case2, axis_f, ndim );
    NORMALIZE_AXIS_SUBCASE( case2, axis_h, ndim );
}

TEST_CASE("normalize_axis(case4)" * doctest::test_suite("index::normalize_axis"))
{
    NORMALIZE_AXIS_SUBCASE( case4, axis, ndim );
    NORMALIZE_AXIS_SUBCASE( case4, axis, ndim );
    NORMALIZE_AXIS_SUBCASE( case4, axis, ndim );
    NORMALIZE_AXIS_SUBCASE( case4, axis, ndim );
    NORMALIZE_AXIS_SUBCASE( case4, axis, ndim );
}

TEST_CASE("normalize_axis(case5)" * doctest::test_suite("index::normalize_axis"))
{
    NORMALIZE_AXIS_SUBCASE( case5, axis, ndim );
    NORMALIZE_AXIS_SUBCASE( case5, axis, ndim );
    NORMALIZE_AXIS_SUBCASE( case5, axis, ndim );
    NORMALIZE_AXIS_SUBCASE( case5, axis, ndim );
    NORMALIZE_AXIS_SUBCASE( case5, axis, ndim );
}