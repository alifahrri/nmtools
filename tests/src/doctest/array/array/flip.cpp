#include "nmtools/array/array/flip.hpp"
#include "nmtools/testing/data/array/flip.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>
#include <tuple>

#define RUN_flip_impl(...) \
nm::array::flip(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs flip fn to callable lambda
#define RUN_flip(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("flip-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_flip_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_flip(case_name, ...) \
RUN_flip_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define FLIP_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(flip, case_name); \
    using namespace args; \
    auto result = RUN_flip(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("flip(case1)" * doctest::test_suite("array::flip"))
{
    FLIP_SUBCASE(case1,   array, axis );
    FLIP_SUBCASE(case1, array_a, axis );
    FLIP_SUBCASE(case1, array_v, axis );
    FLIP_SUBCASE(case1, array_f, axis );
    FLIP_SUBCASE(case1, array_h, axis );
    // FLIP_SUBCASE(case1, array_d, axis );
}

TEST_CASE("flip(case2)" * doctest::test_suite("array::flip"))
{
    FLIP_SUBCASE(case2,   array, axis );
    FLIP_SUBCASE(case2, array_a, axis );
    FLIP_SUBCASE(case2, array_v, axis );
    FLIP_SUBCASE(case2, array_f, axis );
    FLIP_SUBCASE(case2, array_h, axis );
    // FLIP_SUBCASE(case2, array_d, axis );
}

TEST_CASE("flip(case3)" * doctest::test_suite("array::flip"))
{
    FLIP_SUBCASE(case3,   array, axis );
    FLIP_SUBCASE(case3, array_a, axis );
    FLIP_SUBCASE(case3, array_v, axis );
    FLIP_SUBCASE(case3, array_f, axis );
    FLIP_SUBCASE(case3, array_h, axis );
    // FLIP_SUBCASE(case3, array_d, axis );
}

TEST_CASE("flip(case4)" * doctest::test_suite("array::flip"))
{
    FLIP_SUBCASE(case4,   array,   axis );
    FLIP_SUBCASE(case4, array_a, axis_a );
    FLIP_SUBCASE(case4, array_v, axis_v );
    FLIP_SUBCASE(case4, array_f, axis_f );
    FLIP_SUBCASE(case4, array_h, axis_h );
    // FLIP_SUBCASE(case4, array_d, axis_d );
}

// skip constexpr test for emscripten for now, works for gcc & clang
#ifndef __EMSCRIPTEN__
TEST_CASE("flip(case1)" * doctest::test_suite("array::constexpr_flip"))
{
    SUBCASE("case1")
    {
        NMTOOLS_TESTING_DECLARE_NS(constexpr_flip, case1);
        using namespace args;
        constexpr auto context = nm::None;
        // TODO: fix shape inference for fixed ndarray
        constexpr auto output = nm::meta::as_value<int[2][2][2]>{};
        constexpr auto result = nm::array::flip( array, axis, context, output );
        NMTOOLS_ASSERT_EQUAL( result, expect::result );
    }
}
#endif