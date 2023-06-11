#include "nmtools/array/index/broadcast_shape.hpp"
#include "nmtools/array/ndarray.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/testing/data/index/broadcast_shape.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;

#define RUN_impl(...) \
nm::index::broadcast_shape(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs broadcast_shape fn to callable lambda
#define RUN_broadcast_shape(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("broadcast_shape-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_broadcast_shape(case_name, ...) \
RUN_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define BROADCAST_SHAPE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(broadcast_shape, case_name); \
    using namespace args; \
    const auto result = RUN_broadcast_shape(case_name,__VA_ARGS__); \
    const auto success = static_cast<bool>(result); \
    NMTOOLS_ASSERT_EQUAL( success, expect::success ); \
    if (expect::success) \
        NMTOOLS_ASSERT_EQUAL( *result, expect::expected ); \
}

TEST_CASE("broadcast_shape(case1)" * doctest::test_suite("index::broadcast_shape"))
{
    BROADCAST_SHAPE_SUBCASE(case1, a_a, b_a);
    BROADCAST_SHAPE_SUBCASE(case1, a_v, b_v);
    BROADCAST_SHAPE_SUBCASE(case1, a_h, b_h);
    BROADCAST_SHAPE_SUBCASE(case1, a_sv, b_sv);

    BROADCAST_SHAPE_SUBCASE(case1, a_v, b_a);
    BROADCAST_SHAPE_SUBCASE(case1, a_h, b_a);
    BROADCAST_SHAPE_SUBCASE(case1, a_sv, b_a);

    BROADCAST_SHAPE_SUBCASE(case1, a_a, b_v);
    BROADCAST_SHAPE_SUBCASE(case1, a_h, b_v);
    BROADCAST_SHAPE_SUBCASE(case1, a_sv, b_v);

    BROADCAST_SHAPE_SUBCASE(case1, a_a, b_h);
    BROADCAST_SHAPE_SUBCASE(case1, a_v, b_h);
    BROADCAST_SHAPE_SUBCASE(case1, a_sv, b_h);

    BROADCAST_SHAPE_SUBCASE(case1, a_a, b_sv);
    BROADCAST_SHAPE_SUBCASE(case1, a_v, b_sv);
    BROADCAST_SHAPE_SUBCASE(case1, a_h, b_sv);
}

TEST_CASE("broadcast_shape(case2)" * doctest::test_suite("index::broadcast_shape"))
{
    BROADCAST_SHAPE_SUBCASE(case2, a_a, b_a);
    BROADCAST_SHAPE_SUBCASE(case2, a_v, b_v);
    BROADCAST_SHAPE_SUBCASE(case2, a_h, b_h);
    BROADCAST_SHAPE_SUBCASE(case2, a_sv, b_sv);

    BROADCAST_SHAPE_SUBCASE(case2, a_v, b_a);
    BROADCAST_SHAPE_SUBCASE(case2, a_h, b_a);
    BROADCAST_SHAPE_SUBCASE(case2, a_sv, b_a);

    BROADCAST_SHAPE_SUBCASE(case2, a_a, b_v);
    BROADCAST_SHAPE_SUBCASE(case2, a_h, b_v);
    BROADCAST_SHAPE_SUBCASE(case2, a_sv, b_v);

    BROADCAST_SHAPE_SUBCASE(case2, a_a, b_h);
    BROADCAST_SHAPE_SUBCASE(case2, a_v, b_h);
    BROADCAST_SHAPE_SUBCASE(case2, a_sv, b_h);

    BROADCAST_SHAPE_SUBCASE(case2, a_a, b_sv);
    BROADCAST_SHAPE_SUBCASE(case2, a_v, b_sv);
    BROADCAST_SHAPE_SUBCASE(case2, a_h, b_sv);
}

