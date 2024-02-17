#include "nmtools/array/functional/transpose.hpp"
#include "nmtools/testing/data/array/transpose.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace fn = nm::functional;

#define FUNCTIONAL_SUBCASE(subcase_name, function, ...) \
SUBCASE(subcase_name) \
{ \
    auto result = function (__VA_ARGS__); \
    NMTOOLS_REQUIRE_EQUAL( nm::shape(result), nm::shape(expect::expected) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}


TEST_CASE("transpose(case1)" * doctest::test_suite("functional::transpose"))
{
    NMTOOLS_TESTING_DECLARE_NS(transpose, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::transpose[axes_a], array );
    FUNCTIONAL_SUBCASE( "case1", fn::transpose[axes_a], array_a );
    FUNCTIONAL_SUBCASE( "case1", fn::transpose[axes_a], array_f );
    FUNCTIONAL_SUBCASE( "case1", fn::transpose[axes_v], array_h );
    FUNCTIONAL_SUBCASE( "case1", fn::transpose[axes_v], array_d );
}

namespace view = nmtools::view;

TEST_CASE("transpose" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_DECLARE_NS(transpose,case1);
    using namespace args;

    auto a = view::transpose(array,axes_a);

    auto function = fn::get_function_composition(a);
    auto expect = fn::transpose[axes_a];

    NMTOOLS_ASSERT_EQUAL( function, expect );
}