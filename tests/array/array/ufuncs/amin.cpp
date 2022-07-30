#include "nmtools/array/array/ufuncs/amin.hpp"
#include "nmtools/testing/data/array/minimum.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;

#define RUN_amin_impl(...) \
nm::array::amin(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs amin fn to callable lambda
#define RUN_amin(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("amin-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_amin_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_amin(case_name, ...) \
RUN_amin_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define AMIN_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, reduce_minimum, case_name); \
    using namespace args; \
    auto result = RUN_amin(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}


TEST_CASE("amin(case1)" * doctest::test_suite("array::amin"))
{
    AMIN_SUBCASE( case1,   a, axis );
    AMIN_SUBCASE( case1, a_a, axis );
    AMIN_SUBCASE( case1, a_f, axis );
    // dynamic dim array not supported yet
    // AMIN_SUBCASE( case1, a_d, axis );
    AMIN_SUBCASE( case1, a_h, axis );
}

TEST_CASE("amin(case2)" * doctest::test_suite("array::amin"))
{
    AMIN_SUBCASE( case2,   a, axis );
    AMIN_SUBCASE( case2, a_a, axis );
    AMIN_SUBCASE( case2, a_f, axis );
    // dynamic dim array not supported yet
    // AMIN_SUBCASE( case2, a_d, axis );
    AMIN_SUBCASE( case2, a_h, axis );
}

TEST_CASE("amin(case3)" * doctest::test_suite("array::amin"))
{
    AMIN_SUBCASE( case3,   a, axis );
    AMIN_SUBCASE( case3, a_a, axis );
    AMIN_SUBCASE( case3, a_f, axis );
    // dynamic dim array not supported yet
    // AMIN_SUBCASE( case3, a_d, axis );
    AMIN_SUBCASE( case3, a_h, axis );
}

TEST_CASE("amin(case4)" * doctest::test_suite("array::amin"))
{
    AMIN_SUBCASE( case4,   a, axis );
    AMIN_SUBCASE( case4, a_a, axis );
    AMIN_SUBCASE( case4, a_f, axis );
    // dynamic dim array not supported yet
    // AMIN_SUBCASE( case4, a_d, axis );
    AMIN_SUBCASE( case4, a_h, axis );
}

TEST_CASE("amin(case5)" * doctest::test_suite("array::amin"))
{
    AMIN_SUBCASE( case5,   a, axis );
    AMIN_SUBCASE( case5, a_a, axis );
    AMIN_SUBCASE( case5, a_f, axis );
    // dynamic dim array not supported yet
    // AMIN_SUBCASE( case5, a_d, axis );
    AMIN_SUBCASE( case5, a_h, axis );
}

TEST_CASE("amin(case6)" * doctest::test_suite("array::amin"))
{
    AMIN_SUBCASE( case6,   a, axis );
    AMIN_SUBCASE( case6, a_a, axis );
    AMIN_SUBCASE( case6, a_f, axis );
    // dynamic dim array not supported yet
    // AMIN_SUBCASE( case6, a_d, axis );
    AMIN_SUBCASE( case6, a_h, axis );
}

TEST_CASE("amin(case7)" * doctest::test_suite("array::amin"))
{
    AMIN_SUBCASE( case7,   a, axis, dtype, initial );
    AMIN_SUBCASE( case7, a_a, axis, dtype, initial );
    AMIN_SUBCASE( case7, a_f, axis, dtype, initial );
    AMIN_SUBCASE( case7, a_h, axis, dtype, initial );
}

TEST_CASE("amin(case8)" * doctest::test_suite("array::amin"))
{
    AMIN_SUBCASE( case8,   a, axis, dtype, initial, keepdims );
    AMIN_SUBCASE( case8, a_a, axis, dtype, initial, keepdims );
    AMIN_SUBCASE( case8, a_f, axis, dtype, initial, keepdims );
    AMIN_SUBCASE( case8, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("amin(case9)" * doctest::test_suite("array::amin"))
{
    AMIN_SUBCASE( case9,   a, axis, dtype, initial, keepdims );
    AMIN_SUBCASE( case9, a_a, axis, dtype, initial, keepdims );
    AMIN_SUBCASE( case9, a_f, axis, dtype, initial, keepdims );
    AMIN_SUBCASE( case9, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("amin(case10)" * doctest::test_suite("array::amin"))
{
    AMIN_SUBCASE( case10,   a, axis, dtype, initial, keepdims );
    AMIN_SUBCASE( case10, a_a, axis, dtype, initial, keepdims );
    AMIN_SUBCASE( case10, a_f, axis, dtype, initial, keepdims );
    AMIN_SUBCASE( case10, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("amin(case11)" * doctest::test_suite("array::amin"))
{
    AMIN_SUBCASE( case11,   a, axis, dtype, initial, keepdims );
    AMIN_SUBCASE( case11, a_a, axis, dtype, initial, keepdims );
    AMIN_SUBCASE( case11, a_f, axis, dtype, initial, keepdims );
    AMIN_SUBCASE( case11, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("amin(case12)" * doctest::test_suite("array::amin"))
{
    AMIN_SUBCASE( case12,   a, axis, dtype, initial, keepdims );
    AMIN_SUBCASE( case12, a_a, axis, dtype, initial, keepdims );
    AMIN_SUBCASE( case12, a_f, axis, dtype, initial, keepdims );
    AMIN_SUBCASE( case12, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("amin(case13)" * doctest::test_suite("array::amin"))
{
    AMIN_SUBCASE( case13,   a, axis );
    AMIN_SUBCASE( case13, a_a, axis );
    AMIN_SUBCASE( case13, a_f, axis );
    AMIN_SUBCASE( case13, a_h, axis );
}

TEST_CASE("amin(case14)" * doctest::test_suite("array::amin"))
{
    AMIN_SUBCASE( case14,   a, axis, nm::None, initial, keepdims );
    AMIN_SUBCASE( case14, a_a, axis, nm::None, initial, keepdims );
    AMIN_SUBCASE( case14, a_f, axis, nm::None, initial, keepdims );
    AMIN_SUBCASE( case14, a_h, axis, nm::None, initial, keepdims );
}

TEST_CASE("amin(case15)" * doctest::test_suite("array::amin"))
{
    AMIN_SUBCASE( case15,   a, axis, nm::None, initial, keepdims );
    AMIN_SUBCASE( case15, a_a, axis, nm::None, initial, keepdims );
    AMIN_SUBCASE( case15, a_f, axis, nm::None, initial, keepdims );
    AMIN_SUBCASE( case15, a_h, axis, nm::None, initial, keepdims );
}

TEST_CASE("amin(case16)" * doctest::test_suite("array::amin"))
{
    AMIN_SUBCASE( case16,   a, axis, nm::None, initial, keepdims );
    AMIN_SUBCASE( case16, a_a, axis, nm::None, initial, keepdims );
    AMIN_SUBCASE( case16, a_f, axis, nm::None, initial, keepdims );
    AMIN_SUBCASE( case16, a_h, axis, nm::None, initial, keepdims );
}

TEST_CASE("amin(case17)" * doctest::test_suite("array::amin"))
{
    AMIN_SUBCASE( case17,   a, axis, nm::None, initial, keepdims );
    AMIN_SUBCASE( case17, a_a, axis, nm::None, initial, keepdims );
    AMIN_SUBCASE( case17, a_f, axis, nm::None, initial, keepdims );
    AMIN_SUBCASE( case17, a_h, axis, nm::None, initial, keepdims );
}