#include "nmtools/array/functional/ufuncs/tanh.hpp"
#include "nmtools/testing/data/array/tanh.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace fn = nm::functional;

#define FUNCTIONAL_SUBCASE(subcase_name, function, ...) \
SUBCASE(subcase_name) \
{ \
    auto result = function (__VA_ARGS__); \
    NMTOOLS_REQUIRE_EQUAL( nm::shape(result), nm::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("tanh(case1)" * doctest::test_suite("functional::tanh"))
{
    NMTOOLS_TESTING_DECLARE_NS(view, tanh, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::tanh, a );
    FUNCTIONAL_SUBCASE( "case1", fn::tanh, a_a );
    FUNCTIONAL_SUBCASE( "case1", fn::tanh, a_f );
    FUNCTIONAL_SUBCASE( "case1", fn::tanh, a_h );
    FUNCTIONAL_SUBCASE( "case1", fn::tanh, a_d );
}

namespace view = nmtools::view;

TEST_CASE("tanh" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_DECLARE_NS(view,tanh,case1);
    using namespace args;

    auto array = view::tanh(a);

    auto function = fn::get_function_composition(array);
    auto expect = fn::tanh;

    NMTOOLS_ASSERT_EQUAL( function, expect );
}

TEST_CASE("tanh" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_DECLARE_NS(view,tanh,case1);
    using namespace args;

    auto array = view::tanh(a);

    auto function = fn::get_function_composition(array);
    auto expect = fn::unary_ufunc[array.attributes()];

    NMTOOLS_ASSERT_EQUAL( function, expect );
}