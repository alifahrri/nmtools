#include "nmtools/array/prod.hpp"
#include "nmtools/testing/data/array/multiply.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nmtools;
namespace array = nmtools;

#define RUN_prod_impl(...) \
nmtools::prod(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs prod fn to callable lambda
#define RUN_prod(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("prod-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_prod_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_prod(case_name, ...) \
RUN_prod_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define PROD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    /* using test case from reduce_multiply since they're basically the same */ \
    NMTOOLS_TESTING_USE_CASE(view, reduce_multiply, case_name); \
    using namespace args; \
    auto result = RUN_prod(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("prod(case1)" * doctest::test_suite("array::prod"))
{
    PROD_SUBCASE( case1,   a, axis );
    PROD_SUBCASE( case1, a_a, axis );
    PROD_SUBCASE( case1, a_f, axis );
    // reduce doesnt work with dynamic ndarray for now
    // PROD_SUBCASE( case1, a_d, axis );
    PROD_SUBCASE( case1, a_h, axis );
}

TEST_CASE("prod(case2)" * doctest::test_suite("array::prod"))
{
    PROD_SUBCASE( case2,   a, axis );
    PROD_SUBCASE( case2, a_a, axis );
    PROD_SUBCASE( case2, a_f, axis );
    PROD_SUBCASE( case2, a_h, axis );
}

TEST_CASE("prod(case3)" * doctest::test_suite("array::prod"))
{
    PROD_SUBCASE( case3,   a, axis );
    PROD_SUBCASE( case3, a_a, axis );
    PROD_SUBCASE( case3, a_f, axis );
    PROD_SUBCASE( case3, a_h, axis );
}

TEST_CASE("prod(case4)" * doctest::test_suite("array::prod"))
{
    PROD_SUBCASE( case4,   a, axis );
    PROD_SUBCASE( case4, a_a, axis );
    PROD_SUBCASE( case4, a_f, axis );
    PROD_SUBCASE( case4, a_h, axis );
}

TEST_CASE("prod(case5)" * doctest::test_suite("array::prod"))
{
    PROD_SUBCASE( case5,   a, axis );
    PROD_SUBCASE( case5, a_a, axis );
    PROD_SUBCASE( case5, a_f, axis );
    PROD_SUBCASE( case5, a_h, axis );
}

TEST_CASE("prod(case6)" * doctest::test_suite("array::prod"))
{
    PROD_SUBCASE( case6,   a, axis );
    PROD_SUBCASE( case6, a_a, axis );
    PROD_SUBCASE( case6, a_f, axis );
    PROD_SUBCASE( case6, a_h, axis );
}

// TEST_CASE("prod(case7)" * doctest::test_suite("array::prod"))
// {
//     PROD_SUBCASE( case7,   a, axis );
//     PROD_SUBCASE( case7, a_a, axis 
//     PROD_SUBCASE( case7, a_f, axis );
//     PROD_SUBCASE( case7, a_h, axis );
// }

TEST_CASE("prod(case8)" * doctest::test_suite("array::prod"))
{
    PROD_SUBCASE( case8,   a, axis, dtype, initial );
    PROD_SUBCASE( case8, a_a, axis, dtype, initial );
    PROD_SUBCASE( case8, a_f, axis, dtype, initial );
    PROD_SUBCASE( case8, a_h, axis, dtype, initial );
}

TEST_CASE("prod(case9)" * doctest::test_suite("array::prod"))
{
    PROD_SUBCASE( case9,   a, axis, dtype, initial, keepdims );
    PROD_SUBCASE( case9, a_a, axis, dtype, initial, keepdims );
    PROD_SUBCASE( case9, a_f, axis, dtype, initial, keepdims );
    PROD_SUBCASE( case9, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("prod(case10)" * doctest::test_suite("array::prod"))
{
    PROD_SUBCASE( case10,   a, axis, dtype, initial, keepdims );
    PROD_SUBCASE( case10, a_a, axis, dtype, initial, keepdims );
    PROD_SUBCASE( case10, a_f, axis, dtype, initial, keepdims );
    PROD_SUBCASE( case10, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("prod(case11)" * doctest::test_suite("array::prod"))
{
    PROD_SUBCASE( case11,   a, axis, dtype, initial, keepdims );
    PROD_SUBCASE( case11, a_a, axis, dtype, initial, keepdims );
    PROD_SUBCASE( case11, a_f, axis, dtype, initial, keepdims );
    PROD_SUBCASE( case11, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("prod(case12)" * doctest::test_suite("array::prod"))
{
    PROD_SUBCASE( case12,   a, axis, dtype, initial, keepdims );
    PROD_SUBCASE( case12, a_a, axis, dtype, initial, keepdims );
    PROD_SUBCASE( case12, a_f, axis, dtype, initial, keepdims );
    PROD_SUBCASE( case12, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("prod(case13)" * doctest::test_suite("array::prod"))
{
    PROD_SUBCASE( case13,   a, axis, dtype, initial, keepdims );
    PROD_SUBCASE( case13, a_a, axis, dtype, initial, keepdims );
    PROD_SUBCASE( case13, a_f, axis, dtype, initial, keepdims );
    PROD_SUBCASE( case13, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("prod(case14)" * doctest::test_suite("array::prod"))
{
    PROD_SUBCASE( case14,   a, axis );
    PROD_SUBCASE( case14, a_a, axis );
    PROD_SUBCASE( case14, a_f, axis );
    PROD_SUBCASE( case14, a_h, axis );
}

TEST_CASE("prod(case15)" * doctest::test_suite("array::prod"))
{
    PROD_SUBCASE( case15,   a, axis, nm::None, initial, keepdims );
    PROD_SUBCASE( case15, a_a, axis, nm::None, initial, keepdims );
    PROD_SUBCASE( case15, a_f, axis, nm::None, initial, keepdims );
    PROD_SUBCASE( case15, a_h, axis, nm::None, initial, keepdims );
}

TEST_CASE("prod(case16)" * doctest::test_suite("array::prod"))
{
    PROD_SUBCASE( case16,   a, axis, nm::None, initial, keepdims );
    PROD_SUBCASE( case16, a_a, axis, nm::None, initial, keepdims );
    PROD_SUBCASE( case16, a_f, axis, nm::None, initial, keepdims );
    PROD_SUBCASE( case16, a_h, axis, nm::None, initial, keepdims );
}

TEST_CASE("prod(case17)" * doctest::test_suite("array::prod"))
{
    PROD_SUBCASE( case17,   a, axis, nm::None, initial, keepdims );
    PROD_SUBCASE( case17, a_a, axis, nm::None, initial, keepdims );
    PROD_SUBCASE( case17, a_f, axis, nm::None, initial, keepdims );
    PROD_SUBCASE( case17, a_h, axis, nm::None, initial, keepdims );
}

TEST_CASE("prod(case18)" * doctest::test_suite("array::prod"))
{
    PROD_SUBCASE( case18,   a, axis, nm::None, initial, keepdims );
    PROD_SUBCASE( case18, a_a, axis, nm::None, initial, keepdims );
    PROD_SUBCASE( case18, a_f, axis, nm::None, initial, keepdims );
    PROD_SUBCASE( case18, a_h, axis, nm::None, initial, keepdims );
}