#include "nmtools/array/index/slice.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/constants.hpp"

#include <vector>
#include <array>
#include <tuple>

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

#define CAST_ARRAYS(name) \
auto name##_a = cast(name, kind::nested_arr); \
auto name##_v = cast(name, kind::nested_vec); \
auto name##_f = cast(name, kind::fixed); \
auto name##_d = cast(name, kind::dynamic); \
auto name##_h = cast(name, kind::hybrid); \

using std::tuple;

NMTOOLS_TESTING_DECLARE_CASE(index, shape_slice)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int shape[3] = {2,3,2};
        auto slice0 = tuple{None,None};
        auto slice1 = tuple{0,1};
        auto slice2 = tuple{None,None};
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int result[3] = {2,1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        int shape[3] = {2,3,2};
        auto slice0 = tuple{None,None};
        auto slice1 = tuple{None,None};
        auto slice2 = tuple{None,None};
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        int result[3] = {2,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        int shape[3] = {2,3,2};
        auto slice0 = tuple{1,2};
        auto slice1 = tuple{0,1};
        auto slice2 = tuple{None,None};
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        int result[3] = {1,1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        int shape[3] = {2,3,2};
        auto slice0 = tuple{1,3};
        auto slice1 = tuple{0,1};
        auto slice2 = tuple{None,None};
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        int result[3] = {1,1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        int shape[3] = {2,3,2};
        auto slice0 = tuple{None,None};
        auto slice1 = tuple{0,2};
        auto slice2 = tuple{None,-1};
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        int result[3] = {2,2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        int shape[3] = {2,3,2};
        auto slice0 = tuple{None,None};
        auto slice1 = 0;
        auto slice2 = 0;
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        int result[1] = {2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        int shape[3] = {2,3,2};
        auto slice0 = tuple{None,None};
        auto slice1 = 0;
        auto slice2 = tuple{None,-1};
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        int result[2] = {2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        int shape[3] = {2,3,2};
        auto slice0 = tuple{None,None,-1};
        auto slice1 = tuple{None,None};
        auto slice2 = tuple{None,None};
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        int result[3] = {2,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        int shape[3] = {2,3,2};
        auto slice0 = tuple{None,None};
        auto slice1 = tuple{None,None,-1};
        auto slice2 = tuple{None,None};
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        int result[3] = {2,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        int shape[3] = {2,3,2};
        auto slice0 = tuple{None,None,-1};
        auto slice1 = tuple{None,None};
        auto slice2 = tuple{None,None,-1};
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        int result[3] = {2,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        int shape[2] = {4,2};
        auto slice0 = tuple{None,None,2};
        auto slice1 = tuple{None,None};
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        int result[2] = {2,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        int shape[2] = {4,2};
        auto slice0 = tuple{None,None,2};
        auto slice1 = tuple{None,2};
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        int result[2] = {2,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case13)
    {
        int shape[2] = {4,2};
        auto slice0 = tuple{None,None,2};
        auto slice1 = tuple{1,None};
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case13)
    {
        int result[2] = {2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case14)
    {
        int shape[2] = {4,2};
        auto slice0 = tuple{None,None,2};
        auto slice1 = tuple{1,None,2};
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case14)
    {
        int result[2] = {2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case15)
    {
        int shape[2] = {4,2};
        auto slice0 = tuple{None,None,-2};
        auto slice1 = tuple{1,None,-2};
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case15)
    {
        int result[2] = {2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case16)
    {
        int shape[2] = {4,2};
        auto slice0 = tuple{3,None,-2};
        auto slice1 = tuple{1,None,-2};
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case16)
    {
        int result[2] = {2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case17)
    {
        int shape[2] = {4,2};
        auto slice0 = tuple{3,None,2};
        auto slice1 = tuple{1,None,-2};
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case17)
    {
        int result[2] = {1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case18)
    {
        int shape[2] = {4,2};
        auto slice0 = tuple{1,None,-2};
        auto slice1 = tuple{1,None,-2};
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case18)
    {
        int result[2] = {1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case19)
    {
        int shape[2] = {4,2};
        auto slice0 = tuple{2,None,-2};
        auto slice1 = tuple{1,None,-2};
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case19)
    {
        int result[2] = {2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case20)
    {
        int shape[2] = {4,2};
        auto slice0 = tuple{None,None};
        auto slice1 = tuple{1,None,4};
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case20)
    {
        int result[2] = {4,1};
    }
}

#define RUN_shape_slice_impl(...) \
nm::index::shape_slice(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs shape_slice fn to callable lambda
#define RUN_shape_slice(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("shape_slice-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_shape_slice_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_shape_slice(case_name, ...) \
RUN_shape_slice_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define SHAPE_SLICE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(index, shape_slice, case_name); \
    using namespace args; \
    auto result = RUN_shape_slice(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("shape_slice(case1)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case1,   shape, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case1, shape_a, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case1, shape_v, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case1, shape_f, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case1, shape_d, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case1, shape_h, slice0, slice1, slice2);
}

TEST_CASE("shape_slice(case2)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case2,   shape, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case2, shape_a, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case2, shape_v, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case2, shape_f, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case2, shape_d, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case2, shape_h, slice0, slice1, slice2);
}

TEST_CASE("shape_slice(case3)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case3,   shape, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case3, shape_a, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case3, shape_v, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case3, shape_f, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case3, shape_d, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case3, shape_h, slice0, slice1, slice2);
}

TEST_CASE("shape_slice(case4)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case4,   shape, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case4, shape_a, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case4, shape_v, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case4, shape_f, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case4, shape_d, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case4, shape_h, slice0, slice1, slice2);
}

TEST_CASE("shape_slice(case5)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case5,   shape, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case5, shape_a, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case5, shape_v, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case5, shape_f, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case5, shape_d, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case5, shape_h, slice0, slice1, slice2);
}

TEST_CASE("shape_slice(case6)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case6,   shape, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case6, shape_a, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case6, shape_v, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case6, shape_f, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case6, shape_d, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case6, shape_h, slice0, slice1, slice2);
}

TEST_CASE("shape_slice(case7)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case7,   shape, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case7, shape_a, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case7, shape_v, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case7, shape_f, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case7, shape_d, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case7, shape_h, slice0, slice1, slice2);
}

TEST_CASE("shape_slice(case8)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case8,   shape, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case8, shape_a, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case8, shape_v, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case8, shape_f, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case8, shape_d, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case8, shape_h, slice0, slice1, slice2);
}

TEST_CASE("shape_slice(case9)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case9,   shape, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case9, shape_a, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case9, shape_v, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case9, shape_f, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case9, shape_d, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case9, shape_h, slice0, slice1, slice2);
}

TEST_CASE("shape_slice(case10)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case10,   shape, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case10, shape_a, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case10, shape_v, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case10, shape_f, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case10, shape_d, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case10, shape_h, slice0, slice1, slice2);
}

TEST_CASE("shape_slice(case11)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case11,   shape, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case11, shape_a, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case11, shape_v, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case11, shape_f, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case11, shape_d, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case11, shape_h, slice0, slice1);
}

TEST_CASE("shape_slice(case12)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case12,   shape, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case12, shape_a, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case12, shape_v, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case12, shape_f, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case12, shape_d, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case12, shape_h, slice0, slice1);
}

TEST_CASE("shape_slice(case13)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case13,   shape, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case13, shape_a, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case13, shape_v, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case13, shape_f, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case13, shape_d, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case13, shape_h, slice0, slice1);
}

TEST_CASE("shape_slice(case14)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case14,   shape, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case14, shape_a, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case14, shape_v, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case14, shape_f, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case14, shape_d, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case14, shape_h, slice0, slice1);
}

TEST_CASE("shape_slice(case15)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case15,   shape, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case15, shape_a, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case15, shape_v, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case15, shape_f, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case15, shape_d, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case15, shape_h, slice0, slice1);
}

TEST_CASE("shape_slice(case16)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case16,   shape, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case16, shape_a, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case16, shape_v, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case16, shape_f, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case16, shape_d, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case16, shape_h, slice0, slice1);
}

TEST_CASE("shape_slice(case17)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case17,   shape, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case17, shape_a, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case17, shape_v, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case17, shape_f, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case17, shape_d, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case17, shape_h, slice0, slice1);
}

TEST_CASE("shape_slice(case18)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case18,   shape, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case18, shape_a, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case18, shape_v, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case18, shape_f, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case18, shape_d, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case18, shape_h, slice0, slice1);
}

TEST_CASE("shape_slice(case19)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case19,   shape, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case19, shape_a, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case19, shape_v, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case19, shape_f, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case19, shape_d, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case19, shape_h, slice0, slice1);
}

TEST_CASE("shape_slice(case20)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case20,   shape, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case20, shape_a, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case20, shape_v, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case20, shape_f, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case20, shape_d, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case20, shape_h, slice0, slice1);
}

NMTOOLS_TESTING_DECLARE_CASE(index, slice)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int indices[3] = {0,0,1};
        int shape[3] = {2,3,2};
        auto slice0 = tuple{None,None};
        auto slice1 = tuple{0,1};
        auto slice2 = tuple{None,None};
        CAST_ARRAYS(indices)
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        // int result[3] = {2,1,2};
        int result[3] = {0,0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        int indices[3] = {1,2,0};
        int shape[3] = {2,3,2};
        auto slice0 = tuple{None,None};
        auto slice1 = tuple{None,None};
        auto slice2 = tuple{None,None};
        CAST_ARRAYS(indices)
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        // int result[3] = {2,3,2};
        int result[3] = {1,2,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        int indices[3] = {0,0,1};
        int shape[3] = {2,3,2};
        auto slice0 = tuple{1,2};
        auto slice1 = tuple{0,1};
        auto slice2 = tuple{None,None};
        CAST_ARRAYS(indices)
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        // int result[3] = {1,1,2};
        int result[3] = {1,0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        int indices[3] = {0,0,1};
        int shape[3] = {2,3,2};
        auto slice0 = tuple{1,3};
        auto slice1 = tuple{0,1};
        auto slice2 = tuple{None,None};
        CAST_ARRAYS(indices)
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        // int result[3] = {1,1,2};
        int result[3] = {1,0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        int indices[3] = {1,1,0};
        int shape[3] = {2,3,2};
        auto slice0 = tuple{None,None};
        auto slice1 = tuple{0,2};
        auto slice2 = tuple{None,-1};
        CAST_ARRAYS(indices)
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        // int result[3] = {2,2,1};
        int result[3] = {1,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        int indices[1] = {1};
        int shape[3] = {2,3,2};
        auto slice0 = tuple{None,None};
        auto slice1 = 0;
        auto slice2 = 0;
        CAST_ARRAYS(indices)
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        // int result[1] = {2};
        int result[3] = {1,0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        int indices[2] = {1,0};
        int shape[3] = {2,3,2};
        auto slice0 = tuple{None,None};
        auto slice1 = 0;
        auto slice2 = tuple{None,-1};
        CAST_ARRAYS(indices)
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        // int result[2] = {2,1};
        int result[3] = {1,0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        int indices[3] = {0,0,0};
        int shape[3] = {2,3,2};
        auto slice0 = tuple{None,None,-1};
        auto slice1 = tuple{None,None};
        auto slice2 = tuple{None,None};
        CAST_ARRAYS(indices)
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        int result[3] = {1,0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        int indices[3] = {1,2,1};
        int shape[3] = {2,3,2};
        auto slice0 = tuple{None,None,-1};
        auto slice1 = tuple{None,None};
        auto slice2 = tuple{None,None};
        CAST_ARRAYS(indices)
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        int result[3] = {0,2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        int indices[3] = {0,0,0};
        int shape[3] = {2,3,2};
        auto slice0 = tuple{None,None};
        auto slice1 = tuple{None,None,-1};
        auto slice2 = tuple{None,None};
        CAST_ARRAYS(indices)
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        int result[3] = {0,2,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        int indices[3] = {1,2,1};
        int shape[3] = {2,3,2};
        auto slice0 = tuple{None,None};
        auto slice1 = tuple{None,None,-1};
        auto slice2 = tuple{None,None};
        CAST_ARRAYS(indices)
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        int result[3] = {1,0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        int indices[3] = {1,1,1};
        int shape[3] = {2,3,2};
        auto slice0 = tuple{None,None};
        auto slice1 = tuple{None,None,-1};
        auto slice2 = tuple{None,None};
        CAST_ARRAYS(indices)
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        int result[3] = {1,1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case13)
    {
        int indices[3] = {0,0,0};
        int shape[3] = {2,3,2};
        auto slice0 = tuple{None,None,-1};
        auto slice1 = tuple{None,None};
        auto slice2 = tuple{None,None,-1};
        CAST_ARRAYS(indices)
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case13)
    {
        int result[3] = {1,0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case14)
    {
        int indices[3] = {0,0,1};
        int shape[3] = {2,3,2};
        auto slice0 = tuple{None,None,-1};
        auto slice1 = tuple{0,1};
        auto slice2 = tuple{None,None,-1};
        CAST_ARRAYS(indices)
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case14)
    {
        int result[3] = {1,0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case15)
    {
        int indices[3] = {0,0,1};
        int shape[3] = {2,3,2};
        auto slice0 = tuple{None,None,-1};
        auto slice1 = tuple{1,None,-1};
        auto slice2 = tuple{None,None,-1};
        CAST_ARRAYS(indices)
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case15)
    {
        int result[3] = {1,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case16)
    {
        int indices[3] = {0,1,1};
        int shape[3] = {2,3,2};
        auto slice0 = tuple{None,None,-1};
        auto slice1 = tuple{1,None,-1};
        auto slice2 = tuple{None,None,-1};
        CAST_ARRAYS(indices)
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case16)
    {
        int result[3] = {1,0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case17)
    {
        int indices[2] = {1,1};
        int shape[2] = {4,2};
        auto slice0 = tuple{None,None,2};
        auto slice1 = tuple{None,None};
        CAST_ARRAYS(indices)
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case17)
    {
        int result[2] = {2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case18)
    {
        int indices[2] = {1,1};
        int shape[2] = {4,2};
        auto slice0 = tuple{None,None,-2};
        auto slice1 = tuple{None,None};
        CAST_ARRAYS(indices)
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case18)
    {
        int result[2] = {1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case19)
    {
        int indices[2] = {0,0};
        int shape[2] = {4,2};
        auto slice0 = tuple{None,None,-2};
        auto slice1 = tuple{None,None};
        CAST_ARRAYS(indices)
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case19)
    {
        int result[2] = {3,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case20)
    {
        int indices[2] = {0,0};
        int shape[2] = {4,2};
        auto slice0 = tuple{None,None,-2};
        auto slice1 = tuple{1,None,2};
        CAST_ARRAYS(indices)
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case20)
    {
        int result[2] = {3,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case21)
    {
        int indices[2] = {0,0};
        int shape[2] = {4,2};
        auto slice0 = tuple{None,None,-2};
        auto slice1 = tuple{1,None,-2};
        CAST_ARRAYS(indices)
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case21)
    {
        int result[2] = {3,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case22)
    {
        int indices[2] = {0,0};
        int shape[2] = {4,2};
        auto slice0 = tuple{3,None,-2};
        auto slice1 = tuple{1,None,-2};
        CAST_ARRAYS(indices)
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case22)
    {
        int result[2] = {3,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case23)
    {
        int indices[2] = {0,0};
        int shape[2] = {4,2};
        auto slice0 = tuple{3,None,2};
        auto slice1 = tuple{1,None,-2};
        CAST_ARRAYS(indices)
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case23)
    {
        int result[2] = {3,1};
    }
}

#define RUN_slice_impl(...) \
nm::index::slice(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs slice fn to callable lambda
#define RUN_slice(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("slice-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_slice_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_slice(case_name, ...) \
RUN_slice_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define SLICE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(index, slice, case_name); \
    using namespace args; \
    auto result = RUN_slice(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("slice(case1)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case1,   indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case1, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case1, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case1, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case1, indices_d, shape_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case1, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case2)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case2, indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case2, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case2, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case2, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case2, indices_d, shape_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case2, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case3)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case3, indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case3, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case3, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case3, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case3, indices_d, shape_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case3, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case4)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case4, indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case4, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case4, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case4, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case4, indices_d, shape_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case4, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case5)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case5, indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case5, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case5, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case5, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case5, indices_d, shape_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case5, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case6)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case6, indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case6, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case6, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case6, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case6, indices_d, shape_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case6, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case7)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case7, indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case7, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case7, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case7, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case7, indices_d, shape_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case7, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case8)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case8, indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case8, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case8, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case8, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case8, indices_d, shape_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case8, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case9)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case9, indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case9, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case9, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case9, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case9, indices_d, shape_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case9, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case10)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case10, indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case10, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case10, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case10, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case10, indices_d, shape_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case10, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case11)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case11, indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case11, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case11, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case11, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case11, indices_d, shape_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case11, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case12)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case12, indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case12, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case12, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case12, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case12, indices_d, shape_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case12, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case13)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case13, indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case13, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case13, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case13, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case13, indices_d, shape_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case13, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case14)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case14, indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case14, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case14, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case14, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case14, indices_d, shape_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case14, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case15)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case15, indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case15, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case15, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case15, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case15, indices_d, shape_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case15, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case16)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case16, indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case16, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case16, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case16, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case16, indices_d, shape_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case16, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case17)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case17, indices,   shape, slice0, slice1);
    SLICE_SUBCASE(case17, indices_a, shape_a, slice0, slice1);
    SLICE_SUBCASE(case17, indices_v, shape_v, slice0, slice1);
    SLICE_SUBCASE(case17, indices_f, shape_f, slice0, slice1);
    SLICE_SUBCASE(case17, indices_d, shape_d, slice0, slice1);
    SLICE_SUBCASE(case17, indices_h, shape_h, slice0, slice1);
}

TEST_CASE("slice(case18)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case18, indices,   shape, slice0, slice1);
    SLICE_SUBCASE(case18, indices_a, shape_a, slice0, slice1);
    SLICE_SUBCASE(case18, indices_v, shape_v, slice0, slice1);
    SLICE_SUBCASE(case18, indices_f, shape_f, slice0, slice1);
    SLICE_SUBCASE(case18, indices_d, shape_d, slice0, slice1);
    SLICE_SUBCASE(case18, indices_h, shape_h, slice0, slice1);
}

TEST_CASE("slice(case19)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case19, indices,   shape, slice0, slice1);
    SLICE_SUBCASE(case19, indices_a, shape_a, slice0, slice1);
    SLICE_SUBCASE(case19, indices_v, shape_v, slice0, slice1);
    SLICE_SUBCASE(case19, indices_f, shape_f, slice0, slice1);
    SLICE_SUBCASE(case19, indices_d, shape_d, slice0, slice1);
    SLICE_SUBCASE(case19, indices_h, shape_h, slice0, slice1);
}

TEST_CASE("slice(case20)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case20, indices,   shape, slice0, slice1);
    SLICE_SUBCASE(case20, indices_a, shape_a, slice0, slice1);
    SLICE_SUBCASE(case20, indices_v, shape_v, slice0, slice1);
    SLICE_SUBCASE(case20, indices_f, shape_f, slice0, slice1);
    SLICE_SUBCASE(case20, indices_d, shape_d, slice0, slice1);
    SLICE_SUBCASE(case20, indices_h, shape_h, slice0, slice1);
}

TEST_CASE("slice(case21)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case21, indices,   shape, slice0, slice1);
    SLICE_SUBCASE(case21, indices_a, shape_a, slice0, slice1);
    SLICE_SUBCASE(case21, indices_v, shape_v, slice0, slice1);
    SLICE_SUBCASE(case21, indices_f, shape_f, slice0, slice1);
    SLICE_SUBCASE(case21, indices_d, shape_d, slice0, slice1);
    SLICE_SUBCASE(case21, indices_h, shape_h, slice0, slice1);
}

TEST_CASE("slice(case22)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case22, indices,   shape, slice0, slice1);
    SLICE_SUBCASE(case22, indices_a, shape_a, slice0, slice1);
    SLICE_SUBCASE(case22, indices_v, shape_v, slice0, slice1);
    SLICE_SUBCASE(case22, indices_f, shape_f, slice0, slice1);
    SLICE_SUBCASE(case22, indices_d, shape_d, slice0, slice1);
    SLICE_SUBCASE(case22, indices_h, shape_h, slice0, slice1);
}

TEST_CASE("slice(case23)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case23, indices,   shape, slice0, slice1);
    SLICE_SUBCASE(case23, indices_a, shape_a, slice0, slice1);
    SLICE_SUBCASE(case23, indices_v, shape_v, slice0, slice1);
    SLICE_SUBCASE(case23, indices_f, shape_f, slice0, slice1);
    SLICE_SUBCASE(case23, indices_d, shape_d, slice0, slice1);
    SLICE_SUBCASE(case23, indices_h, shape_h, slice0, slice1);
}