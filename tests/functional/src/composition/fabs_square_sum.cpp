#include "nmtools/array/functional/ufuncs/square.hpp"
#include "nmtools/array/functional/ufuncs/subtract.hpp"
#include "nmtools/array/functional/ufuncs/fabs.hpp"
#include "nmtools/array/functional/ufuncs/add.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"
#include "nmtools/array/view/sum.hpp"
#include "nmtools/testing/data/array/fabs.hpp"
#include "nmtools/testing/doctest.hpp"

namespace fn = nmtools::functional;
namespace view = nmtools::view;

TEST_CASE("fabs_square_sum" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_DECLARE_NS(view,fabs,case1);
    using namespace args;

    auto dtype = nm::None;
    auto axis = 0;
    auto x = view::fabs(a);
    auto y = view::square(x);
    auto z = view::sum(y,axis);

    auto function = fn::get_function_composition(z);
    auto expect =
        fn::reduce_add[z.axis][dtype][z.initial][z.keepdims]
        * fn::square * fn::fabs
    ;

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( function (a), z );
}

using namespace nmtools::literals;

TEST_CASE("fabs_square_sum" * doctest::test_suite("functional::get_function_operands"))
{
    NMTOOLS_TESTING_DECLARE_NS(view,fabs,case1);
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
    NMTOOLS_TESTING_DECLARE_NS(view,fabs,case1);
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