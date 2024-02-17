#include "nmtools/array/functional/ufuncs/add.hpp"
#include "nmtools/array/functional/ufuncs/multiply.hpp"
#include "nmtools/array/functional/ufuncs/tanh.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"
#include "nmtools/testing/data/array/multiply.hpp"
#include "nmtools/testing/doctest.hpp"

namespace fn = nmtools::functional;
namespace view = nmtools::view;
namespace meta = nmtools::meta;

using namespace nmtools::literals;

// NOTE: somehow get_function_composition produces wrong result for 3(+?) functions
// TODO: fix
TEST_CASE("multiply_add_tanh" * doctest::test_suite("functional::get_function_composition") * doctest::may_fail())
{
    NMTOOLS_TESTING_DECLARE_NS(view,multiply,case1);
    using namespace args;

    auto x = view::multiply(a,b);
    auto y = view::add(x,b);
    auto z = view::tanh(y);

    NMTOOLS_ASSERT_EQUAL( fn::get_function(z), fn::tanh );
    NMTOOLS_ASSERT_EQUAL( fn::get_function(y), fn::add );
    NMTOOLS_ASSERT_EQUAL( fn::get_function(x), fn::multiply );

    auto z_operands = fn::get_operands(z);
    NMTOOLS_ASSERT_EQUAL( nm::len(z_operands), 1 );
    NMTOOLS_STATIC_CHECK_IS_SAME( decltype(z_operands), nmtools_tuple<decltype(y)> );

    auto z_operand  = at(z_operands,0_ct);
    using z_operand_t = meta::remove_cvref_pointer_t<decltype(z_operand)>;
    NMTOOLS_ASSERT_EQUAL( meta::is_view_v<z_operand_t>, true );
    NMTOOLS_ASSERT_EQUAL( fn::get_function(z_operand), fn::add );

    auto z_sub_operands = fn::get_operands(z_operand);
    NMTOOLS_ASSERT_EQUAL( nm::len(z_sub_operands), 2 );

    auto z_sub_operand_0 = at(z_sub_operands,0_ct);
    using z_sub_operand_0_t = meta::remove_cvref_pointer_t<decltype(z_sub_operand_0)>;
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_view, z_sub_operand_0_t );

    auto function = fn::get_function_composition(z);
    auto expect =
        fn::tanh * fn::add * fn::multiply
    ;
    NMTOOLS_ASSERT_EQUAL( function, expect );
    static_assert( decltype(expect)::arity == 3 );
    static_assert( decltype(function)::arity == 3 );
    // NMTOOLS_ASSERT_CLOSE( function (a) (b) (3), z );
}

TEST_CASE("multiply_add_tanh" * doctest::test_suite("functional::get_function_operands"))
{
    NMTOOLS_TESTING_DECLARE_NS(view,multiply,case1);
    using namespace args;

    auto x = view::multiply(a,b);
    auto y = view::add(x,b);
    auto z = view::tanh(y);

    auto operands = fn::get_function_operands(z);
    auto expect = nmtools_tuple<decltype(a)&,decltype(b)&,decltype(b)&>{a,b,b};
    CHECK( nm::len(operands) == nm::len(expect) );
    CHECK( &nm::at(operands,0_ct) == &nm::at(expect,0_ct) );
    CHECK( &nm::at(operands,1_ct) == &nm::at(expect,1_ct) );
    CHECK( &nm::at(operands,2_ct) == &nm::at(expect,2_ct) );
}

// TODO: fix compile error
#if 0
TEST_CASE("multiply_add_tanh" * doctest::test_suite("functional::apply"))
{
    NMTOOLS_TESTING_DECLARE_NS(view,multiply,case1);
    using namespace args;

    auto x = view::multiply(a,b);
    auto y = view::add(x,b);
    auto z = view::tanh(y);

    auto function = fn::get_function_composition(z);
    auto operands = fn::get_function_operands(z);
    
    NMTOOLS_ASSERT_CLOSE( (fn::apply(function,operands)), z );
}
#endif