TEST_CASE("broadcast_shape(case3)" * doctest::test_suite("index::broadcast_shape"))
{
    BROADCAST_SHAPE_SUBCASE(case3, a_a, b_a);
    BROADCAST_SHAPE_SUBCASE(case3, a_v, b_v);
    BROADCAST_SHAPE_SUBCASE(case3, a_h, b_h);
    BROADCAST_SHAPE_SUBCASE(case3, a_sv, b_sv);

    BROADCAST_SHAPE_SUBCASE(case3, a_v, b_a);
    BROADCAST_SHAPE_SUBCASE(case3, a_h, b_a);
    BROADCAST_SHAPE_SUBCASE(case3, a_sv, b_a);

    BROADCAST_SHAPE_SUBCASE(case3, a_a, b_v);
    BROADCAST_SHAPE_SUBCASE(case3, a_h, b_v);
    BROADCAST_SHAPE_SUBCASE(case3, a_sv, b_v);

    BROADCAST_SHAPE_SUBCASE(case3, a_a, b_h);
    BROADCAST_SHAPE_SUBCASE(case3, a_v, b_h);
    BROADCAST_SHAPE_SUBCASE(case3, a_sv, b_h);

    BROADCAST_SHAPE_SUBCASE(case3, a_a, b_sv);
    BROADCAST_SHAPE_SUBCASE(case3, a_v, b_sv);
    BROADCAST_SHAPE_SUBCASE(case3, a_h, b_sv);
}

TEST_CASE("broadcast_shape(case4)" * doctest::test_suite("index::broadcast_shape"))
{
    BROADCAST_SHAPE_SUBCASE(case4, a_a, b_a);
    BROADCAST_SHAPE_SUBCASE(case4, a_v, b_v);
    BROADCAST_SHAPE_SUBCASE(case4, a_h, b_h);
    BROADCAST_SHAPE_SUBCASE(case4, a_sv, b_sv);

    BROADCAST_SHAPE_SUBCASE(case4, a_v, b_a);
    BROADCAST_SHAPE_SUBCASE(case4, a_h, b_a);
    BROADCAST_SHAPE_SUBCASE(case4, a_sv, b_a);

    BROADCAST_SHAPE_SUBCASE(case4, a_a, b_v);
    BROADCAST_SHAPE_SUBCASE(case4, a_h, b_v);
    BROADCAST_SHAPE_SUBCASE(case4, a_sv, b_v);

    BROADCAST_SHAPE_SUBCASE(case4, a_a, b_h);
    BROADCAST_SHAPE_SUBCASE(case4, a_v, b_h);
    BROADCAST_SHAPE_SUBCASE(case4, a_sv, b_h);

    BROADCAST_SHAPE_SUBCASE(case4, a_a, b_sv);
    BROADCAST_SHAPE_SUBCASE(case4, a_v, b_sv);
    BROADCAST_SHAPE_SUBCASE(case4, a_h, b_sv);
}

TEST_CASE("broadcast_shape(case5)" * doctest::test_suite("index::broadcast_shape"))
{
    BROADCAST_SHAPE_SUBCASE(case5, a_a, b_a);
    BROADCAST_SHAPE_SUBCASE(case5, a_v, b_v);
    BROADCAST_SHAPE_SUBCASE(case5, a_h, b_h);
    BROADCAST_SHAPE_SUBCASE(case5, a_sv, b_sv);

    BROADCAST_SHAPE_SUBCASE(case5, a_v, b_a);
    BROADCAST_SHAPE_SUBCASE(case5, a_h, b_a);
    BROADCAST_SHAPE_SUBCASE(case5, a_sv, b_a);

    BROADCAST_SHAPE_SUBCASE(case5, a_a, b_v);
    BROADCAST_SHAPE_SUBCASE(case5, a_h, b_v);
    BROADCAST_SHAPE_SUBCASE(case5, a_sv, b_v);

    BROADCAST_SHAPE_SUBCASE(case5, a_a, b_h);
    BROADCAST_SHAPE_SUBCASE(case5, a_v, b_h);
    BROADCAST_SHAPE_SUBCASE(case5, a_sv, b_h);

    BROADCAST_SHAPE_SUBCASE(case5, a_a, b_sv);
    BROADCAST_SHAPE_SUBCASE(case5, a_v, b_sv);
    BROADCAST_SHAPE_SUBCASE(case5, a_h, b_sv);
}

