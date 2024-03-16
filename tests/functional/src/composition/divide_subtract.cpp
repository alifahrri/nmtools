#include "nmtools/array/functional/ufuncs/add.hpp"
#include "nmtools/array/functional/ufuncs/divide.hpp"
#include "nmtools/array/functional/ufuncs/subtract.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"
#include "nmtools/testing/data/array/subtract.hpp"
#include "nmtools/testing/doctest.hpp"

namespace fn = nmtools::functional;
namespace view = nmtools::view;

using namespace nmtools::literals;

// TODO: fix, reorder result from divide to subtract rhs
TEST_CASE("divide_subtract" * doctest::test_suite("functional::get_function_composition") * doctest::skip())
{
    NMTOOLS_TESTING_DECLARE_NS(view,subtract,case1);
    using namespace args;

    auto x = view::divide(a,3);
    auto y = view::subtract(a,x);

    auto function = fn::get_function_composition(y);
    auto expect =
        fn::broadcast_binary_ufunc[y.attributes()]
        * fn::broadcast_binary_ufunc[x.attributes()]
    ;

    NMTOOLS_ASSERT_EQUAL( function, expect );
    // TODO: fix, reorder result from divide to subtract rhs
    NMTOOLS_ASSERT_CLOSE( function (a) (a) (3), y );
}

TEST_CASE("divide_subtract" * doctest::test_suite("functional::get_function_composition") )
{
    NMTOOLS_TESTING_DECLARE_NS(view,subtract,case1);
    using namespace args;

    auto x = view::divide(a,3);
    auto y = view::subtract(x,a);

    auto function = fn::get_function_composition(y);
    auto expect =
        fn::broadcast_binary_ufunc[y.attributes()]
        * fn::broadcast_binary_ufunc[x.attributes()]
    ;

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( function (a) (3) (a), y );
}

TEST_CASE("divide_subtract" * doctest::test_suite("functional::get_function_operands"))
{
    NMTOOLS_TESTING_DECLARE_NS(view,subtract,case1);
    using namespace args;

    auto x = view::divide(a,3);
    auto y = view::subtract(x,b);

    // len == 3 because expanded
    auto operands = fn::get_function_operands(y);
    auto expect = nmtools_tuple<decltype(a)&,int,decltype(b)&>{a,3,b};

    CHECK( nm::len(operands) == nm::len(expect) );
    CHECK( &nm::at(operands,0_ct) == &nm::at(expect,0_ct) );
    CHECK( nm::at(operands,1_ct) == nm::at(expect,1_ct) );
    CHECK( &nm::at(operands,2_ct) == &nm::at(expect,2_ct) );
}

TEST_CASE("divide_subtract" * doctest::test_suite("functional::apply"))
{
    NMTOOLS_TESTING_DECLARE_NS(view,subtract,case1);
    using namespace args;

    auto x = view::divide(a,3);
    auto y = view::subtract(x,b);

    auto function = fn::get_function_composition(y);
    auto operands = fn::get_function_operands(y);
    
    NMTOOLS_ASSERT_CLOSE( (fn::apply(function,operands)), y );
}