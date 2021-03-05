#include "nmtools/array/view/compress.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/constants.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

#define CAST_ARRAYS(name) \
auto name##_a = cast(name, kind::nested_arr); \
auto name##_v = cast(name, kind::nested_vec); \
auto name##_f = cast(name, kind::fixed); \
auto name##_d = cast(name, kind::dynamic); \
auto name##_h = cast(name, kind::hybrid); \

NMTOOLS_TESTING_DECLARE_CASE(view, compress)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int condition[2] = {0,1};
        int array[3][2] = {
            {1,2},
            {3,4},
            {5,6},
        };
        int axis = 0;
        CAST_ARRAYS(condition)
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int shape[2] = {1,2};
        int result[1][2] = {
            {3,4}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        int condition[2] = {0,1};
        int array[3][2] = {
            {1,2},
            {3,4},
            {5,6},
        };
        int axis = 1;
        CAST_ARRAYS(condition)
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        int shape[2] = {3,1};
        int result[3][1] = {
            {2},
            {4},
            {6},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        bool condition[3] = {false,true,true};
        int array[3][2] = {
            {1,2},
            {3,4},
            {5,6},
        };
        int axis = 0;
        CAST_ARRAYS(condition)
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        int shape[2] = {2,2};
        int result[2][2] = {
            {3,4},
            {5,6},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        bool condition[5] = {false,true,true,false,true};
        int array[3][2] = {
            {1,2},
            {3,4},
            {5,6},
        };
        auto axis = None;
        CAST_ARRAYS(condition)
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        int shape[1] = {3};
        int result[3] = {2,3,5};
    }
}

#define RUN_compress_impl(...) \
nm::view::compress(__VA_ARGS__);

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
    NMTOOLS_TESTING_DECLARE_NS(view, compress, case_name); \
    using namespace args; \
    auto result = RUN_compress(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("compress(case1)" * doctest::test_suite("view::compress"))
{
    COMPRESS_SUBCASE( case1,   condition,   array, axis );
    COMPRESS_SUBCASE( case1, condition_a, array_a, axis );
    COMPRESS_SUBCASE( case1, condition_v, array_v, axis );
    COMPRESS_SUBCASE( case1, condition_f, array_f, axis );
    COMPRESS_SUBCASE( case1, condition_d, array_d, axis );
    COMPRESS_SUBCASE( case1, condition_h, array_h, axis );
}

TEST_CASE("compress(case2)" * doctest::test_suite("view::compress"))
{
    COMPRESS_SUBCASE( case2,   condition,   array, axis );
    COMPRESS_SUBCASE( case2, condition_a, array_a, axis );
    COMPRESS_SUBCASE( case2, condition_v, array_v, axis );
    COMPRESS_SUBCASE( case2, condition_f, array_f, axis );
    COMPRESS_SUBCASE( case2, condition_d, array_d, axis );
    COMPRESS_SUBCASE( case2, condition_h, array_h, axis );
}

TEST_CASE("compress(case3)" * doctest::test_suite("view::compress"))
{
    COMPRESS_SUBCASE( case3,   condition,   array, axis );
    COMPRESS_SUBCASE( case3, condition_a, array_a, axis );
    COMPRESS_SUBCASE( case3, condition_v, array_v, axis );
    COMPRESS_SUBCASE( case3, condition_f, array_f, axis );
    COMPRESS_SUBCASE( case3, condition_d, array_d, axis );
    COMPRESS_SUBCASE( case3, condition_h, array_h, axis );
}

TEST_CASE("compress(case4)" * doctest::test_suite("view::compress"))
{
    COMPRESS_SUBCASE( case4,   condition,   array, axis );
    COMPRESS_SUBCASE( case4, condition_a, array_a, axis );
    COMPRESS_SUBCASE( case4, condition_v, array_v, axis );
    COMPRESS_SUBCASE( case4, condition_f, array_f, axis );
    COMPRESS_SUBCASE( case4, condition_d, array_d, axis );
    COMPRESS_SUBCASE( case4, condition_h, array_h, axis );
}