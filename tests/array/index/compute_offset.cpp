#include "nmtools/array/index/compute_offset.hpp"
#include "nmtools/utils/isequal.hpp"
#include "nmtools/constants.hpp"
#include "nmtools/testing/doctest.hpp"
#include <array>
#include <vector>

using nmtools::utils::isequal;
using namespace nmtools::literals;

// TODO: refactor testing data & test cases impl

NMTOOLS_TESTING_DECLARE_CASE(index, compute_offset)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1a)
    {
        // note that this is strides not shape
        inline int strides[2] = {2,1};
        inline auto strides_ct = nmtools_tuple{2_ct,1_ct};
        inline auto strides_cl = nmtools_tuple{"2:[2]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(strides);

        inline int indices[2] = {0,0};
        inline auto indices_ct = nmtools_tuple{0_ct,0_ct};
        inline auto indices_cl = nmtools_tuple{"0:[1]"_ct,"0:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1a)
    {
        inline int result = 0;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1b)
    {
        inline int strides[2] = {2,1};
        inline auto strides_ct = nmtools_tuple{2_ct,1_ct};
        inline auto strides_cl = nmtools_tuple{"2:[2]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(strides);

        inline int indices[2] = {0,1};
        inline auto indices_ct = nmtools_tuple{0_ct,1_ct};
        inline auto indices_cl = nmtools_tuple{"0:[1]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1b)
    {
        inline int result = 1;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1c)
    {
        inline int strides[2] = {2,1};
        inline auto strides_ct = nmtools_tuple{2_ct,1_ct};
        inline auto strides_cl = nmtools_tuple{"2:[2]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(strides);

        inline int indices[2] = {1,0};
        inline auto indices_ct = nmtools_tuple{1_ct,0_ct};
        inline auto indices_cl = nmtools_tuple{"1:[1]"_ct,"0:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1c)
    {
        inline int result = 2;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1d)
    {
        inline int strides[2] = {2,1};
        inline auto strides_ct = nmtools_tuple{2_ct,1_ct};
        inline auto strides_cl = nmtools_tuple{"2:[2]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(strides);

        inline int indices[2] = {1,1};
        inline auto indices_ct = nmtools_tuple{1_ct,1_ct};
        inline auto indices_cl = nmtools_tuple{"1:[1]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1d)
    {
        inline int result = 3;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1e)
    {
        inline int strides[2] = {2,1};
        inline auto strides_ct = nmtools_tuple{2_ct,1_ct};
        inline auto strides_cl = nmtools_tuple{"2:[2]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(strides);

        inline int indices[2] = {2,0};
        inline auto indices_ct = nmtools_tuple{2_ct,0_ct};
        inline auto indices_cl = nmtools_tuple{"2:[2]"_ct,"0:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1e)
    {
        inline int result = 4;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1f)
    {
        inline int strides[2] = {2,1};
        inline auto strides_ct = nmtools_tuple{2_ct,1_ct};
        inline auto strides_cl = nmtools_tuple{"2:[2]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(strides);

        inline int indices[2] = {2,1};
        inline auto indices_ct = nmtools_tuple{2_ct,1_ct};
        inline auto indices_cl = nmtools_tuple{"2:[2]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1f)
    {
        inline int result = 5;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2a)
    {
        inline int strides[3] = {6,3,1};
        inline auto strides_ct = nmtools_tuple{6_ct,3_ct,1_ct};
        inline auto strides_cl = nmtools_tuple{"6:[6]"_ct,"3:[3]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(strides);

        inline int indices[3] = {0,0,0};
        inline auto indices_ct = nmtools_tuple{0_ct,0_ct,0_ct};
        inline auto indices_cl = nmtools_tuple{"0:[1]"_ct,"0:[1]"_ct,"0:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2a)
    {
        inline int result = 0;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2b)
    {
        inline int strides[3] = {6,3,1};
        inline auto strides_ct = nmtools_tuple{6_ct,3_ct,1_ct};
        inline auto strides_cl = nmtools_tuple{"6:[6]"_ct,"3:[3]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(strides);

        inline int indices[3] = {0,0,1};
        inline auto indices_ct = nmtools_tuple{0_ct,0_ct,1_ct};
        inline auto indices_cl = nmtools_tuple{"0:[1]"_ct,"0:[1]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2b)
    {
        inline int result = 1;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2c)
    {
        inline int strides[3] = {6,3,1};
        inline auto strides_ct = nmtools_tuple{6_ct,3_ct,1_ct};
        inline auto strides_cl = nmtools_tuple{"6:[6]"_ct,"3:[3]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(strides);

        inline int indices[3] = {0,0,2};
        inline auto indices_ct = nmtools_tuple{0_ct,0_ct,2_ct};
        inline auto indices_cl = nmtools_tuple{"0:[1]"_ct,"0:[1]"_ct,"2:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2c)
    {
        inline int result = 2;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2d)
    {
        inline int strides[3] = {6,3,1};
        inline auto strides_ct = nmtools_tuple{6_ct,3_ct,1_ct};
        inline auto strides_cl = nmtools_tuple{"6:[6]"_ct,"3:[3]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(strides);

        inline int indices[3] = {0,1,0};
        inline auto indices_ct = nmtools_tuple{0_ct,1_ct,0_ct};
        inline auto indices_cl = nmtools_tuple{"0:[1]"_ct,"1:[1]"_ct,"0:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2d)
    {
        inline int result = 3;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2e)
    {
        inline int strides[3] = {6,3,1};
        inline auto strides_ct = nmtools_tuple{6_ct,3_ct,1_ct};
        inline auto strides_cl = nmtools_tuple{"6:[6]"_ct,"3:[3]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(strides);

        inline int indices[3] = {0,1,1};
        inline auto indices_ct = nmtools_tuple{0_ct,1_ct,1_ct};
        inline auto indices_cl = nmtools_tuple{"0:[1]"_ct,"1:[1]"_ct,"1:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2e)
    {
        inline int result = 4;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2f)
    {
        inline int strides[3] = {6,3,1};
        inline auto strides_ct = nmtools_tuple{6_ct,3_ct,1_ct};
        inline auto strides_cl = nmtools_tuple{"6:[6]"_ct,"3:[3]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(strides);

        inline int indices[3] = {0,1,2};
        inline auto indices_ct = nmtools_tuple{0_ct,1_ct,2_ct};
        inline auto indices_cl = nmtools_tuple{"0:[1]"_ct,"1:[1]"_ct,"2:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2f)
    {
        inline int result = 5;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2g)
    {
        inline int strides[3] = {6,3,1};
        inline auto strides_ct = nmtools_tuple{6_ct,3_ct,1_ct};
        inline auto strides_cl = nmtools_tuple{"6:[6]"_ct,"3:[3]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(strides);

        inline int indices[3] = {1,0,0};
        inline auto indices_ct = nmtools_tuple{1_ct,0_ct,0_ct};
        inline auto indices_cl = nmtools_tuple{"1:[1]"_ct,"0:[1]"_ct,"0:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2g)
    {
        inline int result = 6;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2h)
    {
        inline int strides[3] = {6,3,1};
        inline auto strides_ct = nmtools_tuple{6_ct,3_ct,1_ct};
        inline auto strides_cl = nmtools_tuple{"6:[6]"_ct,"3:[3]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(strides);

        inline int indices[3] = {1,0,1};
        inline auto indices_ct = nmtools_tuple{1_ct,0_ct,1_ct};
        inline auto indices_cl = nmtools_tuple{"1:[1]"_ct,"0:[1]"_ct,"1:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2h)
    {
        inline int result = 7;
    }
}

#define RUN_compute_offset_impl(...) \
nmtools::index::compute_offset(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nmtools::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs compute_offset fn to callable lambda
#define RUN_compute_indices(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("compute_offset-") + #case_name; \
    auto name  = nmtools::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_compute_offset_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_compute_indices(case_name, ...) \
RUN_compute_offset_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define COMPUTE_OFFSET_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(index, compute_offset, case_name); \
    using namespace args; \
    auto offset = RUN_compute_indices(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( offset, expect::result ); \
}

// doesn't work, only first are working :|
#define COMPUTE_OFFSET_SUB_SUBCASE(case_name, strides, indices) \
COMPUTE_OFFSET_SUBCASE(case_name,   strides,    indices) \
COMPUTE_OFFSET_SUBCASE(case_name,  strides_a,  indices_a) \
COMPUTE_OFFSET_SUBCASE(case_name,  strides_f,  indices_f) \
COMPUTE_OFFSET_SUBCASE(case_name,  strides_h,  indices_h) \
COMPUTE_OFFSET_SUBCASE(case_name,  strides_v,  indices_v) \
COMPUTE_OFFSET_SUBCASE(case_name, strides_ct, indices_ct) \
COMPUTE_OFFSET_SUBCASE(case_name, strides_cl, indices_cl) \
COMPUTE_OFFSET_SUBCASE(case_name, strides, indices_a); \
COMPUTE_OFFSET_SUBCASE(case_name, strides, indices_f); \
COMPUTE_OFFSET_SUBCASE(case_name, strides, indices_h); \
COMPUTE_OFFSET_SUBCASE(case_name, strides, indices_v); \
COMPUTE_OFFSET_SUBCASE(case_name, strides, indices_ct); \
COMPUTE_OFFSET_SUBCASE(case_name, strides, indices_cl); \
COMPUTE_OFFSET_SUBCASE(case_name, strides_a, indices); \
COMPUTE_OFFSET_SUBCASE(case_name, strides_a, indices_f); \
COMPUTE_OFFSET_SUBCASE(case_name, strides_a, indices_h); \
COMPUTE_OFFSET_SUBCASE(case_name, strides_a, indices_v); \
COMPUTE_OFFSET_SUBCASE(case_name, strides_a, indices_ct); \
COMPUTE_OFFSET_SUBCASE(case_name, strides_a, indices_cl); \
COMPUTE_OFFSET_SUBCASE(case_name, strides_f, indices); \
COMPUTE_OFFSET_SUBCASE(case_name, strides_f, indices_a); \
COMPUTE_OFFSET_SUBCASE(case_name, strides_f, indices_h); \
COMPUTE_OFFSET_SUBCASE(case_name, strides_f, indices_v); \
COMPUTE_OFFSET_SUBCASE(case_name, strides_f, indices_ct); \
COMPUTE_OFFSET_SUBCASE(case_name, strides_f, indices_cl); \
COMPUTE_OFFSET_SUBCASE(case_name, strides_h, indices); \
COMPUTE_OFFSET_SUBCASE(case_name, strides_h, indices_f); \
COMPUTE_OFFSET_SUBCASE(case_name, strides_h, indices_a); \
COMPUTE_OFFSET_SUBCASE(case_name, strides_h, indices_v); \
COMPUTE_OFFSET_SUBCASE(case_name, strides_h, indices_ct); \
COMPUTE_OFFSET_SUBCASE(case_name, strides_h, indices_cl); \
COMPUTE_OFFSET_SUBCASE(case_name, strides_v, indices); \
COMPUTE_OFFSET_SUBCASE(case_name, strides_v, indices_a); \
COMPUTE_OFFSET_SUBCASE(case_name, strides_v, indices_f); \
COMPUTE_OFFSET_SUBCASE(case_name, strides_v, indices_h); \
COMPUTE_OFFSET_SUBCASE(case_name, strides_v, indices_ct); \
COMPUTE_OFFSET_SUBCASE(case_name, strides_v, indices_cl); \
COMPUTE_OFFSET_SUBCASE(case_name, strides_ct, indices); \
COMPUTE_OFFSET_SUBCASE(case_name, strides_ct, indices_a); \
COMPUTE_OFFSET_SUBCASE(case_name, strides_ct, indices_f); \
COMPUTE_OFFSET_SUBCASE(case_name, strides_ct, indices_h); \
COMPUTE_OFFSET_SUBCASE(case_name, strides_ct, indices_v); \
COMPUTE_OFFSET_SUBCASE(case_name, strides_ct, indices_cl); \
COMPUTE_OFFSET_SUBCASE(case_name, strides_cl, indices); \
COMPUTE_OFFSET_SUBCASE(case_name, strides_cl, indices_a); \
COMPUTE_OFFSET_SUBCASE(case_name, strides_cl, indices_f); \
COMPUTE_OFFSET_SUBCASE(case_name, strides_cl, indices_h); \
COMPUTE_OFFSET_SUBCASE(case_name, strides_cl, indices_v); \
COMPUTE_OFFSET_SUBCASE(case_name, strides_cl, indices_ct);

TEST_CASE("compute_offset(case1)" * doctest::test_suite("index::compute_offset"))
{
    // doesn't work as expected :|
    // COMPUTE_OFFSET_SUB_SUBCASE(case1a)
    // COMPUTE_OFFSET_SUB_SUBCASE(case1b)
    // COMPUTE_OFFSET_SUB_SUBCASE(case1c)
    // COMPUTE_OFFSET_SUB_SUBCASE(case1d)
    // COMPUTE_OFFSET_SUB_SUBCASE(case1e)
    // COMPUTE_OFFSET_SUB_SUBCASE(case1f)

    COMPUTE_OFFSET_SUBCASE(case1a,   strides,    indices);
    COMPUTE_OFFSET_SUBCASE(case1a,  strides_a,  indices_a);
    COMPUTE_OFFSET_SUBCASE(case1a,  strides_f,  indices_f);
    COMPUTE_OFFSET_SUBCASE(case1a,  strides_h,  indices_h);
    COMPUTE_OFFSET_SUBCASE(case1a,  strides_v,  indices_v);
    COMPUTE_OFFSET_SUBCASE(case1a, strides_ct, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case1a, strides_cl, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case1a, strides, indices_a);
    COMPUTE_OFFSET_SUBCASE(case1a, strides, indices_f);
    COMPUTE_OFFSET_SUBCASE(case1a, strides, indices_h);
    COMPUTE_OFFSET_SUBCASE(case1a, strides, indices_v);
    COMPUTE_OFFSET_SUBCASE(case1a, strides, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case1a, strides, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case1a, strides_a, indices);
    COMPUTE_OFFSET_SUBCASE(case1a, strides_a, indices_f);
    COMPUTE_OFFSET_SUBCASE(case1a, strides_a, indices_h);
    COMPUTE_OFFSET_SUBCASE(case1a, strides_a, indices_v);
    COMPUTE_OFFSET_SUBCASE(case1a, strides_a, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case1a, strides_a, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case1a, strides_f, indices);
    COMPUTE_OFFSET_SUBCASE(case1a, strides_f, indices_a);
    COMPUTE_OFFSET_SUBCASE(case1a, strides_f, indices_h);
    COMPUTE_OFFSET_SUBCASE(case1a, strides_f, indices_v);
    COMPUTE_OFFSET_SUBCASE(case1a, strides_f, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case1a, strides_f, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case1a, strides_h, indices);
    COMPUTE_OFFSET_SUBCASE(case1a, strides_h, indices_f);
    COMPUTE_OFFSET_SUBCASE(case1a, strides_h, indices_a);
    COMPUTE_OFFSET_SUBCASE(case1a, strides_h, indices_v);
    COMPUTE_OFFSET_SUBCASE(case1a, strides_h, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case1a, strides_h, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case1a, strides_v, indices);
    COMPUTE_OFFSET_SUBCASE(case1a, strides_v, indices_a);
    COMPUTE_OFFSET_SUBCASE(case1a, strides_v, indices_f);
    COMPUTE_OFFSET_SUBCASE(case1a, strides_v, indices_h);
    COMPUTE_OFFSET_SUBCASE(case1a, strides_v, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case1a, strides_v, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case1a, strides_ct, indices);
    COMPUTE_OFFSET_SUBCASE(case1a, strides_ct, indices_a);
    COMPUTE_OFFSET_SUBCASE(case1a, strides_ct, indices_f);
    COMPUTE_OFFSET_SUBCASE(case1a, strides_ct, indices_h);
    COMPUTE_OFFSET_SUBCASE(case1a, strides_ct, indices_v);
    COMPUTE_OFFSET_SUBCASE(case1a, strides_ct, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case1a, strides_cl, indices);
    COMPUTE_OFFSET_SUBCASE(case1a, strides_cl, indices_a);
    COMPUTE_OFFSET_SUBCASE(case1a, strides_cl, indices_f);
    COMPUTE_OFFSET_SUBCASE(case1a, strides_cl, indices_h);
    COMPUTE_OFFSET_SUBCASE(case1a, strides_cl, indices_v);
    COMPUTE_OFFSET_SUBCASE(case1a, strides_cl, indices_ct);

    COMPUTE_OFFSET_SUBCASE(case1b,   strides,    indices);
    COMPUTE_OFFSET_SUBCASE(case1b,  strides_a,  indices_a);
    COMPUTE_OFFSET_SUBCASE(case1b,  strides_f,  indices_f);
    COMPUTE_OFFSET_SUBCASE(case1b,  strides_h,  indices_h);
    COMPUTE_OFFSET_SUBCASE(case1b,  strides_v,  indices_v);
    COMPUTE_OFFSET_SUBCASE(case1b, strides_ct, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case1b, strides_cl, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case1b, strides, indices_a);
    COMPUTE_OFFSET_SUBCASE(case1b, strides, indices_f);
    COMPUTE_OFFSET_SUBCASE(case1b, strides, indices_h);
    COMPUTE_OFFSET_SUBCASE(case1b, strides, indices_v);
    COMPUTE_OFFSET_SUBCASE(case1b, strides, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case1b, strides, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case1b, strides_a, indices);
    COMPUTE_OFFSET_SUBCASE(case1b, strides_a, indices_f);
    COMPUTE_OFFSET_SUBCASE(case1b, strides_a, indices_h);
    COMPUTE_OFFSET_SUBCASE(case1b, strides_a, indices_v);
    COMPUTE_OFFSET_SUBCASE(case1b, strides_a, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case1b, strides_a, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case1b, strides_f, indices);
    COMPUTE_OFFSET_SUBCASE(case1b, strides_f, indices_a);
    COMPUTE_OFFSET_SUBCASE(case1b, strides_f, indices_h);
    COMPUTE_OFFSET_SUBCASE(case1b, strides_f, indices_v);
    COMPUTE_OFFSET_SUBCASE(case1b, strides_f, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case1b, strides_f, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case1b, strides_h, indices);
    COMPUTE_OFFSET_SUBCASE(case1b, strides_h, indices_f);
    COMPUTE_OFFSET_SUBCASE(case1b, strides_h, indices_a);
    COMPUTE_OFFSET_SUBCASE(case1b, strides_h, indices_v);
    COMPUTE_OFFSET_SUBCASE(case1b, strides_h, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case1b, strides_h, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case1b, strides_v, indices);
    COMPUTE_OFFSET_SUBCASE(case1b, strides_v, indices_a);
    COMPUTE_OFFSET_SUBCASE(case1b, strides_v, indices_f);
    COMPUTE_OFFSET_SUBCASE(case1b, strides_v, indices_h);
    COMPUTE_OFFSET_SUBCASE(case1b, strides_v, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case1b, strides_v, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case1b, strides_ct, indices);
    COMPUTE_OFFSET_SUBCASE(case1b, strides_ct, indices_a);
    COMPUTE_OFFSET_SUBCASE(case1b, strides_ct, indices_f);
    COMPUTE_OFFSET_SUBCASE(case1b, strides_ct, indices_h);
    COMPUTE_OFFSET_SUBCASE(case1b, strides_ct, indices_v);
    COMPUTE_OFFSET_SUBCASE(case1b, strides_ct, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case1b, strides_cl, indices);
    COMPUTE_OFFSET_SUBCASE(case1b, strides_cl, indices_a);
    COMPUTE_OFFSET_SUBCASE(case1b, strides_cl, indices_f);
    COMPUTE_OFFSET_SUBCASE(case1b, strides_cl, indices_h);
    COMPUTE_OFFSET_SUBCASE(case1b, strides_cl, indices_v);
    COMPUTE_OFFSET_SUBCASE(case1b, strides_cl, indices_ct);

    COMPUTE_OFFSET_SUBCASE(case1c,   strides,    indices);
    COMPUTE_OFFSET_SUBCASE(case1c,  strides_a,  indices_a);
    COMPUTE_OFFSET_SUBCASE(case1c,  strides_f,  indices_f);
    COMPUTE_OFFSET_SUBCASE(case1c,  strides_h,  indices_h);
    COMPUTE_OFFSET_SUBCASE(case1c,  strides_v,  indices_v);
    COMPUTE_OFFSET_SUBCASE(case1c, strides_ct, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case1c, strides_cl, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case1c, strides, indices_a);
    COMPUTE_OFFSET_SUBCASE(case1c, strides, indices_f);
    COMPUTE_OFFSET_SUBCASE(case1c, strides, indices_h);
    COMPUTE_OFFSET_SUBCASE(case1c, strides, indices_v);
    COMPUTE_OFFSET_SUBCASE(case1c, strides, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case1c, strides, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case1c, strides_a, indices);
    COMPUTE_OFFSET_SUBCASE(case1c, strides_a, indices_f);
    COMPUTE_OFFSET_SUBCASE(case1c, strides_a, indices_h);
    COMPUTE_OFFSET_SUBCASE(case1c, strides_a, indices_v);
    COMPUTE_OFFSET_SUBCASE(case1c, strides_a, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case1c, strides_a, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case1c, strides_f, indices);
    COMPUTE_OFFSET_SUBCASE(case1c, strides_f, indices_a);
    COMPUTE_OFFSET_SUBCASE(case1c, strides_f, indices_h);
    COMPUTE_OFFSET_SUBCASE(case1c, strides_f, indices_v);
    COMPUTE_OFFSET_SUBCASE(case1c, strides_f, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case1c, strides_f, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case1c, strides_h, indices);
    COMPUTE_OFFSET_SUBCASE(case1c, strides_h, indices_f);
    COMPUTE_OFFSET_SUBCASE(case1c, strides_h, indices_a);
    COMPUTE_OFFSET_SUBCASE(case1c, strides_h, indices_v);
    COMPUTE_OFFSET_SUBCASE(case1c, strides_h, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case1c, strides_h, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case1c, strides_v, indices);
    COMPUTE_OFFSET_SUBCASE(case1c, strides_v, indices_a);
    COMPUTE_OFFSET_SUBCASE(case1c, strides_v, indices_f);
    COMPUTE_OFFSET_SUBCASE(case1c, strides_v, indices_h);
    COMPUTE_OFFSET_SUBCASE(case1c, strides_v, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case1c, strides_v, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case1c, strides_ct, indices);
    COMPUTE_OFFSET_SUBCASE(case1c, strides_ct, indices_a);
    COMPUTE_OFFSET_SUBCASE(case1c, strides_ct, indices_f);
    COMPUTE_OFFSET_SUBCASE(case1c, strides_ct, indices_h);
    COMPUTE_OFFSET_SUBCASE(case1c, strides_ct, indices_v);
    COMPUTE_OFFSET_SUBCASE(case1c, strides_ct, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case1c, strides_cl, indices);
    COMPUTE_OFFSET_SUBCASE(case1c, strides_cl, indices_a);
    COMPUTE_OFFSET_SUBCASE(case1c, strides_cl, indices_f);
    COMPUTE_OFFSET_SUBCASE(case1c, strides_cl, indices_h);
    COMPUTE_OFFSET_SUBCASE(case1c, strides_cl, indices_v);
    COMPUTE_OFFSET_SUBCASE(case1c, strides_cl, indices_ct);

    COMPUTE_OFFSET_SUBCASE(case1d,   strides,    indices);
    COMPUTE_OFFSET_SUBCASE(case1d,  strides_a,  indices_a);
    COMPUTE_OFFSET_SUBCASE(case1d,  strides_f,  indices_f);
    COMPUTE_OFFSET_SUBCASE(case1d,  strides_h,  indices_h);
    COMPUTE_OFFSET_SUBCASE(case1d,  strides_v,  indices_v);
    COMPUTE_OFFSET_SUBCASE(case1d, strides_ct, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case1d, strides_cl, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case1d, strides, indices_a);
    COMPUTE_OFFSET_SUBCASE(case1d, strides, indices_f);
    COMPUTE_OFFSET_SUBCASE(case1d, strides, indices_h);
    COMPUTE_OFFSET_SUBCASE(case1d, strides, indices_v);
    COMPUTE_OFFSET_SUBCASE(case1d, strides, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case1d, strides, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case1d, strides_a, indices);
    COMPUTE_OFFSET_SUBCASE(case1d, strides_a, indices_f);
    COMPUTE_OFFSET_SUBCASE(case1d, strides_a, indices_h);
    COMPUTE_OFFSET_SUBCASE(case1d, strides_a, indices_v);
    COMPUTE_OFFSET_SUBCASE(case1d, strides_a, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case1d, strides_a, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case1d, strides_f, indices);
    COMPUTE_OFFSET_SUBCASE(case1d, strides_f, indices_a);
    COMPUTE_OFFSET_SUBCASE(case1d, strides_f, indices_h);
    COMPUTE_OFFSET_SUBCASE(case1d, strides_f, indices_v);
    COMPUTE_OFFSET_SUBCASE(case1d, strides_f, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case1d, strides_f, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case1d, strides_h, indices);
    COMPUTE_OFFSET_SUBCASE(case1d, strides_h, indices_f);
    COMPUTE_OFFSET_SUBCASE(case1d, strides_h, indices_a);
    COMPUTE_OFFSET_SUBCASE(case1d, strides_h, indices_v);
    COMPUTE_OFFSET_SUBCASE(case1d, strides_h, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case1d, strides_h, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case1d, strides_v, indices);
    COMPUTE_OFFSET_SUBCASE(case1d, strides_v, indices_a);
    COMPUTE_OFFSET_SUBCASE(case1d, strides_v, indices_f);
    COMPUTE_OFFSET_SUBCASE(case1d, strides_v, indices_h);
    COMPUTE_OFFSET_SUBCASE(case1d, strides_v, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case1d, strides_v, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case1d, strides_ct, indices);
    COMPUTE_OFFSET_SUBCASE(case1d, strides_ct, indices_a);
    COMPUTE_OFFSET_SUBCASE(case1d, strides_ct, indices_f);
    COMPUTE_OFFSET_SUBCASE(case1d, strides_ct, indices_h);
    COMPUTE_OFFSET_SUBCASE(case1d, strides_ct, indices_v);
    COMPUTE_OFFSET_SUBCASE(case1d, strides_ct, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case1d, strides_cl, indices);
    COMPUTE_OFFSET_SUBCASE(case1d, strides_cl, indices_a);
    COMPUTE_OFFSET_SUBCASE(case1d, strides_cl, indices_f);
    COMPUTE_OFFSET_SUBCASE(case1d, strides_cl, indices_h);
    COMPUTE_OFFSET_SUBCASE(case1d, strides_cl, indices_v);
    COMPUTE_OFFSET_SUBCASE(case1d, strides_cl, indices_ct);

    COMPUTE_OFFSET_SUBCASE(case1e,   strides,    indices);
    COMPUTE_OFFSET_SUBCASE(case1e,  strides_a,  indices_a);
    COMPUTE_OFFSET_SUBCASE(case1e,  strides_f,  indices_f);
    COMPUTE_OFFSET_SUBCASE(case1e,  strides_h,  indices_h);
    COMPUTE_OFFSET_SUBCASE(case1e,  strides_v,  indices_v);
    COMPUTE_OFFSET_SUBCASE(case1e, strides_ct, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case1e, strides_cl, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case1e, strides, indices_a);
    COMPUTE_OFFSET_SUBCASE(case1e, strides, indices_f);
    COMPUTE_OFFSET_SUBCASE(case1e, strides, indices_h);
    COMPUTE_OFFSET_SUBCASE(case1e, strides, indices_v);
    COMPUTE_OFFSET_SUBCASE(case1e, strides, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case1e, strides, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case1e, strides_a, indices);
    COMPUTE_OFFSET_SUBCASE(case1e, strides_a, indices_f);
    COMPUTE_OFFSET_SUBCASE(case1e, strides_a, indices_h);
    COMPUTE_OFFSET_SUBCASE(case1e, strides_a, indices_v);
    COMPUTE_OFFSET_SUBCASE(case1e, strides_a, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case1e, strides_a, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case1e, strides_f, indices);
    COMPUTE_OFFSET_SUBCASE(case1e, strides_f, indices_a);
    COMPUTE_OFFSET_SUBCASE(case1e, strides_f, indices_h);
    COMPUTE_OFFSET_SUBCASE(case1e, strides_f, indices_v);
    COMPUTE_OFFSET_SUBCASE(case1e, strides_f, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case1e, strides_f, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case1e, strides_h, indices);
    COMPUTE_OFFSET_SUBCASE(case1e, strides_h, indices_f);
    COMPUTE_OFFSET_SUBCASE(case1e, strides_h, indices_a);
    COMPUTE_OFFSET_SUBCASE(case1e, strides_h, indices_v);
    COMPUTE_OFFSET_SUBCASE(case1e, strides_h, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case1e, strides_h, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case1e, strides_v, indices);
    COMPUTE_OFFSET_SUBCASE(case1e, strides_v, indices_a);
    COMPUTE_OFFSET_SUBCASE(case1e, strides_v, indices_f);
    COMPUTE_OFFSET_SUBCASE(case1e, strides_v, indices_h);
    COMPUTE_OFFSET_SUBCASE(case1e, strides_v, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case1e, strides_v, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case1e, strides_ct, indices);
    COMPUTE_OFFSET_SUBCASE(case1e, strides_ct, indices_a);
    COMPUTE_OFFSET_SUBCASE(case1e, strides_ct, indices_f);
    COMPUTE_OFFSET_SUBCASE(case1e, strides_ct, indices_h);
    COMPUTE_OFFSET_SUBCASE(case1e, strides_ct, indices_v);
    COMPUTE_OFFSET_SUBCASE(case1e, strides_ct, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case1e, strides_cl, indices);
    COMPUTE_OFFSET_SUBCASE(case1e, strides_cl, indices_a);
    COMPUTE_OFFSET_SUBCASE(case1e, strides_cl, indices_f);
    COMPUTE_OFFSET_SUBCASE(case1e, strides_cl, indices_h);
    COMPUTE_OFFSET_SUBCASE(case1e, strides_cl, indices_v);
    COMPUTE_OFFSET_SUBCASE(case1e, strides_cl, indices_ct);

    COMPUTE_OFFSET_SUBCASE(case1f,   strides,    indices);
    COMPUTE_OFFSET_SUBCASE(case1f,  strides_a,  indices_a);
    COMPUTE_OFFSET_SUBCASE(case1f,  strides_f,  indices_f);
    COMPUTE_OFFSET_SUBCASE(case1f,  strides_h,  indices_h);
    COMPUTE_OFFSET_SUBCASE(case1f,  strides_v,  indices_v);
    COMPUTE_OFFSET_SUBCASE(case1f, strides_ct, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case1f, strides_cl, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case1f, strides, indices_a);
    COMPUTE_OFFSET_SUBCASE(case1f, strides, indices_f);
    COMPUTE_OFFSET_SUBCASE(case1f, strides, indices_h);
    COMPUTE_OFFSET_SUBCASE(case1f, strides, indices_v);
    COMPUTE_OFFSET_SUBCASE(case1f, strides, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case1f, strides, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case1f, strides_a, indices);
    COMPUTE_OFFSET_SUBCASE(case1f, strides_a, indices_f);
    COMPUTE_OFFSET_SUBCASE(case1f, strides_a, indices_h);
    COMPUTE_OFFSET_SUBCASE(case1f, strides_a, indices_v);
    COMPUTE_OFFSET_SUBCASE(case1f, strides_a, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case1f, strides_a, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case1f, strides_f, indices);
    COMPUTE_OFFSET_SUBCASE(case1f, strides_f, indices_a);
    COMPUTE_OFFSET_SUBCASE(case1f, strides_f, indices_h);
    COMPUTE_OFFSET_SUBCASE(case1f, strides_f, indices_v);
    COMPUTE_OFFSET_SUBCASE(case1f, strides_f, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case1f, strides_f, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case1f, strides_h, indices);
    COMPUTE_OFFSET_SUBCASE(case1f, strides_h, indices_f);
    COMPUTE_OFFSET_SUBCASE(case1f, strides_h, indices_a);
    COMPUTE_OFFSET_SUBCASE(case1f, strides_h, indices_v);
    COMPUTE_OFFSET_SUBCASE(case1f, strides_h, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case1f, strides_h, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case1f, strides_v, indices);
    COMPUTE_OFFSET_SUBCASE(case1f, strides_v, indices_a);
    COMPUTE_OFFSET_SUBCASE(case1f, strides_v, indices_f);
    COMPUTE_OFFSET_SUBCASE(case1f, strides_v, indices_h);
    COMPUTE_OFFSET_SUBCASE(case1f, strides_v, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case1f, strides_v, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case1f, strides_ct, indices);
    COMPUTE_OFFSET_SUBCASE(case1f, strides_ct, indices_a);
    COMPUTE_OFFSET_SUBCASE(case1f, strides_ct, indices_f);
    COMPUTE_OFFSET_SUBCASE(case1f, strides_ct, indices_h);
    COMPUTE_OFFSET_SUBCASE(case1f, strides_ct, indices_v);
    COMPUTE_OFFSET_SUBCASE(case1f, strides_ct, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case1f, strides_cl, indices);
    COMPUTE_OFFSET_SUBCASE(case1f, strides_cl, indices_a);
    COMPUTE_OFFSET_SUBCASE(case1f, strides_cl, indices_f);
    COMPUTE_OFFSET_SUBCASE(case1f, strides_cl, indices_h);
    COMPUTE_OFFSET_SUBCASE(case1f, strides_cl, indices_v);
    COMPUTE_OFFSET_SUBCASE(case1f, strides_cl, indices_ct);
}

TEST_CASE("compute_offset(case2)" * doctest::test_suite("index::compute_offset"))
{
    COMPUTE_OFFSET_SUBCASE(case2a,   strides,    indices);
    COMPUTE_OFFSET_SUBCASE(case2a,  strides_a,  indices_a);
    COMPUTE_OFFSET_SUBCASE(case2a,  strides_f,  indices_f);
    COMPUTE_OFFSET_SUBCASE(case2a,  strides_h,  indices_h);
    COMPUTE_OFFSET_SUBCASE(case2a,  strides_v,  indices_v);
    COMPUTE_OFFSET_SUBCASE(case2a, strides_ct, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case2a, strides_cl, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2a, strides, indices_a);
    COMPUTE_OFFSET_SUBCASE(case2a, strides, indices_f);
    COMPUTE_OFFSET_SUBCASE(case2a, strides, indices_h);
    COMPUTE_OFFSET_SUBCASE(case2a, strides, indices_v);
    COMPUTE_OFFSET_SUBCASE(case2a, strides, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case2a, strides, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2a, strides_a, indices);
    COMPUTE_OFFSET_SUBCASE(case2a, strides_a, indices_f);
    COMPUTE_OFFSET_SUBCASE(case2a, strides_a, indices_h);
    COMPUTE_OFFSET_SUBCASE(case2a, strides_a, indices_v);
    COMPUTE_OFFSET_SUBCASE(case2a, strides_a, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case2a, strides_a, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2a, strides_f, indices);
    COMPUTE_OFFSET_SUBCASE(case2a, strides_f, indices_a);
    COMPUTE_OFFSET_SUBCASE(case2a, strides_f, indices_h);
    COMPUTE_OFFSET_SUBCASE(case2a, strides_f, indices_v);
    COMPUTE_OFFSET_SUBCASE(case2a, strides_f, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case2a, strides_f, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2a, strides_h, indices);
    COMPUTE_OFFSET_SUBCASE(case2a, strides_h, indices_f);
    COMPUTE_OFFSET_SUBCASE(case2a, strides_h, indices_a);
    COMPUTE_OFFSET_SUBCASE(case2a, strides_h, indices_v);
    COMPUTE_OFFSET_SUBCASE(case2a, strides_h, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case2a, strides_h, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2a, strides_v, indices);
    COMPUTE_OFFSET_SUBCASE(case2a, strides_v, indices_a);
    COMPUTE_OFFSET_SUBCASE(case2a, strides_v, indices_f);
    COMPUTE_OFFSET_SUBCASE(case2a, strides_v, indices_h);
    COMPUTE_OFFSET_SUBCASE(case2a, strides_v, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case2a, strides_v, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2a, strides_ct, indices);
    COMPUTE_OFFSET_SUBCASE(case2a, strides_ct, indices_a);
    COMPUTE_OFFSET_SUBCASE(case2a, strides_ct, indices_f);
    COMPUTE_OFFSET_SUBCASE(case2a, strides_ct, indices_h);
    COMPUTE_OFFSET_SUBCASE(case2a, strides_ct, indices_v);
    COMPUTE_OFFSET_SUBCASE(case2a, strides_ct, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2a, strides_cl, indices);
    COMPUTE_OFFSET_SUBCASE(case2a, strides_cl, indices_a);
    COMPUTE_OFFSET_SUBCASE(case2a, strides_cl, indices_f);
    COMPUTE_OFFSET_SUBCASE(case2a, strides_cl, indices_h);
    COMPUTE_OFFSET_SUBCASE(case2a, strides_cl, indices_v);
    COMPUTE_OFFSET_SUBCASE(case2a, strides_cl, indices_ct);

    COMPUTE_OFFSET_SUBCASE(case2b,   strides,    indices);
    COMPUTE_OFFSET_SUBCASE(case2b,  strides_a,  indices_a);
    COMPUTE_OFFSET_SUBCASE(case2b,  strides_f,  indices_f);
    COMPUTE_OFFSET_SUBCASE(case2b,  strides_h,  indices_h);
    COMPUTE_OFFSET_SUBCASE(case2b,  strides_v,  indices_v);
    COMPUTE_OFFSET_SUBCASE(case2b, strides_ct, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case2b, strides_cl, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2b, strides, indices_a);
    COMPUTE_OFFSET_SUBCASE(case2b, strides, indices_f);
    COMPUTE_OFFSET_SUBCASE(case2b, strides, indices_h);
    COMPUTE_OFFSET_SUBCASE(case2b, strides, indices_v);
    COMPUTE_OFFSET_SUBCASE(case2b, strides, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case2b, strides, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2b, strides_a, indices);
    COMPUTE_OFFSET_SUBCASE(case2b, strides_a, indices_f);
    COMPUTE_OFFSET_SUBCASE(case2b, strides_a, indices_h);
    COMPUTE_OFFSET_SUBCASE(case2b, strides_a, indices_v);
    COMPUTE_OFFSET_SUBCASE(case2b, strides_a, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case2b, strides_a, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2b, strides_f, indices);
    COMPUTE_OFFSET_SUBCASE(case2b, strides_f, indices_a);
    COMPUTE_OFFSET_SUBCASE(case2b, strides_f, indices_h);
    COMPUTE_OFFSET_SUBCASE(case2b, strides_f, indices_v);
    COMPUTE_OFFSET_SUBCASE(case2b, strides_f, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case2b, strides_f, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2b, strides_h, indices);
    COMPUTE_OFFSET_SUBCASE(case2b, strides_h, indices_f);
    COMPUTE_OFFSET_SUBCASE(case2b, strides_h, indices_a);
    COMPUTE_OFFSET_SUBCASE(case2b, strides_h, indices_v);
    COMPUTE_OFFSET_SUBCASE(case2b, strides_h, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case2b, strides_h, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2b, strides_v, indices);
    COMPUTE_OFFSET_SUBCASE(case2b, strides_v, indices_a);
    COMPUTE_OFFSET_SUBCASE(case2b, strides_v, indices_f);
    COMPUTE_OFFSET_SUBCASE(case2b, strides_v, indices_h);
    COMPUTE_OFFSET_SUBCASE(case2b, strides_v, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case2b, strides_v, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2b, strides_ct, indices);
    COMPUTE_OFFSET_SUBCASE(case2b, strides_ct, indices_a);
    COMPUTE_OFFSET_SUBCASE(case2b, strides_ct, indices_f);
    COMPUTE_OFFSET_SUBCASE(case2b, strides_ct, indices_h);
    COMPUTE_OFFSET_SUBCASE(case2b, strides_ct, indices_v);
    COMPUTE_OFFSET_SUBCASE(case2b, strides_ct, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2b, strides_cl, indices);
    COMPUTE_OFFSET_SUBCASE(case2b, strides_cl, indices_a);
    COMPUTE_OFFSET_SUBCASE(case2b, strides_cl, indices_f);
    COMPUTE_OFFSET_SUBCASE(case2b, strides_cl, indices_h);
    COMPUTE_OFFSET_SUBCASE(case2b, strides_cl, indices_v);
    COMPUTE_OFFSET_SUBCASE(case2b, strides_cl, indices_ct);

    COMPUTE_OFFSET_SUBCASE(case2c,   strides,    indices);
    COMPUTE_OFFSET_SUBCASE(case2c,  strides_a,  indices_a);
    COMPUTE_OFFSET_SUBCASE(case2c,  strides_f,  indices_f);
    COMPUTE_OFFSET_SUBCASE(case2c,  strides_h,  indices_h);
    COMPUTE_OFFSET_SUBCASE(case2c,  strides_v,  indices_v);
    COMPUTE_OFFSET_SUBCASE(case2c, strides_ct, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case2c, strides_cl, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2c, strides, indices_a);
    COMPUTE_OFFSET_SUBCASE(case2c, strides, indices_f);
    COMPUTE_OFFSET_SUBCASE(case2c, strides, indices_h);
    COMPUTE_OFFSET_SUBCASE(case2c, strides, indices_v);
    COMPUTE_OFFSET_SUBCASE(case2c, strides, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case2c, strides, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2c, strides_a, indices);
    COMPUTE_OFFSET_SUBCASE(case2c, strides_a, indices_f);
    COMPUTE_OFFSET_SUBCASE(case2c, strides_a, indices_h);
    COMPUTE_OFFSET_SUBCASE(case2c, strides_a, indices_v);
    COMPUTE_OFFSET_SUBCASE(case2c, strides_a, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case2c, strides_a, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2c, strides_f, indices);
    COMPUTE_OFFSET_SUBCASE(case2c, strides_f, indices_a);
    COMPUTE_OFFSET_SUBCASE(case2c, strides_f, indices_h);
    COMPUTE_OFFSET_SUBCASE(case2c, strides_f, indices_v);
    COMPUTE_OFFSET_SUBCASE(case2c, strides_f, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case2c, strides_f, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2c, strides_h, indices);
    COMPUTE_OFFSET_SUBCASE(case2c, strides_h, indices_f);
    COMPUTE_OFFSET_SUBCASE(case2c, strides_h, indices_a);
    COMPUTE_OFFSET_SUBCASE(case2c, strides_h, indices_v);
    COMPUTE_OFFSET_SUBCASE(case2c, strides_h, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case2c, strides_h, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2c, strides_v, indices);
    COMPUTE_OFFSET_SUBCASE(case2c, strides_v, indices_a);
    COMPUTE_OFFSET_SUBCASE(case2c, strides_v, indices_f);
    COMPUTE_OFFSET_SUBCASE(case2c, strides_v, indices_h);
    COMPUTE_OFFSET_SUBCASE(case2c, strides_v, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case2c, strides_v, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2c, strides_ct, indices);
    COMPUTE_OFFSET_SUBCASE(case2c, strides_ct, indices_a);
    COMPUTE_OFFSET_SUBCASE(case2c, strides_ct, indices_f);
    COMPUTE_OFFSET_SUBCASE(case2c, strides_ct, indices_h);
    COMPUTE_OFFSET_SUBCASE(case2c, strides_ct, indices_v);
    COMPUTE_OFFSET_SUBCASE(case2c, strides_ct, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2c, strides_cl, indices);
    COMPUTE_OFFSET_SUBCASE(case2c, strides_cl, indices_a);
    COMPUTE_OFFSET_SUBCASE(case2c, strides_cl, indices_f);
    COMPUTE_OFFSET_SUBCASE(case2c, strides_cl, indices_h);
    COMPUTE_OFFSET_SUBCASE(case2c, strides_cl, indices_v);
    COMPUTE_OFFSET_SUBCASE(case2c, strides_cl, indices_ct);

    COMPUTE_OFFSET_SUBCASE(case2d,   strides,    indices);
    COMPUTE_OFFSET_SUBCASE(case2d,  strides_a,  indices_a);
    COMPUTE_OFFSET_SUBCASE(case2d,  strides_f,  indices_f);
    COMPUTE_OFFSET_SUBCASE(case2d,  strides_h,  indices_h);
    COMPUTE_OFFSET_SUBCASE(case2d,  strides_v,  indices_v);
    COMPUTE_OFFSET_SUBCASE(case2d, strides_ct, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case2d, strides_cl, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2d, strides, indices_a);
    COMPUTE_OFFSET_SUBCASE(case2d, strides, indices_f);
    COMPUTE_OFFSET_SUBCASE(case2d, strides, indices_h);
    COMPUTE_OFFSET_SUBCASE(case2d, strides, indices_v);
    COMPUTE_OFFSET_SUBCASE(case2d, strides, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case2d, strides, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2d, strides_a, indices);
    COMPUTE_OFFSET_SUBCASE(case2d, strides_a, indices_f);
    COMPUTE_OFFSET_SUBCASE(case2d, strides_a, indices_h);
    COMPUTE_OFFSET_SUBCASE(case2d, strides_a, indices_v);
    COMPUTE_OFFSET_SUBCASE(case2d, strides_a, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case2d, strides_a, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2d, strides_f, indices);
    COMPUTE_OFFSET_SUBCASE(case2d, strides_f, indices_a);
    COMPUTE_OFFSET_SUBCASE(case2d, strides_f, indices_h);
    COMPUTE_OFFSET_SUBCASE(case2d, strides_f, indices_v);
    COMPUTE_OFFSET_SUBCASE(case2d, strides_f, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case2d, strides_f, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2d, strides_h, indices);
    COMPUTE_OFFSET_SUBCASE(case2d, strides_h, indices_f);
    COMPUTE_OFFSET_SUBCASE(case2d, strides_h, indices_a);
    COMPUTE_OFFSET_SUBCASE(case2d, strides_h, indices_v);
    COMPUTE_OFFSET_SUBCASE(case2d, strides_h, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case2d, strides_h, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2d, strides_v, indices);
    COMPUTE_OFFSET_SUBCASE(case2d, strides_v, indices_a);
    COMPUTE_OFFSET_SUBCASE(case2d, strides_v, indices_f);
    COMPUTE_OFFSET_SUBCASE(case2d, strides_v, indices_h);
    COMPUTE_OFFSET_SUBCASE(case2d, strides_v, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case2d, strides_v, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2d, strides_ct, indices);
    COMPUTE_OFFSET_SUBCASE(case2d, strides_ct, indices_a);
    COMPUTE_OFFSET_SUBCASE(case2d, strides_ct, indices_f);
    COMPUTE_OFFSET_SUBCASE(case2d, strides_ct, indices_h);
    COMPUTE_OFFSET_SUBCASE(case2d, strides_ct, indices_v);
    COMPUTE_OFFSET_SUBCASE(case2d, strides_ct, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2d, strides_cl, indices);
    COMPUTE_OFFSET_SUBCASE(case2d, strides_cl, indices_a);
    COMPUTE_OFFSET_SUBCASE(case2d, strides_cl, indices_f);
    COMPUTE_OFFSET_SUBCASE(case2d, strides_cl, indices_h);
    COMPUTE_OFFSET_SUBCASE(case2d, strides_cl, indices_v);
    COMPUTE_OFFSET_SUBCASE(case2d, strides_cl, indices_ct);

    COMPUTE_OFFSET_SUBCASE(case2e,   strides,    indices);
    COMPUTE_OFFSET_SUBCASE(case2e,  strides_a,  indices_a);
    COMPUTE_OFFSET_SUBCASE(case2e,  strides_f,  indices_f);
    COMPUTE_OFFSET_SUBCASE(case2e,  strides_h,  indices_h);
    COMPUTE_OFFSET_SUBCASE(case2e,  strides_v,  indices_v);
    COMPUTE_OFFSET_SUBCASE(case2e, strides_ct, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case2e, strides_cl, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2e, strides, indices_a);
    COMPUTE_OFFSET_SUBCASE(case2e, strides, indices_f);
    COMPUTE_OFFSET_SUBCASE(case2e, strides, indices_h);
    COMPUTE_OFFSET_SUBCASE(case2e, strides, indices_v);
    COMPUTE_OFFSET_SUBCASE(case2e, strides, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case2e, strides, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2e, strides_a, indices);
    COMPUTE_OFFSET_SUBCASE(case2e, strides_a, indices_f);
    COMPUTE_OFFSET_SUBCASE(case2e, strides_a, indices_h);
    COMPUTE_OFFSET_SUBCASE(case2e, strides_a, indices_v);
    COMPUTE_OFFSET_SUBCASE(case2e, strides_a, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case2e, strides_a, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2e, strides_f, indices);
    COMPUTE_OFFSET_SUBCASE(case2e, strides_f, indices_a);
    COMPUTE_OFFSET_SUBCASE(case2e, strides_f, indices_h);
    COMPUTE_OFFSET_SUBCASE(case2e, strides_f, indices_v);
    COMPUTE_OFFSET_SUBCASE(case2e, strides_f, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case2e, strides_f, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2e, strides_h, indices);
    COMPUTE_OFFSET_SUBCASE(case2e, strides_h, indices_f);
    COMPUTE_OFFSET_SUBCASE(case2e, strides_h, indices_a);
    COMPUTE_OFFSET_SUBCASE(case2e, strides_h, indices_v);
    COMPUTE_OFFSET_SUBCASE(case2e, strides_h, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case2e, strides_h, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2e, strides_v, indices);
    COMPUTE_OFFSET_SUBCASE(case2e, strides_v, indices_a);
    COMPUTE_OFFSET_SUBCASE(case2e, strides_v, indices_f);
    COMPUTE_OFFSET_SUBCASE(case2e, strides_v, indices_h);
    COMPUTE_OFFSET_SUBCASE(case2e, strides_v, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case2e, strides_v, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2e, strides_ct, indices);
    COMPUTE_OFFSET_SUBCASE(case2e, strides_ct, indices_a);
    COMPUTE_OFFSET_SUBCASE(case2e, strides_ct, indices_f);
    COMPUTE_OFFSET_SUBCASE(case2e, strides_ct, indices_h);
    COMPUTE_OFFSET_SUBCASE(case2e, strides_ct, indices_v);
    COMPUTE_OFFSET_SUBCASE(case2e, strides_ct, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2e, strides_cl, indices);
    COMPUTE_OFFSET_SUBCASE(case2e, strides_cl, indices_a);
    COMPUTE_OFFSET_SUBCASE(case2e, strides_cl, indices_f);
    COMPUTE_OFFSET_SUBCASE(case2e, strides_cl, indices_h);
    COMPUTE_OFFSET_SUBCASE(case2e, strides_cl, indices_v);
    COMPUTE_OFFSET_SUBCASE(case2e, strides_cl, indices_ct);

    COMPUTE_OFFSET_SUBCASE(case2f,   strides,    indices);
    COMPUTE_OFFSET_SUBCASE(case2f,  strides_a,  indices_a);
    COMPUTE_OFFSET_SUBCASE(case2f,  strides_f,  indices_f);
    COMPUTE_OFFSET_SUBCASE(case2f,  strides_h,  indices_h);
    COMPUTE_OFFSET_SUBCASE(case2f,  strides_v,  indices_v);
    COMPUTE_OFFSET_SUBCASE(case2f, strides_ct, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case2f, strides_cl, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2f, strides, indices_a);
    COMPUTE_OFFSET_SUBCASE(case2f, strides, indices_f);
    COMPUTE_OFFSET_SUBCASE(case2f, strides, indices_h);
    COMPUTE_OFFSET_SUBCASE(case2f, strides, indices_v);
    COMPUTE_OFFSET_SUBCASE(case2f, strides, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case2f, strides, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2f, strides_a, indices);
    COMPUTE_OFFSET_SUBCASE(case2f, strides_a, indices_f);
    COMPUTE_OFFSET_SUBCASE(case2f, strides_a, indices_h);
    COMPUTE_OFFSET_SUBCASE(case2f, strides_a, indices_v);
    COMPUTE_OFFSET_SUBCASE(case2f, strides_a, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case2f, strides_a, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2f, strides_f, indices);
    COMPUTE_OFFSET_SUBCASE(case2f, strides_f, indices_a);
    COMPUTE_OFFSET_SUBCASE(case2f, strides_f, indices_h);
    COMPUTE_OFFSET_SUBCASE(case2f, strides_f, indices_v);
    COMPUTE_OFFSET_SUBCASE(case2f, strides_f, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case2f, strides_f, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2f, strides_h, indices);
    COMPUTE_OFFSET_SUBCASE(case2f, strides_h, indices_f);
    COMPUTE_OFFSET_SUBCASE(case2f, strides_h, indices_a);
    COMPUTE_OFFSET_SUBCASE(case2f, strides_h, indices_v);
    COMPUTE_OFFSET_SUBCASE(case2f, strides_h, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case2f, strides_h, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2f, strides_v, indices);
    COMPUTE_OFFSET_SUBCASE(case2f, strides_v, indices_a);
    COMPUTE_OFFSET_SUBCASE(case2f, strides_v, indices_f);
    COMPUTE_OFFSET_SUBCASE(case2f, strides_v, indices_h);
    COMPUTE_OFFSET_SUBCASE(case2f, strides_v, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case2f, strides_v, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2f, strides_ct, indices);
    COMPUTE_OFFSET_SUBCASE(case2f, strides_ct, indices_a);
    COMPUTE_OFFSET_SUBCASE(case2f, strides_ct, indices_f);
    COMPUTE_OFFSET_SUBCASE(case2f, strides_ct, indices_h);
    COMPUTE_OFFSET_SUBCASE(case2f, strides_ct, indices_v);
    COMPUTE_OFFSET_SUBCASE(case2f, strides_ct, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2f, strides_cl, indices);
    COMPUTE_OFFSET_SUBCASE(case2f, strides_cl, indices_a);
    COMPUTE_OFFSET_SUBCASE(case2f, strides_cl, indices_f);
    COMPUTE_OFFSET_SUBCASE(case2f, strides_cl, indices_h);
    COMPUTE_OFFSET_SUBCASE(case2f, strides_cl, indices_v);
    COMPUTE_OFFSET_SUBCASE(case2f, strides_cl, indices_ct);

    COMPUTE_OFFSET_SUBCASE(case2g,   strides,    indices);
    COMPUTE_OFFSET_SUBCASE(case2g,  strides_a,  indices_a);
    COMPUTE_OFFSET_SUBCASE(case2g,  strides_f,  indices_f);
    COMPUTE_OFFSET_SUBCASE(case2g,  strides_h,  indices_h);
    COMPUTE_OFFSET_SUBCASE(case2g,  strides_v,  indices_v);
    COMPUTE_OFFSET_SUBCASE(case2g, strides_ct, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case2g, strides_cl, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2g, strides, indices_a);
    COMPUTE_OFFSET_SUBCASE(case2g, strides, indices_f);
    COMPUTE_OFFSET_SUBCASE(case2g, strides, indices_h);
    COMPUTE_OFFSET_SUBCASE(case2g, strides, indices_v);
    COMPUTE_OFFSET_SUBCASE(case2g, strides, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case2g, strides, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2g, strides_a, indices);
    COMPUTE_OFFSET_SUBCASE(case2g, strides_a, indices_f);
    COMPUTE_OFFSET_SUBCASE(case2g, strides_a, indices_h);
    COMPUTE_OFFSET_SUBCASE(case2g, strides_a, indices_v);
    COMPUTE_OFFSET_SUBCASE(case2g, strides_a, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case2g, strides_a, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2g, strides_f, indices);
    COMPUTE_OFFSET_SUBCASE(case2g, strides_f, indices_a);
    COMPUTE_OFFSET_SUBCASE(case2g, strides_f, indices_h);
    COMPUTE_OFFSET_SUBCASE(case2g, strides_f, indices_v);
    COMPUTE_OFFSET_SUBCASE(case2g, strides_f, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case2g, strides_f, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2g, strides_h, indices);
    COMPUTE_OFFSET_SUBCASE(case2g, strides_h, indices_f);
    COMPUTE_OFFSET_SUBCASE(case2g, strides_h, indices_a);
    COMPUTE_OFFSET_SUBCASE(case2g, strides_h, indices_v);
    COMPUTE_OFFSET_SUBCASE(case2g, strides_h, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case2g, strides_h, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2g, strides_v, indices);
    COMPUTE_OFFSET_SUBCASE(case2g, strides_v, indices_a);
    COMPUTE_OFFSET_SUBCASE(case2g, strides_v, indices_f);
    COMPUTE_OFFSET_SUBCASE(case2g, strides_v, indices_h);
    COMPUTE_OFFSET_SUBCASE(case2g, strides_v, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case2g, strides_v, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2g, strides_ct, indices);
    COMPUTE_OFFSET_SUBCASE(case2g, strides_ct, indices_a);
    COMPUTE_OFFSET_SUBCASE(case2g, strides_ct, indices_f);
    COMPUTE_OFFSET_SUBCASE(case2g, strides_ct, indices_h);
    COMPUTE_OFFSET_SUBCASE(case2g, strides_ct, indices_v);
    COMPUTE_OFFSET_SUBCASE(case2g, strides_ct, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2g, strides_cl, indices);
    COMPUTE_OFFSET_SUBCASE(case2g, strides_cl, indices_a);
    COMPUTE_OFFSET_SUBCASE(case2g, strides_cl, indices_f);
    COMPUTE_OFFSET_SUBCASE(case2g, strides_cl, indices_h);
    COMPUTE_OFFSET_SUBCASE(case2g, strides_cl, indices_v);
    COMPUTE_OFFSET_SUBCASE(case2g, strides_cl, indices_ct);

    COMPUTE_OFFSET_SUBCASE(case2h,   strides,    indices);
    COMPUTE_OFFSET_SUBCASE(case2h,  strides_a,  indices_a);
    COMPUTE_OFFSET_SUBCASE(case2h,  strides_f,  indices_f);
    COMPUTE_OFFSET_SUBCASE(case2h,  strides_h,  indices_h);
    COMPUTE_OFFSET_SUBCASE(case2h,  strides_v,  indices_v);
    COMPUTE_OFFSET_SUBCASE(case2h, strides_ct, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case2h, strides_cl, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2h, strides, indices_a);
    COMPUTE_OFFSET_SUBCASE(case2h, strides, indices_f);
    COMPUTE_OFFSET_SUBCASE(case2h, strides, indices_h);
    COMPUTE_OFFSET_SUBCASE(case2h, strides, indices_v);
    COMPUTE_OFFSET_SUBCASE(case2h, strides, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case2h, strides, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2h, strides_a, indices);
    COMPUTE_OFFSET_SUBCASE(case2h, strides_a, indices_f);
    COMPUTE_OFFSET_SUBCASE(case2h, strides_a, indices_h);
    COMPUTE_OFFSET_SUBCASE(case2h, strides_a, indices_v);
    COMPUTE_OFFSET_SUBCASE(case2h, strides_a, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case2h, strides_a, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2h, strides_f, indices);
    COMPUTE_OFFSET_SUBCASE(case2h, strides_f, indices_a);
    COMPUTE_OFFSET_SUBCASE(case2h, strides_f, indices_h);
    COMPUTE_OFFSET_SUBCASE(case2h, strides_f, indices_v);
    COMPUTE_OFFSET_SUBCASE(case2h, strides_f, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case2h, strides_f, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2h, strides_h, indices);
    COMPUTE_OFFSET_SUBCASE(case2h, strides_h, indices_f);
    COMPUTE_OFFSET_SUBCASE(case2h, strides_h, indices_a);
    COMPUTE_OFFSET_SUBCASE(case2h, strides_h, indices_v);
    COMPUTE_OFFSET_SUBCASE(case2h, strides_h, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case2h, strides_h, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2h, strides_v, indices);
    COMPUTE_OFFSET_SUBCASE(case2h, strides_v, indices_a);
    COMPUTE_OFFSET_SUBCASE(case2h, strides_v, indices_f);
    COMPUTE_OFFSET_SUBCASE(case2h, strides_v, indices_h);
    COMPUTE_OFFSET_SUBCASE(case2h, strides_v, indices_ct);
    COMPUTE_OFFSET_SUBCASE(case2h, strides_v, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2h, strides_ct, indices);
    COMPUTE_OFFSET_SUBCASE(case2h, strides_ct, indices_a);
    COMPUTE_OFFSET_SUBCASE(case2h, strides_ct, indices_f);
    COMPUTE_OFFSET_SUBCASE(case2h, strides_ct, indices_h);
    COMPUTE_OFFSET_SUBCASE(case2h, strides_ct, indices_v);
    COMPUTE_OFFSET_SUBCASE(case2h, strides_ct, indices_cl);
    COMPUTE_OFFSET_SUBCASE(case2h, strides_cl, indices);
    COMPUTE_OFFSET_SUBCASE(case2h, strides_cl, indices_a);
    COMPUTE_OFFSET_SUBCASE(case2h, strides_cl, indices_f);
    COMPUTE_OFFSET_SUBCASE(case2h, strides_cl, indices_h);
    COMPUTE_OFFSET_SUBCASE(case2h, strides_cl, indices_v);
    COMPUTE_OFFSET_SUBCASE(case2h, strides_cl, indices_ct);
}

TEST_CASE("compute_offset" * doctest::test_suite("index"))
{
    {
        auto strides = nmtools_array{2,1};
        {
            auto indices = nmtools_array{0,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==0 );
        }
        {
            auto indices = nmtools_array{0,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==1 );
        }
        {
            auto indices = nmtools_array{1,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==2 );
        }
        {
            auto indices = nmtools_array{1,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==3 );
        }
        {
            auto indices = nmtools_array{2,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==4 );
        }
        {
            auto indices = nmtools_array{2,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==5 );
        }
    }
    {
        // auto shape   = nmtools_array{3,2,3};
        // CHECK( isequal(strides,nmtools_array{6,3,1}) );
        auto strides = nmtools_array{6,3,1};
        {
            auto indices = nmtools_array{0,0,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==0 );
        }
        {
            auto indices = nmtools_array{0,0,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==1 );
        }
        {
            auto indices = nmtools_array{0,0,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==2 );
        }
        {
            auto indices = nmtools_array{0,1,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==3 );
        }
        {
            auto indices = nmtools_array{0,1,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==4 );
        }
        {
            auto indices = nmtools_array{0,1,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==5 );
        }
        {
            auto indices = nmtools_array{1,0,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==6 );
        }
        {
            auto indices = nmtools_array{1,0,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==7 );
        }
        {
            auto indices = nmtools_array{1,0,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==8 );
        }
        {
            auto indices = nmtools_array{1,1,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==9 );
        }
        {
            auto indices = nmtools_array{1,1,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==10 );
        }
        {
            auto indices = nmtools_array{1,1,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==11 );
        }
        {
            auto indices = nmtools_array{2,0,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==12 );
        }
        {
            auto indices = nmtools_array{2,0,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==13 );
        }
        {
            auto indices = nmtools_array{2,0,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==14 );
        }
        {
            auto indices = nmtools_array{2,1,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==15 );
        }
        {
            auto indices = nmtools_array{2,1,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==16 );
        }
        {
            auto indices = nmtools_array{2,1,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==17 );
        }
    }

    using namespace nmtools::literals;

    // clipped shape
    {
        // auto shape   = nmtools_array{3,2,3};
        // CHECK( isequal(strides,nmtools_array{6,3,1}) );
        auto strides = nmtools_tuple{"6:[6]"_ct,"3:[3]"_ct,"1:[1]"_ct};
        {
            auto indices = nmtools_array{0,0,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==0 );
        }
        {
            auto indices = nmtools_array{0,0,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==1 );
        }
        {
            auto indices = nmtools_array{0,0,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==2 );
        }
        {
            auto indices = nmtools_array{0,1,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==3 );
        }
        {
            auto indices = nmtools_array{0,1,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==4 );
        }
        {
            auto indices = nmtools_array{0,1,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==5 );
        }
        {
            auto indices = nmtools_array{1,0,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==6 );
        }
        {
            auto indices = nmtools_array{1,0,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==7 );
        }
        {
            auto indices = nmtools_array{1,0,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==8 );
        }
        {
            auto indices = nmtools_array{1,1,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==9 );
        }
        {
            auto indices = nmtools_array{1,1,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==10 );
        }
        {
            auto indices = nmtools_array{1,1,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==11 );
        }
        {
            auto indices = nmtools_array{2,0,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==12 );
        }
        {
            auto indices = nmtools_array{2,0,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==13 );
        }
        {
            auto indices = nmtools_array{2,0,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==14 );
        }
        {
            auto indices = nmtools_array{2,1,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==15 );
        }
        {
            auto indices = nmtools_array{2,1,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==16 );
        }
        {
            auto indices = nmtools_array{2,1,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==17 );
        }
    }
    // clipped shape
    {
        // auto shape   = nmtools_array{3,2,3};
        // CHECK( isequal(strides,nmtools_array{6,3,1}) );
        auto strides = nmtools_array{"6:[6]"_ct,"3:[6]"_ct,"1:[6]"_ct};
        {
            auto indices = nmtools_array{0,0,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==0 );
        }
        {
            auto indices = nmtools_array{0,0,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==1 );
        }
        {
            auto indices = nmtools_array{0,0,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==2 );
        }
        {
            auto indices = nmtools_array{0,1,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==3 );
        }
        {
            auto indices = nmtools_array{0,1,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==4 );
        }
        {
            auto indices = nmtools_array{0,1,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==5 );
        }
        {
            auto indices = nmtools_array{1,0,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==6 );
        }
        {
            auto indices = nmtools_array{1,0,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==7 );
        }
        {
            auto indices = nmtools_array{1,0,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==8 );
        }
        {
            auto indices = nmtools_array{1,1,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==9 );
        }
        {
            auto indices = nmtools_array{1,1,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==10 );
        }
        {
            auto indices = nmtools_array{1,1,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==11 );
        }
        {
            auto indices = nmtools_array{2,0,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==12 );
        }
        {
            auto indices = nmtools_array{2,0,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==13 );
        }
        {
            auto indices = nmtools_array{2,0,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==14 );
        }
        {
            auto indices = nmtools_array{2,1,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==15 );
        }
        {
            auto indices = nmtools_array{2,1,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==16 );
        }
        {
            auto indices = nmtools_array{2,1,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==17 );
        }
    }
}

#if 0
TEST_CASE("compute_offset(std::vector)" * doctest::test_suite("index"))
{
    {
        auto shape   = std::vector{3,2};
        auto strides = std::vector{2,1};
        {
            auto indices = std::vector{0,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==0 );
        }
        {
            auto indices = std::vector{0,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==1 );
        }
        {
            auto indices = std::vector{1,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==2 );
        }
        {
            auto indices = std::vector{1,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==3 );
        }
        {
            auto indices = std::vector{2,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==4 );
        }
        {
            auto indices = std::vector{2,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==5 );
        }
    }
    {
        // auto shape   = nmtools_array{3,2,3};
        // CHECK( isequal(strides,nmtools_array{6,3,1}) );
        auto strides = std::vector{6,3,1};
        {
            auto indices = std::vector{0,0,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==0 );
        }
        {
            auto indices = std::vector{0,0,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==1 );
        }
        {
            auto indices = std::vector{0,0,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==2 );
        }
        {
            auto indices = std::vector{0,1,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==3 );
        }
        {
            auto indices = std::vector{0,1,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==4 );
        }
        {
            auto indices = std::vector{0,1,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==5 );
        }
        {
            auto indices = std::vector{1,0,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==6 );
        }
        {
            auto indices = std::vector{1,0,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==7 );
        }
        {
            auto indices = std::vector{1,0,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==8 );
        }
        {
            auto indices = std::vector{1,1,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==9 );
        }
        {
            auto indices = std::vector{1,1,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==10 );
        }
        {
            auto indices = std::vector{1,1,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==11 );
        }
        {
            auto indices = std::vector{2,0,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==12 );
        }
        {
            auto indices = std::vector{2,0,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==13 );
        }
        {
            auto indices = std::vector{2,0,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==14 );
        }
        {
            auto indices = std::vector{2,1,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==15 );
        }
        {
            auto indices = std::vector{2,1,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==16 );
        }
        {
            auto indices = std::vector{2,1,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==17 );
        }
    }
}
#endif

TEST_CASE("compute_offset(nmtools_tuple)" * doctest::test_suite("index"))
{
    {
        auto strides = nmtools_tuple{2,1};
        {
            auto indices = nmtools_tuple{0,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==0 );
        }
        {
            auto indices = nmtools_tuple{0,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==1 );
        }
        {
            auto indices = nmtools_tuple{1,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==2 );
        }
        {
            auto indices = nmtools_tuple{1,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==3 );
        }
        {
            auto indices = nmtools_tuple{2,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==4 );
        }
        {
            auto indices = nmtools_tuple{2,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==5 );
        }
    }
    {
        // auto shape   = nmtools_array{3,2,3};
        // CHECK( isequal(strides,nmtools_array{6,3,1}) );
        auto strides = nmtools_tuple{6,3,1};
        {
            auto indices = nmtools_tuple{0,0,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==0 );
        }
        {
            auto indices = nmtools_tuple{0,0,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==1 );
        }
        {
            auto indices = nmtools_tuple{0,0,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==2 );
        }
        {
            auto indices = nmtools_tuple{0,1,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==3 );
        }
        {
            auto indices = nmtools_tuple{0,1,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==4 );
        }
        {
            auto indices = nmtools_tuple{0,1,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==5 );
        }
        {
            auto indices = nmtools_tuple{1,0,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==6 );
        }
        {
            auto indices = nmtools_tuple{1,0,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==7 );
        }
        {
            auto indices = nmtools_tuple{1,0,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==8 );
        }
        {
            auto indices = nmtools_tuple{1,1,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==9 );
        }
        {
            auto indices = nmtools_tuple{1,1,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==10 );
        }
        {
            auto indices = nmtools_tuple{1,1,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==11 );
        }
        {
            auto indices = nmtools_tuple{2,0,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==12 );
        }
        {
            auto indices = nmtools_tuple{2,0,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==13 );
        }
        {
            auto indices = nmtools_tuple{2,0,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==14 );
        }
        {
            auto indices = nmtools_tuple{2,1,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==15 );
        }
        {
            auto indices = nmtools_tuple{2,1,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==16 );
        }
        {
            auto indices = nmtools_tuple{2,1,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==17 );
        }
    }
    #if 0
    {
        // auto shape   = nmtools_array{3,2,3};
        // CHECK( isequal(strides,nmtools_array{6,3,1}) );
        auto strides = std::vector{6,3,1};
        {
            auto indices = nmtools_tuple{0,0,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==0 );
        }
        {
            auto indices = nmtools_tuple{0,0,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==1 );
        }
        {
            auto indices = nmtools_tuple{0,0,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==2 );
        }
        {
            auto indices = nmtools_tuple{0,1,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==3 );
        }
        {
            auto indices = nmtools_tuple{0,1,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==4 );
        }
        {
            auto indices = nmtools_tuple{0,1,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==5 );
        }
        {
            auto indices = nmtools_tuple{1,0,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==6 );
        }
        {
            auto indices = nmtools_tuple{1,0,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==7 );
        }
        {
            auto indices = nmtools_tuple{1,0,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==8 );
        }
        {
            auto indices = nmtools_tuple{1,1,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==9 );
        }
        {
            auto indices = nmtools_tuple{1,1,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==10 );
        }
        {
            auto indices = nmtools_tuple{1,1,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==11 );
        }
        {
            auto indices = nmtools_tuple{2,0,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==12 );
        }
        {
            auto indices = nmtools_tuple{2,0,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==13 );
        }
        {
            auto indices = nmtools_tuple{2,0,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==14 );
        }
        {
            auto indices = nmtools_tuple{2,1,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==15 );
        }
        {
            auto indices = nmtools_tuple{2,1,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==16 );
        }
        {
            auto indices = nmtools_tuple{2,1,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==17 );
        }
    }
    #endif
}