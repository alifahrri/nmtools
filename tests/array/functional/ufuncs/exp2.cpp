#include "nmtools/array/functional/ufuncs/exp2.hpp"
#include "nmtools/testing/data/array/exp2.hpp"
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

TEST_CASE("exp2(case1)" * doctest::test_suite("functional::exp2"))
{
    NMTOOLS_TESTING_DECLARE_NS(view, exp2, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::exp2, a );
    FUNCTIONAL_SUBCASE( "case1", fn::exp2, a_a );
    FUNCTIONAL_SUBCASE( "case1", fn::exp2, a_f );
    FUNCTIONAL_SUBCASE( "case1", fn::exp2, a_h );
    FUNCTIONAL_SUBCASE( "case1", fn::exp2, a_d );
}