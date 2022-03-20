#include "nmtools/array/index/reshape.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
using namespace nm::literals;

NMTOOLS_TESTING_DECLARE_CASE(shape_reshape)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int shape[1]     = {12};
        inline int newshape[2]  = {12,1};
        inline auto shape_ct    = nmtools_tuple{12_ct};
        inline auto newshape_ct = nmtools_tuple{12_ct,1_ct};
        NMTOOLS_CAST_ARRAYS(shape)
        NMTOOLS_CAST_ARRAYS(newshape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[2] = {12,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int shape[1]    = {12};
        inline int newshape[2] = {3,4};
        inline auto shape_ct    = nmtools_tuple{12_ct};
        inline auto newshape_ct = nmtools_tuple{3_ct,4_ct};
        NMTOOLS_CAST_ARRAYS(shape)
        NMTOOLS_CAST_ARRAYS(newshape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[2] = {3,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int shape[1]    = {12};
        inline int newshape[4] = {1,2,3,2};
        NMTOOLS_CAST_ARRAYS(shape)
        NMTOOLS_CAST_ARRAYS(newshape)
        inline auto shape_ct    = nmtools_tuple{12_ct};
        inline auto newshape_ct = nmtools_tuple{1_ct,2_ct,3_ct,2_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[4] = {1,2,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int shape[2] = {12,1};
        inline int newshape[4] = {2,1,3,2};
        NMTOOLS_CAST_ARRAYS(shape)
        NMTOOLS_CAST_ARRAYS(newshape)
        inline auto shape_ct    = nmtools_tuple{12_ct,1_ct};
        inline auto newshape_ct = nmtools_tuple{2_ct,1_ct,3_ct,2_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[4] = {2,1,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int shape[1]    = {12};
        inline int newshape[2] = {12,-1};
        NMTOOLS_CAST_ARRAYS(shape)
        NMTOOLS_CAST_ARRAYS(newshape)
        inline auto shape_ct    = nmtools_tuple{12_ct};
        inline auto newshape_ct = nmtools_tuple{12_ct,"-1"_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int result[2] = {12,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int shape[1]    = {12};
        inline int newshape[2] = {3,-1};
        NMTOOLS_CAST_ARRAYS(shape)
        NMTOOLS_CAST_ARRAYS(newshape)
        inline auto shape_ct    = nmtools_tuple{12_ct};
        inline auto newshape_ct = nmtools_tuple{3_ct,"-1"_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int result[2] = {3,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int shape[1]    = {12};
        inline int newshape[4] = {1,2,-1,2};
        NMTOOLS_CAST_ARRAYS(shape)
        NMTOOLS_CAST_ARRAYS(newshape)
        inline auto shape_ct    = nmtools_tuple{12_ct};
        inline auto newshape_ct = nmtools_tuple{1_ct,2_ct,"-1"_ct,2_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int result[4] = {1,2,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline int shape[2] = {12,1};
        inline int newshape[4] = {-1,1,3,2};
        NMTOOLS_CAST_ARRAYS(shape)
        NMTOOLS_CAST_ARRAYS(newshape)
        inline auto shape_ct    = nmtools_tuple{12_ct,1_ct};
        inline auto newshape_ct = nmtools_tuple{"-1"_ct,1_ct,3_ct,2_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline int result[4] = {2,1,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        inline int shape[1]    = {12};
        inline int newshape[2] = {-1,-1};
        NMTOOLS_CAST_ARRAYS(shape)
        NMTOOLS_CAST_ARRAYS(newshape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline auto result = meta::Nothing;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        inline int shape[1]    = {12};
        inline int newshape[2] = {7,-1};
        NMTOOLS_CAST_ARRAYS(shape)
        NMTOOLS_CAST_ARRAYS(newshape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline auto result = meta::Nothing;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        inline int shape[1]    = {12};
        inline int newshape[4] = {1,9,-1,2};
        NMTOOLS_CAST_ARRAYS(shape)
        NMTOOLS_CAST_ARRAYS(newshape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        inline auto result = meta::Nothing;
    }
}

#define RUN_impl(...) \
nm::index::shape_reshape(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs shape_reshape fn to callable lambda
#define RUN_shape_reshape(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("shape_reshape-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_shape_reshape(case_name, ...) \
RUN_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define SHAPE_RESHAPE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(shape_reshape, case_name); \
    using namespace args; \
    auto result = RUN_shape_reshape(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("shape_reshape(case1)" * doctest::test_suite("index::shape_reshape"))
{
    SHAPE_RESHAPE_SUBCASE( case1, shape, newshape );
    SHAPE_RESHAPE_SUBCASE( case1, shape_a, newshape_a );
    SHAPE_RESHAPE_SUBCASE( case1, shape_f, newshape_f );
    SHAPE_RESHAPE_SUBCASE( case1, shape_v, newshape_v );
    SHAPE_RESHAPE_SUBCASE( case1, shape_h, newshape_h );

    SHAPE_RESHAPE_SUBCASE( case1, shape, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case1, shape_a, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case1, shape_f, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case1, shape_v, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case1, shape_h, newshape_ct );
}

TEST_CASE("shape_reshape(case2)" * doctest::test_suite("index::shape_reshape"))
{
    SHAPE_RESHAPE_SUBCASE( case2, shape, newshape );
    SHAPE_RESHAPE_SUBCASE( case2, shape_a, newshape_a );
    SHAPE_RESHAPE_SUBCASE( case2, shape_f, newshape_f );
    SHAPE_RESHAPE_SUBCASE( case2, shape_v, newshape_v );
    SHAPE_RESHAPE_SUBCASE( case2, shape_h, newshape_h );

    SHAPE_RESHAPE_SUBCASE( case2, shape, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case2, shape_a, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case2, shape_f, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case2, shape_v, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case2, shape_h, newshape_ct );
}

TEST_CASE("shape_reshape(case3)" * doctest::test_suite("index::shape_reshape"))
{
    SHAPE_RESHAPE_SUBCASE( case3, shape, newshape );
    SHAPE_RESHAPE_SUBCASE( case3, shape_a, newshape_a );
    SHAPE_RESHAPE_SUBCASE( case3, shape_f, newshape_f );
    SHAPE_RESHAPE_SUBCASE( case3, shape_v, newshape_v );
    SHAPE_RESHAPE_SUBCASE( case3, shape_h, newshape_h );

    SHAPE_RESHAPE_SUBCASE( case3, shape, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case3, shape_a, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case3, shape_f, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case3, shape_v, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case3, shape_h, newshape_ct );
}

TEST_CASE("shape_reshape(case4)" * doctest::test_suite("index::shape_reshape"))
{
    SHAPE_RESHAPE_SUBCASE( case4, shape, newshape );
    SHAPE_RESHAPE_SUBCASE( case4, shape_a, newshape_a );
    SHAPE_RESHAPE_SUBCASE( case4, shape_f, newshape_f );
    SHAPE_RESHAPE_SUBCASE( case4, shape_v, newshape_v );
    SHAPE_RESHAPE_SUBCASE( case4, shape_h, newshape_h );

    SHAPE_RESHAPE_SUBCASE( case4, shape, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case4, shape_a, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case4, shape_f, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case4, shape_v, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case4, shape_h, newshape_ct );
}

TEST_CASE("shape_reshape(case5)" * doctest::test_suite("index::shape_reshape"))
{
    SHAPE_RESHAPE_SUBCASE( case5, shape, newshape );
    SHAPE_RESHAPE_SUBCASE( case5, shape_a, newshape_a );
    SHAPE_RESHAPE_SUBCASE( case5, shape_f, newshape_f );
    SHAPE_RESHAPE_SUBCASE( case5, shape_v, newshape_v );
    SHAPE_RESHAPE_SUBCASE( case5, shape_h, newshape_h );

    SHAPE_RESHAPE_SUBCASE( case5, shape, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case5, shape_a, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case5, shape_f, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case5, shape_v, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case5, shape_h, newshape_ct );
}

TEST_CASE("shape_reshape(case6)" * doctest::test_suite("index::shape_reshape"))
{
    SHAPE_RESHAPE_SUBCASE( case6, shape, newshape );
    SHAPE_RESHAPE_SUBCASE( case6, shape_a, newshape_a );
    SHAPE_RESHAPE_SUBCASE( case6, shape_f, newshape_f );
    SHAPE_RESHAPE_SUBCASE( case6, shape_v, newshape_v );
    SHAPE_RESHAPE_SUBCASE( case6, shape_h, newshape_h );

    SHAPE_RESHAPE_SUBCASE( case6, shape, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case6, shape_a, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case6, shape_f, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case6, shape_v, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case6, shape_h, newshape_ct );
}

TEST_CASE("shape_reshape(case7)" * doctest::test_suite("index::shape_reshape"))
{
    SHAPE_RESHAPE_SUBCASE( case7, shape, newshape );
    SHAPE_RESHAPE_SUBCASE( case7, shape_a, newshape_a );
    SHAPE_RESHAPE_SUBCASE( case7, shape_f, newshape_f );
    SHAPE_RESHAPE_SUBCASE( case7, shape_v, newshape_v );
    SHAPE_RESHAPE_SUBCASE( case7, shape_h, newshape_h );

    SHAPE_RESHAPE_SUBCASE( case7, shape, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case7, shape_a, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case7, shape_f, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case7, shape_v, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case7, shape_h, newshape_ct );
}

TEST_CASE("shape_reshape(case8)" * doctest::test_suite("index::shape_reshape"))
{
    SHAPE_RESHAPE_SUBCASE( case8, shape, newshape );
    SHAPE_RESHAPE_SUBCASE( case8, shape_a, newshape_a );
    SHAPE_RESHAPE_SUBCASE( case8, shape_f, newshape_f );
    SHAPE_RESHAPE_SUBCASE( case8, shape_v, newshape_v );
    SHAPE_RESHAPE_SUBCASE( case8, shape_h, newshape_h );

    SHAPE_RESHAPE_SUBCASE( case8, shape, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case8, shape_a, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case8, shape_f, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case8, shape_v, newshape_ct );
    SHAPE_RESHAPE_SUBCASE( case8, shape_h, newshape_ct );
}

TEST_CASE("shape_reshape(case9)" * doctest::test_suite("index::shape_reshape"))
{
    SHAPE_RESHAPE_SUBCASE( case9, shape, newshape );
    SHAPE_RESHAPE_SUBCASE( case9, shape_a, newshape_a );
    SHAPE_RESHAPE_SUBCASE( case9, shape_f, newshape_f );
    SHAPE_RESHAPE_SUBCASE( case9, shape_v, newshape_v );
    SHAPE_RESHAPE_SUBCASE( case9, shape_h, newshape_h );
}

TEST_CASE("shape_reshape(case10)" * doctest::test_suite("index::shape_reshape"))
{
    SHAPE_RESHAPE_SUBCASE( case10, shape, newshape );
    SHAPE_RESHAPE_SUBCASE( case10, shape_a, newshape_a );
    SHAPE_RESHAPE_SUBCASE( case10, shape_f, newshape_f );
    SHAPE_RESHAPE_SUBCASE( case10, shape_v, newshape_v );
    SHAPE_RESHAPE_SUBCASE( case10, shape_h, newshape_h );
}

TEST_CASE("shape_reshape(case11)" * doctest::test_suite("index::shape_reshape"))
{
    SHAPE_RESHAPE_SUBCASE( case11, shape, newshape );
    SHAPE_RESHAPE_SUBCASE( case11, shape_a, newshape_a );
    SHAPE_RESHAPE_SUBCASE( case11, shape_f, newshape_f );
    SHAPE_RESHAPE_SUBCASE( case11, shape_v, newshape_v );
    SHAPE_RESHAPE_SUBCASE( case11, shape_h, newshape_h );
}