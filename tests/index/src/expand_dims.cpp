#include "nmtools/array/index/expand_dims.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/testing/array_cast.hpp"

#include "nmtools/stl.hpp"

namespace nm = nmtools;
namespace na = nm::array;

using namespace nm::literals;

NMTOOLS_TESTING_DECLARE_CASE(index, shape_expand_dims)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int shape[3] = {1,2,3};
        inline int axes[1]  = {0};
        inline auto shape_ct = nmtools_tuple{1_ct,2_ct,3_ct};
        inline auto shape_cl = nmtools_tuple{"1:[1]"_ct,"2:[2]"_ct,"3:[3]"_ct};
        inline auto axes_ct  = nmtools_tuple{0_ct};
        inline auto axes_cl  = nmtools_tuple{"0:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(axes);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int expected[4] = {1,1,2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int shape[3] = {1,2,3};
        inline int axes[1]  = {1};
        inline auto shape_ct = nmtools_tuple{1_ct,2_ct,3_ct};
        inline auto shape_cl = nmtools_tuple{"1:[1]"_ct,"2:[2]"_ct,"3:[3]"_ct};
        inline auto axes_ct  = nmtools_tuple{1_ct};
        inline auto axes_cl  = nmtools_tuple{"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(axes);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int expected[4] = {1,1,2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int shape[3] = {1,2,3};
        inline int axes[1]  = {2};
        inline auto shape_ct = nmtools_tuple{1_ct,2_ct,3_ct};
        inline auto shape_cl = nmtools_tuple{"1:[1]"_ct,"2:[2]"_ct,"3:[3]"_ct};
        inline auto axes_ct  = nmtools_tuple{2_ct};
        inline auto axes_cl  = nmtools_tuple{"2:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(axes);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int expected[4] = {1,2,1,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int shape[3] = {1,2,3};
        inline int axes[1]  = {3};
        inline auto shape_ct = nmtools_tuple{1_ct,2_ct,3_ct};
        inline auto shape_cl = nmtools_tuple{"1:[1]"_ct,"2:[2]"_ct,"3:[3]"_ct};
        inline auto axes_ct  = nmtools_tuple{3_ct};
        inline auto axes_cl  = nmtools_tuple{"3:[3]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(axes);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int expected[4] = {1,2,3,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int shape[3] = {1,2,3};
        inline int axes[2]  = {0,1};
        inline auto shape_ct = nmtools_tuple{1_ct,2_ct,3_ct};
        inline auto shape_cl = nmtools_tuple{"1:[1]"_ct,"2:[2]"_ct,"3:[3]"_ct};
        inline auto axes_ct  = nmtools_tuple{0_ct,1_ct};
        inline auto axes_cl  = nmtools_tuple{"0:[1]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(axes);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int expected[5] = {1,1,1,2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int shape[3] = {1,2,3};
        inline int axes[2]  = {0,2};
        inline auto shape_ct = nmtools_tuple{1_ct,2_ct,3_ct};
        inline auto shape_cl = nmtools_tuple{"1:[1]"_ct,"2:[2]"_ct,"3:[3]"_ct};
        inline auto axes_ct  = nmtools_tuple{0_ct,2_ct};
        inline auto axes_cl  = nmtools_tuple{"0:[1]"_ct,"2:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(axes);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int expected[5] = {1,1,1,2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int shape[3] = {1,2,3};
        inline int axes[2]  = {1,2};
        inline auto shape_ct = nmtools_tuple{1_ct,2_ct,3_ct};
        inline auto shape_cl = nmtools_tuple{"1:[1]"_ct,"2:[2]"_ct,"3:[3]"_ct};
        inline auto axes_ct  = nmtools_tuple{1_ct,2_ct};
        inline auto axes_cl  = nmtools_tuple{"1:[1]"_ct,"2:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(axes);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int expected[5] = {1,1,1,2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline int shape[3] = {1,2,3};
        inline int axes[2]  = {2,3};
        inline auto shape_ct = nmtools_tuple{1_ct,2_ct,3_ct};
        inline auto shape_cl = nmtools_tuple{"1:[1]"_ct,"2:[2]"_ct,"3:[3]"_ct};
        inline auto axes_ct  = nmtools_tuple{2_ct,3_ct};
        inline auto axes_cl  = nmtools_tuple{"2:[2]"_ct,"3:[3]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(axes);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline int expected[5] = {1,2,1,1,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        inline int shape[3] = {1,2,3};
        inline int axes[3]  = {2,3,0};
        inline auto shape_ct = nmtools_tuple{1_ct,2_ct,3_ct};
        inline auto shape_cl = nmtools_tuple{"1:[1]"_ct,"2:[2]"_ct,"3:[3]"_ct};
        inline auto axes_ct  = nmtools_tuple{2_ct,3_ct,0_ct};
        inline auto axes_cl  = nmtools_tuple{"2:[2]"_ct,"3:[3]"_ct,"0:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(axes);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline int expected[6] = {1,1,1,1,2,3};
    }
}

#define RUN_shape_expand_dims_impl(...) \
nm::index::shape_expand_dims(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs shape_expand_dims fn to callable lambda
#define RUN_shape_expand_dims(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("shape_expand_dims-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_shape_expand_dims_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_shape_expand_dims(case_name, ...) \
RUN_shape_expand_dims_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define SHAPE_EXPAND_DIMS_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index, shape_expand_dims, case_name); \
    using namespace args; \
    auto result = RUN_shape_expand_dims(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::expected ); \
}

TEST_CASE("shape_expand_dims(case1)" * doctest::test_suite("index::shape_expand_dims"))
{
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape, axes );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_a, axes_a );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_f, axes_f );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_h, axes_h );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_v, axes_v );

    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_ct, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_cl, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_cl, axes_cl );

    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_a, axes_a );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_a, axes_f );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_a, axes_h );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_a, axes_v );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_a, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_a, axes_cl );

    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_f, axes_a );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_f, axes_f );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_f, axes_h );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_f, axes_v );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_f, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_f, axes_cl );

    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_h, axes_a );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_h, axes_f );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_h, axes_h );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_h, axes_v );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_h, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_h, axes_cl );

    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_v, axes_a );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_v, axes_f );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_v, axes_h );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_v, axes_v );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_v, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_v, axes_cl );

    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_ct, axes_a );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_ct, axes_f );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_ct, axes_h );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_ct, axes_v );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_ct, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_ct, axes_cl );

    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_cl, axes_a );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_cl, axes_f );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_cl, axes_h );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_cl, axes_v );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_cl, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case1, shape_cl, axes_cl );
}

