#include "nmtools/array/functional/atleast_1d.hpp"
#include "nmtools/testing/data/array/atleast_1d.hpp"
#include "nmtools/array/array/arange.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools::array;
namespace fn = nm::functional;
namespace view = nmtools::view;

#define FUNCTIONAL_SUBCASE(subcase_name, function, ...) \
SUBCASE(subcase_name) \
{ \
    auto result = function (__VA_ARGS__); \
    NMTOOLS_REQUIRE_EQUAL( nm::shape(result), nm::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}


TEST_CASE("atleast_1d(case1)" * doctest::test_suite("functional::atleast_1d"))
{
    NMTOOLS_TESTING_USE_CASE(array, atleast_1d, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::atleast_1d, a );
}

TEST_CASE("atleast_1d(case2)" * doctest::test_suite("functional::atleast_1d"))
{
    NMTOOLS_TESTING_USE_CASE(array, atleast_1d, case2);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case2", fn::atleast_1d, a );
    FUNCTIONAL_SUBCASE( "case2", fn::atleast_1d, a_a );
    FUNCTIONAL_SUBCASE( "case2", fn::atleast_1d, a_f );
    FUNCTIONAL_SUBCASE( "case2", fn::atleast_1d, a_h );
    FUNCTIONAL_SUBCASE( "case2", fn::atleast_1d, a_d );
}

TEST_CASE("atleast_1d(case3)" * doctest::test_suite("functional::atleast_1d"))
{
    NMTOOLS_TESTING_USE_CASE(array, atleast_1d, case3);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case3", fn::atleast_1d, a );
    FUNCTIONAL_SUBCASE( "case3", fn::atleast_1d, a_a );
    FUNCTIONAL_SUBCASE( "case3", fn::atleast_1d, a_f );
    FUNCTIONAL_SUBCASE( "case3", fn::atleast_1d, a_h );
    FUNCTIONAL_SUBCASE( "case3", fn::atleast_1d, a_d );
}

TEST_CASE("atleast_1d(case4)" * doctest::test_suite("functional::atleast_1d"))
{
    NMTOOLS_TESTING_USE_CASE(array, atleast_1d, case4);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case4", fn::atleast_1d, a );
    FUNCTIONAL_SUBCASE( "case4", fn::atleast_1d, a_a );
    FUNCTIONAL_SUBCASE( "case4", fn::atleast_1d, a_f );
    FUNCTIONAL_SUBCASE( "case4", fn::atleast_1d, a_h );
    FUNCTIONAL_SUBCASE( "case4", fn::atleast_1d, a_d );
}

TEST_CASE("atleast_1d" * doctest::test_suite("functional::get_function_composition"))
{
    auto array = na::arange(10);
    auto a = view::atleast_1d(array);

    [[maybe_unused]]
    auto function = fn::get_function_composition(a);
    // auto expect = fn::atleast_1d;

    // NMTOOLS_ASSERT_EQUAL( function, expect );
}