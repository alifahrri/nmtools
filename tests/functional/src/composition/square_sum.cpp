#include "nmtools/array/ufuncs/square.hpp"
#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/core/ufunc/ufunc.hpp"
#include "nmtools/array/sum.hpp"
#include "nmtools/testing/data/array/square.hpp"
#include "nmtools/testing/doctest.hpp"

namespace fn = nmtools::functional;
namespace view = nmtools::view;

using nmtools::unwrap;

TEST_CASE("square_sum" * doctest::test_suite("functional::get_function_composition") )
{
    NMTOOLS_TESTING_USE_CASE(view,square,case1);
    using namespace args;

    auto axis = 0;

    auto x = view::square(a);
    auto y = view::sum(x,axis);

    auto function = unwrap(fn::get_function_composition(y));
    auto expect =
          fn::reduce[unwrap(y).attributes()]
        * fn::unary_ufunc[unwrap(x).attributes()]
    ;

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( unwrap(function) (a), y );
}

using namespace nmtools::literals;

TEST_CASE("square_sum" * doctest::test_suite("functional::get_function_operands"))
{
    NMTOOLS_TESTING_USE_CASE(view,square,case1);
    using namespace args;

    auto axis = 0;

    auto x = view::square(a);
    auto y = view::sum(x,axis);

    auto operands = fn::get_function_operands(y);
    auto expect = nmtools_tuple<decltype(a)&>{a};
    CHECK( nm::len(operands) == nm::len(expect) );
    CHECK( &nm::at(operands,0_ct) == &nm::at(expect,0_ct) );
}

TEST_CASE("square_sum" * doctest::test_suite("functional::apply"))
{
    NMTOOLS_TESTING_USE_CASE(view,square,case1);
    using namespace args;

    auto axis = 0;

    auto x = view::square(a);
    auto y = view::sum(x,axis);

    auto function = fn::get_function_composition(y);
    auto operands = fn::get_function_operands(y);
    
    NMTOOLS_ASSERT_CLOSE( (fn::apply(function,operands)), y );
}