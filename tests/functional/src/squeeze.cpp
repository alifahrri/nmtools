#include "nmtools/array/functional/squeeze.hpp"
#include "nmtools/testing/data/array/squeeze.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace fn = nm::functional;

using nmtools::unwrap;

#define FUNCTIONAL_SUBCASE(subcase_name, function, ...) \
SUBCASE(subcase_name) \
{ \
    auto result = function (__VA_ARGS__); \
    NMTOOLS_REQUIRE_EQUAL( nm::shape(result), nm::shape(expect::expected) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}


TEST_CASE("squeeze(case1)" * doctest::test_suite("functional::squeeze"))
{
    NMTOOLS_TESTING_DECLARE_NS(squeeze, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::squeeze, array );
    FUNCTIONAL_SUBCASE( "case1", fn::squeeze, array_a );
    FUNCTIONAL_SUBCASE( "case1", fn::squeeze, array_f );
    FUNCTIONAL_SUBCASE( "case1", fn::squeeze, array_h );
    FUNCTIONAL_SUBCASE( "case1", fn::squeeze, array_d );
}

namespace view = nmtools::view;

TEST_CASE("squeeze" * doctest::test_suite("functional::get_function_composition") * doctest::may_fail())
{
    NMTOOLS_TESTING_DECLARE_NS(squeeze,case1);
    using namespace args;

    auto a = view::squeeze(array);

    auto function = fn::get_function_composition(a);
    auto expect = fn::squeeze;

    NMTOOLS_ASSERT_EQUAL( function, expect );
}

TEST_CASE("squeeze" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_DECLARE_NS(squeeze,case1);
    using namespace args;

    auto a = view::squeeze(array);

    auto function = fn::get_function_composition(a);
    auto expect = fn::indexing[unwrap(a).attributes()];

    NMTOOLS_ASSERT_EQUAL( function, expect );
}