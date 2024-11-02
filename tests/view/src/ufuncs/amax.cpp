#include "nmtools/array/view/ufuncs/amax.hpp"
#include "nmtools/testing/data/array/maximum.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define RUN_amax_impl(...) \
nm::view::amax(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs amax fn to callable lambda
#define RUN_amax(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("amax-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_amax_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_amax(case_name, ...) \
RUN_amax_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define AMAX_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, reduce_maximum, case_name); \
    using namespace args; \
    auto result = RUN_amax(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}


TEST_CASE("amax(case1)" * doctest::test_suite("view::amax"))
{
    AMAX_SUBCASE( case1,   a, axis );
    AMAX_SUBCASE( case1, a_a, axis );
    AMAX_SUBCASE( case1, a_f, axis );
    // dynamic dim array not supported yet
    // AMAX_SUBCASE( case1, a_d, axis );
    AMAX_SUBCASE( case1, a_h, axis );
}

TEST_CASE("amax(case2)" * doctest::test_suite("view::amax"))
{
    AMAX_SUBCASE( case2,   a, axis );
    AMAX_SUBCASE( case2, a_a, axis );
    AMAX_SUBCASE( case2, a_f, axis );
    // dynamic dim array not supported yet
    // AMAX_SUBCASE( case2, a_d, axis );
    AMAX_SUBCASE( case2, a_h, axis );
}

TEST_CASE("amax(case3)" * doctest::test_suite("view::amax"))
{
    AMAX_SUBCASE( case3,   a, axis );
    AMAX_SUBCASE( case3, a_a, axis );
    AMAX_SUBCASE( case3, a_f, axis );
    // dynamic dim array not supported yet
    // AMAX_SUBCASE( case3, a_d, axis );
    AMAX_SUBCASE( case3, a_h, axis );
}

TEST_CASE("amax(case4)" * doctest::test_suite("view::amax"))
{
    AMAX_SUBCASE( case4,   a, axis );
    AMAX_SUBCASE( case4, a_a, axis );
    AMAX_SUBCASE( case4, a_f, axis );
    // dynamic dim array not supported yet
    // AMAX_SUBCASE( case4, a_d, axis );
    AMAX_SUBCASE( case4, a_h, axis );
}

TEST_CASE("amax(case5)" * doctest::test_suite("view::amax"))
{
    AMAX_SUBCASE( case5,   a, axis );
    AMAX_SUBCASE( case5, a_a, axis );
    AMAX_SUBCASE( case5, a_f, axis );
    // dynamic dim array not supported yet
    // AMAX_SUBCASE( case5, a_d, axis );
    AMAX_SUBCASE( case5, a_h, axis );
}

TEST_CASE("amax(case6)" * doctest::test_suite("view::amax"))
{
    AMAX_SUBCASE( case6,   a, axis );
    AMAX_SUBCASE( case6, a_a, axis );
    AMAX_SUBCASE( case6, a_f, axis );
    // dynamic dim array not supported yet
    // AMAX_SUBCASE( case6, a_d, axis );
    AMAX_SUBCASE( case6, a_h, axis );
}

TEST_CASE("amax(case7)" * doctest::test_suite("view::amax"))
{
    AMAX_SUBCASE( case7,   a, axis, dtype, initial );
    AMAX_SUBCASE( case7, a_a, axis, dtype, initial );
    AMAX_SUBCASE( case7, a_f, axis, dtype, initial );
    AMAX_SUBCASE( case7, a_h, axis, dtype, initial );
}

TEST_CASE("amax(case8)" * doctest::test_suite("view::amax"))
{
    AMAX_SUBCASE( case8,   a, axis, dtype, initial, keepdims );
    AMAX_SUBCASE( case8, a_a, axis, dtype, initial, keepdims );
    AMAX_SUBCASE( case8, a_f, axis, dtype, initial, keepdims );
    AMAX_SUBCASE( case8, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("amax(case9)" * doctest::test_suite("view::amax"))
{
    AMAX_SUBCASE( case9,   a, axis, dtype, initial, keepdims );
    AMAX_SUBCASE( case9, a_a, axis, dtype, initial, keepdims );
    AMAX_SUBCASE( case9, a_f, axis, dtype, initial, keepdims );
    AMAX_SUBCASE( case9, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("amax(case10)" * doctest::test_suite("view::amax"))
{
    AMAX_SUBCASE( case10,   a, axis, dtype, initial, keepdims );
    AMAX_SUBCASE( case10, a_a, axis, dtype, initial, keepdims );
    AMAX_SUBCASE( case10, a_f, axis, dtype, initial, keepdims );
    AMAX_SUBCASE( case10, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("amax(case11)" * doctest::test_suite("view::amax"))
{
    AMAX_SUBCASE( case11,   a, axis, dtype, initial, keepdims );
    AMAX_SUBCASE( case11, a_a, axis, dtype, initial, keepdims );
    AMAX_SUBCASE( case11, a_f, axis, dtype, initial, keepdims );
    AMAX_SUBCASE( case11, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("amax(case12)" * doctest::test_suite("view::amax"))
{
    AMAX_SUBCASE( case12,   a, axis, dtype, initial, keepdims );
    AMAX_SUBCASE( case12, a_a, axis, dtype, initial, keepdims );
    AMAX_SUBCASE( case12, a_f, axis, dtype, initial, keepdims );
    AMAX_SUBCASE( case12, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("amax(case13)" * doctest::test_suite("view::amax"))
{
    AMAX_SUBCASE( case13,   a, axis );
    AMAX_SUBCASE( case13, a_a, axis );
    AMAX_SUBCASE( case13, a_f, axis );
    AMAX_SUBCASE( case13, a_h, axis );
}

TEST_CASE("amax(case14)" * doctest::test_suite("view::amax"))
{
    AMAX_SUBCASE( case14,   a, axis, nm::None, initial, keepdims );
    AMAX_SUBCASE( case14, a_a, axis, nm::None, initial, keepdims );
    AMAX_SUBCASE( case14, a_f, axis, nm::None, initial, keepdims );
    AMAX_SUBCASE( case14, a_h, axis, nm::None, initial, keepdims );
}

TEST_CASE("amax(case15)" * doctest::test_suite("view::amax"))
{
    AMAX_SUBCASE( case15,   a, axis, nm::None, initial, keepdims );
    AMAX_SUBCASE( case15, a_a, axis, nm::None, initial, keepdims );
    AMAX_SUBCASE( case15, a_f, axis, nm::None, initial, keepdims );
    AMAX_SUBCASE( case15, a_h, axis, nm::None, initial, keepdims );
}

TEST_CASE("amax(case16)" * doctest::test_suite("view::amax"))
{
    AMAX_SUBCASE( case16,   a, axis, nm::None, initial, keepdims );
    AMAX_SUBCASE( case16, a_a, axis, nm::None, initial, keepdims );
    AMAX_SUBCASE( case16, a_f, axis, nm::None, initial, keepdims );
    AMAX_SUBCASE( case16, a_h, axis, nm::None, initial, keepdims );
}

TEST_CASE("amax(case17)" * doctest::test_suite("view::amax"))
{
    AMAX_SUBCASE( case17,   a, axis, nm::None, initial, keepdims );
    AMAX_SUBCASE( case17, a_a, axis, nm::None, initial, keepdims );
    AMAX_SUBCASE( case17, a_f, axis, nm::None, initial, keepdims );
    AMAX_SUBCASE( case17, a_h, axis, nm::None, initial, keepdims );
}