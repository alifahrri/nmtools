#include "nmtools/array/index/outer.hpp"
#include "nmtools/ndarray/dynamic.hpp"
#include "nmtools/ndarray/hybrid.hpp"
#include "nmtools/ndarray/fixed.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>
#include <tuple>

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(index, shape_outer)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int ashape[2] = {1,2};
        int bshape[2] = {3,4};
        NMTOOLS_CAST_INDEX_ARRAYS(ashape)
        NMTOOLS_CAST_INDEX_ARRAYS(bshape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int result[4] = {1,2,3,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        int ashape[1] = {1};
        int bshape[2] = {3,4};
        NMTOOLS_CAST_INDEX_ARRAYS(ashape)
        NMTOOLS_CAST_INDEX_ARRAYS(bshape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        int result[3] = {1,3,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        int ashape[2] = {1,2};
        int bshape[3] = {2,3,4};
        NMTOOLS_CAST_INDEX_ARRAYS(ashape)
        NMTOOLS_CAST_INDEX_ARRAYS(bshape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        int result[5] = {1,2,2,3,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        int ashape[2] = {1,2};
        int bshape[1] = {4};
        NMTOOLS_CAST_INDEX_ARRAYS(ashape)
        NMTOOLS_CAST_INDEX_ARRAYS(bshape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        int result[3] = {1,2,4};
    }
}

#define RUN_shape_outer_impl(...) \
nm::index::shape_outer(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs shape_outer fn to callable lambda
#define RUN_shape_outer(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("shape_outer-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_shape_outer_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_shape_outer(case_name, ...) \
RUN_shape_outer_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define SHAPE_OUTER_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index, shape_outer, case_name); \
    using namespace args; \
    auto result = RUN_shape_outer(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("shape_outer(case1)" * doctest::test_suite("index::shape_outer"))
{
    SHAPE_OUTER_SUBCASE( case1, ashape, bshape );
    SHAPE_OUTER_SUBCASE( case1, ashape_a, bshape_a );
    SHAPE_OUTER_SUBCASE( case1, ashape_v, bshape_v );
    SHAPE_OUTER_SUBCASE( case1, ashape_f, bshape_f );
    // SHAPE_OUTER_SUBCASE( case1, ashape_d, bshape_d );
    SHAPE_OUTER_SUBCASE( case1, ashape_h, bshape_h );
}

TEST_CASE("shape_outer(case2)" * doctest::test_suite("index::shape_outer"))
{
    SHAPE_OUTER_SUBCASE( case2, ashape, bshape );
    SHAPE_OUTER_SUBCASE( case2, ashape_a, bshape_a );
    SHAPE_OUTER_SUBCASE( case2, ashape_v, bshape_v );
    SHAPE_OUTER_SUBCASE( case2, ashape_f, bshape_f );
    // SHAPE_OUTER_SUBCASE( case2, ashape_d, bshape_d );
    SHAPE_OUTER_SUBCASE( case2, ashape_h, bshape_h );
}

TEST_CASE("shape_outer(case3)" * doctest::test_suite("index::shape_outer"))
{
    SHAPE_OUTER_SUBCASE( case3, ashape, bshape );
    SHAPE_OUTER_SUBCASE( case3, ashape_a, bshape_a );
    SHAPE_OUTER_SUBCASE( case3, ashape_v, bshape_v );
    SHAPE_OUTER_SUBCASE( case3, ashape_f, bshape_f );
    // SHAPE_OUTER_SUBCASE( case3, ashape_d, bshape_d );
    SHAPE_OUTER_SUBCASE( case3, ashape_h, bshape_h );
}

TEST_CASE("shape_outer(case4)" * doctest::test_suite("index::shape_outer"))
{
    SHAPE_OUTER_SUBCASE( case4, ashape, bshape );
    SHAPE_OUTER_SUBCASE( case4, ashape_a, bshape_a );
    SHAPE_OUTER_SUBCASE( case4, ashape_v, bshape_v );
    SHAPE_OUTER_SUBCASE( case4, ashape_f, bshape_f );
    // SHAPE_OUTER_SUBCASE( case4, ashape_d, bshape_d );
    SHAPE_OUTER_SUBCASE( case4, ashape_h, bshape_h );
}

NMTOOLS_TESTING_DECLARE_CASE(index, outer)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int indices[4] = {0,0,0,0};
        int ashape[2] = {1,2};
        int bshape[2] = {3,4};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(ashape)
        NMTOOLS_CAST_INDEX_ARRAYS(bshape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int aidx[2] = {0,0};
        int bidx[2] = {0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        int indices[3] = {0,0,0};
        int ashape[1] = {1};
        int bshape[2] = {3,4};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(ashape)
        NMTOOLS_CAST_INDEX_ARRAYS(bshape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        int aidx[1] = {0};
        int bidx[2] = {0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        int indices[5] = {0,0,0,0,0};
        int ashape[2] = {1,2};
        int bshape[3] = {2,3,4};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(ashape)
        NMTOOLS_CAST_INDEX_ARRAYS(bshape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        int aidx[2] = {0,0};
        int bidx[3] = {0,0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        int indices[3] = {0,0,0};
        int ashape[2] = {1,2};
        int bshape[1] = {4};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(ashape)
        NMTOOLS_CAST_INDEX_ARRAYS(bshape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        int aidx[2] = {0,0};
        int bidx[1] = {0};
    }
}


#define RUN_outer_impl(...) \
nm::index::outer(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs outer fn to callable lambda
#define RUN_outer(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("outer-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_outer_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_outer(case_name, ...) \
RUN_outer_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define OUTER_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index, outer, case_name); \
    using namespace args; \
    auto result = RUN_outer(case_name, __VA_ARGS__); \
    auto aidx = nmtools::get<0>(result); \
    auto bidx = nmtools::get<1>(result); \
    NMTOOLS_ASSERT_CLOSE( aidx, expect::aidx ); \
    NMTOOLS_ASSERT_CLOSE( bidx, expect::bidx ); \
}

TEST_CASE("outer(case1)" * doctest::test_suite("index::outer"))
{
    OUTER_SUBCASE( case1, indices, ashape, bshape );
    OUTER_SUBCASE( case1, indices_a, ashape_a, bshape_a );
    OUTER_SUBCASE( case1, indices_v, ashape_v, bshape_v );
    OUTER_SUBCASE( case1, indices_f, ashape_f, bshape_f );
    // OUTER_SUBCASE( case1, indices_d, ashape_d, bshape_d );
    OUTER_SUBCASE( case1, indices_h, ashape_h, bshape_h );
}

TEST_CASE("outer(case2)" * doctest::test_suite("index::outer"))
{
    OUTER_SUBCASE( case2, indices, ashape, bshape );
    OUTER_SUBCASE( case2, indices_a, ashape_a, bshape_a );
    OUTER_SUBCASE( case2, indices_v, ashape_v, bshape_v );
    OUTER_SUBCASE( case2, indices_f, ashape_f, bshape_f );
    // OUTER_SUBCASE( case2, indices_d, ashape_d, bshape_d );
    OUTER_SUBCASE( case2, indices_h, ashape_h, bshape_h );
}

TEST_CASE("outer(case3)" * doctest::test_suite("index::outer"))
{
    OUTER_SUBCASE( case3, indices, ashape, bshape );
    OUTER_SUBCASE( case3, indices_a, ashape_a, bshape_a );
    OUTER_SUBCASE( case3, indices_v, ashape_v, bshape_v );
    OUTER_SUBCASE( case3, indices_f, ashape_f, bshape_f );
    // OUTER_SUBCASE( case3, indices_d, ashape_d, bshape_d );
    OUTER_SUBCASE( case3, indices_h, ashape_h, bshape_h );
}

TEST_CASE("outer(case4)" * doctest::test_suite("index::outer"))
{
    OUTER_SUBCASE( case4, indices, ashape, bshape );
    OUTER_SUBCASE( case4, indices_a, ashape_a, bshape_a );
    OUTER_SUBCASE( case4, indices_v, ashape_v, bshape_v );
    OUTER_SUBCASE( case4, indices_f, ashape_f, bshape_f );
    // OUTER_SUBCASE( case4, indices_d, ashape_d, bshape_d );
    OUTER_SUBCASE( case4, indices_h, ashape_h, bshape_h );
}