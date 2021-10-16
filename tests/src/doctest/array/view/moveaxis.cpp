#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/testing/testing.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

// TODO: add index vector kind, do not use nested vec
#ifndef PLATFORMIO
#define CAST_ARRAYS(name) \
inline auto name##_a = cast(name, kind::nested_arr); \
inline auto name##_v = cast(name, kind::nested_vec); \
inline auto name##_f = cast(name, kind::fixed); \
inline auto name##_d = cast(name, kind::dynamic); \
inline auto name##_h = cast(name, kind::hybrid);
#else
#define CAST_ARRAYS(name) \
inline auto name##_a = cast(name, kind::nested_arr); \
inline auto name##_f = cast(name, kind::fixed); \
inline auto name##_h = cast(name, kind::hybrid);
#endif // PLATFORMIO

NMTOOLS_TESTING_DECLARE_CASE(detail, moveaxis_to_transpose)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int shape[3] = {1,2,3};
        inline int source = 0;
        inline int destination = 1;
        CAST_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[3] = {1,0,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int shape[3] = {1,2,3};
        inline int source = 1;
        inline int destination = 0;
        CAST_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[3] = {1,0,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int shape[3] = {1,2,3};
        inline int source = 0;
        inline int destination = -2;
        CAST_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[3] = {1,0,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int shape[3] = {1,2,3};
        inline int source = 0;
        inline int destination = 2;
        CAST_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[3] = {1,2,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int shape[3] = {1,2,3};
        inline int source = 0;
        inline int destination = -1;
        CAST_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int result[3] = {1,2,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int shape[3] = {1,2,3};
        inline int source = -1;
        inline int destination = 0;
        CAST_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int result[3] = {2,0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int shape[3] = {1,2,3};
        inline int source[1] = {-1};
        inline int destination[1] = {0};
        CAST_ARRAYS(shape);
        CAST_ARRAYS(source);
        CAST_ARRAYS(destination);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int result[3] = {2,0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline int shape[4] = {1,2,3,4};
        inline int source[1] = {0};
        inline int destination[1] = {-1};
        CAST_ARRAYS(shape);
        CAST_ARRAYS(source);
        CAST_ARRAYS(destination);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline int result[4] = {1,2,3,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        inline int shape[4] = {1,2,3,4};
        inline int source[2] = {0,1};
        inline int destination[2] = {-1,2};
        CAST_ARRAYS(shape);
        CAST_ARRAYS(source);
        CAST_ARRAYS(destination);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline int result[4] = {2,3,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        inline int shape[4] = {1,2,3,4};
        inline int source[2] = {0,1};
        inline int destination[2] = {3,2};
        CAST_ARRAYS(shape);
        CAST_ARRAYS(source);
        CAST_ARRAYS(destination);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline int result[4] = {2,3,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        inline int shape[4] = {1,2,3,4};
        inline int source = 0;
        inline int destination = -1;
        CAST_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        inline int result[4] = {1,2,3,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        inline int shape[4] = {1,2,3,4};
        inline int source = 0;
        inline int destination = -2;
        CAST_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        inline int result[4] = {1,2,0,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case13)
    {
        inline int shape[4] = {1,2,3,4};
        inline int source = 2;
        inline int destination = 3;
        CAST_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case13)
    {
        inline int result[4] = {0,1,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case14)
    {
        inline int shape[4] = {1,2,3,4};
        inline int source[1] = {2};
        inline int destination[1] = {1};
        CAST_ARRAYS(shape);
        CAST_ARRAYS(source);
        CAST_ARRAYS(destination);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case14)
    {
        inline int result[4] = {0,2,1,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case15)
    {
        inline int shape[4] = {1,2,3,4};
        // inline int source[2] = {2,0};
        // inline int destination[2] = {1,2};
        inline int source[2] = {2,1};
        inline int destination[2] = {1,0};
        CAST_ARRAYS(shape);
        CAST_ARRAYS(source);
        CAST_ARRAYS(destination);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case15)
    {
        inline int result[4] = {1,2,0,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case16)
    {
        inline int shape[4] = {1,2,3,4};
        inline int source[2] = {2,0};
        inline int destination[2] = {1,2};
        CAST_ARRAYS(shape);
        CAST_ARRAYS(source);
        CAST_ARRAYS(destination);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case16)
    {
        inline int result[4] = {1,2,0,3};
    }
}

#include "nmtools/array/view/moveaxis.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;

#define RUN_moveaxis_to_transpose_impl(...) \
nm::view::detail::moveaxis_to_transpose(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs moveaxis_to_transpose fn to callable lambda
#define RUN_moveaxis_to_transpose(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("view::detail::moveaxis_to_transpose-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_moveaxis_to_transpose_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_moveaxis_to_transpose(case_name, ...) \
RUN_moveaxis_to_transpose_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define MOVEAXIS_TO_TRANSPOSE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(detail, moveaxis_to_transpose, case_name); \
    using namespace args; \
    auto result = RUN_moveaxis_to_transpose(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("moveaxis_to_transpose(case1)" * doctest::test_suite("view::detail::moveaxis_to_transpose"))
{
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case1, shape, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case1, shape_a, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case1, shape_v, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case1, shape_f, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case1, shape_h, source, destination );
}

TEST_CASE("moveaxis_to_transpose(case2)" * doctest::test_suite("view::detail::moveaxis_to_transpose"))
{
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case2, shape, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case2, shape_a, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case2, shape_v, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case2, shape_f, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case2, shape_h, source, destination );
}

TEST_CASE("moveaxis_to_transpose(case3)" * doctest::test_suite("view::detail::moveaxis_to_transpose"))
{
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case3, shape, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case3, shape_a, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case3, shape_v, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case3, shape_f, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case3, shape_h, source, destination );
}

TEST_CASE("moveaxis_to_transpose(case4)" * doctest::test_suite("view::detail::moveaxis_to_transpose"))
{
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case4, shape, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case4, shape_a, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case4, shape_v, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case4, shape_f, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case4, shape_h, source, destination );
}

TEST_CASE("moveaxis_to_transpose(case5)" * doctest::test_suite("view::detail::moveaxis_to_transpose"))
{
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case5, shape, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case5, shape_a, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case5, shape_v, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case5, shape_f, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case5, shape_h, source, destination );
}

TEST_CASE("moveaxis_to_transpose(case6)" * doctest::test_suite("view::detail::moveaxis_to_transpose"))
{
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case6, shape, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case6, shape_a, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case6, shape_v, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case6, shape_f, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case6, shape_h, source, destination );
}

TEST_CASE("moveaxis_to_transpose(case7)" * doctest::test_suite("view::detail::moveaxis_to_transpose"))
{
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case7, shape, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case7, shape_a, source_a, destination_a );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case7, shape_v, source_v, destination_v );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case7, shape_f, source_f, destination_f );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case7, shape_h, source_h, destination_h );
}

TEST_CASE("moveaxis_to_transpose(case8)" * doctest::test_suite("view::detail::moveaxis_to_transpose"))
{
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case8, shape, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case8, shape_a, source_a, destination_a );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case8, shape_v, source_v, destination_v );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case8, shape_f, source_f, destination_f );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case8, shape_h, source_h, destination_h );
}

TEST_CASE("moveaxis_to_transpose(case9)" * doctest::test_suite("view::detail::moveaxis_to_transpose"))
{
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case9, shape, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case9, shape_a, source_a, destination_a );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case9, shape_v, source_v, destination_v );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case9, shape_f, source_f, destination_f );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case9, shape_h, source_h, destination_h );
}

