#include "nmtools/array/functional/ufuncs/add.hpp"
#include "nmtools/array/functional/ufuncs/multiply.hpp"
#include "nmtools/array/functional/ufuncs/tanh.hpp"
#include "nmtools/testing/data/array/multiply.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace fn = nmtools::functional;
namespace view = nmtools::view;
namespace meta = nmtools::meta;

TEST_CASE("add_tanh" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_DECLARE_NS(view,multiply,case1);
    using namespace args;

    auto y = view::add(a,b);
    auto z = view::tanh(y);

    auto function = fn::get_function_composition(z);
    auto expect =
          fn::unary_ufunc[z.attributes()]
        * fn::broadcast_binary_ufunc[y.attributes()]
    ;

    // TODO: make fn::tanh == fn::unary_ufunc[view::tanh_{}]
    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( function (a) (b), z );
}

using namespace nmtools::literals;

TEST_CASE("add_tanh" * doctest::test_suite("functional::get_function_operands"))
{
    NMTOOLS_TESTING_DECLARE_NS(view,multiply,case1);
    using namespace args;

    auto y = view::add(a,b);
    auto z = view::tanh(y);

    auto operands = fn::get_function_operands(z);
    auto expect = nmtools_tuple<decltype(a)&,decltype(b)&>{a,b};
    CHECK( nm::len(operands) == nm::len(expect) );
    CHECK( &nm::at(operands,0_ct) == &nm::at(expect,0_ct) );
    CHECK( &nm::at(operands,1_ct) == &nm::at(expect,1_ct) );
}

TEST_CASE("add_tanh" * doctest::test_suite("functional::apply"))
{
    NMTOOLS_TESTING_DECLARE_NS(view,multiply,case1);
    using namespace args;

    auto y = view::add(a,b);
    auto z = view::tanh(y);

    auto function = fn::get_function_composition(z);
    auto operands = fn::get_function_operands(z);
    
    NMTOOLS_ASSERT_CLOSE( (fn::apply(function,operands)), z );
}