#include "nmtools/array/array/var.hpp"
#include "nmtools/testing/data/array/var.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;

#define RUN_var_impl(...) \
nmtools::array::var(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs var fn to callable lambda
#define RUN_var(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("array::var-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_var_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_var(case_name, ...) \
RUN_var_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define VAR_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, var, case_name); \
    using namespace args; \
    auto result = RUN_var(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("var(case1)" * doctest::test_suite("array::var"))
{
    VAR_SUBCASE( case1, array, axis );
    VAR_SUBCASE( case1, array_a, axis_a );
    VAR_SUBCASE( case1, array_f, axis_f );
    VAR_SUBCASE( case1, array_h, axis );
    // not supported yet,
    // TODO: support slicing for dynamic dim
    // VAR_SUBCASE( case1, array_d, axis );
}

TEST_CASE("var(case2)" * doctest::test_suite("array::var"))
{
    VAR_SUBCASE( case2, array, axis );
    VAR_SUBCASE( case2, array_a, axis_a );
    VAR_SUBCASE( case2, array_f, axis_f );
    VAR_SUBCASE( case2, array_h, axis );
    // not supported yet,
    // TODO: support slicing for dynamic dim
    // VAR_SUBCASE( case2, array_d, axis );
}

TEST_CASE("var(case3)" * doctest::test_suite("array::var"))
{
    VAR_SUBCASE( case3, array, axis );
    VAR_SUBCASE( case3, array_a, axis );
    VAR_SUBCASE( case3, array_f, axis );
    VAR_SUBCASE( case3, array_h, axis );
    // not supported yet,
    // TODO: support slicing for dynamic dim
    // VAR_SUBCASE( case3, array_d, axis );
}

TEST_CASE("var(case4)" * doctest::test_suite("array::var"))
{
    VAR_SUBCASE( case4, array, axis );
    VAR_SUBCASE( case4, array_a, axis );
    VAR_SUBCASE( case4, array_f, axis );
    VAR_SUBCASE( case4, array_h, axis );
    // not supported yet,
    // TODO: support slicing for dynamic dim
    // VAR_SUBCASE( case4, array_d, axis );
}

TEST_CASE("var(case5)" * doctest::test_suite("array::var"))
{
    VAR_SUBCASE( case5, array, axis );
    VAR_SUBCASE( case5, array_a, axis );
    VAR_SUBCASE( case5, array_f, axis );
    VAR_SUBCASE( case5, array_h, axis );
    // not supported yet,
    // TODO: support slicing for dynamic dim
    // VAR_SUBCASE( case5, array_d, axis );
}

TEST_CASE("var(case6)" * doctest::test_suite("array::var"))
{
    VAR_SUBCASE( case6,   array, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case6, array_a, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case6, array_f, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case6, array_h, axis, nm::None, ddof, keepdims );
    // not supported yet,
    // TODO: support slicing for dynamic dim
    // VAR_SUBCASE( case6, array_d, axis, nm::None, ddof, keepdims );
}

TEST_CASE("var(case7)" * doctest::test_suite("array::var"))
{
    VAR_SUBCASE( case7,   array, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case7, array_a, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case7, array_f, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case7, array_h, axis, nm::None, ddof, keepdims );
    // not supported yet,
    // TODO: support slicing for dynamic dim
    // VAR_SUBCASE( case7, array_d, axis, nm::None, ddof, keepdims );
}

TEST_CASE("var(case8)" * doctest::test_suite("array::var"))
{
    VAR_SUBCASE( case8,   array, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case8, array_a, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case8, array_f, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case8, array_h, axis, nm::None, ddof, keepdims );
    // not supported yet,
    // TODO: support slicing for dynamic dim
    // VAR_SUBCASE( case7, array_d, axis, nm::None, ddof, keepdims );
}

TEST_CASE("var(case9)" * doctest::test_suite("array::var"))
{
    // TODO: fix segfault, likely because of buggy utl::either utl::maybe composition
    #ifndef NMTOOLS_DISABLE_STL
    VAR_SUBCASE( case9,   array, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case9, array_a, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case9, array_f, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case9, array_h, axis, nm::None, ddof, keepdims );
    #endif
    // not supported yet,
    // TODO: support slicing for dynamic dim
    // VAR_SUBCASE( case9, array_d, axis, nm::None, ddof, keepdims );
}

TEST_CASE("var(case10)" * doctest::test_suite("array::var"))
{

    VAR_SUBCASE( case10,   array, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case10, array_a, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case10, array_f, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case10, array_h, axis, nm::None, ddof, keepdims );
    // not supported yet,
    // TODO: support slicing for dynamic dim
    // VAR_SUBCASE( case10, array_d, axis, nm::None, ddof, keepdims );
}

TEST_CASE("var(case11)" * doctest::test_suite("array::var"))
{
    VAR_SUBCASE( case11,   array, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case11, array_a, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case11, array_f, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case11, array_h, axis, nm::None, ddof, keepdims );
    // not supported yet,
    // TODO: support slicing for dynamic dim
    // VAR_SUBCASE( case11, array_d, axis, nm::None, ddof, keepdims );
}

TEST_CASE("var(case12)" * doctest::test_suite("array::var"))
{
    VAR_SUBCASE( case12,   array, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case12, array_a, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case12, array_f, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case12, array_h, axis, nm::None, ddof, keepdims );
    // not supported yet,
    // TODO: support slicing for dynamic dim
    // VAR_SUBCASE( case12, array_d, axis, nm::None, ddof, keepdims );
}

TEST_CASE("var(case13)" * doctest::test_suite("array::var"))
{
    VAR_SUBCASE( case13,   array, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case13, array_a, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case13, array_f, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case13, array_h, axis, nm::None, ddof, keepdims );
    // not supported yet,
    // TODO: support slicing for dynamic dim
    // VAR_SUBCASE( case13, array_d, axis, nm::None, ddof, keepdims );
}

TEST_CASE("var(case14)" * doctest::test_suite("array::var"))
{
    VAR_SUBCASE( case14,   array, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case14, array_a, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case14, array_f, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case14, array_h, axis, nm::None, ddof, keepdims );
    // not supported yet,
    // TODO: support slicing for dynamic dim
    // VAR_SUBCASE( case14, array_d, axis, nm::None, ddof, keepdims );
}