TEST_CASE("broadcast_shape(case6)" * doctest::test_suite("index::broadcast_shape"))
{
    BROADCAST_SHAPE_SUBCASE(case6, a_a, b_a);
    BROADCAST_SHAPE_SUBCASE(case6, a_v, b_v);
    BROADCAST_SHAPE_SUBCASE(case6, a_h, b_h);
    BROADCAST_SHAPE_SUBCASE(case6, a_sv, b_sv);

    BROADCAST_SHAPE_SUBCASE(case6, a_v, b_a);
    BROADCAST_SHAPE_SUBCASE(case6, a_h, b_a);
    BROADCAST_SHAPE_SUBCASE(case6, a_sv, b_a);

    BROADCAST_SHAPE_SUBCASE(case6, a_a, b_v);
    BROADCAST_SHAPE_SUBCASE(case6, a_h, b_v);
    BROADCAST_SHAPE_SUBCASE(case6, a_sv, b_v);

    BROADCAST_SHAPE_SUBCASE(case6, a_a, b_h);
    BROADCAST_SHAPE_SUBCASE(case6, a_v, b_h);
    BROADCAST_SHAPE_SUBCASE(case6, a_sv, b_h);

    BROADCAST_SHAPE_SUBCASE(case6, a_a, b_sv);
    BROADCAST_SHAPE_SUBCASE(case6, a_v, b_sv);
    BROADCAST_SHAPE_SUBCASE(case6, a_h, b_sv);
}

TEST_CASE("broadcast_shape(case7)" * doctest::test_suite("index::broadcast_shape"))
{
    BROADCAST_SHAPE_SUBCASE(case7, a_a, b_a);
    BROADCAST_SHAPE_SUBCASE(case7, a_v, b_v);
    BROADCAST_SHAPE_SUBCASE(case7, a_h, b_h);
    BROADCAST_SHAPE_SUBCASE(case7, a_sv, b_sv);

    BROADCAST_SHAPE_SUBCASE(case7, a_v, b_a);
    BROADCAST_SHAPE_SUBCASE(case7, a_h, b_a);
    BROADCAST_SHAPE_SUBCASE(case7, a_sv, b_a);

    BROADCAST_SHAPE_SUBCASE(case7, a_a, b_v);
    BROADCAST_SHAPE_SUBCASE(case7, a_h, b_v);
    BROADCAST_SHAPE_SUBCASE(case7, a_sv, b_v);

    BROADCAST_SHAPE_SUBCASE(case7, a_a, b_h);
    BROADCAST_SHAPE_SUBCASE(case7, a_v, b_h);
    BROADCAST_SHAPE_SUBCASE(case7, a_sv, b_h);

    BROADCAST_SHAPE_SUBCASE(case7, a_a, b_sv);
    BROADCAST_SHAPE_SUBCASE(case7, a_v, b_sv);
    BROADCAST_SHAPE_SUBCASE(case7, a_h, b_sv);
}

