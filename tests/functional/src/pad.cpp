#include "nmtools/array/pad.hpp"
#include "nmtools/testing/data/array/pad.hpp"
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


TEST_CASE("pad(case1)" * doctest::test_suite("functional::pad"))
{
    NMTOOLS_TESTING_USE_CASE(array, pad, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::pad[pad_width], array );
    FUNCTIONAL_SUBCASE( "case1", fn::pad[pad_width_a], array_a );
    FUNCTIONAL_SUBCASE( "case1", fn::pad[pad_width_f], array_f );
    FUNCTIONAL_SUBCASE( "case1", fn::pad[pad_width_h], array_h );
    FUNCTIONAL_SUBCASE( "case1", fn::pad[pad_width_v], array_d );
}

namespace view = nmtools::view;

TEST_CASE("pad" * doctest::test_suite("functional::get_function_composition") * doctest::may_fail())
{
    NMTOOLS_TESTING_USE_CASE(array,pad,case1);
    using namespace args;

    auto pad_value = 0.0f;

    auto a = view::pad(array,pad_width);

    auto function = fn::get_function_composition(a);
    auto expect = fn::pad[pad_width][pad_value];

    NMTOOLS_ASSERT_EQUAL( function, expect );
}