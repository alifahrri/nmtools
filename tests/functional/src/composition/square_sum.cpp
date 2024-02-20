#include "nmtools/array/functional/ufuncs/square.hpp"
#include "nmtools/array/functional/ufuncs/add.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"
#include "nmtools/array/view/sum.hpp"
#include "nmtools/testing/data/array/square.hpp"
#include "nmtools/testing/doctest.hpp"

namespace fn = nmtools::functional;
namespace view = nmtools::view;

TEST_CASE("square_sum" * doctest::test_suite("functional::get_function_composition") )
{
    NMTOOLS_TESTING_DECLARE_NS(view,square,case1);
    using namespace args;

    auto dtype = nm::None;
    auto axis = 0;

    auto x = view::square(a);
    auto y = view::sum(x,axis);

    auto function = fn::get_function_composition(y);
    auto expect =
        fn::reduce_add[y.axis][dtype][y.initial][y.keepdims]
        * fn::square
    ;

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( function (a), y );
}

using namespace nmtools::literals;

TEST_CASE("square_sum" * doctest::test_suite("functional::get_function_operands"))
{
    NMTOOLS_TESTING_DECLARE_NS(view,square,case1);
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
    NMTOOLS_TESTING_DECLARE_NS(view,square,case1);
    using namespace args;

    auto axis = 0;

    auto x = view::square(a);
    auto y = view::sum(x,axis);

    auto function = fn::get_function_composition(y);
    auto operands = fn::get_function_operands(y);
    
    NMTOOLS_ASSERT_CLOSE( (fn::apply(function,operands)), y );
}