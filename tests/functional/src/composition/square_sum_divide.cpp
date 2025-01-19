#include "nmtools/array/ufuncs/square.hpp"
#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/array/ufuncs/divide.hpp"
#include "nmtools/core/ufunc/ufunc.hpp"
#include "nmtools/array/sum.hpp"
#include "nmtools/testing/data/array/square.hpp"
#include "nmtools/testing/doctest.hpp"

namespace fn = nmtools::functional;
namespace view = nmtools::view;

using nmtools::unwrap;

TEST_CASE("square_sum_divide" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(view,square,case1);
    using namespace args;

    auto dtype = nm::None;
    auto axis = 0;
    auto divisor = 3;

    auto x = view::square(a);
    auto y = view::sum(x,axis,dtype);
    auto z = view::divide(y,divisor);

    auto function = fn::get_function_composition(z);
    auto expect =
        fn::broadcast_binary_ufunc[unwrap(z).attributes()]
        * fn::reduce[unwrap(y).attributes()]
        * fn::unary_ufunc[unwrap(x).attributes()]
    ;

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( unwrap(function) (a) (divisor), z );
}

TEST_CASE("square_sum_divide" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(view,square,case1);
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
        fn::broadcast_binary_ufunc[unwrap(z).attributes()]
        * fn::reduce[unwrap(y).attributes()]
        * fn::unary_ufunc[unwrap(x).attributes()]
    ;

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( unwrap(function) (a) (a), z );
}

using namespace nmtools::literals;

TEST_CASE("square_sum_divide" * doctest::test_suite("functional::get_function_operands"))
{
    NMTOOLS_TESTING_USE_CASE(view,square,case1);
    using namespace args;

    auto dtype = nm::None;
    auto axis = 0;
    auto initial = nm::None;
    auto keepdims = nm::True;

    auto x = view::square(a);
    auto y = view::sum(x,axis,dtype,initial,keepdims);
    auto z = view::divide(y,a);

    auto operands = unwrap(fn::get_function_operands(z));
    auto expect = nmtools_tuple<decltype(a)&,decltype(a)&>{a,a};
    CHECK( nm::len(operands) == nm::len(expect) );
    CHECK( &nm::at(operands,0_ct) == &nm::at(expect,0_ct) );
    CHECK( &nm::at(operands,1_ct) == &nm::at(expect,1_ct) );
}

TEST_CASE("square_sum_divide" * doctest::test_suite("functional::apply"))
{
    NMTOOLS_TESTING_USE_CASE(view,square,case1);
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