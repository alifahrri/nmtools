#include "nmtools/array/ufuncs/square.hpp"
#include "nmtools/array/ufuncs/subtract.hpp"
#include "nmtools/array/ufuncs/fabs.hpp"
#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/core/ufunc/ufunc.hpp"
#include "nmtools/array/sum.hpp"
#include "nmtools/testing/data/array/fabs.hpp"
#include "nmtools/testing/doctest.hpp"

namespace fn = nmtools::functional;
namespace view = nmtools::view;

TEST_CASE("fabs_square_sum" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(view,fabs,case1);
    using namespace args;

    auto axis = 0;
    auto x = view::fabs(a);
    auto y = view::square(x);
    auto z = view::sum(y,axis);

    auto function = fn::get_function_composition(z);
    auto expect =
          fn::reduce[z.attributes()]
        * fn::unary_ufunc[y.attributes()]
        * fn::unary_ufunc[x.attributes()]
    ;

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( function (a), z );
}

using namespace nmtools::literals;

TEST_CASE("fabs_square_sum" * doctest::test_suite("functional::get_function_operands"))
{
    NMTOOLS_TESTING_USE_CASE(view,fabs,case1);
    using namespace args;

    // auto dtype = nm::None;
    auto axis = 0;
    auto x = view::fabs(a);
    auto y = view::square(x);
    auto z = view::sum(y,axis);

    auto operands = fn::get_function_operands(z);
    auto expect = nmtools_tuple<decltype(a)&>{a};

    CHECK( nm::len(operands) == nm::len(expect) );
    CHECK( &nm::at(operands,0_ct) == &nm::at(expect,0_ct) );
}

TEST_CASE("fabs_square_sum" * doctest::test_suite("functional::apply"))
{
    NMTOOLS_TESTING_USE_CASE(view,fabs,case1);
    using namespace args;

    // auto dtype = nm::None;
    auto axis = 0;
    auto x = view::fabs(a);
    auto y = view::square(x);
    auto z = view::sum(y,axis);

    auto function = fn::get_function_composition(z);
    auto operands = fn::get_function_operands(z);
    
    NMTOOLS_ASSERT_CLOSE( (fn::apply(function,operands)), z );
}