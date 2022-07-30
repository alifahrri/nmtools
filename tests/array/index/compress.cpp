#include "nmtools/array/index/compress.hpp"
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

NMTOOLS_TESTING_DECLARE_CASE(index, shape_compress)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int condition[2] = {0,1};
        int shape[2] = {3,2};
        int axis = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(condition)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int result[2] = {1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        int condition[3] = {0,1,1};
        int shape[2] = {3,2};
        int axis = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(condition)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        int result[2] = {2,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        int condition[2] = {0,1};
        int shape[2] = {3,2};
        int axis = 1;
        NMTOOLS_CAST_INDEX_ARRAYS(condition)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        int result[2] = {3,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        int condition[1] = {0};
        int shape[2] = {3,2};
        int axis = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(condition)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        int result[2] = {0,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        bool condition[3] = {false,true,true};
        int shape[2] = {3,2};
        int axis = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(condition)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        int result[2] = {2,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        bool condition[5] = {false,true,true,false,true};
        int shape[2] = {3,2};
        auto axis = None;
        NMTOOLS_CAST_INDEX_ARRAYS(condition)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        int result[1] = {3};
    }
}

NMTOOLS_TESTING_DECLARE_CASE(index, compress)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int indices[2]   = {0,0};
        int condition[2] = {0,1};
        int shape[2] = {3,2};
        int axis = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(condition)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int result[2] = {1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        int indices[2]   = {1,0};
        int condition[3] = {0,1,1};
        int shape[2] = {3,2};
        int axis = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(condition)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        int result[2] = {2,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        int indices[2]   = {1,0};
        int condition[3] = {1,0,1};
        int shape[2] = {3,2};
        int axis = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(condition)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        int result[2] = {2,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        int indices[2]   = {2,0};
        int condition[5] = {1,0,1,0,1};
        int shape[2] = {5,2};
        int axis = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(condition)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        int result[2] = {4,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        int indices[3]   = {1,1,1};
        int condition[5] = {1,0,1,0,1};
        int shape[3] = {2,5,2};
        int axis = 1;
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(condition)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        int result[3] = {1,2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        int indices[1] = {0};
        int condition[2] = {false, true};
        int shape[2] = {3,2};
        auto axis = None;
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(condition)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        int result[2] = {0,1};
    }
}

#define RUN_shape_compress_impl(...) \
nm::index::shape_compress(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs shape_compress fn to callable lambda
#define RUN_shape_compress(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("shape_compress-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_shape_compress_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_shape_compress(case_name, ...) \
RUN_shape_compress_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define SHAPE_COMPRESS_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(index, shape_compress, case_name); \
    using namespace args; \
    auto result = RUN_shape_compress(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("shape_compress(case1)" * doctest::test_suite("index::shape_compress"))
{
    SHAPE_COMPRESS_SUBCASE( case1,   condition,   shape, axis );
    SHAPE_COMPRESS_SUBCASE( case1, condition_a, shape_a, axis );
    SHAPE_COMPRESS_SUBCASE( case1, condition_v, shape_v, axis );
    SHAPE_COMPRESS_SUBCASE( case1, condition_f, shape_f, axis );
    SHAPE_COMPRESS_SUBCASE( case1, condition_h, shape_h, axis );
}

TEST_CASE("shape_compress(case2)" * doctest::test_suite("index::shape_compress"))
{
    SHAPE_COMPRESS_SUBCASE( case2,   condition,   shape, axis );
    SHAPE_COMPRESS_SUBCASE( case2, condition_a, shape_a, axis );
    SHAPE_COMPRESS_SUBCASE( case2, condition_v, shape_v, axis );
    SHAPE_COMPRESS_SUBCASE( case2, condition_f, shape_f, axis );
    SHAPE_COMPRESS_SUBCASE( case2, condition_h, shape_h, axis );
}

TEST_CASE("shape_compress(case3)" * doctest::test_suite("index::shape_compress"))
{
    SHAPE_COMPRESS_SUBCASE( case3,   condition,   shape, axis );
    SHAPE_COMPRESS_SUBCASE( case3, condition_a, shape_a, axis );
    SHAPE_COMPRESS_SUBCASE( case3, condition_v, shape_v, axis );
    SHAPE_COMPRESS_SUBCASE( case3, condition_f, shape_f, axis );
    SHAPE_COMPRESS_SUBCASE( case3, condition_h, shape_h, axis );
}

TEST_CASE("shape_compress(case4)" * doctest::test_suite("index::shape_compress"))
{
    SHAPE_COMPRESS_SUBCASE( case4,   condition,   shape, axis );
    SHAPE_COMPRESS_SUBCASE( case4, condition_a, shape_a, axis );
    SHAPE_COMPRESS_SUBCASE( case4, condition_v, shape_v, axis );
    SHAPE_COMPRESS_SUBCASE( case4, condition_f, shape_f, axis );
    SHAPE_COMPRESS_SUBCASE( case4, condition_h, shape_h, axis );
}

TEST_CASE("shape_compress(case5)" * doctest::test_suite("index::shape_compress"))
{
    SHAPE_COMPRESS_SUBCASE( case5,   condition,   shape, axis );
    SHAPE_COMPRESS_SUBCASE( case5, condition_a, shape_a, axis );
    SHAPE_COMPRESS_SUBCASE( case5, condition_v, shape_v, axis );
    SHAPE_COMPRESS_SUBCASE( case5, condition_f, shape_f, axis );
    SHAPE_COMPRESS_SUBCASE( case5, condition_h, shape_h, axis );
}

TEST_CASE("shape_compress(case6)" * doctest::test_suite("index::shape_compress"))
{
    SHAPE_COMPRESS_SUBCASE( case6,   condition,   shape, axis );
    SHAPE_COMPRESS_SUBCASE( case6, condition_a, shape_a, axis );
    SHAPE_COMPRESS_SUBCASE( case6, condition_v, shape_v, axis );
    SHAPE_COMPRESS_SUBCASE( case6, condition_f, shape_f, axis );
    SHAPE_COMPRESS_SUBCASE( case6, condition_h, shape_h, axis );
}

#define RUN_compress_impl(...) \
nm::index::compress(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs compress fn to callable lambda
#define RUN_compress(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("compress-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_compress_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_compress(case_name, ...) \
RUN_compress_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define COMPRESS_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(index, compress, case_name); \
    using namespace args; \
    auto result = RUN_compress(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("compress(case1)" * doctest::test_suite("index::compress"))
{
    COMPRESS_SUBCASE( case1, indices,   condition,   shape, axis );
    COMPRESS_SUBCASE( case1, indices_a, condition_a, shape_a, axis );
    COMPRESS_SUBCASE( case1, indices_v, condition_v, shape_v, axis );
    COMPRESS_SUBCASE( case1, indices_f, condition_f, shape_f, axis );
    COMPRESS_SUBCASE( case1, indices_h, condition_h, shape_h, axis );
}

TEST_CASE("compress(case2)" * doctest::test_suite("index::compress"))
{
    COMPRESS_SUBCASE( case2, indices,   condition,   shape, axis );
    COMPRESS_SUBCASE( case2, indices_a, condition_a, shape_a, axis );
    COMPRESS_SUBCASE( case2, indices_v, condition_v, shape_v, axis );
    COMPRESS_SUBCASE( case2, indices_f, condition_f, shape_f, axis );
    COMPRESS_SUBCASE( case2, indices_h, condition_h, shape_h, axis );
}

TEST_CASE("compress(case3)" * doctest::test_suite("index::compress"))
{
    COMPRESS_SUBCASE( case3, indices,   condition,   shape, axis );
    COMPRESS_SUBCASE( case3, indices_a, condition_a, shape_a, axis );
    COMPRESS_SUBCASE( case3, indices_v, condition_v, shape_v, axis );
    COMPRESS_SUBCASE( case3, indices_f, condition_f, shape_f, axis );
    COMPRESS_SUBCASE( case3, indices_h, condition_h, shape_h, axis );
}

TEST_CASE("compress(case4)" * doctest::test_suite("index::compress"))
{
    COMPRESS_SUBCASE( case4, indices,   condition,   shape, axis );
    COMPRESS_SUBCASE( case4, indices_a, condition_a, shape_a, axis );
    COMPRESS_SUBCASE( case4, indices_v, condition_v, shape_v, axis );
    COMPRESS_SUBCASE( case4, indices_f, condition_f, shape_f, axis );
    COMPRESS_SUBCASE( case4, indices_h, condition_h, shape_h, axis );
}

TEST_CASE("compress(case5)" * doctest::test_suite("index::compress"))
{
    COMPRESS_SUBCASE( case5, indices,   condition,   shape, axis );
    COMPRESS_SUBCASE( case5, indices_a, condition_a, shape_a, axis );
    COMPRESS_SUBCASE( case5, indices_v, condition_v, shape_v, axis );
    COMPRESS_SUBCASE( case5, indices_f, condition_f, shape_f, axis );
    COMPRESS_SUBCASE( case5, indices_h, condition_h, shape_h, axis );
}

TEST_CASE("compress(case6)" * doctest::test_suite("index::compress"))
{
    COMPRESS_SUBCASE( case6, indices,   condition,   shape, axis );
    COMPRESS_SUBCASE( case6, indices_a, condition_a, shape_a, axis );
    COMPRESS_SUBCASE( case6, indices_v, condition_v, shape_v, axis );
    COMPRESS_SUBCASE( case6, indices_f, condition_f, shape_f, axis );
    COMPRESS_SUBCASE( case6, indices_h, condition_h, shape_h, axis );
}