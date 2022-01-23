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

    // a[...,:]
    NMTOOLS_TESTING_DECLARE_ARGS(case21)
    {
        int shape[3] = {2,3,2};
        auto slice0  = Elipsis;
        auto slice1  = tuple{None,None};
        CAST_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case21)
    {
        int result[3] = {2,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case22)
    {
        int shape[3] = {2,3,2};
        auto slice0  = Elipsis;
        auto slice1  = tuple{None,Last};
        CAST_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case22)
    {
        int result[3] = {2,3,1};
    }

    // a[...,0:-1]
    NMTOOLS_TESTING_DECLARE_ARGS(case23)
    {
        int shape[3] = {2,3,2};
        auto slice0  = Elipsis;
        auto slice1  = tuple{0,Last};
        CAST_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case23)
    {
        int result[3] = {2,3,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case24)
    {
        int shape[3] = {2,3,2};
        auto slice0  = tuple{0ul,Last};
        auto slice1  = Elipsis;
        CAST_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case24)
    {
        int result[3] = {1,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case25)
    {
        int shape[3] = {2,3,2};
        auto slice0  = 0;
        auto slice1  = Elipsis;
        CAST_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case25)
    {
        int result[2] = {3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case26)
    {
        int shape[3] = {2,3,2};
        auto slice0  = Elipsis;
        auto slice1  = 0;
        CAST_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case26)
    {
        int result[2] = {2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case27)
    {
        int shape[3] = {2,3,2};
        auto slice0  = 0;
        auto slice1  = Elipsis;
        auto slice2  = 0;
        CAST_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case27)
    {
        int result[1] = {3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case28)
    {
        int shape[4] = {2,1,3,2};
        auto slice0  = Elipsis;
        auto slice1  = 1;
        CAST_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case28)
    {
        int result[3] = {2,1,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case29)
    {
        int shape[4] = {2,1,3,2};
        auto slice0  = Elipsis;
        auto slice1  = 1;
        auto slice2  = 0;
        CAST_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case29)
    {
        int result[2] = {2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case30)
    {
        int shape[4] = {2,1,3,2};
        auto slice0  = 1;
        auto slice1  = Elipsis;
        auto slice2  = 0;
        CAST_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case30)
    {
        int result[2] = {1,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case31)
    {
        int shape[4] = {2,1,3,2};
        auto slice0  = Last;
        auto slice1  = Elipsis;
        auto slice2  = 0;
        CAST_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case31)
    {
        int result[2] = {1,3};
    }

    // a[...,0:-1:-1]
    NMTOOLS_TESTING_DECLARE_ARGS(case32)
    {
        int shape[3] = {2,3,2};
        auto slice0  = Elipsis;
        auto slice1  = tuple{0,Last,-1};
        CAST_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case32)
    {
        int result[3] = {2,3,1};
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

TEST_CASE("shape_slice(case21)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case21,   shape, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case21, shape_a, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case21, shape_v, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case21, shape_f, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case21, shape_d, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case21, shape_h, slice0, slice1);
}

TEST_CASE("shape_slice(case22)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case22,   shape, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case22, shape_a, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case22, shape_v, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case22, shape_f, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case22, shape_d, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case22, shape_h, slice0, slice1);
}

TEST_CASE("shape_slice(case23)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case23,   shape, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case23, shape_a, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case23, shape_v, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case23, shape_f, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case23, shape_d, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case23, shape_h, slice0, slice1);
}

TEST_CASE("shape_slice(case24)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case24,   shape, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case24, shape_a, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case24, shape_v, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case24, shape_f, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case24, shape_d, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case24, shape_h, slice0, slice1);

    static_assert( nm::meta::is_index_v<decltype(nm::Last)> );
    static_assert( nm::meta::is_integral_constant_v<decltype(nm::Last)> );
}

TEST_CASE("shape_slice(case25)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case25,   shape, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case25, shape_a, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case25, shape_v, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case25, shape_f, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case25, shape_d, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case25, shape_h, slice0, slice1);
}

TEST_CASE("shape_slice(case26)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case26,   shape, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case26, shape_a, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case26, shape_v, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case26, shape_f, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case26, shape_d, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case26, shape_h, slice0, slice1);
}

TEST_CASE("shape_slice(case27)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case27,   shape, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case27, shape_a, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case27, shape_v, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case27, shape_f, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case27, shape_d, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case27, shape_h, slice0, slice1, slice2);
}

TEST_CASE("shape_slice(case28)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case28,   shape, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case28, shape_a, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case28, shape_v, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case28, shape_f, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case28, shape_d, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case28, shape_h, slice0, slice1);
}

TEST_CASE("shape_slice(case29)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case29,   shape, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case29, shape_a, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case29, shape_v, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case29, shape_f, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case29, shape_d, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case29, shape_h, slice0, slice1, slice2);
}

TEST_CASE("shape_slice(case30)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case30,   shape, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case30, shape_a, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case30, shape_v, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case30, shape_f, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case30, shape_d, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case30, shape_h, slice0, slice1, slice2);
}

TEST_CASE("shape_slice(case31)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case31,   shape, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case31, shape_a, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case31, shape_v, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case31, shape_f, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case31, shape_d, slice0, slice1, slice2);
    SHAPE_SLICE_SUBCASE(case31, shape_h, slice0, slice1, slice2);
}

TEST_CASE("shape_slice(case32)" * doctest::test_suite("index::shape_slice"))
{
    SHAPE_SLICE_SUBCASE(case32,   shape, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case32, shape_a, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case32, shape_v, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case32, shape_f, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case32, shape_d, slice0, slice1);
    SHAPE_SLICE_SUBCASE(case32, shape_h, slice0, slice1);
}

NMTOOLS_TESTING_DECLARE_CASE(index, shape_dynamic_slice)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        using slice_t  = std::array<int,3>;
        using slices_t = meta::make_sequence_type_t<slice_t>;
        inline auto shape  = nmtools_list{2,3,2};
        inline auto slices = slices_t{{0,2,1},{0,1,1},{0,2,1}};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline auto result = nmtools_list{2,1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        using slice_t  = std::array<int,2>;
        using slices_t = meta::make_sequence_type_t<slice_t>;
        inline auto shape  = nmtools_list{2,3,2};
        inline auto slices = slices_t{{0,2},{0,1},{0,2}};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline auto result = nmtools_list{2,1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        using slice_t  = nmtools_tuple<none_t,int>;
        using slices_t = meta::make_sequence_type_t<slice_t>;
        inline auto shape  = nmtools_list{2,3,2};
        inline auto slices = slices_t{{None,2},{None,1},{None,2}};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline auto result = nmtools_list{2,1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        using slice_t  = nmtools_tuple<none_t,none_t>;
        using slices_t = meta::make_sequence_type_t<slice_t>;
        inline auto shape  = nmtools_list{2,3,2};
        inline auto slices = slices_t{{None,None},{None,None},{None,None}};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline auto result = nmtools_list{2,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        using slice_t  = nmtools_tuple<none_t,int>;
        using slices_t = nmtools_list<slice_t>;
        inline auto shape  = nmtools_list{2,3,2};
        inline auto slices = slices_t{{None,2},{None,2},{None,-1}};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline auto result = nmtools_list{2,2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        using slice_t  = nmtools_tuple<none_t,none_t,int>;
        using slices_t = nmtools_list<slice_t>;
        inline auto shape  = nmtools_list{2,3,2};
        inline auto slices = slices_t{{None,None,1},{None,None,-1},{None,None,1}};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline auto result = nmtools_list{2,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        using slice_t  = nmtools_tuple<none_t,none_t,int>;
        using slices_t = nmtools_list<slice_t>;
        inline auto shape  = nmtools_list{4,2};
        inline auto slices = slices_t{{None,None,2},{None,None,1}};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline auto result = nmtools_list{2,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        using slice_t  = nmtools_tuple<int,none_t,int>;
        using slices_t = nmtools_list<slice_t>;
        inline auto shape  = nmtools_list{4,2};
        inline auto slices = slices_t{{0,None,-2},{1,None,-2}};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline auto result = nmtools_list{1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        using slice_t  = nmtools_tuple<int,none_t,int>;
        using slices_t = nmtools_list<slice_t>;
        inline auto shape = nmtools_list{4,2};
        inline auto slices = slices_t{{3,None,-2},{1,None,-2}};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline auto result = nmtools_list{2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        using slice_t  = nmtools_tuple<int,none_t,int>;
        using slices_t = nmtools_list<slice_t>;
        inline auto shape = nmtools_list{4,2};
        inline auto slices = slices_t{{3,None,2},{1,None,-2}};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline auto result = nmtools_list{1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        using slice_t  = nmtools_tuple<int,none_t,int>;
        using slices_t = nmtools_list<slice_t>;
        inline auto shape = nmtools_list{4,2};
        inline auto slices = slices_t{{2,None,-2},{1,None,-2}};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        inline auto result = nmtools_list{2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        using slice_t  = nmtools_either<int,nmtools_tuple<none_t,none_t>>;
        using slices_t = nmtools_list<slice_t>;
        inline auto shape   = nmtools_list{2,3,2};
        inline auto slices  = slices_t{nmtools_tuple{None,None},0,0};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        inline auto result = nmtools_list{2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case13)
    {
        using slice_t  = nmtools_either<int,nmtools_tuple<none_t,int>>;
        using slices_t = nmtools_list<slice_t>;
        inline auto shape   = nmtools_list{2,3,2};
        inline auto slices  = slices_t{nmtools_tuple{None,2},0,nmtools_tuple{None,-1}};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case13)
    {
        inline auto result = nmtools_list{2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case14)
    {
        using slice_t  = nmtools_either<elipsis_t,nmtools_tuple<none_t,none_t>>;
        using slices_t = nmtools_list<slice_t>;
        inline auto shape   = nmtools_list{2,3,2};
        inline auto slices  = slices_t{Elipsis,nmtools_tuple{None,None}};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case14)
    {
        inline auto result = nmtools_list{2,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case15)
    {
        using slice_t  = nmtools_either<int,elipsis_t>;
        using slices_t = nmtools_list<slice_t>;
        inline auto shape  = nmtools_list{2,3,2};
        inline auto slices = slices_t{0,Elipsis};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case15)
    {
        inline auto result = nmtools_list{3,2};
    }
}

#define RUN_shape_dynamic_slice_impl(...) \
nm::index::shape_dynamic_slice(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs shape_dynamic_slice fn to callable lambda
#define RUN_shape_dynamic_slice(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("shape_dynamic_slice-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_shape_dynamic_slice_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_shape_dynamic_slice(case_name, ...) \
RUN_shape_dynamic_slice_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define SHAPE_DYNAMIC_SLICE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(index, shape_dynamic_slice, case_name); \
    using namespace args; \
    auto result = RUN_shape_dynamic_slice(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("shape_dynamic_slice(case1)" * doctest::test_suite("index::shape_dynamic_slice"))
{
    SHAPE_DYNAMIC_SLICE_SUBCASE(case1, shape, slices);
}

TEST_CASE("shape_dynamic_slice(case2)" * doctest::test_suite("index::shape_dynamic_slice"))
{
    SHAPE_DYNAMIC_SLICE_SUBCASE(case2, shape, slices);
}

TEST_CASE("shape_dynamic_slice(case3)" * doctest::test_suite("index::shape_dynamic_slice"))
{
    SHAPE_DYNAMIC_SLICE_SUBCASE(case3, shape, slices);
}

TEST_CASE("shape_dynamic_slice(case4)" * doctest::test_suite("index::shape_dynamic_slice"))
{
    SHAPE_DYNAMIC_SLICE_SUBCASE(case4, shape, slices);
}

TEST_CASE("shape_dynamic_slice(case5)" * doctest::test_suite("index::shape_dynamic_slice"))
{
    SHAPE_DYNAMIC_SLICE_SUBCASE(case5, shape, slices);
}

TEST_CASE("shape_dynamic_slice(case6)" * doctest::test_suite("index::shape_dynamic_slice"))
{
    SHAPE_DYNAMIC_SLICE_SUBCASE(case6, shape, slices);
}

TEST_CASE("shape_dynamic_slice(case7)" * doctest::test_suite("index::shape_dynamic_slice"))
{
    SHAPE_DYNAMIC_SLICE_SUBCASE(case7, shape, slices);
}

TEST_CASE("shape_dynamic_slice(case8)" * doctest::test_suite("index::shape_dynamic_slice"))
{
    SHAPE_DYNAMIC_SLICE_SUBCASE(case8, shape, slices);
}

TEST_CASE("shape_dynamic_slice(case9)" * doctest::test_suite("index::shape_dynamic_slice"))
{
    SHAPE_DYNAMIC_SLICE_SUBCASE(case9, shape, slices);
}

TEST_CASE("shape_dynamic_slice(case10)" * doctest::test_suite("index::shape_dynamic_slice"))
{
    SHAPE_DYNAMIC_SLICE_SUBCASE(case10, shape, slices);
}

TEST_CASE("shape_dynamic_slice(case11)" * doctest::test_suite("index::shape_dynamic_slice"))
{
    SHAPE_DYNAMIC_SLICE_SUBCASE(case11, shape, slices);
}

TEST_CASE("shape_dynamic_slice(case12)" * doctest::test_suite("index::shape_dynamic_slice"))
{
    SHAPE_DYNAMIC_SLICE_SUBCASE(case12, shape, slices);
}

TEST_CASE("shape_dynamic_slice(case13)" * doctest::test_suite("index::shape_dynamic_slice"))
{
    SHAPE_DYNAMIC_SLICE_SUBCASE(case13, shape, slices);
}

TEST_CASE("shape_dynamic_slice(case14)" * doctest::test_suite("index::shape_dynamic_slice"))
{
    SHAPE_DYNAMIC_SLICE_SUBCASE(case14, shape, slices);
}

TEST_CASE("shape_dynamic_slice(case15)" * doctest::test_suite("index::shape_dynamic_slice"))
{
    SHAPE_DYNAMIC_SLICE_SUBCASE(case15, shape, slices);
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

    NMTOOLS_TESTING_DECLARE_ARGS(case24)
    {
        int indices[3] = {0,1,0};
        int shape[3] = {2,3,2};
        auto slice0  = Elipsis;
        auto slice1  = tuple{None,None};
        CAST_ARRAYS(shape);
        CAST_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case24)
    {
        int result[3] = {0,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case25)
    {
        int indices[3] = {0,1,0};
        int shape[3] = {2,3,2};
        auto slice0  = Elipsis;
        auto slice1  = tuple{None,Last};
        CAST_ARRAYS(shape);
        CAST_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case25)
    {
        int result[3] = {0,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case26)
    {
        int indices[3] = {0,1,0};
        int shape[3] = {2,3,2};
        auto slice0  = Elipsis;
        auto slice1  = tuple{0,Last};
        CAST_ARRAYS(shape);
        CAST_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case26)
    {
        int result[3] = {0,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case27)
    {
        int indices[3] = {0,1,0};
        int shape[3] = {2,3,2};
        auto slice0  = tuple{0ul,Last};
        auto slice1  = Elipsis;
        CAST_ARRAYS(shape);
        CAST_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case27)
    {
        int result[3] = {0,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case28)
    {
        int indices[2] = {1,0};
        int shape[3] = {2,3,2};
        auto slice0  = 0;
        auto slice1  = Elipsis;
        CAST_ARRAYS(shape);
        CAST_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case28)
    {
        int result[3] = {0,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case29)
    {
        int indices[2] = {1,1};
        int shape[3] = {2,3,2};
        auto slice0  = 0;
        auto slice1  = Elipsis;
        CAST_ARRAYS(shape);
        CAST_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case29)
    {
        int result[3] = {0,1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case30)
    {
        int indices[2] = {1,0};
        int shape[3] = {2,3,2};
        auto slice0  = Elipsis;
        auto slice1  = 0;
        CAST_ARRAYS(shape);
        CAST_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case30)
    {
        int result[3] = {1,0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case31)
    {
        int indices[2] = {1,1};
        int shape[3] = {2,3,2};
        auto slice0  = Elipsis;
        auto slice1  = 0;
        CAST_ARRAYS(shape);
        CAST_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case31)
    {
        int result[3] = {1,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case32)
    {
        int indices[1] = {2};
        int shape[3] = {2,3,2};
        auto slice0  = 0;
        auto slice1  = Elipsis;
        auto slice2  = 0;
        CAST_ARRAYS(shape);
        CAST_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case32)
    {
        int result[3] = {0,2,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case33)
    {
        int indices[3] = {0,0,0};
        int shape[4] = {2,1,3,2};
        auto slice0  = Elipsis;
        auto slice1  = 1;
        CAST_ARRAYS(shape);
        CAST_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case33)
    {
        int result[4] = {0,0,0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case34)
    {
        int indices[2] = {0,0};
        int shape[4] = {2,1,3,2};
        auto slice0  = Elipsis;
        auto slice1  = 1;
        auto slice2  = 0;
        CAST_ARRAYS(shape);
        CAST_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case34)
    {
        int result[4] = {0,0,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case35)
    {
        int indices[2] = {0,0};
        int shape[4] = {2,1,3,2};
        auto slice0  = 1;
        auto slice1  = Elipsis;
        auto slice2  = 0;
        CAST_ARRAYS(shape);
        CAST_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case35)
    {
        int result[4] = {1,0,0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case36)
    {
        int indices[2] = {0,2};
        int shape[4] = {2,1,3,2};
        auto slice0  = 1;
        auto slice1  = Elipsis;
        auto slice2  = 0;
        CAST_ARRAYS(shape);
        CAST_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case36)
    {
        int result[4] = {1,0,2,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case37)
    {
        int indices[2] = {1,0};
        int shape[3] = {2,3,2};
        auto slice0  = Elipsis;
        auto slice1  = -1;
        auto slice2  = tuple{None,None,-1};
        CAST_ARRAYS(shape);
        CAST_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case37)
    {
        int result[3] = {1,2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case38)
    {
        int indices[2] = {1,1};
        int shape[3] = {2,3,2};
        auto slice0  = Elipsis;
        auto slice1  = -2;
        auto slice2  = tuple{None,None,-1};
        CAST_ARRAYS(shape);
        CAST_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case38)
    {
        int result[3] = {1,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case39)
    {
        int indices[1] = {2};
        int shape[3] = {2,3,2};
        auto slice0  = 0;
        auto slice1  = Elipsis;
        auto slice2  = -1;
        CAST_ARRAYS(shape);
        CAST_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case39)
    {
        int result[3] = {0,2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case40)
    {
        int indices[3] = {0,0,-1};
        int shape[4] = {2,1,3,2};
        auto slice0  = Elipsis;
        auto slice1  = -1;
        CAST_ARRAYS(shape);
        CAST_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case40)
    {
        int result[4] = {0,0,2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case41)
    {
        int indices[2] = {1,0};
        int shape[4] = {2,1,3,2};
        auto slice0  = Elipsis;
        auto slice1  = -1;
        auto slice2  = 0;
        CAST_ARRAYS(shape);
        CAST_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case41)
    {
        int result[4] = {1,0,2,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case42)
    {
        int indices[2] = {0,-1};
        int shape[4] = {2,1,3,2};
        auto slice0  = -1;
        auto slice1  = Elipsis;
        auto slice2  = 0;
        CAST_ARRAYS(shape);
        CAST_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case42)
    {
        int result[4] = {1,0,2,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case43)
    {
        int indices[2] = {0,0};
        int shape[4] = {2,1,3,2};
        auto slice0  = 1;
        auto slice1  = Elipsis;
        auto slice2  = tuple{None,None,-1};
        auto slice3  = 1;
        CAST_ARRAYS(shape);
        CAST_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case43)
    {
        int result[4] = {1,0,2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case44)
    {
        int indices[2] = {0,2};
        int shape[4] = {2,1,3,2};
        auto slice0  = 1;
        auto slice1  = Elipsis;
        auto slice2  = tuple{None,None,1};
        auto slice3  = 1;
        CAST_ARRAYS(shape);
        CAST_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case44)
    {
        int result[4] = {1,0,2,1};
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

TEST_CASE("slice(case24)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case24, indices,   shape, slice0, slice1);
    SLICE_SUBCASE(case24, indices_a, shape_a, slice0, slice1);
    SLICE_SUBCASE(case24, indices_v, shape_v, slice0, slice1);
    SLICE_SUBCASE(case24, indices_f, shape_f, slice0, slice1);
    SLICE_SUBCASE(case24, indices_d, shape_d, slice0, slice1);
    SLICE_SUBCASE(case24, indices_h, shape_h, slice0, slice1);
}

TEST_CASE("slice(case25)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case25, indices,   shape, slice0, slice1);
    SLICE_SUBCASE(case25, indices_a, shape_a, slice0, slice1);
    SLICE_SUBCASE(case25, indices_v, shape_v, slice0, slice1);
    SLICE_SUBCASE(case25, indices_f, shape_f, slice0, slice1);
    SLICE_SUBCASE(case25, indices_d, shape_d, slice0, slice1);
    SLICE_SUBCASE(case25, indices_h, shape_h, slice0, slice1);
}

TEST_CASE("slice(case26)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case26, indices,   shape, slice0, slice1);
    SLICE_SUBCASE(case26, indices_a, shape_a, slice0, slice1);
    SLICE_SUBCASE(case26, indices_v, shape_v, slice0, slice1);
    SLICE_SUBCASE(case26, indices_f, shape_f, slice0, slice1);
    SLICE_SUBCASE(case26, indices_d, shape_d, slice0, slice1);
    SLICE_SUBCASE(case26, indices_h, shape_h, slice0, slice1);
}

TEST_CASE("slice(case27)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case27, indices,   shape, slice0, slice1);
    SLICE_SUBCASE(case27, indices_a, shape_a, slice0, slice1);
    SLICE_SUBCASE(case27, indices_v, shape_v, slice0, slice1);
    SLICE_SUBCASE(case27, indices_f, shape_f, slice0, slice1);
    SLICE_SUBCASE(case27, indices_d, shape_d, slice0, slice1);
    SLICE_SUBCASE(case27, indices_h, shape_h, slice0, slice1);
}

TEST_CASE("slice(case28)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case28, indices,   shape, slice0, slice1);
    SLICE_SUBCASE(case28, indices_a, shape_a, slice0, slice1);
    SLICE_SUBCASE(case28, indices_v, shape_v, slice0, slice1);
    SLICE_SUBCASE(case28, indices_f, shape_f, slice0, slice1);
    SLICE_SUBCASE(case28, indices_d, shape_d, slice0, slice1);
    SLICE_SUBCASE(case28, indices_h, shape_h, slice0, slice1);
}

TEST_CASE("slice(case29)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case29, indices,   shape, slice0, slice1);
    SLICE_SUBCASE(case29, indices_a, shape_a, slice0, slice1);
    SLICE_SUBCASE(case29, indices_v, shape_v, slice0, slice1);
    SLICE_SUBCASE(case29, indices_f, shape_f, slice0, slice1);
    SLICE_SUBCASE(case29, indices_d, shape_d, slice0, slice1);
    SLICE_SUBCASE(case29, indices_h, shape_h, slice0, slice1);
}

TEST_CASE("slice(case30)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case30, indices,   shape, slice0, slice1);
    SLICE_SUBCASE(case30, indices_a, shape_a, slice0, slice1);
    SLICE_SUBCASE(case30, indices_v, shape_v, slice0, slice1);
    SLICE_SUBCASE(case30, indices_f, shape_f, slice0, slice1);
    SLICE_SUBCASE(case30, indices_d, shape_d, slice0, slice1);
    SLICE_SUBCASE(case30, indices_h, shape_h, slice0, slice1);
}

TEST_CASE("slice(case31)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case31, indices,   shape, slice0, slice1);
    SLICE_SUBCASE(case31, indices_a, shape_a, slice0, slice1);
    SLICE_SUBCASE(case31, indices_v, shape_v, slice0, slice1);
    SLICE_SUBCASE(case31, indices_f, shape_f, slice0, slice1);
    SLICE_SUBCASE(case31, indices_d, shape_d, slice0, slice1);
    SLICE_SUBCASE(case31, indices_h, shape_h, slice0, slice1);
}

TEST_CASE("slice(case32)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case32, indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case32, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case32, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case32, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case32, indices_d, shape_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case32, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case33)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case33, indices,   shape, slice0, slice1);
    SLICE_SUBCASE(case33, indices_a, shape_a, slice0, slice1);
    SLICE_SUBCASE(case33, indices_v, shape_v, slice0, slice1);
    SLICE_SUBCASE(case33, indices_f, shape_f, slice0, slice1);
    SLICE_SUBCASE(case33, indices_d, shape_d, slice0, slice1);
    SLICE_SUBCASE(case33, indices_h, shape_h, slice0, slice1);
}

TEST_CASE("slice(case34)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case34, indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case34, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case34, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case34, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case34, indices_d, shape_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case34, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case35)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case35, indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case35, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case35, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case35, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case35, indices_d, shape_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case35, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case36)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case36, indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case36, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case36, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case36, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case36, indices_d, shape_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case36, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case37)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case37, indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case37, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case37, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case37, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case37, indices_d, shape_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case37, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case38)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case38, indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case38, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case38, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case38, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case38, indices_d, shape_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case38, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case39)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case39, indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case39, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case39, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case39, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case39, indices_d, shape_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case39, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case40)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case40, indices,   shape, slice0, slice1);
    SLICE_SUBCASE(case40, indices_a, shape_a, slice0, slice1);
    SLICE_SUBCASE(case40, indices_v, shape_v, slice0, slice1);
    SLICE_SUBCASE(case40, indices_f, shape_f, slice0, slice1);
    SLICE_SUBCASE(case40, indices_d, shape_d, slice0, slice1);
    SLICE_SUBCASE(case40, indices_h, shape_h, slice0, slice1);
}

TEST_CASE("slice(case41)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case41, indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case41, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case41, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case41, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case41, indices_d, shape_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case41, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case42)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case42, indices,   shape, slice0, slice1, slice2);
    SLICE_SUBCASE(case42, indices_a, shape_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case42, indices_v, shape_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case42, indices_f, shape_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case42, indices_d, shape_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case42, indices_h, shape_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case43)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case43, indices,   shape, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case43, indices_a, shape_a, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case43, indices_v, shape_v, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case43, indices_f, shape_f, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case43, indices_d, shape_d, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case43, indices_h, shape_h, slice0, slice1, slice2, slice3);
}

TEST_CASE("slice(case44)" * doctest::test_suite("index::slice"))
{
    SLICE_SUBCASE(case44, indices,   shape, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case44, indices_a, shape_a, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case44, indices_v, shape_v, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case44, indices_f, shape_f, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case44, indices_d, shape_d, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case44, indices_h, shape_h, slice0, slice1, slice2, slice3);
}

NMTOOLS_TESTING_DECLARE_CASE(index, dynamic_slice)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        using slice_t  = nmtools_array<int,2>;
        using slices_t = nmtools_list<slice_t>;
        inline auto indices = nmtools_list{0,0,1};
        inline auto shape   = nmtools_list{2,3,2};
        inline auto slices  = slices_t{{0,2},{0,1},{0,2}};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline auto result = nmtools_list{0,0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        using slice_t  = nmtools_tuple<none_t,none_t>;
        using slices_t = nmtools_list<slice_t>;
        inline auto indices = nmtools_list{1,2,0};
        inline auto shape   = nmtools_list{2,3,2};
        inline auto slices  = slices_t{{None,None},{None,None},{None,None}};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline auto result = nmtools_list{1,2,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        using slice_t  = nmtools_tuple<none_t,int>;
        using slices_t = nmtools_list<slice_t>;
        inline auto indices = nmtools_list{1,1,0};
        inline auto shape   = nmtools_list{2,3,2};
        inline auto slices  = slices_t{{None,2},{None,2},{None,-1}};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline auto result = nmtools_list{1,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        using slice_t  = nmtools_tuple<none_t,none_t,int>;
        using slices_t = nmtools_list<slice_t>;
        inline auto indices = nmtools_list{1,1,0};
        inline auto shape   = nmtools_list{2,3,2};
        inline auto slices  = slices_t{{None,None,-1},{None,None,1},{None,None,1}};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline auto result = nmtools_list{0,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        using slice_t  = nmtools_tuple<none_t,none_t,int>;
        using slices_t = nmtools_list<slice_t>;
        inline auto indices = nmtools_list{0,0,0};
        inline auto shape   = nmtools_list{2,3,2};
        inline auto slices  = slices_t{{None,None,1},{None,None,-1},{None,None,1}};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline auto result = nmtools_list{0,2,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        using slice_t  = nmtools_tuple<int,none_t,int>;
        using slices_t = nmtools_list<slice_t>;
        inline auto indices = nmtools_list{0,0,0};
        inline auto shape   = nmtools_list{2,3,2};
        inline auto slices  = slices_t{{0,None,1},{2,None,-1},{0,None,1}};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline auto result = nmtools_list{0,2,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        using slice_t  = nmtools_either<nmtools_tuple<none_t,none_t>,nmtools_tuple<int,int>>;
        using slices_t = nmtools_list<slice_t>;
        inline auto indices = nmtools_list{0,0,1};
        inline auto shape   = nmtools_list{2,3,2};
        inline auto slices  = slices_t{nmtools_tuple{None,None},nmtools_tuple{0,1},nmtools_tuple{None,None}};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline auto result = nmtools_list{0,0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        using slice_t  = nmtools_either<nmtools_tuple<none_t,none_t>,nmtools_tuple<int,int>>;
        using slices_t = nmtools_list<slice_t>;
        inline auto indices = nmtools_list{0,0,1};
        inline auto shape   = nmtools_list{2,3,2};
        inline auto slices  = slices_t{nmtools_tuple{1,2},nmtools_tuple{0,1},nmtools_tuple{None,None}};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline auto result = nmtools_list{1,0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        using slice_t  = nmtools_either<nmtools_tuple<none_t,none_t>,int>;
        using slices_t = nmtools_list<slice_t>;
        inline auto indices = nmtools_list{1};
        inline auto shape   = nmtools_list{2,3,2};
        inline auto slices  = slices_t{nmtools_tuple{None,None},0,0};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline auto result = nmtools_list{1,0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        using slice_t  = nmtools_either<nmtools_tuple<none_t,none_t,int>,nmtools_tuple<int,int>>;
        using slices_t = nmtools_list<slice_t>;
        inline auto indices = nmtools_list{0,0,1};
        inline auto shape   = nmtools_list{2,3,2};
        inline auto slices  = slices_t{
            nmtools_tuple{None,None,-1},
            nmtools_tuple{0,1},
            nmtools_tuple{None,None,-1}
        };
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline auto result = nmtools_list{1,0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        using slice_t  = nmtools_either<nmtools_tuple<none_t,none_t,int>,nmtools_tuple<none_t,none_t>>;
        using slices_t = nmtools_list<slice_t>;
        inline auto indices = nmtools_list{1,1};
        inline auto shape   = nmtools_list{4,2};
        inline auto slices  = slices_t{nmtools_tuple{None,None,2},nmtools_tuple{None,None}};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        inline auto result = nmtools_list{2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        using slice_t  = nmtools_either<nmtools_tuple<none_t,none_t,int>,nmtools_tuple<none_t,none_t>>;
        using slices_t = nmtools_list<slice_t>;
        inline auto indices = nmtools_list{1,1};
        inline auto shape   = nmtools_list{4,2};
        inline auto slices  = slices_t{nmtools_tuple{None,None,-2},nmtools_tuple{None,None}};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        inline auto result = nmtools_list{1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case13)
    {
        using slice_t  = nmtools_either<elipsis_t,nmtools_tuple<none_t,none_t>>;
        using slices_t = nmtools_list<slice_t>;
        inline auto indices = nmtools_list{0,1,0};
        inline auto shape   = nmtools_list{2,3,2};
        inline auto slices  = slices_t{Elipsis,nmtools_tuple{None,None}};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case13)
    {
        inline auto result = nmtools_list{0,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case14)
    {
        using slice_t  = nmtools_either<elipsis_t,nmtools_tuple<none_t,int>>;
        using slices_t = nmtools_list<slice_t>;
        inline auto indices = nmtools_list{0,1,0};
        inline auto shape   = nmtools_list{2,3,2};
        inline auto slices  = slices_t{Elipsis,nmtools_tuple{None,-1}};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case14)
    {
        inline auto result = nmtools_list{0,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case15)
    {
        using slice_t  = nmtools_either<elipsis_t,nmtools_tuple<int,none_t>>;
        using slices_t = nmtools_list<slice_t>;
        inline auto indices = nmtools_list{0,1,0};
        inline auto shape   = nmtools_list{2,3,2};
        inline auto slices  = slices_t{Elipsis,nmtools_tuple{0,None}};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case15)
    {
        inline auto result = nmtools_list{0,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case16)
    {
        using slice_t  = nmtools_either<elipsis_t,nmtools_tuple<int,int>>;
        using slices_t = nmtools_list<slice_t>;
        inline auto indices = nmtools_list{0,1,0};
        inline auto shape   = nmtools_list{2,3,2};
        inline auto slices  = slices_t{nmtools_tuple{0,-1},Elipsis};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case16)
    {
        inline auto result = nmtools_list{0,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case17)
    {
        using slice_t  = nmtools_either<elipsis_t,int>;
        using slices_t = nmtools_list<slice_t>;
        inline auto indices = nmtools_list{1,0};
        inline auto shape   = nmtools_list{2,3,2};
        inline auto slices  = slices_t{0,Elipsis};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case17)
    {
        inline auto result = nmtools_list{0,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case18)
    {
        using slice_t  = nmtools_either<elipsis_t,int>;
        using slices_t = nmtools_list<slice_t>;
        inline auto indices = nmtools_list{1,1};
        inline auto shape   = nmtools_list{2,3,2};
        inline auto slices  = slices_t{0,Elipsis};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case18)
    {
        inline auto result = nmtools_list{0,1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case19)
    {
        using slice_t  = nmtools_either<elipsis_t,int>;
        using slices_t = nmtools_list<slice_t>;
        inline auto indices = nmtools_list{1,0};
        inline auto shape   = nmtools_list{2,3,2};
        inline auto slices  = slices_t{Elipsis,0};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case19)
    {
        inline auto result = nmtools_list{1,0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case20)
    {
        using slice_t  = nmtools_either<elipsis_t,int>;
        using slices_t = nmtools_list<slice_t>;
        inline auto indices = nmtools_list{2};
        inline auto shape   = nmtools_list{2,3,2};
        inline auto slices  = slices_t{0,Elipsis,0};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case20)
    {
        inline auto result = nmtools_list{0,2,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case21)
    {
        using slice_t  = nmtools_either<elipsis_t,int>;
        using slices_t = nmtools_list<slice_t>;
        inline auto indices = nmtools_list{0,0,0};
        inline auto shape   = nmtools_list{2,1,3,2};
        inline auto slices  = slices_t{Elipsis,1};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case21)
    {
        inline auto result = nmtools_list{0,0,0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case22)
    {
        using slice_t  = nmtools_either<elipsis_t,int>;
        using slices_t = nmtools_list<slice_t>;
        inline auto indices = nmtools_list{0,0,0};
        inline auto shape   = nmtools_list{2,1,3,2};
        inline auto slices  = slices_t{1,Elipsis};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case22)
    {
        inline auto result = nmtools_list{1,0,0,0};
    }
}

#define RUN_dynamic_slice_impl(...) \
nm::index::dynamic_slice(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs dynamic_slice fn to callable lambda
#define RUN_dynamic_slice(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("dynamic_slice-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_dynamic_slice_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_dynamic_slice(case_name, ...) \
RUN_dynamic_slice_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define DYNAMIC_SLICE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(index, dynamic_slice, case_name); \
    using namespace args; \
    auto result = RUN_dynamic_slice(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("dynamic_slice(case1)" * doctest::test_suite("index::dynamic_slice"))
{
    DYNAMIC_SLICE_SUBCASE( case1, indices, shape, slices );
}

TEST_CASE("dynamic_slice(case2)" * doctest::test_suite("index::dynamic_slice"))
{
    DYNAMIC_SLICE_SUBCASE( case2, indices, shape, slices );
}

TEST_CASE("dynamic_slice(case3)" * doctest::test_suite("index::dynamic_slice"))
{
    DYNAMIC_SLICE_SUBCASE( case3, indices, shape, slices );
}

TEST_CASE("dynamic_slice(case4)" * doctest::test_suite("index::dynamic_slice"))
{
    DYNAMIC_SLICE_SUBCASE( case4, indices, shape, slices );
}

TEST_CASE("dynamic_slice(case5)" * doctest::test_suite("index::dynamic_slice"))
{
    DYNAMIC_SLICE_SUBCASE( case5, indices, shape, slices );
}

TEST_CASE("dynamic_slice(case6)" * doctest::test_suite("index::dynamic_slice"))
{
    DYNAMIC_SLICE_SUBCASE( case6, indices, shape, slices );
}

TEST_CASE("dynamic_slice(case7)" * doctest::test_suite("index::dynamic_slice"))
{
    DYNAMIC_SLICE_SUBCASE( case7, indices, shape, slices );
}

TEST_CASE("dynamic_slice(case8)" * doctest::test_suite("index::dynamic_slice"))
{
    DYNAMIC_SLICE_SUBCASE( case8, indices, shape, slices );
}

TEST_CASE("dynamic_slice(case9)" * doctest::test_suite("index::dynamic_slice"))
{
    DYNAMIC_SLICE_SUBCASE( case9, indices, shape, slices );
}

TEST_CASE("dynamic_slice(case10)" * doctest::test_suite("index::dynamic_slice"))
{
    DYNAMIC_SLICE_SUBCASE( case10, indices, shape, slices );
}

TEST_CASE("dynamic_slice(case11)" * doctest::test_suite("index::dynamic_slice"))
{
    DYNAMIC_SLICE_SUBCASE( case11, indices, shape, slices );
}

TEST_CASE("dynamic_slice(case12)" * doctest::test_suite("index::dynamic_slice"))
{
    DYNAMIC_SLICE_SUBCASE( case12, indices, shape, slices );
}

TEST_CASE("dynamic_slice(case13)" * doctest::test_suite("index::dynamic_slice"))
{
    DYNAMIC_SLICE_SUBCASE( case13, indices, shape, slices );
}

TEST_CASE("dynamic_slice(case14)" * doctest::test_suite("index::dynamic_slice"))
{
    DYNAMIC_SLICE_SUBCASE( case14, indices, shape, slices );
}

TEST_CASE("dynamic_slice(case15)" * doctest::test_suite("index::dynamic_slice"))
{
    DYNAMIC_SLICE_SUBCASE( case15, indices, shape, slices );
}

TEST_CASE("dynamic_slice(case16)" * doctest::test_suite("index::dynamic_slice"))
{
    DYNAMIC_SLICE_SUBCASE( case16, indices, shape, slices );
}

TEST_CASE("dynamic_slice(case17)" * doctest::test_suite("index::dynamic_slice"))
{
    DYNAMIC_SLICE_SUBCASE( case17, indices, shape, slices );
}

TEST_CASE("dynamic_slice(case18)" * doctest::test_suite("index::dynamic_slice"))
{
    DYNAMIC_SLICE_SUBCASE( case18, indices, shape, slices );
}

TEST_CASE("dynamic_slice(case19)" * doctest::test_suite("index::dynamic_slice"))
{
    DYNAMIC_SLICE_SUBCASE( case19, indices, shape, slices );
}

TEST_CASE("dynamic_slice(case20)" * doctest::test_suite("index::dynamic_slice"))
{
    DYNAMIC_SLICE_SUBCASE( case20, indices, shape, slices );
}

TEST_CASE("dynamic_slice(case21)" * doctest::test_suite("index::dynamic_slice"))
{
    DYNAMIC_SLICE_SUBCASE( case21, indices, shape, slices );
}

TEST_CASE("dynamic_slice(case22)" * doctest::test_suite("index::dynamic_slice"))
{
    DYNAMIC_SLICE_SUBCASE( case22, indices, shape, slices );
}