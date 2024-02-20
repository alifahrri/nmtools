#include "nmtools/array/functional/ufuncs/fabs.hpp"
#include "nmtools/testing/data/array/fabs.hpp"
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

TEST_CASE("fabs(case1)" * doctest::test_suite("functional::fabs"))
{
    NMTOOLS_TESTING_DECLARE_NS(view, fabs, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::fabs, a );
    FUNCTIONAL_SUBCASE( "case1", fn::fabs, a_a );
    FUNCTIONAL_SUBCASE( "case1", fn::fabs, a_f );
    FUNCTIONAL_SUBCASE( "case1", fn::fabs, a_h );
    FUNCTIONAL_SUBCASE( "case1", fn::fabs, a_d );
}


namespace view = nmtools::view;

TEST_CASE("fabs" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_DECLARE_NS(view,fabs,case1);
    using namespace args;

    auto array = view::fabs(a);

    auto function = fn::get_function_composition(array);
    auto expect = fn::fabs;

    NMTOOLS_ASSERT_EQUAL( function, expect );
}