TEST_CASE("shape_expand_dims(case2)" * doctest::test_suite("index::shape_expand_dims"))
{
    SHAPE_EXPAND_DIMS_SUBCASE( case2, shape, axes );
    SHAPE_EXPAND_DIMS_SUBCASE( case2, shape_a, axes_a );
    SHAPE_EXPAND_DIMS_SUBCASE( case2, shape_f, axes_f );
    SHAPE_EXPAND_DIMS_SUBCASE( case2, shape_h, axes_h );
    SHAPE_EXPAND_DIMS_SUBCASE( case2, shape_v, axes_v );

    SHAPE_EXPAND_DIMS_SUBCASE( case2, shape_ct, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case2, shape_cl, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case2, shape_cl, axes_cl );
}

TEST_CASE("shape_expand_dims(case3)" * doctest::test_suite("index::shape_expand_dims"))
{
    SHAPE_EXPAND_DIMS_SUBCASE( case3, shape, axes );
    SHAPE_EXPAND_DIMS_SUBCASE( case3, shape_a, axes_a );
    SHAPE_EXPAND_DIMS_SUBCASE( case3, shape_f, axes_f );
    SHAPE_EXPAND_DIMS_SUBCASE( case3, shape_h, axes_h );
    SHAPE_EXPAND_DIMS_SUBCASE( case3, shape_v, axes_v );

    SHAPE_EXPAND_DIMS_SUBCASE( case3, shape_ct, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case3, shape_cl, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case3, shape_cl, axes_cl );
}