TEST_CASE("moveaxis_to_transpose(case10)" * doctest::test_suite("view::detail::moveaxis_to_transpose"))
{
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case10, shape, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case10, shape_a, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case10, shape_v, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case10, shape_f, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case10, shape_h, source, destination );
}

TEST_CASE("moveaxis_to_transpose(case11)" * doctest::test_suite("view::detail::moveaxis_to_transpose"))
{
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case11, shape, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case11, shape_a, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case11, shape_v, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case11, shape_f, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case11, shape_h, source, destination );
}

TEST_CASE("moveaxis_to_transpose(case12)" * doctest::test_suite("view::detail::moveaxis_to_transpose"))
{
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case12, shape, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case12, shape_a, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case12, shape_v, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case12, shape_f, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case12, shape_h, source, destination );
}

TEST_CASE("moveaxis_to_transpose(case13)" * doctest::test_suite("view::detail::moveaxis_to_transpose"))
{
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case13, shape, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case13, shape_a, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case13, shape_v, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case13, shape_f, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case13, shape_h, source, destination );
}

TEST_CASE("moveaxis_to_transpose(case14)" * doctest::test_suite("view::detail::moveaxis_to_transpose"))
{
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case14, shape, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case14, shape_a, source_a, destination_a );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case14, shape_v, source_v, destination_v );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case14, shape_f, source_f, destination_f );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case14, shape_h, source_h, destination_h );
}

TEST_CASE("moveaxis_to_transpose(case15)" * doctest::test_suite("view::detail::moveaxis_to_transpose"))
{
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case15, shape, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case15, shape_a, source_a, destination_a );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case15, shape_v, source_v, destination_v );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case15, shape_f, source_f, destination_f );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case15, shape_h, source_h, destination_h );
}

TEST_CASE("moveaxis_to_transpose(case16)" * doctest::test_suite("view::detail::moveaxis_to_transpose"))
{
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case16, shape, source, destination );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case16, shape_a, source_a, destination_a );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case16, shape_v, source_v, destination_v );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case16, shape_f, source_f, destination_f );
    MOVEAXIS_TO_TRANSPOSE_SUBCASE( case16, shape_h, source_h, destination_h );
}

#include "nmtools/array/view/moveaxis.hpp"
#include "nmtools/testing/data/array/moveaxis.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;

