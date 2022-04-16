#include "nmtools/array/functional/ufuncs/reciprocal.hpp"
#include "nmtools/testing/data/array/reciprocal.hpp"
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

TEST_CASE("reciprocal(case1)" * doctest::test_suite("functional::reciprocal"))
{
    NMTOOLS_TESTING_DECLARE_NS(view, reciprocal, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::reciprocal, a );
    FUNCTIONAL_SUBCASE( "case1", fn::reciprocal, a_a );
    FUNCTIONAL_SUBCASE( "case1", fn::reciprocal, a_f );
    FUNCTIONAL_SUBCASE( "case1", fn::reciprocal, a_h );
    FUNCTIONAL_SUBCASE( "case1", fn::reciprocal, a_d );
}