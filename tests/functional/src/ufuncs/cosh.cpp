#include "nmtools/array/functional/ufuncs/cosh.hpp"
#include "nmtools/testing/data/array/cosh.hpp"
#include "nmtools/testing/doctest.hpp"

// lower testing precision for cosh
#undef NMTOOLS_TESTING_OUTPUT_PRECISION
#define NMTOOLS_TESTING_OUTPUT_PRECISION 1e-5

namespace nm = nmtools;
namespace fn = nm::functional;

#define FUNCTIONAL_SUBCASE(subcase_name, function, ...) \
SUBCASE(subcase_name) \
{ \
    auto result = function (__VA_ARGS__); \
    NMTOOLS_REQUIRE_EQUAL( nm::shape(result), nm::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("cosh(case1)" * doctest::test_suite("functional::cosh"))
{
    NMTOOLS_TESTING_USE_CASE(view, cosh, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::cosh, a );
    FUNCTIONAL_SUBCASE( "case1", fn::cosh, a_a );
    FUNCTIONAL_SUBCASE( "case1", fn::cosh, a_f );
    FUNCTIONAL_SUBCASE( "case1", fn::cosh, a_h );
    FUNCTIONAL_SUBCASE( "case1", fn::cosh, a_d );
}

namespace view = nmtools::view;

TEST_CASE("cosh" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(view,cosh,case1);
    using namespace args;

    auto array = view::cosh(a);

    auto function = fn::get_function_composition(array);
    auto expect = fn::cosh;

    NMTOOLS_ASSERT_EQUAL( function, expect );
}

TEST_CASE("cosh" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(view,cosh,case1);
    using namespace args;

    auto array = view::cosh(a);

    auto function = fn::get_function_composition(array);
    auto expect = fn::unary_ufunc[array.attributes()];

    NMTOOLS_ASSERT_EQUAL( function, expect );
}