TEST_CASE("broadcast_shape(case8)" * doctest::test_suite("index::broadcast_shape"))
{
    BROADCAST_SHAPE_SUBCASE(case8, a_a, b_a, c_a);
    BROADCAST_SHAPE_SUBCASE(case8, a_v, b_v, c_a);
    BROADCAST_SHAPE_SUBCASE(case8, a_h, b_h, c_a);

    BROADCAST_SHAPE_SUBCASE(case8, a_v, b_a, c_a);
    BROADCAST_SHAPE_SUBCASE(case8, a_h, b_a, c_a);

    BROADCAST_SHAPE_SUBCASE(case8, a_a, b_v, c_a);
    BROADCAST_SHAPE_SUBCASE(case8, a_h, b_v, c_a);

    BROADCAST_SHAPE_SUBCASE(case8, a_a, b_h, c_a);
    BROADCAST_SHAPE_SUBCASE(case8, a_v, b_h, c_a);

    //
    BROADCAST_SHAPE_SUBCASE(case8, a_v, b_v, c_a);
    BROADCAST_SHAPE_SUBCASE(case8, a_h, b_h, c_a);

    BROADCAST_SHAPE_SUBCASE(case8, a_v, b_a, c_a);
    BROADCAST_SHAPE_SUBCASE(case8, a_h, b_a, c_a);

    BROADCAST_SHAPE_SUBCASE(case8, a_a, b_v, c_a);
    BROADCAST_SHAPE_SUBCASE(case8, a_h, b_v, c_a);

    BROADCAST_SHAPE_SUBCASE(case8, a_a, b_h, c_a);
    BROADCAST_SHAPE_SUBCASE(case8, a_v, b_h, c_a);
}

TEST_CASE("broadcast_shape(case9)" * doctest::test_suite("index::broadcast_shape"))
{
    BROADCAST_SHAPE_SUBCASE(case9, a_a, b_a, c_a);
    BROADCAST_SHAPE_SUBCASE(case9, a_v, b_v, c_a);
    BROADCAST_SHAPE_SUBCASE(case9, a_h, b_h, c_a);

    BROADCAST_SHAPE_SUBCASE(case9, a_v, b_a, c_a);
    BROADCAST_SHAPE_SUBCASE(case9, a_h, b_a, c_a);

    BROADCAST_SHAPE_SUBCASE(case9, a_a, b_v, c_a);
    BROADCAST_SHAPE_SUBCASE(case9, a_h, b_v, c_a);

    BROADCAST_SHAPE_SUBCASE(case9, a_a, b_h, c_a);
    BROADCAST_SHAPE_SUBCASE(case9, a_v, b_h, c_a);

    //
    BROADCAST_SHAPE_SUBCASE(case9, a_v, b_v, c_a);
    BROADCAST_SHAPE_SUBCASE(case9, a_h, b_h, c_a);

    BROADCAST_SHAPE_SUBCASE(case9, a_v, b_a, c_a);
    BROADCAST_SHAPE_SUBCASE(case9, a_h, b_a, c_a);

    BROADCAST_SHAPE_SUBCASE(case9, a_a, b_v, c_a);
    BROADCAST_SHAPE_SUBCASE(case9, a_h, b_v, c_a);

    BROADCAST_SHAPE_SUBCASE(case9, a_a, b_h, c_a);
    BROADCAST_SHAPE_SUBCASE(case9, a_v, b_h, c_a);
}

TEST_CASE("broadcast_shape(case10)" * doctest::test_suite("index::broadcast_shape"))
{
    BROADCAST_SHAPE_SUBCASE(case10, a_a, b_a, c_a, d_a);
    BROADCAST_SHAPE_SUBCASE(case10, a_v, b_v, c_a, d_a);
    BROADCAST_SHAPE_SUBCASE(case10, a_h, b_h, c_a, d_a);

    BROADCAST_SHAPE_SUBCASE(case10, a_v, b_a, c_a, d_a);
    BROADCAST_SHAPE_SUBCASE(case10, a_h, b_a, c_a, d_a);

    BROADCAST_SHAPE_SUBCASE(case10, a_a, b_v, c_a, d_a);
    BROADCAST_SHAPE_SUBCASE(case10, a_h, b_v, c_a, d_a);

    BROADCAST_SHAPE_SUBCASE(case10, a_a, b_h, c_a, d_a);
    BROADCAST_SHAPE_SUBCASE(case10, a_v, b_h, c_a, d_a);

    //
    BROADCAST_SHAPE_SUBCASE(case10, a_v, b_v, c_a, d_a);
    BROADCAST_SHAPE_SUBCASE(case10, a_h, b_h, c_a, d_a);

    BROADCAST_SHAPE_SUBCASE(case10, a_v, b_a, c_a, d_a);
    BROADCAST_SHAPE_SUBCASE(case10, a_h, b_a, c_a, d_a);

    BROADCAST_SHAPE_SUBCASE(case10, a_a, b_v, c_a, d_a);
    BROADCAST_SHAPE_SUBCASE(case10, a_h, b_v, c_a, d_a);

    BROADCAST_SHAPE_SUBCASE(case10, a_a, b_h, c_a, d_a);
    BROADCAST_SHAPE_SUBCASE(case10, a_v, b_h, c_a, d_a);
}