#define RUN_moveaxis_impl(...) \
nm::view::moveaxis(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs moveaxis fn to callable lambda
#define RUN_moveaxis(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("view::moveaxis-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_moveaxis_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_moveaxis(case_name, ...) \
RUN_moveaxis_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define MOVEAXIS_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, moveaxis, case_name); \
    using namespace args; \
    auto result = RUN_moveaxis(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("moveaxis(case1)" * doctest::test_suite("view::moveaxis"))
{
    MOVEAXIS_SUBCASE( case1, a, source, destination );
    MOVEAXIS_SUBCASE( case1, a_a, source, destination );
    MOVEAXIS_SUBCASE( case1, a_v, source, destination );
    MOVEAXIS_SUBCASE( case1, a_f, source, destination );
    MOVEAXIS_SUBCASE( case1, a_d, source, destination );
    MOVEAXIS_SUBCASE( case1, a_h, source, destination );
}

TEST_CASE("moveaxis(case2)" * doctest::test_suite("view::moveaxis"))
{
    MOVEAXIS_SUBCASE( case2, a, source, destination );
    MOVEAXIS_SUBCASE( case2, a_a, source, destination );
    MOVEAXIS_SUBCASE( case2, a_v, source, destination );
    MOVEAXIS_SUBCASE( case2, a_f, source, destination );
    MOVEAXIS_SUBCASE( case2, a_d, source, destination );
    MOVEAXIS_SUBCASE( case2, a_h, source, destination );
}

TEST_CASE("moveaxis(case3)" * doctest::test_suite("view::moveaxis"))
{
    MOVEAXIS_SUBCASE( case3, a, source, destination );
    MOVEAXIS_SUBCASE( case3, a_a, source, destination );
    MOVEAXIS_SUBCASE( case3, a_v, source, destination );
    MOVEAXIS_SUBCASE( case3, a_f, source, destination );
    MOVEAXIS_SUBCASE( case3, a_d, source, destination );
    MOVEAXIS_SUBCASE( case3, a_h, source, destination );
}

TEST_CASE("moveaxis(case4)" * doctest::test_suite("view::moveaxis"))
{
    MOVEAXIS_SUBCASE( case4, a, source, destination );
    MOVEAXIS_SUBCASE( case4, a_a, source, destination );
    MOVEAXIS_SUBCASE( case4, a_v, source, destination );
    MOVEAXIS_SUBCASE( case4, a_f, source, destination );
    MOVEAXIS_SUBCASE( case4, a_d, source, destination );
    MOVEAXIS_SUBCASE( case4, a_h, source, destination );
}

TEST_CASE("moveaxis(case5)" * doctest::test_suite("view::moveaxis"))
{
    MOVEAXIS_SUBCASE( case5, a, source, destination );
    MOVEAXIS_SUBCASE( case5, a_a, source, destination );
    MOVEAXIS_SUBCASE( case5, a_v, source, destination );
    MOVEAXIS_SUBCASE( case5, a_f, source, destination );
    MOVEAXIS_SUBCASE( case5, a_d, source, destination );
    MOVEAXIS_SUBCASE( case5, a_h, source, destination );
}

TEST_CASE("moveaxis(case6)" * doctest::test_suite("view::moveaxis"))
{
    MOVEAXIS_SUBCASE( case6, a, source, destination );
    MOVEAXIS_SUBCASE( case6, a_a, source, destination );
    MOVEAXIS_SUBCASE( case6, a_v, source, destination );
    MOVEAXIS_SUBCASE( case6, a_f, source, destination );
    MOVEAXIS_SUBCASE( case6, a_d, source, destination );
    MOVEAXIS_SUBCASE( case6, a_h, source, destination );
}

TEST_CASE("moveaxis(case7)" * doctest::test_suite("view::moveaxis"))
{
    MOVEAXIS_SUBCASE( case7, a, source, destination );
    MOVEAXIS_SUBCASE( case7, a_a, source, destination );
    MOVEAXIS_SUBCASE( case7, a_v, source, destination );
    MOVEAXIS_SUBCASE( case7, a_f, source, destination );
    MOVEAXIS_SUBCASE( case7, a_d, source, destination );
    MOVEAXIS_SUBCASE( case7, a_h, source, destination );
}

TEST_CASE("moveaxis(case8)" * doctest::test_suite("view::moveaxis"))
{
    MOVEAXIS_SUBCASE( case8, a, source, destination );
    MOVEAXIS_SUBCASE( case8, a_a, source, destination );
    MOVEAXIS_SUBCASE( case8, a_v, source, destination );
    MOVEAXIS_SUBCASE( case8, a_f, source, destination );
    MOVEAXIS_SUBCASE( case8, a_d, source, destination );
    MOVEAXIS_SUBCASE( case8, a_h, source, destination );
}

TEST_CASE("moveaxis(case9)" * doctest::test_suite("view::moveaxis"))
{
    MOVEAXIS_SUBCASE( case9, a, source, destination );
    MOVEAXIS_SUBCASE( case9, a_a, source, destination );
    MOVEAXIS_SUBCASE( case9, a_v, source, destination );
    MOVEAXIS_SUBCASE( case9, a_f, source, destination );
    MOVEAXIS_SUBCASE( case9, a_d, source, destination );
    MOVEAXIS_SUBCASE( case9, a_h, source, destination );
}