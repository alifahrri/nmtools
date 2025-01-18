#include "nmtools/array/sliding_window.hpp"
#include "nmtools/testing/data/array/sliding_window.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace fn = nm::functional;
namespace view = nm::view;

using nmtools::unwrap;

#define SLIDING_WINDOW_SUBCASE(case_name, function, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, sliding_window, case_name); \
    using namespace args; \
    auto result = function (__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect::expected) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}

TEST_CASE("sliding_window(case1)" * doctest::test_suite("functional::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case1, fn::sliding_window[window_shape], x );
    SLIDING_WINDOW_SUBCASE( case1, fn::sliding_window[window_shape], x_a );
    SLIDING_WINDOW_SUBCASE( case1, fn::sliding_window[window_shape], x_f );
    SLIDING_WINDOW_SUBCASE( case1, fn::sliding_window[window_shape], x_h );
    SLIDING_WINDOW_SUBCASE( case1, fn::sliding_window[window_shape], x_d );
}

TEST_CASE("sliding_window(case2)" * doctest::test_suite("functional::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case2, fn::sliding_window[window_shape], x );
    SLIDING_WINDOW_SUBCASE( case2, fn::sliding_window[window_shape], x_a );
    SLIDING_WINDOW_SUBCASE( case2, fn::sliding_window[window_shape], x_f );
    SLIDING_WINDOW_SUBCASE( case2, fn::sliding_window[window_shape], x_h );
    SLIDING_WINDOW_SUBCASE( case2, fn::sliding_window[window_shape], x_d );
}

TEST_CASE("sliding_window(case3)" * doctest::test_suite("functional::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case3, fn::sliding_window[window_shape][axis], x );
    SLIDING_WINDOW_SUBCASE( case3, fn::sliding_window[window_shape][axis], x_a );
    SLIDING_WINDOW_SUBCASE( case3, fn::sliding_window[window_shape][axis], x_f );
    SLIDING_WINDOW_SUBCASE( case3, fn::sliding_window[window_shape][axis], x_h );
    SLIDING_WINDOW_SUBCASE( case3, fn::sliding_window[window_shape][axis], x_d );
}

TEST_CASE("sliding_window(case4)" * doctest::test_suite("functional::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case4, fn::sliding_window[window_shape][axis], x );
    SLIDING_WINDOW_SUBCASE( case4, fn::sliding_window[window_shape][axis], x_a );
    SLIDING_WINDOW_SUBCASE( case4, fn::sliding_window[window_shape][axis], x_f );
    SLIDING_WINDOW_SUBCASE( case4, fn::sliding_window[window_shape][axis], x_h );
    SLIDING_WINDOW_SUBCASE( case4, fn::sliding_window[window_shape][axis], x_d );
}

TEST_CASE("sliding_window(case5)" * doctest::test_suite("functional::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case5, fn::sliding_window[window_shape], x );
    SLIDING_WINDOW_SUBCASE( case5, fn::sliding_window[window_shape], x_a );
    SLIDING_WINDOW_SUBCASE( case5, fn::sliding_window[window_shape], x_f );
    SLIDING_WINDOW_SUBCASE( case5, fn::sliding_window[window_shape], x_h );
    SLIDING_WINDOW_SUBCASE( case5, fn::sliding_window[window_shape], x_d );
}

TEST_CASE("sliding_window(case6)" * doctest::test_suite("functional::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case6, fn::sliding_window[window_shape][axis], x );
    SLIDING_WINDOW_SUBCASE( case6, fn::sliding_window[window_shape][axis], x_a );
    SLIDING_WINDOW_SUBCASE( case6, fn::sliding_window[window_shape][axis], x_f );
    SLIDING_WINDOW_SUBCASE( case6, fn::sliding_window[window_shape][axis], x_h );
    SLIDING_WINDOW_SUBCASE( case6, fn::sliding_window[window_shape][axis], x_d );
}

TEST_CASE("sliding_window(case7)" * doctest::test_suite("functional::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case7, fn::sliding_window[window_shape][axis], x );
    SLIDING_WINDOW_SUBCASE( case7, fn::sliding_window[window_shape][axis], x_a );
    SLIDING_WINDOW_SUBCASE( case7, fn::sliding_window[window_shape][axis], x_f );
    SLIDING_WINDOW_SUBCASE( case7, fn::sliding_window[window_shape][axis], x_h );
    SLIDING_WINDOW_SUBCASE( case7, fn::sliding_window[window_shape][axis], x_d );
}

TEST_CASE("sliding_window(case8)" * doctest::test_suite("functional::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case8, fn::sliding_window[window_shape][axis], x );
    SLIDING_WINDOW_SUBCASE( case8, fn::sliding_window[window_shape][axis], x_a );
    SLIDING_WINDOW_SUBCASE( case8, fn::sliding_window[window_shape][axis], x_f );
    SLIDING_WINDOW_SUBCASE( case8, fn::sliding_window[window_shape][axis], x_h );
    SLIDING_WINDOW_SUBCASE( case8, fn::sliding_window[window_shape][axis], x_d );
}

TEST_CASE("sliding_window(case9)" * doctest::test_suite("functional::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case9, fn::sliding_window[window_shape], x );
    SLIDING_WINDOW_SUBCASE( case9, fn::sliding_window[window_shape], x_a );
    SLIDING_WINDOW_SUBCASE( case9, fn::sliding_window[window_shape], x_f );
    SLIDING_WINDOW_SUBCASE( case9, fn::sliding_window[window_shape], x_h );
    SLIDING_WINDOW_SUBCASE( case9, fn::sliding_window[window_shape], x_d );
}

TEST_CASE("sliding_window(case10)" * doctest::test_suite("functional::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case10, fn::sliding_window[window_shape][axis], x );
    SLIDING_WINDOW_SUBCASE( case10, fn::sliding_window[window_shape][axis], x_a );
    SLIDING_WINDOW_SUBCASE( case10, fn::sliding_window[window_shape][axis], x_f );
    SLIDING_WINDOW_SUBCASE( case10, fn::sliding_window[window_shape][axis], x_h );
    SLIDING_WINDOW_SUBCASE( case10, fn::sliding_window[window_shape][axis], x_d );
}

TEST_CASE("sliding_window(case11)" * doctest::test_suite("functional::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case11, fn::sliding_window[window_shape][axis], x );
    SLIDING_WINDOW_SUBCASE( case11, fn::sliding_window[window_shape][axis], x_a );
    SLIDING_WINDOW_SUBCASE( case11, fn::sliding_window[window_shape][axis], x_f );
    SLIDING_WINDOW_SUBCASE( case11, fn::sliding_window[window_shape][axis], x_h );
    SLIDING_WINDOW_SUBCASE( case11, fn::sliding_window[window_shape][axis], x_d );
}

TEST_CASE("sliding_window" * doctest::test_suite("functional::get_function_composition") * doctest::may_fail())
{
    NMTOOLS_TESTING_USE_CASE(array,sliding_window,case1);
    using namespace args;

    auto a = view::sliding_window(x,window_shape);

    auto function = fn::get_function_composition(a);
    // auto expect   = fn::sliding_window[window_shape][axis];
    auto expect = fn::indexing[unwrap(a).attributes()];

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_EQUAL( function(x), a );
}

TEST_CASE("sliding_window" * doctest::test_suite("functional::get_function_composition") * doctest::may_fail())
{
    NMTOOLS_TESTING_USE_CASE(array,sliding_window,case3);
    using namespace args;

    auto a = view::sliding_window(x,window_shape,axis);

    auto function = fn::get_function_composition(a);
    // auto expect   = fn::sliding_window[window_shape][axis];
    auto expect = fn::indexing[unwrap(a).attributes()];

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_EQUAL( function(x), a );
}