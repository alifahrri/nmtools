#include "nmtools/array/functional/ufuncs/square.hpp"
#include "nmtools/array/functional/ufuncs/add.hpp"
#include "nmtools/array/functional/ufuncs/divide.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"
#include "nmtools/array/view/sum.hpp"
#include "nmtools/testing/data/array/square.hpp"
#include "nmtools/testing/doctest.hpp"

namespace fn = nmtools::functional;
namespace view = nmtools::view;

// NOTE: somehow get_function_composition produces wrong result for 3(+?) functions
// TODO: fix
TEST_CASE("square_sum_divide" * doctest::test_suite("functional::get_function_composition") * doctest::may_fail())
{
    NMTOOLS_TESTING_DECLARE_NS(view,square,case1);
    using namespace args;

    auto dtype = nm::None;
    auto axis = 0;
    auto divisor = 3;

    auto x = view::square(a);
    auto y = view::sum(x,axis,dtype);
    auto z = view::divide(y,divisor);

    auto function = fn::get_function_composition(z);
    auto expect =
        fn::divide
        * fn::reduce_add[y.axis][dtype][y.initial][y.keepdims]
        * fn::square
    ;

    NMTOOLS_ASSERT_EQUAL( function, expect );
    // NMTOOLS_ASSERT_CLOSE( function (a) (divisor), z );
}

// NOTE: somehow get_function_composition produces wrong result for 3(+?) functions
// TODO: fix
TEST_CASE("square_sum_divide" * doctest::test_suite("functional::get_function_composition") * doctest::may_fail())
{
    NMTOOLS_TESTING_DECLARE_NS(view,square,case1);
    using namespace args;

    auto dtype = nm::None;
    auto axis = 0;
    auto initial = nm::None;
    auto keepdims = nm::True;

    auto x = view::square(a);
    auto y = view::sum(x,axis,dtype,initial,keepdims);
    auto z = view::divide(y,a);

    auto function = fn::get_function_composition(z);
    auto expect =
        fn::divide
        * fn::reduce_add[y.axis][dtype][y.initial][y.keepdims]
        * fn::square
    ;

    NMTOOLS_ASSERT_EQUAL( function, expect );
    // NMTOOLS_ASSERT_CLOSE( function (a) (a), z );
}

using namespace nmtools::literals;

TEST_CASE("square_sum_divide" * doctest::test_suite("functional::get_function_operands"))
{
    NMTOOLS_TESTING_DECLARE_NS(view,square,case1);
    using namespace args;

    auto dtype = nm::None;
    auto axis = 0;
    auto initial = nm::None;
    auto keepdims = nm::True;

    auto x = view::square(a);
    auto y = view::sum(x,axis,dtype,initial,keepdims);
    auto z = view::divide(y,a);

    auto operands = fn::get_function_operands(z);
    auto expect = nmtools_tuple<decltype(a)&,decltype(a)&>{a,a};
    CHECK( nm::len(operands) == nm::len(expect) );
    CHECK( &nm::at(operands,0_ct) == &nm::at(expect,0_ct) );
    CHECK( &nm::at(operands,1_ct) == &nm::at(expect,1_ct) );
}

// NOTE: somehow get_function_composition produces wrong result for 3(+?) functions
// TODO: fix
TEST_CASE("square_sum_divide" * doctest::test_suite("functional::apply") * doctest::skip())
{
    NMTOOLS_TESTING_DECLARE_NS(view,square,case1);
    using namespace args;

    auto dtype = nm::None;
    auto axis = 0;
    auto initial = nm::None;
    auto keepdims = nm::True;

    auto x = view::square(a);
    auto y = view::sum(x,axis,dtype,initial,keepdims);
    auto z = view::divide(y,a);

    auto function = fn::get_function_composition(z);
    auto operands = fn::get_function_operands(z);
    
    NMTOOLS_ASSERT_CLOSE( (fn::apply(function,operands)), z );
}