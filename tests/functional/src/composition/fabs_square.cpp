#include "nmtools/array/ufuncs/fabs.hpp"
#include "nmtools/array/ufuncs/square.hpp"
#include "nmtools/array/ufunc/ufunc.hpp"
#include "nmtools/testing/data/array/square.hpp"
#include "nmtools/testing/doctest.hpp"

namespace fn = nmtools::functional;
namespace view = nmtools::view;

TEST_CASE("fabs_square" * doctest::test_suite("functional::get_function_composition") )
{
    NMTOOLS_TESTING_USE_CASE(view,square,case1);
    using namespace args;

    auto x = view::fabs(a);
    auto y = view::square(x);

    auto function = fn::get_function_composition(y);
    auto expect =
        fn::unary_ufunc[y.attributes()]
        * fn::unary_ufunc[x.attributes()]
    ;

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( function (a), y );
}

using namespace nmtools::literals;

TEST_CASE("fabs_square" * doctest::test_suite("functional::get_function_operands"))
{
    NMTOOLS_TESTING_USE_CASE(view,square,case1);
    using namespace args;

    auto x = view::fabs(a);
    auto y = view::square(x);

    auto operands = fn::get_function_operands(y);
    auto expect = nmtools_tuple<decltype(a)&>{a};
    CHECK( nm::len(operands) == nm::len(expect) );
    CHECK( &nm::at(operands,0_ct) == &nm::at(expect,0_ct) );
}

TEST_CASE("fabs_square" * doctest::test_suite("functional::apply"))
{
    NMTOOLS_TESTING_USE_CASE(view,square,case1);
    using namespace args;

    auto x = view::fabs(a);
    auto y = view::square(x);

    auto function = fn::get_function_composition(y);
    auto operands = fn::get_function_operands(y);
    
    NMTOOLS_ASSERT_CLOSE( (fn::apply(function,operands)), y );
}