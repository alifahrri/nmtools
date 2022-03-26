#include "nmtools/array/array/stddev.hpp"
#include "nmtools/testing/data/array/stddev.hpp"
#include "nmtools/testing/doctest.hpp"

#define RUN_stddev_impl(...) \
nmtools::array::stddev(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs stddev fn to callable lambda
#define RUN_stddev(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("array::stddev-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_stddev_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_stddev(case_name, ...) \
RUN_stddev_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define STDDEV_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, stddev, case_name); \
    using namespace args; \
    auto result = RUN_stddev(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

using nm::None;

TEST_CASE("stddev(case1)" * doctest::test_suite("array::stddev"))
{
    STDDEV_SUBCASE( case1, array, axis, None, ddof, keepdims );
    STDDEV_SUBCASE( case1, array_a, axis, None, ddof, keepdims );
    STDDEV_SUBCASE( case1, array_f, axis, None, ddof, keepdims );
    STDDEV_SUBCASE( case1, array_h, axis, None, ddof, keepdims );
    // not supportd yet
    // TODO: support slicing for dynamic dim
    // STDDEV_SUBCASE( case1, array_d, axis, None, ddof, keepdims );
}

TEST_CASE("stddev(case2)" * doctest::test_suite("array::stddev"))
{
    STDDEV_SUBCASE( case2, array, axis, None, ddof, keepdims );
    STDDEV_SUBCASE( case2, array_a, axis, None, ddof, keepdims );
    STDDEV_SUBCASE( case2, array_f, axis, None, ddof, keepdims );
    STDDEV_SUBCASE( case2, array_h, axis, None, ddof, keepdims );
    // not supportd yet
    // TODO: support slicing for dynamic dim
    // STDDEV_SUBCASE( case2, array_d, axis, None, ddof, keepdims );
}

TEST_CASE("stddev(case3)" * doctest::test_suite("array::stddev"))
{
    STDDEV_SUBCASE( case3, array, axis, None, ddof, keepdims );
    STDDEV_SUBCASE( case3, array_a, axis, None, ddof, keepdims );
    STDDEV_SUBCASE( case3, array_f, axis, None, ddof, keepdims );
    STDDEV_SUBCASE( case3, array_h, axis, None, ddof, keepdims );
    // not supportd yet
    // TODO: support slicing for dynamic dim
    // STDDEV_SUBCASE( case3, array_d, axis, None, ddof, keepdims );
}

TEST_CASE("stddev(case4)" * doctest::test_suite("array::stddev"))
{
    STDDEV_SUBCASE( case4, array, axis, None, ddof, keepdims );
    STDDEV_SUBCASE( case4, array_a, axis, None, ddof, keepdims );
    STDDEV_SUBCASE( case4, array_f, axis, None, ddof, keepdims );
    STDDEV_SUBCASE( case4, array_h, axis, None, ddof, keepdims );
    // not supportd yet
    // TODO: support slicing for dynamic dim
    // STDDEV_SUBCASE( case4, array_d, axis, None, ddof, keepdims );
}


TEST_CASE("stddev(case5)" * doctest::test_suite("array::stddev"))
{
    STDDEV_SUBCASE( case5, array, axis, None, ddof, keepdims );
    STDDEV_SUBCASE( case5, array_a, axis, None, ddof, keepdims );
    STDDEV_SUBCASE( case5, array_f, axis, None, ddof, keepdims );
    STDDEV_SUBCASE( case5, array_h, axis, None, ddof, keepdims );
    // not supportd yet
    // TODO: support slicing for dynamic dim
    // STDDEV_SUBCASE( case5, array_d, axis, None, ddof, keepdims );
}

TEST_CASE("stddev(case6)" * doctest::test_suite("array::stddev"))
{
    STDDEV_SUBCASE( case6, array, axis, None, ddof, keepdims );
    STDDEV_SUBCASE( case6, array_a, axis, None, ddof, keepdims );
    STDDEV_SUBCASE( case6, array_f, axis, None, ddof, keepdims );
    STDDEV_SUBCASE( case6, array_h, axis, None, ddof, keepdims );
    // not supportd yet
    // TODO: support slicing for dynamic dim
    // STDDEV_SUBCASE( case6, array_d, axis, None, ddof, keepdims );
}

TEST_CASE("stddev(case7)" * doctest::test_suite("array::stddev"))
{
    STDDEV_SUBCASE( case7, array, axis, None, ddof, keepdims );
    STDDEV_SUBCASE( case7, array_a, axis, None, ddof, keepdims );
    STDDEV_SUBCASE( case7, array_f, axis, None, ddof, keepdims );
    STDDEV_SUBCASE( case7, array_h, axis, None, ddof, keepdims );
    // not supportd yet
    // TODO: support slicing for dynamic dim
    // STDDEV_SUBCASE( case7, array_d, axis, None, ddof, keepdims );
}

TEST_CASE("stddev(case8)" * doctest::test_suite("array::stddev"))
{
    STDDEV_SUBCASE( case8, array, axis, None, ddof, keepdims );
    STDDEV_SUBCASE( case8, array_a, axis, None, ddof, keepdims );
    STDDEV_SUBCASE( case8, array_f, axis, None, ddof, keepdims );
    STDDEV_SUBCASE( case8, array_h, axis, None, ddof, keepdims );
    // not supportd yet
    // TODO: support slicing for dynamic dim
    // STDDEV_SUBCASE( case8, array_d, axis, None, ddof, keepdims );
}

TEST_CASE("stddev(case9)" * doctest::test_suite("array::stddev"))
{
    STDDEV_SUBCASE( case9, array, axis, None, ddof, keepdims );
    STDDEV_SUBCASE( case9, array_a, axis, None, ddof, keepdims );
    STDDEV_SUBCASE( case9, array_f, axis, None, ddof, keepdims );
    STDDEV_SUBCASE( case9, array_h, axis, None, ddof, keepdims );
    // not supportd yet
    // TODO: support slicing for dynamic dim
    // STDDEV_SUBCASE( case9, array_d, axis, None, ddof, keepdims );
}

TEST_CASE("stddev(case10)" * doctest::test_suite("array::stddev"))
{
    STDDEV_SUBCASE( case10, array, axis, None, ddof, keepdims );
    STDDEV_SUBCASE( case10, array_a, axis, None, ddof, keepdims );
    STDDEV_SUBCASE( case10, array_f, axis, None, ddof, keepdims );
    STDDEV_SUBCASE( case10, array_h, axis, None, ddof, keepdims );
    // not supportd yet
    // TODO: support slicing for dynamic dim
    // STDDEV_SUBCASE( case10, array_d, axis, None, ddof, keepdims );
}

TEST_CASE("stddev(case11)" * doctest::test_suite("array::stddev"))
{
    STDDEV_SUBCASE( case11, array, axis, None, ddof, keepdims );
    STDDEV_SUBCASE( case11, array_a, axis, None, ddof, keepdims );
    STDDEV_SUBCASE( case11, array_f, axis, None, ddof, keepdims );
    STDDEV_SUBCASE( case11, array_h, axis, None, ddof, keepdims );
    // not supportd yet
    // TODO: support slicing for dynamic dim
    // STDDEV_SUBCASE( case11, array_d, axis, None, ddof, keepdims );
}

TEST_CASE("stddev(case12)" * doctest::test_suite("array::stddev"))
{
    STDDEV_SUBCASE( case12, array, axis, None, ddof, keepdims );
    STDDEV_SUBCASE( case12, array_a, axis, None, ddof, keepdims );
    STDDEV_SUBCASE( case12, array_f, axis, None, ddof, keepdims );
    STDDEV_SUBCASE( case12, array_h, axis, None, ddof, keepdims );
    // not supportd yet
    // TODO: support slicing for dynamic dim
    // STDDEV_SUBCASE( case12, array_d, axis, None, ddof, keepdims );
}

TEST_CASE("stddev(case13)" * doctest::test_suite("array::stddev"))
{
    STDDEV_SUBCASE( case13, array, axis, None, ddof, keepdims );
    STDDEV_SUBCASE( case13, array_a, axis, None, ddof, keepdims );
    STDDEV_SUBCASE( case13, array_f, axis, None, ddof, keepdims );
    STDDEV_SUBCASE( case13, array_h, axis, None, ddof, keepdims );
    // not supportd yet
    // TODO: support slicing for dynamic dim
    // STDDEV_SUBCASE( case13, array_d, axis, None, ddof, keepdims );
}

TEST_CASE("stddev(case14)" * doctest::test_suite("array::stddev"))
{
    STDDEV_SUBCASE( case14, array, axis, None, ddof, keepdims );
    STDDEV_SUBCASE( case14, array_a, axis, None, ddof, keepdims );
    STDDEV_SUBCASE( case14, array_f, axis, None, ddof, keepdims );
    STDDEV_SUBCASE( case14, array_h, axis, None, ddof, keepdims );
    // not supportd yet
    // TODO: support slicing for dynamic dim
    // STDDEV_SUBCASE( case14, array_d, axis, None, ddof, keepdims );
}

TEST_CASE("stddev(case15)" * doctest::test_suite("array::stddev"))
{
    STDDEV_SUBCASE( case15, array, axis, None, ddof, keepdims );
    STDDEV_SUBCASE( case15, array_a, axis, None, ddof, keepdims );
    STDDEV_SUBCASE( case15, array_f, axis, None, ddof, keepdims );
    STDDEV_SUBCASE( case15, array_h, axis, None, ddof, keepdims );
    // not supportd yet
    // TODO: support slicing for dynamic dim
    // STDDEV_SUBCASE( case15, array_d, axis, None, ddof, keepdims );
}

TEST_CASE("stddev(case16)" * doctest::test_suite("array::stddev"))
{
    STDDEV_SUBCASE( case16, array, axis, None, ddof, keepdims );
    STDDEV_SUBCASE( case16, array_a, axis, None, ddof, keepdims );
    STDDEV_SUBCASE( case16, array_f, axis, None, ddof, keepdims );
    STDDEV_SUBCASE( case16, array_h, axis, None, ddof, keepdims );
    // not supportd yet
    // TODO: support slicing for dynamic dim
    // STDDEV_SUBCASE( case16, array_d, axis, None, ddof, keepdims );
}

TEST_CASE("stddev(case17)" * doctest::test_suite("array::stddev"))
{
    STDDEV_SUBCASE( case17, array, axis, None, ddof, keepdims );
    STDDEV_SUBCASE( case17, array_a, axis, None, ddof, keepdims );
    STDDEV_SUBCASE( case17, array_f, axis, None, ddof, keepdims );
    STDDEV_SUBCASE( case17, array_h, axis, None, ddof, keepdims );
    // not supportd yet
    // TODO: support slicing for dynamic dim
    // STDDEV_SUBCASE( case17, array_d, axis, None, ddof, keepdims );
}