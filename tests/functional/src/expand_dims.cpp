#include "nmtools/array/functional/expand_dims.hpp"
#include "nmtools/testing/data/array/expand_dims.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace fn = nm::functional;

using nmtools::unwrap;

#define FUNCTIONAL_SUBCASE(subcase_name, function, ...) \
SUBCASE(subcase_name) \
{ \
    auto result = function (__VA_ARGS__); \
    NMTOOLS_REQUIRE_EQUAL( nm::shape(result), nm::shape(expect::expected) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}


TEST_CASE("expand_dims(case1)" * doctest::test_suite("functional::expand_dims"))
{
    NMTOOLS_TESTING_USE_CASE(expand_dims, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::expand_dims[axis], array );
    FUNCTIONAL_SUBCASE( "case1", fn::expand_dims[axis], array_a );
    FUNCTIONAL_SUBCASE( "case1", fn::expand_dims[axis], array_f );
    FUNCTIONAL_SUBCASE( "case1", fn::expand_dims[axis], array_h );
    FUNCTIONAL_SUBCASE( "case1", fn::expand_dims[axis], array_d );
}

TEST_CASE("expand_dims(case2)" * doctest::test_suite("functional::expand_dims"))
{
    NMTOOLS_TESTING_USE_CASE(expand_dims, case2);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case2", fn::expand_dims[axis], array );
    FUNCTIONAL_SUBCASE( "case2", fn::expand_dims[axis], array_a );
    FUNCTIONAL_SUBCASE( "case2", fn::expand_dims[axis], array_f );
    FUNCTIONAL_SUBCASE( "case2", fn::expand_dims[axis], array_h );
    FUNCTIONAL_SUBCASE( "case2", fn::expand_dims[axis], array_d );
}

namespace view = nmtools::view;

TEST_CASE("expand_dims" * doctest::test_suite("functional::get_function_composition") * doctest::may_fail())
{
    NMTOOLS_TESTING_USE_CASE(expand_dims, case2);
    using namespace args;

    auto a = view::expand_dims(array,axis);

    auto function = fn::get_function_composition(a);
    auto expect = fn::expand_dims[axis];

    NMTOOLS_ASSERT_EQUAL( function, expect );
}

TEST_CASE("expand_dims" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(expand_dims, case2);
    using namespace args;

    auto a = view::expand_dims(array,axis);

    auto function = fn::get_function_composition(a);
    auto expect = fn::indexing[unwrap(a).attributes()];

    NMTOOLS_ASSERT_EQUAL( function, expect );
}