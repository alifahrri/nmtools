#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/array/ufuncs/multiply.hpp"
#include "nmtools/array/ufuncs/tanh.hpp"
#include "nmtools/testing/data/array/multiply.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace fn = nmtools::functional;
namespace view = nmtools::view;

TEST_CASE("multiply_tanh" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(view,multiply,case1);
    using namespace args;

    auto x = view::multiply(a,b);
    auto y = view::tanh(x);

    auto function = fn::get_function_composition(y);
    auto expect =
          fn::unary_ufunc[y.attributes()]
        * fn::broadcast_binary_ufunc[x.attributes()]
    ;

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( nm::unwrap(function) (a) (b), y );
}

using namespace nmtools::literals;

TEST_CASE("multiply_tanh" * doctest::test_suite("functional::get_function_operands"))
{
    NMTOOLS_TESTING_USE_CASE(view,multiply,case1);
    using namespace args;

    auto x = view::multiply(a,b);
    auto y = view::tanh(x);

    auto operands = fn::get_function_operands(y);
    auto expect = nmtools_tuple<decltype(a)&,decltype(b)&>{a,b};
    CHECK( nm::len(operands) == nm::len(expect) );
    CHECK( &nm::at(operands,0_ct) == &nm::at(expect,0_ct) );
    CHECK( &nm::at(operands,1_ct) == &nm::at(expect,1_ct) );
}


TEST_CASE("multiply_tanh" * doctest::test_suite("functional::apply"))
{
    NMTOOLS_TESTING_USE_CASE(view,multiply,case1);
    using namespace args;

    auto x = view::multiply(a,b);
    auto y = view::tanh(x);

    [[maybe_unused]]
    auto function = fn::get_function_composition(y);
    [[maybe_unused]]
    auto operands = fn::get_function_operands(y);
    
    NMTOOLS_ASSERT_CLOSE( (fn::apply(function,operands)), y );
}