TEST_CASE("broadcast_shape(case11)" * doctest::test_suite("index::broadcast_shape"))
{
    BROADCAST_SHAPE_SUBCASE(case11, a_a, b_a, c_a, d_a, e_a, f_a, g_a);
    BROADCAST_SHAPE_SUBCASE(case11, a_v, b_v, c_a, d_a, e_a, f_a, g_a);
    BROADCAST_SHAPE_SUBCASE(case11, a_h, b_h, c_a, d_a, e_a, f_a, g_a);

    BROADCAST_SHAPE_SUBCASE(case11, a_v, b_a, c_a, d_a, e_a, f_a, g_a);
    BROADCAST_SHAPE_SUBCASE(case11, a_h, b_a, c_a, d_a, e_a, f_a, g_a);

    BROADCAST_SHAPE_SUBCASE(case11, a_a, b_v, c_a, d_a, e_a, f_a, g_a);
    BROADCAST_SHAPE_SUBCASE(case11, a_h, b_v, c_a, d_a, e_a, f_a, g_a);

    BROADCAST_SHAPE_SUBCASE(case11, a_a, b_h, c_a, d_a, e_a, f_a, g_a);
    BROADCAST_SHAPE_SUBCASE(case11, a_v, b_h, c_a, d_a, e_a, f_a, g_a);

    //
    BROADCAST_SHAPE_SUBCASE(case11, a_v, b_v, c_a, d_a, e_a, f_a, g_a);
    BROADCAST_SHAPE_SUBCASE(case11, a_h, b_h, c_a, d_a, e_a, f_a, g_a);

    BROADCAST_SHAPE_SUBCASE(case11, a_v, b_a, c_a, d_a, e_a, f_a, g_a);
    BROADCAST_SHAPE_SUBCASE(case11, a_h, b_a, c_a, d_a, e_a, f_a, g_a);

    BROADCAST_SHAPE_SUBCASE(case11, a_a, b_v, c_a, d_a, e_a, f_a, g_a);
    BROADCAST_SHAPE_SUBCASE(case11, a_h, b_v, c_a, d_a, e_a, f_a, g_a);

    BROADCAST_SHAPE_SUBCASE(case11, a_a, b_h, c_a, d_a, e_a, f_a, g_a);
    BROADCAST_SHAPE_SUBCASE(case11, a_v, b_h, c_a, d_a, e_a, f_a, g_a);
}

TEST_CASE("broadcast_shape(constexpr)" * doctest::test_suite("index::broadcast_shape"))
{
    {
        constexpr int a[2] = {4,1};
        constexpr int b[3] = {8,1,3};
        constexpr int c[1] = {3};
        constexpr int d[6] = {2,2,3,1,4,1};
        constexpr int expected[6] = {2,2,3,8,4,3};
        constexpr auto broadcasted = nm::index::broadcast_shape(a,b,c,d);
        [[maybe_unused]] constexpr auto success = static_cast<bool>(broadcasted);
        NMTOOLS_STATIC_ASSERT( success );
        NMTOOLS_STATIC_ASSERT_EQUAL( broadcasted, expected );
    }
}