#include "nmtools/array/functional/ufuncs/add.hpp"
#include "nmtools/array/functional/ufuncs/divide.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"
#include "nmtools/testing/data/array/add.hpp"
#include "nmtools/testing/doctest.hpp"

namespace fn = nmtools::functional;
namespace view = nmtools::view;

// NOTE: somehow get_function_composition produces wrong result for 3(+?) functions
// TODO: fix
TEST_CASE("reduce_add_divide" * doctest::test_suite("functional::get_function_composition") * doctest::may_fail())
{
    NMTOOLS_TESTING_DECLARE_NS(view,reduce_add,case9);
    using namespace args;

    auto b = 3;
    auto x = view::reduce_add(a,axis,dtype,initial,keepdims);
    auto y = view::divide(x,b);

    auto function = fn::get_function_composition(y);
    auto expect =
        fn::divide
        * fn::reduce_add[axis][dtype][initial][keepdims]
    ;

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( function (a) (b), y );
}

using namespace nmtools::literals;

TEST_CASE("reduce_add_divide" * doctest::test_suite("functional::get_function_operands"))
{
    NMTOOLS_TESTING_DECLARE_NS(view,reduce_add,case9);
    using namespace args;

    auto b = 3;
    auto x = view::reduce_add(a,axis,dtype,initial,keepdims);
    auto y = view::divide(x,b);

    auto operands = fn::get_function_operands(y);
    auto expect = nmtools_tuple<decltype(a)&,int>{a,b};
    CHECK( nm::len(operands) == nm::len(expect) );
    CHECK( &nm::at(operands,0_ct) == &nm::at(expect,0_ct) );
    CHECK( nm::at(operands,1_ct) == nm::at(expect,1_ct) );
}

TEST_CASE("reduce_add_divide" * doctest::test_suite("functional::apply"))
{
    NMTOOLS_TESTING_DECLARE_NS(view,reduce_add,case9);
    using namespace args;

    auto b = 3;
    auto x = view::reduce_add(a,axis,dtype,initial,keepdims);
    auto y = view::divide(x,b);

    auto function = fn::get_function_composition(y);
    auto operands = fn::get_function_operands(y);
    
    NMTOOLS_ASSERT_CLOSE( (fn::apply(function,operands)), y );
}