#include "nmtools/array/functional/ufuncs/multiply.hpp"
#include "nmtools/testing/data/array/multiply.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace fn = nm::functional;

#define FUNCTIONAL_SUBCASE(subcase_name, function, ...) \
SUBCASE(subcase_name) \
{ \
    auto result = function (__VA_ARGS__); \
    NMTOOLS_REQUIRE_EQUAL( nm::shape(result), nm::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define CURRY_BINARY_SUBCASE(subcase_name, function, lhs, rhs) \
SUBCASE(subcase_name) \
{ \
    auto result = function (lhs) (rhs); \
    NMTOOLS_REQUIRE_EQUAL( nm::shape(result), nm::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("multiply(case1)" * doctest::test_suite("functional::multiply"))
{
    // TODO: rename namespace to (array, multiply)
    NMTOOLS_TESTING_DECLARE_NS(view, multiply, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::multiply, a, b );
    FUNCTIONAL_SUBCASE( "case1", fn::multiply, a_a, b_a );
    FUNCTIONAL_SUBCASE( "case1", fn::multiply, a_f, b_f );
    FUNCTIONAL_SUBCASE( "case1", fn::multiply, a_h, b_h );
    FUNCTIONAL_SUBCASE( "case1", fn::multiply, a_d, b_d );

    CURRY_BINARY_SUBCASE( "case1", fn::multiply, a, b );
    CURRY_BINARY_SUBCASE( "case1", fn::multiply, a_a, b_a );
    CURRY_BINARY_SUBCASE( "case1", fn::multiply, a_f, b_f );
    CURRY_BINARY_SUBCASE( "case1", fn::multiply, a_h, b_h );
    CURRY_BINARY_SUBCASE( "case1", fn::multiply, a_d, b_d );
}

TEST_CASE("reduce_multiply(case1)" * doctest::test_suite("functional::multiply"))
{
    // TODO: rename namespace to (array, reduce_multiply)
    NMTOOLS_TESTING_DECLARE_NS(view, reduce_multiply, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::reduce_multiply[axis], a );
    FUNCTIONAL_SUBCASE( "case1", fn::reduce_multiply[axis], a_a );
    FUNCTIONAL_SUBCASE( "case1", fn::reduce_multiply[axis], a_f );
    FUNCTIONAL_SUBCASE( "case1", fn::reduce_multiply[axis], a_h );
    FUNCTIONAL_SUBCASE( "case1", fn::reduce_multiply[axis], a_d );
}

TEST_CASE("reduce_multiply(case4)" * doctest::test_suite("functional::multiply"))
{
    // TODO: rename namespace to (array, reduce_multiply)
    NMTOOLS_TESTING_DECLARE_NS(view, reduce_multiply, case4);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case4", fn::reduce_multiply[axis], a );
    FUNCTIONAL_SUBCASE( "case4", fn::reduce_multiply[axis], a_a );
    FUNCTIONAL_SUBCASE( "case4", fn::reduce_multiply[axis], a_f );
    FUNCTIONAL_SUBCASE( "case4", fn::reduce_multiply[axis], a_h );
    FUNCTIONAL_SUBCASE( "case4", fn::reduce_multiply[axis], a_d );
}

TEST_CASE("reduce_multiply(case8)" * doctest::test_suite("functional::multiply"))
{
    // TODO: rename namespace to (array, reduce_multiply)
    NMTOOLS_TESTING_DECLARE_NS(view, reduce_multiply, case8);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case8", fn::reduce_multiply[axis][dtype][initial], a );
    FUNCTIONAL_SUBCASE( "case8", fn::reduce_multiply[axis][dtype][initial], a_a );
    FUNCTIONAL_SUBCASE( "case8", fn::reduce_multiply[axis][dtype][initial], a_f );
    FUNCTIONAL_SUBCASE( "case8", fn::reduce_multiply[axis][dtype][initial], a_h );
    FUNCTIONAL_SUBCASE( "case8", fn::reduce_multiply[axis][dtype][initial], a_d );
}

TEST_CASE("reduce_multiply(case9)" * doctest::test_suite("functional::multiply"))
{
    // TODO: rename namespace to (array, reduce_multiply)
    NMTOOLS_TESTING_DECLARE_NS(view, reduce_multiply, case9);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case9", fn::reduce_multiply[axis][dtype][initial][keepdims], a );
    FUNCTIONAL_SUBCASE( "case9", fn::reduce_multiply[axis][dtype][initial][keepdims], a_a );
    FUNCTIONAL_SUBCASE( "case9", fn::reduce_multiply[axis][dtype][initial][keepdims], a_f );
    FUNCTIONAL_SUBCASE( "case9", fn::reduce_multiply[axis][dtype][initial][keepdims], a_h );
    FUNCTIONAL_SUBCASE( "case9", fn::reduce_multiply[axis][dtype][initial][keepdims], a_d );
}

TEST_CASE("accumulate_multiply(case1)" * doctest::test_suite("functional::multiply"))
{
    NMTOOLS_TESTING_DECLARE_NS(view, accumulate_multiply, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::accumulate_multiply[axis], a );
    FUNCTIONAL_SUBCASE( "case1", fn::accumulate_multiply[axis], a_a );
    FUNCTIONAL_SUBCASE( "case1", fn::accumulate_multiply[axis], a_f );
    FUNCTIONAL_SUBCASE( "case1", fn::accumulate_multiply[axis], a_h );
    FUNCTIONAL_SUBCASE( "case1", fn::accumulate_multiply[axis], a_d );
}

TEST_CASE("outer_multiply(case1)" * doctest::test_suite("functional::multiply"))
{
    NMTOOLS_TESTING_DECLARE_NS(view, outer_multiply, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::outer_multiply, a, b );
    FUNCTIONAL_SUBCASE( "case1", fn::outer_multiply, a_a, b_a );
    FUNCTIONAL_SUBCASE( "case1", fn::outer_multiply, a_f, b_f );
    FUNCTIONAL_SUBCASE( "case1", fn::outer_multiply, a_h, b_h );
    FUNCTIONAL_SUBCASE( "case1", fn::outer_multiply, a_d, b_d );

    CURRY_BINARY_SUBCASE( "case1", fn::outer_multiply, a, b );
    CURRY_BINARY_SUBCASE( "case1", fn::outer_multiply, a_a, b_a );
    CURRY_BINARY_SUBCASE( "case1", fn::outer_multiply, a_f, b_f );
    CURRY_BINARY_SUBCASE( "case1", fn::outer_multiply, a_h, b_h );
    CURRY_BINARY_SUBCASE( "case1", fn::outer_multiply, a_d, b_d );
}

namespace view = nmtools::view;

TEST_CASE("multiply" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_DECLARE_NS(view,multiply,case1);
    using namespace args;

    auto array = view::multiply(a,b);

    auto function = fn::get_function_composition(array);
    auto expect = fn::multiply;

    NMTOOLS_ASSERT_EQUAL( function, expect );
}

namespace view = nmtools::view;

TEST_CASE("reduce_multiply" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_DECLARE_NS(view,reduce_multiply,case9);
    using namespace args;

    auto array = view::reduce_multiply(a,axis,dtype,initial,keepdims);

    auto function = fn::get_function_composition(array);
    auto expect = fn::reduce_multiply[axis][dtype][initial][keepdims];

    NMTOOLS_ASSERT_EQUAL( function, expect );
}