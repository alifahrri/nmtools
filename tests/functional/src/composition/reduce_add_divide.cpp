#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/array/ufuncs/divide.hpp"
#include "nmtools/array/ufunc/ufunc.hpp"
#include "nmtools/testing/data/array/add.hpp"
#include "nmtools/testing/doctest.hpp"

namespace fn = nmtools::functional;
namespace view = nmtools::view;

using nmtools::unwrap;

TEST_CASE("reduce_add_divide" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(view,reduce_add,case9);
    using namespace args;

    auto b = 3;
    auto x = view::reduce_add(a,axis,dtype,initial,keepdims);
    auto y = view::divide(x,b);

    auto function = fn::get_function_composition(y);
    auto expect =
        fn::broadcast_binary_ufunc[unwrap(y).attributes()]
        * fn::reduce[unwrap(x).attributes()]
    ;

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( unwrap(function) (a) (b), y );
}

using namespace nmtools::literals;

TEST_CASE("reduce_add_divide" * doctest::test_suite("functional::get_function_operands"))
{
    NMTOOLS_TESTING_USE_CASE(view,reduce_add,case9);
    using namespace args;

    auto b = 3;
    auto x = view::reduce_add(a,axis,dtype,initial,keepdims);
    auto y = view::divide(x,b);

    auto operands = unwrap(fn::get_function_operands(y));
    auto expect = nmtools_tuple<decltype(a)&,int>{a,b};
    CHECK( nm::len(operands) == nm::len(expect) );
    CHECK( &nm::at(operands,0_ct) == &nm::at(expect,0_ct) );
    CHECK( nm::at(operands,1_ct) == nm::at(expect,1_ct) );
}

TEST_CASE("reduce_add_divide" * doctest::test_suite("functional::apply"))
{
    NMTOOLS_TESTING_USE_CASE(view,reduce_add,case9);
    using namespace args;

    auto b = 3;
    auto x = view::reduce_add(a,axis,dtype,initial,keepdims);
    auto y = view::divide(x,b);

    auto function = fn::get_function_composition(y);
    auto operands = fn::get_function_operands(y);
    
    NMTOOLS_ASSERT_CLOSE( (fn::apply(function,operands)), y );
}