TEST_CASE("shape_expand_dims(case4)" * doctest::test_suite("index::shape_expand_dims"))
{
    SHAPE_EXPAND_DIMS_SUBCASE( case4, shape, axes );
    SHAPE_EXPAND_DIMS_SUBCASE( case4, shape_a, axes_a );
    SHAPE_EXPAND_DIMS_SUBCASE( case4, shape_f, axes_f );
    SHAPE_EXPAND_DIMS_SUBCASE( case4, shape_h, axes_h );
    SHAPE_EXPAND_DIMS_SUBCASE( case4, shape_v, axes_v );

    SHAPE_EXPAND_DIMS_SUBCASE( case4, shape_ct, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case4, shape_cl, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case4, shape_cl, axes_cl );
}

TEST_CASE("shape_expand_dims(case5)" * doctest::test_suite("index::shape_expand_dims"))
{
    SHAPE_EXPAND_DIMS_SUBCASE( case5, shape, axes );
    SHAPE_EXPAND_DIMS_SUBCASE( case5, shape_a, axes_a );
    SHAPE_EXPAND_DIMS_SUBCASE( case5, shape_f, axes_f );
    SHAPE_EXPAND_DIMS_SUBCASE( case5, shape_h, axes_h );
    SHAPE_EXPAND_DIMS_SUBCASE( case5, shape_v, axes_v );

    SHAPE_EXPAND_DIMS_SUBCASE( case5, shape_ct, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case5, shape_cl, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case5, shape_cl, axes_cl );
}

TEST_CASE("shape_expand_dims(case6)" * doctest::test_suite("index::shape_expand_dims"))
{
    SHAPE_EXPAND_DIMS_SUBCASE( case6, shape, axes );
    SHAPE_EXPAND_DIMS_SUBCASE( case6, shape_a, axes_a );
    SHAPE_EXPAND_DIMS_SUBCASE( case6, shape_f, axes_f );
    SHAPE_EXPAND_DIMS_SUBCASE( case6, shape_h, axes_h );
    SHAPE_EXPAND_DIMS_SUBCASE( case6, shape_v, axes_v );

    SHAPE_EXPAND_DIMS_SUBCASE( case6, shape_ct, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case6, shape_cl, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case6, shape_cl, axes_cl );
}

TEST_CASE("shape_expand_dims(case7)" * doctest::test_suite("index::shape_expand_dims"))
{
    SHAPE_EXPAND_DIMS_SUBCASE( case7, shape, axes );
    SHAPE_EXPAND_DIMS_SUBCASE( case7, shape_a, axes_a );
    SHAPE_EXPAND_DIMS_SUBCASE( case7, shape_f, axes_f );
    SHAPE_EXPAND_DIMS_SUBCASE( case7, shape_h, axes_h );
    SHAPE_EXPAND_DIMS_SUBCASE( case7, shape_v, axes_v );

    SHAPE_EXPAND_DIMS_SUBCASE( case7, shape_ct, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case7, shape_cl, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case7, shape_cl, axes_cl );
}

TEST_CASE("shape_expand_dims(case8)" * doctest::test_suite("index::shape_expand_dims"))
{
    SHAPE_EXPAND_DIMS_SUBCASE( case8, shape, axes );
    SHAPE_EXPAND_DIMS_SUBCASE( case8, shape_a, axes_a );
    SHAPE_EXPAND_DIMS_SUBCASE( case8, shape_f, axes_f );
    SHAPE_EXPAND_DIMS_SUBCASE( case8, shape_h, axes_h );
    SHAPE_EXPAND_DIMS_SUBCASE( case8, shape_v, axes_v );

    SHAPE_EXPAND_DIMS_SUBCASE( case8, shape_ct, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case8, shape_cl, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case8, shape_cl, axes_cl );
}

TEST_CASE("shape_expand_dims(case9)" * doctest::test_suite("index::shape_expand_dims"))
{
    SHAPE_EXPAND_DIMS_SUBCASE( case9, shape, axes );
    SHAPE_EXPAND_DIMS_SUBCASE( case9, shape_a, axes_a );
    SHAPE_EXPAND_DIMS_SUBCASE( case9, shape_f, axes_f );
    SHAPE_EXPAND_DIMS_SUBCASE( case9, shape_h, axes_h );
    SHAPE_EXPAND_DIMS_SUBCASE( case9, shape_v, axes_v );

    SHAPE_EXPAND_DIMS_SUBCASE( case9, shape_ct, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case9, shape_cl, axes_ct );
    SHAPE_EXPAND_DIMS_SUBCASE( case9, shape_cl, axes_cl );
}