#include "nmtools/array/functional/expand_dims.hpp"
#include "nmtools/testing/data/array/expand_dims.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace fn = nm::functional;

#define FUNCTIONAL_SUBCASE(subcase_name, function, ...) \
SUBCASE(subcase_name) \
{ \
    auto result = function (__VA_ARGS__); \
    NMTOOLS_REQUIRE_EQUAL( nm::shape(result), nm::shape(expect::expected) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}


TEST_CASE("expand_dims(case1)" * doctest::test_suite("functional::expand_dims"))
{
    NMTOOLS_TESTING_DECLARE_NS(expand_dims, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::expand_dims[axis], array );
    FUNCTIONAL_SUBCASE( "case1", fn::expand_dims[axis], array_a );
    FUNCTIONAL_SUBCASE( "case1", fn::expand_dims[axis], array_f );
    FUNCTIONAL_SUBCASE( "case1", fn::expand_dims[axis], array_h );
    FUNCTIONAL_SUBCASE( "case1", fn::expand_dims[axis], array_d );
}

TEST_CASE("expand_dims(case2)" * doctest::test_suite("functional::expand_dims"))
{
    NMTOOLS_TESTING_DECLARE_NS(expand_dims, case2);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case2", fn::expand_dims[axis], array );
    FUNCTIONAL_SUBCASE( "case2", fn::expand_dims[axis], array_a );
    FUNCTIONAL_SUBCASE( "case2", fn::expand_dims[axis], array_f );
    FUNCTIONAL_SUBCASE( "case2", fn::expand_dims[axis], array_h );
    FUNCTIONAL_SUBCASE( "case2", fn::expand_dims[axis], array_d );
}