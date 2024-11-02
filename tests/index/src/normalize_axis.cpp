#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

using namespace nmtools::literals;

NMTOOLS_TESTING_DECLARE_CASE(index, normalize_axis)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int axis[3] = {-1,-2,-3};
        inline int ndim = 3;
        NMTOOLS_CAST_INDEX_ARRAYS(axis);
        inline auto axis_ct = nmtools_tuple{"-1"_ct,"-2"_ct,"-3"_ct};
        inline auto ndim_ct = 3_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[3] = {2,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int axis[3] = {-1,-2,3};
        inline int ndim = 3;
        NMTOOLS_CAST_INDEX_ARRAYS(axis);
        inline auto axis_ct = nmtools_tuple{"-1"_ct,"-2"_ct,3_ct};
        inline auto ndim_ct = 3_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        // AxisError: axis 3 is out of bounds for array of dimension 3
        inline auto result = meta::Nothing;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int axis[3] = {-1,2,-3};
        inline int ndim = 3;
        NMTOOLS_CAST_INDEX_ARRAYS(axis);
        inline auto axis_ct = nmtools_tuple{"-1"_ct,2_ct,"-3"_ct};
        inline auto ndim_ct = 3_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[3] = {2,2,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int axis = -3;
        inline int ndim = 3;
        inline auto axis_ct = "-3"_ct;
        inline auto ndim_ct = 3_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result = 0;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int axis = 3;
        inline int ndim = 3;
        inline auto axis_ct = 3_ct;
        inline auto ndim_ct = 3_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline auto result = meta::Nothing;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline auto axis = 0ul;
        inline int ndim = 3;
        inline auto axis_ct = 0_ct;
        inline auto ndim_ct = 3_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int result = 0;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline auto axis = 0ul;
        inline auto ndim = 3ul;
        inline auto axis_ct = 0_ct;
        inline auto ndim_ct = 3_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int result = 0;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline auto axis = 1ul;
        inline auto ndim = 3ul;
        inline auto axis_ct = 1_ct;
        inline auto ndim_ct = 3_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline int result = 1;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        inline auto axis = 2ul;
        inline auto ndim = 3ul;
        inline auto axis_ct = 2_ct;
        inline auto ndim_ct = 3_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline int result = 2;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        inline auto axis = 3ul;
        inline auto ndim = 3ul;
        inline auto axis_ct = 3_ct;
        inline auto ndim_ct = 3_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline auto result = meta::Nothing;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        inline int axis = 0;
        inline int ndim = 3;
        inline auto axis_ct = 0_ct;
        inline auto ndim_ct = 3_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        inline int result = 0;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        inline int axis = 1;
        inline int ndim = 3;
        inline auto axis_ct = 1_ct;
        inline auto ndim_ct = 3_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        inline int result = 1;
    }
}

#include "nmtools/array/index/normalize_axis.hpp"
#include "nmtools/testing/doctest.hpp"

#define RUN_impl(...) \
nm::index::normalize_axis(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs normalize_axis fn to callable lambda
#define RUN_normalize_axis(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("normalize_axis-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_normalize_axis(case_name, ...) \
RUN_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define NORMALIZE_AXIS_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index, normalize_axis, case_name); \
    using namespace args; \
    auto result = RUN_normalize_axis(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
} \


TEST_CASE("normalize_axis(case1)" * doctest::test_suite("index::normalize_axis"))
{
    NORMALIZE_AXIS_SUBCASE( case1, axis, ndim );
    NORMALIZE_AXIS_SUBCASE( case1, axis_a, ndim );
    NORMALIZE_AXIS_SUBCASE( case1, axis_v, ndim );
    NORMALIZE_AXIS_SUBCASE( case1, axis_f, ndim );
    NORMALIZE_AXIS_SUBCASE( case1, axis_h, ndim );

    NORMALIZE_AXIS_SUBCASE( case1, axis, ndim_ct );
    NORMALIZE_AXIS_SUBCASE( case1, axis_a, ndim_ct );
    NORMALIZE_AXIS_SUBCASE( case1, axis_v, ndim_ct );
    NORMALIZE_AXIS_SUBCASE( case1, axis_f, ndim_ct );
    NORMALIZE_AXIS_SUBCASE( case1, axis_h, ndim_ct );

    NORMALIZE_AXIS_SUBCASE( case1, axis_ct, ndim_ct );
    NORMALIZE_AXIS_SUBCASE( case1, axis_ct, ndim );
}

