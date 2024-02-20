#include "nmtools/array/functional/ufuncs/subtract.hpp"
#include "nmtools/array/functional/ufuncs/maximum.hpp"
#include "nmtools/array/functional/ufuncs/exp.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"
#include "nmtools/testing/data/array/maximum.hpp"
#include "nmtools/testing/doctest.hpp"

namespace fn = nmtools::functional;
namespace view = nmtools::view;

// NOTE: somehow get_function_composition produces wrong result for 3(+?) functions
// TODO: fix
TEST_CASE("reduce_maximum_subtract_exp" * doctest::test_suite("functional::get_function_composition") * doctest::may_fail())
{
    NMTOOLS_TESTING_DECLARE_NS(view,reduce_maximum,case1);
    using namespace args;

    auto dtype = nm::None;
    auto axis = 0;
    auto initial = nm::None;
    auto keepdims = nm::True;

    auto x = view::reduce_maximum(a,axis,dtype,initial,keepdims);
    auto y = view::subtract(x,a);
    auto z = view::exp(y);

    auto function = fn::get_function_composition(y);
    auto expect =
        fn::exp
        * fn::subtract
        * fn::reduce_maximum[x.axis][dtype][x.initial][x.keepdims]
    ;

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( function (a) (a), z );
}

using namespace nmtools::literals;

TEST_CASE("reduce_maximum_subtract_exp" * doctest::test_suite("functional::get_function_operands"))
{
    NMTOOLS_TESTING_DECLARE_NS(view,reduce_maximum,case1);
    using namespace args;

    auto dtype = nm::None;
    auto axis = 0;
    auto initial = nm::None;
    auto keepdims = nm::True;

    auto x = view::reduce_maximum(a,axis,dtype,initial,keepdims);
    auto y = view::subtract(x,a);
    auto z = view::exp(y);

    auto operands = fn::get_function_operands(z);
    auto expect = nmtools_tuple<decltype(a)&,decltype(a)&>{a,a};
    CHECK( nm::len(operands) == nm::len(expect) );
    CHECK( &nm::at(operands,0_ct) == &nm::at(expect,0_ct) );
    CHECK( &nm::at(operands,1_ct) == &nm::at(expect,1_ct) );
}

// NOTE: somehow get_function_composition produces wrong result for 3(+?) functions
// TODO: fix
TEST_CASE("reduce_maximum_subtract_exp" * doctest::test_suite("functional::apply") * doctest::may_fail())
{
    NMTOOLS_TESTING_DECLARE_NS(view,reduce_maximum,case1);
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