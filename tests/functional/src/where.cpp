#include "nmtools/array/functional/where.hpp"
#include "nmtools/testing/data/array/where.hpp"
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


TEST_CASE("where(case1)" * doctest::test_suite("functional::where"))
{
    NMTOOLS_TESTING_USE_CASE(view, where, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::where, condition, x, y );
    FUNCTIONAL_SUBCASE( "case1", fn::where, condition_a, x_a, y_a );
    FUNCTIONAL_SUBCASE( "case1", fn::where, condition_f, x_f, y_f );
    FUNCTIONAL_SUBCASE( "case1", fn::where, condition_h, x_h, y_h );
    FUNCTIONAL_SUBCASE( "case1", fn::where, condition_d, x_d, y_d );
}