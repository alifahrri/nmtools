#include "nmtools/array/tile.hpp"
#include "nmtools/testing/data/array/tile.hpp"
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


TEST_CASE("tile(case1)" * doctest::test_suite("functional::tile"))
{
    NMTOOLS_TESTING_USE_CASE(view, tile, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::tile[reps], array );
    FUNCTIONAL_SUBCASE( "case1", fn::tile[reps], array_a );
    FUNCTIONAL_SUBCASE( "case1", fn::tile[reps], array_f );
    FUNCTIONAL_SUBCASE( "case1", fn::tile[reps], array_h );
    FUNCTIONAL_SUBCASE( "case1", fn::tile[reps], array_d );
}

namespace view = nmtools::view;

TEST_CASE("tile" * doctest::test_suite("functional::get_function_composition") * doctest::may_fail())
{
    NMTOOLS_TESTING_USE_CASE(view,tile,case1);
    using namespace args;

    auto a = view::tile(array,reps);

    auto function = fn::get_function_composition(a);
    auto expect = fn::tile[reps];

    NMTOOLS_ASSERT_EQUAL( function, expect );
}

TEST_CASE("tile" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(view,tile,case1);
    using namespace args;

    auto a = view::tile(array,reps);

    auto function = fn::get_function_composition(a);

    NMTOOLS_ASSERT_EQUAL( function(array), a );
}