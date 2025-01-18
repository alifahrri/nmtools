#include "nmtools/array/index/take.hpp"
#include "nmtools/ndarray.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/constants.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;
using namespace nm::literals;

NMTOOLS_TESTING_DECLARE_CASE(index, shape_take)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int indices[3] = {0,1,4};
        int shape[2] = {2,5};
        int axis = 1;
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
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
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
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
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        int result[1] = {3};
    }

    // TODO: test for multidimensional indices
}

NMTOOLS_TESTING_DECLARE_CASE(index, constexpr_shape_take)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr int indices[3] = {0,1,4};
        constexpr int shape[2] = {2,5};
        constexpr int axis = 1;
        constexpr auto indices_ct = nmtools_tuple{0_ct,1_ct,4_ct};
        constexpr auto shape_ct   = nmtools_tuple{2_ct,5_ct};
        constexpr auto axis_ct    = 1_ct;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(indices)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr int result[2] = {2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        constexpr int indices[1] = {0};
        constexpr int shape[2] = {2,5};
        constexpr int axis = 0;
        constexpr auto indices_ct = nmtools_tuple{0_ct};
        constexpr auto shape_ct   = nmtools_tuple{2_ct,5_ct};
        constexpr auto axis_ct    = 0_ct;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(indices)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        constexpr int result[2] = {1,5};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        constexpr int indices[3] = {0,1,4};
        constexpr int shape[2] = {2,5};
        constexpr auto axis = None;
        constexpr auto indices_ct = nmtools_tuple{0_ct,1_ct,4_ct};
        constexpr auto shape_ct   = nmtools_tuple{2_ct,5_ct};
        constexpr auto axis_ct    = None;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(indices)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        constexpr int result[1] = {3};
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
        NMTOOLS_CAST_INDEX_ARRAYS(idx)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
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
        NMTOOLS_CAST_INDEX_ARRAYS(idx)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
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
        NMTOOLS_CAST_INDEX_ARRAYS(idx)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
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
        NMTOOLS_CAST_INDEX_ARRAYS(idx)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        int result[2] = {0,4};
    }
}

