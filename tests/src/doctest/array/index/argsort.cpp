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

NMTOOLS_TESTING_DECLARE_CASE(index, argsort)
{
    using namespace literals;
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int array[4] = {0,1,2,3};
        CAST_ARRAYS(array);
        inline auto array_ct = std::tuple{0_ct,1_ct,2_ct,3_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[4] = {0,1,2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int array[4] = {1,0,2,3};
        CAST_ARRAYS(array);
        inline auto array_ct = std::tuple{1_ct,0_ct,2_ct,3_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[4] = {1,0,2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int array[4] = {2,1,0,3};
        CAST_ARRAYS(array);
        inline auto array_ct = std::tuple{2_ct,1_ct,0_ct,3_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[4] = {2,1,0,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int array[4] = {1,2,3,4};
        CAST_ARRAYS(array);
        inline auto array_ct = std::tuple{1_ct,2_ct,3_ct,4_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[4] = {0,1,2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int array[4] = {2,1,3,4};
        CAST_ARRAYS(array);
        inline auto array_ct = std::tuple{2_ct,1_ct,3_ct,4_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int result[4] = {1,0,2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int array[4] = {3,2,1,4};
        CAST_ARRAYS(array);
        inline auto array_ct = std::tuple{3_ct,2_ct,1_ct,4_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int result[4] = {2,1,0,3};
    }
}

#undef CAST_ARRAYS

#include "nmtools/array/index/argsort.hpp"
#include "nmtools/testing/doctest.hpp"

#define RUN_impl(...) \
nm::index::argsort(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs argsort fn to callable lambda
#define RUN_argsort(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("index::argsort-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_argsort(case_name, ...) \
RUN_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define ARGSORT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(index, argsort, case_name); \
    using namespace args; \
    auto result = RUN_argsort(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
} \

TEST_CASE("argsort(case1)" * doctest::test_suite("index::argsort"))
{
    ARGSORT_SUBCASE( case1, array );
    ARGSORT_SUBCASE( case1, array_a );
    ARGSORT_SUBCASE( case1, array_v );
    ARGSORT_SUBCASE( case1, array_f );
    ARGSORT_SUBCASE( case1, array_h );
    ARGSORT_SUBCASE( case1, array_ct );
}

TEST_CASE("argsort(case2)" * doctest::test_suite("index::argsort"))
{
    ARGSORT_SUBCASE( case2, array );
    ARGSORT_SUBCASE( case2, array_a );
    ARGSORT_SUBCASE( case2, array_v );
    ARGSORT_SUBCASE( case2, array_f );
    ARGSORT_SUBCASE( case2, array_h );
    ARGSORT_SUBCASE( case2, array_ct );
}

TEST_CASE("argsort(case3)" * doctest::test_suite("index::argsort"))
{
    ARGSORT_SUBCASE( case3, array );
    ARGSORT_SUBCASE( case3, array_a );
    ARGSORT_SUBCASE( case3, array_v );
    ARGSORT_SUBCASE( case3, array_f );
    ARGSORT_SUBCASE( case3, array_h );
    ARGSORT_SUBCASE( case3, array_ct );
}

TEST_CASE("argsort(case4)" * doctest::test_suite("index::argsort"))
{
    ARGSORT_SUBCASE( case4, array );
    ARGSORT_SUBCASE( case4, array_a );
    ARGSORT_SUBCASE( case4, array_v );
    ARGSORT_SUBCASE( case4, array_f );
    ARGSORT_SUBCASE( case4, array_h );
    ARGSORT_SUBCASE( case4, array_ct );
}

TEST_CASE("argsort(case5)" * doctest::test_suite("index::argsort"))
{
    ARGSORT_SUBCASE( case5, array );
    ARGSORT_SUBCASE( case5, array_a );
    ARGSORT_SUBCASE( case5, array_v );
    ARGSORT_SUBCASE( case5, array_f );
    ARGSORT_SUBCASE( case5, array_h );
    ARGSORT_SUBCASE( case5, array_ct );
}

TEST_CASE("argsort(case6)" * doctest::test_suite("index::argsort"))
{
    ARGSORT_SUBCASE( case6, array );
    ARGSORT_SUBCASE( case6, array_a );
    ARGSORT_SUBCASE( case6, array_v );
    ARGSORT_SUBCASE( case6, array_f );
    ARGSORT_SUBCASE( case6, array_h );
    ARGSORT_SUBCASE( case6, array_ct );
}