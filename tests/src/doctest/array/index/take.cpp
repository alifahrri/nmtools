#include "nmtools/array/index/take.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/constants.hpp"

#include <array>
#include <tuple>
#include <vector>

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

#define CAST_ARRAYS(name) \
auto name##_a = cast(name, kind::nested_arr); \
auto name##_v = cast(name, kind::nested_vec); \
auto name##_f = cast(name, kind::fixed); \
auto name##_d = cast(name, kind::dynamic); \
auto name##_h = cast(name, kind::hybrid); \

NMTOOLS_TESTING_DECLARE_CASE(index, shape_take)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int indices[3] = {0,1,4};
        int shape[2] = {2,5};
        int axis = 1;
        CAST_ARRAYS(indices)
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int result[2] = {2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        int indices[1] = {0};
        int shape[2] = {2,5};
        int axis = 0;
        CAST_ARRAYS(indices)
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        int result[2] = {1,5};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        int indices[3] = {0,1,4};
        int shape[2] = {2,5};
        auto axis = None;
        CAST_ARRAYS(indices)
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        int result[1] = {3};
    }
}

NMTOOLS_TESTING_DECLARE_CASE(index, take)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int idx[1] = {2};
        int shape[1] = {6};
        int indices[3] = {0,1,4};
        int axis = 0;
        CAST_ARRAYS(idx)
        CAST_ARRAYS(indices)
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int result[1] = {4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        int idx[1] = {2};
        int shape[1] = {6};
        int indices[3] = {0,1,4};
        auto axis = None;
        CAST_ARRAYS(idx)
        CAST_ARRAYS(indices)
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        int result[1] = {4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        int idx[1] = {2};
        int shape[2] = {2,5};
        int indices[3] = {0,1,4};
        auto axis = None;
        CAST_ARRAYS(idx)
        CAST_ARRAYS(indices)
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        int result[2] = {0,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        int idx[2] = {0,2};
        int shape[2] = {2,5};
        int indices[3] = {0,1,4};
        int axis = 1;
        CAST_ARRAYS(idx)
        CAST_ARRAYS(indices)
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        int result[2] = {0,4};
    }
}

#define RUN_shape_take_impl(...) \
nm::index::shape_take(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs shape_take fn to callable lambda
#define RUN_shape_take(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("shape_take-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_shape_take_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_shape_take(case_name, ...) \
RUN_shape_take_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define SHAPE_TAKE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(index, shape_take, case_name); \
    using namespace args; \
    auto result = RUN_shape_take(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("shape_take(case1)" * doctest::test_suite("index::shape_take"))
{
    SHAPE_TAKE_SUBCASE( case1,   shape,   indices, axis );
    SHAPE_TAKE_SUBCASE( case1, shape_a, indices_a, axis );
    SHAPE_TAKE_SUBCASE( case1, shape_v, indices_v, axis );
    SHAPE_TAKE_SUBCASE( case1, shape_f, indices_f, axis );
    SHAPE_TAKE_SUBCASE( case1, shape_d, indices_d, axis );
    SHAPE_TAKE_SUBCASE( case1, shape_h, indices_h, axis );
}

TEST_CASE("shape_take(case2)" * doctest::test_suite("index::shape_take"))
{
    SHAPE_TAKE_SUBCASE( case2,   shape,   indices, axis );
    SHAPE_TAKE_SUBCASE( case2, shape_a, indices_a, axis );
    SHAPE_TAKE_SUBCASE( case2, shape_v, indices_v, axis );
    SHAPE_TAKE_SUBCASE( case2, shape_f, indices_f, axis );
    SHAPE_TAKE_SUBCASE( case2, shape_d, indices_d, axis );
    SHAPE_TAKE_SUBCASE( case2, shape_h, indices_h, axis );
}

TEST_CASE("shape_take(case3)" * doctest::test_suite("index::shape_take"))
{
    SHAPE_TAKE_SUBCASE( case3,    shape,   indices, axis );
    SHAPE_TAKE_SUBCASE( case3,  shape_a, indices_a, axis );
    SHAPE_TAKE_SUBCASE( case3,  shape_v, indices_v, axis );
    SHAPE_TAKE_SUBCASE( case3,  shape_f, indices_f, axis );
    SHAPE_TAKE_SUBCASE( case3,  shape_d, indices_d, axis );
    SHAPE_TAKE_SUBCASE( case3,  shape_h, indices_h, axis );
}

#define RUN_take_impl(...) \
nm::index::take(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs take fn to callable lambda
#define RUN_take(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("take-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_take_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_take(case_name, ...) \
RUN_take_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define TAKE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(index, take, case_name); \
    using namespace args; \
    auto result = RUN_take(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("take(case1)" * doctest::test_suite("index::take"))
{
    TAKE_SUBCASE( case1,   idx,   shape,   indices, axis );
    TAKE_SUBCASE( case1, idx_a, shape_a, indices_a, axis );
    TAKE_SUBCASE( case1, idx_v, shape_v, indices_v, axis );
    TAKE_SUBCASE( case1, idx_f, shape_f, indices_f, axis );
    TAKE_SUBCASE( case1, idx_d, shape_d, indices_d, axis );
    TAKE_SUBCASE( case1, idx_h, shape_h, indices_h, axis );
}

TEST_CASE("take(case2)" * doctest::test_suite("index::take"))
{
    TAKE_SUBCASE( case2,   idx,   shape,   indices, axis );
    TAKE_SUBCASE( case2, idx_a, shape_a, indices_a, axis );
    TAKE_SUBCASE( case2, idx_v, shape_v, indices_v, axis );
    TAKE_SUBCASE( case2, idx_f, shape_f, indices_f, axis );
    TAKE_SUBCASE( case2, idx_d, shape_d, indices_d, axis );
    TAKE_SUBCASE( case2, idx_h, shape_h, indices_h, axis );
}

TEST_CASE("take(case3)" * doctest::test_suite("index::take"))
{
    TAKE_SUBCASE( case3,   idx,   shape,   indices, axis );
    TAKE_SUBCASE( case3, idx_a, shape_a, indices_a, axis );
    TAKE_SUBCASE( case3, idx_v, shape_v, indices_v, axis );
    TAKE_SUBCASE( case3, idx_f, shape_f, indices_f, axis );
    TAKE_SUBCASE( case3, idx_d, shape_d, indices_d, axis );
    TAKE_SUBCASE( case3, idx_h, shape_h, indices_h, axis );
}

TEST_CASE("take(case4)" * doctest::test_suite("index::take"))
{
    TAKE_SUBCASE( case4,   idx,   shape,   indices, axis );
    TAKE_SUBCASE( case4, idx_a, shape_a, indices_a, axis );
    TAKE_SUBCASE( case4, idx_v, shape_v, indices_v, axis );
    TAKE_SUBCASE( case4, idx_f, shape_f, indices_f, axis );
    TAKE_SUBCASE( case4, idx_d, shape_d, indices_d, axis );
    TAKE_SUBCASE( case4, idx_h, shape_h, indices_h, axis );
}