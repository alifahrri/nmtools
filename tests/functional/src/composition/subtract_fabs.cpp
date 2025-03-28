#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/array/ufuncs/divide.hpp"
#include "nmtools/array/ufuncs/subtract.hpp"
#include "nmtools/array/ufuncs/fabs.hpp"
#include "nmtools/core/ufunc/ufunc.hpp"
#include "nmtools/testing/data/array/subtract.hpp"
#include "nmtools/testing/doctest.hpp"

namespace fn = nmtools::functional;
namespace view = nmtools::view;

using nmtools::unwrap;

TEST_CASE("subtract_fabs" * doctest::test_suite("functional::get_function_composition") )
{
    NMTOOLS_TESTING_USE_CASE(view,subtract,case1);
    using namespace args;

    auto x = view::subtract(a,b);
    auto y = view::fabs(x);

    auto function = fn::get_function_composition(y);
    auto expect =
          fn::unary_ufunc[unwrap(y).attributes()]
        * fn::broadcast_binary_ufunc[unwrap(x).attributes()]
    ;

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( unwrap(function) (a) (b), y );
}

using namespace nmtools::literals;

TEST_CASE("subtract_fabs" * doctest::test_suite("functional::get_function_operands"))
{
    NMTOOLS_TESTING_USE_CASE(view,subtract,case1);
    using namespace args;

    auto x = view::subtract(a,b);
    auto y = view::fabs(x);

    auto operands = unwrap(fn::get_function_operands(y));
    auto expect = nmtools_tuple<decltype(a)&,decltype(b)&>{a,b};
    CHECK( nm::len(operands) == nm::len(expect) );
    CHECK( &nm::at(operands,0_ct) == &nm::at(expect,0_ct) );
    CHECK( &nm::at(operands,1_ct) == &nm::at(expect,1_ct) );
}

TEST_CASE("subtract_fabs" * doctest::test_suite("functional::apply"))
{
    NMTOOLS_TESTING_USE_CASE(view,subtract,case1);
    using namespace args;

    auto x = view::subtract(a,b);
    auto y = view::fabs(x);

    auto function = fn::get_function_composition(y);
    auto operands = fn::get_function_operands(y);
    
    NMTOOLS_ASSERT_CLOSE( (fn::apply(function,operands)), y );
}