#define RUN_shape_take_impl(...) \
nm::index::shape_take(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
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
    NMTOOLS_TESTING_USE_CASE(index, shape_take, case_name); \
    using namespace args; \
    auto result = RUN_shape_take(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

#define CONSTEXPR_SHAPE_TAKE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index, constexpr_shape_take, case_name); \
    using namespace args; \
    constexpr auto result = RUN_shape_take_impl(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("shape_take(case1)" * doctest::test_suite("index::shape_take"))
{
    SHAPE_TAKE_SUBCASE( case1,   shape,   indices, axis );
    SHAPE_TAKE_SUBCASE( case1, shape_a, indices_a, axis );
    SHAPE_TAKE_SUBCASE( case1, shape_v, indices_v, axis );
    SHAPE_TAKE_SUBCASE( case1, shape_f, indices_f, axis );
    SHAPE_TAKE_SUBCASE( case1, shape_h, indices_h, axis );
}

TEST_CASE("shape_take(case2)" * doctest::test_suite("index::shape_take"))
{
    SHAPE_TAKE_SUBCASE( case2,   shape,   indices, axis );
    SHAPE_TAKE_SUBCASE( case2, shape_a, indices_a, axis );
    SHAPE_TAKE_SUBCASE( case2, shape_v, indices_v, axis );
    SHAPE_TAKE_SUBCASE( case2, shape_f, indices_f, axis );
    SHAPE_TAKE_SUBCASE( case2, shape_h, indices_h, axis );
}

TEST_CASE("shape_take(case3)" * doctest::test_suite("index::shape_take"))
{
    SHAPE_TAKE_SUBCASE( case3,    shape,   indices, axis );
    SHAPE_TAKE_SUBCASE( case3,  shape_a, indices_a, axis );
    SHAPE_TAKE_SUBCASE( case3,  shape_v, indices_v, axis );
    SHAPE_TAKE_SUBCASE( case3,  shape_f, indices_f, axis );
    SHAPE_TAKE_SUBCASE( case3,  shape_h, indices_h, axis );
}

TEST_CASE("shape_take(case1)" * doctest::test_suite("index::constexpr_shape_take"))
{
    CONSTEXPR_SHAPE_TAKE_SUBCASE( case1,   shape,   indices, axis );
    CONSTEXPR_SHAPE_TAKE_SUBCASE( case1, shape_a, indices_a, axis );
    CONSTEXPR_SHAPE_TAKE_SUBCASE( case1, shape_f, indices_f, axis );
    CONSTEXPR_SHAPE_TAKE_SUBCASE( case1, shape_h, indices_h, axis );

    CONSTEXPR_SHAPE_TAKE_SUBCASE( case1, shape_ct, indices_ct, axis_ct );
}

TEST_CASE("shape_take(case2)" * doctest::test_suite("index::constexpr_shape_take"))
{
    CONSTEXPR_SHAPE_TAKE_SUBCASE( case2,   shape,   indices, axis );
    CONSTEXPR_SHAPE_TAKE_SUBCASE( case2, shape_a, indices_a, axis );
    CONSTEXPR_SHAPE_TAKE_SUBCASE( case2, shape_f, indices_f, axis );
    CONSTEXPR_SHAPE_TAKE_SUBCASE( case2, shape_h, indices_h, axis );
    
    CONSTEXPR_SHAPE_TAKE_SUBCASE( case2, shape_ct, indices_ct, axis_ct );
}

TEST_CASE("shape_take(case3)" * doctest::test_suite("index::constexpr_shape_take"))
{
    CONSTEXPR_SHAPE_TAKE_SUBCASE( case3,   shape,   indices, axis );
    CONSTEXPR_SHAPE_TAKE_SUBCASE( case3, shape_a, indices_a, axis );
    CONSTEXPR_SHAPE_TAKE_SUBCASE( case3, shape_f, indices_f, axis );
    CONSTEXPR_SHAPE_TAKE_SUBCASE( case3, shape_h, indices_h, axis );

    CONSTEXPR_SHAPE_TAKE_SUBCASE( case3, shape_ct, indices_ct, axis_ct );
}

#define RUN_take_impl(...) \
nm::index::take(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
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
    NMTOOLS_TESTING_USE_CASE(index, take, case_name); \
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
    // dynamic dimension ndarray is not considered as index array, even if the element type is index type
    TAKE_SUBCASE( case1, idx_h, shape_h, indices_h, axis );
}

TEST_CASE("take(case2)" * doctest::test_suite("index::take"))
{
    TAKE_SUBCASE( case2,   idx,   shape,   indices, axis );
    TAKE_SUBCASE( case2, idx_a, shape_a, indices_a, axis );
    TAKE_SUBCASE( case2, idx_v, shape_v, indices_v, axis );
    TAKE_SUBCASE( case2, idx_f, shape_f, indices_f, axis );
    TAKE_SUBCASE( case2, idx_h, shape_h, indices_h, axis );
}

TEST_CASE("take(case3)" * doctest::test_suite("index::take"))
{
    TAKE_SUBCASE( case3,   idx,   shape,   indices, axis );
    TAKE_SUBCASE( case3, idx_a, shape_a, indices_a, axis );
    TAKE_SUBCASE( case3, idx_v, shape_v, indices_v, axis );
    TAKE_SUBCASE( case3, idx_f, shape_f, indices_f, axis );
    TAKE_SUBCASE( case3, idx_h, shape_h, indices_h, axis );
}

TEST_CASE("take(case4)" * doctest::test_suite("index::take"))
{
    TAKE_SUBCASE( case4,   idx,   shape,   indices, axis );
    TAKE_SUBCASE( case4, idx_a, shape_a, indices_a, axis );
    TAKE_SUBCASE( case4, idx_v, shape_v, indices_v, axis );
    TAKE_SUBCASE( case4, idx_f, shape_f, indices_f, axis );
    TAKE_SUBCASE( case4, idx_h, shape_h, indices_h, axis );
}