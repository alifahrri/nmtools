#include "nmtools/array/functional/ufuncs/add.hpp"
#include "nmtools/array/functional/ufuncs/multiply.hpp"
#include "nmtools/array/functional/ufuncs/tanh.hpp"
#include "nmtools/testing/data/array/multiply.hpp"
#include "nmtools/testing/doctest.hpp"

namespace fn = nmtools::functional;
namespace view = nmtools::view;

TEST_CASE("multiply_add" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(view,multiply,case1);
    using namespace args;

    auto x = view::multiply(a,b);
    auto y = view::add(x,b);

    auto function = fn::get_function_composition(y);
    auto expect =
        fn::broadcast_binary_ufunc[y.attributes()]
        * fn::broadcast_binary_ufunc[x.attributes()]
    ;

    NMTOOLS_ASSERT_EQUAL( function, expect );
    static_assert( decltype(expect)::arity == 3 );
    static_assert( decltype(function)::arity == 3 );
    NMTOOLS_ASSERT_CLOSE( function (a) (b) (b), y );
}

using namespace nmtools::literals;

TEST_CASE("multiply_add" * doctest::test_suite("functional::get_function_operands"))
{
    NMTOOLS_TESTING_USE_CASE(view,multiply,case1);
    using namespace args;

    auto x = view::multiply(a,b);
    auto y = view::add(x,b);

    auto operands = fn::get_function_operands(y);
    auto expect = nmtools_tuple<decltype(a)&,decltype(b)&,decltype(b)&>{a,b,b};
    CHECK( nm::len(operands) == nm::len(expect) );
    CHECK( &nm::at(operands,0_ct) == &nm::at(expect,0_ct) );
    CHECK( &nm::at(operands,1_ct) == &nm::at(expect,1_ct) );
    CHECK( &nm::at(operands,2_ct) == &nm::at(expect,2_ct) );
}

TEST_CASE("multiply_add" * doctest::test_suite("functional::apply"))
{
    NMTOOLS_TESTING_USE_CASE(view,multiply,case1);
    using namespace args;

    auto x = view::multiply(a,b);
    auto y = view::add(x,b);

    auto function = fn::get_function_composition(y);
    auto operands = fn::get_function_operands(y);
    
    NMTOOLS_ASSERT_CLOSE( (fn::apply(function,operands)), y );
}