TEST_CASE("normalize_axis(case2)" * doctest::test_suite("index::normalize_axis"))
{
    NORMALIZE_AXIS_SUBCASE( case2, axis, ndim );
    NORMALIZE_AXIS_SUBCASE( case2, axis_a, ndim );
    NORMALIZE_AXIS_SUBCASE( case2, axis_v, ndim );
    NORMALIZE_AXIS_SUBCASE( case2, axis_f, ndim );
    NORMALIZE_AXIS_SUBCASE( case2, axis_h, ndim );

    NORMALIZE_AXIS_SUBCASE( case2, axis, ndim_ct );
    NORMALIZE_AXIS_SUBCASE( case2, axis_a, ndim_ct );
    NORMALIZE_AXIS_SUBCASE( case2, axis_v, ndim_ct );
    NORMALIZE_AXIS_SUBCASE( case2, axis_f, ndim_ct );
    NORMALIZE_AXIS_SUBCASE( case2, axis_h, ndim_ct );

    #if 0
    NORMALIZE_AXIS_SUBCASE( case2, axis_ct, ndim_ct );
    #endif
    NORMALIZE_AXIS_SUBCASE( case2, axis_ct, ndim );
}

TEST_CASE("normalize_axis(case3)" * doctest::test_suite("index::normalize_axis"))
{
    NORMALIZE_AXIS_SUBCASE( case3, axis, ndim );
    NORMALIZE_AXIS_SUBCASE( case3, axis_a, ndim );
    NORMALIZE_AXIS_SUBCASE( case3, axis_v, ndim );
    NORMALIZE_AXIS_SUBCASE( case3, axis_f, ndim );
    NORMALIZE_AXIS_SUBCASE( case3, axis_h, ndim );

    NORMALIZE_AXIS_SUBCASE( case3, axis, ndim_ct );
    NORMALIZE_AXIS_SUBCASE( case3, axis_a, ndim_ct );
    NORMALIZE_AXIS_SUBCASE( case3, axis_v, ndim_ct );
    NORMALIZE_AXIS_SUBCASE( case3, axis_f, ndim_ct );
    NORMALIZE_AXIS_SUBCASE( case3, axis_h, ndim_ct );

    NORMALIZE_AXIS_SUBCASE( case3, axis_ct, ndim_ct );
    NORMALIZE_AXIS_SUBCASE( case3, axis_ct, ndim );
}

TEST_CASE("normalize_axis(case4)" * doctest::test_suite("index::normalize_axis"))
{
    NORMALIZE_AXIS_SUBCASE( case4, axis, ndim );

    NORMALIZE_AXIS_SUBCASE( case4, axis_ct, ndim_ct );
    NORMALIZE_AXIS_SUBCASE( case4, axis_ct, ndim );
    NORMALIZE_AXIS_SUBCASE( case4,    axis, ndim_ct );
}

TEST_CASE("normalize_axis(case5)" * doctest::test_suite("index::normalize_axis"))
{
    NORMALIZE_AXIS_SUBCASE( case5, axis, ndim );

    #if 0 // should trigger invalid type
    NORMALIZE_AXIS_SUBCASE( case5, axis_ct, ndim_ct );
    #endif
    NORMALIZE_AXIS_SUBCASE( case5, axis_ct, ndim );
    NORMALIZE_AXIS_SUBCASE( case5,    axis, ndim_ct );
}

TEST_CASE("normalize_axis(case6)" * doctest::test_suite("index::normalize_axis"))
{
    NORMALIZE_AXIS_SUBCASE( case6, axis, ndim );

    NORMALIZE_AXIS_SUBCASE( case6, axis_ct, ndim_ct );
    NORMALIZE_AXIS_SUBCASE( case6, axis_ct, ndim );
    NORMALIZE_AXIS_SUBCASE( case6,    axis, ndim_ct );
}

TEST_CASE("normalize_axis(case7)" * doctest::test_suite("index::normalize_axis"))
{
    NORMALIZE_AXIS_SUBCASE( case7, axis, ndim );

    NORMALIZE_AXIS_SUBCASE( case7, axis_ct, ndim_ct );
    NORMALIZE_AXIS_SUBCASE( case7, axis_ct, ndim );
    NORMALIZE_AXIS_SUBCASE( case7,    axis, ndim_ct );
}

