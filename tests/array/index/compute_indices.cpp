#include "nmtools/array/index/compute_indices.hpp"
#include "nmtools/array/index/as_tuple.hpp"
#include "nmtools/utils/isequal.hpp"
#include "nmtools/constants.hpp"
#include "nmtools/testing/doctest.hpp"
#include <array>
#include <vector>

namespace nm = nmtools;
using nmtools::utils::isequal;
using namespace nmtools::literals;

NMTOOLS_TESTING_DECLARE_CASE(compute_indices)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1_2d)
    {
        int shape[2] = {3,2};
        int offset   = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1_2d)
    {
        auto indices = nmtools_tuple{0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2_2d)
    {
        int shape[2] = {3,2};
        int offset   = 1;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2_2d)
    {
        auto indices = nmtools_tuple{0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3_2d)
    {
        int shape[2] = {3,2};
        int offset   = 2;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3_2d)
    {
        auto indices = nmtools_tuple{1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4_2d)
    {
        int shape[2] = {3,2};
        int offset   = 3;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4_2d)
    {
        auto indices = nmtools_tuple{1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5_2d)
    {
        int shape[2] = {3,2};
        int offset   = 4;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5_2d)
    {
        auto indices = nmtools_tuple{2,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6_2d)
    {
        int shape[2] = {3,2};
        int offset   = 5;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6_2d)
    {
        auto indices = nmtools_tuple{2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1_3d)
    {
        int shape[3] = {3,2,3};
        int offset   = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1_3d)
    {
        auto indices = nmtools_tuple{0,0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2_3d)
    {
        int shape[3] = {3,2,3};
        int offset   = 1;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2_3d)
    {
        auto indices = nmtools_tuple{0,0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3_3d)
    {
        int shape[3] = {3,2,3};
        int offset   = 2;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3_3d)
    {
        auto indices = nmtools_tuple{0,0,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4_3d)
    {
        int shape[3] = {3,2,3};
        int offset   = 3;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4_3d)
    {
        auto indices = nmtools_tuple{0,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5_3d)
    {
        int shape[3] = {3,2,3};
        int offset   = 4;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5_3d)
    {
        auto indices = nmtools_tuple{0,1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6_3d)
    {
        int shape[3] = {3,2,3};
        int offset   = 5;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6_3d)
    {
        auto indices = nmtools_tuple{0,1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7_3d)
    {
        int shape[3] = {3,2,3};
        int offset   = 6;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7_3d)
    {
        auto indices = nmtools_tuple{1,0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8_3d)
    {
        int shape[3] = {3,2,3};
        int offset   = 7;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8_3d)
    {
        auto indices = nmtools_tuple{1,0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9_3d)
    {
        int shape[3] = {3,2,3};
        int offset   = 8;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9_3d)
    {
        auto indices = nmtools_tuple{1,0,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10_3d)
    {
        int shape[3] = {3,2,3};
        int offset   = 9;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10_3d)
    {
        auto indices = nmtools_tuple{1,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11_3d)
    {
        int shape[3] = {3,2,3};
        int offset   = 10;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11_3d)
    {
        auto indices = nmtools_tuple{1,1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12_3d)
    {
        int shape[3] = {3,2,3};
        int offset   = 11;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12_3d)
    {
        auto indices = nmtools_tuple{1,1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case13_3d)
    {
        int shape[3] = {3,2,3};
        int offset   = 12;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case13_3d)
    {
        auto indices = nmtools_tuple{2,0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case14_3d)
    {
        int shape[3] = {3,2,3};
        int offset   = 13;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case14_3d)
    {
        auto indices = nmtools_tuple{2,0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case15_3d)
    {
        int shape[3] = {3,2,3};
        int offset   = 14;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case15_3d)
    {
        auto indices = nmtools_tuple{2,0,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case16_3d)
    {
        int shape[3] = {3,2,3};
        int offset   = 15;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case16_3d)
    {
        auto indices = nmtools_tuple{2,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case17_3d)
    {
        int shape[3] = {3,2,3};
        int offset   = 16;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case17_3d)
    {
        auto indices = nmtools_tuple{2,1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case18_3d)
    {
        int shape[3] = {3,2,3};
        int offset   = 17;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case18_3d)
    {
        auto indices = nmtools_tuple{2,1,2};
    }
}

#define RUN_impl(...) \
nm::index::compute_indices(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs compute_indices fn to callable lambda
#define RUN_compute_indices(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("compute_indices-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_compute_indices(case_name, ...) \
RUN_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define COMPUTE_INDICES_SUBCASE(case_name, offset, shape) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(compute_indices, case_name); \
    auto indices = RUN_compute_indices(case_name, args::offset, args::shape); \
    NMTOOLS_ASSERT_EQUAL( indices, expect::indices ); \
}

TEST_CASE("compute_indices(case2d)" * doctest::test_suite("index::compute_indices"))
{
    COMPUTE_INDICES_SUBCASE(case1_2d, offset, shape_a);
    COMPUTE_INDICES_SUBCASE(case1_2d, offset, shape_v);

    COMPUTE_INDICES_SUBCASE(case2_2d, offset, shape_a);
    COMPUTE_INDICES_SUBCASE(case2_2d, offset, shape_v);

    COMPUTE_INDICES_SUBCASE(case3_2d, offset, shape_a);
    COMPUTE_INDICES_SUBCASE(case3_2d, offset, shape_v);

    COMPUTE_INDICES_SUBCASE(case4_2d, offset, shape_a);
    COMPUTE_INDICES_SUBCASE(case4_2d, offset, shape_v);

    COMPUTE_INDICES_SUBCASE(case5_2d, offset, shape_a);
    COMPUTE_INDICES_SUBCASE(case5_2d, offset, shape_v);

    COMPUTE_INDICES_SUBCASE(case6_2d, offset, shape_a);
    COMPUTE_INDICES_SUBCASE(case6_2d, offset, shape_v);
}

TEST_CASE("compute_indices(case3d)" * doctest::test_suite("index::compute_indices"))
{
    COMPUTE_INDICES_SUBCASE(case1_3d, offset, shape_a);
    COMPUTE_INDICES_SUBCASE(case1_3d, offset, shape_v);

    COMPUTE_INDICES_SUBCASE(case2_3d, offset, shape_a);
    COMPUTE_INDICES_SUBCASE(case2_3d, offset, shape_v);

    COMPUTE_INDICES_SUBCASE(case3_3d, offset, shape_a);
    COMPUTE_INDICES_SUBCASE(case3_3d, offset, shape_v);

    COMPUTE_INDICES_SUBCASE(case4_3d, offset, shape_a);
    COMPUTE_INDICES_SUBCASE(case4_3d, offset, shape_v);

    COMPUTE_INDICES_SUBCASE(case5_3d, offset, shape_a);
    COMPUTE_INDICES_SUBCASE(case5_3d, offset, shape_v);

    COMPUTE_INDICES_SUBCASE(case6_3d, offset, shape_a);
    COMPUTE_INDICES_SUBCASE(case6_3d, offset, shape_v);

    COMPUTE_INDICES_SUBCASE(case7_3d, offset, shape_a);
    COMPUTE_INDICES_SUBCASE(case7_3d, offset, shape_v);

    COMPUTE_INDICES_SUBCASE(case8_3d, offset, shape_a);
    COMPUTE_INDICES_SUBCASE(case8_3d, offset, shape_v);

    COMPUTE_INDICES_SUBCASE(case9_3d, offset, shape_a);
    COMPUTE_INDICES_SUBCASE(case9_3d, offset, shape_v);

    COMPUTE_INDICES_SUBCASE(case10_3d, offset, shape_a);
    COMPUTE_INDICES_SUBCASE(case10_3d, offset, shape_v);

    COMPUTE_INDICES_SUBCASE(case11_3d, offset, shape_a);
    COMPUTE_INDICES_SUBCASE(case11_3d, offset, shape_v);

    COMPUTE_INDICES_SUBCASE(case12_3d, offset, shape_a);
    COMPUTE_INDICES_SUBCASE(case12_3d, offset, shape_v);

    COMPUTE_INDICES_SUBCASE(case13_3d, offset, shape_a);
    COMPUTE_INDICES_SUBCASE(case13_3d, offset, shape_v);

    COMPUTE_INDICES_SUBCASE(case14_3d, offset, shape_a);
    COMPUTE_INDICES_SUBCASE(case14_3d, offset, shape_v);

    COMPUTE_INDICES_SUBCASE(case15_3d, offset, shape_a);
    COMPUTE_INDICES_SUBCASE(case15_3d, offset, shape_v);

    COMPUTE_INDICES_SUBCASE(case16_3d, offset, shape_a);
    COMPUTE_INDICES_SUBCASE(case16_3d, offset, shape_v);

    COMPUTE_INDICES_SUBCASE(case17_3d, offset, shape_a);
    COMPUTE_INDICES_SUBCASE(case17_3d, offset, shape_v);

    COMPUTE_INDICES_SUBCASE(case18_3d, offset, shape_a);
    COMPUTE_INDICES_SUBCASE(case18_3d, offset, shape_v);
}