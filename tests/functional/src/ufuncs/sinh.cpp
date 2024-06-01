#include "nmtools/array/functional/ufuncs/sinh.hpp"
#include "nmtools/testing/data/array/sinh.hpp"
#include "nmtools/testing/doctest.hpp"

// lower testing precision for sinh
#undef  NMTOOLS_TESTING_OUTPUT_PRECISION
#define NMTOOLS_TESTING_OUTPUT_PRECISION 7e-5

namespace nm = nmtools;
namespace fn = nm::functional;

#define FUNCTIONAL_SUBCASE(subcase_name, function, ...) \
SUBCASE(subcase_name) \
{ \
    auto result = function (__VA_ARGS__); \
    NMTOOLS_REQUIRE_EQUAL( nm::shape(result), nm::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("sinh(case1)" * doctest::test_suite("functional::sinh"))
{
    NMTOOLS_TESTING_USE_CASE(view, sinh, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::sinh, a );
    FUNCTIONAL_SUBCASE( "case1", fn::sinh, a_a );
    FUNCTIONAL_SUBCASE( "case1", fn::sinh, a_f );
    FUNCTIONAL_SUBCASE( "case1", fn::sinh, a_h );
    FUNCTIONAL_SUBCASE( "case1", fn::sinh, a_d );
}

namespace view = nmtools::view;

TEST_CASE("sinh" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(view,sinh,case1);
    using namespace args;

    auto array = view::sinh(a);

    auto function = fn::get_function_composition(array);
    auto expect = fn::sinh;

    NMTOOLS_ASSERT_EQUAL( function, expect );
}

TEST_CASE("sinh" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(view,sinh,case1);
    using namespace args;

    auto array = view::sinh(a);

    auto function = fn::get_function_composition(array);
    auto expect = fn::unary_ufunc[array.attributes()];

    NMTOOLS_ASSERT_EQUAL( function, expect );
}