TEST_CASE("normalize_axis(case8)" * doctest::test_suite("index::normalize_axis"))
{
    NORMALIZE_AXIS_SUBCASE( case8, axis, ndim );

    NORMALIZE_AXIS_SUBCASE( case8, axis_ct, ndim_ct );
    NORMALIZE_AXIS_SUBCASE( case8, axis_ct, ndim );
    NORMALIZE_AXIS_SUBCASE( case8,    axis, ndim_ct );
}

TEST_CASE("normalize_axis(case9)" * doctest::test_suite("index::normalize_axis"))
{
    NORMALIZE_AXIS_SUBCASE( case9, axis, ndim );

    NORMALIZE_AXIS_SUBCASE( case9, axis_ct, ndim_ct );
    NORMALIZE_AXIS_SUBCASE( case9, axis_ct, ndim );
    NORMALIZE_AXIS_SUBCASE( case9, axis, ndim_ct );
}

TEST_CASE("normalize_axis(case10)" * doctest::test_suite("index::normalize_axis"))
{
    NORMALIZE_AXIS_SUBCASE( case10, axis, ndim );

    #if 0 // should trigger invalid type
    NORMALIZE_AXIS_SUBCASE( case10, axis_ct, ndim_ct );
    #endif
    NORMALIZE_AXIS_SUBCASE( case10, axis_ct, ndim );
    NORMALIZE_AXIS_SUBCASE( case10, axis, ndim_ct );
}

TEST_CASE("normalize_axis(case11)" * doctest::test_suite("index::normalize_axis"))
{
    NORMALIZE_AXIS_SUBCASE( case11, axis, ndim );
    NORMALIZE_AXIS_SUBCASE( case11, axis_ct, ndim_ct );
    NORMALIZE_AXIS_SUBCASE( case11, axis_ct, ndim );
    NORMALIZE_AXIS_SUBCASE( case11, axis, ndim_ct );
}

TEST_CASE("normalize_axis(case12)" * doctest::test_suite("index::normalize_axis"))
{
    NORMALIZE_AXIS_SUBCASE( case12, axis, ndim );
    NORMALIZE_AXIS_SUBCASE( case12, axis_ct, ndim_ct );
    NORMALIZE_AXIS_SUBCASE( case12, axis_ct, ndim );
    NORMALIZE_AXIS_SUBCASE( case12, axis, ndim_ct );
}

