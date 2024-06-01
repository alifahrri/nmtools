#include "nmtools/array/functional/prod.hpp"
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


TEST_CASE("prod(case1)" * doctest::test_suite("functional::prod"))
{
    NMTOOLS_TESTING_USE_CASE(view, reduce_multiply, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::prod[axis], a );
    FUNCTIONAL_SUBCASE( "case1", fn::prod[axis], a_a );
    FUNCTIONAL_SUBCASE( "case1", fn::prod[axis], a_f );
    FUNCTIONAL_SUBCASE( "case1", fn::prod[axis], a_h );
    FUNCTIONAL_SUBCASE( "case1", fn::prod[axis], a_d );
}

TEST_CASE("prod(case8)" * doctest::test_suite("functional::prod"))
{
    NMTOOLS_TESTING_USE_CASE(view, reduce_multiply, case8);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case8", fn::prod[axis][dtype][initial], a );
    FUNCTIONAL_SUBCASE( "case8", fn::prod[axis][dtype][initial], a_a );
    FUNCTIONAL_SUBCASE( "case8", fn::prod[axis][dtype][initial], a_f );
    FUNCTIONAL_SUBCASE( "case8", fn::prod[axis][dtype][initial], a_h );
    FUNCTIONAL_SUBCASE( "case8", fn::prod[axis][dtype][initial], a_d );
}

TEST_CASE("prod(case9)" * doctest::test_suite("functional::prod"))
{
    NMTOOLS_TESTING_USE_CASE(view, reduce_multiply, case9);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case9", fn::prod[axis][dtype][initial][keepdims], a );
    FUNCTIONAL_SUBCASE( "case9", fn::prod[axis][dtype][initial][keepdims], a_a );
    FUNCTIONAL_SUBCASE( "case9", fn::prod[axis][dtype][initial][keepdims], a_f );
    FUNCTIONAL_SUBCASE( "case9", fn::prod[axis][dtype][initial][keepdims], a_h );
    FUNCTIONAL_SUBCASE( "case9", fn::prod[axis][dtype][initial][keepdims], a_d );
}