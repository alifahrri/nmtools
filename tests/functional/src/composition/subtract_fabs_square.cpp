#include "nmtools/array/functional/ufuncs/square.hpp"
#include "nmtools/array/functional/ufuncs/subtract.hpp"
#include "nmtools/array/functional/ufuncs/fabs.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"
#include "nmtools/testing/data/array/subtract.hpp"
#include "nmtools/testing/doctest.hpp"

namespace fn = nmtools::functional;
namespace view = nmtools::view;

// NOTE: somehow get_function_composition produces wrong result for 3(+?) functions
// TODO: fix
TEST_CASE("subtract_fabs_square" * doctest::test_suite("functional::get_function_composition") * doctest::may_fail() )
{
    NMTOOLS_TESTING_DECLARE_NS(view,subtract,case1);
    using namespace args;

    auto x = view::subtract(a,b);
    auto y = view::fabs(x);
    auto z = view::square(y);

    auto function = fn::get_function_composition(z);
    auto expect =
        fn::square * fn::fabs * fn::subtract
    ;

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( function (a) (b), z );
}

using namespace nmtools::literals;

TEST_CASE("subtract_fabs_square" * doctest::test_suite("functional::get_function_operands"))
{
    NMTOOLS_TESTING_DECLARE_NS(view,subtract,case1);
    using namespace args;

    auto x = view::subtract(a,b);
    auto y = view::fabs(x);
    auto z = view::square(y);

    auto operands = fn::get_function_operands(z);
    auto expect = nmtools_tuple<decltype(a)&,decltype(b)&>{a,b};
    CHECK( nm::len(operands) == nm::len(expect) );
    CHECK( &nm::at(operands,0_ct) == &nm::at(expect,0_ct) );
    CHECK( &nm::at(operands,1_ct) == &nm::at(expect,1_ct) );
}

// NOTE: somehow get_function_composition produces wrong result for 3(+?) functions
// TODO: fix
TEST_CASE("subtract_fabs_square" * doctest::test_suite("functional::apply") * doctest::may_fail())
{
    NMTOOLS_TESTING_DECLARE_NS(view,subtract,case1);
    using namespace args;

    auto x = view::subtract(a,b);
    auto y = view::fabs(x);
    auto z = view::square(y);

    auto function = fn::get_function_composition(z);
    auto operands = fn::get_function_operands(z);
    
    NMTOOLS_ASSERT_CLOSE( (fn::apply(function,operands)), z );
}