NMTOOLS_TESTING_DECLARE_CASE(index, constexpr_normalize_axis)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr inline int axis[3] = {-1,-2,-3};
        constexpr inline int ndim = 3;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(axis);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline int result[3] = {2,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        constexpr inline int axis[3] = {-1,-2,3};
        constexpr inline int ndim = 3;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(axis);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        // AxisError: axis 3 is out of bounds for array of dimension 3
        constexpr inline auto result = meta::Nothing;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        constexpr inline int axis[3] = {-1,2,-3};
        constexpr inline int ndim = 3;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(axis);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        constexpr inline int result[3] = {2,2,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        constexpr inline int axis = -3;
        constexpr inline int ndim = 3;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        constexpr inline int result = 0;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        constexpr inline int axis = 3;
        constexpr inline int ndim = 3;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        constexpr inline auto result = meta::Nothing;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        constexpr inline int axis[1] = {0};
        constexpr inline int ndim = 3;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(axis);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        constexpr inline int result[1] = {0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        constexpr inline int axis[1] = {1};
        constexpr inline int ndim = 3;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(axis);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        constexpr inline int result[1] = {1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        constexpr inline unsigned int axis[1] = {0};
        constexpr inline int ndim = 3;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(axis);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        constexpr inline int result[1] = {0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        constexpr inline unsigned int axis[1] = {1};
        constexpr inline int ndim = 3;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(axis);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        constexpr inline int result[1] = {1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        constexpr inline unsigned int axis[1] = {0};
        constexpr inline unsigned int ndim = 3;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(axis);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        constexpr inline int result[1] = {0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        constexpr inline unsigned int axis[1] = {1};
        constexpr inline unsigned int ndim = 3;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(axis);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        constexpr inline int result[1] = {1};
    }
}

#define CONSTEXPR_NORMALIZE_AXIS_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index, constexpr_normalize_axis, case_name); \
    using namespace args; \
    constexpr auto result = RUN_impl(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

#if defined(__clang__) && (__clang_major__ <= 10)
#define NMTOOLS_NO_CONSTEXPR_MOVEAXIS
#endif // clang 10


TEST_CASE("normalize_axis(case1)" * doctest::test_suite("index::constexpr_normalize_axis"))
{
    // somehow doesn't work on clang 🤷, works fine on gcc
    // note: non-constexpr function 'operator()<int const (&)[3], const int &>' cannot be used in a constant expression
    // TODO: fix constexpr clang, seems like something to do with at customization point
    #ifndef NMTOOLS_NO_CONSTEXPR_MOVEAXIS
    CONSTEXPR_NORMALIZE_AXIS_SUBCASE( case1, axis, ndim );
    CONSTEXPR_NORMALIZE_AXIS_SUBCASE( case1, axis_a, ndim );
    CONSTEXPR_NORMALIZE_AXIS_SUBCASE( case1, axis_f, ndim );
    CONSTEXPR_NORMALIZE_AXIS_SUBCASE( case1, axis_h, ndim );
    #endif // NMTOOLS_NO_CONSTEXPR_MOVEAXIS
}

TEST_CASE("normalize_axis(case2)" * doctest::test_suite("index::constexpr_normalize_axis"))
{
    #ifndef NMTOOLS_NO_CONSTEXPR_MOVEAXIS
    CONSTEXPR_NORMALIZE_AXIS_SUBCASE( case2, axis, ndim );
    CONSTEXPR_NORMALIZE_AXIS_SUBCASE( case2, axis_a, ndim );
    CONSTEXPR_NORMALIZE_AXIS_SUBCASE( case2, axis_f, ndim );
    CONSTEXPR_NORMALIZE_AXIS_SUBCASE( case2, axis_h, ndim );
    #endif // NMTOOLS_NO_CONSTEXPR_MOVEAXIS
}

TEST_CASE("normalize_axis(case3)" * doctest::test_suite("index::constexpr_normalize_axis"))
{
    #ifndef NMTOOLS_NO_CONSTEXPR_MOVEAXIS
    CONSTEXPR_NORMALIZE_AXIS_SUBCASE( case3, axis, ndim );
    CONSTEXPR_NORMALIZE_AXIS_SUBCASE( case3, axis_a, ndim );
    CONSTEXPR_NORMALIZE_AXIS_SUBCASE( case3, axis_f, ndim );
    CONSTEXPR_NORMALIZE_AXIS_SUBCASE( case3, axis_h, ndim );
    #endif // NMTOOLS_NO_CONSTEXPR_MOVEAXIS
}

TEST_CASE("normalize_axis(case4)" * doctest::test_suite("index::constexpr_normalize_axis"))
{
    #ifndef NMTOOLS_NO_CONSTEXPR_MOVEAXIS
    CONSTEXPR_NORMALIZE_AXIS_SUBCASE( case4, axis, ndim );
    #endif // NMTOOLS_NO_CONSTEXPR_MOVEAXIS
}

TEST_CASE("normalize_axis(case5)" * doctest::test_suite("index::constexpr_normalize_axis"))
{
    #ifndef NMTOOLS_NO_CONSTEXPR_MOVEAXIS
    CONSTEXPR_NORMALIZE_AXIS_SUBCASE( case5, axis, ndim );
    #endif // NMTOOLS_NO_CONSTEXPR_MOVEAXIS
}

TEST_CASE("normalize_axis(case6)" * doctest::test_suite("index::constexpr_normalize_axis"))
{
    // somehow doesn't work on clang 🤷, works fine on gcc
    // note: non-constexpr function 'operator()<int const (&)[3], const int &>' cannot be used in a constant expression
    // TODO: fix constexpr clang, seems like something to do with at customization point
    #ifndef NMTOOLS_NO_CONSTEXPR_MOVEAXIS
    CONSTEXPR_NORMALIZE_AXIS_SUBCASE( case6, axis, ndim );
    CONSTEXPR_NORMALIZE_AXIS_SUBCASE( case6, axis_a, ndim );
    CONSTEXPR_NORMALIZE_AXIS_SUBCASE( case6, axis_f, ndim );
    CONSTEXPR_NORMALIZE_AXIS_SUBCASE( case6, axis_h, ndim );
    #endif // NMTOOLS_NO_CONSTEXPR_MOVEAXIS
}

TEST_CASE("normalize_axis(case7)" * doctest::test_suite("index::constexpr_normalize_axis"))
{
    // somehow doesn't work on clang 🤷, works fine on gcc
    // note: non-constexpr function 'operator()<int const (&)[3], const int &>' cannot be used in a constant expression
    // TODO: fix constexpr clang, seems like something to do with at customization point
    #ifndef NMTOOLS_NO_CONSTEXPR_MOVEAXIS
    CONSTEXPR_NORMALIZE_AXIS_SUBCASE( case7, axis, ndim );
    CONSTEXPR_NORMALIZE_AXIS_SUBCASE( case7, axis_a, ndim );
    CONSTEXPR_NORMALIZE_AXIS_SUBCASE( case7, axis_f, ndim );
    CONSTEXPR_NORMALIZE_AXIS_SUBCASE( case7, axis_h, ndim );
    #endif // NMTOOLS_NO_CONSTEXPR_MOVEAXIS
}

TEST_CASE("normalize_axis(case8)" * doctest::test_suite("index::constexpr_normalize_axis"))
{
    // somehow doesn't work on clang 🤷, works fine on gcc
    // note: non-constexpr function 'operator()<int const (&)[3], const int &>' cannot be used in a constant expression
    // TODO: fix constexpr clang, seems like something to do with at customization point
    #ifndef NMTOOLS_NO_CONSTEXPR_MOVEAXIS
    CONSTEXPR_NORMALIZE_AXIS_SUBCASE( case8, axis, ndim );
    CONSTEXPR_NORMALIZE_AXIS_SUBCASE( case8, axis_a, ndim );
    CONSTEXPR_NORMALIZE_AXIS_SUBCASE( case8, axis_f, ndim );
    CONSTEXPR_NORMALIZE_AXIS_SUBCASE( case8, axis_h, ndim );
    #endif // NMTOOLS_NO_CONSTEXPR_MOVEAXIS
}

TEST_CASE("normalize_axis(case9)" * doctest::test_suite("index::constexpr_normalize_axis"))
{
    // somehow doesn't work on clang 🤷, works fine on gcc
    // note: non-constexpr function 'operator()<int const (&)[3], const int &>' cannot be used in a constant expression
    // TODO: fix constexpr clang, seems like something to do with at customization point
    #ifndef NMTOOLS_NO_CONSTEXPR_MOVEAXIS
    CONSTEXPR_NORMALIZE_AXIS_SUBCASE( case9, axis, ndim );
    CONSTEXPR_NORMALIZE_AXIS_SUBCASE( case9, axis_a, ndim );
    CONSTEXPR_NORMALIZE_AXIS_SUBCASE( case9, axis_f, ndim );
    CONSTEXPR_NORMALIZE_AXIS_SUBCASE( case9, axis_h, ndim );
    #endif // NMTOOLS_NO_CONSTEXPR_MOVEAXIS
}

TEST_CASE("normalize_axis(case10)" * doctest::test_suite("index::constexpr_normalize_axis"))
{
    #ifndef NMTOOLS_NO_CONSTEXPR_MOVEAXIS
    CONSTEXPR_NORMALIZE_AXIS_SUBCASE( case10, axis, ndim );
    CONSTEXPR_NORMALIZE_AXIS_SUBCASE( case10, axis_a, ndim );
    CONSTEXPR_NORMALIZE_AXIS_SUBCASE( case10, axis_f, ndim );
    CONSTEXPR_NORMALIZE_AXIS_SUBCASE( case10, axis_h, ndim );
    #endif // NMTOOLS_NO_CONSTEXPR_MOVEAXIS
}

TEST_CASE("normalize_axis(case11)" * doctest::test_suite("index::constexpr_normalize_axis"))
{
    #ifndef NMTOOLS_NO_CONSTEXPR_MOVEAXIS
    CONSTEXPR_NORMALIZE_AXIS_SUBCASE( case11, axis, ndim );
    CONSTEXPR_NORMALIZE_AXIS_SUBCASE( case11, axis_a, ndim );
    CONSTEXPR_NORMALIZE_AXIS_SUBCASE( case11, axis_f, ndim );
    CONSTEXPR_NORMALIZE_AXIS_SUBCASE( case11, axis_h, ndim );
    #endif // NMTOOLS_NO_CONSTEXPR_MOVEAXIS
}