#include "nmtools/array/functional/ufuncs/subtract.hpp"
#include "nmtools/array/functional/ufuncs/maximum.hpp"
#include "nmtools/array/functional/ufuncs/exp.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"
#include "nmtools/testing/data/array/maximum.hpp"
#include "nmtools/testing/doctest.hpp"

namespace fn = nmtools::functional;
namespace view = nmtools::view;

using nmtools::unwrap;

TEST_CASE("reduce_maximum_subtract_exp" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(view,reduce_maximum,case1);
    using namespace args;

    auto dtype = nm::None;
    auto axis = 0;
    auto initial = nm::None;
    auto keepdims = nm::True;

    auto x = view::reduce_maximum(a,axis,dtype,initial,keepdims);
    auto y = view::subtract(x,a);
    auto z = view::exp(y);

    auto function = fn::get_function_composition(z);
    auto expect =
          fn::unary_ufunc[unwrap(z).attributes()]
        * fn::broadcast_binary_ufunc[unwrap(y).attributes()]
        * fn::reduce[unwrap(x).attributes()]
    ;

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( unwrap(function) (a) (a), z );
}

using namespace nmtools::literals;

TEST_CASE("reduce_maximum_subtract_exp" * doctest::test_suite("functional::get_function_operands"))
{
    NMTOOLS_TESTING_USE_CASE(view,reduce_maximum,case1);
    using namespace args;

    auto dtype = nm::None;
    auto axis = 0;
    auto initial = nm::None;
    auto keepdims = nm::True;

    auto x = view::reduce_maximum(a,axis,dtype,initial,keepdims);
    auto y = view::subtract(x,a);
    auto z = view::exp(y);

    auto operands = unwrap(fn::get_function_operands(z));
    auto expect = nmtools_tuple<decltype(a)&,decltype(a)&>{a,a};
    CHECK( nm::len(operands) == nm::len(expect) );
    CHECK( &nm::at(operands,0_ct) == &nm::at(expect,0_ct) );
    CHECK( &nm::at(operands,1_ct) == &nm::at(expect,1_ct) );
}

TEST_CASE("reduce_maximum_subtract_exp" * doctest::test_suite("functional::apply"))
{
    NMTOOLS_TESTING_USE_CASE(view,reduce_maximum,case1);
    using namespace args;

    auto dtype = nm::None;
    auto axis = 0;
    auto initial = nm::None;
    auto keepdims = nm::True;

    auto x = view::reduce_maximum(a,axis,dtype,initial,keepdims);
    auto y = view::subtract(x,a);
    auto z = view::exp(y);

    auto function = fn::get_function_composition(z);
    auto operands = fn::get_function_operands(z);
    
    NMTOOLS_ASSERT_CLOSE( (fn::apply(function,operands)), z );
}