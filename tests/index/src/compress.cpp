#include "nmtools/array/index/compress.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/constants.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

using namespace nmtools::literals;

NMTOOLS_TESTING_DECLARE_CASE(index, shape_compress)
{
    // TODO: provide helper class form constant index to clipped index
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int condition[2] = {0,1};
        int shape[2] = {3,2};
        int axis = 0;
        auto condition_ct = nmtools_tuple{0_ct,1_ct};
        auto condition_cl = nmtools_tuple{"0:[1]"_ct,"1:[1]"_ct};
        auto shape_ct = nmtools_tuple{3_ct,2_ct};
        auto shape_cl = nmtools_tuple{"3:[3]"_ct,"2:[2]"_ct};
        auto axis_ct  = 0_ct;
        auto axis_cl  = "0:[1]"_ct;
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
        auto condition_ct = nmtools_tuple{0_ct,1_ct,1_ct};
        auto condition_cl = nmtools_tuple{"0:[1]"_ct,"1:[1]"_ct,"1:[1]"_ct};
        auto shape_ct = nmtools_tuple{3_ct,2_ct};
        auto shape_cl = nmtools_tuple{"3:[3]"_ct,"2:[2]"_ct};
        auto axis_ct  = 0_ct;
        auto axis_cl  = "0:[1]"_ct;
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
        auto condition_ct = nmtools_tuple{0_ct,1_ct};
        auto condition_cl = nmtools_tuple{"0:[1]"_ct,"1:[1]"_ct};
        auto shape_ct = nmtools_tuple{3_ct,2_ct};
        auto shape_cl = nmtools_tuple{"3:[3]"_ct,"2:[2]"_ct};
        auto axis_ct  = 1_ct;
        auto axis_cl  = "1:[1]"_ct;
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
        auto condition_ct = nmtools_tuple{0_ct};
        auto condition_cl = nmtools_tuple{"0:[1]"_ct};
        auto shape_ct = nmtools_tuple{3_ct,2_ct};
        auto shape_cl = nmtools_tuple{"3:[3]"_ct,"2:[2]"_ct};
        auto axis_ct  = 0_ct;
        auto axis_cl  = "0:[1]"_ct;
        NMTOOLS_CAST_INDEX_ARRAYS(condition)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        int result[2] = {0,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        nm_bool_t condition[3] = {false,true,true};
        int shape[2] = {3,2};
        int axis = 0;
        auto condition_ct = nmtools_tuple{0_ct,1_ct,1_ct};
        auto condition_cl = nmtools_tuple{"0:[1]"_ct,"1:[1]"_ct,"1:[1]"_ct};
        auto shape_ct = nmtools_tuple{3_ct,2_ct};
        auto shape_cl = nmtools_tuple{"3:[3]"_ct,"2:[2]"_ct};
        auto axis_ct  = 0_ct;
        auto axis_cl  = "0:[1]"_ct;
        NMTOOLS_CAST_INDEX_ARRAYS(condition)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        int result[2] = {2,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        nm_bool_t condition[5] = {false,true,true,false,true};
        int shape[2] = {3,2};
        auto axis = None;
        auto condition_ct = nmtools_tuple{0_ct,1_ct,1_ct,0_ct,1_ct};
        auto condition_cl = nmtools_tuple{"0:[1]"_ct,"1:[1]"_ct,"1:[1]"_ct,"0:[1]"_ct,"1:[1]"_ct};
        auto shape_ct = nmtools_tuple{3_ct,2_ct};
        auto shape_cl = nmtools_tuple{"3:[3]"_ct,"2:[2]"_ct};
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
    NMTOOLS_TESTING_USE_CASE(index, shape_compress, case_name); \
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

    SHAPE_COMPRESS_SUBCASE( case1, condition_ct, shape_ct, axis_ct );
    SHAPE_COMPRESS_SUBCASE( case1, condition_ct, shape_cl, axis_ct );

    SHAPE_COMPRESS_SUBCASE( case1, condition_a, shape_v, axis );
    SHAPE_COMPRESS_SUBCASE( case1, condition_a, shape_f, axis );
    SHAPE_COMPRESS_SUBCASE( case1, condition_a, shape_h, axis );
    SHAPE_COMPRESS_SUBCASE( case1, condition_a, shape_ct, axis );
    SHAPE_COMPRESS_SUBCASE( case1, condition_a, shape_cl, axis );

    SHAPE_COMPRESS_SUBCASE( case1, condition_v, shape_a, axis );
    SHAPE_COMPRESS_SUBCASE( case1, condition_v, shape_f, axis );
    SHAPE_COMPRESS_SUBCASE( case1, condition_v, shape_h, axis );
    SHAPE_COMPRESS_SUBCASE( case1, condition_v, shape_ct, axis );
    SHAPE_COMPRESS_SUBCASE( case1, condition_v, shape_cl, axis );

    SHAPE_COMPRESS_SUBCASE( case1, condition_f, shape_a, axis );
    SHAPE_COMPRESS_SUBCASE( case1, condition_f, shape_v, axis );
    SHAPE_COMPRESS_SUBCASE( case1, condition_f, shape_h, axis );
    SHAPE_COMPRESS_SUBCASE( case1, condition_f, shape_ct, axis );
    SHAPE_COMPRESS_SUBCASE( case1, condition_f, shape_cl, axis );

    SHAPE_COMPRESS_SUBCASE( case1, condition_h, shape_a, axis );
    SHAPE_COMPRESS_SUBCASE( case1, condition_h, shape_v, axis );
    SHAPE_COMPRESS_SUBCASE( case1, condition_h, shape_f, axis );
    SHAPE_COMPRESS_SUBCASE( case1, condition_h, shape_ct, axis );
    SHAPE_COMPRESS_SUBCASE( case1, condition_h, shape_cl, axis );

    SHAPE_COMPRESS_SUBCASE( case1, condition_ct, shape_a, axis );
    SHAPE_COMPRESS_SUBCASE( case1, condition_ct, shape_v, axis );
    SHAPE_COMPRESS_SUBCASE( case1, condition_ct, shape_f, axis );
    SHAPE_COMPRESS_SUBCASE( case1, condition_ct, shape_h, axis );
    SHAPE_COMPRESS_SUBCASE( case1, condition_ct, shape_cl, axis );

    SHAPE_COMPRESS_SUBCASE( case1, condition_cl, shape_a, axis );
    SHAPE_COMPRESS_SUBCASE( case1, condition_cl, shape_v, axis );
    SHAPE_COMPRESS_SUBCASE( case1, condition_cl, shape_f, axis );
    SHAPE_COMPRESS_SUBCASE( case1, condition_cl, shape_h, axis );
    SHAPE_COMPRESS_SUBCASE( case1, condition_cl, shape_ct, axis );


    SHAPE_COMPRESS_SUBCASE( case1, condition_a, shape_v, axis_ct );
    SHAPE_COMPRESS_SUBCASE( case1, condition_a, shape_f, axis_ct );
    SHAPE_COMPRESS_SUBCASE( case1, condition_a, shape_h, axis_ct );
    SHAPE_COMPRESS_SUBCASE( case1, condition_a, shape_ct, axis_ct );
    SHAPE_COMPRESS_SUBCASE( case1, condition_a, shape_cl, axis_ct );

    SHAPE_COMPRESS_SUBCASE( case1, condition_v, shape_a, axis_ct );
    SHAPE_COMPRESS_SUBCASE( case1, condition_v, shape_f, axis_ct );
    SHAPE_COMPRESS_SUBCASE( case1, condition_v, shape_h, axis_ct );
    SHAPE_COMPRESS_SUBCASE( case1, condition_v, shape_ct, axis_ct );
    SHAPE_COMPRESS_SUBCASE( case1, condition_v, shape_cl, axis_ct );

    SHAPE_COMPRESS_SUBCASE( case1, condition_f, shape_a, axis_ct );
    SHAPE_COMPRESS_SUBCASE( case1, condition_f, shape_v, axis_ct );
    SHAPE_COMPRESS_SUBCASE( case1, condition_f, shape_h, axis_ct );
    SHAPE_COMPRESS_SUBCASE( case1, condition_f, shape_ct, axis_ct );
    SHAPE_COMPRESS_SUBCASE( case1, condition_f, shape_cl, axis_ct );

    SHAPE_COMPRESS_SUBCASE( case1, condition_h, shape_a, axis_ct );
    SHAPE_COMPRESS_SUBCASE( case1, condition_h, shape_v, axis_ct );
    SHAPE_COMPRESS_SUBCASE( case1, condition_h, shape_f, axis_ct );
    SHAPE_COMPRESS_SUBCASE( case1, condition_h, shape_ct, axis_ct );
    SHAPE_COMPRESS_SUBCASE( case1, condition_h, shape_cl, axis_ct );

    SHAPE_COMPRESS_SUBCASE( case1, condition_ct, shape_a, axis_ct );
    SHAPE_COMPRESS_SUBCASE( case1, condition_ct, shape_v, axis_ct );
    SHAPE_COMPRESS_SUBCASE( case1, condition_ct, shape_f, axis_ct );
    SHAPE_COMPRESS_SUBCASE( case1, condition_ct, shape_h, axis_ct );
    SHAPE_COMPRESS_SUBCASE( case1, condition_ct, shape_cl, axis_ct );

    SHAPE_COMPRESS_SUBCASE( case1, condition_cl, shape_a, axis_ct );
    SHAPE_COMPRESS_SUBCASE( case1, condition_cl, shape_v, axis_ct );
    SHAPE_COMPRESS_SUBCASE( case1, condition_cl, shape_f, axis_ct );
    SHAPE_COMPRESS_SUBCASE( case1, condition_cl, shape_h, axis_ct );
    SHAPE_COMPRESS_SUBCASE( case1, condition_cl, shape_ct, axis_ct );
}

TEST_CASE("shape_compress(case2)" * doctest::test_suite("index::shape_compress"))
{
    SHAPE_COMPRESS_SUBCASE( case2,   condition,   shape, axis );
    SHAPE_COMPRESS_SUBCASE( case2, condition_a, shape_a, axis );
    SHAPE_COMPRESS_SUBCASE( case2, condition_v, shape_v, axis );
    SHAPE_COMPRESS_SUBCASE( case2, condition_f, shape_f, axis );
    SHAPE_COMPRESS_SUBCASE( case2, condition_h, shape_h, axis );

    SHAPE_COMPRESS_SUBCASE( case2, condition_ct, shape_ct, axis_ct );
    SHAPE_COMPRESS_SUBCASE( case2, condition_ct, shape_cl, axis_ct );
}

TEST_CASE("shape_compress(case3)" * doctest::test_suite("index::shape_compress"))
{
    SHAPE_COMPRESS_SUBCASE( case3,   condition,   shape, axis );
    SHAPE_COMPRESS_SUBCASE( case3, condition_a, shape_a, axis );
    SHAPE_COMPRESS_SUBCASE( case3, condition_v, shape_v, axis );
    SHAPE_COMPRESS_SUBCASE( case3, condition_f, shape_f, axis );
    SHAPE_COMPRESS_SUBCASE( case3, condition_h, shape_h, axis );

    SHAPE_COMPRESS_SUBCASE( case3, condition_ct, shape_ct, axis_ct );
    SHAPE_COMPRESS_SUBCASE( case3, condition_ct, shape_cl, axis_ct );
}

TEST_CASE("shape_compress(case4)" * doctest::test_suite("index::shape_compress"))
{
    SHAPE_COMPRESS_SUBCASE( case4,   condition,   shape, axis );
    SHAPE_COMPRESS_SUBCASE( case4, condition_a, shape_a, axis );
    SHAPE_COMPRESS_SUBCASE( case4, condition_v, shape_v, axis );
    SHAPE_COMPRESS_SUBCASE( case4, condition_f, shape_f, axis );
    SHAPE_COMPRESS_SUBCASE( case4, condition_h, shape_h, axis );

    SHAPE_COMPRESS_SUBCASE( case4, condition_ct, shape_ct, axis_ct );
    SHAPE_COMPRESS_SUBCASE( case4, condition_ct, shape_cl, axis_ct );
}

TEST_CASE("shape_compress(case5)" * doctest::test_suite("index::shape_compress"))
{
    SHAPE_COMPRESS_SUBCASE( case5,   condition,   shape, axis );
    SHAPE_COMPRESS_SUBCASE( case5, condition_a, shape_a, axis );
    SHAPE_COMPRESS_SUBCASE( case5, condition_v, shape_v, axis );
    SHAPE_COMPRESS_SUBCASE( case5, condition_f, shape_f, axis );
    SHAPE_COMPRESS_SUBCASE( case5, condition_h, shape_h, axis );

    SHAPE_COMPRESS_SUBCASE( case5, condition_ct, shape_ct, axis_ct );
    SHAPE_COMPRESS_SUBCASE( case5, condition_ct, shape_cl, axis_ct );
}

TEST_CASE("shape_compress(case6)" * doctest::test_suite("index::shape_compress"))
{
    SHAPE_COMPRESS_SUBCASE( case6,   condition,   shape, axis );
    SHAPE_COMPRESS_SUBCASE( case6, condition_a, shape_a, axis );
    SHAPE_COMPRESS_SUBCASE( case6, condition_v, shape_v, axis );
    SHAPE_COMPRESS_SUBCASE( case6, condition_f, shape_f, axis );
    SHAPE_COMPRESS_SUBCASE( case6, condition_h, shape_h, axis );

    SHAPE_COMPRESS_SUBCASE( case6, condition_ct, shape_ct, axis );
    SHAPE_COMPRESS_SUBCASE( case6, condition_ct, shape_cl, axis );

    SHAPE_COMPRESS_SUBCASE( case6, condition_a, shape_v, axis );
    SHAPE_COMPRESS_SUBCASE( case6, condition_a, shape_f, axis );
    SHAPE_COMPRESS_SUBCASE( case6, condition_a, shape_h, axis );
    SHAPE_COMPRESS_SUBCASE( case6, condition_a, shape_ct, axis );
    SHAPE_COMPRESS_SUBCASE( case6, condition_a, shape_cl, axis );

    SHAPE_COMPRESS_SUBCASE( case6, condition_v, shape_a, axis );
    SHAPE_COMPRESS_SUBCASE( case6, condition_v, shape_f, axis );
    SHAPE_COMPRESS_SUBCASE( case6, condition_v, shape_h, axis );
    SHAPE_COMPRESS_SUBCASE( case6, condition_v, shape_ct, axis );
    SHAPE_COMPRESS_SUBCASE( case6, condition_v, shape_cl, axis );

    SHAPE_COMPRESS_SUBCASE( case6, condition_f, shape_a, axis );
    SHAPE_COMPRESS_SUBCASE( case6, condition_f, shape_v, axis );
    SHAPE_COMPRESS_SUBCASE( case6, condition_f, shape_h, axis );
    SHAPE_COMPRESS_SUBCASE( case6, condition_f, shape_ct, axis );
    SHAPE_COMPRESS_SUBCASE( case6, condition_f, shape_cl, axis );

    SHAPE_COMPRESS_SUBCASE( case6, condition_h, shape_a, axis );
    SHAPE_COMPRESS_SUBCASE( case6, condition_h, shape_v, axis );
    SHAPE_COMPRESS_SUBCASE( case6, condition_h, shape_f, axis );
    SHAPE_COMPRESS_SUBCASE( case6, condition_h, shape_ct, axis );
    SHAPE_COMPRESS_SUBCASE( case6, condition_h, shape_cl, axis );

    SHAPE_COMPRESS_SUBCASE( case6, condition_ct, shape_a, axis );
    SHAPE_COMPRESS_SUBCASE( case6, condition_ct, shape_v, axis );
    SHAPE_COMPRESS_SUBCASE( case6, condition_ct, shape_f, axis );
    SHAPE_COMPRESS_SUBCASE( case6, condition_ct, shape_h, axis );
    SHAPE_COMPRESS_SUBCASE( case6, condition_ct, shape_cl, axis );

    SHAPE_COMPRESS_SUBCASE( case6, condition_cl, shape_a, axis );
    SHAPE_COMPRESS_SUBCASE( case6, condition_cl, shape_v, axis );
    SHAPE_COMPRESS_SUBCASE( case6, condition_cl, shape_f, axis );
    SHAPE_COMPRESS_SUBCASE( case6, condition_cl, shape_h, axis );
    SHAPE_COMPRESS_SUBCASE( case6, condition_cl, shape_ct, axis );
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
    NMTOOLS_TESTING_USE_CASE(index, compress, case_name); \
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