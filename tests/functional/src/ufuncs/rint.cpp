#include "nmtools/array/functional/ufuncs/rint.hpp"
#include "nmtools/testing/data/array/rint.hpp"
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

TEST_CASE("rint(case1)" * doctest::test_suite("functional::rint"))
{
    NMTOOLS_TESTING_USE_CASE(view, rint, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::rint, a );
    FUNCTIONAL_SUBCASE( "case1", fn::rint, a_a );
    FUNCTIONAL_SUBCASE( "case1", fn::rint, a_f );
    FUNCTIONAL_SUBCASE( "case1", fn::rint, a_h );
    FUNCTIONAL_SUBCASE( "case1", fn::rint, a_d );
}

namespace view = nmtools::view;

TEST_CASE("rint" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(view,rint,case1);
    using namespace args;

    auto array = view::rint(a);

    auto function = fn::get_function_composition(array);
    auto expect = fn::rint;

    NMTOOLS_ASSERT_EQUAL( function, expect );
}

TEST_CASE("rint" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(view,rint,case1);
    using namespace args;

    auto array = view::rint(a);

    auto function = fn::get_function_composition(array);
    auto expect = fn::unary_ufunc[array.attributes()];

    NMTOOLS_ASSERT_EQUAL( function, expect );
}