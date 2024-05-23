#include "nmtools/array/functional/ufuncs/square.hpp"
#include "nmtools/array/functional/ufuncs/add.hpp"
#include "nmtools/array/functional/ufuncs/divide.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"
#include "nmtools/array/view/sum.hpp"
#include "nmtools/testing/data/array/add.hpp"
#include "nmtools/testing/doctest.hpp"

namespace fn = nmtools::functional;
namespace view = nmtools::view;

using nmtools::unwrap;

TEST_CASE("sum_divide" * doctest::test_suite("functional::get_function_composition") )
{
    NMTOOLS_TESTING_DECLARE_NS(view,reduce_add,case1);
    using namespace args;

    auto dtype = nm::None;
    auto axis = 0;
    auto divisor = 3;

    auto x = view::sum(a,axis,dtype);
    auto y = view::divide(x,divisor);

    auto function = fn::get_function_composition(y);
    auto expect =
        fn::broadcast_binary_ufunc[unwrap(y).attributes()]
        * fn::reduce[unwrap(x).attributes()]
    ;

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( unwrap(function) (a) (divisor), y );
}

using namespace nmtools::literals;

TEST_CASE("sum_divide" * doctest::test_suite("functional::get_function_operands"))
{
    NMTOOLS_TESTING_DECLARE_NS(view,reduce_add,case1);
    using namespace args;

    auto dtype = nm::None;
    auto axis = 0;
    auto divisor = 3;

    auto x = view::sum(a,axis,dtype);
    auto y = view::divide(x,divisor);

    auto operands = unwrap(fn::get_function_operands(y));
    auto expect = nmtools_tuple<decltype(a)&,int>{a,divisor};
    CHECK( nm::len(operands) == nm::len(expect) );
    CHECK( &nm::at(operands,0_ct) == &nm::at(expect,0_ct) );
    CHECK( nm::at(operands,1_ct) == nm::at(expect,1_ct) );
}

TEST_CASE("sum_divide" * doctest::test_suite("functional::apply"))
{
    NMTOOLS_TESTING_DECLARE_NS(view,reduce_add,case1);
    using namespace args;

    auto dtype = nm::None;
    auto axis = 0;
    auto divisor = 3;

    auto x = view::sum(a,axis,dtype);
    auto y = view::divide(x,divisor);

    auto function = fn::get_function_composition(y);
    auto operands = fn::get_function_operands(y);
    
    NMTOOLS_ASSERT_CLOSE( (fn::apply(function,operands)), y );
}