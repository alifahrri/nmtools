#include "nmtools/array/functional/ufuncs/add.hpp"
#include "nmtools/array/functional/ufuncs/tanh.hpp"
#include "nmtools/testing/data/array/add.hpp"
#include "nmtools/testing/doctest.hpp"

namespace fn = nmtools::functional;
namespace view = nmtools::view;

using nmtools::unwrap;

TEST_CASE("reduce_add_tanh" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(view,reduce_add,case9);
    using namespace args;

    auto x = view::reduce_add(a,axis,dtype,initial,keepdims);
    auto y = view::tanh(x);

    auto function = fn::get_function_composition(y);
    auto expect =
          fn::unary_ufunc[unwrap(y).attributes()]
        * fn::reduce[unwrap(x).attributes()]
    ;

    // TODO: make fn::tanh == fn::unary_ufunc[view::tanh_t{}]

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( function (a), y );
}

using namespace nmtools::literals;

TEST_CASE("reduce_add_tanh" * doctest::test_suite("functional::get_function_operands"))
{
    NMTOOLS_TESTING_USE_CASE(view,reduce_add,case9);
    using namespace args;

    auto x = view::reduce_add(a,axis,dtype,initial,keepdims);
    auto y = view::tanh(x);

    auto operands = unwrap(fn::get_function_operands(y));
    auto expect = nmtools_tuple<decltype(a)&>{a};
    CHECK( nm::len(operands) == nm::len(expect) );
    CHECK( &nm::at(operands,0_ct) == &nm::at(expect,0_ct) );
}

TEST_CASE("reduce_add_tanh" * doctest::test_suite("functional::apply"))
{
    NMTOOLS_TESTING_USE_CASE(view,reduce_add,case9);
    using namespace args;

    auto x = view::reduce_add(a,axis,dtype,initial,keepdims);
    auto y = view::tanh(x);

    auto function = fn::get_function_composition(y);
    auto operands = fn::get_function_operands(y);
    
    NMTOOLS_ASSERT_CLOSE( (fn::apply(function,operands)), y );
}